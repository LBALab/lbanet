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


namespace libconfig
{
	class Config;
}

#include <string>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>

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
	bool GetBool(const std::string & path, bool &res);
	bool GetInt(const std::string & path, int &res);
	bool GetLong(const std::string & path, long &res);
	bool GetFloat(const std::string & path, float &res);
	bool GetDouble(const std::string & path, double &res);
	bool GetString(const std::string & path, std::string &res);

	// set functions
	bool SetBool(const std::string & path, const bool &res);
	bool SetInt(const std::string & path, const int &res);
	bool SetLong(const std::string & path, const long &res);
	bool SetFloat(const std::string & path, const float &res);
	bool SetDouble(const std::string & path, const double &res);
	bool SetString(const std::string & path, const std::string &res);


protected:
	// constructor
	ConfigurationManager();

private:

	static ConfigurationManager *	_singletonInstance;
	libconfig::Config *				_configH;
	bool							_opened;

	boost::mutex					m_mutex;
};


#endif
