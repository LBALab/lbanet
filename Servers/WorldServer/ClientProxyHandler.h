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

#ifndef _CLIENT_PROXY_HANDLER_H__
#define _CLIENT_PROXY_HANDLER_H__

#include <ClientInterface.h>


//! base class taking care of client proxy
class ClientProxyBase : public IceUtil::Shared
{
public:
	//! constructor
	ClientProxyBase(){}

	//! destructor
	virtual ~ClientProxyBase(){}

	//server send events to client
	virtual void ServerEvents(const LbaNet::EventsSeq &evts) = 0;
};
typedef IceUtil::Handle<ClientProxyBase> ClientProxyBasePtr;

//! class taking care of remote client proxy
class RemoteClientProxy : public ClientProxyBase
{
public:
	//! constructor
	RemoteClientProxy(const LbaNet::ClientInterfacePrx &proxy)
		: _proxy(proxy)
	{}

	//! destructor
	virtual ~RemoteClientProxy(){}

	//server send events to client
	virtual void ServerEvents(const LbaNet::EventsSeq &evts)
	{
		_proxy->ServerEvents(evts);
	}


private:
	LbaNet::ClientInterfacePrx _proxy;
};



//! class taking care of local client proxy
class LocalClientProxy : public ClientProxyBase
{
public:
	//! constructor
	LocalClientProxy(const LbaNet::ClientInterfacePtr &proxy)
		: _proxy(proxy)
	{}

	//! destructor
	virtual ~LocalClientProxy(){}

	//server send events to client
	virtual void ServerEvents(const LbaNet::EventsSeq &evts)
	{
		_proxy->ServerEvents(evts);
	}


private:
	LbaNet::ClientInterfacePtr _proxy;
};

#endif