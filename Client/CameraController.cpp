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

/***********************************************************
	Constructor
***********************************************************/
CameraController::CameraController()
: _lastactX(0), _lastactY(0), _lastactZ(0), _movecamera(false), _isGhost(false)
{

}


/***********************************************************
	Destructor
***********************************************************/
CameraController::~CameraController()
{

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
void CameraController::Process()
{
	if(!_character)
		return;

	boost::shared_ptr<PhysicalObjectHandlerBase> phys = _character->GetPhysicalObject();
	if(!phys)
		return;

	//float rotY = phys->GetRotationYAxis();
	//OsgHandler::getInstance()->SetCameraAzimut(rotY);


	float actX, actY, actZ;
	phys->GetPosition(actX, actY, actZ);
	double _targetx, _targety, _targetz;
	OsgHandler::getInstance()->GetCameraTarget(_targetx, _targety, _targetz);

	if(_isGhost)
	{
		OsgHandler::getInstance()->SetCameraTarget(actX, actY, actZ);
		_movecamera = false;
		return;
	}


	// start to move camera only when actor moves a certain distance
	if(abs(actX - _targetx) > 3 || abs(actY - _targety) > 3 || abs(actZ - _targetz) > 3)
		_movecamera = true;

	if(abs(actX - _targetx) > 6 || abs(actY - _targety) > 6 || abs(actZ - _targetz) > 6)
	{
		OsgHandler::getInstance()->SetCameraTarget(actX, actY, actZ);
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

		OsgHandler::getInstance()->SetCameraTarget(_targetx, _targety, _targetz);


		if(actX == _lastactX && actY == _lastactY && actZ == _lastactZ)
		{
			_movecamera = false;		
		}

	}

	_lastactX = actX;
	_lastactY = actY;
	_lastactZ = actZ;
}