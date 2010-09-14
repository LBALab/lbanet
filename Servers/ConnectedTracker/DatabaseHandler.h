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


#if !defined(__Agent_database_handler_h)
#define __Agent_database_handler_h

#include <string>
#include <vector>
#include <map>

#include <IceUtil/Mutex.h>

#include <mysql++.h>


/***********************************************************************
 * Module:  DatabaseHandler.h
 * Author:  vivien
 * Modified: lundi 27 juillet 2009 14:59:17
 * Purpose: Declaration of the class SharedData
 ***********************************************************************/
class DatabaseHandler : public IceUtil::Mutex
{
public:
	//! default construtor
	DatabaseHandler(const std::string db, const std::string server,
						const std::string user, const std::string password);

	//! check login
	//! return -1 if login incorrect - else return the user id
	long CheckLogin(const std::string & PlayerName, const std::string & Password);


	//! set the user as disconnected in the database
	void DisconnectUser(long Id);

	//! reformat stored letters
	void ReformatLetters();

protected:
	DatabaseHandler(const DatabaseHandler &);
	const DatabaseHandler & operator=(const DatabaseHandler &);

	// connect to database
	void Connect();

	void Clear();

private:
	// mysql connection handler
	mysqlpp::Connection* _mysqlH;

	std::string			_db;
	std::string			_server;
	std::string			_user;
	std::string			_password;
};

#endif