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

#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "ScriptEnvironmentBase.h"
#include "Holomap.h"


#include <vector>

/***********************************************************
constructor
***********************************************************/
ClientLuaHandler::ClientLuaHandler()
{
	try
	{
		luabind::module(m_LuaState) [

		luabind::class_<LbaVecLong>("LbaVecLong")
		.def(luabind::constructor<>())
        .def("Add", &LbaVecLong::Add),

		luabind::class_<LbaColor>("LbaColor")
		.def(luabind::constructor<>())
		.def(luabind::constructor<float, float, float, float>())
		.def_readwrite("R", &LbaColor::R)
		.def_readwrite("G", &LbaColor::G)
		.def_readwrite("B", &LbaColor::B)
		.def_readwrite("A", &LbaColor::A),

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

		luabind::class_<HoloCoordinate>("HoloCoordinate")
		.def(luabind::constructor<>())
		.def_readwrite("polarcoords", &HoloCoordinate::polarcoords)
		.def_readwrite("posX", &HoloCoordinate::posX)
		.def_readwrite("posY", &HoloCoordinate::posY)
		.def_readwrite("posZ", &HoloCoordinate::posZ)
		.def_readwrite("dir_cen_X", &HoloCoordinate::dir_cen_X)
		.def_readwrite("dir_cen_Y", &HoloCoordinate::dir_cen_Y)
		.def_readwrite("dir_cen_Z", &HoloCoordinate::dir_cen_Z),

		luabind::class_<DisplayInfoHandler>("DisplayInfoHandler")
		.def(luabind::constructor<>())
		.def("SetRenderType", &DisplayInfoHandler::SetRenderType)
		.def_readwrite("Dinfo", &DisplayInfoHandler::Dinfo),

		luabind::class_<HolomapLocation, boost::shared_ptr<HolomapLocation> >("HolomapLocation")
		.def(luabind::constructor<long>())
		.def("GetId", &HolomapLocation::GetId)
		.def("GetName", &HolomapLocation::GetName)			
		.def("SetName", &HolomapLocation::SetName)
		.def("SetCoordinate", &HolomapLocation::SetCoordinate)
		.def("GetCoordinate", &HolomapLocation::GetCoordinate)
		.def("GetTextId", &HolomapLocation::GetTextId)
		.def("SetTextId", &HolomapLocation::SetTextId)
		.def("SetParentLocId", &HolomapLocation::SetParentLocId)
		.def("SetChildHoloId", &HolomapLocation::SetChildHoloId)
		.def("SetParentHoloId", &HolomapLocation::SetParentHoloId),


		luabind::class_<HolomapTravelPath, boost::shared_ptr<HolomapTravelPath> >("HolomapTravelPath")
		.def(luabind::constructor<long>())
		.def("GetId", &HolomapTravelPath::GetId)
		.def("GetName", &HolomapTravelPath::GetName)			
		.def("SetName", &HolomapTravelPath::SetName)
		.def("AddCoordinate", &HolomapTravelPath::AddCoordinate)
		.def("SetVehicleModel", &HolomapTravelPath::SetVehicleModel)
		.def("GetVehicleModel", &HolomapTravelPath::GetVehicleModel)
		.def("SetParentHoloId", &HolomapTravelPath::SetParentHoloId)
		.def("GetMovingSpeed", &HolomapTravelPath::GetMovingSpeed)
		.def("SetMovingSpeed", &HolomapTravelPath::SetMovingSpeed),

		luabind::class_<Holomap, boost::shared_ptr<Holomap> >("Holomap")
		.def(luabind::constructor<long>())
		.def("GetId", &Holomap::GetId)
		.def("SetMapModel", &Holomap::SetMapModel)
		.def("SetArrowModel", &Holomap::SetArrowModel)
		.def("SetPlayerModel", &Holomap::SetPlayerModel)
		.def("SetArrowPlayerModel", &Holomap::SetArrowPlayerModel)			
		.def("SetTravelDotModel", &Holomap::SetTravelDotModel)			
		.def("GetMapModel", &Holomap::GetMapModel)
		.def("GetArrowModel", &Holomap::GetArrowModel)
		.def("GetPlayerModel", &Holomap::GetPlayerModel)
		.def("GetArrowPlayerModel", &Holomap::GetArrowPlayerModel)			
		.def("GetTravelDotModel", &Holomap::GetTravelDotModel)			
		.def("GetName", &Holomap::GetName)			
		.def("SetName", &Holomap::SetName)
		.def("GetUsePCoordinates", &Holomap::GetUsePCoordinates)			
		.def("SetUsePCoordinates", &Holomap::SetUsePCoordinates)
		.def("Set3DMap", &Holomap::Set3DMap)			
		.def("Get3DMap", &Holomap::Get3DMap)
		.def("Set3DCoordinateScaleX", &Holomap::Set3DCoordinateScaleX)			
		.def("Get3DCoordinateScaleX", &Holomap::Get3DCoordinateScaleX)	
		.def("Set3DCoordinateScaleY", &Holomap::Set3DCoordinateScaleY)			
		.def("Get3DCoordinateScaleY", &Holomap::Get3DCoordinateScaleY)	
		.def("Set3DCoordinateScaleZ", &Holomap::Set3DCoordinateScaleZ)			
		.def("Get3DCoordinateScaleZ", &Holomap::Get3DCoordinateScaleZ)
		.def("GetDistanceBetweenPathPoints", &Holomap::GetDistanceBetweenPathPoints)			
		.def("SetDistanceBetweenPathPoints", &Holomap::SetDistanceBetweenPathPoints),


		luabind::class_<ScriptEnvironmentBase>("ScriptEnvironmentBase")
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
		.def("ActorFollowGivenWaypoint", &ScriptEnvironmentBase::ActorFollowGivenWaypoint, luabind::yield)
		.def("Async_ActorRotateFromPoint", &ScriptEnvironmentBase::Async_ActorRotateFromPoint)
		.def("Async_ActorFollowWaypoint", &ScriptEnvironmentBase::Async_ActorFollowWaypoint)
		.def("Async_ActorFollowGivenWaypoint", &ScriptEnvironmentBase::Async_ActorFollowGivenWaypoint)		
		.def("ActorShowHide", &ScriptEnvironmentBase::ActorShowHide)
		.def("AttachActor", &ScriptEnvironmentBase::AttachActor)
		.def("DettachActor", &ScriptEnvironmentBase::DettachActor)
		.def("LogToFile", &ScriptEnvironmentBase::LogToFile)
		.def("ThreadRunning", &ScriptEnvironmentBase::ThreadRunning)
		.def("PlayClientVideo", &ScriptEnvironmentBase::PlayClientVideo, luabind::yield)
		.def("DisplayImage", &ScriptEnvironmentBase::DisplayImage, luabind::yield)
		.def("DisplayScrollingText", &ScriptEnvironmentBase::DisplayScrollingText, luabind::yield)
		.def("StartDisplayExtraScreen", &ScriptEnvironmentBase::StartDisplayExtraScreen, luabind::yield)
		.def("EndDisplayExtraScreen", &ScriptEnvironmentBase::EndDisplayExtraScreen)
		.def("ActorStartSound", &ScriptEnvironmentBase::ActorStartSound)
		.def("ActorStopSound", &ScriptEnvironmentBase::ActorStopSound)
		.def("ActorPauseSound", &ScriptEnvironmentBase::ActorPauseSound)
		.def("ActorResumeSound", &ScriptEnvironmentBase::ActorResumeSound)
		.def("TeleportPlayerAtEndScript", &ScriptEnvironmentBase::TeleportPlayerAtEndScript)
		.def("AddHolomap", &ScriptEnvironmentBase::AddHolomap)
		.def("AddHolomapLoc", &ScriptEnvironmentBase::AddHolomapLoc)
		.def("AddHolomapPath", &ScriptEnvironmentBase::AddHolomapPath)
		.def("DisplayHolomap", &ScriptEnvironmentBase::DisplayHolomap, luabind::yield)
		];
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

