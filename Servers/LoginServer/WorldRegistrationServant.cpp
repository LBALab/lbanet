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

#include "WorldRegistrationServant.h"
#include "AvailableWorldsHandler.h"



/***********************************************************
register world
***********************************************************/
void WorldRegistrationServant::RegisterWorld(const WorldDesc& winfo, 
											 const LbaNet::WorldServerInterfacePrx& proxy,
											const LbaNet::MaintenanceInterfacePrx& mproxy, 
											const Ice::Current &current)
{
	AvailableWorldsHandler::getInstance()->AddWorld(winfo, proxy, mproxy);
}


/***********************************************************
unregister world
***********************************************************/
void WorldRegistrationServant::UnregisterWorld(const std::string& Worldname, const Ice::Current &current)
{
	AvailableWorldsHandler::getInstance()->RemoveWorld(Worldname);
}