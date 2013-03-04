
file(
	GLOB
	sharedlib_INCLUDES
	${3RD_PARTY_PATH}/recast/Recast/include/*.h
)

SET(recastlib_SOURCES 		
		${3RD_PARTY_PATH}/recast/Recast/Source/Recast.cpp
		${3RD_PARTY_PATH}/recast/Recast/Source/RecastAlloc.cpp
		${3RD_PARTY_PATH}/recast/Recast/Source/RecastArea.cpp
		${3RD_PARTY_PATH}/recast/Recast/Source/RecastContour.cpp
		${3RD_PARTY_PATH}/recast/Recast/Source/RecastFilter.cpp
		${3RD_PARTY_PATH}/recast/Recast/Source/RecastLayers.cpp
		${3RD_PARTY_PATH}/recast/Recast/Source/RecastMesh.cpp
		${3RD_PARTY_PATH}/recast/Recast/Source/RecastMeshDetail.cpp
		${3RD_PARTY_PATH}/recast/Recast/Source/RecastRasterization.cpp
		${3RD_PARTY_PATH}/recast/Recast/Source/RecastRegion.cpp
		${3RD_PARTY_PATH}/recast/Detour/Source/DetourAlloc.cpp
		${3RD_PARTY_PATH}/recast/Detour/Source/DetourCommon.cpp
		${3RD_PARTY_PATH}/recast/Detour/Source/DetourNavMesh.cpp
		${3RD_PARTY_PATH}/recast/Detour/Source/DetourNavMeshBuilder.cpp
		${3RD_PARTY_PATH}/recast/Detour/Source/DetourNavMeshQuery.cpp
		${3RD_PARTY_PATH}/recast/Detour/Source/DetourNode.cpp
		${3RD_PARTY_PATH}/recast/DetourCrowd/Source/DetourCrowd.cpp
		${3RD_PARTY_PATH}/recast/DetourCrowd/Source/DetourLocalBoundary.cpp
		${3RD_PARTY_PATH}/recast/DetourCrowd/Source/DetourObstacleAvoidance.cpp
		${3RD_PARTY_PATH}/recast/DetourCrowd/Source/DetourPathCorridor.cpp
		${3RD_PARTY_PATH}/recast/DetourCrowd/Source/DetourPathQueue.cpp
		${3RD_PARTY_PATH}/recast/DetourCrowd/Source/DetourProximityGrid.cpp)
		
add_library(RecastLib STATIC ${recastlib_INCLUDES} ${recastlib_SOURCES})


SET(client_SOURCES 
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
		editorhandler.cpp
		editor.cpp		
		editlba1animsound.cpp
		ExternalActor.cpp
		ExternalPlayer.cpp
		GUI.cpp
		GUILocalizationCallback.cpp
		GameGUI.cpp
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
		../Servers/WorldServer/PointFlag.cpp
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
		${3RD_PARTY_PATH}/sqlite/sqlite3.c)
		
file(
	GLOB
	client_INCLUDES
	*.h
)

IF (WIN32)
   SET(client_SOURCES ${client_SOURCES} LBANet.rc)
ENDIF (WIN32)

	
#QT stuff
SET(QT_USE_QTOPENGL TRUE)
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE( ${QT_USE_FILE} )


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


LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/shared)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/Servers/WorldServer)
INCLUDE_DIRECTORIES(${3RD_PARTY_PATH}/sqlite)

IF (WIN32)
INCLUDE_DIRECTORIES(${3RD_PARTY_PATH}/CrashRpt/include)
LINK_DIRECTORIES(${3RD_PARTY_PATH}/CrashRpt/lib)
ENDIF (WIN32)


#QT moc stuff
SET(client_TOMOC_HEADERS client.h vlc_on_qt.h treemodel.h editor.h editorhandler.h editlba1animsound.h)
SET(client_FORMS addactordialog.ui additemdialog.ui addmapdialog.ui addspawning.ui addstartitemdialog.ui addteleportdialog.ui addtemplate.ui addtextdialog.ui addtriggerdialog.ui addworlddialog.ui client.ui editor.ui editlba1animsound.ui edittemplatesdialog.ui ImportantNotice.ui NavMeshOption.ui openworlddialog.ui LuaConsole.ui)
SET(client_RESOURCES client.qrc editor.qrc editlba1animsound.qrc)

QT4_WRAP_CPP(client_HEADERS_MOC ${client_TOMOC_HEADERS})
QT4_WRAP_UI(client_FORMS_HEADERS ${client_FORMS})
QT4_ADD_RESOURCES(client_RESOURCES_RCC ${client_RESOURCES})


ADD_EXECUTABLE(LBANetGame ${client_INCLUDES} 
			${client_SOURCES} 
			${client_HEADERS_MOC} 
			${client_FORMS_HEADERS} 
			${client_RESOURCES_RCC})

if(WIN32)
   set_target_properties(LBANetGame PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:windows")
   set_target_properties(LBANetGame PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:windows")
endif(WIN32)


ADD_EXECUTABLE(libfmodex-4.40.06.so IMPORTED)
		    
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
TARGET_LINK_LIBRARIES(LBANetGame ${OPENGL_LIBRARY})

TARGET_LINK_LIBRARIES(LBANetGame LBANetShared)
TARGET_LINK_LIBRARIES(LBANetGame LBANetInfrastructure)
TARGET_LINK_LIBRARIES(LBANetGame RecastLib)