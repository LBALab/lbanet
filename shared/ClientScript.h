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

#ifndef _LBANET_CLIENT_SCRIPT_H__
#define _LBANET_CLIENT_SCRIPT_H__

#include <boost/shared_ptr.hpp>
#include <LbaTypes.h>

class ScriptEnvironmentBase;
class ClientScriptBase;
typedef boost::shared_ptr<ClientScriptBase> ClientScriptBasePtr;

#include <string>

//! base class used as action argument
class ClientScriptBase
{
public:
	//! constructor
	ClientScriptBase()
	{}
	
	//! destructor
	virtual ~ClientScriptBase(void){}

	//! get type of the script in string form
	virtual std::string GetTypeName(){ return "";}


	// save script to lua file
	virtual void SaveToLuaFile(std::ofstream & editorfile, const std::string & name){}


	//! execute the script
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId){}
};



//! use to start a script on client side
class GoUpLadderScript : public ClientScriptBase
{
public:
	//! constructor
	GoUpLadderScript();
	
	//! destructor
	virtual ~GoUpLadderScript(void);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "GoUpLadderScript"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & editorfile, const std::string & name);

	//! execute the script
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId);


	// accessors
	float GetLadderPositionX() const { return _LadderPositionX; }
	void SetLadderPositionX(float val) { _LadderPositionX = val; }
	float GetLadderPositionY() const { return _LadderPositionY; }
	void SetLadderPositionY(float val) { _LadderPositionY = val; }
	float GetLadderPositionZ() const { return _LadderPositionZ; }
	void SetLadderPositionZ(float val) { _LadderPositionZ = val; }
	float GetLadderHeight() const { return _LadderHeight; }
	void SetLadderHeight(float val) { _LadderHeight = val; }
	int GetLadderDirection() const { return _LadderDirection; }
	void SetLadderDirection(int val) { _LadderDirection = val; }

private:
	float	_LadderPositionX;
	float	_LadderPositionY;
	float	_LadderPositionZ;
	float	_LadderHeight;
	int		_LadderDirection;

};




//! use to start a script on client side
class TakeExitUpScript : public ClientScriptBase
{
public:
	//! constructor
	TakeExitUpScript();

	//! destructor
	virtual ~TakeExitUpScript(void);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "TakeExitUpScript"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & editorfile, const std::string & name);

	//! execute the script
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId);


	// accessors
	float GetExitPositionX() const { return _ExitPositionX; }
	void SetExitPositionX(float val) { _ExitPositionX = val; }
	float GetExitPositionY() const { return _ExitPositionY; }
	void SetExitPositionY(float val) { _ExitPositionY = val; }
	float GetExitPositionZ() const { return _ExitPositionZ; }
	void SetExitPositionZ(float val) { _ExitPositionZ = val; }
	int GetExitDirection() const { return _ExitDirection; }
	void SetExitDirection(int val) { _ExitDirection = val; }

protected:
	float	_ExitPositionX;
	float	_ExitPositionY;
	float	_ExitPositionZ;
	int		_ExitDirection;
};





//! use to start a script on client side
class TakeExitDownScript : public ClientScriptBase
{
public:
	//! constructor
	TakeExitDownScript();

	//! destructor
	virtual ~TakeExitDownScript(void);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "TakeExitDownScript"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & editorfile, const std::string & name);

	//! execute the script
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId);

	// accessors
	float GetExitPositionX() const { return _ExitPositionX; }
	void SetExitPositionX(float val) { _ExitPositionX = val; }
	float GetExitPositionY() const { return _ExitPositionY; }
	void SetExitPositionY(float val) { _ExitPositionY = val; }
	float GetExitPositionZ() const { return _ExitPositionZ; }
	void SetExitPositionZ(float val) { _ExitPositionZ = val; }
	int GetExitDirection() const { return _ExitDirection; }
	void SetExitDirection(int val) { _ExitDirection = val; }

protected:
	float	_ExitPositionX;
	float	_ExitPositionY;
	float	_ExitPositionZ;
	int		_ExitDirection;
};




//! use to start a script on client side
class CustomScript : public ClientScriptBase
{
public:
	//! constructor
	CustomScript();

	//! destructor
	virtual ~CustomScript(void);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "CustomScript"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & editorfile, const std::string & name);

	// accessors
	std::string GetLuaFunctionName() const { return _luafunctionname; }
	void SetLuaFunctionName(const std::string & val) { _luafunctionname = val; }


	//! execute the script
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId);

protected:
	std::string	_luafunctionname;

};



#endif
