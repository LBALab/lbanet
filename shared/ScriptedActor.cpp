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
bool PlayAnimationScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor, bool & moved)
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

		// extra move
		float mx, my, mz, mr;
		actor->GetAdditionalMoves(mx, my, mz, mr);

		if(speedX != 0 || speedY != 0 || speedZ != 0)
			physo->Move(ajustedspeedx*tdiff+mx, speedY*tdiff+my, ajustedspeedZ*tdiff+mz, false);

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
	// proces with animation
	actor->Process(tnow, tdiff);

	return actor->ReceivedSignal(_SignalId);
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
	std::vector<LbaVec3> waypoints = actor->GetWaypoints(waypointindex1);
	if(waypoints.size() > 0)
	{
		if(waypointindex2 < (int)waypoints.size())
		{
			_P2 =  waypoints[waypointindex2];

			if((waypointindex2+1) < (int)waypoints.size())
				_P3 = waypoints[waypointindex2+1];
			else
				_P3 = _P2;

			if((waypointindex2+2) < (int)waypoints.size())
				_P4 = waypoints[waypointindex2+2];
			else
				_P4 = _P2;

			--waypointindex2;
			if(waypointindex2 >= 0)
				_P1 =  waypoints[waypointindex2];
			else
				actor->GetPhysicalObject()->GetPosition(_P1.x, _P1.y, _P1.z);

			--waypointindex2;
			if(waypointindex2 >= 0)
				_P0 =  waypoints[waypointindex2];
			else
				_P0 =  _P1;

			--waypointindex2;
			if(waypointindex2 >= 0)
				_Pm1 =  waypoints[waypointindex2];
			else
				_Pm1 =  _P1;

			_distance = GetArcLength(_P0, _P1, _P2, _P3, 100);
		}
	}
}

/***********************************************************
constructor
***********************************************************/
FollowWaypointScriptPart::FollowWaypointScriptPart(int scriptid, bool asynchronus, 
							const LbaVec3 &Pm1, const LbaVec3 &P0, const LbaVec3 &P1, 
							const LbaVec3 &P2, const LbaVec3 &P3, const LbaVec3 & P4)
: ScriptPartBase(scriptid, asynchronus), _distance(0), _distancedone(0)
{
	_Pm1 = Pm1;
	_P0 = P0;
	_P1 = P1;
	_P2 = P2;
	_P3 = P3;
	_P4 = P4;

	_distance = GetArcLength(_P0, _P1, _P2, _P3, 100);
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
	float ratio = _distancedone/_distance;
	LbaVec3 res = CatmullSpline(_P0, _P1, _P2, _P3, ratio);
	LbaVec3 curr;
	physo->GetPosition(curr.x, curr.y, curr.z);


	// move actor
	physo->MoveTo(res.x, res.y, res.z);


	LbaVec3 tang1;
	LbaVec3 tang2;

	float r1 = ratio-0.1f;
	if(r1 < 0)
	{
		r1 += 1;
		tang1 = CatmullSpline(_Pm1, _P0, _P1, _P2, r1);
	}
	else
		tang1 = CatmullSpline(_P0, _P1, _P2, _P3, r1);

	float r2 = ratio+0.1f;
	if(r2 > 1)
	{
		r2 -= 1;
		tang2 = CatmullSpline(_P1, _P2, _P3, _P4, r2);
	}
	else
		tang2 = CatmullSpline(_P0, _P1, _P2, _P3, r2);


	LbaVec3 diff(	tang2.x-tang1.x, 
					tang2.y-tang1.y, 
					tang2.z-tang1.z);

	float angle = LbaQuaternion::GetSignedAngleFromVector(diff);
	if(animation != "MoveForward")
		angle += 180;


	LbaQuaternion Q;
	Q.AddSingleRotation(angle, LbaVec3(0, 1, 0));
	physo->RotateTo(Q);

	return false;
}


/***********************************************************
//! calculate spline from to between 0 and 1
***********************************************************/
float FollowWaypointScriptPart::CatmullSpline(float P0, float P1, float P2, float P3, float t)
{
	float res =	0.5f *( (2 * P1) + (-P0 + P2) * t 
				+ (2*P0 - 5*P1 + 4*P2 - P3) * t*t 
				+ (-P0 + 3*P1- 3*P2 + P3) * t*t*t);

	return res;
}


/***********************************************************
calculate spline of vector from to between 0 and 1
***********************************************************/
LbaVec3 FollowWaypointScriptPart::CatmullSpline(const LbaVec3 &P0, const LbaVec3 &P1, 
												const LbaVec3 &P2, const LbaVec3 &P3, float t)
{
	LbaVec3 res;
	res.x = CatmullSpline(P0.x, P1.x, P2.x, P3.x, t);
	res.y = CatmullSpline(P0.y, P1.y, P2.y, P3.y, t);
	res.z = CatmullSpline(P0.z, P1.z, P2.z, P3.z, t);

	return res;
}


/***********************************************************
calculate arc length
***********************************************************/
float FollowWaypointScriptPart::GetArcLength(const LbaVec3 &P0, const LbaVec3 &P1, 
											 const LbaVec3 &P2, const LbaVec3 &P3, int nbsamples)
{
	float res = 0;
	LbaVec3 currpoint = P1;
	for(int i=0; i < nbsamples; ++i)
	{
		float t = (1.0f / nbsamples) * i;
		LbaVec3 respoint = CatmullSpline(P0, P1, P2, P3, t);
		res += respoint.Distance(currpoint);
		currpoint = respoint;
	}

	return res;
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

