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
#include "InventoryItemHandler.h"
#include "Spawn.h"
#include "LogHandler.h"

#include <math.h>

#define _THREAD_WAIT_TIME_	17
#define	_CUSTOM_OFFSET_	10000000



/***********************************************************
constructor
***********************************************************/
MapHandler::MapHandler(const std::string & worldname, const MapInfo & mapinfo,
						const std::string & mapluafilename,
						const std::string & customluafilename)
: _Trunning(false), _mapinfo(mapinfo), _worldname(worldname)
{
	// initialize the gui handlers
	_guihandlers["CommunityBox"] = boost::shared_ptr<ServerGUIBase>(new CommunityBoxHandler(this));
	_guihandlers["ShortcutBox"] = boost::shared_ptr<ServerGUIBase>(new ShortcutBoxHandler(this));
	_guihandlers["MailBox"] = boost::shared_ptr<ServerGUIBase>(new MailBoxHandler(this));

	_guihandlers["TextBox"] = boost::shared_ptr<ServerGUIBase>(new TextBoxHandler(this));
	_guihandlers["ContainerBox"] = boost::shared_ptr<ServerGUIBase>(new ContainerBoxHandler(this));
	_guihandlers["DialogBox"] = boost::shared_ptr<ServerGUIBase>(new DialogBoxHandler(this));
	_guihandlers["ShopBox"] = boost::shared_ptr<ServerGUIBase>(new ShopBoxHandler(this));
	_guihandlers["InventoryBox"] = boost::shared_ptr<ServerGUIBase>(new InventoryBoxHandler(this));


	//script part
	m_luaHandler = boost::shared_ptr<ServerLuaHandler>(new  ServerLuaHandler());
	m_luaHandler->LoadFile("LuaCommon/ClientHelperFunctions.lua");
	m_luaHandler->LoadFile(customluafilename);
	m_luaHandler->LoadFile(mapluafilename);

	m_luaHandler->CallLua("InitMap", this);

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

	_Actors.clear();
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
	double timetodiff = SynchronizedTimeHandler::GetCurrentTimeDouble();
	float tdiff = _THREAD_WAIT_TIME_;

	// stop thread if running is false
	while(_Trunning)
	{
		// prepare events to send to everybody
		_tosendevts.clear();

		//add and remove players
		std::vector<std::pair<Ice::Long, boost::shared_ptr<PlayerHandler> > > toadd;
		std::vector<Ice::Long> toremove;
		GetToAddRemove(toadd, toremove);
		for(size_t pp=0; pp<toadd.size(); ++pp)
			MakePlayerEnterMap((long)toadd[pp].first, toadd[pp].second);
		for(size_t pp=0; pp<toremove.size(); ++pp)
			MakePlayerLeaveMap((long)toremove[pp]);


		// process events
		std::map<Ice::Long, EventsSeq> evts;
		GetEvents(evts);
		ProcessEvents(evts);

		// process guis
		{
			std::map<std::string, boost::shared_ptr<ServerGUIBase> >::iterator itg = _guihandlers.begin();
			std::map<std::string, boost::shared_ptr<ServerGUIBase> >::iterator endg = _guihandlers.end();
			for(; itg != endg; ++itg)
				itg->second->Process(timetodiff);
		}


		// process actors
		{
			std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator ita = _Actors.begin();
			std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator enda = _Actors.end();
			for(; ita != enda; ++ita)
			{
				std::vector<LbaNet::ClientServerEventBasePtr> evta = ita->second->Process(timetodiff, tdiff);
				for(size_t veci=0; veci < evta.size(); ++veci)
					_tosendevts.push_back(evta[veci]);
			}
		}


		// inform triggers
		{
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
			for(; ittr != endtr; ++ittr)
				ittr->second->NewFrame(this, timetodiff, tdiff);
		}



		// send events to all proxies
		if(_tosendevts.size() > 0)
		{
			std::vector<ClientProxyBasePtr> proxies = GetProxies();
			std::vector<ClientProxyBasePtr>::iterator it = proxies.begin();
			std::vector<ClientProxyBasePtr>::iterator end = proxies.end();
			for(; it != end; ++it)
			{
				try
				{
					if(*it)
						(*it)->ServerEvents(_tosendevts);
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

		// refresh lua stuff
		CheckFinishedAsynScripts();


		// wait for a few milliseconds
		{
			long currwtime = SynchronizedTimeHandler::GetCurrentTimeInt();
			long wdiff = (currwtime-waittime);

			if(wdiff < _THREAD_WAIT_TIME_)
			{
				IceUtil::Time t = IceUtil::Time::milliSeconds(_THREAD_WAIT_TIME_-wdiff);
				_monitor.timedWait(t);
			}

			// mesure the time used to do one cycle
			waittime = SynchronizedTimeHandler::GetCurrentTimeInt();
			double tdouble = SynchronizedTimeHandler::GetCurrentTimeDouble();
			tdiff = (float)(tdouble-timetodiff);
			timetodiff = tdouble;
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
process event
***********************************************************/
void MapHandler::ProcessEvent(Ice::Long id, LbaNet::ClientServerEventBasePtr evt)
{
	if(!evt)
		return;

	//check if player is still present on map
	#ifndef _USE_QT_EDITOR_
	{
		boost::shared_ptr<PlayerHandler> pinfo =  GetPlayerInfo((long)id);
		if(!pinfo)
			return;
	}
	#endif


	LbaNet::ClientServerEventBase & obj = *evt;
	const std::type_info& info = typeid(obj);


	// player updated position
	if(info == typeid(LbaNet::PlayerMovedEvent))
	{
		LbaNet::PlayerMovedEvent* castedptr =
			dynamic_cast<LbaNet::PlayerMovedEvent *>(&obj);

		PlayerMoved(id, castedptr->Time, castedptr->info);
		return;
	}


	// UpdateGameGUIEvent
	if(info == typeid(LbaNet::UpdateGameGUIEvent))
	{
		LbaNet::UpdateGameGUIEvent* castedptr =
			dynamic_cast<LbaNet::UpdateGameGUIEvent *>(&obj);

		GuiUpdate(id, castedptr->GUIId, castedptr->Updates);
		return;
	}

	// TeleportEvent
	if(info == typeid(LbaNet::TeleportEvent))
	{
		LbaNet::TeleportEvent* castedptr =
			dynamic_cast<LbaNet::TeleportEvent *>(&obj);

		LbaNet::PlayerPosition newpos = SharedDataHandler::getInstance()->GetTeleportPos(this, (long)id,
																			(long)castedptr->TeleportId,
																			GetPlayerRotation(id));
		TeleportPlayer((long)id, newpos);
		return;
	}

	// ChangeStanceEvent
	if(info == typeid(LbaNet::ChangeStanceEvent))
	{
		LbaNet::ChangeStanceEvent* castedptr =
			dynamic_cast<LbaNet::ChangeStanceEvent *>(&obj);

		ChangeStance(id, castedptr->NewStance);
		return;
	}


	// PressedActionKeyEvent
	if(info == typeid(LbaNet::PressedActionKeyEvent))
	{
		LbaNet::PressedActionKeyEvent* castedptr =
			dynamic_cast<LbaNet::PressedActionKeyEvent *>(&obj);

		ProcessPlayerAction(id, castedptr->ForcedNormalAction);
		return;
	}



	// RefreshObjectRequestEvent
	if(info == typeid(LbaNet::RefreshObjectRequestEvent))
	{
		RefreshPlayerObjects(id);
		return;
	}


	// UpdateStateEvent
	if(info == typeid(LbaNet::UpdateStateEvent))
	{
		LbaNet::UpdateStateEvent* castedptr =
			dynamic_cast<LbaNet::UpdateStateEvent *>(&obj);

		ChangePlayerState(id, castedptr->NewState, castedptr->FallingSize, 5, -1);
		return;
	}

	// RaiseFromDeadEvent
	if(info == typeid(LbaNet::RaiseFromDeadEvent))
	{
		RaiseFromDeadEvent(id);
		return;
	}

	//NewClientExtraInfoEvent
	if(info == typeid(LbaNet::NewClientExtraInfoEvent))
	{
		LbaNet::NewClientExtraInfoEvent* castedptr =
			dynamic_cast<LbaNet::NewClientExtraInfoEvent *>(&obj);

		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
							2, id, new ObjectExtraInfoUpdate(castedptr->ExtraInfo)));
		return;
	}

	//ReadyToPlayEvent
	if(info == typeid(LbaNet::ReadyToPlayEvent))
	{
		SetReady(id);
		return;
	}


	//ScriptExecutionFinishedEvent
	if(info == typeid(LbaNet::ScriptExecutionFinishedEvent))
	{
		LbaNet::ScriptExecutionFinishedEvent* castedptr =
			dynamic_cast<LbaNet::ScriptExecutionFinishedEvent *>(&obj);

		FinishedScript((long)id, castedptr->ScriptName);
		return;
	}


	//editor update event
	#ifdef _USE_QT_EDITOR_
	if(info == typeid(EditorEvent))
	{
		EditorEvent* castedptr =
			static_cast<EditorEvent *>(&obj);

		ProcessEditorUpdate(castedptr->_update);

		return;
	}


	#endif



	//PlayerItemUsedEvent
	if(info == typeid(LbaNet::PlayerItemUsedEvent))
	{
		LbaNet::PlayerItemUsedEvent* castedptr =
			dynamic_cast<LbaNet::PlayerItemUsedEvent *>(&obj);

		PlayerItemUsed((long)id, (long)castedptr->ItemId);
		return;
	}


	//ShowHideEvent
	if(info == typeid(LbaNet::ShowHideEvent))
	{
		LbaNet::ShowHideEvent* castedptr =
			dynamic_cast<LbaNet::ShowHideEvent *>(&obj);

		// only allowed on scripted event
		if(GetPlayerModelInfo(id).State == StScripted)
		{
			_tosendevts.push_back(new LbaNet::ShowHideEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
								2, id, castedptr->Show));
		}
		return;
	}

	//RefreshTpRequestEvent
	if(info == typeid(LbaNet::RefreshTpRequestEvent))
	{
		LbaNet::TeleportsSeq tpseq = SharedDataHandler::getInstance()->GetTpList(this, id);

		EventsSeq toplayer;
		GuiParamsSeq seq;
		seq.push_back(new TeleportGuiParameter(tpseq));
		toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
													"TeleportBox", seq, true, false));

		SendEvents((long)id, toplayer);
		return;
	}

	// UpdatePlayerColorEvent
	if(info == typeid(LbaNet::UpdatePlayerColorEvent))
	{
		LbaNet::UpdatePlayerColorEvent* castedptr =
			dynamic_cast<LbaNet::UpdatePlayerColorEvent *>(&obj);

		ChangePlayerColor((long)id, castedptr->SkinColor, castedptr->EyesColor,
								castedptr->HairColor, -2, -2, -2, -2);
		return;
	}

	// DestroyProjectileEvent
	if(info == typeid(LbaNet::DestroyProjectileEvent))
	{
		LbaNet::DestroyProjectileEvent* castedptr =
			dynamic_cast<LbaNet::DestroyProjectileEvent *>(&obj);

		DestroyProjectile((long)id, (long)castedptr->Id,
							castedptr->TouchedActorType, (long)castedptr->TouchedActorId);
		return;
	}

	// ProjectileHittedActorEvent
	if(info == typeid(LbaNet::ProjectileHittedActorEvent))
	{
		LbaNet::ProjectileHittedActorEvent* castedptr =
			dynamic_cast<LbaNet::ProjectileHittedActorEvent *>(&obj);

		HittedProjectile((long)id, (long)castedptr->Id,
							castedptr->TouchedActorType, (long)castedptr->TouchedActorId);
		return;
	}

	// PlayerHittedContactActorEvent
	if(info == typeid(LbaNet::PlayerHittedContactActorEvent))
	{
		LbaNet::PlayerHittedContactActorEvent* castedptr =
			dynamic_cast<LbaNet::PlayerHittedContactActorEvent *>(&obj);

		PlayerHittedContact((long)id, castedptr->WithWeapon,
							castedptr->TouchedActorType, (long)castedptr->TouchedActorId);
		return;
	}

	// UpdateExtraInfoEvent
	if(info == typeid(UpdateExtraInfoEvent))
	{
		UpdateExtraInfoEvent* castedptr =
			dynamic_cast<UpdateExtraInfoEvent *>(&obj);

		std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find((long)id);
		if(it != _players.end())
			it->second->SetExtraInfo(castedptr->_extrainfo);
		return;
	}
	

	// ghost updated position
	if(info == typeid(LbaNet::GhostMovedEvent))
	{
		LbaNet::GhostMovedEvent* castedptr =
			dynamic_cast<LbaNet::GhostMovedEvent *>(&obj);

		GhostMoved(id, castedptr->GhostId, castedptr->Time, castedptr->info);
		return;
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
			ProcessEvent(it->first, *itevt);
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
add player from external
***********************************************************/
void MapHandler::ExtAddPlayer(Ice::Long PlayerId, boost::shared_ptr<PlayerHandler> pinfo)
{
	IceUtil::Mutex::Lock sync(_mutex_events);
	_toadd.push_back(std::make_pair<Ice::Long, boost::shared_ptr<PlayerHandler> >(PlayerId, pinfo));
}


/***********************************************************
remove player from external
***********************************************************/
void MapHandler::ExtRemovePlayer(Ice::Long PlayerId)
{
	IceUtil::Mutex::Lock sync(_mutex_events);
	_toremove.push_back(PlayerId);
}


/***********************************************************
get player to add and remove
***********************************************************/
void MapHandler::GetToAddRemove(std::vector<std::pair<Ice::Long, boost::shared_ptr<PlayerHandler> > > &toadd,
										std::vector<Ice::Long> &toremove)
{
	IceUtil::Mutex::Lock sync(_mutex_events);
	_toadd.swap(toadd);
	_toremove.swap(toremove);
}


/***********************************************************
player entered map
***********************************************************/
void MapHandler::PlayerEntered(Ice::Long id)
{
	// first give info to the player about current map state
	EventsSeq toplayer;

	std::string clluafile = "Worlds/" + _worldname + "/Lua/";
	clluafile += _mapinfo.Name + "_client.lua";


	// inform client he enter a new map
	toplayer.push_back(new NewMapEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
											_mapinfo.Name, clluafile,
											_mapinfo.AutoCameraType, _mapinfo.Music, _mapinfo.Repeat));

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

	/// send events to player
	SendEvents((long)id, toplayer);


	// then inform all players that player entered
	{
		ObjectPhysicDesc	PhysicDesc;
		PhysicDesc.Pos = GetPlayerPosition(id);
		PhysicDesc.TypePhysO = KynematicAType;
		PhysicDesc.TypeShape = CapsuleShape;
		PhysicDesc.Collidable = true;
		PhysicDesc.Density = 1;

		float sizeX, sizeY, sizeZ;
		GetPlayerPhysicalSize(id, sizeX, sizeY, sizeZ);
		PhysicDesc.SizeX = sizeX;
		PhysicDesc.SizeY = sizeY;

		_tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
													2, id, GetPlayerModelInfo(id), PhysicDesc,
													GetPlayerLifeInfo(id), GetPlayerExtraInfo(id)));
	}


	// inform triggers
	{
		std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
		std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
		for(; ittr != endtr; ++ittr)
			ittr->second->ObjectEnterMap(this, 2, id);
	}


	//check if map is interior
	if(_mapinfo.Type == "interior")
	{
		LbaNet::ModelInfo minfo = GetPlayerModelInfo(id);
		if(minfo.Mode == "Horse" || minfo.Mode == "Dinofly")
			ChangeStance(id, LbaNet::StanceNormal, true);
	}
}

/***********************************************************
player left map
***********************************************************/
void MapHandler::PlayerLeft(Ice::Long id)
{
	// inform triggers
	{
		std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
		std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
		for(; ittr != endtr; ++ittr)
			ittr->second->ObjectLeaveMap(this, 2, id);
	}

	// inform npcs
	{
		std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator ittr = _Actors.begin();
		std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator endtr = _Actors.end();
		for(; ittr != endtr; ++ittr)
			ittr->second->PlayerLeaveMap(id);
	}

	// inform guis
	std::map<std::string, boost::shared_ptr<ServerGUIBase> >::iterator itg = _guihandlers.begin();
	std::map<std::string, boost::shared_ptr<ServerGUIBase> >::iterator endg = _guihandlers.end();
	for(; itg != endg; ++itg)
		itg->second->PlayerLeftMap(id);



	// inform all players that player left
	_tosendevts.push_back(new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
												2, id));

	// destroy projectiles
	DestroyPlayerProjectile(id);

	// remove ephemere item
	RemoveEphemere(id);


	// remove ghosts
	std::map<Ice::Long, std::vector<Ice::Long> >::iterator itghost = _playerghosts.find(id);
	if(itghost != _playerghosts.end())
	{
		std::vector<Ice::Long> ghs = itghost->second;
		for(size_t i=0; i< ghs.size(); ++i)
			RemoveGhost(ghs[i]);
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


	//do an sweep test and check for triggers
	try
	{
		PlayerPosition lastpos = GetPlayerPosition(id);
		lastpos.Y += 0.2f; // small offset to make sure object is inside zone and not online a bit lower
		PlayerPosition currPos = info.CurrentPos;
		currPos.Y += 0.2f;

		ModelState state = GetPlayerModelInfo(id).State;

		// inform triggers
		{
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
			for(; ittr != endtr; ++ittr)
			{
				ittr->second->ObjectMoved(this, 2, id, lastpos, currPos, state);

				//check if player left map
				if(_players.find((long)id) == _players.end())
					throw 1;
			}
		}


		// inform npcs
		{
			std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator ittr = _Actors.begin();
			std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator endtr = _Actors.end();
			for(; ittr != endtr; ++ittr)
				ittr->second->PlayerMoved(id, lastpos, currPos);
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
	catch(int)
	{
		// catch exception when player leave map with trigger
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
					1, itact->first, actinfo.DisplayDesc, actinfo.PhysicDesc, actinfo.LifeInfo,
					xinfo));

				LbaNet::ClientServerEventBasePtr lastevent = itact->second->GetLastEvent();
				if(lastevent)
					toplayer.push_back(lastevent);

				LbaNet::ClientServerEventBasePtr attachevent = itact->second->AttachActorEvent();
				if(attachevent)
					toplayer.push_back(attachevent);

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
				4, itact->first, actinfo.DisplayDesc, actinfo.PhysicDesc, actinfo.LifeInfo ,
				actinfo.ExtraInfo));
		}
	}
	#endif


	// current players in map
	{
		std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itact = _players.begin();
		std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator endact = _players.end();
		for(; itact != endact; ++itact)
		{
			ObjectPhysicDesc	PhysicDesc;
			PhysicDesc.Pos = itact->second->GetPlayerPosition();
			PhysicDesc.TypePhysO = KynematicAType;
			PhysicDesc.TypeShape = CapsuleShape;
			PhysicDesc.Collidable = true;
			PhysicDesc.Density = 1;

			float sizeX, sizeY, sizeZ;
			itact->second->GetPlayerPhysicalSize(sizeX, sizeY, sizeZ);
			PhysicDesc.SizeX = sizeX;
			PhysicDesc.SizeY = sizeY;

			toplayer.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
														2, itact->first,
														itact->second->GetModelInfo(), PhysicDesc,
														itact->second->GetLifeManaInfo(),
														itact->second->GetExtraInfo()));
		}
	}

	// current ghosts in map
	{
		std::map<Ice::Long, GhostInfo>::iterator itgh = _ghosts.begin();
		std::map<Ice::Long, GhostInfo>::iterator endgh = _ghosts.end();
		for(; itgh != endgh; ++itgh)
		{
			std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	
															_Actors.find(itgh->second.ActorId);
			if(itact != _Actors.end())
			{
				ActorObjectInfo ainfo = itact->second->GetActorInfo();
				ainfo.PhysicDesc.Pos = itgh->second.CurrentPos;
				ainfo.PhysicDesc.Collidable = false;
				ainfo.DisplayDesc.ColorA = 0.3f;
				toplayer.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
															3, itgh->first, ainfo.DisplayDesc, 
															ainfo.PhysicDesc,
															ainfo.LifeInfo, ainfo.ExtraInfo));
			}
		}
	}



	toplayer.push_back(new RefreshEndEvent(SynchronizedTimeHandler::GetCurrentTimeDouble()));

	/// send evens to player
	SendEvents((long)id, toplayer);
}



/***********************************************************
change player stance
***********************************************************/
void MapHandler::ChangeStance(Ice::Long id, LbaNet::ModelStance NewStance, bool fromserver, int mountid)
{
	ModelInfo returnmodel;
	if(UpdatePlayerStance(id, NewStance, returnmodel, fromserver, mountid))
	{
		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					2, id, new ModelUpdate(returnmodel, false)));

		// update physical info as well
		float sizeX, sizeY, sizeZ;
		GetPlayerPhysicalSize(id, sizeX, sizeY, sizeZ);
		_tosendevts.push_back(new UpdatePhysicObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
													2, id,
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
					2, id, new ModelUpdate(returnmodel, false)));
}


/***********************************************************
change player outfit
***********************************************************/
void MapHandler::ChangeOutfit(Ice::Long id, const std::string & outfit, long itemid)
{
	ModelInfo returnmodel;
	if(UpdatePlayerOutfit(id, outfit, returnmodel, itemid))
		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					2, id, new ModelUpdate(returnmodel, false)));
}


/***********************************************************
change player state
***********************************************************/
void MapHandler::ChangePlayerState(Ice::Long id, LbaNet::ModelState NewState, float FallingSize,
										int EventType, long ActorId, bool fromserver)
{
	LbaNet::ModelInfo currinfo = GetPlayerModelInfo(id);

	if(currinfo.State != NewState)
	{
		ModelInfo returnmodel;
		if(UpdatePlayerState(id, NewState, returnmodel))
		{
			_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
							2, id, new ModelUpdate(returnmodel, !fromserver)));

			//if hurt by falling
			if(NewState == LbaNet::StHurtFall)
			{
				if(FallingSize > 0)
					DeltaUpdateLife(id, -FallingSize*_mapinfo.HurtFallFactor, 2, -1);
			}

			// record death by drowning
			if(NewState == LbaNet::StDrowning || NewState == LbaNet::StDrowningGas || NewState == LbaNet::StBurning)
			{
				boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
				if(dbh)
					dbh->RecordKill(_worldname, (long)id, 6, -1);
			}

			// record death
			if(NewState == LbaNet::StDying)
			{
				boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
				if(dbh)
					dbh->RecordKill(_worldname, (long)id, EventType, ActorId);
			}


			// execute delayed actions
			std::map<Ice::Long, DelayedAction>::iterator itact = _delayedactions.find(id);
			if(itact != _delayedactions.end())
			{
				DelayedAction daction = itact->second;
				_delayedactions.erase(itact);
				if(daction.action)
					daction.action->Execute(this, 2, id, daction.args);
			}

			// check if use weapon
			if(NewState == LbaNet::StUseWeapon)
			{
				UseWeapon(id);
			}
		}
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
		// if so change state and teleport to raising area
		LbaNet::PlayerPosition pos = GetSpawningPlace(id);
		if(!TeleportPlayer((long)id, pos))
		{
			//only do that if player is not teleported in another map
			LbaNet::PlayerMoveInfo moveinfo;
			moveinfo.ForcedChange = true;
			moveinfo.CurrentPos = pos;
			moveinfo.CurrentSpeedX = 0;
			moveinfo.CurrentSpeedY = 0;
			moveinfo.CurrentSpeedZ = 0;
			moveinfo.CurrentSpeedRotation = 0;
			moveinfo.AnimationIdx = "Stand";

			_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
						2, id, new ModelUpdate(returnmodel, false)));

			_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
									2, id, new ObjectLifeInfoUpdate(GetPlayerLifeInfo(id))));

			_tosendevts.push_back(new LbaNet::PlayerMovedEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
																id, moveinfo, true));
		}
	}
}



/***********************************************************
function used by LUA to add actor
***********************************************************/
void MapHandler::AddActorObject(boost::shared_ptr<ActorHandler> actor)
{
	actor->SetScriptHandler(this);
	_Actors[actor->GetId()] = actor;
}




/***********************************************************
teleport an object
***********************************************************/
void MapHandler::Teleport(int ObjectType, long ObjectId,
							const std::string &NewMapName, long SpawningId,
							float offsetX, float offsetY, float offsetZ)
{
	if(ObjectType == 2)
	{
		LbaNet::PlayerPosition newpos =
			SharedDataHandler::getInstance()->GetSpawnPos(NewMapName, SpawningId, GetPlayerRotation(ObjectId));
		newpos.X += offsetX;
		newpos.Y += offsetY;
		newpos.Z += offsetZ;
		TeleportPlayer(ObjectId, newpos);
	}


	//TODO - other actors
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
																			4, edobjid));

			_tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					4, edobjid, ainfo.DisplayDesc, ainfo.PhysicDesc, ainfo.LifeInfo,
					ainfo.ExtraInfo));
		}
		else
		{
			// object does not exist - add it
			_editorObjects[edobjid] = ainfo;

			_tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
					4, edobjid, ainfo.DisplayDesc, ainfo.PhysicDesc, ainfo.LifeInfo ,
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
	PlayerPosition pos = GetPlayerPosition(id);
	std::string mode = GetPlayerModeString(id);

	// inform triggers
	{
		std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
		std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
		for(; ittr != endtr; ++ittr)
			ittr->second->ObjectAction(this, 2, id, pos, (ForcedNormalAction? "Normal": mode));
	}

	// inform npcs
	{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator ittr = _Actors.begin();
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator endtr = _Actors.end();
	for(; ittr != endtr; ++ittr)
		ittr->second->PlayerAction(id, pos, (ForcedNormalAction? "Normal": mode));
	}
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
		return;
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
		return;
	}

	// map info modified
	if(info == typeid(UpdateEditor_AddOrModMap))
	{
		UpdateEditor_AddOrModMap* castedptr =
			dynamic_cast<UpdateEditor_AddOrModMap *>(&obj);

		_mapinfo = castedptr->_mapinfo;
		return;
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
		return;
	}

	// color change
	if(info == typeid(ChangeColorEvent))
	{
		ChangeColorEvent* castedptr =
			static_cast<ChangeColorEvent *>(&obj);

		ChangePlayerColor(1, castedptr->_skinidx, castedptr->_eyesidx,
								castedptr->_hairidx, castedptr->_outfitidx,
								castedptr->_weaponidx, castedptr->_mountidx,
								castedptr->_mountidx2);
		return;

	}

	// player tp
	if(info == typeid(EditorTeleportPlayerEvent))
	{
		EditorTeleportPlayerEvent* castedptr =
			dynamic_cast<EditorTeleportPlayerEvent *>(&obj);

		TeleportPlayer(castedptr->_playerid, castedptr->_newpos);
		return;
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
	boost::shared_ptr<Spawn> newspan(new Spawn(SpawningId));
	newspan->SetName(spawningname);
	newspan->SetPosX(PosX);
	newspan->SetPosY(PosY);
	newspan->SetPosZ(PosZ);
	newspan->SetRotation(Rotation);
	newspan->SetForceRotation(forcedrotation);
	AddSpawn(newspan);

}
#endif


/***********************************************************
remove a spawning
***********************************************************/
#ifdef _USE_QT_EDITOR_
void MapHandler::Editor_RemoveSpawning(long SpawningId)
{
	long edobjid = SpawningId + 1000000;
	std::map<long, boost::shared_ptr<Spawn> >::iterator it = _spawns.find(SpawningId);
	if(it != _spawns.end())
	{
		// erase from data
		_spawns.erase(it);

		std::map<Ice::Long, ActorObjectInfo >::iterator itm = _editorObjects.find(edobjid);
		if(itm != _editorObjects.end())
		{
			_editorObjects.erase(itm);

			_tosendevts.push_back(new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
																			4, edobjid));
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
																			4, edobjid));
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
	ainfo.LifeInfo.Display = false;
	return ainfo;
}



/***********************************************************
add an actor
***********************************************************/
#ifdef _USE_QT_EDITOR_
void MapHandler::Editor_AddModActor(boost::shared_ptr<ActorHandler> actor)
{
	AddActorObject(actor);


	// update client
	_tosendevts.push_back(new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
																	1, actor->GetId()));



	LbaNet::ObjectExtraInfo xinfo = actor->GetActorInfo().ExtraInfo;
	std::stringstream strs;
	strs<<"Actor_"<<actor->GetId()<<": "<<xinfo.Name;
	xinfo.Name = strs.str();
	xinfo.NameColorR = 0.2;
	xinfo.NameColorG = 0.2;
	xinfo.NameColorB = 1.0;


	_tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
														1, actor->GetId(),
														actor->GetActorInfo().DisplayDesc,
														actor->GetActorInfo().PhysicDesc,
														actor->GetActorInfo().LifeInfo,
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
																		1, Id));
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
		clientid = GetGhostOwnerPlayer((long)ObjectId);
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
					2, clientid, new ModelUpdate(returnmodel, false)));

		toplayer.push_back(new StartClientScriptEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
									ScriptName, InlineFunction));

		/// send evens to player
		SendEvents(clientid, toplayer);
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
	m_luaHandler->ExecuteCustomAction(ObjectType, ObjectId, FunctionName, args, this);
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
		clientid = GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return;


	// send text request to player
	_guihandlers["TextBox"]->ShowGUI(clientid, GetPlayerPosition(clientid),
					boost::shared_ptr<ShowGuiParamBase>(new TextBoxParam(TextId)));
}




/***********************************************************
send error message to client
***********************************************************/
void MapHandler::SendErrorMessage(long clientid, const std::string & messagetitle,
									const std::string &  messagecontent)
{
	if(clientid >= 0)
	{
		LbaNet::EventsSeq toplayer;
		LbaNet::GuiUpdatesSeq paramseq;
		paramseq.push_back(new LbaNet::SystemMessageUpdate(messagetitle, messagecontent));
		toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
												"main", paramseq));

		/// send evens to player
		SendEvents(clientid, toplayer);
	}
}


/***********************************************************
open container on client side
***********************************************************/
void MapHandler::OpenContainer(long clientid, boost::shared_ptr<ContainerSharedInfo> sharedinfo)
{
	if(clientid >= 0)
	{
		ItemsMap inventory = GetInventory(clientid);
		int size = GetInventorySize(clientid);

		// send container to player
		_guihandlers["ContainerBox"]->ShowGUI(clientid, GetPlayerPosition(clientid),
						boost::shared_ptr<ShowGuiParamBase>(new ContainerParam(sharedinfo, inventory, size)));
	}
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
					2, id, new ModelUpdate(returnmodel, false)));

		/// send evens to player
		SendEvents(id, toplayer);
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
									2, clientid, new ObjectLifeInfoUpdate(GetPlayerLifeInfo(clientid))));
			}
			break;
		case 2: // key item - dont do anything
			break;
		case 3: // monture item - ride it
			{
				switch(itinfo.Info.Flag)
				{
					case 1:
						ChangeStance(clientid, LbaNet::StanceProtopack, true, ItemId);
					break;
					case 2:
						if(_mapinfo.Type == "exterior")
							ChangeStance(clientid, LbaNet::StanceHorse, true, ItemId);
					break;
					case 3:
						if(_mapinfo.Type == "exterior")
							ChangeStance(clientid, LbaNet::StanceDinofly, true, ItemId);
					break;
				}
			}
			break;
		case 4: // weapon item - equip it
			ChangeWeapon(clientid, itinfo.Info.StringFlag, (long)itinfo.Info.Id);
			break;
		case 5: // quest item
			break;
		case 6: // other item - dont do anything
			break;
		case 7: // special usage item
			{
				ActionBasePtr actptr = InventoryItemHandler::getInstance()->GetItemAction((long)itinfo.Info.Id);
				if(actptr)
					actptr->Execute(this, 2, clientid, NULL);
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

						/// send evens to player
						SendEvents((long)clientid, toplayer);
					}
				}
			}
			break;
		case 9: // outfit item - equip it
			ChangeOutfit(clientid, itinfo.Info.StringFlag, (long)itinfo.Info.Id);
			break;

		case 10: // container item - open it
			OpenInventoryContainer((long)clientid, (long)itinfo.Info.Id);
		break;
	}

}



/***********************************************************
used by lua to get an actor Position
***********************************************************/
LbaVec3 MapHandler::GetActorPosition(long ActorId)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		return itact->second->GetActorPosition();

	return LbaVec3();
}


/***********************************************************
used by lua to get an actor Rotation
***********************************************************/
float MapHandler::GetActorRotation(long ActorId)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		return itact->second->GetActorRotation();

	return 0;
}


 /***********************************************************
used by lua to get an actor Rotation
***********************************************************/
LbaQuaternion MapHandler::GetActorRotationQuat(long ActorId)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		return itact->second->GetActorRotationQuat();

	return LbaQuaternion();
}



/***********************************************************
 used by lua to update an actor animation
***********************************************************/
void MapHandler::UpdateActorAnimation(long ActorId, const std::string & AnimationString)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
	{
		itact->second->UpdateActorAnimation(AnimationString);
	}
}



/***********************************************************
//! used by lua to update an actor mode
***********************************************************/
void MapHandler::UpdateActorMode(long ActorId, const std::string & Mode)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->UpdateActorMode(Mode, true);
}



/***********************************************************
used by lua to move an actor or player
the actor will move using animation speed
***********************************************************/
void MapHandler::InternalActorStraightWalkTo(int ScriptId, long ActorId, const LbaVec3 &Position, bool asynchronus)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->ActorStraightWalkTo(ScriptId, false, Position.x, Position.y, Position.z);
}



/***********************************************************
//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
***********************************************************/
void MapHandler::InternalActorRotate(int ScriptId, long ActorId, float Angle, float RotationSpeedPerSec,
								bool ManageAnimation, bool asynchronus)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->ActorRotate(ScriptId, false, Angle, RotationSpeedPerSec, ManageAnimation);
}



/***********************************************************
//! used by lua to wait until an actor animation is finished
//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
***********************************************************/
void MapHandler::InternalActorAnimate(int ScriptId, long ActorId, bool AnimationMove, bool asynchronus)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->ActorAnimate(ScriptId, false, AnimationMove);
}



/***********************************************************
//! called when a script has finished
***********************************************************/
void MapHandler::ScriptFinished(int scriptid, const std::string & functioname)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.begin();
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator endact = _Actors.end();
	for(; itact != endact; ++itact)
		itact->second->ScriptFinished(scriptid, functioname);
}




/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will change model
***********************************************************/
void MapHandler::UpdateActorModel(long ActorId, const std::string & Name)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->UpdateActorModel(Name, true);
}



/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will change outfit
***********************************************************/
void MapHandler::UpdateActorOutfit(long ActorId, const std::string & Name)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->UpdateActorOutfit(Name, true);
}



/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will change weapon
***********************************************************/
void MapHandler::UpdateActorWeapon(long ActorId, const std::string & Name)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->UpdateActorWeapon(Name, true);
}



/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will change mode
***********************************************************/
void MapHandler::SendSignalToActor(long ActorId, int Signalnumber)
{
	if(ActorId < 0)
	{
		//inform players
		_tosendevts.push_back(new SendSignalEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
																						Signalnumber));
	}
	else
	{
		std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
		if(itact != _Actors.end())
			itact->second->SendSignal(Signalnumber);
	}
}





/***********************************************************
//! used by lua to move an actor or player
//! the actor will move using animation speed
***********************************************************/
void MapHandler::TeleportActorTo(int ScriptId, long ActorId, const LbaVec3 &Position)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->TeleportTo(Position.x, Position.y, Position.z);
}


/***********************************************************
//! used by lua to move an actor or player
//! the actor change rotation
***********************************************************/
void MapHandler::SetActorRotation(long ActorId, float Angle)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->SetRotation(Angle);
}



/***********************************************************
//! used by lua to move an actor or player
//! the actor show/hide
***********************************************************/
void MapHandler::ActorShowHide(long ActorId, bool Show)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
			itact->second->ShowHide(Show);

}



/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will move using speed
***********************************************************/
void MapHandler::InternalActorGoTo(int ScriptId, long ActorId, const LbaVec3 &Position,
										float Speed, bool asynchronus)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->ActorGoTo(ScriptId, Position.x, Position.y, Position.z, Speed, asynchronus);
}



/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will wait for signal
***********************************************************/
void MapHandler::InternalActorWaitForSignal(int ScriptId, long ActorId, int Signalnumber,
												bool asynchronus)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->ActorWaitForSignal(ScriptId, Signalnumber, asynchronus);
}




/***********************************************************
	//! used by lua to rotate an actor
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
***********************************************************/
void MapHandler::InternalActorRotateFromPoint(int ScriptId, long ActorId, float Angle, const LbaVec3 &Position,
												float RotationSpeedPerSec, bool asynchronus)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->ActorRotateFromPoint(ScriptId, Angle,
													Position.x, Position.y, Position.z, RotationSpeedPerSec,
													asynchronus);
}


/***********************************************************
 used by lua to make actor follow waypoint
***********************************************************/
void MapHandler::InternalActorFollowWaypoint(int ScriptId, long ActorId, int waypointindex1,
												int waypointindex2, bool asynchronus)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
	{
		itact->second->ActorFollowWaypoint(ScriptId, waypointindex1, waypointindex2, asynchronus);
	}
}



/***********************************************************
add/remove item from player inventory
***********************************************************/
void MapHandler::AddOrRemoveItem(long PlayerId, long ItemId, int number, int InformClientType)
{
	LbaNet::ItemList Taken;
	LbaNet::ItemList Put;
	LbaNet::ItemClientInformType informtype = LbaNet::DontInform;
	switch(InformClientType)
	{
		case 1:
			informtype = LbaNet::InformChat;
		break;
		case 2:
			informtype = LbaNet::InformHappy;
		break;
	}

	if(number > 0)
		Put[ItemId] = number;
	else
		Taken[ItemId] = -number;

	UpdateInventory(PlayerId, Taken, Put, informtype);
}




/***********************************************************
	// hurt actor
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
***********************************************************/
void MapHandler::HurtActor(int ObjectType, long ObjectId, float HurtValue, bool HurtLife,
								int PlayedAnimation)
{
	switch(ObjectType)
	{
		case 1: // actor
		{
			//Todo - hurt NPC
		}
		break;

		case 2: // player
		{
			if(HurtLife)
				DeltaUpdateLife(ObjectId, -HurtValue, 1, -1);
			else
				DeltaUpdateMana(ObjectId, -HurtValue);

			if(PlayedAnimation == 1)
				ChangePlayerState(ObjectId, LbaNet::StSmallHurt, 0, 1, -1, true);
			if(PlayedAnimation == 2)
				ChangePlayerState(ObjectId, LbaNet::StMediumHurt, 0, 1, -1, true);
			if(PlayedAnimation == 3)
				ChangePlayerState(ObjectId, LbaNet::StBigHurt, 0, 1, -1, true);
		}
		break;

		case 3: // moved object
		{
			long clientid = GetGhostOwnerPlayer((long)ObjectId);
			HurtActor(2, clientid, HurtValue, HurtLife, PlayedAnimation);
		}
		break;
	}
}


/***********************************************************
	// kill actor
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
***********************************************************/
void MapHandler::KillActor(int ObjectType, long ObjectId)
{
	switch(ObjectType)
	{
		case 1: // actor
		{
			//Todo - kill NPC
		}
		break;

		case 2: // player
		{
			ChangePlayerState(ObjectId, LbaNet::StDying, 0, 1, -1, true);
		}
		break;

		case 3: // moved object
		{
			long clientid = GetGhostOwnerPlayer((long)ObjectId);
			KillActor(2, clientid);
		}
		break;
	}
}



/***********************************************************
delay action execution
***********************************************************/
void MapHandler::DelayActionAfterPlayerChangeState(const DelayedAction &action, LbaNet::ModelState newstate)
{
	ModelInfo returnmodel;
	if(UpdatePlayerState(action.ClientId, newstate, returnmodel))
	{
		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
											2, action.ClientId, new ModelUpdate(returnmodel, false)));

		_delayedactions[action.ClientId] = action;
	}
}



/***********************************************************
switch the model of an actor
***********************************************************/
void MapHandler::SwitchActorModel(long ActorId, const std::string & newmodelname)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->SwitchModel(newmodelname);
}

/***********************************************************
revert the switch the model of an actor
***********************************************************/
void MapHandler::RevertActorModel(long ActorId)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(ActorId);
	if(itact != _Actors.end())
		itact->second->ReverModel();
}


/***********************************************************
open dialog with player
***********************************************************/
void MapHandler::StartDialog(long PlayerId, long NpcId, long npcnametextid, bool simpledialog,
												boost::shared_ptr<DialogPart> dialogroot)
{
	if(PlayerId >= 0)
	{
		// send container to player
		_guihandlers["DialogBox"]->ShowGUI(PlayerId, GetPlayerPosition(PlayerId),
						boost::shared_ptr<ShowGuiParamBase>(new DialogParam(NpcId, npcnametextid,
																	simpledialog, dialogroot)));
	}
}

/***********************************************************
stop target player
***********************************************************/
void MapHandler::NpcUntargetPlayer(long NpcId, long PlayerId)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(NpcId);
	if(itact != _Actors.end())
		itact->second->UntargetPlayer(PlayerId);
}




/***********************************************************
open shop
***********************************************************/
void MapHandler::OpenShop(long PlayerId, const LbaNet::ItemsMap &items,
									const LbaNet::ItemInfo & currencyitem)
{
	if(PlayerId >= 0)
	{
		// send container to player
		_guihandlers["ShopBox"]->ShowGUI(PlayerId, GetPlayerPosition(PlayerId),
						boost::shared_ptr<ShowGuiParamBase>(new ShopParam(items, currencyitem)));
	}
}

/***********************************************************
add spawn
***********************************************************/
void MapHandler::AddSpawn(boost::shared_ptr<Spawn> spawn)
{
	if(spawn)
		_spawns[spawn->GetId()] = spawn;

#ifdef _USE_QT_EDITOR_
	long edobjid = spawn->GetId() + 1000000;

	std::map<Ice::Long, ActorObjectInfo >::iterator itm = _editorObjects.find(edobjid);
	if(itm != _editorObjects.end())
	{
		// object already exist - update position if needed
		itm->second.PhysicDesc.Pos.X = spawn->GetPosX();
		itm->second.PhysicDesc.Pos.Y = spawn->GetPosY();
		itm->second.PhysicDesc.Pos.Z = spawn->GetPosZ();

		std::stringstream strs;
		strs << "Spawn-"<<spawn->GetId()<<": " << spawn->GetName();
		itm->second.ExtraInfo.Name = strs.str();

		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
				4, edobjid, new ObjectExtraInfoUpdate(itm->second.ExtraInfo)));

		_tosendevts.push_back(new UpdatePhysicObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
				4, edobjid, new PositionUpdate(itm->second.PhysicDesc.Pos)));
	}
	else
	{
		// object does not exist - add it
		ActorObjectInfo ainfo = CreateSpawningDisplay(edobjid,
					spawn->GetPosX(), spawn->GetPosY(), spawn->GetPosZ(), spawn->GetName());
		_editorObjects[edobjid] = ainfo;

		_tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
				4, edobjid, ainfo.DisplayDesc, ainfo.PhysicDesc, ainfo.LifeInfo ,
				ainfo.ExtraInfo));
	}
#endif

}

/***********************************************************
get spawn
***********************************************************/
boost::shared_ptr<Spawn> MapHandler::GetSpawn(long id)
{
	if(id < 0)
	{
		if(_spawns.size() > 0)
			return _spawns.begin()->second;
		else
			return boost::shared_ptr<Spawn>();
	}

	std::map<long, boost::shared_ptr<Spawn> >::iterator it = _spawns.find(id);
	if(it != _spawns.end())
		return it->second;

	return boost::shared_ptr<Spawn>();
}

/***********************************************************
get spawn
***********************************************************/
boost::shared_ptr<Spawn> MapHandler::GetSpawn(const std::string SpawnName)
{
	std::map<long, boost::shared_ptr<Spawn> >::iterator it = _spawns.begin();
	std::map<long, boost::shared_ptr<Spawn> >::iterator end = _spawns.end();
	for(;it != end; ++it)
	{
		if(SpawnName == it->second->GetName())
			return it->second;
	}

	return boost::shared_ptr<Spawn>();
}


/***********************************************************
get spawn
***********************************************************/
long MapHandler::GetSpawnId(const std::string SpawnName)
{
	if(SpawnName == "")
	{
		if(_spawns.size() > 0)
			return _spawns.begin()->first;
		else
			return -1;
	}

	std::map<long, boost::shared_ptr<Spawn> >::iterator it = _spawns.begin();
	std::map<long, boost::shared_ptr<Spawn> >::iterator end = _spawns.end();
	for(;it != end; ++it)
	{
		if(SpawnName == it->second->GetName())
			return it->first;
	}

	return -1;
}


/***********************************************************
open mailbox
***********************************************************/
void MapHandler::OpenMailbox(long PlayerId)
{
	if(PlayerId >= 0)
	{
		// send container to player
		_guihandlers["MailBox"]->ShowGUI(PlayerId, GetPlayerPosition(PlayerId),
						boost::shared_ptr<ShowGuiParamBase>());
	}
}

/***********************************************************
use weapon
***********************************************************/
void MapHandler::UseWeapon(Ice::Long PlayerId)
{
	LbaNet::ItemPosInfo weaponinfo = GetCurrentWeaponInfo(PlayerId);
	if(weaponinfo.Info.Id < 0)
		return;

	if(weaponinfo.Info.StringFlag.find("MagicBall") != std::string::npos)//todo - not static -> add projectile to item
	{
		std::string mode = GetPlayerModelInfo(PlayerId).Mode;

		LbaNet::ProjectileInfo newProj;

		newProj.Comeback = true;
		newProj.Power = weaponinfo.Info.Effect;
		newProj.OwnerActorType = 2;
		newProj.OwnerActorId = PlayerId;
		newProj.Id = ((_launchedprojectiles.size() > 0) ? (_launchedprojectiles.rbegin()->first+1): 0);

		newProj.DisplayDesc.TypeRenderer = LbaNet::RenderSphere;
		newProj.DisplayDesc.UseLight = true;
		newProj.DisplayDesc.CastShadow = true;
		newProj.DisplayDesc.RotX=0;
		newProj.DisplayDesc.RotY=0;
		newProj.DisplayDesc.RotZ=0;
		newProj.DisplayDesc.TransX=0;
		newProj.DisplayDesc.TransY=0;
		newProj.DisplayDesc.TransZ=0;
		newProj.DisplayDesc.ScaleX=1;
		newProj.DisplayDesc.ScaleY=1;
		newProj.DisplayDesc.ScaleZ=1;
		newProj.DisplayDesc.ColorR=0.9f;
		newProj.DisplayDesc.ColorG=0.788f;
		newProj.DisplayDesc.ColorB=0.376f;
		newProj.DisplayDesc.ColorA=1.0f;
		newProj.DisplayDesc.State = LbaNet::NoState;


		PlayerPosition playerpos = GetPlayerPosition(PlayerId);

		newProj.OffsetX = 1.0f;
		newProj.OffsetY = 4;
		newProj.Delay = 500;


	    newProj.PhysicDesc.Pos.X = playerpos.X;
	    newProj.PhysicDesc.Pos.Y = playerpos.Y;
	    newProj.PhysicDesc.Pos.Z = playerpos.Z;
		newProj.PhysicDesc.TypeShape = LbaNet::SphereShape;
		newProj.PhysicDesc.TypePhysO = LbaNet::DynamicAType;
		newProj.PhysicDesc.Density = 1.8f;
		newProj.PhysicDesc.Collidable = false;
		newProj.PhysicDesc.SizeX = 0;
		newProj.PhysicDesc.SizeY = 0.2f;
		newProj.PhysicDesc.SizeZ = 0;
		newProj.PhysicDesc.Bounciness = 0.999f;
		newProj.PhysicDesc.StaticFriction = 0.1f;
		newProj.PhysicDesc.DynamicFriction = 0.1f;


		newProj.ManagingClientId = PlayerId;

		newProj.IgnoreGravity = false;

		newProj.ForceX = 0;
		newProj.ForceY = 0;
		newProj.ForceYOnImpact = 0;
		bool launch = false;

		if(mode == "Normal" || mode == "Protopack")
		{
			newProj.ForceX = 0.15f;
			newProj.ForceY = 0.1f;
			newProj.ForceYOnImpact = 0.1f;
			launch = true;
			newProj.LifeTime = 5000;
		}

		if(mode == "Sport")
		{
			newProj.ForceX = 0.17f;
			newProj.ForceY = 0;
			newProj.ForceYOnImpact = 0.05f;
			launch = true;
			newProj.LifeTime = 5000;
		}

		if(mode == "Angry")
		{
			newProj.ForceX = 0.17f;
			newProj.ForceY = 0;
			newProj.ForceYOnImpact = 0.05f;
			launch = true;
			newProj.LifeTime = 5000;
		}

		if(mode == "Discrete")
		{
			newProj.ForceX = 0.06f;
			newProj.ForceY = 0.15f;
			newProj.ForceYOnImpact = 0.1f;
			launch = true;
			newProj.LifeTime = 8000;
		}

		bool nomana = DeltaUpdateMana(PlayerId, -5);
		newProj.NbBounce = (nomana ? 1 : 3);

		if(launch)
		{
			_launchedprojectiles[(long)newProj.Id] = newProj;
			_playerprojectiles[(long)PlayerId].push_back((long)newProj.Id);

			_tosendevts.push_back(new CreateProjectileEvent(
							SynchronizedTimeHandler::GetCurrentTimeDouble(), newProj));
		}

	}


	// todo - other weapons
}




/***********************************************************
destroy projectile
***********************************************************/
void MapHandler::DestroyProjectile(long PlayerId, long ProjectileId, int	TouchedActorType,
										long TouchedActorId)
{
	std::map<long, LbaNet::ProjectileInfo>::iterator itp =	_launchedprojectiles.find(ProjectileId);
	if(itp != _launchedprojectiles.end())
	{
		if(itp->second.ManagingClientId == PlayerId)
		{
			//todo - hurt actors
			if(TouchedActorId >= 0)
				HittedProjectile(PlayerId, ProjectileId, TouchedActorType, TouchedActorId);


			//destroy projectile
			_launchedprojectiles.erase(itp);


			std::map<long, std::vector<long> >::iterator itplayer = _playerprojectiles.find(PlayerId);
			if(itplayer != _playerprojectiles.end())
			{
				std::vector<long>::iterator itpp =
					std::find(itplayer->second.begin(), itplayer->second.end(), ProjectileId);
				if(itpp != itplayer->second.end())
					itplayer->second.erase(itpp);

				if(itplayer->second.size() == 0)
					_playerprojectiles.erase(itplayer);
			}

			_tosendevts.push_back(new DestroyProjectileEvent(
							SynchronizedTimeHandler::GetCurrentTimeDouble(), ProjectileId,
															TouchedActorType, TouchedActorId));
		}

	}
}

/***********************************************************
hitted projectile
***********************************************************/
void MapHandler::HittedProjectile(long PlayerId, long ProjectileId, int	TouchedActorType,
									long TouchedActorId)
{
	std::map<long, LbaNet::ProjectileInfo>::iterator itp =	_launchedprojectiles.find(ProjectileId);
	if(itp != _launchedprojectiles.end())
	{
		if(itp->second.ManagingClientId == PlayerId)
		{
			if(TouchedActorType == 1)
			{
				//todo - hurt actors
			}

			if(TouchedActorType == 2)
			{
				PlayerHitPlayer(PlayerId, TouchedActorId, itp->second.Power);
			}
		}

	}
}


/***********************************************************
HittedProjectile
***********************************************************/
void MapHandler::PlayerHittedContact(long PlayerId, bool WithWeapon, int	TouchedActorType,
										long TouchedActorId)
{
	float power = GetPlayerHitContactPower(PlayerId, WithWeapon);
	if(power > 0)
	{
		if(TouchedActorType == 1)
		{
			//todo - hurt actors
		}

		if(TouchedActorType == 2)
		{
			PlayerHitPlayer(PlayerId, TouchedActorId, power);
		}
	}
}


/***********************************************************
playr hit player
***********************************************************/
void MapHandler::PlayerHitPlayer(long hitterId, long hittedid, float hitpower)
{
	// reduce it by armor
	float armor = GetPlayerArmor(hittedid);
	float hitlife = armor - hitpower;
	if(hitlife < 0)
	{
		// hurt the player
		if(!DeltaUpdateLife(hittedid, hitlife, 4, hitterId))
		{
			//only play hurt if not dead
			if(hitlife < -19.9)
				ChangePlayerState(hittedid, LbaNet::StBigHurt, 0, 1, -1, true);
			else if(hitlife < -9.9)
				ChangePlayerState(hittedid, LbaNet::StMediumHurt, 0, 1, -1, true);
			else
				ChangePlayerState(hittedid, LbaNet::StSmallHurt, 0, 1, -1, true);
		}
	}
}


/***********************************************************
destroy projectile
***********************************************************/
void MapHandler::DestroyPlayerProjectile(Ice::Long PlayerId)
{
	std::map<long, std::vector<long> >::iterator itplayer = _playerprojectiles.find((long)PlayerId);
	if(itplayer != _playerprojectiles.end())
	{
		std::vector<long> projs = itplayer->second;
		for(size_t i=0; i< projs.size(); ++i)
			DestroyProjectile((long)PlayerId, projs[i], -1, -1);
	}
}



/***********************************************************
get actor info
***********************************************************/
boost::shared_ptr<DynamicObject> MapHandler::GetActor(int ObjectType, long ObjectId)
{
	if(ObjectType == 1)
	{
		std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.find(ObjectId);
		if(it != _Actors.end())
			return it->second->GetActor();
	}

	return boost::shared_ptr<DynamicObject>();
}



/***********************************************************
AttachActor
***********************************************************/
void MapHandler::AttachActor(long ActorId, int AttachedObjectType, long AttachedObjectId)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.find(ActorId);
	if(it != _Actors.end())
		return it->second->AttachActor(AttachedObjectType, AttachedObjectId);
}

/***********************************************************
DettachActor
***********************************************************/
void MapHandler::DettachActor(long ActorId, long AttachedObjectId)
{
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator it = _Actors.find(ActorId);
	if(it != _Actors.end())
		return it->second->DettachActor(AttachedObjectId);
}








/***********************************************************
get player proxy
***********************************************************/
ClientProxyBasePtr MapHandler::GetProxy(Ice::Long clientid)
{
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
	std::vector<ClientProxyBasePtr> proxies;
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.begin();
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator end = _players.end();
	for(; it != end; ++it)
		proxies.push_back(it->second->GetProxy());

	return proxies;
}


/***********************************************************
client open container
***********************************************************/
void MapHandler::OpenInventoryContainer(long clientid, long itemid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		it->second->OpenInventoryContainer(itemid);
}


/***********************************************************
return inventory size
***********************************************************/
int MapHandler::GetInventorySize(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetInventorySize();

	return 0;
}

/***********************************************************
return inventory content
***********************************************************/
ItemsMap MapHandler::GetInventory(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetInventory();

	return ItemsMap();
}



/***********************************************************
return shortcuts
***********************************************************/
ShortcutsSeq MapHandler::GetShorcuts(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetShorcuts();

	return ShortcutsSeq();
}

/***********************************************************
get player position
***********************************************************/
PlayerPosition MapHandler::GetPlayerPosition(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetPlayerPosition();

	return PlayerPosition();
}

/***********************************************************
get player rotation
***********************************************************/
float MapHandler::GetPlayerRotation(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetPlayerRotation();

	return 0;
}




/***********************************************************
get player mode string
***********************************************************/
std::string MapHandler::GetPlayerModeString(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetPlayerModeString();

	return "";
}



/***********************************************************
get player life info
***********************************************************/
LbaNet::LifeManaInfo MapHandler::GetPlayerLifeInfo(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetLifeManaInfo();

	return LbaNet::LifeManaInfo();
}


/***********************************************************
get player extra info
***********************************************************/
LbaNet::ObjectExtraInfo MapHandler::GetPlayerExtraInfo(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetExtraInfo();

	return LbaNet::ObjectExtraInfo();
}


/***********************************************************
get player model info
***********************************************************/
LbaNet::ModelInfo MapHandler::GetPlayerModelInfo(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetModelInfo();

	return LbaNet::ModelInfo();
}




/***********************************************************
get player physcial size
***********************************************************/
void MapHandler::GetPlayerPhysicalSize(Ice::Long clientid, float &sX, float &sY, float &sZ)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		it->second->GetPlayerPhysicalSize(sX, sY, sZ);
}


/***********************************************************
//!  get the place to respawn in case of death
***********************************************************/
LbaNet::PlayerPosition MapHandler::GetSpawningPlace(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->GetSpawningPlace();

	return LbaNet::PlayerPosition();
}




/***********************************************************
update player position
***********************************************************/
bool MapHandler::UpdatePlayerPosition(Ice::Long clientid, const PlayerPosition & pos, bool teleport)
{
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
												ModelInfo & returnmodel, bool fromserver,
												int mountid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->UpdatePlayerStance(NewStance, returnmodel, fromserver, mountid);

	return false;
}


/***********************************************************
//!  update player state
//! return true if state has been updated
***********************************************************/
bool MapHandler::UpdatePlayerState(Ice::Long clientid, LbaNet::ModelState NewState,
												ModelInfo & returnmodel )
{
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
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		it->second->SavePlayerState();
}


/***********************************************************
//!  restore player state
***********************************************************/
bool MapHandler::RestorePlayerState(Ice::Long clientid, ModelInfo & returnmodel)
{
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
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		it->second->SetReady();
}


/***********************************************************
ask if player ready to play
***********************************************************/
bool MapHandler::IsReady(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator it = _players.find(clientid);
	if(it != _players.end())
		return it->second->IsReady();

	return false;
}




/***********************************************************
get info about an item
***********************************************************/
LbaNet::ItemPosInfo MapHandler::GetItemInfo(Ice::Long clientid, long ItemId)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		return itplayer->second->GetItemInfo(ItemId);

	LbaNet::ItemPosInfo res;
	res.Info.Id = -1;
	return res;
}


/***********************************************************
get info about an item
***********************************************************/
LbaNet::ItemPosInfo MapHandler::GetCurrentWeaponInfo(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		return itplayer->second->GetCurrentWeaponInfo();

	LbaNet::ItemPosInfo res;
	res.Info.Id = -1;
	return res;
}


/***********************************************************
get player hit contact power
***********************************************************/
float MapHandler::GetPlayerHitContactPower(Ice::Long clientid, bool withweapon)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		return itplayer->second->GetHitContactPower(withweapon);

	return -1;
}


/***********************************************************
get player armor
***********************************************************/
float MapHandler::GetPlayerArmor(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		return itplayer->second->GetArmor();

	return 0;
}


/***********************************************************
item consumed
***********************************************************/
bool MapHandler::PlayerConsumeItem(Ice::Long clientid, long ItemId)
{
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
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		itplayer->second->RemoveEphemere();
}



/***********************************************************
//! update player life
//! return true if no life
***********************************************************/
bool MapHandler::DeltaUpdateLife(Ice::Long clientid, float update, int updatetype, long actorid)
{
	bool res = false;

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
	{
		res = itplayer->second->DeltaUpdateLife(update);

		// give life update to everybody
		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
								2, clientid, new ObjectLifeInfoUpdate(GetPlayerLifeInfo(clientid))));
	}


	if(res)// die
		ChangePlayerState(clientid, LbaNet::StDying, 0, updatetype, actorid, true);

	return res;
}


/***********************************************************
//! update player mana
//! return true if no mana
***********************************************************/
bool MapHandler::DeltaUpdateMana(Ice::Long clientid, float update)
{
	bool res = false;

	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
	{
		res = itplayer->second->DeltaUpdateMana(update);

		// give life update to everybody
		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
								2, clientid, new ObjectLifeInfoUpdate(GetPlayerLifeInfo(clientid))));
	}

	return res;
}

/***********************************************************
//! return number of player on map
***********************************************************/
int MapHandler::GetNbPlayers()
{
	return (int)_players.size();
}


/***********************************************************
update player inventory
***********************************************************/
void MapHandler::UpdateInventory(Ice::Long clientid, LbaNet::ItemList Taken, LbaNet::ItemList Put,
										LbaNet::ItemClientInformType informtype)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		itplayer->second->UpdateInventory(Taken, Put, informtype);
}



/***********************************************************
start quest
***********************************************************/
void MapHandler::StartQuest(long PlayerId, long Questid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(PlayerId);
	if(itplayer != _players.end())
	{
		if(!itplayer->second->QuestStarted(Questid) && !itplayer->second->QuestFinished(Questid))
		{
			if(QuestHandler::getInstance()->StartQuest(this, Questid, PlayerId))
				itplayer->second->StartQuest(Questid);
		}
	}
}

/***********************************************************
end quest
***********************************************************/
void MapHandler::TriggerQuestEnd(long PlayerId, long Questid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(PlayerId);
	if(itplayer != _players.end())
	{
		if(itplayer->second->QuestStarted(Questid))
		{
			if(QuestHandler::getInstance()->QuestFinished(this, Questid, PlayerId))
				itplayer->second->FinishQuest(Questid);
		}
	}
}



/***********************************************************
condition
***********************************************************/
bool MapHandler::QuestStarted(long PlayerId, long Questid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(PlayerId);
	if(itplayer != _players.end())
		return itplayer->second->QuestStarted(Questid);

	return false;
}

/***********************************************************
condition
***********************************************************/
bool MapHandler::QuestFinished(long PlayerId, long Questid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(PlayerId);
	if(itplayer != _players.end())
		return itplayer->second->QuestFinished(Questid);

	return false;
}

/***********************************************************
condition
***********************************************************/
bool MapHandler::ChapterStarted(long PlayerId, int Chapter)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(PlayerId);
	if(itplayer != _players.end())
		return (itplayer->second->GetCurrentChapter() >= Chapter);

	return false;
}


/***********************************************************
//! change player color
***********************************************************/
void MapHandler::ChangePlayerColor(long clientid, int skinidx, int eyesidx, int hairidx, int outfitidx,
								   int weaponidx, int mountidx, int mountidx2)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
	{
		itplayer->second->ChangePlayerColor(skinidx, eyesidx, hairidx, outfitidx, weaponidx, mountidx, mountidx2);

		_tosendevts.push_back(new UpdateDisplayObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
						2, clientid, new ModelUpdate(itplayer->second->GetModelInfo(), false)));
	}
}



/***********************************************************
get client name
***********************************************************/
std::string MapHandler::GetName(Ice::Long clientid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		return itplayer->second->GetExtraInfo().Name;


	return "";
}


/***********************************************************
player switch item
***********************************************************/
void MapHandler::PlayerSwitchItem(Ice::Long clientid, long ItemId, int NewPosition)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		itplayer->second->SwitchItem(ItemId, NewPosition);

}

/***********************************************************
Player Create Letter
***********************************************************/
void MapHandler::PlayerCreateLetter(Ice::Long clientid, const std::string & subject,
											const std::string & message)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		itplayer->second->CreateLetter(subject, message);
}

/***********************************************************
Player Destroy Item
***********************************************************/
void MapHandler::PlayerDestroyItem(Ice::Long clientid, long ItemId)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		itplayer->second->DestroyItem(ItemId);
}


/***********************************************************
get player inventory
***********************************************************/
LbaNet::ItemsMap MapHandler::GetInventory(Ice::Long clientid, int & inventorysize)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
	{
		inventorysize = itplayer->second->GetInventorySize();
		return itplayer->second->GetInventory();
	}

	return LbaNet::ItemsMap();
}

/***********************************************************
get player inventory
***********************************************************/
int MapHandler::GetInventoryItemCount(long PlayerId, long Itemid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(PlayerId);
	if(itplayer != _players.end())
	{
		const LbaNet::ItemsMap &invmap = itplayer->second->GetInventory();
		LbaNet::ItemsMap::const_iterator itm = invmap.find(Itemid);
		if(itm != invmap.end())
			return itm->second.Count;
	}

	return 0;
}




/***********************************************************
update player shortcut
***********************************************************/
void MapHandler::UpdatePlayerShortcut(Ice::Long clientid, int Position, long ItemId)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(clientid);
	if(itplayer != _players.end())
		itplayer->second->UpdateShortcut(Position, ItemId);
}




/***********************************************************
//! send event to player
***********************************************************/
void MapHandler::SendEvents(long PlayerId, const LbaNet::EventsSeq & evts)
{
	ClientProxyBasePtr proxy = GetProxy(PlayerId);
	if(proxy)
	{
		try
		{
			proxy->ServerEvents(evts);
		}
		catch(const IceUtil::Exception& ex)
		{
			std::cout<<"Exception in sending events to client: "<<ex.what()<<std::endl;
		}
		catch(...)
		{
			std::cout<<"Unknown exception in sending events to client. "<<std::endl;
		}
	}
}




/***********************************************************
//! teleport a player
//! return true if player left the map
***********************************************************/
bool MapHandler::TeleportPlayer(long playerid, const LbaNet::PlayerPosition &newpos)
{
	if(newpos.MapName == "")	//something wrong happened
		return false;

	//! cehck if already left
	 boost::shared_ptr<PlayerHandler> pinfo = GetPlayerInfo(playerid);
	 if(!pinfo)
		 return true;

	if(newpos.MapName != _mapinfo.Name)
	{
		//! leave current map
		MakePlayerLeaveMap(playerid);

		//! teleport player to other map
		SharedDataHandler::getInstance()->TeleportPlayer(playerid, pinfo, newpos);

		return true;
	}
	else
	{
		// update player position
		if(UpdatePlayerPosition(playerid, newpos, true))
		{
			// inform all of player move
			LbaNet::PlayerMoveInfo moveinfo;
			moveinfo.ForcedChange = true;
			moveinfo.CurrentPos = newpos;
			moveinfo.CurrentSpeedX = 0;
			moveinfo.CurrentSpeedY = 0;
			moveinfo.CurrentSpeedZ = 0;
			moveinfo.CurrentSpeedRotation = 0;
			_tosendevts.push_back(new LbaNet::PlayerMovedEvent(
													SynchronizedTimeHandler::GetCurrentTimeDouble(),
													playerid, moveinfo, true));
		}
		return false;
	}
}


/***********************************************************
//! make player enter the map
***********************************************************/
void MapHandler::MakePlayerEnterMap(long playerid, boost::shared_ptr<PlayerHandler> info)
{
	_players[playerid] = info;
	PlayerEntered(playerid);
}

/***********************************************************
//! make player leave the map
***********************************************************/
void MapHandler::MakePlayerLeaveMap(long playerid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(playerid);
	if(itplayer != _players.end())
	{
		// inform everybody
		PlayerLeft(playerid);

		//save info to DB
		itplayer->second->SaveCurrentInfo();

		// remove from map
		_players.erase(itplayer);
	}
}

/***********************************************************
return player info
***********************************************************/
boost::shared_ptr<PlayerHandler> MapHandler::GetPlayerInfo(long playerid)
{
	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >::iterator itplayer = _players.find(playerid);
	if(itplayer != _players.end())
		return itplayer->second;

	return boost::shared_ptr<PlayerHandler>();
}



/***********************************************************
called when a player moved
***********************************************************/
void MapHandler::GhostMoved(Ice::Long id, Ice::Long ghostid, 
							double time, const LbaNet::PlayerMoveInfo &info)
{
	// check if player ready to play - else do nothing as this may be old move form other maps
	if(!IsReady(id))
		return;

	long gid = -1;

	//check if ghost already exist - if not create it
	{
		std::map<std::pair<Ice::Long, Ice::Long>, Ice::Long>::iterator itg = 
			_revertghosts.find(std::make_pair<Ice::Long, Ice::Long>(id,ghostid));

		if(itg == _revertghosts.end())
			gid = AddGhost(id, ghostid, info.CurrentPos);
		else
			gid = itg->second;
	}

	//do a sweep test and check for triggers
	try
	{
		PlayerPosition lastpos = GetGhostPosition(gid);
		lastpos.Y += 0.2f; // small offset to make sure object is inside zone and not online a bit lower
		PlayerPosition currPos = info.CurrentPos;
		currPos.Y += 0.2f;

		// inform triggers
		{
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
			for(; ittr != endtr; ++ittr)
			{
				ittr->second->ObjectMoved(this, 3, gid, lastpos, currPos, LbaNet::NoState);

				//check if player left map
				if(_players.find((long)id) == _players.end())
					throw 1;
			}
		}


		// update player position
		PlayerPosition pos(info.CurrentPos);
		pos.MapName = _mapinfo.Name;

		// check if position could be updated
		if(UpdateGhostPosition(gid, pos))
		{
			if(info.ForcedChange)
			{
				// inform all of player move
				_tosendevts.push_back(new LbaNet::GhostMovedEvent(time, gid, info));
			}
		}
	}
	catch(int)
	{
		// catch exception when player leave map with trigger
	}
}



/***********************************************************
add a new ghost
***********************************************************/
Ice::Long MapHandler::AddGhost(Ice::Long playerid, Ice::Long actorid, const LbaNet::PlayerPosition &info)
{
	// generate uid
	Ice::Long gid = 0;
	if(_ghosts.size() > 0)
		gid = _ghosts.rbegin()->first + 1;


	// add to maps
	_revertghosts[std::make_pair<Ice::Long, Ice::Long>(playerid, actorid)] = gid;
	_playerghosts[playerid].push_back(gid);

	GhostInfo ginfo;
	ginfo.Id = gid;
	ginfo.OwnerPlayerId = playerid;
	ginfo.ActorId = actorid;
	ginfo.CurrentPos = info;
	_ghosts[ginfo.Id] = ginfo;


	//inform triggers
	{
		std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
		std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
		for(; ittr != endtr; ++ittr)			
			ittr->second->ObjectEnterMap(this, 3, gid);
	}

	// inform players
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator itact =	_Actors.find(actorid);
	if(itact != _Actors.end())
	{
		ActorObjectInfo ainfo = itact->second->GetActorInfo();
		ainfo.PhysicDesc.Pos = info;
		ainfo.PhysicDesc.Collidable = false;
		ainfo.DisplayDesc.ColorA = 0.3f;
		_tosendevts.push_back(new AddObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
													3, gid, ainfo.DisplayDesc, ainfo.PhysicDesc,
													ainfo.LifeInfo, ainfo.ExtraInfo));
	}


	return gid;
}


/***********************************************************
remove a  ghost
***********************************************************/
void MapHandler::RemoveGhost(Ice::Long ghostid)
{
	std::map<Ice::Long, GhostInfo>::iterator it=_ghosts.find(ghostid);
	if(it != _ghosts.end())
	{
		// inform players
		_tosendevts.push_back(new RemoveObjectEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
														3, ghostid));


		//inform triggers
		{
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator ittr = _triggers.begin();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator endtr = _triggers.end();
			for(; ittr != endtr; ++ittr)			
				ittr->second->ObjectLeaveMap(this, 3, ghostid);
		}

		//remove from maps
		std::map<std::pair<Ice::Long, Ice::Long>, Ice::Long>::iterator itrev = 
								_revertghosts.find(std::make_pair<Ice::Long, Ice::Long>
								(it->second.OwnerPlayerId, it->second.ActorId));
		if(itrev != _revertghosts.end())
			_revertghosts.erase(itrev);

		std::map<Ice::Long, std::vector<Ice::Long> >::iterator itp = _playerghosts.find(it->second.OwnerPlayerId);
		if(itp != _playerghosts.end())
		{
			std::vector<Ice::Long>::iterator itv = std::find(itp->second.begin(), itp->second.end(), ghostid);
			if(itv != itp->second.end())
				itp->second.erase(itv);

			if(itp->second.size() == 0)
				_playerghosts.erase(itp);
		}

		_ghosts.erase(it);
	}
}


/***********************************************************
get ghost position
***********************************************************/
LbaNet::PlayerPosition  MapHandler::GetGhostPosition(Ice::Long ghostid)
{
	std::map<Ice::Long, GhostInfo>::iterator it=_ghosts.find(ghostid);
	if(it != _ghosts.end())
		return it->second.CurrentPos;

	return LbaNet::PlayerPosition();

}


/***********************************************************
update ghost position
***********************************************************/
bool MapHandler::UpdateGhostPosition(Ice::Long ghostid, const LbaNet::PlayerPosition &info)
{
	std::map<Ice::Long, GhostInfo>::iterator it=_ghosts.find(ghostid);
	if(it != _ghosts.end())
	{
		it->second.CurrentPos = info;
		return true;
	}

	return false;
}



/***********************************************************
return ghost owner player
***********************************************************/
long MapHandler::GetGhostOwnerPlayer(long ghostid)
{
	std::map<Ice::Long, GhostInfo>::iterator it=_ghosts.find(ghostid);
	if(it != _ghosts.end())
		return ((long)it->second.OwnerPlayerId);

	return -1;
}
