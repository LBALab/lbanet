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


#ifndef __LBA_NET_PHYSX_OBJECTS_HANDLERS_H__
#define __LBA_NET_PHYSX_OBJECTS_HANDLERS_H__

#include <boost/shared_ptr.hpp>
#include "PhysicalObjectHandlerBase.h"


class PhysXEngine;
class ActorUserData;
class NxActor;
class NxController;
class PhysicalDescriptionBase;

/***********************************************************************
 * Handler on a physX object
 ***********************************************************************/
class PhysXObjectHandlerBase : public PhysicalObjectHandlerBase
{
public:
	//! constructor
	PhysXObjectHandlerBase(boost::shared_ptr<ActorUserData> UserData);

	//! destructor
	virtual ~PhysXObjectHandlerBase(){}

	//! get user data
	virtual boost::shared_ptr<ActorUserData> GetUserData()
	{ return _UserData; }
	

protected:
	boost::shared_ptr<ActorUserData>	_UserData;
};



/***********************************************************************
 * Handler on a physX dynamic actor - this actor controll itself its rotation
 ***********************************************************************/
class PhysXActorsHandler : public PhysXObjectHandlerBase
{
public:
	//! constructor
	PhysXActorsHandler(boost::shared_ptr<ActorUserData> UserData,
						NxActor* Actor, float sizeY,
						boost::shared_ptr<PhysicalDescriptionBase> desc );

	//! destructor
	virtual ~PhysXActorsHandler();

	//! get object position in the world
	virtual void GetPosition(float &X, float &Y, float &Z);

	//! get object rotation on all axis
	virtual void GetRotation(LbaQuaternion& Q);

	//! get object rotation on a single angle
	virtual float GetRotationYAxis();

	//! set object position in the world
	virtual void SetPosition(float X, float Y, float Z);

	//! set object rotation on all axis
	virtual void SetRotation(const LbaQuaternion& Q);

	//! move object in the world
	virtual void Move(float deltaX, float deltaY, float deltaZ, bool checkcollision = true);

	//! move object to a position in the world
	virtual void MoveTo(float X, float Y, float Z);

	//! rotate object in the world
	virtual void RotateYAxis(float deltaY);

	//! rotate object in the world
	virtual void RotateTo(const LbaQuaternion& Q);

	//! show or hide the object
	virtual void ShowOrHide(bool Show);

	//! update physic with new data
	virtual void Update(LbaNet::PhysicObjectUpdateBasePtr update);


	//! ignore collision between two pairs of actors
	virtual void IgnoreCollisionWith(PhysicalObjectHandlerBase * actor);

	//! add force to actor - only for dynamic actors
	virtual void AddForce(float X, float Y, float Z);

	//! return internal actor - only for physX actor
	virtual NxActor* GetphysXInternalActor();

protected:
	NxActor*										_Actor;
	float											_sizeY;

	boost::shared_ptr<PhysicalDescriptionBase>		_desc;
};



/***********************************************************************
 * Handler on a physX controller
 ***********************************************************************/
class PhysXControllerHandler : public PhysXObjectHandlerBase
{
public:
	//! constructor
	PhysXControllerHandler(boost::shared_ptr<ActorUserData> UserData,
								NxController* Controller,
								boost::shared_ptr<SimpleRotationHandler> rotH,
								float sizeY,
								boost::shared_ptr<PhysicalDescriptionBase> desc );

	//! destructor
	virtual ~PhysXControllerHandler();

	//! get object position in the world
	virtual void GetPosition(float &X, float &Y, float &Z);

	//! get object rotation on all axis
	virtual void GetRotation(LbaQuaternion& Q);

	//! get object rotation on a single angle
	virtual float GetRotationYAxis();

	//! set object position in the world
	virtual void SetPosition(float X, float Y, float Z);

	//! set object rotation on all axis
	virtual void SetRotation(const LbaQuaternion& Q);

	//! move object in the world
	virtual void Move(float deltaX, float deltaY, float deltaZ, bool checkcollision = true);

	//! move object to a position in the world
	virtual void MoveTo(float X, float Y, float Z);

	//! rotate object in the world
	virtual void RotateYAxis(float deltaY);

	//! rotate object in the world
	virtual void RotateTo(const LbaQuaternion& Q);

	//! show or hide the object
	virtual void ShowOrHide(bool Show);

	//! update physic with new data
	virtual void Update(LbaNet::PhysicObjectUpdateBasePtr update);


	//! ignore collision between two pairs of actors
	virtual void IgnoreCollisionWith(PhysicalObjectHandlerBase * actor){}

	//! add force to actor - only for dynamic actors
	virtual void AddForce(float X, float Y, float Z){}

	//! return internal actor - only for physX actor
	virtual NxActor* GetphysXInternalActor();

protected:
	NxController*									_Controller;
	boost::shared_ptr<SimpleRotationHandler>		_rotH;
	float											_sizeY;

	boost::shared_ptr<PhysicalDescriptionBase>		_desc;
};

#endif