/*
------------------------[ Lbanet Source ]-------------------------
Copyright (C) 2009
Author: Vivien Delage [Rincevent_123]
Email : vdelage@gmail.com

-------------------------------[ GNU License ]-------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
*/

#ifndef _LBA_QUEST_H__
#define _LBA_QUEST_H__


#include <map>
#include <string>
#include <vector>
#include "Conditions.h"
#include "Actions.h"

//! take care of shared data between process
class Quest
{
public:
	//! constructor
	Quest(long id)
		: _id(id)
	{}

	//! destructor
	~Quest(void){}

	//! get quest id
	long GetId()
	{return _id;}

	//! add condition
	void AddCondition(ConditionBasePtr cond);

	//! remove condition
	void RemoveCondition(ConditionBasePtr cond);

	//! get conditions
	std::vector<ConditionBasePtr> GetConditions()
	{return _conditions;}

	//! get action at start
	ActionBasePtr GetActionAtStart()
	{ return _actionAtStart;}

	//! set action at start
	void SetActionAtStart(ActionBasePtr act)
	{_actionAtStart = act;}

	//! get action at Complete
	ActionBasePtr GetActionAtComplete()
	{ return _actionAtComplete;}

	//! set action at Complete
	void SetActionAtComplete(ActionBasePtr act)
	{_actionAtComplete = act;}

	//! get title text id
	long GetTitleTextId()
	{return _titleTextId;}

	//! set title text id
	void SetTitleTextId(long id)
	{_titleTextId = id;}

	//! get desc text id
	long GetDescriptionTextId()
	{return _descriptionTextId;}

	//! set desc text id
	void SetDescriptionTextId(long id)
	{_descriptionTextId = id;}


	//! start quest for player
	void StartQuest(ScriptEnvironmentBase * owner, long playerid);

	//! check if quest is done for player
	bool QuestFinished(ScriptEnvironmentBase * owner, long playerid);


	// save quest to lua file
	void SaveToLuaFile(std::ofstream & file);

private:
	long							_id;

	std::vector<ConditionBasePtr>	_conditions;
	ActionBasePtr					_actionAtStart;
	ActionBasePtr					_actionAtComplete;

	long							_titleTextId;
	long							_descriptionTextId;
};

#endif
