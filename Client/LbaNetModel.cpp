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



/***********************************************************
	Constructor
***********************************************************/
LbaNetModel::LbaNetModel()
: m_playerObjectId(0), m_paused(false)
{
	LogHandler::getInstance()->LogToFile("Initializing model class...");
	m_lasttime = SynchronizedTimeHandler::GetCurrentTimeDouble();

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
void LbaNetModel::Process()
{
	if(m_paused)
		return;


	double ctime = SynchronizedTimeHandler::GetCurrentTimeDouble();

	// process all _serverObjects
	{
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _serverObjects.begin();
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator end = _serverObjects.end();
	for(; it != end; ++it)
		it->second->Process();
	}

	// process all _movableObjects
	{
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _movableObjects.begin();
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator end = _movableObjects.end();
	for(; it != end; ++it)
		it->second->Process();
	}

	// process all _playerObjects
	{
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _playerObjects.begin();
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator end = _playerObjects.end();
	for(; it != end; ++it)
		it->second->Process();
	}

	// process all _ghostObjects
	{
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.begin();
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator end = _ghostObjects.end();
	for(; it != end; ++it)
		it->second->Process();
	}


	//process player object
	if(m_playerObject)
		m_playerObject->Process();

	if(m_controllerCam)
		m_controllerCam->Process();



	//double currtime = ctime*0.001;
	//float diff = (float)(currtime-m_lasttime);
	//m_lasttime = currtime;

	// process controllers
	//if(m_controllerChar)
	//	m_controllerChar->Process(ctime, diff);

}





/***********************************************************
add object to the scene
***********************************************************/
void LbaNetModel::AddObject(int type, const ObjectInfo &desc)
{
	switch(type)
	{
		// 1 -> static object
		case 1:
			{
			boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
			_staticObjects[desc.Id] = tmpobj;
			}
		break;

		// 2 -> server controlled
		case 2:
			{
			boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
			_serverObjects[desc.Id] = tmpobj;
			}
		break;

		// 3 -> movable by player
		case 3:
			{
			boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
			_movableObjects[desc.Id] = tmpobj;
			}
		break;

		// 4 -> player object
		case 4:
			//special treatment if main player
			if(m_playerObjectId == desc.Id)
			{
				// change to character controller
				ObjectInfo tmp(desc);
				static_cast<PhysicalDescriptionWithShape *>(tmp.PhysInfo.get())->type = 4;

				m_playerObject = tmp.BuildSelf(OsgHandler::getInstance());

				if(m_controllerChar)
					m_controllerChar->SetPhysicalCharacter(m_playerObject->GetPhysicalObject());
				if(m_controllerCam)
					m_controllerCam->SetCharacter(m_playerObject);
			}
			else
			{
				boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
				_playerObjects[desc.Id] = tmpobj;
			}
		break;

		// 5 -> ghost object
		case 5:
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
void LbaNetModel::RemObject(int type, long id)
{
	switch(type)
	{
		// 1 -> static object
		case 1:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _staticObjects.find(id);
			if(it != _staticObjects.end())
				_staticObjects.erase(it);
			}
		break;

		// 2 -> server controlled
		case 2:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _serverObjects.find(id);
			if(it != _serverObjects.end())
				_serverObjects.erase(it);
			}
		break;

		// 3 -> movable by player
		case 3:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _movableObjects.find(id);
			if(it != _movableObjects.end())
				_movableObjects.erase(it);
			}
		break;

		// 4 -> player object
		case 4:
			//special treatment if main player
			if(m_playerObjectId == id)
			{
				ResetPlayerObject();
			}
			else
			{
				std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _playerObjects.find(id);
				if(it != _playerObjects.end())
					_playerObjects.erase(it);
			}
		break;

		// 5 -> ghost object
		case 5:
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
	m_lasttime = SynchronizedTimeHandler::GetCurrentTimeDouble();
	m_paused = true;
}


/***********************************************************
resume the game
***********************************************************/
void LbaNetModel::Resume(bool reinit)
{
	m_lasttime = SynchronizedTimeHandler::GetCurrentTimeDouble();
	m_paused = false;
}



/***********************************************************
reset player object
***********************************************************/
void LbaNetModel::ResetPlayerObject()
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo(new SimplePhysicalObjectHandler(0, 0, 0, LbaQuaternion()));
	m_playerObject = boost::shared_ptr<DynamicObject>(new StaticObject(physo, boost::shared_ptr<DisplayObjectHandlerBase>(), m_playerObjectId));

	if(m_controllerChar)
		m_controllerChar->SetPhysicalCharacter(m_playerObject->GetPhysicalObject(), true);
	if(m_controllerCam)
		m_controllerCam->SetCharacter(m_playerObject, true);
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
void LbaNetModel::AddObject(int Type, Ice::Long ObjectId, 
					const LbaNet::ModelInfo &DisplayDesc, 
					const LbaNet::ObjectPhysicDesc &PhysicDesc)
{
	boost::shared_ptr<DisplayInfo> DInfo;

	// create display object
	switch(DisplayDesc.RendererType)
	{
		//0 -> osg model 
		case 0:
		{
			if(DisplayDesc.ModelName != "")
			{
				boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
					(new OsgSimpleObjectDescription(DisplayDesc.ModelName));

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
		case 1:
		{
			//TODO
		}
		break;

		//2 -> LBA1 model 
		case 2:
		{
			//TODO
			boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
				(new OsgOrientedCapsuleDescription(5, 0.5, 1, 0, 0, 1));

			boost::shared_ptr<DisplayTransformation> Tr(new DisplayTransformation());
			Tr->translationY = 4;
			Tr->rotation = LbaQuaternion(90, LbaVec3(1, 0, 0));
			DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(Tr, dispobdesc));
		}
		break;

		//3-> LBA2 model
		case 3:
		{
			//TODO
		}
		break;

	}

	// create physic object
	boost::shared_ptr<PhysicalDescriptionBase> PInfo;
	switch(PhysicDesc.Type)
	{
		// 0= no shape
		case 0:
		{
			PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
					PhysicalDescriptionNoShape(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z, 
										LbaQuaternion(PhysicDesc.Pos.Rotation, LbaVec3(0, 1, 0))));

		}
		break;

		
		// 1 = Box
		case 1:
		{
				PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
					PhysicalDescriptionBox(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z, 
										PhysicDesc.ShapeType, PhysicDesc.Density,
										LbaQuaternion(PhysicDesc.Pos.Rotation, LbaVec3(0, 1, 0)),
										PhysicDesc.SizeX, PhysicDesc.SizeY, PhysicDesc.SizeZ,
										PhysicDesc.Collidable));
		}
		break;

		// 2 = Capsule
		case 2:
		{
				PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
					PhysicalDescriptionCapsule(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z, 
										PhysicDesc.ShapeType, PhysicDesc.Density,
										LbaQuaternion(PhysicDesc.Pos.Rotation, LbaVec3(0, 1, 0)),
										PhysicDesc.Radius, PhysicDesc.Height,
										PhysicDesc.Collidable));
		}
		break;

		// 3 = Sphere
		case 3:
		{
				// TODO
				//PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
				//	PhysicalDescriptionCapsule(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z, 
				//						PhysicDesc.ShapeType, PhysicDesc.Density,
				//						LbaQuaternion(PhysicDesc.Pos.Rotation, LbaVec3(0, 1, 0)),
				//						PhysicDesc.Radius, 
				//						PhysicDesc.Collidable));
		}
		break;

		// 4 = triangle mesh
		case 4:
		{
				PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
					PhysicalDescriptionTriangleMesh(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z, 
										PhysicDesc.Filename,
										PhysicDesc.Collidable));
		}
		break;

	}

	ObjectInfo obj((long)ObjectId, DInfo, PInfo, (Type == 1));
	AddObject(Type, obj);
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
void LbaNetModel::RemoveObject(int Type, Ice::Long ObjectId)
{
	RemObject(Type, (long)ObjectId);
}


/***********************************************************
update object from server
***********************************************************/
void LbaNetModel::UpdateObjectDisplay(int Type, Ice::Long ObjectId, 
									  const LbaNet::ModelInfo &DisplayDesc)
{
	//TODO
}


/***********************************************************
 update object from server
***********************************************************/
void LbaNetModel::UpdateObjectPhysic(int Type, Ice::Long ObjectId, 
									 const LbaNet::ObjectPhysicDesc &PhysicDesc)
{
	//TODO
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