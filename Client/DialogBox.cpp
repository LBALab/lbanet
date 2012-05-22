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

#include "DialogBox.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "ImageSetHandler.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "DataLoader.h"
#include "OSGHandler.h"
#include "Localizer.h"
#include "GUILocalizationCallback.h"
#include "StringHelperFuncs.h"
#include "ClientExtendedEvents.h"
#include "ClientExtendedTypes.h"

#include "MusicHandler.h"

#include <iostream>
#include <algorithm>
#include <CEGUI.h>


// Sample sub-class for ListboxTextItem that auto-sets the selection brush
// image.  This saves doing it manually every time in the code.
class MyDialogItem : public CEGUI::ListboxTextItem
{
private:
	CEGUI::FormattedRenderedString * d_formattedRenderedString;

public:
    MyDialogItem (const CEGUI::String& text, size_t index) 
		: CEGUI::ListboxTextItem(text), _SelectionIdx(index)
    {
        setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");

        d_formattedRenderedString =
            new CEGUI::RenderedStringWordWrapper
                <CEGUI::LeftAlignedRenderedString>(d_renderedString);
    }

	//! destructor
    ~MyDialogItem ()
    {
        delete d_formattedRenderedString;
    }

	/*************************************************************************
		Required implementations of pure virtuals from the base class.
	*************************************************************************/
    CEGUI::Size getPixelSize(void) const
	{
		using namespace CEGUI;

		if (!d_renderedStringValid)
			parseTextString();

		CEGUI::Size parentsi = getOwnerWindow()->getInnerRectClipper().getSize();
		parentsi.d_width -= 20; // TODO - change constant by the real value of the scrollbar
		
        d_formattedRenderedString->format(parentsi);
		return CEGUI::Size(parentsi.d_width, d_formattedRenderedString->getVerticalExtent());
	}


    void draw(CEGUI::GeometryBuffer& buffer, const CEGUI::Rect& targetRect, float alpha, 
					const CEGUI::Rect* clipper) const
	{
		using namespace CEGUI;

		if (d_selected && d_selectBrush != 0)
			d_selectBrush->draw(buffer, targetRect, clipper,
								getModulateAlphaColourRect(d_selectCols, alpha));

		if (!d_renderedStringValid)
			parseTextString();

        d_formattedRenderedString->format(targetRect.getSize());

		const ColourRect final_colours(
			getModulateAlphaColourRect(ColourRect(0xFFFFFFFF), alpha));

        d_formattedRenderedString->draw(buffer,
                                        targetRect.getPosition(),									
										&final_colours, clipper);
	}

	size_t _SelectionIdx;
};





/***********************************************************
execute function
***********************************************************/
void FinishAnimDialogAction::Execute()
{
	if(_dialoghandler)
	{
		_dialoghandler->FinishTextAnim();

		if(_nextaction)
		{
			if(_directnext)
				_nextaction->Execute();
			else
				_dialoghandler->SetSpaceAction(_nextaction);
		}
	}
}

/***********************************************************
execute function
***********************************************************/
void CloseDialogAction::Execute()
{
	if(_dialoghandler)
		_dialoghandler->CloseDialog();
}

/***********************************************************
execute function
***********************************************************/
void ShowPChoiceDialogAction::Execute()
{
	if(_dialoghandler)
		_dialoghandler->DisplayPChoices(_pchoices);
}

/***********************************************************
execute function
***********************************************************/
void Show1ChoiceDialogAction::Execute()
{
	if(_dialoghandler)
		_dialoghandler->DisplayPChoice(_pchoice);
}



/***********************************************************
execute function
***********************************************************/
void PlayerPChoiceVoiceDialogAction::Execute()
{
	if(_dialoghandler)
		_dialoghandler->PlayPChoice();
}


/***********************************************************
execute function
***********************************************************/
void SendChoiceToServerDialogAction::Execute()
{
	if(_dialoghandler)
		_dialoghandler->SendPlayerChoice(_choice);
}





/***********************************************************
constructor
***********************************************************/
NPCDialogBox::NPCDialogBox()
: _plist_shown(true), _currentnpcid(-2)
{



}


/***********************************************************
destructor
***********************************************************/
NPCDialogBox::~NPCDialogBox()
{
	try
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("DialogFrame"));

		int resX, resY; 
		bool fullscreen;
		OsgHandler::getInstance()->GetScreenAttributes(resX, resY, fullscreen);

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetValue("Gui.DialogBox.PosX", vec.d_x.asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetValue("Gui.DialogBox.PosY", vec.d_y.asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetValue("Gui.DialogBox.SizeX", frw->getWidth().asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetValue("Gui.DialogBox.SizeY", frw->getHeight().asRelative((float)resY));
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception destructor chatbox: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
initalize the box
***********************************************************/
void NPCDialogBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "dialog.layout",
								"", "", &MyPropertyCallback);
		Root->addChildWindow(_myBox);


		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("DialogFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&NPCDialogBox::HandleClose, this));

		frw->subscribeEvent(CEGUI::Window::EventKeyDown,
			CEGUI::Event::Subscriber (&NPCDialogBox::HandleEnterKey, this));


		CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
			CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/listbox"));
		lb->subscribeEvent(CEGUI::Listbox::EventMouseClick,
						CEGUI::Event::Subscriber (&NPCDialogBox::Handlelbelected, this));
		lb->subscribeEvent(CEGUI::Listbox::EventMouseMove,
			CEGUI::Event::Subscriber (&NPCDialogBox::HandleMouseEnter, this));


		{
			float PosX = ConfigurationManager::GetInstance()->GetValue("Gui.DialogBox.PosX", 0.14f);
			float PosY = ConfigurationManager::GetInstance()->GetValue("Gui.DialogBox.PosY", 0.14f);
			float SizeX = ConfigurationManager::GetInstance()->GetValue("Gui.DialogBox.SizeX", 0.46f);
			float SizeY = ConfigurationManager::GetInstance()->GetValue("Gui.DialogBox.SizeY", 0.37f);
			frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, 0), CEGUI::UDim(PosY, 0)));
			frw->setWidth(CEGUI::UDim(SizeX, 0));
			frw->setHeight(CEGUI::UDim(SizeY, 0));
		}

		_myBox->hide();


		_textanim = CEGUI::AnimationManager::getSingleton().createAnimation("DialogTextAnim");
		_textanim->setReplayMode(CEGUI::Animation::RM_Once); // when this animation is started, only play it once, then stop

		_textanimaffector = _textanim->createAffector("Text", "StringMorph");
		_textanimaffector->createKeyFrame(0.0f, "");
		_textanimaffector->createKeyFrame(1.0f, "");

		_textaniminstance = CEGUI::AnimationManager::getSingleton().instantiateAnimation(_textanim);

		CEGUI::Window* txs = CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/multiline");
		txs->subscribeEvent(CEGUI::AnimationInstance::EventAnimationEnded,
										CEGUI::Event::Subscriber (&NPCDialogBox::handleAnimFinished, this));
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init DialogBox: ") + ex.getMessage().c_str());
	}
}




/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool NPCDialogBox::HandleClose (const CEGUI::EventArgs& e)
{
	CloseDialog();
	return true;
}


/***********************************************************
catch key event
***********************************************************/
bool NPCDialogBox::HandleEnterKey (const CEGUI::EventArgs& e)
{
	const CEGUI::KeyEventArgs& we =
    static_cast<const CEGUI::KeyEventArgs&>(e);

	if(we.scancode == CEGUI::Key::Space || we.scancode == CEGUI::Key::W)
	{
		if(_space_act)
			_space_act->Execute();
		return true;
	}

	if(we.scancode == CEGUI::Key::ArrowUp)
	{
		if(_plist_shown)
		{
			ChangeSelection(true);
			return true;
		}
	}

	if(we.scancode == CEGUI::Key::ArrowDown)
	{
		if(_plist_shown)
		{
			ChangeSelection(false);
			return true;
		}
	}

	return false;
}



/***********************************************************
catch mouse enter event
***********************************************************/
bool NPCDialogBox::HandleMouseEnter (const CEGUI::EventArgs& e)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/listbox"));

	const CEGUI::MouseEventArgs& wine =
    static_cast<const CEGUI::MouseEventArgs&>(e);

	CEGUI::ListboxItem * itm = lb->getItemAtPoint(wine.position);
	if(itm)
		lb->setItemSelectState(itm, true);

	return true;
}



/***********************************************************
called when animation is finished
***********************************************************/
bool NPCDialogBox::handleAnimFinished (const CEGUI::EventArgs& e)
{
	if(_space_act)
		_space_act->ExecuteEndScrollText();

	return false;
}


/***********************************************************
handle listbox selected
***********************************************************/
bool NPCDialogBox::Handlelbelected(const CEGUI::EventArgs& e)
{
	PlayPChoice();
	return true;
}






/***********************************************************
close dialog and inform actor
***********************************************************/
void NPCDialogBox::CloseDialog()
{
	Hide();

	LbaNet::GuiUpdatesSeq updseq;
	LbaNet::GuiClosedUpdate * upd = 
		new LbaNet::GuiClosedUpdate();
	updseq.push_back(upd);
	
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "DialogBox", updseq));

}




/***********************************************************
build dialog depending of the actor
***********************************************************/
void NPCDialogBox::BuildDialog(const LbaNet::DialogPartInfo &DialogPart)
{
	_currentPchoices.clear();
	long txtid = (long)DialogPart.NpcTextId;

	if(txtid < 0) // special case where no npc talking - direct player talk
	{
		// display first player choice only - mostly used by LBA1 original game
		if(DialogPart.PlayerTextsId.size() > 0)
			DisplayPChoice((long)DialogPart.PlayerTextsId[0]);
		else
			CloseDialog();
	}
	else
	{
		for(size_t i=0; i< DialogPart.PlayerTextsId.size(); ++i)
			_currentPchoices.push_back((long)DialogPart.PlayerTextsId[i]);

		if(_currentPchoices.size() > 1)
		{
			SetSpaceAction(boost::shared_ptr<NPCDialogActionBase>(new FinishAnimDialogAction(this, 
				boost::shared_ptr<NPCDialogActionBase>(new ShowPChoiceDialogAction(this, _currentPchoices)),
				true)));
		}
		else
		{
			if(_currentPchoices.size() > 0)
			{
				SetSpaceAction(boost::shared_ptr<NPCDialogActionBase>(new FinishAnimDialogAction(this, 
					boost::shared_ptr<NPCDialogActionBase>(new Show1ChoiceDialogAction(this, 
					(long)DialogPart.PlayerTextsId[0])),
					false)));
			}
			else
			{
				SetSpaceAction(boost::shared_ptr<NPCDialogActionBase>(new FinishAnimDialogAction(this, 
					boost::shared_ptr<NPCDialogActionBase>(new CloseDialogAction(this)),
					false)));
			}
		}

		DisplayScrollingText(txtid, _currentnpcid);
	}
}




/***********************************************************
refresh gui with info from server
***********************************************************/
void NPCDialogBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{
	for(size_t i=0; i<Parameters.size(); ++i)
	{
		LbaNet::GuiParameterBase * ptr = Parameters[i].get();
		const std::type_info& info = typeid(*ptr);

		// new dialog update
		if(info == typeid(LbaNet::DialogGuiParameter))
		{
			LbaNet::DialogGuiParameter * castedptr = 
				dynamic_cast<LbaNet::DialogGuiParameter *>(ptr);

			_currentnpcid = (long)castedptr->NpcActorId;

			// set dialog title
			std::string title = Localizer::getInstance()->GetText(Localizer::GUI, 96);
			std::string npcname = Localizer::getInstance()->GetText(Localizer::Name, (long)castedptr->NpcNameTextId);
			if(npcname == "")
				npcname = "NPC";
			title+=" "+ npcname;

			static_cast<CEGUI::FrameWindow *> (
				CEGUI::WindowManager::getSingleton().getWindow("DialogFrame"))
				->setText((const unsigned char *)title.c_str());

			// build rest of dialog
			BuildDialog(castedptr->DialogPart);
		}
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void NPCDialogBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{
	for(size_t i=0; i<Updates.size(); ++i)
	{
		LbaNet::GuiUpdateBase * ptr = Updates[i].get();
		const std::type_info& info = typeid(*ptr);

		// DialogUpdate
		if(info == typeid(LbaNet::DialogUpdate))
		{
			LbaNet::DialogUpdate * castedptr = 
				dynamic_cast<LbaNet::DialogUpdate *>(ptr);

			//set dialog
			BuildDialog(castedptr->DialogPartUpdate);
		}

		// SetPlayerNameUpdate
		if(info == typeid(SetPlayerNameUpdate))
		{
			SetPlayerNameUpdate * castedptr = 
				dynamic_cast<SetPlayerNameUpdate *>(ptr);

			_playername = castedptr->_Name;
		}
	}
}

/***********************************************************
show GUI
***********************************************************/
void NPCDialogBox::Display()
{
	_myBox->show();
	_myBox->activate();
}

/***********************************************************
hide GUI
***********************************************************/
void NPCDialogBox::Hide()
{
	_myBox->hide();

	//stop voice
	MusicHandler::getInstance()->PlayVoice(std::vector<std::string>());
}

/***********************************************************
show/hide GUI
***********************************************************/
void NPCDialogBox::ToggleDisplay()
{
	if(_myBox->isVisible())
		Hide();
	else
	{
		_myBox->show();
		_myBox->activate();
	}
}

/***********************************************************
focus GUI
***********************************************************/
void NPCDialogBox::Focus(bool focus)
{

}


/***********************************************************
save size of windows to be restored after resize of the application
***********************************************************/
void NPCDialogBox::SaveGUISizes(int oldscreenX, int oldscreenY)
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogFrame"));

	CEGUI::UVector2 vec = frw->getPosition();
	_savedPosX = vec.d_x.asRelative((float)oldscreenX);
	_savedPosY = vec.d_y.asRelative((float)oldscreenY);
	_savedSizeX = frw->getWidth().asRelative((float)oldscreenX);
	_savedSizeY = frw->getHeight().asRelative((float)oldscreenY);
}


/***********************************************************
restore the correct size of the windows
***********************************************************/
void NPCDialogBox::RestoreGUISizes()
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogFrame"));

	frw->setPosition(CEGUI::UVector2(CEGUI::UDim(_savedPosX, 0), CEGUI::UDim(_savedPosY, 0)));
	frw->setWidth(CEGUI::UDim(_savedSizeX, 0));
	frw->setHeight(CEGUI::UDim(_savedSizeY, 0));
}



/***********************************************************
show or hide player answer list from window
***********************************************************/
void NPCDialogBox::ShowHidePlayerList(bool Show)
{
	if(Show)
	{
		if(_plist_shown)
			return;

		_plist_shown = true;

		CEGUI::WindowManager::getSingleton().getWindow ("DialogFrame/multiline")->setHeight(CEGUI::UDim(0.6f, 0));
		CEGUI::WindowManager::getSingleton().getWindow ("DialogFrame/listbox")->show();	
	}
	else
	{
		if(!_plist_shown)
			return;

		_plist_shown = false;

		CEGUI::WindowManager::getSingleton().getWindow ("DialogFrame/listbox")->hide();
		CEGUI::WindowManager::getSingleton().getWindow ("DialogFrame/multiline")->setHeight(CEGUI::UDim(1, -5));
	}
}



/***********************************************************
finish text anim
***********************************************************/
void NPCDialogBox::FinishTextAnim()
{
	if(_textaniminstance && _textaniminstance->isRunning())
		_textaniminstance->setPosition(_textanim->getDuration());
}

/***********************************************************
set action executed on space bar
***********************************************************/
void NPCDialogBox::SetSpaceAction(boost::shared_ptr<NPCDialogActionBase> act)
{
	_space_act = act;
}

/***********************************************************
display player choice list
***********************************************************/
void NPCDialogBox::DisplayPChoices(std::vector<long> pchoices)
{
	SetSpaceAction(boost::shared_ptr<NPCDialogActionBase>(new PlayerPChoiceVoiceDialogAction(this)));

	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/listbox"));
	
	if(lb)
	{
		lb->resetList();

		// display player choice
		for(size_t i=0; i<pchoices.size(); ++i)
		{
			std::string str = Localizer::getInstance()->GetText(Localizer::Map, pchoices[i]);
			CEGUI::ListboxItem *it = new MyDialogItem((const unsigned char *)str.c_str(), i);
			lb->addItem(it);	
			if(i == 0)
				lb->setItemSelectState(it, true);
		}

		ShowHidePlayerList(true);
	}
}


/***********************************************************
display player choice
***********************************************************/
void NPCDialogBox::DisplayPChoice(long pchoice)
{
	SetSpaceAction(boost::shared_ptr<NPCDialogActionBase>(new FinishAnimDialogAction(this, 
					boost::shared_ptr<NPCDialogActionBase>(new SendChoiceToServerDialogAction(this, 0)),
					false)));
	DisplayScrollingText(pchoice, -1);
}


/***********************************************************
play voice of player choice
***********************************************************/
void NPCDialogBox::PlayPChoice()
{
	if(_plist_shown)
	{
		CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
			CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/listbox"));

		const MyDialogItem * it = static_cast<const MyDialogItem *>(lb->getFirstSelectedItem());
		if(it)
		{
			int tosend = it->_SelectionIdx;
			if((int)_currentPchoices.size() > tosend)
			{
				//play voice
				std::vector<std::string> voices = Localizer::getInstance()->GetVoices(Localizer::Map, _currentPchoices[tosend]);
				if(voices.size() > 0)
				{
					for(size_t vv=0; vv< voices.size(); ++vv)
						voices[vv] = "Data/" + voices[vv];

					MusicHandler::getInstance()->PlayVoice(voices, -1,
					boost::shared_ptr<NPCDialogActionBase>(new SendChoiceToServerDialogAction(this, tosend)));
				
					SetSpaceAction(boost::shared_ptr<NPCDialogActionBase>(new SendChoiceToServerDialogAction(this, tosend)));
				}
				else
					SendPlayerChoice(tosend);
			}
			else
				SendPlayerChoice(0);
		}		
	}
}


/***********************************************************
send selected player choice to server
***********************************************************/
void NPCDialogBox::SendPlayerChoice(int choice)
{
	// send to server
	LbaNet::GuiUpdatesSeq updseq;
	updseq.push_back(new LbaNet::DialogSelectedUpdate(choice));
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "DialogBox", updseq));
}

	
/***********************************************************
display scrolling text
***********************************************************/
void NPCDialogBox::DisplayScrollingText(long textid, long actorid)
{
	ShowHidePlayerList(false);

	// display NPC dialog text
	CEGUI::Window* txs = CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/multiline");
	std::string str = Localizer::getInstance()->GetText(Localizer::Map, textid);
	str = StringHelper::replaceall(str, "#P#", _playername); // replace with player name

	std::string fulltext;
	int idxs = 0;
	bool firsttime=true;
	while((idxs = str.find(" @ ")) != std::string::npos)
	{
		std::string tmp = str.substr(0, idxs);
		if(tmp == "")
			tmp = '\n';

		if(firsttime)
		{
			firsttime = false;
			fulltext = tmp;
		}
		else
		{
			fulltext += '\n';
			fulltext += tmp;
		}

		while(((idxs+4) < (int)str.size()) && (str[idxs+3] == '@') && (str[idxs+4] == ' '))
		{
			fulltext += "\n";
			idxs+= 2;
		}

		str = str.substr(idxs+3);
	}

	if(firsttime)
	{
		firsttime = false;
		fulltext = str;
	}
	else
	{
		fulltext += '\n' + str;
	}


	//start animation
	_textanim->setDuration(fulltext.size() / 15.0f); // duration in seconds
	_textanimaffector->destroyKeyFrame(_textanimaffector->getKeyFrameAtIdx(1));
	_textanimaffector->createKeyFrame(fulltext.size() / 15.0f, (const unsigned char *)fulltext.c_str());
	_textaniminstance->setTargetWindow(txs);
	_textaniminstance->start();


	//play voice
	std::vector<std::string> voices = Localizer::getInstance()->GetVoices(Localizer::Map, textid);
	if(voices.size() > 0)
	{
		for(size_t vv=0; vv< voices.size(); ++vv)
			voices[vv] = "Data/" + voices[vv];

		MusicHandler::getInstance()->PlayVoice(voices, actorid);
	}
}

	
/***********************************************************
move player choice selection up/downt
***********************************************************/
void NPCDialogBox::ChangeSelection(bool up)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/listbox"));
	
	if(lb)
	{
		CEGUI::ListboxItem*	litem = lb->getFirstSelectedItem();
		if(litem)
		{
			int idx = (int)lb->getItemIndex(litem);
			int count = (int)lb->getItemCount();
			if(up)
			{
				++idx;
				if(idx >= count)
					idx = 0;
			}
			else
			{
				--idx;
				if(idx < 0)
					idx = count-1;
			}

			lb->setItemSelectState(litem, false);
			CEGUI::ListboxItem*	litem2 = lb->getListboxItemFromIndex(idx);
			if(litem2)
				lb->setItemSelectState(litem2, true);
		}
	}
}