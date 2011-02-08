#include "LuaHandlerBase.h"

extern "C"
{
    #include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}
#include <luabind/luabind.hpp>


#include "LogHandler.h"
#include "LuaThreadHandler.h"
#include "ScriptEnvironmentBase.h"


/***********************************************************
constructor
***********************************************************/
LuaHandlerBase::LuaHandlerBase()
{
	try
	{
		// Create a new lua state
		m_LuaState = lua_open();

		// Connect LuaBind to this lua state
		luabind::open(m_LuaState);

		luaL_openlibs(m_LuaState);

	}
	catch(const std::exception &error)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception initializing LUA for base lua: ") + error.what(), 0);
	}
}

/***********************************************************
destructor
***********************************************************/	
LuaHandlerBase::~LuaHandlerBase(void)
{
	// clear running thread before closing main lua state
	m_RunningThreads.clear();
	
	lua_close(m_LuaState);
}


/***********************************************************
load a lua file
***********************************************************/
void LuaHandlerBase::LoadFile(const std::string & luafile)
{
	// read lua file
	int error = luaL_dofile(m_LuaState, ("Data/"+luafile).c_str());
	if(error != 0)
	{
		LogHandler::getInstance()->LogToFile(std::string("Error loading lua file: ") + lua_tostring(m_LuaState, -1));
	}
}


/***********************************************************
call lua function
***********************************************************/
void LuaHandlerBase::CallLua(const std::string & functioname, ScriptEnvironmentBase* env)
{
	try
	{
		if(env)
			luabind::call_function<void>(m_LuaState, functioname.c_str(), env);
		else
			luabind::call_function<void>(m_LuaState, functioname.c_str());
	}
	catch(const std::exception &error)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception calling lua function ") + functioname + std::string(" : ") + error.what() + std::string(" : ") + lua_tostring(m_LuaState, -1), 0);
	}
}



/***********************************************************
start script in a new thread
***********************************************************/
void LuaHandlerBase::StartScript(const std::string & FunctionName, bool inlinefunction)
{
	boost::shared_ptr<LuaThreadHandler> Th(new LuaThreadHandler(m_LuaState, FunctionName, inlinefunction));
	if(Th->IsStarted())
		m_RunningThreads[Th->GetReference()] = Th;
	else
		FailedStartingScript(FunctionName);
}


/***********************************************************
resume yiled thread
***********************************************************/
void LuaHandlerBase::ResumeThread(int ThreadIdx)
{
	// check if thread exist
	std::map<int, boost::shared_ptr<LuaThreadHandler> >::iterator it = m_RunningThreads.find(ThreadIdx);
	if(it != m_RunningThreads.end())
	{
		// run thread and destroy it if finished
		if(it->second->ResumeThread())
		{
			ScriptFinished(it->second->GetScriptName());
			m_RunningThreads.erase(it);
		}
	}
}
