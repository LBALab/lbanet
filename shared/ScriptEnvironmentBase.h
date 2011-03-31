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


#ifndef _LBANET_SCRIPT_ENV_BASE_H_
#define _LBANET_SCRIPT_ENV_BASE_H_


class ActorHandler;
class TriggerBase;
class ActionBase;
class ClientScriptBase;
class ActionArgumentBase;
struct ContainerSharedInfo;
class DialogPart;
class Spawn;
class DynamicObject;

#include <boost/shared_ptr.hpp>
#include <ClientServerEvents.h>


#include "CommonTypes.h"
#include "LuaHandlerBase.h"

//*************************************************************************************************
//*                               class ScriptEnvironmentBase
//*************************************************************************************************
/**
* @brief Base class for lua script environment
*
*/
class ScriptEnvironmentBase
{
public:

	//! constructor
	ScriptEnvironmentBase()
		: m_generatednumber(0)
	{}


	//! destructor
	virtual ~ScriptEnvironmentBase(){}


	// function used by LUA to add actor
	virtual void AddActorObject(boost::shared_ptr<ActorHandler> actor) = 0;

	// add a trigger 
	virtual void AddTrigger(boost::shared_ptr<TriggerBase> trigger) = 0;
					
	// add spawn
	virtual void AddSpawn(boost::shared_ptr<Spawn> spawn) = 0;


	// teleport an object
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Teleport(int ObjectType, long ObjectId,
							const std::string &NewMapName, 
							long SpawningId,
							float offsetX, float offsetY, float offsetZ) = 0;


	// execute client script - does not work on npc objects
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ExecuteClientScript(int ObjectType, long ObjectId,
										const std::string & ScriptName,
										bool InlineFunction) = 0;


	// execute custom lua function
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ExecuteCustomAction(int ObjectType, long ObjectId,
										const std::string & FunctionName,
										ActionArgumentBase * args) = 0;


	// display text to client window
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void DisplayTxtAction(int ObjectType, long ObjectId,
										long TextId) = 0;



	// send error message to client
	virtual void SendErrorMessage(long clientid, const std::string & messagetitle, 
											const std::string &  messagecontent) = 0;

	// open container on client side
	virtual void OpenContainer(long clientid, boost::shared_ptr<ContainerSharedInfo> sharedinfo) = 0;


	//! used by lua to get an actor Position
	virtual LbaVec3 GetActorPosition(long ActorId) = 0;

	//! used by lua to get an actor Rotation
	virtual float GetActorRotation(long ActorId) = 0;

	//! used by lua to get an actor Rotation
	virtual LbaQuaternion GetActorRotationQuat(long ActorId) = 0;

	//! used by lua to update an actor animation
	virtual void UpdateActorAnimation(long ActorId, const std::string & AnimationString) = 0;

	//! used by lua to update an actor mode
	virtual void UpdateActorMode(long ActorId, const std::string & Mode) = 0;


	//! used by lua to move an actor or player
	//! the actor will move using animation speed
	void ActorStraightWalkTo(int ScriptId, long ActorId, const LbaVec3 &Position)
	{InternalActorStraightWalkTo(ScriptId, ActorId, Position, false);}

	//! used by lua to rotate an actor
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
	void ActorRotate(int ScriptId, long ActorId, float Angle, float RotationSpeedPerSec,
									bool ManageAnimation)
	{InternalActorRotate(ScriptId, ActorId, Angle, RotationSpeedPerSec, ManageAnimation, false);}

	//! used by lua to wait until an actor animation is finished
	//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
	void ActorAnimate(int ScriptId, long ActorId, bool AnimationMove)
	{InternalActorAnimate(ScriptId, ActorId, AnimationMove, false);}

	//! used by lua to tell that the actor should be reserved for the script
	virtual void ReserveActor(int ScriptId, long ActorId) = 0;



	//! used by lua to move an actor or player
	//! the actor will move using animation speed
	void ActorGoTo(int ScriptId, long ActorId, const LbaVec3 &Position, float Speed)
	{InternalActorGoTo(ScriptId, ActorId, Position, Speed, false);}


	//! used by lua to move an actor or player
	//! the actor will change model
	virtual void UpdateActorModel(long ActorId, const std::string & Name) = 0;

	//! used by lua to move an actor or player
	//! the actor will change outfit
	virtual void UpdateActorOutfit(long ActorId, const std::string & Name) = 0;

	//! used by lua to move an actor or player
	//! the actor will change weapon
	virtual void UpdateActorWeapon(long ActorId, const std::string & Name) = 0;


	//! used by lua to move an actor or player
	//! the actor will move using animation speed
	void ActorWaitForSignal(int ScriptId, long ActorId, int Signalnumber)
	{InternalActorWaitForSignal(ScriptId, ActorId, Signalnumber, false);}

	//! used by lua to move an actor or player
	//! the actor will change mode
	virtual void SendSignalToActor(long ActorId, int Signalnumber) = 0;


	//! used by lua to move an actor or player
	//! the actor will move using animation speed
	virtual void TeleportActorTo(int ScriptId, long ActorId, const LbaVec3 &Position) = 0;


	//! used by lua to move an actor or player
	//! the actor change rotation
	virtual void SetActorRotation(long ActorId, float Angle) = 0;
	

	//! used by lua to rotate an actor
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
	void ActorRotateFromPoint(int ScriptId, long ActorId, float Angle, const LbaVec3 &Position, 
									float RotationSpeedPerSec)
	{InternalActorRotateFromPoint(ScriptId, ActorId, Angle, Position, RotationSpeedPerSec, false);}


	//! used by lua to rotate an actor
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
	void ActorFollowWaypoint(int ScriptId, long ActorId, int waypointindex1, int waypointindex2)
	{InternalActorFollowWaypoint(ScriptId, ActorId, waypointindex1, waypointindex2, false);}


	//! used by lua to move an actor or player
	//! the actor show/hide
	virtual void ActorShowHide(long ActorId, bool Show) = 0;


	//! execute lua script given as a string
	void ExecuteScriptString( const std::string &ScriptString );



	//! called when a script is finished
	void ScriptFinished(int scriptid, bool wasasynchronus);

	//! start lua script in a separate thread
	//! return script id if successed or -1 else
	int StartScript(const std::string & FunctionName, bool inlinefunction);

	//! start lua script in a separate thread
	//! return script id if successed or -1 else
	int StartScript(const std::string & FunctionName, long ActorId, bool inlinefunction);


	//! wait until script part is finished
	void WaitForAsyncScript(int ScriptId, int ScriptPartId);

	//! check for finished asynchronus scripts
	void CheckFinishedAsynScripts();


	//! asynchronus version of ActorStraightWalkTo
	int Async_ActorStraightWalkTo(long ActorId, const LbaVec3 &Position);

	//! asynchronus version of ActorRotate
	int Async_ActorRotate(long ActorId, float Angle, float RotationSpeedPerSec,
									bool ManageAnimation);

	//! asynchronus version of ActorAnimate
	int Async_ActorAnimate(long ActorId, bool AnimationMove);

	//! asynchronus version of ActorGoTo
	int Async_ActorGoTo(long ActorId, const LbaVec3 &Position, float Speed);

	//! asynchronus version of WaitForSignal
	int Async_WaitForSignal(long ActorId, int Signalnumber);

	//! asynchronus version of ActorRotateFromPoint
	int Async_ActorRotateFromPoint(long ActorId, float Angle, const LbaVec3 &Position, 
									float RotationSpeedPerSec);

	//! asynchronus version of ActorFollowWaypoint
	int Async_ActorFollowWaypoint(long ActorId, int waypointindex1, int waypointindex2);

	//! make a lua script sleep for one cycle
	void WaitOneCycle(int ScriptId);


	//! resume a thread given the id
	void ResumeThread(int scriptid);

	//! resume a thread given the id
	void StropThread(int scriptid);

	//! add/remove item from player inventory
	virtual void AddOrRemoveItem(long PlayerId, long ItemId, int number, int InformClientType) = 0;


	// display text to client window
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void HurtActor(int ObjectType, long ObjectId, float HurtValue, bool HurtLife,
								int PlayedAnimation) = 0;


	// display text to client window
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void KillActor(int ObjectType, long ObjectId) = 0;

	//! switch the model of an actor
	virtual void SwitchActorModel(long ActorId, const std::string & newmodelname) = 0;

	//! revert the switch the model of an actor
	virtual void RevertActorModel(long ActorId) = 0;


	//! open dialog with player
	virtual void StartDialog(long PlayerId, long NpcId, long npcnametextid, bool simpledialog, 
												boost::shared_ptr<DialogPart> dialogroot) = 0;


	//! stop target player
	virtual void NpcUntargetPlayer(long NpcId, long PlayerId) = 0;


	//! start quest
	virtual void StartQuest(long PlayerId, long Questid) = 0;

	//! end quest
	virtual void TriggerQuestEnd(long PlayerId, long Questid) = 0;

	//! condition
	virtual bool QuestStarted(long PlayerId, long Questid) = 0;

	//! condition
	virtual bool QuestFinished(long PlayerId, long Questid) = 0;

	//! condition
	virtual bool QuestAvailable(long PlayerId, long Questid) = 0;

	//! condition
	virtual bool ChapterStarted(long PlayerId, int Chapter) = 0;

	//! open shop
	virtual void OpenShop(long PlayerId, const LbaNet::ItemsMap &items, 
									const LbaNet::ItemInfo & currencyitem) = 0;

	//! open mailbox
	virtual void OpenMailbox(long PlayerId) = 0;

	//! get actor info
	virtual boost::shared_ptr<DynamicObject> GetActor(int ObjectType, long ObjectId) = 0;


	// AttachActor
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void AttachActor(long ActorId, int AttachedObjectType, long AttachedObjectId) = 0;

	// DettachActor
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void DettachActor(long ActorId, long AttachedObjectId) = 0;


	//! send event to player
	virtual void SendEvents(long PlayerId, const LbaNet::EventsSeq & evts) = 0;


	//! send event to player
	virtual int GetInventoryItemCount(long PlayerId, long Itemid) = 0;

	//! return ghost owner player
	virtual long GetGhostOwnerPlayer(long ghostid){return -1;}


	//! record player killed npc
	virtual void PlayerKilledNpc(long PlayerId, long NpcId, const LbaNet::ItemsMap & givenitems){}

	// execute custom lua function
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual bool CheckCustomCondition(int ObjectType, long ObjectId,
							const std::string & FunctionName){return false;}


	//! used by lua to get an actor Position
	virtual LbaVec3 GetGhostPosition(long PlayerId, long ActorId)
	{return LbaVec3(-1, -1, -1);}

	//! used by lua to log into file
	void LogToFile(const std::string &text);

	//! used by lua to get an player Position
	virtual LbaVec3 GetPlayerPositionVec(long PlayerId)
	{return LbaVec3(-1, -1, -1);}

	//!  used by lua to get player position
	virtual LbaNet::PlayerPosition GetPlayerPosition(Ice::Long clientid)
	{return LbaNet::PlayerPosition();}



	//! npc rotate to player
	virtual void RotateToTargettedPlayer(int ScriptId, long ActorId, float ToleranceAngle, float speed){}

	//! npc follow player
	virtual void FollowTargettedPlayer(int ScriptId, long ActorId, float DistanceStopFollow){}

	//! npc use weapon
	virtual void UseWeapon(int ScriptId, long ActorId, int WeaponNumber){}

	//! return targeted player
	virtual long GetTargettedAttackPlayer(long ActorId){return -1;}

	//! check if target is in range
	virtual bool IsTargetInRange(float MaxDistance, long ActorId){return false;}

	//! check if target is in rotation range
	virtual float GetTargetRotationDiff(long ActorId){return 360;}


protected:

	//! used by lua to move an actor or player
	//! the actor will move using animation speed
	virtual void InternalActorStraightWalkTo(int ScriptId, long ActorId, const LbaVec3 &Position, 
										bool asynchronus) = 0;

	//! used by lua to rotate an actor
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
	virtual void InternalActorRotate(int ScriptId, long ActorId, float Angle, float RotationSpeedPerSec,
									bool ManageAnimation, bool asynchronus = false) = 0;

	//! used by lua to wait until an actor animation is finished
	//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
	virtual void InternalActorAnimate(int ScriptId, long ActorId, bool AnimationMove, bool asynchronus = false) = 0;


	//! used by lua to move an actor or player
	//! the actor will move using speed
	virtual void InternalActorGoTo(int ScriptId, long ActorId, const LbaVec3 &Position, float Speed, bool asynchronus = false) = 0;
	

		//! used by lua to move an actor or player
	//! the actor will wait for signal
	virtual void InternalActorWaitForSignal(int ScriptId, long ActorId, int Signalnumber, bool asynchronus = false) = 0;


	//! used by lua to rotate an actor
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
	virtual void InternalActorRotateFromPoint(int ScriptId, long ActorId, float Angle, const LbaVec3 &Position, 
												float RotationSpeedPerSec, bool asynchronus = false) = 0;


	//! used by lua to make actor follow waypoint
	virtual void InternalActorFollowWaypoint(int ScriptId, long ActorId, int waypointindex1, 
												int waypointindex2, bool asynchronus = false) = 0;



	//! called when a script has finished
	virtual void ScriptFinished(int scriptid, const std::string & functioname) = 0;




protected:
	boost::shared_ptr<LuaHandlerBase>					m_luaHandler;

private:
	int													m_generatednumber;
	std::map<int, bool>									m_asyncscripts;
	std::map<int, bool>									m_waitingscripts;

	std::map<int, int>									m_sleepingscripts;
};


#endif
