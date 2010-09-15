TARGET=loginserver
OBJ=ActorsParticipantServant.o ChatParticipantServant.o ClientSessionManagerServant.o main.o SessionServant.o DatabaseHandler.o ../../common/ActivableActor.o ../../common/Actor.o ../../common/MapInfoXmlReader.o ../../common/AreaSwitch.o ../../common/ContainerActor.o ../../common/DoorActor.o ../../common/ExitActor.o ../../common/FloorSwitch.o ../../common/LadderActor.o ../../common/LivingActor.o ../../common/SwitchActor.o ../../common/TextActor.o ../../common/UpExitActor.o ../../common/ZoneActivableActor.o ../../common/ZoneActor.o ../../common/HurtArea.o ../../common/Randomizer.o ../../common/3DObjectRenderer.o ../../common/Entities.o ../../common/HQRHandler.o ../../common/HQRlib.o ../../common/NPCActor.o ../../common/ScriptableActor.o ../../common/ScriptedZoneActor.o ../../common/ServerCharacterRenderer.o ../../common/ServerLBA1ModelClass.o ../../common/StreamReader.o ../../common/Quest.o ../../common/QuestCondition.o ../../common/QuestHandler.o ../../common/InventoryCondition.o ../../common/Dialog.o ../../common/MailboxActor.o ../../common/ActorCondition.o

CC=g++
INCDIR=-I. -I../infrastructure/include -I/usr/include -I../../common -I../../tinyxml/include -I/usr/include/mysql++ -I/usr/include/mysql
LIBDIR=-L/usr/lib -L../infrastructure/lib -L../../tinyxml/lib
LIBS=-lIce -lIceStorm -lIceUtil -lGlacier2 -lgenerated -ltinyxml -lmysqlpp -lmysqlclient


all: clean depend $(TARGET) install


$(TARGET): $(OBJ)
	@echo "\n         **********creation de l'exe************\n"
	$(CC) $(INCDIR) *.o -o $(TARGET) $(LIBDIR) $(LIBS) 
	@echo "\n"		

.cpp.o:
	@echo "\n         **********creation des .o************\n"
	$(CC) -O2 -D_LBANET_SERVER_SIDE_ -DTIXML_USE_STL -I. $(INCDIR) -c $<
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
