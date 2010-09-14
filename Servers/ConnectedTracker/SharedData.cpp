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


#include "SharedData.h"


/***********************************************************
constructor
***********************************************************/
SharedData::SharedData()
{

}

/***********************************************************
get player id
***********************************************************/
Ice::Long SharedData::GetId(const std::string & PlayerName)
{
	Lock sync(*this);
	std::map<std::string, long>::iterator it = m_id_map.find(PlayerName);
	if(it == m_id_map.end())
		return -1;

	LbaNet::PlayerInfo pi;
	pi.Id = it->second;
	pi.NameColor = "FFFFFFFF";
	m_connected_users[PlayerName] = pi;

	std::cout<<IceUtil::Time::now().toDateTime()<<": "<<PlayerName<<" connected with id "<<pi.Id<<std::endl;

	return pi.Id;
}

/***********************************************************
check if user already logged in
if not log him in
***********************************************************/
bool SharedData::TryLogin(const std::string & PlayerName, long id)
{
	Lock sync(*this);
	LbaNet::ConnectedL::iterator it = m_connected_users.find(PlayerName);
	if(it != m_connected_users.end())
		return false;

	m_id_map[PlayerName] = id;

	return true;
}

/***********************************************************
get connected list
***********************************************************/
const LbaNet::ConnectedL & SharedData::GetConnected()
{
	Lock sync(*this);
	return m_connected_users;
}

/***********************************************************
disconnect player
***********************************************************/
bool SharedData::Disconnect(Ice::Long playerid)
{
	Lock sync(*this);

	LbaNet::ConnectedL::iterator it = m_connected_users.begin();
	LbaNet::ConnectedL::iterator end = m_connected_users.end();

	for(; it != end; ++it)
	{
		if(it->second.Id == playerid)
		{
			std::cout<<IceUtil::Time::now().toDateTime()<<": "<<it->first<<" disconnected"<<std::endl;
			std::map<std::string, LbaNet::ChatRoomObserverPrx>::iterator itw = 	m_wisper_map.find(it->first);
			if(itw != m_wisper_map.end())
				m_wisper_map.erase(itw);

			m_connected_users.erase(it);

			return true;
		}
	}

	return false;
}

/***********************************************************
set wisper interface used for web chat
***********************************************************/	
void SharedData::SetWebWisperInterface(const LbaNet::ChatRoomObserverPrx& winterface)
{
	Lock sync(*this);
	m_web_wisper = winterface;
}

/***********************************************************
connect from web chat
***********************************************************/
void SharedData::ConnectFromWebChat(const std::string& Nickname)
{
	Lock sync(*this);
	LbaNet::PlayerInfo pi;
	pi.Id = -1;
	pi.NameColor = "FFFFFFFF";
	m_connected_users[Nickname] = pi;

	std::cout<<IceUtil::Time::now().toDateTime()<<": "<<Nickname<<" connected from web chat"<<std::endl;

	m_wisper_map[Nickname] = m_web_wisper;
}

/***********************************************************
disconnect from web chat
***********************************************************/
void SharedData::DisconnectFromWebChat(const std::string& Nickname)
{
	Lock sync(*this);
	LbaNet::ConnectedL::iterator it = m_connected_users.find(Nickname);
	if(it != m_connected_users.end())
	{
		std::cout<<IceUtil::Time::now().toDateTime()<<": "<<Nickname<<" disconnected"<<std::endl;
		std::map<std::string, LbaNet::ChatRoomObserverPrx>::iterator itw = 	m_wisper_map.find(Nickname);
		if(itw != m_wisper_map.end())
			m_wisper_map.erase(itw);

		m_connected_users.erase(it);
	}
}


/***********************************************************
change player status
***********************************************************/
void SharedData::ChangeStatus(const std::string& Nickname, const std::string& NewStatus)
{
	Lock sync(*this);
	LbaNet::ConnectedL::iterator it = m_connected_users.find(Nickname);
	if(it != m_connected_users.end())
		it->second.Status = NewStatus;
}


/***********************************************************
change player name display color
***********************************************************/
void SharedData::ChangeNameColor(const std::string& Nickname, const std::string& Color)
{
	Lock sync(*this);
	LbaNet::ConnectedL::iterator it = m_connected_users.find(Nickname);
	if(it != m_connected_users.end())
		it->second.NameColor = Color;
}



/***********************************************************
set player wisper interface
***********************************************************/
void SharedData::SetWhisperInterface(const std::string& Nickname, const LbaNet::ChatRoomObserverPrx& winterface)
{
	Lock sync(*this);
	m_wisper_map[Nickname] = winterface;
}

/***********************************************************
a player wisper to another
***********************************************************/
bool SharedData::Whisper(const std::string& From, const std::string& To, const std::string& Message)
{
	Lock sync(*this);
	std::map<std::string, LbaNet::ChatRoomObserverPrx>::iterator it = 	m_wisper_map.find(To);
	if(it != m_wisper_map.end())
	{
		try
		{
			it->second->Message(From, "/" + To + " " + Message);
		}
		catch(...)
		{
			return false;
		}

		return true;
	}

	return false;
}