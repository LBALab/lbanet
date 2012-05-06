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

#include "RemoteConnectionHandler.h"
#include "LogHandler.h"

#define _REMOTE_THREAD_WAIT_TIME_	100


/***********************************************************
	Constructor
***********************************************************/
RemoteConnectionHandler::RemoteConnectionHandler(ServerMaintenanceTool & gui)
: _session(NULL), _router(NULL), _Trunning(false), _gui(gui)
{

}



/***********************************************************
	Destructor
***********************************************************/
RemoteConnectionHandler::~RemoteConnectionHandler()
{
	reset();
}



/***********************************************************
connect to the server
***********************************************************/
void RemoteConnectionHandler::reset()
{
	Disconnect();

	// first make sure that the thread is finished
	JoinThread();

	try
	{
		if(_router)
			_router->destroySession();
	}
	catch(const Ice::Exception& ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Error destroying the session: ") + ex.what());
	}


	_session = NULL;
	_router = NULL;
}


/***********************************************************
connect to the server
***********************************************************/
int RemoteConnectionHandler::Connect(Ice::CommunicatorPtr communicator, 
									 const std::string &user, const std::string &password, 
										std::string & reason)
{
	_communicator = communicator;
	Ice::RouterPrx defaultRouter = _communicator->getDefaultRouter();
	if(!defaultRouter)
	{
		LogHandler::getInstance()->LogToFile(std::string("Can not connect: no default router set"));
		return 0;
	}

	try
	{
		_router = Glacier2::RouterPrx::checkedCast(defaultRouter);
	}
	catch(const IceUtil::Exception& ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception connecting to the server: ") + ex.what());
		return 0;
	}
	catch(...)
	{
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception connecting to the server. "));
		return 0;
	}

	if(!_router)
	{
		LogHandler::getInstance()->LogToFile(std::string("Can not connect:  configured router is not a Glacier2 router"));
		return 0;
	}



	try
	{
		_session = LbaNet::ClientSessionPrx::uncheckedCast(_router->createSession(user, password));
	}
	catch(const Glacier2::PermissionDeniedException& ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Permission denied: ") + ex.what());
		LogHandler::getInstance()->InformUser("Permission denied.");
		reason = ex.reason;
		return -1;
	}
	catch(const Ice::Exception& ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Error getting glacier session: ") + ex.what());
		return 0;
	}

	// create thread
	StartThread();

	return 1;
}


/***********************************************************
disconnect from the server
***********************************************************/
void RemoteConnectionHandler::Disconnect()
{
	// stop thread
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	if(_Trunning)
	{
		_Trunning = false;
		_monitor.notifyAll();
	}
}


/***********************************************************
running function of the thread
***********************************************************/
void RemoteConnectionHandler::run()
{
	// start thread to send events to server
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	_Trunning = true;
	
	// stop thread if running is false
	while(_Trunning)
	{
		// process events
		try
		{
			bool status = _session->GetWorldStatus(_worldname);
			_gui.SetServerStatus(status?"ONLINE":"OFFLINE");
		}
		catch(const IceUtil::Exception& ex)
		{
			LogHandler::getInstance()->LogToFile(std::string("Exception sending client events: ") + ex.what());
		}
		catch(...)
		{
			LogHandler::getInstance()->LogToFile(std::string("Unknown exception sending client events. "));
		}


		// wait for a few milliseconds
		IceUtil::Time t = IceUtil::Time::milliSeconds(_REMOTE_THREAD_WAIT_TIME_);
		_monitor.timedWait(t);
	}
}	

/***********************************************************
set world name
***********************************************************/
void RemoteConnectionHandler::setWorldName(const std::string & name)
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	_worldname = name;
}

/***********************************************************
UpdateWorld
***********************************************************/
std::string RemoteConnectionHandler::UpdateWorld(const std::string & name)
{
	try
	{
		return _session->UpdateWorld(name);
	}
	catch(const IceUtil::Exception& ex)
	{
		return std::string("Exception when contacting server: ") + ex.what();
	}
	catch(...)
	{
		return "Unknown exception when contacting server";
	}
}

/***********************************************************
StartWorld
***********************************************************/
std::string RemoteConnectionHandler::StartWorld(const std::string & name)
{
	try
	{
		return _session->StartWorld(name);
	}
	catch(const IceUtil::Exception& ex)
	{
		return std::string("Exception when contacting server: ") + ex.what();
	}
	catch(...)
	{
		return "Unknown exception when contacting server";
	}
}

/***********************************************************
StopWorld
***********************************************************/
std::string RemoteConnectionHandler::StopWorld(const std::string & name)
{
	try
	{
		return _session->ShutdownWorld(name);
	}
	catch(const IceUtil::Exception& ex)
	{
		return std::string("Exception when contacting server: ") + ex.what();
	}
	catch(...)
	{
		return "Unknown exception when contacting server";
	}
}