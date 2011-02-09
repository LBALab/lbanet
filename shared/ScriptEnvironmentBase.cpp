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



/***********************************************************
start lua script in a separate thread
***********************************************************/
int ScriptEnvironmentBase::StartScript(const std::string & FunctionName, bool inlinefunction)
{
	if(m_luaHandler)
		return  m_luaHandler->StartScript(FunctionName, inlinefunction, this);

	return -1;
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
			itmap = m_waitingscripts.erase(itmap);
		}
		else
			++itmap;
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
resume a thread given the id
***********************************************************/
void ScriptEnvironmentBase::ResumeThread(int scriptid)
{
	if(m_luaHandler)
	{
		std::string functioname;
		if(m_luaHandler->ResumeThread(scriptid, functioname))
			ScriptFinished(scriptid, functioname); // inform when script is finished totally	
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