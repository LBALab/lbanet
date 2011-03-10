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

#ifndef _THREAD_LUA_HANDLER_H__
#define _THREAD_LUA_HANDLER_H__

#include <string>

struct lua_State;
class ScriptEnvironmentBase;


//! class taking care of a lua thread
class LuaThreadHandler
{
public:
	//! constructor
	LuaThreadHandler(lua_State * mainstate, const std::string & FunctionName, 
					bool inlinefunction, ScriptEnvironmentBase* env);
	
	//! destructor
	~LuaThreadHandler(void);

	//! resume thread
	//! return true if thread is finished and should be destructed
	bool ResumeThread();

	//! get thread reference
	int GetReference()
	{return m_refKey;}

	//! get script name
	std::string GetScriptName()
	{return m_FunctionName;}

	//! check if thread started
	bool IsStarted()
	{ return m_started;}

private:
	lua_State *		m_LuaThreadState;
	lua_State *		m_LuaMainState;
	std::string		m_FunctionName;
	int				m_refKey;
	bool			m_started;


	static unsigned long	m_idgenerator;
};

#endif
