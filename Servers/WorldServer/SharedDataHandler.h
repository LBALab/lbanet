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


	// return inventory size
	int GetInventorySize(Ice::Long clientid);

	// return inventory content
	ItemsMap GetInventory(Ice::Long clientid);

	// return shortcuts
	ShortcutsSeq GetShorcuts(Ice::Long clientid);

	//! get player info
	SavedWorldInfo GetInfo(Ice::Long clientid);


	//!  update player position
	void UpdatePlayerPosition(Ice::Long clientid, const PlayerPosition & pos);

	//!  get player position
	PlayerPosition GetPlayerPosition(Ice::Long clientid);

	//! get player mode string
	std::string GetPlayerModeString(Ice::Long clientid);


	//! get player extra info
	LbaNet::ObjectExtraInfo GetPlayerExtraInfo(Ice::Long clientid);


	//! get database
	boost::shared_ptr<DatabaseHandlerBase> GetDatabase();


	//!  get player proxy
	ClientProxyBasePtr GetProxy(Ice::Long clientid);


	//!  update player stance
	//! return true if state has been updated
	bool UpdatePlayerStance(Ice::Long clientid, LbaNet::ModelStance NewStance,
									ModelInfo & returnmodel );


	//!  update player state
	//! return true if state has been updated
	bool UpdatePlayerState(Ice::Long clientid, LbaNet::ModelState NewState,
									ModelInfo & returnmodel );
 	
 	// used when a client update name info
	void UpdateClientExtraInfo(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo);


	//! get the place to respawn in case of death
	LbaNet::PlayerPosition GetSpawningPlace(Ice::Long clientid);

	//!  raised player from dead
	//! return true if raised
	bool RaiseFromDead(Ice::Long clientid, ModelInfo & returnmodel);

	//! teleport player
	void TeleportPlayer(Ice::Long clientid, const std::string &TeleportId);

	//! change map for player
	void ChangeMapPlayer(Ice::Long clientid, const std::string &NewMapName, 
										const std::string &SpawningName);

protected:
	//! constructor
	SharedDataHandler(void){}

	//! returning the spawning info for a map
	PlayerPosition GetSpawningInfo(const std::string &MapName, 
									const std::string &SpawningName,
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

private:
	static SharedDataHandler *											_Instance;
	
	boost::shared_ptr<DatabaseHandlerBase>								_dbH;

	WorldInformation													_worldinfo;

	std::map<std::string, boost::shared_ptr<MapHandler> >				_currentmaps;
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >				_currentplayers;
};

#endif
