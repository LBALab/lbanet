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

#include "Localizer.h"
#include "XmlReader.h"

Localizer* Localizer::_singletonInstance = NULL;



/***********************************************************
	Constructor
***********************************************************/
Localizer::Localizer()
{
	RefreshGuiTexts();
}


/***********************************************************
	Destructor
***********************************************************/
Localizer::~Localizer()
{

}


/***********************************************************
singleton pattern
***********************************************************/
Localizer * Localizer::getInstance()
{
	if(!_singletonInstance)
		_singletonInstance = new Localizer();

	return _singletonInstance;
}






/***********************************************************
load world information into memory
***********************************************************/
void Localizer::SetWorldName(std::string WorldName)
{
	if(_currentworldname != WorldName)
	{
		_currentworldname = WorldName;
		RefreshTexts();
	}
}



/***********************************************************
get the text given a text id
***********************************************************/
std::string Localizer::GetText(LocalizeType type, long TextId)
{
	switch(type)
	{
		case GUI:
			return _gui_texts[TextId];			
		break;

		case Map:
			return _map_texts[TextId];	
		break;

		case Quest:
			return _quest_texts[TextId];		
		break;

		case Inventory:
			return _inventory_texts[TextId];			
		break;

		case Name:
			return _name_texts[TextId];			
		break;
	}

	return "unknown";
}


/***********************************************************
set game language
***********************************************************/
void Localizer::SetLanguage(std::string lang)
{

#ifndef _USE_QT_EDITOR_
	if(_lang != lang)
	{
		_lang = lang;
		RefreshGuiTexts();
		RefreshTexts();
	}
#else
		_lang = "en";
		RefreshGuiTexts();
		RefreshTexts();
#endif

}


/***********************************************************
refresh text files
***********************************************************/
void Localizer::RefreshTexts()
{
	if(_currentworldname == "")
		return;

	_map_texts.clear();
	_inventory_texts.clear();
	_quest_texts.clear();
	_name_texts.clear();

	_map_texts = XmlReader::LoadTextFile("Data/Worlds/"+_currentworldname+"/Texts/" + _lang + "/map.xml");
	_inventory_texts = XmlReader::LoadTextFile("Data/Worlds/"+_currentworldname+"/Texts/" + _lang + "/inventory.xml");
	_quest_texts = XmlReader::LoadTextFile("Data/Worlds/"+_currentworldname+"/Texts/" + _lang + "/quest.xml");
	_name_texts = XmlReader::LoadTextFile("Data/Worlds/"+_currentworldname+"/Texts/" + _lang + "/name.xml");


	// then add non translated english text if needed
	if(_lang != "en")
	{
		{
		std::map<long, std::string> tmp = XmlReader::LoadTextFile("Data/Worlds/"+_currentworldname+"/Texts/en/map.xml");
		_map_texts.insert(tmp.begin(),tmp.end());
		}
		{
		std::map<long, std::string> tmp = XmlReader::LoadTextFile("Data/Worlds/"+_currentworldname+"/Texts/en/inventory.xml");
		_inventory_texts.insert(tmp.begin(),tmp.end());
		}
		{
		std::map<long, std::string> tmp = XmlReader::LoadTextFile("Data/Worlds/"+_currentworldname+"/Texts/en/quest.xml");
		_quest_texts.insert(tmp.begin(),tmp.end());
		}
		{
		std::map<long, std::string> tmp = XmlReader::LoadTextFile("Data/Worlds/"+_currentworldname+"/Texts/en/name.xml");
		_name_texts.insert(tmp.begin(),tmp.end());
		}
	}
}


/***********************************************************
refresh text files
***********************************************************/
void Localizer::RefreshGuiTexts()
{
	_gui_texts.clear();

	// first load the choosen language
	_gui_texts = XmlReader::LoadTextFile("Data/GUI/texts/" + _lang + ".xml");

	// then add non translated english text if needed
	if(_lang != "en")
	{
		std::map<long, std::string> tmp = XmlReader::LoadTextFile("Data/GUI/texts/en.xml");
		_gui_texts.insert(tmp.begin(),tmp.end());
	}
}


/***********************************************************
editor functions
***********************************************************/
std::map<long, std::string> Localizer::GetMap(const std::string &texttype)
{
	if(texttype == "inventory")
		return _inventory_texts;

	if(texttype == "quest")
		return _quest_texts;

	if(texttype == "name")
		return _name_texts;

	return _map_texts;
}

/***********************************************************
editor functions
***********************************************************/
void Localizer::AddToMap(const std::string &texttype, long id, const std::string &text)
{
	std::map<long, std::string> &map = _map_texts;

	if(texttype == "inventory")
		map = _inventory_texts;

	if(texttype == "quest")
		map = _quest_texts;

	if(texttype == "name")
		map = _name_texts;

	map[id] = text;
}


/***********************************************************
editor functions
***********************************************************/
void Localizer::RemoveFromMap(const std::string &texttype, long id)
{
	std::map<long, std::string> &map = _map_texts;

	if(texttype == "inventory")
		map = _inventory_texts;

	if(texttype == "quest")
		map = _quest_texts;

	if(texttype == "name")
		map = _name_texts;

	std::map<long, std::string>::iterator it = map.find(id);
	if(it != map.end())
		map.erase(it);
}


/***********************************************************
editor functions
***********************************************************/
void Localizer::SaveTexts()
{
	//todo - save texts
}