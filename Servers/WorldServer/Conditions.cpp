#include "Conditions.h"
#include "ScriptEnvironmentBase.h"
#include <fstream>



/***********************************************************
save action to lua file
***********************************************************/	
void AlwaysTrueCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = AlwaysTrueCondition()"<<std::endl;
}


/***********************************************************
save action to lua file
***********************************************************/	
void NegateCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = NegateCondition()"<<std::endl;
	if(_tonegate)
	{
		_tonegate->SaveToLuaFile(file, conditionname + "_c");
		file<<"\t"<<conditionname<<":SetCondition("<<conditionname + "_c)"<<std::endl;
	}
}


/***********************************************************
save action to lua file
***********************************************************/	
void AndCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = AndCondition()"<<std::endl;
	if(_cond1)
	{
		_cond1->SaveToLuaFile(file, conditionname + "_c1");
		file<<"\t"<<conditionname<<":SetCondition1("<<conditionname + "_c1)"<<std::endl;
	}
	if(_cond2)
	{
		_cond2->SaveToLuaFile(file, conditionname + "_c2");
		file<<"\t"<<conditionname<<":SetCondition2("<<conditionname + "_c2)"<<std::endl;
	}
}


/***********************************************************
save action to lua file
***********************************************************/	
void OrCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = OrCondition()"<<std::endl;
	if(_cond1)
	{
		_cond1->SaveToLuaFile(file, conditionname + "_c1");
		file<<"\t"<<conditionname<<":SetCondition1("<<conditionname + "_c1)"<<std::endl;
	}
	if(_cond2)
	{
		_cond2->SaveToLuaFile(file, conditionname + "_c2");
		file<<"\t"<<conditionname<<":SetCondition2("<<conditionname + "_c2)"<<std::endl;
	}
}
