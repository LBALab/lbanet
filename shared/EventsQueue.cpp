#include "EventsQueue.h"

EventsQueue* EventsQueue::_senderInstance = NULL;
EventsQueue* EventsQueue::_receiverInstance = NULL;

/***********************************************************
constructor
***********************************************************/
EventsQueue::EventsQueue(void)
{
}

/***********************************************************
destructor
***********************************************************/
EventsQueue::~EventsQueue(void)
{
}


/***********************************************************
singleton pattern
***********************************************************/
EventsQueue * EventsQueue::getSenderQueue()
{
    if(!_senderInstance)
    {
        _senderInstance = new EventsQueue();
		return _senderInstance;
    }
    else
    {
		return _senderInstance;
    }
}


/***********************************************************
singleton pattern
***********************************************************/
EventsQueue * EventsQueue::getReceiverQueue()
{
    if(!_receiverInstance)
    {
        _receiverInstance = new EventsQueue();
		return _receiverInstance;
    }
    else
    {
		return _receiverInstance;
    }
}







/***********************************************************
add event to queue
***********************************************************/
void EventsQueue::AddEvent(LbaNet::ClientServerEventBasePtr evt)
{
	IceUtil::Mutex::Lock lock(_mutex);
	_currevents.push_back(evt);
}

/***********************************************************
get all events and clear the queue
***********************************************************/
void EventsQueue::GetEvents(LbaNet::EventsSeq & events)
{
	IceUtil::Mutex::Lock lock(_mutex);
	events.clear();
	_currevents.swap(events);
}