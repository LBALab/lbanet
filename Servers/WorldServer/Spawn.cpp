#include "Spawn.h"
#include <fstream>
#include <sstream>


/***********************************************************
save trigger to lua file
***********************************************************/
void Spawn::SaveToLuaFile(std::ofstream & file)
{
	std::stringstream names;
	names<<"Spawn_"<<GetId();

	file<<"\t"<<names.str()<<" = Spawn("<<GetId()<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetPosX("<<_PosX<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetPosY("<<_PosY<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetPosZ("<<_PosZ<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetName(\""<<_Name<<"\")"<<std::endl;
	if(_ForceRotation)
	{
		file<<"\t"<<names.str()<<":SetForceRotation(true)"<<std::endl;
		file<<"\t"<<names.str()<<":SetRotation("<<_Rotation<<")"<<std::endl;	
	}

	file<<"\tenvironment:AddSpawn("<<names.str()<<")"<<std::endl<<std::endl;
}
