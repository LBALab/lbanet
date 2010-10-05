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


#if !defined(__LbaNetModel_1_LocalConnectionHandler_h)
#define __LbaNetModel_1_LocalConnectionHandler_h

#include "ConnectionHandlerBase.h"
#include <IceUtil/Monitor.h>
#include <Ice/Application.h>
#include <ClientInterface.h>

class DatabaseHandlerBase;

/***********************************************************************
 * Module:  LocalConnectionHandler.h
 * Author:  vivien
 * Purpose: Class used to take care of ice connection to the server
 ***********************************************************************/

class LocalConnectionHandler : public ConnectionHandlerBase
{
public:
	//! constructor
	LocalConnectionHandler();

	//! destructor
	virtual ~LocalConnectionHandler();

	//! connect to the server
	virtual int Connect(const std::string &user, const std::string &password, std::string & reason);

	//! disconnect from the server
	virtual void Disconnect();

	//! ask server to change world
	virtual void ChangeWorld(const std::string & NewWorld);

	// running function of the thread
	virtual void run();

	//! get the list of world to connect to
	virtual void RefreshWorldList();

private:
	std::string												_username;

	// threading and mutex stuff
	IceUtil::Monitor<IceUtil::Mutex>						_monitor;
	bool													_Trunning;

	LbaNet::ClientInterfacePtr								_interface;
};

#endif