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


#ifndef _ROOM_MANAGER_SERVANT_H
#define _ROOM_MANAGER_SERVANT_H

#include <ConnectedTracker.h>

#include <Ice/Ice.h>
#include <IceStorm/IceStorm.h>

using namespace LbaNet;

#include "SharedData.h"
#include "DatabaseHandler.h"

class ConnectedTrackerServant : public ConnectedTracker
{
public:
	//! constructor
    ConnectedTrackerServant(const Ice::CommunicatorPtr& communicator, SharedData * shd, 
								DatabaseHandler &dbh);

	//! add a connected person
    virtual Ice::Long Connect(const std::string& Nickname, const Ice::Current&);

	//! remove a disconnected person
    virtual void Disconnect(Ice::Long Id, const Ice::Current&);
	
	//! set wisper interface used for web chat
	virtual void SetWebWisperInterface(const LbaNet::ChatRoomObserverPrx& winterface, 
										const Ice::Current&);

	//! connect from web chat
	virtual void ConnectFromWebChat(const std::string& Nickname, 
									const Ice::Current&);

	//! disconnect from web chat
	virtual void DisconnectFromWebChat(const std::string& Nickname, const Ice::Current&);	

	//! get list of connected people
    virtual LbaNet::ConnectedL GetConnected(const Ice::Current&);

	//! change status of one player
    virtual void ChangeStatus(const std::string& Nickname, const std::string& NewStatus, 
							const Ice::Current&);

	//! change player name display color
    virtual void ChangeNameColor(const std::string& Nickname, const std::string& Color, 
									const Ice::Current&);

	//! set player wisper interface
    virtual void SetWhisperInterface(const std::string& Nickname, const LbaNet::ChatRoomObserverPrx& winterface, 
									const Ice::Current&);

	//! a player wisper to another
    virtual bool Whisper(const std::string& From, const std::string& To, const std::string& Message, 
								const ::Ice::Current&);

private:
	const Ice::CommunicatorPtr& _communicator;

	SharedData *				_shd;
	DatabaseHandler &			_dbh;
};

#endif
