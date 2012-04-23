TARGET=worldserver
OBJ=Actions.o ActorHandler.o  ActorScriptPart.o CommunityBoxHandler.o Conditions.o ContainerBoxHandler.o DatabaseHandler.o DialogBoxHandler.o DialogPart.o DoorHandler.o InventoryBoxHandler.o InventoryItemHandler.o MailBoxHandler.o main.o MaintenanceInterfaceServant.o MapHandler.o NpcHandler.o ObjectsDescription.o PlayerHandler.o Quest.o QuestHandler.o ServerGUIBase.o ServerLBA1ModelClass.o ServerLba1ModelHandler.o ServerLuaHandler.o SharedDataHandler.o ShopBoxHandler.o ShortcutBoxHandler.o Spawn.o Teleport.o TextBoxHandler.o Triggers.o WorldChatHandler.o WorldServerInterfaceServant.o LuaHandlerBase.o LuaThreadHandler.o ProjectileObjectDef.o NavMeshObjectHandlers.o SoundObjectHandlerServer.o

CC=g++
INCDIR=-I. -I../../infrastructure/include -I/usr/include -I../../shared -I. -I/usr/include/mysql++ -I/usr/include/mysql -I/usr/include/lua5.1 -I/usr/local/include/luabind
LIBDIR=-L/usr/lib -L../../infrastructure/lib -L../../shared/lib -L/usr/local/lib
LIBS=-lIce -lIceStorm -lIceUtil -lGlacier2 -lgenerated -llua5.1 -lluabind -lshared -lmysqlpp -lmysqlclient


all: $(TARGET) install

clear: clean depend


$(TARGET): $(OBJ)
	@echo "\n         **********creation de l'exe************\n"
	$(CC)  -R /usr/local/lib $(INCDIR) *.o -o $(TARGET) $(LIBDIR) $(LIBS) 
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
	cp $(TARGET) ../bin
	@echo "\n"
clean:
	@echo "\n        ********** nettoyage ************\n"
	rm -f $(OBJ) $(TARGET) dep
	@touch dep
	@echo "\n"
		
include dep
