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
	Constructor
***********************************************************/
PhysXObjectHandlerBase::PhysXObjectHandlerBase(boost::shared_ptr<ActorUserData> UserData)
		: _UserData(UserData)
{}




/***********************************************************
	Constructor
***********************************************************/
PhysXActorsHandler::PhysXActorsHandler(boost::shared_ptr<ActorUserData> UserData,
													NxActor* Actor, const LbaQuaternion& rotation)
		: PhysXObjectHandlerBase(UserData), _Actor(Actor)
{
	_Actor->setGlobalOrientationQuat(NxQuat(NxVec3(rotation.X, rotation.Y, rotation.Z), rotation.W));


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
	Y = vec.y;
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
float PhysXActorsHandler::GetRotationSingleAngle()
{
	NxQuat quat = _Actor->getGlobalOrientationQuat();
	return quat.getAngle();
}

/***********************************************************
set object position in the world
***********************************************************/
void PhysXActorsHandler::SetPosition(float X, float Y, float Z)
{
	_Actor->setGlobalPosition(NxVec3(X, Y, Z));
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
void PhysXActorsHandler::Move(float deltaX, float deltaY, float deltaZ)
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
	_Actor->moveGlobalPosition(NxVec3(X, Y, Z));
}


/***********************************************************
rotate object in the world
***********************************************************/
void PhysXActorsHandler::RotateYAxis(float deltaY)
{
	NxQuat q(deltaY, NxVec3(0, 1, 0));
	NxQuat targetRot = _Actor->getGlobalOrientationQuat();
	targetRot = q * targetRot;
	_Actor->moveGlobalOrientationQuat(targetRot);
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
												boost::shared_ptr<SimpleRotationHandler> rotH)
		: PhysXObjectHandlerBase(UserData), _Controller(Controller), _rotH(rotH)
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
	Y = (float)vec.y;
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
float PhysXControllerHandler::GetRotationSingleAngle()
{
	return _rotH->GetRotationSingleAngle();
}

/***********************************************************
set object position in the world
***********************************************************/
void PhysXControllerHandler::SetPosition(float X, float Y, float Z)
{	
	if(!_Controller) return;

	PhysXEngine::getInstance()->SetCharacterPos(_Controller, NxVec3(X, Y, Z));
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
void PhysXControllerHandler::Move(float deltaX, float deltaY, float deltaZ)
{
	PhysXEngine::getInstance()->MoveCharacter(_Controller, NxVec3(deltaX, deltaY, deltaZ), true);
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
									NxVec3(X - (float)vec.x, Y - (float)vec.y, Z - (float)vec.z), 
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
												int Otype, float Odensity,
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
	boost::shared_ptr<ActorUserData> udata = boost::shared_ptr<ActorUserData>(new ActorUserData(type, id));

	if(type != 4)
	{
		NxActor* act = PhysXEngine::getInstance()->CreateBox(NxVec3(positionX, positionY, positionZ), 
													sizeX, sizeY, sizeZ, 
													density, type, udata.get(), collidable);
		
		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXActorsHandler(udata, act, rotation));
	}
	else
	{
		NxController* controller = PhysXEngine::getInstance()->CreateCharacterBox(NxVec3(positionX, positionY, positionZ), 
															NxVec3(sizeX, sizeY, sizeZ), udata.get());

		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXControllerHandler(udata, controller, 
								boost::shared_ptr<SimpleRotationHandler>(new SimpleRotationHandler(rotation))));
	}
}

/***********************************************************
	Constructor
***********************************************************/
PhysicalDescriptionCapsule::PhysicalDescriptionCapsule(float posX, float posY, float posZ,
														int Otype, float Odensity,
														const LbaQuaternion &rot,
														float rad, float ht,
														bool Collidable)
	:PhysicalDescriptionWithShape(posX, posY, posZ, Otype, Odensity, rot, Collidable),
		radius(rad), height(ht)
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
	boost::shared_ptr<ActorUserData> udata = boost::shared_ptr<ActorUserData>(new ActorUserData(type, id));

	if(type != 4)
	{
		NxActor* act = PhysXEngine::getInstance()->CreateCapsule(NxVec3(positionX, positionY, positionZ), 
													radius, height,
													density, type, udata.get(), collidable);
		
		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXActorsHandler(udata, act, rotation));
	}
	else
	{
		NxController* controller = PhysXEngine::getInstance()->CreateCharacter(NxVec3(positionX, positionY, positionZ), 
															radius, height, udata.get());

		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXControllerHandler(udata, controller, 
								boost::shared_ptr<SimpleRotationHandler>(new SimpleRotationHandler(rotation))));
	}
}

/***********************************************************
	Constructor
***********************************************************/
PhysicalDescriptionSphere::PhysicalDescriptionSphere(float posX, float posY, float posZ,
														int Otype, float Odensity,
														const LbaQuaternion &rot,
														float rad,
														float StaticFriction, 
														float DynamicFriction, 
														float Restitution,
														bool Collidable)
	:PhysicalDescriptionWithShape(posX, posY, posZ, Otype, Odensity, rot, Collidable),
		radius(rad), staticFriction(StaticFriction), 
		dynamicFriction(DynamicFriction), restitution(Restitution)
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
	boost::shared_ptr<ActorUserData> udata = boost::shared_ptr<ActorUserData>(new ActorUserData(type, id));

	if(type != 4)
	{
		NxActor* act = PhysXEngine::getInstance()->CreateSphere(NxVec3(positionX, positionY, positionZ), radius, 
													density, type, udata.get(), 
													staticFriction, dynamicFriction,
													restitution, collidable);

		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXActorsHandler(udata, act, rotation));
	}
	else
	{
		NxController* controller = PhysXEngine::getInstance()->CreateCharacter(NxVec3(positionX, positionY, positionZ), 
															radius, 0, udata.get());

		return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXControllerHandler(udata, controller, 
								boost::shared_ptr<SimpleRotationHandler>(new SimpleRotationHandler(rotation))));
	}
}

/***********************************************************
	Constructor
***********************************************************/
PhysicalDescriptionTriangleMesh::PhysicalDescriptionTriangleMesh(float posX, float posY, float posZ,
																	const std::string &FileName,
																	bool Collidable)
	:PhysicalDescriptionWithShape(posX, posY, posZ, 1, 0, LbaQuaternion(), Collidable),
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


	boost::shared_ptr<ActorUserData> udata = boost::shared_ptr<ActorUserData>(new ActorUserData(type, id));

	NxActor* actor = PhysXEngine::getInstance()->LoadTriangleMeshFile(NxVec3(positionX, positionY, positionZ), 
														"Data/"+MeshInfoDataFileName, udata.get(), collidable);

	return boost::shared_ptr<PhysicalObjectHandlerBase>(new PhysXActorsHandler(udata, actor, rotation));
}