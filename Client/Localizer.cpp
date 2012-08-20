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
#include "FileUtil.h"

#include "DataDirHandler.h"

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
get languages available
***********************************************************/
std::vector<std::string> Localizer::GetLanguages()
{
	std::vector<std::string> res;
	FileUtil::ListDirsNoPathInDir(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/", res);
	return res;
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
	_map_voices.clear();
	_inventory_voices.clear();


	_map_texts = XmlReader::LoadTextFile(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + _lang + "/map.xml");
	_inventory_texts = XmlReader::LoadTextFile(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + _lang + "/inventory.xml");
	_quest_texts = XmlReader::LoadTextFile(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + _lang + "/quest.xml");
	_name_texts = XmlReader::LoadTextFile(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + _lang + "/name.xml");

	_map_voices = XmlReader::LoadVoiceFile(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Voices/" + _lang + "/map.xml");
	_inventory_voices = XmlReader::LoadVoiceFile(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Voices/" + _lang + "/inventory.xml");



#ifdef _USE_QT_EDITOR_
	_map_texts_ed.clear();
	_inventory_texts_ed.clear();
	_quest_texts_ed.clear();
	_name_texts_ed.clear();
	_map_voices_ed.clear();
	_inventory_voices_ed.clear();

	CheckMapPresent(_lang);
	CheckVoiceMapPresent(_lang);
#endif


	// then add non translated english text if needed
	if(_lang != "en")
	{
		{
		std::map<long, std::string> tmp = XmlReader::LoadTextFile(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/en/map.xml");
		_map_texts.insert(tmp.begin(),tmp.end());
		}
		{
		std::map<long, std::string> tmp = XmlReader::LoadTextFile(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/en/inventory.xml");
		_inventory_texts.insert(tmp.begin(),tmp.end());
		}
		{
		std::map<long, std::string> tmp = XmlReader::LoadTextFile(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/en/quest.xml");
		_quest_texts.insert(tmp.begin(),tmp.end());
		}
		{
		std::map<long, std::string> tmp = XmlReader::LoadTextFile(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/en/name.xml");
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
	_gui_texts = XmlReader::LoadTextFile(DataDirHandler::getInstance()->GetDataDirPath() + "/GUI/texts/" + _lang + ".xml");

	// then add non translated english text if needed
	if(_lang != "en")
	{
		std::map<long, std::string> tmp = XmlReader::LoadTextFile(DataDirHandler::getInstance()->GetDataDirPath() + "/GUI/texts/en.xml");
		_gui_texts.insert(tmp.begin(),tmp.end());
	}
}






/***********************************************************
get the text given a text id
***********************************************************/
std::string Localizer::GetText(LocalizeType type, long TextId, std::string lang)
{
	if(TextId < 0)
		return "";

	if(lang == "")
		lang = _lang;


#ifdef _USE_QT_EDITOR_
	switch(type)
	{
		case GUI:
			return _gui_texts[TextId];			
		break;

		case Map:
			return _map_texts_ed[lang][TextId];	
		break;

		case Quest:
			return _quest_texts_ed[lang][TextId];		
		break;

		case Inventory:
			return _inventory_texts_ed[lang][TextId];			
		break;

		case Name:
			return _name_texts_ed[lang][TextId];			
		break;
	}
#else
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
#endif

	return "unknown";
}


/***********************************************************
get the voice given a text id
***********************************************************/
std::vector<std::string> Localizer::GetVoices(LocalizeType type, long TextId, std::string lang)
{
	if(TextId < 0)
		return std::vector<std::string>();

	if(lang == "")
		lang = _lang;


#ifdef _USE_QT_EDITOR_
	switch(type)
	{
		case Map:
			return _map_voices_ed[lang][TextId];	
		break;

		case Inventory:
			return _inventory_voices_ed[lang][TextId];			
		break;
	}
#else
	switch(type)
	{
		case Map:
			return _map_voices[TextId];	
		break;

		case Inventory:
			return _inventory_voices[TextId];			
		break;
	}
#endif

	return std::vector<std::string>();
}





/***********************************************************
get voices dir path
***********************************************************/
std::string Localizer::GetVoiceDirPath(const std::string &lang)
{
	return (DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Voices/" + lang);
}

#ifdef _USE_QT_EDITOR_
/***********************************************************
editor functions
***********************************************************/
std::map<long, std::string> Localizer::GetMap(LocalizeType texttype, const std::string &lang)
{
	CheckMapPresent(lang);
	CheckVoiceMapPresent(lang);

	switch(texttype)
	{
		case Map:
			return _map_texts_ed[lang];
		break;
		case Quest:
			return _quest_texts_ed[lang];
		break;
		case Inventory:
			return _inventory_texts_ed[lang];
		break;
		case Name:
			return _name_texts_ed[lang];
		break;
	}

	return _map_texts_ed[lang];
}

/***********************************************************
editor functions
return new index in case of insertion
***********************************************************/
long Localizer::AddToMap(LocalizeType texttype, long id, const std::string &text, const std::string &lang)
{
	CheckMapPresent(lang);

	std::map<long, std::string> *map = &_map_texts_ed[lang];

	switch(texttype)
	{
		case Map:
			map = &_map_texts_ed[lang];
		break;
		case Quest:
			map = &_quest_texts_ed[lang];
		break;
		case Inventory:
			map = &_inventory_texts_ed[lang];
		break;
		case Name:
			map = &_name_texts_ed[lang];
		break;
	}


	if(id < 0)
	{
		long res = 1;
		if(map->size() > 0)
			res = map->rbegin()->first + 1;

		(*map)[res] = text;
		return res;
	}
	else
	{
		(*map)[id] = text;
		return id;
	}
}


/***********************************************************
editor functions
***********************************************************/
void Localizer::RemoveFromMap(LocalizeType texttype, long id, const std::string &lang)
{
	CheckMapPresent(lang);

	std::map<long, std::string> *map = &_map_texts_ed[lang];

	switch(texttype)
	{
		case Map:
			map = &_map_texts_ed[lang];
		break;
		case Quest:
			map = &_quest_texts_ed[lang];
		break;
		case Inventory:
			map = &_inventory_texts_ed[lang];
		break;
		case Name:
			map = &_name_texts_ed[lang];
		break;
	}

	std::map<long, std::string>::iterator it = map->find(id);
	if(it != map->end())
		map->erase(it);
}





/***********************************************************
return new index in case of insertion
***********************************************************/
long Localizer::AddToMapVoice(LocalizeType texttype, long id, const std::vector<std::string> &voices, 
							  const std::string &lang)
{
	CheckVoiceMapPresent(lang);

	std::map<long, std::vector<std::string> > *map = NULL;

	switch(texttype)
	{
		case Map:
			map = &_map_voices_ed[lang];
		break;
		case Inventory:
			map = &_inventory_voices_ed[lang];
		break;
	}

	if(map == NULL)
		return -1;

	if(id < 0)
	{
		long res = map->rbegin()->first + 1;
		(*map)[res] = voices;
		return res;
	}
	else
	{
		(*map)[id] = voices;
		return id;
	}
}

/***********************************************************
editor functions
***********************************************************/
void Localizer::RemoveFromMapVoice(LocalizeType texttype, long id, const std::string &lang)
{
	CheckVoiceMapPresent(lang);

	std::map<long, std::vector<std::string> > *map = NULL;

	switch(texttype)
	{
		case Map:
			map = &_map_voices_ed[lang];
		break;
		case Inventory:
			map = &_inventory_voices_ed[lang];
		break;
	}
	
	if(map == NULL)
		return;

	std::map<long, std::vector<std::string> >::iterator it = map->find(id);
	if(it != map->end())
		map->erase(it);
}


/***********************************************************
editor functions
***********************************************************/
void Localizer::SaveTexts()
{
	if(_currentworldname == "")
		return;

	{
		std::map<std::string, std::map<long, std::string> >::iterator itm = _map_texts_ed.begin();
		std::map<std::string, std::map<long, std::string> >::iterator endm = _map_texts_ed.end();

		for(;itm != endm; ++itm)
		{
			// create dir if not exist already
			FileUtil::CreateNewDirectory(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + itm->first);

			XmlReader::SaveTextFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + itm->first + "/map.xml", _map_texts_ed[itm->first]);
			XmlReader::SaveTextFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + itm->first + "/inventory.xml", _inventory_texts_ed[itm->first]);
			XmlReader::SaveTextFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + itm->first + "/quest.xml", _quest_texts_ed[itm->first]);
			XmlReader::SaveTextFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + itm->first + "/name.xml", _name_texts_ed[itm->first]);
		}
	}


	{
		std::map<std::string, std::map<long, std::vector<std::string> > >::iterator itm = _map_voices_ed.begin();
		std::map<std::string, std::map<long, std::vector<std::string> > >::iterator endm = _map_voices_ed.end();

		for(;itm != endm; ++itm)
		{
			// create dir if not exist already
			FileUtil::CreateNewDirectory(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Voices/" + itm->first);

			XmlReader::SaveVoiceFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Voices/" + itm->first + "/map.xml", _map_voices_ed[itm->first]);
			XmlReader::SaveVoiceFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Voices/" + itm->first + "/inventory.xml", _inventory_voices_ed[itm->first]);
		}
	}
}



/***********************************************************
check map loaded, if not load it
***********************************************************/
void Localizer::CheckMapPresent(const std::string & lang)
{	
	if(_currentworldname == "")
		return;

	if(_map_texts_ed.find(lang) == _map_texts_ed.end())
	{
		_map_texts_ed[lang] = XmlReader::LoadTextFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + lang + "/map.xml");
		_inventory_texts_ed[lang] = XmlReader::LoadTextFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + lang + "/inventory.xml");
		_quest_texts_ed[lang] = XmlReader::LoadTextFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + lang + "/quest.xml");
		_name_texts_ed[lang] = XmlReader::LoadTextFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Texts/" + lang + "/name.xml");	
	}


}

/***********************************************************
check map loaded, if not load it
***********************************************************/
void Localizer::CheckVoiceMapPresent(const std::string & lang)
{
	if(_currentworldname == "")
		return;

	if(_map_voices_ed.find(lang) == _map_voices_ed.end())
	{
		_map_voices_ed[lang] = XmlReader::LoadVoiceFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Voices/" + lang + "/map.xml");
		_inventory_voices_ed[lang] = XmlReader::LoadVoiceFile(DataLoader::getInstance()->GetDataDirPath() + "/Worlds/"+_currentworldname+"/Voices/" + lang + "/inventory.xml");
	}
}
#endif