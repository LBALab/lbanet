#include "ActorHandler.h"


/***********************************************************
constructor
***********************************************************/
ActorObjectInfo::ActorObjectInfo(long id, int type)
: ObjectId(id)
{
	switch(type)
	{
		case 1:
			TypeO = LbaNet::StaticObject;
		break;
		case 2:
			TypeO = LbaNet::CpuObject;
		break;
		case 3:
			TypeO = LbaNet::MovableObject;
		break;
		case 4:
			TypeO = LbaNet::PlayerObject;
		break;
		case 5:
			TypeO = LbaNet::GhostObject;
		break;
	}
}





/***********************************************************
	// set enum for render type as lua does not map enum
	//1 - RenderOsgModel
	//2 - RenderSprite
	//3 - RenderLba1M
	//4 - RenderLba2M
***********************************************************/
void ActorObjectInfo::SetRenderType(int rtype)
{
	switch(rtype)
	{
		case 1:
			DisplayDesc.TypeRenderer = LbaNet::RenderOsgModel;
		break;
		case 2:
			DisplayDesc.TypeRenderer = LbaNet::RenderSprite;
		break;
		case 3:
			DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
		break;
		case 4:
			DisplayDesc.TypeRenderer = LbaNet::RenderLba2M;
		break;
	}
}


/***********************************************************
	// set enum for PhysicalShape as lua does not map enum
	//1 - NoShape
	//2 - BoxShape
	//3 - CapsuleShape
	//4 - SphereShape
	//5 - TriangleMeshShape
***********************************************************/
void ActorObjectInfo::SetPhysicalShape(int shape)
{
	switch(shape)
	{
		case 1:
			PhysicDesc.TypeShape = LbaNet::NoShape;
		break;
		case 2:
			PhysicDesc.TypeShape = LbaNet::BoxShape;
		break;
		case 3:
			PhysicDesc.TypeShape = LbaNet::CapsuleShape;
		break;
		case 4:
			PhysicDesc.TypeShape = LbaNet::SphereShape;
		break;
		case 5:
			PhysicDesc.TypeShape = LbaNet::TriangleMeshShape;
		break;
	}
}

	
/***********************************************************
	// set enum for SetPhysicalActorType as lua does not map enum
	//1 - StaticAType
	//2 - KynematicAType
	//3 - DynamicAType
	//4 - CharControlAType
***********************************************************/
void ActorObjectInfo::SetPhysicalActorType(int ptype)
{
	switch(ptype)
	{
		case 1:
			PhysicDesc.TypePhysO = LbaNet::StaticAType;
		break;
		case 2:
			PhysicDesc.TypePhysO = LbaNet::KynematicAType;
		break;
		case 3:
			PhysicDesc.TypePhysO = LbaNet::DynamicAType;
		break;
		case 4:
			PhysicDesc.TypePhysO = LbaNet::CharControlAType;
		break;
	}
}


/***********************************************************
	// set the model state - used by lua instead of  the enum
	//1 - NoState
	//2 - StNormal
	//3 - StDying
	//4 - StDrowning
	//5 - StDrowningGas
	//6 - StBurning
	//7 - StSmallHurt
	//8 - StMediumHurt
	//9 - StBigHurt
	//10 - StHurtFall
	//11 - StFinishedFall
	//12 - StFalling
	//13 - StJumping
	//14 - StMovingObject
	//15 - StUseWeapon
	//16 - StImmune
	//17 - StHidden
	//18 - StScripted
	//19 - StProtectedHurt
	//20 - StRestrictedMovingObject
	//21 - StFighting
***********************************************************/
void ActorObjectInfo::SetModelState(int state)
{
	switch(state)
	{
		case 1:
			DisplayDesc.State = LbaNet::NoState;
		break;
		case 2:
			DisplayDesc.State = LbaNet::StNormal;
		break;
		case 3:
			DisplayDesc.State = LbaNet::StDying;
		break;
		case 4:
			DisplayDesc.State = LbaNet::StDrowning;
		break;
		case 5:
			DisplayDesc.State = LbaNet::StDrowningGas;
		break;
		case 6:
			DisplayDesc.State = LbaNet::StBurning;
		break;
		case 7:
			DisplayDesc.State = LbaNet::StSmallHurt;
		break;
		case 8:
			DisplayDesc.State = LbaNet::StMediumHurt;
		break;
		case 9:
			DisplayDesc.State = LbaNet::StBigHurt;
		break;
		case 10:
			DisplayDesc.State = LbaNet::StHurtFall;
		break;
		case 11:
			DisplayDesc.State = LbaNet::StFinishedFall;
		break;
		case 12:
			DisplayDesc.State = LbaNet::StFalling;
		break;
		case 13:
			DisplayDesc.State = LbaNet::StJumping;
		break;
		case 14:
			DisplayDesc.State = LbaNet::StMovingObject;
		break;
		case 15:
			DisplayDesc.State = LbaNet::StUseWeapon;
		break;
		case 16:
			DisplayDesc.State = LbaNet::StImmune;
		break;
		case 17:
			DisplayDesc.State = LbaNet::StHidden;
		break;
		case 18:
			DisplayDesc.State = LbaNet::StScripted;
		break;
		case 19:
			DisplayDesc.State = LbaNet::StProtectedHurt;
		break;
		case 20:
			DisplayDesc.State = LbaNet::StRestrictedMovingObject;
		break;
		case 21:
			DisplayDesc.State = LbaNet::StFighting;
		break;
	}
}


/***********************************************************
constructor
***********************************************************/
ActorHandler::ActorHandler(const ActorObjectInfo & actorinfo)
: m_actorinfo(actorinfo)
{

}


/***********************************************************
destructor
***********************************************************/
ActorHandler::~ActorHandler(void)
{

}