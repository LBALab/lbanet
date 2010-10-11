#include "Triggers.h"



/***********************************************************
constructor
***********************************************************/
ZoneTrigger::ZoneTrigger(	float sizeX, float sizeY, float sizeZ, 
							bool CheckPlayers, bool CheckNpcs, bool CheckMovableObjects,
							bool AllowMultiActivation)
	: _sizeX(sizeX/2), _sizeY(sizeY), _sizeZ(sizeZ/2), _CheckPlayers(CheckPlayers),
			_CheckNpcs(CheckNpcs), _CheckMovableObjects(CheckMovableObjects), 
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
void ZoneTrigger::CheckTriggerOnMove(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId,
										const LbaNet::PlayerMoveInfo &info)
{
	if(OType == LbaNet::StaticObject || LbaNet::GhostObject)
		return;

	if(OType == LbaNet::CpuObject && !_CheckNpcs)
		return;

	if(OType == LbaNet::MovableObject && !_CheckMovableObjects)
		return;

	if(OType == LbaNet::PlayerObject && !_CheckPlayers)
		return;

	bool wasinside = _objectsinside.find(std::make_pair<LbaNet::ObjectTypeEnum, Ice::Long>(OType, ObjectId)) 
																		!= _objectsinside.end();

	bool isinside = false;
	if( (info.CurrentPos.X >= (_posX-_sizeX) && info.CurrentPos.X < (_posX+_sizeX)) &&
		(info.CurrentPos.Y >= (_posY)		 && info.CurrentPos.Y < (_posY+_sizeY)) &&
		(info.CurrentPos.Z >= (_posZ-_sizeZ) && info.CurrentPos.Z < (_posZ+_sizeZ)))
	{
		isinside = true;
	}

	if(isinside && !wasinside)
		Entered(OType, ObjectId);

	if(!isinside && wasinside)
		Left(OType, ObjectId);
}




/***********************************************************
check trigger on object leave map
***********************************************************/
void ZoneTrigger::ObjectLeaveMap(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId)
{
	if(_objectsinside.find(std::make_pair<LbaNet::ObjectTypeEnum, Ice::Long>(OType, ObjectId)) 
																		!= _objectsinside.end())
		Left(OType, ObjectId);
}


/***********************************************************
when object entered
***********************************************************/
void ZoneTrigger::Entered(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId)
{
	_objectsinside.insert(std::make_pair<LbaNet::ObjectTypeEnum, Ice::Long>(OType, ObjectId));

	if(_AllowMultiActivation || _objectsinside.size() == 1)
		if(_actionOnEnter)
			_actionOnEnter->Execute(_map, OType, ObjectId);
}


/***********************************************************
when object left
***********************************************************/
void ZoneTrigger::Left(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId)
{
	_objectsinside.erase(std::make_pair<LbaNet::ObjectTypeEnum, Ice::Long>(OType, ObjectId));

	if(_AllowMultiActivation || _objectsinside.size() == 0)
		if(_actionOnLeave)
			_actionOnLeave->Execute(_map, OType, ObjectId);
}