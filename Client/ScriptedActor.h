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

class DynamicObject;
class ClientLuaHandler;


/***********************************************************************
 * Module:  ScriptedActor.h
 * Author:  vivien
 * Purpose: Declaration of the class ScriptPartBase
 ***********************************************************************/
class ScriptPartBase
{
public:

	//! constructor
	ScriptPartBase(int scriptid)
		: _scriptid(scriptid)
	{}

	//! destructor
	virtual ~ScriptPartBase(){}

	//! get the id of the attached script
	int GetAttachedScriptId()
	{return _scriptid;}

	//! process script part
	//! return true if finished
	virtual bool Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor) = 0;

protected:

	int _scriptid;
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
	StraightWalkToScriptPart(int scriptid, float PosX, float PosY, float PosZ,
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
	void ProcessScript(double tnow, float tdiff, boost::shared_ptr<ClientLuaHandler> scripthandler);

	//! used by lua to move an actor or player
	//! if id < 1 then it moves players
	//! the actor will move using animation speed
	void ActorStraightWalkTo(int ScriptId, float PosX, float PosY, float PosZ);

protected:
	boost::shared_ptr<DynamicObject>			_character;
	boost::shared_ptr<ScriptPartBase>			_currentScript;
};

#endif