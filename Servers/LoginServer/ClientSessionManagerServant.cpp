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


#include "ClientSessionManagerServant.h"
#include "SessionServant.h"

#include <IceUtil/UUID.h>


ClientSessionManagerServant::ClientSessionManagerServant(const Ice::CommunicatorPtr& communicator)
{
	try
	{
		_version = communicator->getProperties()->getProperty("LbanetVersion");

		_manager = RoomManagerPrx::checkedCast(communicator->stringToProxy(
												communicator->getProperties()->getProperty("RoomManager")));
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception getting room manager proxy: "<<ex.what()<<std::endl;
	}
	catch(...)
	{
		std::cout<<"Unknown exception getting room manager. "<<std::endl;
	}

	try
	{
		_ctracker = ConnectedTrackerPrx::checkedCast(communicator->stringToProxy(
														communicator->getProperties()->getProperty("ConnectedTracker")));
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception getting room manager proxy: "<<ex.what()<<std::endl;
	}
	catch(...)
	{
		std::cout<<"Unknown exception getting room manager. "<<std::endl;
	}
}

ClientSessionManagerServant::~ClientSessionManagerServant()
{

}

Glacier2::SessionPrx ClientSessionManagerServant::create(	const std::string & userId,
															const Glacier2::SessionControlPrx &,
															const Ice::Current &current)
{
	Ice::Identity id;
    id.category = "_" + userId;
    id.name = IceUtil::generateUUID();

	SessionServant * sservant = new SessionServant(userId, _manager, _ctracker, _version);
	Ice::ObjectPrx prx = current.adapter->add(sservant, id);
    return Glacier2::SessionPrx::uncheckedCast(prx);
}
