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
#include "PlayerHandler.h"
#include "ActorHandler.h"

#include <math.h>

#define _THREAD_WAIT_TIME_	17
#define	_CUSTOM_OFFSET_	10000000

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
EventsSenderToAll::EventsSenderToAll(EventsSeq & events, std::vector<ClientProxyBasePtr> &proxies)
{
	_events.swap(events);
	_proxies.swap(proxies);
}


/***********************************************************
running function of the thread
***********************************************************/
void EventsSenderToAll::run()
{
	std::vector<ClientProxyBasePtr>::iterator it = _proxies.begin();
	std::vector<ClientProxyBasePtr>::iterator end = _proxies.end();
	for(; it != end; ++it)
	{
		try
		{
			if(*it)
				(*it)->ServerEvents(_events);
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
MapHandler::MapHandler(const MapInfo & mapinfo, 
						const std::string & mapluafilename,
						const std::string & customluafilename)
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

	_luaH.LoadFile(customluafilename);
	_luaH.LoadFile(mapluafilename);


	_luaH.CallLua("InitMap", this);


	// add editor display objects
	#ifdef _USE_QT_EDITOR_
	LbaNet::SpawningsSeq::const_iterator it = _mapinfo.Spawnings.begin();
	LbaNet::SpawningsSeq::const_iterator end = _mapinfo.Spawnings.end();
	for(; it != end; ++it)
	{
		long edobjid = it->first + 1000000;

		ActorObjectInfo ainfo = CreateSpawningDisplay(edobjid, it->second.PosX, 
									it->second.PosY, it->second.PosZ, it->second.Name);
		ainfo.LifeInfo.Display = false;
		_editorObjects[edobjid] = ainfo;
	}
	#endif
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
	_stopping = false;

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
		ProcessEvents(evts);


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

		//stop thread after a while if no player inside
		int nbp = GetNbPlayers();
		if(nbp == 0)
		{
			if(!_stopping)
			{
				_stopping = true;
				_stopstarttime = SynchronizedTimeHandler::GetCurrentTimeDouble();
			}
			else
			{
				double currtime = SynchronizedTimeHandler::GetCurrentTimeDouble();
				double tdiff = currtime - _stopstarttime;
				if(tdiff > 60000) // stop after 1min
					_Trunning = false;
			}
		}
		else
		{
			_stopping = false;
		}
	}
}



/***********************************************************
process events
***********************************************************/
void MapHandler::ProcessEvents(const std::map<Ice::Long, EventsSeq> & evts)
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
				PlayerEntered(it->first);
				continue;
			}

			// client left
			if(info == typeid(LbaNet::PlayerLeaveEvent))
			{
				PlayerLeft(it->first);
				continue;
			}

			// player updated position
			if(info == typeid(LbaNet::PlayerMovedEvent))
			{
				LbaNet::PlayerMovedEvent* castedptr = 
					dynamic_cast<LbaNet::PlayerMovedEvent *>(&obj);

				PlayerMoved(it->first, castedptr->Time, castedptr->info);
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

				SharedDataHandler::getInstance()->TeleportPlayer(it->first, (long)castedptr->TeleportId);

				continue;
			}

			// ChangeStanceEvent
			if(info == typeid(LbaNet::ChangeStanceEvent))
			{
				LbaNet::ChangeStanceEvent* castedptr = 
					dynamic_cast<LbaNet::ChangeStanceEvent *>(&obj);
				
				ChangeStance(it->first, castedptr->NewStance);
				continue;
			}


			// PressedActionKeyEvent
			if(info == typeid(LbaNet::PressedActionKeyEvent))
			{
				LbaNet::PressedActionKeyEvent* castedptr = 
					dynamic_cast<LbaNet::PressedActionKeyEvent *>(&obj);

				ProcessPlayerAction(it->first, castedptr->ForcedNormalAction);
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

				ChangePlayerState(it->first, castedptr->NewState, castedptr->FallingSize);
				continue;
			}

			// RaiseFromDeadEvent
			if(info == typeid(LbaNet::RaiseFromDeadEvent))
			{
				RaiseFromDeadEvent(it->first);
				continue;
			}

			//NewClientExtraInfoEvent
			if(info == typeid(LbaNet::NewClientExtraInfoEvent))
			{
				LbaNet::NewClientExtraInfoEvent* castedptr = 
					dynamic_cast<LbaNet::NewClientExtraInfoEvent *>(&obj);

				_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
									PlayerObject, it->first, new ObjectExtraInfoUpdate(castedptr->ExtraInfo)));
				continue;
			}

			//ReadyToPlayEvent
			if(info == typeid(LbaNet::ReadyToPlayEvent))
			{
				SetReady(it->first);
				continue;
			}


			//ScriptExecutionFinishedEvent
			if(info == typeid(LbaNet::ScriptExecutionFinishedEvent))
			{
				LbaNet::ScriptExecutionFinishedEvent* castedptr = 
					dynamic_cast<LbaNet::ScriptExecutionFinishedEvent *>(&obj);

				FinishedScript((long)it->first, castedptr->ScriptName);
				continue;
			}


			//editor update event
			#ifdef _USE_QT_EDITOR_
			if(info == typeid(EditorEvent))
			{
				EditorEvent* castedptr = 
					static_cast<EditorEvent *>(&obj);

				ProcessEditorUpdate(castedptr->_update);

				continue;
			}
			#endif



			//PlayerItemUsedEvent
			if(info == typeid(LbaNet::PlayerItemUsedEvent))
			{
				LbaNet::PlayerItemUsedEvent* castedptr = 
					dynamic_cast<LbaNet::PlayerItemUsedEvent *>(&obj);

				PlayerItemUsed((long)it->first, (long)castedptr->ItemId);
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
void MapHandler::AddPlayer(Ice::Long clientid, boost::shared_ptr<PlayerHandler> player)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);
	_players[clientid] = player;

}

/***********************************************************
remove player proxy
***********************************************************/
void MapHandler::RemovePlayer(Ice::Long clientid)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it =	_players.find(clientid);	
	if(it != _players.end())
		_players.erase(it);
}


/***********************************************************
get player proxy
***********************************************************/
ClientProxyBasePtr MapHandler::GetProxy(Ice::Long clientid)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it =	_players.find(clientid);	
	if(it != _players.end())
		return it->second->GetProxy();

	return NULL;
}

/***********************************************************
get players proxies
***********************************************************/
std::vector<ClientProxyBasePtr> MapHandler::GetProxies()
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::vector<ClientProxyBasePtr> proxies;
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.begin();
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator end = _players.end();
	for(; it != end; ++it)
		proxies.push_back(it->second->GetProxy());

	return proxies;
}


/***********************************************************
player entered map
***********************************************************/
void MapHandler::PlayerEntered(Ice::Long id)
{
	// add player to list
	_currentplayers.push_back(id);

	try
	{
		// first give info to the player about current map state
		EventsSeq toplayer;


		// inform client he enter a new map
		toplayer.push_back(new NewMapEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
												_mapinfo.Name, 
												SharedDataHandler::getInstance()->GetClientLuaFilename(_mapinfo.Name), 
												_mapinfo.AutoCameraType)); 
		
		// remove ephemere item
		RemoveEphemere(id);

		//check if map is interior
		if(_mapinfo.Type == "interior")
		{
			LbaNet::ModelInfo minfo = GetPlayerModelInfo(id);
			if(minfo.Mode == "Horse" || minfo.Mode == "Dinofly")
				ChangeStance(id, LbaNet::StanceNormal, true);
		}

		// player inventory
		{
		GuiParamsSeq seq;
		seq.push_back(new InventoryGuiParameter(GetInventorySize(id), GetInventory(id)));
		toplayer.push_back(
			new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), "InventoryBox", seq, false, false));
		}

		// player shortcut
		{
		GuiParamsSeq seq;
		seq.push_back(new ShortcutGuiParameter(GetShorcuts(id)));
		toplayer.push_back(
			new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", seq, false, false));
		}



		IceUtil::ThreadPtr t = new EventsSender(toplayer, GetProxy(id));
		t->start();	



		// then inform all players that player entered
		{
			ObjectPhysicDesc	PhysicDesc;
			PhysicDesc.Pos = GetPlayerPosition(id);
			PhysicDesc.TypePhysO = KynematicAType;	
			PhysicDesc.TypeShape = CapsuleShape;
			PhysicDesc.Collidable = false;
			PhysicDesc.Density = 1;

			float sizeX, sizeY, sizeZ;
			GetPlayerPhysicalSize(id, sizeX, sizeY, sizeZ);
			PhysicDesc.SizeX = sizeX/2;
			PhysicDesc.SizeY = sizeY;

			_tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														PlayerObject, id, GetPlayerModelInfo(id), PhysicDesc, 
														GetPlayerLifeInfo(id), GetPlayerExtraInfo(id)));
		}


		// inform triggers
		{
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
			for(; ittr != endtr; ++ittr)
				ittr->second->ObjectEnterMap(2, id);
		}
	}
	catch(NoPlayerException)
	{
		// player already left the map
	}
}

/***********************************************************
player left map
***********************************************************/
void MapHandler::PlayerLeft(Ice::Long id)
{
	std::vector<Ice::Long>::iterator it = std::find(_currentplayers.begin(), _currentplayers.end(), id);
	if(it != _currentplayers.end())
	{
		// inform triggers
		{
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
			for(; ittr != endtr; ++ittr)
				ittr->second->ObjectLeaveMap(2, id);
		}


		// inform all players that player left
		_tosendevts.push_back(new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
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
void MapHandler::PlayerMoved(Ice::Long id, double time, const LbaNet::PlayerMoveInfo &info)
{
	// check if player ready to play - else do nothing as this may be old move form other maps
	if(!IsReady(id))
		return;

	#ifndef _USE_QT_EDITOR_
	//TODO first check if the info is correct and no cheating
	#endif

	try
	{
		//do an sweep test and check for triggers
		{
			PlayerPosition lastpos = GetPlayerPosition(id);
			lastpos.Y += 0.2; // small offset to make sure object is inside zone and not online a bit lower
			PlayerPosition currPos = info.CurrentPos;
			currPos.Y += 0.2;

			// inform triggers
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
			for(; ittr != endtr; ++ittr)
				ittr->second->ObjectMoved(2, id, lastpos, currPos);
		}


		// update player position
		PlayerPosition pos(info.CurrentPos);
		pos.MapName = _mapinfo.Name;

		// check if position could be updated
		if(UpdatePlayerPosition(id, pos))
		{
			if(info.ForcedChange)
			{
				// inform all of player move
				_tosendevts.push_back(new LbaNet::PlayerMovedEvent(time, id, info, false));
			}

			// inform guis that player moved
			std::map<std::string, boost::shared_ptr<ServerGUIBase> >::iterator itg = _guihandlers.begin();
			std::map<std::string, boost::shared_ptr<ServerGUIBase> >::iterator endg = _guihandlers.end();
			for(; itg != endg; ++itg)
				itg->second->PlayerMoved(id, info.CurrentPos);
		}
	}
	catch(NoPlayerException)
	{
		// player already left the map
	}
}


/***********************************************************
refresh player objects
***********************************************************/
void MapHandler::RefreshPlayerObjects(Ice::Long id)
{
	// first give info to the player about current map state
	EventsSeq toplayer;


	//current objects in map
	{
		std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact = _Actors.begin();
		std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator endact = _Actors.end();
		for(; itact != endact; ++itact)
		{
			
			const ActorObjectInfo & actinfo = itact->second->GetActorInfo();

			// check if objects are visible by the player ( depends of condition)
			bool passed = true;
			if(actinfo.Condition)
				passed = actinfo.Condition->Passed(this, 2, id);

			if(passed)
			{
				LbaNet::ObjectExtraInfo xinfo = actinfo.ExtraInfo;

				#ifdef _USE_QT_EDITOR_
					std::stringstream strs;
					strs<<"Actor_"<<actinfo.ObjectId<<": "<<xinfo.Name;
					xinfo.Name = strs.str();
					xinfo.NameColorR = 0.2;
					xinfo.NameColorG = 0.2;
					xinfo.NameColorB = 1.0;
				#endif

				toplayer.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
					LbaNet::NpcObject, itact->first, actinfo.DisplayDesc, actinfo.PhysicDesc, actinfo.LifeInfo, 
					xinfo));
			}
		}
	}

	#ifdef _USE_QT_EDITOR_
	{
		std::map<Ice::Long, ActorObjectInfo >::iterator itact = _editorObjects.begin();
		std::map<Ice::Long, ActorObjectInfo >::iterator endact = _editorObjects.end();
		for(; itact != endact; ++itact)
		{
			ActorObjectInfo & actinfo = itact->second;
			actinfo.LifeInfo.Display = false;

			toplayer.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
				LbaNet::EditorObject, itact->first, actinfo.DisplayDesc, actinfo.PhysicDesc, actinfo.LifeInfo , 
				actinfo.ExtraInfo));
		}
	}
	#endif

	
	// current players in map
	for(size_t cc=0; cc<_currentplayers.size(); ++cc)
	{
		try
		{
			ObjectPhysicDesc	PhysicDesc;
			PhysicDesc.Pos = GetPlayerPosition(_currentplayers[cc]);
			PhysicDesc.TypePhysO = KynematicAType;	
			PhysicDesc.TypeShape = CapsuleShape;
			PhysicDesc.Collidable = false;
			PhysicDesc.Density = 1;

			float sizeX, sizeY, sizeZ;
			GetPlayerPhysicalSize(_currentplayers[cc], sizeX, sizeY, sizeZ);
			PhysicDesc.SizeX = sizeX/2;
			PhysicDesc.SizeY = sizeY;

			toplayer.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														PlayerObject, _currentplayers[cc], 
														GetPlayerModelInfo(_currentplayers[cc]), PhysicDesc, 
														GetPlayerLifeInfo(_currentplayers[cc]),
														GetPlayerExtraInfo(_currentplayers[cc])));
		}
		catch(NoPlayerException)
		{
			// player already left the map
		}
	}


	toplayer.push_back(new RefreshEndEvent(SynchronizedTimeHandler::GetCurrentTimeDouble()));
	IceUtil::ThreadPtr t = new EventsSender(toplayer, GetProxy(id));
	t->start();	
}



/***********************************************************
change player stance
***********************************************************/
void MapHandler::ChangeStance(Ice::Long id, LbaNet::ModelStance NewStance, bool fromserver)
{
	ModelInfo returnmodel;
	if(UpdatePlayerStance(id, NewStance, returnmodel, fromserver))
	{
		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					PlayerObject, id, new ModelUpdate(returnmodel, false)));

		// update physical info as well
		float sizeX, sizeY, sizeZ;
		GetPlayerPhysicalSize(id, sizeX, sizeY, sizeZ);
		_tosendevts.push_back(new UpdatePhysicObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													PlayerObject, id,  
													new SizeUpdate(sizeX, sizeY, sizeZ)));

	}
}


/***********************************************************
change player weapon
***********************************************************/
void MapHandler::ChangeWeapon(Ice::Long id, const std::string & weapon, long itemid)
{
	ModelInfo returnmodel;
	if(UpdatePlayerWeapon(id, weapon, returnmodel, itemid))
		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					PlayerObject, id, new ModelUpdate(returnmodel, false)));
}


/***********************************************************
change player outfit
***********************************************************/
void MapHandler::ChangeOutfit(Ice::Long id, const std::string & outfit, long itemid)
{
	ModelInfo returnmodel;
	if(UpdatePlayerOutfit(id, outfit, returnmodel, itemid))
		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					PlayerObject, id, new ModelUpdate(returnmodel, false)));
}



/***********************************************************
change player state
***********************************************************/
void MapHandler::ChangePlayerState(Ice::Long id, LbaNet::ModelState NewState, float FallingSize,
																						bool fromserver)
{
	ModelInfo returnmodel;
	if(UpdatePlayerState(id, NewState, returnmodel))
		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					PlayerObject, id, new ModelUpdate(returnmodel, !fromserver)));

	//if hurt by falling
	if(NewState == LbaNet::StHurtFall)
	{
		if(FallingSize > 0)
			DeltaUpdateLife(id, -FallingSize*_mapinfo.HurtFallFactor);
	}
}


/***********************************************************
a player is raised from dead
***********************************************************/
void MapHandler::RaiseFromDeadEvent(Ice::Long id)
{
	ModelInfo returnmodel;

	//check if player was dead
	if(RaiseFromDead(id, returnmodel))
	{
		try
		{
			// if so change state and teleport to raising area
			LbaNet::PlayerPosition pos = GetSpawningPlace(id);

			LbaNet::PlayerMoveInfo moveinfo;
			moveinfo.ForcedChange = true;
			moveinfo.CurrentPos = pos;
			moveinfo.CurrentSpeedX = 0;
			moveinfo.CurrentSpeedY = 0;
			moveinfo.CurrentSpeedZ = 0;
			moveinfo.CurrentSpeedRotation = 0;
			_tosendevts.push_back(new LbaNet::PlayerMovedEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																id, moveinfo, true));

			_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
						PlayerObject, id, new ModelUpdate(returnmodel, false)));

			_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
									PlayerObject, id, new ObjectLifeInfoUpdate(GetPlayerLifeInfo(id))));
		}
		catch(NoPlayerException)
		{
			// player already left the map
		}
	}
}



/***********************************************************
function used by LUA to add actor
***********************************************************/
void MapHandler::AddActorObject(boost::shared_ptr<ActorHandler> actor)
{
	_Actors[actor->GetId()] = actor;
	actor->GetInfo().LifeInfo.Display = false;
	actor->GetInfo().ExtraInfo.Display = false;
}




/***********************************************************
teleport an object
***********************************************************/
void MapHandler::Teleport(int ObjectType, long ObjectId,
							const std::string &NewMapName, long SpawningId,
							float offsetX, float offsetY, float offsetZ)
{
	// if teleport on different map
	if(NewMapName != _mapinfo.Name)
	{
		// teleport player outside the map
		if(ObjectType == 2)
			SharedDataHandler::getInstance()->ChangeMapPlayer(ObjectId, NewMapName, SpawningId,
																		offsetX, offsetY, offsetZ);
	}
	else // same map
	{
		// get spawning info
		LbaNet::SpawningsSeq::iterator itsp = _mapinfo.Spawnings.find(SpawningId);
		if(itsp != _mapinfo.Spawnings.end())
		{
			PlayerPosition pos;
			pos.X = itsp->second.PosX + offsetX;
			pos.Y = itsp->second.PosY + offsetY;
			pos.Z = itsp->second.PosZ + offsetZ;
			if(itsp->second.ForceRotation)
				pos.Rotation = itsp->second.Rotation;

			pos.MapName = _mapinfo.Name;


			if(ObjectType == 2)
			{
				// update player position
				if(UpdatePlayerPosition(ObjectId, pos, true))
				{
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
			}

			//TODO - other actors
		}
	}
}




/***********************************************************
add a trigger to the map
***********************************************************/
void MapHandler::AddTrigger(boost::shared_ptr<TriggerBase> trigger)
{
	if(trigger)
	{
		trigger->SetOwner(this);
		_triggers[trigger->GetId()] = trigger;

		#ifdef _USE_QT_EDITOR_
		ActorObjectInfo ainfo = trigger->GetDisplayObject();
		ainfo.LifeInfo.Display = false;
		long edobjid = ainfo.ObjectId;
		if(edobjid < 0)
			return;

		std::map<Ice::Long, ActorObjectInfo >::iterator itm = _editorObjects.find(edobjid);
		if(itm != _editorObjects.end())
		{
			// object already exist - update position if needed
			_editorObjects[edobjid] = ainfo;

			// reset the object display on client
			_tosendevts.push_back(new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																			LbaNet::EditorObject, edobjid));

			_tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
					LbaNet::EditorObject, edobjid, ainfo.DisplayDesc, ainfo.PhysicDesc, ainfo.LifeInfo, 
					ainfo.ExtraInfo));
		}
		else
		{
			// object does not exist - add it
			_editorObjects[edobjid] = ainfo;

			_tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
					LbaNet::EditorObject, edobjid, ainfo.DisplayDesc, ainfo.PhysicDesc, ainfo.LifeInfo , 
					ainfo.ExtraInfo));
		}
		#endif
	}
}


/***********************************************************
process player action
***********************************************************/
void MapHandler::ProcessPlayerAction(Ice::Long id, bool ForcedNormalAction)
{
	try
	{
		PlayerPosition pos = GetPlayerPosition(id);
		std::string mode = GetPlayerModeString(id);

		// inform triggers
		{
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
			for(; ittr != endtr; ++ittr)
				ittr->second->ObjectAction(2, id, pos, (ForcedNormalAction? "Normal": mode));
		}
	}
	catch(NoPlayerException)
	{
		// player already left the map
	}
}




/***********************************************************
return inventory size
***********************************************************/
int MapHandler::GetInventorySize(Ice::Long clientid)
{
	{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetInventorySize();
	}

	throw(NoPlayerException());
}

/***********************************************************
return inventory content
***********************************************************/
ItemsMap MapHandler::GetInventory(Ice::Long clientid)
{
	{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetInventory();
	}

	throw(NoPlayerException());
}



/***********************************************************
return shortcuts
***********************************************************/
ShortcutsSeq MapHandler::GetShorcuts(Ice::Long clientid)
{
	{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetShorcuts();
	}

	throw(NoPlayerException());
}

/***********************************************************
get player position
***********************************************************/
PlayerPosition MapHandler::GetPlayerPosition(Ice::Long clientid)
{
	{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetPlayerPosition();
	}

	throw(NoPlayerException());
}


/***********************************************************
get player mode string
***********************************************************/
std::string MapHandler::GetPlayerModeString(Ice::Long clientid)
{
	{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetPlayerModeString();
	}

	throw(NoPlayerException());
}



/***********************************************************
get player life info
***********************************************************/
LbaNet::LifeManaInfo MapHandler::GetPlayerLifeInfo(Ice::Long clientid)
{
	{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetLifeManaInfo();
	}

	throw(NoPlayerException());
}


/***********************************************************
get player extra info
***********************************************************/
LbaNet::ObjectExtraInfo MapHandler::GetPlayerExtraInfo(Ice::Long clientid)
{
	{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetExtraInfo();
	}

	throw(NoPlayerException());
}


/***********************************************************
get player model info
***********************************************************/
LbaNet::ModelInfo MapHandler::GetPlayerModelInfo(Ice::Long clientid)
{
	{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetModelInfo();
	}

	throw(NoPlayerException());
}


/***********************************************************
get player physcial size
***********************************************************/
void MapHandler::GetPlayerPhysicalSize(Ice::Long clientid, float &sX, float &sY, float &sZ)
{
	{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetPlayerPhysicalSize(sX, sY, sZ);
	}

	throw(NoPlayerException());
}


/***********************************************************
//!  get the place to respawn in case of death
***********************************************************/
LbaNet::PlayerPosition MapHandler::GetSpawningPlace(Ice::Long clientid)
{
	{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetSpawningPlace();
	}

	throw(NoPlayerException());
}




/***********************************************************
update player position
***********************************************************/
bool MapHandler::UpdatePlayerPosition(Ice::Long clientid, const PlayerPosition & pos, bool teleport)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
	{
		if(teleport)
			it->second->Teleport(pos);
		else
			it->second->UpdatePositionInWorld(pos);
		return true;
	}

	return false;
}


/***********************************************************
//!  update player stance
//! return true if state has been updated
***********************************************************/
bool MapHandler::UpdatePlayerStance(Ice::Long clientid, LbaNet::ModelStance NewStance,
												ModelInfo & returnmodel, bool fromserver)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->UpdatePlayerStance(NewStance, returnmodel, fromserver);

	return false;
}


/***********************************************************
//!  update player state
//! return true if state has been updated
***********************************************************/
bool MapHandler::UpdatePlayerState(Ice::Long clientid, LbaNet::ModelState NewState,
												ModelInfo & returnmodel )
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->UpdatePlayerState(NewState, returnmodel);

	return false;
}


/***********************************************************
//!  update player weapon
//! return true if state has been updated
***********************************************************/
bool MapHandler::UpdatePlayerWeapon(Ice::Long clientid, const std::string & weapon,
													ModelInfo & returnmodel, long itemid)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->UpdatePlayerWeapon(weapon, returnmodel, itemid);

	return false;
}


/***********************************************************
//!  update player outfit
//! return true if state has been updated
***********************************************************/
bool MapHandler::UpdatePlayerOutfit(Ice::Long clientid, const std::string & outfit,
													ModelInfo & returnmodel, long itemid)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->UpdatePlayerOutfit(outfit, returnmodel, itemid);

	return false;
}


/***********************************************************
//!  save player state
***********************************************************/
void MapHandler::SavePlayerState(Ice::Long clientid)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		it->second->SavePlayerState();

}


/***********************************************************
//!  restore player state
***********************************************************/
bool MapHandler::RestorePlayerState(Ice::Long clientid, ModelInfo & returnmodel)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->RestorePlayerState(returnmodel);

	return false;
}



/***********************************************************
	//!  raised player from dead
	//! return true if raised
***********************************************************/
bool MapHandler::RaiseFromDead(Ice::Long clientid, ModelInfo & returnmodel)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->RaiseFromDead(returnmodel);

	return false;
}


/***********************************************************
set player ready to play
***********************************************************/
void MapHandler::SetReady(Ice::Long clientid)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		it->second->SetReady();
}


/***********************************************************
ask if player ready to play
***********************************************************/
bool MapHandler::IsReady(Ice::Long clientid)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->IsReady();

	return false;
}






/***********************************************************
process editor events
***********************************************************/
#ifdef _USE_QT_EDITOR_
void MapHandler::ProcessEditorUpdate(LbaNet::EditorUpdateBasePtr update)
{
	LbaNet::EditorUpdateBase & obj = *update;
	const std::type_info& info = typeid(obj);

	// spawning update
	if(info == typeid(UpdateEditor_AddOrModSpawning))
	{
		UpdateEditor_AddOrModSpawning* castedptr = 
			dynamic_cast<UpdateEditor_AddOrModSpawning *>(&obj);

		Editor_AddOrModSpawning(castedptr->_SpawningId,
									castedptr->_spawningname,
									castedptr->_PosX,
									castedptr->_PosY, 
									castedptr->_PosZ,
									castedptr->_Rotation, 
									castedptr->_forcedrotation);

		return;
	}


	// spawning remove
	if(info == typeid(UpdateEditor_RemoveSpawning))
	{
		UpdateEditor_RemoveSpawning* castedptr = 
			dynamic_cast<UpdateEditor_RemoveSpawning *>(&obj);

		Editor_RemoveSpawning(castedptr->_SpawningId);
	}


	// trigger update
	if(info == typeid(UpdateEditor_AddOrModTrigger))
	{
		UpdateEditor_AddOrModTrigger* castedptr = 
			dynamic_cast<UpdateEditor_AddOrModTrigger *>(&obj);

		AddTrigger(castedptr->_trigger);
		return;
	}


	// trigger remove
	if(info == typeid(UpdateEditor_RemoveTrigger))
	{
		UpdateEditor_RemoveTrigger* castedptr = 
			dynamic_cast<UpdateEditor_RemoveTrigger *>(&obj);

		Editor_RemoveTrigger(castedptr->_TriggerId);
	}

	// map info modified
	if(info == typeid(UpdateEditor_AddOrModMap))
	{
		UpdateEditor_AddOrModMap* castedptr = 
			dynamic_cast<UpdateEditor_AddOrModMap *>(&obj);

		_mapinfo = castedptr->_mapinfo;
	}



	// actor update
	if(info == typeid(UpdateEditor_AddOrModActor))
	{
		UpdateEditor_AddOrModActor* castedptr = 
			dynamic_cast<UpdateEditor_AddOrModActor *>(&obj);

		Editor_AddModActor(castedptr->_actor);
		return;
	}


	// actor remove
	if(info == typeid(UpdateEditor_RemoveActor))
	{
		UpdateEditor_RemoveActor* castedptr = 
			dynamic_cast<UpdateEditor_RemoveActor *>(&obj);

		Editor_RemoveActor(castedptr->_id);
	}

}
#endif


/***********************************************************
add a spawning to the map
***********************************************************/
#ifdef _USE_QT_EDITOR_
void MapHandler::Editor_AddOrModSpawning(	long SpawningId, const std::string &spawningname,
											float PosX, float PosY, float PosZ,
											float Rotation, bool forcedrotation)
{
	LbaNet::SpawningInfo spawn;
	spawn.Id = SpawningId;
	spawn.Name = spawningname;
	spawn.PosX = PosX;
	spawn.PosY = PosY;
	spawn.PosZ = PosZ;
	spawn.Rotation = Rotation;
	spawn.ForceRotation = forcedrotation;
	_mapinfo.Spawnings[SpawningId] = spawn;	

	long edobjid = SpawningId + 1000000;

	std::map<Ice::Long, ActorObjectInfo >::iterator itm = _editorObjects.find(edobjid);
	if(itm != _editorObjects.end())
	{
		// object already exist - update position if needed
		itm->second.PhysicDesc.Pos.X = PosX;
		itm->second.PhysicDesc.Pos.Y = PosY;
		itm->second.PhysicDesc.Pos.Z = PosZ;

		std::stringstream strs;
		strs << "Spawn-"<<SpawningId<<": " << spawningname;
		itm->second.ExtraInfo.Name = strs.str();

		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
				LbaNet::EditorObject, edobjid, new ObjectExtraInfoUpdate(itm->second.ExtraInfo)));

		_tosendevts.push_back(new UpdatePhysicObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
				LbaNet::EditorObject, edobjid, new PositionUpdate(itm->second.PhysicDesc.Pos)));
	}
	else
	{
		// object does not exist - add it
		ActorObjectInfo ainfo = CreateSpawningDisplay(edobjid, PosX, PosY, PosZ, spawningname);
		_editorObjects[edobjid] = ainfo;

		_tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
				LbaNet::EditorObject, edobjid, ainfo.DisplayDesc, ainfo.PhysicDesc, ainfo.LifeInfo , 
				ainfo.ExtraInfo));
	}
}
#endif


/***********************************************************
remove a spawning
***********************************************************/
#ifdef _USE_QT_EDITOR_
void MapHandler::Editor_RemoveSpawning(long SpawningId)
{
	long edobjid = SpawningId + 1000000;

	LbaNet::SpawningsSeq::iterator it = _mapinfo.Spawnings.find(SpawningId);
	if(it != _mapinfo.Spawnings.end())
	{
		// erase from data
		_mapinfo.Spawnings.erase(it);

		std::map<Ice::Long, ActorObjectInfo >::iterator itm = _editorObjects.find(edobjid);
		if(itm != _editorObjects.end())
		{
			_editorObjects.erase(itm);

			_tosendevts.push_back(new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																			LbaNet::EditorObject, edobjid));
		}
	}
}
#endif





/***********************************************************
remove a trigger
***********************************************************/
#ifdef _USE_QT_EDITOR_
void MapHandler::Editor_RemoveTrigger(long TriggerId)
{
	std::map<long, boost::shared_ptr<TriggerBase> >::iterator it = _triggers.find(TriggerId);
	if(it != _triggers.end())
	{
		// erase from data
		_triggers.erase(it);

		long edobjid = TriggerId + 2000000;
		std::map<Ice::Long, ActorObjectInfo >::iterator itm = _editorObjects.find(edobjid);
		if(itm != _editorObjects.end())
		{
			_editorObjects.erase(itm);

			_tosendevts.push_back(new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																			LbaNet::EditorObject, edobjid));
		}
	}
}
#endif


/***********************************************************
create display object for spawning
***********************************************************/
ActorObjectInfo MapHandler::CreateSpawningDisplay(long id, float PosX, float PosY, float PosZ, 
												  const std::string & name)
{
	ActorObjectInfo ainfo(id);
	ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderCross;
	ainfo.DisplayDesc.ColorR = 0.2f;
	ainfo.DisplayDesc.ColorG = 1.0f;
	ainfo.DisplayDesc.ColorB = 0.2f;
	ainfo.DisplayDesc.ColorA = 1.0f;
	ainfo.PhysicDesc.TypeShape = LbaNet::NoShape;
	ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
	ainfo.PhysicDesc.Pos.X = PosX;
	ainfo.PhysicDesc.Pos.Y = PosY;
	ainfo.PhysicDesc.Pos.Z = PosZ;
	ainfo.PhysicDesc.Pos.Rotation = 0;
	ainfo.PhysicDesc.SizeX = 3;
	ainfo.PhysicDesc.SizeY = 0;
	ainfo.PhysicDesc.SizeZ = 0;

	std::stringstream strs;
	strs << "Spawn-"<<id-1000000<<": " << name;
	ainfo.ExtraInfo.Name = strs.str();
	ainfo.ExtraInfo.NameColorR = 0.2f;
	ainfo.ExtraInfo.NameColorG = 1.0f;
	ainfo.ExtraInfo.NameColorB = 0.2f;
	return ainfo;
}



/***********************************************************
add an actor
***********************************************************/
#ifdef _USE_QT_EDITOR_
void MapHandler::Editor_AddModActor(boost::shared_ptr<ActorHandler> actor)
{
	AddActorObject(actor);

	//bool passed = true;
	//if(actor->GetInfo().Condition)
	//	passed = actor->GetInfo().Condition->Passed(this, 2, 1);

	
	// update client
	_tosendevts.push_back(new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																	LbaNet::NpcObject, actor->GetId()));



	LbaNet::ObjectExtraInfo xinfo = actor->GetInfo().ExtraInfo;
	std::stringstream strs;
	strs<<"Actor_"<<actor->GetId()<<": "<<xinfo.Name;
	xinfo.Name = strs.str();
	xinfo.NameColorR = 0.2;
	xinfo.NameColorG = 0.2;
	xinfo.NameColorB = 1.0;


	_tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														LbaNet::NpcObject, actor->GetId(), 
														actor->GetInfo().DisplayDesc, 
														actor->GetInfo().PhysicDesc, 
														actor->GetInfo().LifeInfo, 
														xinfo));

}
#endif


/***********************************************************
remove an actor
***********************************************************/
#ifdef _USE_QT_EDITOR_
void MapHandler::Editor_RemoveActor(long Id)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.find(Id);
	if(it != _Actors.end())
	{
		// erase from data
		_Actors.erase(it);

		// update client
		_tosendevts.push_back(new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																		LbaNet::NpcObject, Id));
	}
}
#endif


/***********************************************************
execute client script - does not work on npc objects
ObjectType ==>
 1 -> npc object
 2 -> player object
 3 -> movable object
***********************************************************/
void MapHandler::ExecuteClientScript(int ObjectType, long ObjectId,
										const std::string & ScriptName,
										bool InlineFunction)
{
	// does not work on npc
	if(ObjectType == 1)
		return;


	long clientid = -1;

	// on player
	if(ObjectType == 2)
		clientid = ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		// todo - find attached player
	}

	// check if client found - else return
	if(clientid < 0)
		return;

	// do nothing if we are already on scripted state
	if(GetPlayerModelInfo(clientid).State == LbaNet::StScripted)
		return;

	// change to scripted state and inform player to run script
	ModelInfo returnmodel;
	SavePlayerState(clientid);
	if(UpdatePlayerState(clientid, LbaNet::StScripted, returnmodel))
	{
		EventsSeq toplayer;

		toplayer.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					PlayerObject, clientid, new ModelUpdate(returnmodel, false)));

		toplayer.push_back(new StartClientScriptEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
									ScriptName, InlineFunction));

		IceUtil::ThreadPtr t = new EventsSender(toplayer, GetProxy(clientid));
		t->start();	
	}
}



/***********************************************************
execute custom lua function
ObjectType ==>
 1 -> npc object
 2 -> player object
 3 -> movable object
***********************************************************/
void MapHandler::ExecuteCustomAction(int ObjectType, long ObjectId,
										const std::string & FunctionName,
										ActionArgumentBase * args)
{
	_luaH.ExecuteCustomAction(ObjectType, ObjectId, FunctionName, args, this);
}



/***********************************************************
display text to client window
ObjectType ==>
 1 -> npc object
 2 -> player object
 3 -> movable object
***********************************************************/
void MapHandler::DisplayTxtAction(int ObjectType, long ObjectId,
										long TextId)
{
	// does not work on npc
	if(ObjectType == 1)
		return;


	long clientid = -1;

	// on player
	if(ObjectType == 2)
		clientid = ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		// todo - find attached player
	}

	// check if client found - else return
	if(clientid < 0)
		return;


	// send text request to player
	_guihandlers["TextBox"]->ShowGUI(clientid, GetPlayerPosition(clientid), 
					boost::shared_ptr<ShowGuiParamBase>(new TextBoxParam(TextId)));
}




/***********************************************************
called when a script is finished on a client
***********************************************************/
void MapHandler::FinishedScript(long id, const std::string & ScriptName)
{
	// check if script was running 
	LbaNet::ModelInfo  modelinfo = GetPlayerModelInfo(id);
	if(modelinfo.State != LbaNet::StScripted)
		return;


	// change state back to before scripted and inform the client
	ModelInfo returnmodel;
	if(RestorePlayerState(id, returnmodel))
	{
		EventsSeq toplayer;

		toplayer.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					PlayerObject, id, new ModelUpdate(returnmodel, false)));

		IceUtil::ThreadPtr t = new EventsSender(toplayer, GetProxy(id));
		t->start();	
	}
}



/***********************************************************
called when the player use an item
***********************************************************/
void MapHandler::PlayerItemUsed(Ice::Long clientid, long ItemId)
{
	// get item info
	LbaNet::ItemPosInfo itinfo = GetItemInfo(clientid, ItemId);

	if(itinfo.Info.Id < 0) // invalid item
		return;

	switch(itinfo.Info.Type)
	{
		case 1: // consummable item
			if(PlayerConsumeItem(clientid, ItemId))
			{
				// give life update to everybody
				_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
									PlayerObject, clientid, new ObjectLifeInfoUpdate(GetPlayerLifeInfo(clientid))));
			}
			break;
		case 2: // key item - dont do anything
			break;
		case 3: // monture item - ride it
			{
				switch(itinfo.Info.Flag)
				{
					case 1:
						ChangeStance(clientid, LbaNet::StanceProtopack, true);
					break;
					case 2:
						if(_mapinfo.Type == "exterior")
							ChangeStance(clientid, LbaNet::StanceHorse, true);
					break;
					case 3:
						if(_mapinfo.Type == "exterior")
							ChangeStance(clientid, LbaNet::StanceDinofly, true);
					break;
				}
			}
			break;
		case 4: // weapon item - equip it
			ChangeWeapon(clientid, itinfo.Info.StringFlag, itinfo.Info.Id);
			break;
		case 5: // quest item - todo - might trigger quest
			break;
		case 6: // other item - dont do anything
			break;
		case 7: // special usage item
			switch(itinfo.Info.Flag)
			{
				case 1: // letter writter
				{
					EventsSeq toplayer;		
					toplayer.push_back(
						new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"LetterEditorBox", GuiParamsSeq(), true, false));

					IceUtil::ThreadPtr t = new EventsSender(toplayer, GetProxy(clientid));
					t->start();	
				}
				break;
			}
			break;
		case 8: // letters item, open them
			{
				boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
				if(dbh)
				{
					LbaNet::LetterInfo linfo = dbh->GetLetterInfo(itinfo.Info.Id-_CUSTOM_OFFSET_);
					if(linfo.LetterId >= 0)
					{
						EventsSeq toplayer;		
						GuiParamsSeq seq;
						seq.push_back(new LetterViewerGuiParameter(linfo));
						toplayer.push_back(
							new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														"LetterViewerBox", seq, true, false));

						IceUtil::ThreadPtr t = new EventsSender(toplayer, GetProxy(clientid));
						t->start();
					}
				}
			}
			break;
		case 9: // outfit item - equip it
			ChangeOutfit(clientid, itinfo.Info.StringFlag, itinfo.Info.Id);
			break;
	}

}


/***********************************************************
get info about an item
***********************************************************/
LbaNet::ItemPosInfo MapHandler::GetItemInfo(Ice::Long clientid, long ItemId)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		return itplayer->second->GetItemInfo(ItemId);

	LbaNet::ItemPosInfo res;
	res.Info.Id = -1;
	return res;
}


/***********************************************************
item consumed
***********************************************************/
bool MapHandler::PlayerConsumeItem(Ice::Long clientid, long ItemId)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		return itplayer->second->ConsumeItem(ItemId);

	return false;
}


/***********************************************************
remove ephemere from player inventory
***********************************************************/
void MapHandler::RemoveEphemere(Ice::Long clientid)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		itplayer->second->RemoveEphemere();
}

/***********************************************************
//! update player life
//! return true if no life
***********************************************************/
bool MapHandler::DeltaUpdateLife(Ice::Long clientid, float update)
{
	bool res = false;
	{
		IceUtil::Mutex::Lock sync(_mutex_proxies);

		std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
		if(itplayer != _players.end())
		{
			res = itplayer->second->DeltaUpdateLife(update);
		}
	}

	// give life update to everybody	
	_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
							PlayerObject, clientid, new ObjectLifeInfoUpdate(GetPlayerLifeInfo(clientid))));
	if(res)// die
		ChangePlayerState(clientid, LbaNet::StDying, 0, true);



	return res;
}


/***********************************************************
//! update player mana
//! return true if no mana
***********************************************************/
bool MapHandler::DeltaUpdateMana(Ice::Long clientid, float update)
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		return itplayer->second->DeltaUpdateMana(update);

	return false;
}

/***********************************************************
//! return number of player on map
***********************************************************/
int MapHandler::GetNbPlayers()
{
	IceUtil::Mutex::Lock sync(_mutex_proxies);
	return (int)_players.size();
}