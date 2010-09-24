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

#include "LocalConnectionHandler.h"
#include "LogHandler.h"
#include "EventsQueue.h"
#include "DataLoader.h"
#include "SynchronizedTimeHandler.h"
#include "EventsQueue.h"
#include "InfosReceiverServant.h"


#define _LOCAL_THREAD_WAIT_TIME_	10

/***********************************************************
	Constructor
***********************************************************/
LocalConnectionHandler::LocalConnectionHandler(Ice::CommunicatorPtr communicator)
: _communicator(communicator), _adapter(NULL), _interface(NULL)
{

}



/***********************************************************
	Destructor
***********************************************************/
LocalConnectionHandler::~LocalConnectionHandler()
{
	// first make sure that the thread is finished
	JoinThread();


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

	_adapter = NULL;
	_interface = NULL;
}




/***********************************************************
connect to the server
***********************************************************/
int LocalConnectionHandler::Connect(const std::string &user, const std::string &password, 
										std::string & reason)
{
	_username = user;


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


	try
	{
		//if connected then set up an interface and give it to the server
		Ice::Identity id;
		id.name = "ClientInterface";
		_interface = LbaNet::ClientInterfacePrx::uncheckedCast(
												_adapter->add(new InfosReceiverServant(), id)->ice_oneway());
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

	// set client id to 1
	EventsQueue::getReceiverQueue()->AddEvent(
		new LbaNet::ClientIdEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 1));

	return 1;
}


/***********************************************************
disconnect from the server
***********************************************************/
void LocalConnectionHandler::Disconnect()
{
	// stop thread
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	_Trunning = false;
	_monitor.notifyAll();
}


/***********************************************************
ask server to change world
***********************************************************/
void LocalConnectionHandler::ChangeWorld(const std::string & NewWorld)
{
	//TODO 
}


/***********************************************************
running function of the thread
***********************************************************/
void LocalConnectionHandler::run()
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
			LbaNet::EventsSeq events;
			EventsQueue::getSenderQueue()->GetEvents(events);
			//TODO - send
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
		IceUtil::Time t = IceUtil::Time::milliSeconds(_LOCAL_THREAD_WAIT_TIME_);
		_monitor.timedWait(t);
	}
}



/***********************************************************
get the list of world to connect to
***********************************************************/
void LocalConnectionHandler::RefreshWorldList()
{
	std::vector<LbaNet::WorldDesc> worldlist;
	DataLoader::getInstance()->GetAvailableWorlds(worldlist);

	EventsQueue::getReceiverQueue()->AddEvent(
		new LbaNet::AvailableWorldsEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), worldlist));
}
