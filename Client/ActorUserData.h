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
	ActorUserData(int ActType, long index);

	//! destructor
	~ActorUserData();

	//! accessor thread safe
	int					GetActorType();
	void				SetActorType(int newv);


	long				GetActorId(); 
	void				SetActorId(long newv); 


	size_t				GetMaterialsSize();
	void				SetMaterialsSize(size_t newv); 

	short				GetMaterials(unsigned int id);
	void				SetMaterials(short * newv);  

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

	bool				GetAllowFreeMove();
	void				SetAllowFreeMove(bool newv);

	void				AddActorHitted(long ActorId, int ActorType);
	void				GetHittedActors(std::vector<std::pair<long, int> > & vec);

private:
	IceUtil::RecMutex *	m_mutex;

	// Actor type
	// 1 = static
	// 2 = kinematic
	// 3 = dynamic
	// 4 = controller
	int					ActorType;
	long				ActorId; 

	size_t				MaterialsSize;
	short *				Materials; 


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

	std::vector<std::pair<long, int> >	HittedActors;
};



#endif
