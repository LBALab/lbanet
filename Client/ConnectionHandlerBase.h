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


#if !defined(__LbaNetModel_1_ConnectionHandlerBase_h)
#define __LbaNetModel_1_ConnectionHandlerBase_h


#include <string>

/***********************************************************************
 * Module:  ConnectionHandlerBase.h
 * Author:  vivien
 * Purpose: Base class to hanlde connection with server
 ***********************************************************************/

class ConnectionHandlerBase
{
public:
	//! constructor
	ConnectionHandlerBase(){}

   //! destructor
	virtual ~ConnectionHandlerBase(){}

   //! connect to the server
   //! return 1 in case of success
	//! else set the string reason
   virtual int Connect(const std::string &user, const std::string &password, std::string & reason) = 0;

	//! disconnect from the server
	virtual void Disconnect() = 0;

};

#endif