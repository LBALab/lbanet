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
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
}


/***********************************************************
save action to lua file
***********************************************************/	
void NegateCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = NegateCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
	if(_tonegate)
	{
		_tonegate->SaveToLuaFile(file, conditionname + "_c");
		file<<"\t"<<conditionname<<":SetCondition("<<conditionname <<"_c)"<<std::endl;
	}
}


/***********************************************************
save action to lua file
***********************************************************/	
void AndCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = AndCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
	if(_cond1)
	{
		_cond1->SaveToLuaFile(file, conditionname + "_c1");
		file<<"\t"<<conditionname<<":SetCondition1("<<conditionname <<"_c1)"<<std::endl;
	}
	if(_cond2)
	{
		_cond2->SaveToLuaFile(file, conditionname + "_c2");
		file<<"\t"<<conditionname<<":SetCondition2("<<conditionname <<"_c2)"<<std::endl;
	}
}


/***********************************************************
save action to lua file
***********************************************************/	
void OrCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = OrCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
	if(_cond1)
	{
		_cond1->SaveToLuaFile(file, conditionname + "_c1");
		file<<"\t"<<conditionname<<":SetCondition1("<<conditionname <<"_c1)"<<std::endl;
	}
	if(_cond2)
	{
		_cond2->SaveToLuaFile(file, conditionname + "_c2");
		file<<"\t"<<conditionname<<":SetCondition2("<<conditionname <<"_c2)"<<std::endl;
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
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return false;

	if(owner)
	{
		int count = owner->GetInventoryItemCount(clientid, _itemid);
		return (count >= _itemnumber);
	}

	return false;
}
	

/***********************************************************
save action to lua file
***********************************************************/	
void ItemInInventoryCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = ItemInInventoryCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
	file<<"\t"<<conditionname<<":SetItemId("<<_itemid <<")"<<std::endl;
	file<<"\t"<<conditionname<<":SetItemNumber("<<_itemnumber <<")"<<std::endl;

}



/***********************************************************
check if the condition is true or not
***********************************************************/	
bool QuestStartedCondition::Passed(ScriptEnvironmentBase * owner, 
							int ObjectType, Ice::Long ObjectId)
{
	if(_questid < 0)
		return false;

	long clientid = -1;

	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return false;

	return owner->QuestStarted(clientid, _questid);
}
	

/***********************************************************
save action to lua file
***********************************************************/	
void QuestStartedCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = QuestStartedCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
	file<<"\t"<<conditionname<<":SetQuestId("<<_questid <<")"<<std::endl;
}



/***********************************************************
check if the condition is true or not
***********************************************************/	
bool QuestFinishedCondition::Passed(ScriptEnvironmentBase * owner, 
							int ObjectType, Ice::Long ObjectId)
{
	if(_questid < 0)
		return false;

	long clientid = -1;

	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return false;

	return owner->QuestFinished(clientid, _questid);
}
	

/***********************************************************
save action to lua file
***********************************************************/	
void QuestFinishedCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = QuestFinishedCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
	file<<"\t"<<conditionname<<":SetQuestId("<<_questid <<")"<<std::endl;
}



/***********************************************************
check if the condition is true or not
***********************************************************/	
bool ChapterStartedCondition::Passed(ScriptEnvironmentBase * owner, 
							int ObjectType, Ice::Long ObjectId)
{
	if(_chapter < 0)
		return false;

	long clientid = -1;

	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return false;

	return owner->ChapterStarted(clientid, _chapter);
}
	

/***********************************************************
save action to lua file
***********************************************************/	
void ChapterStartedCondition::SaveToLuaFile(std::ofstream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = ChapterStartedCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
	file<<"\t"<<conditionname<<":SetChapter("<<_chapter <<")"<<std::endl;
}