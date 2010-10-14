#include "SharedDataHandler.h"
#include "PlayerHandler.h"
#include "MapHandler.h"
#include "SynchronizedTimeHandler.h"
#include "LogHandler.h"

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
	Lock sync(*this);
	_worldinfo = worldinfo;

	// create all maps
	LbaNet::MapsSeq::const_iterator itm = worldinfo.Maps.begin();
	LbaNet::MapsSeq::const_iterator endm = worldinfo.Maps.end();
	for(; itm != endm; ++itm)
	{
		std::string luafile = "Worlds/" + _worldinfo.Description.WorldName;
		luafile += "/Lua/" + itm->second.Name + "_server.lua";

		// create map object
		boost::shared_ptr<MapHandler> mapH(new MapHandler(itm->second, luafile));
		_currentmaps[itm->first] = mapH;
	}
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
	RegisterClient(clientid, extrainfo, new RemoteClientProxy(proxy));
}


/***********************************************************
used when a client connect to a world
***********************************************************/
void SharedDataHandler::RegisterClient(Ice::Long clientid, const LbaNet::ObjectExtraInfo& extrainfo, 
											ClientInterfacePtr proxy)
{
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
											_worldinfo.StartingInfo.SpawningId,
											forcerotation);

		savedinfo.lifemana.CurrentLife = _worldinfo.StartingInfo.StartingLife;
		savedinfo.lifemana.MaxLife = _worldinfo.StartingInfo.StartingLife;
		savedinfo.lifemana.CurrentMana = _worldinfo.StartingInfo.StartingMana;
		savedinfo.lifemana.MaxMana = _worldinfo.StartingInfo.StartingMana;
		savedinfo.inventory.InventoryStructure = _worldinfo.StartingInfo.StartingInventory;
		savedinfo.model = _worldinfo.StartingInfo.StartingModel;
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
		// get list from db
		LbaNet::FriendsSeq friends = _dbH->GetFriends((long)clientid);

		// send list to player
		if(proxy)
		{
			EventsSeq toplayer;
			GuiParamsSeq paramseq;
			paramseq.push_back(new FriendListGuiParameter(friends));
			toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"CommunityBox", paramseq, false, false));

			IceUtil::ThreadPtr t = new EventsSender(toplayer, proxy);
			t->start();	
		}
	}

	// send teleport list
	//  TODO - add condition on list
	{
		std::vector<std::string> Tps;
		LbaNet::ServerTeleportsSeq::iterator ittp = _worldinfo.TeleportInfo.begin();
		LbaNet::ServerTeleportsSeq::iterator endtp = _worldinfo.TeleportInfo.end();
		for(; ittp != endtp; ++ittp)
			Tps.push_back(ittp->first);

		EventsSeq toplayer;
		GuiParamsSeq seq;
		seq.push_back(new TeleportGuiParameter(Tps));
		toplayer.push_back(
			new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), "TeleportBox", seq, false, false));

		IceUtil::ThreadPtr t = new EventsSender(toplayer, proxy);
		t->start();	
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
	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator it = _currentmaps.find(MapName);
	if(it != _currentmaps.end())
		it->second->AddEvent(clientid, evt);
}



/***********************************************************
player leave map
***********************************************************/
void SharedDataHandler::PlayerLeaveMap(const std::string &MapName, Ice::Long clientid)
{
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
	PlayerPosition res;
	res.MapName = MapName;
	res.Rotation = 0;
	forcerotation = false;

	MapsSeq::iterator it = _worldinfo.Maps.find(MapName);
	if(it != _worldinfo.Maps.end())
	{
		SpawningsSeq::iterator itsp = it->second.Spawnings.find(SpawningId);
		if(itsp != it->second.Spawnings.end())
		{
			res.X = itsp->second.PosX;
			res.Y = itsp->second.PosY;
			res.Z = itsp->second.PosZ;
			res.Rotation = itsp->second.Rotation;

			forcerotation = itsp->second.ForceRotation;
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
void SharedDataHandler::TeleportPlayer(Ice::Long clientid, const std::string &TeleportId)
{
	{
		Lock sync(*this);
		//TODO - check if teleport is legal
	}

	// get tp info
	LbaNet::ServerTeleportsSeq::iterator ittp = _worldinfo.TeleportInfo.find(TeleportId);
	if(ittp != _worldinfo.TeleportInfo.end())
	{
		//! get player current map
		std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
		if(itplayer != _currentplayers.end())
		{
			//only tp if change map
			if(ittp->second.MapName != itplayer->second->GetCurrentMap())
				ChangeMapPlayer(clientid, ittp->second.MapName, ittp->second.SpawningId);
		}
	}
}


/***********************************************************
change map for player
***********************************************************/
void SharedDataHandler::ChangeMapPlayer(Ice::Long clientid, const std::string &NewMapName, 
											long SpawningId)
{
	Lock sync(*this);

	// get map spawning info
	LbaNet::MapsSeq::iterator itm = _worldinfo.Maps.find(NewMapName);
	if(itm != _worldinfo.Maps.end())
	{
		LbaNet::SpawningsSeq::iterator itsp = itm->second.Spawnings.find(SpawningId);
		if(itsp != itm->second.Spawnings.end())
		{
			//! get player current position
			std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
			if(itplayer != _currentplayers.end())
			{
				LbaNet::PlayerPosition ppos = itplayer->second->GetPlayerPosition();
				ppos.MapName = NewMapName;
				ppos.X = itsp->second.PosX;
				ppos.Y = itsp->second.PosY;
				ppos.Z = itsp->second.PosZ;

				if(itsp->second.ForceRotation)
					ppos.Rotation = itsp->second.Rotation;

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
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _currentplayers.find(clientid);
	if(itplayer == _currentplayers.end())
		return;

	// first exit current map
	PlayerLeaveMap(itplayer->second->GetCurrentMap(), clientid);


	// then update player info
	itplayer->second->Teleport(newpos);


	//then connect to new map

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


	// add player enter event
	AddEvent(newpos.MapName, clientid, 
				new PlayerEnterEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), clientid));
}


/***********************************************************
called by editor
***********************************************************/
#ifdef _USE_QT_EDITOR_
void SharedDataHandler::EditorUpdate(const std::string &mapname, 
									 boost::shared_ptr<EditorUpdateBase> update)
{
	EditorUpdateBase & obj = *update;
	const std::type_info& info = typeid(obj);

	// spawning update
	if(info == typeid(UpdateEditor_AddOrModSpawning))
	{
		UpdateEditor_AddOrModSpawning* castedptr = 
			static_cast<UpdateEditor_AddOrModSpawning *>(&obj);

		LbaNet::SpawningInfo spawn;
		spawn.Id = castedptr->_SpawningId;
		spawn.Name = castedptr->_spawningname;
		spawn.PosX = castedptr->_PosX;
		spawn.PosY = castedptr->_PosY;
		spawn.PosZ = castedptr->_PosZ;
		spawn.Rotation = castedptr->_Rotation;
		spawn.ForceRotation = castedptr->_forcedrotation;
		_worldinfo.Maps[mapname].Spawnings[spawn.Id] = spawn;
	}

	// spawning remove
	if(info == typeid(UpdateEditor_RemoveSpawning))
	{
		UpdateEditor_RemoveSpawning* castedptr = 
			static_cast<UpdateEditor_RemoveSpawning *>(&obj);

		LbaNet::SpawningsSeq::iterator it = _worldinfo.Maps[mapname].Spawnings.find(castedptr->_SpawningId);
		if(it != _worldinfo.Maps[mapname].Spawnings.end())
		{
			// erase from data
			_worldinfo.Maps[mapname].Spawnings.erase(it);
		}
	}
	

	// inform the map
	AddEvent(mapname, 1, new EditorEvent(update));
}
#endif