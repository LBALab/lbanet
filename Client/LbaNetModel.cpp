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
#include "ClientLuaHandler.h"
#include "DataLoader.h"


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

	//data loader init
	DataLoader::getInstance()->SetWorldName(NewWorld);

	//script part
	m_luaHandler = boost::shared_ptr<ClientLuaHandler>(new  ClientLuaHandler(this));
	m_luaHandler->LoadFile("LuaCommon/ClientHelperFunctions.lua");
	m_luaHandler->LoadFile("Worlds/" + NewWorld + "/Lua/global_client.lua");
}




/***********************************************************
do all check to be done when idle
***********************************************************/
void LbaNetModel::Process(double tnow, float tdiff)
{
	if(m_paused)
		return;


	// process all _npcObjects
	{
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _npcObjects.begin();
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator end = _npcObjects.end();
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


	// process all editor Objects
	#ifdef _USE_QT_EDITOR_
	{
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _editorObjects.begin();
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator end = _editorObjects.end();
	for(; it != end; ++it)
		it->second->Process(tnow, tdiff);
	}
	#endif


	//process player object
	if(m_controllerChar)
		m_controllerChar->Process(tnow, tdiff, m_luaHandler);

	if(m_controllerCam)
		m_controllerCam->Process(tnow, tdiff);



}





/***********************************************************
add object to the scene
***********************************************************/
void LbaNetModel::AddObject(LbaNet::ObjectTypeEnum OType, const ObjectInfo &desc, 
								const LbaNet::ModelInfo &DisplayDesc,
								const LbaNet::ObjectExtraInfo &extrainfo,
								const LbaNet::LifeManaInfo &lifeinfo)
{
	switch(OType)
	{
		// 1 -> npc object
		case LbaNet::NpcObject:
			{
				boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
				_npcObjects[desc.Id] = tmpobj;
				if(tmpobj->GetDisplayObject())
				{
					std::stringstream strs;
					strs << "A_" << desc.Id;
					tmpobj->GetDisplayObject()->SetName(strs.str());
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectExtraInfoUpdate(extrainfo));
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectLifeInfoUpdate(lifeinfo));
				}
			}
		break;


		// 2 -> player object
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

				if(playerObject->GetDisplayObject())
				{
					std::stringstream strs;
					strs << "M_" << desc.Id;
					playerObject->GetDisplayObject()->SetName(strs.str());
					m_controllerChar->UpdateDisplay(new LbaNet::ObjectExtraInfoUpdate(extrainfo));
					m_controllerChar->UpdateDisplay(new LbaNet::ObjectLifeInfoUpdate(lifeinfo));
				}
			}
			else
			{
				boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
				_playerObjects[desc.Id] = boost::shared_ptr<ExternalPlayer>(new ExternalPlayer(tmpobj, DisplayDesc));
				if(tmpobj->GetDisplayObject())
				{
					std::stringstream strs;
					strs << "P_" << desc.Id;
					tmpobj->GetDisplayObject()->SetName(strs.str());
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectExtraInfoUpdate(extrainfo));
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectLifeInfoUpdate(lifeinfo));
				}
			}
		break;

		// 3 -> ghost object
		case LbaNet::GhostObject:
			{
				boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
				_ghostObjects[desc.Id] = tmpobj;
				if(tmpobj->GetDisplayObject())
				{
					std::stringstream strs;
					strs << "G_" << desc.Id;
					tmpobj->GetDisplayObject()->SetName(strs.str());
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectExtraInfoUpdate(extrainfo));
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectLifeInfoUpdate(lifeinfo));
				}
			}
		break;


		// editor object
		#ifdef _USE_QT_EDITOR_
		case LbaNet::EditorObject:
			{
				boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
				_editorObjects[desc.Id] = tmpobj;
				if(tmpobj->GetDisplayObject())
				{
					std::stringstream strs;
					strs << "E_" << desc.Id;
					tmpobj->GetDisplayObject()->SetName(strs.str());
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectExtraInfoUpdate(extrainfo));
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectLifeInfoUpdate(lifeinfo));
				}
			}
		break;
		#endif
	}
}


/***********************************************************
remove object from the scene
***********************************************************/
void LbaNetModel::RemObject(LbaNet::ObjectTypeEnum OType, long id)
{
	switch(OType)
	{
		// 1 -> npc object
		case LbaNet::NpcObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _npcObjects.find(id);
			if(it != _npcObjects.end())
				_npcObjects.erase(it);
			}
		break;

		// 2 -> player object
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

		// 3 -> ghost object
		case LbaNet::GhostObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.find(id);
			if(it != _ghostObjects.end())
				_ghostObjects.erase(it);
			}
		break;

		// editor object
		#ifdef _USE_QT_EDITOR_
		case LbaNet::EditorObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _editorObjects.find(id);
			if(it != _editorObjects.end())
				_editorObjects.erase(it);
			}
		break;
		#endif
	}
}

/***********************************************************
clean up map
***********************************************************/
void LbaNetModel::CleanupMap()
{
	//clean up player
	ResetPlayerObject();

	//clear dynamic object of the current scene
	_npcObjects.clear();
	_playerObjects.clear();
	_ghostObjects.clear();

	#ifdef _USE_QT_EDITOR_
	_editorObjects.clear();
	#endif
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
1 -> npc object
2 -> player object
3 -> ghost object
***********************************************************/
void LbaNetModel::AddObject(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId, 
					const LbaNet::ModelInfo &DisplayDesc, 
					const LbaNet::ObjectPhysicDesc &PhysicDesc,
					const LbaNet::ObjectExtraInfo &extrainfo,
					const LbaNet::LifeManaInfo &lifeinfo)
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
					(new OsgSimpleObjectDescription(DisplayDesc.ModelName, 
								DisplayDesc.UseLight, DisplayDesc.CastShadow, extrainfo));

				boost::shared_ptr<DisplayTransformation> tr( new DisplayTransformation());
				tr->translationX = DisplayDesc.TransX;
				tr->translationY = DisplayDesc.TransY;
				tr->translationZ = DisplayDesc.TransZ;

				tr->rotation.AddRotation(DisplayDesc.RotX, LbaVec3(1,0,0));
				tr->rotation.AddRotation(DisplayDesc.RotY, LbaVec3(0,1,0));
				tr->rotation.AddRotation(DisplayDesc.RotZ, LbaVec3(0,0,1));

				tr->scaleX = DisplayDesc.ScaleX;
				tr->scaleY = DisplayDesc.ScaleY;
				tr->scaleZ = DisplayDesc.ScaleZ;

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
				(new Lba1ModelObjectDescription(DisplayDesc, _LBA1_MODEL_ANIMATION_SPEED_,
													extrainfo, lifeinfo));

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

		//RenderCross
		case LbaNet::RenderCross:
		{
			boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
				(new OsgCrossDescription(PhysicDesc.SizeX, 
				DisplayDesc.ColorR, DisplayDesc.ColorG, DisplayDesc.ColorB, DisplayDesc.ColorA, extrainfo));


			boost::shared_ptr<DisplayTransformation> tr( new DisplayTransformation());
			tr->translationX = DisplayDesc.TransX;
			tr->translationY = DisplayDesc.TransY;
			tr->translationZ = DisplayDesc.TransZ;

			tr->rotation.AddRotation(DisplayDesc.RotX, LbaVec3(1,0,0));
			tr->rotation.AddRotation(DisplayDesc.RotY, LbaVec3(0,1,0));
			tr->rotation.AddRotation(DisplayDesc.RotZ, LbaVec3(0,0,1));

			tr->scaleX = DisplayDesc.ScaleX;
			tr->scaleY = DisplayDesc.ScaleY;
			tr->scaleZ = DisplayDesc.ScaleZ;

			DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(tr, dispobdesc));
		}
		break;

		//RenderBox
		case LbaNet::RenderBox:
		{
			boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
				(new OsgBoxDescription(PhysicDesc.SizeX, PhysicDesc.SizeY, PhysicDesc.SizeZ, 
				DisplayDesc.ColorR, DisplayDesc.ColorG, DisplayDesc.ColorB, DisplayDesc.ColorA, extrainfo));


			boost::shared_ptr<DisplayTransformation> tr( new DisplayTransformation());
			tr->translationX = DisplayDesc.TransX;
			tr->translationY = DisplayDesc.TransY;
			tr->translationZ = DisplayDesc.TransZ;

			tr->rotation.AddRotation(DisplayDesc.RotX, LbaVec3(1,0,0));
			tr->rotation.AddRotation(DisplayDesc.RotY, LbaVec3(0,1,0));
			tr->rotation.AddRotation(DisplayDesc.RotZ, LbaVec3(0,0,1));

			tr->scaleX = DisplayDesc.ScaleX;
			tr->scaleY = DisplayDesc.ScaleY;
			tr->scaleZ = DisplayDesc.ScaleZ;

			DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(tr, dispobdesc));
		}
		break;

		//RenderCapsule
		case LbaNet::RenderCapsule:
		{
			boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
				(new OsgOrientedCapsuleDescription(PhysicDesc.SizeY, PhysicDesc.SizeX, 
				DisplayDesc.ColorR, DisplayDesc.ColorG, DisplayDesc.ColorB, DisplayDesc.ColorA, extrainfo));

			boost::shared_ptr<DisplayTransformation> tr( new DisplayTransformation());
			tr->translationX = DisplayDesc.TransX;
			tr->translationY = DisplayDesc.TransY;
			tr->translationZ = DisplayDesc.TransZ;

			tr->rotation.AddRotation(DisplayDesc.RotX, LbaVec3(1,0,0));
			tr->rotation.AddRotation(DisplayDesc.RotY, LbaVec3(0,1,0));
			tr->rotation.AddRotation(DisplayDesc.RotZ, LbaVec3(0,0,1));

			tr->scaleX = DisplayDesc.ScaleX;
			tr->scaleY = DisplayDesc.ScaleY;
			tr->scaleZ = DisplayDesc.ScaleZ;

			DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(tr, dispobdesc));
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
				PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
					PhysicalDescriptionSphere(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z, 
										PhysicDesc.TypePhysO, PhysicDesc.Density,
										LbaQuaternion(PhysicDesc.Pos.Rotation, LbaVec3(0, 1, 0)),
										PhysicDesc.SizeY, 
										PhysicDesc.Collidable));
		}
		break;

		// 4 = triangle mesh
		case LbaNet::TriangleMeshShape:
		{
				PInfo = boost::shared_ptr<PhysicalDescriptionBase>(new 
					PhysicalDescriptionTriangleMesh(PhysicDesc.Pos.X, PhysicDesc.Pos.Y, PhysicDesc.Pos.Z,
										LbaQuaternion(PhysicDesc.Pos.Rotation, LbaVec3(0, 1, 0)),
										PhysicDesc.Filename,
										PhysicDesc.Collidable));
		}
		break;

	}
#ifdef _USE_QT_EDITOR_
	ObjectInfo obj((long)ObjectId, DInfo, PInfo, false); // make all objects dynamic in editor as we can change them
#else
	ObjectInfo obj((long)ObjectId, DInfo, PInfo, (PhysicDesc.TypePhysO == LbaNet::StaticAType));
#endif
	AddObject(OType, obj, DisplayDesc, extrainfo, lifeinfo);
}



/***********************************************************
 remove object from server	
 type:
1 -> npc object
2 -> player object
3 -> ghost object
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
		// 1 -> npc object
		case LbaNet::NpcObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _npcObjects.find((long)ObjectId);
			if(it != _npcObjects.end())
				it->second->GetDisplayObject()->Update(update);
			}
		break;


		// 2 -> player object
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
					it->second->UpdateDisplay(update);
			}
		break;

		// 3 -> ghost object
		case LbaNet::GhostObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.find((long)ObjectId);
			if(it != _ghostObjects.end())
				it->second->GetDisplayObject()->Update(update);
			}
		break;

		// editor object
		#ifdef _USE_QT_EDITOR_
		case LbaNet::EditorObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _editorObjects.find((long)ObjectId);
			if(it != _editorObjects.end())
				it->second->GetDisplayObject()->Update(update);
			}
		break;
		#endif
	}
}


/***********************************************************
update object physic
***********************************************************/
void LbaNetModel::UpdateObjectPhysic(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId, 
								  LbaNet::PhysicObjectUpdateBasePtr update)
{
	switch(OType)
	{
		// 1 -> npc object
		case LbaNet::NpcObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _npcObjects.find((long)ObjectId);
			if(it != _npcObjects.end())
				it->second->GetPhysicalObject()->Update(update);
			}
		break;


		// 2 -> player object
		case LbaNet::PlayerObject:
			//special treatment if main player
			if(m_playerObjectId == (long)ObjectId)
			{
				m_controllerChar->UpdatePhysic(update);
			}
			else
			{
				std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.find((long)ObjectId);
				if(it != _playerObjects.end())
					it->second->UpdatePhysic(update);
			}
		break;

		// 3 -> ghost object
		case LbaNet::GhostObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.find((long)ObjectId);
			if(it != _ghostObjects.end())
				it->second->GetPhysicalObject()->Update(update);
			}
		break;

		// editor object
		#ifdef _USE_QT_EDITOR_
		case LbaNet::EditorObject:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _editorObjects.find((long)ObjectId);
			if(it != _editorObjects.end())
				it->second->GetPhysicalObject()->Update(update);
			}
		break;
		#endif
	}
}




/***********************************************************
key pressed
***********************************************************/
void LbaNetModel::KeyPressed(LbanetKey keyid)
{
	if(m_controllerChar)
		m_controllerChar->KeyPressed(keyid);

	if(m_controllerCam)
		m_controllerCam->KeyPressed(keyid);
}

/***********************************************************
key released
***********************************************************/
void LbaNetModel::KeyReleased(LbanetKey keyid)
{
	if(m_controllerChar)
		m_controllerChar->KeyReleased(keyid);

	if(m_controllerCam)
		m_controllerCam->KeyReleased(keyid);
}


/***********************************************************
when update player position
***********************************************************/
void LbaNetModel::PlayerMovedUpdate(Ice::Long PlayerId, double updatetime, 
									const LbaNet::PlayerMoveInfo &info,
									bool teleport)
{
	std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.find((long)PlayerId);
	if(it != _playerObjects.end())
	{
		it->second->UpdateMove(updatetime, info, teleport);
	}
	else
	{
		if(teleport && (m_playerObjectId == (long)PlayerId))
		{
			m_controllerChar->Teleport(info);

			EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ReadyToPlayEvent(
				SynchronizedTimeHandler::GetCurrentTimeDouble()));
		}
	}
}


/***********************************************************
called when we enter a new map
***********************************************************/
void LbaNetModel::NewMap(const std::string & NewMap, const std::string & Script,
							int AutoCameraType)
{
	Pause();

	// clean old map
	CleanupMap();

	m_current_map_name = NewMap;


	// todo remove that
	OsgHandler::getInstance()->ResetDisplayTree();
	LbaMainLightInfo lightinfo(0, 100, 50);
	OsgHandler::getInstance()->SetLight(lightinfo);


	// ask server to get a refresh of all objects
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::RefreshObjectRequestEvent(
										SynchronizedTimeHandler::GetCurrentTimeDouble()));


	OsgHandler::getInstance()->ToggleAutoCameraType(AutoCameraType);
}


/***********************************************************
map is fully refreshed
***********************************************************/
void LbaNetModel::RefreshEnd()
{
	// tell server that we are ready to play
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ReadyToPlayEvent(
										SynchronizedTimeHandler::GetCurrentTimeDouble()));

	OsgHandler::getInstance()->OptimizeScene();
	Resume();
}



/***********************************************************
center the camera on player
***********************************************************/
void LbaNetModel::CenterCamera()
{
	if(m_controllerCam)
		m_controllerCam->Center();
}



/***********************************************************
start lua script in a separate thread
***********************************************************/
void LbaNetModel::StartScript(const std::string & FunctionName)
{
	if(m_luaHandler)
		m_luaHandler->StartScript(FunctionName);
}


/***********************************************************
used by lua to get an actor Position
if id < 1 then it get player position
***********************************************************/
LbaVec3 LbaNetModel::GetActorPosition(long ActorId)
{
	LbaVec3 res;

	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->GetPhysicalObject()->GetPosition(res.x, res.y, res.z);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->GetPosition(res.x, res.y, res.z);
	}

	return res;
}


/***********************************************************
used by lua to get an actor Rotation
if id < 1 then it get player position
***********************************************************/
float LbaNetModel::GetActorRotation(long ActorId)
{
	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			return it->second->GetPhysicalObject()->GetRotationYAxis();
	}
	else
	{
		// on player
		if(m_controllerChar)
			return m_controllerChar->GetRotation();
	}

	return 0;
}


 /***********************************************************
used by lua to get an actor Rotation
if id < 1 then it get player position
***********************************************************/
LbaQuaternion LbaNetModel::GetActorRotationQuat(long ActorId)
{
	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
		{
			LbaQuaternion res;
			it->second->GetPhysicalObject()->GetRotation(res);
			return res;
		}
	}
	else
	{
		// on player
		if(m_controllerChar)
			return m_controllerChar->GetRotationQuat();
	}

	return LbaQuaternion();
}



/***********************************************************
 used by lua to update an actor animation
 if id < 1 then it get player position
***********************************************************/
void LbaNetModel::UpdateActorAnimation(long ActorId, const std::string & AnimationString)
{
	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->GetDisplayObject()->Update(new LbaNet::AnimationStringUpdate(AnimationString));
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->UpdateAnimation(AnimationString);
	}
}



/***********************************************************
//! used by lua to update an actor mode
//! if id < 1 then it get player position
***********************************************************/
void LbaNetModel::UpdateActorMode(long ActorId, const std::string & Mode)
{
	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
		{
			LbaNet::ModelInfo model = it->second->GetDisplayObject()->GetCurrentModel();
			model.Mode = Mode;
			it->second->GetDisplayObject()->Update(new LbaNet::ModelUpdate(model, false));
		}
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->UpdateActorMode(Mode);
	}
}



/***********************************************************
used by lua to move an actor or player
if id < 1 then it moves players
the actor will move using animation speed
***********************************************************/
void LbaNetModel::ActorStraightWalkTo(int ScriptId, long ActorId, const LbaVec3 &Position)
{
	if(ActorId >= 0)
	{
		// on actor
		//TODO
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->ActorStraightWalkTo(ScriptId, Position.x, Position.y, Position.z);
	}
}



/***********************************************************
//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
***********************************************************/
void LbaNetModel::ActorRotate(int ScriptId, long ActorId, float Angle, float RotationSpeedPerSec,
								bool ManageAnimation)
{
	if(ActorId >= 0)
	{
		// on actor
		//TODO
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->ActorRotate(ScriptId, Angle, RotationSpeedPerSec, ManageAnimation);
	}
}


/***********************************************************
//! used by lua to wait until an actor animation is finished
//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
***********************************************************/
void LbaNetModel::ActorAnimate(int ScriptId, long ActorId, bool AnimationMove)
{
	if(ActorId >= 0)
	{
		// on actor
		//TODO
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->ActorAnimate(ScriptId, AnimationMove);
	}
}


/***********************************************************
execute lua script given as a string
***********************************************************/
void LbaNetModel::ExecuteScriptString( const std::string &ScriptString )
{
	if(m_luaHandler)
		m_luaHandler->ExecuteScriptString(ScriptString);
}





#ifdef _USE_QT_EDITOR_
/***********************************************************
editor tp the player
***********************************************************/
void LbaNetModel::EditorTpPlayer(float posx, float posy, float posz)
{
	LbaNet::PlayerMoveInfo info;
	info.CurrentPos.X = posx;
	info.CurrentPos.Y = posy;
	info.CurrentPos.Z = posz;
	info.CurrentPos.Rotation = 0;
	m_controllerChar->Teleport(info);
}


/***********************************************************
force the camera in ghost mode or not
***********************************************************/
void LbaNetModel::ForceGhost(bool force)
{
	m_controllerChar->ForceGhost(force);
	m_controllerCam->ForceGhost(force);
}

#endif

