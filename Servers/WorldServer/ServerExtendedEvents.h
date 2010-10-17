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


#if !defined(__LbaNetModel_ServerExtendedEvents_h)
#define __LbaNetModel_ServerExtendedEvents_h

#include <ClientServerEvents.h>
#include <boost/shared_ptr.hpp>

class ActionBase;
class TriggerBase;

/*
************************************************************************************************************************
*                                                  class UpdateEditor_AddOrModSpawning
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_AddOrModSpawning : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_AddOrModSpawning(long SpawningId, const std::string &spawningname,
									float PosX, float PosY, float PosZ,
									float Rotation, bool forcedrotation)
	: _SpawningId(SpawningId), _spawningname(spawningname), _PosX(PosX), _PosY(PosY), _PosZ(PosZ),
		_Rotation(Rotation), _forcedrotation(forcedrotation)
	{
	}
	long 			_SpawningId;
	std::string		_spawningname;
	float			_PosX;
	float			_PosY;
	float			_PosZ;
	float			_Rotation;
	bool			_forcedrotation;
};



/*
************************************************************************************************************************
*                                                  class UpdateEditor_RemoveSpawning
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_RemoveSpawning : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_RemoveSpawning(long SpawningId)
	: _SpawningId(SpawningId)
	{
	}

	long 		_SpawningId;
};






/*
************************************************************************************************************************
*                                                  class UpdateEditor_AddAction
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_AddOrModAction : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_AddOrModAction(boost::shared_ptr<ActionBase> action)
	: _action(action)
	{
	}

	boost::shared_ptr<ActionBase> _action;
};



/*
************************************************************************************************************************
*                                                  class UpdateEditor_RemoveAction
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_RemoveAction : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_RemoveAction(long ActionId)
	: _ActionId(ActionId)
	{
	}

	long 		_ActionId;
};







/*
************************************************************************************************************************
*                                                  class UpdateEditor_AddTrigger
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_AddOrModTrigger : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_AddOrModTrigger(boost::shared_ptr<TriggerBase> trigger)
	: _trigger(trigger)
	{
	}

	boost::shared_ptr<TriggerBase> _trigger;
};



/*
************************************************************************************************************************
*                                                  class UpdateEditor_RemoveTrigger
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_RemoveTrigger : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_RemoveTrigger(long TriggerId)
	: _TriggerId(TriggerId)
	{
	}

	long 		_TriggerId;
};






/*
************************************************************************************************************************
*                                                  class EditorEvent
*
*	class used for editor event between client and server
************************************************************************************************************************
*/
class EditorEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	EditorEvent(LbaNet::EditorUpdateBasePtr update)
		: _update(update)
	{
	}

	LbaNet::EditorUpdateBasePtr _update;
};


#endif