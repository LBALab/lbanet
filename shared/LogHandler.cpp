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

#include "LogHandler.h"
#include <IceUtil/StaticMutex.h>
#include <IceUtil/IceUtil.h>

LogHandler* LogHandler::_singletonInstance = NULL;
static IceUtil::StaticMutex myStaticMutex = ICE_STATIC_MUTEX_INITIALIZER;


/***********************************************************
singleton pattern
***********************************************************/
LogHandler * LogHandler::getInstance()
{
    if(!_singletonInstance)
    {
        _singletonInstance = new LogHandler();
		return _singletonInstance;
    }
    else
    {
		return _singletonInstance;
    }
}


/***********************************************************
Constructor
***********************************************************/
LogHandler::LogHandler()
{
	_filename = "LBAClient.log";
	_guifilename = "CEGUI.log";

	_logfile.open(_filename.c_str());

	_logfile<<std::endl<<std::endl<<"**********************************"<<std::endl;
	_logfile<<IceUtil::Time::now().toDateTime()<<" - Starting new game."<<std::endl;
}


/***********************************************************
Destructor
***********************************************************/
LogHandler::~LogHandler()
{

}


/***********************************************************
close opened log file
***********************************************************/
void LogHandler::CloseFile()
{
	if(_logfile.is_open())
	{
		_logfile.flush();
		_logfile.close();
	}
}


/***********************************************************
log a text into file
***********************************************************/
void LogHandler::LogToFile(const std::string &text, int category)
{
	IceUtil::StaticMutex::Lock lock(myStaticMutex);
	if(_logfile.is_open())
		_logfile<<IceUtil::Time::now().toDateTime()<<","<<category<<","<<text<<std::endl;
}



/***********************************************************
inform the use of something
***********************************************************/
void LogHandler::InformUser(const std::string &text)
{
	IceUtil::StaticMutex::Lock lock(myStaticMutex);
	std::cout<<text<<std::endl;
}




