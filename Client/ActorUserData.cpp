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

#include "ActorUserData.h"
#include <string>
#include <IceUtil/RecMutex.h>


/***********************************************************
constructor
***********************************************************/
ActorUserData::ActorUserData(short ActType, long index, PhysicCallbackBase * callback)
	: ActorType(ActType), Materials(NULL), 
		MaterialsSize(0),
		HittedFloorMaterial(0), InternalActor(NULL),
		released(false), Callback(callback), ActorId(index), MovingObject(false),
		AllowedMovingX(false), AllowedMovingZ(false), ShouldUpdate(false),
		CurrentMoveX(0), CurrentMoveY(0), CurrentMoveZ(0), AllowFreeMove(false)
{
	m_mutex = new IceUtil::RecMutex();
}


/***********************************************************
destructor
***********************************************************/
ActorUserData::~ActorUserData()
{
	if(Materials)
		delete Materials;

	delete m_mutex;
}

/***********************************************************
accessor thread safe
***********************************************************/
short				ActorUserData::GetActorType()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return ActorType;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetActorType(short newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	ActorType = newv;
}



/***********************************************************
accessor thread safe
***********************************************************/
long				ActorUserData::GetActorId()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return ActorId;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetActorId(long newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	ActorId = newv;
}
 


/***********************************************************
accessor thread safe
***********************************************************/
size_t				ActorUserData::GetMaterialsSize()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return MaterialsSize;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetMaterialsSize(size_t newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	MaterialsSize = newv;
}
 

/***********************************************************
accessor thread safe
***********************************************************/
short				ActorUserData::GetMaterials(unsigned int id)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return Materials[id];
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetMaterials(short * newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	Materials = newv;
}
  

/***********************************************************
accessor thread safe
***********************************************************/
NxActor *			ActorUserData::GetInternalActor()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return InternalActor;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetInternalActor(NxActor * newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	InternalActor = newv;
}
  


/***********************************************************
accessor thread safe
***********************************************************/
short				ActorUserData::GetHittedFloorMaterial()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return HittedFloorMaterial;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetHittedFloorMaterial(short newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	HittedFloorMaterial = newv;
}
  


/***********************************************************
accessor thread safe
***********************************************************/
bool				ActorUserData::Getreleased()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return released;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::Setreleased(bool newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	released = newv;
}
 

/***********************************************************
accessor thread safe
***********************************************************/
bool				ActorUserData::GetMovingObject()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return MovingObject;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetMovingObject(bool newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	MovingObject = newv;
}
  

/***********************************************************
accessor thread safe
***********************************************************/
int					ActorUserData::GetMovingDirection()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return MovingDirection;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetMovingDirection(int newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	MovingDirection = newv;
}
  


/***********************************************************
accessor thread safe
***********************************************************/
bool				ActorUserData::GetAllowedMovingX()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return AllowedMovingX;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetAllowedMovingX(bool newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	AllowedMovingX = newv;
}
 

/***********************************************************
accessor thread safe
***********************************************************/
bool				ActorUserData::GetAllowedMovingZ()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return AllowedMovingZ;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::GetMove(float &X, float &Y, float &Z)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	X = (AllowedMovingX?CurrentMoveX:0);
	Y = 0;
	Z = (AllowedMovingZ?CurrentMoveZ:0);
}


/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetAllowedMovingZ(bool newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	AllowedMovingZ = newv;
}
  

/***********************************************************
accessor thread safe
***********************************************************/
bool				ActorUserData::GetShouldUpdate()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return ShouldUpdate;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetShouldUpdate(bool newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	ShouldUpdate = newv;
}
  


/***********************************************************
accessor thread safe
***********************************************************/
float				ActorUserData::GetCurrentMoveX()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return CurrentMoveX;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetCurrentMoveX(float newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	CurrentMoveX = newv;
}
 

/***********************************************************
accessor thread safe
***********************************************************/
float				ActorUserData::GetCurrentMoveY()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return CurrentMoveY;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetCurrentMoveY(float newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	CurrentMoveY = newv;
}
  

/***********************************************************
accessor thread safe
***********************************************************/
float				ActorUserData::GetCurrentMoveZ()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return CurrentMoveZ;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetCurrentMoveZ(float newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	CurrentMoveZ = newv;
}
  

/***********************************************************
accessor thread safe
***********************************************************/
bool				ActorUserData::GetAllowFreeMove()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return AllowFreeMove;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetAllowFreeMove(bool newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	AllowFreeMove = newv;
}



/***********************************************************
accessor thread safe
***********************************************************/
void ActorUserData::SetCallback(PhysicCallbackBase * newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	Callback = newv;
}

/***********************************************************
accessor thread safe
***********************************************************/
void ActorUserData::CallbackOnContact(int TouchedActorType, long TouchedActorIdx)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	if(!released && Callback && (ActorType >= 0))
		Callback->CallbackOnContact(TouchedActorType, TouchedActorIdx);
}