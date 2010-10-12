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
	TriggerBase(){}
	
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

protected:
	MapHandler *	_map;
	float			_posX;
	float			_posY;
	float			_posZ;
};



//!  class handling triggers when player/object enter or leave map
class EnterLeaveMapTrigger : public TriggerBase
{
public:
	//! constructor
	EnterLeaveMapTrigger(){}
	
	//! destructor
	virtual ~EnterLeaveMapTrigger(void){}

	//! check trigger on object enter map
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectEnterMap(int ObjectType, Ice::Long ObjectId) = 0;

	//! check trigger on object leave map
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectLeaveMap(int ObjectType, Ice::Long ObjectId) = 0;
};



//!  class handling triggers when player/object moves
class MovingTrigger : public EnterLeaveMapTrigger
{
public:
	//! constructor
	MovingTrigger(){}
	
	//! destructor
	virtual ~MovingTrigger(void){}

	//! check trigger on object move
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void CheckTriggerOnMove(int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerMoveInfo &info) = 0;
};



//! class handling triggers when player/object enter/leave zone
class ZoneTrigger : public MovingTrigger
{
public:
	//! constructor
	//! AllowMultiActivation is used as flag to know if the trigger should be activated
	//! again if an object is already inside the zone and a second object enters
	//! as an example for door trigger, we would set the flag to false as only 
	//! the first player entering would open
	//! the door, any other player entering the zone will do nothing
	//! as well, the door will close only when the last player leave the zone
	ZoneTrigger(	float sizeX, float sizeY, float sizeZ, 
					bool CheckPlayers, bool CheckNpcs, bool CheckMovableObjects,
					bool AllowMultiActivation);
	
	//! destructor
	virtual ~ZoneTrigger(void);

	//! check trigger on object move
	virtual void CheckTriggerOnMove(int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerMoveInfo &info);


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

	bool													_CheckPlayers;
	bool													_CheckNpcs;
	bool													_CheckMovableObjects;
	bool													_AllowMultiActivation;

	boost::shared_ptr<ActionBase>							_actionOnEnter;
	boost::shared_ptr<ActionBase>							_actionOnLeave;

	std::set<std::pair<int, Ice::Long> >					_objectsinside;
};



#endif
