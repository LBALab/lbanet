/*
------------------------[ Lbanet Source ]-------------------------
Copyright (C) 2009
Author: Vivien Delage [Rincevent_123]
Email : vdelage@gmail.com

-------------------------------[ GNU License ]-------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
*/

#include "PhysXObjectHandlers.h"
#include "NxPhysics.h"
#include "NxCapsuleController.h"
#include "PhysXEngine.h"
#include "NxVec3.h"
#include "ObjectsDescription.h"
#include "LogHandler.h"



/***********************************************************
update physic with new data
***********************************************************/
void PhysicalObjectHandlerBase::Update(LbaNet::PhysicObjectUpdateBasePtr update)
{
	const std::type_info& info = typeid(*update);

	// PositionUpdate
	if(info == typeid(LbaNet::PositionUpdate))
	{
		LbaNet::PositionUpdate * castedptr = 
			dynamic_cast<LbaNet::PositionUpdate *>(update.get());

		MoveTo(castedptr->Update.X, castedptr->Update.Y, castedptr->Update.Z);
		LbaQuaternion Q(castedptr->Update.Rotation, LbaVec3(0,1,0));
		RotateTo(Q);
	}
}



/***********************************************************
	Constructor
***********************************************************/
PhysXObjectHandlerBase::PhysXObjectHandlerBase(boost::shared_ptr<ActorUserData> UserData)
		: _UserData(UserData)
{}




/***********************************************************
	Constructor
***********************************************************/
PhysXActorsHandler::PhysXActorsHandler(boost::shared_ptr<ActorUserData> UserData,
													NxActor* Actor, float sizeY)
		: PhysXObjectHandlerBase(UserData), _Actor(Actor), _sizeY(sizeY)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Created new PhysXActor.");
	#endif
}


/***********************************************************
	destructor
***********************************************************/
PhysXActorsHandler::~PhysXActorsHandler()
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Destroyed PhysXActor.");
	#endif

	PhysXEngine::getInstance()->DestroyActor(_Actor);
}

/***********************************************************
get object position in the world
***********************************************************/
void PhysXActorsHandler::GetPosition(float &X, float &Y, float &Z)
{	
	if(!_Actor) return;

	NxVec3 vec = _Actor->getGlobalPosition();
	X = vec.x;
	Y = vec.y-(_sizeY/2);
	Z = vec.z;
}

/***********************************************************
get object rotation on all axis
***********************************************************/
void PhysXActorsHandler::GetRotation(LbaQuaternion& Q)
{	
	if(!_Actor) return;

	NxQuat quat = _Actor->getGlobalOrientationQuat();
	Q.X = quat.x;
	Q.Y = quat.y;
	Q.Z = quat.z;
	Q.W = quat.w;
}

/***********************************************************
get object rotation on all axis
***********************************************************/
float PhysXActorsHandler::GetRotationYAxis()
{
	NxQuat quat = _Actor->getGlobalOrientationQuat();
	float Yangle;
	quat.getAngleAxis(Yangle, NxVec3(0, 1, 0));
	return Yangle;
}

/***********************************************************
set object position in the world
***********************************************************/
void PhysXActorsHandler::SetPosition(float X, float Y, float Z)
{
	_Actor->setGlobalPosition(NxVec3(X, Y+(_sizeY/2), Z));
	_resetted = true;
}

/***********************************************************
set object rotation on all axis
***********************************************************/
void PhysXActorsHandler::SetRotation(const LbaQuaternion& Q)
{	
	_Actor->setGlobalOrientationQuat(NxQuat(NxVec3(Q.X, Q.Y, Q.Z), Q.W));
	_resetted = true;
}

/***********************************************************
move object in the world
***********************************************************/
void PhysXActorsHandler::Move(float deltaX, float deltaY, float deltaZ, bool checkcollision)
{
	float currPosX, currPosY, currPosZ;
	GetPosition(currPosX, currPosY, currPosZ);
	MoveTo(currPosX+deltaX, currPosY+deltaY, currPosZ+deltaZ);
}

/***********************************************************
move object to a position in the world
***********************************************************/
void PhysXActorsHandler::MoveTo(float X, float Y, float Z)
{
	_Actor->moveGlobalPosition(NxVec3(X, Y+(_sizeY/2), Z));
}


/***********************************************************
rotate object in the world
***********************************************************/
void PhysXActorsHandler::RotateYAxis(float deltaY)
{
	// get current Y
	NxQuat quat = _Actor->getGlobalOrientationQuat();
	float Yangle;
	quat.getAngleAxis(Yangle, NxVec3(0, 1, 0));

	// calculate new angle
	float tochange = Yangle + deltaY;
	if(tochange < 0)
		tochange += 360;
	if(tochange > 360)
		tochange -= 360;

	// move to new angle
	_Actor->moveGlobalOrientationQuat(NxQuat(tochange, NxVec3(0, 1, 0)));
}

/***********************************************************
rotate object in the world
***********************************************************/
void PhysXActorsHandler::RotateTo(const LbaQuaternion& Q)
{
	_Actor->moveGlobalOrientationQuat(NxQuat(NxVec3(Q.X, Q.Y, Q.Z), Q.W));
}


/***********************************************************
show or hide the object
***********************************************************/
void PhysXActorsHandler::ShowOrHide(bool Show)
{
	PhysXEngine::getInstance()->HideShowActor(_Actor, Show);
}








/***********************************************************
	Constructor
***********************************************************/
PhysXControllerHandler::PhysXControllerHandler(boost::shared_ptr<ActorUserData> UserData,
												NxController* Controller,
												boost::shared_ptr<SimpleRotationHandler> rotH,
												float sizeY)
		: PhysXObjectHandlerBase(UserData), _Controller(Controller), _rotH(rotH),
			_sizeY(sizeY)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Created new PhysXController.");
	#endif
}



/***********************************************************
	destructor
***********************************************************/
PhysXControllerHandler::~PhysXControllerHandler()
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Destroyed PhysXController.");
	#endif

	PhysXEngine::getInstance()->DestroyCharacter(_Controller);
}


/***********************************************************
get object position in the world
***********************************************************/
void PhysXControllerHandler::GetPosition(float &X, float &Y, float &Z)
{	
	if(!_Controller) return;

	NxExtendedVec3 vec = _Controller->getPosition();
	X = (float)vec.x;
	Y = (float)vec.y-(_sizeY/2);
	Z = (float)vec.z;
}

/***********************************************************
get object rotation on all axis
***********************************************************/
void PhysXControllerHandler::GetRotation(LbaQuaternion& Q)
{
	_rotH->GetRotation(Q);
}

/***********************************************************
get object rotation on all axis
***********************************************************/
float PhysXControllerHandler::GetRotationYAxis()
{
	return _rotH->GetRotationYAxis();
}

/***********************************************************
set object position in the world
***********************************************************/
void PhysXControllerHandler::SetPosition(float X, float Y, float Z)
{	
	if(!_Controller) return;

	PhysXEngine::getInstance()->SetCharacterPos(_Controller, NxVec3(X, Y+(_sizeY/2), Z));
	_resetted = true;
}

/***********************************************************
set object rotation on all axis
***********************************************************/
void PhysXControllerHandler::SetRotation(const LbaQuaternion& Q)
{
	_rotH->SetRotation(Q);
}


/***********************************************************
rotate object in the world
***********************************************************/
void PhysXControllerHandler::RotateYAxis(float deltaY)
{	
	_rotH->RotateYAxis(deltaY);
}

/***********************************************************
move object in the world
***********************************************************/
void PhysXControllerHandler::Move(float deltaX, float deltaY, float deltaZ, bool checkcollision)
{
	unsigned int flags = 
		PhysXEngine::getInstance()->MoveCharacter(_Controller, NxVec3(deltaX, deltaY, deltaZ), checkcollision);

	if(_UserData)
	{
		if((bool)(flags & NXCC_COLLISION_DOWN))
			_UserData->SetTouchingGround(true);
		else
			_UserData->SetTouchingGround(false);
	}
	
}

/***********************************************************
move object to a position in the world
***********************************************************/
void PhysXControllerHandler::MoveTo(float X, float Y, float Z)
{
	if(!_Controller) 
		return;

	NxExtendedVec3 vec = _Controller->getPosition();
	PhysXEngine::getInstance()->MoveCharacter(_Controller, 
									NxVec3(X - (float)vec.x, (Y+(_sizeY/2)) - (float)vec.y, Z - (float)vec.z), 
									false);
}

/***********************************************************
rotate object in the world
***********************************************************/
void PhysXControllerHandler::RotateTo(const LbaQuaternion& Q)
{
	_rotH->RotateTo(Q);
}



/***********************************************************
show or hide the object
***********************************************************/
void PhysXControllerHandler::ShowOrHide(bool Show)
{
	PhysXEngine::getInstance()->HideShowCharacter(_Controller, Show);
}








/***********************************************************
	Constructor
***********************************************************/
PhysicalDescriptionBox::PhysicalDescriptionBox(float posX, float posY, float posZ,
												LbaNet::PhysicalActorType Otype, float Odensity,
												const LbaQuaternion &rot,
												float sX, float sY, float sZ,
												bool Collidable)
	:PhysicalDescriptionWithShape(posX, posY, posZ, Otype, Odensity, rot, Collidable),
			sizeX(sX), sizeY(sY), sizeZ(sZ)
{

}

/***********************************************************
	destructor
***********************************************************/
PhysicalDescriptionBox::~PhysicalDescriptionBox()
{

}


/***********************************************************
 build description into a reald physic object
***********************************************************/
boost::shared_ptr<PhysicalObjectHandlerBase> PhysicalDescriptionBox::BuildSelf(long id) const
{
	boost::shared_ptr<ActorUserData> udata = boost::shared_ptr<ActorUserData>(new ActorUserData(ActorType, id));

	if(ActorType != LbaNet::CharControlAType)
	{
		NxActor* act = PhysXEngine::getInstance()->CreateBox(NxVec3(positionX, positionY + sizeY/2, positionZ), 
													sizeX, sizeY, sizeZ, 
													density, ActorType, udata.get(), rotation, collidable);
		
		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXActorsHandler(udata, act, sizeY));
	}
	else
	{
		NxController* controller = PhysXEngine::getInstance()->CreateCharacterBox(NxVec3(positionX, positionY + sizeY/2, positionZ), 
															NxVec3(sizeX, sizeY, sizeZ), udata.get());

		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXControllerHandler(udata, controller, 
								boost::shared_ptr<SimpleRotationHandler>(new SimpleRotationHandler(rotation)), sizeY));
	}
}

/***********************************************************
	Constructor
***********************************************************/
PhysicalDescriptionCapsule::PhysicalDescriptionCapsule(float posX, float posY, float posZ,
														LbaNet::PhysicalActorType Otype, float Odensity,
														const LbaQuaternion &rot,
														float sX, float sY,
														bool Collidable)
	:PhysicalDescriptionWithShape(posX, posY, posZ, Otype, Odensity, rot, Collidable),
		radius(sX/2), height(sY-sX), sizeY(sY)
{

}

/***********************************************************
	destructor
***********************************************************/
PhysicalDescriptionCapsule::~PhysicalDescriptionCapsule()
{

}


/***********************************************************
 build description into a reald physic object
***********************************************************/
boost::shared_ptr<PhysicalObjectHandlerBase> PhysicalDescriptionCapsule::BuildSelf(long id) const
{
	boost::shared_ptr<ActorUserData> udata = boost::shared_ptr<ActorUserData>(new ActorUserData(ActorType, id));

	if(ActorType != LbaNet::CharControlAType)
	{
		NxActor* act = PhysXEngine::getInstance()->CreateCapsule(NxVec3(positionX, positionY + sizeY/2, positionZ), 
																	radius, height,
																	density, ActorType, udata.get(), 
																	rotation, collidable);
		
		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXActorsHandler(udata, act, sizeY));
	}
	else
	{
		NxController* controller = PhysXEngine::getInstance()->CreateCharacter(NxVec3(positionX, positionY + sizeY/2, positionZ), 
																		radius, height, udata.get());

		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXControllerHandler(udata, controller, 
								boost::shared_ptr<SimpleRotationHandler>(new SimpleRotationHandler(rotation)), sizeY));
	}
}

/***********************************************************
	Constructor
***********************************************************/
PhysicalDescriptionSphere::PhysicalDescriptionSphere(float posX, float posY, float posZ,
														LbaNet::PhysicalActorType Otype, float Odensity,
														const LbaQuaternion &rot,
														float sY,
														bool Collidable)
	:PhysicalDescriptionWithShape(posX, posY, posZ, Otype, Odensity, rot, Collidable),
		radius(sY/2), sizeY(sY)
{

}

/***********************************************************
	destructor
***********************************************************/
PhysicalDescriptionSphere::~PhysicalDescriptionSphere()
{

}


/***********************************************************
 build description into a reald physic object
***********************************************************/
boost::shared_ptr<PhysicalObjectHandlerBase> PhysicalDescriptionSphere::BuildSelf(long id) const
{
	boost::shared_ptr<ActorUserData> udata = boost::shared_ptr<ActorUserData>(new ActorUserData(ActorType, id));

	if(ActorType != LbaNet::CharControlAType)
	{
		NxActor* act = PhysXEngine::getInstance()->CreateSphere(NxVec3(positionX, positionY + sizeY/2, positionZ), 
																	radius, 
																	density, ActorType, udata.get(), 
																	rotation, collidable);

		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXActorsHandler(udata, act, sizeY));
	}
	else
	{
		NxController* controller = PhysXEngine::getInstance()->CreateCharacter(NxVec3(positionX, 
																		positionY + sizeY/2, positionZ), 
																		radius, 0, udata.get());

		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXControllerHandler(udata, controller, 
								boost::shared_ptr<SimpleRotationHandler>(new SimpleRotationHandler(rotation)), sizeY));
	}
}

/***********************************************************
	Constructor
***********************************************************/
PhysicalDescriptionTriangleMesh::PhysicalDescriptionTriangleMesh(float posX, float posY, float posZ,
																	const LbaQuaternion &rot,
																	const std::string &FileName,
																	bool Collidable)
:PhysicalDescriptionWithShape(posX, posY, posZ, LbaNet::StaticAType, 1, rot, Collidable),
		MeshInfoDataFileName(FileName)
{

}

/***********************************************************
	destructor
***********************************************************/
PhysicalDescriptionTriangleMesh::~PhysicalDescriptionTriangleMesh()
{

}



/***********************************************************
 build description into a reald physic object
***********************************************************/
boost::shared_ptr<PhysicalObjectHandlerBase> PhysicalDescriptionTriangleMesh::BuildSelf(long id) const
{
	boost::shared_ptr<ActorUserData> udata = boost::shared_ptr<ActorUserData>(new ActorUserData(ActorType, id));

	NxActor* actor = PhysXEngine::getInstance()->LoadTriangleMeshFile(NxVec3(positionX, positionY, positionZ), 
														"Data/"+MeshInfoDataFileName, udata.get(), 
														rotation, collidable);

	return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXActorsHandler(udata, actor, 0));
}
