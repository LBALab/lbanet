#include "Triggers.h"
#include "ScriptEnvironmentBase.h"
#include <fstream>

/***********************************************************
constructor
***********************************************************/
ZoneTrigger::ZoneTrigger( const TriggerInfo & triggerinfo,
							float sizeX, float sizeY, float sizeZ, 
							bool AllowMultiActivation)
	: TriggerBase(triggerinfo), 
			_sizeX(sizeX/2), _sizeY(sizeY), _sizeZ(sizeZ/2),
			_AllowMultiActivation(AllowMultiActivation)
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
void ZoneTrigger::ObjectMoved(int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerPosition &StartPosition,
										const LbaNet::PlayerPosition &EndPosition)
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
	{
		LbaNet::PlayerPosition collisionpos;
		if(SweepTest(StartPosition, EndPosition, collisionpos))
		{
			if(!wasinside)
				Entered(ObjectType, ObjectId, (collisionpos.X-_posX), (collisionpos.Y-_posY), 
																		(collisionpos.Z-_posZ));	

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
			Left(ObjectType, ObjectId);
	}
}




/***********************************************************
check trigger on object leave map
***********************************************************/
void ZoneTrigger::ObjectLeaveMap(int ObjectType, Ice::Long ObjectId)
{
	if(_objectsinside.find(std::make_pair<int, Ice::Long>(ObjectType, ObjectId)) 
																		!= _objectsinside.end())
		Left(ObjectType, ObjectId);
}


/***********************************************************
when object entered
***********************************************************/
void ZoneTrigger::Entered(int ObjectType, Ice::Long ObjectId,
							float offsetX, float offsetY, float offsetZ)
{
	_objectsinside.insert(std::make_pair<int, Ice::Long>(ObjectType, ObjectId));

	if(_AllowMultiActivation || _objectsinside.size() == 1)
	{
		boost::shared_ptr<ActionBase> act = _owner->GetAction(_actionid1);
		if(act)
		{
			OffsetArgument arg(offsetX, offsetY, offsetZ);
			act->Execute(_owner, ObjectType, ObjectId, &arg);
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
		boost::shared_ptr<ActionBase> act = _owner->GetAction(_actionid2);
		if(act)
			act->Execute(_owner, ObjectType, ObjectId, 0);
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
	ainfo.PhysicDesc.SizeX = _sizeX*2;
	ainfo.PhysicDesc.SizeY = _sizeY;
	ainfo.PhysicDesc.SizeZ = _sizeZ*2;

	std::stringstream strs;
	strs << "ZoneTrigger-"<<GetId()<<": " << GetName();
	ainfo.ExtraInfo.Name = strs.str();
	ainfo.ExtraInfo.NameColorR = 1.0f;
	ainfo.ExtraInfo.NameColorG = 0.2f;
	ainfo.ExtraInfo.NameColorB = 0.2f;
	return ainfo;
}




/***********************************************************
save trigger to lua file
***********************************************************/
void ZoneTrigger::SaveToLuaFile(std::ofstream & file)
{
	file<<"\tTrigger_"<<GetId()<<"_info = TriggerInfo("<<GetId()<<", \""<<GetName()<<"\", "<<
			(CheckPlayer()?"true":"false")<<", "<<(CheckNpcs()?"true":"false")<<", "<<(CheckMovableObjects()?"true":"false")<<")"<<std::endl;
	file<<"\tTrigger_"<<GetId()<<" = ZoneTrigger(Trigger_"<<GetId()<<"_info, "
		<<(_sizeX*2)<<", "<<_sizeY<<", "<<(_sizeZ*2)<<", "<<(_AllowMultiActivation?"true":"false")<<")"<<std::endl;
	file<<"\tTrigger_"<<GetId()<<":SetPosition("<<GetPosX()<<", "<<GetPosY()<<", "<<GetPosZ()<<")"<<std::endl;
	file<<"\tTrigger_"<<GetId()<<":SetAction1("<<GetAction1()<<")"<<std::endl;
	file<<"\tTrigger_"<<GetId()<<":SetAction2("<<GetAction2()<<")"<<std::endl;
	file<<"\tTrigger_"<<GetId()<<":SetAction3("<<GetAction3()<<")"<<std::endl;
	file<<"\tenvironment:AddTrigger(Trigger_"<<GetId()<<")"<<std::endl<<std::endl;
}




/***********************************************************
constructor
***********************************************************/
ActivationTrigger::ActivationTrigger( const TriggerInfo & triggerinfo,
										float MaxSquaredDistance, 
										const std::string & AcceptedMode1, 
										const std::string & AcceptedMode2)
	: TriggerBase(triggerinfo),
		_MaxSquaredDistance(MaxSquaredDistance), _AcceptedMode1(AcceptedMode1),
		_AcceptedMode2(AcceptedMode2)
{

}



/***********************************************************
destructor
***********************************************************/
ActivationTrigger::~ActivationTrigger(void)
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
void ActivationTrigger::ObjectAction(int ObjectType, Ice::Long ObjectId,
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
		boost::shared_ptr<ActionBase> act = _owner->GetAction(_actionid1);
		if(act)
			act->Execute(_owner, ObjectType, ObjectId, 0);
	}
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
		_AcceptedMode1(AcceptedMode1),	_AcceptedMode2(AcceptedMode2)
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
void ZoneActionTrigger::ObjectAction(int ObjectType, Ice::Long ObjectId,
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
		boost::shared_ptr<ActionBase> act = _owner->GetAction(_actionid1);
		if(act)
			act->Execute(_owner, ObjectType, ObjectId, 0);
	}
}

