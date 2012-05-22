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

#include "ConfigurationManager.h"
#include "LogHandler.h"

#include <boost/property_tree/xml_parser.hpp>


ConfigurationManager* ConfigurationManager::_singletonInstance = NULL;


/***********************************************************
constructor
***********************************************************/
ConfigurationManager::ConfigurationManager()
: _opened(false)
{
	// Load the XML file into the property tree
	try
	{
		read_xml("LBANetGameConfig.xml", _pt);
	}
	catch(...)
	{
		return;
	}

	_opened = true;
}



/***********************************************************
destructor
***********************************************************/
ConfigurationManager::~ConfigurationManager()
{
}


/***********************************************************
get singleton instance
***********************************************************/
ConfigurationManager *	ConfigurationManager::GetInstance()
{
	if(!_singletonInstance)
		_singletonInstance = new ConfigurationManager();

	return _singletonInstance;
}


/***********************************************************
SetSmallFontName
***********************************************************/
void ConfigurationManager::SetSmallFontName(const std::string & fontname)
{
	boost::mutex::scoped_lock lock(m_mutex);
	_smallfontname = fontname;
}

/***********************************************************
GetSmallFontName
***********************************************************/
std::string ConfigurationManager::GetSmallFontName()
{
	boost::mutex::scoped_lock lock(m_mutex);
	return _smallfontname;
}


/***********************************************************
save config file
***********************************************************/
void ConfigurationManager::SaveConfigFile()
{
	boost::mutex::scoped_lock lock(m_mutex);
	try
	{
		const boost::property_tree::xml_parser::xml_writer_settings<char> settings('	', 1);
		write_xml("LBANetGameConfig.xml", _pt, std::locale(), settings);
	}
	catch(...)
	{
	}
}