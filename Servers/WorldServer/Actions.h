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



//! base class used as action argument
class ActionArgumentBase
{
public:
	//! constructor
	ActionArgumentBase(){}
	
	//! destructor
	virtual ~ActionArgumentBase(void){}
};


//! base class used as action argument
class OffsetArgument : public ActionArgumentBase
{
public:
	//! constructor
	OffsetArgument()
		: _offsetX(0), _offsetY(0), _offsetZ(0)
	{}

	//! constructor
	OffsetArgument(float offsetX, float offsetY, float offsetZ)
		: _offsetX(offsetX), _offsetY(offsetY), _offsetZ(offsetZ)
	{}

	//! destructor
	virtual ~OffsetArgument(void){}


	float _offsetX;
	float _offsetY;
	float _offsetZ;
};




//! base class used as action to be performed on trigger
class ActionBase
{
public:
	//! constructor
	ActionBase(long id, const std::string &name)
		: _id(id), _name(name)
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

	//! get action id
	long GetId()
	{ return _id;}

	//! get action name
	std::string GetName()
	{ return _name;}

	//! set action name
	void SetName(const std::string & name)
	{ _name = name;}

	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file){}


private:
	long			_id;
	std::string		_name;

};



//! use to teleport the object to a new location
class TeleportAction : public ActionBase
{
public:
	//! constructor
	TeleportAction(long id, const std::string &name,
						const std::string & NewMap, long SpawningId);
	
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
	virtual void SaveToLuaFile(std::ofstream & file);

	// acessor
	std::string GetMapName()
	{ return _NewMap;}

	// acessor
	long GetSpawning()
	{ return _SpawningId;}

private:
	std::string		_NewMap;
	long			_SpawningId;
};



//! use to teleport the object to a new location
class ClientScriptAction : public ActionBase
{
public:
	//! constructor
	ClientScriptAction(long id, const std::string &name,
						const std::string & ScriptName);
	
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
	virtual void SaveToLuaFile(std::ofstream & file);

	// accessor
	std::string GetScriptName()
	{ return _ScriptName;}


private:
	std::string		_ScriptName;
};

#endif
