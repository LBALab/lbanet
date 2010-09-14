#ifndef WORLD_REGISTER_ICE
#define WORLD_REGISTER_ICE

#include <WorldServerInterface.ice>

module LbaNet
{
	interface WorldRegisterInterface
	{
		// world server register a world to login server
	 	void RegisterWorld(WorldDesc winfo, WorldServerInterface * proxy);
	 	
		// world server unregister a world to login server
		void UnregisterWorld(string Worldname);
 	
	};

};

#endif

