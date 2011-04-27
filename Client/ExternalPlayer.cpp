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

#include "ExternalPlayer.h"
#include "SynchronizedTimeHandler.h"
#include "LogHandler.h"
#include "SharedDataHandler.h"

#include <math.h>


/***********************************************************
	Constructor
***********************************************************/
ExternalPlayer::ExternalPlayer(boost::shared_ptr<DynamicObject> obje, 
											const LbaNet::ModelInfo &Info)
: _last_update(0), _shouldupdate(false), _playingscript(false), _freemove(false)
{

	_character = obje;
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
	float X, Y, Z;
	physo->GetPosition(X, Y, Z);

	_velocityX=0;
	_velocityY=0;
	_velocityZ=0;
	_velocityR=0;
	_dr.Set(X, Y, Z, physo->GetRotationYAxis(), 0, 0, 0, 0);

	std::stringstream strs;
	strs<<"Creating external player";
	LogHandler::getInstance()->LogToFile(strs.str(), _character->GetId());


	UpdateModeAndState(Info.Mode, Info.State);
}

/***********************************************************
	Destructor
***********************************************************/
ExternalPlayer::~ExternalPlayer()
{
}

/***********************************************************
 update with external info
***********************************************************/
void ExternalPlayer::UpdateMove(double updatetime, const LbaNet::PlayerMoveInfo &info, bool teleport)
{
	// set free move
	_freemove = true;

	if(updatetime > _last_update)
	{
		std::stringstream strs;
		strs<<"Updating external player move with anim"<<info.AnimationIdx;
		LogHandler::getInstance()->LogToFile(strs.str(), _character->GetId());


		// update imediatly modifiable states
		_last_update = updatetime;

		_shouldupdate = true;

		if(!_playingscript)
		{
			boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();


			_velocityX = info.CurrentSpeedX;
			_velocityY = info.CurrentSpeedY;
			_velocityZ = info.CurrentSpeedZ;
			_velocityR = info.CurrentSpeedRotation;


			bool finishedmove = false;
			if(teleport || (abs(_velocityX) < 0.000001f && abs(_velocityY) < 0.000001f && abs(_velocityZ) < 0.000001f))
			{
				finishedmove = true;
				physo->SetPosition(info.CurrentPos.X,  info.CurrentPos.Y, info.CurrentPos.Z);
			}

			if(teleport || (abs(_velocityR) < 0.00001f))
			{
				LbaQuaternion Q(info.CurrentPos.Rotation, LbaVec3(0,1,0));
				physo->RotateTo(Q);

				// do not need to update if no rotation and no rotation
				if(finishedmove)
				{
					_shouldupdate = false;
				}
			}
		}

		// update dead reckon for the rest
		_dr.Set(info.CurrentPos.X,  info.CurrentPos.Y, info.CurrentPos.Z, info.CurrentPos.Rotation,
					info.CurrentSpeedX, info.CurrentSpeedY, info.CurrentSpeedZ, info.CurrentSpeedRotation);

		//update animation
		if(info.AnimationIdx != "")
			_character->GetDisplayObject()->Update(new LbaNet::AnimationStringUpdate(info.AnimationIdx), _playingscript);
	}
}



/***********************************************************
do all check to be done when idle
***********************************************************/
void ExternalPlayer::Process(double tnow, float tdiff, 
								ScriptEnvironmentBase* scripthandler)
{
	if(_playingscript)
	{
		// process script
		if(!ProcessScript(tnow, tdiff, scripthandler))
		{
			// if not moved - move with attached actor
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

		//still update dead recon
		_dr.Update(tnow, tdiff);
		return;
	}


	//update display and animation
	_character->Process(tnow, tdiff);


	if(_shouldupdate)
	{
		boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();

		// calculate prediction
		float predicted_posX, predicted_posY, predicted_posZ;
		physo->GetPosition(predicted_posX, predicted_posY, predicted_posZ);
		predicted_posX += (_velocityX*tdiff);
		predicted_posY += (_velocityY*tdiff);
		predicted_posZ += (_velocityZ*tdiff);


		float predicted_rotation = physo->GetRotationYAxis() + (_velocityR*tdiff);

		// calculate dead reckon
		_dr.Update(tnow, tdiff);


		//// do interpolation X
		{
			float diffX = (_dr._predicted_posX - predicted_posX);
			if(fabs(diffX) > 8)
				predicted_posX = _dr._predicted_posX;
			else
				predicted_posX += diffX / 40;
		}


		//// do interpolation Y
		{
			float diffY = (_dr._predicted_posY - predicted_posY);
			if(fabs(diffY) > 8)
				predicted_posY = _dr._predicted_posY;
			else
				predicted_posY += diffY / 40;
		}


		//// do interpolation Z
		{
			float diffZ = (_dr._predicted_posZ - predicted_posZ);
			if(fabs(diffZ) > 8)
				predicted_posZ = _dr._predicted_posZ;
			else
				predicted_posZ += diffZ / 40;
		}


		//// do interpolation rotation
		{
			float diffR = (_dr._predicted_rotation - predicted_rotation);
			if(fabs(diffR) > 20)
				predicted_rotation = _dr._predicted_rotation;
			else
				predicted_rotation += diffR / 5;
		}

		physo->MoveTo(predicted_posX,  predicted_posY, predicted_posZ);
		LbaQuaternion Q(predicted_rotation, LbaVec3(0,1,0));
		physo->RotateTo(Q);
	}


}


/***********************************************************
update player display
***********************************************************/
void ExternalPlayer::UpdateDisplay(LbaNet::DisplayObjectUpdateBasePtr update, bool updatefromlua)
{
	const std::type_info& info = typeid(*update);

	// ModelUpdate
	if(info == typeid(LbaNet::ModelUpdate))
	{
		LbaNet::ModelUpdate * castedptr = 
			dynamic_cast<LbaNet::ModelUpdate *>(update.get());

		std::stringstream strs;
		strs<<"Updating external player model "<<castedptr->Info.ModelName<<" "
			<<castedptr->Info.Outfit<<" "<<castedptr->Info.Weapon<<" "<<castedptr->Info.Mode<<" ";
		LogHandler::getInstance()->LogToFile(strs.str(), _character->GetId());

		UpdateModeAndState(castedptr->Info.Mode, castedptr->Info.State);
	}

	// anim string upd
	if(info == typeid(LbaNet::AnimationStringUpdate))
	{
		LbaNet::AnimationStringUpdate * castedptr = 
			dynamic_cast<LbaNet::AnimationStringUpdate *>(update.get());

		std::stringstream strs;
		strs<<"Updating external player anim "<<castedptr->Animation;
		LogHandler::getInstance()->LogToFile(strs.str(), _character->GetId());
	}

	// ObjectExtraInfoUpdate
	if(info == typeid(LbaNet::ObjectExtraInfoUpdate))
	{
		LbaNet::ObjectExtraInfoUpdate * castedptr = 
			dynamic_cast<LbaNet::ObjectExtraInfoUpdate *>(update.get());

		std::stringstream strs;
		strs<<"Updating external player extra info "<<castedptr->Update.Name<<" "<<(castedptr->Update.Display?"Display":"Dontdisplay");
		LogHandler::getInstance()->LogToFile(strs.str(), _character->GetId());
	}	

	// ObjectLifeInfoUpdate
	if(info == typeid(LbaNet::ObjectLifeInfoUpdate))
	{
		LbaNet::ObjectLifeInfoUpdate * castedptr = 
			dynamic_cast<LbaNet::ObjectLifeInfoUpdate *>(update.get());

		std::stringstream strs;
		strs<<"Updating external player life info "<<(castedptr->Update.Display?"Display":"Dontdisplay");
		LogHandler::getInstance()->LogToFile(strs.str(), _character->GetId());
	}	


	_character->GetDisplayObject()->Update(update, (!updatefromlua && _playingscript));
}

/***********************************************************
update player physic
***********************************************************/
void ExternalPlayer::UpdatePhysic(LbaNet::PhysicObjectUpdateBasePtr update)
{
	_character->GetPhysicalObject()->Update(update);
}



/***********************************************************
internaly update mode and state
***********************************************************/
void ExternalPlayer::UpdateModeAndState(const std::string &newmode,
												LbaNet::ModelState newstate)
{
	// only update if different
	if(newmode == "Normal")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new NormalCharacterMode());
	}

	if(newmode == "Sport")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new SportyCharacterMode());
	}

	if(newmode == "Angry")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new AggresiveCharacterMode());
	}

	if(newmode == "Discrete")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new DiscreteCharacterMode());
	}		

	if(newmode == "Protopack")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new ProtopackCharacterMode());
	}

	if(newmode == "Horse")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new HorseCharacterMode());
	}

	if(newmode == "Dinofly")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new DinoflyCharacterMode());
	}		


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


	//TODO - get state and display player accordingly
}




/***********************************************************
internaly update mode and state
***********************************************************/
void ExternalPlayer::SetPlayingScript(bool playing)
{
	if(playing && !_playingscript)
		_character->GetDisplayObject()->SaveState();

	if(!playing && _playingscript)
		_character->GetDisplayObject()->RestoreState();


	_playingscript = playing;
}


/***********************************************************
get actor position
***********************************************************/
void ExternalPlayer::GetPosition(float &X, float &Y, float &Z)
{
	_character->GetPhysicalObject()->GetPosition(X, Y, Z);
}


/***********************************************************
get actor rotation
***********************************************************/
float ExternalPlayer::GetRotationYAxis()
{
	return _character->GetPhysicalObject()->GetRotationYAxis();
}

/***********************************************************
get rotation
***********************************************************/
void ExternalPlayer::GetRotation(LbaQuaternion& Q)
{
	_character->GetPhysicalObject()->GetRotation(Q);
}

/***********************************************************
update Mode
***********************************************************/
void ExternalPlayer::UpdateActorMode( const std::string & Mode, bool updatefromlua)
{
	bool usestored = !updatefromlua && _playingscript;

	LbaNet::ModelInfo model = _character->GetDisplayObject()->GetCurrentModel(usestored);
	model.Mode = Mode;
	_character->GetDisplayObject()->Update(new LbaNet::ModelUpdate(model, false), usestored);

	std::stringstream strs;
	strs<<"Updating external player mode "<<Mode;
	LogHandler::getInstance()->LogToFile(strs.str(), _character->GetId());
}


/***********************************************************
update Model
***********************************************************/
void ExternalPlayer::UpdateActorModel(const std::string & Model, bool updatefromlua)
{
	bool usestored = !updatefromlua && _playingscript;

	LbaNet::ModelInfo model = _character->GetDisplayObject()->GetCurrentModel(usestored);
	model.ModelName = Model;
	_character->GetDisplayObject()->Update(new LbaNet::ModelUpdate(model, false), usestored);

	std::stringstream strs;
	strs<<"Updating external player model "<<Model;
	LogHandler::getInstance()->LogToFile(strs.str(), _character->GetId());
}


/***********************************************************
update outfit
***********************************************************/
void ExternalPlayer::UpdateActorOutfit(const std::string & Outfit, bool updatefromlua)
{
	bool usestored = !updatefromlua && _playingscript;

	LbaNet::ModelInfo model = _character->GetDisplayObject()->GetCurrentModel(usestored);
	model.Outfit = Outfit;
	_character->GetDisplayObject()->Update(new LbaNet::ModelUpdate(model, false), usestored);

	std::stringstream strs;
	strs<<"Updating external player outfit "<<Outfit;
	LogHandler::getInstance()->LogToFile(strs.str(), _character->GetId());
}


/***********************************************************
update weapon
***********************************************************/
void ExternalPlayer::UpdateActorWeapon(const std::string & Weapon, bool updatefromlua)
{
	bool usestored = !updatefromlua && _playingscript;

	LbaNet::ModelInfo model = _character->GetDisplayObject()->GetCurrentModel(usestored);
	model.Weapon = Weapon;
	_character->GetDisplayObject()->Update(new LbaNet::ModelUpdate(model, false), usestored);

	std::stringstream strs;
	strs<<"Updating external player weapon "<<Weapon;
	LogHandler::getInstance()->LogToFile(strs.str(), _character->GetId());
}



/***********************************************************
update signal
***********************************************************/
void ExternalPlayer::SendSignal(int Signalnumber)
{
	_character->AddSignal(Signalnumber);
}



/***********************************************************
teleport
***********************************************************/
void ExternalPlayer::TeleportTo(float PosX, float PosY, float PosZ)
{
	PlayerMoveInfo minfo;
    minfo.CurrentPos.X = PosX;
    minfo.CurrentPos.Y = PosY;
    minfo.CurrentPos.Z = PosZ;
	minfo.CurrentPos.Rotation = _dr._rotation;
    minfo.CurrentSpeedX = 0;
    minfo.CurrentSpeedY = 0;
    minfo.CurrentSpeedZ = 0;
    minfo.CurrentSpeedRotation = 0;
	UpdateMove(SynchronizedTimeHandler::GetCurrentTimeDouble(), minfo, true);
}


/***********************************************************
set rotation
***********************************************************/
void ExternalPlayer::SetRotation(float angle)
{
	PlayerMoveInfo minfo;
    minfo.CurrentPos.X = _dr._posX;
    minfo.CurrentPos.Y = _dr._posY;
    minfo.CurrentPos.Z = _dr._posZ;
	minfo.CurrentPos.Rotation = angle;
    minfo.CurrentSpeedX = _dr._velocityX;
    minfo.CurrentSpeedY = _dr._velocityY;
    minfo.CurrentSpeedZ = _dr._velocityZ;
    minfo.CurrentSpeedRotation = 0;
	UpdateMove(SynchronizedTimeHandler::GetCurrentTimeDouble(), minfo, false);
}

/***********************************************************
show/hide
***********************************************************/
void ExternalPlayer::ShowHide(bool Show)
{
	_character->ShowOrHide(Show);

	std::stringstream strs;
	strs<<"Updating external player "<<(Show?"Show":"Hide");
	LogHandler::getInstance()->LogToFile(strs.str(), _character->GetId());
}