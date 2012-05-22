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


#ifndef _LBANET_CONFIGURATION_MANAGER_H_
#define _LBANET_CONFIGURATION_MANAGER_H_


#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/property_tree/ptree.hpp>

#include <string>


//*************************************************************************************************
//*                               class ConfigurationManager
//*************************************************************************************************
/**
* @brief Class handling configuration file
*
*/
class ConfigurationManager
{
public:
	// destructor
	~ConfigurationManager();

	// get singleton instance
	static ConfigurationManager *	GetInstance();

	// get functions
	template <typename T>
	T GetValue(const std::string & path, const T &defaultV);

	// set functions
	template <typename T>
	void SetValue(const std::string & path, const T &V);


	void SetSmallFontName(const std::string & fontname);
	std::string GetSmallFontName();

	// save config file
	void SaveConfigFile();

protected:
	// constructor
	ConfigurationManager();

private:

	static ConfigurationManager *	_singletonInstance;

	bool							_opened;
	boost::property_tree::ptree		_pt;

	std::string						_smallfontname;

	boost::mutex					m_mutex;
};


template <typename T>
T ConfigurationManager::GetValue(const std::string & path, const T &defaultV)
{
	boost::mutex::scoped_lock lock(m_mutex);
	return _pt.get<T>(path, defaultV);
}

// set functions
template <typename T>
void ConfigurationManager::SetValue(const std::string & path, const T &V)
{
	boost::mutex::scoped_lock lock(m_mutex);
	_pt.put(path, V);
}


#endif
