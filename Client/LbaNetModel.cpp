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
#include "ExternalActor.h"
#include "ProjectileHandler.h"
#include "ClientExtendedTypes.h"


#define	_LBA1_MODEL_ANIMATION_SPEED_	1.8f

/***********************************************************
	Constructor
***********************************************************/
LbaNetModel::LbaNetModel()
: m_playerObjectId(0), m_paused(false), m_newworld(false)
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
	m_current_world_name = NewWorld;

	//script part
	m_luaHandler = boost::shared_ptr<ClientLuaHandler>(new  ClientLuaHandler());
	m_luaHandler->LoadFile("LuaCommon/ClientHelperFunctions.lua");

	// custom client file
	m_luaHandler->LoadFile("Worlds/"+NewWorld+"/Lua/CustomClient.lua");

	// indicate that we changed world
	m_newworld = true;
}


/***********************************************************
refresh lua file
***********************************************************/
void LbaNetModel::RefreshLua()
{
	// custom client file
	if(m_luaHandler)
		m_luaHandler->LoadFile("Worlds/"+m_current_world_name+"/Lua/CustomClient.lua");
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
	std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.begin();
	std::map<long, boost::shared_ptr<ExternalActor> >::iterator end = _npcObjects.end();
	for(; it != end; ++it)
		it->second->Process(tnow, tdiff, this);
	}

	// process all _playerObjects
	{
	std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.begin();
	std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator end = _playerObjects.end();
	for(; it != end; ++it)
		it->second->Process(tnow, tdiff, this);
	}

	// process all _ghostObjects
	{
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.begin();
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator end = _ghostObjects.end();
	for(; it != end; ++it)
		it->second->Process(tnow, tdiff);
	}

	//process projectiles
	std::map<long, boost::shared_ptr<ProjectileHandler> >::iterator itproj = _projectileObjects.begin();
	while(itproj != _projectileObjects.end())
	{
		if(itproj->second->Process(tnow, tdiff))
		{
			if(itproj->second->IsPlayerOwner(m_playerObjectId))
			{
				if(m_controllerChar)
					m_controllerChar->SetProjectileLaunched(false);
			}

			itproj = _projectileObjects.erase(itproj);
		}
		else
			++itproj;
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
		m_controllerChar->Process(tnow, tdiff, this);

	if(m_controllerCam)
		m_controllerCam->Process(tnow, tdiff);



	// check for finished scripts
	CheckFinishedAsynScripts();

}





/***********************************************************
add object to the scene
***********************************************************/
void LbaNetModel::AddObject(int OType, const ObjectInfo &desc, 
								const LbaNet::ModelInfo &DisplayDesc,
								const LbaNet::ObjectExtraInfo &extrainfo,
								const LbaNet::LifeManaInfo &lifeinfo,
								bool movable, bool freemove)
{
	switch(OType)
	{
		// 1 -> npc object
		case 1:
			{
				boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
				boost::shared_ptr<PhysicalObjectHandlerBase> physo = tmpobj->GetPhysicalObject();
				if(physo)
				{
					boost::shared_ptr<ActorUserData> udata = physo->GetUserData();
					if(udata)
						udata->SetAllowFreeMove(freemove);
				}
				

				_npcObjects[desc.Id] = boost::shared_ptr<ExternalActor>(new ExternalActor(tmpobj, DisplayDesc, movable));
				if(tmpobj->GetDisplayObject())
				{
					std::stringstream strs;
					strs << "A_" << desc.Id;
					tmpobj->GetDisplayObject()->SetName(strs.str());
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectExtraInfoUpdate(extrainfo), false);
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectLifeInfoUpdate(lifeinfo), false);
				}
			}
		break;


		// 2 -> player object
		case 2:
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
				std::stringstream strs;
				strs<<"New player object "<<DisplayDesc.ModelName<<" "<<DisplayDesc.Outfit<<" "<<DisplayDesc.Weapon<<" "<<DisplayDesc.Mode<<" ";
				strs<<" Display name: "<<extrainfo.Name<<" "<<(extrainfo.Display?"Yes":"No");
				strs<<" Display life: "<<(lifeinfo.Display?"Yes":"No");
				LogHandler::getInstance()->LogToFile(strs.str(), desc.Id);

				boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
				_playerObjects[desc.Id] = boost::shared_ptr<ExternalPlayer>(new ExternalPlayer(tmpobj, DisplayDesc));
				if(tmpobj->GetDisplayObject())
				{
					std::stringstream strs;
					strs << "P_" << desc.Id;
					tmpobj->GetDisplayObject()->SetName(strs.str());
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectExtraInfoUpdate(extrainfo), false);
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectLifeInfoUpdate(lifeinfo), false);
				}
			}
		break;

		// 3 -> ghost object
		case 3:
			{
				boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
				_ghostObjects[desc.Id] = tmpobj;
				if(tmpobj->GetDisplayObject())
				{
					std::stringstream strs;
					strs << "G_" << desc.Id;
					tmpobj->GetDisplayObject()->SetName(strs.str());
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectExtraInfoUpdate(extrainfo), false);
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectLifeInfoUpdate(lifeinfo), false);
				}
			}
		break;


		// editor object
		#ifdef _USE_QT_EDITOR_
		case 4:
			{
				boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
				_editorObjects[desc.Id] = tmpobj;
				if(tmpobj->GetDisplayObject())
				{
					std::stringstream strs;
					strs << "E_" << desc.Id;
					tmpobj->GetDisplayObject()->SetName(strs.str());
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectExtraInfoUpdate(extrainfo), false);
					tmpobj->GetDisplayObject()->Update(new LbaNet::ObjectLifeInfoUpdate(lifeinfo), false);
				}
			}
		break;
		#endif
	}
}


/***********************************************************
remove object from the scene
***********************************************************/
void LbaNetModel::RemObject(int OType, long id)
{
	switch(OType)
	{
		// 1 -> npc object
		case 1:
			{
			std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(id);
			if(it != _npcObjects.end())
				_npcObjects.erase(it);
			}
		break;

		// 2 -> player object
		case 2:
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
		case 3:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.find(id);
			if(it != _ghostObjects.end())
				_ghostObjects.erase(it);
			}
		break;

		// editor object
		#ifdef _USE_QT_EDITOR_
		case 4:
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

	//clear scripts
	m_playingscriptactors.clear();
	m_controllerChar->SetProjectileLaunched(false);

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
	{
		m_controllerChar->ClearScripts();
		m_controllerChar->SetPhysicalCharacter(playerObject, LbaNet::ModelInfo(), true);
	}
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
ObjectInfo LbaNetModel::CreateObject(int OType, Ice::Long ObjectId, 
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
								DisplayDesc.UseLight, DisplayDesc.CastShadow, extrainfo, lifeinfo));

				boost::shared_ptr<DisplayTransformation> tr( new DisplayTransformation());
				tr->translationX = DisplayDesc.TransX;
				tr->translationY = DisplayDesc.TransY;
				tr->translationZ = DisplayDesc.TransZ;

				tr->rotation = LbaQuaternion(DisplayDesc.RotX, DisplayDesc.RotY, DisplayDesc.RotZ);

				tr->scaleX = DisplayDesc.ScaleX;
				tr->scaleY = DisplayDesc.ScaleY;
				tr->scaleZ = DisplayDesc.ScaleZ;

				DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(tr, dispobdesc));
			}
		}
		break;

		//1 -> sprite 
		case LbaNet::RenderSprite:
		{

			if(DisplayDesc.ModelName != "")
			{
				boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
					(new SpriteDescription(DisplayDesc.ModelName, DisplayDesc.UseLight, DisplayDesc.CastShadow, 
								DisplayDesc.ColorR, DisplayDesc.ColorG, DisplayDesc.ColorB, DisplayDesc.ColorA,
								extrainfo, lifeinfo));

				boost::shared_ptr<DisplayTransformation> tr( new DisplayTransformation());
				tr->translationX = DisplayDesc.TransX;
				tr->translationY = DisplayDesc.TransY;
				tr->translationZ = DisplayDesc.TransZ;

				tr->rotation = LbaQuaternion(DisplayDesc.RotX, DisplayDesc.RotY, DisplayDesc.RotZ);

				tr->scaleX = DisplayDesc.ScaleX;
				tr->scaleY = DisplayDesc.ScaleY;
				tr->scaleZ = DisplayDesc.ScaleZ;

				DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(tr, dispobdesc));
			}
		}
		break;

		//2 -> LBA1 model 
		case LbaNet::RenderLba1M:
		{
			bool mainchar = false;
			if(OType == 2)
				if(ObjectId == m_playerObjectId)
					mainchar = true;


			//TODO animation speed
			boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
				(new Lba1ModelObjectDescription(DisplayDesc, _LBA1_MODEL_ANIMATION_SPEED_,
												DisplayDesc.UseLight, DisplayDesc.CastShadow, extrainfo, 
												lifeinfo, mainchar));

			boost::shared_ptr<DisplayTransformation> tr(new DisplayTransformation());
			tr->translationX = DisplayDesc.TransX;
			tr->translationY = DisplayDesc.TransY;
			tr->translationZ = DisplayDesc.TransZ;

			tr->rotation = LbaQuaternion(DisplayDesc.RotX, DisplayDesc.RotY, DisplayDesc.RotZ);

			tr->scaleX = DisplayDesc.ScaleX;
			tr->scaleY = DisplayDesc.ScaleY*2;
			tr->scaleZ = DisplayDesc.ScaleZ;

			DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(tr, dispobdesc));
		}
		break;

		//3-> LBA2 model
		case LbaNet::RenderLba2M:
		{
			//TODO - lba2 models
		}
		break;

		//RenderCross
		case LbaNet::RenderCross:
		{
			boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
				(new OsgCrossDescription(PhysicDesc.SizeX, 
				DisplayDesc.ColorR, DisplayDesc.ColorG, DisplayDesc.ColorB, DisplayDesc.ColorA, extrainfo, lifeinfo));


			boost::shared_ptr<DisplayTransformation> tr( new DisplayTransformation());
			tr->translationX = DisplayDesc.TransX;
			tr->translationY = DisplayDesc.TransY;
			tr->translationZ = DisplayDesc.TransZ;

			tr->rotation = LbaQuaternion(DisplayDesc.RotX, DisplayDesc.RotY, DisplayDesc.RotZ);

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
				DisplayDesc.ColorR, DisplayDesc.ColorG, DisplayDesc.ColorB, DisplayDesc.ColorA, extrainfo, lifeinfo));


			boost::shared_ptr<DisplayTransformation> tr( new DisplayTransformation());
			tr->translationX = DisplayDesc.TransX;
			tr->translationY = DisplayDesc.TransY;
			tr->translationZ = DisplayDesc.TransZ;

			tr->rotation = LbaQuaternion(DisplayDesc.RotX, DisplayDesc.RotY, DisplayDesc.RotZ);

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
				DisplayDesc.ColorR, DisplayDesc.ColorG, DisplayDesc.ColorB, DisplayDesc.ColorA, extrainfo, lifeinfo));

			boost::shared_ptr<DisplayTransformation> tr( new DisplayTransformation());
			tr->translationX = DisplayDesc.TransX;
			tr->translationY = DisplayDesc.TransY;
			tr->translationZ = DisplayDesc.TransZ;

			tr->rotation = LbaQuaternion(DisplayDesc.RotX, DisplayDesc.RotY, DisplayDesc.RotZ);

			tr->scaleX = DisplayDesc.ScaleX;
			tr->scaleY = DisplayDesc.ScaleY;
			tr->scaleZ = DisplayDesc.ScaleZ;

			DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(tr, dispobdesc));
		}
		break;

		//RenderCapsule
		case LbaNet::RenderSphere:
		{
			boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
				(new OsgSphereDescription(PhysicDesc.SizeY, 
						DisplayDesc.ColorR, DisplayDesc.ColorG, DisplayDesc.ColorB, 
						DisplayDesc.ColorA, extrainfo, lifeinfo));

			boost::shared_ptr<DisplayTransformation> tr( new DisplayTransformation());
			tr->translationX = DisplayDesc.TransX;
			tr->translationY = DisplayDesc.TransY;
			tr->translationZ = DisplayDesc.TransZ;

			tr->rotation = LbaQuaternion(DisplayDesc.RotX, DisplayDesc.RotY, DisplayDesc.RotZ);

			tr->scaleX = DisplayDesc.ScaleX;
			tr->scaleY = DisplayDesc.ScaleY;
			tr->scaleZ = DisplayDesc.ScaleZ;

			DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(tr, dispobdesc));
		}
		break;
	}

	float sizeX=PhysicDesc.SizeX, sizeY=PhysicDesc.SizeY, sizeZ=PhysicDesc.SizeZ;
	if(sizeX < 0)
		sizeX = 1;
	if(sizeY < 0)
		sizeY = 1;
	if(sizeZ < 0)
		sizeZ = 1;

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
										sizeX, sizeY, sizeZ,
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
										sizeX, sizeY,
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
										sizeY, 
										PhysicDesc.Collidable, 
										PhysicDesc.Bounciness, 
										PhysicDesc.StaticFriction, PhysicDesc.DynamicFriction));
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
	ObjectInfo obj(OType, (long)ObjectId, DInfo, PInfo, false); // make all objects dynamic in editor as we can change them
#else
	ObjectInfo obj(OType, (long)ObjectId, DInfo, PInfo, (PhysicDesc.TypePhysO == LbaNet::StaticAType));
#endif
	
	return obj;
}


/***********************************************************
 add object from server
 type:
1 -> npc object
2 -> player object
3 -> ghost object
***********************************************************/
void LbaNetModel::AddObject(int OType, Ice::Long ObjectId, 
					const LbaNet::ModelInfo &DisplayDesc, 
					const LbaNet::ObjectPhysicDesc &PhysicDesc,
					const LbaNet::ObjectExtraInfo &extrainfo,
					const LbaNet::LifeManaInfo &lifeinfo)
{
	ObjectInfo obj = CreateObject(OType, ObjectId, DisplayDesc, PhysicDesc, extrainfo, lifeinfo);
	AddObject(OType, obj, DisplayDesc, extrainfo, lifeinfo, 
					(PhysicDesc.TypePhysO == LbaNet::CharControlAType), PhysicDesc.AllowFreeMove);
}



/***********************************************************
 remove object from server	
 type:
1 -> npc object
2 -> player object
3 -> ghost object
***********************************************************/
void LbaNetModel::RemoveObject(int OType, Ice::Long ObjectId)
{
	RemObject(OType, (long)ObjectId);
}


/***********************************************************
update object from server
***********************************************************/
void LbaNetModel::UpdateObjectDisplay(int OType, Ice::Long ObjectId, 
									  LbaNet::DisplayObjectUpdateBasePtr update)
{
	switch(OType)
	{
		// 1 -> npc object
		case 1:
			{
			std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find((long)ObjectId);
			if(it != _npcObjects.end())
				it->second->UpdateDisplay(update, false);
			}
		break;


		// 2 -> player object
		case 2:
			//special treatment if main player
			if(m_playerObjectId == (long)ObjectId)
			{
				m_controllerChar->UpdateDisplay(update);
			}
			else
			{
				std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.find((long)ObjectId);
				if(it != _playerObjects.end())
					it->second->UpdateDisplay(update, false);
			}
		break;

		// 3 -> ghost object
		case 3:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.find((long)ObjectId);
			if(it != _ghostObjects.end())
				it->second->GetDisplayObject()->Update(update, false);
			}
		break;

		// editor object
		#ifdef _USE_QT_EDITOR_
		case 4:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _editorObjects.find((long)ObjectId);
			if(it != _editorObjects.end())
				it->second->GetDisplayObject()->Update(update, false);
			}
		break;
		#endif
	}
}


/***********************************************************
update object physic
***********************************************************/
void LbaNetModel::UpdateObjectPhysic(int OType, Ice::Long ObjectId, 
								  LbaNet::PhysicObjectUpdateBasePtr update)
{
	switch(OType)
	{
		// 1 -> npc object
		case 1:
			{
			std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find((long)ObjectId);
			if(it != _npcObjects.end())
				it->second->UpdatePhysic(update);
			}
		break;


		// 2 -> player object
		case 2:
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
		case 3:
			{
			std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.find((long)ObjectId);
			if(it != _ghostObjects.end())
				it->second->GetPhysicalObject()->Update(update);
			}
		break;

		// editor object
		#ifdef _USE_QT_EDITOR_
		case 4:
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
when update npc position
***********************************************************/
void LbaNetModel::NpcChangedUpdate(Ice::Long NpcId, double updatetime, 
									float CurrPosX, float CurrPosY, float CurrPosZ,
									float CurrRotation, const std::string &CurrAnimation,
									bool ResetPosition, bool ResetRotation,
									LbaNet::NpcUpdateBasePtr Update)
{
	std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find((long)NpcId);
	if(it != _npcObjects.end())
	{
		it->second->NpcChangedUpdate(updatetime, CurrPosX, CurrPosY, CurrPosZ, CurrRotation,
										CurrAnimation, ResetPosition, ResetRotation, Update, this);
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

	if(m_newworld)
	{
		m_newworld = false;
		RefreshPlayerPortrait();
	}
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
used by lua to get an actor Position
if id < 1 then it get player position
***********************************************************/
LbaVec3 LbaNetModel::GetActorPosition(long ActorId)
{
	LbaVec3 res;

	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->GetPosition(res.x, res.y, res.z);
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
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			return it->second->GetRotationYAxis();
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
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
		{
			LbaQuaternion res;
			it->second->GetRotation(res);
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
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->UpdateDisplay(new LbaNet::AnimationStringUpdate(AnimationString), true);
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
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->UpdateActorMode(Mode, true);
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
void LbaNetModel::InternalActorStraightWalkTo(int ScriptId, long ActorId, const LbaVec3 &Position, bool asynchronus)
{
	if(ActorId >= 0)
	{
		ReserveActor(ScriptId, ActorId);

		// on actor
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->ActorStraightWalkTo(ScriptId, asynchronus, Position.x, Position.y, Position.z);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->ActorStraightWalkTo(ScriptId, asynchronus, Position.x, Position.y, Position.z);
	}
}



/***********************************************************
//! used by lua to rotate an actor
//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
***********************************************************/
void LbaNetModel::InternalActorRotate(int ScriptId, long ActorId, float Angle, float RotationSpeedPerSec,
									bool ManageAnimation, bool asynchronus)
{
	if(ActorId >= 0)
	{
		ReserveActor(ScriptId, ActorId);

		// on actor
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->ActorRotate(ScriptId, asynchronus, Angle, RotationSpeedPerSec, ManageAnimation);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->ActorRotate(ScriptId, asynchronus, Angle, RotationSpeedPerSec, ManageAnimation);
	}
}


/***********************************************************
//! used by lua to wait until an actor animation is finished
//! if AnimationMove = true then the actor will be moved at the same time using the current animation speed
***********************************************************/
void LbaNetModel::InternalActorAnimate(int ScriptId, long ActorId, bool AnimationMove, bool asynchronus)
{
	if(ActorId >= 0)
	{
		ReserveActor(ScriptId, ActorId);

		// on actor
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->ActorAnimate(ScriptId, asynchronus, AnimationMove);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->ActorAnimate(ScriptId, asynchronus, AnimationMove);
	}
}



/***********************************************************
//! called when a script has finished
***********************************************************/
void LbaNetModel::ScriptFinished(int scriptid, const std::string & functioname)
{
	// inform server that script is finished
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ScriptExecutionFinishedEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), functioname));

	ReleaseActorFromScript(scriptid);
}


/***********************************************************
//! set the actor as playing script
***********************************************************/
void LbaNetModel::ReserveActor(int ScriptId, long ActorId)
{
	std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
	if(it != _npcObjects.end())
	{
		it->second->SetPlayingScript(true);
		m_playingscriptactors[ScriptId].insert(ActorId);
	}
}


/***********************************************************
//! release scripted actors
***********************************************************/
void LbaNetModel::ReleaseActorFromScript(int scriptid)
{
	std::map<int, std::set<long> >::iterator itpl = m_playingscriptactors.find(scriptid);
	if(itpl != m_playingscriptactors.end())
	{
		std::set<long>::iterator its = itpl->second.begin();
		std::set<long>::iterator ends = itpl->second.end();
		for(; its != ends; ++its)
		{
			std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(*its);
			if(it != _npcObjects.end())
				it->second->SetPlayingScript(false);
		}

		m_playingscriptactors.erase(itpl);
	}
}




/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will change model
***********************************************************/
void LbaNetModel::UpdateActorModel(long ActorId, const std::string & Name)
{
	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->UpdateActorModel(Name, true);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->UpdateActorModel(Name);
	}
}



/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will change outfit
***********************************************************/
void LbaNetModel::UpdateActorOutfit(long ActorId, const std::string & Name)
{
	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->UpdateActorOutfit(Name, true);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->UpdateActorOutfit(Name);
	}
}



/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will change weapon
***********************************************************/
void LbaNetModel::UpdateActorWeapon(long ActorId, const std::string & Name)
{
	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->UpdateActorWeapon(Name, true);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->UpdateActorWeapon(Name);
	}
}



/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will change mode
***********************************************************/
void LbaNetModel::SendSignalToActor(long ActorId, int Signalnumber)
{
	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->SendSignal(Signalnumber);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->SendSignal(Signalnumber);
	}
}





/***********************************************************
//! used by lua to move an actor or player
//! the actor will move using animation speed
***********************************************************/
void LbaNetModel::TeleportActorTo(int ScriptId, long ActorId, const LbaVec3 &Position)
{
	if(ActorId >= 0)
	{
		ReserveActor(ScriptId, ActorId);

		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->TeleportTo(Position.x, Position.y, Position.z);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->TeleportTo(Position.x, Position.y, Position.z);
	}
}



/***********************************************************
//! used by lua to move an actor or player
//! the actor change rotation
***********************************************************/
void LbaNetModel::SetActorRotation(long ActorId, float Angle)
{
	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->SetRotation(Angle);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->SetRotation(Angle);
	}
}


/***********************************************************
//! used by lua to move an actor or player
//! the actor show/hide
***********************************************************/
void LbaNetModel::ActorShowHide(long ActorId, bool Show)
{
	if(ActorId >= 0)
	{
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->ShowHide(Show);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->ShowHide(Show);
	}
}



/***********************************************************
// show/hide object
// ObjectType ==>
//! 1 -> npc object
//! 2 -> player object
//! 3 -> movable object
***********************************************************/
void LbaNetModel::ShowHideActor(int ObjectType, long ObjectId, bool SHow)
{
	switch(ObjectType)
	{
		// 1 -> npc object
		case 1:
			{
			std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find((long)ObjectId);
			if(it != _npcObjects.end())
				it->second->ShowHide(SHow);
			}
		break;


		// 2 -> player object
		case 2:
			//special treatment if main player
			if(m_playerObjectId == (long)ObjectId)
			{
				m_controllerChar->ShowHide(SHow);
			}
			else
			{
				std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.find((long)ObjectId);
				if(it != _playerObjects.end())
					it->second->ShowHide(SHow);
			}
		break;

		// 3 -> ghost object
		case 3:
			{
				std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.find((long)ObjectId);
				//if(it != _ghostObjects.end())
					//todo - GhostObject
			}
		break;

	}
}



/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will move using speed
***********************************************************/
void LbaNetModel::InternalActorGoTo(int ScriptId, long ActorId, const LbaVec3 &Position, 
										float Speed, bool asynchronus)
{
	if(ActorId >= 0)
	{
		ReserveActor(ScriptId, ActorId);

		// on actor
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->ActorGoTo(ScriptId, Position.x, Position.y, Position.z, Speed, asynchronus);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->ActorGoTo(ScriptId, Position.x, Position.y, Position.z, Speed, asynchronus);
	}
}
	


/***********************************************************
	//! used by lua to move an actor or player
	//! the actor will wait for signal
***********************************************************/
void LbaNetModel::InternalActorWaitForSignal(int ScriptId, long ActorId, int Signalnumber, 
												bool asynchronus)
{
	if(ActorId >= 0)
	{
		ReserveActor(ScriptId, ActorId);

		// on actor
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->ActorWaitForSignal(ScriptId, Signalnumber, asynchronus);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->ActorWaitForSignal(ScriptId, Signalnumber, asynchronus);
	}
}




/***********************************************************
	//! used by lua to rotate an actor
	//! the actor will rotate until it reach "Angle" with speed "RotationSpeedPerSec"
	//! if RotationSpeedPerSec> 1 it will take the shortest rotation path else the longest
	//! if ManageAnimation is true then the animation will be changed to suit the rotation
***********************************************************/
void LbaNetModel::InternalActorRotateFromPoint(int ScriptId, long ActorId, float Angle, const LbaVec3 &Position, 
												float RotationSpeedPerSec, bool asynchronus)
{
	if(ActorId >= 0)
	{
		ReserveActor(ScriptId, ActorId);

		// on actor
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->ActorRotateFromPoint(ScriptId, Angle, 
												Position.x, Position.y, Position.z, RotationSpeedPerSec, 
												asynchronus);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->ActorRotateFromPoint(ScriptId, Angle, 
													Position.x, Position.y, Position.z, RotationSpeedPerSec, 
													asynchronus);
	}
}


/***********************************************************
 used by lua to make actor follow waypoint
***********************************************************/
void LbaNetModel::InternalActorFollowWaypoint(int ScriptId, long ActorId, int waypointindex1, 
												int waypointindex2, bool asynchronus)
{
	if(ActorId >= 0)
	{
		ReserveActor(ScriptId, ActorId);

		// on actor
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
			it->second->ActorFollowWaypoint(ScriptId, waypointindex1, waypointindex2, asynchronus);
	}
	else
	{
		// on player
		if(m_controllerChar)
			m_controllerChar->ActorFollowWaypoint(ScriptId, waypointindex1, waypointindex2, asynchronus);
	}
}


/***********************************************************
internally update player state
***********************************************************/
void LbaNetModel::UpdatePlayerState(LbaNet::ModelState	NewState)
{
	if(m_controllerChar)
		m_controllerChar->UpdateState(NewState);
}



/***********************************************************
actor target player
***********************************************************/
void LbaNetModel::NpcTargetPlayer(long ActorId, long PlayerId)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> object;

	if(m_playerObjectId == (long)PlayerId)
	{
		object = m_controllerChar->GetPhysicalObject();
	}
	else
	{
		std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.find((long)PlayerId);
		if(it != _playerObjects.end())
			object = it->second->GetPhysicalObject();
	}


	// on actor
	if(object)
	{
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
		if(it != _npcObjects.end())
		{
			it->second->Target(object);
		}
	}
}


/***********************************************************
actor untarget player
***********************************************************/
void LbaNetModel::NpcUnTargetPlayer(long ActorId)
{
	std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find(ActorId);
	if(it != _npcObjects.end())
		it->second->UnTarget();
}



/***********************************************************
create projectile
***********************************************************/
void LbaNetModel::CreateProjectile(const LbaNet::ProjectileInfo & Info)
{
	LbaNet::ObjectExtraInfo extrainfo;
	extrainfo.Display = false;
	LbaNet::LifeManaInfo lifeinfo;
	lifeinfo.Display = false;

	ObjectInfo obj = CreateObject(5, Info.Id, 
								Info.DisplayDesc, Info.PhysicDesc, extrainfo, lifeinfo);

	boost::shared_ptr<DynamicObject> dynobj = obj.BuildSelf(OsgHandler::getInstance());


	// projectile should not touch creator
	boost::shared_ptr<PhysicalObjectHandlerBase> physobj = dynobj->GetPhysicalObject();
	boost::shared_ptr<PhysicalObjectHandlerBase> ownerobj;
	if(physobj)
	{
		if(Info.OwnerActorId >= 0)
		{
			switch(Info.OwnerActorType)
			{
				// 1 -> npc object
				case 1:
				{
					std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find((long)Info.OwnerActorId);
					if(it != _npcObjects.end())
						ownerobj = it->second->GetPhysicalObject();
				}
				break;


				// 2 -> player object
				case 2:
					//special treatment if main player
					if(m_playerObjectId == (long)Info.OwnerActorId)
					{
						if(m_controllerChar)
						{
							if(Info.Comeback)
								m_controllerChar->SetProjectileLaunched(true);

							ownerobj = m_controllerChar->GetPhysicalObject();
						}
					}
					else
					{
						std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.find((long)Info.OwnerActorId);
						if(it != _playerObjects.end())
							ownerobj = it->second->GetPhysicalObject();
					}
				break;
			}
		}
	}

	//create projectile handler
	_projectileObjects[(long)Info.Id] = boost::shared_ptr<ProjectileHandler>(
		new ProjectileHandler(dynobj, Info, Info.ManagingClientId == m_playerObjectId, ownerobj));
}


/***********************************************************
destroy projectile
***********************************************************/
void LbaNetModel::DestroyProjectile(long Id)
{
	std::map<long, boost::shared_ptr<ProjectileHandler> >::iterator it = _projectileObjects.find(Id);
	if(it != _projectileObjects.end())
		_projectileObjects.erase(it);
}



/***********************************************************
get actor info
***********************************************************/
boost::shared_ptr<DynamicObject> LbaNetModel::GetActor(int ObjectType, long ObjectId)
{
	switch(ObjectType)
	{
		// 1 -> npc object
		case 1:
			{
			std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find((long)ObjectId);
			if(it != _npcObjects.end())
				return it->second->GetActor();
			}
		break;


		// 2 -> player object
		case 2:
			//special treatment if main player
			if(m_playerObjectId == (long)ObjectId)
			{
				return m_controllerChar->GetActor();
			}
			else
			{
				std::map<long, boost::shared_ptr<ExternalPlayer> >::iterator it = _playerObjects.find((long)ObjectId);
				if(it != _playerObjects.end())
					return it->second->GetActor();
			}
		break;

		// 3 -> ghost object
		case 3:
			{
				std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _ghostObjects.find((long)ObjectId);
				//if(it != _ghostObjects.end())
					//todo - GhostObject
			}
		break;

	}

	return boost::shared_ptr<DynamicObject>();
}



/***********************************************************
AttachActor
***********************************************************/
void LbaNetModel::AttachActor(long ActorId, int AttachedObjectType, long AttachedObjectId)
{
	//special treatment if main player
	if(ActorId < 0)
	{
		m_controllerChar->SetAttached(GetActor(AttachedObjectType, AttachedObjectId));
	}
	else
	{
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find((long)ActorId);
		if(it != _npcObjects.end())
			it->second->SetAttached(GetActor(AttachedObjectType, AttachedObjectId));
	}
}

/***********************************************************
DettachActor
***********************************************************/
void LbaNetModel::DettachActor(long ActorId, long AttachedObjectId)
{
	//special treatment if main player
	if(ActorId < 0)
	{
		m_controllerChar->SetAttached(boost::shared_ptr<DynamicObject>());
	}
	else
	{
		std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find((long)ActorId);
		if(it != _npcObjects.end())
			it->second->SetAttached(boost::shared_ptr<DynamicObject>());
	}
}



/***********************************************************
attached actor to npc
***********************************************************/
void LbaNetModel::NpcAttachActor(long NpcId, int AttachedObjectType, long AttachedObjectId)
{
	std::map<long, boost::shared_ptr<ExternalActor> >::iterator it = _npcObjects.find((long)NpcId);
	if(it != _npcObjects.end())
		it->second->ServerAttachActor(GetActor(AttachedObjectType, AttachedObjectId));
}




/***********************************************************
refresh player portrait
***********************************************************/
void LbaNetModel::RefreshPlayerPortrait()
{
#ifndef _USE_QT_EDITOR_
	//save player image
	if(m_controllerChar)
		m_controllerChar->SavePlayerDisplayToFile("Data/GUI/imagesets/charportrait.png");

	//refresh GUI
	LbaNet::GuiUpdatesSeq updseq;
	updseq.push_back(new RefreshCharPortraitUpdate());
	EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "main", updseq));
#endif
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



