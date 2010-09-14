TARGET=connectedtraker
OBJ=ConnectedTrackerServant.o PermissionsVerifierServant.o SharedData.o DatabaseHandler.o main.o ../../common/md5.o

CC=g++
INCDIR=-I. -I../infrastructure/include -I/usr/include  -I/usr/include/mysql++ -I/usr/include/mysql -I../../common
LIBDIR=-L/usr/lib -L../infrastructure/lib -L/usr/local/lib
LIBS=-lIce -lIceStorm -lIceUtil -lGlacier2 -lgenerated -lmysqlpp -lmysqlclient


all: clean depend $(TARGET) install


$(TARGET): $(OBJ)
	@echo "\n         **********creation de l'exe************\n"
	$(CC) $(INCDIR) *.o -o $(TARGET) $(LIBDIR) $(LIBS) 
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
	cp $(TARGET) ../bin
	@echo "\n"
clean:
	@echo "\n        ********** nettoyage ************\n"
	rm -f $(OBJ) $(TARGET) dep
	@touch dep
	@echo "\n"
		
include dep
