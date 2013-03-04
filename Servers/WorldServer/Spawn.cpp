#include "Spawn.h"
#include "Actions.h"

#include <fstream>
#include <sstream>


/***********************************************************
save trigger to lua file
***********************************************************/
void Spawn::SaveToLuaFile(std::ostream & file, std::string forcedid)
{
	std::string namesp = _Name;

	std::stringstream spid;
	if(forcedid != "")
	{
		spid<<forcedid;
		namesp = "spawning"+forcedid;
	}
	else
		spid<<GetId();

	std::stringstream names;
	names<<"lmap.sp";


	file<<"\t"<<names.str()<<" = Spawn("<<spid.str()<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetPosX("<<_PosX<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetPosY("<<_PosY<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetPosZ("<<_PosZ<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetName(\""<<namesp<<"\")"<<std::endl;
	if(_ForceRotation)
	{
		file<<"\t"<<names.str()<<":SetForceRotation(true)"<<std::endl;
		file<<"\t"<<names.str()<<":SetRotation("<<_Rotation<<")"<<std::endl;
	}


	if(_actionAtArrival)
	{
		std::stringstream aname;
		aname<<names.str()<<"_act1";
		_actionAtArrival->SaveToLuaFile(file, aname.str());

		file<<"\t"<<names.str()<<":SetActionAtArrival("<<aname.str()<<")"<<std::endl;
	}

	file<<"\tenvironment:AddSpawn("<<names.str()<<")"<<std::endl<<std::endl;

}
