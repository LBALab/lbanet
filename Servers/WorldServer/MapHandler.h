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

#ifndef _MAP_HANDLER_H__
#define _MAP_HANDLER_H__


#include <ClientInterface.h>
#include <IceUtil/Mutex.h>
#include <boost/shared_ptr.hpp>

#include "RunnableThread.h"
#include "ServerGuiBase.h"
#include "ClientProxyHandler.h"
#include "ActorHandler.h"
#include "ServerLuaHandler.h"
#include "Triggers.h"
#include "ScriptEnvironmentBase.h"

using namespace LbaNet;
class PlayerHandler;
class EditorUpdateBase;


//! used to send event to 1 client
class EventsSender : public IceUtil::Thread
{
public:
	//! constructor
	EventsSender(EventsSeq & events, ClientProxyBasePtr proxy);

	// running function of the thread
	virtual void run();

private:
	EventsSeq				_events;
	ClientProxyBasePtr		_proxy;
};


//! used to send event to all clients
class EventsSenderToAll : public IceUtil::Thread
{
public:
	//! constructor
	EventsSenderToAll(EventsSeq & events, std::vector<ClientProxyBasePtr> &proxies);

	// running function of the thread
	virtual void run();

private:
	EventsSeq									_events;
	std::vector<ClientProxyBasePtr>		_proxies;
};



class NoPlayerException : public std::exception
{
public:

	NoPlayerException()
	{}

	virtual ~NoPlayerException()  throw ()
	{}

	virtual const char* what() const throw ()
	{ return ""; }
};



//! take care of a map of the world
class MapHandler : public Runnable, public ScriptEnvironmentBase
{
public:
	//! constructor
	MapHandler(const MapInfo & mapinfo, 
					const std::string & mapluafilename,
					const std::string & globalluafilname);

	//! desructor
	~MapHandler(void);

	//! start run function
	void StartThread();

	// running function of the thread
	virtual void run();


	//! add events
	void AddEvents(Ice::Long clientid, const EventsSeq &evts);

	//! add 1 event
	void AddEvent(Ice::Long clientid, ClientServerEventBasePtr evt);

	// get all events for a specific map
	void GetEvents(std::map<Ice::Long, EventsSeq> & evts);

	// add player proxy
	void AddPlayer(Ice::Long clientid, boost::shared_ptr<PlayerHandler> player);

	// remove player proxy
	void RemovePlayer(Ice::Long clientid);

	// get player proxy
	ClientProxyBasePtr GetProxy(Ice::Long clientid);

	// get players proxies
	std::vector<ClientProxyBasePtr> GetProxies();


	// function used by LUA to add actor
	virtual void AddActorObject(boost::shared_ptr<ActorHandler> actor);
					
	// add a trigger of moving type to the map
	virtual void AddTrigger(boost::shared_ptr<TriggerBase> trigger);
					
	// add an action
	virtual void AddAction(boost::shared_ptr<ActionBase> action);

	// teleport an object
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Teleport(int ObjectType, long ObjectId,
						const std::string &NewMapName, 
						long SpawningId,
						float offsetX, float offsetY, float offsetZ);


	// get the action correspondant to the id
	virtual boost::shared_ptr<ActionBase> GetAction(long actionid);

protected:
	// process events
	void ProcessEvents(const std::map<Ice::Long, EventsSeq> & evts);

	// player entered map
	void PlayerEntered(Ice::Long id);

	// player left map
	void PlayerLeft(Ice::Long id);


	// gui update from a client
	void GuiUpdate(Ice::Long id, const std::string guidi, GuiUpdatesSeq	Updates);


	//! called when a player moved
	void PlayerMoved(Ice::Long id, double time, const LbaNet::PlayerMoveInfo &info);


	//! refresh player objects
	void RefreshPlayerObjects(Ice::Long id);


	//! change player stance
	void ChangeStance(Ice::Long id, LbaNet::ModelStance NewStanceId);

	//! change player state
	void ChangePlayerState(Ice::Long id, LbaNet::ModelState NewState, float FallingSize);

	//! a player is raised from dead
	void RaiseFromDeadEvent(Ice::Long id);

	//! process player action
	void ProcessPlayerAction(Ice::Long id, bool ForcedNormalAction);



	// return inventory size
	int GetInventorySize(Ice::Long clientid);

	// return inventory content
	ItemsMap GetInventory(Ice::Long clientid);

	// return shortcuts
	ShortcutsSeq GetShorcuts(Ice::Long clientid);

	//!  get player position
	PlayerPosition GetPlayerPosition(Ice::Long clientid);

	//! get player mode string
	std::string GetPlayerModeString(Ice::Long clientid);

	//! get player life info
	LbaNet::LifeManaInfo GetPlayerLifeInfo(Ice::Long clientid);

	//! get player extra info
	LbaNet::ObjectExtraInfo GetPlayerExtraInfo(Ice::Long clientid);

	//! get player model info
	LbaNet::ModelInfo  GetPlayerModelInfo(Ice::Long clientid);

	//! get the place to respawn in case of death
	LbaNet::PlayerPosition GetSpawningPlace(Ice::Long clientid);

	//! set player ready to play
	void SetReady(Ice::Long clientid);

	//! ask if player ready to play
	bool IsReady(Ice::Long clientid);


	//!  update player position
	bool UpdatePlayerPosition(Ice::Long clientid, const PlayerPosition & pos);

	//!  update player stance
	//! return true if state has been updated
	bool UpdatePlayerStance(Ice::Long clientid, LbaNet::ModelStance NewStance,
									ModelInfo & returnmodel );


	//!  update player state
	//! return true if state has been updated
	bool UpdatePlayerState(Ice::Long clientid, LbaNet::ModelState NewState,
									ModelInfo & returnmodel );

	//!  raised player from dead
	//! return true if raised
	bool RaiseFromDead(Ice::Long clientid, ModelInfo & returnmodel);


	//! process editor events
	#ifdef _USE_QT_EDITOR_
	void ProcessEditorUpdate(LbaNet::EditorUpdateBasePtr update);


	//! add a spawning to the map
	void Editor_AddOrModSpawning(	long SpawningId, const std::string &spawningname,
									float PosX, float PosY, float PosZ,
									float Rotation, bool forcedrotation);

	//! remove a spawning
	void Editor_RemoveSpawning(long SpawningId);

	//! remove an action
	void Editor_RemoveAction(long ActionId);

	//! remove an trigger
	void Editor_RemoveTrigger(long TriggerId);

	//! add an actor
	void Editor_AddModActor(boost::shared_ptr<ActorHandler> actor);

	//! remove an actor
	void Editor_RemoveActor(long Id);
	#endif
	
	//! create display object for spawning
	ActorObjectInfo CreateSpawningDisplay(long id, float PosX, float PosY, float PosZ, 
											const std::string & name);

private:
	// threading and mutex stuff
	IceUtil::Monitor<IceUtil::Mutex>							_monitor;
	IceUtil::Mutex												_mutex_events;
	IceUtil::Mutex												_mutex_proxies;

	bool														_Trunning;
	IceUtil::ThreadControl										_threadcontrol;
	IceUtil::ThreadPtr											_thread;

	MapInfo														_mapinfo;
	std::vector<Ice::Long>										_currentplayers;


	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >		_players;
	std::map<Ice::Long, EventsSeq>								_events;

	std::map<std::string, boost::shared_ptr<ServerGUIBase> >	_guihandlers;

	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >		_Actors;

	#ifdef _USE_QT_EDITOR_
	std::map<Ice::Long, ActorObjectInfo >						_editorObjects;
	#endif

	EventsSeq													_tosendevts;

	ServerLuaHandler											_luaH;

	std::map<long, boost::shared_ptr<TriggerBase> >				_triggers;
	std::map<long, boost::shared_ptr<ActionBase> >				_actions;
};


#endif