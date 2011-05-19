#include "Teleport.h"


/***********************************************************
save to lua
***********************************************************/
void TeleportDef::SaveToLuaFile(std::ostream & file)
{
	std::stringstream names;
	names<<"Teleport_"<<GetId();

	file<<"\t"<<names.str()<<" = TeleportDef("<<GetId()<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetName(\""<<_Name<<"\")"<<std::endl;
	file<<"\t"<<names.str()<<":SetMapName(\""<<_MapName<<"\")"<<std::endl;
	file<<"\t"<<names.str()<<":SetSpawn("<<_SpawnId<<")"<<std::endl;

	if(_condition)
	{
		std::stringstream condname;
		condname<<names.str()<<"_cond";
		_condition->SaveToLuaFile(file, condname.str());

		file<<"\t"<<names.str()<<":SetCondition("<<condname.str()<<")"<<std::endl;
	}

	file<<"\tenvironment:AddTeleport("<<names.str()<<")"<<std::endl<<std::endl;
}
	

/***********************************************************
check if tp valid for player
***********************************************************/
bool TeleportDef::ValidForPlayer(ScriptEnvironmentBase * owner, long playerid) const
{
	if(_condition)
		return _condition->Passed(owner, 2, playerid);

	return true;
}


