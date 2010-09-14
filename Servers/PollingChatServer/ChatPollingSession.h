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


#ifndef _CHAT_POLLING_SESSION_SERVANT_H
#define _CHAT_POLLING_SESSION_SERVANT_H

#include <Ice/Ice.h>
#include "PollingChat.h"

#include <ChatInfo.h>
#include <ConnectedTracker.h>

/***********************************************************************
 * Module:  ChatPollingSessionServant
 * Author:  vivien
 * Purpose: Polling Chat session servant
 ***********************************************************************/
class ChatPollingSessionServant : public LbaNet::PollingChatSession
{
public:
	//! constructor
	ChatPollingSessionServant(const std::string username,
								const LbaNet::ChatRoomObserverPrx & chatP,
								const LbaNet::ConnectedTrackerPrx &ctracker);

	//! destructor
    ~ChatPollingSessionServant();

	//! get user online
    virtual LbaNet::UserSeq getInitialUsers(const Ice::Current&);

	//! get update since last time asked
    virtual LbaNet::ChatRoomEventSeq getUpdates(const Ice::Current&);

	//! send message
    virtual Ice::Long send(const std::string& message, const Ice::Current&);

	//! destroy session
    virtual void destroy(const Ice::Current&);

	//! get timestamp since last action
    virtual IceUtil::Time timestamp() const;

	//! add new chat event
	void AddEvent(const LbaNet::ChatRoomEventPtr & evt);

	//! get usr name
	const std::string &GetName(){return _name;}

protected:
	//! send status update
	void UpdateStatus();

private:
	std::string			_name;
    IceUtil::Time		_timestamp; // The last time the session was refreshed.
    IceUtil::Time		_timestamptalk; // The last time we talked.
    bool				_destroy;
    IceUtil::Mutex		_mutex;
	bool				_away;

	LbaNet::ChatRoomObserverPrx _chatP;
	LbaNet::ConnectedTrackerPrx _ctracker;

	LbaNet::ChatRoomEventSeq	_events;

	std::string					_currstatus;
	std::string					_currcolor;
};
typedef IceUtil::Handle<ChatPollingSessionServant> ChatPollingSessionServantPtr;


#endif
