#include "ServerLuaHandler.h"

extern "C"
{
    #include "lua.h"
}
#include <luabind/luabind.hpp>


#include <LbaTypes.h>
#include "MapHandler.h"
#include "LogHandler.h"


/***********************************************************
constructor
***********************************************************/
ServerLuaHandler::ServerLuaHandler(const std::string & luafile)
{
	try
	{
		// Create a new lua state
		m_LuaState = lua_open();

		// Connect LuaBind to this lua state
		luabind::open(m_LuaState);

		// Add server interfaces to the state's global scope
		luabind::module(m_LuaState) [
		luabind::class_<LbaNet::ModelInfo>("ModelInfo")
		.def(luabind::constructor<>())
		.def_readwrite("TypeRenderer", &LbaNet::ModelInfo::TypeRenderer)
		.def_readwrite("ModelId", &LbaNet::ModelInfo::ModelId)
		.def_readwrite("ModelName", &LbaNet::ModelInfo::ModelName)
		.def_readwrite("Outfit", &LbaNet::ModelInfo::Outfit)
		.def_readwrite("Weapon", &LbaNet::ModelInfo::Weapon)
		.def_readwrite("Mode", &LbaNet::ModelInfo::Mode)
		.def_readwrite("State", &LbaNet::ModelInfo::State)
		.def_readwrite("UseLight", &LbaNet::ModelInfo::UseLight)
		.def_readwrite("CastShadow", &LbaNet::ModelInfo::CastShadow),


		luabind::class_<LbaNet::PlayerPosition>("PlayerPosition")
		.def(luabind::constructor<>())
		.def_readwrite("MapName", &LbaNet::PlayerPosition::MapName)
		.def_readwrite("X", &LbaNet::PlayerPosition::X)
		.def_readwrite("Y", &LbaNet::PlayerPosition::Y)
		.def_readwrite("Z", &LbaNet::PlayerPosition::Z)
		.def_readwrite("Rotation", &LbaNet::PlayerPosition::Rotation),


		luabind::class_<LbaNet::ObjectPhysicDesc>("ObjectPhysicDesc")
		.def(luabind::constructor<>())
		.def_readwrite("Pos", &LbaNet::ObjectPhysicDesc::Pos)
		.def_readwrite("TypeShape", &LbaNet::ObjectPhysicDesc::TypeShape)
		.def_readwrite("TypePhysO", &LbaNet::ObjectPhysicDesc::TypePhysO)
		.def_readwrite("Density", &LbaNet::ObjectPhysicDesc::Density)
		.def_readwrite("Collidable", &LbaNet::ObjectPhysicDesc::Collidable)
		.def_readwrite("SizeX", &LbaNet::ObjectPhysicDesc::SizeX)
		.def_readwrite("SizeY", &LbaNet::ObjectPhysicDesc::SizeY)
		.def_readwrite("SizeZ", &LbaNet::ObjectPhysicDesc::SizeZ)
		.def_readwrite("Filename", &LbaNet::ObjectPhysicDesc::Filename),


		luabind::class_<LbaNet::LifeManaInfo>("LifeManaInfo")
		.def(luabind::constructor<>())
		.def_readwrite("CurrentLife", &LbaNet::LifeManaInfo::CurrentLife)
		.def_readwrite("MaxLife", &LbaNet::LifeManaInfo::MaxLife)
		.def_readwrite("CurrentMana", &LbaNet::LifeManaInfo::CurrentMana)
		.def_readwrite("MaxMana", &LbaNet::LifeManaInfo::MaxMana),


		luabind::class_<LbaNet::ObjectExtraInfo>("ObjectExtraInfo")
		.def(luabind::constructor<>())
		.def_readwrite("Name", &LbaNet::ObjectExtraInfo::Name)
		.def_readwrite("NameColorR", &LbaNet::ObjectExtraInfo::NameColorR)
		.def_readwrite("NameColorG", &LbaNet::ObjectExtraInfo::NameColorG)
		.def_readwrite("NameColorB", &LbaNet::ObjectExtraInfo::NameColorB),


		luabind::class_<ActorObjectInfo>("ActorObjectInfo")
		.def(luabind::constructor<long, int>())
		.def_readwrite("DisplayDesc", &ActorObjectInfo::DisplayDesc)
		.def_readwrite("PhysicDesc", &ActorObjectInfo::PhysicDesc)
		.def_readwrite("LifeInfo", &ActorObjectInfo::LifeInfo)
		.def_readwrite("ExtraInfo", &ActorObjectInfo::ExtraInfo)
		.def("SetRenderType", &ActorObjectInfo::SetRenderType)
		.def("SetPhysicalShape", &ActorObjectInfo::SetPhysicalShape)
		.def("SetPhysicalActorType", &ActorObjectInfo::SetPhysicalActorType)
		.def("SetModelState", &ActorObjectInfo::SetModelState),

		luabind::class_<MapHandler>("MapHandler")
		.def("AddActorObject", &MapHandler::AddActorObject)
		
		];

		// read lua file
		int error = luaL_dofile(m_LuaState, ("Data/"+luafile).c_str());
		if(error != 0)
		{
			LogHandler::getInstance()->LogToFile(std::string("Error loading lua file: ") + lua_tostring(m_LuaState, -1));
		}
	}
	catch(const std::exception &error)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception initializing LUA for server: ") + error.what(), 0);
	}
}

/***********************************************************
destructor
***********************************************************/	
ServerLuaHandler::~ServerLuaHandler(void)
{
	lua_close(m_LuaState);
}


/***********************************************************
register map to lua global
***********************************************************/
void ServerLuaHandler::RegisterMap(const std::string & mapname, MapHandler * map)
{
	try
	{
		luabind::globals(m_LuaState)["Map_" + mapname] = map;
	}
	catch(const std::exception &error)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception registering map to lua: ") + error.what(), 0);
	}
}

/***********************************************************
call lua function
***********************************************************/
void ServerLuaHandler::CallLua(const std::string & functioname)
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
