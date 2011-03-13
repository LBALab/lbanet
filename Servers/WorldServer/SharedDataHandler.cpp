#include "SharedDataHandler.h"
#include "PlayerHandler.h"
#include "MapHandler.h"
#include "SynchronizedTimeHandler.h"
#include "LogHandler.h"
#include "InventoryItemHandler.h"
#include "LuaHandlerBase.h"
#include "QuestHandler.h"
#include "Quest.h"
#include "Spawn.h"


SharedDataHandler* SharedDataHandler::_Instance = NULL;


/***********************************************************
singleton pattern
***********************************************************/
SharedDataHandler * SharedDataHandler::getInstance()
{
    if(!_Instance)
    {
        _Instance = new SharedDataHandler();
		return _Instance;
    }
    else
    {
		return _Instance;
    }
}


/***********************************************************
set world default information
***********************************************************/
void SharedDataHandler::SetWorldDefaultInformation(WorldInformation &worldinfo)
{
	// copy world info
	{
	Lock sync(*this);
	_worldinfo = worldinfo;
	_currentmaps.clear();
	}

	//init lua part
	std::string luafile = "Worlds/" + worldinfo.Description.WorldName + "/Lua/";
	luafile += "general.lua";

	m_luaHandler = boost::shared_ptr<ServerLuaHandler>(new ServerLuaHandler());
	m_luaHandler->LoadFile(luafile);
	m_luaHandler->CallLua("Init", this);



	Lock sync(*this);


//#ifndef _USE_QT_EDITOR_

	// create all maps
	LbaNet::MapsSeq::const_iterator itm = worldinfo.Maps.begin();
	LbaNet::MapsSeq::const_iterator endm = worldinfo.Maps.end();
	for(; itm != endm; ++itm)
	{
		std::string luafile = "Worlds/" + _worldinfo.Description.WorldName + "/Lua/";
		
		// custom server file
		std::string customluafile = luafile+"CustomServer.lua";
		luafile += itm->second.Name + "_server.lua";

		// create map object
		boost::shared_ptr<MapHandler> mapH(new MapHandler(worldinfo.Description.WorldName, itm->second, luafile, customluafile));
		_currentmaps[itm->first] = mapH;
	}
//#endif

}



/***********************************************************
set database manager
***********************************************************/
void SharedDataHandler::SetDbManager(boost::shared_ptr<DatabaseHandlerBase> dbH)
{
	Lock sync(*this);
	_dbH = dbH;
}


/***********************************************************
get database
***********************************************************/
boost::shared_ptr<DatabaseHandlerBase> SharedDataHandler::GetDatabase()
{
	Lock sync(*this);
	return _dbH;
}


/***********************************************************
client send events to server
***********************************************************/
void SharedDataHandler::ClientEvents(Ice::Long clientid, const EventsSeq &evts)
{
	Lock sync(*this);

	//get player current map
	std::map<Ice::Long, std::string>::iterator it = _currentplayermaps.find(clientid);
	if(it != _currentplayermaps.end())
		AddEvents(it->second, clientid, evts);
}


/***********************************************************
used when a client connect to a world
***********************************************************/
void SharedDataHandler::RegisterClient(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo, 
											const ClientInterfacePrx &proxy)
{
	// internal - no lock

	RegisterClient(clientid, extrainfo, new RemoteClientProxy(proxy));
}


/***********************************************************
used when a client connect to a world
***********************************************************/
void SharedDataHandler::RegisterClient(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo, 
											ClientInterfacePtr proxy)
{
	// internal - no lock

	RegisterClient(clientid, extrainfo, new LocalClientProxy(proxy));
}



/***********************************************************
used when a client connect to a world
***********************************************************/
void SharedDataHandler::RegisterClient(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo, 
											ClientProxyBasePtr proxy)
{
	Lock sync(*this);
	LbaNet::SavedWorldInfo savedinfo;

	// first get info from database
	if(_dbH)
		savedinfo = _dbH->ChangeWorld(_worldinfo.Description.WorldName, 
								(long)clientid, _worldinfo.StartingInfo.InventorySize);

	// check if first time arrival in world
	if(savedinfo.ppos.MapName == "")
	{
		//in this case set the default information
		bool forcerotation;
		savedinfo.ppos = GetSpawningInfo(	_worldinfo.StartingInfo.StartingMap, 
											(long)_worldinfo.StartingInfo.SpawningId,
											forcerotation);

		savedinfo.lifemana.CurrentLife = _worldinfo.StartingInfo.StartingLife;
		savedinfo.lifemana.MaxLife = _worldinfo.StartingInfo.StartingLife;
		savedinfo.lifemana.CurrentMana = _worldinfo.StartingInfo.StartingMana;
		savedinfo.lifemana.MaxMana = _worldinfo.StartingInfo.StartingMana;
		savedinfo.inventory.InventoryStructure = _worldinfo.StartingInfo.StartingInventory;
		savedinfo.model = _worldinfo.StartingInfo.StartingModel;


		// set default values
		savedinfo.EquipedWeapon = -1;
		savedinfo.EquipedOutfit = -1;
		savedinfo.EquipedMount = -1;
		savedinfo.model.SkinColor = -1;
		savedinfo.model.EyesColor = -1;
		savedinfo.model.HairColor = -1;
		savedinfo.model.OutfitColor = -1;
		savedinfo.model.WeaponColor = -1;
		savedinfo.model.MountSkinColor = -1;
		savedinfo.model.MountHairColor = -1;
	}

	// reset map if needed
	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator it = _currentmaps.find(savedinfo.ppos.MapName);
	if(it == _currentmaps.end())
	{
		bool forcerotation;
		savedinfo.ppos = GetSpawningInfo(	_worldinfo.StartingInfo.StartingMap, 
											(long)_worldinfo.StartingInfo.SpawningId,
											forcerotation);
	}

	if(savedinfo.model.ModelName == "")
		savedinfo.model = _worldinfo.StartingInfo.StartingModel;


	// create player object
	boost::shared_ptr<PlayerHandler> player(new PlayerHandler((long)clientid, proxy, 
											_dbH, _worldinfo.Description.WorldName, savedinfo, extrainfo));
#ifdef _USE_QT_EDITOR_
	m_mainplayerH = player;
#endif

	// teleport player to correct map
	TeleportPlayerInternal((long)clientid, player, savedinfo.ppos);






	// send friend list to client
	if(_dbH)
	{
		 //also quest list
		std::vector<long> questStarted, questFinished;
		_dbH->GetQuestInfo(_worldinfo.Description.WorldName, (long)clientid, questStarted, questFinished);
		LbaNet::QuestsMap startedQ, endedQ;
		for(size_t i=0; i< questStarted.size(); ++i)
		{
			QuestPtr q = QuestHandler::getInstance()->GetQuest(questStarted[i]);
			if(q)
			{
				LbaNet::QuestInfo qinf;
				qinf.Id = questStarted[i];
				qinf.ChapterTextId = q->GetChapter();
				qinf.QuestAreaTextId = q->GetLocationTextId();	
				qinf.TittleTextId = q->GetTitleTextId();
				qinf.DescriptionTextId = q->GetDescriptionTextId();
				qinf.Visible = q->GetVisible();
				startedQ[qinf.Id] = qinf;
			}
		}
		for(size_t i=0; i< questFinished.size(); ++i)
		{
			QuestPtr q = QuestHandler::getInstance()->GetQuest(questFinished[i]);
			if(q)
			{
				LbaNet::QuestInfo qinf;
				qinf.Id = questFinished[i];
				qinf.ChapterTextId = q->GetChapter();
				qinf.QuestAreaTextId = q->GetLocationTextId();	
				qinf.TittleTextId = q->GetTitleTextId();
				qinf.DescriptionTextId = q->GetDescriptionTextId();
				qinf.Visible = q->GetVisible();
				endedQ[qinf.Id] = qinf;
			}
		}

		// get friend list from db
		LbaNet::FriendsSeq friends = _dbH->GetFriends((long)clientid);

		// send list to player
		if(proxy)
		{
			EventsSeq toplayer;
			GuiParamsSeq paramseq;
			paramseq.push_back(new FriendListGuiParameter(friends));
			toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"CommunityBox", paramseq, false, false));

			GuiParamsSeq paramseq2;
			paramseq2.push_back(new QuestJournalGuiParameter(startedQ, endedQ));
			toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"JournalBox", paramseq2, false, false));

			try
			{
				proxy->ServerEvents(toplayer);
			}
			catch(const IceUtil::Exception& ex)
			{
				std::cout<<"Exception in sending event to client: "<<ex.what()<<std::endl;
			}
			catch(...)
			{
				std::cout<<"Unknown exception in sending event to client. "<<std::endl;
			}
		}
	}

}




/***********************************************************
used when a client disconnect from a world
***********************************************************/
 void SharedDataHandler::UnregisterClient(Ice::Long clientid)
{
	Lock sync(*this);

	//get player current map
	std::map<Ice::Long, std::string>::iterator it = _currentplayermaps.find(clientid);
	if(it != _currentplayermaps.end())
	{
		// make player leave map
		std::map<std::string, boost::shared_ptr<MapHandler> >::iterator itmap = _currentmaps.find(it->second);
		if(itmap != _currentmaps.end())
		{
			itmap->second->ExtRemovePlayer(clientid);
		}

		//remove player
		_currentplayermaps.erase(it);
	}
} 






/***********************************************************
add events
***********************************************************/
void SharedDataHandler::AddEvents(const std::string &MapName, Ice::Long clientid, const EventsSeq &evts)
{
	// internal - no lock

	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator it = _currentmaps.find(MapName);
	if(it != _currentmaps.end())
		it->second->AddEvents(clientid, evts);
}


/***********************************************************
add 1 event
***********************************************************/
void SharedDataHandler::AddEvent(const std::string &MapName,Ice::Long clientid, 
									ClientServerEventBasePtr evt)
{
	// internal - no lock

	if(MapName == "") // send to all maps
	{
		std::map<std::string, boost::shared_ptr<MapHandler> >::iterator it = _currentmaps.begin();
		std::map<std::string, boost::shared_ptr<MapHandler> >::iterator end = _currentmaps.end();
		for(; it != end; ++it)
			it->second->AddEvent(clientid, evt);
	}
	else
	{
		std::map<std::string, boost::shared_ptr<MapHandler> >::iterator it = _currentmaps.find(MapName);
		if(it != _currentmaps.end())
			it->second->AddEvent(clientid, evt);
	}
}



/***********************************************************
return position of a tp
***********************************************************/
LbaNet::PlayerPosition SharedDataHandler::GetTeleportPos(ScriptEnvironmentBase * owner, long playerid, 
															long tpid,	float CurrentRotation)
{
	Lock sync(*this);

	// get tp info
	std::map<long, boost::shared_ptr<TeleportDef> >::iterator ittp = m_teleports.find(tpid);
	if(ittp != m_teleports.end())
	{
		//check if player allowed to tp
		if(ittp->second->ValidForPlayer(owner, playerid))
			return GetSpawnPosInternal(ittp->second->GetMapName(), ittp->second->GetSpawn(), CurrentRotation);
	}

	LbaNet::PlayerPosition newpos;
	return newpos;
}


/***********************************************************
return spawn pos
***********************************************************/
LbaNet::PlayerPosition SharedDataHandler::GetSpawnPos(const std::string &mapname, 
													  const std::string& spawnname, 
														float CurrentRotation)
{
	Lock sync(*this);
	long spawnid = SharedDataHandler::GetSpawnId(mapname, spawnname);
	return GetSpawnPosInternal(mapname, spawnid, CurrentRotation);
}


/***********************************************************
return spawn pos
***********************************************************/
LbaNet::PlayerPosition SharedDataHandler::GetSpawnPos(const std::string &mapname, long spawnid, 
													  float CurrentRotation)
{
	Lock sync(*this);
	return GetSpawnPosInternal(mapname, spawnid, CurrentRotation);
}


/***********************************************************
return spawn pos
***********************************************************/
LbaNet::PlayerPosition SharedDataHandler::GetSpawnPosInternal(const std::string &mapname, long spawnid, 
																	float CurrentRotation)
{
	// no lock - internal function

	LbaNet::PlayerPosition newpos;
	newpos.Rotation = CurrentRotation;

	// get spawn info
	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator itmap = _currentmaps.find(mapname);
	if(itmap != _currentmaps.end())
	{
		boost::shared_ptr<Spawn> spn = itmap->second->GetSpawn(spawnid);
		if(spn)
		{
			newpos.MapName = mapname;
			newpos.X = spn->GetPosX();
			newpos.Y = spn->GetPosY();
			newpos.Z = spn->GetPosZ();

			if(spn->GetForceRotation())
				newpos.Rotation = spn->GetRotation();
		}
	}

	return newpos;
}



/***********************************************************
teleport the player
***********************************************************/
void SharedDataHandler::TeleportPlayerInternal(long playerid, boost::shared_ptr<PlayerHandler> pinfo, 
												const LbaNet::PlayerPosition &newpos)
{
	// teleport player
	if(pinfo)
		pinfo->Teleport(newpos);

	// internally set player to correct map
	_currentplayermaps[playerid] = newpos.MapName;


	//connect player to new map
#ifndef _USE_QT_EDITOR_
	//check if map handler for the map is already present
	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator it = _currentmaps.find(newpos.MapName);
	if(it != _currentmaps.end())
	{
		//start run thread if not started already
		it->second->StartThread();

		// add proxies to the map
		it->second->ExtAddPlayer(playerid, pinfo);
	}
	else
	{
		// log the issue, we have no map of this name
		std::stringstream strs;
		strs<<"Player trying to go to a non existing map - player id: "<<playerid;
		LogHandler::getInstance()->LogToFile(strs.str(), 0);
		return;
	}
#else
	LbaNet::MapsSeq::const_iterator itm = _worldinfo.Maps.find(newpos.MapName);
	if(itm != _worldinfo.Maps.end())
	{
		std::string luafile = "Worlds/" + _worldinfo.Description.WorldName + "/Lua/";

		// custom server file
		std::string customluafile = luafile+"CustomServer.lua";

		luafile += newpos.MapName + "_server.lua";

		// create map object
		boost::shared_ptr<MapHandler> mapH(new MapHandler(_worldinfo.Description.WorldName, itm->second, luafile, customluafile));
		_currentmaps[itm->first] = mapH;

		//start run thread if not started already
		mapH->StartThread();

		// add proxies to the map
		mapH->ExtAddPlayer(playerid, pinfo);
	}
#endif

}

/***********************************************************
teleport the player
***********************************************************/
void SharedDataHandler::TeleportPlayer(long playerid, boost::shared_ptr<PlayerHandler> pinfo, 
										const LbaNet::PlayerPosition &newpos)
{
	Lock sync(*this);
	TeleportPlayerInternal(playerid, pinfo, newpos);
}




/***********************************************************
clean up
***********************************************************/
void SharedDataHandler::CleanUp()
{
	Lock sync(*this);

	_currentmaps.clear();
	_currentplayermaps.clear();

	_dbH = boost::shared_ptr<DatabaseHandlerBase>();
}






/***********************************************************
returning the spawning info for a map
***********************************************************/
PlayerPosition SharedDataHandler::GetSpawningInfo(const std::string &MapName, 
													long SpawningId,
													bool &forcerotation)
{
	// internal - no lock

	PlayerPosition res;
	res.MapName = MapName;
	res.Rotation = 0;
	forcerotation = false;

	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator itmap = _currentmaps.find(MapName);
	if(itmap != _currentmaps.end())
	{
		boost::shared_ptr<Spawn> spn = itmap->second->GetSpawn(SpawningId);
		if(spn)
		{
			res.X = spn->GetPosX();
			res.Y = spn->GetPosY();
			res.Z = spn->GetPosZ();
			res.Rotation = spn->GetRotation();

			forcerotation = spn->GetForceRotation();
		}
	}

	return res;
}










/***********************************************************
called by editor
***********************************************************/
#ifdef _USE_QT_EDITOR_
void SharedDataHandler::EditorUpdate(const std::string &mapname, 
										LbaNet::EditorUpdateBasePtr update)
{
	LbaNet::EditorUpdateBase & obj = *update;
	const std::type_info& info = typeid(obj);
	bool publish = true;


	// map add
	if(info == typeid(UpdateEditor_AddOrModMap))
	{
		publish = false;
		UpdateEditor_AddOrModMap* castedptr = 
			dynamic_cast<UpdateEditor_AddOrModMap *>(&obj);

		LbaNet::MapsSeq::iterator it = _worldinfo.Maps.find(castedptr->_mapinfo.Name);
		if(it != _worldinfo.Maps.end())
		{
			// map already exist - update it
			_worldinfo.Maps[castedptr->_mapinfo.Name] = castedptr->_mapinfo;
			AddEvent(castedptr->_mapinfo.Name, 1, new EditorEvent(update));
		}
		else
		{
			//new map - add it
			_worldinfo.Maps[castedptr->_mapinfo.Name] = castedptr->_mapinfo;

			// create map object
			std::string luafile = "Worlds/" + _worldinfo.Description.WorldName + "/Lua/";
			
			// custom server file
			std::string customluafile = luafile+"CustomServer.lua";
			luafile += castedptr->_mapinfo.Name + "_server.lua";
			boost::shared_ptr<MapHandler> mapH(new MapHandler(_worldinfo.Description.WorldName, castedptr->_mapinfo, luafile, customluafile));
			_currentmaps[castedptr->_mapinfo.Name] = mapH;

			//start thread
			mapH->StartThread();
		}
	}


	// map remove
	if(info == typeid(UpdateEditor_RemoveMap))
	{
		publish = false;
		UpdateEditor_RemoveMap* castedptr = 
			dynamic_cast<UpdateEditor_RemoveMap *>(&obj);

		LbaNet::MapsSeq::iterator it = _worldinfo.Maps.find(castedptr->_MapName);
		if(it != _worldinfo.Maps.end())
		{
			// map exist - delete it
			_worldinfo.Maps.erase(it);

			//delete map object
			std::map<std::string, boost::shared_ptr<MapHandler> >::iterator itm = 
													_currentmaps.find(castedptr->_MapName);
			if(itm != _currentmaps.end())
				_currentmaps.erase(itm);

		}
	}
	
	// player tp
	if(info == typeid(EditorTeleportPlayerEvent))
	{
		if(mapname == "")
		{
			publish = false;

			EditorTeleportPlayerEvent* castedptr = 
				dynamic_cast<EditorTeleportPlayerEvent *>(&obj);

			TeleportPlayerInternal(castedptr->_playerid, m_mainplayerH, castedptr->_newpos);
		}
	}	


	// inform the map
	if(publish)
		AddEvent(mapname, 1, new EditorEvent(update));
}
#endif



/***********************************************************
send tp list to player
***********************************************************/
LbaNet::TeleportsSeq SharedDataHandler::GetTpList(ScriptEnvironmentBase * owner, Ice::Long clientid) const
{
	Lock sync(*this);

	LbaNet::TeleportsSeq Tps;
	std::map<long, boost::shared_ptr<TeleportDef> >::const_iterator ittp = m_teleports.begin();
	std::map<long, boost::shared_ptr<TeleportDef> >::const_iterator endtp = m_teleports.end();
	for(; ittp != endtp; ++ittp)
	{
		if(ittp->second->ValidForPlayer(owner, (long)clientid))
			Tps[ittp->first] = ittp->second->GetName();
	}

	return Tps;
}


/***********************************************************
add tp
***********************************************************/
void SharedDataHandler::AddTeleport(boost::shared_ptr<TeleportDef> tp)
{
	Lock sync(*this);

	if(tp)
		m_teleports[tp->GetId()] = tp;
}


/***********************************************************
remove tp
***********************************************************/
bool SharedDataHandler::RemoveTeleport(long id)
{
	Lock sync(*this);

	std::map<long, boost::shared_ptr<TeleportDef> >::iterator it = m_teleports.find(id);
	if(it != m_teleports.end())
	{
		m_teleports.erase(it);
		return true;
	}

	return false;
}

/***********************************************************
get tp
***********************************************************/
boost::shared_ptr<TeleportDef> SharedDataHandler::GetTeleport(long id)
{
	Lock sync(*this);

	std::map<long, boost::shared_ptr<TeleportDef> >::iterator it = m_teleports.find(id);
	if(it != m_teleports.end())
		return it->second;


	return boost::shared_ptr<TeleportDef>();
}


/***********************************************************
save to lua
***********************************************************/
void SharedDataHandler::SaveToLua()
{
	std::string luafile = "Data/Worlds/" + _worldinfo.Description.WorldName + "/Lua/";
	luafile += "general.lua";

	std::ofstream file(luafile.c_str());
	file<<"function Init(environment)"<<std::endl;

	// save tps
	std::map<long, boost::shared_ptr<TeleportDef> >::iterator ita = m_teleports.begin();
	std::map<long, boost::shared_ptr<TeleportDef> >::iterator enda = m_teleports.end();
	for(;ita != enda; ++ita)
		ita->second->SaveToLuaFile(file);


	// save quests
	std::map<long, QuestPtr> questmap = QuestHandler::getInstance()->GetQuests();
	std::map<long, QuestPtr>::iterator itq = questmap.begin();
	std::map<long, QuestPtr>::iterator endq = questmap.end();
	for(;itq != endq; ++itq)
		itq->second->SaveToLuaFile(file);


	// save items
	const std::map<long, InventoryItemDefPtr> &items = InventoryItemHandler::getInstance()->GetItemMap();
	std::map<long, InventoryItemDefPtr>::const_iterator ititm = items.begin();
	std::map<long, InventoryItemDefPtr>::const_iterator enditm = items.end();
	for(;ititm != enditm; ++ititm)
		ititm->second->SaveToLuaFile(file);

	file<<"end"<<std::endl;
}




/***********************************************************
add quest
***********************************************************/
void SharedDataHandler::AddQuest(QuestPtr quest)
{
	QuestHandler::getInstance()->AddQuest(quest);
}


/***********************************************************
remove quest
***********************************************************/
void SharedDataHandler::RemoveQuest(long id)
{
	QuestHandler::getInstance()->RemoveQuest(id);
}



/***********************************************************
get quest
***********************************************************/
QuestPtr SharedDataHandler::GetQuest(long id)
{
	return QuestHandler::getInstance()->GetQuest(id);
}



/***********************************************************
add item
***********************************************************/
void SharedDataHandler::AddInventoryItem(boost::shared_ptr<InventoryItemDef> item)
{
	InventoryItemHandler::getInstance()->AddItem(item);
}


/***********************************************************
get spawn
***********************************************************/
boost::shared_ptr<Spawn> SharedDataHandler::GetSpawn(const std::string & mapname, long spawnid)
{
	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator itmap = _currentmaps.find(mapname);
	if(itmap != _currentmaps.end())
		return itmap->second->GetSpawn(spawnid);

	return boost::shared_ptr<Spawn>();
}



/***********************************************************
get spawn
***********************************************************/
long SharedDataHandler::GetSpawnId(const std::string & mapname, const std::string & name)
{
	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator itmap = _currentmaps.find(mapname);
	if(itmap != _currentmaps.end())
		return itmap->second->GetSpawnId(name);

	return -1;
}


/***********************************************************
get spawns
***********************************************************/
std::map<long, boost::shared_ptr<Spawn> > SharedDataHandler::GetSpawns(const std::string & mapname)
{
	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator itmap = _currentmaps.find(mapname);
	if(itmap != _currentmaps.end())
		return itmap->second->GetSpawns();

	return std::map<long, boost::shared_ptr<Spawn> >();
}



/***********************************************************
update client extra info
***********************************************************/
void SharedDataHandler::UpdateClientExtraInfo(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo)
{
	EventsSeq seq;
	seq.push_back(new UpdateExtraInfoEvent(extrainfo));
	ClientEvents(clientid, seq);
}