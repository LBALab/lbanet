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


#ifndef _CLIENT_SESSION_MANAGER_SERVANT_H
#define _CLIENT_SESSION_MANAGER_SERVANT_H

#include <Ice/Ice.h>
#include <Glacier2/Session.h>
#include <RoomManager.h>
#include <ConnectedTracker.h>


class ClientSessionManagerServant : public Glacier2::SessionManager
{
public:

    ClientSessionManagerServant(const Ice::CommunicatorPtr& communicator);
    ~ClientSessionManagerServant();

    virtual Glacier2::SessionPrx create(const std::string & userId,const Glacier2::SessionControlPrx &,
											const Ice::Current &current);

private:
	LbaNet::RoomManagerPrx			_manager;
	LbaNet::ConnectedTrackerPrx		_ctracker;

	std::string						_version;
};

#endif
