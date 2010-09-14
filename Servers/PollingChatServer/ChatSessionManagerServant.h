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


#ifndef _CHAT_SESSION_MANAGER_SERVANT_H
#define _CHAT_SESSION_MANAGER_SERVANT_H

#include <Ice/Ice.h>
#include "PollingChat.h"
#include "ChatPollingSession.h"
#include "ChatReceiverServant.h"

#include <list>
#include <map>

class ChatSessionManagerServant;

/***********************************************************************
 * Module:  ReaperTask
 * Author:  vivien
 * Purpose: Used to kill session in case of timeout
 ***********************************************************************/
class ReaperTask : public IceUtil::TimerTask
{
public:
	//! constructor
    ReaperTask(int timeout, const ChatReceiverServantPtr & chatR);

	//! set callback
	void SetCallback(ChatSessionManagerServant * callbak);

	//! called by the timer
    virtual void runTimerTask();

	//! add new session to monitor
    void add(const LbaNet::PollingChatSessionPrx& proxy, const ChatPollingSessionServantPtr& session);

private:
    IceUtil::Mutex _mutex;
    const IceUtil::Time _timeout;
    std::list<std::pair<LbaNet::PollingChatSessionPrx, ChatPollingSessionServantPtr> > _reapables;
	ChatReceiverServantPtr _chatR;
	ChatSessionManagerServant * _callbak;
};
typedef IceUtil::Handle<ReaperTask> ReaperTaskPtr;





/***********************************************************************
 * Module:  ChatSessionManagerServant
 * Author:  vivien
 * Purpose: chat session creator
 ***********************************************************************/
class ChatSessionManagerServant : public LbaNet::PollingChatSessionFactory
{
public:
	//! constructor
    ChatSessionManagerServant(const ReaperTaskPtr& reaper,
								const LbaNet::ChatRoomObserverPrx & chatP,
								const ChatReceiverServantPtr & chatR,
								const LbaNet::ConnectedTrackerPrx &ctracker);

	//! destructor
    ~ChatSessionManagerServant();

	//! create chat session
	virtual LbaNet::PollingChatSessionPrx create(const std::string & name, 
													const std::string & password, 
													const Ice::Current&);

	//! infrom session destroyed
	void SessionDestroyed(const std::string & name);


private:
	ReaperTaskPtr											_reaper;
	LbaNet::ChatRoomObserverPrx								_chatP;
	ChatReceiverServantPtr									_chatR;
	LbaNet::ConnectedTrackerPrx								_ctracker;

	std::map<std::string, LbaNet::PollingChatSessionPrx>	_sessions;
};

#endif
