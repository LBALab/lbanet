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
#include "PhysXEngine.h"
#include "SynchronizedTimeHandler.h"
#include "NxPhysics.h"
#include "NxControllerManager.h"
#include "NxCapsuleController.h"
#include "NxBoxController.h"
#include "UserAllocator.h"
#include "NxCooking.h"
#include "Stream.h"
#include "PhysXErrorStream.h"
#include "CommonTypes.h"

#include <limits>
#include <fstream>

#include <windows.h>    // Header File For Windows
#include <GL/gl.h>      // Header File For The OpenGL32 Library
#include <GL/glu.h>     // Header File For The GLu32 Library


#define SKINWIDTH	0.01f
#define STEPOFFSET	0.5f
#define LIMITANGLE	70.0f

enum GameGroup
{
	GROUP_NON_COLLIDABLE,
	GROUP_COLLIDABLE_NON_PUSHABLE,
	GROUP_COLLIDABLE_PUSHABLE,
	GROUP_EXTERNAL_PLAYERS
};

#define COLLIDABLE_MASK	(1<<GROUP_COLLIDABLE_NON_PUSHABLE) | (1<<GROUP_COLLIDABLE_PUSHABLE)


class MyContactReport : public NxUserContactReport    
{        
	void onContactNotify(NxContactPair& pair, NxU32 events)        
	{  
		if(events & NX_NOTIFY_ON_START_TOUCH)
		{
			NxActor* n1 = pair.actors[0];
			NxActor* n2 = pair.actors[1];
			if(n1 && n2)
			{
				ActorUserData * acd1 = (ActorUserData *) n1->userData;
				ActorUserData * acd2 = (ActorUserData *) n2->userData;
				if(acd1 && acd2)
				{
					HitInfo hinfo;
					hinfo.ActorId = acd2->GetActorId();
					hinfo.ActorObjType = acd2->GetActorObjType();
					hinfo.ActorPhysType = acd2->GetActorType();
					hinfo.HitBottom = false;
					acd1->AddActorHitted(hinfo);

					HitInfo hinfo2;
					hinfo2.ActorId = acd1->GetActorId();
					hinfo2.ActorObjType = acd1->GetActorObjType();
					hinfo2.ActorPhysType = acd1->GetActorType();
					hinfo2.HitBottom = false;
					acd2->AddActorHitted(hinfo2);
				}
			}
		} 
	}    
} myReport;


/***********************************************************************
 * Declaration of the class ControllerHitReport
 ***********************************************************************/
class ControllerHitReport : public NxUserControllerHitReport
{
public:
	virtual NxControllerAction  onShapeHit(const NxControllerShapeHit& hit)
	{
		if(1 && hit.shape)
		{
			NxActor& actor = hit.shape->getActor();
			ActorUserData * characterdata = (ActorUserData *)hit.controller->getActor()->userData;
			ActorUserData * mstorage = (ActorUserData *)actor.userData;
			if(characterdata && mstorage)
			{
				HitInfo hinfo;
				hinfo.ActorId = mstorage->GetActorId();
				hinfo.ActorObjType = mstorage->GetActorObjType();
				hinfo.ActorPhysType = mstorage->GetActorType();
				hinfo.HitBottom = false;
				hinfo.FloorMaterial = 0;

				if(hit.shape)
				{
					NxRaycastHit hitinfo;
					NxVec3 pos((float)hit.worldPos.x,(float)hit.worldPos.y+0.01f,(float)hit.worldPos.z);
					NxVec3 vec(0, -1,0);

					if(hit.shape->raycast(NxRay(pos, vec), 0.02f, 
												NX_RAYCAST_FACE_INDEX, hitinfo, false))
					{
						// character hit the shape  from the bottom
						hinfo.HitBottom = true;

						// check material hit
						if(hitinfo.faceID < mstorage->GetMaterialsSize())
							hinfo.FloorMaterial = mstorage->GetMaterials(hitinfo.faceID);
					}
				}

				characterdata->AddActorHitted(hinfo);
			}
		}

		return NX_ACTION_NONE;
	}

	virtual NxControllerAction  onControllerHit(const NxControllersHit& hit)
	{
		//used for movable objects

		NxController* cont = hit.controller;
		ActorUserData * characterdatamain = NULL;
		if(cont->getActor())
			characterdatamain = (ActorUserData *)cont->getActor()->userData;

		ActorUserData * characterdata = NULL;
		if(hit.other->getActor())
			characterdata = (ActorUserData *)hit.other->getActor()->userData;

		if(characterdatamain && characterdata)
		{
			HitInfo hinfo;
			hinfo.ActorId = characterdata->GetActorId();
			hinfo.ActorObjType = characterdata->GetActorObjType();
			hinfo.ActorPhysType = characterdata->GetActorType();
			hinfo.HitBottom = false;
			characterdatamain->AddActorHitted(hinfo);
		}

		if(characterdatamain)
		{
			if(characterdatamain->GetAllowedMovingX() || characterdatamain->GetAllowedMovingZ())
			{
				float mox, moy, moz;
				characterdatamain->GetMove(mox, moy, moz);
				mox = characterdatamain->GetAllowedMovingX() ? mox : 0;
				moy = 0;
				moz = characterdatamain->GetAllowedMovingZ() ? moz : 0;

				characterdatamain->SetMovingObject(true);
			}
			else
			{
				NxExtendedVec3 vecmain = cont->getPosition();
				NxExtendedVec3 vecother = hit.other->getPosition();
				NxVec3 diff = (vecother - vecmain);

				characterdatamain->SetMovingObject(true);
				if(characterdata)
					characterdatamain->SetAllowFreeMove(characterdata->GetAllowFreeMove());
				if(abs(diff.x) > abs(diff.z))
				{
					if(diff.x < 0)
						characterdatamain->SetMovingDirection(2);
					else
						characterdatamain->SetMovingDirection(1);
				}
				else
				{
					if(diff.z < 0)
						characterdatamain->SetMovingDirection(4);
					else
						characterdatamain->SetMovingDirection(3);
				}
			}
		}


		return NX_ACTION_NONE;
	}

} gControllerHitReport;







PhysXEngine* PhysXEngine::_singletonInstance = NULL;


/***********************************************************
singleton pattern
***********************************************************/
PhysXEngine * PhysXEngine::getInstance()
{
    if(!_singletonInstance)
        _singletonInstance = new PhysXEngine();

	return _singletonInstance;
}


/***********************************************************
	Constructor
***********************************************************/
PhysXEngine::PhysXEngine()
: gAllocator(NULL)
{
	gAllocator = new UserAllocator();
	gOutputStream = new PhysXErrorStream();
}


/***********************************************************
	Destructor
***********************************************************/
PhysXEngine::~PhysXEngine()
{
	if(gAllocator!=NULL)
	{
			delete gAllocator;
			gAllocator=NULL;
	}
}



/***********************************************************
	init function
***********************************************************/
void PhysXEngine::Init(float gravity)
{
	// Create the physics SDK
	NxPhysicsSDKDesc desc;
	NxSDKCreateError errorCode = NXCE_NO_ERROR;
	gPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, gAllocator, gOutputStream, desc, &errorCode);
    if (!gPhysicsSDK)  
	{
		LogHandler::getInstance()->LogToFile("Problem initializing physX - error initializing creating SDK. Make sure you have the physX drivers installed!");
		return;
	}

	if (gPhysicsSDK->getFoundationSDK().getRemoteDebugger())
		gPhysicsSDK->getFoundationSDK().getRemoteDebugger()->connect("localhost", 5425);


	// Set the physics parameters
	gPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.01f);

	// Set the debug visualization parameters
	gPhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1);
	gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
	gPhysicsSDK->setParameter(NX_VISUALIZE_ACTOR_AXES, 1);

    // Create the scene
    NxSceneDesc sceneDesc;
 	sceneDesc.simType				= NX_SIMULATION_SW;
    sceneDesc.gravity               = NxVec3(0,gravity,0);
    gScene = gPhysicsSDK->createScene(sceneDesc);	
	if(!gScene)
	{ 
		sceneDesc.simType			= NX_SIMULATION_SW; 
		gScene = gPhysicsSDK->createScene(sceneDesc);  
		if(!gScene) 
		{
			LogHandler::getInstance()->LogToFile("Problem initializing physX - error initializing the scene. Make sure you have the physX drivers installed!");
			return;
		}
	}

	gScene->setUserContactReport(&myReport);


	// Create the default material
	NxMaterial* defaultMaterial = gScene->getMaterialFromIndex(0); 
	defaultMaterial->setRestitution(0.5);
	defaultMaterial->setStaticFriction(0.5);
	defaultMaterial->setDynamicFriction(0.5);
	defaultMaterial->setFrictionCombineMode(NX_CM_MIN);
	defaultMaterial->setRestitutionCombineMode(NX_CM_MAX);


	// init character controllers
	gManager = NxCreateControllerManager(gAllocator);


	//float TimeStep = 1.0f / 60.0f;
	gScene->setTiming(0.017f/*, 8, NX_TIMESTEP_VARIABLE*/);

	//gScene->setGroupCollisionFlag(GROUP_COLLIDABLE_PUSHABLE, GROUP_NON_COLLIDABLE, false);



	// Start the first frame of the simulation
	if (gScene)  
		StartPhysics(17); // start with a fixed timestep

	// init cooking
	NxInitCooking(gAllocator, gOutputStream);

	_isInitialized = true;
}

/***********************************************************
	quit function
***********************************************************/
void PhysXEngine::Quit()
{
	_isInitialized = false;

	// close cooking
	NxCloseCooking();

    if (gScene)
	{
		// Make sure to fetchResults() before shutting down
		GetPhysicsResults();  

		// clean up character controllers
		gManager->purgeControllers();
		NxReleaseControllerManager(gManager);
		gManager = NULL;

		gPhysicsSDK->releaseScene(*gScene);
		gScene = NULL;
	}

	if (gPhysicsSDK)  
		gPhysicsSDK->release();

	gPhysicsSDK = NULL;
}


/***********************************************************
	call to start physic calculation after having updated state from inputs
***********************************************************/
void PhysXEngine::StartPhysics(float tdiff)
{
	// Start collision and dynamics for delta time since the last frame
    gScene->simulate(tdiff);
	gScene->flushStream();
}


/***********************************************************
	call after render to get results of calculation
***********************************************************/
void PhysXEngine::GetPhysicsResults()
{
	// Get results from gScene->simulate
	gScene->fetchResults(NX_RIGID_BODY_FINISHED, true);

	NxReal maxTimestep;
	NxTimeStepMethod method;
	NxU32 maxIter;
	NxU32 numSubSteps;
	gScene->getTiming(maxTimestep, maxIter, method, &numSubSteps);
	if(numSubSteps)	
		gManager->updateControllers();
}


/***********************************************************
	create plane actor
***********************************************************/
NxActor* PhysXEngine::CreatePlane(const NxVec3 & StartPosition, const NxVec3 & PlaneNormal)
{
    // Create a plane with default descriptor
    NxPlaneShapeDesc planeDesc;
	planeDesc.normal = PlaneNormal;
	planeDesc.group = GROUP_COLLIDABLE_NON_PUSHABLE;

    NxActorDesc actorDesc;
    actorDesc.shapes.pushBack(&planeDesc);
	actorDesc.globalPose.t	= StartPosition;	

    return gScene->createActor(actorDesc);
}


/***********************************************************
	create box actor
***********************************************************/
NxActor* PhysXEngine::CreateBox(const NxVec3 & StartPosition, float dimX, float dimY, float dimZ, 
								float density, LbaNet::PhysicalActorType Type, ActorUserData * adata, 
								const LbaQuaternion& rotation, bool collidable)
{

	// Add a single-shape actor to the scene
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;

	// The actor has one shape, a box, 1m on a side
	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions.set(dimX/2, dimY/2, dimZ/2);
	boxDesc.localPose.t = NxVec3(0, 0, 0);

	if(Type != LbaNet::StaticAType)
	{
		if(Type == LbaNet::KynematicAType)
			bodyDesc.flags |= NX_BF_KINEMATIC;

		actorDesc.body	= &bodyDesc;
		actorDesc.density = density;

		if(Type == LbaNet::DynamicAType)
			boxDesc.group = GROUP_COLLIDABLE_PUSHABLE;
		else
			boxDesc.group = GROUP_COLLIDABLE_NON_PUSHABLE;
	}
	else
		boxDesc.group = GROUP_COLLIDABLE_NON_PUSHABLE;

	if(!collidable)
		boxDesc.group = GROUP_NON_COLLIDABLE;


	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.userData = adata;

	actorDesc.globalPose.t	= StartPosition;	
	actorDesc.globalPose.M = NxQuat(NxVec3(rotation.X, rotation.Y, rotation.Z), rotation.W);

	assert(actorDesc.isValid());
	NxActor *pActor = gScene->createActor(actorDesc);	
	assert(pActor);

	pActor->setContactReportFlags(NX_NOTIFY_ON_START_TOUCH);
	return pActor;
}

/***********************************************************
	create sphere actor
***********************************************************/
NxActor* PhysXEngine::CreateSphere(const NxVec3 & StartPosition, float radius, float density, 
						LbaNet::PhysicalActorType Type, ActorUserData * adata,
						const LbaQuaternion& rotation, bool collidable)
{
	// Add a single-shape actor to the scene
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;

	// The actor has one shape, a sphere, 1m on radius
	NxSphereShapeDesc sphereDesc;
	sphereDesc.radius		= radius;
	sphereDesc.localPose.t	= NxVec3(0, 0, 0);
	

	if(Type != LbaNet::StaticAType)
	{
		if(Type == LbaNet::KynematicAType)
			bodyDesc.flags |= NX_BF_KINEMATIC;

		actorDesc.body	= &bodyDesc;
		actorDesc.density = density;
		
		if(Type == LbaNet::DynamicAType)
			sphereDesc.group = GROUP_COLLIDABLE_PUSHABLE;
		else
			sphereDesc.group = GROUP_COLLIDABLE_NON_PUSHABLE;
	}
	else
		sphereDesc.group = GROUP_COLLIDABLE_NON_PUSHABLE;


	if(!collidable)
		sphereDesc.group = GROUP_NON_COLLIDABLE;

	actorDesc.shapes.pushBack(&sphereDesc);
	actorDesc.userData = adata;

	actorDesc.globalPose.t	= StartPosition;	
	actorDesc.globalPose.M = NxQuat(NxVec3(rotation.X, rotation.Y, rotation.Z), rotation.W);


	assert(actorDesc.isValid());
	NxActor *pActor = gScene->createActor(actorDesc);	
	assert(pActor);

	pActor->setContactReportFlags(NX_NOTIFY_ON_START_TOUCH);
	return pActor;
}


/***********************************************************
	create sphere actor
***********************************************************/
NxActor* PhysXEngine::CreateSphere(const NxVec3 & StartPosition, float radius, float density, 
									LbaNet::PhysicalActorType Type,  ActorUserData * adata,
									float staticFriction, float dynamicFriction, float restitution, 
									const LbaQuaternion& rotation, bool collidable)
{
	// Add a single-shape actor to the scene
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;

	// The actor has one shape, a sphere, 1m on radius
	NxSphereShapeDesc sphereDesc;
	sphereDesc.radius		= radius;
	sphereDesc.localPose.t	= NxVec3(0, 0, 0);
	

    NxMaterialDesc materialDesc;    
	materialDesc.restitution = restitution;    
	materialDesc.staticFriction = staticFriction;    
	materialDesc.dynamicFriction = dynamicFriction; 
	materialDesc.frictionCombineMode = NX_CM_MIN;
	materialDesc.restitutionCombineMode = NX_CM_MAX;
    NxMaterial *newMaterial=gScene->createMaterial(materialDesc); 

	sphereDesc.materialIndex = newMaterial->getMaterialIndex();

	
	if(Type != LbaNet::StaticAType)
	{
		if(Type == LbaNet::KynematicAType)
			bodyDesc.flags |= NX_BF_KINEMATIC;

		actorDesc.body	= &bodyDesc;
		actorDesc.density		= density;
		
		if(Type == LbaNet::DynamicAType)
			sphereDesc.group = GROUP_COLLIDABLE_PUSHABLE;
		else
			sphereDesc.group = GROUP_COLLIDABLE_NON_PUSHABLE;
	}
	else
		sphereDesc.group = GROUP_COLLIDABLE_NON_PUSHABLE;


	if(!collidable)
		sphereDesc.group = GROUP_NON_COLLIDABLE;

	actorDesc.shapes.pushBack(&sphereDesc);
	actorDesc.userData = adata;

	actorDesc.globalPose.t	= StartPosition;	
	actorDesc.globalPose.M = NxQuat(NxVec3(rotation.X, rotation.Y, rotation.Z), rotation.W);


	assert(actorDesc.isValid());
	NxActor *pActor = gScene->createActor(actorDesc);	
	assert(pActor);

	pActor->setContactReportFlags(NX_NOTIFY_ON_START_TOUCH);
	return pActor;
}

/***********************************************************
	create capsule actor
***********************************************************/
NxActor* PhysXEngine::CreateCapsule(const NxVec3 & StartPosition, float radius, float height, float density, 
										LbaNet::PhysicalActorType Type, ActorUserData * adata, 
										const LbaQuaternion& rotation, bool collidable)
{
	// Add a single-shape actor to the scene
	NxActorDesc actorDesc;
	NxBodyDesc bodyDesc;

	// The actor has one shape, a sphere, 1m on radius
	NxCapsuleShapeDesc capsuleDesc;
	capsuleDesc.radius		= radius;
	capsuleDesc.height		= height;
	capsuleDesc.localPose.t = NxVec3(0, 0, 0);

	if(Type != LbaNet::StaticAType)
	{
		if(Type == LbaNet::KynematicAType)
			bodyDesc.flags |= NX_BF_KINEMATIC;

		actorDesc.body	= &bodyDesc;
		actorDesc.density = density;

		if(Type == LbaNet::DynamicAType)
			capsuleDesc.group = GROUP_COLLIDABLE_PUSHABLE;
		else
			capsuleDesc.group = GROUP_COLLIDABLE_NON_PUSHABLE;
	}
	else
		capsuleDesc.group = GROUP_COLLIDABLE_NON_PUSHABLE;

	if(!collidable)
		capsuleDesc.group = GROUP_NON_COLLIDABLE;

	actorDesc.shapes.pushBack(&capsuleDesc);
	actorDesc.userData = adata;

	actorDesc.globalPose.t	= StartPosition;
	actorDesc.globalPose.M = NxQuat(NxVec3(rotation.X, rotation.Y, rotation.Z), rotation.W);


	assert(actorDesc.isValid());
	NxActor *pActor = gScene->createActor(actorDesc);	
	assert(pActor);

	pActor->setContactReportFlags(NX_NOTIFY_ON_START_TOUCH);
	return pActor;
}



/***********************************************************
	create character controller
***********************************************************/
NxController* PhysXEngine::CreateCharacter(const NxVec3 & StartPosition, float radius, float height,
											ActorUserData * adata)
{
	NxCapsuleControllerDesc desc;
	desc.position.x		= StartPosition.x;
	desc.position.y		= StartPosition.y;
	desc.position.z		= StartPosition.z;
	desc.radius			= radius;
	desc.height			= height;
	desc.upDirection	= NX_Y;
	desc.slopeLimit		= cosf(NxMath::degToRad(LIMITANGLE));
	desc.skinWidth		= SKINWIDTH;
	desc.stepOffset		= STEPOFFSET;
	desc.callback		= &gControllerHitReport;

	NxController* res = gManager->createController(gScene, desc);
	res->getActor()->userData = adata;
	res->setCollision(true);

	return res;
}


/***********************************************************
	create character controller
***********************************************************/
NxController* PhysXEngine::CreateCharacterBox(const NxVec3 & StartPosition, const NxVec3 & Extents,
								ActorUserData * adata)
{
	NxBoxControllerDesc desc;
	desc.position.x		= StartPosition.x;
	desc.position.y		= StartPosition.y;
	desc.position.z		= StartPosition.z;
	desc.extents		= Extents;
	desc.upDirection	= NX_Y;
	desc.slopeLimit		= cosf(NxMath::degToRad(LIMITANGLE));
	desc.skinWidth		= SKINWIDTH;
	desc.stepOffset		= STEPOFFSET;
	desc.callback		= &gControllerHitReport;

	NxController* res = gManager->createController(gScene, desc);
	res->getActor()->userData = adata;
	res->setCollision(true);

	return res;
}

/***********************************************************
	CreateTriangleMesh
***********************************************************/
NxActor* PhysXEngine::CreateTriangleMesh(const NxVec3 & StartPosition, float *Vertexes, size_t VertexesSize, 
											unsigned int *Indices, size_t IndicesSize,
											ActorUserData * adata, 
											const LbaQuaternion& rotation, bool collidable)
{
	// Create descriptor for triangle mesh
	NxTriangleMeshDesc triangleMeshDesc;
	triangleMeshDesc.numVertices = VertexesSize/3;
	triangleMeshDesc.pointStrideBytes = 3 * sizeof(float);
	triangleMeshDesc.points	= Vertexes;
	triangleMeshDesc.numTriangles = IndicesSize/3;
	triangleMeshDesc.flags = 0;
	triangleMeshDesc.triangles = Indices;
	triangleMeshDesc.triangleStrideBytes = 3 * sizeof(unsigned int);


	// The actor has one shape, a triangle mesh
	MemoryWriteBuffer buf;

	bool status = NxCookTriangleMesh(triangleMeshDesc, buf);
	NxTriangleMesh* pMesh;
	if (status)
	{
		pMesh = gPhysicsSDK->createTriangleMesh(MemoryReadBuffer(buf.data));
	}
	else
	{
		assert(false);
		pMesh = NULL;
	}


	// Create TriangleMesh above code segment.
	NxTriangleMeshShapeDesc tmsd;
	tmsd.meshData			= pMesh;
	tmsd.localPose.t		= NxVec3(0, 0, 0);
	tmsd.meshPagingMode 	= NX_MESH_PAGING_AUTO;

	if(collidable)
		tmsd.group = GROUP_COLLIDABLE_NON_PUSHABLE;
	else
		tmsd.group = GROUP_NON_COLLIDABLE;

	NxActorDesc actorDesc;
	NxBodyDesc  bodyDesc;

	assert(tmsd.isValid());
	actorDesc.shapes.pushBack(&tmsd);
	actorDesc.body		= NULL;		
	actorDesc.userData = adata;

	actorDesc.globalPose.t	= StartPosition;
	actorDesc.globalPose.M = NxQuat(NxVec3(rotation.X, rotation.Y, rotation.Z), rotation.W);

	if (pMesh)
	{
		assert(actorDesc.isValid());
		NxActor *actor = gScene->createActor(actorDesc);
		assert(actor);

		return actor;
	}

	return NULL;
}





/***********************************************************
//! Load triangle mesh shape to the engine
***********************************************************/
NxActor* PhysXEngine::LoadTriangleMeshFile(const NxVec3 & StartPosition, const std::string Filename,
												ActorUserData * userdata, 
												const LbaQuaternion& rotation, bool collidable)
{
	// load data from binary file and set it into a triangle mesh
	std::ifstream file(Filename.c_str(), std::ifstream::binary);
	if(!file.is_open())
	{
		return NULL;
	}

	unsigned int sizevertex;
	unsigned int sizeindices;
	unsigned int sizematerials;
	//unsigned int tmp;

	file.read((char*)&sizevertex, sizeof(unsigned int));
	file.read((char*)&sizeindices, sizeof(unsigned int));
	file.read((char*)&sizematerials, sizeof(unsigned int));
	//file.read((char*)&tmp, sizeof(unsigned int));
	//file.read((char*)&tmp, sizeof(unsigned int));


	float *buffervertex = new float[sizevertex];
	unsigned int *bufferindices = new unsigned int[sizeindices];
	file.read((char*)buffervertex, sizevertex*sizeof(float));
	file.read((char*)bufferindices, sizeindices*sizeof(unsigned int));

	if(sizematerials > 0)
	{
		short *buffermaterials = new short[sizematerials];
		file.read((char*)buffermaterials, sizematerials*sizeof(short));

		userdata->SetMaterialsSize(sizematerials);
		userdata->SetMaterials(buffermaterials);
	}

	NxActor* actor = CreateTriangleMesh(StartPosition, buffervertex, sizevertex, bufferindices, sizeindices, 
											userdata, rotation, collidable);
	//NxActor* act = NULL;
	delete[] buffervertex;
	delete[] bufferindices;


	return actor;
}




/***********************************************************
 move character
 returned collision flags, collection of NxControllerFlag
***********************************************************/
unsigned int PhysXEngine::MoveCharacter(NxController* character, const NxVec3& moveVector, bool checkcollision)
{
	NxU32 collisionFlags;
	if(character)
		character->move(moveVector, (checkcollision?COLLIDABLE_MASK:0), 0.000001f, collisionFlags);

	return collisionFlags;
}


/***********************************************************
set actor position (teleport)
***********************************************************/
void PhysXEngine::SetCharacterPos(NxController* character, const NxVec3& posVector)
{
	NxExtendedVec3 pos;
	pos.x = posVector.x;
	pos.y = posVector.y;
	pos.z = posVector.z;
	character->setPosition(pos);
}

/***********************************************************
get gravity
***********************************************************/
void PhysXEngine::GetGravity(NxVec3 & Gravity)
{
	if(gScene)
		gScene->getGravity(Gravity);
}

/***********************************************************
DestroyActor
***********************************************************/
void PhysXEngine::DestroyActor(NxActor* actor)
{
	if(!_isInitialized)
		return;


	//destroy internal actor if there is one
	if(actor)
	{
		ActorUserData * udata = (ActorUserData *)actor->userData;
		if(udata && !udata->Getreleased())
		{
			udata->Setreleased(true);
		}

		if(gScene)
			gScene->releaseActor(*actor);

		// inform controllers
		for(unsigned int i=0; i<gManager->getNbControllers(); ++i)
		{
			NxController*	cont = gManager->getController(i);
			cont->reportSceneChanged();
		}
	
	}
}

/***********************************************************
DestroyCharacter
***********************************************************/
void PhysXEngine::DestroyCharacter(NxController* character)
{
	//destroy internal actor if there is one
	ActorUserData * udata = (ActorUserData *)character->getActor()->userData;
	if(udata && !udata->Getreleased())
	{
		udata->Setreleased(true);
	}

	if(gManager && character)
		gManager->releaseController(*character);

	// inform controllers
	for(unsigned int i=0; i<gManager->getNbControllers(); ++i)
	{
		NxController*	cont = gManager->getController(i);
		cont->reportSceneChanged();
	}
}




/***********************************************************
GetCharacterPosition
***********************************************************/
void PhysXEngine::GetCharacterPosition(NxController* character, float &posX, float &posY, float &posZ)
{
	NxExtendedVec3 vec = character->getPosition();
	posX = (float)vec.x;
	posY = (float)vec.y;
	posZ = (float)vec.z;
}


/***********************************************************
HideShowCharacter
***********************************************************/
void PhysXEngine::HideShowCharacter(NxController* character, bool Show)
{
	character->setCollision(Show);
}

/***********************************************************
HideShowActor
***********************************************************/
void PhysXEngine::HideShowActor(NxActor* actor, bool Show)
{
	if(Show)
		actor->clearActorFlag(NX_AF_DISABLE_COLLISION);
	else
		actor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
}




/***********************************************************
//! Get Closest Floor
***********************************************************/
int PhysXEngine::GetClosestFloor(float PositionX, float PositionY, float PositionZ)
{
	NxRaycastHit hitinfo;
	NxVec3 vec(0, -1, 0);
	NxVec3 Position(PositionX, PositionY+1, PositionZ);

	// only test against static shape as dynamic are not suposed to be floor
	 if(gScene->raycastClosestShape(NxRay(Position, vec), NX_STATIC_SHAPES, hitinfo, -1, 10000, NX_RAYCAST_DISTANCE))
	 {
		return (int)(Position.y - hitinfo.distance + 0.5);
	 }

	//if(_flooractor)
	//{
	//	if(_flooractor->getNbShapes() > 0)
	//	{
	//		NxTriangleMeshShape* _currmap = (*_flooractor->getShapes())->isTriangleMesh();

	//		NxRaycastHit hitinfo;
	//		NxVec3 vec(0, -1, 0);
	//		NxVec3 Position(PositionX, PositionY+1, PositionZ);

	//		if(_currmap && _currmap->raycast(NxRay(Position, vec), 100.0f, NX_RAYCAST_DISTANCE, hitinfo, false))
	//		{
	//			return (int)(Position.y - hitinfo.distance + 0.5);
	//		}
	//	}
	//}

	return -1;
}



/***********************************************************
ignore collision for a pair of actor
***********************************************************/
void PhysXEngine::IgnoreActorContact(NxActor* actor1, NxActor* actor2)
{
	gScene->setActorPairFlags(*actor1, *actor2, NX_IGNORE_PAIR);
}

/***********************************************************
check fi actor 1 is on top of actor2
***********************************************************/
bool PhysXEngine::CheckOnTopOff(NxActor* actor1, NxActor* actor2)
{
	if(!actor1 || !actor2)
		return false;

	if(actor2->getNbShapes() < 1)
		return false;
	if(actor1->getNbShapes() < 1)
		return false;

	NxBounds3 bound1, bound2;
	(*actor1->getShapes())->getWorldBounds(bound1);
	(*actor2->getShapes())->getWorldBounds(bound2);

	return bound1.intersects2D(bound2, 1);
}
	 



/***********************************************************
	Render actors
***********************************************************/
void PhysXEngine::RenderActors()
{
	//glEnable(GL_BLEND);
	//glDisable(GL_TEXTURE_2D);
	//glDisable(GL_DEPTH_TEST);
	//glLineWidth(2.0f);

 //   // Render all the actors in the scene
 //   NxU32 nbActors = gScene->getNbActors();
 //   NxActor** actors = gScene->getActors();
 //   while (nbActors--)
 //   {
 //       NxActor* actor = *actors++;

	//	glPushMatrix();

	//	glScalef(1, 0.5f, 1);
	//	glTranslated(0, 1.0, 0);
	//	NxMat34 pose = actor->getShapes()[0]->getGlobalPose();
	//	//glTranslated(pose.t.x, pose.t.y/2. + 0.5, pose.t.z);

	//	float glmat[16];	//4x4 column major matrix for OpenGL.
	//	pose.M.getColumnMajorStride4(&(glmat[0]));
	//	pose.t.get(&(glmat[12]));
	//	//clear the elements we don't need:
	//	glmat[3] = glmat[7] = glmat[11] = 0.0f;
	//	glmat[15] = 1.0f;
	//	glMultMatrixf(&(glmat[0]));

	//	NxBoxShape* boxshap = actor->getShapes()[0]->isBox();
	//	if(boxshap)
	//	{
	//		glColor4f(0.0f,0.0f,1.0f, 1.f);

	//		NxVec3 boxDim = boxshap->getDimensions();
	//		glScalef(boxDim.x, boxDim.y, boxDim.z);

	//		float _sizeX = 1, _sizeY = 1, _sizeZ = 1;
	//		glBegin(GL_LINES);
	//			glVertex3f(-_sizeX,-_sizeY,-_sizeZ);
	//			glVertex3f(_sizeX,-_sizeY,-_sizeZ);
	//			glVertex3f(_sizeX,-_sizeY,-_sizeZ);
	//			glVertex3f(_sizeX,-_sizeY,_sizeZ);
	//			glVertex3f(_sizeX,-_sizeY,_sizeZ);
	//			glVertex3f(-_sizeX,-_sizeY,_sizeZ);
	//			glVertex3f(-_sizeX,-_sizeY,_sizeZ);
	//			glVertex3f(-_sizeX,-_sizeY,-_sizeZ);

	//			glVertex3f(-_sizeX,_sizeY,-_sizeZ);
	//			glVertex3f(_sizeX,_sizeY,-_sizeZ);
	//			glVertex3f(_sizeX,_sizeY,-_sizeZ);
	//			glVertex3f(_sizeX,_sizeY,_sizeZ);
	//			glVertex3f(_sizeX,_sizeY,_sizeZ);
	//			glVertex3f(-_sizeX,_sizeY,_sizeZ);
	//			glVertex3f(-_sizeX,_sizeY,_sizeZ);
	//			glVertex3f(-_sizeX,_sizeY,-_sizeZ);

	//			glVertex3f(-_sizeX,-_sizeY,-_sizeZ);
	//			glVertex3f(-_sizeX,_sizeY,-_sizeZ);

	//			glVertex3f(_sizeX,-_sizeY,-_sizeZ);
	//			glVertex3f(_sizeX,_sizeY,-_sizeZ);

	//			glVertex3f(_sizeX,-_sizeY,_sizeZ);
	//			glVertex3f(_sizeX,_sizeY,_sizeZ);

	//			glVertex3f(-_sizeX,-_sizeY,_sizeZ);
	//			glVertex3f(-_sizeX,_sizeY,_sizeZ);
	//		glEnd();
	//	}
	//	//else
	//	//{
	//	//	for(int i=1; i<100; ++i)
	//	//	{
	//	//		glColor4f(1.0f,0.0f,0.0f, 1.f);
	//	//		float _sizeX = (float)i, _sizeY = 0, _sizeZ = (float)i;
	//	//		glBegin(GL_LINES);
	//	//			glVertex3f(-_sizeX,-_sizeY,-_sizeZ);
	//	//			glVertex3f(_sizeX,-_sizeY,-_sizeZ);
	//	//			glVertex3f(_sizeX,-_sizeY,-_sizeZ);
	//	//			glVertex3f(_sizeX,-_sizeY,_sizeZ);
	//	//			glVertex3f(_sizeX,-_sizeY,_sizeZ);
	//	//			glVertex3f(-_sizeX,-_sizeY,_sizeZ);
	//	//			glVertex3f(-_sizeX,-_sizeY,_sizeZ);
	//	//			glVertex3f(-_sizeX,-_sizeY,-_sizeZ);
	//	//		glEnd();
	//	//	}
	//	//}





	//	glPopMatrix();
 //   }


	//////if(_sizebuff > 0)
	//////{
	//////	glPushMatrix();
	//////	glScalef(1, 0.5f, 1);

	//////	for(int i=0; i<_sizebuff;)
	//////	{
	//////		int id1 = _bufferindiceroof[i++] * 3;
	//////		float p1x =_buffervertexroof[id1];
	//////		float p1y =_buffervertexroof[id1+1];
	//////		float p1z =_buffervertexroof[id1+2];

	//////		int id2 = _bufferindiceroof[i++] * 3;
	//////		float p2x =_buffervertexroof[id2];
	//////		float p2y =_buffervertexroof[id2+1];
	//////		float p2z =_buffervertexroof[id2+2];

	//////		int id3 = _bufferindiceroof[i++] * 3;
	//////		float p3x =_buffervertexroof[id3];
	//////		float p3y =_buffervertexroof[id3+1];
	//////		float p3z =_buffervertexroof[id3+2];

	//////		glColor4f(0.0f,0.0f,1.0f, 1.f);
	//////		glBegin(GL_LINES);
	//////			glVertex3f(p1x,p1y,p1z);
	//////			glVertex3f(p2x,p2y,p2z);
	//////			glVertex3f(p2x,p2y,p2z);
	//////			glVertex3f(p3x,p3y,p3z);
	//////			glVertex3f(p3x,p3y,p3z);
	//////			glVertex3f(p1x,p1y,p1z);
	//////		glEnd();	
	//////	}

	//////	glPopMatrix();
	//////}



	//for(unsigned int i=0; i<gManager->getNbControllers(); ++i)
	//{
	//	NxController* ctrl = gManager->getController(i);
	//	NxExtendedVec3 vec = ctrl->getPosition();

	//	glPushMatrix();
	//	glScalef(1, 0.5f, 1);
	//	glTranslated(vec.x, vec.y+1.0, vec.z);
	//	glColor4f(1.0f,1.0f,0.0f, 1.f);

	//	float _sizeX = 0.4f, _sizeY = 2.5f, _sizeZ = 0.4f;
	//	glBegin(GL_LINES);
	//		glVertex3f(-_sizeX,-_sizeY,-_sizeZ);
	//		glVertex3f(_sizeX,-_sizeY,-_sizeZ);
	//		glVertex3f(_sizeX,-_sizeY,-_sizeZ);
	//		glVertex3f(_sizeX,-_sizeY,_sizeZ);
	//		glVertex3f(_sizeX,-_sizeY,_sizeZ);
	//		glVertex3f(-_sizeX,-_sizeY,_sizeZ);
	//		glVertex3f(-_sizeX,-_sizeY,_sizeZ);
	//		glVertex3f(-_sizeX,-_sizeY,-_sizeZ);

	//		glVertex3f(-_sizeX,_sizeY,-_sizeZ);
	//		glVertex3f(_sizeX,_sizeY,-_sizeZ);
	//		glVertex3f(_sizeX,_sizeY,-_sizeZ);
	//		glVertex3f(_sizeX,_sizeY,_sizeZ);
	//		glVertex3f(_sizeX,_sizeY,_sizeZ);
	//		glVertex3f(-_sizeX,_sizeY,_sizeZ);
	//		glVertex3f(-_sizeX,_sizeY,_sizeZ);
	//		glVertex3f(-_sizeX,_sizeY,-_sizeZ);

	//		glVertex3f(-_sizeX,-_sizeY,-_sizeZ);
	//		glVertex3f(-_sizeX,_sizeY,-_sizeZ);

	//		glVertex3f(_sizeX,-_sizeY,-_sizeZ);
	//		glVertex3f(_sizeX,_sizeY,-_sizeZ);

	//		glVertex3f(_sizeX,-_sizeY,_sizeZ);
	//		glVertex3f(_sizeX,_sizeY,_sizeZ);

	//		glVertex3f(-_sizeX,-_sizeY,_sizeZ);
	//		glVertex3f(-_sizeX,_sizeY,_sizeZ);
	//	glEnd();

	//	glPopMatrix();
	//}


	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_TEXTURE_2D);
}
