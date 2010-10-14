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
    res.Description.WorldName = pt.get<std::string>("World.name");
    res.Description.Description = pt.get<std::string>("World.description");
    res.Description.News = pt.get<std::string>("World.news");

	// get teleport info
    BOOST_FOREACH(ptree::value_type &v, pt.get_child("World.teleports"))
	{
		TeleportInfo tpi;
		tpi.Name = v.second.get<std::string>("<xmlattr>.name");
		tpi.MapName = v.second.get<std::string>("<xmlattr>.map");
		tpi.SpawningId = v.second.get<long>("<xmlattr>.spawningid");
		res.TeleportInfo[tpi.Name] = tpi;
	}

	// get the files info
    BOOST_FOREACH(ptree::value_type &v, pt.get_child("World.files"))
	{
		res.FileUsedInfo[v.second.get<std::string>("<xmlattr>.name")] 
								=  v.second.get<std::string>("<xmlattr>.path");
	}



	// get the starting info
	res.StartingInfo.InventorySize = pt.get<int>("World.PlayerStartingInfo.InventorySize");
	res.StartingInfo.StartingLife = pt.get<float>("World.PlayerStartingInfo.StartingLife");
	res.StartingInfo.StartingMana = pt.get<float>("World.PlayerStartingInfo.StartingMana");	
	res.StartingInfo.StartingMap = pt.get<std::string>("World.PlayerStartingInfo.StartingMap");
	res.StartingInfo.SpawningId = pt.get<long>("World.PlayerStartingInfo.SpawningId");
	res.StartingInfo.StartingModel.ModelName = pt.get<std::string>("World.PlayerStartingInfo.StartingModel.ModelName");
	res.StartingInfo.StartingModel.Outfit = pt.get<std::string>("World.PlayerStartingInfo.StartingModel.Outfit");
	res.StartingInfo.StartingModel.Weapon = pt.get<std::string>("World.PlayerStartingInfo.StartingModel.Weapon");
	res.StartingInfo.StartingModel.Mode = pt.get<std::string>("World.PlayerStartingInfo.StartingModel.Mode");
	res.StartingInfo.StartingModel.State = LbaNet::StNormal;

	int renderT = pt.get<int>("World.PlayerStartingInfo.StartingModel.RendererType");
	switch(renderT)
	{
		case 0: // -> osg model
			res.StartingInfo.StartingModel.TypeRenderer = LbaNet::RenderOsgModel;
		break;

		case 1: // 1 -> sprite
			res.StartingInfo.StartingModel.TypeRenderer = LbaNet::RenderSprite;
		break;

		case 2: // -> LBA1 model
			res.StartingInfo.StartingModel.TypeRenderer = LbaNet::RenderLba1M;
		break;

		case 3: // -> LBA2 model
			res.StartingInfo.StartingModel.TypeRenderer = LbaNet::RenderLba2M;
		break;

	}




    BOOST_FOREACH(ptree::value_type &v, pt.get_child("World.PlayerStartingInfo.StartingInventory"))
	{
		InventoryItem itm;
		itm.Number = v.second.get<int>("Number");
		itm.PlaceInInventory = v.second.get<int>("Position");
		res.StartingInfo.StartingInventory[v.second.get<long>("ObjectId")] = itm;
	}

	
	// get the maps
    BOOST_FOREACH(ptree::value_type &v, pt.get_child("World.maps"))
	{
		if(v.first != "<xmlcomment>")
		{
			MapInfo mapi;
			mapi.Name = v.second.get<std::string>("<xmlattr>.name");
			mapi.Type = v.second.get<std::string>("<xmlattr>.type");
			mapi.Description = v.second.get<std::string>("description", "");
			mapi.AutoCameraType = v.second.get<int>("<xmlattr>.AutoCameraType", 1);

			BOOST_FOREACH(ptree::value_type &v2, v.second.get_child("spareas"))
			{
				SpawningInfo spwi;
				spwi.Id = v2.second.get<long>("<xmlattr>.Id");
				spwi.Name = v2.second.get<std::string>("<xmlattr>.name");
				spwi.PosX = v2.second.get<float>("<xmlattr>.posX");
				spwi.PosY = v2.second.get<float>("<xmlattr>.posY");
				spwi.PosZ = v2.second.get<float>("<xmlattr>.posZ");
				spwi.ForceRotation = v2.second.get<bool>("<xmlattr>.ForceRotation", false);
				spwi.Rotation = v2.second.get<float>("<xmlattr>.RotationAtArrival", 0);

				mapi.Spawnings[spwi.Id] = spwi;
			}

			res.Maps[mapi.Name] = mapi;
		}
	}


	return true;
}




// load a world description into memory
 bool XmlReader::LoadWorldDesc(const std::string &Filename, WorldDesc &res)
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
    res.WorldName = pt.get<std::string>("World.name");
    res.Description = pt.get<std::string>("World.description");
    res.News = pt.get<std::string>("World.news");

	return true;
}
