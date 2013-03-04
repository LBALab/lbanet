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
#include "LogHandler.h"
#include "ActorUserData.h"

#include <fstream>
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
bool StraightWalkToScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor, bool & moved)
{
	// proces with animation
	actor->Process(tnow, tdiff);

	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	boost::shared_ptr<DisplayObjectHandlerBase> disso = actor->GetDisplayObject();


	// check if we arrive at destination
	if(fabs(_distance-_distanceDone) < 0.01)
		return true;

	// set moved flag
	moved = true;

	// get animation speed
	float speedX = disso->GetCurrentAssociatedSpeedX();
	float speedY = disso->GetCurrentAssociatedSpeedY();
	float speedZ = disso->GetCurrentAssociatedSpeedZ();

	_distanceDone += (speedX+speedY+speedZ) * tdiff;

	// extra move
	float mx, my, mz, mr;
	actor->GetAdditionalMoves(mx, my, mz, mr);
	float extramove = (mx*mx) + (my*my) + (mz*mz);
	extramove = sqrt(extramove);
	_distanceDone += extramove;



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
WalkToPointScriptPart
***********************************************************/
WalkToPointScriptPart::WalkToPointScriptPart(int scriptid, bool asynchronus, float PosX, float PosY, float PosZ, float RotationSpeedPerSec, bool moveForward)
	: ScriptPartBase(scriptid, asynchronus), _PosX(PosX), _PosY(PosY), _PosZ(PosZ), _RotationSpeedPerSec(RotationSpeedPerSec), _moveForward(moveForward), _stuck(false)
{
}


/***********************************************************
process script part
return true if finished
***********************************************************/
bool WalkToPointScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor, bool & moved)
{
	// process with animation
	actor->Process(tnow, tdiff);

	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	boost::shared_ptr<DisplayObjectHandlerBase> disso = actor->GetDisplayObject();

	float curPosX, curPosY, curPosZ;
	physo->GetPosition(curPosX, curPosY, curPosZ);

	// check if we arrive at destination
	LbaVec3 diff(_PosX - curPosX, _PosY - curPosY, _PosZ - curPosZ);
	if(diff.FastLength() < 0.8)
		return true;

	// nav-mesh is in charge of moving the actor

	// just check if the nav-mesh got stuck
	LbaVec3 diffBefore(_lastPosX - curPosX, _lastPosY - curPosY, _lastPosZ - curPosZ);
	if(diffBefore.FastLength() < 0.001)
	{
		if (!_stuck)
		{
			_stuck = true;
			_lastime = tnow;
		}
		else
		{
			if ((tnow-_lastime) > 800)
			{
				_stuck = false;
				return true;
			}
		}
	}
	else
	{
		_lastPosX = curPosX;
		_lastPosY = curPosY;
		_lastPosZ = curPosZ;
		_stuck = false;
	}


	// set moved flag
	moved = true;

	return false;
}





/***********************************************************
	Constructor
***********************************************************/
PlayAnimationScriptPart::PlayAnimationScriptPart(int scriptid, bool asynchronus, bool AnimationMove, int nbAnimation)
	: ScriptPartBase(scriptid, asynchronus), _AnimationMove(AnimationMove), _nbAnimation(nbAnimation)
{
}

/***********************************************************
	Constructor
***********************************************************/
PlayAnimationScriptPart::PlayAnimationScriptPart(int scriptid, bool asynchronus, bool AnimationMove)
	: ScriptPartBase(scriptid, asynchronus), _AnimationMove(AnimationMove), _nbAnimation(1)
{
}



/***********************************************************
process script part
return true if finished
***********************************************************/
bool PlayAnimationScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor, bool & moved)
{
	// proces with animation
	int res = actor->Process(tnow, tdiff);
	if(res == 1)
	{
		--_nbAnimation;
		if (_nbAnimation == 0)
			return true;
	}


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

		// extra move
		float mx, my, mz, mr;
		actor->GetAdditionalMoves(mx, my, mz, mr);

		if(speedX != 0 || speedY != 0 || speedZ != 0)
		{
			//if (physo->GetUserData() && physo->GetUserData()->GetActorType() == LbaNet::CharControlAType) // special case for character controller
			//	physo->GetUserData()->SetAddedMove(ajustedspeedx*tdiff+mx, speedY*tdiff+my, ajustedspeedZ*tdiff+mz);
			//else
				physo->Move(ajustedspeedx*tdiff+mx, speedY*tdiff+my, ajustedspeedZ*tdiff+mz, false);
			
		}

		// set moved flag
		moved = true;
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
bool RotateScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor, bool & moved)
{
	actor->Process(tnow, tdiff);

	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	float currAngle = physo->GetRotationYAxis();

	// extra move
	float mx, my, mz, mr;
	actor->GetAdditionalMoves(mx, my, mz, mr);

	// set moved flag
	moved = true;

	double distance = (currAngle-_Angle);
	if(fabs(distance) > 2.0)
	{
		if((distance > 0 && distance < 180) || (distance < -180))
		{
			if(_ManageAnimation)
				actor->GetDisplayObject()->Update(new LbaNet::AnimationStringUpdate("TurnRight"), false);

			physo->RotateYAxis(std::max((-_RotationSpeedPerSec*tdiff)+mr, (-(float)fabs(distance))));
		}
		else
		{
			if(_ManageAnimation)
				actor->GetDisplayObject()->Update(new LbaNet::AnimationStringUpdate("TurnLeft"), false);

			physo->RotateYAxis(std::min((_RotationSpeedPerSec*tdiff)+mr, ((float)fabs(distance))));
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
bool GoToScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor, bool & moved)
{
	// proces with animation
	actor->Process(tnow, tdiff);

	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	boost::shared_ptr<DisplayObjectHandlerBase> disso = actor->GetDisplayObject();


	// check if we arrive at destination
	if(fabs(_distance-_distanceDone) < 0.01)
		return true;


	// set moved flag
	moved = true;


	// get speed
	_distanceDone += (_Speed) * tdiff;


	// extra move
	float mx, my, mz, mr;
	actor->GetAdditionalMoves(mx, my, mz, mr);
	float extramove = (mx*mx) + (my*my) + (mz*mz);
	extramove = sqrt(extramove);
	_distanceDone += extramove;


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
bool WaitForSignalScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor, bool & moved)
{
	// process with animation
	actor->Process(tnow, tdiff);

	return actor->ReceivedSignal(_SignalId);
}


SleepScriptPart::SleepScriptPart(int scriptid, bool asynchronus, int nbMilliseconds)
	: ScriptPartBase(scriptid, asynchronus), _nbMilliseconds(nbMilliseconds), _totalMilliseconds(0)
{

}


bool SleepScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor, bool & moved)
{
	// process with animation
	actor->Process(tnow, tdiff);

	_totalMilliseconds += static_cast<int>(tdiff);
	return (_totalMilliseconds >= _nbMilliseconds);
}





/***********************************************************
constructor
***********************************************************/
RotateFromPointScriptPart::RotateFromPointScriptPart(int scriptid, bool asynchronus, float ArrivalAngle, 
														float PosX, float PosY, float PosZ,
														float Speed, boost::shared_ptr<DynamicObject> actor)
: ScriptPartBase(scriptid, asynchronus), _PosX(PosX), _PosZ(PosZ), _Speed(Speed), _doneAngle(0),
	_actorid(actor->GetId())
		
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	physo->GetPosition(_startPosX, _startPosY, _startPosZ);

	float currY = physo->GetRotationYAxis();
	_Angle = ArrivalAngle - currY;

	while(_Angle < -180)
		_Angle += 360;
	while(_Angle > 180)
		_Angle -= 360;
}


/***********************************************************
//! process script part
//! return true if finished
***********************************************************/
bool RotateFromPointScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor, bool & moved)
{
	actor->Process(tnow, tdiff);

	if(fabs(_doneAngle) >= fabs(_Angle))
		return true;


	// set moved flag
	moved = true;

	// extra move
	float mx, my, mz, mr;
	actor->GetAdditionalMoves(mx, my, mz, mr);

	float move = fabs(_Speed) * tdiff/*+mr*/;
	if(_Angle < 0)
		move = -move;


	_doneAngle += move;
	if(fabs(_doneAngle) > fabs(_Angle))
	{
		float diff = (_doneAngle-_Angle);
		_doneAngle = _Angle;
		move += diff;
	}




	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	physo->RotateYAxis(move);


	//take care of translation
	float startvecX = _startPosX - _PosX;
	float startvecZ = _startPosZ - _PosZ;

	float rad = -_doneAngle * M_PI / 180.0f;

	float endvecX = (startvecX * cos(rad)) - (startvecZ * sin(rad));
	float endvecZ = (startvecX * sin(rad)) + (startvecZ * cos(rad));

	physo->MoveTo(endvecX+_PosX/*+mx*/, _startPosY/*+my*/, endvecZ+_PosZ/*+mz*/);

	return false;
}





/***********************************************************
constructor
***********************************************************/
FollowWaypointScriptPart::FollowWaypointScriptPart(int scriptid, bool asynchronus, 
												   int waypointindex1, int waypointindex2, 
													boost::shared_ptr<DynamicObject> actor)
: ScriptPartBase(scriptid, asynchronus), _distance(0), _distancedone(0)
{
	LbaVec3 defaultPos;
	actor->GetPhysicalObject()->GetPosition(defaultPos.x, defaultPos.y, defaultPos.z);


	_catmullH.SetWaypoints(actor->GetWaypoints(waypointindex1));
	_catmullH.UpdateCurrentPoint(waypointindex2, defaultPos);
	_distance = _catmullH.GetApproximateDistance();
}

/***********************************************************
constructor
***********************************************************/
FollowWaypointScriptPart::FollowWaypointScriptPart(int scriptid, bool asynchronus, 
							const LbaVec3 &Pm1, const LbaVec3 &P0, const LbaVec3 &P1, 
							const LbaVec3 &P2, const LbaVec3 &P3, const LbaVec3 & P4)
: ScriptPartBase(scriptid, asynchronus), _distance(0), _distancedone(0)
{
	std::vector<LbaVec3> waypoints;
	waypoints.push_back(Pm1);
	waypoints.push_back(P0);
	waypoints.push_back(P1);
	waypoints.push_back(P2);
	waypoints.push_back(P3);
	waypoints.push_back(P4);
	_catmullH.SetWaypoints(waypoints);
	_distance = _catmullH.GetApproximateDistance();
}





/***********************************************************
//! process script part
//! return true if finished
***********************************************************/
bool FollowWaypointScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor, bool & moved)
{
	actor->Process(tnow, tdiff);

	// check if we arrive at destination
	if(fabs(_distance) <= fabs(_distancedone))
		return true;


	// set moved flag
	moved = true;


	boost::shared_ptr<DisplayObjectHandlerBase> disso = actor->GetDisplayObject();
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();
	std::string animation = disso->GetCurrentAnimation();

	// get animation speed
	float speedX = disso->GetCurrentAssociatedSpeedX();
	float speedY = disso->GetCurrentAssociatedSpeedY();
	float speedZ = disso->GetCurrentAssociatedSpeedZ();

	float move = (speedX+speedY+speedZ) * tdiff;
	_distancedone += fabs(move);


	if(_distancedone > _distance)
		_distancedone = _distance;


	// calculate move on spline
	LbaVec3 resPos;
	float resAngle;
	float ratio = _distancedone/_distance;
	_catmullH.Compute(ratio, animation == "MoveForward", resPos, resAngle);

	// move actor
	physo->MoveTo(resPos.x, resPos.y, resPos.z);

	LbaQuaternion Q;
	Q.AddSingleRotation(resAngle, LbaVec3(0, 1, 0));
	physo->RotateTo(Q);

	return false;
}






/***********************************************************
	Constructor
***********************************************************/
TargetScriptPart::TargetScriptPart(int scriptid, bool asynchronus, 
							boost::shared_ptr<PhysicalObjectHandlerBase> object)
: ScriptPartBase(scriptid, asynchronus), _target(object)
{

}





/***********************************************************
//! process script part
//! return true if finished
***********************************************************/
bool TargetScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor, bool & moved)
{
	actor->Process(tnow, tdiff);

	if(!_target)
		return true;


	// set moved flag
	moved = true;

	boost::shared_ptr<PhysicalObjectHandlerBase> physo = actor->GetPhysicalObject();

	LbaVec3 curr;
	physo->GetPosition(curr.x, curr.y, curr.z);

	LbaVec3 other;
	_target->GetPosition(other.x, other.y, other.z);

	LbaVec3 diff(	other.x-curr.x, 
					other.y-curr.y, 
					other.z-curr.z);

	float angle = LbaQuaternion::GetSignedAngleFromVector(diff);

	LbaQuaternion Q;
	Q.AddSingleRotation(angle, LbaVec3(0, 1, 0));
	physo->RotateTo(Q);

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
bool ScriptedActor::ProcessScript(double tnow, float tdiff, ScriptEnvironmentBase* scripthandler)
{
	if(_currentScripts.size() > 0 && _character)
	{
		boost::shared_ptr<ScriptPartBase> firstscript = _currentScripts.front();

		bool moved = false;
		bool finished = firstscript->Process(tnow, tdiff, _character, moved);
		if(finished)
		{
			LogHandler::getInstance()->LogToFile("Script part finished", _character->GetId());

			int scid = firstscript->GetAttachedScriptId();
			bool asc = firstscript->IsAsynchronus();

			//tell script handler that script part is finished
			if(scripthandler)
				scripthandler->ScriptIsFinished(scid, asc);

			// delete script part
			_currentScripts.pop_front();
		}

		return moved;
	}

	return false;
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
void ScriptedActor::ActorWalkToPoint(int ScriptId, bool asynchronus, float PosX, float PosY, float PosZ, float RotationSpeedPerSec, bool moveForward)
{
	_currentScripts.push_back(boost::shared_ptr<ScriptPartBase>(
		new WalkToPointScriptPart(ScriptId, asynchronus, PosX, PosY, PosZ, RotationSpeedPerSec, moveForward)));
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
void ScriptedActor::ActorAnimate(int ScriptId, bool asynchronus, bool AnimationMove, int nbAnimation)
{
	_currentScripts.push_back(boost::shared_ptr<ScriptPartBase>(
						new PlayAnimationScriptPart(ScriptId, asynchronus, AnimationMove, nbAnimation)));
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


	

/***********************************************************
//! used by lua to move an actor or player
//! the actor will rotate
***********************************************************/
void ScriptedActor::ActorRotateFromPoint(int ScriptId, float Angle, float PosX, float PosY, 
													float PosZ, float Speed, bool asynchronus)
{
	_currentScripts.push_back(boost::shared_ptr<ScriptPartBase>(
						new RotateFromPointScriptPart(ScriptId, asynchronus, 
													Angle, PosX, PosY, PosZ, Speed, _character)));
}


	

/***********************************************************
//! used by lua to move an actor or player
//! the actor follow waypoint
***********************************************************/
void ScriptedActor::ActorFollowWaypoint(int ScriptId, int waypointindex1, int waypointindex2, bool asynchronus)
{
	_currentScripts.push_back(boost::shared_ptr<ScriptPartBase>(
						new FollowWaypointScriptPart(ScriptId, asynchronus, waypointindex1, 
						waypointindex2, _character)));
}


/***********************************************************
//! used by lua to move an actor or player
//! the actor follow waypoint
***********************************************************/
void ScriptedActor::ActorFollowWaypoint(int ScriptId, const LbaVec3 & Pm1, const LbaVec3 & P0,
										const LbaVec3 & P1, const LbaVec3 & P2, 
										const LbaVec3 & P3, const LbaVec3 & P4, bool asynchronus)
{
	_currentScripts.push_back(boost::shared_ptr<ScriptPartBase>(
						new FollowWaypointScriptPart(ScriptId, asynchronus, Pm1, P0, P1, P2, P3, P4)));
}

/***********************************************************
//! make an actor sleep for a given amount of time
***********************************************************/
void ScriptedActor::ActorSleep(int ScriptId, int nbMilliseconds, bool asynchronus)
{
	_currentScripts.push_back(boost::shared_ptr<ScriptPartBase>(
						new SleepScriptPart(ScriptId, asynchronus, nbMilliseconds)));
}

/***********************************************************
//! store current script
***********************************************************/
void ScriptedActor::StoreScript()
{
	_storedScripts.clear();
	_storedScripts.swap(_currentScripts);
}

/***********************************************************
//! restore current script
***********************************************************/
void ScriptedActor::RestoreScript()
{
	_storedScripts.swap(_currentScripts);
	_storedScripts.clear();
}


/***********************************************************
//! restore current script
***********************************************************/
bool ScriptedActor::CanPlayAnimation(const std::string & anim)
{
	if(_character)
	{
		boost::shared_ptr<DisplayObjectHandlerBase> dyso = _character->GetDisplayObject();
		if(dyso)
			return dyso->CanPlayAnimation(anim);
	}

	return false;
}

