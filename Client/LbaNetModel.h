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

#if !defined(__LbaNetModel_1_LbaNetModel_h)
#define __LbaNetModel_1_LbaNetModel_h

#include <string>
#include <vector>
#include <map>
#include <set>
#include <list>

#include "ObjectsDescription.h"
#include "DynamicObject.h"

#include "ClientExtendedEvents.h"
#include "ScriptEnvironmentBase.h"

#include <boost/shared_ptr.hpp>
#include <ClientServerEvents.h>

class PhysXEngine;
class CharacterController;
class CameraController;
class ExternalPlayer;
class ClientLuaHandler;
class ExternalActor;
class ProjectileHandler;
class ItemObject;
class LbaNetEngine;
class Holomap;

struct ObjecToAdd
{
	ObjecToAdd(int OType, Ice::Long ObjectId, Ice::Long OwnerId,
					const LbaNet::ModelInfo &DisplayDesc, 
					const LbaNet::ObjectPhysicDesc &PhysicDesc,
					const LbaNet::ObjectExtraInfo &extrainfo,
					const LbaNet::LifeManaInfo &lifeinfo)
		:  _OType(OType), _ObjectId(ObjectId), _OwnerId(OwnerId), _DisplayDesc(DisplayDesc), 
					_PhysicDesc(PhysicDesc), _extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	int _OType; 
	Ice::Long _ObjectId; 
	Ice::Long _OwnerId;
	LbaNet::ModelInfo _DisplayDesc; 
	LbaNet::ObjectPhysicDesc _PhysicDesc;
	LbaNet::ObjectExtraInfo _extrainfo;
	LbaNet::LifeManaInfo _lifeinfo;
};


/***********************************************************************
 * Module:  LbaNetModel.h
 * Author:  vivien
 * Modified: mardi 14 juillet 2009 13:54:52
 * Purpose: Declaration of the class LbaNetModel
 ***********************************************************************/
class LbaNetModel : public ScriptEnvironmentBase
{
public:
	//! constructor
	LbaNetModel(LbaNetEngine * engineptr);

	//! destructor
	virtual ~LbaNetModel();


	//! set player id
	void SetPlayerId(long Id);


	// change the world
	void ChangeWorld(const std::string & NewWorld);

	//! do all check to be done when idle
	void Process(double tnow, float tdiff);

	//! clean up everything
	void CleanupWorld();

	//! pause the game
	void Pause();

	//! resume the game
	void Resume();

	//! add object from server
	//! type:
	// 1 -> npc object
	// 2 -> player object
	// 3 -> ghost object
	// 4 -> editor object
	void AddObject(int OType, Ice::Long ObjectId, Ice::Long OwnerId,
						const LbaNet::ModelInfo &DisplayDesc, 
						const LbaNet::ObjectPhysicDesc &PhysicDesc,
						const LbaNet::ObjectExtraInfo &extrainfo,
						const LbaNet::LifeManaInfo &lifeinfo);
	
	//! remove object from server	
	//! type:
	// 1 -> npc object
	// 2 -> player object
	// 3 -> ghost object
	// 4 -> editor object
	void RemoveObject(int OType, Ice::Long ObjectId);

	//! update object display
	void UpdateObjectDisplay(int OType, Ice::Long ObjectId, 
									  LbaNet::DisplayObjectUpdateBasePtr update);

	//! update object physic
	void UpdateObjectPhysic(int OType, Ice::Long ObjectId, 
									  LbaNet::PhysicObjectUpdateBasePtr update);

	//! update object sound
	void UpdateObjectSound(int OType, Ice::Long ObjectId, 
									  LbaNet::SoundObjectUpdateBasePtr update);
	

	//! key pressed
	void KeyPressed(LbanetKey keyid);

	//! key released
	void KeyReleased(LbanetKey keyid);


	//! when update player position
	void PlayerMovedUpdate(Ice::Long PlayerId, double updatetime, 
									const LbaNet::PlayerMoveInfo &info,
									bool teleport);

	//! when update player position
	void GhostMovedUpdate(Ice::Long GhostId, double updatetime, 
									const LbaNet::PlayerMoveInfo &info);


	//! when update player position
	void NPCMovedUpdate(Ice::Long NpcId, double updatetime, 
									const LbaNet::PlayerMoveInfo &info);
	
	//! when update npc position
	void NpcChangedUpdate(Ice::Long NpcId, double updatetime, 
									float CurrPosX, float CurrPosY, float CurrPosZ,
									float CurrRotation, const std::string &CurrAnimation,
									bool ResetPosition, bool ResetRotation,
									const LbaNet::PlayingSoundSequence	&Sounds,
									LbaNet::NpcUpdateBasePtr Update);


	//! called when we enter a new map
	void NewMap(const std::string & NewMap, const std::string & Script,
					int AutoCameraType, const std::string & MapDescription);


	//! map is fully refreshed
	void RefreshEnd();

	//! center the camera on player
	void CenterCamera();


	//! refresh lua file
	void RefreshLua();




	#ifdef _USE_QT_EDITOR_
	//! editor tp the player
	void EditorTpPlayer(float posx, float posy, float posz);

	//! force the camera in ghost mode or not
	void ForceGhost(bool force);
	#endif






	// function used by LUA to add actor
	virtual void AddActorObject(boost::shared_ptr<ActorHandler> actor){}

	// add a trigger 
	virtual void AddTrigger(boost::shared_ptr<TriggerBase> trigger){}
					
	// add spawn
	virtual void AddSpawn(boost::shared_ptr<Spawn> spawn){}

	// teleport an object
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> ghost object
	//! 4 -> editor object
	virtual void Teleport(int ObjectType, long ObjectId,
							const std::string &NewMapName, long SpawningId,
							float offsetX, float offsetY, float offsetZ){}


	// execute client script - does not work on npc objects
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> ghost object
	//! 4 -> editor object
	virtual void ExecuteClientScript(int ObjectType, long ObjectId,
										const std::string & ScriptName,
										bool InlineFunction){}


	// execute custom lua function
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> ghost object
	//! 4 -> editor object
	virtual void ExecuteCustomAction(int ObjectType, long ObjectId,
										const std::string & FunctionName,
										ActionArgumentBase * args){}


	// display text to client window
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> ghost object
	//! 4 -> editor object
	virtual void DisplayTxtAction(int ObjectType, long ObjectId, long TextId){}



	// send error message to client
	virtual void SendErrorMessage(long clientid, const std::string & messagetitle, 
											const std::string &  messagecontent){}

	// open container on client side
	virtual void OpenContainer(long clientid, boost::shared_ptr<ContainerSharedInfo> sharedinfo){}



	//! used by lua to get an actor Position
	//! if id < 1 then it get player position
	virtual LbaVec3 GetActorPosition(int ScriptId, long ActorId);

	//! used by lua to get an actor Rotation
	//! if id < 1 then it get player position
	virtual float GetActorRotation(int ScriptId, long ActorId);

	//! used by lua to get an actor Rotation
	//! if id < 1 then it get player position
	virtual LbaQuaternion GetActorRotationQuat(int ScriptId, long ActorId);

	//! used by lua to update an actor animation
	//! if id < 1 then it get player position
	virtual void UpdateActorAnimation(int ScriptId, long ActorId, const std::string & AnimationString);

	//! used by lua to update an actor mode
	//! if id < 1 then it get player position
	virtual void UpdateActorMode(int ScriptId, long ActorId, const std::string & Mode);


	//! called when a script has finished
	virtual void ScriptFinished(int scriptid, const std::string & functioname);


	//! used by lua to tell that the actor should be reserved for the script
	virtual void ReserveActor(int ScriptId, long ActorId);


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
	virtual void AddOrRemoveItem(long PlayerId, long ItemId, int number, int InformClientType){}

	// display text to client window
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void HurtActor(int ObjectType, long ObjectId, float HurtValue, bool HurtLife,
								int PlayedAnimation){}


	// display text to client window
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void KillActor(int ObjectType, long ObjectId){}

	// show/hide object
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	void ShowHideActor(int ObjectType, long ObjectId, bool SHow);


	//! internally update player state
	void UpdatePlayerState(LbaNet::ModelState	NewState);

	//! switch the model of an actor
	virtual void SwitchActorModel(long ActorId, const std::string & newmodelname){}

	//! revert the switch the model of an actor
	virtual void RevertActorModel(long ActorId){}


	//! open dialog with player
	virtual void StartDialog(long PlayerId, long NpcId, long npcnametextid, bool simpledialog, 
												boost::shared_ptr<DialogPart> dialogroot){}

	//! stop target player
	virtual void NpcUntargetPlayer(long NpcId, long PlayerId){}


	//! actor target player
	virtual void NpcTargetPlayer(long ActorId, long PlayerId);

	//! actor untarget player
	virtual void NpcUnTargetPlayer(long ActorId);

	//! start quest
	virtual void StartQuest(long PlayerId, long Questid){}

	//! end quest
	virtual void TriggerQuestEnd(long PlayerId, long Questid){}

	//! condition
	virtual bool QuestStarted(long PlayerId, long Questid){return false;}

	//! condition
	virtual bool QuestFinished(long PlayerId, long Questid){return false;}

	//! condition
	virtual bool QuestAvailable(long PlayerId, long Questid){return false;}

	//! condition
	virtual bool ChapterStarted(long PlayerId, int Chapter){return false;}

	//! open shop
	virtual void OpenShop(long PlayerId, const LbaNet::ItemsMap &items, 
									const LbaNet::ItemInfo & currencyitem){}
	//! open mailbox
	virtual void OpenMailbox(long PlayerId){}
	

	//! create projectile
	void CreateProjectile(const LbaNet::ProjectileInfo & Info);

	//! destroy projectile
	void DestroyProjectile(long Id);

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



	//! attached actor to npc
	void NpcAttachActor(long NpcId, int AttachedObjectType, long AttachedObjectId);


	//! send event to player
	virtual void SendEvents(long PlayerId, const LbaNet::EventsSeq & evts){}

	//! send event to player
	virtual int GetInventoryItemCount(long PlayerId, long Itemid){return 0;}

	//! refresh player portrait
	void RefreshPlayerPortrait();


	//! called when item looted by player
	void ItemLooted(long itemid);

	//! create projectile object
	boost::shared_ptr<DynamicObject> CreateProjectileObject(const LbaNet::ProjectileInfo & Info);

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
	virtual bool ActorMoving(int ObjectType, long ObjectId){ return false;}

	// run attack script
	virtual void RunAttackScript(long ActorId, const std::string & FunctionName){}

	// set DB flag
	virtual void SetDBFlag(long PlayerId, const std::string & flagid, int value){}

	// get DB flag
	virtual int GetDBFlag(long PlayerId, const std::string & flagid){return -1;}

	//! display shout on screen
	void DisplayShout(const LbaNet::ShoutTextInfo &shoutinfo);

	// PlayClientVideo
	virtual void PlayClientVideo(long ScriptId,	const std::string & VideoPath);

	// video play finished
	void ClientVideoFinished();


	// DisplayImage
	virtual void DisplayImage(int ScriptId, const std::string & imagepath, long NbSecondDisplay, 
								bool FadeIn, const LbaColor &FadeInColor,
								bool FadeOut, const LbaColor &FadeOutColor, 
								const std::string & OptionalMusicPath);

	// FixedImageDisplayFinished
	void DisplayExtraGLFinished();

	// DisplayScrollingText
	virtual void DisplayScrollingText(int ScriptId, const std::string & imagepath, 
										const LbaVecLong &textIds, 
										const std::string & OptionalMusicPath);

	// reset to game screen after displaying extra gl stuff
	virtual void StartDisplayExtraScreen(int ScriptId);

	// reset to game screen after displaying extra gl stuff
	virtual void EndDisplayExtraScreen();

	// show or hide loading screen
	void ShowHideLoadingScreen(bool show);

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
	virtual void TeleportPlayerAtEndScript(int ScriptId, const std::string &newmap, long newspawn);

	//! start client script
	void StartClientScript(const std::string & FunctionName, bool inlinefunction);

	//! ShowHideVoiceSprite
	void ShowHideVoiceSprite(long ActorId, bool Show, bool Left);

	//! AddHolomap
	virtual void AddHolomap(boost::shared_ptr<Holomap> holo);

	//! AddHolomap
	virtual void AddHolomapLoc(boost::shared_ptr<HolomapLocation> holo);

	//! AddHolomap
	virtual void AddHolomapPath(boost::shared_ptr<HolomapTravelPath> holo);

	//! display holomap
	virtual void DisplayHolomap(int ScriptId, long PlayerId, int mode, long holoid);

protected:

	//! clean up map
	void CleanupMap();


	//! reset player object
	void ResetPlayerObject();



	//! add object to the scene
	//! if IsMainPlayer then treat this object as the player object
	void AddObject(int OType, Ice::Long OwnerId, const ObjectInfo &desc,
					const LbaNet::ModelInfo &DisplayDesc,
					const LbaNet::ObjectExtraInfo &extrainfo,
					const LbaNet::LifeManaInfo &lifeinfo,
					bool movable, bool freemove);


	//! remove object from the scene
	virtual void RemObject(int OType, long id);


	//! release scripted actors
	void ReleaseActorFromScript(int scriptid);


	//! used by lua to move an actor or player
	//! if id < 1 then it moves players
	//! the actor will move using animation speed
	virtual void InternalActorStraightWalkTo(int ScriptId, long ActorId, const LbaVec3 &Position, 
										bool asynchronus = false);

	//! used by lua to rotate an actor
	//! if id < 1 then it moves players
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
	virtual void InternalActorRotate(int ScriptId, long ActorId, float Angle, float RotationSpeedPerSec,
								bool ManageAnimation, bool asynchronus = false);

	//! used by lua to wait until an actor animation is finished
	//! if id < 1 then it moves players
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
											bool asynchronus = false);

	//iCreateObject
	ObjectInfo CreateObject(int OType, Ice::Long ObjectId, 
								const LbaNet::ModelInfo &DisplayDesc, 
								const LbaNet::ObjectPhysicDesc &PhysicDesc,
								const LbaNet::ObjectExtraInfo &extrainfo,
								const LbaNet::LifeManaInfo &lifeinfo);


	//init holomap from lua
	void InitHolomap();



private:
	
	// list of object populating the scene
	// npc objects - server controlled
	// player objects - will move randomly - get info from server
	// ghosts objects - replication of other movable objects
	// _itemsObjects - items to loot
	std::map<long, boost::shared_ptr<ExternalActor> >	_npcObjects;
	std::map<long, boost::shared_ptr<ExternalPlayer> >	_playerObjects;
	std::map<long, boost::shared_ptr<ExternalPlayer> >	_ghostObjects;
	std::map<long, boost::shared_ptr<ItemObject> >		_itemsObjects;



	std::map<long, boost::shared_ptr<ProjectileHandler> >	_projectileObjects;
	

	#ifdef _USE_QT_EDITOR_
	std::map<long, boost::shared_ptr<DynamicObject> >	_editorObjects;
	#endif

	// last cycle time
	bool												m_paused;
	bool												m_newworld;


	// controllers
	boost::shared_ptr<CharacterController>				m_controllerChar;
	boost::shared_ptr<CameraController>					m_controllerCam;



	// player object
	long												m_playerObjectId;


	std::string											m_current_map_name;
	std::string											m_current_world_name;


	std::map<int, std::set<long> >						m_playingscriptactors;

	int													m_videoscriptid;
	int													m_fixedimagescriptid;
	bool												m_image_assoc_music;

	bool												m_showing_loading;

	bool												m_display_extra_screens;
	std::list<int>										m_waiting_display_thread;
	int													m_scripttofinish;

	LbaNetEngine *										m_engineptr;

	std::list<ObjecToAdd>								m_toadd;

	std::map<int, std::pair<std::string, long> >		m_tpend_script;

	std::vector<std::pair<std::string, bool> >			m_tostart_scripts;


	bool												m_isafk;
	bool												m_checkafk;
	double												m_checkafk_time;
};

#endif