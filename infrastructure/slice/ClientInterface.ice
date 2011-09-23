#ifndef CLIENT_INTERFACE
#define CLIENT_INTERFACE


#include <ClientServerEvents.ice>

[["java:package:net.lbanet.generated"]]
module LbaNet
{
	interface ClientInterface
	{
	 	//server send events to client
	 	void ServerEvents(EventsSeq evts);
	};	
};

#endif

