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

#include "CommunityBox.h"
#include <iostream>
#include <algorithm>
#include <CEGUI.h>
#include "GameGUI.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "ClientExtendedEvents.h"
#include "ClientExtendedTypes.h"
#include <typeinfo>
#include "OSGHandler.h"
#include "GUILocalizationCallback.h"


// Sample sub-class for ListboxTextItem that auto-sets the selection brush
// image.  This saves doing it manually every time in the code.
class MyComListItem : public CEGUI::ListboxTextItem
{
public:
    MyComListItem (const CEGUI::String& text) 
		: CEGUI::ListboxTextItem(text)
    {
        setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    }
};


/***********************************************************
constructor
***********************************************************/
CommunityBox::CommunityBox()
{
}


/***********************************************************
destructor
***********************************************************/
CommunityBox::~CommunityBox()
{
	try
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("CommunityFrame"));

		int resX, resY; 
		bool fullscreen;
		OsgHandler::getInstance()->GetScreenAttributes(resX, resY, fullscreen);

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.Communitybox.PosX", vec.d_x.asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Communitybox.PosY", vec.d_y.asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Communitybox.SizeX", frw->getWidth().asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Communitybox.SizeY", frw->getHeight().asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetBool("Gui.Communitybox.Visible", frw->isVisible());
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception destructor community box: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
initalize the box
***********************************************************/
void CommunityBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "community.layout",
								"", "", &MyPropertyCallback);
		Root->addChildWindow(_myBox);

		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("CommunityFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&CommunityBox::HandleClose, this));

		float PosX, PosY, SizeX, SizeY;
		bool Visible;
		ConfigurationManager::GetInstance()->GetFloat("Gui.Communitybox.PosX", PosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Communitybox.PosY", PosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Communitybox.SizeX", SizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Communitybox.SizeY", SizeY);
		ConfigurationManager::GetInstance()->GetBool("Gui.Communitybox.Visible", Visible);
		frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, 0), CEGUI::UDim(PosY, 0)));
		frw->setWidth(CEGUI::UDim(SizeX, 0));
		frw->setHeight(CEGUI::UDim(SizeY, 0));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("CommunityFrame/friendAdd"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&CommunityBox::HandleAddFriend, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("CommunityFrame/friendRemove"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&CommunityBox::HandleRemoveFriend, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("CommunityFrame/friendRefresh"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&CommunityBox::HandleRefreshFriend, this));




		_myChooseName = CEGUI::WindowManager::getSingleton().loadWindowLayout( "AddFriendName.layout",
								"", "", &MyPropertyCallback);
		_myChooseName->setProperty("AlwaysOnTop", "True");
		Root->addChildWindow(_myChooseName);
		_myChooseName->hide();

		{
			CEGUI::FrameWindow * fw = static_cast<CEGUI::FrameWindow *>(_myChooseName);
			fw->subscribeEvent (	CEGUI::FrameWindow::EventCloseClicked,
									CEGUI::Event::Subscriber (&CommunityBox::HandleCPCancel, this) );

			static_cast<CEGUI::PushButton *> (
				CEGUI::WindowManager::getSingleton().getWindow("Chat/AddFriendName/bOk"))->subscribeEvent (
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber (&CommunityBox::HandleCPOk, this));

			static_cast<CEGUI::PushButton *> (
				CEGUI::WindowManager::getSingleton().getWindow("Chat/AddFriendName/bCancel"))->subscribeEvent (
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber (&CommunityBox::HandleCPCancel, this));
		}


		static_cast<CEGUI::Listbox *> (
			CEGUI::WindowManager::getSingleton().getWindow("Community/friendlist"))->subscribeEvent (
			CEGUI::Listbox::EventMouseDoubleClick,
			CEGUI::Event::Subscriber (&CommunityBox::HandleListdblClick, this));


		static_cast<CEGUI::Listbox *> (
			CEGUI::WindowManager::getSingleton().getWindow("Community/onlinelist"))->subscribeEvent (
			CEGUI::Listbox::EventMouseDoubleClick,
			CEGUI::Event::Subscriber (&CommunityBox::HandleConnecteddblClick, this));
		
		if(Visible)
			frw->show();
		else
			frw->hide();

	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init community box: ") + ex.getMessage().c_str());
	}
}




/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool CommunityBox::HandleClose (const CEGUI::EventArgs& e)
{
	_myBox->hide();
	return true;
}






/***********************************************************
add people online
***********************************************************/
void CommunityBox::AddOnline(const std::string &_online,
							 const std::string &_status, const std::string &color)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("Community/onlinelist"));

	std::string dis = "[colour='" + color + "']" + _online;
	if(_status != "")
		dis += " (" + _status + ")";

	std::map<std::string, CEGUI::ListboxItem *>::iterator itmap = _onlines.find(_online);
	if(itmap != _onlines.end())
	{
		itmap->second->setText(dis);
		lb->invalidate();
	}
	else
	{
		CEGUI::ListboxItem *it = new MyComListItem(dis);
		lb->addItem(it);
		_onlines[_online] = it;
	}

	UpdateFriendOnlineStatus(_online);
}

/***********************************************************
remove people online
***********************************************************/
void CommunityBox::RemoveOnline(const std::string &_offline)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("Community/onlinelist"));


	std::map<std::string, CEGUI::ListboxItem *>::iterator itmap = _onlines.find(_offline);
	if(itmap != _onlines.end())
	{
		lb->removeItem(itmap->second);
		_onlines.erase(itmap);
	}

	UpdateFriendOnlineStatus(_offline);
}


/***********************************************************
used to process text to add
***********************************************************/
//void CommunityBox::Process()
//{
	//std::vector<ThreadSafeWorkpile::JoinEvent> data;
	//ThreadSafeWorkpile::getInstance()->GetJoinEventData(data);

	//std::vector<ThreadSafeWorkpile::JoinEvent>::const_iterator it = data.begin();
	//std::vector<ThreadSafeWorkpile::JoinEvent>::const_iterator end = data.end();
	//for(; it != end; ++it)
	//{
	//	if(it->Clear)
	//	{
	//		ClearList(it->ListName);
	//	}
	//	else
	//	{
	//		if(it->Joined)
	//			AddOnline(it->ListName, it->Nickname, it->Status, it->Color);
	//		else
	//			RemoveOnline(it->ListName, it->Nickname);
	//	}
	//}


	//LbaNet::FriendsSeq friends;
	//if(ThreadSafeWorkpile::getInstance()->GetFriends(friends))
	//{
	//	ClearFriends();
	//	for(size_t i=0; i<friends.size(); ++i)
	//		UpdateFriend(friends[i]);
	//}
//}


/***********************************************************
clear the list
***********************************************************/
void CommunityBox::ClearList()
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("Community/onlinelist"));
	lb->resetList();
	_onlines.clear();
}



/***********************************************************
handle event when add friend clicked
***********************************************************/
bool CommunityBox::HandleAddFriend(const CEGUI::EventArgs& e)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("Community/friendlist"));

	// check if we accept pending friend
	const CEGUI::ListboxTextItem * it = static_cast<const CEGUI::ListboxTextItem *>(lb->getFirstSelectedItem());
	if(it)
	{
		T_friendmap::iterator itm = _friends.find(it->getID());
		if(itm != _friends.end())
		{
			if(itm->second.first.ToAccept)
			{
				LbaNet::GuiUpdatesSeq updseq;
				LbaNet::AcceptFriend * upd = 
					new LbaNet::AcceptFriend(it->getID());
				updseq.push_back(upd);
				
				EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
					SynchronizedTimeHandler::GetCurrentTimeDouble(), "CommunityBox", updseq));

				return true;
			}
		}
	}

	// if not then we add a new friend
	_myChooseName->show();
	CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
		(CEGUI::WindowManager::getSingleton().getWindow("Chat/choosePlayerName/edit"));
	bed->activate();
	return true;
}


/***********************************************************
handle event when remove friend clicked
***********************************************************/
bool CommunityBox::HandleRemoveFriend(const CEGUI::EventArgs& e)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("Community/friendlist"));

	const CEGUI::ListboxTextItem * it = static_cast<const CEGUI::ListboxTextItem *>(lb->getFirstSelectedItem());
	if(it)
	{
		LbaNet::GuiUpdatesSeq updseq;
		LbaNet::RemoveFriend * upd = 
			new LbaNet::RemoveFriend(it->getID());
		updseq.push_back(upd);
		
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), "CommunityBox", updseq));
	}

	return true;
}



/***********************************************************
handle event when remove friend clicked
***********************************************************/
bool CommunityBox::HandleRefreshFriend(const CEGUI::EventArgs& e)
{
	LbaNet::GuiUpdatesSeq updseq;
	LbaNet::RefreshFriends * upd = 
		new LbaNet::RefreshFriends();
	updseq.push_back(upd);

	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "CommunityBox", updseq));

	return true;
}



/***********************************************************
add people friend
***********************************************************/
void CommunityBox::UpdateFriend(const LbaNet::FriendInfo & frd)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("Community/friendlist"));


	bool connected = false;
	std::string color = "FF777777";
	std::map<std::string, CEGUI::ListboxItem *>::iterator iton = _onlines.find(frd.Name);
	if(iton != _onlines.end())
	{
		connected = true;
		color = "FF33FF33";
	}

	std::string dis = "[colour='" + color + "']";
	if(frd.ToAccept)
		dis += " (Request)";


	dis += frd.Name;

	if(frd.Pending)
	{
		dis += " (Pending)";

		// display pending message on chatbox
		LbaNet::GuiUpdatesSeq updseq;
		LbaNet::ChatTextUpdate * upd = new LbaNet::ChatTextUpdate("All", "Info", "You have a pending friend request from " + frd.Name);
		updseq.push_back(upd);
		EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));
	}


	//check if already exist just update the text
	T_friendmap::iterator it = _friends.find(frd.Id);
	if(it != _friends.end())
	{
		if(frd.Removed)
		{
			// display remove message on chatbox
			LbaNet::GuiUpdatesSeq updseq;
			LbaNet::ChatTextUpdate * upd = new LbaNet::ChatTextUpdate("All", "Info", "Friendship refused/removed with player " + it->second.first.Name);
			updseq.push_back(upd);
			EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
				SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));


			lb->removeItem(it->second.second);
			_friends.erase(it);
		}
		else
		{
			it->second.second->setText(dis);
			lb->invalidate();
		}
	}
	else
	{
		if(!frd.Removed)
		{
			CEGUI::ListboxItem *item = new MyComListItem(dis);
			item->setID((unsigned int)frd.Id);
			lb->addItem(item);
			_friends[frd.Id] = std::make_pair<LbaNet::FriendInfo, CEGUI::ListboxItem *>(frd, item);		
		}
	}
}


/***********************************************************
update friend online status
***********************************************************/
void CommunityBox::UpdateFriendOnlineStatus(const std::string & name)
{
	T_friendmap::iterator it = _friends.begin();
	T_friendmap::iterator end = _friends.end();
	for(; it != end; ++it)
	{
		if(it->second.first.Name == name)
		{
			UpdateFriend(it->second.first);
			break;
		}
	}
}


/***********************************************************
remove people friend
***********************************************************/
//void CommunityBox::RemoveFriend(long frid)
//{
//	T_friendmap::iterator it = _friends.find(frid);
//	if(it == _friends.end()) // does not exist
//		return;
//
//
//	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
//		CEGUI::WindowManager::getSingleton().getWindow("Community/friendlist"));
//
//	lb->removeItem(it->second.second);
//	_friends.erase(it);
//}



/***********************************************************
clear the friend list
***********************************************************/
void CommunityBox::ClearFriends()
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("Community/friendlist"));

	T_friendmap::iterator it = _friends.begin();
	T_friendmap::iterator end = _friends.end();
	for(; it != end; ++it)
		lb->removeItem(it->second.second);

	_friends.clear();
}






/***********************************************************
handle event when list is selected
***********************************************************/
bool CommunityBox::HandleCPOk (const CEGUI::EventArgs& e)
{
	CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
	(CEGUI::WindowManager::getSingleton().getWindow("Chat/AddFriendName/edit"));

	std::string strc = bed->getProperty("Text").c_str();

	if(strc != "")
	{
		LbaNet::GuiUpdatesSeq updseq;
		LbaNet::AddFriend * upd = 
			new LbaNet::AddFriend(strc);
		updseq.push_back(upd);
		
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), "CommunityBox", updseq));

		bed->setProperty("Text", "");
		_myChooseName->hide();
	}
	else
	{
		bed->activate();
	}

	return true;
}

/***********************************************************
handle event when list is selected
***********************************************************/
bool CommunityBox::HandleCPCancel (const CEGUI::EventArgs& e)
{
	CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
	(CEGUI::WindowManager::getSingleton().getWindow("Chat/AddFriendName/edit"));

	bed->setProperty("Text", "");
	_myChooseName->hide();
	return true;
}



/***********************************************************
handle event when list is double clicked
***********************************************************/
bool CommunityBox::HandleListdblClick (const CEGUI::EventArgs& e)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("Community/friendlist"));

	const CEGUI::ListboxTextItem * it = static_cast<const CEGUI::ListboxTextItem *>(lb->getFirstSelectedItem());
	if(it)
	{
		std::string name = it->getText().c_str();
		name = name.substr(name.find("]")+1);
	
		std::map<std::string, CEGUI::ListboxItem *>::iterator iton = _onlines.find(name);
		if(iton != _onlines.end())
		{
			LbaNet::GuiUpdatesSeq updseq;
			AddWhisperChanelUpdate * upd = 
				new AddWhisperChanelUpdate(name);
			updseq.push_back(upd);
			EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
				SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));

			EventsQueue::getReceiverQueue()->AddEvent(new FocusChatEvent(true));
		}
	}

	return true;
}



/***********************************************************
handle event when list is double clicked
***********************************************************/
bool CommunityBox::HandleConnecteddblClick (const CEGUI::EventArgs& e)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("Community/onlinelist"));

	const CEGUI::ListboxTextItem * it = static_cast<const CEGUI::ListboxTextItem *>(lb->getFirstSelectedItem());
	if(it)
	{
		std::string name = it->getText().c_str();
		name = name.substr(name.find("]")+1);
		name = name.substr(0, name.find_last_of("(")-1);

		LbaNet::GuiUpdatesSeq updseq;
		AddWhisperChanelUpdate * upd = 
			new AddWhisperChanelUpdate(name);
		updseq.push_back(upd);
		EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));

		EventsQueue::getReceiverQueue()->AddEvent(new FocusChatEvent(true));
	}

	return true;
}

/***********************************************************
get friend list
***********************************************************/
std::vector<std::string> CommunityBox::GetFriendList()
{
	std::vector<std::string> res;

	T_friendmap::iterator it = _friends.begin();
	T_friendmap::iterator end = _friends.end();
	for(; it != end; ++it)
		res.push_back(it->second.first.Name);

	return res;
}



/***********************************************************
refresh gui with info from server
***********************************************************/
void CommunityBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{
	for(size_t i=0; i<Parameters.size(); ++i)
	{
		LbaNet::GuiParameterBase * ptr = Parameters[i].get();
		const std::type_info& info = typeid(*ptr);

		// got player online list refresh event
		if(info == typeid(LbaNet::PlayerOnlineListGuiParameter))
		{
			LbaNet::PlayerOnlineListGuiParameter * castedptr = 
				dynamic_cast<LbaNet::PlayerOnlineListGuiParameter *>(ptr);

			ClearList();

			LbaNet::PlayerOnlinesSeq	&PlayerList = castedptr->PlayerList;
			LbaNet::PlayerOnlinesSeq::const_iterator it = PlayerList.begin();
			LbaNet::PlayerOnlinesSeq::const_iterator end = PlayerList.end();
			for(; it != end; ++it)
			{
				if(it->Joined)
					AddOnline(it->Nickname, it->Status, it->Color);
				else
					RemoveOnline(it->Nickname);
			}
		}

		// got friend list refresh event
		if(info == typeid(LbaNet::FriendListGuiParameter))
		{
			LbaNet::FriendListGuiParameter * castedptr = 
				dynamic_cast<LbaNet::FriendListGuiParameter *>(ptr);

			ClearFriends();

			LbaNet::FriendsSeq	&friends = castedptr->FriendList;
			for(size_t i=0; i<friends.size(); ++i)
				UpdateFriend(friends[i]);
		}
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void CommunityBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{
	for(size_t i=0; i<Updates.size(); ++i)
	{
		LbaNet::GuiUpdateBase * ptr = Updates[i].get();
		const std::type_info& info = typeid(*ptr);

		// got player online list refresh event
		if(info == typeid(LbaNet::PlayerStatusChanged))
		{
			LbaNet::PlayerStatusChanged * castedptr = 
				dynamic_cast<LbaNet::PlayerStatusChanged *>(ptr);

			if(castedptr->NewInfo.Joined)
				AddOnline(castedptr->NewInfo.Nickname, castedptr->NewInfo.Status, castedptr->NewInfo.Color);
			else
				RemoveOnline(castedptr->NewInfo.Nickname);

		}

		// got friend list refresh event
		if(info == typeid(LbaNet::FriendChangedUpdate))
		{
			LbaNet::FriendChangedUpdate * castedptr = 
				dynamic_cast<LbaNet::FriendChangedUpdate *>(ptr);

			UpdateFriend(castedptr->NewInfo);
		}
	}
}

/***********************************************************
show GUI
***********************************************************/
void CommunityBox::Display()
{
	_myBox->show();
	_myBox->activate();
}

/***********************************************************
hide GUI
***********************************************************/
void CommunityBox::Hide()
{
	_myBox->hide();
}

/***********************************************************
show/hide GUI
***********************************************************/
void CommunityBox::ToggleDisplay()
{
	if(_myBox->isVisible())
		_myBox->hide();
	else
	{
		_myBox->show();
		_myBox->activate();
	}
}

/***********************************************************
focus GUI
***********************************************************/
void CommunityBox::Focus(bool focus)
{

}



/***********************************************************
save size of windows to be restored after resize of the application
***********************************************************/
void CommunityBox::SaveGUISizes(int oldscreenX, int oldscreenY)
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("CommunityFrame"));

	CEGUI::UVector2 vec = frw->getPosition();
	_savedPosX = vec.d_x.asRelative((float)oldscreenX);
	_savedPosY = vec.d_y.asRelative((float)oldscreenY);
	_savedSizeX = frw->getWidth().asRelative((float)oldscreenX);
	_savedSizeY = frw->getHeight().asRelative((float)oldscreenY);
}


/***********************************************************
restore the correct size of the windows
***********************************************************/
void CommunityBox::RestoreGUISizes()
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("CommunityFrame"));

	frw->setPosition(CEGUI::UVector2(CEGUI::UDim(_savedPosX, 0), CEGUI::UDim(_savedPosY, 0)));
	frw->setWidth(CEGUI::UDim(_savedSizeX, 0));
	frw->setHeight(CEGUI::UDim(_savedSizeY, 0));
}