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


#include "ChatPollingSession.h"
#include "ChatReceiverServant.h"
#include <IceUtil/UUID.h>

///Checks whether a std::string containg positive hexadecimal value
///Returns true if possible
///Returns false otherwise
bool IsHexInt(const std::string& s)
{
	unsigned int rInt;
	std::istringstream i(s);
	i >> std::hex;
	if (!(i >> rInt))
		return false;

	return true;
}


/***********************************************************
constructor
***********************************************************/
ChatPollingSessionServant::ChatPollingSessionServant(const std::string username,
													const LbaNet::ChatRoomObserverPrx & chatP,
													const LbaNet::ConnectedTrackerPrx &ctracker) 
:    _name(username),
    _timestamp(IceUtil::Time::now(IceUtil::Time::Monotonic)),
    _destroy(false), _chatP(chatP), _ctracker(ctracker),
	_currcolor("FFFFFFFF"), _away(false), _timestamptalk(IceUtil::Time::now(IceUtil::Time::Monotonic))
{
	try
	{
		_chatP->Message("info", "#joined " +_name);
		_ctracker->ConnectFromWebChat(_name);
	}
	catch(Ice::Exception &)	{}
}

/***********************************************************
destructor
***********************************************************/
ChatPollingSessionServant::~ChatPollingSessionServant()
{
}

/***********************************************************
get user online
***********************************************************/
LbaNet::UserSeq ChatPollingSessionServant::getInitialUsers(const Ice::Current&)
{
	LbaNet::UserSeq res;

    IceUtil::Mutex::Lock sync(_mutex);
    if(_destroy)
        throw Ice::ObjectNotExistException(__FILE__, __LINE__);

	try
	{
		LbaNet::ConnectedL cl = _ctracker->GetConnected();
		LbaNet::ConnectedL::const_iterator it = cl.begin();
		LbaNet::ConnectedL::const_iterator end = cl.end();
		for(;it != end; ++it)
		{
			LbaNet::ChatUserStatusPtr cs = new LbaNet::ChatUserStatus();
			cs->name = it->first;
			cs->color = it->second.NameColor;
			cs->status = it->second.Status;
			res.push_back(cs);
		}
	}
	catch(Ice::Exception &)	{}

	return res;
}

/***********************************************************
get update since last time asked
***********************************************************/
LbaNet::ChatRoomEventSeq ChatPollingSessionServant::getUpdates(const Ice::Current&)
{
    IceUtil::Mutex::Lock sync(_mutex);
    if(_destroy)
        throw Ice::ObjectNotExistException(__FILE__, __LINE__);

	_timestamp = IceUtil::Time::now(IceUtil::Time::Monotonic);

	// we are afk
	if(!_away && (_timestamp -_timestamptalk) > IceUtil::Time::seconds(300))
	{
		_away = true;
		_currstatus = "away";
		UpdateStatus();
	}
		

	LbaNet::ChatRoomEventSeq seq;
	seq.swap(_events);
	return seq;
}

/***********************************************************
send message
***********************************************************/
Ice::Long ChatPollingSessionServant::send(const std::string& message, const Ice::Current&)
{
    IceUtil::Mutex::Lock sync(_mutex);
    if(_destroy)
        throw Ice::ObjectNotExistException(__FILE__, __LINE__);

	_timestamptalk = IceUtil::Time::now(IceUtil::Time::Monotonic);

	// we are not anymore afk
	if(_away)
	{
		_away = false;
		_currstatus = "";
		UpdateStatus();
	}


	// return if text is empty
	if(message == "")
		return IceUtil::Time::now().toMilliSeconds();

	// if it is a command - preproccess it
	if(message[0] == '/')
	{
		std::vector<std::string> tok;
		std::stringstream ss(message);
		std::string buf;
		while(ss >> buf)
		{
			tok.push_back(buf);
		}

		if(tok.size() > 0)
		{
			if(tok[0] == "/w")
			{
				if(tok.size() < 3)
					return IceUtil::Time::now().toMilliSeconds();

				std::string playername = tok[1];
				std::string message;
				for(size_t i=2; i<tok.size(); ++i)
					message += tok[i] + " ";

				try
				{
					_ctracker->Whisper(_name, playername, message);
				}
				catch(Ice::Exception &)	{}
				
				return IceUtil::Time::now().toMilliSeconds();
			}

			if(tok[0] == "/afk")
			{
				_currstatus = "away";
				UpdateStatus();
				return IceUtil::Time::now().toMilliSeconds();
			}

			if(tok[0] == "/back")
			{
				_currstatus = "";
				UpdateStatus();
				return IceUtil::Time::now().toMilliSeconds();
			}

			if(tok[0] == "/colour")
			{
				if(tok.size() < 2)
					return IceUtil::Time::now().toMilliSeconds();

				if(tok[1].size() == 6)
				{
					if(IsHexInt(tok[1]))
					{
						_currcolor = "FF"+tok[1];
						UpdateStatus();
						return IceUtil::Time::now().toMilliSeconds();
					}
				}
			}

		}
	}



	try
	{
		_chatP->Message(_name, message);
	}
	catch(Ice::Exception &)	{}

	return IceUtil::Time::now().toMilliSeconds();
}

/***********************************************************
destroy session
***********************************************************/
void ChatPollingSessionServant::destroy(const Ice::Current& c)
{
    IceUtil::Mutex::Lock sync(_mutex);
    if(_destroy)
        throw Ice::ObjectNotExistException(__FILE__, __LINE__);

	_destroy = true;

    try
    {
        c.adapter->remove(c.id);
		_chatP->Message("info", "#left " +_name);
		_ctracker->DisconnectFromWebChat(_name);
    }
    catch(const Ice::Exception&)
    {
        // No need to clean up, the server is shutting down.
    }
}

/***********************************************************
get timestamp since last action
***********************************************************/
IceUtil::Time ChatPollingSessionServant::timestamp() const
{
    IceUtil::Mutex::Lock sync(_mutex);
    if(_destroy)
        throw Ice::ObjectNotExistException(__FILE__, __LINE__);

	return _timestamp;
}



/***********************************************************
add new chat event
***********************************************************/
void ChatPollingSessionServant::AddEvent(const LbaNet::ChatRoomEventPtr & evt)
{
    IceUtil::Mutex::Lock sync(_mutex);
	_events.push_back(evt);
}

/***********************************************************
send status update
***********************************************************/
void ChatPollingSessionServant::UpdateStatus()
{
	try
	{
		_chatP->Message("info", "#status "+ _name + " " + _currstatus + " " + _currcolor);
		_ctracker->ChangeStatus(_name, _currstatus);
		_ctracker->ChangeNameColor(_name, _currcolor);
	}
	catch(Ice::Exception &)	{}
}