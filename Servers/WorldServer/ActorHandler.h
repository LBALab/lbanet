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
	// type ==>
	//1 - StaticObject
	//2 - CpuObject
	//3 - MovableObject
	//4 - PlayerObject
	//5 - GhostObject
	ActorObjectInfo(long id, int type);

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
	//1 - StaticAType
	//2 - KynematicAType
	//3 - DynamicAType
	//4 - CharControlAType
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




	long						ObjectId;


	//1 - StaticObject
	//2 - CpuObject
	//3 - MovableObject
	//4 - PlayerObject
	//5 - GhostObject
	LbaNet::ObjectTypeEnum		TypeO;

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
	~ActorHandler(void);

	//! get actor info
	const ActorObjectInfo & GetActorInfo()
	{ return m_actorinfo; }


private:
	ActorObjectInfo		m_actorinfo;
};

#endif