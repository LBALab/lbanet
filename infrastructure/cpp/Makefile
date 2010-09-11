
OBJ=ActorInfo.o ChatInfo.o ClientSession.o ConnectedTracker.o MapManager.o MapObserver.o RoomManager.o LbaTypes.o PollingChat.o

CC=g++
INCDIR=-I. -I../include -I/usr/include
LIBDIR=-L/usr/lib
LIBS=-lIce -lIceStorm -lIceutil -lGlacier2


all: clean depend libgenerated.a install


libgenerated.a: $(OBJ)
	@echo "\n         **********creation de la bibliotheque************\n"
	ar rv libgenerated.a $(OBJ)
	@echo "\n"		

.cpp.o:
	@echo "\n         **********creation des .o************\n"
	$(CC) -O2 -I. $(INCDIR) -c $<
	@echo "\n"

depend: 
	@echo "\n         **********creation des dependances************\n"	
	@$(CC) $(INCDIR) -MM *.cpp  > dep



install:
	@echo "\n         ********** copie des fichiers dans include & bib ************\n"
	cp *.a ../lib
	@echo "\n"
clean:
	@echo "\n        ********** nettoyage ************\n"
	rm -f $(OBJ) libgenerated.a dep
	@touch dep
	@echo "\n"
		
include dep
