#include "SharedDataHandler.h"
#include "PlayerHandler.h"
#include "MapHandler.h"
#include "SynchronizedTimeHandler.h"

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
void SharedDataHandler::RegisterClient(Ice::Long clientid, const std::string &clientname, 
											const ClientInterfacePrx &proxy)
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
											_worldinfo.StartingInfo.Spawning,
											forcerotation);

		savedinfo.lifemana.CurrentLife = _worldinfo.StartingInfo.StartingLife;
		savedinfo.lifemana.MaxLife = _worldinfo.StartingInfo.StartingLife;
		savedinfo.lifemana.CurrentMana = _worldinfo.StartingInfo.StartingMana;
		savedinfo.lifemana.MaxMana = _worldinfo.StartingInfo.StartingMana;
		savedinfo.inventory.InventoryStructure = _worldinfo.StartingInfo.StartingInventory;
		savedinfo.model = _worldinfo.StartingInfo.StartingModel;
	}


	// create player object
	boost::shared_ptr<PlayerHandler> player(new PlayerHandler((long)clientid, clientname, proxy, 
											_dbH, _worldinfo.Description.WorldName, savedinfo, 
											savedinfo.model));
	_currentplayers[clientid] = player;


	// take care of map part
	std::string newmapname = savedinfo.ppos.MapName;


	//check if map handler for the map is already present
	std::map<std::string, boost::shared_ptr<MapHandler> >::iterator it = _currentmaps.find(newmapname);
	if(it == _currentmaps.end())
	{
		//if it is the case then launch a map handler
		boost::shared_ptr<MapHandler> mapH(new MapHandler(_worldinfo.Maps[newmapname]));
		mapH->StartThread();
		_currentmaps[newmapname] = mapH;
	}
	else
	{
		//start run thread if not started already
		it->second->StartThread();
	}


	// add proxies to the map
	_currentmaps[newmapname]->AddProxy(clientid, proxy);


	// add player enter event
	AddEvent(newmapname, clientid, 
		new PlayerEnterEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), clientid));
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
returning the spawning info for a map
***********************************************************/
PlayerPosition SharedDataHandler::GetSpawningInfo(const std::string &MapName, 
													const std::string &SpawningName,
													bool &forcerotation)
{
	PlayerPosition res;
	res.MapName = MapName;
	res.Rotation = 0;
	forcerotation = false;

	MapsSeq::iterator it = _worldinfo.Maps.find(MapName);
	if(it != _worldinfo.Maps.end())
	{
		SpawningsSeq::iterator itsp = it->second.Spawnings.find(SpawningName);
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
add events
***********************************************************/
void SharedDataHandler::AddEvents(const std::string &MapName, Ice::Long clientid, const EventsSeq &evts)
{
	_currentmaps[MapName]->AddEvents(clientid, evts);
}


/***********************************************************
add 1 event
***********************************************************/
void SharedDataHandler::AddEvent(const std::string &MapName,Ice::Long clientid, 
									ClientServerEventBasePtr evt)
{
	_currentmaps[MapName]->AddEvent(clientid, evt);
}



/***********************************************************
player leave map
***********************************************************/
void SharedDataHandler::PlayerLeaveMap(const std::string &MapName, Ice::Long clientid)
{
	_currentmaps[MapName]->RemoveProxy(clientid);

	// add player enter event
	AddEvent(MapName, clientid, 
		new PlayerLeaveEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), clientid));
}



/***********************************************************
clean up
***********************************************************/
void SharedDataHandler::CleanUp()
{
	_currentmaps.clear();
	_currentplayers.clear();

	_dbH = boost::shared_ptr<DatabaseHandlerBase>();
}




/***********************************************************
return inventory size
***********************************************************/
int SharedDataHandler::GetInventorySize(Ice::Long clientid)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _currentplayers.find(clientid);
	if(it != _currentplayers.end())
		return it->second->GetInventorySize();
	else
		return 1;
}

/***********************************************************
return inventory content
***********************************************************/
ItemsMap SharedDataHandler::GetInventory(Ice::Long clientid)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _currentplayers.find(clientid);
	if(it != _currentplayers.end())
		return it->second->GetInventory();
	else
		return ItemsMap();
}



/***********************************************************
return shortcuts
***********************************************************/
ShortcutsSeq SharedDataHandler::GetShorcuts(Ice::Long clientid)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _currentplayers.find(clientid);
	if(it != _currentplayers.end())
		return it->second->GetShorcuts();
	else
		return ShortcutsSeq();
}


/***********************************************************
get player info
***********************************************************/
SavedWorldInfo SharedDataHandler::GetInfo(Ice::Long clientid)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _currentplayers.find(clientid);
	if(it != _currentplayers.end())
		return it->second->GetInfo();
	else
		return SavedWorldInfo();
}



/***********************************************************
update player position
***********************************************************/
void SharedDataHandler::UpdatePlayerPosition(Ice::Long clientid, const PlayerPosition & pos)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _currentplayers.find(clientid);
	if(it != _currentplayers.end())
		it->second->UpdatePositionInWorld(pos);
}

/***********************************************************
get player position
***********************************************************/
PlayerPosition SharedDataHandler::GetPlayerPosition(Ice::Long clientid)
{
	Lock sync(*this);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _currentplayers.find(clientid);
	if(it != _currentplayers.end())
		return it->second->GetPlayerPosition();


	return PlayerPosition();
}
