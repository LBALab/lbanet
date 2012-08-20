
file(
	GLOB
	sharedlib_INCLUDES
	*.h
)


SET(sharedlib_SOURCES CatmulSplineHandler.cpp
			CharacterModes.cpp
			CharacterStates.cpp
			ClientScript.cpp
			CommonTypes.cpp
			DynamicObject.cpp
			Entities.cpp
			EventsQueue.cpp
			FileUtil.cpp
			HQRHandler.cpp
			HQRlib.cpp
			Lba1ModelMapHandler.cpp
			LogHandler.cpp
			NavMeshAgent.cpp
			NaviMeshHandler.cpp
			Randomizer.cpp
			ScriptEnvironmentBase.cpp
			ScriptedActor.cpp
			StaticObject.cpp
			StreamReader.cpp
			SynchronizedTimeHandler.cpp
			WorldToDisplayObjectSynchronizer.cpp
			XmlReader.cpp
			md5.cpp
			DataDirHandler.cpp)
		
add_library(LBANetShared STATIC ${sharedlib_INCLUDES} ${sharedlib_SOURCES})
