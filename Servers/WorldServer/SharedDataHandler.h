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
#include "ScriptInitHandler.h"


class MapHandler;
class PlayerHandler;
class ServerLuaHandler;
class LuaHandlerBase;
class ScriptEnvironmentBase;
class Spawn;

using namespace LbaNet;





//! take care of shared data between process
class SharedDataHandler : public IceUtil::Mutex, public ScriptInitHandler
{
public:
	// singleton pattern
	static SharedDataHandler * getInstance();

	//! destructor
	virtual ~SharedDataHandler(void){}


	//! set world default information
	void SetWorldDefaultInformation(WorldInformation &worldinfo);


	//! set database manager
	void SetDbManager(boost::shared_ptr<DatabaseHandlerBase> dbH);

	//! get database
	boost::shared_ptr<DatabaseHandlerBase> GetDatabase();


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



#ifdef _USE_QT_EDITOR_
	//! called by editor
	void EditorUpdate(const std::string &mapname, LbaNet::EditorUpdateBasePtr update);
#endif


	//! return position of a tp
	LbaNet::PlayerPosition GetTeleportPos(ScriptEnvironmentBase * owner, long playerid, long tpid,
												float CurrentRotation);

	//! return spawn pos
	LbaNet::PlayerPosition GetSpawnPos(const std::string &mapname, const std::string& spawnname, 
												float CurrentRotation);

	//! return spawn pos
	LbaNet::PlayerPosition GetSpawnPos(const std::string &mapname, long spawnid, float CurrentRotation);


	//! teleport the player
	void TeleportPlayer(long playerid, boost::shared_ptr<PlayerHandler> pinfo, 
							 const LbaNet::PlayerPosition &newpos);


	//*************
	//	LUA part
	//*************


	//! add tp
	virtual void AddTeleport(boost::shared_ptr<TeleportDef> tp);

	//! remove tp
	virtual bool RemoveTeleport(long id);

	//! get tp list
	const std::map<long, boost::shared_ptr<TeleportDef> > &GetTpList()
	{return m_teleports;}

	// get tp
	virtual boost::shared_ptr<TeleportDef> GetTeleport(long id);


	//! send tp list to player
	LbaNet::TeleportsSeq GetTpList(ScriptEnvironmentBase * owner, Ice::Long clientid) const;



	//! add quest
	virtual void AddQuest(boost::shared_ptr<Quest> quest);

	//! remove quest
	virtual void RemoveQuest(long id);

	//! get quest
	virtual boost::shared_ptr<Quest> GetQuest(long id);

	//! add item
	virtual void AddInventoryItem(boost::shared_ptr<InventoryItemDef> item);

	//! get spawn
	boost::shared_ptr<Spawn> GetSpawn(const std::string & mapname, long spawnid);

	//! get spawn
	long GetSpawnId(const std::string & mapname, const std::string & name);

	//! get spawns
	std::map<long, boost::shared_ptr<Spawn> > GetSpawns(const std::string & mapname);


	//! save to lua
	void SaveToLua();

	//! update client extra info
	void UpdateClientExtraInfo(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo);

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


	//! register client internal function
	void RegisterClient(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo,
							ClientProxyBasePtr proxy);


	//! return spawn pos
	LbaNet::PlayerPosition GetSpawnPosInternal(const std::string &mapname, long spawnid, 
																			float CurrentRotation);


	//! teleport the player
	void TeleportPlayerInternal(long playerid, boost::shared_ptr<PlayerHandler> pinfo, 
												const LbaNet::PlayerPosition &newpos);

private:
	static SharedDataHandler *											_Instance;

	boost::shared_ptr<DatabaseHandlerBase>								_dbH;

	WorldInformation													_worldinfo;

	std::map<std::string, boost::shared_ptr<MapHandler> >				_currentmaps;
	std::map<Ice::Long, std::string>									_currentplayermaps;


	boost::shared_ptr<LuaHandlerBase>									m_luaHandler;

	std::map<long, boost::shared_ptr<TeleportDef> >						m_teleports;

	boost::shared_ptr<PlayerHandler>									m_mainplayerH;
};

#endif
