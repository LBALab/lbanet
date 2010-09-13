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


#if !defined(__LbaNetModel_EventsQueue_h)
#define __LbaNetModel_EventsQueue_h

#include <ClientServerEvents.h>


/***********************************************************************
 * Module:  EventsQueue.h
 * Author:  Vivien
 * Purpose: Used to store a queue of events
 ***********************************************************************/
class EventsQueue
{
public:

	// singleton pattern
	static EventsQueue * getSenderQueue();
	static EventsQueue * getReceiverQueue();

	// same for server
	static EventsQueue * getServerSenderQueue();
	static EventsQueue * getServerReceiverQueue();


	//! destructor
	~EventsQueue(void);

	//! add event to queue
	void AddEvent(LbaNet::ClientServerEventBasePtr evt);

	//! get all events and clear the queue
	void GetEvents(LbaNet::EventsSeq & events);

protected:
	//! constructor
	EventsQueue(void);

	EventsQueue(const EventsQueue &);
	const EventsQueue & operator=(const EventsQueue &);

private:
	static EventsQueue *	_senderInstance;
	static EventsQueue *	_receiverInstance;

	IceUtil::Mutex			_mutex;

	LbaNet::EventsSeq		_currevents;
};

#endif
