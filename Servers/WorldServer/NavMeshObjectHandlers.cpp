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

#include "NavMeshObjectHandlers.h"
#include "ObjectsDescription.h"
#include "LogHandler.h"
#include "NavMeshAgent.h"

#include <math.h>


/***********************************************************
	Constructor
***********************************************************/
NavMeshObjectHandler::NavMeshObjectHandler(boost::shared_ptr<NavMeshAgent> agent,
											float pX, float pY, float pZ,
											const LbaQuaternion& Q)
: _agent(agent), SimplePhysicalObjectHandler(pX, pY, pZ, Q), _lasttdiff(1)
{

}


/***********************************************************
get object position in the world
***********************************************************/
void NavMeshObjectHandler::GetPosition(float &X, float &Y, float &Z)
{
	if(_agent)
		_agent->GetPosition(X, Y, Z);
}


/***********************************************************
set object position in the world
***********************************************************/
void NavMeshObjectHandler::SetPosition(float X, float Y, float Z)
{
	if(_agent)
		_agent->SetPosition(X, Y, Z);
}


/***********************************************************
move object in the world
***********************************************************/
void NavMeshObjectHandler::Move(float deltaX, float deltaY, float deltaZ, bool checkcollision)
{
	_lastmoveX = deltaX;
	_lastmoveY = deltaY;
	_lastmoveZ = deltaZ;

	if(_agent) // crowd manager is multiplying by time already so we nend to remove the time factor
		_agent->UpdateSpeed(deltaX/_lasttdiff, deltaY/_lasttdiff, deltaZ/_lasttdiff);

}

/***********************************************************
move object to a position in the world
***********************************************************/
void NavMeshObjectHandler::MoveTo(float X, float Y, float Z)
{
	float cX, cY, cZ;
	GetPosition(cX, cY, cZ);

	_lastmoveX = X-cX;
	_lastmoveY = Y-cY;
	_lastmoveZ = Z-cZ;

	if(_agent) // crowd manager is multiplying by time already so we nend to remove the time factor
		_agent->UpdateSpeed(_lastmoveX/_lasttdiff, _lastmoveY/_lasttdiff, _lastmoveZ/_lasttdiff);
}

/***********************************************************
	show or hide the object
***********************************************************/
void NavMeshObjectHandler::ShowOrHide(bool Show)
{
	if(_agent)
		_agent->ShowOrHide(Show);
}


/***********************************************************
	process physic
***********************************************************/
void NavMeshObjectHandler::Process(double tnow, float tdiff,
										float animSpeedX, float animSpeedY, float animSpeedZ)
{
	_lasttdiff = tdiff;

	if(_agent)
	{
		if(!_agent->IsTargeting())
			_agent->UpdateSpeed(0, 0, 0);
		else
		{

			//update rotation
			float gangle;
			if(_agent->GetAngle(gangle))
			{
				LbaQuaternion Q;
				Q.AddSingleRotation(gangle, LbaVec3(0, 1, 0));
				_rotH.SetRotation(Q);
			}
		}

		_agent->UpdateMaxSpeed(fabs(animSpeedX+animSpeedY+animSpeedZ));
	}
}