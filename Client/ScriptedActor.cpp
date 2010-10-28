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

}


/***********************************************************
process script part
return true if finished
***********************************************************/
bool StraightWalkToScriptPart::Process(double tnow, float tdiff, boost::shared_ptr<DynamicObject>	actor)
{

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