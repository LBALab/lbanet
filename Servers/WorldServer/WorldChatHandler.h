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

#ifndef _WORLD_CHAT_HANDLER_H
#define _WORLD_CHAT_HANDLER_H

#include <Ice/Ice.h>
#include <IceStorm/IceStorm.h>
#include <ChatInfo.h>


//! take care of connexion with wolrd chat
class WorldChatHandler
{
public:
	//! constructor
	WorldChatHandler(Ice::CommunicatorPtr communicator);

	//! destructor
	~WorldChatHandler(void);

	//! send a system message to world chat
	void SendSystemMessage(const std::string text);


private:
	LbaNet::ChatRoomObserverPrx		_channelpublisher;
};

#endif
