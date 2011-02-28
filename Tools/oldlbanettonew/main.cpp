/*
------------------------[ Lbanet Tool ]-------------------------
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
#include "MapInfoXmlReader.h"
#include "MapInfoXmlWriter.h"

#include <boost/shared_ptr.hpp>
#include <LbaTypes.h>
#include "Triggers.h"
#include "ActorHandler.h"
#include "Spawn.h"

#include <fstream>
#include <sstream>

int main( int argc, char **argv )
{
	WorldInfo winfo;
	MapInfoXmlReader::LoadWorld("Data/Lba1Original.xml", winfo);
	MapInfoXmlWriter::SaveWorld("Data/Worlds/"+winfo.Name+"/WorldDescription.xml", winfo);


	std::map<std::string, MapInfo>::iterator itmap = winfo.Maps.begin();
	std::map<std::string, MapInfo>::iterator endmap = winfo.Maps.begin();
	for(; itmap != endmap; ++itmap)
	{
		std::map<long, boost::shared_ptr<TriggerBase> >			_triggers;
		std::map<Ice::Long, boost::shared_ptr<ActorHandler> >	_Actors;
		std::map<long, boost::shared_ptr<Spawn> >				_spawns;


		// add spawns
		std::map<std::string, SpawningInfo>::iterator itsp = itmap->second.Spawnings.begin();
		std::map<std::string, SpawningInfo>::iterator endsp = itmap->second.Spawnings.end();
		for(; itsp != endsp; ++itsp)
		{
			boost::shared_ptr<Spawn> newsp(new Spawn(itsp->second.Id));
			newsp->SetPosX(itsp->second.PosX);
			newsp->SetPosY(itsp->second.PosY);
			newsp->SetPosZ(itsp->second.PosZ);
			newsp->SetForceRotation(false);
			newsp->SetName(itsp->first);
			_spawns.push_back(newsp);
		}

		// save to files
		{
			std::stringstream filenames;
			filenames<<"Data/Worlds/"<<winfo.Name<<"Lua/"<<itmap->first<<"_server.lua";
			std::ofstream file(filenames.str().c_str());
			file<<"function InitMap(environment)"<<std::endl;

			// save spawns
			std::map<long, boost::shared_ptr<Spawn> >::iterator its= _spawns.begin();
			std::map<long, boost::shared_ptr<Spawn> >::iterator ends = _spawns.end();
			for(;its != ends; ++its)
				its->second->SaveToLuaFile(file);
			

			// save actors
			std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator ita = _Actors.begin();
			std::map<Ice::Long, boost::shared_ptr<ActorHandler> >::iterator enda = _Actors.end();
			for(;ita != enda; ++ita)
				ita->second->SaveToLuaFile(file);

			// save triggers
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator itt = _triggers.begin();
			std::map<long, boost::shared_ptr<TriggerBase> >::iterator endt = _triggers.end();
			for(;itt != endt; ++itt)
				itt->second->SaveToLuaFile(file);

			file<<"end"<<std::endl;
		}
	}

	return 0;
}


