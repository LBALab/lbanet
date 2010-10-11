#include "MapHandler.h"
#include "SynchronizedTimeHandler.h"
#include "SharedDataHandler.h"
#include "TextBoxHandler.h"
#include "ContainerBoxHandler.h"
#include "DialogBoxHandler.h"
#include "ShopBoxHandler.h"
#include "ShortcutBoxHandler.h"
#include "CommunityBoxHandler.h"
#include "InventoryBoxHandler.h"
#include "MailBoxHandler.h"

#define _THREAD_WAIT_TIME_	17

/***********************************************************
constructor
***********************************************************/
EventsSender::EventsSender(EventsSeq & events, ClientProxyBasePtr proxy)
: _proxy(proxy)
{
	_events.swap(events);
}

/***********************************************************
running function of the thread
***********************************************************/
void EventsSender::run()
{
	try
	{
		if(_proxy)
			_proxy->ServerEvents(_events);
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception in EventSender: "<<ex.what()<<std::endl;
	}
	catch(...)
	{
		std::cout<<"Unknown exception in EventSender. "<<std::endl;
	}
}




/***********************************************************
constructor
***********************************************************/
EventsSenderToAll::EventsSenderToAll(EventsSeq & events, std::map<Ice::Long, ClientProxyBasePtr> &proxies)
{
	_events.swap(events);
	_proxies.swap(proxies);
}


/***********************************************************
running function of the thread
***********************************************************/
void EventsSenderToAll::run()
{
	std::map<Ice::Long, ClientProxyBasePtr>::iterator it = _proxies.begin();
	std::map<Ice::Long, ClientProxyBasePtr>::iterator end = _proxies.end();
	for(; it != end; ++it)
	{
		try
		{
			if(it->second)
				it->second->ServerEvents(_events);
		}
		catch(const IceUtil::Exception& ex)
		{
			std::cout<<"Exception in EventsSenderToAll: "<<ex.what()<<std::endl;
		}
		catch(...)
		{
			std::cout<<"Unknown exception in EventsSenderToAll. "<<std::endl;
		}
	}

}





/***********************************************************
constructor
***********************************************************/
MapHandler::MapHandler(const MapInfo & mapinfo)
: _Trunning(false), _mapinfo(mapinfo)
{

	// initialize the gui handlers
	_guihandlers["CommunityBox"] = boost::shared_ptr<ServerGUIBase>(new CommunityBoxHandler());
	_guihandlers["ShortcutBox"] = boost::shared_ptr<ServerGUIBase>(new ShortcutBoxHandler());
	_guihandlers["MailBox"] = boost::shared_ptr<ServerGUIBase>(new MailBoxHandler());

	_guihandlers["TextBox"] = boost::shared_ptr<ServerGUIBase>(new TextBoxHandler());
	_guihandlers["ContainerBox"] = boost::shared_ptr<ServerGUIBase>(new ContainerBoxHandler());
	_guihandlers["DialogBox"] = boost::shared_ptr<ServerGUIBase>(new DialogBoxHandler());
	_guihandlers["ShopBox"] = boost::shared_ptr<ServerGUIBase>(new ShopBoxHandler());
	_guihandlers["InventoryBox"] = boost::shared_ptr<ServerGUIBase>(new InventoryBoxHandler());


}

/***********************************************************
destructor
***********************************************************/
MapHandler::~MapHandler(void)
{
	{
		IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
		_Trunning = false;
		_monitor.notifyAll();
	}

	if(_thread)
	{
		_threadcontrol.join();
		_thread = NULL;
	}
}


/***********************************************************
start run function
***********************************************************/
void MapHandler::StartThread()
{
	// do nothing if already running
	{
		IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
		if(_Trunning)
			return;
	}

	// clean old thread if needed
	if(_thread)
	{
		_threadcontrol.join();
		_thread = NULL;
	}


	// create thread
	_thread = new RunThread(this);
	_threadcontrol = _thread->start();
}



/***********************************************************
running function of the thread
***********************************************************/
void MapHandler::run()
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	_Trunning = true;

	// init time
	long waittime = SynchronizedTimeHandler::GetCurrentTimeInt();
	long tdiff = 17;

	// stop thread if running is false
	while(_Trunning)
	{
		// prepare events to send to everybody
		_tosendevts.clear();

		// process events
		std::map<Ice::Long, EventsSeq> evts;
		GetEvents(evts);
		ProcessEvents(evts, _tosendevts);


		// send events to all proxies
		if(_tosendevts.size() > 0)
		{
			IceUtil::ThreadPtr t = new EventsSenderToAll(_tosendevts, GetProxies());
			t->start();	
		}


		// wait for a few milliseconds
		{
			long currwtime = SynchronizedTimeHandler::GetCurrentTimeInt();
			tdiff = (currwtime-waittime);

			if(tdiff < _THREAD_WAIT_TIME_)
			{
				IceUtil::Time t = IceUtil::Time::milliSeconds(_THREAD_WAIT_TIME_-tdiff);
				_monitor.timedWait(t);
			}

			// mesure the time used to do one cycle
			waittime = SynchronizedTimeHandler::GetCurrentTimeInt();
		}

		//todo stop thread after a while if no player inside
	}
}



/***********************************************************
process events
***********************************************************/
void MapHandler::ProcessEvents(const std::map<Ice::Long, EventsSeq> & evts, 
									EventsSeq &tosendevts)
{
	std::map<Ice::Long, EventsSeq>::const_iterator it = evts.begin();
	std::map<Ice::Long, EventsSeq>::const_iterator end = evts.end();
	for(;it != end; ++it)
	{
		LbaNet::EventsSeq::const_iterator itevt = it->second.begin();
		LbaNet::EventsSeq::const_iterator endevt = it->second.end();
		for(;itevt != endevt; ++itevt)
		{
			LbaNet::ClientServerEventBasePtr ptr = *itevt;
			LbaNet::ClientServerEventBase & obj = *ptr;
			const std::type_info& info = typeid(obj);

			// client entered
			if(info == typeid(LbaNet::PlayerEnterEvent))
			{
				PlayerEntered(it->first, tosendevts);
				continue;
			}

			// client left
			if(info == typeid(LbaNet::PlayerLeaveEvent))
			{
				PlayerLeft(it->first, tosendevts);
				continue;
			}

			// player updated position
			if(info == typeid(LbaNet::PlayerMovedEvent))
			{
				LbaNet::PlayerMovedEvent* castedptr = 
					dynamic_cast<LbaNet::PlayerMovedEvent *>(&obj);

				PlayerMoved(it->first, castedptr->Time, castedptr->info, tosendevts);
				continue;
			}


			// UpdateGameGUIEvent
			if(info == typeid(LbaNet::UpdateGameGUIEvent))
			{
				LbaNet::UpdateGameGUIEvent* castedptr = 
					dynamic_cast<LbaNet::UpdateGameGUIEvent *>(&obj);
	
				GuiUpdate(it->first, castedptr->GUIId, castedptr->Updates);
				continue;
			}

			// TeleportEvent
			if(info == typeid(LbaNet::TeleportEvent))
			{
				LbaNet::TeleportEvent* castedptr = 
					dynamic_cast<LbaNet::TeleportEvent *>(&obj);

				SharedDataHandler::getInstance()->TeleportPlayer(it->first, castedptr->TeleportId);

				continue;
			}

			// ChangeStanceEvent
			if(info == typeid(LbaNet::ChangeStanceEvent))
			{
				LbaNet::ChangeStanceEvent* castedptr = 
					dynamic_cast<LbaNet::ChangeStanceEvent *>(&obj);
				
				ChangeStance(it->first, castedptr->NewStance, tosendevts);
				continue;
			}


			// PressedActionKeyEvent
			if(info == typeid(LbaNet::PressedActionKeyEvent))
			{
				LbaNet::PressedActionKeyEvent* castedptr = 
					dynamic_cast<LbaNet::PressedActionKeyEvent *>(&obj);
				
				//TODO
					//bool			ForcedNormalAction;
				continue;
			}

	
			// PressedWeaponKeyEvent
			if(info == typeid(LbaNet::PressedWeaponKeyEvent))
			{
				//TODO
				continue;
			}


			// RefreshObjectRequestEvent
			if(info == typeid(LbaNet::RefreshObjectRequestEvent))
			{
				RefreshPlayerObjects(it->first);
				continue;
			}


			// UpdateStateEvent
			if(info == typeid(LbaNet::UpdateStateEvent))
			{
				LbaNet::UpdateStateEvent* castedptr = 
					dynamic_cast<LbaNet::UpdateStateEvent *>(&obj);

				ChangePlayerState(it->first, castedptr->NewState, castedptr->FallingSize, tosendevts);
				continue;
			}

			// RaiseFromDeadEvent
			if(info == typeid(LbaNet::RaiseFromDeadEvent))
			{
				RaiseFromDeadEvent(it->first, tosendevts);
				continue;
			}

			//NewClientExtraInfoEvent
			if(info == typeid(LbaNet::NewClientExtraInfoEvent))
			{
				LbaNet::NewClientExtraInfoEvent* castedptr = 
					dynamic_cast<LbaNet::NewClientExtraInfoEvent *>(&obj);

				tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
									PlayerObject, it->first, new ObjectExtraInfoUpdate(castedptr->ExtraInfo)));
				continue;
			}
		}
	}
}




/***********************************************************
add events
***********************************************************/
void MapHandler::AddEvents(Ice::Long clientid, const EventsSeq &evts)
{
	IceUtil::Mutex::Lock sync(_mutex_events);
	EventsSeq &evtseq = _events[clientid];
	for(size_t i=0; i<evts.size(); ++i)
		evtseq.push_back(evts[i]);
}

/***********************************************************
add 1 event
***********************************************************/
void MapHandler::AddEvent(Ice::Long clientid, ClientServerEventBasePtr evt)
{
	IceUtil::Mutex::Lock sync(_mutex_events);
	_events[clientid].push_back(evt);
}

/***********************************************************
get all events for a specific map
***********************************************************/
void MapHandler::GetEvents(std::map<Ice::Long, EventsSeq> & evts)
{
	IceUtil::Mutex::Lock sync(_mutex_events);
	_events.swap(evts);
}

/***********************************************************
add player proxy
***********************************************************/
void MapHandler::AddProxy(Ice::Long clientid, ClientProxyBasePtr proxy)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);
	_playerproxies[clientid] = proxy;

}

/***********************************************************
remove player proxy
***********************************************************/
void MapHandler::RemoveProxy(Ice::Long clientid)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, ClientProxyBasePtr>::iterator it =	_playerproxies.find(clientid);	
	if(it != _playerproxies.end())
		_playerproxies.erase(it);
}

/***********************************************************
get player proxy
***********************************************************/
ClientProxyBasePtr MapHandler::GetProxy(Ice::Long clientid)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, ClientProxyBasePtr>::iterator it =	_playerproxies.find(clientid);	
	if(it != _playerproxies.end())
		return it->second;

	return NULL;
}

/***********************************************************
get players proxies
***********************************************************/
std::map<Ice::Long, ClientProxyBasePtr> MapHandler::GetProxies()
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);
	return _playerproxies;
}


/***********************************************************
player entered map
***********************************************************/
void MapHandler::PlayerEntered(Ice::Long id, EventsSeq &tosendevts)
{
	// add player to list
	_currentplayers.push_back(id);


	// first give info to the player about current map state
	EventsSeq toplayer;


	// inform client he enter a new map
	toplayer.push_back(new NewMapEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
												_mapinfo.Name, "", _mapinfo.AutoCameraType)); //TODO put script here
	

	// player inventory
	{
	GuiParamsSeq seq;
	seq.push_back(new InventoryGuiParameter(SharedDataHandler::getInstance()->GetInventorySize(id), 
								SharedDataHandler::getInstance()->GetInventory(id)));
	toplayer.push_back(
		new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), "InventoryBox", seq, false, false));
	}

	// player shortcut
	{
	GuiParamsSeq seq;
	seq.push_back(new ShortcutGuiParameter(SharedDataHandler::getInstance()->GetShorcuts(id)));
	toplayer.push_back(
		new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", seq, false, false));
	}



	IceUtil::ThreadPtr t = new EventsSender(toplayer, GetProxy(id));
	t->start();	



	// then inform all players that player entered
	//TODO - change size
	{
		SavedWorldInfo pinfo = SharedDataHandler::getInstance()->GetInfo(id);

		ObjectPhysicDesc	PhysicDesc;
		PhysicDesc.Pos = pinfo.ppos;
		PhysicDesc.TypePhysO = KynematicAType;	
		PhysicDesc.TypeShape = CapsuleShape;
		PhysicDesc.Collidable = false;
		PhysicDesc.Density = 1;
		PhysicDesc.SizeX = 0.5;
		PhysicDesc.SizeY = 5;

		tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													PlayerObject, id, pinfo.model, PhysicDesc, 
									SharedDataHandler::getInstance()->GetInfo(id).lifemana,
									SharedDataHandler::getInstance()->GetPlayerExtraInfo(id)));
	}
}

/***********************************************************
player left map
***********************************************************/
void MapHandler::PlayerLeft(Ice::Long id, EventsSeq &tosendevts)
{
	std::vector<Ice::Long>::iterator it = std::find(_currentplayers.begin(), _currentplayers.end(), id);
	if(it != _currentplayers.end())
	{
		// inform all players that player left
		tosendevts.push_back(new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													PlayerObject, id));

		// remove player from list
		_currentplayers.erase(it);
	

		// inform guis
		std::map<std::string, boost::shared_ptr<ServerGUIBase> >::iterator itg = _guihandlers.begin();
		std::map<std::string, boost::shared_ptr<ServerGUIBase> >::iterator endg = _guihandlers.end();
		for(; itg != endg; ++itg)
			itg->second->PlayerLeftMap(id);
	}
}


/***********************************************************
gui update from a client
***********************************************************/
void MapHandler::GuiUpdate(Ice::Long id, const std::string guidi, GuiUpdatesSeq	Updates)
{
	std::map<std::string, boost::shared_ptr<ServerGUIBase> >::iterator it = _guihandlers.find(guidi);
	if(it != _guihandlers.end())
	{
		for(size_t i=0; i<Updates.size(); ++i)
			it->second->Update(id, Updates[i]);
	}
}


/***********************************************************
called when a player moved
***********************************************************/
void MapHandler::PlayerMoved(Ice::Long id, double time, const LbaNet::PlayerMoveInfo &info, 
							 EventsSeq &tosendevts)
{
	//TODO first check if the info is correct

	//TODO then do a interpolation and check for triggers



	if(info.ForcedChange)
	{
		// update player position
		PlayerPosition pos(info.CurrentPos);
		pos.MapName = _mapinfo.Name;
		SharedDataHandler::getInstance()->UpdatePlayerPosition(id, pos);

		// inform all of player move
		tosendevts.push_back(new LbaNet::PlayerMovedEvent(time, id, info, false));
	}


	// inform guis that player moved
	std::map<std::string, boost::shared_ptr<ServerGUIBase> >::iterator itg = _guihandlers.begin();
	std::map<std::string, boost::shared_ptr<ServerGUIBase> >::iterator endg = _guihandlers.end();
	for(; itg != endg; ++itg)
		itg->second->PlayerMoved(id, info.CurrentPos);
}


/***********************************************************
refresh player objects
***********************************************************/
void MapHandler::RefreshPlayerObjects(Ice::Long id)
{
	// first give info to the player about current map state
	EventsSeq toplayer;


	//current objects in map
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact = _Actors.begin();
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator endact = _Actors.end();
	for(; itact != endact; ++itact)
	{
		// TODO - check if objects are visible by the player ( depends of condition)
		const ActorObjectInfo & actinfo = itact->second->GetActorInfo();

		toplayer.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
			actinfo.TypeO, itact->first, actinfo.DisplayDesc, actinfo.PhysicDesc, actinfo.LifeInfo , actinfo.ExtraInfo));
	}


	//{
	//ModelInfo		DisplayDesc;
	//DisplayDesc.TypeRenderer = RenderOsgModel;
	//DisplayDesc.ModelName = "Worlds/Lba1Original/Grids/TheComplexPvpArena.osgb";
	//DisplayDesc.State = LbaNet::NoState;

	//ObjectPhysicDesc	PhysicDesc;
	//PhysicDesc.Pos.X = 0;
	//PhysicDesc.Pos.Y = 0;
	//PhysicDesc.Pos.Z = 0;
	//PhysicDesc.Pos.Rotation = 0;
	//PhysicDesc.TypePhysO = StaticAType;	
	//PhysicDesc.TypeShape = TriangleMeshShape;

	//PhysicDesc.Collidable = true;
	//PhysicDesc.Filename = "Worlds/Lba1Original/Grids/TheComplexPvpArena.phy";

	//toplayer.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
	//											StaticObject, 1, DisplayDesc, PhysicDesc,
	//											LbaNet::LifeManaInfo() ,LbaNet::ObjectExtraInfo()));
	//}

	
	// current players in map
	//TODO - change size
	for(size_t cc=0; cc<_currentplayers.size(); ++cc)
	{
		SavedWorldInfo pinfo = SharedDataHandler::getInstance()->GetInfo(_currentplayers[cc]);

		ObjectPhysicDesc	PhysicDesc;
		PhysicDesc.Pos = pinfo.ppos;
		PhysicDesc.TypePhysO = KynematicAType;	
		PhysicDesc.TypeShape = CapsuleShape;
		PhysicDesc.Collidable = false;
		PhysicDesc.Density = 1;
		PhysicDesc.SizeX = 0.5;
		PhysicDesc.SizeY = 5;

		toplayer.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													PlayerObject, _currentplayers[cc], pinfo.model, PhysicDesc, 
												SharedDataHandler::getInstance()->GetInfo(_currentplayers[cc]).lifemana,
												SharedDataHandler::getInstance()->GetPlayerExtraInfo(_currentplayers[cc])));
	}


	toplayer.push_back(new RefreshEndEvent(SynchronizedTimeHandler::GetCurrentTimeDouble()));
	IceUtil::ThreadPtr t = new EventsSender(toplayer, GetProxy(id));
	t->start();	
}



/***********************************************************
change player stance
***********************************************************/
void MapHandler::ChangeStance(Ice::Long id, LbaNet::ModelStance NewStance, 
														EventsSeq &tosendevts)
{
	ModelInfo returnmodel;
	if(SharedDataHandler::getInstance()->UpdatePlayerStance(id, NewStance, returnmodel))
		tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					PlayerObject, id, new ModelUpdate(returnmodel, false)));
}


/***********************************************************
change player state
***********************************************************/
void MapHandler::ChangePlayerState(Ice::Long id, LbaNet::ModelState NewState, float FallingSize, 
																			 EventsSeq &tosendevts)
{
	ModelInfo returnmodel;
	if(SharedDataHandler::getInstance()->UpdatePlayerState(id, NewState, returnmodel))
		tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					PlayerObject, id, new ModelUpdate(returnmodel, true)));

	//TODO - hurt by falling
}


/***********************************************************
a player is raised from dead
***********************************************************/
void MapHandler::RaiseFromDeadEvent(Ice::Long id, EventsSeq &tosendevts)
{
	ModelInfo returnmodel;

	//check if player was dead
	if(SharedDataHandler::getInstance()->RaiseFromDead(id, returnmodel))
	{
		// if so change state and teleport to raising area
		LbaNet::PlayerPosition pos = SharedDataHandler::getInstance()->GetSpawningPlace(id);

		LbaNet::PlayerMoveInfo moveinfo;
		moveinfo.ForcedChange = true;
		moveinfo.CurrentPos = pos;
		moveinfo.CurrentSpeedX = 0;
		moveinfo.CurrentSpeedY = 0;
		moveinfo.CurrentSpeedZ = 0;
		moveinfo.CurrentSpeedRotation = 0;
		tosendevts.push_back(new LbaNet::PlayerMovedEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
															id, moveinfo, true));

		tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					PlayerObject, id, new ModelUpdate(returnmodel, false)));
	}
}



/***********************************************************
function used by LUA to add actor
***********************************************************/
void MapHandler::AddActorObject(const ActorObjectInfo & object)
{
	_Actors[object.ObjectId] = boost::shared_ptr<ActorHandler>(new ActorHandler(object));
}




/***********************************************************
teleport an object
***********************************************************/
void MapHandler::Teleport(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId,
							const std::string &NewMapName, 
							const std::string &SpawningName)
{
	// if teleport on different map
	if(NewMapName != _mapinfo.Name)
	{
		// teleport player outside the map
		if(OType == LbaNet::PlayerObject)
			SharedDataHandler::getInstance()->ChangeMapPlayer(ObjectId, NewMapName, SpawningName);
	}
	else // same map
	{
		// get spawning info
		LbaNet::SpawningsSeq::iterator itsp = _mapinfo.Spawnings.find(SpawningName);
		if(itsp != _mapinfo.Spawnings.end())
		{
			PlayerPosition pos;
			pos.X = itsp->second.PosX;
			pos.Y = itsp->second.PosY;
			pos.Z = itsp->second.PosZ;
			if(itsp->second.ForceRotation)
				pos.Rotation = itsp->second.Rotation;

			pos.MapName = _mapinfo.Name;


			if(OType == LbaNet::PlayerObject)
			{
				// update player position
				SharedDataHandler::getInstance()->UpdatePlayerPosition(ObjectId, pos);

				// inform all of player move
				LbaNet::PlayerMoveInfo moveinfo;
				moveinfo.ForcedChange = true;
				moveinfo.CurrentPos = pos;
				moveinfo.CurrentSpeedX = 0;
				moveinfo.CurrentSpeedY = 0;
				moveinfo.CurrentSpeedZ = 0;
				moveinfo.CurrentSpeedRotation = 0;
				_tosendevts.push_back(new LbaNet::PlayerMovedEvent(
														SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														ObjectId, moveinfo, true));	
			}

			//TODO - other actors
		}
	}
}