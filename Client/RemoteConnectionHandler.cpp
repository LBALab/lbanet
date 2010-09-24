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
#include "InfosReceiverServant.h"
#include "ChatServerHandler.h"
#include "EventsQueue.h"

#define _REMOTE_THREAD_WAIT_TIME_	10


/***********************************************************
	Constructor
***********************************************************/
RemoteConnectionHandler::RemoteConnectionHandler(Ice::CommunicatorPtr communicator,
													boost::shared_ptr<ChatServerHandler> chatH)
: _communicator(communicator), _adapter(NULL), _session(NULL), 
	_router(NULL), _chatH(chatH), _Trunning(false)
{

}



/***********************************************************
	Destructor
***********************************************************/
RemoteConnectionHandler::~RemoteConnectionHandler()
{
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


	// clean up
	try
	{
		if(_adapter)
		{
			_adapter->deactivate();
			_adapter->destroy();
		}
	}
	catch(const Ice::Exception& ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Error destroying the adapter: ") + ex.what());
	}

	_session = NULL;
	_router = NULL;
	_adapter = NULL;
	_interface = NULL;
}




/***********************************************************
connect to the server
***********************************************************/
int RemoteConnectionHandler::Connect(const std::string &user, const std::string &password, 
										std::string & reason)
{
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

	try
	{
		std::string verS = _session->GetVersion();
		Ice::PropertiesPtr prop = _communicator->getProperties();
		std::string serverV = prop->getPropertyWithDefault("LbanetServerVersion", "v0");
		if(verS != serverV)
		{
			reason = "Server version mismatch - please update your game.";
			Disconnect();
			return -1;
		}
	}
	catch(const Ice::Exception& ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Error getting server version: ") + ex.what());
		return 0;
	}


	try
	{
		_adapter = _communicator->createObjectAdapter("LbaNetClient");
		_adapter->activate();

	}
	catch(const Ice::Exception& ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Error creating adapter: ") + ex.what());
		return 0;
	}


	//connect chat
	if(_chatH)
		_chatH->Initialize(user, _adapter, _session, _router->getServerProxy()->ice_getIdentity().category);


	try
	{
		//if connected then set up an interface and give it to the server
		Ice::Identity id;
		id.name = "ClientInterface";
		id.category = _router->getServerProxy()->ice_getIdentity().category;
		_interface = LbaNet::ClientInterfacePrx::uncheckedCast(
												_adapter->add(new InfosReceiverServant(), id)->ice_oneway());


		_session->SetClientInterface(_interface);
	}
    catch(const IceUtil::Exception& ex)
    {
		LogHandler::getInstance()->LogToFile(std::string("Exception creating client inerface: ") + ex.what());
    }
    catch(...)
    {
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception creating client inerface. "));
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
	//disconnect chat
	if(_chatH)
	{
		_chatH->Disconnect();
		_chatH = boost::shared_ptr<ChatServerHandler>();
	}

	// stop thread
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	_Trunning = false;
	_monitor.notifyAll();
}



/***********************************************************
check if server is reachable
***********************************************************/
bool RemoteConnectionHandler::IsServerOn(Ice::CommunicatorPtr communicator)
{
	LogHandler::getInstance()->LogToFile("Trying to connect to glacier");
	Ice::RouterPrx defaultRouter = communicator->getDefaultRouter();
	if(defaultRouter)
	{
		try
		{
			// timeout after 2 seconds if the serve does not respond
			Glacier2::RouterPrx::checkedCast(defaultRouter->ice_timeout(2000));
		}
		catch(const IceUtil::Exception& ex)
		{
			LogHandler::getInstance()->LogToFile(std::string("Connection to server failed") + ex.what());
			return false;
		}
		catch(...)
		{
			LogHandler::getInstance()->LogToFile("Connection to server failed");
			return false;
		}

		return true;
		LogHandler::getInstance()->LogToFile("Connection to server ok");
	}


	return false;
}

/***********************************************************
ask server to change world
***********************************************************/
void RemoteConnectionHandler::ChangeWorld(const std::string & NewWorld)
{
	try
	{
		if(_session)
			_session->ChangeWorld(NewWorld);
	}
    catch(const IceUtil::Exception& ex)
    {
		LogHandler::getInstance()->LogToFile(std::string("Exception on ChangeWorld: ") + ex.what());
    }
    catch(...)
    {
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception on ChangeWorld"));
    }
}


/***********************************************************
get the list of world to connect to
***********************************************************/
void RemoteConnectionHandler::RefreshWorldList()
{
	try
	{
		if(_session)
			_session->GetWorldList();
	}
    catch(const IceUtil::Exception& ex)
    {
		LogHandler::getInstance()->LogToFile(std::string("Exception on RefreshWorldList: ") + ex.what());
    }
    catch(...)
    {
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception on RefreshWorldList"));
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
		// TODO - turn afk after a while with no events
		// process events
		try
		{
			LbaNet::EventsSeq events;
			EventsQueue::getSenderQueue()->GetEvents(events);
			_session->ClientEvents(events);
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
