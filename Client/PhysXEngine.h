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

#if !defined(__LbaNetModel_1_PhysXEngine_h)
#define __LbaNetModel_1_PhysXEngine_h

class NxPhysicsSDK;
class NxScene;
class NxActor;
class NxControllerManager;
class NxUserAllocator;
class NxVec3;
class NxController;
class NxActor;
class NxUserOutputStream;
class LbaQuaternion;

#include <vector>
#include <set>

#include "ActorUserData.h"





/***********************************************************************
 * Module:  PhysXEngine.h
 * Author:  vivien
 * Modified: lundi 27 juillet 2009 14:59:34
 * Purpose: Declaration of the class PhysXEngine
 ***********************************************************************/
class PhysXEngine
{
public:

	// singleton pattern
	static PhysXEngine * getInstance();

	//! destructor
	~PhysXEngine();


	//! init function
	void Init(float gravity);

	//! quit function
	void Quit();

	//! call to start physic calculation after having updated state from inputs
	void StartPhysics(float tdiff);

	//! call after render to get results of calculation
	void GetPhysicsResults();

	//! create actors
	NxActor* CreatePlane(const NxVec3 & StartPosition, const NxVec3 & PlaneNormal);

	//! create actors
	// type: 1=static, 2=kinematic, 3=dynamic
	NxActor* CreateBox(const NxVec3 & StartPosition, float dimX, float dimY, float dimZ, 
						float density, LbaNet::PhysicalActorType Type, ActorUserData * adata, 
						const LbaQuaternion& rotation, bool collidable = true);

	NxActor* CreateSphere(const NxVec3 & StartPosition, float radius, float density, 
							LbaNet::PhysicalActorType Type, ActorUserData * adata,
							const LbaQuaternion& rotation, bool collidable = true);

	NxActor* CreateSphere(const NxVec3 & StartPosition, float radius, float density, 
							LbaNet::PhysicalActorType Type, ActorUserData * adata,
							float staticFriction, float dynamicFriction, float restitution, 
							const LbaQuaternion& rotation, bool collidable = true);

	NxActor* CreateCapsule(const NxVec3 & StartPosition, float radius, float height, 
							float density, LbaNet::PhysicalActorType Type, ActorUserData * adata, 
							const LbaQuaternion& rotation, bool collidable = true);


	NxController* CreateCharacter(const NxVec3 & StartPosition, float radius, float height,
									ActorUserData * adata);

	NxController* CreateCharacterBox(const NxVec3 & StartPosition, const NxVec3 & Extents,
									ActorUserData * adata);

	NxActor* CreateTriangleMesh(const NxVec3 & StartPosition, float *Vertexes, 
										size_t VertexesSize, unsigned int *Indices, size_t IndicesSize,
										ActorUserData * adata,const LbaQuaternion& rotation, bool collidable=true);

	NxActor* LoadTriangleMeshFile(const NxVec3 & StartPosition, const std::string Filename,
												ActorUserData * userdata, const LbaQuaternion& rotation, bool collidable);

	void DestroyActor(NxActor* actor);
	void DestroyCharacter(NxController* character);


	//! move character
	//! returned collision flags, collection of NxControllerFlag
	unsigned int MoveCharacter(NxController* character, const NxVec3& moveVector, bool checkcollision=true);
	void SetCharacterPos(NxController* character, const NxVec3& posVector);
	void GetCharacterPosition(NxController* character, float &posX, float &posY, float &posZ);
	void HideShowCharacter(NxController* character, bool Show);
	void HideShowActor(NxActor* actor, bool Show);


	//! render actors
	void RenderActors();

	//! get gravity
	void GetGravity(NxVec3 & Gravity);

	bool IsInitialized()
	{return _isInitialized;}


	//! Get Closest Floor
	int GetClosestFloor(float PositionX, float PositionY, float PositionZ);

	//! ignore collision for a pair of actor
	void IgnoreActorContact(NxActor* actor1, NxActor* actor2);

	//! check fi actor 1 is on top of actor2
	bool CheckOnTopOff(NxActor* actor1, NxActor* actor2);

	//! return the floor the actor is stepping on
	short GetFloorMaterial(NxActor* actor);


protected:
	//! constructor
	PhysXEngine();


private:
	// singleton
	static PhysXEngine * _singletonInstance;

	// physX internal data
	NxPhysicsSDK*				gPhysicsSDK;
	NxScene*					gScene;
	NxControllerManager*		gManager;
	NxUserAllocator*			gAllocator;
	NxUserOutputStream*			gOutputStream;

	bool						_isInitialized;
};

#endif