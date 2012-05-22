
file(
	GLOB
	infrastructure_INCLUDES
	include/*.h
)

SET(infrastructure_SOURCES cpp/ChatInfo.cpp
			cpp/ClientInterface.cpp
			cpp/ClientServerEvents.cpp
			cpp/ClientSession.cpp
			cpp/ConnectedTracker.cpp
			cpp/LbaTypes.cpp
			cpp/MaintenanceInterface.cpp
			cpp/PollingChat.cpp
			cpp/RoomManager.cpp
			cpp/WorldRegistration.cpp
			cpp/WorldServerInterface.cpp)

		
add_library(LBANetInfrastructure STATIC ${infrastructure_INCLUDES} ${infrastructure_SOURCES})
