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

		luabind::class_<HolomapLocation>("HolomapLocation")
		.def(luabind::constructor<long>())
		.def("GetId", &HolomapLocation::GetId)
		.def("GetName", &HolomapLocation::GetName)			
		.def("SetName", &HolomapLocation::SetName)
		.def("SetCoordinate", &HolomapLocation::SetCoordinate)
		.def("GetCoordinate", &HolomapLocation::GetCoordinate)
		.def("GetTextId", &HolomapLocation::GetTextId)
		.def("SetTextId", &HolomapLocation::SetTextId)
		.def("SetParentLocId", &HolomapLocation::SetParentLocId)
		.def("SetChildHoloId", &HolomapLocation::SetChildHoloId),


		luabind::class_<HolomapTravelPath>("HolomapTravelPath")
		.def(luabind::constructor<long>())
		.def("GetId", &HolomapTravelPath::GetId)
		.def("GetName", &HolomapTravelPath::GetName)			
		.def("SetName", &HolomapTravelPath::SetName)
		.def("AddCoordinate", &HolomapTravelPath::AddCoordinate)
		.def("SetVehicleModel", &HolomapTravelPath::SetVehicleModel)
		.def("GetVehicleModel", &HolomapTravelPath::GetVehicleModel)
		.def("SetParentHoloId", &HolomapTravelPath::SetParentHoloId),

		luabind::class_<Holomap>("Holomap")
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
		.def("Get3DMap", &Holomap::Get3DMap),



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

