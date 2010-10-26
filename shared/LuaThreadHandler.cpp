#include "LuaThreadHandler.h"
#include "LogHandler.h"

extern "C"
{
    #include "lua.h"
}
#include <luabind/luabind.hpp>



/***********************************************************
constructor
***********************************************************/
LuaThreadHandler::LuaThreadHandler(lua_State * mainstate, const std::string & FunctionName)
: m_FunctionName(FunctionName), m_LuaMainState(mainstate)
{
	try
	{
		m_LuaThreadState = lua_newthread(m_LuaMainState);
		m_refKey = luaL_ref(m_LuaMainState, LUA_REGISTRYINDEX);

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
	luaL_unref(m_LuaMainState,LUA_REGISTRYINDEX,m_refKey);
	lua_close(m_LuaThreadState);
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