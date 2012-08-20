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

#include "DataDirHandler.h"


DataDirHandler* DataDirHandler::_singletonInstance = NULL;



/***********************************************************
	Constructor
***********************************************************/
DataDirHandler::DataDirHandler()
	: _dataDirPath("./Data")
{
}



/***********************************************************
	Destructor
***********************************************************/
DataDirHandler::~DataDirHandler()
{

}

/***********************************************************
singleton pattern
***********************************************************/
DataDirHandler * DataDirHandler::getInstance()
{
	if(!_singletonInstance)
		_singletonInstance = new DataDirHandler();

	return _singletonInstance;
}


/***********************************************************
set the path to the data dir
***********************************************************/
void DataDirHandler::SetDataDirPath(const std::string & datapath)
{
	_dataDirPath = datapath;
}

/***********************************************************
get the path to the data dir
***********************************************************/	
const std::string & DataDirHandler::GetDataDirPath()
{
	return _dataDirPath;
}
