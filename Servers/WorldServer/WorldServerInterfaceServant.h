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


#ifndef _WORLDSERVER_INTERFACE_SERVANT_H
#define _WORLDSERVER_INTERFACE_SERVANT_H

#include <WorldServerInterface.h>


#include <string>

using namespace LbaNet;

class WorldServerInterfaceServant : public WorldServerInterface
{
public:
	//! constructor
	WorldServerInterfaceServant(){}

	//! destructor
	~WorldServerInterfaceServant(){}


 	//client send events to server
 	void ClientEvents(Ice::Long clientid, const EventsSeq &evts, const Ice::Current&);
 	
 	// used when a client connect to a world
	void RegisterClient(Ice::Long clientid, const std::string &clientname, 
						const ClientInterfacePrx &proxy, const Ice::Current&);
 	
 	// used when a client disconnect from a world
	 void UnregisterClient(Ice::Long clientid, const Ice::Current&); 	

};

#endif
