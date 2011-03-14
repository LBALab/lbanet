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
ActorUserData::ActorUserData(LbaNet::PhysicalActorType ActType, int ActObj, long index)
	: ActorType(ActType), ActObjType(ActObj), Materials(NULL), Rotation(0), 
		MaterialsSize(0), released(false), ActorId(index), MovingObject(false),
		AllowedMovingX(false), AllowedMovingZ(false), TouchingGround(false),
		CurrentMoveX(0), CurrentMoveY(0), CurrentMoveZ(0), AllowFreeMove(false),
		AddedMoveX(0), AddedMoveY(0), AddedMoveZ(0)
		
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
LbaNet::PhysicalActorType ActorUserData::GetActorType()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return ActorType;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetActorType(LbaNet::PhysicalActorType newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	ActorType = newv;
}


/***********************************************************
accessor thread safe
***********************************************************/
int	ActorUserData::GetActorObjType()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return ActObjType;
}

/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetActorObjType(int newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	ActObjType = newv;
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
void				ActorUserData::SetAllowedMovingZ(bool newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	AllowedMovingZ = newv;
}
  



/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetTouchingGround(bool newv)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	TouchingGround = newv;
}
 

/***********************************************************
accessor thread safe
***********************************************************/
bool				ActorUserData::GetTouchingGround()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return TouchingGround;
}


/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::GetMove(float &X, float &Y, float &Z)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	X = CurrentMoveX;
	Y = CurrentMoveY;
	Z = CurrentMoveZ;
}


/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetMove(float X, float Y, float Z)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	CurrentMoveX = X;
	CurrentMoveY = Y;
	CurrentMoveZ = Z;
}




/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::GetAddedMove(float &X, float &Y, float &Z)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	X = AddedMoveX;
	Y = AddedMoveY;
	Z = AddedMoveZ;

	AddedMoveX = 0;
	AddedMoveY = 0;
	AddedMoveZ = 0;
}


/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetAddedMove(float X, float Y, float Z)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	AddedMoveX = X;
	AddedMoveY = Y;
	AddedMoveZ = Z;
}


/***********************************************************
accessor thread safe
***********************************************************/
float				ActorUserData::GetRotation()
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	return Rotation;
}


/***********************************************************
accessor thread safe
***********************************************************/
void				ActorUserData::SetRotation(float R)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	Rotation = R;
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
void ActorUserData::AddActorHitted(HitInfo HInfo)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	HittedActors.push_back(HInfo);
}


/***********************************************************
accessor thread safe
***********************************************************/
void ActorUserData::GetHittedActors(std::vector<HitInfo> & vec)
{
	IceUtil::RecMutex::Lock lock(*m_mutex);
	HittedActors.swap(vec);
}