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

#ifndef _SHARED_DATA_HANDLER_H__
#define _SHARED_DATA_HANDLER_H__


#include <map>
#include <string>
#include <boost/shared_ptr.hpp>
#include <IceUtil/Mutex.h>

#include "DatabaseHandlerBase.h"
#include "ClientProxyHandler.h"
#include "ServerExtendedEvents.h"


class MapHandler;
class PlayerHandler;
class ServerLuaHandler;


using namespace LbaNet;





//! take care of shared data between process
class SharedDataHandler : public IceUtil::Mutex
{
public:
	// singleton pattern
	static SharedDataHandler * getInstance();

	//! destructor
	~SharedDataHandler(void){}


	//! set world default information
	void SetWorldDefaultInformation(WorldInformation &worldinfo);

	//! set database manager
	void SetDbManager(boost::shared_ptr<DatabaseHandlerBase> dbH);

	//client send events to server
	void ClientEvents(Ice::Long clientid, const EventsSeq &evts);

	// used when a remote client connect to a world
	void RegisterClient(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo, 
							const ClientInterfacePrx &proxy);

	// used when a local client connect to a world
	void RegisterClient(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo, 
							ClientInterfacePtr proxy);

	// used when a client disconnect from a world
	void UnregisterClient(Ice::Long clientid); 

	// clean up
	void CleanUp();

	//get player proxy
	ClientProxyBasePtr GetProxy(Ice::Long clientid);


	//! get database
	boost::shared_ptr<DatabaseHandlerBase> GetDatabase();

 	
 	// used when a client update name info
	void UpdateClientExtraInfo(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo);

	//! teleport player
	void TeleportPlayer(Ice::Long clientid, long TeleportId);

	//! change map for player
	void ChangeMapPlayer(Ice::Long clientid, const std::string &NewMapName, long SpawningId,
							float offsetX=0, float offsetY=0, float offsetZ=0);

#ifdef _USE_QT_EDITOR_
	//! called by editor
	void EditorUpdate(const std::string &mapname, LbaNet::EditorUpdateBasePtr update);
#endif


	//! return the client lua filename for a map
	std::string GetClientLuaFilename(const std::string & mapname);


	//! update player shortcut
	void UpdatePlayerShortcut(Ice::Long clientid, int Position, long ItemId);

	//! player switch item
	void PlayerSwitchItem(Ice::Long clientid, long ItemId, int NewPosition);

	//! player use item
	void PlayerItemUsed(Ice::Long clientid, long ItemId);

	//! Player Create Letter
	void PlayerCreateLetter(Ice::Long clientid, const std::string & subject,
										const std::string & message);

	//! Player Destroy Item
	void PlayerDestroyItem(Ice::Long clientid, long ItemId);


protected:
	//! constructor
	SharedDataHandler(void){}

	//! returning the spawning info for a map
	PlayerPosition GetSpawningInfo(const std::string &MapName, 
									long SpawningId,
									bool &forcerotation);

	//! add events
	void AddEvents(const std::string &MapName,Ice::Long clientid, const EventsSeq &evts);

	//! add 1 event
	void AddEvent(const std::string &MapName,Ice::Long clientid, ClientServerEventBasePtr evt);

	// player leave map
	void PlayerLeaveMap(const std::string &MapName, Ice::Long clientid);


	//! register client internal function
	void RegisterClient(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo, 
							ClientProxyBasePtr proxy);


	//! internally change map for player
	void ChangeMapPlayer(Ice::Long clientid, LbaNet::PlayerPosition &newpos);

	//! send tp list to player
	void SendTpList(Ice::Long clientid, const ClientProxyBasePtr &proxy);


private:
	static SharedDataHandler *											_Instance;
	
	boost::shared_ptr<DatabaseHandlerBase>								_dbH;

	WorldInformation													_worldinfo;

	std::map<std::string, boost::shared_ptr<MapHandler> >				_currentmaps;
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >				_currentplayers;
};

#endif
