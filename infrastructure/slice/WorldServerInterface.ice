#ifndef WORLD_SERVER_ICE
#define WORLD_SERVER_ICE

#include <ClientInterface.ice>

module LbaNet
{
	interface WorldServerInterface
	{
	 	//client send events to server
	 	void ClientEvents(long clientid, EventsSeq evts);
	 	
	 	// used when a client connect to a world
	 	void RegisterClient(long clientid, ClientInterface * proxy, ObjectExtraInfo extrainfo);
	 	
	 	// used when a client disconnect from a world
		 void UnregisterClient(long clientid); 
	 	
	 	// used when a client update name info
	 	void UpdateClientInfo(long clientid, ObjectExtraInfo extrainfo);		 
		 
	};

};

#endif

