SET(client_SOURCES ActorUserData.cpp
		AnimatedObjectHandlerBase.cpp
		CEGUIDrawable.cpp
		CameraController.cpp
		CharacterControllerLBA.cpp
		ChatBox.cpp
		ChatReceiverServant.cpp
		ChatServerHandler.cpp
		ChooseNumberBox.cpp
		ChooseWorldGUI.cpp
		ClientLuaHandler.cpp
		CommunityBox.cpp
		ConfigurationManager.cpp
		ContainerBox.cpp
		DataLoader.cpp
		DialogBox.cpp
		EditorSharedData.cpp
		ExternalActor.cpp
		ExternalPlayer.cpp
		GUI.cpp
		GUILocalizationCallback.cpp
		GameGUI.cpp
		GraphicsWindowQt.cpp
		GuiHandler.cpp
		Holomap.cpp
		HolomapHandler.cpp
		ImageSetHandler.cpp
		InfosReceiverServant.cpp
		InventoryBox.cpp
		ItemObject.cpp
		JournalBox.cpp
		LBA1ModelClass.cpp
		Lba1ModelHandler.cpp
		LbaNetEngine.cpp
		LbaNetModel.cpp
		LetterEditorBox.cpp
		LetterViewerBox.cpp
		LocalConnectionHandler.cpp
		Localizer.cpp
		LoginGUI.cpp
		MailBox.cpp
		MenuGUI.cpp
		MessageBox.cpp
		MusicHandler.cpp
		OSGHandler.cpp
		OptionsGUI.cpp
		OsgEventHandler.cpp
		OsgObjectHandler.cpp
		PhysXEngine.cpp
		PhysXObjectHandlers.cpp
		ProjectileHandler.cpp
		RemoteConnectionHandler.cpp
		ShopBox.cpp
		ShortcutBox.cpp
		SoundObjectHandlerClient.cpp
		Stream.cpp
		StringMorphInterpolator.cpp
		TeleportBox.cpp
		UserAllocator.cpp
		WorldPatcher.cpp
		client.cpp
		main.cpp
		treeitem.cpp
		treemodel.cpp
		vlc_on_qt.cpp
		../Servers/WorldServer/Actions.cpp
		../Servers/WorldServer/ActorHandler.cpp
		../Servers/WorldServer/ActorScriptPart.cpp
		../Servers/WorldServer/CommunityBoxHandler.cpp
		../Servers/WorldServer/Conditions.cpp
		../Servers/WorldServer/ContainerBoxHandler.cpp
		../Servers/WorldServer/DialogBoxHandler.cpp
		../Servers/WorldServer/DialogPart.cpp
		../Servers/WorldServer/DoorHandler.cpp
		../Servers/WorldServer/InventoryBoxHandler.cpp
		../Servers/WorldServer/InventoryItemHandler.cpp
		../Servers/WorldServer/LocalDatabaseHandler.cpp
		../Servers/WorldServer/LuaHandlerBase.cpp
		../Servers/WorldServer/LuaThreadHandler.cpp
		../Servers/WorldServer/MailBoxHandler.cpp
		../Servers/WorldServer/MapHandler.cpp
		../Servers/WorldServer/NavMeshObjectHandlers.cpp
		../Servers/WorldServer/NpcHandler.cpp
		../Servers/WorldServer/ObjectsDescription.cpp
		../Servers/WorldServer/PlayerHandler.cpp
		../Servers/WorldServer/ProjectileObjectDef.cpp
		../Servers/WorldServer/Quest.cpp
		../Servers/WorldServer/QuestHandler.cpp
		../Servers/WorldServer/ServerGUIBase.cpp
		../Servers/WorldServer/ServerLBA1ModelClass.cpp
		../Servers/WorldServer/ServerLba1ModelHandler.cpp
		../Servers/WorldServer/ServerLuaHandler.cpp
		../Servers/WorldServer/SharedDataHandler.cpp
		../Servers/WorldServer/ShopBoxHandler.cpp
		../Servers/WorldServer/ShortcutBoxHandler.cpp
		../Servers/WorldServer/SoundObjectHandlerServer.cpp
		../Servers/WorldServer/Spawn.cpp
		../Servers/WorldServer/Teleport.cpp
		../Servers/WorldServer/TextBoxHandler.cpp
		../Servers/WorldServer/Triggers.cpp
		../dependencies/sqlite/sqlite3.c
		../dependencies/recast/Recast/Source/Recast.cpp
		../dependencies/recast/Recast/Source/RecastAlloc.cpp
		../dependencies/recast/Recast/Source/RecastArea.cpp
		../dependencies/recast/Recast/Source/RecastContour.cpp
		../dependencies/recast/Recast/Source/RecastFilter.cpp
		../dependencies/recast/Recast/Source/RecastLayers.cpp
		../dependencies/recast/Recast/Source/RecastMesh.cpp
		../dependencies/recast/Recast/Source/RecastMeshDetail.cpp
		../dependencies/recast/Recast/Source/RecastRasterization.cpp
		../dependencies/recast/Recast/Source/RecastRegion.cpp
		../dependencies/recast/Detour/Source/DetourAlloc.cpp
		../dependencies/recast/Detour/Source/DetourCommon.cpp
		../dependencies/recast/Detour/Source/DetourNavMesh.cpp
		../dependencies/recast/Detour/Source/DetourNavMeshBuilder.cpp
		../dependencies/recast/Detour/Source/DetourNavMeshQuery.cpp
		../dependencies/recast/Detour/Source/DetourNode.cpp
		../dependencies/recast/DetourCrowd/Source/DetourCrowd.cpp
		../dependencies/recast/DetourCrowd/Source/DetourLocalBoundary.cpp
		../dependencies/recast/DetourCrowd/Source/DetourObstacleAvoidance.cpp
		../dependencies/recast/DetourCrowd/Source/DetourPathCorridor.cpp
		../dependencies/recast/DetourCrowd/Source/DetourPathQueue.cpp
		../dependencies/recast/DetourCrowd/Source/DetourProximityGrid.cpp)
		

	
#QT stuff
SET(QT_USE_QTOPENGL TRUE)
FIND_PACKAGE(Qt4 REQUIRED)

INCLUDE( ${QT_USE_FILE} )

SET(client_TOMOC_HEADERS client.h vlc_on_qt.h treemodel.h)
SET(client_FORMS client.ui)
SET(client_RESOURCES client.qrc)

QT4_WRAP_CPP(client_HEADERS_MOC ${client_TOMOC_HEADERS})
QT4_WRAP_UI(client_FORMS_HEADERS ${client_FORMS})
QT4_ADD_RESOURCES(client_RESOURCES_RCC ${client_RESOURCES})



file(
	GLOB
	client_INCLUDES
	*.h
)



#PHYSX stuff
FIND_PACKAGE(PHYSX REQUIRED)
INCLUDE_DIRECTORIES(${PHYSX_INCLUDE_DIRS})

#CEGUI stuff
FIND_PACKAGE(CEGUI REQUIRED)
INCLUDE_DIRECTORIES(${CEGUI_INCLUDE_DIRS})

#LUA stuff
FIND_PACKAGE(LUA REQUIRED)
INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIRS})

#LUABIND stuff
FIND_PACKAGE(LUABIND REQUIRED)
INCLUDE_DIRECTORIES(${LUABIND_INCLUDE_DIRS})

#FMOD stuff
FIND_PACKAGE(FMOD REQUIRED)
INCLUDE_DIRECTORIES(${FMOD_INCLUDE_DIRS})

#VLC stuff
FIND_PACKAGE(VLC REQUIRED)
INCLUDE_DIRECTORIES(${VLC_INCLUDE_DIRS})

#FREETYPE stuff
FIND_PACKAGE(FREETYPE REQUIRED)
INCLUDE_DIRECTORIES(${FREETYPE_INCLUDE_DIRS})



INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/shared)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Servers/WorldServer)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/dependencies/sqlite)

IF (WIN32)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/dependencies/CrashReport/crashrpt/include)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/dependencies/CrashReport/crashrpt/lib)
ENDIF (WIN32)

ADD_EXECUTABLE(LBANetGame ${client_INCLUDES} 
			${client_SOURCES} 
			${client_HEADERS_MOC} 
			${client_FORMS_HEADERS} 
			${client_RESOURCES_RCC})
		    
INCLUDE_DIRECTORIES(LBANetGame ${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(LBANetGame  ${PROJECT_SOURCE_DIR}/../shared)

TARGET_LINK_LIBRARIES(LBANetGame ${QT_LIBRARIES} )
TARGET_LINK_LIBRARIES(LBANetGame ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES(LBANetGame ${ICE_LIBRARIES})
TARGET_LINK_LIBRARIES(LBANetGame ${OSG_LIBRARIES})
TARGET_LINK_LIBRARIES(LBANetGame ${PHYSX_LIBRARIES})
TARGET_LINK_LIBRARIES(LBANetGame ${CEGUI_LIBRARIES})
TARGET_LINK_LIBRARIES(LBANetGame ${LUA_LIBRARIES})
TARGET_LINK_LIBRARIES(LBANetGame ${LUABIND_LIBRARIES})
TARGET_LINK_LIBRARIES(LBANetGame ${FMOD_LIBRARIES})
TARGET_LINK_LIBRARIES(LBANetGame ${VLC_LIBRARIES})
TARGET_LINK_LIBRARIES(LBANetGame ${FREETYPE_LIBRARIES})

TARGET_LINK_LIBRARIES(LBANetGame LBANetShared)
TARGET_LINK_LIBRARIES(LBANetGame LBANetInfrastructure)
