
OBJ=CharacterModes.o CharacterStates.o ClientScript.o CommonTypes.o Entities.o HQRHandler.o HQRlib.o Lba1ModelMapHandler.o LogHandler.o LuaHandlerBase.o LuaThreadHandler.o  Randomizer.o StaticObject.o ScriptedActor.o ScriptEnvironmentBase.o StreamReader.o SynchronizedTimeHandler.o XmlReader.o WorldToDisplayObjectSynchronizer.o

CC=g++
INCDIR=-I. -I../include -I/usr/include -I../infrastructure/include -I../dependencies/LUA/include
LIBDIR=-L/usr/lib -L../infrastructure/lib -L../dependencies/LUA/lib
LIBS=-lIce -lIceStorm -lIceutil -lGlacier2 -lgenerated


all: clean depend libshared.a install


libshared.a: $(OBJ)
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
	mv *.a ./lib
	@echo "\n"
clean:
	@echo "\n        ********** nettoyage ************\n"
	rm -f $(OBJ) libgenerated.a dep
	@touch dep
	@echo "\n"
		
include dep
