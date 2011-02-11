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
#include "ScriptEnvironmentBase.h"


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
		// Add server interfaces to the state's global scope
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
		.def_readwrite("MaxMana", &LbaNet::LifeManaInfo::MaxMana)
		.def_readwrite("Display", &LbaNet::LifeManaInfo::Display),


		luabind::class_<LbaNet::ObjectExtraInfo>("ObjectExtraInfo")
		.def(luabind::constructor<>())
		.def_readwrite("Name", &LbaNet::ObjectExtraInfo::Name)
		.def_readwrite("NameColorR", &LbaNet::ObjectExtraInfo::NameColorR)
		.def_readwrite("NameColorG", &LbaNet::ObjectExtraInfo::NameColorG)
		.def_readwrite("NameColorB", &LbaNet::ObjectExtraInfo::NameColorB)
		.def_readwrite("Display", &LbaNet::ObjectExtraInfo::Display),


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


		luabind::class_<ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ActorScriptPartBase")
		.def(luabind::constructor<>()),

		luabind::class_<ActorScriptPart_GoTo, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPGoTo")
		.def(luabind::constructor<float, float, float, float>()),

		luabind::class_<ActorScriptPart_WalkStraightTo, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPWalkStraightTo")
		.def(luabind::constructor<float, float, float>()),

		luabind::class_<ActorScriptPart_PlayAnimation, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPPlayAnimation")
		.def(luabind::constructor<bool>()),

		luabind::class_<ActorScriptPart_Rotate, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPRotate")
		.def(luabind::constructor<float, float, bool>()),

		luabind::class_<ActorScriptPart_ChangeAnimation, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPChangeAnimation")
		.def(luabind::constructor<const std::string &>()),

		luabind::class_<ActorScriptPart_ChangeModel, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPChangeModel")
		.def(luabind::constructor<const std::string &>()),

		luabind::class_<ActorScriptPart_ChangeOutfit, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPChangeOutfit")
		.def(luabind::constructor<const std::string &>()),

		luabind::class_<ActorScriptPart_ChangeWeapon, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPChangeWeapon")
		.def(luabind::constructor<const std::string &>()),

		luabind::class_<ActorScriptPart_ChangeMode, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPChangeMode")
		.def(luabind::constructor<const std::string &>()),

		luabind::class_<ActorScriptPart_WaitForSignal, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPWaitForSignal")
		.def(luabind::constructor<int>()),

		luabind::class_<ActorScriptPart_SendSignal, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPSendSignal")
		.def(luabind::constructor<int, long>()),

		luabind::class_<ActorScriptPart_TeleportTo, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPTeleportTo")
		.def(luabind::constructor<float, float, float>()),

		luabind::class_<ActorScriptPart_Custom, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPCustom")
		.def(luabind::constructor<const std::string &>()),

		luabind::class_<ActorScriptPart_SetRotation, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPSetRotation")
		.def(luabind::constructor<float>()),

		luabind::class_<ActorScriptPart_RotateFromPoint, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPRotateFromPoint")
		.def(luabind::constructor<float, float, float, float, float>()),

		luabind::class_<ActorScriptPart_FollowWaypoint, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPFollowWaypoint")
		.def(luabind::constructor<float, float, float>()),

		luabind::class_<ActorScriptPart_StartWaypoint, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPStartWaypoint")
		.def(luabind::constructor<float, float, float, bool>()),

		

		luabind::class_<ActorHandler, boost::shared_ptr<ActorHandler> >("ActorHandler")
		.def(luabind::constructor<const ActorObjectInfo &>())
		.def("AddScriptPart", &ActorHandler::AddScriptPart)
		.def("StartWaypoint", &ActorHandler::StartWaypoint)
		.def("AddWaypoint", &ActorHandler::AddWaypoint),


		luabind::class_<ScriptEnvironmentBase>("ScriptEnvironmentBase")
		.def("AddActorObject", &ScriptEnvironmentBase::AddActorObject)
		.def("AddTrigger", &ScriptEnvironmentBase::AddTrigger)
		.def("Teleport", &ScriptEnvironmentBase::Teleport)
		.def("ExecuteClientScript", &ScriptEnvironmentBase::ExecuteClientScript)
		.def("DisplayTextAction", &ScriptEnvironmentBase::DisplayTxtAction)
		.def("SendErrorMessage", &ScriptEnvironmentBase::SendErrorMessage)
		.def("OpenContainer", &ScriptEnvironmentBase::OpenContainer)
		.def("GetActorPosition", &ScriptEnvironmentBase::GetActorPosition)
		.def("GetActorRotation", &ScriptEnvironmentBase::GetActorRotation)
		.def("GetActorRotationQuat", &ScriptEnvironmentBase::GetActorRotationQuat)
		.def("UpdateActorAnimation", &ScriptEnvironmentBase::UpdateActorAnimation)
		.def("UpdateActorMode", &ScriptEnvironmentBase::UpdateActorMode)
		.def("ActorStraightWalkTo", &ScriptEnvironmentBase::ActorStraightWalkTo, luabind::yield)
		.def("ActorRotate", &ScriptEnvironmentBase::ActorRotate, luabind::yield)
		.def("ActorAnimate", &ScriptEnvironmentBase::ActorAnimate, luabind::yield)
		.def("Async_ActorStraightWalkTo", &ScriptEnvironmentBase::Async_ActorStraightWalkTo)
		.def("Async_ActorRotate", &ScriptEnvironmentBase::Async_ActorRotate)
		.def("Async_ActorAnimate", &ScriptEnvironmentBase::Async_ActorAnimate)
		.def("WaitForAsyncScript", &ScriptEnvironmentBase::WaitForAsyncScript, luabind::yield)
		.def("ReserveActor", &ScriptEnvironmentBase::ReserveActor)
		.def("ActorGoTo", &ScriptEnvironmentBase::ActorGoTo, luabind::yield)
		.def("UpdateActorModel", &ScriptEnvironmentBase::UpdateActorModel)
		.def("UpdateActorOutfit", &ScriptEnvironmentBase::UpdateActorOutfit)
		.def("UpdateActorWeapon", &ScriptEnvironmentBase::UpdateActorWeapon)
		.def("ActorWaitForSignal", &ScriptEnvironmentBase::ActorWaitForSignal, luabind::yield)
		.def("SendSignalToActor", &ScriptEnvironmentBase::SendSignalToActor)
		.def("TeleportActorTo", &ScriptEnvironmentBase::TeleportActorTo)
		.def("Async_ActorGoTo", &ScriptEnvironmentBase::Async_ActorGoTo)
		.def("Async_WaitForSignal", &ScriptEnvironmentBase::Async_WaitForSignal)
		.def("WaitOneCycle", &ScriptEnvironmentBase::WaitOneCycle, luabind::yield)
		.def("SetActorRotation", &ScriptEnvironmentBase::SetActorRotation)
		.def("ActorRotateFromPoint", &ScriptEnvironmentBase::ActorRotateFromPoint, luabind::yield)
		.def("ActorFollowWaypoint", &ScriptEnvironmentBase::ActorFollowWaypoint, luabind::yield)
		.def("Async_ActorRotateFromPoint", &ScriptEnvironmentBase::Async_ActorRotateFromPoint)
		.def("Async_ActorFollowWaypoint", &ScriptEnvironmentBase::Async_ActorFollowWaypoint),


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
}


