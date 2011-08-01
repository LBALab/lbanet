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

#ifdef NDEBUG
HINSTANCE globalInstance;
#endif

#include "crashrpt.h"
#pragma comment(lib, "crashrpt.lib")

jmp_buf mark;              // Address for long jump to jump to
int     fperr;             // Global error number

BOOL WINAPI CrashCallback(LPVOID lpvState)
{
	LogHandler::getInstance()->CloseFile();
	AddFile(lpvState, LogHandler::getInstance()->GetFilename().c_str(), "Lbanet general log");
	//AddFile(lpvState, LogHandler::getInstance()->GetGUIFilename().c_str(), "GUI log");
	return TRUE;
}
#endif


// fphandler handles SIGFPE (floating-point error) interrupt. Note
// that this prototype accepts two arguments and that the 
// prototype for signal in the run-time library expects a signal 
// handler to have only one argument.
//
// The second argument in this signal handler allows processing of
// _FPE_INVALID, _FPE_OVERFLOW, _FPE_UNDERFLOW, and 
// _FPE_ZERODIVIDE, all of which are Microsoft-specific symbols 
// that augment the information provided by SIGFPE. The compiler 
// will generate a warning, which is harmless and expected.

void fphandler( int sig, int num )
{
   // Set global for outside check since we don't want
   // to do I/O in the handler.
   fperr = num;

   // Initialize floating-point package. */
   _fpreset();

   // Restore calling environment and jump back to setjmp. Return 
   // -1 so that setjmp will return false for conditional test.
   longjmp( mark, -1 );
}

void fpcheck( void )
{
	char fpstr[30];
	switch( fperr )
	{
	case _FPE_INVALID:
	   strcpy_s( fpstr, sizeof(fpstr), "Invalid number" );
	   break;
	case _FPE_OVERFLOW:
	   strcpy_s( fpstr, sizeof(fpstr), "Overflow" );

	   break;
	case _FPE_UNDERFLOW:
	   strcpy_s( fpstr, sizeof(fpstr), "Underflow" );
	   break;
	case _FPE_ZERODIVIDE:
	   strcpy_s( fpstr, sizeof(fpstr), "Divide by zero" );
	   break;
	default:
	   strcpy_s( fpstr, sizeof(fpstr), "Other floating point error" );
	   break;
	}

	std::stringstream strs;
	strs<<"Float Error "<<fperr<<" - "<<fpstr;
	LogHandler::getInstance()->LogToFile(strs.str());
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
		//#if (defined(NDEBUG) && defined(WIN32))
		//SendMessage((HWND)OsgHandler::getInstance()->GetWindowsHandle(), 
		//	WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(globalInstance,  MAKEINTRESOURCE(IDI_ICON1)));
		//#endif




		LogHandler::getInstance()->LogToFile("Starting the game engine...");
		engine.run();


		communicator()->shutdown();
		communicator()->waitForShutdown();
		return EXIT_SUCCESS;
	}
};





#if (defined(NDEBUG) && defined(WIN32))
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

	QApplication a(argc, argv);

#ifdef WIN32
	// disable areo on vista+ operating system
 //   OSVERSIONINFO osvi;
 //   ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
 //   osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
 //   GetVersionEx(&osvi);
	//if(osvi.dwMajorVersion > 5)
	//{
	//	HINSTANCE LoadMe;
	//	LoadMe = LoadLibraryA("Dwmapi.dll");
	//	if(LoadMe)
	//	{
	//		typedef HRESULT (__stdcall *EntryPointfuncPtr)(UINT uCompositionAction );  
	//		EntryPointfuncPtr LibMainEntryPoint;            
	//		LibMainEntryPoint = (EntryPointfuncPtr)GetProcAddress(LoadMe,"DwmEnableComposition");
	//		if(LibMainEntryPoint)
	//			LibMainEntryPoint(DWM_EC_DISABLECOMPOSITION);

	//		FreeLibrary(LoadMe);
	//	}
	//}

	// init crash reporter
	LPVOID chandler = Install(CrashCallback, NULL, NULL);



	// Set up floating-point error handler. The compiler
	// will generate a warning because it expects
	// signal-handling functions to take only one argument.
	if( signal( SIGFPE, (void (__cdecl *)(int)) fphandler ) == SIG_ERR )
	{
		LogHandler::getInstance()->LogToFile("Couldn't set SIGFPE");
		abort();
	}


#endif
   int jmpret;

   // Save stack environment for return in case of error. First 
   // time through, jmpret is 0, so true conditional is executed. 
   // If an error occurs, jmpret will be set to -1 and false 
   // conditional will be executed.
   jmpret = setjmp( mark );


	// Unmask all floating-point exceptions. 
	//_control87( 0, _MCW_EM );


   if( jmpret == 0 )
   {
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
   }
   else
      fpcheck();

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
