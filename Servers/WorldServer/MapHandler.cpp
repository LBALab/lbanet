#include "MapHandler.h"
#include "SynchronizedTimeHandler.h"
#include "SharedDataHandler.h"

#define _THREAD_WAIT_TIME_	17

/***********************************************************
constructor
***********************************************************/
MapHandler::MapHandler(const MapInfo & mapinfo)
: _Trunning(false), _mapinfo(mapinfo)
{
}

/***********************************************************
destructor
***********************************************************/
MapHandler::~MapHandler(void)
{
	{
		IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
		_Trunning = false;
		_monitor.notifyAll();
	}

	if(_thread)
	{
		_threadcontrol.join();
		_thread = NULL;
	}
}


/***********************************************************
start run function
***********************************************************/
void MapHandler::StartThread()
{
	// do nothing if already running
	{
		IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
		if(_Trunning)
			return;
	}

	// clean old thread if needed
	if(_thread)
	{
		_threadcontrol.join();
		_thread = NULL;
	}


	// create thread
	_thread = new RunThread(this);
	_threadcontrol = _thread->start();
}



/***********************************************************
running function of the thread
***********************************************************/
void MapHandler::run()
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	_Trunning = true;

	// init time
	double waittime = SynchronizedTimeHandler::GetCurrentTimeDouble();

	// stop thread if running is false
	while(_Trunning)
	{
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