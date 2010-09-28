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
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "DynamicObject.h"

#include <iostream>
#include <math.h>

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


/***********************************************************
	Constructor
***********************************************************/
CharacterController::CharacterController()
: _isGhost(false), _lastupdatetime(0)
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
void CharacterController::SetPhysicalCharacter(boost::shared_ptr<DynamicObject> charac, 
												const LbaNet::ModelInfo &Info,
												bool AsGhost)
{
	_character = charac;
	_isGhost = AsGhost;

	// update last position
	_character->GetPhysicalObject()->GetPosition(_lastupdate.CurrentPos.X, 
							_lastupdate.CurrentPos.Y, 
							_lastupdate.CurrentPos.Z);

	_lastupdate.CurrentPos.Rotation = _character->GetPhysicalObject()->GetRotationYAxis();

	// update mode if needed
	if(!_isGhost)
		UpdateModeAndState(Info.Mode, Info.State, SynchronizedTimeHandler::GetCurrentTimeDouble(), 0);
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
void CharacterController::Process(double tnow, float tdiff)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();

	if(_isGhost)
	{
		float speedX = 0.0f;
		float speedY = 0.0f;
		float speedZ = 0.0f;

		//if right key pressed
		if(_keyleft)
			speedX = -0.01f;
		else if(_keyright)
			speedX = 0.01f;

		//if up key pressed
		if(_keyforward)
			speedZ = -0.01f;
		else if(_keybackward)
			speedZ = 0.01f;

		if(_keyup)
			speedY = 0.01f;
		else if(_keydown)
			speedY = -0.01f;

		physo->Move(speedX*tdiff, speedY*tdiff, speedZ*tdiff, false);
	}
	else
	{
		//TODO
		if(_keyleft)
			physo->RotateYAxis(0.15f*tdiff);
		else if(_keyright)
			physo->RotateYAxis(-0.15f*tdiff);

		float speed = 0;
		if(_keyforward)
			speed = 0.01f;
		else if(_keybackward)
			speed = -0.01f;

		LbaQuaternion Q;
		physo->GetRotation(Q);
		LbaVec3 current_direction(Q.GetDirection(LbaVec3(0, 0, 1)));
		 physo->Move(current_direction.x*speed*tdiff, -0.1f*tdiff, current_direction.z*speed*tdiff);
	}

	//update display
	_character->Process(tnow, tdiff);

	// update server if needed
	UpdateServer(tnow, tdiff);
}



/***********************************************************
check if we need to send update to server
***********************************************************/
void CharacterController::UpdateServer(double tnow, float tdiff)
{
	// do nothing if ghost
	if(_isGhost)
	{
		_oldtdiff = tdiff;
		return;
	}

	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();

	// get current position
	physo->GetPosition(_currentupdate.CurrentPos.X, 
							_currentupdate.CurrentPos.Y, 
							_currentupdate.CurrentPos.Z);

	// get current rotation
	_currentupdate.CurrentPos.Rotation = physo->GetRotationYAxis();


	// set speed
	_currentupdate.CurrentSpeedX = (_currentupdate.CurrentPos.X-_lastupdate.CurrentPos.X) / _oldtdiff;
	_currentupdate.CurrentSpeedY = (_currentupdate.CurrentPos.Y-_lastupdate.CurrentPos.Y) / _oldtdiff;
	_currentupdate.CurrentSpeedZ = (_currentupdate.CurrentPos.Z-_lastupdate.CurrentPos.Z) / _oldtdiff;

	//calculate angle speed
	_currentupdate.CurrentSpeedRotation = (_currentupdate.CurrentPos.Rotation-
													_lastupdate.CurrentPos.Rotation);
	while(_currentupdate.CurrentSpeedRotation < -180) 
		_currentupdate.CurrentSpeedRotation += 360;
	while(_currentupdate.CurrentSpeedRotation > 180) 
		_currentupdate.CurrentSpeedRotation -= 360;


	_currentupdate.CurrentSpeedRotation /= tdiff;
	

	_oldtdiff = tdiff;


	// set animation
	_currentupdate.AnimationIdx = _character->GetDisplayObject()->GetCurrentAnimation();



	// check if we should force the update
	_currentupdate.ForcedChange = ShouldforceUpdate();


	//else send regular update every seconds
	bool updatebytime = false;
	if(!_currentupdate.ForcedChange)
	{
		if((tnow - _lastupdatetime) > 1000) // if more than 1 second
			updatebytime = true;
	}


	//send to server if needed
	if(_currentupdate.ForcedChange || updatebytime)
	{
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::PlayerMovedEvent(tnow, 0, _currentupdate));
		_lastupdatetime = tnow;
	}

	_lastupdate = _currentupdate;
}



/***********************************************************
check if we should force the update
***********************************************************/
bool CharacterController::ShouldforceUpdate()
{
	if(_lastupdate.AnimationIdx != _currentupdate.AnimationIdx)
		return true;



	if(abs(_lastupdate.CurrentSpeedX - _currentupdate.CurrentSpeedX) > 0.00001f)
		return true;

	if(abs(_lastupdate.CurrentSpeedY - _currentupdate.CurrentSpeedY) > 0.00001f)
		return true;

	if(abs(_lastupdate.CurrentSpeedZ - _currentupdate.CurrentSpeedZ) > 0.00001f)
		return true;

	if(abs(_lastupdate.CurrentSpeedRotation - _currentupdate.CurrentSpeedRotation) > 0.1f)
		return true;



	float diffpos = abs(_lastupdate.CurrentPos.X - _currentupdate.CurrentPos.X) 
					+ abs(_lastupdate.CurrentPos.Y - _currentupdate.CurrentPos.Y) 
					+  abs(_lastupdate.CurrentPos.Z - _currentupdate.CurrentPos.Z);
	if(diffpos > 10)
		return true;


	double diffrot = abs(_lastupdate.CurrentPos.Rotation - _currentupdate.CurrentPos.Rotation);
	if(diffrot > 10)
		return true;


	return false;
}


/***********************************************************
update player display
***********************************************************/
void CharacterController::UpdateDisplay(LbaNet::DisplayObjectUpdateBasePtr update)
{
	const std::type_info& info = typeid(*update);

	// ModelUpdate
	if(info == typeid(LbaNet::ModelUpdate))
	{
		LbaNet::ModelUpdate * castedptr = 
			dynamic_cast<LbaNet::ModelUpdate *>(update.get());

		UpdateModeAndState(castedptr->Info.Mode, castedptr->Info.State, 
							SynchronizedTimeHandler::GetCurrentTimeDouble(), 0);
	}

	_character->GetDisplayObject()->Update(update);
}



/***********************************************************
internaly update mode and state
***********************************************************/
void CharacterController::UpdateModeAndState(const std::string &newmode,
												LbaNet::ModelState newstate,
												double tnow,
												float FallingSize)
{
	// only update if different
	if(newmode != _currentmodestr)
	{
		_currentmodestr = newmode;

		//TODO
	}

	// only update if different
	if(newstate != _currentstatestr)
	{
		_currentstatestr = newstate;
		switch(_currentstatestr)
		{
			case LbaNet::StNormal:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StNormal());
			}
			break;
			case LbaNet::StDying:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StDying());			
			}
			break; 
			case LbaNet::StDrowning:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StDrowning());			
			}
			break; 
			case LbaNet::StDrowningGas:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StDrowningGas());		
			}
			break; 
			case LbaNet::StBurning:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StBurning());						
			}
			break; 
			case LbaNet::StSmallHurt:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StSmallHurt());						
			}
			break; 
			case LbaNet::StMediumHurt:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StMediumHurt());						
			}
			break; 
			case LbaNet::StBigHurt:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StBigHurt());						
			}
			break; 
			case LbaNet::StHurtFall:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StHurtFall());						
			}
			break; 
			case LbaNet::StFalling:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StFalling());					
			}
			break; 
			case LbaNet::StJumping:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StJumping());						
			}
			break; 
			case LbaNet::StMovingObject:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StMovingObject());						
			}
			break; 
			case LbaNet::StRestrictedMovingObject:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StRestrictedMovingObject());						
			}
			break; 
			case LbaNet::StUseWeapon:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StUseWeapon());						
			}
			break; 
			case LbaNet::StImmune:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StImmune());						
			}
			break; 
			case LbaNet::StProtectedHurt:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StProtectedHurt());						
			}
			break; 
			case LbaNet::StHidden:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StHidden());						
			}
			break; 
			case LbaNet::StScripted:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StScripted());						
			}
			break;
		}

		if(_currentstate)
		{
			std::string animstring;
			if(_currentstate->PlayAnimationAtStart(animstring))
			{
				//TODO update animation
			}
		}

		// inform mode that state changed
		if(_currentmode)
			_currentmode->CharacterChangedState();

		//inform server that state is updated
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateStateEvent(tnow, newstate, FallingSize));
	}
}