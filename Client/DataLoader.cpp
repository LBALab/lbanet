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
#include "Localizer.h"
#include "FileUtil.h"

#include <LbaTypes.h>
#include <fstream>



/***********************************************************
constructor
***********************************************************/
TriangleMeshInfo::TriangleMeshInfo(const std::string & filename, bool deletematerial)
: _deletematerial(deletematerial), _sizevertex(0), _sizeindices(0), _sizematerials(0)
{
	_buffervertex = NULL;
	_bufferindices = NULL;
	_buffermaterials = NULL;

	// load data from binary file and set it into a triangle mesh
	std::ifstream file(filename.c_str(), std::ifstream::binary);
	if(!file.is_open())
		return;

	file.read((char*)&_sizevertex, sizeof(unsigned int));
	file.read((char*)&_sizeindices, sizeof(unsigned int));
	file.read((char*)&_sizematerials, sizeof(unsigned int));

	_buffervertex = new float[_sizevertex];
	_bufferindices = new unsigned int[_sizeindices];
	file.read((char*)_buffervertex, _sizevertex*sizeof(float));
	file.read((char*)_bufferindices, _sizeindices*sizeof(unsigned int));

	if(_sizematerials > 0)
	{
		_buffermaterials = new short[_sizematerials];
		file.read((char*)_buffermaterials, _sizematerials*sizeof(short));
	}
}

/***********************************************************
destructor
***********************************************************/
TriangleMeshInfo::~TriangleMeshInfo()
{
	if(_buffervertex)
		delete[] _buffervertex;

	if(_bufferindices)
		delete[] _bufferindices;

	if(_deletematerial && _buffermaterials)
		delete[] _buffermaterials;

}







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

		Localizer::getInstance()->SetWorldName(WorldName);
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

