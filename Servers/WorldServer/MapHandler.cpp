#include "MapHandler.h"
#include "SynchronizedTimeHandler.h"
#include "SharedDataHandler.h"

#define _THREAD_WAIT_TIME_	17

/***********************************************************
constructor
***********************************************************/
MapHandler::MapHandler(const MapInfo & mapinfo)
: _running(false), _mapinfo(mapinfo)
{
}

/***********************************************************
destructor
***********************************************************/
MapHandler::~MapHandler(void)
{
	StopThread();
}


/***********************************************************
start run function
***********************************************************/
void MapHandler::StartThread()
{
	// do nothing if already running
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	if(_running)
		return;

	_running = true;
	_threadcontrol = start();
}


/***********************************************************
stop run function
***********************************************************/
void MapHandler::StopThread()
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	_running = false;
	_monitor.notifyAll();
	_threadcontrol.join();
}


/***********************************************************
running function of the thread
***********************************************************/
void MapHandler::run()
{
	// init time
	double waittime = SynchronizedTimeHandler::GetCurrentTimeDouble();

	while(true)
	{
		// stop thread if running is false
		{
			IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
			if(!_running)
				return;
		}


		// process events
		std::map<Ice::Long, EventsSeq> evts;
		SharedDataHandler::getInstance()->GetEvents(_mapinfo.Name, evts);
		ProcessEvents(evts);


		// wait for a few milliseconds
		{
			double currwtime = SynchronizedTimeHandler::GetCurrentTimeDouble();
			double wdiff = (currwtime-waittime);
			long timelong = (long)(wdiff);

			if(timelong < _THREAD_WAIT_TIME_)
			{
				IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
				IceUtil::Time t = IceUtil::Time::milliSeconds(_THREAD_WAIT_TIME_-timelong);
				_monitor.timedWait(t);
			}

			// mesure the time used to do one cycle
			waittime = SynchronizedTimeHandler::GetCurrentTimeDouble();
		}
	}
}



/***********************************************************
process events
***********************************************************/
void MapHandler::ProcessEvents(const std::map<Ice::Long, EventsSeq> & evts)
{

}