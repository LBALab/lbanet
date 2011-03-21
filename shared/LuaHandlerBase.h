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

#ifndef _BASE_LUA_HANDLER_H__
#define _BASE_LUA_HANDLER_H__

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

struct lua_State;
class LuaThreadHandler;
class ScriptEnvironmentBase;
class ActionArgumentBase;
class ScriptInitHandler;

//! class taking care of the maping between lua and the server interfaces
class LuaHandlerBase
{
public:
	//! constructor
	LuaHandlerBase();

	//! destructor
	virtual ~LuaHandlerBase(void);

	//! load a lua file
	void LoadFile(const std::string & luafile);

	//! call lua function
	void CallLua(const std::string & functioname, ScriptEnvironmentBase* env = 0);

	//! call lua function
	void CallLua(const std::string & functioname, ScriptInitHandler* env);


	//! start script in a new thread
	//! return script id if successed or -1 else
	int StartScript(const std::string & FunctionName, bool inlinefunction,
							ScriptEnvironmentBase* env);

	//! resume yield thread
	//! return true if finished
	bool ResumeThread(int ThreadIdx, std::string & functioname);

	//! try to stop lua thread
	void StopThread(int ThreadIdx);

	//! execute lua script given as a string
	void ExecuteScriptString( const std::string & ScriptString );


	// execute custom lua function
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	void ExecuteCustomAction(int ObjectType, long ObjectId,
										const std::string & FunctionName,
										ActionArgumentBase * args,
										ScriptEnvironmentBase* env);


	//! call lua function
	bool CallLuaCondition(const std::string & functioname, ScriptEnvironmentBase* env, 
							int objecttype, long objectid);

protected:
	lua_State *													m_LuaState;

	std::map<int, boost::shared_ptr<LuaThreadHandler> >			m_RunningThreads;
};

#endif
