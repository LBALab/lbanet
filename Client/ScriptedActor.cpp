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

#include "ScriptedActor.h"
#include "PhysicalObjectHandlerBase.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "DynamicObject.h"
#include "ClientLuaHandler.h"


#include <iostream>
#include <math.h>

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif




/***********************************************************
constructor
***********************************************************/
StraightWalkToScriptPart::StraightWalkToScriptPart(int scriptid, float PosX, float PosY, float PosZ, 
									boost::shared_ptr<DynamicObject> actor)
	: ScriptPartBase(scriptid), _PosX(PosX), _PosY(PosY), _PosZ(PosZ)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	physo->GetPosition(_StartPosX, _StartPosY, _StartPosZ);

	float diffX = (_PosX - _StartPosX);
	float diffY = (_PosY - _StartPosY);
	float diffZ = (_PosZ - _StartPosZ);
	float _distance = (diffX*diffX) + (diffY*diffY) + (diffZ*diffZ);
	_distance = sqrt(_distance);

	_distanceDone = 0;
}


/***********************************************************
process script part
return true if finished
***********************************************************/
bool StraightWalkToScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor)
{
	// proces with animation
	actor->Process(tnow, tdiff);

	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	boost::shared_ptr<DisplayObjectHandlerBase> disso = actor->GetDisplayObject();


	// check if we arrive at destination
	if(abs(_distance-_distanceDone) < 0.01)
		return true;


	// get animation speed
	float speedX = disso->GetCurrentAssociatedSpeedX();
	float speedY = disso->GetCurrentAssociatedSpeedY();
	float speedZ = disso->GetCurrentAssociatedSpeedZ();

	_distanceDone += (speedX+speedY+speedZ) * tdiff;
	if(_distanceDone > _distance)
		_distanceDone = _distance;

	float ratio = (_distanceDone / _distance);

	float curPosX = (_PosX*ratio) + (_StartPosX*(1-ratio));
	float curPosY = (_PosY*ratio) + (_StartPosY*(1-ratio));
	float curPosZ = (_PosZ*ratio) + (_StartPosZ*(1-ratio));

	physo->MoveTo(curPosX, curPosY, curPosZ);


	return false;
}





/***********************************************************
	Constructor
***********************************************************/
PlayAnimationScriptPart::PlayAnimationScriptPart(int scriptid, bool AnimationMove)
	: ScriptPartBase(scriptid), _AnimationMove(AnimationMove)
{
}



/***********************************************************
process script part
return true if finished
***********************************************************/
bool PlayAnimationScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor)
{
	// proces with animation
	int res = actor->Process(tnow, tdiff);
	if(res == 1)
		return true;


	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	boost::shared_ptr<DisplayObjectHandlerBase> disso = actor->GetDisplayObject();

	if(_AnimationMove)
	{
		// get animation speed
		float speedX = disso->GetCurrentAssociatedSpeedX();
		float speedY = disso->GetCurrentAssociatedSpeedY();
		float speedZ = disso->GetCurrentAssociatedSpeedZ();

		if(speedX != 0 && speedY != 0 && speedZ != 0)
			physo->Move(speedX*tdiff, speedY*tdiff, speedZ*tdiff, false);
	}

	return false;
}






/***********************************************************
	Constructor
***********************************************************/
RotateScriptPart::RotateScriptPart(int scriptid, float Angle, float RotationSpeedPerSec)
	: ScriptPartBase(scriptid), _Angle(Angle), _RotationSpeedPerSec(RotationSpeedPerSec)
{

}


/***********************************************************
//! process script part
//! return true if finished
***********************************************************/
bool RotateScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	float currAngle = physo->GetRotationYAxis();

	double distance = (_Angle-currAngle);
	if(abs(distance) > 1.0)
	{
		if((distance > 0 && distance < 180) || (distance < -180))
			physo->RotateYAxis(-_RotationSpeedPerSec*tdiff);
		else
			physo->RotateYAxis(_RotationSpeedPerSec*tdiff);
	}
	else
		return true;

	return false;
}





/***********************************************************
	Constructor
***********************************************************/
ScriptedActor::ScriptedActor()
{

}


/***********************************************************
	Destructor
***********************************************************/
ScriptedActor::~ScriptedActor()
{

}

/***********************************************************
process function
***********************************************************/
void ScriptedActor::ProcessScript(double tnow, float tdiff, boost::shared_ptr<ClientLuaHandler> scripthandler)
{
	if(_currentScript)
	{
		bool finished = _currentScript->Process(tnow, tdiff, _character);
		if(finished)
		{
			//tell script handler that script part is finished
			if(scripthandler)
				scripthandler->ResumeThread(_currentScript->GetAttachedScriptId());

			// delete script part
			_currentScript = boost::shared_ptr<ScriptPartBase>();
		}
	}
}


/***********************************************************
used by lua to move an actor or player
if id < 1 then it moves players
the actor will move using animation speed
***********************************************************/
void ScriptedActor::ActorStraightWalkTo(int ScriptId, float PosX, float PosY, float PosZ)
{
	_currentScript = boost::shared_ptr<ScriptPartBase>(
						new StraightWalkToScriptPart(ScriptId, PosX, PosY, PosZ, _character));
}



/***********************************************************
//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
***********************************************************/
void ScriptedActor::ActorRotate(int ScriptId, float Angle, float RotationSpeedPerSec)
{
	_currentScript = boost::shared_ptr<ScriptPartBase>(
						new RotateScriptPart(ScriptId, Angle, RotationSpeedPerSec));
}


/***********************************************************
//! used by lua to wait until an actor animation is finished
//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
***********************************************************/
void ScriptedActor::ActorAnimate(int ScriptId, bool AnimationMove)
{
	_currentScript = boost::shared_ptr<ScriptPartBase>(
						new PlayAnimationScriptPart(ScriptId, AnimationMove));
}