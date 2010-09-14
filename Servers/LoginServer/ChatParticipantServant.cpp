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


#include "ChatParticipantServant.h"


/***********************************************************
constructor
***********************************************************/
ChatParticipantServant::ChatParticipantServant(const std::string& room, const ChatRoomObserverPrx& observer,
												const RoomManagerPrx& manager)
:	 _room(room),
    _manager(manager),
    _observer(observer),
    _publish(manager->JoinChat(room, observer))
{

}

/***********************************************************
destructor
***********************************************************/
ChatParticipantServant::~ChatParticipantServant()
{
    try
    {
		_manager->LeaveChat(_room, _observer);
    }
    catch(...)
    {
		// Ignore. The ice mediated invocation can throw an
		// exception on shutdown.
    }
}

/***********************************************************
say something
***********************************************************/
void ChatParticipantServant::Say(const std::string& sender, const std::string& text, const Ice::Current&)
{
	try
	{
		_publish->Message(sender, text);
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception updating actor info: "<<ex.what()<<std::endl;
	}
	catch(...)
	{
		std::cout<<"Unknown exception updating actor info. "<<std::endl;
	}
}