#ifndef WORLD_REGISTER_ICE
#define WORLD_REGISTER_ICE

#include <WorldServerInterface.ice>
#include <MaintenanceInterface.ice>

[["java:package:net.lbanet.generated"]]
module LbaNet
{
	interface WorldRegisterInterface
	{
		// world server register a world to login server
	 	void RegisterWorld(WorldDesc winfo, WorldServerInterface * proxy, MaintenanceInterface * mproxy);
	 	
		// world server unregister a world to login server
		void UnregisterWorld(string Worldname);
 	
	};

};

#endif

