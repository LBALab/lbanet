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


#ifndef _LBANET_ACTOR_USER_H_
#define _LBANET_ACTOR_USER_H_

#include "PhysicCallbackBase.h"

class NxActor;
class NxVec3;

namespace IceUtil
{
	class RecMutex;
}

//*************************************************************************************************
//*                               class Camera
//*************************************************************************************************
/**
* @brief Class taking care of the opengl scene camera
*
*/
class ActorUserData
{
public:
	//! constructor
	ActorUserData(short ActType, long index, PhysicCallbackBase * callback);

	//! destructor
	~ActorUserData();

	//! accessor thread safe
	short				GetActorType();
	void				SetActorType(short newv);


	long				GetActorId(); 
	void				SetActorId(long newv); 


	size_t				GetMaterialsSize();
	void				SetMaterialsSize(size_t newv); 

	short				GetMaterials(unsigned int id);
	void				SetMaterials(short * newv);  

	NxActor *			GetInternalActor();
	void				SetInternalActor(NxActor * newv);  


	short				GetHittedFloorMaterial();
	void				SetHittedFloorMaterial(short newv);  


	bool				Getreleased();
	void				Setreleased(bool newv);  

	bool				GetMovingObject();
	void				SetMovingObject(bool newv);  

	int					GetMovingDirection();
	void				SetMovingDirection(int newv);  


	bool				GetAllowedMovingX();
	void				SetAllowedMovingX(bool newv);  

	void				GetMove(float &X, float &Y, float &Z);

	bool				GetAllowedMovingZ();
	void				SetAllowedMovingZ(bool newv);  

	bool				GetShouldUpdate();
	void				SetShouldUpdate(bool newv);  


	float				GetCurrentMoveX();
	void				SetCurrentMoveX(float newv);  

	float				GetCurrentMoveY();
	void				SetCurrentMoveY(float newv);  

	float				GetCurrentMoveZ();
	void				SetCurrentMoveZ(float newv);  

	void				SetCallback(PhysicCallbackBase * newv);
	void CallbackOnContact(int TouchedActorType, long TouchedActorIdx);

	bool				GetAllowFreeMove();
	void				SetAllowFreeMove(bool newv);

private:
	IceUtil::RecMutex *	m_mutex;

	// Actor type
	// 1 = actor
	// 2 = terrain
	// 3 = player
	// 4 = other
	short				ActorType;
	long				ActorId; 

	size_t				MaterialsSize;
	short *				Materials; 
	NxActor *			InternalActor;

	short				HittedFloorMaterial;

	bool				released;
	bool				MovingObject;
	int					MovingDirection;

	bool				AllowedMovingX;
	bool				AllowedMovingZ;


	bool				ShouldUpdate;

	float				CurrentMoveX;
	float				CurrentMoveY;
	float				CurrentMoveZ;

	bool				AllowFreeMove;


	PhysicCallbackBase * Callback;
};



#endif
