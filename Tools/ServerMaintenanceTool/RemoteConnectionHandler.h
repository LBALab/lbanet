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

#include "servermaintenancetool.h"

#include <Ice/Application.h>
#include <Glacier2/Router.h>
#include <ClientSession.h>


#include <IceUtil/Thread.h>



class Runnable
{	
public:
	//! constructor
	Runnable(){}
	
	//! destructor
	virtual ~Runnable(){}

	virtual void run() = 0;	
};


class RunThread : public IceUtil::Thread
{
public:

	// constructor
	RunThread(Runnable * runnable)
		: _runnable(runnable)
	{
	}

	// running function of the thread
	virtual void run()
	{
		_runnable->run();
	}

private:
	Runnable * _runnable;
};

/***********************************************************************
 * Module:  RemoteConnectionHandler.h
 * Author:  vivien
 * Purpose: Class used to take care of ice connection to the server
 ***********************************************************************/

class RemoteConnectionHandler : public Runnable
{
public:
	//! constructor
	RemoteConnectionHandler(ServerMaintenanceTool & gui);

	//! destructor
	virtual ~RemoteConnectionHandler();

	//! connect to the server
	virtual int Connect(Ice::CommunicatorPtr communicator, const std::string &user, 
						const std::string &password, std::string & reason);

	//! disconnect from the server
	virtual void Disconnect();

	// running function of the thread
	virtual void run();

	// set world name
	void setWorldName(const std::string & name);

	// reset connection
	void reset();

	std::string UpdateWorld(const std::string & name);
	std::string StartWorld(const std::string & name);
	std::string StopWorld(const std::string & name);

	//! start running the thread
	void StartThread()
	{
		_thread = new RunThread(this);
		_threadcontrol = _thread->start();
	}

	//! join started thread
	void JoinThread()
	{
		if(_thread)
		{
			_threadcontrol.join();
			_thread = NULL;
		}
	}

private:
	// threading stuff
	IceUtil::ThreadControl									_threadcontrol;		
	IceUtil::ThreadPtr										_thread;


	// threading and mutex stuff
	IceUtil::Monitor<IceUtil::Mutex>						_monitor;
	bool													_Trunning;

	// pointer to the ice communicator
	Ice::CommunicatorPtr									_communicator;

	Glacier2::RouterPrx										_router;
	LbaNet::ClientSessionPrx								_session;


	std::string												_worldname;

	ServerMaintenanceTool &									_gui;
};

#endif