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
#include "DelayedExecutionHandler.h"

using namespace LbaNet;
class PlayerHandler;
class EditorUpdateBase;
class Spawn;

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
class MapHandler : public Runnable, public ScriptEnvironmentBase, public DelayedExecutionHandler
{
public:
	//! constructor
	MapHandler(const MapInfo & mapinfo, 
					const std::string & mapluafilename,
					const std::string & customluafilename);

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
					
	// add a trigger of moving type to the map
	virtual void AddSpawn(boost::shared_ptr<Spawn> spawn);


	// teleport an object
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Teleport(int ObjectType, long ObjectId,
						const std::string &NewMapName, 
						long SpawningId,
						float offsetX, float offsetY, float offsetZ);


	// execute client script - does not work on npc objects
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ExecuteClientScript(int ObjectType, long ObjectId,
										const std::string & ScriptName,
										bool InlineFunction);


	// execute custom lua function
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ExecuteCustomAction(int ObjectType, long ObjectId,
										const std::string & FunctionName,
										ActionArgumentBase * args);



	// display text to client window
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void DisplayTxtAction(int ObjectType, long ObjectId,
										long TextId);

	// send error message to client
	virtual void SendErrorMessage(long clientid, const std::string & messagetitle, 
									const std::string &  messagecontent);

	// open container on client side
	virtual void OpenContainer(long clientid, boost::shared_ptr<ContainerSharedInfo> sharedinfo);



	//! used by lua to get an actor Position
	virtual LbaVec3 GetActorPosition(long ActorId);

	//! used by lua to get an actor Rotation
	virtual float GetActorRotation(long ActorId);

	//! used by lua to get an actor Rotation
	//! if id < 1 then it get player position
	virtual LbaQuaternion GetActorRotationQuat(long ActorId);

	//! used by lua to update an actor animation
	virtual void UpdateActorAnimation(long ActorId, const std::string & AnimationString);

	//! used by lua to update an actor mode
	virtual void UpdateActorMode(long ActorId, const std::string & Mode);


	//! used by lua to tell that the actor should be reserved for the script
	virtual void ReserveActor(int ScriptId, long ActorId){}


	//! called when a script has finished
	virtual void ScriptFinished(int scriptid, const std::string & functioname);


	//! used by lua to move an actor or player
	//! the actor will change model
	virtual void UpdateActorModel(long ActorId, const std::string & Name);

	//! used by lua to move an actor or player
	//! the actor will change outfit
	virtual void UpdateActorOutfit(long ActorId, const std::string & Name);

	//! used by lua to move an actor or player
	//! the actor will change weapon
	virtual void UpdateActorWeapon(long ActorId, const std::string & Name);

	//! used by lua to move an actor or player
	//! the actor will change mode
	virtual void SendSignalToActor(long ActorId, int Signalnumber);


	//! used by lua to move an actor or player
	//! the actor will move using animation speed
	void TeleportActorTo(int ScriptId, long ActorId, const LbaVec3 &Position);

	//! used by lua to move an actor or player
	//! the actor change rotation
	void SetActorRotation(long ActorId, float Angle);


	//! used by lua to move an actor or player
	//! the actor show/hide
	virtual void ActorShowHide(long ActorId, bool Show);


	//! add/remove item from player inventory
	virtual void AddOrRemoveItem(long PlayerId, long ItemId, int number, int InformClientType);

	// display text to client window
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void HurtActor(int ObjectType, long ObjectId, float HurtValue, bool HurtLife,
								int PlayedAnimation);

	// display text to client window
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void KillActor(int ObjectType, long ObjectId);


	//! delay action execution
	virtual void DelayActionAfterPlayerChangeState(const DelayedAction &action, 
													LbaNet::ModelState newstate);

	//! switch the model of an actor
	virtual void SwitchActorModel(long ActorId, const std::string & newmodelname);

	//! revert the switch the model of an actor
	virtual void RevertActorModel(long ActorId);

	//! open dialog with player
	virtual void StartDialog(long PlayerId, long NpcId, long npcnametextid, bool simpledialog, 
												boost::shared_ptr<DialogPart> dialogroot);

	//! stop target player
	virtual void NpcUntargetPlayer(long NpcId, long PlayerId);


	//! start quest
	virtual void StartQuest(long PlayerId, long Questid);

	//! end quest
	virtual void TriggerQuestEnd(long PlayerId, long Questid);

	//! condition
	virtual bool QuestStarted(long PlayerId, long Questid);

	//! condition
	virtual bool QuestFinished(long PlayerId, long Questid);

	//! condition
	virtual bool ChapterStarted(long PlayerId, int Chapter);

	//! open shop
	virtual void OpenShop(long PlayerId, const LbaNet::ItemsMap &items, 
									const LbaNet::ItemInfo & currencyitem);

	// get spawn
	boost::shared_ptr<Spawn> GetSpawn(long id);

	// get spawn
	boost::shared_ptr<Spawn> GetSpawn(const std::string SpawnName);

	// get spawn
	long GetSpawnId(const std::string SpawnName);

	//! get spawns
	std::map<long, boost::shared_ptr<Spawn> > GetSpawns()
	{return _spawns;}

	//! open mailbox
	virtual void OpenMailbox(long PlayerId);


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
	void ChangeStance(Ice::Long id, LbaNet::ModelStance NewStanceId, bool fromserver = false,
							int mountid = -1);

	//! change player state
	void ChangePlayerState(Ice::Long id, LbaNet::ModelState NewState, float FallingSize,
																			bool fromserver = false);

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

	//! get player physcial size
	void GetPlayerPhysicalSize(Ice::Long clientid, float &sX, float &sY, float &sZ);


	//! get the place to respawn in case of death
	LbaNet::PlayerPosition GetSpawningPlace(Ice::Long clientid);

	//! set player ready to play
	void SetReady(Ice::Long clientid);

	//! ask if player ready to play
	bool IsReady(Ice::Long clientid);


	//!  update player position
	bool UpdatePlayerPosition(Ice::Long clientid, const PlayerPosition & pos, bool teleport = false);

	//!  update player stance
	//! return true if state has been updated
	bool UpdatePlayerStance(Ice::Long clientid, LbaNet::ModelStance NewStance,
									ModelInfo & returnmodel, bool fromserver = false,
									int mountid = -1);


	//!  update player state
	//! return true if state has been updated
	bool UpdatePlayerState(Ice::Long clientid, LbaNet::ModelState NewState,
									ModelInfo & returnmodel );

	//!  update player weapon
	//! return true if state has been updated
	bool UpdatePlayerWeapon(Ice::Long clientid, const std::string & weapon,
													ModelInfo & returnmodel, long itemid);


	//!  update player outfit
	//! return true if state has been updated
	bool UpdatePlayerOutfit(Ice::Long clientid, const std::string & outfit,
													ModelInfo & returnmodel, long itemid);
	
	//! change player weapon
	void ChangeWeapon(Ice::Long id, const std::string & weapon, long itemid);

	//! change player outfit
	void ChangeOutfit(Ice::Long id, const std::string & outfit, long itemid);


	//!  save player state
	void SavePlayerState(Ice::Long clientid);

	//!  restore player state
	bool RestorePlayerState(Ice::Long clientid, ModelInfo & returnmodel);



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

	//! called when a script is finished on a client
	void FinishedScript(long id, const std::string & ScriptName);

	//! called when the player use an item
	void PlayerItemUsed(Ice::Long clientid, long ItemId);

	//! get info about an item
	LbaNet::ItemPosInfo GetItemInfo(Ice::Long clientid, long ItemId);

	//! get info about an item
	LbaNet::ItemPosInfo GetCurrentWeaponInfo(Ice::Long clientid);

	//! item consumed
	bool PlayerConsumeItem(Ice::Long clientid, long ItemId);

	//! remove ephemere from player inventory
	void RemoveEphemere(Ice::Long clientid);

	//! update player life
	//! return true if no life
	bool DeltaUpdateLife(Ice::Long clientid, float update);

	//! update player mana
	//! return true if no mana
	bool DeltaUpdateMana(Ice::Long clientid, float update);

	//! return number of player on map
	int GetNbPlayers();

	//! change player color
	void ChangePlayerColor(long clientid, int skinidx, int eyesidx, int hairidx, 
										int outfitidx, int weaponidx, int mountidx, 
										int mountidx2);

	//! client open container
	void OpenInventoryContainer(long clientid, long itemid);





	//! used by lua to move an actor or player
	//! if id < 1 then it moves players
	//! the actor will move using animation speed
	virtual void InternalActorStraightWalkTo(int ScriptId, long ActorId, const LbaVec3 &Position, 
										bool asynchronus = false);

	//! used by lua to rotate an actor
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
	virtual void InternalActorRotate(int ScriptId, long ActorId, float Angle, float RotationSpeedPerSec,
						bool ManageAnimation, bool asynchronus = false);

	//! used by lua to wait until an actor animation is finished
	//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
	virtual void InternalActorAnimate(int ScriptId, long ActorId, bool AnimationMove, 
									bool asynchronus = false);




	//! used by lua to move an actor or player
	//! the actor will move using speed
	virtual void InternalActorGoTo(int ScriptId, long ActorId, const LbaVec3 &Position, 
										float Speed, bool asynchronus = false);
	

		//! used by lua to move an actor or player
	//! the actor will wait for signal
	virtual void InternalActorWaitForSignal(int ScriptId, long ActorId, int Signalnumber, 
										bool asynchronus = false);



	//! used by lua to rotate an actor
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
	virtual void InternalActorRotateFromPoint(int ScriptId, long ActorId, float Angle, const LbaVec3 &Position, 
												float RotationSpeedPerSec, bool asynchronus = false);


	//! used by lua to make actor follow waypoint
	virtual void InternalActorFollowWaypoint(int ScriptId, long ActorId, int waypointindex1, 
												int waypointindex2, bool asynchronus = false);


	//! update player inventory
	void UpdateInventory(long clientid, LbaNet::ItemList Taken, LbaNet::ItemList Put, 
								LbaNet::ItemClientInformType informtype);


	//! player use weapon
	void UseWeapon(Ice::Long PlayerId);

	//! destroy projectile
	void DestroyProjectile(long PlayerId, long ProjectileId, int	TouchedActorType,
							long TouchedActorId);

	//! destroy projectile
	void DestroyPlayerProjectile(Ice::Long PlayerId);


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

	std::map<long, boost::shared_ptr<TriggerBase> >				_triggers;
	std::map<long, boost::shared_ptr<Spawn> >					_spawns;


	bool														_stopping;
	double														_stopstarttime;


	std::map<Ice::Long, DelayedAction>							_delayedactions;

	std::map<long, LbaNet::ProjectileInfo>						_launchedprojectiles;
	std::map<long, std::vector<long> >							_playerprojectiles;
};


#endif