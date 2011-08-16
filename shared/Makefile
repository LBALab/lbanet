
OBJ=CharacterModes.o CharacterStates.o ClientScript.o CommonTypes.o Entities.o HQRHandler.o HQRlib.o Lba1ModelMapHandler.o LogHandler.o Randomizer.o StaticObject.o ScriptedActor.o ScriptEnvironmentBase.o StreamReader.o SynchronizedTimeHandler.o XmlReader.o WorldToDisplayObjectSynchronizer.o NaviMeshHandler.o NavMeshAgent.o FileUtil.o DynamicObject.o ../dependencies/recast/Detour/Source/DetourAlloc.o ../dependencies/recast/Detour/Source/DetourCommon.o ../dependencies/recast/Detour/Source/DetourNavMesh.o ../dependencies/recast/Detour/Source/DetourNavMeshBuilder.o ../dependencies/recast/Detour/Source/DetourNavMeshQuery.o ../dependencies/recast/Detour/Source/DetourNode.o ../dependencies/recast/DetourCrowd/Source/DetourCrowd.o ../dependencies/recast/DetourCrowd/Source/DetourLocalBoundary.o ../dependencies/recast/DetourCrowd/Source/DetourObstacleAvoidance.o ../dependencies/recast/DetourCrowd/Source/DetourPathCorridor.o ../dependencies/recast/DetourCrowd/Source/DetourPathQueue.o ../dependencies/recast/DetourCrowd/Source/DetourProximityGrid.o ../dependencies/recast/Recast/Source/Recast.o ../dependencies/recast/Recast/Source/RecastAlloc.o ../dependencies/recast/Recast/Source/RecastArea.o ../dependencies/recast/Recast/Source/RecastContour.o ../dependencies/recast/Recast/Source/RecastFilter.o ../dependencies/recast/Recast/Source/RecastLayers.o ../dependencies/recast/Recast/Source/RecastMesh.o ../dependencies/recast/Recast/Source/RecastMeshDetail.o ../dependencies/recast/Recast/Source/RecastRasterization.o ../dependencies/recast/Recast/Source/RecastRegion.o

CC=g++
INCDIR=-I. -I../include -I/usr/include -I../infrastructure/include -I../dependencies/LUA/include -I../dependencies/luabind/include -I../dependencies/tmpboost -I../dependencies/recast/Detour/Include -I../dependencies/recast/DetourCrowd/Include -I../dependencies/recast/Recast/Include


all: libshared.a install

clear: clean depend


libshared.a: $(OBJ)
	@echo "\n         **********creation de la bibliotheque************\n"
	ar rv libshared.a *.o
	@echo "\n"		

.cpp.o:
	@echo "\n         **********creation des .o************\n"
	$(CC) -O2 -D_LBANET_SERVER_SIDE_ $(INCDIR) -c $<
	@echo "\n"

depend: 
	@echo "\n         **********creation des dependances************\n"	
	@$(CC) $(INCDIR) -D_LBANET_SERVER_SIDE_ -MM *.cpp  > dep



install:
	@echo "\n         ********** copie des fichiers dans include & bib ************\n"
	mv *.a ./lib
	@echo "\n"
clean:
	@echo "\n        ********** nettoyage ************\n"
	rm -f $(OBJ) libshared.a dep
	@touch dep
	@echo "\n"
		
include dep
