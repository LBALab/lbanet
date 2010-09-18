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

	// process all dynamic objects
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _dynamicObjects.begin();
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator end = _dynamicObjects.end();
	for(; it != end; ++it)
		it->second->Process();

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
boost::shared_ptr<PhysicalObjectHandlerBase> 
	LbaNetModel::AddObject(const ObjectInfo &desc)
{
	//special treatment if main object
	if(m_playerObjectId == desc.Id)
	{
		m_playerObject = desc.BuildSelf(OsgHandler::getInstance());

		if(m_controllerChar)
			m_controllerChar->SetPhysicalCharacter(m_playerObject->GetPhysicalObject());
		if(m_controllerCam)
			m_controllerCam->SetCharacter(m_playerObject);

		return m_playerObject->GetPhysicalObject();
	}
	else
	{
		boost::shared_ptr<DynamicObject> tmpobj = desc.BuildSelf(OsgHandler::getInstance());
		_dynamicObjects[desc.Id] = tmpobj;

		return tmpobj->GetPhysicalObject();
	}
}


/***********************************************************
remove object from the scene
***********************************************************/
void LbaNetModel::RemObject(long id)
{
	//special treatment if main object
	if(id == m_playerObjectId)
	{
		ResetPlayerObject();
	}
	else
	{
		std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _dynamicObjects.find(id);
		if(it != _dynamicObjects.end())
			_dynamicObjects.erase(it);
	}
}


/***********************************************************
remove object from the scene
***********************************************************/
boost::shared_ptr<DynamicObject> LbaNetModel::GetObject(long id)
{
	std::map<long, boost::shared_ptr<DynamicObject> >::iterator it = _dynamicObjects.find(id);
	if(it != _dynamicObjects.end())
	{
		return it->second;
	}

	return boost::shared_ptr<DynamicObject>();
}

/***********************************************************
clean up map
***********************************************************/
void LbaNetModel::CleanupMap()
{
	//clear dynamic object of the current scene
	_dynamicObjects.clear();

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
	m_playerObjectId = 0;

	boost::shared_ptr<PhysicalObjectHandlerBase> physo(new SimplePhysicalObjectHandler(0, 0, 0, LbaQuaternion()));
	m_playerObject = boost::shared_ptr<DynamicObject>(new StaticObject(physo, boost::shared_ptr<DisplayObjectHandlerBase>(), m_playerObjectId));

	if(m_controllerChar)
		m_controllerChar->SetPhysicalCharacter(m_playerObject->GetPhysicalObject(), true);
	if(m_controllerCam)
		m_controllerCam->SetCharacter(m_playerObject, true);
}


