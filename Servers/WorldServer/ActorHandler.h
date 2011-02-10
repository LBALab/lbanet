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

#ifndef _ACTOR_HANDLER_H__
#define _ACTOR_HANDLER_H__

#include <string>
#include <LbaTypes.h>
#include "Conditions.h"
#include "ScriptedActor.h"
#include "CommonTypes.h"
#include "ActorScriptPart.h"
#include <ClientServerEvents.h>

/***********************************************************************
class used by lua to add objects on the map
 ***********************************************************************/
struct ActorObjectInfo
{
	//constructor
	ActorObjectInfo()
		: ObjectId(-1)
	{
		DisplayDesc.RotX = 0;
		DisplayDesc.RotY = 0;
		DisplayDesc.RotZ = 0;

		DisplayDesc.TransX = 0;
		DisplayDesc.TransY = 0;
		DisplayDesc.TransZ = 0;

		DisplayDesc.ScaleX = 1;
		DisplayDesc.ScaleY = 1;
		DisplayDesc.ScaleZ = 1;	
	}

	//constructor
	ActorObjectInfo(long id);

	// set enum for render type as lua does not map enum
	//1 - RenderOsgModel
	//2 - RenderSprite
	//3 - RenderLba1M
	//4 - RenderLba2M
	void SetRenderType(int rtype);

	// set enum for PhysicalShape as lua does not map enum
	//1 - NoShape
	//2 - BoxShape
	//3 - CapsuleShape
	//4 - SphereShape
	//5 - TriangleMeshShape
	void SetPhysicalShape(int shape);

	// set enum for SetPhysicalActorType as lua does not map enum
	//1 - StaticAType - used for static npc
	//2 - KynematicAType - used for moving npc
	//3 - DynamicAType - used for dynamic object (not implemented)
	//4 - CharControlAType - used for object movable by the player
	void SetPhysicalActorType(int ptype);


	// set the model state - used by lua instead of  the enum
	//1 - NoState
	//2 - StNormal
	//3 - StDying
	//4 - StDrowning
	//5 - StDrowningGas
	//6 - StBurning
	//7 - StSmallHurt
	//8 - StMediumHurt
	//9 - StBigHurt
	//10 - StHurtFall
	//11 - StFinishedFall
	//12 - StFalling
	//13 - StJumping
	//14 - StMovingObject
	//15 - StUseWeapon
	//16 - StImmune
	//17 - StHidden
	//18 - StScripted
	//19 - StProtectedHurt
	//20 - StRestrictedMovingObject
	//21 - StFighting
	void SetModelState(int state);

	// accessors
	int GetRenderType();
	int GetPhysicalShape();
	int GetPhysicalActorType();
	int GetModelState();

	
	//! used by lua to add color swap to object info
	void AddColorSwap(int modelpart, int oldcolor, int newcolor);


	ConditionBasePtr			Condition;


	long						ObjectId;


	LbaNet::ModelInfo			DisplayDesc;
	LbaNet::ObjectPhysicDesc	PhysicDesc;
	LbaNet::LifeManaInfo		LifeInfo;
	LbaNet::ObjectExtraInfo		ExtraInfo;
};



/***********************************************************************
class taking care of the maping between lua and the server interfaces
 ***********************************************************************/
class ActorHandler : public ScriptedActor
{
public:
	//! constructor
	ActorHandler(const ActorObjectInfo & actorinfo);
	
	//! destructor
	virtual ~ActorHandler(void);

	//! set script handler
	void SetScriptHandler(ScriptEnvironmentBase* scripthandler);

	//! get actor info
	const ActorObjectInfo & GetActorInfo()
	{ return m_actorinfo; }

	//! set actor info
	void SetActorInfo(const ActorObjectInfo & ainfo);


	// save actor to lua file
	virtual void SaveToLuaFile(std::ofstream & file);

	//! get actor id
	long GetId()
	{ return m_actorinfo.ObjectId;}

	//! clear color swap info
	void ClearColorSwap();


	//! used by lua to get an actor Position
	LbaVec3 GetActorPosition();

	//! used by lua to get an actor Rotation
	float GetActorRotation();

	//! used by lua to get an actor Rotation
	LbaQuaternion GetActorRotationQuat();

	//! used by lua to update an actor animation
	void UpdateActorAnimation(const std::string & AnimationString);

	//! used by lua to update an actor mode
	void UpdateActorMode(const std::string & Mode, bool updatefromlua);

	//! called when a script has finished
	void ScriptFinished(int scriptid, const std::string & functioname);


	//! update Model
	void UpdateActorModel(const std::string & Model, bool updatefromlua);

	//! update Model
	void UpdateActorOutfit(const std::string & Outfit, bool updatefromlua);

	//! update Model
	void UpdateActorWeapon(const std::string & Weapon, bool updatefromlua);

	//! update Model
	void SendSignal(int Signalnumber);

	//! get player current position
	void TeleportTo(float PosX, float PosY, float PosZ);



	//! process actor
	std::vector<LbaNet::ClientServerEventBasePtr> Process(double tnow, float tdiff);


	//! add script part to the script
	void AddScriptPart(ActorScriptPartBasePtr part);


	//! remove script part to the script
	void RemoveScriptPart(ActorScriptPartBasePtr part);

	//! update position of the script
	void UpdateScriptPosition(ActorScriptPartBasePtr part, int position);

	//! get script
	std::vector<ActorScriptPartBasePtr> GetScript()
	{ return m_script; }

	//! clear the running script
	void ClearRunningScript();


#ifdef _USE_QT_EDITOR_
public:
	std::vector<int>		initpolycolors;
	std::vector<int>		initspherecolors;
	std::vector<int>		initlinecolors;

	std::vector<int>		currentpolycolors;
	std::vector<int>		currentspherecolors;
	std::vector<int>		currentlinecolors;

	//! get actor info
	ActorObjectInfo & GetEditorActorInfo()
	{ return m_actorinfo; }

	//! refresh actor
	void Refresh()
	{ SetActorInfo(m_actorinfo); }

#endif


protected:

	//! create actor
	void CreateActor();

	//! pause the playing script
	void Pause();

	//! resume the playing script
	void Resume();

	//! update client if needed
	void UpdateServer(double tnow, float tdiff);

	//! check if should update
	bool ShouldforceUpdate();

	//! start script
	void StartScript();

protected:
	ActorObjectInfo										m_actorinfo;
	int													m_launchedscript;
	bool												m_paused;

	ScriptEnvironmentBase*								m_scripthandler;


	float												m_saved_X;
	float												m_saved_Y;
	float												m_saved_Z;
	float												m_saved_rot;
	LbaQuaternion										m_saved_Q;



	std::vector<ActorScriptPartBasePtr>					m_script;


	// update pos to clients
	LbaNet::PlayerMoveInfo								_lastupdate;
	LbaNet::PlayerMoveInfo								_currentupdate;

	std::vector<LbaNet::ClientServerEventBasePtr>		_events;
};

#endif
