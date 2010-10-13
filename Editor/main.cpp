
#include <QtGui/QApplication>
#include "LbaNetEngine.h"
#include "OSGHandler.h"
#include "LogHandler.h"



#ifdef WIN32
#include <windows.h>
#include <tchar.h>
#include <Dwmapi.h>


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
#endif



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

#ifdef WIN32
	// disable areo on vista+ operating system
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
	if(osvi.dwMajorVersion > 5)
	{
		HINSTANCE LoadMe;
		LoadMe = LoadLibraryA("Dwmapi.dll");
		if(LoadMe)
		{
			typedef HRESULT (__stdcall *EntryPointfuncPtr)(UINT uCompositionAction );  
			EntryPointfuncPtr LibMainEntryPoint;            
			LibMainEntryPoint = (EntryPointfuncPtr)GetProcAddress(LoadMe,"DwmEnableComposition");
			if(LibMainEntryPoint)
				LibMainEntryPoint(DWM_EC_DISABLECOMPOSITION);

			FreeLibrary(LoadMe);
		}
	}

	// init crash reporter
	LPVOID chandler = Install(CrashCallback, NULL, NULL);
#endif


	QApplication a(argc, argv);


	// create engine
	LogHandler::getInstance()->LogToFile("Initializing the game engine...");
	LbaNetEngine engine(NULL, "editor");

	LogHandler::getInstance()->LogToFile("Running the game engine...");
	engine.run();

	return 0;
}
