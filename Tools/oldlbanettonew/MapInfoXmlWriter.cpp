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


#include "MapInfoXmlWriter.h"
#include <fstream>
#include "tinyxml.h"

// save world information into file
void MapInfoXmlWriter::SaveWorld(const std::string &Filename, WorldInfo & wi)
{
	TiXmlDocument doc;
	std::string s;

 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
	doc.LinkEndChild( decl );

	TiXmlElement * root = new TiXmlElement("World");
	doc.LinkEndChild( root );
	root->SetAttribute("name", wi.Name);
	root->SetAttribute("firstmap", wi.FirstMap);
	root->SetAttribute("firstsparea", wi.FirstSpawning);

	TiXmlElement * desc = new TiXmlElement( "description" );
	root->LinkEndChild(desc);
	desc->LinkEndChild(new TiXmlText(wi.Description));


	TiXmlElement * maps = new TiXmlElement( "maps" );
	root->LinkEndChild(maps);

	std::map<std::string, MapInfo>::iterator it = wi.Maps.begin();
	std::map<std::string, MapInfo>::iterator end = wi.Maps.end();
	for(; it != end; ++it)
	{
		TiXmlElement * map = new TiXmlElement( "Map" );
		maps->LinkEndChild(map);


		std::string worldmapname = wi.Name;
		std::string mapname2 = it->second.Files["Maps"];
		mapname2 = mapname2.substr(0, mapname2.find_last_of("/"));
		mapname2 = mapname2.substr(mapname2.find_last_of("/")+1);
		if(mapname2 == "Lba1")
			worldmapname = "Lba1Original";
		if(mapname2 == "Lba2")
			worldmapname = "Lba2Original";


		map->SetAttribute("name", it->first);
		map->SetAttribute("type", it->second.Type);
		map->SetAttribute("music", "World/"+worldmapname+"/"+it->second.Music);
		map->SetAttribute("repeatmusic", it->second.MusicLoop);

		map->SetAttribute("AutoCameraType", 1);
		map->SetAttribute("IsInstance", "false");
		map->SetAttribute("HurtFallFactor", 2);


		TiXmlElement * descm = new TiXmlElement( "description" );
		map->LinkEndChild(descm);
		descm->LinkEndChild(new TiXmlText(it->second.Description));



	}

	doc.SaveFile(Filename);
}

