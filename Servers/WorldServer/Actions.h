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

#ifndef _LBANET_ACTION_H__
#define _LBANET_ACTION_H__

#include <LbaTypes.h>
class MapHandler;

//! base class used as action to be performed on trigger
class ActionBase
{
public:
	//! constructor
	ActionBase(){}
	
	//! destructor
	virtual ~ActionBase(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	virtual void Execute(MapHandler * owner, LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId) = 0;

};


//! use to teleport the object to a new location
class Teleport
{
public:
	//! constructor
	Teleport(const std::string & NewMap, const std::string & Spawning);
	
	//! destructor
	virtual ~Teleport(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	virtual void Execute(MapHandler * owner, LbaNet::ObjectTypeEnum OType, Ice::Long ObjectId);

private:
	std::string		_NewMap;
	std::string		_Spawning;

};


#endif
