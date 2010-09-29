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

#if !defined(__LbaNetModel_1_LbaNetModel_h)
#define __LbaNetModel_1_LbaNetModel_h

#include <string>
#include <vector>
#include <map>

#include "ObjectsDescription.h"
#include "DynamicObject.h"
#include "CommonTypes.h"
#include "ClientExtendedEvents.h"

#include <boost/shared_ptr.hpp>
#include <ClientServerEvents.h>

class PhysXEngine;
class CharacterController;
class CameraController;
class ExternalPlayer;


/***********************************************************************
 * Module:  LbaNetModel.h
 * Author:  vivien
 * Modified: mardi 14 juillet 2009 13:54:52
 * Purpose: Declaration of the class LbaNetModel
 ***********************************************************************/
class LbaNetModel
{
public:
	//! constructor
	LbaNetModel();

	//! destructor
	~LbaNetModel();


	//! set player id
	void SetPlayerId(long Id);


	// change the world
	void ChangeWorld(const std::string & NewWorld);

	//! do all check to be done when idle
	void Process(double tnow, float tdiff);

	//! clean up everything
	void CleanupWorld();

	//! pause the game
	void Pause();

	//! resume the game
	void Resume();

	//! add object from server
	//! type:
	// 1 -> static object
	// 2 -> server controlled
	// 3 -> movable by player
	// 4 -> player object
	// 5 -> ghost object
	void AddObject(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId, 
						const LbaNet::ModelInfo &DisplayDesc, 
						const LbaNet::ObjectPhysicDesc &PhysicDesc);
	
	//! remove object from server	
	//! type:
	// 1 -> static object
	// 2 -> server controlled
	// 3 -> movable by player
	// 4 -> player object
	// 5 -> ghost object
	void RemoveObject(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId);

	//! update object display
	void UpdateObjectDisplay(LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId, 
									  LbaNet::DisplayObjectUpdateBasePtr update);

	//! key pressed
	void KeyPressed(LbanetKey keyid);

	//! key released
	void KeyReleased(LbanetKey keyid);


	//! when update player position
	void PlayerMovedUpdate(Ice::Long PlayerId, double updatetime, 
									const LbaNet::PlayerMoveInfo &info);


	//! called when we enter a new map
	void NewMap(const std::string & NewMap, const std::string & Script);


	//! map is fully refreshed
	void RefreshEnd();

protected:

	//! clean up map
	void CleanupMap();


	//! reset player object
	void ResetPlayerObject();



	//! add object to the scene
	//! if IsMainPlayer then treat this object as the player object
	//! type:
	// 1 -> static object
	// 2 -> server controlled
	// 3 -> movable by player
	// 4 -> player object
	// 5 -> ghost object
	void AddObject(LbaNet::ObjectTypeEnum OType, const ObjectInfo &desc,
					const LbaNet::ModelInfo &DisplayDesc);


	//! remove object from the scene
	//! type:
	// 1 -> static object
	// 2 -> server controlled
	// 3 -> movable by player
	// 4 -> player object
	// 5 -> ghost object
	virtual void RemObject(LbaNet::ObjectTypeEnum OType, long id);



private:
	
	// list of object populating the scene
	// static object - do not move, do not need to process
	// server objects - will move from script
	// movable objects - moved by player - create a ghost in the other side
	// player objects - will move randomly - get info from server
	// ghosts objects - replication of other movable objects
	std::map<long, boost::shared_ptr<DynamicObject> >	_staticObjects;
	std::map<long, boost::shared_ptr<DynamicObject> >	_serverObjects;
	std::map<long, boost::shared_ptr<DynamicObject> >	_movableObjects;
	std::map<long, boost::shared_ptr<ExternalPlayer> >	_playerObjects;
	std::map<long, boost::shared_ptr<DynamicObject> >	_ghostObjects;


	// last cycle time
	bool												m_paused;


	// controllers
	boost::shared_ptr<CharacterController>				m_controllerChar;
	boost::shared_ptr<CameraController>					m_controllerCam;


	// player object
	long												m_playerObjectId;


	std::string											m_current_map_name;
};

#endif