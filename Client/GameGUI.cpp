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

#include "GameGUI.h"
#include <CEGUI.h>
#include "LogHandler.h"
#include "MusicHandler.h"
#include "MessageBox.h"
#include "ChooseNumberBox.h"
#include "EventsQueue.h"
#include "ClientExtendedEvents.h"
#include "ClientExtendedTypes.h"
#include "DataLoader.h"
#include "SynchronizedTimeHandler.h"
#include "ImageSetHandler.h"

#include "InventoryBox.h"
#include "ShortcutBox.h"
#include "ContainerBox.h"
#include "LetterEditorBox.h"
#include "LetterViewerBox.h"
#include "DialogBox.h"
#include "JournalBox.h"
#include "MailBox.h"
#include "ShopBox.h"
#include "Localizer.h"
#include "GUILocalizationCallback.h"

#include <CEGUIAnimation.h>

/***********************************************************
constructor
***********************************************************/
GameGUI::GameGUI()
{
	_gameguis["ChatBox"] = boost::shared_ptr<GameGUIBase>(new ChatBox());

	CommunityBox * combox = new CommunityBox();
	InventoryBox * invbox = new InventoryBox(50);
	_gameguis["CommunityBox"] = boost::shared_ptr<GameGUIBase>(combox);
	_gameguis["TeleportBox"] = boost::shared_ptr<GameGUIBase>(new TeleportBox());
	_gameguis["InventoryBox"] = boost::shared_ptr<GameGUIBase>(invbox);
	_gameguis["ShortcutBox"] = boost::shared_ptr<GameGUIBase>(new ShortcutBox(50, invbox));
	_gameguis["JournalBox"] = boost::shared_ptr<GameGUIBase>(new JournalBox());
	_gameguis["ContainerBox"] = boost::shared_ptr<GameGUIBase>(new ContainerBox(50));
	_gameguis["LetterEditorBox"] = boost::shared_ptr<GameGUIBase>(new LetterEditorBox());
	_gameguis["LetterViewerBox"] = boost::shared_ptr<GameGUIBase>(new LetterViewerBox());
	_gameguis["DialogBox"] = boost::shared_ptr<GameGUIBase>(new NPCDialogBox());
	_gameguis["MailBox"] = boost::shared_ptr<GameGUIBase>(new MailBox(combox));
	_gameguis["ShopBox"] = boost::shared_ptr<GameGUIBase>(new NPCShopBox(50));

	_textanim = CEGUI::AnimationManager::getSingleton().createAnimation("SignTextAnim");
	_textanim->setReplayMode(CEGUI::Animation::RM_Once); // when this animation is started, only play it once, then stop

	_textanimaffector = _textanim->createAffector("Text", "StringMorph");
	_textanimaffector->createKeyFrame(0.0f, "");
	_textanimaffector->createKeyFrame(1.0f, "");

	_textaniminstance = CEGUI::AnimationManager::getSingleton().instantiateAnimation(_textanim);
}


/***********************************************************
destructor
***********************************************************/
GameGUI::~GameGUI()
{
}

/***********************************************************
initialize the GUI
***********************************************************/
void GameGUI::Initialize()
{
	try
	{
		_root = CEGUI::WindowManager::getSingleton().loadWindowLayout( "GameGuiRoot.layout",
								"", "", &MyPropertyCallback);

		std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator it = _gameguis.begin();
		std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator end = _gameguis.end();
		for(; it != end; ++it)
			it->second->Initialize(_root);

		CGMessageBox::getInstance()->Initialize(_root);
		ChooseNumberBox::getInstance()->Initialize(_root);


		CEGUI::WindowManager::getSingleton().getWindow("HeadInterfaceBG")->disable();
		CEGUI::WindowManager::getSingleton().getWindow("MenuCharInterfaceBG")->disable();

		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btnchaticon"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleChatIconClicked, this));

		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btncomicon"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleComIconClicked, this));

		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btnteleporticon"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleTeleIconClicked, this));

		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btnquit"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleQuitIconClicked, this));

		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btnsound"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleSoundIconClicked, this));

		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btnchangeworld"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleChangeWorldIconClicked, this));

		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btnoption"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleOptionIconClicked, this));

		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("DisplayGameTextFrame/bok"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleCloseTextClicked, this));

		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btntunic"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleInventoryClicked, this));

		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btnweapon"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleShortcutClicked, this));

		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btnquest"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleJournalClicked, this));

		

		
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("DisplayGameTextFrame"));
		frw->subscribeEvent (CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&GameGUI::HandleCloseTextClicked, this));


		CEGUI::WindowManager::getSingleton().getWindow("DisplayGameTextFrame")->hide();


		CEGUI::WindowManager::getSingleton().getWindow("CharPortraitDisplayHalo")->disable();
		CEGUI::WindowManager::getSingleton().getWindow("CharPortraitDisplay")->disable();

	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init login gui: ") + ex.getMessage().c_str());
		_root = NULL;
	}

	RefreshSOundButton();
}


/***********************************************************
handle send button event
***********************************************************/
bool GameGUI::HandleChatIconClicked (const CEGUI::EventArgs& e)
{
	ToggleDisplayGUI("ChatBox");
	return true;
}



/***********************************************************
handle send button event
***********************************************************/
bool GameGUI::HandleComIconClicked (const CEGUI::EventArgs& e)
{
	ToggleDisplayGUI("CommunityBox");
	return true;
}




/***********************************************************
handle send button event
***********************************************************/
bool GameGUI::HandleTeleIconClicked (const CEGUI::EventArgs& e)
{
	ToggleDisplayGUI("TeleportBox");
	return true;
}

/***********************************************************
handle send button event
***********************************************************/
bool GameGUI::HandleQuitIconClicked (const CEGUI::EventArgs& e)
{
	EventsQueue::getReceiverQueue()->AddEvent(new DisplayGUIEvent(3));
	return true;
}

/***********************************************************
handle send button event
***********************************************************/
bool GameGUI::HandleSoundIconClicked (const CEGUI::EventArgs& e)
{
	MusicHandler::getInstance()->EnableDisableSound();
	RefreshSOundButton();
	return true;
}


/***********************************************************
handle send button event
***********************************************************/
bool GameGUI::HandleChangeWorldIconClicked (const CEGUI::EventArgs& e)
{
#ifndef _USE_QT_EDITOR_
	EventsQueue::getReceiverQueue()->AddEvent(new DisplayGUIEvent(1));
#endif
	return true;
}


/***********************************************************
handle send button event
***********************************************************/
bool GameGUI::HandleOptionIconClicked (const CEGUI::EventArgs& e)
{
	EventsQueue::getReceiverQueue()->AddEvent(new DisplayGUIEvent(4));
	return true;
}


/***********************************************************
handle send button event
***********************************************************/
bool GameGUI::HandleInventoryClicked (const CEGUI::EventArgs& e)
{
	ToggleDisplayGUI("InventoryBox");
	return true;
}

/***********************************************************
handle send button event
***********************************************************/
bool GameGUI::HandleShortcutClicked (const CEGUI::EventArgs& e)
{
	ToggleDisplayGUI("ShortcutBox");
	return true;
}


/***********************************************************
handle send button event
***********************************************************/
bool GameGUI::HandleJournalClicked (const CEGUI::EventArgs& e)
{
	ToggleDisplayGUI("JournalBox");
	return true;
}


/***********************************************************
handle send button event
***********************************************************/
bool GameGUI::HandleCloseTextClicked (const CEGUI::EventArgs& e)
{
	DisplayGameText(0, true, true);
	return true;
}


/***********************************************************
CloseText
***********************************************************/
void GameGUI::CloseText()
{
	if(CEGUI::WindowManager::getSingleton().getWindow("DisplayGameTextFrame")->isVisible())
		CEGUI::WindowManager::getSingleton().getWindow("DisplayGameTextFrame")->hide();


	// inform server that gui is closed
	LbaNet::GuiUpdatesSeq updseq;
	LbaNet::GuiClosedUpdate * upd = new LbaNet::GuiClosedUpdate();
	updseq.push_back(upd);
	
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "TextBox", updseq));

	//stop voice
	MusicHandler::getInstance()->PlayVoice(std::vector<std::string>());
}


/***********************************************************
refresh gui with info from server
***********************************************************/
void GameGUI::RefreshGUI(const std::string & guiid, const LbaNet::GuiParamsSeq &Parameters, bool Show, bool Hide)
{
	// case if this concern textbox directly
	if(guiid == "TextBox")
	{
		for(size_t i=0; i<Parameters.size(); ++i)
		{
			LbaNet::GuiParameterBase * ptr = Parameters[i].get();
			const std::type_info& info = typeid(*ptr);


			// DisplayGameText
			if(info == typeid(LbaNet::DisplayGameText))
			{
				LbaNet::DisplayGameText * castedptr = 
					dynamic_cast<LbaNet::DisplayGameText *>(ptr);

				DisplayGameText((long)castedptr->Textid, Show, Hide);
			}
		}

		if(Parameters.size() == 0)
			DisplayGameText(0, Show, Hide);
	}
	else
	{
		std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator it = _gameguis.find(guiid);
		if(it != _gameguis.end())
		{
			it->second->Refresh(Parameters);

			if(Show)
				it->second->Display();

			if(Hide)
				it->second->Hide();
		}
	}
}

/***********************************************************
refresh gui with info from server
***********************************************************/
//! update gui with info from server
void GameGUI::UpdateGUI(const std::string & guiid,const LbaNet::GuiUpdatesSeq &Updates)
{
	// case if this concern himself directly
	if(guiid == "main")
	{
		for(size_t i=0; i<Updates.size(); ++i)
		{
			LbaNet::GuiUpdateBase * ptr = Updates[i].get();
			const std::type_info& info = typeid(*ptr);

			// RefreshSOundButton
			if(info == typeid(RefreshSoundButtonUpdate))
			{
				RefreshSOundButton();

			}

			// SetPlayerNameUpdate
			if(info == typeid(SetPlayerNameUpdate))
			{
				SetPlayerNameUpdate * castedptr = 
					dynamic_cast<SetPlayerNameUpdate *>(ptr);

				SetPlayerName(castedptr->_Name);

				//update dialog gui
				_gameguis["DialogBox"]->Update(Updates);
			}

			// SystemMessageUpdate
			if(info == typeid(LbaNet::SystemMessageUpdate))
			{
				LbaNet::SystemMessageUpdate * castedptr = 
					dynamic_cast<LbaNet::SystemMessageUpdate *>(ptr);

				CGMessageBox::getInstance()->Show(castedptr->Title, castedptr->Message);
			}

			// RefreshCharPortraitUpdate
			if(info == typeid(RefreshCharPortraitUpdate))
			{
				RefreshCharPortrait();
			}
			
		}
	}
	else
	{
		std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator it = _gameguis.find(guiid);
		if(it != _gameguis.end())
			it->second->Update(Updates);
	}
}

/***********************************************************
show GUI
***********************************************************/
void GameGUI::ShowGUI(const std::string & guiid)
{
	std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator it = _gameguis.find(guiid);
	if(it != _gameguis.end())
		it->second->Display();
}

/***********************************************************
hide GUI
***********************************************************/
void GameGUI::HideGUI(const std::string & guiid)
{
	std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator it = _gameguis.find(guiid);
	if(it != _gameguis.end())
		it->second->Hide();
}

/***********************************************************
show/hide GUI
***********************************************************/
void GameGUI::ToggleDisplayGUI(const std::string & guiid)
{
	std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator it = _gameguis.find(guiid);
	if(it != _gameguis.end())
		it->second->ToggleDisplay();
}

/***********************************************************
focus GUI
***********************************************************/
void GameGUI::FocusGUI(const std::string & guiid, bool focus)
{
	std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator it = _gameguis.find(guiid);
	if(it != _gameguis.end())
		it->second->Focus(focus);
}







/***********************************************************
refresh sound button
***********************************************************/
void GameGUI::RefreshSOundButton()
{
	try
	{
		if(!MusicHandler::getInstance()->IsSoundEnabled())
			static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btnsound"))->
												setProperty("NormalImage", "set:soundbutton image:disabled");
		else
			static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("btnsound"))->
												setProperty("NormalImage", "set:soundbutton image:normal");
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception refreshing the sound button: ") + ex.getMessage().c_str());
		_root = NULL;
	}
}

/***********************************************************
display game text
***********************************************************/
bool GameGUI::DisplayGameText(long textid, bool show, bool hide)
{
	try
	{
		CEGUI::MultiLineEditbox * txs =
		static_cast<CEGUI::MultiLineEditbox *> (CEGUI::WindowManager::getSingleton().getWindow("DisplayGameTextFrame/text"));
		

		if(show)
		{
			if(hide)
			{
				//hide only if animation is finished, else finish anim
				if(_textaniminstance && _textaniminstance->isRunning())
					_textaniminstance->setPosition(_textanim->getDuration());
				else
					CloseText();

				return true;
			}
			else
			{
				std::string fulltext;
				std::string str = Localizer::getInstance()->GetText(Localizer::Map, textid);
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


				//play voice with text
				std::vector<std::string> voices = Localizer::getInstance()->GetVoices(Localizer::Map, textid);
				if(voices.size() > 0)
				{
					for(size_t vv=0; vv< voices.size(); ++vv)
						voices[vv] = "Data/" + voices[vv];

					MusicHandler::getInstance()->PlayVoice(voices);
				}

				if(!CEGUI::WindowManager::getSingleton().getWindow("DisplayGameTextFrame")->isVisible())
				{
					CEGUI::WindowManager::getSingleton().getWindow("DisplayGameTextFrame")->show();
					return true;
				}
			}

			return false;
		}
		else
		{
			CloseText();
			return true;
		}

	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception showing text window: ") + ex.getMessage().c_str());
		_root = NULL;
	}

	return true;
}




/***********************************************************
set player name
***********************************************************/
void GameGUI::SetPlayerName(const std::string & name)
{
	try
	{
		CEGUI::WindowManager::getSingleton().getWindow("PlayerName")->setText(name);
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception SetPlayerName: ") + ex.getMessage().c_str());
		_root = NULL;
	}
}



/***********************************************************
save size of windows to be restored after resize of the application
***********************************************************/
void GameGUI::SaveGUISizes(int oldscreenX, int oldscreenY)
{
	std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator it = _gameguis.begin();
	std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator end = _gameguis.end();
	for(; it != end; ++it)
		it->second->SaveGUISizes(oldscreenX, oldscreenY);
}

/***********************************************************
restore the correct size of the windows
***********************************************************/
void GameGUI::RestoreGUISizes()
{
	std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator it = _gameguis.begin();
	std::map<std::string, boost::shared_ptr<GameGUIBase> >::iterator end = _gameguis.end();
	for(; it != end; ++it)
		it->second->RestoreGUISizes();
}


/***********************************************************
refresh portrait
***********************************************************/
void GameGUI::RefreshCharPortrait()
{
	std::string imagesetname = ImageSetHandler::RefreshCharPortrait();
	CEGUI::Window*	tmp = CEGUI::WindowManager::getSingleton().getWindow("CharPortraitDisplay");
	if(tmp)
		tmp->setProperty("Image", "set:" + imagesetname + " image:full_image");
}