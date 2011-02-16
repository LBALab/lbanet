#include "NpcHandler.h"
#include <math.h>

#include <fstream>


/***********************************************************
update position of the script
***********************************************************/
NPCHandler::NPCHandler(const ActorObjectInfo & actorinfo)
	: ActorHandler(actorinfo), _rootdialog(new DialogPart())
{
	
}

/***********************************************************
return the build class
***********************************************************/
std::string NPCHandler::LuaBuildClass()
{
	std::stringstream res;
	res<<"NpcHandler(Actor_"<<m_actorinfo.ObjectId<<")";

	return res.str();
}



/***********************************************************
write extra lua
***********************************************************/
void NPCHandler::ExtraLua(std::ofstream & file, const std::string & name)
{
	std::stringstream named;
	named<<name<<"_dialog";
	_rootdialog->SaveToLuaFile(file, named.str());

	file<<"\t"<<name<<":SetRootDialog("<<named.str()<<")"<<std::endl;
}