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

#ifndef _LBANET_TRIGGERS_H__
#define _LBANET_TRIGGERS_H__

#include "Actions.h"
#include <boost/shared_ptr.hpp>
#include <set>


//! base class handling game triggers
class TriggerBase
{
public:
	//! constructor
	TriggerBase(long id, bool CheckPlayers, bool CheckNpcs, bool CheckMovableObjects)
		: _id(id), _CheckPlayers(CheckPlayers), 
			_CheckNpcs(CheckNpcs), _CheckMovableObjects(CheckMovableObjects)
	{}
	
	//! destructor
	virtual ~TriggerBase(void){}

	//! set the map owning the trigger
	void SetOwner(MapHandler * map)
	{ _map = map; }


	//! set trigger position in world
	void SetPosition(float X, float Y, float Z)
	{
		_posX = X;
		_posY = Y;
		_posZ = Z;
	}

	//! get trigger id
	long GetId()
	{
		return _id;
	}


	//! check trigger on object enter map
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectEnterMap(int ObjectType, Ice::Long ObjectId){}

	//! check trigger on object leave map
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectLeaveMap(int ObjectType, Ice::Long ObjectId){}

	//! check trigger on object move
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectMoved(int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerPosition &info){}


	//! check trigger on object action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	// ObjectMode give the mode the object was when performing the action
	virtual void ObjectAction(int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerPosition &info,
										const std::string &ObjectMode){}


protected:
	long			_id;
	bool			_CheckPlayers;
	bool			_CheckNpcs;
	bool			_CheckMovableObjects;


	MapHandler *	_map;
	float			_posX;
	float			_posY;
	float			_posZ;
};



//! class handling triggers when player/object enter/leave zone
class ZoneTrigger : public TriggerBase
{
public:
	//! constructor
	//! AllowMultiActivation is used as flag to know if the trigger should be activated
	//! again if an object is already inside the zone and a second object enters
	//! as an example for door trigger, we would set the flag to false as only 
	//! the first player entering would open
	//! the door, any other player entering the zone will do nothing
	//! as well, the door will close only when the last player leave the zone
	ZoneTrigger( long id, bool CheckPlayers, bool CheckNpcs, bool CheckMovableObjects,
					float sizeX, float sizeY, float sizeZ, 
					bool AllowMultiActivation);
	
	//! destructor
	virtual ~ZoneTrigger(void);

	//! check trigger on object move
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectMoved(int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerPosition &info);

	//! check trigger on object leave map
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectLeaveMap(int ObjectType, Ice::Long ObjectId);


	//! set action when enter zone
	void SetActionOnEnter(boost::shared_ptr<ActionBase> action)
	{_actionOnEnter = action;}

	//! set action when leave zone
	void SetActionOnLeave(boost::shared_ptr<ActionBase> action)
	{_actionOnLeave = action;}


protected:
	//! when object entered
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	void Entered(int ObjectType, Ice::Long ObjectId);

	//! when object left
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	void Left(int ObjectType, Ice::Long ObjectId);

private:
	float													_sizeX;
	float													_sizeY;
	float													_sizeZ;


	bool													_AllowMultiActivation;

	boost::shared_ptr<ActionBase>							_actionOnEnter;
	boost::shared_ptr<ActionBase>							_actionOnLeave;

	std::set<std::pair<int, Ice::Long> >					_objectsinside;
};




//! class handling triggers when player/object use action at a certain distance of an object
class ActivationTrigger : public TriggerBase
{
public:
	//! constructor
	//! can configure up to 2 modes to be accepted for trigger the action
	ActivationTrigger( long id, bool CheckPlayers, bool CheckNpcs, bool CheckMovableObjects,
							float MaxSquaredDistance, 
							const std::string & AcceptedMode1, 
							const std::string & AcceptedMode2);
	
	//! destructor
	virtual ~ActivationTrigger(void);


	//! set action when activated
	void SetActionOnActivation(boost::shared_ptr<ActionBase> action)
	{_action = action;}


	//! check trigger on object action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	// ObjectMode give the mode the object was when performing the action
	virtual void ObjectAction(int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerPosition &info,
										const std::string &ObjectMode);

private:
	boost::shared_ptr<ActionBase>			_action;
	float									_MaxSquaredDistance; 
	std::string								_AcceptedMode1; 
	std::string								_AcceptedMode2;
};



//! class handling triggers when player/object use action in a zone
class ZoneActionTrigger : public TriggerBase
{
public:
	//! constructor
	ZoneActionTrigger( long id, bool CheckPlayers, bool CheckNpcs, bool CheckMovableObjects,
						float sizeX, float sizeY, float sizeZ, 
							const std::string & AcceptedMode1, 
							const std::string & AcceptedMode2);
	
	//! destructor
	virtual ~ZoneActionTrigger(void);


	//! check trigger on object action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	// ObjectMode give the mode the object was when performing the action
	virtual void ObjectAction(int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerPosition &info,
										const std::string &ObjectMode);



	//! set action when activated
	void SetActionOnActivation(boost::shared_ptr<ActionBase> action)
	{_action = action;}



private:
	float									_sizeX;
	float									_sizeY;
	float									_sizeZ;

	std::string								_AcceptedMode1; 
	std::string								_AcceptedMode2;

	boost::shared_ptr<ActionBase>			_action;
};


#endif
