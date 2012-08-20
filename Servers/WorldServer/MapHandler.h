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
#include <IceUtil/RecMutex.h>

#include <boost/shared_ptr.hpp>

#include "RunnableThread.h"
#include "ServerGUIBase.h"
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
class NaviMeshHandler;


struct GhostInfo
{
	Ice::Long					Id;
	Ice::Long					OwnerPlayerId;
	Ice::Long					ActorId;
	LbaNet::PlayerPosition		CurrentPos;
};

struct PlayerToAddInfo
{
	Ice::Long							Id;
	boost::shared_ptr<PlayerHandler>	Phandler;
	long								SpawnId;
};


//! take care of a map of the world
class MapHandler : public Runnable, public ScriptEnvironmentBase, public DelayedExecutionHandler
{
public:
	//! constructor
	MapHandler(const std::string & worldname, const MapInfo & mapinfo, 
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

	
	//! add player from external
	void ExtAddPlayer(Ice::Long PlayerId, boost::shared_ptr<PlayerHandler> pinfo,
						long spawnid);
	
	//! remove player from external
	void ExtRemovePlayer(Ice::Long PlayerId);

	//! get player to add and remove
	void GetToAddRemove(std::vector<PlayerToAddInfo> &toadd, std::vector<Ice::Long> &toremove);


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


	//!  used by lua to get player position
	virtual PlayerPosition GetPlayerPosition(Ice::Long clientid);

	//! used by lua to get an actor Position
	virtual LbaVec3 GetActorPosition(int ScriptId, long ActorId);

	//! used by lua to get an actor Rotation
	virtual float GetActorRotation(int ScriptId, long ActorId);

	//! used by lua to get an actor Rotation
	//! if id < 1 then it get player position
	virtual LbaQuaternion GetActorRotationQuat(int ScriptId, long ActorId);

	//! used by lua to update an actor animation
	virtual void UpdateActorAnimation(int ScriptId, long ActorId, const std::string & AnimationString);

	//! used by lua to update an actor mode
	virtual void UpdateActorMode(int ScriptId, long ActorId, const std::string & Mode);


	//! used by lua to tell that the actor should be reserved for the script
	virtual void ReserveActor(int ScriptId, long ActorId){}


	//! called when a script has finished
	virtual void ScriptFinished(int scriptid, const std::string & functioname);


	//! used by lua to move an actor or player
	//! the actor will change model
	virtual void UpdateActorModel(int ScriptId, long ActorId, const std::string & Name);

	//! used by lua to move an actor or player
	//! the actor will change outfit
	virtual void UpdateActorOutfit(int ScriptId, long ActorId, const std::string & Name);

	//! used by lua to move an actor or player
	//! the actor will change weapon
	virtual void UpdateActorWeapon(int ScriptId, long ActorId, const std::string & Name);

	//! used by lua to move an actor or player
	//! the actor will change mode
	virtual void SendSignalToActor(long ActorId, int Signalnumber);


	//! used by lua to move an actor or player
	//! the actor will move using animation speed
	void TeleportActorTo(int ScriptId, long ActorId, const LbaVec3 &Position);

	//! used by lua to move an actor or player
	//! the actor change rotation
	void SetActorRotation(int ScriptId, long ActorId, float Angle);


	//! used by lua to move an actor or player
	//! the actor show/hide
	virtual void ActorShowHide(int ScriptId, long ActorId, bool Show);


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
	virtual bool QuestAvailable(long PlayerId, long Questid);

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

	//! get actor info
	virtual boost::shared_ptr<DynamicObject> GetActor(int ObjectType, long ObjectId);


	// AttachActor
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void AttachActor(long ActorId, int AttachedObjectType, long AttachedObjectId);

	// DettachActor
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void DettachActor(long ActorId, long AttachedObjectId);


	//! send event to player
	virtual void SendEvents(long PlayerId, const LbaNet::EventsSeq & evts);



	// get client name
	std::string GetName(Ice::Long clientid);



	//! update player shortcut
	void UpdatePlayerShortcut(Ice::Long clientid, int Position, long ItemId);

	//! player switch item
	void PlayerSwitchItem(Ice::Long clientid, long ItemId, int NewPosition);

	//! player use item
	void PlayerItemUsed(Ice::Long clientid, long ItemId);

	//! Player Create Letter
	void PlayerCreateLetter(Ice::Long clientid, const std::string & subject,
										const std::string & message);

	//! Player Destroy Item
	void PlayerDestroyItem(Ice::Long clientid, long ItemId);

	//! get player inventory
	LbaNet::ItemsMap GetInventory(Ice::Long clientid, int & inventorysize);

	//! update player inventory
	void UpdateInventory(Ice::Long clientid, LbaNet::ItemList Taken, LbaNet::ItemList Put, 
								LbaNet::ItemClientInformType informtype);

	//! send event to player
	virtual int GetInventoryItemCount(long PlayerId, long Itemid);


	//! return ghost owner player
	virtual long GetGhostOwnerPlayer(long ghostid);


	//! record player killed npc
	virtual void PlayerKilledNpc(long PlayerId, long NpcId, const LbaNet::ItemsMap & givenitems);

	// execute custom lua function
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual bool CheckCustomCondition(int ObjectType, long ObjectId,
										const std::string & FunctionName);


	//! used by lua to get an actor Position
	virtual LbaVec3 GetGhostPosition(long PlayerId, long ActorId);

	//! used by lua to get an player Position
	virtual LbaVec3 GetPlayerPositionVec(long PlayerId);


	//! npc rotate to player
	virtual void RotateToTargettedPlayer(int ScriptId, long ActorId, float ToleranceAngle, float speed);

	//! npc follow player
	virtual void FollowTargettedPlayer(int ScriptId, long ActorId, float DistanceStopFollow);

	//! npc use weapon
	virtual void UseWeapon(int ScriptId, long ActorId, int WeaponNumber);

	//! npc start use weapon - will not stop until changing state - only usefull for distance weapon
	virtual void StartUseWeapon(int ScriptId, long ActorId, int WeaponNumber);


	//! return targeted player
	virtual long GetTargettedAttackPlayer(long ActorId);

	//! check if target is in range
	virtual bool IsTargetInRange(float MaxDistance, long ActorId);

	//! check if target is in rotation range
	virtual float GetTargetRotationDiff(long ActorId);


	//! launch projectile
	virtual long LaunchProjectile(LbaNet::ProjectileInfo pinfo);

	//! destroy projectile
	virtual void DestroyProjectile(long projectileid);


	//! get weapon distance
	//! 1-> first contact weapon, 2 -> first distance weapon
	//! 3-> second contact weapon, 4 -> second distance weapon
	virtual float GetNpcWeaponReachDistance(long ActorId, int WeaponNumber);

	// check if actor can play animation
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual bool CanPlayAnimation(int ObjectType, long ObjectId, const std::string & anim);

	// check if actor is moving
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual bool ActorMoving(int ObjectType, long ObjectId);

	// run attack script
	virtual void RunAttackScript(long ActorId, const std::string & FunctionName);

	// set DB flag
	virtual void SetDBFlag(long PlayerId, const std::string & flagid, int value);

	// get DB flag
	virtual int GetDBFlag(long PlayerId, const std::string & flagid);

	// PlayClientVideo
	virtual void PlayClientVideo(long ClientId,	const std::string & VideoPath);

	// DisplayImage
	virtual void DisplayImage(int ScriptId, const std::string & imagepath, long NbSecondDisplay, 
								bool FadeIn, const LbaColor &FadeInColor,
								bool FadeOut, const LbaColor &FadeOutColor, 
								const std::string & OptionalMusicPath){}

	// DisplayScrollingText
	virtual void DisplayScrollingText(int ScriptId, const std::string & imagepath, 
										const LbaVecLong &textIds, 
										const std::string & OptionalMusicPath){}


	// reset to game screen after displaying extra gl stuff
	virtual void StartDisplayExtraScreen(int ScriptId){}

	// reset to game screen after displaying extra gl stuff
	virtual void EndDisplayExtraScreen(){}

	//! used by lua to make an actor play a sound
	//! there is 5 available channels (0 to 5)
	virtual void ActorStartSound(int ScriptId, long ActorId, int SoundChannel, 
										const std::string & soundpath, bool loop);

	//! used by lua to make an actor stop a sound
	//! there is 5 available channels (0 to 5)
	virtual void ActorStopSound(int ScriptId, long ActorId, int SoundChannel);

	//! used by lua to make an actor stop a sound
	//! there is 5 available channels (0 to 5)
	virtual void ActorPauseSound(int ScriptId, long ActorId, int SoundChannel);

	//! used by lua to make an actor stop a sound
	//! there is 5 available channels (0 to 5)
	virtual void ActorResumeSound(int ScriptId, long ActorId, int SoundChannel);

	//! TeleportPlayerAtEndScript
	virtual void TeleportPlayerAtEndScript(int ScriptId, const std::string &newmap, long newspawn){}
	
	//! AddHolomap
	virtual void AddHolomap(boost::shared_ptr<Holomap> holo){}

	//! AddHolomap
	virtual void AddHolomapLoc(boost::shared_ptr<HolomapLocation> holo){}

	//! AddHolomap
	virtual void AddHolomapPath(boost::shared_ptr<HolomapTravelPath> holo){}

	//! display holomap
	virtual void DisplayHolomap(int ScriptId, long PlayerId, int mode, long holoid);


protected:

	// process events
	void ProcessEvents(const std::map<Ice::Long, EventsSeq> & evts);

	// process events
	void ProcessEvent(Ice::Long id, LbaNet::ClientServerEventBasePtr evt);


	// player entered map
	void PlayerEntered(Ice::Long id);

	// player left map
	void PlayerLeft(Ice::Long id);


	// gui update from a client
	void GuiUpdate(Ice::Long id, const std::string guidi, GuiUpdatesSeq	Updates);


	//! called when a player moved
	void PlayerMoved(Ice::Long id, double time, const LbaNet::PlayerMoveInfo &info);

	//! called when a ghost moved
	void GhostMoved(Ice::Long id, Ice::Long ghostid, double time, const LbaNet::PlayerMoveInfo &info);
	


	//! refresh player objects
	void RefreshPlayerObjects(Ice::Long id);


	//! change player stance
	void ChangeStance(Ice::Long id, LbaNet::ModelStance NewStanceId, bool fromserver = false,
							int mountid = -1);

	//! change player state
	//! EventType - 1 - environment, 2 - fall down, 3 - npc, 4 - player, 5 - other, 6 - drown
	void ChangePlayerState(Ice::Long id, LbaNet::ModelState NewState, float FallingSize,
								int EventType, long ActorId, bool fromserver = false);

	//! a player is raised from dead
	void RaiseFromDeadEvent(Ice::Long id);

	//! process player action
	void ProcessPlayerAction(Ice::Long id, bool ForcedNormalAction);


	// get player proxy
	ClientProxyBasePtr GetProxy(Ice::Long clientid);

	// get players proxies
	std::vector<ClientProxyBasePtr> GetProxies();

	//! return player info
	boost::shared_ptr<PlayerHandler> GetPlayerInfo(long playerid);

	// return inventory size
	int GetInventorySize(Ice::Long clientid);

	// return inventory content
	ItemsMap GetInventory(Ice::Long clientid);

	// return shortcuts
	ShortcutsSeq GetShorcuts(Ice::Long clientid);

	//!  get player rotation
	float GetPlayerRotation(Ice::Long clientid);

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
	bool UpdatePlayerPosition(Ice::Long clientid, const PlayerPosition & pos, 
								float speedX, float speedY, float speedZ, bool teleport = false);

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
	void ProcessEditorUpdate(LbaNet::EditorUpdateBasePtr update);


	//! add a spawning to the map
	void Editor_AddOrModSpawning(boost::shared_ptr<Spawn> spawn);

	//! remove a spawning
	void Editor_RemoveSpawning(long SpawningId);



	//! remove an trigger
	void Editor_RemoveTrigger(long TriggerId);

	//! add an actor
	void Editor_AddModActor(boost::shared_ptr<ActorHandler> actor);

	//! remove an actor
	void Editor_RemoveActor(long Id);

	
	//! create display object for spawning
	ActorObjectInfo CreateSpawningDisplay(long id, float PosX, float PosY, float PosZ, 
											const std::string & name);

	//! called when a script is finished on a client
	void FinishedScript(long id, const std::string & ScriptName,
							const std::string & tpnewmap, long tpnewspan);


	//! called when a video is finished on a client
	void FinishedVideo(long id);


	//! get info about an item
	LbaNet::ItemPosInfo GetItemInfo(Ice::Long clientid, long ItemId);

	//! get info about an item
	LbaNet::ItemPosInfo GetCurrentWeaponInfo(Ice::Long clientid);
	
	//! get player hit contact power
	float GetPlayerHitContactPower(Ice::Long clientid, bool withweapon);
	
	//! get player armor
	float GetPlayerArmor(Ice::Long clientid);


	//! item consumed
	bool PlayerConsumeItem(Ice::Long clientid, long ItemId);

	//! remove ephemere from player inventory
	void RemoveEphemere(Ice::Long clientid);

	//! update player life
	//! return true if no life
	//! updatetype : 0 - potion, 1 - environment, 2 - fall down, 3 - npc, 4 - player, 5 - other
	bool DeltaUpdateLife(Ice::Long clientid, float update, int updatetype, long actorid,
							bool forcelooselife);

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



	//! used by lua to make actor follow waypoint
	virtual void InternalActorFollowGivenWaypoint(int ScriptId, long ActorId, 
											const LbaVec3 & Pm1, const LbaVec3 & P0,
											const LbaVec3 & P1, const LbaVec3 & P2, 
											const LbaVec3 & P3, const LbaVec3 & P4, 
											bool asynchronus = false){}


	//! player use weapon
	void UseWeapon(Ice::Long PlayerId);

	//! destroy projectile
	void DestroyProjectile(long PlayerId, long ProjectileId, int	TouchedActorType,
							long TouchedActorId);

	//! HittedProjectile
	void HittedProjectile(long PlayerId, long ProjectileId, int	TouchedActorType,
							long TouchedActorId);

	//! HittedProjectile
	void PlayerHittedContact(long PlayerId, bool WithWeapon, int	TouchedActorType,
							long TouchedActorId);
	

	//! destroy projectile
	void DestroyPlayerProjectile(Ice::Long PlayerId);


	//! playr hit player
	void ProjectileHitPlayer(long hitterType, long hitterId, long hittedid, float hitpower, bool forcelooselife);


	//! teleport a player
	//! return true if player left the map
	bool TeleportPlayer(long playerid, const LbaNet::PlayerPosition &newpos, long spawnid);

	//! make player enter the map
	void MakePlayerEnterMap(long playerid, boost::shared_ptr<PlayerHandler> info, long SpawnId);

	//! make player leave the map
	void MakePlayerLeaveMap(long playerid);

	//! add a new ghost
	Ice::Long AddGhost(Ice::Long playerid, Ice::Long actorid, const LbaNet::PlayerPosition &info);

	//! remove a  ghost
	void RemoveGhost(Ice::Long ghostid);

	//! get ghost position
	LbaNet::PlayerPosition GetGhostPosition(Ice::Long ghostid);

	//! update ghost position
	bool UpdateGhostPosition(Ice::Long ghostid, const LbaNet::PlayerPosition &info);
	
	//! player loot item
	void PlayerLootItem(Ice::Long playerid, Ice::Long ItemId);


	//! refresh navimesh
	void RefreshNaviMesh();

private:
	// threading and mutex stuff
	IceUtil::Monitor<IceUtil::Mutex>							_monitor;
	IceUtil::Mutex												_mutex_events;

	bool														_Trunning;
	IceUtil::ThreadControl										_threadcontrol;
	IceUtil::ThreadPtr											_thread;

	std::string													_worldname;
	MapInfo														_mapinfo;


	EventsSeq													_tosendevts;
	std::map<Ice::Long, EventsSeq>								_events;

	std::vector<PlayerToAddInfo>								_toadd;
	std::vector<Ice::Long>										_toremove;


	std::map<Ice::Long, ActorObjectInfo >						_editorObjects;



	std::map<Ice::Long, boost::shared_ptr<PlayerHandler> >		_players;
	std::map<Ice::Long, boost::shared_ptr<ActorHandler> >		_Actors;
	std::map<long, boost::shared_ptr<TriggerBase> >				_triggers;
	std::map<long, boost::shared_ptr<Spawn> >					_spawns;

	std::map<std::string, boost::shared_ptr<ServerGUIBase> >	_guihandlers;


	bool														_stopping;
	double														_stopstarttime;

	std::map<Ice::Long, DelayedAction>							_delayedactions;

	std::map<long, LbaNet::ProjectileInfo>						_launchedprojectiles;
	std::map<long, std::vector<long> >							_playerprojectiles;

	std::map<Ice::Long, GhostInfo>								_ghosts;
	std::map<std::pair<Ice::Long, Ice::Long>, Ice::Long>		_revertghosts;
	std::map<Ice::Long, std::vector<Ice::Long> >				_playerghosts;

	std::map<Ice::Long, std::map< ::Ice::Long, ::LbaNet::ItemPosInfo> >	_playeritems;


	std::string													_customluafilename;

	boost::shared_ptr<NaviMeshHandler>							_navimesh;

};


#endif