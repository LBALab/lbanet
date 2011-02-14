#include "Conditions.h"
#include "ScriptEnvironmentBase.h"
#include <fstream>
#include "SharedDataHandler.h"


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




/***********************************************************
check if the condition is true or not
***********************************************************/	
bool ItemInInventoryCondition::Passed(ScriptEnvironmentBase * owner, 
							int ObjectType, Ice::Long ObjectId)
{
	if(_itemid < 0)
		return false;

	long clientid = -1;

	if(ObjectType == 2)
		clientid = ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		// todo - find attached player
	}

	// check if client found - else return
	if(clientid < 0)
		return false;

	int inventorysize;
	LbaNet::ItemsMap itmap = SharedDataHandler::getInstance()->GetInventory(clientid, inventorysize);
	LbaNet::ItemsMap::iterator it = itmap.find(_itemid);
	if(it != itmap.end())
		return (it->second.Count >= _itemnumber);

	return false;
}
	

/***********************************************************
save action to lua file
***********************************************************/	
void ItemInInventoryCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = ItemInInventoryCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetItemId("<<_itemid + ")"<<std::endl;
	file<<"\t"<<conditionname<<":SetItemNumber("<<_itemnumber + ")"<<std::endl;

}