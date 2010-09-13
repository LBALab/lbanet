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


#ifndef __CHAT_RECEIVER_SERVANT_H_
#define __CHAT_RECEIVER_SERVANT_H_

#include <ChatInfo.h>
#include <string>

class GameGUI;


/***********************************************************
  Wrapper class containing the callback function used when a
  message is received in IceStorm
***********************************************************/
class ChatReceiverServant : public LbaNet::ChatRoomObserver
{
public:

	explicit ChatReceiverServant(const std::string & RoomName)
		: _RoomName(RoomName)
	{}

	// callback function called when a message is received from IceStorm
	virtual void Message(const std::string& Sender, const std::string& Text, const Ice::Current&);


private:
	std::string _RoomName;
};

#endif
