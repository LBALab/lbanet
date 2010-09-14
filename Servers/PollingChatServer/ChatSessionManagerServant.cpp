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

#include "ChatSessionManagerServant.h"
#include <IceUtil/UUID.h>

using namespace std;


/***********************************************************
constructor
***********************************************************/
ReaperTask::ReaperTask(int timeout, const ChatReceiverServantPtr & chatR) 
: _timeout(IceUtil::Time::seconds(timeout)), _chatR(chatR)
{
}

/***********************************************************
set callback
***********************************************************/
void ReaperTask::SetCallback(ChatSessionManagerServant * callbak)
{
	_callbak = callbak;
}


/***********************************************************
called by the timer
***********************************************************/
void ReaperTask::runTimerTask()
{
    IceUtil::Mutex::Lock sync(_mutex);
    std::list<std::pair<LbaNet::PollingChatSessionPrx, ChatPollingSessionServantPtr> >::iterator p = _reapables.begin();
    while(p != _reapables.end())
    {
        try
        {
            if((IceUtil::Time::now(IceUtil::Time::Monotonic) - (*p).second->timestamp()) > _timeout)
            {
				_callbak->SessionDestroyed(p->second->GetName());
				_chatR->Unsubscribe(p->second);
                p->first->destroy();
                p = _reapables.erase(p);
				
            }
            else
            {
                ++p;
            }
        }
        catch(const Ice::LocalException&)
        {
			_callbak->SessionDestroyed(p->second->GetName());
			_chatR->Unsubscribe(p->second);
            p = _reapables.erase(p);
        }
    }
}

/***********************************************************
add new session to monitor
***********************************************************/
void ReaperTask::add(const LbaNet::PollingChatSessionPrx& proxy, const ChatPollingSessionServantPtr& session)
{
    IceUtil::Mutex::Lock sync(_mutex);
    _reapables.push_back(make_pair(proxy, session));
}




/***********************************************************
constructor
***********************************************************/
ChatSessionManagerServant::ChatSessionManagerServant(const ReaperTaskPtr& reaper,
														const LbaNet::ChatRoomObserverPrx & chatP,
														const ChatReceiverServantPtr & chatR,
														const LbaNet::ConnectedTrackerPrx &ctracker)
: _reaper(reaper), _chatP(chatP), _chatR(chatR), _ctracker(ctracker)
{
}

/***********************************************************
destructor
***********************************************************/
ChatSessionManagerServant::~ChatSessionManagerServant()
{

}



/***********************************************************
create chat session
***********************************************************/
LbaNet::PollingChatSessionPrx ChatSessionManagerServant::create(const std::string & name, 
																  const std::string & password,
																  const Ice::Current& c)
{
	std::map<std::string, LbaNet::PollingChatSessionPrx>::iterator it =	_sessions.find(name);
	if(it != _sessions.end())
	{
		return it->second;
	}
	else
	{
		LbaNet::PollingChatSessionPrx proxy;
		ChatPollingSessionServantPtr session = new ChatPollingSessionServant(name, _chatP, _ctracker);
		proxy = LbaNet::PollingChatSessionPrx::uncheckedCast(c.adapter->addWithUUID(session));
		_reaper->add(proxy, session);
		_chatR->Subscribe(session);

		_sessions[name] = proxy;
		return proxy;
	}
}


/***********************************************************
inform session destroyed
***********************************************************/
void ChatSessionManagerServant::SessionDestroyed(const std::string & name)
{
	std::map<std::string, LbaNet::PollingChatSessionPrx>::iterator it =	_sessions.find(name);
	if(it != _sessions.end())
		_sessions.erase(it);
}