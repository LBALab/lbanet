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
		boost::shared_ptr<MapHandler> mapH(new MapHandler(itm->second, luafile, customluafile));
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
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _currentplayers.find(clientid);
	if(it != _currentplayers.end())
	{
		AddEvents(it->second->GetCurrentMap(), clientid, evts);
	}
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



	// create player object
	boost::shared_ptr<PlayerHandler> player(new PlayerHandler((long)clientid, proxy, 
											_dbH, _worldinfo.Description.WorldName, savedinfo, extrainfo));
	_currentplayers[clientid] = player;


	// take care of map part
	ChangeMapPlayer(clientid, savedinfo.ppos);


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
			LbaNet::QuestInfo qinf;
			qinf.Id = questStarted[i];
			qinf.ChapterTextId = q->GetChapter();
			qinf.QuestAreaTextId = q->GetLocationTextId();	
			qinf.TittleTextId = q->GetTitleTextId();
			qinf.DescriptionTextId = q->GetDescriptionTextId();
			qinf.Visible = q->GetVisible();
			startedQ[qinf.Id] = qinf;
		}
		for(size_t i=0; i< questFinished.size(); ++i)
		{
			QuestPtr q = QuestHandler::getInstance()->GetQuest(questFinished[i]);
			LbaNet::QuestInfo qinf;
			qinf.Id = questFinished[i];
			qinf.ChapterTextId = q->GetChapter();
			qinf.QuestAreaTextId = q->GetLocationTextId();	
			qinf.TittleTextId = q->GetTitleTextId();
			qinf.DescriptionTextId = q->GetDescriptionTextId();
			qinf.Visible = q->GetVisible();
			endedQ[qinf.Id] = qinf;
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

			IceUtil::ThreadPtr t = new EventsSender(toplayer, proxy);
			t->start();	
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
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _currentplayers.find(clientid);
	if(it != _currentplayers.end())
	{
		// make player leave map
		PlayerLeaveMap(it->second->GetCurrentMap(), clientid);

		// save db and remove player
		it->second->SaveCurrentInfo();
		_currentplayers.erase(it);
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
player leave map
***********************************************************/
void SharedDataHandler::PlayerLeaveMap(const std::string &MapName, Ice::Long clientid)
{
	// internal - no lock

	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator it = _currentmaps.find(MapName);
	if(it != _currentmaps.end())
		it->second->RemovePlayer(clientid);

	// add player leave event
	AddEvent(MapName, clientid, 
		new PlayerLeaveEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), clientid));
}



/***********************************************************
clean up
***********************************************************/
void SharedDataHandler::CleanUp()
{
	Lock sync(*this);

	_currentmaps.clear();
	_currentplayers.clear();

	_dbH = boost::shared_ptr<DatabaseHandlerBase>();
}






/***********************************************************
get player proxy
***********************************************************/
ClientProxyBasePtr SharedDataHandler::GetProxy(Ice::Long clientid)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _currentplayers.find(clientid);
	if(it != _currentplayers.end())
		return it->second->GetProxy();


	return NULL;
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
used when a client update name info
***********************************************************/
void SharedDataHandler::UpdateClientExtraInfo(Ice::Long clientid, 
											  const LbaNet::ObjectExtraInfo& extrainfo)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _currentplayers.find(clientid);
	if(it != _currentplayers.end())
	{
		it->second->SetExtraInfo(extrainfo);

		// add event
		AddEvent(it->second->GetCurrentMap(), clientid, 
			new NewClientExtraInfoEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), extrainfo));
	}
}


/***********************************************************
teleport player
***********************************************************/
void SharedDataHandler::TeleportPlayer(ScriptEnvironmentBase * owner, Ice::Long clientid, long TeleportId)
{
	bool ok = false;
	std::string mapname;
	long spawnid = 0;

	{
		Lock sync(*this);
		//TODO - check if teleport is legal

		// get tp info
		std::map<long, boost::shared_ptr<TeleportDef> >::iterator ittp = m_teleports.find(TeleportId);
		std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
	
		if(ittp != m_teleports.end())
		{
			//! get player current map
			if(itplayer != _currentplayers.end())
			{
				//check if player allowed to tp
				if(ittp->second->ValidForPlayer(owner, (long)clientid))
				{
					//only tp if change map
					if(ittp->second->GetMapName() != itplayer->second->GetCurrentMap())
					{
						ok = true;
						mapname = ittp->second->GetMapName();
						spawnid = (long)ittp->second->GetSpawn();
					}
				}
			}
		}
	}

	// cant lock this part...
	if(ok)
		ChangeMapPlayer(clientid, mapname, spawnid);
}


/***********************************************************
update player shortcut
***********************************************************/
void SharedDataHandler::UpdatePlayerShortcut(Ice::Long clientid, int Position, long ItemId)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
	if(itplayer != _currentplayers.end())
		itplayer->second->UpdateShortcut(Position, ItemId);
}



/***********************************************************
change map for player
***********************************************************/
void SharedDataHandler::ChangeMapPlayer(Ice::Long clientid, const std::string &NewMapName, long SpawningId,
											float offsetX, float offsetY, float offsetZ)
{
	Lock sync(*this);

	// get map spawning info
	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator itmap = _currentmaps.find(NewMapName);
	if(itmap != _currentmaps.end())
	{
		boost::shared_ptr<Spawn> spn = itmap->second->GetSpawn(SpawningId);
		if(spn)
		{
			//! get player current position
			std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
			if(itplayer != _currentplayers.end())
			{
				LbaNet::PlayerPosition ppos = itplayer->second->GetPlayerPosition();
				ppos.MapName = NewMapName;
				ppos.X = spn->GetPosX() + offsetX;
				ppos.Y = spn->GetPosY() + offsetY;
				ppos.Z = spn->GetPosZ() + offsetZ;

				if(spn->GetForceRotation())
					ppos.Rotation = spn->GetRotation();

				ChangeMapPlayer(clientid, ppos);
			}
		}
	}
}


/***********************************************************
change map for player
***********************************************************/
void SharedDataHandler::ChangeMapPlayer(Ice::Long clientid, const std::string &NewMapName, 
										const std::string SpawnName,
										float offsetX, float offsetY, float offsetZ)
{
	Lock sync(*this);

	// get map spawning info
	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator itmap = _currentmaps.find(NewMapName);
	if(itmap != _currentmaps.end())
	{
		boost::shared_ptr<Spawn> spn = itmap->second->GetSpawn(SpawnName);
		if(spn)
		{
			//! get player current position
			std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
			if(itplayer != _currentplayers.end())
			{
				LbaNet::PlayerPosition ppos = itplayer->second->GetPlayerPosition();
				ppos.MapName = NewMapName;
				ppos.X = spn->GetPosX() + offsetX;
				ppos.Y = spn->GetPosY() + offsetY;
				ppos.Z = spn->GetPosZ() + offsetZ;

				if(spn->GetForceRotation())
					ppos.Rotation = spn->GetRotation();

				ChangeMapPlayer(clientid, ppos);
			}
		}
	}
}



/***********************************************************
internally change map for player
***********************************************************/
void SharedDataHandler::ChangeMapPlayer(Ice::Long clientid, LbaNet::PlayerPosition &newpos)
{
	// internal - no lock

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
	if(itplayer == _currentplayers.end())
		return;

	// first exit current map
	PlayerLeaveMap(itplayer->second->GetCurrentMap(), clientid);


	// then update player info
	itplayer->second->Teleport(newpos);


	//then connect to new map

#ifndef _USE_QT_EDITOR_
	//check if map handler for the map is already present
	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator it = _currentmaps.find(newpos.MapName);
	if(it != _currentmaps.end())
	{
		//start run thread if not started already
		it->second->StartThread();

		// add proxies to the map
		it->second->AddPlayer(clientid, itplayer->second);
	}
	else
	{
		// log the issue, we have no map of this name
		std::stringstream strs;
		strs<<"Player trying to go to a non existing map - player id: "<<clientid;
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
		boost::shared_ptr<MapHandler> mapH(new MapHandler(itm->second, luafile, customluafile));
		_currentmaps[itm->first] = mapH;

		//start run thread if not started already
		mapH->StartThread();

		// add proxies to the map
		mapH->AddPlayer(clientid, itplayer->second);
	}
#endif


	// add player enter event
	AddEvent(newpos.MapName, clientid, 
				new PlayerEnterEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), clientid));
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
			boost::shared_ptr<MapHandler> mapH(new MapHandler(castedptr->_mapinfo, luafile, customluafile));
			_currentmaps[castedptr->_mapinfo.Name] = mapH;
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

	//EventsSeq toplayer;
	//GuiParamsSeq seq;
	//seq.push_back(new TeleportGuiParameter(Tps));
	//toplayer.push_back(
	//	new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), "TeleportBox", seq, false, false));
}


/***********************************************************
return the client lua filename for a map
***********************************************************/
std::string SharedDataHandler::GetClientLuaFilename(const std::string & mapname)
{
	Lock sync(*this);

	std::string luafile = "Worlds/" + _worldinfo.Description.WorldName + "/Lua/";
	luafile += mapname + "_client.lua";
	return luafile;
}


/***********************************************************
player switch item
***********************************************************/
void SharedDataHandler::PlayerSwitchItem(Ice::Long clientid, long ItemId, int NewPosition)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
	if(itplayer != _currentplayers.end())
		itplayer->second->SwitchItem(ItemId, NewPosition);

}

/***********************************************************
player use item
***********************************************************/
void SharedDataHandler::PlayerItemUsed(Ice::Long clientid, long ItemId)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _currentplayers.find(clientid);
	if(it != _currentplayers.end())
	{
		// add event
		AddEvent(it->second->GetCurrentMap(), clientid, 
			new PlayerItemUsedEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), ItemId));
	}
}

/***********************************************************
Player Create Letter
***********************************************************/
void SharedDataHandler::PlayerCreateLetter(Ice::Long clientid, const std::string & subject,
											const std::string & message)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
	if(itplayer != _currentplayers.end())
		itplayer->second->CreateLetter(subject, message);
}

/***********************************************************
Player Destroy Item
***********************************************************/
void SharedDataHandler::PlayerDestroyItem(Ice::Long clientid, long ItemId)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
	if(itplayer != _currentplayers.end())
		itplayer->second->DestroyItem(ItemId);
}



 
/***********************************************************
get player inventory
***********************************************************/
LbaNet::ItemsMap SharedDataHandler::GetInventory(Ice::Long clientid, int & inventorysize)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
	if(itplayer != _currentplayers.end())
	{
		inventorysize = itplayer->second->GetInventorySize();
		return itplayer->second->GetInventory();
	}

	return LbaNet::ItemsMap();
}


/***********************************************************
update player inventory
***********************************************************/
void SharedDataHandler::UpdateInventory(Ice::Long clientid, LbaNet::ItemList Taken, 
										LbaNet::ItemList Put, LbaNet::ItemClientInformType informtype)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
	if(itplayer != _currentplayers.end())
		itplayer->second->UpdateInventory(Taken, Put, informtype);
}


/***********************************************************
set main player state
***********************************************************/
void SharedDataHandler::SetMainState(LbaNet::ModelState state)
{
	// no need to lock - always called within the same thread
	_currentplayerstate = state;
}

/***********************************************************
return main player state
***********************************************************/
LbaNet::ModelState SharedDataHandler::GetMainState()
{
	// no need to lock - always called within the same thread
	return _currentplayerstate;
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