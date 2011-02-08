#include "ClientLuaHandler.h"

extern "C"
{
    #include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}
#include <luabind/luabind.hpp>

#include <LbaTypes.h>
#include "LogHandler.h"
#include "LbaNetModel.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"


/***********************************************************
constructor
***********************************************************/
ClientLuaHandler::ClientLuaHandler(LbaNetModel * model)
{
	try
	{
		luabind::module(m_LuaState) [

		luabind::class_<LbaVec3>("LbaVec3")
		.def(luabind::constructor<>())
		.def(luabind::constructor<float, float, float>())
		.def(luabind::constructor<LbaVec3>())
		.def_readwrite("x", &LbaVec3::x)
		.def_readwrite("y", &LbaVec3::y)
		.def_readwrite("z", &LbaVec3::z),

		luabind::class_<LbaQuaternion>("LbaQuaternion")
		.def(luabind::constructor<>())
		.def(luabind::constructor<float, float, float, float>())
		.def(luabind::constructor<float, float, float>())
		.def(luabind::constructor<float, LbaVec3>())
		.def_readwrite("X", &LbaQuaternion::X)
		.def_readwrite("Y", &LbaQuaternion::Y)
		.def_readwrite("Z", &LbaQuaternion::Z)
		.def_readwrite("W", &LbaQuaternion::W)	
		.def("AddSingleRotation", &LbaQuaternion::AddSingleRotation)
		.def("GetDirection", &LbaQuaternion::GetDirection)
		.def("GetRotationSingleAngle", &LbaQuaternion::GetRotationSingleAngle)
		.scope
		[
			luabind::def("GetAngleFromVector", &LbaQuaternion::GetAngleFromVector)
		],
		

		luabind::class_<LbaNetModel>("LbaNetModel")
		.def(luabind::constructor<>())
		.def("GetActorPosition", &LbaNetModel::GetActorPosition)
		.def("GetActorRotation", &LbaNetModel::GetActorRotation)
		.def("GetActorRotationQuat", &LbaNetModel::GetActorRotationQuat)
		.def("UpdateActorAnimation", &LbaNetModel::UpdateActorAnimation)
		.def("UpdateActorMode", &LbaNetModel::UpdateActorMode)
		.def("ActorStraightWalkTo", &LbaNetModel::ActorStraightWalkTo, luabind::yield)
		.def("ActorRotate", &LbaNetModel::ActorRotate, luabind::yield)
		.def("ActorAnimate", &LbaNetModel::ActorAnimate, luabind::yield)
		.def("Async_ActorStraightWalkTo", &LbaNetModel::Async_ActorStraightWalkTo)
		.def("Async_ActorRotate", &LbaNetModel::Async_ActorRotate)
		.def("Async_ActorAnimate", &LbaNetModel::Async_ActorAnimate)
		.def("WaitForAsyncScript", &LbaNetModel::WaitForAsyncScript, luabind::yield)
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
}



/***********************************************************
called when failed starting a script
***********************************************************/
void ClientLuaHandler::FailedStartingScript(const std::string & functioname)
{
	// inform server that script is not started
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ScriptExecutionFinishedEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), functioname));
}

/***********************************************************
called when a script has finished
***********************************************************/
void ClientLuaHandler::ScriptFinished(const std::string & functioname)
{
	// inform server that script is finished
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ScriptExecutionFinishedEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), functioname));
}


/***********************************************************
execute lua script given as a string
***********************************************************/
void ClientLuaHandler::ExecuteScriptString( const std::string & ScriptString )
{
	int error = luaL_dostring(m_LuaState, ScriptString.c_str());
	if(error != 0)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception calling executing script string: ") + lua_tostring(m_LuaState, -1));
	}

}
