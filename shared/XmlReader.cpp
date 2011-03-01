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
#include <boost/property_tree/detail/xml_parser_writer_settings.hpp>




/***********************************************************
load a world information into memory
***********************************************************/
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




	// get the starting info
	res.StartingInfo.InventorySize = pt.get<int>("World.PlayerStartingInfo.InventorySize", 1);
	res.StartingInfo.StartingLife = pt.get<float>("World.PlayerStartingInfo.StartingLife", 1);
	res.StartingInfo.StartingMana = pt.get<float>("World.PlayerStartingInfo.StartingMana", 1);	
	res.StartingInfo.StartingMap = pt.get<std::string>("World.PlayerStartingInfo.StartingMap", "");
	res.StartingInfo.SpawningId = pt.get<long>("World.PlayerStartingInfo.SpawningId", -1);
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

	// get the inventory
	try
	{
		BOOST_FOREACH(ptree::value_type &v, pt.get_child("World.PlayerStartingInfo.StartingInventory"))
		{
			ItemPosInfo itm;
			itm.Count = v.second.get<int>("Number");
			itm.Position = v.second.get<int>("Position");
			res.StartingInfo.StartingInventory[v.second.get<long>("ObjectId")] = itm;
		}
	}
	catch(...){} // no inventory
	


	// get the maps
	try
	{
		BOOST_FOREACH(ptree::value_type &v, pt.get_child("World.maps"))
		{
			if(v.first != "<xmlcomment>")
			{
				MapInfo mapi;
				mapi.Name = v.second.get<std::string>("<xmlattr>.name");
				mapi.Type = v.second.get<std::string>("<xmlattr>.type");
				mapi.Description = v.second.get<std::string>("description", "");
				mapi.AutoCameraType = v.second.get<int>("<xmlattr>.AutoCameraType", 1);
				mapi.IsInstance = v.second.get<bool>("<xmlattr>.IsInstance", false);
				mapi.HurtFallFactor = v.second.get<float>("<xmlattr>.HurtFallFactor", 2);
				mapi.Music = v.second.get<std::string>("<xmlattr>.music", "");
				mapi.Repeat = v.second.get<int>("<xmlattr>.repeatmusic", 0);

				res.Maps[mapi.Name] = mapi;
			}
		}
	}
	catch(...){} // no map

	return true;
}



/***********************************************************
save a world information into file
***********************************************************/
bool XmlReader::SaveWorldInfo(const std::string &Filename, const WorldInformation &res)
{
	// Create an empty property tree object
	using boost::property_tree::ptree;
	ptree pt;


	// get map description
    pt.put("World.name", res.Description.WorldName);
    pt.put("World.description", res.Description.Description);
    pt.put("World.news", res.Description.News);


	//// get the starting info
	pt.put("World.PlayerStartingInfo.InventorySize", res.StartingInfo.InventorySize);
	pt.put("World.PlayerStartingInfo.StartingLife", res.StartingInfo.StartingLife);
	pt.put("World.PlayerStartingInfo.StartingMana", res.StartingInfo.StartingMana);	
	pt.put("World.PlayerStartingInfo.StartingMap", res.StartingInfo.StartingMap);
	pt.put("World.PlayerStartingInfo.SpawningId", res.StartingInfo.SpawningId);
	pt.put("World.PlayerStartingInfo.StartingModel.ModelName", res.StartingInfo.StartingModel.ModelName);
	pt.put("World.PlayerStartingInfo.StartingModel.Outfit", res.StartingInfo.StartingModel.Outfit);
	pt.put("World.PlayerStartingInfo.StartingModel.Weapon", res.StartingInfo.StartingModel.Weapon);
	pt.put("World.PlayerStartingInfo.StartingModel.Mode", res.StartingInfo.StartingModel.Mode);

	switch(res.StartingInfo.StartingModel.TypeRenderer)
	{
		case LbaNet::RenderOsgModel: // -> osg model
			pt.put("World.PlayerStartingInfo.StartingModel.RendererType", 0);
		break;

		case LbaNet::RenderSprite: // 1 -> sprite
			pt.put("World.PlayerStartingInfo.StartingModel.RendererType", 1);
		break;

		case LbaNet::RenderLba1M: // 2 -> LBA1 model
			pt.put("World.PlayerStartingInfo.StartingModel.RendererType", 2);
		break;

		case LbaNet::RenderLba2M: // 3 -> LBA2 model
			pt.put("World.PlayerStartingInfo.StartingModel.RendererType", 3);
		break;
	}


    BOOST_FOREACH(const LbaNet::ItemsMap::value_type &itm, res.StartingInfo.StartingInventory)
	{
		ptree &tmp = pt.add("World.PlayerStartingInfo.StartingInventory.object","");
		tmp.put("ObjectId", itm.first);
		tmp.put("Number", itm.second.Count);
		tmp.put("Position", itm.second.Position);
	}

	
	// get the maps
    BOOST_FOREACH(const LbaNet::MapsSeq::value_type &mapi, res.Maps)
	{
		ptree &tmp = pt.add("World.maps.Map","");
		tmp.put("<xmlattr>.name", mapi.second.Name);
		tmp.put("<xmlattr>.type", mapi.second.Type);
		tmp.put("description", mapi.second.Description);
		tmp.put("<xmlattr>.AutoCameraType", mapi.second.AutoCameraType);
		tmp.put("<xmlattr>.IsInstance", mapi.second.IsInstance);
		tmp.put("<xmlattr>.HurtFallFactor", mapi.second.HurtFallFactor);
		tmp.put("<xmlattr>.music", mapi.second.Music);
		tmp.put("<xmlattr>.repeatmusic", mapi.second.Repeat);
	}

	// Write the property tree into the XML file 
	try
	{
		const boost::property_tree::xml_parser::xml_writer_settings<char> settings('	', 1);
		write_xml(Filename, pt, std::locale(), settings);
	}
	catch(...)
	{
		return false;
	}
	return true;
}





/***********************************************************
load a world description into memory
***********************************************************/
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

 

/***********************************************************
get a text from file
***********************************************************/
std::map<long, std::string> XmlReader::LoadTextFile(const std::string &Filename)
{
	std::map<long, std::string> res;


	// Create an empty property tree object
	using boost::property_tree::wptree;
	wptree pt;

	// Load the XML file into the property tree
	try
	{
		read_xml(Filename, pt);
	}
	catch(...)
	{
		return res;
	}

	// get text info
	try
	{
		BOOST_FOREACH(wptree::value_type &v, pt.get_child(L"texts"))
		{
			long Id = v.second.get<long>(L"<xmlattr>.id");
			std::wstring text = v.second.data();
			std::string conv(text.begin(), text.end());
			res[Id] = conv;
		}
	}
	catch(...){} // no text


	return res;
}



/***********************************************************
save text in file
***********************************************************/
void XmlReader::SaveTextFile(const std::string &Filename, const std::map<long, std::string> &text)
{
	// Create an empty property tree object
	using boost::property_tree::ptree;
	ptree pt;

	typedef std::map<long, std::string> textseq;

	// get teleport info
    BOOST_FOREACH(const textseq::value_type &txt, text)
	{
		ptree &tmp = pt.add("texts.text", txt.second);
		tmp.put("<xmlattr>.id", txt.first);
	}


	// Write the property tree into the XML file 
	try
	{
		const boost::property_tree::xml_parser::xml_writer_settings<char> settings('	', 1);
		write_xml(Filename, pt, std::locale(), settings);
	}
	catch(...)
	{
	}
}

