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


#ifndef _LBANET_PHYSICAL_OBJECT_HANDLER_BASE_H_
#define _LBANET_PHYSICAL_OBJECT_HANDLER_BASE_H_

#include "CommonTypes.h"
#include <LbaTypes.h>

class ActorUserData;
class NxActor;


//*************************************************************************************************
//*                               class PhysicalObjectHandlerBase
//*************************************************************************************************
/**
* @brief Pure virtual class to get access to a physical object current transformation
* (e.g. translation, rotation, etc.)
*
*/
class PhysicalObjectHandlerBase
{
public:

	//! constructor
	PhysicalObjectHandlerBase()
		: _resetted(false)
	{}

	//! destructor
	virtual ~PhysicalObjectHandlerBase(){}

	//! get object position in the world
	virtual void GetPosition(float &X, float &Y, float &Z) = 0;

	//! get object rotation on all axis
	virtual void GetRotation(LbaQuaternion &Q) = 0;

	//! get object rotation on a single angle
	virtual float GetRotationYAxis() = 0;

	//! set object position in the world
	virtual void SetPosition(float X, float Y, float Z) = 0;

	//! set object rotation on all axis
	virtual void SetRotation(const LbaQuaternion& Q) = 0;

	//! move object in the world
	virtual void Move(float deltaX, float deltaY, float deltaZ, bool checkcollision = true) = 0;

	//! move object to a position in the world
	virtual void MoveTo(float X, float Y, float Z) = 0;

	//! rotate object in the world
	virtual void RotateYAxis(float deltaY) = 0;

	//! rotate object in the world
	virtual void RotateTo(const LbaQuaternion& Q) = 0;

	
	//! get user data
	virtual boost::shared_ptr<ActorUserData> GetUserData() = 0;

	//! call to see if the object was resetted in the physical world
	//! (e.g. object has been teleported) in this case the synchronization process
	//! would directly set display object to the new position without smoothing
	bool WasReseted()
	{
		bool res = _resetted;
		_resetted = false;
		return res;
	}

	//! show or hide the object
	virtual void ShowOrHide(bool Show) = 0;


	//! update physic with new data
	virtual void Update(LbaNet::PhysicObjectUpdateBasePtr update)
	{
		const std::type_info& info = typeid(*update);

		// PositionUpdate
		if(info == typeid(LbaNet::PositionUpdate))
		{
			LbaNet::PositionUpdate * castedptr = 
				dynamic_cast<LbaNet::PositionUpdate *>(update.get());

			MoveTo(castedptr->Update.X, castedptr->Update.Y, castedptr->Update.Z);
			LbaQuaternion Q(castedptr->Update.Rotation, LbaVec3(0,1,0));
			RotateTo(Q);
		}
	}

	//! ignore collision between two pairs of actors
	virtual void IgnoreCollisionWith(PhysicalObjectHandlerBase * actor) = 0;

	//! add force to actor - only for dynamic actors
	virtual void AddForce(float X, float Y, float Z) = 0;

	//! return internal actor - only for physX actor
	virtual NxActor* GetphysXInternalActor() = 0;

	//! get last move
	virtual void GetLastMove(float &X, float &Y, float &Z) = 0;

	//! get last rotation
	virtual float GetLastRotation() = 0;


	//! check if actor is on top of other
	virtual bool OnTopOff(PhysicalObjectHandlerBase * actor) = 0;


	//! reset last move
	virtual void ResetMove() = 0;

protected:
	bool _resetted;
};


//*************************************************************************************************
//*                               class SimpleRotationHandler
//*************************************************************************************************
/**
* @brief Handle rotation directly if they do not have any influence on the physical shape
*
*/
class SimpleRotationHandler
{
public:

	//! constructor
	SimpleRotationHandler(const LbaQuaternion& Q)
		: _Q(Q)
	{}

	//! destructor
	~SimpleRotationHandler(){}

	//! get object rotation on all axis
	void GetRotation(LbaQuaternion& Q) const
	{
		Q = _Q;
	}

	//! get object rotation on a single angle
	float GetRotationYAxis() const
	{
		return _Q.GetRotationSingleAngle();
	}

	//! set object rotation on all axis
	void SetRotation(const LbaQuaternion& Q)
	{
		_Q = Q;
	}

	//! rotate object in the world
	void RotateTo(const LbaQuaternion& Q)
	{
		_Q = Q;
	}

	//! rotate object in the world
	void RotateYAxis(float deltaY)
	{
		_Q.AddSingleRotation(deltaY, LbaVec3(0,1,0));
	}


	//! get direction vector
	LbaVec3 GetDirection(const LbaVec3 &vec) const
	{
		return _Q.GetDirection(vec);
	}

private:
	LbaQuaternion _Q;
};



//*************************************************************************************************
//*                               class SimplePhysicalObjectHandler
//*************************************************************************************************
/**
* @brief Handle position and rotation directly with no physical shape
*
*/
class SimplePhysicalObjectHandler : public PhysicalObjectHandlerBase
{
public:

	//! constructor
	SimplePhysicalObjectHandler(float pX, float pY, float pZ,
									const LbaQuaternion& Q)
		: _PosX(pX), _PosY(pY), _PosZ(pZ), _rotH(Q), _lastmoveX(0), 
			_lastmoveY(0), _lastmoveZ(0), _lastrotation(0)
	{}

	//! destructor
	virtual ~SimplePhysicalObjectHandler(){}


	//! get object position in the world
	virtual void GetPosition(float &X, float &Y, float &Z)
	{
		X = _PosX;
		Y = _PosY;
		Z = _PosZ;
	}


	//! set object position in the world
	virtual void SetPosition(float X, float Y, float Z)
	{
		_PosX = X;
		_PosY = Y;
		_PosZ = Z;
		_resetted = true;
	}


	//! move object in the world
	virtual void Move(float deltaX, float deltaY, float deltaZ, bool checkcollision = true)
	{
		_PosX += deltaX;
		_PosY += deltaY;
		_PosZ += deltaZ;

		_lastmoveX = deltaX;
		_lastmoveY = deltaY;
		_lastmoveZ = deltaZ;
	}


	//! get object rotation on all axis
	virtual void GetRotation(LbaQuaternion& Q)
	{
		_rotH.GetRotation(Q);
	}

	//! get object rotation on a single angle
	virtual float GetRotationYAxis()
	{
		return _rotH.GetRotationYAxis();
	}

	//! set object rotation on all axis
	virtual void SetRotation(const LbaQuaternion& Q)
	{
		_rotH.SetRotation(Q);
		_resetted = true;
	}

	//! move object to a position in the world
	virtual void MoveTo(float X, float Y, float Z)
	{
		_lastmoveX = X-_PosX;
		_lastmoveY = Y-_PosY;
		_lastmoveZ = Z-_PosZ;

		_PosX = X;
		_PosY = Y;
		_PosZ = Z;
	}


	//! rotate object in the world
	virtual void RotateTo(const LbaQuaternion& Q)
	{
		_rotH.RotateTo(Q);
	}


	//! rotate object in the world
	virtual void RotateYAxis(float Speed)
	{
		_lastrotation = Speed;
		_rotH.RotateYAxis(Speed);
	}



	//! destroy function - clear the object content
	virtual void Destroy(void){}
	
	//! get user data
	virtual boost::shared_ptr<ActorUserData> GetUserData()
	{return boost::shared_ptr<ActorUserData>();}


	//! show or hide the object
	virtual void ShowOrHide(bool Show){}

	//! ignore collision between two pairs of actors
	virtual void IgnoreCollisionWith(PhysicalObjectHandlerBase * actor){}

	//! add force to actor - only for dynamic actors
	virtual void AddForce(float X, float Y, float Z){}


	//! return internal actor - only for physX actor
	virtual NxActor* GetphysXInternalActor(){return NULL;}

	//! get last move
	virtual void GetLastMove(float &X, float &Y, float &Z) 
	{
		X = _lastmoveX;
		Y = _lastmoveY;
		Z = _lastmoveZ;
	}

	//! get last rotation
	virtual float GetLastRotation()
	{return _lastrotation;}


	//! check if actor is on top of other
	virtual bool OnTopOff(PhysicalObjectHandlerBase * actor)
	{return false;}


	//! reset last move
	virtual void ResetMove()
	{
		_lastmoveX = 0;
		_lastmoveY = 0;
		_lastmoveZ = 0;
		_lastrotation = 0;
	}


private:
	float _PosX;
	float _PosY;
	float _PosZ;

	float	_lastmoveX;
	float	_lastmoveY;
	float	_lastmoveZ;
	float	_lastrotation;

	SimpleRotationHandler _rotH;
};

#endif