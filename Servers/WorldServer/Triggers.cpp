#include "Triggers.h"



/***********************************************************
constructor
***********************************************************/
ZoneTrigger::ZoneTrigger( long id, bool CheckPlayers, bool CheckNpcs, bool CheckMovableObjects,
							float sizeX, float sizeY, float sizeZ, 
							bool AllowMultiActivation)
	: TriggerBase(id, CheckPlayers, CheckNpcs, CheckMovableObjects), 
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
										const LbaNet::PlayerPosition &info)
{
	if(ObjectType == 1 && !_CheckNpcs)
		return;

	if(ObjectType == 2 && !_CheckPlayers)
		return;

	if(ObjectType == 3 && !_CheckMovableObjects)
		return;


	bool wasinside = _objectsinside.find(std::make_pair<int, Ice::Long>(ObjectType, ObjectId)) 
																		!= _objectsinside.end();

	bool isinside = false;
	if( (info.X >= (_posX-_sizeX) && info.X < (_posX+_sizeX)) &&
		(info.Y >= (_posY)		  && info.Y < (_posY+_sizeY)) &&
		(info.Z >= (_posZ-_sizeZ) && info.Z < (_posZ+_sizeZ)))
	{
		isinside = true;
	}

	if(isinside && !wasinside)
		Entered(ObjectType, ObjectId);

	if(!isinside && wasinside)
		Left(ObjectType, ObjectId);
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
void ZoneTrigger::Entered(int ObjectType, Ice::Long ObjectId)
{
	_objectsinside.insert(std::make_pair<int, Ice::Long>(ObjectType, ObjectId));

	if(_AllowMultiActivation || _objectsinside.size() == 1)
		if(_actionOnEnter)
			_actionOnEnter->Execute(_map, ObjectType, ObjectId);
}


/***********************************************************
when object left
***********************************************************/
void ZoneTrigger::Left(int ObjectType, Ice::Long ObjectId)
{
	_objectsinside.erase(std::make_pair<int, Ice::Long>(ObjectType, ObjectId));

	if(_AllowMultiActivation || _objectsinside.size() == 0)
		if(_actionOnLeave)
			_actionOnLeave->Execute(_map, ObjectType, ObjectId);
}



/***********************************************************
constructor
***********************************************************/
ActivationTrigger::ActivationTrigger( long id, bool CheckPlayers, bool CheckNpcs, bool CheckMovableObjects,
										float MaxSquaredDistance, 
										const std::string & AcceptedMode1, 
										const std::string & AcceptedMode2)
	: TriggerBase(id, CheckPlayers, CheckNpcs, CheckMovableObjects),
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
	if(ObjectType == 1 && !_CheckNpcs)
		return;

	if(ObjectType == 2 && !_CheckPlayers)
		return;

	if(ObjectType == 3 && !_CheckMovableObjects)
		return;

	if(ObjectMode != _AcceptedMode1 && ObjectMode != _AcceptedMode2)
		return;

	float diffX = (info.X - _posX);
	float diffY = (info.Y - _posY);
	float diffZ = (info.Z - _posZ);

	float distance = (diffX*diffX) + (diffY*diffY) + (diffZ*diffZ);
	if(distance <= _MaxSquaredDistance)
		_action->Execute(_map, ObjectType, ObjectId);
}



/***********************************************************
constructor
***********************************************************/
ZoneActionTrigger::ZoneActionTrigger( long id, bool CheckPlayers, bool CheckNpcs, bool CheckMovableObjects,
					float sizeX, float sizeY, float sizeZ, 
						const std::string & AcceptedMode1, 
						const std::string & AcceptedMode2)
	: TriggerBase(id, CheckPlayers, CheckNpcs, CheckMovableObjects),
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
	if(ObjectType == 1 && !_CheckNpcs)
		return;

	if(ObjectType == 2 && !_CheckPlayers)
		return;

	if(ObjectType == 3 && !_CheckMovableObjects)
		return;

	if(ObjectMode != _AcceptedMode1 && ObjectMode != _AcceptedMode2)
		return;


	if( (info.X >= (_posX-_sizeX) && info.X < (_posX+_sizeX)) &&
		(info.Y >= (_posY)		  && info.Y < (_posY+_sizeY)) &&
		(info.Z >= (_posZ-_sizeZ) && info.Z < (_posZ+_sizeZ)))
	{
		_action->Execute(_map, ObjectType, ObjectId);
	}
}