TARGET=worldserver
OBJ=Actions.o ActorHandler.o  ActorScriptPart.o CommunityBoxHandler.o Conditions.o ContainerBoxHandler.o DatabaseHandler.o DialogBoxHandler.o DialogPart.o DoorHandler.o InventoryBoxHandler.o InventoryItemHandler.oMailBoxHandler.o main.o MaintenanceInterfaceServant.o MapHandler.o NpcHandler.o ObjectsDescription.o PlayerHandler.o Quest.o QuestHandler.oServerGUIBase.o ServerLBA1ModelClass.o ServerLba1ModelHandler.o ServerLuaHandler.o SharedDataHandler.o ShopBoxHandler.o ShortcutBoxHandler.o Spawn.o Teleport.o TextBoxHandler.o Triggers.o WorldChatHandler.o WorldServerInterfaceServant.o

CC=g++
INCDIR=-I. -I../../infrastructure/include -I/usr/include -I../../shared -I. -I/usr/include/mysql++ -I/usr/include/mysql -I../../dependencies/LUA/include
LIBDIR=-L/usr/lib -L../../infrastructure/lib
LIBS=-lIce -lIceStorm -lIceUtil -lGlacier2 -lgenerated -lmysqlpp -lmysqlclient


all: $(TARGET) install

clear: clean depend


$(TARGET): $(OBJ)
	@echo "\n         **********creation de l'exe************\n"
	$(CC) $(INCDIR) *.o -o $(TARGET) $(LIBDIR) $(LIBS) 
	@echo "\n"		

.cpp.o:
	@echo "\n         **********creation des .o************\n"
	$(CC) -O2 -D_LBANET_SERVER_SIDE_ -I. $(INCDIR) -c $<
	@echo "\n"

depend: 
	@echo "\n         **********creation des dependances************\n"	
	@$(CC) $(INCDIR) -MM *.cpp  > dep



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
