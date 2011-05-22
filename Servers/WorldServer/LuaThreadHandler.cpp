#include "LuaThreadHandler.h"
#include "ScriptEnvironmentBase.h"
#include "LogHandler.h"
#include <sstream>
#include <iostream>

extern "C"
{
    #include "lua.h"
}
#include <luabind/luabind.hpp>

unsigned long LuaThreadHandler::m_idgenerator = 0;

/***********************************************************
constructor
***********************************************************/
LuaThreadHandler::LuaThreadHandler(lua_State * mainstate, const std::string & FunctionName, 
								   bool inlinefunction, ScriptEnvironmentBase* env, int &ThreadReference)
: m_FunctionName(FunctionName), m_LuaMainState(mainstate), m_started(false)
{
	try
	{
		m_LuaThreadState = lua_newthread(m_LuaMainState);
		m_refKey = luaL_ref(m_LuaMainState, LUA_REGISTRYINDEX);
		ThreadReference = m_refKey;

		if(inlinefunction)
		{
			++m_idgenerator;

			std::stringstream fctname;
			fctname<<"LTH"<<m_idgenerator;

			std::stringstream inlinefct;
			inlinefct<<"function "<<fctname.str()<<"(ScriptId, Environment)"<<std::endl;
			inlinefct<<FunctionName;
			inlinefct<<"end"<<std::endl;

			std::string check = inlinefct.str();
			luaL_dostring(m_LuaMainState, inlinefct.str().c_str());

			luabind::resume_function<void>(m_LuaThreadState, fctname.str().c_str(), m_refKey, env);
			m_started = true;
		}
		else
		{
			// check if function exist
			lua_getglobal(m_LuaMainState, m_FunctionName.c_str());
			if (lua_isfunction(m_LuaMainState, lua_gettop(m_LuaMainState)))
			{
				luabind::resume_function<void>(m_LuaThreadState, m_FunctionName.c_str(), m_refKey, env);
				m_started = true;
				LogHandler::getInstance()->LogToFile("Script started: "+m_FunctionName, m_refKey);
			}
			else
			{
				LogHandler::getInstance()->LogToFile(std::string("Trying to execute an undefined LUA function: ") 
																					+ m_FunctionName, 0);		
			}
		}
	}
	catch(const std::exception &error)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception initializing LUA thread: ") 
																					+ error.what(), 0);
	}
}




/***********************************************************
constructor with actor id
***********************************************************/
LuaThreadHandler::LuaThreadHandler(lua_State * mainstate, long actorid, const std::string & FunctionName, 
								   bool inlinefunction, ScriptEnvironmentBase* env, int &ThreadReference)
: m_FunctionName(FunctionName), m_LuaMainState(mainstate), m_started(false)
{
	try
	{
		m_LuaThreadState = lua_newthread(m_LuaMainState);
		m_refKey = luaL_ref(m_LuaMainState, LUA_REGISTRYINDEX);
		ThreadReference = m_refKey;

		if(inlinefunction)
		{
			++m_idgenerator;

			std::stringstream fctname;
			fctname<<"LTH"<<m_idgenerator;

			std::stringstream inlinefct;
			inlinefct<<"function "<<fctname.str()<<"(ScriptId, ActorId, Environment)"<<std::endl;
			inlinefct<<FunctionName;
			inlinefct<<"end"<<std::endl;

			std::string check = inlinefct.str();
			luaL_dostring(m_LuaMainState, inlinefct.str().c_str());

			luabind::resume_function<void>(m_LuaThreadState, fctname.str().c_str(), m_refKey, actorid, env);
			m_started = true;
		}
		else
		{
			// check if function exist
			lua_getglobal(m_LuaMainState, m_FunctionName.c_str());
			if (lua_isfunction(m_LuaMainState, lua_gettop(m_LuaMainState)))
			{
				luabind::resume_function<void>(m_LuaThreadState, m_FunctionName.c_str(), m_refKey, actorid, env);
				m_started = true;
				LogHandler::getInstance()->LogToFile("Script started: "+m_FunctionName, m_refKey);
			}
			else
			{
				LogHandler::getInstance()->LogToFile(std::string("Trying to execute an undefined LUA function: ") 
																					+ m_FunctionName, 0);		
			}
		}
	}
	catch(const std::exception &error)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception initializing LUA thread: ") 
																					+ error.what(), 0);
	}
}


/***********************************************************
destructor
***********************************************************/	
LuaThreadHandler::~LuaThreadHandler(void)
{
	luaL_unref(m_LuaMainState,LUA_REGISTRYINDEX,m_refKey);
}


/***********************************************************
resume thread
return true if thread is finished and should be destructed
***********************************************************/	
bool LuaThreadHandler::ResumeThread()
{
	if(!m_started)
		return true;

	// check if thread already finished
	if(lua_status(m_LuaThreadState) != LUA_YIELD)
	{
		m_started = false;
		return true;
	}

	try
	{
		// if not then resume thread
		luabind::resume<void>(m_LuaThreadState);


		// check thread status after resume
		int status = lua_status(m_LuaThreadState);
		if(status == LUA_YIELD)
			return false;

		// check if error occured and log them
		if(status != 0)
			LogHandler::getInstance()->LogToFile(std::string("Error in lua thread ") + m_FunctionName + std::string(" : ") + lua_tostring(m_LuaThreadState, -1), 0);	
	}
	catch(const std::exception &error)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception resuming LUA thread: ") 
																					+ error.what(), 0);
	}

	m_started = false;
	return true;
}


