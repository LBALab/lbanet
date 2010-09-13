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


#if !defined(__LbaNetModel_1_RemoteConnectionHandler_h)
#define __LbaNetModel_1_RemoteConnectionHandler_h

#include <Ice/Application.h>
#include <Glacier2/Router.h>
#include <ClientSession.h>
#include <boost/shared_ptr.hpp>
#include <IceUtil/Thread.h>


#include "ConnectionHandlerBase.h"

class ChatServerHandler;

/***********************************************************************
 * Module:  ServerConnectionHandler.h
 * Author:  vivien
 * Purpose: Class used to take care of ice connection to the server
 ***********************************************************************/

class RemoteConnectionHandler : public ConnectionHandlerBase, public IceUtil::Thread
{
public:
	//! constructor
	RemoteConnectionHandler(Ice::CommunicatorPtr communicator,
								boost::shared_ptr<ChatServerHandler> chatH);

	//! destructor
	virtual ~RemoteConnectionHandler();

	//! connect to the server
	virtual int Connect(const std::string &user, const std::string &password, std::string & reason);

	//! disconnect from the server
	virtual void Disconnect();

	//! query the serrver to see if it is on
	static bool IsServerOn(Ice::CommunicatorPtr communicator);

	// running function of the thread
	virtual void run();

private:
	// threading and mutex stuff
	IceUtil::Monitor<IceUtil::Mutex>						_monitor;
	bool													_running;
	IceUtil::ThreadControl									_threadcontrol;

	// pointer to the ice communicator
	Ice::CommunicatorPtr									_communicator;

	Glacier2::RouterPrx										_router;
	LbaNet::ClientSessionPrx								_session;
	Ice::ObjectAdapterPtr									_adapter;

	LbaNet::ClientInterfacePrx								_interface;

	boost::shared_ptr<ChatServerHandler>					_chatH;
};

#endif