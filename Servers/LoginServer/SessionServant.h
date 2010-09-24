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


#ifndef _SESSION_SERVANT_H
#define _SESSION_SERVANT_H

#include <ClientSession.h>
#include <RoomManager.h>
#include <ConnectedTracker.h>
#include <WorldServerInterface.h>

#include <map>

#include "ChatParticipantServant.h"


using namespace LbaNet;


class SessionServant : public ClientSession, public IceUtil::Mutex
{
public:
	//! constructor
	SessionServant(const std::string& userId, const RoomManagerPrx& manager,
					const ConnectedTrackerPrx& ctracker, std::string version);

	//! destroy the session
	virtual void destroy(const Ice::Current&);


	//! get server version
	std::string GetVersion(const Ice::Current&);


	 	
 	//client send interface to server
 	void SetClientInterface(const ClientInterfacePrx& winterface, const Ice::Current&);
 	
 	//client send events to server
 	void ClientEvents(const EventsSeq& evts, const Ice::Current&);
 	
 	
 	// client ask server to change world
 	void ChangeWorld(const std::string& WorldName, const Ice::Current&);





	//! the client join a chat room
    virtual ChatRoomParticipantPrx JoinChatChannel(const std::string& room, const ChatRoomObserverPrx& observer,
												const Ice::Current&);

	//! the client leave a chat room
    virtual void LeaveChatChannel(const std::string& room, const ChatRoomObserverPrx& observer,
								const Ice::Current&);



	//! set player wisper interface
    virtual void SetWhisperInterface(const LbaNet::ChatRoomObserverPrx& winterface, const Ice::Current&);

	//! a player wisper to another
    virtual bool Whisper(const std::string& To, const std::string& Message, const ::Ice::Current&);


 	// client ask to get the list of world available
 	virtual void GetWorldList(const ::Ice::Current&); 	


	// change player status
	void ChangeStatus(const std::string& Status, const Ice::Current&);

	// change name display color
	virtual void ChangeNameColor(const std::string& Color, const Ice::Current&);


protected:
	// infrom connected world that player left
	void QuitCurrentWorld();

private:
	std::string							_userName;
	Ice::Long							_userNumber;

	std::string							_currStatus;
	std::string							_currColor;

	std::map<std::string, ChatRoomParticipantPrx>	_chat_rooms;


	ClientInterfacePrx					_client;
	RoomManagerPrx						_manager;
	ConnectedTrackerPrx					_ctracker;
	WorldServerInterfacePrx				_currentWorld;


	std::string							_version;
	std::string							_currWorldName;

};

#endif
