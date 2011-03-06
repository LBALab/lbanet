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
#include "Teleport.h"
#include "QuestHandler.h"

class MapHandler;
class PlayerHandler;
class ServerLuaHandler;
class LuaHandlerBase;
class ScriptEnvironmentBase;
class InventoryItemDef;
class Spawn;

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

	// get client name
	std::string GetName(Ice::Long clientid);

	//get player proxy
	ClientProxyBasePtr GetProxy(Ice::Long clientid);


	//! get database
	boost::shared_ptr<DatabaseHandlerBase> GetDatabase();

 	
 	// used when a client update name info
	void UpdateClientExtraInfo(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo);

	//! teleport player
	void TeleportPlayer(ScriptEnvironmentBase * owner, Ice::Long clientid, long TeleportId);

	//! change map for player
	void ChangeMapPlayer(Ice::Long clientid, const std::string &NewMapName, long SpawningId,
							float offsetX=0, float offsetY=0, float offsetZ=0);

	//! change map for player
	void ChangeMapPlayer(Ice::Long clientid, const std::string &NewMapName, const std::string SpawnName,
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

	//! get player inventory
	LbaNet::ItemsMap GetInventory(Ice::Long clientid, int & inventorysize);

	//! update player inventory
	void UpdateInventory(Ice::Long clientid, LbaNet::ItemList Taken, LbaNet::ItemList Put, 
								LbaNet::ItemClientInformType informtype);


	//! set main player state
	void SetMainState(LbaNet::ModelState state);

	//! return main player state
	LbaNet::ModelState GetMainState();


	//! add tp
	void AddTeleport(boost::shared_ptr<TeleportDef> tp);

	//! remove tp
	bool RemoveTeleport(long id);

	//! get tp list
	const std::map<long, boost::shared_ptr<TeleportDef> > &GetTpList()
	{return m_teleports;}

	// get tp
	boost::shared_ptr<TeleportDef> GetTeleport(long id);


	//! send tp list to player
	LbaNet::TeleportsSeq GetTpList(ScriptEnvironmentBase * owner, Ice::Long clientid) const;


	//! save to lua
	void SaveToLua();


	//! add quest
	void AddQuest(QuestPtr quest);

	//! remove quest
	void RemoveQuest(long id);

	//! get quest
	QuestPtr GetQuest(long id);

	//! add item
	void AddInventoryItem(boost::shared_ptr<InventoryItemDef> item);

	//! get spawn
	boost::shared_ptr<Spawn> GetSpawn(const std::string & mapname, long spawnid);

	//! get spawn
	long GetSpawnId(const std::string & mapname, const std::string & name);

	//! get spawns
	std::map<long, boost::shared_ptr<Spawn> > GetSpawns(const std::string & mapname);


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



private:
	static SharedDataHandler *											_Instance;
	
	boost::shared_ptr<DatabaseHandlerBase>								_dbH;

	WorldInformation													_worldinfo;

	std::map<std::string, boost::shared_ptr<MapHandler> >				_currentmaps;
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >				_currentplayers;

	LbaNet::ModelState													_currentplayerstate;

	boost::shared_ptr<LuaHandlerBase>									m_luaHandler;

	std::map<long, boost::shared_ptr<TeleportDef> >						m_teleports;
};

#endif
