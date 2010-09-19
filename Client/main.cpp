/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This application is open source and may be redistributed and/or modified   
 * freely and without restriction, both in commericial and non commericial applications,
 * as long as this copyright notice is maintained.
 * 
 * This application is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/



#include "LbaNetEngine.h"
#include <Ice/Application.h>
#include "resource.h"
#include "OSGHandler.h"
#include "LogHandler.h"

#include <windows.h>
#include <tchar.h>


#ifdef NDEBUG
HINSTANCE globalInstance;
#endif

#include "crashrpt.h"
#pragma comment(lib, "crashrpt.lib")


BOOL WINAPI CrashCallback(LPVOID lpvState)
{
	LogHandler::getInstance()->CloseFile();
	AddFile(lpvState, LogHandler::getInstance()->GetFilename().c_str(), "Lbanet general log");
	//AddFile(lpvState, LogHandler::getInstance()->GetGUIFilename().c_str(), "GUI log");
	return TRUE;
}



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



		// set windows icon in release mode
		#ifdef NDEBUG
		SendMessage((HWND)OsgHandler::getInstance()->GetWindowsHandle(), 
			WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(globalInstance,  MAKEINTRESOURCE(IDI_ICON1)));
		#endif




		LogHandler::getInstance()->LogToFile("Starting the game engine...");
		engine.run();


		communicator()->shutdown();
		communicator()->waitForShutdown();
		return EXIT_SUCCESS;
	}
};






#ifdef NDEBUG
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	globalInstance = hInstance;

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

	// init crash reporter
	LPVOID chandler = Install(CrashCallback, NULL, NULL);

	try
	{
		LogHandler::getInstance()->LogToFile("Entering main program...");
		IceClient app;
		return app.main(argc, argv, "config.client");
	}
	catch(std::exception & ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Unhandled exception catched:") + ex.what());
	}
	catch(...)
	{
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception catched"));
	}
	return -1;
}


