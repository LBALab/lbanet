#include "LuaThreadHandler.h"
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
LuaThreadHandler::LuaThreadHandler(lua_State * mainstate, const std::string & FunctionName, bool inlinefunction)
: m_FunctionName(FunctionName), m_LuaMainState(mainstate)
{
	try
	{
		m_LuaThreadState = lua_newthread(m_LuaMainState);
		m_refKey = luaL_ref(m_LuaMainState, LUA_REGISTRYINDEX);

		if(inlinefunction)
		{
			++m_idgenerator;

			std::stringstream fctname;
			fctname<<"LTH"<<m_idgenerator;

			std::stringstream inlinefct;
			inlinefct<<"function "<<fctname.str()<<"(ScriptId)"<<std::endl;
			inlinefct<<FunctionName;
			inlinefct<<"end"<<std::endl;

			std::string check = inlinefct.str();
			luaL_dostring(m_LuaMainState, inlinefct.str().c_str());

			luabind::resume_function<void>(m_LuaThreadState, fctname.str().c_str(), m_refKey);

		}
		else
			luabind::resume_function<void>(m_LuaThreadState, m_FunctionName.c_str(), m_refKey);
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
	//lua_close(m_LuaThreadState);
	luaL_unref(m_LuaMainState,LUA_REGISTRYINDEX,m_refKey);
}


/***********************************************************
resume thread
return true if thread is finished and should be destructed
***********************************************************/	
bool LuaThreadHandler::ResumeThread()
{
	// check if thread already finished
	if(lua_status(m_LuaThreadState) != LUA_YIELD)
		return true;

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
		LogHandler::getInstance()->LogToFile(std::string("Exception initializing LUA thread: ") 
																					+ error.what(), 0);
	}

	return true;
}