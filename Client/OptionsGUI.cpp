/*
------------------------[ Lbanet Source ]-------------------------
Copyright (C) 2009
Author: Vivien Delage [Rincevent_123]
Email : vdelage@gmail.com

-------------------------------[ GNU License ]-------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
*/

#include "OptionsGUI.h"
#include <CEGUI.h>
#include <iostream>
#include "ConfigurationManager.h"
#include "LogHandler.h"
#include "MusicHandler.h"
#include "OSGHandler.h"
#include "EventsQueue.h"
#include "ClientExtendedEvents.h"
#include "DataLoader.h"
#include "Localizer.h"
#include "GUILocalizationCallback.h"
#include "SynchronizedTimeHandler.h"
#include "DataDirHandler.h"


// Sample sub-class for ListboxTextItem that auto-sets the selection brush
// image.  This saves doing it manually every time in the code.
class MyOptListItem : public CEGUI::ListboxTextItem
{
public:
    MyOptListItem (const CEGUI::String& text) : CEGUI::ListboxTextItem(text)
    {
        setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    }
};


/***********************************************************
constructor
***********************************************************/
OptionsGUI::OptionsGUI()
{
}


/***********************************************************
destructor
***********************************************************/
OptionsGUI::~OptionsGUI()
{
}

/***********************************************************
initialize the GUI
***********************************************************/
void OptionsGUI::Initialize()
{
	try
	{
		// Load the Imageset that has the pictures for our button.
		_root = CEGUI::WindowManager::getSingleton().loadWindowLayout( "Options.layout",
								"", "", &MyPropertyCallback);

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsFrameW/OK"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&OptionsGUI::HandleOK, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsFrameW/Cancel"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&OptionsGUI::HandleCancel, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsFrameW/Apply"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&OptionsGUI::HandleApply, this));

		static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsFrameW"))->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&OptionsGUI::HandleCancel, this));



		// add screen resolutions to the combo box
		CEGUI::Combobox * cb = static_cast<CEGUI::Combobox *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Video/ComboRes"));

		std::ifstream filesc(DataDirHandler::getInstance()->GetDataDirPath() + "/screen_resolutions.txt");
		std::string restmp;
		while(!filesc.eof())
		{
			filesc >> restmp;
			cb->addItem(new CEGUI::ListboxTextItem(restmp));
		}

		{
		CEGUI::Combobox * cbatype = static_cast<CEGUI::Combobox *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltxtLangcb"));
			cbatype->addItem(new MyOptListItem("en"));
			cbatype->addItem(new MyOptListItem("fr"));
			cbatype->addItem(new MyOptListItem("de"));
			cbatype->addItem(new MyOptListItem("sp"));
			cbatype->addItem(new MyOptListItem("it"));
			cbatype->addItem(new MyOptListItem("ru"));

			_lang = Localizer::getInstance()->GetLanguage();
			cbatype->setText(_lang);
		}

		{
			CEGUI::Combobox * combocamtype = static_cast<CEGUI::Combobox *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Video/cbcameratype"));
			if(combocamtype)
			{
				MyOptListItem * tmp0 = new MyOptListItem((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 89).c_str());
				tmp0->setID(0);
				combocamtype->addItem(tmp0);

				MyOptListItem * tmp1 = new MyOptListItem((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 90).c_str());
				tmp1->setID(1);
				combocamtype->addItem(tmp1);

				MyOptListItem * tmp2 = new MyOptListItem((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 91).c_str());
				tmp2->setID(2);
				combocamtype->addItem(tmp2);

				MyOptListItem * tmp3 = new MyOptListItem((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 92).c_str());
				tmp3->setID(3);
				combocamtype->addItem(tmp3);
			}
		}


		{
			CEGUI::Combobox * combocamtype = static_cast<CEGUI::Combobox *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Video/cbshadow"));
			if(combocamtype)
			{
				MyOptListItem * tmp0 = new MyOptListItem((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 102).c_str());
				tmp0->setID(0);
				combocamtype->addItem(tmp0);

				MyOptListItem * tmp1 = new MyOptListItem((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 103).c_str());
				tmp1->setID(1);
				combocamtype->addItem(tmp1);

				MyOptListItem * tmp2 = new MyOptListItem((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 104).c_str());
				tmp2->setID(2);
				combocamtype->addItem(tmp2);

				MyOptListItem * tmp3 = new MyOptListItem((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 105).c_str());
				tmp3->setID(3);
				combocamtype->addItem(tmp3);
			}
		}


		Displayed();
		SendNameColor();


		static_cast<CEGUI::TabControl *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsTab"))->setSelectedTab("OptionsTab/General");

	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init login gui: ") + ex.getMessage().c_str());
		_root = NULL;
	}
}



/***********************************************************
handle connect button event
***********************************************************/
bool OptionsGUI::HandleOK(const CEGUI::EventArgs& e)
{
	Apply();
	Quit();
	return true;
}


/***********************************************************
handle cancel button event
***********************************************************/
bool OptionsGUI::HandleCancel (const CEGUI::EventArgs& e)
{
	Cancel();
	Quit();
	return true;
}


/***********************************************************
handle cancel button event
***********************************************************/
bool OptionsGUI::HandleApply (const CEGUI::EventArgs& e)
{
	Apply();
	return true;
}



/***********************************************************
apply new changes
***********************************************************/
void OptionsGUI::Apply()
{
	try
	{

		//------------- handle general tab
		{
			CEGUI::Combobox * cbatype = static_cast<CEGUI::Combobox *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltxtLangcb"));
			if(cbatype)
			{
				std::string sp = cbatype->getText().c_str();
				if(_lang != sp)
				{
					_lang = sp;
					Localizer::getInstance()->SetLanguage(_lang);
					ConfigurationManager::GetInstance()->SetValue("Options.General.Language", _lang);
				}
			}

			{
				bool nchanged = false;

				//handle skin color
				CEGUI::Spinner *sbgs = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextSkinColorv_name"));
				if(sbgs)
				{
					int sp = (int)sbgs->getCurrentValue();
					if(_skinC != sp)
					{
						nchanged = true;
						_skinC = sp;
					}
				}

				//handle eyes color
				CEGUI::Spinner *sbgsG = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextEyesColorv_name"));
				if(sbgsG)
				{
					int sp = (int)sbgsG->getCurrentValue();
					if(_eyesC != sp)
					{
						nchanged = true;
						_eyesC = sp;
					}
				}

				//handle hair color
				CEGUI::Spinner *sbgsB = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextHairColorv_name"));
				if(sbgsB)
				{
					int sp = (int)sbgsB->getCurrentValue();
					if(_hairC != sp)
					{
						nchanged = true;
						_hairC = sp;
					}
				}

				if(nchanged)
					SendPlayerColor();
			}




			{
				bool nchanged = false;

				//handle name R
				CEGUI::Spinner *sbgs = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextRv_name"));
				if(sbgs)
				{
					int sp = (int)sbgs->getCurrentValue();
					if(_nameR != sp)
					{
						nchanged = true;
						_nameR = sp;
						ConfigurationManager::GetInstance()->SetValue("Options.General.NameR", _nameR);
					}
				}

				//handle name G
				CEGUI::Spinner *sbgsG = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextGv_name"));
				if(sbgsG)
				{
					int sp = (int)sbgsG->getCurrentValue();
					if(_nameG != sp)
					{
						nchanged = true;
						_nameG = sp;
						ConfigurationManager::GetInstance()->SetValue("Options.General.NameG", _nameG);
					}
				}

				//handle name B
				CEGUI::Spinner *sbgsB = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextBv_name"));
				if(sbgsB)
				{
					int sp = (int)sbgsB->getCurrentValue();
					if(_nameB != sp)
					{
						nchanged = true;
						_nameB = sp;
						ConfigurationManager::GetInstance()->SetValue("Options.General.NameB", _nameB);
					}
				}

				if(nchanged)
					SendNameColor();
			}
		}



		//------------- handle video tab
		{
			if(!DataDirHandler::getInstance()->IsInEditorMode())
			{
				bool changeRes = false;

				//handle screen resolution
				CEGUI::Combobox * cb = static_cast<CEGUI::Combobox *> (
					CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Video/ComboRes"));
				if(cb)
				{
					CEGUI::ListboxItem *itm = cb->getSelectedItem();
					if(itm)
					{
						std::string selectedres = itm->getText().c_str();
						int posX = selectedres.find("x");
						int xs =  atoi(selectedres.substr(0, posX).c_str());
						int ys =  atoi(selectedres.substr(posX+1).c_str());

						if(xs != _currScreenX || ys != _currScreenY)
						{
							changeRes = true;
							_currScreenX = xs;
							_currScreenY = ys;
						}
					}
				}


				//handle fullscreen
				CEGUI::Checkbox * checkbfull = static_cast<CEGUI::Checkbox *> (
					CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Video/cbfullscreen"));
				if(checkbfull)
				{
					bool selectedb = checkbfull->isSelected();
					if(selectedb != _currFullscreen)
					{
						changeRes = true;
						_currFullscreen = selectedb;
					}
				}

				if(changeRes)
				{
					EventsQueue::getReceiverQueue()->AddEvent(new ResizeEvent(_currScreenX, _currScreenY, _currFullscreen));
				}
			}

			{
				//handle perpective
				CEGUI::Combobox * combocamtype = static_cast<CEGUI::Combobox *> (
					CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Video/cbcameratype"));
				if(combocamtype)
				{
					CEGUI::ListboxItem* selected = combocamtype->getSelectedItem();
					if(selected)
					{
						int sid = selected->getID();
						if(sid !=  _currCamType)
						{
							_currCamType = sid;
							OsgHandler::getInstance()->ToggleCameraType(_currCamType);
						}
					}
				}
			}

			{
				//handle shadow
				CEGUI::Combobox * combocamtype = static_cast<CEGUI::Combobox *> (
					CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Video/cbshadow"));
				if(combocamtype)
				{
					CEGUI::ListboxItem* selected = combocamtype->getSelectedItem();
					if(selected)
					{
						int sid = selected->getID();
						if(sid !=  _currShadowType)
						{
							_currShadowType = sid;
							OsgHandler::getInstance()->ToggleShadow(_currShadowType);
						}
					}
				}
			}
		}



		//------------- handle sound tab
		{
			//handle general sound
			CEGUI::Scrollbar *sbgs = static_cast<CEGUI::Scrollbar *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Sound/sbgeneralvolume"));
			if(sbgs)
			{
				int sp = (int)sbgs->getScrollPosition ();
				if(_currGenVolume != sp)
				{
					_currGenVolume = sp;
					MusicHandler::getInstance()->SetGeneralVolume(_currGenVolume);
					ConfigurationManager::GetInstance()->SetValue("Options.Sound.GeneralVolume", _currGenVolume);
				}
			}



			//handle music sound
			CEGUI::Scrollbar *sbms = static_cast<CEGUI::Scrollbar *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Sound/sbMusicVolume"));
			if(sbms)
			{
				int sp = (int)sbms->getScrollPosition ();
				if(_currMusicVolume != sp)
				{
					_currMusicVolume = sp;
					MusicHandler::getInstance()->SetMusicVolume(_currMusicVolume);
					ConfigurationManager::GetInstance()->SetValue("Options.Sound.MusicVolume", _currMusicVolume);
				}
			}

			//handle sample sound
			CEGUI::Scrollbar *sbmss = static_cast<CEGUI::Scrollbar *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Sound/sbSampleVolume"));
			if(sbmss)
			{
				int sp = (int)sbmss->getScrollPosition ();
				if(_currSampleVolume != sp)
				{
					_currSampleVolume = sp;
					MusicHandler::getInstance()->SetSampleVolume(_currSampleVolume);
					ConfigurationManager::GetInstance()->SetValue("Options.Sound.SampleVolume", _currSampleVolume);
				}
			}
		}


		//------------- handle gui tab
		{
			//handle font size
			CEGUI::Spinner *sbgs = static_cast<CEGUI::Spinner *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Gui/fontsize"));
			if(sbgs)
			{
				int sp = (int)sbgs->getCurrentValue();
				if(_fontSize != sp)
				{
					_fontSize = sp;
					ConfigurationManager::GetInstance()->SetValue("Options.Gui.FontSize", _fontSize);
					EventsQueue::getReceiverQueue()->AddEvent(new NewFontSizeEvent());
				}
			}
		}
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception applying options: ") + ex.getMessage().c_str());
		_root = NULL;
	}
}

/***********************************************************
cancel changes
***********************************************************/
void OptionsGUI::Cancel()
{
	try
	{
		//------------- handle general tab
		{

			CEGUI::Combobox * cbatype = static_cast<CEGUI::Combobox *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltxtLangcb"));
			if(cbatype)
				cbatype->setText(_lang);

			{
				//handle skin color
				CEGUI::Spinner *sbgs = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextSkinColorv_name"));
				if(sbgs)
				{
					std::stringstream strs;
					strs<<_skinC;
					sbgs->setText(strs.str());
				}

				//handle eyes color
				CEGUI::Spinner *sbgsG = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextEyesColorv_name"));
				if(sbgsG)
				{
					std::stringstream strs;
					strs<<_eyesC;
					sbgsG->setText(strs.str());
				}

				//handle hair color
				CEGUI::Spinner *sbgsB = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextHairColorv_name"));
				if(sbgsB)
				{
					std::stringstream strs;
					strs<<_hairC;
					sbgsB->setText(strs.str());
				}
			}


			{
				//handle name R
				CEGUI::Spinner *sbgs = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextRv_name"));
				if(sbgs)
				{
					std::stringstream strs;
					strs<<_nameR;
					sbgs->setText(strs.str());
				}

				//handle name G
				CEGUI::Spinner *sbgsG = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextGv_name"));
				if(sbgsG)
				{
					std::stringstream strs;
					strs<<_nameG;
					sbgsG->setText(strs.str());
				}

				//handle name B
				CEGUI::Spinner *sbgsB = static_cast<CEGUI::Spinner *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/General/lbltextBv_name"));
				if(sbgsB)
				{
					std::stringstream strs;
					strs<<_nameB;
					sbgsB->setText(strs.str());
				}
			}

		}


		//------------- handle video tab
		{
			//handle screen resolution
			CEGUI::Combobox * cb = static_cast<CEGUI::Combobox *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Video/ComboRes"));
			if(cb)
			{
				std::stringstream strs;
				strs<<_currScreenX<<"x"<<_currScreenY;
				cb->setText(strs.str());
			}

			//handle fullscreen
			CEGUI::Checkbox * checkbfull = static_cast<CEGUI::Checkbox *> (
				CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Video/cbfullscreen"));
			if(checkbfull)
				checkbfull->setSelected(_currFullscreen);

			{
				//handle perspective
				CEGUI::Combobox * combocamtype = static_cast<CEGUI::Combobox *> (
					CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Video/cbcameratype"));
				if(combocamtype)
				{
					combocamtype->setItemSelectState(_currCamType, true);
				}
			}

			{
				//handle shadow
				CEGUI::Combobox * combocamtype = static_cast<CEGUI::Combobox *> (
					CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Video/cbshadow"));
				if(combocamtype)
				{
					combocamtype->setItemSelectState(_currShadowType, true);
				}
			}
		}


		//------------- handle sound tab
		{
			//handle general sound
			CEGUI::Scrollbar *sbgs = static_cast<CEGUI::Scrollbar *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Sound/sbgeneralvolume"));
			if(sbgs)
				sbgs->setScrollPosition((float)_currGenVolume);


			//handle music sound
			CEGUI::Scrollbar *sbms = static_cast<CEGUI::Scrollbar *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Sound/sbMusicVolume"));
			if(sbms)
				sbms->setScrollPosition((float)_currMusicVolume);


			//handle sample sound
			CEGUI::Scrollbar *sbmss = static_cast<CEGUI::Scrollbar *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Sound/sbSampleVolume"));
			if(sbmss)
				sbmss->setScrollPosition((float)_currSampleVolume);
			
		}



		//------------- handle gui tab
		{
			//handle font size
			CEGUI::Spinner *sbgs = static_cast<CEGUI::Spinner *> (
			CEGUI::WindowManager::getSingleton().getWindow("OptionsTab/Gui/fontsize"));
			if(sbgs)
			{
				std::stringstream strs;
				strs<<_fontSize;
				sbgs->setText(strs.str());
			}
		}
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception cancelling options: ") + ex.getMessage().c_str());
		_root = NULL;
	}
}

/***********************************************************
quit windows
***********************************************************/
void OptionsGUI::Quit()
{
	EventsQueue::getReceiverQueue()->AddEvent(new GuiExitEvent());

}


/***********************************************************
 called to infrom the gui that it is displayed
***********************************************************/
void OptionsGUI::Displayed()
{
	//init the values from file
	_nameR = ConfigurationManager::GetInstance()->GetValue("Options.General.NameR", 200);
	_nameG = ConfigurationManager::GetInstance()->GetValue("Options.General.NameG", 200);
	_nameB = ConfigurationManager::GetInstance()->GetValue("Options.General.NameB", 200);

	_skinC = _savedskinC;
	_eyesC = _savedeyesC;
	_hairC = _savedhairC;

	_currScreenX = ConfigurationManager::GetInstance()->GetValue("Display.Screen.ScreenResolutionX", 800);
	_currScreenY = ConfigurationManager::GetInstance()->GetValue("Display.Screen.ScreenResolutionY", 600);
	_currFullscreen = ConfigurationManager::GetInstance()->GetValue("Display.Screen.Fullscreen", false);
	_currCamType = ConfigurationManager::GetInstance()->GetValue("Display.Camera.CameraType", 0);
	_currShadowType = ConfigurationManager::GetInstance()->GetValue("Display.ShadowType", 1);
	

	_currGenVolume = ConfigurationManager::GetInstance()->GetValue("Options.Sound.GeneralVolume", 100);
	_currMusicVolume = ConfigurationManager::GetInstance()->GetValue("Options.Sound.MusicVolume", 20);
	_currSampleVolume = ConfigurationManager::GetInstance()->GetValue("Options.Sound.SampleVolume", 100);
	

	_fontSize = ConfigurationManager::GetInstance()->GetValue("Options.Gui.FontSize", 10);

	Cancel();
}


/***********************************************************
send name color
***********************************************************/
void OptionsGUI::SendNameColor()
{
	std::stringstream colorstr;
	colorstr << "FF" ;
	colorstr <<((_nameR < 16)?"0":"") << std::uppercase <<std::hex << _nameR; 
	colorstr <<((_nameG < 16)?"0":"") << std::uppercase << std::hex << _nameG;
	colorstr <<((_nameB < 16)?"0":"") << std::uppercase << std::hex << _nameB;

	EventsQueue::getReceiverQueue()->AddEvent(new PlayerNameColorChangedEvent(colorstr.str()));
}



/***********************************************************
send player color
***********************************************************/
void OptionsGUI::SendPlayerColor()
{
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdatePlayerColorEvent(
													SynchronizedTimeHandler::GetCurrentTimeDouble(),
													_skinC, _eyesC, _hairC));
}

/***********************************************************
refresh player color
***********************************************************/
void OptionsGUI::RefreshPlayerColor(int skin, int eyes, int hair)
{
	_savedskinC = skin;
	_savedeyesC = eyes;
	_savedhairC = hair;
}