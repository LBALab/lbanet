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
#include "ActorUserData.h"
#include "ClientExtendedEvents.h"

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
	_keyaction = false;
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

		case LbanetKey_Action:
		{
			if(!_keyaction)
			{
				double tnow = SynchronizedTimeHandler::GetCurrentTimeDouble();
				_keyaction = true;

				EventsQueue::getSenderQueue()->AddEvent(new LbaNet::PressedActionKeyEvent(tnow, false));

				LbaNet::ModelState newstate;
				if(_currentmode && _currentmode->ChangeStateOnPressAction(newstate))
					UpdateModeAndState(_currentmodestr, newstate, tnow);
			}
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

		case LbanetKey_Action:
		{
			if(_keyaction)
			{
				double tnow = SynchronizedTimeHandler::GetCurrentTimeDouble();
				_keyaction = false;

				LbaNet::ModelState newstate;
				if(_currentmode && _currentmode->ChangeStateOnReleaseAction(newstate))
					UpdateModeAndState(_currentmodestr, newstate, tnow);
			}
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
	boost::shared_ptr<DisplayObjectHandlerBase> diso = _character->GetDisplayObject();

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
		bool moving = false;
		bool IsIdle = true;
		bool allowedmoving = false;
		bool allowedrotating = false;
		bool standoniddle = false;
		bool canfly = false;
		bool checkgravity = true;
		bool checkwater = true;

		float speedX = 0;
		float speedY = 0;
		float speedZ = 0;

		if(_currentstate)
		{
			allowedmoving = _currentstate->AllowedMoving();
			allowedrotating = _currentstate->AllowedRotating();
			standoniddle = _currentstate->StandOnIddle();
			checkgravity = checkgravity && !(_currentstate->IsImmuneGravity());
			checkwater = checkwater && !(_currentstate->IsImmuneDrowning());
		}
		if(_currentmode)
		{
			canfly = _currentmode->CanFly();
			checkgravity = checkgravity && _currentmode->NeedCheckForGravity();
			checkwater = checkwater && _currentmode->NeedCheckForWater();
		}


		// check for moving forward/backward
		if(allowedmoving)
		{	
			if(_keyforward)
			{
				//update animation
				int resupd = diso->Update(new LbaNet::AnimationStringUpdate("MoveForward"));
				if(resupd == 0)
				{
					IsIdle = false;
					moving = true;
				}			
			}
			else if(_keybackward)
			{
				//update animation
				int resupd = diso->Update(new LbaNet::AnimationStringUpdate("MoveBackward"));
				if(resupd == 0)
				{
					IsIdle = false;
					moving = true;
				}	
			}

			if(canfly)
			{
				if(_keyup)
				{
					IsIdle = false;
					speedY += (0.01f * tdiff);
				}
				else if(_keydown)
				{
					IsIdle = false;
					speedY -= (0.01f * tdiff);
				}
			}
		}

		// check for rotating
		if(allowedrotating)
		{
			if(_keyleft)
			{
				if(!moving)
				{
					//update animation
					diso->Update(new LbaNet::AnimationStringUpdate("TurnLeft"));
					IsIdle = false;
				}

				physo->RotateYAxis(0.15f*tdiff);
			}
			else if(_keyright)
			{
				if(!moving)
				{
					//update animation
					diso->Update(new LbaNet::AnimationStringUpdate("TurnRight"));
					IsIdle = false;
				}

				physo->RotateYAxis(-0.15f*tdiff);
			}
		}

		// update to standing pose if needed
		if(IsIdle && standoniddle)
		{
			//update animation
			diso->Update(new LbaNet::AnimationStringUpdate("Stand"));
		}


		// inform mode and state that we are moving
		if(moving)
		{
			if(_currentstate)
				_currentstate->InformMoving();

			if(_currentmode)
				_currentmode->CharacterMoving();
		}
		else
		{
			if(_currentmode)
				_currentmode->CharacterStoppedMoving();
		}


		// get speed of animation
		if(_currentmode)
		{
			if(_currentmode->UseAnimationSpeed())
			{	
				speedX += diso->GetCurrentAssociatedSpeedX() * tdiff;
				speedY += diso->GetCurrentAssociatedSpeedY() * tdiff;
				speedZ += diso->GetCurrentAssociatedSpeedZ() * tdiff;
			}

			speedX += _currentmode->GetAddedSpeedX() * tdiff;
		}


		// check for gravity
		if(checkgravity)
			speedY -= (0.05f * tdiff); //TODO - make the gravity configurable?

		// move the physical shape
		LbaQuaternion Q;
		physo->GetRotation(Q);
		LbaVec3 current_directionX(Q.GetDirection(LbaVec3(0, 0, 1)));
		LbaVec3 current_directionZ(Q.GetDirection(LbaVec3(1, 0, 0)));
		float ajustedspeedx = speedX*current_directionX.x + speedZ*current_directionZ.x;
		float ajustedspeedZ = speedX*current_directionX.z + speedZ*current_directionZ.z;

		physo->Move(ajustedspeedx, speedY, ajustedspeedZ);
		boost::shared_ptr<ActorUserData> udata = physo->GetUserData();
		bool touchground = true;
		int touchedfloormaterial = 0;
		if(udata)
		{
			touchground = udata->GetTouchingGround();
			touchedfloormaterial = udata->GetHittedFloorMaterial();
		}



		// check if we are falling down
		if(checkgravity)
		{
			// get current position
			float cX, cY, CZ;
			physo->GetPosition(cX, cY, CZ);


			// if the actor does not touch the ground it means he is falling down
			if(!touchground /*&& !_player->IsAttached()*/) // TODO attach system
			{
				if(!_chefkiffall)
				{
					_chefkiffall = true;
					_ycheckiffall = cY;
				}
				else
				{
					float fallsize = (_ycheckiffall - cY);
					if(fallsize > 0.2)
					{
						// start fall down state
						UpdateModeAndState(_currentmodestr, LbaNet::StFalling, tnow);
					}
				}

				// additionnal check if we go out of map - if yes then just die
				if(cY < -5)
					UpdateModeAndState(_currentmodestr, LbaNet::StDying, tnow);
			}
			else
			{
				_chefkiffall = false;

				//if we were falling down then player will be hurt by touching the ground
				if(_currentstatestr == LbaNet::StFalling)
				{
					float fallsize = _ycheckiffall - cY;

					if(fallsize > 1.5)
					{
						if(fallsize > 6)
						{
							// go to hurt state as fall was very big
							UpdateModeAndState(_currentmodestr, LbaNet::StHurtFall, tnow, fallsize);
						}
						else
						{
							// go to landed state as fall is not that big
							UpdateModeAndState(_currentmodestr, LbaNet::StFinishedFall, tnow, fallsize);
						}
					}
					else
					{
						// go back to normal state as this was a very small fall
						UpdateModeAndState(_currentmodestr, LbaNet::StNormal, tnow);
					}
				}
			}
			
		}

		// check if we touch water
		if(checkwater)
		{
			if(touchground)
			{
				if(touchedfloormaterial == 17)	// water
					UpdateModeAndState(_currentmodestr, LbaNet::StDrowning, tnow);

				if(touchedfloormaterial == 18)	// gaz
					UpdateModeAndState(_currentmodestr, LbaNet::StDrowningGas, tnow);

				if(touchedfloormaterial == 19)	// lava
					UpdateModeAndState(_currentmodestr, LbaNet::StBurning, tnow);
			}
		}

		

	}

	//update display and animation
	bool animfinished = false;
	int pout = _character->Process(tnow, tdiff);
	animfinished = (pout == 1);


	// do last check for state
	if(_currentstate)
	{
		// inform state if animation is finished
		if(animfinished)
		{
			bool shouldpause = _currentstate->AnimationFinished();

			// pause animation if necessary
			if(shouldpause)
				diso->Update(new LbaNet::PauseAnimationUpdate());
		}


		// check if state should be changed
		LbaNet::ModelState newstate;
		if(_currentstate->ShouldChangeState(newstate))
			UpdateModeAndState(_currentmodestr, newstate, tnow);
	}



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

	// lifeUpdate
	if(info == typeid(LbaNet::ObjectLifeInfoUpdate))
	{
		LbaNet::ObjectLifeInfoUpdate * castedptr = 
			dynamic_cast<LbaNet::ObjectLifeInfoUpdate *>(update.get());

		// update gui with new life info
		EventsQueue::getReceiverQueue()->AddEvent(new UpdateGuiLifeEvent(
			castedptr->Update.CurrentLife / castedptr->Update.MaxLife, 
			castedptr->Update.CurrentMana / castedptr->Update.MaxMana));
		
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

		if(_currentmodestr == "Normal")
		{
			_currentmode = boost::shared_ptr<CharacterModeBase>(new NormalCharacterMode());
		}

		if(_currentmodestr == "Sport")
		{
			_currentmode = boost::shared_ptr<CharacterModeBase>(new SportyCharacterMode());
		}

		if(_currentmodestr == "Angry")
		{
			_currentmode = boost::shared_ptr<CharacterModeBase>(new AggresiveCharacterMode());
		}

		if(_currentmodestr == "Discrete")
		{
			_currentmode = boost::shared_ptr<CharacterModeBase>(new DiscreteCharacterMode());
		}		

		if(_currentmodestr == "Protopack")
		{
			_currentmode = boost::shared_ptr<CharacterModeBase>(new ProtopackCharacterMode());
		}

		if(_currentmodestr == "Horse")
		{
			_currentmode = boost::shared_ptr<CharacterModeBase>(new HorseCharacterMode());
		}

		if(_currentmodestr == "Dinofly")
		{
			_currentmode = boost::shared_ptr<CharacterModeBase>(new DinoflyCharacterMode());
		}		
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
			case LbaNet::StFinishedFall:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StFinishedFall());						
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
			case LbaNet::StFighting:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StFighting());						
			}
			break;

		}

		if(_currentstate)
		{
			std::string animstring;
			if(_currentstate->PlayAnimationAtStart(animstring))
			{
				//update animation
				_character->GetDisplayObject()->Update(new LbaNet::AnimationStringUpdate(animstring));
			}
		}

		// inform mode that state changed
		if(_currentmode)
			_currentmode->CharacterChangedState();

		//inform server that state is updated
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateStateEvent(tnow, newstate, FallingSize));
	}
}