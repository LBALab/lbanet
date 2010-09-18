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

#include <boost/shared_ptr.hpp>

class PhysXEngine;
class CharacterController;
class CameraController;


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
	void Process();


	//! add object to the scene
	//! if IsMainPlayer then treat this object as the player object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> AddObject(const ObjectInfo &desc);


	//! remove object from the scene
	virtual void RemObject(long id);


	//! get object from the scene
	boost::shared_ptr<DynamicObject> GetObject(long id);


	//! clean up everything
	void CleanupWorld();

	//! pause the game
	void Pause();

	//! resume the game
	void Resume(bool reinit);



protected:

	//! clean up map
	void CleanupMap();


	//! reset player object
	void ResetPlayerObject();


private:

	//TODO change this to 5 types of objects:
	// static object - do not move, do not need to process
	// player objects - will move randomly - get info from server
	// actors objects - will move from script
	// movable objects - moved by player - create a ghost in the other side
	// ghosts objects - replication of other movable objects

	// list of object populating the scene
	std::map<long, boost::shared_ptr<DynamicObject> >	_dynamicObjects;


	// last cycle time
	double												m_lasttime;
	bool												m_paused;


	// controllers
	boost::shared_ptr<CharacterController>				m_controllerChar;
	boost::shared_ptr<CameraController>					m_controllerCam;


	// player object
	long												m_playerObjectId;
	boost::shared_ptr<DynamicObject>					m_playerObject;
};

#endif