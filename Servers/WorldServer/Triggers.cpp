#include "Triggers.h"
#include "ScriptEnvironmentBase.h"
#include <fstream>
#include "SynchronizedTimeHandler.h"
#include "LogHandler.h"


#include <math.h>

/***********************************************************
constructor
***********************************************************/
ZoneTrigger::ZoneTrigger( const TriggerInfo & triggerinfo,
							float sizeX, float sizeY, float sizeZ, 
							bool AllowMultiActivation)
	: TriggerBase(triggerinfo),  _activateOnJump(true),
			_sizeX(sizeX/2), _sizeY(sizeY), _sizeZ(sizeZ/2),
			_AllowMultiActivation(AllowMultiActivation), _StayUpdateFrequency(-1)
{
}
	

/***********************************************************
destructor
***********************************************************/
ZoneTrigger::~ZoneTrigger(void)
{

}


/***********************************************************
check trigger on object move
***********************************************************/
void ZoneTrigger::ObjectMoved(DelayedExecutionHandler * delayedactH, int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerPosition &StartPosition,
										const LbaNet::PlayerPosition &EndPosition,
										const LbaNet::ModelState &state)
{
	if(ObjectType == 1 && !_triggerinfo.CheckNpcs)
		return;

	if(ObjectType == 2 && !_triggerinfo.CheckPlayers)
		return;

	if(ObjectType == 3 && !_triggerinfo.CheckMovableObjects)
		return;


	bool wasinside = _objectsinside.find(std::make_pair<int, Ice::Long>(ObjectType, ObjectId)) 
																		!= _objectsinside.end();


	//do a sweep test to check if object crossed trigger
	if(_activateOnJump || state != LbaNet::StJumping)
	{
		LbaNet::PlayerPosition collisionpos;
		if(SweepTest(StartPosition, EndPosition, collisionpos))
		{
			if(!wasinside)
			{
				if(ObjectType == 1)
				{
					std::cout<<"OK"<<std::endl;
				}

				Entered(ObjectType, ObjectId, (collisionpos.X-_posX), (collisionpos.Y-_posY), 
																		(collisionpos.Z-_posZ));
			}

			wasinside = true;
		}
	}


	// test if last point was inside - if not do a left signal
	{
		bool isinside = false;
		if( (EndPosition.X >= (_posX-_sizeX) && EndPosition.X < (_posX+_sizeX)) &&
			(EndPosition.Y >= (_posY)		  && EndPosition.Y < (_posY+_sizeY)) &&
			(EndPosition.Z >= (_posZ-_sizeZ) && EndPosition.Z < (_posZ+_sizeZ)))
		{
			isinside = true;
		}



		if(!isinside && wasinside)
		{

			std::stringstream strs;
			strs<<"Trigger - object left: "<<ObjectType<<" "<<ObjectId;
			LogHandler::getInstance()->LogToFile(strs.str(), GetId());

			Left(ObjectType, ObjectId);
		}
	}
}




/***********************************************************
check trigger on object leave map
***********************************************************/
void ZoneTrigger::ObjectLeaveMap(DelayedExecutionHandler * delayedactH, int ObjectType, Ice::Long ObjectId)
{
	if(_objectsinside.find(std::make_pair<int, Ice::Long>(ObjectType, ObjectId)) != _objectsinside.end())
	{
		Left(ObjectType, ObjectId);
		std::stringstream strs;
		strs<<"Trigger - object left map: "<<ObjectType<<" "<<ObjectId;
		LogHandler::getInstance()->LogToFile(strs.str(), GetId());
	}
}


/***********************************************************
//! check trigger on each fram
//! warning - this can reduce performance!
***********************************************************/
void ZoneTrigger::NewFrame(DelayedExecutionHandler * delayedactH, double tnow, float tdiff)
{
	if(_action3 && _StayUpdateFrequency > 0)
	{
		std::map<std::pair<int, Ice::Long>, double >::iterator it =	_objectsinside.begin();
		std::map<std::pair<int, Ice::Long>, double >::iterator end = _objectsinside.end();
		for(; it != end; ++it)
		{
			if((tnow - it->second) >= (_StayUpdateFrequency*1000))
			{
				it->second = tnow;
				_action3->Execute(_owner, it->first.first, it->first.second, NULL);
			}
		}
	}
}


/***********************************************************
when object entered
***********************************************************/
void ZoneTrigger::Entered(int ObjectType, Ice::Long ObjectId,
							float offsetX, float offsetY, float offsetZ)
{
	_objectsinside[std::make_pair<int, Ice::Long>(ObjectType, ObjectId)] = SynchronizedTimeHandler::GetCurrentTimeDouble();


	std::stringstream strs;
	strs<<"Trigger - object entered: "<<ObjectType<<" "<<ObjectId;
	LogHandler::getInstance()->LogToFile(strs.str(), GetId());



	if(_AllowMultiActivation || _objectsinside.size() == 1)
	{
		if(_action1)
		{
			OffsetArgument arg(offsetX, offsetY, offsetZ);
			_action1->Execute(_owner, ObjectType, ObjectId, &arg);
		}
	}
}


/***********************************************************
when object left
***********************************************************/
void ZoneTrigger::Left(int ObjectType, Ice::Long ObjectId)
{
	_objectsinside.erase(std::make_pair<int, Ice::Long>(ObjectType, ObjectId));

	if(_AllowMultiActivation || _objectsinside.size() == 0)
	{
		if(_action2)
			_action2->Execute(_owner, ObjectType, ObjectId, 0);
	}
}



/***********************************************************
perform a sweep test
***********************************************************/
bool ZoneTrigger::SweepTest(	const LbaNet::PlayerPosition &StartPosition,
								const LbaNet::PlayerPosition &EndPosition,
								LbaNet::PlayerPosition &CollisionPoint)
{
	Box zone;
	zone.min.x = (_posX-_sizeX);  
	zone.min.y = _posY;  
	zone.min.z = (_posZ-_sizeZ); 

	zone.max.x = (_posX+_sizeX);  
	zone.max.y = (_posY+_sizeY);  
	zone.max.z = (_posZ+_sizeZ);  


	float st, et, fst = 0, fet = 1;  
	float const *bmin = &zone.min.x;
	float const *bmax = &zone.max.x;
	float const *si = &StartPosition.X;  
	float const *ei = &EndPosition.X;  

	for (int i = 0; i < 3; i++) 
	{  
		if (*si < *ei) 
		{  
			if (*si > *bmax || *ei < *bmin)  
				return false;  

			float di = *ei - *si;  
			st = (*si < *bmin)? (*bmin - *si) / di: 0;  
			et = (*ei > *bmax)? (*bmax - *si) / di: 1;  
		}  
		else 
		{  
			if (*ei > *bmax || *si < *bmin)  
				return false;  

			float di = *ei - *si;  
			st = (*si > *bmax)? (*bmax - *si) / di: 0;  
			et = (*ei < *bmin)? (*bmin - *si) / di: 1;  
		}  

		if (st > fst) fst = st;  
			if (et < fet) fet = et;  
				if (fet < fst)  
					return false;  

		bmin++; bmax++;  
		si++; ei++;  
	}  

	CollisionPoint.X = StartPosition.X + ((EndPosition.X-StartPosition.X)*fst);
	CollisionPoint.Y = StartPosition.Y + ((EndPosition.Y-StartPosition.Y)*fst);
	CollisionPoint.Z = StartPosition.Z + ((EndPosition.Z-StartPosition.Z)*fst);
	return true;  
}










/***********************************************************
get object to display for editor
***********************************************************/
ActorObjectInfo ZoneTrigger::GetDisplayObject()
{
	ActorObjectInfo ainfo(GetId() + 2000000);
	ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderBox;
	ainfo.DisplayDesc.ColorR = 1.0f;
	ainfo.DisplayDesc.ColorG = 0.2f;
	ainfo.DisplayDesc.ColorB = 0.2f;
	ainfo.DisplayDesc.ColorA = 0.5f;
	ainfo.PhysicDesc.TypeShape = LbaNet::NoShape;
	ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
	ainfo.PhysicDesc.Pos.X = _posX;
	ainfo.PhysicDesc.Pos.Y = _posY;
	ainfo.PhysicDesc.Pos.Z = _posZ;
	ainfo.PhysicDesc.Pos.Rotation = 0;
	ainfo.DisplayDesc.ScaleX = _sizeX*2;
	ainfo.DisplayDesc.ScaleY = _sizeY;
	ainfo.DisplayDesc.ScaleZ = _sizeZ*2;

	std::stringstream strs;
	strs << "ZoneTrigger-"<<GetId()<<": " << GetName();
	ainfo.ExtraInfo.Name = strs.str();
	ainfo.ExtraInfo.NameColorR = 1.0f;
	ainfo.ExtraInfo.NameColorG = 0.2f;
	ainfo.ExtraInfo.NameColorB = 0.2f;
	ainfo.LifeInfo.Display = false;
	return ainfo;
}




/***********************************************************
save trigger to lua file
***********************************************************/
void ZoneTrigger::SaveToLuaFile(std::ostream & file, std::string forcedid)
{
	std::string namesp = GetName();

	std::stringstream objidstrs;
	objidstrs<<GetId();

	std::string objidstr = objidstrs.str();
	if(forcedid != "")
	{
		objidstr = forcedid;
		namesp = "trigger" + forcedid;
	}

	file<<"\tlmap.Trigger_info = TriggerInfo("<<objidstr<<", \""<<namesp<<"\", "<<
			(CheckPlayer()?"true":"false")<<", "<<(CheckNpcs()?"true":"false")<<", "<<(CheckMovableObjects()?"true":"false")<<")"<<std::endl;
	file<<"\tlmap.Trigger = ZoneTrigger(lmap.Trigger_info, "
		<<(_sizeX*2)<<", "<<_sizeY<<", "<<(_sizeZ*2)<<", "<<(_AllowMultiActivation?"true":"false")<<")"<<std::endl;
	file<<"\tlmap.Trigger:SetPosition("<<GetPosX()<<", "<<GetPosY()<<", "<<GetPosZ()<<")"<<std::endl;
	file<<"\tlmap.Trigger:SetStayUpdateFrequency("<<_StayUpdateFrequency<<")"<<std::endl;
	file<<"\tlmap.Trigger:SetActivateOnJump("<<(_activateOnJump?"true":"false")<<")"<<std::endl;

	if(_action1)
	{
		std::stringstream aname;
		aname<<"lmap.Trigger_act1";
		_action1->SaveToLuaFile(file, aname.str());

		file<<"\tlmap.Trigger:SetAction1("<<aname.str()<<")"<<std::endl;
	}

	if(_action2)
	{
		std::stringstream aname;
		aname<<"lmap.Trigger_act2";
		_action2->SaveToLuaFile(file, aname.str());

		file<<"\tlmap.Trigger:SetAction2("<<aname.str()<<")"<<std::endl;
	}

	if(_action3)
	{
		std::stringstream aname;
		aname<<"lmap.Trigger_act3";
		_action3->SaveToLuaFile(file, aname.str());

		file<<"\tlmap.Trigger:SetAction3("<<aname.str()<<")"<<std::endl;
	}

	file<<"\tenvironment:AddTrigger(lmap.Trigger)"<<std::endl<<std::endl;
}




/***********************************************************
constructor
***********************************************************/
ActivationTrigger::ActivationTrigger( const TriggerInfo & triggerinfo,
										float MaxDistance, 
										const std::string & AcceptedMode1, 
										const std::string & AcceptedMode2)
	: TriggerBase(triggerinfo),
		_MaxSquaredDistance(MaxDistance*MaxDistance), _AcceptedMode1(AcceptedMode1),
		_AcceptedMode2(AcceptedMode2), _PlayAnimation(false)
{

}



/***********************************************************
destructor
***********************************************************/
ActivationTrigger::~ActivationTrigger(void)
{

}

/***********************************************************
get distance
***********************************************************/
float ActivationTrigger::GetDistance()
{
	return sqrt(_MaxSquaredDistance);
}

/***********************************************************
set distance
***********************************************************/
void ActivationTrigger::SetDistance(float distance)
{
	_MaxSquaredDistance = (distance*distance);
}



/***********************************************************
//! check trigger on object action
// ObjectType ==>
//! 1 -> npc object
//! 2 -> player object
//! 3 -> movable object
// ObjectMode give the mode the object was when performing the action
***********************************************************/
void ActivationTrigger::ObjectAction(DelayedExecutionHandler * delayedactH, 
									 int ObjectType, Ice::Long ObjectId,
									const LbaNet::PlayerPosition &info,
									const std::string &ObjectMode)
{
	if(ObjectType == 1 && !_triggerinfo.CheckNpcs)
		return;

	if(ObjectType == 2 && !_triggerinfo.CheckPlayers)
		return;

	if(ObjectType == 3 && !_triggerinfo.CheckMovableObjects)
		return;

	if(ObjectMode != _AcceptedMode1 && ObjectMode != _AcceptedMode2)
		return;

	float diffX = (info.X - _posX);
	float diffY = (info.Y - _posY);
	float diffZ = (info.Z - _posZ);

	float distance = (diffX*diffX) + (diffY*diffY) + (diffZ*diffZ);
	if(distance <= _MaxSquaredDistance)
	{
		LbaVec3 lvec(-diffX, -diffY, -diffZ);
		float angle = LbaQuaternion::GetAngleFromVector(lvec);
		float angle1a = (angle - 50);
		float angle1b = (angle - 50);

		float angle2a = (angle + 50);
		float angle2b = (angle + 50);

		if(angle1a < 0)
		{
			angle1a += 360;
			angle2a += 360;
			angle1b = 0;		
		}

		if(angle2b > 360)
		{
			angle1b -= 360;
			angle2b -= 360;
			angle2a = 360;
		}

		if(	((info.Rotation > angle1a) && (info.Rotation < angle2a)) ||
			((info.Rotation > angle1b) && (info.Rotation < angle2b)) )
		{
			if(_action1)
			{
				if(_PlayAnimation && ObjectType == 2)
				{
					DelayedAction daction;
					daction.action = _action1;
					daction.ClientId = ObjectId;
					daction.args = NULL;
					delayedactH->DelayActionAfterPlayerChangeState(daction, LbaNet::StActivateSwitch);
				}
				else
				{
					_action1->Execute(_owner, ObjectType, ObjectId, 0);
				}
			}
		}
	}
}



/***********************************************************
get object to display for editor
***********************************************************/
ActorObjectInfo ActivationTrigger::GetDisplayObject()
{
	ActorObjectInfo ainfo(GetId() + 2000000);
	ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderCapsule;
	ainfo.DisplayDesc.ColorR = 1.0f;
	ainfo.DisplayDesc.ColorG = 0.2f;
	ainfo.DisplayDesc.ColorB = 0.2f;
	ainfo.DisplayDesc.ColorA = 0.5f;

	ainfo.PhysicDesc.TypeShape = LbaNet::NoShape;
	ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
	ainfo.PhysicDesc.Pos.X = _posX;
	ainfo.PhysicDesc.Pos.Y = _posY;
	ainfo.PhysicDesc.Pos.Z = _posZ;
	ainfo.PhysicDesc.Pos.Rotation = 0;
	ainfo.DisplayDesc.ScaleX = GetDistance();
	ainfo.DisplayDesc.ScaleY = 0;


	std::stringstream strs;
	strs << "ActivationTrigger-"<<GetId()<<": " << GetName();
	ainfo.ExtraInfo.Name = strs.str();
	ainfo.ExtraInfo.NameColorR = 1.0f;
	ainfo.ExtraInfo.NameColorG = 0.2f;
	ainfo.ExtraInfo.NameColorB = 0.2f;
	ainfo.LifeInfo.Display = false;
	return ainfo;
}




/***********************************************************
save trigger to lua file
***********************************************************/
void ActivationTrigger::SaveToLuaFile(std::ostream & file, std::string forcedid)
{
	std::string namesp = GetName();

	std::stringstream objidstrs;
	objidstrs<<GetId();

	std::string objidstr = objidstrs.str();
	if(forcedid != "")
	{
		objidstr = forcedid;
		namesp = "trigger" + forcedid;
	}

	file<<"\tlmap.Trigger_info = TriggerInfo("<<objidstr<<", \""<<namesp<<"\", "<<
		(CheckPlayer()?"true":"false")<<", "<<(CheckNpcs()?"true":"false")<<", "<<(CheckMovableObjects()?"true":"false")<<")"<<std::endl;
	file<<"\tlmap.Trigger = ActivationTrigger(lmap.Trigger_info, "
		<<GetDistance()<<", \""<<_AcceptedMode1<<"\", \""<<_AcceptedMode2<<"\")"<<std::endl;
	file<<"\tlmap.Trigger:SetPosition("<<GetPosX()<<", "<<GetPosY()<<", "<<GetPosZ()<<")"<<std::endl;

	if(_action1)
	{
		std::stringstream aname;
		aname<<"lmap.Trigger_act1";
		_action1->SaveToLuaFile(file, aname.str());

		file<<"\tlmap.Trigger:SetAction1("<<aname.str()<<")"<<std::endl;
	}

	if(_action2)
	{
		std::stringstream aname;
		aname<<"lmap.Trigger_act2";
		_action2->SaveToLuaFile(file, aname.str());

		file<<"\tlmap.Trigger:SetAction2("<<aname.str()<<")"<<std::endl;
	}

	if(_action3)
	{
		std::stringstream aname;
		aname<<"lmap.Trigger_act3";
		_action3->SaveToLuaFile(file, aname.str());

		file<<"\tlmap.Trigger:SetAction3("<<aname.str()<<")"<<std::endl;
	}

	file<<"\tlmap.Trigger:SetPlayAnimation("<<(_PlayAnimation?"true":"false")<<")"<<std::endl;
	

	file<<"\tenvironment:AddTrigger(lmap.Trigger)"<<std::endl<<std::endl;
}






/***********************************************************
constructor
***********************************************************/
ZoneActionTrigger::ZoneActionTrigger( const TriggerInfo & triggerinfo,
									float sizeX, float sizeY, float sizeZ, 
										const std::string & AcceptedMode1, 
										const std::string & AcceptedMode2)
	: TriggerBase(triggerinfo),
		_sizeX(sizeX/2), _sizeY(sizeY), _sizeZ(sizeZ/2),
		_AcceptedMode1(AcceptedMode1),	_AcceptedMode2(AcceptedMode2),
		_PlayAnimation(false)
{

}


/***********************************************************
destructor
***********************************************************/
ZoneActionTrigger::~ZoneActionTrigger(void)
{

}


/***********************************************************
//! check trigger on object action
// ObjectType ==>
//! 1 -> npc object
//! 2 -> player object
//! 3 -> movable object
// ObjectMode give the mode the object was when performing the action
***********************************************************/
void ZoneActionTrigger::ObjectAction(DelayedExecutionHandler * delayedactH, 
									 int ObjectType, Ice::Long ObjectId,
									const LbaNet::PlayerPosition &info,
									const std::string &ObjectMode)
{
	if(ObjectType == 1 && !_triggerinfo.CheckNpcs)
		return;

	if(ObjectType == 2 && !_triggerinfo.CheckPlayers)
		return;

	if(ObjectType == 3 && !_triggerinfo.CheckMovableObjects)
		return;

	if(ObjectMode != _AcceptedMode1 && ObjectMode != _AcceptedMode2)
		return;


	if( (info.X >= (_posX-_sizeX) && info.X < (_posX+_sizeX)) &&
		(info.Y >= (_posY)		  && info.Y < (_posY+_sizeY)) &&
		(info.Z >= (_posZ-_sizeZ) && info.Z < (_posZ+_sizeZ)))
	{
		if(_action1)
		{
			if(_PlayAnimation && ObjectType == 2)
			{
				DelayedAction daction;
				daction.action = _action1;
				daction.ClientId = ObjectId;
				daction.args = NULL;
				delayedactH->DelayActionAfterPlayerChangeState(daction, LbaNet::StActivateGroundSwitch);
			}
			else
			{
				_action1->Execute(_owner, ObjectType, ObjectId, 0);
			}
		}
	}
}



/***********************************************************
get object to display for editor
***********************************************************/
ActorObjectInfo ZoneActionTrigger::GetDisplayObject()
{
	ActorObjectInfo ainfo(GetId() + 2000000);
	ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderBox;
	ainfo.DisplayDesc.ColorR = 1.0f;
	ainfo.DisplayDesc.ColorG = 0.2f;
	ainfo.DisplayDesc.ColorB = 0.2f;
	ainfo.DisplayDesc.ColorA = 0.5f;
	ainfo.PhysicDesc.TypeShape = LbaNet::NoShape;
	ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
	ainfo.PhysicDesc.Pos.X = _posX;
	ainfo.PhysicDesc.Pos.Y = _posY;
	ainfo.PhysicDesc.Pos.Z = _posZ;
	ainfo.PhysicDesc.Pos.Rotation = 0;
	ainfo.DisplayDesc.ScaleX = _sizeX*2;
	ainfo.DisplayDesc.ScaleY = _sizeY;
	ainfo.DisplayDesc.ScaleZ = _sizeZ*2;

	std::stringstream strs;
	strs << "ZoneActionTrigger-"<<GetId()<<": " << GetName();
	ainfo.ExtraInfo.Name = strs.str();
	ainfo.ExtraInfo.NameColorR = 1.0f;
	ainfo.ExtraInfo.NameColorG = 0.2f;
	ainfo.ExtraInfo.NameColorB = 0.2f;
	ainfo.LifeInfo.Display = false;
	return ainfo;
}




/***********************************************************
save trigger to lua file
***********************************************************/
void ZoneActionTrigger::SaveToLuaFile(std::ostream & file, std::string forcedid)
{
	std::string namesp = GetName();

	std::stringstream objidstrs;
	objidstrs<<GetId();

	std::string objidstr = objidstrs.str();
	if(forcedid != "")
	{
		objidstr = forcedid;
		namesp = "trigger" + forcedid;
	}

	file<<"\tlmap.Trigger_info = TriggerInfo("<<objidstr<<", \""<<namesp<<"\", "<<
		(CheckPlayer()?"true":"false")<<", "<<(CheckNpcs()?"true":"false")<<", "<<(CheckMovableObjects()?"true":"false")<<")"<<std::endl;
	file<<"\tlmap.Trigger = ZoneActionTrigger(lmap.Trigger_info, "
		<<(_sizeX*2)<<", "<<_sizeY<<", "<<(_sizeZ*2)<<", \""<<_AcceptedMode1<<"\", \""<<_AcceptedMode2<<"\")"<<std::endl;
	file<<"\tlmap.Trigger:SetPosition("<<GetPosX()<<", "<<GetPosY()<<", "<<GetPosZ()<<")"<<std::endl;

	if(_action1)
	{
		std::stringstream aname;
		aname<<"lmap.Trigger_act1";
		_action1->SaveToLuaFile(file, aname.str());

		file<<"\tlmap.Trigger:SetAction1("<<aname.str()<<")"<<std::endl;
	}

	if(_action2)
	{
		std::stringstream aname;
		aname<<"lmap.Trigger_act2";
		_action2->SaveToLuaFile(file, aname.str());

		file<<"\tlmap.Trigger:SetAction2("<<aname.str()<<")"<<std::endl;
	}

	if(_action3)
	{
		std::stringstream aname;
		aname<<"lmap.Trigger_act3";
		_action3->SaveToLuaFile(file, aname.str());

		file<<"\tlmap.Trigger:SetAction3("<<aname.str()<<")"<<std::endl;
	}

	file<<"\tlmap.Trigger:SetPlayAnimation("<<(_PlayAnimation?"true":"false")<<")"<<std::endl;

	file<<"\tenvironment:AddTrigger(lmap.Trigger)"<<std::endl<<std::endl;
}







/***********************************************************
constructor
***********************************************************/
TimerTrigger::TimerTrigger( const TriggerInfo & triggerinfo,
									long TimeInMillisecond)
	: TriggerBase(triggerinfo),
		_TimeInMillisecond(TimeInMillisecond), _lasttime(-1)
{

}


/***********************************************************
destructor
***********************************************************/
TimerTrigger::~TimerTrigger(void)
{

}


/***********************************************************
//! check trigger on object action
// ObjectType ==>
//! 1 -> npc object
//! 2 -> player object
//! 3 -> movable object
// ObjectMode give the mode the object was when performing the action
***********************************************************/
void TimerTrigger::NewFrame(DelayedExecutionHandler * delayedactH, double tnow, float tdiff)
{
	if(_lasttime > 0)
	{
		// if timer time elapsed
		if((tnow - _lasttime) > _TimeInMillisecond)
		{
			// reset timer
			_lasttime = tnow;

			// execute action
			if(_action1)
				_action1->Execute(_owner, 0, 0, 0);
		}
	}
	else
		_lasttime = tnow;
}

/***********************************************************
save trigger to lua file
***********************************************************/
void TimerTrigger::SaveToLuaFile(std::ostream & file, std::string forcedid)
{
	std::string namesp = GetName();

	std::stringstream objidstrs;
	objidstrs<<GetId();

	std::string objidstr = objidstrs.str();
	if(forcedid != "")
	{
		objidstr = forcedid;
		namesp = "trigger" + forcedid;
	}

	file<<"\tlmap.Trigger_info = TriggerInfo("<<objidstr<<", \""<<namesp<<"\", "<<
		(CheckPlayer()?"true":"false")<<", "<<(CheckNpcs()?"true":"false")<<", "<<(CheckMovableObjects()?"true":"false")<<")"<<std::endl;
	file<<"\tlmap.Trigger = TimerTrigger(lmap.Trigger_info, "
		<<_TimeInMillisecond<<"\")"<<std::endl;
	file<<"\tlmap.Trigger:SetAction1("<<GetAction1()<<")"<<std::endl;
	file<<"\tlmap.Trigger:SetAction2("<<GetAction2()<<")"<<std::endl;
	file<<"\tlmap.Trigger:SetAction3("<<GetAction3()<<")"<<std::endl;
	file<<"\tenvironment:AddTrigger(lmap.Trigger)"<<std::endl<<std::endl;
}


