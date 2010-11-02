#include "Actions.h"
#include "ScriptEnvironmentBase.h"
#include <fstream>

/***********************************************************
constructor
***********************************************************/
TeleportAction::TeleportAction(long id, const std::string &name,
							   const std::string & NewMap, long SpawningId)
: ActionBase(id, name), _NewMap(NewMap), _SpawningId(SpawningId)
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
void TeleportAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	if(owner)
	{
		float offsetX=0, offsetY=0, offsetZ=0;
		if(args)
		{
			ActionArgumentBase & obj = *args;
			const std::type_info& info = typeid(obj);

			// player updated position
			if(info == typeid(OffsetArgument))
			{
				OffsetArgument* castedptr = 
					static_cast<OffsetArgument *>(args);

				offsetX = castedptr->_offsetX;
				offsetY = castedptr->_offsetY;
				offsetZ = castedptr->_offsetZ;
			}
		}

		owner->Teleport(ObjectType, ObjectId, _NewMap, _SpawningId,
							offsetX, offsetY, offsetZ);
	}
}


/***********************************************************
save action to lua file
***********************************************************/	
void TeleportAction::SaveToLuaFile(std::ofstream & file)
{
	file<<"\tAction_"<<GetId()<<" = TeleportAction("<<GetId()<<", \""
				<<GetName()<<"\", \""<<_NewMap<<"\", "<<_SpawningId<<")"<<std::endl;

	file<<"\tenvironment:AddAction(Action_"<<GetId()<<")"<<std::endl<<std::endl;
}




/***********************************************************
constructor
***********************************************************/
ClientScriptAction::ClientScriptAction(long id, const std::string &name,
									   long ScriptId)
: ActionBase(id, name), _ScriptId(ScriptId)
{

}

/***********************************************************
destructor
***********************************************************/	
ClientScriptAction::~ClientScriptAction(void)
{

}

/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void ClientScriptAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	if(owner && _ScriptId >= 0)
	{
		std::stringstream strs;
		strs << "ClientScript_" << _ScriptId;
		owner->ExecuteClientScript(ObjectType, ObjectId, strs.str());
	}
}


/***********************************************************
save action to lua file
***********************************************************/	
void ClientScriptAction::SaveToLuaFile(std::ofstream & file)
{
	file<<"\tAction_"<<GetId()<<" = ClientScriptAction("<<GetId()<<", \""
				<<GetName()<<"\", "<<_ScriptId<<")"<<std::endl;

	file<<"\tenvironment:AddAction(Action_"<<GetId()<<")"<<std::endl<<std::endl;
}


