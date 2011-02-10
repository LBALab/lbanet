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
#include "DynamicObject.h"
#include "ScriptEnvironmentBase.h"


#include <iostream>
#include <math.h>

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif




/***********************************************************
constructor
***********************************************************/
StraightWalkToScriptPart::StraightWalkToScriptPart(int scriptid, bool asynchronus, 
												   float PosX, float PosY, float PosZ, 
													boost::shared_ptr<DynamicObject> actor)
	: ScriptPartBase(scriptid, asynchronus), _PosX(PosX), _PosY(PosY), _PosZ(PosZ)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	physo->GetPosition(_StartPosX, _StartPosY, _StartPosZ);

	float diffX = (_PosX - _StartPosX);
	float diffY = (_PosY - _StartPosY);
	float diffZ = (_PosZ - _StartPosZ);
	_distance = (diffX*diffX) + (diffY*diffY) + (diffZ*diffZ);
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
PlayAnimationScriptPart::PlayAnimationScriptPart(int scriptid, bool asynchronus, bool AnimationMove)
	: ScriptPartBase(scriptid, asynchronus), _AnimationMove(AnimationMove)
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

		LbaQuaternion Q;
		physo->GetRotation(Q);
		LbaVec3 current_directionX(Q.GetDirection(LbaVec3(0, 0, 1)));
		LbaVec3 current_directionZ(Q.GetDirection(LbaVec3(1, 0, 0)));
		float ajustedspeedx = speedX*current_directionX.x + speedZ*current_directionZ.x;
		float ajustedspeedZ = speedX*current_directionX.z + speedZ*current_directionZ.z;


		if(speedX != 0 || speedY != 0 || speedZ != 0)
			physo->Move(ajustedspeedx*tdiff, speedY*tdiff, ajustedspeedZ*tdiff, false);
	}

	return false;
}






/***********************************************************
	Constructor
***********************************************************/
RotateScriptPart::RotateScriptPart(int scriptid, bool asynchronus, float Angle, 
								   float RotationSpeedPerSec, bool ManageAnimation)
	: ScriptPartBase(scriptid, asynchronus), _Angle(Angle), _RotationSpeedPerSec(RotationSpeedPerSec),
		_ManageAnimation(ManageAnimation)
{
	while(_Angle < 0)
		_Angle += 360;
	while(_Angle > 360)
		_Angle -= 360;
}


/***********************************************************
//! process script part
//! return true if finished
***********************************************************/
bool RotateScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor)
{
	actor->Process(tnow, tdiff);

	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	float currAngle = physo->GetRotationYAxis();

	double distance = (currAngle-_Angle);
	if(abs(distance) > 2.0)
	{
		if((distance > 0 && distance < 180) || (distance < -180))
		{
			if(_ManageAnimation)
				actor->GetDisplayObject()->Update(new LbaNet::AnimationStringUpdate("TurnRight"), false);

			physo->RotateYAxis(std::max((-_RotationSpeedPerSec*tdiff), (-(float)abs(distance))));
		}
		else
		{
			if(_ManageAnimation)
				actor->GetDisplayObject()->Update(new LbaNet::AnimationStringUpdate("TurnLeft"), false);

			physo->RotateYAxis(std::min((_RotationSpeedPerSec*tdiff), ((float)abs(distance))));
		}
	}
	else
		return true;

	return false;
}







/***********************************************************
constructor
***********************************************************/
GoToScriptPart::GoToScriptPart(int scriptid, bool asynchronus, 
												   float PosX, float PosY, float PosZ, 
													float Speed, boost::shared_ptr<DynamicObject> actor)
	: ScriptPartBase(scriptid, asynchronus), _PosX(PosX), _PosY(PosY), _PosZ(PosZ), _Speed(Speed)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	physo->GetPosition(_StartPosX, _StartPosY, _StartPosZ);

	float diffX = (_PosX - _StartPosX);
	float diffY = (_PosY - _StartPosY);
	float diffZ = (_PosZ - _StartPosZ);
	_distance = (diffX*diffX) + (diffY*diffY) + (diffZ*diffZ);
	_distance = sqrt(_distance);

	_distanceDone = 0;
}


/***********************************************************
process script part
return true if finished
***********************************************************/
bool GoToScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor)
{
	// proces with animation
	actor->Process(tnow, tdiff);

	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	boost::shared_ptr<DisplayObjectHandlerBase> disso = actor->GetDisplayObject();


	// check if we arrive at destination
	if(abs(_distance-_distanceDone) < 0.01)
		return true;


	// get speed
	_distanceDone += (_Speed) * tdiff;
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
constructor
***********************************************************/
WaitForSignalScriptPart::WaitForSignalScriptPart(int scriptid, bool asynchronus, int SignalId)
	: ScriptPartBase(scriptid, asynchronus), _SignalId(SignalId)
{
}


/***********************************************************
process script part
return true if finished
***********************************************************/
bool WaitForSignalScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor)
{
	// proces with animation
	actor->Process(tnow, tdiff);

	return actor->ReceivedSignal(_SignalId);
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
void ScriptedActor::ProcessScript(double tnow, float tdiff, ScriptEnvironmentBase* scripthandler)
{
	if(_currentScripts.size() > 0 && _character)
	{
		boost::shared_ptr<ScriptPartBase> firstscript = _currentScripts.front();

		bool finished = firstscript->Process(tnow, tdiff, _character);
		if(finished)
		{
			int scid = firstscript->GetAttachedScriptId();
			bool asc = firstscript->IsAsynchronus();

			//tell script handler that script part is finished
			if(scripthandler)
				scripthandler->ScriptFinished(scid, asc);

			// delete script part
			_currentScripts.pop_front();
		}
	}
}


/***********************************************************
clear all running scripts
***********************************************************/
void ScriptedActor::ClearAllScripts()
{
	_currentScripts.clear();
}


/***********************************************************
used by lua to move an actor or player
if id < 1 then it moves players
the actor will move using animation speed
***********************************************************/
void ScriptedActor::ActorStraightWalkTo(int ScriptId, bool asynchronus, float PosX, float PosY, float PosZ)
{
	_currentScripts.push_back(boost::shared_ptr<ScriptPartBase>(
						new StraightWalkToScriptPart(ScriptId, asynchronus, PosX, PosY, PosZ, _character)));
}



/***********************************************************
//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
***********************************************************/
void ScriptedActor::ActorRotate(int ScriptId, bool asynchronus, float Angle, float RotationSpeedPerSec, 
								bool ManageAnimation)
{
	_currentScripts.push_back(boost::shared_ptr<ScriptPartBase>(
						new RotateScriptPart(ScriptId, asynchronus, Angle, RotationSpeedPerSec, ManageAnimation)));
}


/***********************************************************
//! used by lua to wait until an actor animation is finished
//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
***********************************************************/
void ScriptedActor::ActorAnimate(int ScriptId, bool asynchronus, bool AnimationMove)
{
	_currentScripts.push_back(boost::shared_ptr<ScriptPartBase>(
						new PlayAnimationScriptPart(ScriptId, asynchronus, AnimationMove)));
}





/***********************************************************
//! used by lua to move an actor or player
//! the actor will move using speed
***********************************************************/
void ScriptedActor::ActorGoTo(int ScriptId, float PosX, float PosY, float PosZ, float Speed, bool asynchronus)
{
	_currentScripts.push_back(boost::shared_ptr<ScriptPartBase>(
						new GoToScriptPart(ScriptId, asynchronus, PosX, PosY, PosZ, Speed, _character)));
}
	



/***********************************************************
//! used by lua to move an actor or player
//! the actor will wait for signal
***********************************************************/
void ScriptedActor::ActorWaitForSignal(int ScriptId, int Signalnumber, bool asynchronus)
{
	_currentScripts.push_back(boost::shared_ptr<ScriptPartBase>(
						new WaitForSignalScriptPart(ScriptId, asynchronus, Signalnumber)));
}