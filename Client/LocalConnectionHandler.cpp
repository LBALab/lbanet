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
#include "SharedDataHandler.h"
#include "LocalDatabaseHandler.h"


#define _LOCAL_THREAD_WAIT_TIME_	10

/***********************************************************
	Constructor
***********************************************************/
LocalConnectionHandler::LocalConnectionHandler()
: _interface(NULL)
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
	_interface = NULL;
}




/***********************************************************
connect to the server
***********************************************************/
int LocalConnectionHandler::Connect(const std::string &user, const std::string &password, 
										std::string & reason)
{
	_username = user;

	_interface = new InfosReceiverServant();


	// create thread
	StartThread();

	// set client id to 1
	EventsQueue::getReceiverQueue()->AddEvent(
		new LbaNet::ClientIdEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 1));


	// register local database
	boost::shared_ptr<DatabaseHandlerBase> dbhandler = 
		boost::shared_ptr<DatabaseHandlerBase>(new LocalDatabaseHandler("lbanet.sav"));
	SharedDataHandler::getInstance()->SetDbManager(dbhandler);

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

	SharedDataHandler::getInstance()->UnregisterClient(1);
	SharedDataHandler::getInstance()->CleanUp();
}


/***********************************************************
ask server to change world
***********************************************************/
void LocalConnectionHandler::ChangeWorld(const std::string & NewWorld)
{
	// clean up old world
	SharedDataHandler::getInstance()->UnregisterClient(1);
	SharedDataHandler::getInstance()->CleanUp();

	// register new world information
	LbaNet::WorldInformation worldinfo;
	DataLoader::getInstance()->GetWorldInformation(NewWorld, worldinfo);
	SharedDataHandler::getInstance()->SetWorldDefaultInformation(worldinfo);

	// register local database
	boost::shared_ptr<DatabaseHandlerBase> dbhandler = 
		boost::shared_ptr<DatabaseHandlerBase>(new LocalDatabaseHandler("lbanet.sav"));
	SharedDataHandler::getInstance()->SetDbManager(dbhandler);

	// register player
	LbaNet::ObjectExtraInfo extrainfos;
	extrainfos.Name = _username;
	extrainfos.NameColorR = 1;
	extrainfos.NameColorG = 1;
	extrainfos.NameColorB = 1;
	SharedDataHandler::getInstance()->RegisterClient(1, extrainfos, _interface);
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
			SharedDataHandler::getInstance()->ClientEvents(1, events);
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
