#include "ClientScript.h"
#include <fstream>



/***********************************************************
constructor
***********************************************************/	
GoUpLadderScript::GoUpLadderScript(long id, const std::string &name,
					float LadderPositionX, float LadderPositionY, float LadderPositionZ,
					float LadderHeight, int LadderDirection)
					: 	ClientScriptBase(id, name), 
						_LadderPositionX(LadderPositionX),
						_LadderPositionY(LadderPositionY),
						_LadderPositionZ(LadderPositionZ),
						_LadderHeight(LadderHeight),
						_LadderDirection(LadderDirection)
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
void GoUpLadderScript::SaveToLuaFile(std::ofstream & editorfile)
{
	editorfile<<"\tScript_"<<GetId()<<" = GoUpLadderScript("<<GetId()<<", \""
				<<GetName()<<"\", "<<_LadderPositionX<<", "<<_LadderPositionY<<", "
				<<_LadderPositionZ<<", "<<_LadderHeight<<", "<<_LadderDirection<<")"<<std::endl;

	editorfile<<"\tenvironment:EditorAddClientScript(Script_"<<GetId()<<")"<<std::endl<<std::endl;
}

 
/***********************************************************
save script content to lua
***********************************************************/
void GoUpLadderScript::SaveScriptToLua(std::ostream & luastream)
{
	luastream << "function ClientScript_"<<GetId()<<"(ScriptId)"<<std::endl;
	luastream << "LadderPosition = LbaVec3("<<_LadderPositionX<<", "<<_LadderPositionY<<", "<<_LadderPositionZ<<")"<<std::endl;
	luastream << "ActorGoUpLadder(ScriptId, -1, LadderPosition, "<<_LadderHeight<<", "<<_LadderDirection<<")"<<std::endl;
	luastream << "end"<<std::endl<<std::endl;
}




/***********************************************************
constructor
***********************************************************/	
TakeExitUpScript::TakeExitUpScript(long id, const std::string &name,
								   float  ExitPositionX, float  ExitPositionY, float  ExitPositionZ,
								   int  ExitDirection)
								   : ClientScriptBase(id, name), 
								   _ExitPositionX(ExitPositionX),
								   _ExitPositionY(ExitPositionY),
								   _ExitPositionZ(ExitPositionZ),
								   _ExitDirection(ExitDirection)
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
void TakeExitUpScript::SaveToLuaFile(std::ofstream & editorfile)
{
	editorfile<<"\tScript_"<<GetId()<<" = TakeExitUpScript("<<GetId()<<", \""
		<<GetName()<<"\", "<<_ExitPositionX<<", "<<_ExitPositionY<<", "
		<<_ExitPositionZ<<", "<<_ExitDirection<<")"<<std::endl;

	editorfile<<"\tenvironment:EditorAddClientScript(Script_"<<GetId()<<")"<<std::endl<<std::endl;
}


/***********************************************************
save script content to lua
***********************************************************/
void TakeExitUpScript::SaveScriptToLua(std::ostream & luastream)
{
	luastream << "function ClientScript_"<<GetId()<<"(ScriptId)"<<std::endl;
	luastream << "ExitPosition = LbaVec3("<<_ExitPositionX<<", "<<_ExitPositionY<<", "<<_ExitPositionZ<<")"<<std::endl;
	luastream << "TakeExitUp(ScriptId, -1, ExitPosition, "<<_ExitDirection<<")"<<std::endl;
	luastream << "end"<<std::endl<<std::endl;
}



/***********************************************************
constructor
***********************************************************/	
TakeExitDownScript::TakeExitDownScript(long id, const std::string &name,
								   float  ExitPositionX, float  ExitPositionY, float  ExitPositionZ,
								   int  ExitDirection)
								   : ClientScriptBase(id, name), 
								   _ExitPositionX(ExitPositionX),
								   _ExitPositionY(ExitPositionY),
								   _ExitPositionZ(ExitPositionZ),
								   _ExitDirection(ExitDirection)
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
void TakeExitDownScript::SaveToLuaFile(std::ofstream & editorfile)
{
	editorfile<<"\tScript_"<<GetId()<<" = TakeExitDownScript("<<GetId()<<", \""
		<<GetName()<<"\", "<<_ExitPositionX<<", "<<_ExitPositionY<<", "
		<<_ExitPositionZ<<", "<<_ExitDirection<<")"<<std::endl;

	editorfile<<"\tenvironment:EditorAddClientScript(Script_"<<GetId()<<")"<<std::endl<<std::endl;
}


/***********************************************************
save script content to lua
***********************************************************/
void TakeExitDownScript::SaveScriptToLua(std::ostream & luastream)
{
	luastream << "function ClientScript_"<<GetId()<<"(ScriptId)"<<std::endl;
	luastream << "ExitPosition = LbaVec3("<<_ExitPositionX<<", "<<_ExitPositionY<<", "<<_ExitPositionZ<<")"<<std::endl;
	luastream << "TakeExitDown(ScriptId, -1, ExitPosition, "<<_ExitDirection<<")"<<std::endl;
	luastream << "end"<<std::endl<<std::endl;
}