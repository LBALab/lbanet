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



DataLoader* DataLoader::_singletonInstance = NULL;



/***********************************************************
	Constructor
***********************************************************/
DataLoader::DataLoader()
:  _lang("en")
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

		// process reading all necessary data

		RefreshTexts();
	}
}



/***********************************************************
get the text given a text id
***********************************************************/
std::string DataLoader::GetText(long TextId)
{
	return _map_texts[TextId];
}


/***********************************************************
get the text given a text id
***********************************************************/
std::string DataLoader::GetInventoryText(long TextId)
{
	return _inventory_texts[TextId];
}

/***********************************************************
get the text given a text id
***********************************************************/
std::string DataLoader::GetQuestText(long TextId)
{
	return _quests_texts[TextId];
}

/***********************************************************
get the text given a text id
***********************************************************/
std::string DataLoader::GetNameText(long TextId)
{
	return _name_texts[TextId];
}



/***********************************************************
set game language
***********************************************************/
void DataLoader::SetLanguage(std::string lang)
{
	if(_lang != lang)
	{
		_lang = lang;
		RefreshTexts();
	}
}


/***********************************************************
refresh text files
***********************************************************/
void DataLoader::RefreshTexts()
{

}