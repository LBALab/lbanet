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

/*
************************************************************************************************************************
*                                                  class EditorUpdateBase
*
*	base class for all editor update
************************************************************************************************************************
*/
class EditorUpdateBase
{
public:
	//! constructor
	EditorUpdateBase()
	{
	}
};


/*
************************************************************************************************************************
*                                                  class UpdateEditor_AddOrModSpawning
*
*	base class for all editor update
************************************************************************************************************************
*/
class UpdateEditor_AddOrModSpawning : public EditorUpdateBase
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
class UpdateEditor_RemoveSpawning : public EditorUpdateBase
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
*                                                  class EditorEvent
*
*	class used for editor event between client and server
************************************************************************************************************************
*/
class EditorEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	EditorEvent(boost::shared_ptr<EditorUpdateBase> update)
		: _update(update)
	{
	}

	boost::shared_ptr<EditorUpdateBase> _update;

};


#endif