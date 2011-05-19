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

#ifndef _LBANET_DIALOG_PART_H__
#define _LBANET_DIALOG_PART_H__

#include <boost/shared_ptr.hpp>
#include <set>


class DialogPart;
typedef boost::shared_ptr<DialogPart> DialogPartPtr;

#include "Conditions.h"
#include "Actions.h"

class ScriptEnvironmentBase;



//! base class used for dialog
class DialogPart
{
public:
	//! constructor
	DialogPart()
		: _resetdialog(false), _childsize(new int)
	{
		*_childsize = 0;
	}
	
	//! destructor
	virtual ~DialogPart(void){}

	//! add child dialog
	int AddChild(DialogPartPtr child);

	//! remove child dialog
	void RemoveChild(DialogPartPtr child);

	//! update position of the child
	void UpdateChildPosition(DialogPartPtr child, int position);

	//! get child list
	std::vector<DialogPartPtr> GetChilds()
	{ return _childs;}

	//! get condition
	ConditionBasePtr GetCondition()
	{ return _condition;}

	//! set condition
	void Setcondition(ConditionBasePtr cond)
	{ _condition = cond;}
	
	//! get action
	ActionBasePtr GetAction()
	{return _action;}
	
	//! set action
	void SetAction(ActionBasePtr act)
	{_action = act;}

	//! accessor
	bool ResetDialog()
	{ return _resetdialog;}

	//! accessor
	void SetResetDialog(bool end)
	{ _resetdialog = end;}


	//! set text
	void SetText(long id);

	//! set text
	void AddText(long id);

	//! set text
	void RemoveText(long id);

	//! get text list
	std::set<long> GetTextList()
	{ return _textids;}

	//! pick text for dialog
	long PickText();

	//! get npc next dialog
	DialogPartPtr GetNpcNextDialog(ScriptEnvironmentBase * owner, long PlayerId);

	//! get player next dialog
	std::vector<DialogPartPtr> GetPlayerNextDialog(ScriptEnvironmentBase * owner, long PlayerId);

	// save action to lua file
	void SaveToLuaFile(std::ostream & file, const std::string & name);

	// return child size
	boost::shared_ptr<int> GetChildSize()
	{ return _childsize;}


protected:
	std::vector<DialogPartPtr>		_childs;
	ConditionBasePtr				_condition;
	ActionBasePtr					_action;

	bool							_resetdialog;

	std::set<long>					_textids;


	boost::shared_ptr<int>			_childsize;
};



#endif
