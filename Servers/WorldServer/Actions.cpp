#include "Actions.h"
#include "MapHandler.h"

/***********************************************************
constructor
***********************************************************/
Teleport::Teleport(const std::string & NewMap, const std::string & Spawning)
: _NewMap(NewMap), _Spawning(Spawning)
{

}

/***********************************************************
destructor
***********************************************************/	
Teleport::~Teleport(void)
{

}

/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void Teleport::Execute(MapHandler * owner, LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId)
{
	if(owner)
		owner->Teleport(OType, ObjectId, _NewMap, _Spawning);
}