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

#ifndef _LBANET_ACTION_H__
#define _LBANET_ACTION_H__

#include <LbaTypes.h>
#include <boost/shared_ptr.hpp>
class ScriptEnvironmentBase;

#include "ActionArguments.h"
#include "Conditions.h"
#include "ClientScript.h"

class ActionBase;
typedef boost::shared_ptr<ActionBase> ActionBasePtr;


//! base class used as action to be performed on trigger
class ActionBase
{
public:
	//! constructor
	ActionBase()
	{}
	
	//! destructor
	virtual ~ActionBase(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args){}

	//! get type of the action in string form
	virtual std::string GetTypeName(){ return "";}


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name){}

};



//! use to teleport the object to a new location
class TeleportAction : public ActionBase
{
public:
	//! constructor
	TeleportAction();
	
	//! destructor
	virtual ~TeleportAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "TeleportAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// acessor
	std::string GetMapName()
	{ return _NewMap;}

	// acessor
	long GetSpawning()
	{ return _SpawningId;}


	// acessor
	void SetMapName(std::string map)
	{ _NewMap = map;}

	// acessor
	void SetSpawning(long spawn)
	{ _SpawningId = spawn;}


private:
	std::string		_NewMap;
	long			_SpawningId;
};



//! use to start a script on client side
class ClientScriptAction : public ActionBase
{
public:
	//! constructor
	ClientScriptAction();
	
	//! destructor
	virtual ~ClientScriptAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ClientScriptAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// accessor
	ClientScriptBasePtr GetScript()
	{ return _Script;}

	void SetScript(ClientScriptBasePtr Script)
	{ _Script = Script;}

private:
	ClientScriptBasePtr		_Script;
};




//! use to perform a custom lua action
class CustomAction : public ActionBase
{
public:
	//! constructor
	CustomAction();
	
	//! destructor
	virtual ~CustomAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "CustomAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// accessor
	std::string GetLuaFunctionName()
	{ return _customluafunctionname;}

	void SetLuaFunctionName(std::string FunctionName)
	{ _customluafunctionname = FunctionName;}

private:
	std::string		_customluafunctionname;
};




//! use to display a text on client
class DisplayTextAction : public ActionBase
{
public:
	//! constructor
	DisplayTextAction();
	
	//! destructor
	virtual ~DisplayTextAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "DisplayTextAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// acessor
	long GetTextId()
	{ return _TextId;}

	// acessor
	void SetTextId(long id)
	{ _TextId = id;}


private:
	long			_TextId;
};



//! use to display a text on client
class ConditionalAction : public ActionBase
{
public:
	//! constructor
	ConditionalAction();
	
	//! destructor
	virtual ~ConditionalAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ConditionalAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	//accessors
	void SetCondition(ConditionBasePtr	condition)
	{ _condition = condition; }

	ConditionBasePtr GetCondition()
	{ return _condition; }

	void SetActionTrue(ActionBasePtr act)
	{_actionTrue = act;}

	void SetActionFalse(ActionBasePtr act)
	{_actionFalse = act;}

	ActionBasePtr GetActionTrue()
	{ return _actionTrue; }

	ActionBasePtr GetActionFalse()
	{ return _actionFalse; }

private:
	ConditionBasePtr		_condition;

	ActionBasePtr			_actionTrue;
	ActionBasePtr			_actionFalse;
};




struct ContainerSharedInfo
{
	long				OpeningClient;
	LbaNet::ItemsMap	ContainerItems;
};

// work-around because lua did not work with LbaNet::ItemGroupElement ...
struct ContainerItemGroupElement
{
	ContainerItemGroupElement(long id, int min, int max, float proba, int group)
		: Id(id), Min(min), Max(max), Probability(proba), Group(group)
	{}

	long 			Id;
	int 			Min;
	int 			Max;
	float 			Probability;
	int 			Group;
};



//! use to display a text on client
class OpenContainerAction : public ActionBase
{
public:
	//! constructor
	OpenContainerAction();
	
	//! destructor
	virtual ~OpenContainerAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "OpenContainerAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// acessor
	double GetTimeToReset()
	{ return _TimeToReset/1000;}

	// acessor
	void SetTimeToReset(double t)
	{ _TimeToReset = t*1000;}


	//add item to container start
	void AddItem(const ContainerItemGroupElement &item);

	// get items
	std::vector<ContainerItemGroupElement> &GetItems()
	{return _containerstartitems;}

	// check if item already in container
	bool ItemExist(long id);

protected:
	// prepare the container
	void PrepareContainer();

	//clear container
	void ClearContainer();

private:
	double									_lastResetTime;
	double									_TimeToReset;

	boost::shared_ptr<ContainerSharedInfo>	_shared;
	std::vector<ContainerItemGroupElement>	_containerstartitems;
};





//TODO - add action list

#endif
