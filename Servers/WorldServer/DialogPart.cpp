#include "DialogPart.h"
#include "Randomizer.h"

#include <fstream>

/***********************************************************
add child dialog
***********************************************************/
void DialogPart::AddChild(DialogPartPtr child)
{
	_childs.push_back(child);
}


/***********************************************************
remove child dialog
***********************************************************/
void DialogPart::RemoveChild(DialogPartPtr child)
{
	std::vector<DialogPartPtr>::iterator it = std::find(_childs.begin(), _childs.end(), child);
	if(it != _childs.end())
		_childs.erase(it);
}

/***********************************************************
update position of the child
***********************************************************/
void DialogPart::UpdateChildPosition(DialogPartPtr child, int position)
{
	std::vector<DialogPartPtr>::iterator it = std::find(_childs.begin(), _childs.end(), child);
	if(it != _childs.end())
	{
		DialogPartPtr keep = *it;
		_childs.erase(it);

		std::vector<DialogPartPtr>::iterator itinsert = _childs.begin();
		for(int cc=0; cc<position; ++cc)
			++itinsert;

		_childs.insert(itinsert, keep);
	}
}



/***********************************************************
set text
***********************************************************/
void DialogPart::SetText(long id)
{
	_textids.clear();
	AddText(id);
}



/***********************************************************
add text
***********************************************************/
void DialogPart::AddText(long id)
{
	_textids.insert(id);
}


/***********************************************************
remvoe text
***********************************************************/
void DialogPart::RemoveText(long id)
{
	std::set<long>::iterator it = _textids.find(id);
	if(it != _textids.end())
		_textids.erase(it);
}


/***********************************************************
pick text for dialog
***********************************************************/
long DialogPart::PickText()
{
	int size = (int)_textids.size();
	std::set<long>::iterator it = _textids.begin();

	if(size == 0)
		return -1;
	if(size == 1)
		return *it;

	int index = Randomizer::getInstance()->RandInt(size-1);
	for(int i=0; i<index; ++i)
		++it;

	return *it;
}

 
/***********************************************************
get npc next dialog
***********************************************************/
DialogPartPtr DialogPart::GetNpcNextDialog(ScriptEnvironmentBase * owner, long PlayerId)
{
	std::vector<DialogPartPtr>::iterator it = _childs.begin();
	std::vector<DialogPartPtr>::iterator end = _childs.end();
	for(; it != end; ++it)
	{
		if((*it)->GetCondition()->Passed(owner, 2, PlayerId))
			return *it;
	}

	return DialogPartPtr();
}


/***********************************************************
get player next dialog
***********************************************************/
std::vector<DialogPartPtr>  DialogPart::GetPlayerNextDialog(ScriptEnvironmentBase * owner, 
															long PlayerId)
{
	std::vector<DialogPartPtr> res;

	std::vector<DialogPartPtr>::iterator it = _childs.begin();
	std::vector<DialogPartPtr>::iterator end = _childs.end();
	for(; it != end; ++it)
	{
		if((*it)->GetCondition()->Passed(owner, 2, PlayerId))
			res.push_back(*it);
	}

	return res;
}


/***********************************************************
save action to lua file
***********************************************************/
void DialogPart::SaveToLuaFile(std::ofstream & file, const std::string & name)
{
	file<<"\t"<<name<<" = DialogPart()"<<std::endl;

	if(_condition)
	{
		std::stringstream condname;
		condname<<name<<"_cond";
		_condition->SaveToLuaFile(file, condname.str());

		file<<"\t"<<name<<":Setcondition("<<condname.str()<<")"<<std::endl;
	}

	if(_action)
	{
		std::stringstream aname;
		aname<<name<<"_act";
		_action->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name<<":SetAction("<<aname.str()<<")"<<std::endl;
	}

	file<<"\t"<<name<<":SetEndDialog("<<(_enddialog?"true":"false")<<")"<<std::endl;
	file<<"\t"<<name<<":SetResetDialog("<<(_resetdialog?"true":"false")<<")"<<std::endl;

	std::set<long>::iterator it = _textids.begin();
	std::set<long>::iterator end = _textids.end();
	for(; it != end; ++it)
		file<<"\t"<<name<<":AddText("<<*it<<")"<<std::endl;	


	for(size_t i=0; i<_childs.size(); ++i)
	{
		std::stringstream named;
		named<<name<<"_child"<<i;
		_childs[i]->SaveToLuaFile(file, named.str());

		file<<"\t"<<name<<":AddChild("<<named.str()<<")"<<std::endl;
	}

}