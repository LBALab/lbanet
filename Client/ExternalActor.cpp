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

#include "ExternalActor.h"
#include "SynchronizedTimeHandler.h"
#include "LogHandler.h"
#include "SharedDataHandler.h"
#include "ScriptEnvironmentBase.h"
#include "EventsQueue.h"
#include "ActorUserData.h"

#include <math.h>


/***********************************************************
	Constructor
***********************************************************/
ExternalActor::ExternalActor(boost::shared_ptr<DynamicObject> obje, 
											const LbaNet::ModelInfo &Info,
											bool movable)
: ExternalPlayer(obje, Info), _shouldreset(true), _targetting(false),
	_movable(movable), _lastupdatetime(0)
{
	if(_movable)
	{
		// update last position
		_character->GetPhysicalObject()->GetPosition(_lastupdate.CurrentPos.X,
							_lastupdate.CurrentPos.Y,
							_lastupdate.CurrentPos.Z);

		_lastupdate.CurrentSpeedX = 0;
		_lastupdate.CurrentSpeedY = 0;
		_lastupdate.CurrentSpeedZ = 0;
	}
}

/***********************************************************
	Destructor
***********************************************************/
ExternalActor::~ExternalActor()
{
}


/***********************************************************
when update npc position
***********************************************************/
void ExternalActor::NpcChangedUpdate(double updatetime, 
									float CurrPosX, float CurrPosY, float CurrPosZ,
									float CurrRotation, const std::string &CurrAnimation,
									bool ResetPosition, bool ResetRotation,
									LbaNet::NpcUpdateBasePtr Update, 
									ScriptEnvironmentBase* scripthandler)
{
	// reset free move
	_freemove = false;

	// reset projectiles
	if(_character)
		_character->ClearActionsOnAnimation();


	// update only newest info
	if(updatetime < _last_update)
		return;

	_last_update = updatetime;

	if(_playingscript)
		return;


	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
	float posX, posY, posZ;
	physo->GetPosition(posX, posY, posZ);
	float rotation = physo->GetRotationYAxis();


	// update position and rotation
	float diffpos = (CurrPosX-posX)*(CurrPosX-posX) + 
						(CurrPosY-posY)*(CurrPosY-posY) +
						(CurrPosZ-posZ)*(CurrPosZ-posZ);

	float diffrot = abs(CurrRotation-rotation);


	// reset actor position
	if(ResetPosition || diffpos > 64 || _shouldreset)
	{
		physo->SetPosition(CurrPosX,  CurrPosY, CurrPosZ);
		posX = CurrPosX;
		posY = CurrPosY;
		posZ = CurrPosZ;
	}

	// reset actor rotation
	if(ResetRotation || diffrot > 20 || _shouldreset)
	{
		LbaQuaternion Q(CurrRotation, LbaVec3(0,1,0));
		physo->SetRotation(Q);
		rotation = CurrRotation;
	}

	_differencePosX = CurrPosX-posX;
	_differencePosY = CurrPosY-posY;
	_differencePosZ = CurrPosZ-posZ;
	_differenceRotation = CurrRotation-rotation;

	//update animation
	if(CurrAnimation != "")
		_character->GetDisplayObject()->Update(new LbaNet::AnimationStringUpdate(CurrAnimation), _playingscript);

	_shouldreset = false;



	// update the script part
	if(!Update)
	{
		_currentScripts = boost::shared_ptr<ScriptPartBase>();
		return;
	}


	LbaNet::NpcUpdateBase & obj = *Update;
	const std::type_info& info = typeid(obj);

	// StraightWalkToNpcUpd
	if(info == typeid(LbaNet::StraightWalkToNpcUpd))
	{
		LbaNet::StraightWalkToNpcUpd * castedptr = 
			dynamic_cast<LbaNet::StraightWalkToNpcUpd *>(&obj);


		_currentScripts = boost::shared_ptr<ScriptPartBase>(new 
			StraightWalkToScriptPart(0, false, castedptr->PosX, castedptr->PosY, castedptr->PosZ,
										_character));
		return;
	}

	// GoToNpcUpd
	if(info == typeid(LbaNet::GoToNpcUpd))
	{
		LbaNet::GoToNpcUpd * castedptr = 
			dynamic_cast<LbaNet::GoToNpcUpd *>(&obj);


		_currentScripts = boost::shared_ptr<ScriptPartBase>(new 
			GoToScriptPart(0, false, castedptr->PosX, castedptr->PosY, castedptr->PosZ, castedptr->Speed,
										_character));
		return;
	}

	// RotateNpcUpd
	if(info == typeid(LbaNet::RotateNpcUpd))
	{
		LbaNet::RotateNpcUpd * castedptr = 
			dynamic_cast<LbaNet::RotateNpcUpd *>(&obj);


		_currentScripts = boost::shared_ptr<ScriptPartBase>(new 
			RotateScriptPart(0, false, castedptr->Angle, castedptr->RotationSpeedPerSec, 
								castedptr->ManageAnimation));
		return;
	}

	// AnimateNpcUpd
	if(info == typeid(LbaNet::AnimateNpcUpd))
	{
		LbaNet::AnimateNpcUpd * castedptr = 
			dynamic_cast<LbaNet::AnimateNpcUpd *>(&obj);


		_currentScripts = boost::shared_ptr<ScriptPartBase>(new 
			PlayAnimationScriptPart(0, false, castedptr->AnimationMove));
		return;
	}

	// RotateFromPointNpcUpd
	if(info == typeid(LbaNet::RotateFromPointNpcUpd))
	{
		LbaNet::RotateFromPointNpcUpd * castedptr = 
			dynamic_cast<LbaNet::RotateFromPointNpcUpd *>(&obj);


		_currentScripts = boost::shared_ptr<ScriptPartBase>(new 
			RotateFromPointScriptPart(0, false, castedptr->Angle,
			castedptr->PosX, castedptr->PosY, castedptr->PosZ, castedptr->Speed, _character));
		return;
	}


	// FollowWaypointNpcUpd
	if(info == typeid(LbaNet::FollowWaypointNpcUpd))
	{
		LbaNet::FollowWaypointNpcUpd * castedptr = 
			dynamic_cast<LbaNet::FollowWaypointNpcUpd *>(&obj);


		LbaVec3 Pm1X(castedptr->Pm1X, castedptr->Pm1Y, castedptr->Pm1Z);
		LbaVec3 P0(castedptr->P0X, castedptr->P0Y, castedptr->P0Z);
		LbaVec3 P1(castedptr->P1X, castedptr->P1Y, castedptr->P1Z);
		LbaVec3 P2(castedptr->P2X, castedptr->P2Y, castedptr->P2Z);
		LbaVec3 P3(castedptr->P3X, castedptr->P3Y, castedptr->P3Z);
		LbaVec3 P4(castedptr->P4X, castedptr->P4Y, castedptr->P4Z);


		_currentScripts = boost::shared_ptr<ScriptPartBase>(new 
			FollowWaypointScriptPart(0, false, Pm1X, P0, P1, P2, P3, P4));
		return;
	}

}



/***********************************************************
do all check to be done when idle
***********************************************************/
void ExternalActor::Process(double tnow, float tdiff, 
								ScriptEnvironmentBase* scripthandler)
{
	if(_freemove || _playingscript)
	{
		ExternalPlayer::Process(tnow, tdiff, scripthandler);
		return;
	}


	bool moved = false;

	if(_currentScripts)	
	{
		_character->SetAdditionalMoves(_differencePosX/10, _differencePosY/10, 
											_differencePosZ/10, _differenceRotation/5);

		_differencePosX -= _differencePosX/10;
		_differencePosY -= _differencePosY/10;
		_differencePosZ -= _differencePosZ/10;
		_differenceRotation -= _differenceRotation/5;


		bool finished = _currentScripts->Process(tnow, tdiff, _character, moved);
		if(finished)
			_currentScripts = boost::shared_ptr<ScriptPartBase>();
	}
	else
	{
		_character->Process(tnow, tdiff);

		if(_movable)
		{
			ProcessMovable(tnow, tdiff, scripthandler);
			moved = true;
		}
	}

	if(!moved)
	{
		// move with attached actor
		if(_externalattachedactor)
		{
			boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
			boost::shared_ptr<PhysicalObjectHandlerBase> attchedphys = _externalattachedactor->GetPhysicalObject();
			if(physo && attchedphys)
			{
				physo->RotateYAxis(attchedphys->GetLastRotation());

				float addspeedX=0, addspeedY=0, addspeedZ=0;
				attchedphys->GetLastMove(addspeedX, addspeedY, addspeedZ);
				physo->Move(addspeedX, addspeedY, addspeedZ);
			}
		}
	}
}


/***********************************************************
internaly update mode and state
***********************************************************/
void ExternalActor::SetPlayingScript(bool playing)
{
	_shouldreset = true;
	_currentScripts = boost::shared_ptr<ScriptPartBase>();
	ExternalPlayer::SetPlayingScript(playing);
}



/***********************************************************
target player
***********************************************************/
void ExternalActor::Target(boost::shared_ptr<PhysicalObjectHandlerBase> object)
{
	if(!_targetting)
	{
		_targetting = true;
		_targetsavedScripts = _currentScripts;

		boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
		_targetsavedangle = physo->GetRotationYAxis();
	}

	_currentScripts = boost::shared_ptr<ScriptPartBase>(new 
		TargetScriptPart(0, false, object));
}


/***********************************************************
untarget
***********************************************************/
void ExternalActor::UnTarget()
{
	if(_targetting)
	{
		_currentScripts = _targetsavedScripts;
		if(!_playingscript)
		{
			boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
			LbaQuaternion Q(_targetsavedangle, LbaVec3(0, 1, 0));
			physo->SetRotation(Q);
		}

		_targetsavedScripts = boost::shared_ptr<ScriptPartBase>();
		_targetting = false;
	}
}

	
/***********************************************************
server attach actor
***********************************************************/
void ExternalActor::ServerAttachActor(boost::shared_ptr<DynamicObject> actor)
{
	_externalattachedactor = actor;
}


/***********************************************************
check if we need to send update to server
***********************************************************/
void ExternalActor::UpdateServer(double tnow, float tdiff)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();

	// get current position
	physo->GetPosition(_currentupdate.CurrentPos.X,
							_currentupdate.CurrentPos.Y,
							_currentupdate.CurrentPos.Z);


	// get current rotation
	_currentupdate.CurrentPos.Rotation = 0;


	// set speed
	_currentupdate.CurrentSpeedX = (_currentupdate.CurrentPos.X-_lastupdate.CurrentPos.X) / _oldtdiff;
	_currentupdate.CurrentSpeedY = (_currentupdate.CurrentPos.Y-_lastupdate.CurrentPos.Y) / _oldtdiff;
	_currentupdate.CurrentSpeedZ = (_currentupdate.CurrentPos.Z-_lastupdate.CurrentPos.Z) / _oldtdiff;
	float sumspeed = _currentupdate.CurrentSpeedX + _currentupdate.CurrentSpeedY + _currentupdate.CurrentSpeedZ;

	//calculate angle speed
	_currentupdate.CurrentSpeedRotation = 0;


	_oldtdiff = tdiff;


	// check if we should force the update
	_currentupdate.ForcedChange = ShouldforceUpdate();


	//else send regular update every seconds when moving
	bool updatebytime = false;
	if(!_currentupdate.ForcedChange && fabs(sumspeed) > 0)
	{
		if((tnow - _lastupdatetime) > 1000) // if more than 1 second
			updatebytime = true;
	}


	//send to server if needed
	if(_currentupdate.ForcedChange || updatebytime)
	{
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::GhostMovedEvent(tnow, _character->GetId(), 
																					_currentupdate));
		_lastupdatetime = tnow;
	}


	_lastupdate = _currentupdate;
}



/***********************************************************
check if we should force the update
***********************************************************/
bool ExternalActor::ShouldforceUpdate()
{
	if(abs(_lastupdate.CurrentSpeedX - _currentupdate.CurrentSpeedX) > 0.00001f)
		return true;

	if(abs(_lastupdate.CurrentSpeedY - _currentupdate.CurrentSpeedY) > 0.00001f)
		return true;

	if(abs(_lastupdate.CurrentSpeedZ - _currentupdate.CurrentSpeedZ) > 0.00001f)
		return true;


	float diffpos = fabs(_lastupdate.CurrentPos.X - _currentupdate.CurrentPos.X)
					+ fabs(_lastupdate.CurrentPos.Y - _currentupdate.CurrentPos.Y)
					+  fabs(_lastupdate.CurrentPos.Z - _currentupdate.CurrentPos.Z);
	if(diffpos > 10)
		return true;


	return false;
}



/***********************************************************
do all check to be done when idle
***********************************************************/
void ExternalActor::ProcessMovable(double tnow, float tdiff, 
								ScriptEnvironmentBase* scripthandler)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
	if(!physo)
		return;


	float admx=0, admy=0, admz=0;
	boost::shared_ptr<ActorUserData> udata = physo->GetUserData();
	if(udata)
		udata->GetAddedMove(admx, admy, admz);


	admy = (-0.05f * tdiff); //TODO - make the gravity configurable?


	// get additional speed in case we are on lift
	if(_attachedactor)
	{
		float addspeedX=0, addspeedY=0, addspeedZ=0;

		boost::shared_ptr<PhysicalObjectHandlerBase> attchedphys = _attachedactor->GetPhysicalObject();
		if(attchedphys)
			attchedphys->GetLastMove(addspeedX, addspeedY, addspeedZ);
		
		admx+=addspeedX;
		admz+=addspeedZ;

		if(addspeedY <= 0)
		{
			admy += addspeedY;
			_attachedactor = boost::shared_ptr<DynamicObject>(); // dettach actor afterwards
		}
		else
		{
			//check if we are still on the actor
			if(physo->OnTopOff(attchedphys.get()))
			{
				admy = addspeedY;
			}
			else
			{
				_attachedactor = boost::shared_ptr<DynamicObject>(); // dettach actor
			}
		}
	}


	// move actor
	physo->Move(admx, admy, admz);



	// check for attached actor
	if(udata)
	{
		if(udata->GetTouchingGround())
		{
			std::vector<HitInfo> hitvec;
			udata->GetHittedActors(hitvec);
			for(size_t i=0; i< hitvec.size(); ++i)
			{
				HitInfo &hi = hitvec[i];
				if(hi.HitBottom)
				{
					if(scripthandler)
						_attachedactor = scripthandler->GetActor(hi.ActorObjType, hi.ActorId);
				}
			}
		}
	}


	// update server
	UpdateServer(tnow, tdiff);
}