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

#ifndef _LBANET_TELEPORT_H__
#define _LBANET_TELEPORT_H__


#include <string>
#include <fstream>
#include "Conditions.h"

//! base class handling teleport
class TeleportDef
{
public:
	//! constructor
	TeleportDef(long id)
		: _Id(id)
	{}
	
	//! destructor
	virtual ~TeleportDef(void){}

	//! accessor
	long GetId()
	{return _Id;}

	//! accessor
	std::string GetName() const
	{return _Name;}

	//! accessor
	void SetName(const std::string &name)
	{_Name = name;}

	//! accessor
	std::string GetMapName() const
	{return _MapName;}

	//! accessor
	void SetMapName(const std::string &name)
	{_MapName = name;}

	//! accessor
	long GetSpawn() const
	{return _SpawnId;}

	//! accessor
	void SetSpawn(long spawn)
	{_SpawnId = spawn;}

	//! accessor
	void SetCondition(ConditionBasePtr	condition)
	{ _condition = condition; }

	//! accessor
	ConditionBasePtr GetCondition() const
	{ return _condition; }

	// save Teleport to lua file
	void SaveToLuaFile(std::ofstream & file);

	//! check if tp valid for player
	bool ValidForPlayer(ScriptEnvironmentBase * owner, long playerid) const;

protected:

    long								_Id;
	std::string							_Name;
	std::string							_MapName;
	long								_SpawnId;

	ConditionBasePtr					_condition;
};



#endif
