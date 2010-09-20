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

#ifndef _MAP_HANDLER_H__
#define _MAP_HANDLER_H__


#include <ClientInterface.h>
#include <IceUtil/Mutex.h>

#include "RunnableThread.h"


using namespace LbaNet;


//! used to send event to 1 client
class EventsSender : public IceUtil::Thread
{
public:
	//! constructor
	EventsSender(EventsSeq & events, ClientInterfacePrx proxy);

	// running function of the thread
	virtual void run();

private:
	EventsSeq				_events;
	ClientInterfacePrx		_proxy;
};


//! used to send event to all clients
class EventsSenderToAll : public IceUtil::Thread
{
public:
	//! constructor
	EventsSenderToAll(EventsSeq & events, std::map<Ice::Long, ClientInterfacePrx> &proxies);

	// running function of the thread
	virtual void run();

private:
	EventsSeq									_events;
	std::map<Ice::Long, ClientInterfacePrx>		_proxies;
};





//! take care of a map of the world
class MapHandler : public Runnable
{
public:
	//! constructor
	MapHandler(const MapInfo & mapinfo);

	//! desructor
	~MapHandler(void);

	//! start run function
	void StartThread();

	// running function of the thread
	virtual void run();



	//! add events
	void AddEvents(Ice::Long clientid, const EventsSeq &evts);

	//! add 1 event
	void AddEvent(Ice::Long clientid, ClientServerEventBasePtr evt);

	// get all events for a specific map
	void GetEvents(std::map<Ice::Long, EventsSeq> & evts);

	// add player proxy
	void AddProxy(Ice::Long clientid, ClientInterfacePrx proxy);

	// remove player proxy
	void RemoveProxy(Ice::Long clientid);

	// get player proxy
	ClientInterfacePrx GetProxy(Ice::Long clientid);

	// get players proxies
	std::map<Ice::Long, ClientInterfacePrx> GetProxies();


protected:
	// process events
	void ProcessEvents(const std::map<Ice::Long, EventsSeq> & evts, 
						EventsSeq &tosendevts);

	// player entered map
	void PlayerEntered(Ice::Long id, EventsSeq &tosendevts);

	// player left map
	void PlayerLeft(Ice::Long id, EventsSeq &tosendevts);


private:
	// threading and mutex stuff
	IceUtil::Monitor<IceUtil::Mutex>						_monitor;
	IceUtil::Mutex											_mutex_events;
	IceUtil::Mutex											_mutex_proxies;

	bool													_Trunning;
	IceUtil::ThreadControl									_threadcontrol;
	IceUtil::ThreadPtr										_thread;

	MapInfo													_mapinfo;


	 std::map<Ice::Long, ClientInterfacePrx>				_playerproxies;
	 std::map<Ice::Long, EventsSeq>							_events;
};


#endif