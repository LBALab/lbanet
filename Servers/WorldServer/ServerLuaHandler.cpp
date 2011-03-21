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
#include "DoorHandler.h"
#include "DialogPart.h"
#include "NpcHandler.h"
#include "Quest.h"
#include "Teleport.h"
#include "SharedDataHandler.h"
#include "InventoryItemHandler.h"
#include "Spawn.h"

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
		.def("GetTextid", &ConditionBase::GetTextid)
		.def("SetTextid", &ConditionBase::SetTextid),

		luabind::class_<AlwaysTrueCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("AlwaysTrueCondition")
		.def(luabind::constructor<>()),

		luabind::class_<NegateCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("NegateCondition")
		.def(luabind::constructor<>())
		.def("SetCondition", &NegateCondition::SetCondition)
		.def("GetCondition", &NegateCondition::GetCondition),

		luabind::class_<AndCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("AndCondition")
		.def(luabind::constructor<>())
		.def("SetCondition1", &AndCondition::SetCondition1)
		.def("SetCondition2", &AndCondition::SetCondition2)
		.def("GetCondition1", &AndCondition::GetCondition1)
		.def("GetCondition2", &AndCondition::GetCondition2),


		luabind::class_<OrCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("OrCondition")
		.def(luabind::constructor<>())
		.def("SetCondition1", &OrCondition::SetCondition1)
		.def("SetCondition2", &OrCondition::SetCondition2)
		.def("GetCondition1", &OrCondition::GetCondition1)
		.def("GetCondition2", &OrCondition::GetCondition2),

		luabind::class_<ItemInInventoryCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("ItemInInventoryCondition")
		.def(luabind::constructor<>())
		.def("GetItemId", &ItemInInventoryCondition::GetItemId)
		.def("SetItemId", &ItemInInventoryCondition::SetItemId)
		.def("GetItemNumber", &ItemInInventoryCondition::GetItemNumber)
		.def("SetItemNumber", &ItemInInventoryCondition::SetItemNumber),

		luabind::class_<QuestStartedCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("QuestStartedCondition")
		.def(luabind::constructor<>())
		.def("GetQuestId", &QuestStartedCondition::GetQuestId)
		.def("SetQuestId", &QuestStartedCondition::SetQuestId),

		luabind::class_<QuestFinishedCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("QuestFinishedCondition")
		.def(luabind::constructor<>())
		.def("GetQuestId", &QuestFinishedCondition::GetQuestId)
		.def("SetQuestId", &QuestFinishedCondition::SetQuestId),

		luabind::class_<ChapterStartedCondition, ConditionBase, boost::shared_ptr<ConditionBase> >("ChapterStartedCondition")
		.def(luabind::constructor<>())
		.def("GetChapter", &ChapterStartedCondition::GetChapter)
		.def("SetChapter", &ChapterStartedCondition::SetChapter),



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
		.def_readwrite("UseBillboard", &LbaNet::ModelInfo::UseBillboard)
		.def_readwrite("UseTransparentMaterial", &LbaNet::ModelInfo::UseTransparentMaterial)
		.def_readwrite("MatAlpha", &LbaNet::ModelInfo::MatAlpha)
		.def_readwrite("ColorMaterialType", &LbaNet::ModelInfo::ColorMaterialType)
		.def_readwrite("MatAmbientColorR", &LbaNet::ModelInfo::MatAmbientColorR)
		.def_readwrite("MatAmbientColorG", &LbaNet::ModelInfo::MatAmbientColorG)
		.def_readwrite("MatAmbientColorB", &LbaNet::ModelInfo::MatAmbientColorB)
		.def_readwrite("MatAmbientColorA", &LbaNet::ModelInfo::MatAmbientColorA)
		.def_readwrite("MatDiffuseColorR", &LbaNet::ModelInfo::MatDiffuseColorR)
		.def_readwrite("MatDiffuseColorG", &LbaNet::ModelInfo::MatDiffuseColorG)
		.def_readwrite("MatDiffuseColorB", &LbaNet::ModelInfo::MatDiffuseColorB)
		.def_readwrite("MatDiffuseColorA", &LbaNet::ModelInfo::MatDiffuseColorA)
		.def_readwrite("MatSpecularColorR", &LbaNet::ModelInfo::MatSpecularColorR)
		.def_readwrite("MatSpecularColorG", &LbaNet::ModelInfo::MatSpecularColorG)
		.def_readwrite("MatSpecularColorB", &LbaNet::ModelInfo::MatSpecularColorB)
		.def_readwrite("MatSpecularColorA", &LbaNet::ModelInfo::MatSpecularColorA)
		.def_readwrite("MatEmissionColorR", &LbaNet::ModelInfo::MatEmissionColorR)
		.def_readwrite("MatEmissionColorG", &LbaNet::ModelInfo::MatEmissionColorG)
		.def_readwrite("MatEmissionColorB", &LbaNet::ModelInfo::MatEmissionColorB)
		.def_readwrite("MatEmissionColorA", &LbaNet::ModelInfo::MatEmissionColorA)
		.def_readwrite("MatShininess", &LbaNet::ModelInfo::MatShininess),


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
		.def_readwrite("Filename", &LbaNet::ObjectPhysicDesc::Filename)
		.def_readwrite("AllowFreeMove", &LbaNet::ObjectPhysicDesc::AllowFreeMove)
		.def_readwrite("Bounciness", &LbaNet::ObjectPhysicDesc::Bounciness)
		.def_readwrite("StaticFriction", &LbaNet::ObjectPhysicDesc::StaticFriction)
		.def_readwrite("DynamicFriction", &LbaNet::ObjectPhysicDesc::DynamicFriction),


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

		luabind::class_<ActorScriptPart_ShowHide, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPShowHide")
		.def(luabind::constructor<bool>()),

		luabind::class_<ActorScriptPart_AttachToActor, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPAttachToActor")
		.def(luabind::constructor<int, long>()),

		luabind::class_<ActorScriptPart_DetachFromActor, ActorScriptPartBase, boost::shared_ptr<ActorScriptPartBase> >("ASPDetachFromActor")
		.def(luabind::constructor<long>()),


		luabind::class_<ActorHandler, boost::shared_ptr<ActorHandler> >("ActorHandler")
		.def(luabind::constructor<const ActorObjectInfo &>())
		.def("AddScriptPart", &ActorHandler::AddScriptPart)
		.def("StartWaypoint", &ActorHandler::StartWaypoint)
		.def("AddWaypoint", &ActorHandler::AddWaypoint),

		luabind::class_<DoorHandler, ActorHandler, boost::shared_ptr<ActorHandler> >("DoorHandler")
		.def(luabind::constructor<const ActorObjectInfo &, int, int, float, float, bool>()),

		luabind::class_<NPCHandler, ActorHandler, boost::shared_ptr<ActorHandler> >("NPCHandler")
		.def(luabind::constructor<const ActorObjectInfo &>())
		.def("GetRootDialog", &NPCHandler::GetRootDialog)
		.def("SetRootDialog", &NPCHandler::SetRootDialog)
		.def("GetSimpleDialog", &NPCHandler::GetSimpleDialog)
		.def("SetSimpleDialog", &NPCHandler::SetSimpleDialog)
		.def("GetNpcName", &NPCHandler::GetNpcName)
		.def("SetNpcName", &NPCHandler::SetNpcName)
		.def("GetAggresive", &NPCHandler::GetAggresive)
		.def("SetAggresive", &NPCHandler::SetAggresive)
		.def("GetLife", &NPCHandler::GetLife)
		.def("SetLife", &NPCHandler::SetLife)
		.def("GetMana", &NPCHandler::GetMana)
		.def("SetMana", &NPCHandler::SetMana)
		.def("GetArmor", &NPCHandler::GetArmor)
		.def("SetArmor", &NPCHandler::SetArmor)
		.def("GetWeapon1Power", &NPCHandler::GetWeapon1Power)
		.def("SetWeapon1Power", &NPCHandler::SetWeapon1Power)
		.def("GetWeapon2Power", &NPCHandler::GetWeapon2Power)
		.def("SetWeapon2Power", &NPCHandler::SetWeapon2Power)
		.def("GetAttackActiDist", &NPCHandler::GetAttackActiDist)
		.def("SetAttackActiDist", &NPCHandler::SetAttackActiDist)
		.def("GetAttackActiDistDiscrete", &NPCHandler::GetAttackActiDistDiscrete)
		.def("SetAttackActiDistDiscrete", &NPCHandler::SetAttackActiDistDiscrete)
		.def("GetAttackActiDistHidden", &NPCHandler::GetAttackActiDistHidden)
		.def("SetAttackActiDistHidden", &NPCHandler::SetAttackActiDistHidden)
		.def("GetAttackStopDist", &NPCHandler::GetAttackStopDist)
		.def("SetAttackStopDist", &NPCHandler::SetAttackStopDist)
		.def("GetRespawnTimeInSec", &NPCHandler::GetRespawnTimeInSec)
		.def("SetRespawnTimeInSec", &NPCHandler::SetRespawnTimeInSec)
		.def("GetAttackActivationCondition", &NPCHandler::GetAttackActivationCondition)
		.def("SetAttackActivationCondition", &NPCHandler::SetAttackActivationCondition)
		.def("GetActionOnAttackActivation", &NPCHandler::GetActionOnAttackActivation)
		.def("SetActionOnAttackActivation", &NPCHandler::SetActionOnAttackActivation)
		.def("AddGivenItem", &NPCHandler::AddGivenItem),



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
		.def("Async_ActorFollowWaypoint", &ScriptEnvironmentBase::Async_ActorFollowWaypoint)
		.def("ActorShowHide", &ScriptEnvironmentBase::ActorShowHide)
		.def("AddOrRemoveItem", &ScriptEnvironmentBase::AddOrRemoveItem)
		.def("HurtActor", &ScriptEnvironmentBase::HurtActor)
		.def("KillActor", &ScriptEnvironmentBase::KillActor)
		.def("SwitchActorModel", &ScriptEnvironmentBase::SwitchActorModel)
		.def("RevertActorModel", &ScriptEnvironmentBase::RevertActorModel)
		.def("StartDialog", &ScriptEnvironmentBase::StartDialog)
		.def("NpcUntargetPlayer", &ScriptEnvironmentBase::NpcUntargetPlayer)
		.def("StartQuest", &ScriptEnvironmentBase::StartQuest)
		.def("TriggerQuestEnd", &ScriptEnvironmentBase::TriggerQuestEnd)
		.def("QuestStarted", &ScriptEnvironmentBase::QuestStarted)
		.def("QuestFinished", &ScriptEnvironmentBase::QuestFinished)
		.def("ChapterStarted", &ScriptEnvironmentBase::ChapterStarted)
		.def("OpenShop", &ScriptEnvironmentBase::OpenShop)
		.def("AddSpawn", &ScriptEnvironmentBase::AddSpawn)
		.def("OpenMailbox", &ScriptEnvironmentBase::OpenMailbox)
		.def("AttachActor", &ScriptEnvironmentBase::AttachActor)
		.def("DettachActor", &ScriptEnvironmentBase::DettachActor),


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
		.def("SetAction1", &TriggerBase::SetAction1)
		.def("SetAction2", &TriggerBase::SetAction2)
		.def("SetAction3", &TriggerBase::SetAction3),

		luabind::class_<ZoneTrigger, TriggerBase, boost::shared_ptr<TriggerBase> >("ZoneTrigger")
		.def(luabind::constructor<TriggerInfo, float, float, float, bool>())
		.def("SetStayUpdateFrequency", &ZoneTrigger::SetStayUpdateFrequency)
		.def("GetStayUpdateFrequency", &ZoneTrigger::GetStayUpdateFrequency)
		.def("SetActivateOnJump", &ZoneTrigger::SetActivateOnJump)
		.def("GetActivateOnJump", &ZoneTrigger::GetActivateOnJump),

		luabind::class_<ActivationTrigger, TriggerBase, boost::shared_ptr<TriggerBase> >("ActivationTrigger")
		.def(luabind::constructor<TriggerInfo, float, const std::string &, const std::string &>())
		.def("GetPlayAnimation", &ActivationTrigger::GetPlayAnimation)
		.def("SetPlayAnimation", &ActivationTrigger::SetPlayAnimation),

		luabind::class_<ZoneActionTrigger, TriggerBase, boost::shared_ptr<TriggerBase> >("ZoneActionTrigger")
		.def(luabind::constructor<TriggerInfo, float, float, float, const std::string &, const std::string &>())
		.def("GetPlayAnimation", &ZoneActionTrigger::GetPlayAnimation)
		.def("SetPlayAnimation", &ZoneActionTrigger::SetPlayAnimation),

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

		luabind::class_<SendSignalAction, ActionBase, boost::shared_ptr<ActionBase> >("SendSignalAction")
		.def(luabind::constructor<>())
		.def("GetActorId", &SendSignalAction::GetActorId)
		.def("SetActorId", &SendSignalAction::SetActorId)
		.def("GetSignal", &SendSignalAction::GetSignal)
		.def("SetSignal", &SendSignalAction::SetSignal),

		luabind::class_<OpenDoorAction, SendSignalAction, boost::shared_ptr<ActionBase> >("OpenDoorAction")
		.def(luabind::constructor<>()),

		luabind::class_<CloseDoorAction, SendSignalAction, boost::shared_ptr<ActionBase> >("CloseDoorAction")
		.def(luabind::constructor<>()),

		luabind::class_<AddRemoveItemAction, ActionBase, boost::shared_ptr<ActionBase> >("AddRemoveItemAction")
		.def(luabind::constructor<>())
		.def("GetItemId", &AddRemoveItemAction::GetItemId)
		.def("SetItemId", &AddRemoveItemAction::SetItemId)
		.def("GetNumber", &AddRemoveItemAction::GetNumber)
		.def("SetNumber", &AddRemoveItemAction::SetNumber)
		.def("GetInformClientType", &AddRemoveItemAction::GetInformClientType)
		.def("SetInformClientType", &AddRemoveItemAction::SetInformClientType),

		luabind::class_<HurtAction, ActionBase, boost::shared_ptr<ActionBase> >("HurtAction")
		.def(luabind::constructor<>())
		.def("GetHurtValue", &HurtAction::GetHurtValue)
		.def("SetHurtValue", &HurtAction::SetHurtValue)
		.def("HurtLife", &HurtAction::HurtLife)
		.def("HurtLifeOrMana", &HurtAction::HurtLifeOrMana)
		.def("GetPlayedAnimation", &HurtAction::GetPlayedAnimation)
		.def("SetPlayedAnimation", &HurtAction::SetPlayedAnimation),

		luabind::class_<KillAction, ActionBase, boost::shared_ptr<ActionBase> >("KillAction")
		.def(luabind::constructor<>()),

		luabind::class_<MultiAction, ActionBase, boost::shared_ptr<ActionBase> >("MultiAction")
		.def(luabind::constructor<>())
		.def("AddAction", &MultiAction::AddAction)
		.def("RemoveAction", &MultiAction::RemoveAction),

		luabind::class_<SwitchAction, ActionBase, boost::shared_ptr<ActionBase> >("SwitchAction")
		.def(luabind::constructor<>())
		.def("GetActorId", &SwitchAction::GetActorId)
		.def("SetActorId", &SwitchAction::SetActorId)
		.def("GetSwitchModel", &SwitchAction::GetSwitchModel)
		.def("SetSwitchModel", &SwitchAction::SetSwitchModel)
		.def("SetActionTrue", &SwitchAction::SetActionTrue)
		.def("SetActionFalse", &SwitchAction::SetActionFalse)
		.def("GetActionTrue", &SwitchAction::GetActionTrue)
		.def("GetActionFalse", &SwitchAction::GetActionFalse),

		luabind::class_<StartQuestAction, ActionBase, boost::shared_ptr<ActionBase> >("StartQuestAction")
		.def(luabind::constructor<>())
		.def("GetQuestId", &StartQuestAction::GetQuestId)
		.def("SetQuestId", &StartQuestAction::SetQuestId),

		luabind::class_<FinishQuestAction, ActionBase, boost::shared_ptr<ActionBase> >("FinishQuestAction")
		.def(luabind::constructor<>())
		.def("GetQuestId", &FinishQuestAction::GetQuestId)
		.def("SetQuestId", &FinishQuestAction::SetQuestId),

		luabind::class_<OpenShopAction, ActionBase, boost::shared_ptr<ActionBase> >("OpenShopAction")
		.def(luabind::constructor<>())
		.def("AddItem", &OpenShopAction::AddItem)
		.def("RemoveItem", &OpenShopAction::RemoveItem)
		.def("GetCurrencyItem", &OpenShopAction::GetCurrencyItem)
		.def("SetCurrencyItem", &OpenShopAction::SetCurrencyItem),

		luabind::class_<CutMapAction, ActionBase, boost::shared_ptr<ActionBase> >("CutMapAction")
		.def(luabind::constructor<>())
		.def("GetY", &CutMapAction::GetY)
		.def("SetY", &CutMapAction::SetY),

		luabind::class_<OpenLetterWritterAction, ActionBase, boost::shared_ptr<ActionBase> >("OpenLetterWritterAction")
		.def(luabind::constructor<>()),

		luabind::class_<OpenMailboxAction, ActionBase, boost::shared_ptr<ActionBase> >("OpenMailboxAction")
		.def(luabind::constructor<>()),

		luabind::class_<PlaySoundAction, ActionBase, boost::shared_ptr<ActionBase> >("PlaySoundAction")
		.def(luabind::constructor<>())
		.def("GetToEveryone", &PlaySoundAction::GetToEveryone)
		.def("SetToEveryone", &PlaySoundAction::SetToEveryone)
		.def("GetSoundPath", &PlaySoundAction::GetSoundPath)
		.def("SetSoundPath", &PlaySoundAction::SetSoundPath),



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
		.def("SetLuaFunctionName", &CustomScript::SetLuaFunctionName),

		luabind::class_<DialogPart, boost::shared_ptr<DialogPart> >("DialogPart")
		.def(luabind::constructor<>())
		.def("AddChild", &DialogPart::AddChild)
		.def("RemoveChild", &DialogPart::RemoveChild)
		.def("UpdateChildPosition", &DialogPart::UpdateChildPosition)
		.def("GetCondition", &DialogPart::GetCondition)
		.def("Setcondition", &DialogPart::Setcondition)
		.def("GetAction", &DialogPart::GetAction)
		.def("SetAction", &DialogPart::SetAction)
		.def("ResetDialog", &DialogPart::ResetDialog)
		.def("SetResetDialog", &DialogPart::SetResetDialog)
		.def("SetText", &DialogPart::SetText)
		.def("AddText", &DialogPart::AddText)
		.def("RemoveText", &DialogPart::RemoveText)
		.def("PickText", &DialogPart::PickText),

		luabind::class_<Quest, boost::shared_ptr<Quest> >("Quest")
		.def(luabind::constructor<long>())
		.def("GetId", &Quest::GetId)
		.def("AddCondition", &Quest::AddCondition)
		.def("RemoveCondition", &Quest::RemoveCondition)
		.def("GetActionAtStart", &Quest::GetActionAtStart)
		.def("SetActionAtStart", &Quest::SetActionAtStart)
		.def("GetActionAtComplete", &Quest::GetActionAtComplete)
		.def("SetActionAtComplete", &Quest::SetActionAtComplete)
		.def("GetTitleTextId", &Quest::GetTitleTextId)
		.def("SetTitleTextId", &Quest::SetTitleTextId)
		.def("GetDescriptionTextId", &Quest::GetDescriptionTextId)
		.def("SetDescriptionTextId", &Quest::SetDescriptionTextId)
		.def("StartQuest", &Quest::StartQuest)
		.def("QuestFinished", &Quest::QuestFinished)
		.def("GetLocationTextId", &Quest::GetLocationTextId)
		.def("SetLocationTextId", &Quest::SetLocationTextId)
		.def("GetChapter", &Quest::GetChapter)
		.def("SetChapter", &Quest::SetChapter)
		.def("GetVisible", &Quest::GetVisible)
		.def("SetVisible", &Quest::SetVisible),

		luabind::class_<TeleportDef, boost::shared_ptr<TeleportDef> >("TeleportDef")
		.def(luabind::constructor<long>())
		.def("GetId", &TeleportDef::GetId)
		.def("GetName", &TeleportDef::GetName)
		.def("SetName", &TeleportDef::SetName)
		.def("GetMapName", &TeleportDef::GetMapName)
		.def("SetMapName", &TeleportDef::SetMapName)
		.def("GetSpawn", &TeleportDef::GetSpawn)
		.def("SetSpawn", &TeleportDef::SetSpawn)
		.def("GetCondition", &TeleportDef::GetCondition)
		.def("SetCondition", &TeleportDef::SetCondition),

		luabind::class_<ScriptInitHandler>("ScriptInitHandler")
		.def("AddTeleport", &SharedDataHandler::AddTeleport)
		.def("RemoveTeleport", &SharedDataHandler::RemoveTeleport)
		.def("GetTeleport", &SharedDataHandler::GetTeleport)
		.def("AddQuest", &SharedDataHandler::AddQuest)
		.def("RemoveQuest", &SharedDataHandler::RemoveQuest)
		.def("GetQuest", &SharedDataHandler::GetQuest)
		.def("AddInventoryItem", &SharedDataHandler::AddInventoryItem),

		luabind::class_<SharedDataHandler, ScriptInitHandler>("SharedDataHandler"),

		luabind::class_<InventoryItemDef, boost::shared_ptr<InventoryItemDef> >("InventoryItemDef")
		.def(luabind::constructor<long>())
		.def("GetId", &InventoryItemDef::GetId)
		.def("GetName", &InventoryItemDef::GetName)
		.def("GetIconName", &InventoryItemDef::GetIconName)
		.def("GetNameTextId", &InventoryItemDef::GetNameTextId)
		.def("GetDescriptionId", &InventoryItemDef::GetDescriptionId)
		.def("GetLongDescriptionId", &InventoryItemDef::GetLongDescriptionId)
		.def("GetMax", &InventoryItemDef::GetMax)
		.def("GetBuyPrice", &InventoryItemDef::GetBuyPrice)
		.def("GetSellPrice", &InventoryItemDef::GetSellPrice)
		.def("GetDescriptionTextExtra", &InventoryItemDef::GetDescriptionTextExtra)
		.def("GetType", &InventoryItemDef::GetType)
		.def("GetEffect", &InventoryItemDef::GetEffect)
		.def("GetEffect2", &InventoryItemDef::GetEffect2)
		.def("GetFlag", &InventoryItemDef::GetFlag)
		.def("GetEphemere", &InventoryItemDef::GetEphemere)
		.def("GetStringFlag", &InventoryItemDef::GetStringFlag)
		.def("GetColor1", &InventoryItemDef::GetColor1)
		.def("GetColor2", &InventoryItemDef::GetColor2)
		.def("SetName", &InventoryItemDef::SetName)
		.def("SetIconName", &InventoryItemDef::SetIconName)
		.def("SetNameTextId", &InventoryItemDef::SetNameTextId)
		.def("SetDescriptionId", &InventoryItemDef::SetDescriptionId)
		.def("SetLongDescriptionId", &InventoryItemDef::SetLongDescriptionId)
		.def("SetMax", &InventoryItemDef::SetMax)
		.def("SetBuyPrice", &InventoryItemDef::SetBuyPrice)
		.def("SetSellPrice", &InventoryItemDef::SetSellPrice)
		.def("SetDescriptionTextExtra", &InventoryItemDef::SetDescriptionTextExtra)
		.def("SetType", &InventoryItemDef::SetType)
		.def("SetEffect", &InventoryItemDef::SetEffect)
		.def("SetEffect2", &InventoryItemDef::SetEffect2)
		.def("SetFlag", &InventoryItemDef::SetFlag)
		.def("SetEphemere", &InventoryItemDef::SetEphemere)
		.def("SetStringFlag", &InventoryItemDef::SetStringFlag)
		.def("SetColor1", &InventoryItemDef::SetColor1)
		.def("SetColor2", &InventoryItemDef::SetColor2)
		.def("AddContainedItem", &InventoryItemDef::AddContainedItem)
		.def("GetReplacedItem", &InventoryItemDef::GetReplacedItem)
		.def("GetAction", &InventoryItemDef::GetAction)
		.def("SetReplacedItem", &InventoryItemDef::SetReplacedItem)
		.def("SetAction", &InventoryItemDef::SetAction)
		.def("SetDisplayInfo", &InventoryItemDef::SetDisplayInfo)
		.def("GetDisplayInfo", &InventoryItemDef::GetDisplayInfo)
		.def("SetRenderType", &InventoryItemDef::SetRenderType)
		.def("GetRenderType", &InventoryItemDef::GetRenderType)
		.def_readwrite("DisplayDesc", &InventoryItemDef::_displayinfo),

		luabind::class_<Spawn, boost::shared_ptr<Spawn> >("Spawn")
		.def(luabind::constructor<long>())
		.def("GetId", &Spawn::GetId)
		.def("GetPosX", &Spawn::GetPosX)
		.def("GetPosY", &Spawn::GetPosY)
		.def("GetPosZ", &Spawn::GetPosZ)
		.def("SetPosX", &Spawn::SetPosX)
		.def("SetPosY", &Spawn::SetPosY)
		.def("SetPosZ", &Spawn::SetPosZ)
		.def("GetForceRotation", &Spawn::GetForceRotation)
		.def("SetForceRotation", &Spawn::SetForceRotation)
		.def("GetRotation", &Spawn::GetRotation)
		.def("SetRotation", &Spawn::SetRotation)
		.def("GetName", &Spawn::GetName)
		.def("SetName", &Spawn::SetName)
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


