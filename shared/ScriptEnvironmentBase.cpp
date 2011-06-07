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
		IceUtil::Mutex::Lock sync(m_mutex);
		m_asyncscripts[scriptid] = true;
	}
}



/***********************************************************
wait until script part is finished
***********************************************************/
void ScriptEnvironmentBase::WaitForAsyncScript(int ScriptId, int ScriptPartId)
{
	IceUtil::Mutex::Lock sync(m_mutex);
	m_waitingscripts[ScriptPartId] = ScriptId;
}


/***********************************************************
check for finished asynchronus scripts
***********************************************************/
void ScriptEnvironmentBase::CheckFinishedAsynScripts()
{
	IceUtil::Mutex::Lock sync(m_mutex);

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
generate script id
***********************************************************/
int ScriptEnvironmentBase::GenerateScriptId()
{
	IceUtil::Mutex::Lock sync(m_mutex);
	return m_generatednumber++;
}


/***********************************************************
asynchronus version of ActorStraightWalkTo
***********************************************************/
int ScriptEnvironmentBase::Async_ActorStraightWalkTo(long ActorId, const LbaVec3 &Position)
{
	int genid = GenerateScriptId();

	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorStraightWalkTo, this, genid, ActorId, Position, true)));
	m_callbacks.push_back(calb);

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

	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorRotate, this, genid, ActorId, Angle, RotationSpeedPerSec, ManageAnimation, true)));
	m_callbacks.push_back(calb);

	m_asyncscripts[genid] = false;
	return genid;
}

/***********************************************************
asynchronus version of ActorAnimate
***********************************************************/
int ScriptEnvironmentBase::Async_ActorAnimate(long ActorId, bool AnimationMove)
{
	int genid = GenerateScriptId();

	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorAnimate, this, genid, ActorId, AnimationMove, true)));
	m_callbacks.push_back(calb);

	m_asyncscripts[genid] = false;
	return genid;
}


/***********************************************************
asynchronus version of ActorGoTo
***********************************************************/
int ScriptEnvironmentBase::Async_ActorGoTo(long ActorId, const LbaVec3 &Position, float Speed)
{
	int genid = GenerateScriptId();

	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorGoTo, this, genid, ActorId, Position, Speed, true)));
	m_callbacks.push_back(calb);

	m_asyncscripts[genid] = false;
	return genid;
}

/***********************************************************
asynchronus version of WaitForSignal
***********************************************************/
int ScriptEnvironmentBase::Async_WaitForSignal(long ActorId, int Signalnumber)
{
	int genid = GenerateScriptId();

	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorWaitForSignal, this, genid, ActorId, Signalnumber, true)));
	m_callbacks.push_back(calb);

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

	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorRotateFromPoint, this, genid, ActorId, Angle, Position, RotationSpeedPerSec, true)));
	m_callbacks.push_back(calb);

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

	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorFollowWaypoint, this, genid, ActorId, waypointindex1, waypointindex2, true)));
	m_callbacks.push_back(calb);

	m_asyncscripts[genid] = false;
	return genid;
}



/***********************************************************
make a lua script sleep for one cycle
***********************************************************/
void ScriptEnvironmentBase::WaitOneCycle(int scriptid)
{
	IceUtil::Mutex::Lock sync(m_mutex);
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
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorStraightWalkTo, this, ScriptId, ActorId, Position, false)));
	m_callbacks.push_back(calb);
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
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorRotate, this, ScriptId, ActorId, Angle, RotationSpeedPerSec, ManageAnimation, false)));
	m_callbacks.push_back(calb);
}

/***********************************************************/
//! used by lua to wait until an actor animation is finished
//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
/***********************************************************/
void ScriptEnvironmentBase::ActorAnimate(int ScriptId, long ActorId, bool AnimationMove)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorAnimate, this, ScriptId, ActorId, AnimationMove, false)));
	m_callbacks.push_back(calb);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor will move using animation speed
/***********************************************************/
void ScriptEnvironmentBase::ActorGoTo(int ScriptId, long ActorId, const LbaVec3 &Position, float Speed)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorGoTo, this, ScriptId, ActorId, Position, Speed, false)));
	m_callbacks.push_back(calb);
}


/***********************************************************/
//! used by lua to move an actor or player
//! the actor will move using animation speed
/***********************************************************/
void ScriptEnvironmentBase::ActorWaitForSignal(int ScriptId, long ActorId, int Signalnumber)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorWaitForSignal, this, ScriptId, ActorId, Signalnumber, false)));
	m_callbacks.push_back(calb);
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
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorRotateFromPoint, this, ScriptId, ActorId, Angle, Position, RotationSpeedPerSec, false)));
	m_callbacks.push_back(calb);
}


/***********************************************************/
//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
//! if ManageAnimation is true then the animation will be changed to suit the rotation
/***********************************************************/
void ScriptEnvironmentBase::ActorFollowWaypoint(int ScriptId, long ActorId, int waypointindex1, int waypointindex2)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorFollowWaypoint, this, ScriptId, ActorId, waypointindex1, waypointindex2, false)));
	m_callbacks.push_back(calb);
}







/***********************************************************/
//! used by lua to tell that the actor should be reserved for the script
/***********************************************************/
void ScriptEnvironmentBase::ReserveActor(int ScriptId, long ActorId)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalReserveActor, this, ScriptId, ActorId)));
	m_callbacks.push_back(calb);
}



/***********************************************************/
//! used by lua to get an actor Position
/***********************************************************/
void ScriptEnvironmentBase::GetActorPosition(int ScriptId, long ActorId)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseReturnYield<LbaVec3>(
		boost::bind(&ScriptEnvironmentBase::InternalGetActorPosition, this, ScriptId, ActorId), ScriptId));
	m_callbacks.push_back(calb);
}


/***********************************************************/
//! used by lua to get an actor Rotation
/***********************************************************/
void ScriptEnvironmentBase::GetActorRotation(int ScriptId, long ActorId)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseReturnYield<float>(
		boost::bind(&ScriptEnvironmentBase::InternalGetActorRotation, this, ScriptId, ActorId), ScriptId));
	m_callbacks.push_back(calb);
}


 
/***********************************************************/
//! used by lua to get an actor Rotation
/***********************************************************/
void ScriptEnvironmentBase::GetActorRotationQuat(int ScriptId, long ActorId)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseReturnYield<LbaQuaternion>(
		boost::bind(&ScriptEnvironmentBase::InternalGetActorRotationQuat, this, ScriptId, ActorId), ScriptId));
	m_callbacks.push_back(calb);
}


 
/***********************************************************/
//! return targeted player
/***********************************************************/
void ScriptEnvironmentBase::GetTargettedAttackPlayer(int ScriptId, long ActorId)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseReturnYield<long>(
		boost::bind(&ScriptEnvironmentBase::InternalGetTargettedAttackPlayer, this, ScriptId, ActorId), ScriptId));
	m_callbacks.push_back(calb);
}


/***********************************************************/
//! check if target is in range
/***********************************************************/
void ScriptEnvironmentBase::IsTargetInRange(int ScriptId, float MaxDistance, long ActorId)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseReturnYield<bool>(
		boost::bind(&ScriptEnvironmentBase::InternalIsTargetInRange, this, ScriptId, MaxDistance, ActorId), ScriptId));
	m_callbacks.push_back(calb);
}


 
/***********************************************************/
//! check if target is in rotation range
/***********************************************************/
void ScriptEnvironmentBase::GetTargetRotationDiff(int ScriptId, long ActorId)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseReturnYield<float>(
		boost::bind(&ScriptEnvironmentBase::InternalGetTargetRotationDiff, this, ScriptId, ActorId), ScriptId));
	m_callbacks.push_back(calb);
}


 
/***********************************************************/
//! get weapon distance
//! 1-> first contact weapon, 2 -> first distance weapon
//! 3-> second contact weapon, 4 -> second distance weapon
/***********************************************************/
void ScriptEnvironmentBase::GetNpcWeaponReachDistance(int ScriptId, long ActorId, int WeaponNumber)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseReturnYield<float>(
		boost::bind(&ScriptEnvironmentBase::InternalGetNpcWeaponReachDistance, this, ScriptId, ActorId, WeaponNumber), ScriptId));
	m_callbacks.push_back(calb);
}


 
/***********************************************************/
// check if actor can play animation
// ObjectType ==>
//! 1 -> npc object
//! 2 -> player object
//! 3 -> movable object
/***********************************************************/
void ScriptEnvironmentBase::CanPlayAnimation(int ScriptId, int ObjectType, long ObjectId, 
											 const std::string & anim)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseReturnYield<bool>(
		boost::bind(&ScriptEnvironmentBase::InternalCanPlayAnimation, this, ScriptId, ObjectType, ObjectId, anim), ScriptId));
	m_callbacks.push_back(calb);
}






/***********************************************************/
//! used by lua to update an actor animation
/***********************************************************/
void ScriptEnvironmentBase::UpdateActorAnimation(int ScriptId, long ActorId, 
												 const std::string & AnimationString)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalUpdateActorAnimation, this, ScriptId, ActorId, AnimationString)));
	m_callbacks.push_back(calb);
}



/***********************************************************/
//! used by lua to update an actor mode
/***********************************************************/
void ScriptEnvironmentBase::UpdateActorMode(int ScriptId, long ActorId, const std::string & Mode)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalUpdateActorMode, this, ScriptId, ActorId, Mode)));
	m_callbacks.push_back(calb);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor will change model
/***********************************************************/
void ScriptEnvironmentBase::UpdateActorModel(int ScriptId, long ActorId, const std::string & Name)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalUpdateActorModel, this, ScriptId, ActorId, Name)));
	m_callbacks.push_back(calb);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor will change outfit
/***********************************************************/
void ScriptEnvironmentBase::UpdateActorOutfit(int ScriptId, long ActorId, const std::string & Name)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalUpdateActorOutfit, this, ScriptId, ActorId, Name)));
	m_callbacks.push_back(calb);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor will change weapon
/***********************************************************/
void ScriptEnvironmentBase::UpdateActorWeapon(int ScriptId, long ActorId, const std::string & Name)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalUpdateActorWeapon, this, ScriptId, ActorId, Name)));
	m_callbacks.push_back(calb);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor will move using animation speed
/***********************************************************/
void ScriptEnvironmentBase::TeleportActorTo(int ScriptId, long ActorId, const LbaVec3 &Position)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalTeleportActorTo, this, ScriptId, ActorId, Position)));
	m_callbacks.push_back(calb);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor change rotation
/***********************************************************/
void ScriptEnvironmentBase::SetActorRotation(int ScriptId, long ActorId, float Angle)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalSetActorRotation, this, ScriptId, ActorId, Angle)));
	m_callbacks.push_back(calb);
}



/***********************************************************/
//! used by lua to move an actor or player
//! the actor show/hide
/***********************************************************/
void ScriptEnvironmentBase::ActorShowHide(int ScriptId, long ActorId, bool Show)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalActorShowHide, this, ScriptId, ActorId, Show)));
	m_callbacks.push_back(calb);
}




/***********************************************************/
//! used by lua to send signal to actor
/***********************************************************/
void ScriptEnvironmentBase::SendSignalToActor(int ScriptId, long ActorId, int Signalnumber)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalSendSignalToActor, this, ScriptId, ActorId, Signalnumber)));
	m_callbacks.push_back(calb);
}



/***********************************************************/
// AttachActor
// ObjectType ==>
//! 1 -> npc object
//! 2 -> player object
//! 3 -> movable object
/***********************************************************/
void ScriptEnvironmentBase::AttachActor(int ScriptId, long ActorId, int AttachedObjectType, 
										long AttachedObjectId)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalAttachActor, this, ScriptId, ActorId, 
															AttachedObjectType, AttachedObjectId)));
	m_callbacks.push_back(calb);
}



/***********************************************************/
// DettachActor
// ObjectType ==>
//! 1 -> npc object
//! 2 -> player object
//! 3 -> movable object
/***********************************************************/
void ScriptEnvironmentBase::DettachActor(int ScriptId, long ActorId, long AttachedObjectId)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalDettachActor, this, ScriptId, ActorId, 
															AttachedObjectId));
	m_callbacks.push_back(calb);
}



/***********************************************************/
//! npc use weapon
//! 1-> first contact weapon, 2 -> first distance weapon
//! 3-> second contact weapon, 4 -> second distance weapon
/***********************************************************/
void ScriptEnvironmentBase::UseWeapon(int ScriptId, long ActorId, int WeaponNumber)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalUseWeapon, this, ScriptId, ActorId, WeaponNumber));
	m_callbacks.push_back(calb);
}






/***********************************************************/
//! npc rotate to player
/***********************************************************/
void ScriptEnvironmentBase::RotateToTargettedPlayer(int ScriptId, long ActorId, 
													float ToleranceAngle, float speed)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalRotateToTargettedPlayer, this, ScriptId, ActorId, 
																		ToleranceAngle, speed));
	m_callbacks.push_back(calb);
}


/***********************************************************/
//! npc follow player
/***********************************************************/
void ScriptEnvironmentBase::FollowTargettedPlayer(int ScriptId, long ActorId, float DistanceStopFollow)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalFollowTargettedPlayer, this, ScriptId, ActorId, 
																		DistanceStopFollow));
	m_callbacks.push_back(calb);
}


/***********************************************************/
//! npc start use weapon - will not stop until changing state - only usefull for distance weapon
//! 1-> first contact weapon, 2 -> first distance weapon
//! 3-> second contact weapon, 4 -> second distance weapon
/***********************************************************/
void ScriptEnvironmentBase::StartUseWeapon(int ScriptId, long ActorId, int WeaponNumber)
{
	IceUtil::Mutex::Lock sync(m_mutex);

	boost::shared_ptr<ScriptCallbackBase> calb
		(new ScriptCallbackBaseNoYield(
		boost::bind(&ScriptEnvironmentBase::InternalStartUseWeapon, this, ScriptId, ActorId, 
																		WeaponNumber));
	m_callbacks.push_back(calb);
}
