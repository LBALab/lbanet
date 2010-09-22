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

#include "CharacterControllerLBA.h"
#include "PhysicalObjectHandlerBase.h"


#include <iostream>
#include <math.h>

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


/***********************************************************
	Constructor
***********************************************************/
CharacterController::CharacterController()
: _isGhost(false)
{
	_keyforward = false;
	_keybackward = false;
	_keyleft = false;
	_keyright = false;
	_keyup = false;
	_keydown = false;
}


/***********************************************************
	Destructor
***********************************************************/
CharacterController::~CharacterController()
{

}


/***********************************************************
	Set character to control
***********************************************************/
void CharacterController::SetPhysicalCharacter(boost::shared_ptr<PhysicalObjectHandlerBase> charac, bool AsGhost)
{
	_character = charac;
	_isGhost = AsGhost;
}


/***********************************************************
key pressed
***********************************************************/
void CharacterController::KeyPressed(LbanetKey keyid)
{
	switch(keyid)
	{
		case LbanetKey_Forward:
		{
			_keyforward = true;
		}
		break;
		
		case LbanetKey_Backward:
		{
			_keybackward = true;
		}
		break;
		
		case LbanetKey_Left:
		{
			_keyleft = true;
		}
		break;
		
		case LbanetKey_Right:
		{
			_keyright = true;
		}
		break;

		case LbanetKey_Up:
		{
			_keyup = true;
		}
		break;
		
		case LbanetKey_Down:
		{
			_keydown = true;
		}
		break;
	}
}

/***********************************************************
key released
***********************************************************/
void CharacterController::KeyReleased(LbanetKey keyid)
{
	switch(keyid)
	{
		case LbanetKey_Forward:
		{
			_keyforward = false;
		}
		break;
		
		case LbanetKey_Backward:
		{
			_keybackward = false;
		}
		break;
		
		case LbanetKey_Left:
		{
			_keyleft = false;
		}
		break;
		
		case LbanetKey_Right:
		{
			_keyright = false;
		}
		break;

		case LbanetKey_Up:
		{
			_keyup = false;
		}
		break;
		
		case LbanetKey_Down:
		{
			_keydown = false;
		}
		break;


	}
}


/***********************************************************
process function
***********************************************************/
void CharacterController::Process()
{
	if(_isGhost)
	{
		float speedX = 0.0f;
		float speedY = 0.0f;
		float speedZ = 0.0f;

		//if right key pressed
		if(_keyleft)
			speedX = -1.0f;
		else if(_keyright)
			speedX = 1.0f;

		//if up key pressed
		if(_keyforward)
			speedZ = -1.0f;
		else if(_keybackward)
			speedZ = 1.0f;

		if(_keyup)
			speedY = 1.0f;
		else if(_keydown)
			speedY = -1.0f;

		_character->Move(speedX, speedY, speedZ, false);
	}
	else
	{
		if(_keyleft)
			_character->RotateYAxis(1.0f);
		else if(_keyright)
			_character->RotateYAxis(-1.0f);

		float speed = 0;
		if(_keyforward)
			speed = 0.1f;
		else if(_keybackward)
			speed = -0.1f;

		//if(_keyforward || _keybackward)
		//{
			LbaQuaternion Q;
			_character->GetRotation(Q);
			LbaVec3 current_direction(Q.GetDirection(LbaVec3(0, 0, 1)));
			 _character->Move(current_direction.x*speed, -1, current_direction.z*speed);
		//}
	}
}

