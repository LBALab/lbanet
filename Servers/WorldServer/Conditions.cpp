#include "Conditions.h"
#include "ScriptEnvironmentBase.h"
#include <fstream>
#include "SharedDataHandler.h"


/***********************************************************
save action to lua file
***********************************************************/	
void AlwaysTrueCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = AlwaysTrueCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
}


/***********************************************************
save action to lua file
***********************************************************/	
void NegateCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
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
void AndCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
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
void OrCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
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
void ItemInInventoryCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
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
void QuestStartedCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
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
void QuestFinishedCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
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
void ChapterStartedCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = ChapterStartedCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
	file<<"\t"<<conditionname<<":SetChapter("<<_chapter <<")"<<std::endl;
}



/***********************************************************
check if the condition is true or not
***********************************************************/	
bool QuestAvailableCondition::Passed(ScriptEnvironmentBase * owner, 
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

	return owner->QuestAvailable(clientid, _questid);
}
	

/***********************************************************
save action to lua file
***********************************************************/	
void QuestAvailableCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = QuestAvailableCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
	file<<"\t"<<conditionname<<":SetQuestId("<<_questid <<")"<<std::endl;
}





/***********************************************************
check if the condition is true or not
***********************************************************/	
bool CustomCondition::Passed(ScriptEnvironmentBase * owner, 
							int ObjectType, Ice::Long ObjectId)
{
	if(owner)
		return owner->CheckCustomCondition(ObjectType, (long)ObjectId, _luafunction);

	return false;
}
	

/***********************************************************
save action to lua file
***********************************************************/	
void CustomCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = CustomCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
	file<<"\t"<<conditionname<<":SetLuaFunction(\""<<_luafunction <<"\")"<<std::endl;
}




/***********************************************************
check if the condition is true or not
***********************************************************/	
bool ActorMovingCondition::Passed(ScriptEnvironmentBase * owner, 
							int ObjectType, Ice::Long ObjectId)
{
	if(owner)
		return owner->ActorMoving(ObjectType, (long)ObjectId);

	return false;
}
	

/***********************************************************
save action to lua file
***********************************************************/	
void ActorMovingCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = ActorMovingCondition()"<<std::endl;
	file<<"\t"<<conditionname<<":SetTextid("<<_textid <<")"<<std::endl;
}




/***********************************************************
check if the condition is true or not
***********************************************************/	
bool CheckFlagCondition::Passed(ScriptEnvironmentBase * owner, 
							int ObjectType, Ice::Long ObjectId)
{
	long clientid = -2;
	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3 && owner)
		clientid = owner->GetGhostOwnerPlayer((long)ObjectId);

	// check if client found - else return
	if(clientid < 0)
		return false;


	if(owner)
		return (owner->GetDBFlag(clientid, _flagname) == _checkvalue);

	return false;
}
	

/***********************************************************
save action to lua file
***********************************************************/	
void CheckFlagCondition::SaveToLuaFile(std::ostream & file, const std::string & conditionname)
{
	file<<"\t"<<conditionname<<" = CheckFlagCondition()"<<std::endl;
	if(_flagname != "")
		file<<"\t"<<conditionname<<":SetFlagName(\""<<_flagname <<"\")"<<std::endl;
	file<<"\t"<<conditionname<<":SetValue("<<_checkvalue <<")"<<std::endl;
}
