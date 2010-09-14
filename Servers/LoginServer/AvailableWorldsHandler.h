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


#ifndef _AVAILABLE_WORLDS_HD_H
#define _AVAILABLE_WORLDS_HD_H

#include <LbaTypes.h>
#include <WorldServerInterface.h>

using namespace LbaNet;

class AvailableWorldsHandler
{
public:
	// singleton pattern
	static AvailableWorldsHandler * getInstance();

	//! destructor
	~AvailableWorldsHandler(void);

	// add a world to the list
	void AddWorld(const WorldDesc &desc, const WorldServerInterfacePrx & proxy);

	// remove a world from list
	void RemoveWorld(const std::string worldname);

	// get list of worlds
	WorldsSeq GetWorldList();

	// get proxy to a specific world - NULL if not existing
	WorldServerInterfacePrx GetWorldProxy(const std::string worldname);


protected:
	//! constructor
	AvailableWorldsHandler(void);


private:
	static AvailableWorldsHandler *						_singletoninstance;

	IceUtil::Mutex										_mutex;
	std::map<std::string, WorldDesc>					_worldsinfo;
	std::map<std::string, WorldServerInterfacePrx>		_worldsproxy;

};

#endif