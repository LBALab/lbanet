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
class ThreadedScriptHandlerBase;


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
	void ProcessScript(double tnow, float tdiff, ThreadedScriptHandlerBase* scripthandler);

	//! used by lua to move an actor
	//! the actor will move using animation speed
	void ActorStraightWalkTo(int ScriptId, bool asynchronus, float PosX, float PosY, float PosZ);

	//! used by lua to rotate an actor
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
	void ActorRotate(int ScriptId, bool asynchronus, float Angle, float RotationSpeedPerSec, bool ManageAnimation);

	//! used by lua to wait until an actor animation is finished
	//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
	void ActorAnimate(int ScriptId, bool asynchronus, bool AnimationMove);


protected:
	boost::shared_ptr<DynamicObject>						_character;
	std::list<boost::shared_ptr<ScriptPartBase> >			_currentScripts;
};

#endif