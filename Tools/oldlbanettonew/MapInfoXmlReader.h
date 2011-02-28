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


#ifndef __LBA_NET_MAP_INFO_XML_READER_H__
#define __LBA_NET_MAP_INFO_XML_READER_H__

#include "WorldInfo.h"
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include <LbaTypes.h>
#include "Triggers.h"
#include "ActorHandler.h"
#include "NpcHandler.h"
#include "DoorHandler.h"

class TiXmlElement;


//*************************************************************************************************
//*                                      class MapInfoXmlReader
//*************************************************************************************************

class MapInfoXmlReader
{
public:
	// load a world information into memory
	static  bool LoadWorld(const std::string &Filename, WorldInfo & res);


	// load map actors into memory
	static  bool LoadActors(const std::string &Filename,
							std::map<long, boost::shared_ptr<TriggerBase> >	&triggers,
							std::map<Ice::Long, boost::shared_ptr<ActorHandler> >	&Actors,
							long &triggerid, long &actorid);


protected:
	// load a map information into memory
	static MapInfo LoadMap(TiXmlElement* pElem);

};


#endif
