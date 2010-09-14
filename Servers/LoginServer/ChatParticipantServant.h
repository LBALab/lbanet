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


#ifndef _CHAT_PARTICIPANT_SERVANT_H
#define _CHAT_PARTICIPANT_SERVANT_H

#include <ChatInfo.h>
#include <RoomManager.h>

#include <string>

using namespace LbaNet;

class ChatParticipantServant : public ChatRoomParticipant
{
public:
	//! constructor
	ChatParticipantServant(const std::string& room, const ChatRoomObserverPrx& observer,
							const RoomManagerPrx& manager);

	//! destructor
    ~ChatParticipantServant();

	// say something
    virtual void Say(const std::string& sender, const std::string& text, const Ice::Current&);

private:
	const std::string _room;
    const RoomManagerPrx _manager;
    const ChatRoomObserverPrx _observer;
    const ChatRoomObserverPrx _publish;
};

#endif
