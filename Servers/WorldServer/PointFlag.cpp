#include "PointFlag.h"

#include <fstream>
#include <sstream>


/***********************************************************
save trigger to lua file
***********************************************************/
void PointFlag::SaveToLuaFile(std::ostream & file, std::string forcedid)
{
	std::string namesp = _Name;

	std::stringstream spid;
	if(forcedid != "")
	{
		spid<<forcedid;
		namesp = "point"+forcedid;
	}
	else
		spid<<GetId();

	std::stringstream names;
	names<<"lmap.Point";


	file<<"\t"<<names.str()<<" = PointFlag("<<spid.str()<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetPosX("<<_PosX<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetPosY("<<_PosY<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetPosZ("<<_PosZ<<")"<<std::endl;
	file<<"\t"<<names.str()<<":SetName(\""<<namesp<<"\")"<<std::endl;

	file<<"\tenvironment:AddPoint("<<names.str()<<")"<<std::endl<<std::endl;

}
