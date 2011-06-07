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

#include <boost/bind.hpp>

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
		//IceUtil::Mutex::Lock sync(m_mutex);
		m_asyncscripts[scriptid] = true;
	}
}



/***********************************************************
wait until script part is finished
***********************************************************/
void ScriptEnvironmentBase::WaitForAsyncScript(int ScriptId, int ScriptPartId)
{
	//IceUtil::Mutex::Lock sync(m_mutex);
	m_waitingscripts[ScriptPartId] = ScriptId;
}


/***********************************************************
check for finished asynchronus scripts
***********************************************************/
void ScriptEnvironmentBase::CheckFinishedAsynScripts()
{
	{
		//IceUtil::Mutex::Lock sync(m_mutex);

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


	// do lua calls
	{
		//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
		//while(m_waiting_luacall > 0)
		//{
		//	m_monitor.notify();
		//	m_monitor.wait();
		//}
	}
}



/***********************************************************
generate script id
***********************************************************/
int ScriptEnvironmentBase::GenerateScriptId()
{
	//IceUtil::Mutex::Lock sync(m_mutex);
	return m_generatednumber++;
}


/***********************************************************
asynchronus version of ActorStraightWalkTo
***********************************************************/
int ScriptEnvironmentBase::Async_ActorStraightWalkTo(long ActorId, const LbaVec3 &Position)
{
	int genid = GenerateScriptId();

	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorStraightWalkTo(genid, ActorId, Position, true);

	//IceUtil::Mutex::Lock sync(m_mutex);
	m_asyncscripts[genid] = false;
	return genid;
}

/***********************************************************
asynchronus version of ActorRotate
***********************************************************/
int ScriptEnvironmentBase::Async_ActorRotate(long ActorId, float Angle, float RotationSpeedPerSec,
													bool ManageAnimation)
{
	int genid = GenerateScriptId();

	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorRotate(genid, ActorId, Angle, RotationSpeedPerSec, ManageAnimation, true);

	//IceUtil::Mutex::Lock sync(m_mutex);
	m_asyncscripts[genid] = false;
	return genid;
}

/***********************************************************
asynchronus version of ActorAnimate
***********************************************************/
int ScriptEnvironmentBase::Async_ActorAnimate(long ActorId, bool AnimationMove)
{
	int genid = GenerateScriptId();

	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorAnimate(genid, ActorId, AnimationMove, true);

	//IceUtil::Mutex::Lock sync(m_mutex);
	m_asyncscripts[genid] = false;
	return genid;
}


/***********************************************************
asynchronus version of ActorGoTo
***********************************************************/
int ScriptEnvironmentBase::Async_ActorGoTo(long ActorId, const LbaVec3 &Position, float Speed)
{
	int genid = GenerateScriptId();

	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorGoTo(genid, ActorId, Position, Speed, true);

	//IceUtil::Mutex::Lock sync(m_mutex);
	m_asyncscripts[genid] = false;
	return genid;
}

/***********************************************************
asynchronus version of WaitForSignal
***********************************************************/
int ScriptEnvironmentBase::Async_WaitForSignal(long ActorId, int Signalnumber)
{
	int genid = GenerateScriptId();

	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorWaitForSignal(genid, ActorId, Signalnumber, true);

	//IceUtil::Mutex::Lock sync(m_mutex);
	m_asyncscripts[genid] = false;
	return genid;
}


/***********************************************************
asynchronus version of WaitForSignal
***********************************************************/
int ScriptEnvironmentBase::Async_ActorRotateFromPoint(long ActorId, float Angle, const LbaVec3 &Position,
									float RotationSpeedPerSec)
{
	int genid = GenerateScriptId();

	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorRotateFromPoint(genid, ActorId, Angle, Position, RotationSpeedPerSec, true);

	//IceUtil::Mutex::Lock sync(m_mutex);
	m_asyncscripts[genid] = false;
	return genid;
}

/***********************************************************
asynchronus version of WaitForSignal
***********************************************************/
int ScriptEnvironmentBase::Async_ActorFollowWaypoint(long ActorId,
												int waypointindex1, int waypointindex2)
{
	int genid = GenerateScriptId();

	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorFollowWaypoint(genid, ActorId, waypointindex1, waypointindex2, true);

	//IceUtil::Mutex::Lock sync(m_mutex);
	m_asyncscripts[genid] = false;
	return genid;
}


/***********************************************************
make a lua script sleep for one cycle
***********************************************************/
void ScriptEnvironmentBase::WaitOneCycle(int scriptid)
{
	//IceUtil::Mutex::Lock sync(m_mutex);
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



/***********************************************************/
//! used by lua to move an actor or player
//! the actor will move using animation speed
/***********************************************************/
void ScriptEnvironmentBase::ActorStraightWalkTo(int ScriptId, long ActorId, const LbaVec3 &Position)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorStraightWalkTo(ScriptId, ActorId, Position, false);
}

/***********************************************************/
//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
//! if ManageAnimation is true then the animation will be changed to suit the rotation
/***********************************************************/
void ScriptEnvironmentBase::ActorRotate(int ScriptId, long ActorId, float Angle, float RotationSpeedPerSec,
								bool ManageAnimation)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorRotate(ScriptId, ActorId, Angle, RotationSpeedPerSec, ManageAnimation, false);
}

/***********************************************************/
//! used by lua to wait until an actor animation is finished
//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
/***********************************************************/
void ScriptEnvironmentBase::ActorAnimate(int ScriptId, long ActorId, bool AnimationMove)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorAnimate(ScriptId, ActorId, AnimationMove, false);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor will move using animation speed
/***********************************************************/
void ScriptEnvironmentBase::ActorGoTo(int ScriptId, long ActorId, const LbaVec3 &Position, float Speed)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorGoTo(ScriptId, ActorId, Position, Speed, false);
}


/***********************************************************/
//! used by lua to move an actor or player
//! the actor will move using animation speed
/***********************************************************/
void ScriptEnvironmentBase::ActorWaitForSignal(int ScriptId, long ActorId, int Signalnumber)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorWaitForSignal(ScriptId, ActorId, Signalnumber, false);
}


/***********************************************************/
//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
//! if ManageAnimation is true then the animation will be changed to suit the rotation
/***********************************************************/
void ScriptEnvironmentBase::ActorRotateFromPoint(int ScriptId, long ActorId, float Angle, const LbaVec3 &Position, 
								float RotationSpeedPerSec)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorRotateFromPoint(ScriptId, ActorId, Angle, Position, RotationSpeedPerSec, false);
}


/***********************************************************/
//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
//! if ManageAnimation is true then the animation will be changed to suit the rotation
/***********************************************************/
void ScriptEnvironmentBase::ActorFollowWaypoint(int ScriptId, long ActorId, int waypointindex1, int waypointindex2)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorFollowWaypoint(ScriptId, ActorId, waypointindex1, waypointindex2, false);
}







/***********************************************************/
//! used by lua to tell that the actor should be reserved for the script
/***********************************************************/
void ScriptEnvironmentBase::ReserveActor(int ScriptId, long ActorId)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalReserveActor(ScriptId, ActorId);
}



/***********************************************************/
//! used by lua to get an actor Position
/***********************************************************/
LbaVec3 ScriptEnvironmentBase::GetActorPosition(int ScriptId, long ActorId)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	return InternalGetActorPosition(ScriptId, ActorId);
}


/***********************************************************/
//! used by lua to get an actor Rotation
/***********************************************************/
float ScriptEnvironmentBase::GetActorRotation(int ScriptId, long ActorId)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	return InternalGetActorRotation(ScriptId, ActorId);
}


 
/***********************************************************/
//! used by lua to get an actor Rotation
/***********************************************************/
LbaQuaternion ScriptEnvironmentBase::GetActorRotationQuat(int ScriptId, long ActorId)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	return InternalGetActorRotationQuat(ScriptId, ActorId);
}


 
/***********************************************************/
//! return targeted player
/***********************************************************/
long ScriptEnvironmentBase::GetTargettedAttackPlayer(long ActorId)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	return InternalGetTargettedAttackPlayer(ActorId);
}


/***********************************************************/
//! check if target is in range
/***********************************************************/
bool ScriptEnvironmentBase::IsTargetInRange(float MaxDistance, long ActorId)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	return InternalIsTargetInRange(MaxDistance, ActorId);
}


 
/***********************************************************/
//! check if target is in rotation range
/***********************************************************/
float ScriptEnvironmentBase::GetTargetRotationDiff(long ActorId)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	return InternalGetTargetRotationDiff(ActorId);
}


 
/***********************************************************/
//! get weapon distance
//! 1-> first contact weapon, 2 -> first distance weapon
//! 3-> second contact weapon, 4 -> second distance weapon
/***********************************************************/
float ScriptEnvironmentBase::GetNpcWeaponReachDistance(long ActorId, int WeaponNumber)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	return InternalGetNpcWeaponReachDistance(ActorId, WeaponNumber);
}


 
/***********************************************************/
// check if actor can play animation
// ObjectType ==>
//! 1 -> npc object
//! 2 -> player object
//! 3 -> movable object
/***********************************************************/
bool ScriptEnvironmentBase::CanPlayAnimation(int ObjectType, long ObjectId, 
											 const std::string & anim)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	return InternalCanPlayAnimation(ObjectType, ObjectId, anim);
}






/***********************************************************/
//! used by lua to update an actor animation
/***********************************************************/
void ScriptEnvironmentBase::UpdateActorAnimation(int ScriptId, long ActorId, 
												 const std::string & AnimationString)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalUpdateActorAnimation(ScriptId, ActorId, AnimationString);
}



/***********************************************************/
//! used by lua to update an actor mode
/***********************************************************/
void ScriptEnvironmentBase::UpdateActorMode(int ScriptId, long ActorId, const std::string & Mode)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalUpdateActorMode(ScriptId, ActorId, Mode);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor will change model
/***********************************************************/
void ScriptEnvironmentBase::UpdateActorModel(int ScriptId, long ActorId, const std::string & Name)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalUpdateActorModel(ScriptId, ActorId, Name);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor will change outfit
/***********************************************************/
void ScriptEnvironmentBase::UpdateActorOutfit(int ScriptId, long ActorId, const std::string & Name)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalUpdateActorOutfit(ScriptId, ActorId, Name);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor will change weapon
/***********************************************************/
void ScriptEnvironmentBase::UpdateActorWeapon(int ScriptId, long ActorId, const std::string & Name)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalUpdateActorWeapon(ScriptId, ActorId, Name);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor will move using animation speed
/***********************************************************/
void ScriptEnvironmentBase::TeleportActorTo(int ScriptId, long ActorId, const LbaVec3 &Position)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalTeleportActorTo(ScriptId, ActorId, Position);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor change rotation
/***********************************************************/
void ScriptEnvironmentBase::SetActorRotation(int ScriptId, long ActorId, float Angle)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalSetActorRotation(ScriptId, ActorId, Angle);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor show/hide
/***********************************************************/
void ScriptEnvironmentBase::ActorShowHide(int ScriptId, long ActorId, bool Show)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalActorShowHide(ScriptId, ActorId, Show);
}




/***********************************************************/
//! used by lua to send signal to actor
/***********************************************************/
void ScriptEnvironmentBase::SendSignalToActor(long ActorId, int Signalnumber)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalSendSignalToActor(ActorId, Signalnumber);
}



/***********************************************************/
// AttachActor
// ObjectType ==>
//! 1 -> npc object
//! 2 -> player object
//! 3 -> movable object
/***********************************************************/
void ScriptEnvironmentBase::AttachActor(long ActorId, int AttachedObjectType, 
										long AttachedObjectId)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalAttachActor(ActorId, AttachedObjectType, AttachedObjectId);
}



/***********************************************************/
// DettachActor
// ObjectType ==>
//! 1 -> npc object
//! 2 -> player object
//! 3 -> movable object
/***********************************************************/
void ScriptEnvironmentBase::DettachActor(long ActorId, long AttachedObjectId)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalDettachActor(ActorId, AttachedObjectId);
}



/***********************************************************/
//! npc use weapon
//! 1-> first contact weapon, 2 -> first distance weapon
//! 3-> second contact weapon, 4 -> second distance weapon
/***********************************************************/
void ScriptEnvironmentBase::UseWeapon(int ScriptId, long ActorId, int WeaponNumber)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalUseWeapon(ScriptId, ActorId, WeaponNumber);
}






/***********************************************************/
//! npc rotate to player
/***********************************************************/
void ScriptEnvironmentBase::RotateToTargettedPlayer(int ScriptId, long ActorId, 
													float ToleranceAngle, float speed)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalRotateToTargettedPlayer(ScriptId, ActorId, ToleranceAngle, speed);
}


/***********************************************************/
//! npc follow player
/***********************************************************/
void ScriptEnvironmentBase::FollowTargettedPlayer(int ScriptId, long ActorId, float DistanceStopFollow)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalFollowTargettedPlayer(ScriptId, ActorId, DistanceStopFollow);
}


/***********************************************************/
//! npc start use weapon - will not stop until changing state - only usefull for distance weapon
//! 1-> first contact weapon, 2 -> first distance weapon
//! 3-> second contact weapon, 4 -> second distance weapon
/***********************************************************/
void ScriptEnvironmentBase::StartUseWeapon(int ScriptId, long ActorId, int WeaponNumber)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	InternalStartUseWeapon(ScriptId, ActorId, WeaponNumber);
}



/***********************************************************/
//! check if thread is still running
/***********************************************************/
bool ScriptEnvironmentBase::ThreadRunning(int ScriptId)
{
	//IceUtil::Monitor<IceUtil::Mutex>::Lock lock(m_monitor);
	//++m_waiting_luacall;

	//m_monitor.wait();
	//m_monitor.notify();

	//--m_waiting_luacall;

	if(m_luaHandler)
		return m_luaHandler->ThreadRunning(ScriptId);

	return false;
}