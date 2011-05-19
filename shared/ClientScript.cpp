#include "ClientScript.h"
#include <fstream>
#include "ScriptEnvironmentBase.h"


/***********************************************************
constructor
***********************************************************/	
GoUpLadderScript::GoUpLadderScript()
: _LadderPositionX(0), _LadderPositionY(0), _LadderPositionZ(0), 
	_LadderHeight(5), _LadderDirection(0)
{

}

/***********************************************************
destructor
***********************************************************/	
GoUpLadderScript::~GoUpLadderScript(void)
{

}


/***********************************************************
save action to lua file
***********************************************************/	
void GoUpLadderScript::SaveToLuaFile(std::ostream & editorfile, const std::string & name)
{
	editorfile<<"\t"<<name<<" = GoUpLadderScript()"<<std::endl;
	editorfile<<"\t"<<name<<":SetLadderPositionX("<<_LadderPositionX<<")"<<std::endl;
	editorfile<<"\t"<<name<<":SetLadderPositionY("<<_LadderPositionY<<")"<<std::endl;
	editorfile<<"\t"<<name<<":SetLadderPositionZ("<<_LadderPositionZ<<")"<<std::endl;
	editorfile<<"\t"<<name<<":SetLadderHeight("<<_LadderHeight<<")"<<std::endl;
	editorfile<<"\t"<<name<<":SetLadderDirection("<<_LadderDirection<<")"<<std::endl;
}

 

/***********************************************************
execute the script
***********************************************************/
void GoUpLadderScript::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId)
{
	if(owner)
	{
		std::stringstream luastream;
		luastream << "LadderPosition = LbaVec3("<<_LadderPositionX<<", "<<_LadderPositionY<<", "<<_LadderPositionZ<<")"<<std::endl;
		luastream << "ActorGoUpLadder(ScriptId, -1, LadderPosition, "<<_LadderHeight<<", "<<_LadderDirection<<", Environment)"<<std::endl;

		owner->ExecuteClientScript(ObjectType, (long)ObjectId, luastream.str(), true);
	}
}



/***********************************************************
constructor
***********************************************************/	
TakeExitUpScript::TakeExitUpScript()
: _ExitPositionX(0), _ExitPositionY(0), _ExitPositionZ(0), 
	_ExitDirection(0)
{

}

/***********************************************************
destructor
***********************************************************/	
TakeExitUpScript::~TakeExitUpScript(void)
{

}


/***********************************************************
save action to lua file
***********************************************************/	
void TakeExitUpScript::SaveToLuaFile(std::ostream & editorfile, const std::string & name)
{
	editorfile<<"\t"<<name<<" = TakeExitUpScript()"<<std::endl;
	editorfile<<"\t"<<name<<":SetExitPositionX("<<_ExitPositionX<<")"<<std::endl;
	editorfile<<"\t"<<name<<":SetExitPositionY("<<_ExitPositionY<<")"<<std::endl;
	editorfile<<"\t"<<name<<":SetExitPositionZ("<<_ExitPositionZ<<")"<<std::endl;
	editorfile<<"\t"<<name<<":SetExitDirection("<<_ExitDirection<<")"<<std::endl;
}


/***********************************************************
execute the script
***********************************************************/
void TakeExitUpScript::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId)
{
	if(owner)
	{
		std::stringstream luastream;
		luastream << "ExitPosition = LbaVec3("<<_ExitPositionX<<", "<<_ExitPositionY<<", "<<_ExitPositionZ<<")"<<std::endl;
		luastream << "TakeExitUp(ScriptId, -1, ExitPosition, "<<_ExitDirection<<", Environment)"<<std::endl;
		
		owner->ExecuteClientScript(ObjectType, (long)ObjectId, luastream.str(), true);
	}
}




/***********************************************************
constructor
***********************************************************/	
TakeExitDownScript::TakeExitDownScript()
: _ExitPositionX(0), _ExitPositionY(0), _ExitPositionZ(0), 
	_ExitDirection(0)
{

}

/***********************************************************
destructor
***********************************************************/	
TakeExitDownScript::~TakeExitDownScript(void)
{

}


/***********************************************************
save action to lua file
***********************************************************/	
void TakeExitDownScript::SaveToLuaFile(std::ostream & editorfile, const std::string & name)
{
	editorfile<<"\t"<<name<<" = TakeExitDownScript()"<<std::endl;
	editorfile<<"\t"<<name<<":SetExitPositionX("<<_ExitPositionX<<")"<<std::endl;
	editorfile<<"\t"<<name<<":SetExitPositionY("<<_ExitPositionY<<")"<<std::endl;
	editorfile<<"\t"<<name<<":SetExitPositionZ("<<_ExitPositionZ<<")"<<std::endl;
	editorfile<<"\t"<<name<<":SetExitDirection("<<_ExitDirection<<")"<<std::endl;
}



/***********************************************************
execute the script
***********************************************************/
void TakeExitDownScript::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId)
{
	if(owner)
	{
		std::stringstream luastream;
		luastream << "ExitPosition = LbaVec3("<<_ExitPositionX<<", "<<_ExitPositionY<<", "<<_ExitPositionZ<<")"<<std::endl;
		luastream << "TakeExitDown(ScriptId, -1, ExitPosition, "<<_ExitDirection<<", Environment)"<<std::endl;
		
		owner->ExecuteClientScript(ObjectType, (long)ObjectId, luastream.str(), true);
	}
}





/***********************************************************
constructor
***********************************************************/	
CustomScript::CustomScript()
{

}

/***********************************************************
destructor
***********************************************************/	
CustomScript::~CustomScript(void)
{

}


/***********************************************************
save action to lua file
***********************************************************/	
void CustomScript::SaveToLuaFile(std::ostream & editorfile, const std::string & name)
{
	editorfile<<"\t"<<name<<" = CustomScript()"<<std::endl;
	editorfile<<"\t"<<name<<":SetLuaFunctionName(\""<<_luafunctionname<<"\")"<<std::endl;
}




/***********************************************************
execute the script
***********************************************************/
void CustomScript::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId)
{
	if(owner)
		owner->ExecuteClientScript(ObjectType, (long)ObjectId, _luafunctionname, false);
}
