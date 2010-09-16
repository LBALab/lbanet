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


#include "XmlReader.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>


// load a world information into memory
bool XmlReader::LoadWorldInfo(const std::string &Filename, WorldInformation &res)
{
	// Create an empty property tree object
	using boost::property_tree::ptree;
	ptree pt;

	// Load the XML file into the property tree
	try
	{
		read_xml(Filename, pt);
	}
	catch(...)
	{
		return false;
	}

	// get map description
    res.Description.WorldName = pt.get<std::string>("name" );
    res.Description.Description = pt.get<std::string>("description" );
    res.Description.News = pt.get<std::string>("news" );

	// get teleport info
    BOOST_FOREACH(ptree::value_type &v, pt.get_child("teleports"))
	{
		TeleportInfo tpi;
		tpi.Name = v.second.get<std::string>("xmlattr.name");
		tpi.MapName = v.second.get<std::string>("xmlattr.map");
		tpi.SpawningName = v.second.get<std::string>("xmlattr.sparea");
		res.TeleportInfo[tpi.Name] = tpi;
	}

	// get the files info
    BOOST_FOREACH(ptree::value_type &v, pt.get_child("files"))
	{
		res.FileUsedInfo[v.second.get<std::string>("xmlattr.name")] 
								=  v.second.get<std::string>("xmlattr.path");
	}



	// get the starting info
	res.StartingInfo.InventorySize = pt.get<int>("PlayerStartingInfo.InventorySize");
	res.StartingInfo.StartingLife = pt.get<float>("PlayerStartingInfo.StartingLife");
	res.StartingInfo.StartingMana = pt.get<float>("PlayerStartingInfo.StartingMana");	
	res.StartingInfo.StartingMap = pt.get<std::string>("PlayerStartingInfo.StartingMap");
	res.StartingInfo.Spawning = pt.get<std::string>("PlayerStartingInfo.Spawning");
	res.StartingInfo.StartingModel.ModelName = pt.get<std::string>("PlayerStartingInfo.StartingModel.ModelName");
	res.StartingInfo.StartingModel.Outfit = pt.get<std::string>("PlayerStartingInfo.StartingModel.Outfit");
	res.StartingInfo.StartingModel.Weapon = pt.get<std::string>("PlayerStartingInfo.StartingModel.Weapon");
	res.StartingInfo.StartingModel.Mode = pt.get<std::string>("PlayerStartingInfo.StartingModel.Mode");
	
    BOOST_FOREACH(ptree::value_type &v, pt.get_child("PlayerStartingInfo.StartingInventory"))
	{
		InventoryItem itm;
		itm.Number = v.second.get<int>("Number");
		itm.PlaceInInventory = v.second.get<int>("Position");
		res.StartingInfo.StartingInventory[v.second.get<long>("ObjectId")] = itm;
	}

	
	// get the maps
    BOOST_FOREACH(ptree::value_type &v, pt.get_child("maps"))
	{
		MapInfo mapi;
		mapi.Name = v.second.get<std::string>("xmlattr.name");
		mapi.Description = v.second.get<std::string>("description", "");
		mapi.Type = v.second.get<std::string>("xmlattr.type");
		mapi.ObjectFile = v.second.get<std::string>("ObjectFile", "");
		mapi.MusicFile = v.second.get<std::string>("xmlattr.music");
		mapi.RepatMusic = v.second.get<int>("xmlattr.repeatmusic", 0);

		BOOST_FOREACH(ptree::value_type &v2, v.second.get_child("spareas"))
		{
			SpawningInfo spwi;
			spwi.Name = v2.second.get<std::string>("xmlattr.name");
			spwi.PosX = v2.second.get<float>("xmlattr.posX");
			spwi.PosY = v2.second.get<float>("xmlattr.posY");
			spwi.PosZ = v2.second.get<float>("xmlattr.posZ");
			spwi.ForceRotation = v2.second.get<bool>("xmlattr.ForceRotation", false);
			spwi.Rotation = v2.second.get<float>("xmlattr.RotationAtArrival", 0);

			mapi.Spawnings[spwi.Name] = spwi;
		}

		res.Maps[mapi.Name] = mapi;
	}


	return true;
}
