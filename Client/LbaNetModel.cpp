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


#include "LbaNetModel.h"
#include "LogHandler.h"
#include "PhysXEngine.h"
#include "OSGHandler.h"
#include "CameraController.h"
#include "SynchronizedTimeHandler.h"
#include "StaticObject.h"
#include "CharacterControllerLBA.h"
#include "ExternalPlayer.h"
#include "EventsQueue.h"



#define	_LBA1_MODEL_ANIMATION_SPEED_	1.8f

/***********************************************************
	Constructor
***********************************************************/
LbaNetModel::LbaNetModel()
: m_playerObjectId(0), m_paused(false)
{
	LogHandler::getInstance()->LogToFile("Initializing model class...");

	//initialize controllers
	m_controllerChar = boost::shared_ptr<CharacterController>(new CharacterController());
	m_controllerCam = boost::shared_ptr<CameraController>(new CameraController());
	ResetPlayerObject();
}


/***********************************************************
	Destructor
***********************************************************/
LbaNetModel::~LbaNetModel()
{
}


/***********************************************************
set player id
***********************************************************/
void LbaNetModel::SetPlayerId(long Id)
{
	m_playerObjectId = Id;
}




/***********************************************************
change the world
***********************************************************/
void LbaNetModel::ChangeWorld(const std::string & NewWorld)
{
	// clean old world
	CleanupWorld();
}




/***********************************************************
do all check to be done when idle
***********************************************************/
void LbaNetModel::Process(double tnow, float tdiff)
{
	if(m_paused)
		return;

	// process all _serverObjects
	{
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _serverObjects.begin();
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator end = _serverObjects.end();
	for(; it != end; ++it)
		it->second->Process(tnow, tdiff);
	}

	// process all _movableObjects
	{
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _movableObjects.begin();
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator end = _movableObjects.end();
	for(; it != end; ++it)
		it->second->Process(tnow, tdiff);
	}

	// process all _playerObjects
	{
	std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.begin();
	std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator end = _playerObjects.end();
	for(; it != end; ++it)
		it->second->Process(tnow, tdiff);
	}

	// process all _ghostObjects
	{
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.begin();
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator end = _ghostObjects.end();
	for(; it != end; ++it)
		it->second->Process(tnow, tdiff);
	}


	//process player object
	if(m_controllerChar)
		m_controllerChar->Process(tnow, tdiff);

	if(m_controllerCam)
		m_controllerCam->Process();



}





/***********************************************************
add object to the scene
***********************************************************/
void LbaNetModel::AddObject(LbaNet::ObjectTypeEnum OType, const ObjectInfo &desc, 
							const LbaNet::ModelInfo &DisplayDesc)
{
	switch(OType)
	{
		// 1 -> static object
	case LbaNet::StaticObject:
			{
			boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
			_staticObjects[desc.Id] = tmpobj;
			}
		break;

		// 2 -> server controlled
		case LbaNet::CpuObject:
			{
			boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
			_serverObjects[desc.Id] = tmpobj;
			}
		break;

		// 3 -> movable by player
		case LbaNet::MovableObject:
			{
			boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
			_movableObjects[desc.Id] = tmpobj;
			}
		break;

		// 4 -> player object
		case LbaNet::PlayerObject:
			//special treatment if main player
			if(m_playerObjectId == desc.Id)
			{
				// change to character controller
				ObjectInfo tmp(desc);
				static_cast<PhysicalDescriptionWithShape *>(tmp.PhysInfo.get())->ActorType = LbaNet::CharControlAType;

				boost::shared_ptr<DynamicObject> playerObject = tmp.BuildSelf(OsgHandler::getInstance());

				if(m_controllerChar)
					m_controllerChar->SetPhysicalCharacter(playerObject, DisplayDesc);
				if(m_controllerCam)
					m_controllerCam->SetCharacter(playerObject);
			}
			else
			{
				boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
				_playerObjects[desc.Id] = boost::shared_ptr<ExternalPlayer>(new ExternalPlayer(tmpobj));
			}
		break;

		// 5 -> ghost object
		case LbaNet::GhostObject:
			{
			boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
			_ghostObjects[desc.Id] = tmpobj;
			}
		break;
	}
}


/***********************************************************
remove object from the scene
***********************************************************/
void LbaNetModel::RemObject(LbaNet::ObjectTypeEnum OType, long id)
{
	switch(OType)
	{
		// 1 -> static object
		case LbaNet::StaticObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _staticObjects.find(id);
			if(it != _staticObjects.end())
				_staticObjects.erase(it);
			}
		break;

		// 2 -> server controlled
		case LbaNet::CpuObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _serverObjects.find(id);
			if(it != _serverObjects.end())
				_serverObjects.erase(it);
			}
		break;

		// 3 -> movable by player
		case LbaNet::MovableObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _movableObjects.find(id);
			if(it != _movableObjects.end())
				_movableObjects.erase(it);
			}
		break;

		// 4 -> player object
		case LbaNet::PlayerObject:
			//special treatment if main player
			if(m_playerObjectId == id)
			{
				ResetPlayerObject();
			}
			else
			{
				std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.find(id);
				if(it != _playerObjects.end())
					_playerObjects.erase(it);
			}
		break;

		// 5 -> ghost object
		case LbaNet::GhostObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.find(id);
			if(it != _ghostObjects.end())
				_ghostObjects.erase(it);
			}
		break;
	}
}

/***********************************************************
clean up map
***********************************************************/
void LbaNetModel::CleanupMap()
{
	//clear dynamic object of the current scene
	_staticObjects.clear();
	_serverObjects.clear();
	_movableObjects.clear();
	_playerObjects.clear();
	_ghostObjects.clear();

	//clean up player
	ResetPlayerObject();
}


/***********************************************************
clean up everything
***********************************************************/
void LbaNetModel::CleanupWorld()
{
	CleanupMap();
}


/***********************************************************
pause the game
***********************************************************/
void LbaNetModel::Pause()
{
	m_paused = true;
}


/***********************************************************
resume the game
***********************************************************/
void LbaNetModel::Resume()
{
	m_paused = false;
}



/***********************************************************
reset player object
***********************************************************/
void LbaNetModel::ResetPlayerObject()
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo(new SimplePhysicalObjectHandler(0, 0, 0, LbaQuaternion()));
	boost::shared_ptr<DynamicObject> playerObject = boost::shared_ptr<DynamicObject>(new StaticObject(physo, boost::shared_ptr<DisplayObjectHandlerBase>(), m_playerObjectId));

	if(m_controllerChar)
		m_controllerChar->SetPhysicalCharacter(playerObject, LbaNet::ModelInfo(), true);
	if(m_controllerCam)
		m_controllerCam->SetCharacter(playerObject, true);
}





/***********************************************************
 add object from server
 type:
1 -> static object
2 -> server controlled
3 -> movable by player
4 -> player object
5 -> ghost object
***********************************************************/
void LbaNetModel::AddObject(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId, 
					const LbaNet::ModelInfo &DisplayDesc, 
					const LbaNet::ObjectPhysicDesc &PhysicDesc)
{
	boost::shared_ptr<DisplayInfo> DInfo;

	// create display object
	switch(DisplayDesc.TypeRenderer)
	{
		//0 -> osg model 
		case LbaNet::RenderOsgModel:
		{
			if(DisplayDesc.ModelName != "")
			{
				boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
					(new OsgSimpleObjectDescription(DisplayDesc.ModelName, false)); //TODO make it configurable

				boost::shared_ptr<DisplayTransformation> tr;
				DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(tr, dispobdesc));
			}
			else
			{
				//TODO
			}
		}
		break;

		//1 -> sprite 
		case LbaNet::RenderSprite:
		{
			//TODO
		}
		break;

		//2 -> LBA1 model 
		case LbaNet::RenderLba1M:
		{
			//TODO animation speed
			boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
				(new Lba1ModelObjectDescription(DisplayDesc, _LBA1_MODEL_ANIMATION_SPEED_));

			boost::shared_ptr<DisplayTransformation> Tr(new DisplayTransformation());
			Tr->scaleY = 2;
			DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(Tr, dispobdesc));
		}
		break;

		//3-> LBA2 model
		case LbaNet::RenderLba2M:
		{
			//TODO
		}
		break;

	}

	// create physic object
	boost::shared_ptr<PhysicalDescriptionBase> PInfo;
	switch(PhysicDesc.TypeShape)
	{
		// 0= no shape
		case LbaNet::NoShape:
		{
			PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
					PhysicalDescriptionNoShape(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z, 
										LbaQuaternion(PhysicDesc.Pos.Rotation, LbaVec3(0, 1, 0))));

		}
		break;

		
		// 1 = Box
		case LbaNet::BoxShape:
		{
				PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
					PhysicalDescriptionBox(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z, 
										PhysicDesc.TypePhysO, PhysicDesc.Density,
										LbaQuaternion(PhysicDesc.Pos.Rotation, LbaVec3(0, 1, 0)),
										PhysicDesc.SizeX, PhysicDesc.SizeY, PhysicDesc.SizeZ,
										PhysicDesc.Collidable));
		}
		break;

		// 2 = Capsule
		case LbaNet::CapsuleShape:
		{
				PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
					PhysicalDescriptionCapsule(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z, 
										PhysicDesc.TypePhysO, PhysicDesc.Density,
										LbaQuaternion(PhysicDesc.Pos.Rotation, LbaVec3(0, 1, 0)),
										PhysicDesc.SizeX, PhysicDesc.SizeY,
										PhysicDesc.Collidable));
		}
		break;

		// 3 = Sphere
		case LbaNet::SphereShape:
		{
				// TODO
				//PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
				//	PhysicalDescriptionCapsule(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z, 
				//						PhysicDesc.TypePhysO, PhysicDesc.Density,
				//						LbaQuaternion(PhysicDesc.Pos.Rotation, LbaVec3(0, 1, 0)),
				//						PhysicDesc.SizeY, 
				//						PhysicDesc.Collidable));
		}
		break;

		// 4 = triangle mesh
		case LbaNet::TriangleMeshShape:
		{
				PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
					PhysicalDescriptionTriangleMesh(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z, 
										PhysicDesc.Filename,
										PhysicDesc.Collidable));
		}
		break;

	}

	ObjectInfo obj((long)ObjectId, DInfo, PInfo, (OType == LbaNet::StaticObject));
	AddObject(OType, obj, DisplayDesc);
}



/***********************************************************
 remove object from server	
 type:
1 -> static object
2 -> server controlled
3 -> movable by player
4 -> player object
5 -> ghost object
***********************************************************/
void LbaNetModel::RemoveObject(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId)
{
	RemObject(OType, (long)ObjectId);
}


/***********************************************************
update object from server
***********************************************************/
void LbaNetModel::UpdateObjectDisplay(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId, 
									  LbaNet::DisplayObjectUpdateBasePtr update)
{
	switch(OType)
	{
		// 1 -> static object
		case LbaNet::StaticObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _staticObjects.find((long)ObjectId);
			if(it != _staticObjects.end())
				it->second->GetDisplayObject()->Update(update);
			}
		break;

		// 2 -> server controlled
		case LbaNet::CpuObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _serverObjects.find((long)ObjectId);
			if(it != _serverObjects.end())
				it->second->GetDisplayObject()->Update(update);
			}
		break;

		// 3 -> movable by player
		case LbaNet::MovableObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _movableObjects.find((long)ObjectId);
			if(it != _movableObjects.end())
				it->second->GetDisplayObject()->Update(update);
			}
		break;

		// 4 -> player object
		case LbaNet::PlayerObject:
			//special treatment if main player
			if(m_playerObjectId == (long)ObjectId)
			{
				m_controllerChar->UpdateDisplay(update);
			}
			else
			{
				std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.find((long)ObjectId);
				if(it != _playerObjects.end())
					it->second->GetDisplayObject()->Update(update);
			}
		break;

		// 5 -> ghost object
		case LbaNet::GhostObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.find((long)ObjectId);
			if(it != _ghostObjects.end())
				it->second->GetDisplayObject()->Update(update);
			}
		break;
	}
}



/***********************************************************
key pressed
***********************************************************/
void LbaNetModel::KeyPressed(LbanetKey keyid)
{
	if(m_controllerChar)
		m_controllerChar->KeyPressed(keyid);
}

/***********************************************************
key released
***********************************************************/
void LbaNetModel::KeyReleased(LbanetKey keyid)
{
	if(m_controllerChar)
		m_controllerChar->KeyReleased(keyid);
}


/***********************************************************
when update player position
***********************************************************/
void LbaNetModel::PlayerMovedUpdate(Ice::Long PlayerId, double updatetime, 
									const LbaNet::PlayerMoveInfo &info)
{
	std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.find((long)PlayerId);
	if(it != _playerObjects.end())
	{
		it->second->UpdateMove(updatetime, info);
	}
}


/***********************************************************
called when we enter a new map
***********************************************************/
void LbaNetModel::NewMap(const std::string & NewMap, const std::string & Script)
{
	Pause();

	// clean old map
	CleanupMap();

	m_current_map_name = NewMap;

	//TODO script part

	// to remove that
	OsgHandler::getInstance()->ResetDisplayTree();
	LbaMainLightInfo lightinfo(0, 100, 50);
	OsgHandler::getInstance()->SetLight(lightinfo);


	// ask server to get a refresh of all objects
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::RefreshObjectRequestEvent(
										SynchronizedTimeHandler::GetCurrentTimeDouble()));

	
}


/***********************************************************
map is fully refreshed
***********************************************************/
void LbaNetModel::RefreshEnd()
{
	Resume();
}