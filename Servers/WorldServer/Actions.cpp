#include "Actions.h"
#include "MapHandler.h"

/***********************************************************
constructor
***********************************************************/
TeleportAction::TeleportAction(const std::string & NewMap, long SpawningId)
: _NewMap(NewMap), _SpawningId(SpawningId)
{

}

/***********************************************************
destructor
***********************************************************/	
TeleportAction::~TeleportAction(void)
{

}

/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void TeleportAction::Execute(MapHandler * owner, int ObjectType, Ice::Long ObjectId)
{
	if(owner)
		owner->Teleport(ObjectType, ObjectId, _NewMap, _SpawningId);
}