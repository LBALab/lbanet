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


#if !defined(__LbaNetModel_1_DataLoader_h)
#define __LbaNetModel_1_DataLoader_h

#include <string>
#include <vector>
#include <map>
#include <LbaTypes.h>

/***********************************************************************
 * Module:  DataLoader.h
 * Author:  vivien
 * Modified: lundi 27 juillet 2009 14:56:34
 * Purpose: Declaration of the class DataLoader
 ***********************************************************************/
class DataLoader
{
public:

	//! destructor
	~DataLoader();

	// singleton pattern
	static DataLoader * getInstance();


	//! set current world name
	void SetWorldName(std::string WorldName);


	//! get the text given a text id
	std::string GetText(long TextId);
	std::string GetInventoryText(long TextId);
	std::string GetQuestText(long TextId);
	std::string GetNameText(long TextId);


	//! set game language
	void SetLanguage(std::string lang);

	//! get language
	std::string GetLanguage()
	{return _lang;}


	//! get list of available worlds
	void GetAvailableWorlds(std::vector<LbaNet::WorldDesc> & list);


protected:
	//! constructor
   DataLoader();

   //! refresh text files
   void RefreshTexts();

private:
	static DataLoader *		_singletonInstance;

	std::string						_currentworldname;

	std::map<long, std::string>		_map_texts;
	std::map<long, std::string>		_inventory_texts;
	std::map<long, std::string>		_quests_texts;
	std::map<long, std::string>		_name_texts;

	std::string						_lang;

};

#endif