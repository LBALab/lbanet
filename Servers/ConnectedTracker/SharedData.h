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


#if !defined(__Agent_shared_data_h)
#define __Agent_shared_data_h

#include <string>
#include <vector>
#include <map>

#include <IceUtil/Mutex.h>
#include <IceUtil/Monitor.h>
#include <Ice/Config.h>

#include <ConnectedTracker.h>
#include <ChatInfo.h>

/***********************************************************************
 * Module:  SharedData.h
 * Author:  vivien
 * Modified: lundi 27 juillet 2009 14:59:17
 * Purpose: Declaration of the class SharedData
 ***********************************************************************/
class SharedData : public IceUtil::Mutex
{
public:
	//! default construtor
	SharedData();

	//! get player id
	Ice::Long GetId(const std::string & PlayerName);

	//! check if user already logged in
	//! if not log him in
	bool TryLogin(const std::string & PlayerName, long id);

	//! get connected list
	const LbaNet::ConnectedL & GetConnected();

	//! disconnect player
	bool Disconnect(Ice::Long playerid);
		
	//! set wisper interface used for web chat
	void SetWebWisperInterface(const LbaNet::ChatRoomObserverPrx& winterface);

	//! connect from web chat
	void ConnectFromWebChat(const std::string& Nickname);

	//! disconnect from web chat
	void DisconnectFromWebChat(const std::string& Nickname);	

	//! change player status
	void ChangeStatus(const std::string& Nickname, const std::string& NewStatus);

	//! change player name display color
	void ChangeNameColor(const std::string& Nickname, const std::string& Color);


	//! set player wisper interface
    void SetWhisperInterface(const std::string& Nickname, const LbaNet::ChatRoomObserverPrx& winterface);

	//! a player wisper to another
    bool Whisper(const std::string& From, const std::string& To, const std::string& Message);


protected:
	SharedData(const SharedData &);
	const SharedData & operator=(const SharedData &);

private:
	LbaNet::ConnectedL 										m_connected_users;
	std::map<std::string, long>								m_id_map;

	std::map<std::string, LbaNet::ChatRoomObserverPrx>		m_wisper_map;
	LbaNet::ChatRoomObserverPrx								m_web_wisper;
};

#endif