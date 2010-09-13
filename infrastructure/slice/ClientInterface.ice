#ifndef LBANET_ACTOR_HANDLER
#define LBANET_ACTOR_HANDLER


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

