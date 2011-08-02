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

#include "CameraController.h"
#include "DynamicObject.h"
#include "OSGHandler.h"

#include <iostream>
#include <math.h>

#define	_CAM_OFFSET_Y_	2

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif

/***********************************************************
	Constructor
***********************************************************/
CameraController::CameraController()
: _lastactX(0), _lastactY(0), _lastactZ(0), _movecamera(false), 
	_isGhost(false), _forcedghost(false)
{

}


/***********************************************************
	Destructor
***********************************************************/
CameraController::~CameraController()
{

}



/***********************************************************
key pressed
***********************************************************/
void CameraController::KeyPressed(LbanetKey keyid)
{
	switch(keyid)
	{
		case LbanetKey_Forward:
		{
			_pressedkeys._keyforward = true;
		}
		break;
		
		case LbanetKey_Backward:
		{
			_pressedkeys._keybackward = true;
		}
		break;
		
		case LbanetKey_Left:
		{
			_pressedkeys._keyleft = true;
		}
		break;
		
		case LbanetKey_Right:
		{
			_pressedkeys._keyright = true;
		}
		break;

		case LbanetKey_Up:
		{
			_pressedkeys._keyup = true;
		}
		break;
		
		case LbanetKey_Down:
		{
			_pressedkeys._keydown = true;
		}
		break;
	}
}

/***********************************************************
key released
***********************************************************/
void CameraController::KeyReleased(LbanetKey keyid)
{
	switch(keyid)
	{
		case LbanetKey_Forward:
		{
			_pressedkeys._keyforward = false;
		}
		break;
		
		case LbanetKey_Backward:
		{
			_pressedkeys._keybackward = false;
		}
		break;
		
		case LbanetKey_Left:
		{
			_pressedkeys._keyleft = false;
		}
		break;
		
		case LbanetKey_Right:
		{
			_pressedkeys._keyright = false;
		}
		break;

		case LbanetKey_Up:
		{
			_pressedkeys._keyup = false;
		}
		break;
		
		case LbanetKey_Down:
		{
			_pressedkeys._keydown = false;
		}
		break;

		
		case LbanetKey_All:
		{
			_pressedkeys._keyforward = false;
			_pressedkeys._keybackward = false;
			_pressedkeys._keyleft = false;
			_pressedkeys._keyright = false;
			_pressedkeys._keyup = false;
			_pressedkeys._keydown = false;
		}
		break;
	}
}



/***********************************************************
	Set character to control
***********************************************************/
void CameraController::SetCharacter(boost::shared_ptr<DynamicObject> charac, bool AsGhost)
{
	_character = charac;
	_isGhost = AsGhost;
}




/***********************************************************
process function
***********************************************************/
void CameraController::Process(double tnow, float tdiff)
{
	if(!_character)
		return;

	boost::shared_ptr<PhysicalObjectHandlerBase> phys = _character->GetPhysicalObject();
	if(!phys)
		return;

	//float rotY = phys->GetRotationYAxis();
	//double azimut = OsgHandler::getInstance()->GetCameraAzimut();
	//if(abs(rotY-azimut) > 1.0)
	//{
	//	double distance = (azimut - rotY);

	//	if((distance > 0 && distance < 180) || (distance < -180))
	//		OsgHandler::getInstance()->SetCameraAzimut(azimut - 0.3);
	//	else
	//		OsgHandler::getInstance()->SetCameraAzimut(azimut + 0.3);
	//}




	float actX, actY, actZ;
	phys->GetPosition(actX, actY, actZ);
	double _targetx, _targety, _targetz;
	OsgHandler::getInstance()->GetCameraTarget(_targetx, _targety, _targetz);
	_targety -= _CAM_OFFSET_Y_;

	if(_isGhost || _forcedghost)
	{
		float speedX = 0.0f;
		float speedY = 0.0f;
		float speedZ = 0.0f;

		//if right key pressed
		if(_pressedkeys._keyleft)
			speedX = -0.01f;
		else if(_pressedkeys._keyright)
			speedX = 0.01f;

		//if up key pressed
		if(_pressedkeys._keyforward)
			speedZ = -0.01f;
		else if(_pressedkeys._keybackward)
			speedZ = 0.01f;

		if(_pressedkeys._keyup)
			speedY = 0.01f;
		else if(_pressedkeys._keydown)
			speedY = -0.01f;

		double azimut = OsgHandler::getInstance()->GetCameraAzimut();

		LbaQuaternion Q((float)azimut, LbaVec3(0, 1, 0));
		LbaVec3 current_directionX(Q.GetDirection(LbaVec3(1, 0, 0)));
		LbaVec3 current_directionZ(Q.GetDirection(LbaVec3(0, 0, 1)));


		float ajustedspeedx = speedX*current_directionX.x + speedZ*current_directionX.z;
		float ajustedspeedz = speedX*current_directionZ.x + speedZ*current_directionZ.z;



		OsgHandler::getInstance()->SetCameraTarget(_targetx+ajustedspeedx*tdiff, 
													_targety+speedY*tdiff+_CAM_OFFSET_Y_,
													_targetz+ajustedspeedz*tdiff);

		_movecamera = false;
		return;
	}


	// start to move camera only when actor moves a certain distance
	if(abs(actX - _targetx) > 3 || abs(actY - _targety) > 3 || abs(actZ - _targetz) > 3)
		_movecamera = true;

	if(abs(actX - _targetx) > 6 || abs(actY - _targety) > 6 || abs(actZ - _targetz) > 6)
	{
		OsgHandler::getInstance()->SetCameraTarget(actX, actY+_CAM_OFFSET_Y_, actZ);
		_movecamera = false;
		return;
	}


	if(_movecamera)
	{
		double speedX = (actX - _lastactX);
		double speedY = (actY - _lastactY);
		double speedZ = (actZ - _lastactZ);
		_targetx+=speedX;
		_targety+=speedY;
		_targetz+=speedZ;

		double deltaX = (actX - _targetx);
		double deltaY = (actY - _targety);
		double deltaZ = (actZ - _targetz);

		if(abs(deltaX) > 0.1)
			_targetx+=deltaX/100;
		if(abs(deltaY) > 0.1)
			_targety+=deltaY/100;
		if(abs(deltaZ) > 0.1)
			_targetz+=deltaZ/100;

		OsgHandler::getInstance()->SetCameraTarget(_targetx, _targety+_CAM_OFFSET_Y_, _targetz);


		if(actX == _lastactX && actY == _lastactY && actZ == _lastactZ)
		{
			_movecamera = false;		
		}

	}

	_lastactX = actX;
	_lastactY = actY;
	_lastactZ = actZ;
}



/***********************************************************
center camera on player
***********************************************************/
void CameraController::Center()
{
	boost::shared_ptr<PhysicalObjectHandlerBase> phys = _character->GetPhysicalObject();
	if(!phys)
		return;

	float rotY = phys->GetRotationYAxis();
	float actX, actY, actZ;
	phys->GetPosition(actX, actY, actZ);


	OsgHandler::getInstance()->SetCameraAzimut(rotY);
	OsgHandler::getInstance()->SetCameraTarget(actX, actY+_CAM_OFFSET_Y_, actZ);
	_movecamera = false;
}