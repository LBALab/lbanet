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



//! class used by lua to add objects on the map
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

	long						ObjectId;


	LbaNet::ModelInfo			DisplayDesc;
	LbaNet::ObjectPhysicDesc	PhysicDesc;
	LbaNet::LifeManaInfo		LifeInfo;
	LbaNet::ObjectExtraInfo		ExtraInfo;
};


//! class taking care of the maping between lua and the server interfaces
class ActorHandler
{
public:
	//! constructor
	ActorHandler(const ActorObjectInfo & actorinfo);
	
	//! destructor
	virtual ~ActorHandler(void);

	//! get actor info
	const ActorObjectInfo & GetActorInfo()
	{ return m_actorinfo; }


	// save actor to lua file
	virtual void SaveToLuaFile(std::ofstream & file);

	//! get actor id
	long GetId()
	{ return m_actorinfo.ObjectId;}

	// get actor info
	ActorObjectInfo & GetInfo()
	{ return m_actorinfo; }

private:
	ActorObjectInfo		m_actorinfo;
};

#endif
