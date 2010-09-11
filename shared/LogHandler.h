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

#ifndef _LBA_NET_LOG_HANDLER_H_
#define _LBA_NET_LOG_HANDLER_H_

#include <string>
#include <fstream>

/***********************************
*	class taking care of the log
*************************************/
class LogHandler
{
public:
	// constructor
	LogHandler();

	// destructor
    ~LogHandler();

	// singleton pattern
   static LogHandler * getInstance();

	// log a text into file
   void LogToFile(const std::string text, int category = 0);


	// inform the use of something
   void InformUser(const std::string text);

   // get log file name
   const std::string &GetFilename()
   { return _filename; }

   const std::string &GetGUIFilename()
   { return _guifilename; }

	//! close opened log file
   void CloseFile();

private:
	std::ofstream			_logfile;
	std::string				_filename;
	std::string				_guifilename;

	// singleton
	static LogHandler *		_singletonInstance;
    static bool				_instanceFlag;

};


#endif
