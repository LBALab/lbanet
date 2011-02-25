#include "Quest.h"
#include <fstream>

/***********************************************************
add condition
***********************************************************/	
void Quest::AddCondition(ConditionBasePtr cond)
{
	_conditions.push_back(cond);
}

/***********************************************************
remove condition
***********************************************************/	
void Quest::RemoveCondition(ConditionBasePtr cond)
{
	std::vector<ConditionBasePtr>::iterator it = std::find(_conditions.begin(), _conditions.end(), cond);
	if(it != _conditions.end())
		_conditions.erase(it);
}


/***********************************************************
replace condition
***********************************************************/	
void Quest::ReplaceCondition(ConditionBasePtr oldc, ConditionBasePtr newc)
{
	std::vector<ConditionBasePtr>::iterator it = std::find(_conditions.begin(), _conditions.end(), oldc);
	if(it != _conditions.end())
		*it = newc;
}


/***********************************************************
start quest for player
***********************************************************/
void Quest::StartQuest(ScriptEnvironmentBase * owner, long playerid)
{
	if(playerid >= playerid)
	{
		if(_actionAtStart)
			_actionAtStart->Execute(owner, 2, playerid, NULL);

		//todo - init tracking conditions
	}
}


/***********************************************************
check if quest is done for player
***********************************************************/
bool Quest::QuestFinished(ScriptEnvironmentBase * owner, long playerid)
{
	bool res = false;
	if(playerid >= playerid)
	{
		res = true;
		for(size_t i=0; i< _conditions.size(); ++i)
		{
			if(!_conditions[i]->Passed(owner, 2, playerid))
			{
				res = false;
				break;
			}
		}

		if(res)
		{
			if(_actionAtComplete)
				_actionAtComplete->Execute(owner, 2, playerid, NULL);	
		}
	}

	return res;
}


/***********************************************************
save quest to lua file
***********************************************************/
void Quest::SaveToLuaFile(std::ofstream & file)
{
	std::stringstream name;
	name<<"Quest_"<<GetId();
	file<<"\t"<<name.str()<<" = Quest("<<GetId()<<")"<<std::endl;

	if(_actionAtStart)
	{
		std::stringstream aname;
		aname<<name.str()<<"_act1";
		_actionAtStart->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name.str()<<":SetActionAtStart("<<aname.str()<<")"<<std::endl;
	}

	if(_actionAtComplete)
	{
		std::stringstream aname;
		aname<<name.str()<<"_act2";
		_actionAtComplete->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name.str()<<":SetActionAtComplete("<<aname.str()<<")"<<std::endl;
	}

	file<<"\t"<<name.str()<<":SetChapter("<<_chapternumber<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetTitleTextId("<<_titleTextId<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetDescriptionTextId("<<_descriptionTextId<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetLocationTextId("<<_locationtextid<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetVisible("<<(_visible?"true":"false")<<")"<<std::endl;


	for(size_t i=0; i< _conditions.size(); ++i)
	{
		std::stringstream cname;
		cname<<name.str()<<"_cond"<<i;
		_conditions[i]->SaveToLuaFile(file, cname.str());

		file<<"\t"<<name.str()<<":AddCondition("<<cname.str()<<")"<<std::endl;
	}

	file<<"\tenvironment:AddQuest("<<name.str()<<")"<<std::endl<<std::endl;
}