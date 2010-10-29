#include "ClientLuaHandler.h"

extern "C"
{
    #include "lua.h"
}
#include <luabind/luabind.hpp>


#include <LbaTypes.h>
#include "LogHandler.h"
#include "LbaNetModel.h"
#include "LuaThreadHandler.h"

#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"


/***********************************************************
constructor
***********************************************************/
ClientLuaHandler::ClientLuaHandler(LbaNetModel * model)
{
	try
	{
		// Create a new lua state
		m_LuaState = lua_open();

		// Connect LuaBind to this lua state
		luabind::open(m_LuaState);

		luabind::module(m_LuaState) [
		luabind::class_<LbaNetModel>("LbaNetModel")
		.def(luabind::constructor<>())
		.def("ActorStraightWalkTo", &LbaNetModel::ActorStraightWalkTo, luabind::yield)
		.def("ActorRotate", &LbaNetModel::ActorRotate, luabind::yield)
		.def("ActorAnimate", &LbaNetModel::ActorAnimate, luabind::yield)
		];

		// register the lbanetmodel as global for the whole script
		luabind::globals(m_LuaState)["Model"] = model;

	}
	catch(const std::exception &error)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception initializing LUA for client: ") + error.what(), 0);
	}
}

/***********************************************************
destructor
***********************************************************/	
ClientLuaHandler::~ClientLuaHandler(void)
{
	// clear running thread before closing main lua state
	m_RunningThreads.clear();
	
	lua_close(m_LuaState);
}


/***********************************************************
load a lua file
***********************************************************/
void ClientLuaHandler::LoadFile(const std::string & luafile)
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
void ClientLuaHandler::CallLua(const std::string & functioname)
{
	try
	{
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
void ClientLuaHandler::StartScript(const std::string & FunctionName)
{
	boost::shared_ptr<LuaThreadHandler> Th(new LuaThreadHandler(m_LuaState, FunctionName));
	m_RunningThreads[Th->GetReference()] = Th;
}


/***********************************************************
resume yiled thread
***********************************************************/
void ClientLuaHandler::ResumeThread(int ThreadIdx)
{
	// check if thread exist
	std::map<int, boost::shared_ptr<LuaThreadHandler> >::iterator it = m_RunningThreads.find(ThreadIdx);
	if(it != m_RunningThreads.end())
	{
		// run thread and destroy it if finished
		if(it->second->ResumeThread())
		{
			// inform server that script is finished
			EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ScriptExecutionFinishedEvent(
				SynchronizedTimeHandler::GetCurrentTimeDouble(), it->second->GetScriptName()));

			m_RunningThreads.erase(it);
		}
	}
}