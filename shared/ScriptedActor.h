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

#if !defined(__SCRIPTED_ACTOR_h)
#define __SCRIPTED_ACTOR_h

#include <boost/shared_ptr.hpp>
#include <list>
class DynamicObject;
class ScriptEnvironmentBase;


/***********************************************************************
 * Module:  ScriptedActor.h
 * Author:  vivien
 * Purpose: Declaration of the class ScriptPartBase
 ***********************************************************************/
class ScriptPartBase
{
public:

	//! constructor
	ScriptPartBase(int scriptid, bool asynchronus)
		: _scriptid(scriptid), _asynchronus(asynchronus)
	{}

	//! destructor
	virtual ~ScriptPartBase(){}

	//! get the id of the attached script
	int GetAttachedScriptId()
	{return _scriptid;}

	//! return true if script was running Asynchronus
	bool IsAsynchronus()
	{return _asynchronus;}

	//! process script part
	//! return true if finished
	virtual bool Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor) = 0;

protected:

	int		_scriptid;
	bool	_asynchronus;
};



/***********************************************************************
 * Module:  ScriptedActor.h
 * Author:  vivien
 * Purpose: Declaration of the class WalkToScriptPart
 ***********************************************************************/
class StraightWalkToScriptPart : public ScriptPartBase
{
public:

	//! constructor
	StraightWalkToScriptPart(int scriptid, bool asynchronus, float PosX, float PosY, float PosZ,
						boost::shared_ptr<DynamicObject> actor);

	//! destructor
	virtual ~StraightWalkToScriptPart(){}


	//! process script part
	//! return true if finished
	virtual bool Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor);

protected:
	float	_PosX;
	float	_PosY;
	float	_PosZ;

	float	_StartPosX;
	float	_StartPosY;
	float	_StartPosZ;

	float	_distance;
	float	_distanceDone;
};



/***********************************************************************
 * Module:  ScriptedActor.h
 * Author:  vivien
 * Purpose: Declaration of the class AnimateScriptPart
 ***********************************************************************/
class PlayAnimationScriptPart : public ScriptPartBase
{
public:

	//! constructor
	PlayAnimationScriptPart(int scriptid, bool asynchronus, bool AnimationMove);

	//! destructor
	virtual ~PlayAnimationScriptPart(){}


	//! process script part
	//! return true if finished
	virtual bool Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor);

protected:
	bool	_AnimationMove;
};



/***********************************************************************
 * Module:  ScriptedActor.h
 * Author:  vivien
 * Purpose: Declaration of the class AnimateScriptPart
 ***********************************************************************/
class RotateScriptPart : public ScriptPartBase
{
public:

	//! constructor
	RotateScriptPart(int scriptid, bool asynchronus, float Angle, 
						float RotationSpeedPerSec, bool ManageAnimation);

	//! destructor
	virtual ~RotateScriptPart(){}


	//! process script part
	//! return true if finished
	virtual bool Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor);

protected:
	float	_RotationSpeedPerSec;
	float	_Angle;
	bool	_ManageAnimation;
};






/***********************************************************************
 * Module:  ScriptedActor.h
 * Author:  vivien
 * Purpose: Declaration of the class GoToScriptPart
 ***********************************************************************/
class GoToScriptPart : public ScriptPartBase
{
public:

	//! constructor
	GoToScriptPart(int scriptid, bool asynchronus, float PosX, float PosY, float PosZ,
								float Speed, boost::shared_ptr<DynamicObject> actor);

	//! destructor
	virtual ~GoToScriptPart(){}


	//! process script part
	//! return true if finished
	virtual bool Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor);

protected:
	float	_PosX;
	float	_PosY;
	float	_PosZ;
	float	_Speed;

	float	_StartPosX;
	float	_StartPosY;
	float	_StartPosZ;

	float	_distance;
	float	_distanceDone;
};





/***********************************************************************
 * Module:  ScriptedActor.h
 * Author:  vivien
 * Purpose: Declaration of the class GoToScriptPart
 ***********************************************************************/
class WaitForSignalScriptPart : public ScriptPartBase
{
public:

	//! constructor
	WaitForSignalScriptPart(int scriptid, bool asynchronus, int SignalId);

	//! destructor
	virtual ~WaitForSignalScriptPart(){}


	//! process script part
	//! return true if finished
	virtual bool Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor);

protected:
	int		_SignalId;
};




/***********************************************************************
 * Module:  ScriptedActor.h
 * Author:  vivien
 * Purpose: Declaration of the class GoToScriptPart
 ***********************************************************************/
class RotateFromPointScriptPart : public ScriptPartBase
{
public:

	//! constructor
	RotateFromPointScriptPart(int scriptid, bool asynchronus, float Angle, float PosX, float PosY, float PosZ,
								float Speed, boost::shared_ptr<DynamicObject> actor);

	//! destructor
	virtual ~RotateFromPointScriptPart(){}


	//! process script part
	//! return true if finished
	virtual bool Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor);

protected:
	float	_PosX;
	float	_PosZ;
	float	_startPosX;
	float	_startPosY;
	float	_starPosZ;
	float	_Speed;
	float	_Angle;
	float	_doneAngle;

};




/***********************************************************************
 * Module:  ScriptedActor.h
 * Author:  vivien
 * Purpose: Declaration of the class GoToScriptPart
 ***********************************************************************/
class FollowWaypointScriptPart : public ScriptPartBase
{
public:

	//! constructor
	FollowWaypointScriptPart(int scriptid, bool asynchronus, int waypointindex1, int waypointindex2, 
								boost::shared_ptr<DynamicObject> actor);

	//! destructor
	virtual ~FollowWaypointScriptPart(){}


	//! process script part
	//! return true if finished
	virtual bool Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor);


protected:
	//! calculate spline from to between 0 and 1
	float CatmullSpline(float P0, float P1, float P2, float P3, float t);

	//! calculate spline of vector from to between 0 and 1
	LbaVec3 CatmullSpline(LbaVec3 P0, LbaVec3 P1, LbaVec3 P2, LbaVec3 P3, float t);

	//! calculate arc length
	float GetArcLength(LbaVec3 P0, LbaVec3 P1, LbaVec3 P2, LbaVec3 P3, int nbsamples);

private:
	float			_distance;
	float			_distancedone;
	LbaVec			_P0;
	LbaVec			_P1;
	LbaVec			_P2;
	LbaVec			_P3;
};









/***********************************************************************
 * Module:  ScriptedActor.h
 * Author:  vivien
 * Purpose: Declaration of the class ScriptedActor
 ***********************************************************************/
class ScriptedActor
{
public:
	//! constructor
	ScriptedActor();

	//! destructor
	virtual ~ScriptedActor();

	//! process function
	void ProcessScript(double tnow, float tdiff, ScriptEnvironmentBase* scripthandler);

	//! used by lua to move an actor
	//! the actor will move using animation speed
	void ActorStraightWalkTo(int ScriptId, bool asynchronus, float PosX, float PosY, float PosZ);

	//! used by lua to rotate an actor
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
	void ActorRotate(int ScriptId, bool asynchronus, float Angle, float RotationSpeedPerSec, 
					bool ManageAnimation);

	//! used by lua to wait until an actor animation is finished
	//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
	void ActorAnimate(int ScriptId, bool asynchronus, bool AnimationMove);

	
	//! used by lua to move an actor or player
	//! the actor will move using speed
	void ActorGoTo(int ScriptId, float PosX, float PosY, float PosZ, float Speed, bool asynchronus);
	

	//! used by lua to move an actor or player
	//! the actor will wait for signal
	void ActorWaitForSignal(int ScriptId, int Signalnumber, bool asynchronus);

	//! clear all running scripts
	void ClearAllScripts();

	
	//! used by lua to move an actor or player
	//! the actor will rotate
	void ActorRotateFromPoint(int ScriptId, float Angle, float PosX, float PosY, 
													float PosZ, float Speed, bool asynchronus);


	
	//! used by lua to move an actor or player
	//! the actor follow waypoint
	void ActorFollowWaypoint(int ScriptId, int waypointindex1, int waypointindex2, bool asynchronus);


protected:
	boost::shared_ptr<DynamicObject>						_character;
	std::list<boost::shared_ptr<ScriptPartBase> >			_currentScripts;
};

#endif