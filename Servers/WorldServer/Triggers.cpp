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
void ZoneTrigger::CheckTriggerOnMove(int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerMoveInfo &info)
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
	if( (info.CurrentPos.X >= (_posX-_sizeX) && info.CurrentPos.X < (_posX+_sizeX)) &&
		(info.CurrentPos.Y >= (_posY)		 && info.CurrentPos.Y < (_posY+_sizeY)) &&
		(info.CurrentPos.Z >= (_posZ-_sizeZ) && info.CurrentPos.Z < (_posZ+_sizeZ)))
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