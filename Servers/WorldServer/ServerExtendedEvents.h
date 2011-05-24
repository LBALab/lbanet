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


class Spawn;
class ActionBase;
class TriggerBase;
class ActorHandler;


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
	UpdateEditor_AddOrModSpawning(boost::shared_ptr<Spawn> spawn)
	: _spawn(spawn)
	{
	}

	boost::shared_ptr<Spawn> _spawn;
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
*                                                  class UpdateEditor_AddTrigger
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_AddOrModMap : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_AddOrModMap(const LbaNet::MapInfo & mapinfo)
	: _mapinfo(mapinfo)
	{
	}

	LbaNet::MapInfo _mapinfo;
};



/*
************************************************************************************************************************
*                                                  class UpdateEditor_RemoveMap
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_RemoveMap : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_RemoveMap(const std::string & MapName)
	: _MapName(MapName)
	{
	}

	std::string 		_MapName;
};




/*
************************************************************************************************************************
*                                                  class UpdateEditor_AddOrModActor
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_AddOrModActor : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_AddOrModActor(boost::shared_ptr<ActorHandler> actor)
	: _actor(actor)
	{
	}

	boost::shared_ptr<ActorHandler> _actor;
};



/*
************************************************************************************************************************
*                                                  class UpdateEditor_RemoveActor
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_RemoveActor : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_RemoveActor(long id)
	: _id(id)
	{
	}

	long 		_id;
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




/*
************************************************************************************************************************
*                                                  class ChangeColorEvent
*
*	editor to test player color
************************************************************************************************************************
*/
class ChangeColorEvent : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	ChangeColorEvent(int skinidx, int eyesidx, int hairidx, int outfitidx, int weaponidx, 
						int mountidx, int mountidx2)
		: _skinidx(skinidx), _eyesidx(eyesidx), _hairidx(hairidx), _outfitidx(outfitidx),
			_weaponidx(weaponidx), _mountidx(mountidx), _mountidx2(mountidx2)
	{
	}

	int _skinidx;
	int _eyesidx;
	int _hairidx;
	int _outfitidx;
	int _weaponidx;
	int _mountidx;
	int _mountidx2;
};



/*
************************************************************************************************************************
*                                                  class ChangeColorEvent
*
*	editor to test player color
************************************************************************************************************************
*/
class EditorTeleportPlayerEvent : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	EditorTeleportPlayerEvent(long playerid, const LbaNet::PlayerPosition & newpos)
		: _newpos(newpos), _playerid(playerid)
	{
	}

	long						_playerid;
	LbaNet::PlayerPosition		_newpos;
};



/*
************************************************************************************************************************
*                                                  class FocusChatEvent
*
*	used to focus chat box edit line
************************************************************************************************************************
*/
class UpdateExtraInfoEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	UpdateExtraInfoEvent(const LbaNet::ObjectExtraInfo& extrainfo)
		: _extrainfo(extrainfo)
	{
	}

	LbaNet::ObjectExtraInfo _extrainfo;
};


/*
************************************************************************************************************************
*                                                  class UpdateEditor_AddOrModSpawning
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_Refreshscript : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_Refreshscript()
	{
	}
};



/*
************************************************************************************************************************
*                                                  class UpdateEditor_RefreshNavMesh
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_RefreshNavMesh : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_RefreshNavMesh()
	{
	}
};



/*
************************************************************************************************************************
*                                                  class UpdateEditor_RefreshNavMesh
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_NPCAttack : public LbaNet::EditorUpdateBase
{
public:
	//! constructor
	UpdateEditor_NPCAttack(bool attack, long npcid, long playerid)
		: _attack(attack), _npcid(npcid), _playerid(playerid)
	{
	}

	bool	_attack;
	long	_npcid;
	long	_playerid;
};


#endif