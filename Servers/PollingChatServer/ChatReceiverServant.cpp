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

#include "ChatReceiverServant.h"
#include <algorithm>

/***********************************************************
callback function called when a message is received from IceStorm
***********************************************************/
void ChatReceiverServant::Message(const std::string& Sender, const std::string& Text, const Ice::Current&)
{
	if(Sender == "info")
	{
		if(Text.substr(0, 7) == "#joined")
		{
			LbaNet::UserJoinedEventPtr ev = new LbaNet::UserJoinedEvent();
			ev->timestamp = IceUtil::Time::now().toMilliSeconds();
			ev->name = Text.substr(8);
			PublishOther(ev);
			return;
		}

		if(Text.substr(0, 5) == "#left")
		{
			LbaNet::UserLeftEventPtr ev = new LbaNet::UserLeftEvent();
			ev->timestamp = IceUtil::Time::now().toMilliSeconds();
			ev->name = Text.substr(6);
			PublishOther(ev);
			return;
		}

		if(Text.substr(0, 7) == "#status")
		{
			LbaNet::UserStatusEventPtr ev = new LbaNet::UserStatusEvent();
			ev->timestamp = IceUtil::Time::now().toMilliSeconds();

			std::string tmptxt = Text.substr(8);
			ev->name = tmptxt.substr(0, tmptxt.find(" "));
			tmptxt = tmptxt.substr(tmptxt.find(" ")+1);
			ev->status = tmptxt.substr(0, tmptxt.find(" "));
			tmptxt = tmptxt.substr(tmptxt.find(" ")+1);
			ev->color = tmptxt;

			PublishStatus(ev);
			return;
		}

	}

	LbaNet::MessageEventPtr ev = new LbaNet::MessageEvent();
	ev->timestamp = IceUtil::Time::now().toMilliSeconds();
	ev->name = Sender;
	ev->message = Text;
	PublishMessage(ev);
}

/***********************************************************
subscribe to chat events
***********************************************************/
void ChatReceiverServant::Subscribe(const ChatPollingSessionServantPtr session)
{
	IceUtil::Mutex::Lock sync(_mutex);
	_sessions.push_back(session);
}

/***********************************************************
unsubscribe from chat events
***********************************************************/
void ChatReceiverServant::Unsubscribe(const ChatPollingSessionServantPtr session)
{
	IceUtil::Mutex::Lock sync(_mutex);
	std::vector<ChatPollingSessionServantPtr>::iterator it = std::find(_sessions.begin(), _sessions.end(), session);
	if(it != _sessions.end())
		_sessions.erase(it);
}


/***********************************************************
publish an event
***********************************************************/
void ChatReceiverServant::PublishMessage(const LbaNet::MessageEventPtr & evt)
{
	// take care fo whispers
	if(evt->message[0] == '/')
	{
		std::vector<std::string> tok;
		std::stringstream ss(evt->message);
		std::string buf;
		while(ss >> buf)
		{
			tok.push_back(buf);
		}
		if(tok.size() > 1)
		{
			tok[0] = tok[0].substr(1);
			IceUtil::Mutex::Lock sync(_mutex);
			for(size_t i=0; i<_sessions.size(); ++i)
			{
				if(_sessions[i]->GetName() == tok[0])
				{
					LbaNet::MessageEventPtr evnew = new LbaNet::MessageEvent();
					evnew->timestamp = evt->timestamp;
					evnew->name = evt->name;

					for(size_t j=1; j<tok.size(); ++j)
						evnew->message += tok[j] + " ";

					_sessions[i]->AddEvent(evnew);
					return;
				}
					
			}
		}
	}
	else
		PublishOther(evt);
}



/***********************************************************
publish an event
***********************************************************/
void ChatReceiverServant::PublishStatus(const LbaNet::UserStatusEventPtr & evt)
{
	IceUtil::Mutex::Lock sync(_mutex);
	for(size_t i=0; i<_sessions.size(); ++i)
	{
		_sessions[i]->AddEvent(evt);
	}
}



/***********************************************************
publish an event
***********************************************************/
void ChatReceiverServant::PublishOther(const LbaNet::ChatRoomEventPtr & evt)
{
	IceUtil::Mutex::Lock sync(_mutex);
	for(size_t i=0; i<_sessions.size(); ++i)
	{
		if(_sessions[i]->GetName() != evt->name)
			_sessions[i]->AddEvent(evt);
	}
}
