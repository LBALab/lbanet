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

#include <math.h>


/***********************************************************
	Constructor
***********************************************************/
ExternalActor::ExternalActor(boost::shared_ptr<DynamicObject> obje, 
											const LbaNet::ModelInfo &Info)
: ExternalPlayer(obje, Info), _shouldreset(true)
{

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
									LbaNet::NpcUpdateBasePtr Update)
{
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
		return;


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
	if(!_playingscript)
	{
		if(_currentScripts)	
		{
			_character->SetAdditionalMoves(_differencePosX/10, _differencePosY/10, 
												_differencePosZ/10, _differenceRotation/5);

			_differencePosX -= _differencePosX/10;
			_differencePosY -= _differencePosY/10;
			_differencePosZ -= _differencePosZ/10;
			_differenceRotation -= _differenceRotation/5;


			bool finished = _currentScripts->Process(tnow, tdiff, _character);
			if(finished)
				_currentScripts = boost::shared_ptr<ScriptPartBase>();
		}
		else
			_character->Process(tnow, tdiff);
	}
	else
		ProcessScript(tnow, tdiff, scripthandler);

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
