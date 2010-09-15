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


#ifndef _MAINTENANCE_INTERFACE_SERVANT_H
#define _MAINTENANCE_INTERFACE_SERVANT_H

#include <MaintenanceInterface.h>

#include <Ice/Application.h>
#include <string>

#include "WorldChatHandler.h"

using namespace LbaNet;

class MaintenanceInterfaceServant : public MaintenanceInterface
{
public:
	//! constructor
	MaintenanceInterfaceServant(Ice::CommunicatorPtr communicator, const std::string & worldname,
									WorldChatHandler * wcH)
		: _communicator(communicator), _worldname(worldname), _wcH(wcH)
	{}

	//! destructor
	~MaintenanceInterfaceServant(){}


 	//tell the server to shutdown
 	void Shutdown(const Ice::Current&);
 	

private:
	Ice::CommunicatorPtr	_communicator;
	std::string				_worldname;
	WorldChatHandler *		_wcH;

};

#endif
