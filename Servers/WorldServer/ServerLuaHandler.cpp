#include "ServerLuaHandler.h"

extern "C"
{
    #include "lua.h"
}
#include <luabind/luabind.hpp>


#include <LbaTypes.h>
#include "MapHandler.h"
#include "LogHandler.h"
#include "Triggers.h"

#ifdef _USE_QT_EDITOR_	
#include "editorhandler.h"
#endif

/***********************************************************
constructor
***********************************************************/
ServerLuaHandler::ServerLuaHandler()
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
		.def_readwrite("ModelId", &LbaNet::ModelInfo::ModelId)
		.def_readwrite("ModelName", &LbaNet::ModelInfo::ModelName)
		.def_readwrite("Outfit", &LbaNet::ModelInfo::Outfit)
		.def_readwrite("Weapon", &LbaNet::ModelInfo::Weapon)
		.def_readwrite("Mode", &LbaNet::ModelInfo::Mode)
		.def_readwrite("State", &LbaNet::ModelInfo::State)
		.def_readwrite("UseLight", &LbaNet::ModelInfo::UseLight)
		.def_readwrite("CastShadow", &LbaNet::ModelInfo::CastShadow)
		.def_readwrite("ColorR", &LbaNet::ModelInfo::ColorR)
		.def_readwrite("ColorG", &LbaNet::ModelInfo::ColorG)
		.def_readwrite("ColorB", &LbaNet::ModelInfo::ColorB)
		.def_readwrite("ColorA", &LbaNet::ModelInfo::ColorA)
		.def_readwrite("TransX", &LbaNet::ModelInfo::TransX)
		.def_readwrite("TransY", &LbaNet::ModelInfo::TransY)
		.def_readwrite("TransZ", &LbaNet::ModelInfo::TransZ)		
		.def_readwrite("ScaleX", &LbaNet::ModelInfo::ScaleX)
		.def_readwrite("ScaleY", &LbaNet::ModelInfo::ScaleY)
		.def_readwrite("ScaleZ", &LbaNet::ModelInfo::ScaleZ)	
		.def_readwrite("RotX", &LbaNet::ModelInfo::RotX)
		.def_readwrite("RotY", &LbaNet::ModelInfo::RotY)
		.def_readwrite("RotZ", &LbaNet::ModelInfo::RotZ),

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
		.def(luabind::constructor<long>())
		.def_readwrite("DisplayDesc", &ActorObjectInfo::DisplayDesc)
		.def_readwrite("PhysicDesc", &ActorObjectInfo::PhysicDesc)
		.def_readwrite("LifeInfo", &ActorObjectInfo::LifeInfo)
		.def_readwrite("ExtraInfo", &ActorObjectInfo::ExtraInfo)
		.def("SetRenderType", &ActorObjectInfo::SetRenderType)
		.def("SetPhysicalShape", &ActorObjectInfo::SetPhysicalShape)
		.def("SetPhysicalActorType", &ActorObjectInfo::SetPhysicalActorType)
		.def("SetModelState", &ActorObjectInfo::SetModelState),

		luabind::class_<ActorHandler, boost::shared_ptr<ActorHandler> >("ActorHandler")
		.def(luabind::constructor<const ActorObjectInfo &>()),

		luabind::class_<ScriptEnvironmentBase>("ScriptEnvironmentBase")
		.def("AddActorObject", &ScriptEnvironmentBase::AddActorObject)
		.def("AddTrigger", &ScriptEnvironmentBase::AddTrigger)
		.def("AddAction", &ScriptEnvironmentBase::AddAction)
		.def("Teleport", &ScriptEnvironmentBase::Teleport),

		luabind::class_<MapHandler, ScriptEnvironmentBase>("MapHandler"),

		#ifdef _USE_QT_EDITOR_	
		luabind::class_<EditorHandler, ScriptEnvironmentBase>("EditorHandler"),
		#endif


		luabind::class_<TriggerInfo>("TriggerInfo")
		.def(luabind::constructor<>())
		.def(luabind::constructor<long, const std::string &, bool, bool, bool>())
		.def_readwrite("id", &TriggerInfo::id)
		.def_readwrite("name", &TriggerInfo::name)
		.def_readwrite("CheckPlayers", &TriggerInfo::CheckPlayers)
		.def_readwrite("CheckNpcs", &TriggerInfo::CheckNpcs)
		.def_readwrite("CheckMovableObjects", &TriggerInfo::CheckMovableObjects),
		

		luabind::class_<TriggerBase, boost::shared_ptr<TriggerBase> >("TriggerBase")
		.def(luabind::constructor<TriggerInfo>())
		.def("SetPosition", &TriggerBase::SetPosition)
		.def("SetAction1", &ZoneTrigger::SetAction1)
		.def("SetAction2", &ZoneTrigger::SetAction2)
		.def("SetAction3", &ZoneTrigger::SetAction3),

		luabind::class_<ZoneTrigger, TriggerBase, boost::shared_ptr<TriggerBase> >("ZoneTrigger")
		.def(luabind::constructor<TriggerInfo, float, float, float, bool>()),

		luabind::class_<ActivationTrigger, TriggerBase, boost::shared_ptr<TriggerBase> >("ActivationTrigger")
		.def(luabind::constructor<TriggerInfo, float, const std::string &, const std::string &>()),

		luabind::class_<ZoneActionTrigger, TriggerBase, boost::shared_ptr<TriggerBase> >("ZoneActionTrigger")
		.def(luabind::constructor<TriggerInfo, float, float, float, const std::string &, const std::string &>()),

		

		luabind::class_<ActionBase, boost::shared_ptr<ActionBase> >("ActionBase")
		.def(luabind::constructor<long, const std::string&>()),

		luabind::class_<TeleportAction, ActionBase, boost::shared_ptr<ActionBase> >("TeleportAction")
		.def(luabind::constructor<long, const std::string&, const std::string &, long>())

		];


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
load a lua file
***********************************************************/
void ServerLuaHandler::LoadFile(const std::string & luafile)
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
void ServerLuaHandler::CallLua(const std::string & functioname, ScriptEnvironmentBase* env)
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
