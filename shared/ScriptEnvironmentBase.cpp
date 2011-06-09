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


#include "ScriptEnvironmentBase.h"
#include "LogHandler.h"


/***********************************************************
start lua script in a separate thread
***********************************************************/
void ScriptEnvironmentBase::StartScript(const std::string & FunctionName, 
										bool inlinefunction, int &ThreadReference)
{
	ThreadReference = -1;

	if(m_luaHandler)
		m_luaHandler->StartScript(FunctionName, inlinefunction, this, ThreadReference);
}

/***********************************************************
start lua script in a separate thread
***********************************************************/
void ScriptEnvironmentBase::StartScript(const std::string & FunctionName, long ActorId, 
										bool inlinefunction, int &ThreadReference)
{
	ThreadReference = -1;

	if(m_luaHandler)
		 m_luaHandler->StartScript(FunctionName, ActorId, inlinefunction, this, ThreadReference);
}

/***********************************************************
execute lua script given as a string
***********************************************************/
void ScriptEnvironmentBase::ExecuteScriptString( const std::string &ScriptString )
{
	if(m_luaHandler)
		m_luaHandler->ExecuteScriptString(ScriptString);
}



/***********************************************************
called when a script is finished
***********************************************************/
void ScriptEnvironmentBase::ScriptFinished(int scriptid, bool wasasynchronus)
{
	if(!wasasynchronus)
	{
		ResumeThread(scriptid);
	}
	else
	{
		m_asyncscripts[scriptid] = true;
	}
}



/***********************************************************
wait until script part is finished
***********************************************************/
void ScriptEnvironmentBase::WaitForAsyncScript(int ScriptId, int ScriptPartId)
{
	m_waitingscripts[ScriptPartId] = ScriptId;
}


/***********************************************************
check for finished asynchronus scripts
***********************************************************/
void ScriptEnvironmentBase::CheckFinishedAsynScripts()
{
	// check waiting scripts
	{
		std::map<int, bool>::iterator itmap = m_waitingscripts.begin();
		while(itmap != m_waitingscripts.end())
		{
			bool erase = false;

			std::map<int, bool>::iterator its =	m_asyncscripts.find(itmap->first);
			if(its != m_asyncscripts.end())
			{
				if(its->second == true)
				{
					erase = true;
					m_asyncscripts.erase(its);
				}
			}
			else
				erase = true;

			if(erase)
			{
				ResumeThread(itmap->first);
				m_waitingscripts.erase(itmap++);
			}
			else
				++itmap;
		}
	}

	// check sleeping scripts
	{
		std::map<int, int>::iterator itmaps = m_sleepingscripts.begin();
		while(itmaps != m_sleepingscripts.end())
		{
			itmaps->second++;
			if(itmaps->second > 3)
			{
				ResumeThread(itmaps->first);
				m_sleepingscripts.erase(itmaps++);
			}
			else
			{
				++itmaps;
			}
		}
	}

}



/***********************************************************
asynchronus version of ActorStraightWalkTo
***********************************************************/
int ScriptEnvironmentBase::Async_ActorStraightWalkTo(long ActorId, const LbaVec3 &Position)
{
	int genid = m_generatednumber++;

	InternalActorStraightWalkTo(genid, ActorId, Position, true);

	m_asyncscripts[genid] = false;
	return genid;
}

/***********************************************************
asynchronus version of ActorRotate
***********************************************************/
int ScriptEnvironmentBase::Async_ActorRotate(long ActorId, float Angle, float RotationSpeedPerSec,
													bool ManageAnimation)
{
	int genid = m_generatednumber++;

	InternalActorRotate(genid, ActorId, Angle, RotationSpeedPerSec, ManageAnimation, true);

	m_asyncscripts[genid] = false;
	return genid;
}

/***********************************************************
asynchronus version of ActorAnimate
***********************************************************/
int ScriptEnvironmentBase::Async_ActorAnimate(long ActorId, bool AnimationMove)
{
	int genid = m_generatednumber++;

	InternalActorAnimate(genid, ActorId, AnimationMove, true);

	m_asyncscripts[genid] = false;
	return genid;
}


/***********************************************************
asynchronus version of ActorGoTo
***********************************************************/
int ScriptEnvironmentBase::Async_ActorGoTo(long ActorId, const LbaVec3 &Position, float Speed)
{
	int genid = m_generatednumber++;

	InternalActorGoTo(genid, ActorId, Position, Speed, true);

	m_asyncscripts[genid] = false;
	return genid;
}

/***********************************************************
asynchronus version of WaitForSignal
***********************************************************/
int ScriptEnvironmentBase::Async_WaitForSignal(long ActorId, int Signalnumber)
{
	int genid = m_generatednumber++;

	InternalActorWaitForSignal(genid, ActorId, Signalnumber, true);

	m_asyncscripts[genid] = false;
	return genid;
}


/***********************************************************
asynchronus version of WaitForSignal
***********************************************************/
int ScriptEnvironmentBase::Async_ActorRotateFromPoint(long ActorId, float Angle, const LbaVec3 &Position,
									float RotationSpeedPerSec)
{
	int genid = m_generatednumber++;

	InternalActorRotateFromPoint(genid, ActorId, Angle, Position, RotationSpeedPerSec, true);

	m_asyncscripts[genid] = false;
	return genid;
}

/***********************************************************
asynchronus version of WaitForSignal
***********************************************************/
int ScriptEnvironmentBase::Async_ActorFollowWaypoint(long ActorId,
												int waypointindex1, int waypointindex2)
{
	int genid = m_generatednumber++;

	InternalActorFollowWaypoint(genid, ActorId, waypointindex1, waypointindex2, true);

	m_asyncscripts[genid] = false;
	return genid;
}



/***********************************************************
make a lua script sleep for one cycle
***********************************************************/
void ScriptEnvironmentBase::WaitOneCycle(int scriptid)
{
	LogHandler::getInstance()->LogToFile("Wait one cycle.", scriptid);
	m_sleepingscripts[scriptid] = 0;
}


/***********************************************************
resume a thread given the id
***********************************************************/
void ScriptEnvironmentBase::ResumeThread(int scriptid)
{
	if(m_luaHandler)
	{
		std::string functioname;
		if(m_luaHandler->ResumeThread(scriptid, functioname))
		{
			ScriptFinished(scriptid, functioname); // inform when script is finished totally
		}
	}
}


/***********************************************************
resume a thread given the id
***********************************************************/
void ScriptEnvironmentBase::StropThread(int scriptid)
{
	if(m_luaHandler)
		m_luaHandler->StopThread(scriptid);
}

/***********************************************************
used by lua to log into file
***********************************************************/
void ScriptEnvironmentBase::LogToFile(const std::string &text)
{
	LogHandler::getInstance()->LogToFile(text);
}



//! used by lua to move an actor or player
//! the actor will move using animation speed
void ScriptEnvironmentBase::ActorStraightWalkTo(int ScriptId, long ActorId, const LbaVec3 &Position)
{
	InternalActorStraightWalkTo(ScriptId, ActorId, Position, false);
}

//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
//! if ManageAnimation is true then the animation will be changed to suit the rotation
void ScriptEnvironmentBase::ActorRotate(int ScriptId, long ActorId, float Angle, float RotationSpeedPerSec,
								bool ManageAnimation)
{
	InternalActorRotate(ScriptId, ActorId, Angle, RotationSpeedPerSec, ManageAnimation, false);
}

//! used by lua to wait until an actor animation is finished
//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
void ScriptEnvironmentBase::ActorAnimate(int ScriptId, long ActorId, bool AnimationMove)
{
	InternalActorAnimate(ScriptId, ActorId, AnimationMove, false);
}



//! used by lua to move an actor or player
//! the actor will move using animation speed
void ScriptEnvironmentBase::ActorGoTo(int ScriptId, long ActorId, const LbaVec3 &Position, float Speed)
{
	InternalActorGoTo(ScriptId, ActorId, Position, Speed, false);
}


//! used by lua to move an actor or player
//! the actor will move using animation speed
void ScriptEnvironmentBase::ActorWaitForSignal(int ScriptId, long ActorId, int Signalnumber)
{
	InternalActorWaitForSignal(ScriptId, ActorId, Signalnumber, false);
}


//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
//! if ManageAnimation is true then the animation will be changed to suit the rotation
void ScriptEnvironmentBase::ActorRotateFromPoint(int ScriptId, long ActorId, float Angle, const LbaVec3 &Position, 
								float RotationSpeedPerSec)
{
	InternalActorRotateFromPoint(ScriptId, ActorId, Angle, Position, RotationSpeedPerSec, false);
}


//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
//! if ManageAnimation is true then the animation will be changed to suit the rotation
void ScriptEnvironmentBase::ActorFollowWaypoint(int ScriptId, long ActorId, int waypointindex1, int waypointindex2)
{
	InternalActorFollowWaypoint(ScriptId, ActorId, waypointindex1, waypointindex2, false);
}


/***********************************************************/
//! check if thread is still running
/***********************************************************/
bool ScriptEnvironmentBase::ThreadRunning(int ScriptId)
{
	if(m_luaHandler)
		return m_luaHandler->ThreadRunning(ScriptId);

	return false;
}
