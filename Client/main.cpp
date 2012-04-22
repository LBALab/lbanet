/*
------------------------[ Lbanet Source ]-------------------------
Copyright (C) 2009
Author: Vivien Delage [Rincevent_123]
Email : vdelage@gmail.com

-------------------------------[ GNU License ]-------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
*/

#include <QtGui/QApplication>

#include "LbaNetEngine.h"
#include <Ice/Application.h>
#include "resource.h"
#include "OSGHandler.h"
#include "LogHandler.h"


#ifdef WIN32
#include <windows.h>
#include <tchar.h>
#include <Dwmapi.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>
#include <float.h>

#include "crashrpt.h"
#pragma comment(lib, "crashrpt.lib")


#ifdef _USE_QT_EDITOR_
#include "editorhandler.h"
#endif

BOOL WINAPI CrashCallback(LPVOID lpvState)
{
	LogHandler::getInstance()->CloseFile();
	AddFile(lpvState, LogHandler::getInstance()->GetFilename().c_str(), "Lbanet general log");
	//AddFile(lpvState, LogHandler::getInstance()->GetGUIFilename().c_str(), "GUI log");
	return TRUE;
}
#endif


#ifndef _USE_QT_EDITOR_
class IceClient : public Ice::Application
{
public:

    virtual int run(int argc, char* argv[])
    {
		shutdownOnInterrupt();

		LogHandler::getInstance()->LogToFile("Reading properties...");
		Ice::PropertiesPtr prop = communicator()->getProperties();
		std::string clientV = prop->getPropertyWithDefault("LbanetClientVersion", "v0");

		LogHandler::getInstance()->LogToFile("Initializing the game engine...");
		// create engine
		LbaNetEngine engine(communicator(), clientV);

		LogHandler::getInstance()->LogToFile("Starting the game engine...");
		engine.run();


		communicator()->shutdown();
		communicator()->waitForShutdown();
		return EXIT_SUCCESS;
	}
};
#endif




#if (defined(NDEBUG) && defined(WIN32))
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// convert to argc/argv
    char cmdline[4096];
    char* argv[4096];
    int argc = 0 ;
    strcpy( cmdline, GetCommandLineA() ) ;
    argv[argc] = strtok( cmdline, " \t" ) ;
    while( argv[argc] != 0 )
    {
        argc++ ;
        argv[argc] = strtok( 0, " \t" ) ;
    }
#else
int main( int argc, char **argv )
{
#endif

	std::ofstream filecout("cout.log");
	std::cout.rdbuf(filecout.rdbuf());
	std::ofstream filecerr("cerr.log");
	std::cerr.rdbuf(filecerr.rdbuf());

	QApplication a(argc, argv);

#ifdef WIN32

	// init crash reporter
	LPVOID chandler = Install(CrashCallback, NULL, NULL);
#endif


	try
	{
#ifdef _USE_QT_EDITOR_
		// create engine
		LogHandler::getInstance()->LogToFile("Initializing the game engine...");
		boost::shared_ptr<EditorHandlerBase> editH(new EditorHandler);
		LbaNetEngine engine(NULL, "editor", editH);

		LogHandler::getInstance()->LogToFile("Running the game engine...");
		engine.run();
		return 0;
#else
		LogHandler::getInstance()->LogToFile("Entering main program...");
		IceClient app;
		int ret = app.main(argc, argv, "config.client");
		filecout.close();
		filecerr.close();
		return ret;
#endif
	}
	catch(std::exception & ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Unhandled exception catched:") + ex.what());
	}
	catch(...)
	{
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception catched"));
	}

	filecout.close();
	filecerr.close();
	return -1;
}



//
//// crt_fpreset.c
//// This program uses signal to set up a
//// routine for handling floating-point errors.
//
//#include <stdio.h>
//#include <signal.h>
//#include <setjmp.h>
//#include <stdlib.h>
//#include <float.h>
//#include <math.h>
//#include <string.h>
//

//
//void __cdecl fphandler( int sig, int num );   // Prototypes
//void fpcheck( void );
//
//int main( void )
//{
//   double n1 = 5.0;
//   double n2 = 0.0;
//   double r;
//   int jmpret;
//

//
//   // Save stack environment for return in case of error. First 
//   // time through, jmpret is 0, so true conditional is executed. 
//   // If an error occurs, jmpret will be set to -1 and false 
//   // conditional will be executed.
//   jmpret = setjmp( mark );
//   if( jmpret == 0 )
//   {
//      printf( "Dividing %4.3g by %4.3g...\n", n1, n2 );
//      r = n1 / n2;
//      // This won't be reached if error occurs.
//      printf( "\n\n%4.3g / %4.3g = %4.3g\n", n1, n2, r );
//
//      r = n1 * n2;
//      // This won't be reached if error occurs.
//      printf( "\n\n%4.3g * %4.3g = %4.3g\n", n1, n2, r );
//   }
//   else
//      fpcheck();
//}
