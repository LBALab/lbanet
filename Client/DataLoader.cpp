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

#include "DataLoader.h"
#include "LogHandler.h"
#include "XmlReader.h"

#include "FileUtil.h"

#include <LbaTypes.h>
#include <fstream>

#ifndef  _LBANET_SERVER_SIDE_
#include "Localizer.h"
#endif









DataLoader* DataLoader::_singletonInstance = NULL;



/***********************************************************
	Constructor
***********************************************************/
DataLoader::DataLoader()
{
	LogHandler::getInstance()->LogToFile("Initializing data handler class...");
}



/***********************************************************
	Destructor
***********************************************************/
DataLoader::~DataLoader()
{

}


/***********************************************************
singleton pattern
***********************************************************/
DataLoader * DataLoader::getInstance()
{
	if(!_singletonInstance)
		_singletonInstance = new DataLoader();

	return _singletonInstance;
}






/***********************************************************
load world information into memory
***********************************************************/
void DataLoader::SetWorldName(std::string WorldName)
{
	if(_currentworldname != WorldName)
	{
		_currentworldname = WorldName;

#ifndef  _LBANET_SERVER_SIDE_
		Localizer::getInstance()->SetWorldName(WorldName);
#endif
	}
}



/***********************************************************
get the list of available worlds
***********************************************************/
void DataLoader::GetAvailableWorlds(std::vector<LbaNet::WorldDesc> & list)
{
	// get all xml file of the directory
	std::vector<std::string> files;
	if(!FileUtil::ListDirsInDir("./Data/Worlds", files, "/WorldDescription.xml"))
	{
		LogHandler::getInstance()->LogToFile(std::string("\nData/Worlds directory Not found!"));
		return;
	}


	// for each file add an entry
	for(size_t i=0; i< files.size(); ++i)
	{
		WorldDesc desc;
		if(XmlReader::LoadWorldDesc(files[i], desc))
			list.push_back(desc);
	}
}

/***********************************************************
get information about a specific world
***********************************************************/
void DataLoader::GetWorldInformation(const std::string &Filename, LbaNet::WorldInformation &res)
{
	XmlReader::LoadWorldInfo( "./Data/Worlds/" + Filename + "/WorldDescription.xml", res);
}


/***********************************************************
saved information about a specific world
***********************************************************/

void DataLoader::SaveWorldInformation(const std::string &Filename, const LbaNet::WorldInformation &res)
{
	XmlReader::SaveWorldInfo( "./Data/Worlds/" + Filename + "/WorldDescription.xml", res);
}

