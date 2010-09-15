#ifndef MAINTENANCE_INTERFACE_ICE
#define MAINTENANCE_INTERFACE_ICE

module LbaNet
{
	interface MaintenanceInterface
	{
	 	//tell the server to shutdown
	 	void Shutdown(); 	
	};

};

#endif

