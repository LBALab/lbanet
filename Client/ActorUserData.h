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

#include <vector>
#include <LbaTypes.h>

struct HitInfo
{
	//! constructor
	HitInfo()
		: FloorMaterial(0), HitBottom(false), ActorId(-1)
	{}

	int								ActorObjType;
	long							ActorId;
	LbaNet::PhysicalActorType		ActorPhysType;
	bool							HitBottom;
	short							FloorMaterial;
};


//*************************************************************************************************
//*                               class ActorUserData
//*************************************************************************************************
/**
* @brief Class taking care of user data in physic object
*
*/
class ActorUserData
{
public:
	//! constructor
	ActorUserData(LbaNet::PhysicalActorType ActType, int ActObj, long index);

	//! destructor
	~ActorUserData();

	//! accessor thread safe
	LbaNet::PhysicalActorType	GetActorType();
	void				SetActorType(LbaNet::PhysicalActorType newv);


	int	GetActorObjType();
	void				SetActorObjType(int newv);


	long				GetActorId(); 
	void				SetActorId(long newv); 


	size_t				GetMaterialsSize();
	void				SetMaterialsSize(size_t newv); 

	short				GetMaterials(unsigned int id);
	void				SetMaterials(short * newv);  

	bool				Getreleased();
	void				Setreleased(bool newv);  

	bool				GetMovingObject();
	void				SetMovingObject(bool newv);  

	void				GetMove(float &X, float &Y, float &Z);
	void				SetMove(float X, float Y, float Z);

	float				GetRotation();
	void				SetRotation(float R);

	bool				GetAllowFreeMove();
	void				SetAllowFreeMove(bool newv);

	void				AddActorHitted(HitInfo HInfo);
	void				GetHittedActors(std::vector<HitInfo> & vec);

	bool				GetTouchingGround();
	void				SetTouchingGround(bool newv);  


	void				GetAddedMove(float &X, float &Y, float &Z);
	void				SetAddedMove(float X, float Y, float Z);

private:
	IceUtil::RecMutex *	m_mutex;



	int			ActObjType;

	// Actor type
	// 1 = static
	// 2 = kinematic
	// 3 = dynamic
	// 4 = controller
	LbaNet::PhysicalActorType		ActorType;
	long							ActorId; 

	size_t							MaterialsSize;
	short *							Materials; 


	bool							TouchingGround;

	bool							released;
	bool							MovingObject;
	bool							AllowFreeMove;

	float							CurrentMoveX;
	float							CurrentMoveY;
	float							CurrentMoveZ;

	float							Rotation;

	std::vector<HitInfo>			HittedActors;


	float							AddedMoveX;
	float							AddedMoveY;
	float							AddedMoveZ;
};



#endif
