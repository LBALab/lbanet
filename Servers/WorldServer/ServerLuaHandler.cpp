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
#include "ClientScript.h"
#include "ActionArguments.h"
#include "Conditions.h"


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



		luabind::class_<ConditionBase, boost::shared_ptr<ConditionBase> >("ConditionBase")
		.def(luabind::constructor<>())
		.def("Passed", &ConditionBase::Passed)
		,

		luabind::class_<AlwaysTrueCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("AlwaysTrueCondition")
		.def(luabind::constructor<>()),

		luabind::class_<NegateCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("NegateCondition")
		.def(luabind::constructor<>())
		.def("SetCondition", &NegateCondition::SetCondition)
		.def("GetCondition", &NegateCondition::GetCondition)
		,

		luabind::class_<AndCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("AndCondition")
		.def(luabind::constructor<>())
		.def("SetCondition1", &AndCondition::SetCondition1)
		.def("SetCondition2", &AndCondition::SetCondition2)
		.def("GetCondition1", &AndCondition::GetCondition1)
		.def("GetCondition2", &AndCondition::GetCondition2)
		,


		luabind::class_<OrCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("OrCondition")
		.def(luabind::constructor<>())
		.def("SetCondition1", &OrCondition::SetCondition1)
		.def("SetCondition2", &OrCondition::SetCondition2)
		.def("GetCondition1", &OrCondition::GetCondition1)
		.def("GetCondition2", &OrCondition::GetCondition2)
		,



		luabind::class_<ContainerItemGroupElement>("ContainerItemGroupElement")
		.def(luabind::constructor<long, int, int, float, int>())
		.def_readwrite("Id", &ContainerItemGroupElement::Id)
		.def_readwrite("Min", &ContainerItemGroupElement::Min)
		.def_readwrite("Max", &ContainerItemGroupElement::Max)
		.def_readwrite("Probability", &ContainerItemGroupElement::Probability)
		.def_readwrite("Group", &ContainerItemGroupElement::Group),	


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
		.def_readwrite("RotZ", &LbaNet::ModelInfo::RotZ)
		.def_readwrite("SkinColor", &LbaNet::ModelInfo::SkinColor)
		.def_readwrite("EyesColor", &LbaNet::ModelInfo::EyesColor)		
		.def_readwrite("HairColor", &LbaNet::ModelInfo::HairColor)
		.def_readwrite("OutfitColor", &LbaNet::ModelInfo::OutfitColor)
		.def_readwrite("WeaponColor", &LbaNet::ModelInfo::WeaponColor)		
		.def_readwrite("MountSkinColor", &LbaNet::ModelInfo::MountSkinColor)
		.def_readwrite("MountHairColor", &LbaNet::ModelInfo::MountHairColor)			
		,


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
		.def_readwrite("Condition", &ActorObjectInfo::Condition)
		.def("SetRenderType", &ActorObjectInfo::SetRenderType)
		.def("SetPhysicalShape", &ActorObjectInfo::SetPhysicalShape)
		.def("SetPhysicalActorType", &ActorObjectInfo::SetPhysicalActorType)
		.def("SetModelState", &ActorObjectInfo::SetModelState)
		.def("AddColorSwap", &ActorObjectInfo::AddColorSwap)
		,

		luabind::class_<ActorHandler, boost::shared_ptr<ActorHandler> >("ActorHandler")
		.def(luabind::constructor<const ActorObjectInfo &>()),

		luabind::class_<ScriptEnvironmentBase>("ScriptEnvironmentBase")
		.def("AddActorObject", &ScriptEnvironmentBase::AddActorObject)
		.def("AddTrigger", &ScriptEnvironmentBase::AddTrigger)
		.def("Teleport", &ScriptEnvironmentBase::Teleport)
		.def("ExecuteClientScript", &ScriptEnvironmentBase::ExecuteClientScript)
		.def("DisplayTextAction", &ScriptEnvironmentBase::DisplayTxtAction)
		.def("SendErrorMessage", &ScriptEnvironmentBase::SendErrorMessage)
		.def("OpenContainer", &ScriptEnvironmentBase::OpenContainer)
		,

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

		luabind::class_<TimerTrigger, TriggerBase, boost::shared_ptr<TriggerBase> >("TimerTrigger")
		.def(luabind::constructor<TriggerInfo, long>()),


		luabind::class_<ActionArgumentBase>("ActionArgumentBase")
		.def(luabind::constructor<ActionArgumentBase>()),

		luabind::class_<OffsetArgument, ActionArgumentBase>("OffsetArgument")
		.def(luabind::constructor<float, float, float>())
		.def_readwrite("OffsetX", &OffsetArgument::_offsetX)
		.def_readwrite("OffsetY", &OffsetArgument::_offsetY)
		.def_readwrite("OffsetZ", &OffsetArgument::_offsetZ),



		luabind::class_<ActionBase, boost::shared_ptr<ActionBase> >("ActionBase")
		.def(luabind::constructor<>())
		.def("Execute", &ActionBase::Execute),

		luabind::class_<TeleportAction, ActionBase, boost::shared_ptr<ActionBase> >("TeleportAction")
		.def(luabind::constructor<>())
		.def("GetMapName", &TeleportAction::GetMapName)
		.def("SetMapName", &TeleportAction::SetMapName)	
		.def("GetSpawning", &TeleportAction::GetSpawning)
		.def("SetSpawning", &TeleportAction::SetSpawning),

		luabind::class_<ClientScriptAction, ActionBase, boost::shared_ptr<ActionBase> >("ClientScriptAction")
		.def(luabind::constructor<>())
		.def("GetScript", &ClientScriptAction::GetScript)
		.def("SetScript", &ClientScriptAction::SetScript),

		luabind::class_<CustomAction, ActionBase, boost::shared_ptr<ActionBase> >("CustomAction")
		.def(luabind::constructor<>())
		.def("GetLuaFunctionName", &CustomAction::GetLuaFunctionName)
		.def("SetLuaFunctionName", &CustomAction::SetLuaFunctionName),

		luabind::class_<DisplayTextAction, ActionBase, boost::shared_ptr<ActionBase> >("DisplayTextAction")
		.def(luabind::constructor<>())
		.def("GetTextId", &DisplayTextAction::GetTextId)
		.def("SetTextId", &DisplayTextAction::SetTextId),

		luabind::class_<ConditionalAction, ActionBase, boost::shared_ptr<ActionBase> >("ConditionalAction")
		.def(luabind::constructor<>())
		.def("SetCondition", &ConditionalAction::SetCondition)
		.def("GetCondition", &ConditionalAction::GetCondition)
		.def("SetActionTrue", &ConditionalAction::SetActionTrue)
		.def("SetActionFalse", &ConditionalAction::SetActionFalse)
		.def("GetActionTrue", &ConditionalAction::GetActionTrue)
		.def("GetActionFalse", &ConditionalAction::GetActionFalse),

		luabind::class_<ContainerSharedInfo, boost::shared_ptr<ContainerSharedInfo> >("ContainerSharedInfo")
		.def_readwrite("OpeningClient", &ContainerSharedInfo::OpeningClient)
		.def_readwrite("ContainerItems", &ContainerSharedInfo::ContainerItems),


		luabind::class_<OpenContainerAction, ActionBase, boost::shared_ptr<ActionBase> >("OpenContainerAction")
		.def(luabind::constructor<>())
		.def("GetTimeToReset", &OpenContainerAction::GetTimeToReset)
		.def("SetTimeToReset", &OpenContainerAction::SetTimeToReset)
		.def("AddItem", &OpenContainerAction::AddItem),


		luabind::class_<ClientScriptBase, boost::shared_ptr<ClientScriptBase> >("ClientScriptBase")
		.def(luabind::constructor<>())
		.def("Execute", &ClientScriptBase::Execute),

		luabind::class_<GoUpLadderScript, ClientScriptBase, boost::shared_ptr<ClientScriptBase> >("GoUpLadderScript")
		.def(luabind::constructor<>())
		.def("GetLadderPositionX", &GoUpLadderScript::GetLadderPositionX)
		.def("GetLadderPositionY", &GoUpLadderScript::GetLadderPositionY)
		.def("GetLadderPositionZ", &GoUpLadderScript::GetLadderPositionZ)
		.def("SetLadderPositionX", &GoUpLadderScript::SetLadderPositionX)
		.def("SetLadderPositionY", &GoUpLadderScript::SetLadderPositionY)
		.def("SetLadderPositionZ", &GoUpLadderScript::SetLadderPositionZ)
		.def("GetLadderHeight", &GoUpLadderScript::GetLadderHeight)
		.def("SetLadderHeight", &GoUpLadderScript::SetLadderHeight)
		.def("GetLadderDirection", &GoUpLadderScript::GetLadderDirection)
		.def("SetLadderDirection", &GoUpLadderScript::SetLadderDirection),

		luabind::class_<TakeExitUpScript, ClientScriptBase, boost::shared_ptr<ClientScriptBase> >("TakeExitUpScript")
		.def(luabind::constructor<>())
		.def("GetExitPositionX", &TakeExitUpScript::GetExitPositionX)
		.def("GetExitPositionY", &TakeExitUpScript::GetExitPositionY)
		.def("GetExitPositionZ", &TakeExitUpScript::GetExitPositionZ)
		.def("SetExitPositionX", &TakeExitUpScript::SetExitPositionX)
		.def("SetExitPositionY", &TakeExitUpScript::SetExitPositionY)
		.def("SetExitPositionZ", &TakeExitUpScript::SetExitPositionZ)
		.def("GetExitDirection", &TakeExitUpScript::GetExitDirection)
		.def("SetExitDirection", &TakeExitUpScript::SetExitDirection),

		luabind::class_<TakeExitDownScript, ClientScriptBase, boost::shared_ptr<ClientScriptBase> >("TakeExitDownScript")
		.def(luabind::constructor<>())
		.def("GetExitPositionX", &TakeExitDownScript::GetExitPositionX)
		.def("GetExitPositionY", &TakeExitDownScript::GetExitPositionY)
		.def("GetExitPositionZ", &TakeExitDownScript::GetExitPositionZ)
		.def("SetExitPositionX", &TakeExitDownScript::SetExitPositionX)
		.def("SetExitPositionY", &TakeExitDownScript::SetExitPositionY)
		.def("SetExitPositionZ", &TakeExitDownScript::SetExitPositionZ)
		.def("GetExitDirection", &TakeExitDownScript::GetExitDirection)
		.def("SetExitDirection", &TakeExitDownScript::SetExitDirection),

		luabind::class_<CustomScript, ClientScriptBase, boost::shared_ptr<ClientScriptBase> >("CustomScript")
		.def(luabind::constructor<>())
		.def("GetLuaFunctionName", &CustomScript::GetLuaFunctionName)
		.def("SetLuaFunctionName", &CustomScript::SetLuaFunctionName)
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



/***********************************************************
call lua function
***********************************************************/
void ServerLuaHandler::ExecuteCustomAction(int ObjectType, long ObjectId,
											const std::string & FunctionName,
											ActionArgumentBase * args,
											ScriptEnvironmentBase* env)
{
	try
	{
		luabind::call_function<void>(m_LuaState, FunctionName.c_str(), ObjectType, ObjectId, args, env);
	}
	catch(const std::exception &error)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception calling lua function ") + FunctionName + std::string(" : ") + error.what() + std::string(" : ") + lua_tostring(m_LuaState, -1), 0);
	}
}