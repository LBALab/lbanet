#ifndef CLIENT_INTERFACE
#define CLIENT_INTERFACE


#include <ClientServerEvents.ice>

module LbaNet
{
	interface ClientInterface
	{
	 	//server send events to client
	 	void ServerEvents(EventsSeq evts);
	};	
};

#endif

