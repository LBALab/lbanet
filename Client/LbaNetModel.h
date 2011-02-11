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
	LbaNetModel();

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
	void AddObject(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId, 
						const LbaNet::ModelInfo &DisplayDesc, 
						const LbaNet::ObjectPhysicDesc &PhysicDesc,
						const LbaNet::ObjectExtraInfo &extrainfo,
						const LbaNet::LifeManaInfo &lifeinfo);
	
	//! remove object from server	
	//! type:
	// 1 -> static object
	// 2 -> server controlled
	// 3 -> movable by player
	// 4 -> player object
	// 5 -> ghost object
	void RemoveObject(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId);

	//! update object display
	void UpdateObjectDisplay(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId, 
									  LbaNet::DisplayObjectUpdateBasePtr update);

	//! update object physic
	void UpdateObjectPhysic(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId, 
									  LbaNet::PhysicObjectUpdateBasePtr update);

	//! key pressed
	void KeyPressed(LbanetKey keyid);

	//! key released
	void KeyReleased(LbanetKey keyid);


	//! when update player position
	void PlayerMovedUpdate(Ice::Long PlayerId, double updatetime, 
									const LbaNet::PlayerMoveInfo &info,
									bool teleport);

	//! when update npc position
	void NpcMovedUpdate(Ice::Long NpcId, double updatetime, 
									const LbaNet::PlayerMoveInfo &info,
									bool teleport);



	//! called when we enter a new map
	void NewMap(const std::string & NewMap, const std::string & Script,
					int AutoCameraType);


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


	// teleport an object
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Teleport(int ObjectType, long ObjectId,
							const std::string &NewMapName, long SpawningId,
							float offsetX, float offsetY, float offsetZ){}


	// execute client script - does not work on npc objects
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ExecuteClientScript(int ObjectType, long ObjectId,
										const std::string & ScriptName,
										bool InlineFunction){}


	// execute custom lua function
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ExecuteCustomAction(int ObjectType, long ObjectId,
										const std::string & FunctionName,
										ActionArgumentBase * args){}


	// display text to client window
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void DisplayTxtAction(int ObjectType, long ObjectId, long TextId){}



	// send error message to client
	virtual void SendErrorMessage(long clientid, const std::string & messagetitle, 
											const std::string &  messagecontent){}

	// open container on client side
	virtual void OpenContainer(long clientid, boost::shared_ptr<ContainerSharedInfo> sharedinfo){}



	//! used by lua to get an actor Position
	//! if id < 1 then it get player position
	virtual LbaVec3 GetActorPosition(long ActorId);

	//! used by lua to get an actor Rotation
	//! if id < 1 then it get player position
	virtual float GetActorRotation(long ActorId);

	//! used by lua to get an actor Rotation
	//! if id < 1 then it get player position
	virtual LbaQuaternion GetActorRotationQuat(long ActorId);

	//! used by lua to update an actor animation
	//! if id < 1 then it get player position
	virtual void UpdateActorAnimation(long ActorId, const std::string & AnimationString);

	//! used by lua to update an actor mode
	//! if id < 1 then it get player position
	virtual void UpdateActorMode(long ActorId, const std::string & Mode);


	//! called when a script has finished
	virtual void ScriptFinished(int scriptid, const std::string & functioname);


	//! used by lua to tell that the actor should be reserved for the script
	virtual void ReserveActor(int ScriptId, long ActorId);


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

protected:

	//! clean up map
	void CleanupMap();


	//! reset player object
	void ResetPlayerObject();



	//! add object to the scene
	//! if IsMainPlayer then treat this object as the player object
	void AddObject(LbaNet::ObjectTypeEnum OType, const ObjectInfo &desc,
					const LbaNet::ModelInfo &DisplayDesc,
					const LbaNet::ObjectExtraInfo &extrainfo,
					const LbaNet::LifeManaInfo &lifeinfo);


	//! remove object from the scene
	virtual void RemObject(LbaNet::ObjectTypeEnum OType, long id);


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
private:
	
	// list of object populating the scene
	// npc objects - server controlled
	// player objects - will move randomly - get info from server
	// ghosts objects - replication of other movable objects
	std::map<long, boost::shared_ptr<ExternalPlayer> >	_npcObjects;
	std::map<long, boost::shared_ptr<ExternalPlayer> >	_playerObjects;
	std::map<long, boost::shared_ptr<DynamicObject> >	_ghostObjects;

	#ifdef _USE_QT_EDITOR_
	std::map<long, boost::shared_ptr<DynamicObject> >	_editorObjects;
	#endif

	// last cycle time
	bool												m_paused;


	// controllers
	boost::shared_ptr<CharacterController>				m_controllerChar;
	boost::shared_ptr<CameraController>					m_controllerCam;



	// player object
	long												m_playerObjectId;


	std::string											m_current_map_name;
	std::string											m_current_world_name;


	std::map<int, std::set<long> >						m_playingscriptactors;
};

#endif