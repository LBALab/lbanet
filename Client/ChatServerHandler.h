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


#ifndef _LBANET_CHAT_SERVER_HANDLER_
#define _LBANET_CHAT_SERVER_HANDLER_

#include <IceUtil/Thread.h>
#include <ChatInfo.h>
#include <fstream>
#include <ClientSession.h>


class ChatServerHandler : public IceUtil::Thread
{
public:
	// constructor
	ChatServerHandler();


	//! initialize
	void Initialize(const std::string PlayerName, const Ice::ObjectAdapterPtr& adapter,
							const LbaNet::ClientSessionPrx& session,
							const std::string& category);


	//! disconnect from server
	void Disconnect();

	// join a chat channel
    bool JoinChatChannel(const std::string& roomName);

	// leave a chat channel
    bool LeaveChatChannel(const std::string& roomName);

	// change map associated with chat
	void ChangeMap(const std::string & NewWorld, const std::string & NewMap);


	// send chat text to server
	void SendChatText(const std::string & Text);

	// running function of the thread
	virtual void run();


protected:
	// find a chat room if we already joined
	LbaNet::ChatRoomParticipantPrx FindChatRoom(const std::string& room) const;

	// process text
	void ProcessText(const std::string & Text);

	// send chat to room
	void SendChat(LbaNet::ChatRoomParticipantPrx room, const std::string & Text);

	// change status
	void ChangeStatus(const std::string & NewStatus);

	// whisper to a player
	bool Whisper(const std::string & playername, const std::string & message);


private:
	// threading and mutex stuff
	IceUtil::Monitor<IceUtil::Mutex>						_monitor;
	bool													_running;
	IceUtil::ThreadControl									_threadcontrol;
	std::vector<std::string>								_texttoprocess;

    Ice::ObjectAdapterPtr									_adapter;	// ice adapter
    LbaNet::ClientSessionPrx								_session;	// glacier session

	std::map<std::string, LbaNet::ChatRoomParticipantPrx>	_chat_publishers;	// pointer to the chat rooms publishers
	std::map<std::string, LbaNet::ChatRoomObserverPrx>		_chat_observers;	// pointer to the chat rooms observers
	std::string												_category; // category

	std::string												_current_world;
	std::string												_current_map;
	std::string												_main_name;

};






#endif
