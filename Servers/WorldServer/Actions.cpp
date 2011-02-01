#include "Actions.h"
#include "ScriptEnvironmentBase.h"
#include <fstream>

/***********************************************************
constructor
***********************************************************/
TeleportAction::TeleportAction()
: _SpawningId(-1)
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

		owner->Teleport(ObjectType, (long)ObjectId, _NewMap, _SpawningId,
							offsetX, offsetY, offsetZ);
	}
}


/***********************************************************
save action to lua file
***********************************************************/	
void TeleportAction::SaveToLuaFile(std::ofstream & file, const std::string & name)
{
	file<<"\t"<<name<<" = TeleportAction()"<<std::endl;
	file<<"\t"<<name<<":SetMapName(\""<<_NewMap<<"\")"<<std::endl;
	file<<"\t"<<name<<":SetSpawning("<<_SpawningId<<")"<<std::endl;
}




/***********************************************************
constructor
***********************************************************/
ClientScriptAction::ClientScriptAction()
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
	if(_Script)
		_Script->Execute(owner, ObjectType, ObjectId);
}


/***********************************************************
save action to lua file
***********************************************************/	
void ClientScriptAction::SaveToLuaFile(std::ofstream & file, const std::string & name)
{
	file<<"\t"<<name<<" = ClientScriptAction()"<<std::endl;

	if(_Script)
	{
		std::stringstream csname;
		csname<<name<<"_cs";
		_Script->SaveToLuaFile(file, csname.str());
		file<<"\t"<<name<<":SetScript("<<csname.str()<<")"<<std::endl;
	}
}






/***********************************************************
constructor
***********************************************************/
CustomAction::CustomAction()
{

}

/***********************************************************
destructor
***********************************************************/	
CustomAction::~CustomAction(void)
{

}

/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void CustomAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	if(owner && _customluafunctionname != "")
		owner->ExecuteCustomAction(ObjectType, (long)ObjectId, _customluafunctionname, args);
}


/***********************************************************
save action to lua file
***********************************************************/	
void CustomAction::SaveToLuaFile(std::ofstream & file, const std::string & name)
{
	file<<"\t"<<name<<" = CustomAction()"<<std::endl;
	file<<"\t"<<name<<":SetLuaFunctionName(\""<<_customluafunctionname<<"\")"<<std::endl;
}




/***********************************************************
constructor
***********************************************************/
DisplayTextAction::DisplayTextAction()
: _TextId(-1)
{

}

/***********************************************************
destructor
***********************************************************/	
DisplayTextAction::~DisplayTextAction(void)
{

}

/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void DisplayTextAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	if(owner)
		owner->DisplayTxtAction(ObjectType, (long)ObjectId, _TextId);
}


/***********************************************************
save action to lua file
***********************************************************/	
void DisplayTextAction::SaveToLuaFile(std::ofstream & file, const std::string & name)
{
	file<<"\t"<<name<<" = DisplayTextAction()"<<std::endl;
	file<<"\t"<<name<<":SetTextId("<<_TextId<<")"<<std::endl;
}




/***********************************************************
constructor
***********************************************************/	
ConditionalAction::ConditionalAction()
{

}
	

/***********************************************************
destructor
***********************************************************/	
ConditionalAction::~ConditionalAction(void)
{

}

/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/	
void ConditionalAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
											ActionArgumentBase* args)
{
	if(_condition && _condition->Passed(owner, ObjectType, ObjectId))
	{
		if(_actionTrue)
			_actionTrue->Execute(owner, ObjectType, ObjectId, 0);
	}
	else
	{
		if(_actionFalse)
			_actionFalse->Execute(owner, ObjectType, ObjectId, 0);
	}
}




/***********************************************************
save action to lua file
***********************************************************/	
void ConditionalAction::SaveToLuaFile(std::ofstream & file, const std::string & name)
{
	file<<"\t"<<name<<" = ConditionalAction()"<<std::endl;

	if(_actionTrue)
	{
		std::stringstream aname;
		aname<<name<<"_act1";
		_actionTrue->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name<<":SetActionTrue("<<aname.str()<<")"<<std::endl;
	}

	if(_actionFalse)
	{
		std::stringstream aname;
		aname<<name<<"_act2";
		_actionFalse->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name<<":SetActionFalse("<<aname.str()<<")"<<std::endl;
	}

	if(_condition)
	{
		std::stringstream condname;
		condname<<name<<"_cond";
		_condition->SaveToLuaFile(file, condname.str());

		file<<"\t"<<name<<":SetCondition("<<condname.str()<<")"<<std::endl;
	}

}