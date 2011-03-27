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
#include "SharedDataHandler.h"
#include "ScriptEnvironmentBase.h"


#include <iostream>
#include <math.h>

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


/***********************************************************
	Constructor
***********************************************************/
CharacterController::CharacterController()
: _isGhost(false), _lastupdatetime(0), _forcedghost(false), _projectilelaunched(false)
{

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

	// reset attached actor
	_attachedactor = boost::shared_ptr<DynamicObject>();


	// update last position
	_character->GetPhysicalObject()->GetPosition(_lastupdate.CurrentPos.X,
							_lastupdate.CurrentPos.Y,
							_lastupdate.CurrentPos.Z);

	_lastupdate.CurrentPos.Rotation = _character->GetPhysicalObject()->GetRotationYAxis();

	// update mode if needed
	if(!_isGhost)
	{
		UpdateModeAndState(Info.Mode, Info.State, SynchronizedTimeHandler::GetCurrentTimeDouble(), 0);

		//inform gui
		EventsQueue::getReceiverQueue()->AddEvent(new GuiRefreshPlayerColorEvent(
													Info.SkinColor, Info.EyesColor, Info.HairColor));
	}

	#ifdef _USE_QT_EDITOR_
	{
			EventsQueue::getReceiverQueue()->AddEvent(new EditorPlayerMovedEvent(	_lastupdate.CurrentPos.X,
																					_lastupdate.CurrentPos.Y,
																					_lastupdate.CurrentPos.Z));
	}
	#endif
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

		case LbanetKey_Action:
		{
			_pressedkeys._keyaction = true;
		}
		break;

		case LbanetKey_Weapon:
		{
			_pressedkeys._keyweapon = true;
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

		case LbanetKey_Action:
		{
			_pressedkeys._keyaction = false;
		}
		break;

		case LbanetKey_Weapon:
		{
			_pressedkeys._keyweapon = false;
		}
		break;
	}
}


/***********************************************************
process function
***********************************************************/
void CharacterController::Process(double tnow, float tdiff,
									ScriptEnvironmentBase* scripthandler)
{
	// do nothing if ghost
	if(_forcedghost || _isGhost)
	{
		_oldtdiff = tdiff;
		return;
	}


	if(_currentplayerstate == LbaNet::StScripted)
	{
		// process script
		if(!ProcessScript(tnow, tdiff, scripthandler))
		{
			// if not moved check attached
			if(_attachedactor)
			{
				boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
				boost::shared_ptr<PhysicalObjectHandlerBase> attchedphys = _attachedactor->GetPhysicalObject();
				if(physo && attchedphys)
				{
					physo->RotateYAxis(attchedphys->GetLastRotation());

					float addspeedX=0, addspeedY=0, addspeedZ=0;
					attchedphys->GetLastMove(addspeedX, addspeedY, addspeedZ);
					physo->Move(addspeedX, addspeedY, addspeedZ);
				}
			}
		}

		// update server if needed
		UpdateServer(tnow, tdiff);

		return;
	}



	//update display and animation
	bool animfinished = false;
	int pout = _character->Process(tnow, tdiff);
	animfinished = (pout == 1);



	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
	boost::shared_ptr<DisplayObjectHandlerBase> diso = _character->GetDisplayObject();



	bool moving = false;
	bool IsIdle = true;
	bool allowedmoving = false;
	int allowedrotating = 0;
	int standoniddle = 0;
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
		if(_pressedkeys._keyforward)
		{
			//update animation
			int resupd = diso->Update(new LbaNet::AnimationStringUpdate("MoveForward"), false);
			if(resupd == 0)
			{
				IsIdle = false;
				moving = true;
			}
		}
		else if(_pressedkeys._keybackward)
		{
			//update animation
			int resupd = diso->Update(new LbaNet::AnimationStringUpdate("MoveBackward"), false);
			if(resupd == 0)
			{
				IsIdle = false;
				moving = true;
			}
		}

		if(canfly)
		{
			if(_pressedkeys._keyup)
			{
				IsIdle = false;
				speedY += (0.01f * tdiff);
			}
			else if(_pressedkeys._keydown)
			{
				IsIdle = false;
				speedY -= (0.01f * tdiff);
			}
		}
	}

	float rotation = 0;

	// check for rotating
	if(allowedrotating > 0)
	{
		if(_pressedkeys._keyleft)
		{
			if(!moving && (allowedrotating == 1))
			{
				//update animation
				diso->Update(new LbaNet::AnimationStringUpdate("TurnLeft"), false);
				IsIdle = false;
			}
			rotation = 0.15f*tdiff;
		}
		else if(_pressedkeys._keyright)
		{
			if(!moving && (allowedrotating == 1))
			{
				//update animation
				diso->Update(new LbaNet::AnimationStringUpdate("TurnRight"), false);
				IsIdle = false;
			}
			rotation = -0.15f*tdiff;
		}
	}

	float extrarotation = 0;
	if(_attachedactor)
	{
		boost::shared_ptr<PhysicalObjectHandlerBase> attchedphys = _attachedactor->GetPhysicalObject();
		if(attchedphys)
			extrarotation = attchedphys->GetLastRotation();
		
	}

	physo->RotateYAxis(rotation+extrarotation);


	// update to standing pose if needed
	if(IsIdle && standoniddle > 0)
	{
		if(standoniddle == 2) //change to normal state
			UpdateModeAndState(_currentmodestr, LbaNet::StNormal, tnow);			
		else if(diso)
			diso->Update(new LbaNet::AnimationStringUpdate("Stand"), false); //update animation
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
		if(diso && _currentmode->UseAnimationSpeed())
		{
			speedX += diso->GetCurrentAssociatedSpeedX() * tdiff;
			speedY += diso->GetCurrentAssociatedSpeedY() * tdiff;
			speedZ += diso->GetCurrentAssociatedSpeedZ() * tdiff;
		}

		speedX += _currentmode->GetAddedSpeedX() * tdiff;
		
		if(_currentstate)
			_currentstate->ModifyYVelocity(speedY);
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


	// get additional speed in case we are on lift
	if(_attachedactor)
	{
		float addspeedX=0, addspeedY=0, addspeedZ=0;

		boost::shared_ptr<PhysicalObjectHandlerBase> attchedphys = _attachedactor->GetPhysicalObject();
		if(attchedphys)
			attchedphys->GetLastMove(addspeedX, addspeedY, addspeedZ);
		
		ajustedspeedx+=addspeedX;
		ajustedspeedZ+=addspeedZ;

		if(addspeedY <= 0)
		{
			speedY += addspeedY;
			_attachedactor = boost::shared_ptr<DynamicObject>(); // dettach actor afterwards
		}
		else
		{
			//check if we are still on the actor
			if(physo->OnTopOff(attchedphys.get()))
			{
				checkgravity = false;
				speedY = addspeedY;
			}
			else
			{
				_attachedactor = boost::shared_ptr<DynamicObject>(); // dettach actor
			}
		}
	}


	// move actor
	physo->Move(ajustedspeedx, speedY, ajustedspeedZ);


	// check for touched ground and attached actor
	bool touchground = true;
	int touchedfloormaterial = 0;
	boost::shared_ptr<ActorUserData> udata = physo->GetUserData();
	if(udata)
	{
		touchground = udata->GetTouchingGround();

		if(touchground)
		{
			std::vector<HitInfo> hitvec;
			udata->GetHittedActors(hitvec);
			for(size_t i=0; i< hitvec.size(); ++i)
			{
				HitInfo &hi = hitvec[i];
				if(hi.ActorObjType == 5)
				{
					// hitted an object - loot it
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerLootItemEvent(hi.ActorId));
				}
				else
				{
					if(hi.HitBottom)
					{
						touchedfloormaterial = hi.FloorMaterial;

						if(scripthandler)
							_attachedactor = scripthandler->GetActor(hi.ActorObjType, hi.ActorId);
					}
					else
					{
						if(hi.ActorPhysType == LbaNet::KynematicAType)
						{
							//if we go forward
							if(speedX > 0)
							{
								int hittedAct = _currentstate->HurtActorsOnMove();
								if(hittedAct > 0)
								{
									//we touched an actor - hit him
									EventsQueue::getSenderQueue()->AddEvent(new LbaNet::PlayerHittedContactActorEvent(
																	SynchronizedTimeHandler::GetCurrentTimeDouble(),
																	(hittedAct==2), hi.ActorObjType, hi.ActorId));	
								}
							}
						}
					}
				}
			}

			// only move object when moving forward
			if(udata->GetMovingObject() && _pressedkeys._keyforward)
			{
				_movingstarttime = tnow;

				//only move object if we can
				if(_currentstate && _currentstate->CanPlayMovingObject())
					UpdateModeAndState(_currentmodestr, LbaNet::StMovingObject, tnow);
			}
			else
			{
				// stop moving object after a while if we dont touch anything
				if(_currentplayerstate == LbaNet::StMovingObject)
				{
					if(!_pressedkeys._keyforward || (tnow-_movingstarttime) >= 2000)
						UpdateModeAndState(_currentmodestr, LbaNet::StNormal, tnow);
				}
			}
		}
	}



	// check if we are falling down
	if(checkgravity)
	{
		// get current position
		float cX, cY, CZ;
		physo->GetPosition(cX, cY, CZ);


		// if the actor does not touch the ground it means he is falling down
		if(!touchground)
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
			if(_currentplayerstate == LbaNet::StFalling)
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


	// do last check for state
	bool changedstate = false;
	if(_currentstate)
	{
		// inform state if animation is finished
		if(animfinished)
		{
			bool shouldpause = _currentstate->AnimationFinished();

			// pause animation if necessary
			if(diso && shouldpause)
				diso->Update(new LbaNet::PauseAnimationUpdate(), false);
		}


		// check if state should be changed by state
		LbaNet::ModelState newstate;
		if(_currentstate->ShouldChangeState(newstate))
		{
			UpdateModeAndState(_currentmodestr, newstate, tnow);
			changedstate = true;
		}
	}


	// check if state should be changed by mode
	LbaNet::ModelState newstate;
	if(!_chefkiffall && !changedstate && _currentmode && 
		_currentmode->ChangeState(_currentplayerstate, _pressedkeys, newstate))
		UpdateModeAndState(_currentmodestr, newstate, tnow);


	// process weapon
	if(_pressedkeys._keyweapon)
		WeaponUsed();
	else
		if(!_projectilelaunched) // stop weapon except if magic ball already launched
			StopUseWeapon();


	// update server if needed
	UpdateServer(tnow, tdiff);
}



/***********************************************************
check if we need to send update to server
***********************************************************/
void CharacterController::UpdateServer(double tnow, float tdiff)
{
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


	boost::shared_ptr<DisplayObjectHandlerBase> diso = _character->GetDisplayObject();

	// set animation
	if(diso)
		_currentupdate.AnimationIdx = diso->GetCurrentAnimation();



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
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::PlayerMovedEvent(tnow, 0, _currentupdate, false));
		_lastupdatetime = tnow;
	}

	#ifdef _USE_QT_EDITOR_
	{
		float diffpos = abs(_lastupdate.CurrentPos.X - _currentupdate.CurrentPos.X)
						+ abs(_lastupdate.CurrentPos.Y - _currentupdate.CurrentPos.Y)
						+  abs(_lastupdate.CurrentPos.Z - _currentupdate.CurrentPos.Z);
		if(diffpos > 0.001)
			EventsQueue::getReceiverQueue()->AddEvent(new EditorPlayerMovedEvent(	_currentupdate.CurrentPos.X,
																					_currentupdate.CurrentPos.Y,
																					_currentupdate.CurrentPos.Z));
	}
	#endif


	_lastupdate = _currentupdate;
}



/***********************************************************
check if we should force the update
***********************************************************/
bool CharacterController::ShouldforceUpdate()
{
	if(_lastupdate.AnimationIdx != _currentupdate.AnimationIdx)
		return true;



	if(fabs(_lastupdate.CurrentSpeedX - _currentupdate.CurrentSpeedX) > 0.00001f)
		return true;

	if(fabs(_lastupdate.CurrentSpeedY - _currentupdate.CurrentSpeedY) > 0.00001f)
		return true;

	if(fabs(_lastupdate.CurrentSpeedZ - _currentupdate.CurrentSpeedZ) > 0.00001f)
		return true;

	if(fabs(_lastupdate.CurrentSpeedRotation - _currentupdate.CurrentSpeedRotation) > 0.01f)
		return true;



	float diffpos = fabs(_lastupdate.CurrentPos.X - _currentupdate.CurrentPos.X)
					+ fabs(_lastupdate.CurrentPos.Y - _currentupdate.CurrentPos.Y)
					+  fabs(_lastupdate.CurrentPos.Z - _currentupdate.CurrentPos.Z);
	if(diffpos > 10)
		return true;


	double diffrot = fabs(_lastupdate.CurrentPos.Rotation - _currentupdate.CurrentPos.Rotation);
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

		// do not use update coming from the client trough the server as this could create endless loop
		if(!castedptr->UpdateFromPlayer)
		{
			UpdateModeAndState(castedptr->Info.Mode, castedptr->Info.State,
								SynchronizedTimeHandler::GetCurrentTimeDouble(), 0);

			//inform gui
			EventsQueue::getReceiverQueue()->AddEvent(new GuiRefreshPlayerColorEvent(
				castedptr->Info.SkinColor, castedptr->Info.EyesColor, castedptr->Info.HairColor));

			EventsQueue::getReceiverQueue()->AddEvent(new RefreshPlayerPortraitEvent());
		}
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

	if(_character && _character->GetDisplayObject())
		_character->GetDisplayObject()->Update(update, false);
}


/***********************************************************
update player physic
***********************************************************/
void CharacterController::UpdatePhysic(LbaNet::PhysicObjectUpdateBasePtr update)
{
	if(_character && _character->GetPhysicalObject())
		_character->GetPhysicalObject()->Update(update);
}



/***********************************************************
internaly update player state
***********************************************************/
void CharacterController::UpdateState(LbaNet::ModelState	NewState)
{
	UpdateModeAndState(_currentmodestr, NewState, SynchronizedTimeHandler::GetCurrentTimeDouble(), 0);
}


/***********************************************************
get physic object
***********************************************************/
boost::shared_ptr<PhysicalObjectHandlerBase> CharacterController::GetPhysicalObject()
{
	return _character->GetPhysicalObject();
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
	if(newstate != _currentplayerstate)
	{
		// restore display if older state was scripted
		if(_currentplayerstate == LbaNet::StScripted)
			_character->GetDisplayObject()->RestoreState();

		_currentplayerstate = newstate;

		switch(newstate)
		{
			case LbaNet::StNormal:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateNormal());
			}
			break;
			case LbaNet::StDying:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateDying());
			}
			break;
			case LbaNet::StDrowning:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateDrowning());
			}
			break;
			case LbaNet::StDrowningGas:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateDrowningGas());
			}
			break;
			case LbaNet::StBurning:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateBurning());
			}
			break;
			case LbaNet::StSmallHurt:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateSmallHurt());
			}
			break;
			case LbaNet::StMediumHurt:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateMediumHurt());
			}
			break;
			case LbaNet::StBigHurt:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateBigHurt());
			}
			break;
			case LbaNet::StHurtFall:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateHurtFall());
			}
			break;
			case LbaNet::StFinishedFall:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateFinishedFall());
			}
			break;
			case LbaNet::StFalling:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateFalling());
			}
			break;
			case LbaNet::StJumping:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateJumping());
			}
			break;
			case LbaNet::StMovingObject:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateMovingObject());
			}
			break;
			case LbaNet::StUseWeapon:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateUseWeapon());
			}
			break;
			case LbaNet::StImmune:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateImmune());
			}
			break;
			case LbaNet::StProtectedHurt:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateProtectedHurt());
			}
			break;
			case LbaNet::StHidden:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateHidden());
			}
			break;
			case LbaNet::StScripted:
			{
				// save current display for when we finish script
				_character->GetDisplayObject()->SaveState();

				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateScripted());
			}
			break;
			case LbaNet::StFighting:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateFighting());
			}
			break;

			case LbaNet::StPrepareWeapon:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StatePrepareWeapon());
			}
			break;

			case LbaNet::StActivateSwitch:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateActivateSwitch());
			}
			break;

			case LbaNet::StActivateGroundSwitch:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateActivateGroundSwitch());
			}
			break;

			case LbaNet::StHappy:
			{
				_currentstate = boost::shared_ptr<CharacterStateBase>(new StateHappy());
			}
			break;
		}

		if(_currentstate)
		{
			std::string animstring;
			if(_currentstate->PlayAnimationAtStart(animstring))
			{
				//update animation
				boost::shared_ptr<DisplayObjectHandlerBase> diso = _character->GetDisplayObject();
				if(diso)
					diso->Update(new LbaNet::AnimationStringUpdate(animstring), false);
			}
		}

		// inform mode that state changed
		if(_currentmode)
			_currentmode->CharacterChangedState();

		//inform server that state is updated
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateStateEvent(tnow, newstate, FallingSize));
	}
}

/***********************************************************
server teleport player
***********************************************************/
void CharacterController::Teleport(const LbaNet::PlayerMoveInfo &info)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();

	physo->SetPosition(info.CurrentPos.X, info.CurrentPos.Y, info.CurrentPos.Z);

	LbaQuaternion Q(info.CurrentPos.Rotation, LbaVec3(0,1,0));
	physo->RotateTo(Q);

	// reset attached actor
	_attachedactor = boost::shared_ptr<DynamicObject>();
}


/***********************************************************
get player current position
***********************************************************/
void CharacterController::GetPosition(float & PosX, float & PosY, float & PosZ)
{
	_character->GetPhysicalObject()->GetPosition(PosX, PosY, PosZ);
}


/***********************************************************
get player current rotation
***********************************************************/
float CharacterController::GetRotation()
{
	return _character->GetPhysicalObject()->GetRotationYAxis();
}


/***********************************************************
get player current rotation
***********************************************************/
LbaQuaternion CharacterController::GetRotationQuat()
{
	LbaQuaternion res;
	_character->GetPhysicalObject()->GetRotation(res);
	return res;
}



/***********************************************************
used by lua to update animation
***********************************************************/
void CharacterController::UpdateAnimation( const std::string & AnimationString)
{
	_character->GetDisplayObject()->Update(new LbaNet::AnimationStringUpdate(AnimationString), false);
}

/***********************************************************
update Mode
***********************************************************/
void CharacterController::UpdateActorMode( const std::string & Mode )
{
	UpdateModeAndState(Mode, _currentplayerstate, SynchronizedTimeHandler::GetCurrentTimeDouble(), 0);

	LbaNet::ModelInfo model = _character->GetDisplayObject()->GetCurrentModel(false);
	model.Mode = Mode;
	_character->GetDisplayObject()->Update(new LbaNet::ModelUpdate(model, false), false);
}



/***********************************************************
update Model
***********************************************************/
void CharacterController::UpdateActorModel(const std::string & Model)
{
	LbaNet::ModelInfo model = _character->GetDisplayObject()->GetCurrentModel(false);
	model.ModelName = Model;
	_character->GetDisplayObject()->Update(new LbaNet::ModelUpdate(model, false), false);
}


/***********************************************************
update outfit
***********************************************************/
void CharacterController::UpdateActorOutfit(const std::string & Outfit)
{
	LbaNet::ModelInfo model = _character->GetDisplayObject()->GetCurrentModel(false);
	model.Outfit = Outfit;
	_character->GetDisplayObject()->Update(new LbaNet::ModelUpdate(model, false), false);
}


/***********************************************************
update weapon
***********************************************************/
void CharacterController::UpdateActorWeapon(const std::string & Weapon)
{
	LbaNet::ModelInfo model = _character->GetDisplayObject()->GetCurrentModel(false);
	model.Weapon = Weapon;
	_character->GetDisplayObject()->Update(new LbaNet::ModelUpdate(model, false), false);
}



/***********************************************************
update signal
***********************************************************/
void CharacterController::SendSignal(int Signalnumber)
{
	if(_currentplayerstate == LbaNet::StScripted) // only if in scripted state
	{
		_character->ClearSignals();
		_character->AddSignal(Signalnumber);
	}
}



/***********************************************************
teleport
***********************************************************/
void CharacterController::TeleportTo(float PosX, float PosY, float PosZ)
{
	_character->GetPhysicalObject()->SetPosition(PosX, PosY, PosZ);
}


/***********************************************************
set rotation
***********************************************************/
void CharacterController::SetRotation(float angle)
{
	LbaQuaternion Q;
	Q.AddSingleRotation(angle, LbaVec3(0, 1, 0));
	_character->GetPhysicalObject()->SetRotation(Q);
}


/***********************************************************
show/hide
***********************************************************/
void CharacterController::ShowHide(bool Show)
{
	if(_character->IsShown() != Show)
	{
		_character->ShowOrHide(Show);

		//inform server that state is updated
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ShowHideEvent( SynchronizedTimeHandler::GetCurrentTimeDouble(),
																		2, -1, Show));
	}
}


/***********************************************************
show/hide
***********************************************************/
void CharacterController::WeaponUsed()
{
	if(_currentstate && _currentstate->CanUseWeapon() && !_projectilelaunched)
	{
		if(_currentmode && _currentmode->CanUseWeapon())
		{
			UpdateState(StUseWeapon);	
		}
	}
}


/***********************************************************
stop using weapon
***********************************************************/
void CharacterController::StopUseWeapon()
{
	if(_currentplayerstate == LbaNet::StUseWeapon)
	{
		UpdateState(LbaNet::StNormal);	
	}
}


/***********************************************************
save player to file
***********************************************************/
void CharacterController::SavePlayerDisplayToFile(const std::string & filename)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo =  _character->GetPhysicalObject();
	boost::shared_ptr<DisplayObjectHandlerBase> diso =  _character->GetDisplayObject();
	if(physo && diso)
	{
		//change mode to normal
		std::string savemode = _currentmodestr;
		UpdateActorMode("Normal");
		std::string saveanim = diso->GetCurrentAnimation();
		UpdateAnimation("Stand");

		float X, Y, Z;
		LbaQuaternion Qs;
		physo->GetPosition(X, Y, Z);
		physo->GetRotation(Qs);
		

		LbaQuaternion Q(60, LbaVec3(0, 1, 0));
		diso->SetRotation(Q);
		diso->SetPosition(0, 0, 0);
		diso->StoreObjectCopy();


		//restore state
		UpdateActorMode(savemode);
		UpdateAnimation(saveanim);

		diso->SetRotation(Qs);
		diso->SetPosition(X, Y, Z);
		diso->SaveToFile(filename);
	}		
}

