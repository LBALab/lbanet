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


#include "WorldServerInterfaceServant.h"
#include "SharedDataHandler.h"
#include "LogHandler.h"


/***********************************************************
client send events to server
***********************************************************/
void WorldServerInterfaceServant::ClientEvents(Ice::Long clientid, const EventsSeq &evts, const Ice::Current&)
{
	SharedDataHandler::getInstance()->ClientEvents(clientid, evts);
}

/***********************************************************
used when a client connect to a world
***********************************************************/
void WorldServerInterfaceServant::RegisterClient(Ice::Long clientid, const ClientInterfacePrx &proxy, 
													const LbaNet::ObjectExtraInfo& extrainfo,
													const Ice::Current&)
{
	try
	{
		SharedDataHandler::getInstance()->RegisterClient(clientid, extrainfo, proxy);
	}
	catch(std::exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Problem registering the client: ") + ex.what(), 0);	
	}
}


/***********************************************************
used when a client disconnect from a world
***********************************************************/
 void WorldServerInterfaceServant::UnregisterClient(Ice::Long clientid, const Ice::Current&)
{
	SharedDataHandler::getInstance()->UnregisterClient(clientid);
}

 
/***********************************************************
used when a client update name info
***********************************************************/	
void WorldServerInterfaceServant::UpdateClientInfo(Ice::Long clientid, 
												   const LbaNet::ObjectExtraInfo& extrainfo, 
													const Ice::Current&)
{
	SharedDataHandler::getInstance()->UpdateClientExtraInfo(clientid, extrainfo);
}


