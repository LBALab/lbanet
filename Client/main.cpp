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
#include "ConfigurationManager.h"
#include "DataLoader.h"
#include "DataDirHandler.h"
#include "editorhandler.h"
#include "editlba1animsound.h"

#ifdef WIN32
#include <windows.h>
#include <tchar.h>
#include <Dwmapi.h>
#include <signal.h>
#include <setjmp.h>
#include <stdlib.h>
#include <float.h>

#include "CrashRpt.h"
#pragma comment(lib, "CrashRpt1300.lib")


BOOL WINAPI CrashCallback(LPVOID lpvState)
{
	LogHandler::getInstance()->CloseFile();

	// Add our log file to the error report
	crAddFile2(LogHandler::getInstance()->GetFilename().c_str(), NULL, _T("Lbanet general log"), CR_AF_MAKE_FILE_COPY);    

	return TRUE;
}
#endif


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

	// Define CrashRpt configuration parameters
	CR_INSTALL_INFO info;  
	memset(&info, 0, sizeof(CR_INSTALL_INFO));  
	info.cb = sizeof(CR_INSTALL_INFO);    
	info.pszAppName = _T("LBANet");  
	info.pszAppVersion = _T("1.2.0");  
	info.pszEmailSubject = _T("LBANet 1.2.0 Error Report");  
	info.pszEmailTo = _T("vdelage@gmail.com");
	info.pfnCrashCallback = CrashCallback;   
	info.uPriorities[CR_SMTP] = 3;  // first try send report over SMTP  
	info.uPriorities[CR_SMAPI] = 2; // second try send report over Simple MAPI    
	// Install all available exception handlers, use HTTP binary transfer encoding (recommended).
	info.dwFlags |= CR_INST_ALL_POSSIBLE_HANDLERS;
	info.dwFlags |= CR_INST_HTTP_BINARY_ENCODING; 
	info.dwFlags |= CR_INST_APP_RESTART; 
	info.dwFlags |= CR_INST_SEND_QUEUED_REPORTS; 
	info.pszRestartCmdLine = _T("/restart");
	// Define the Privacy Policy URL 
	info.pszPrivacyPolicyURL = NULL; 

	// Install exception handlers
	int nResult = crInstall(&info);    
	if(nResult!=0)  
	{    
		// Something went wrong. Get error message.
		TCHAR szErrorMsg[512] = _T("");        
		crGetLastErrorMsg(szErrorMsg, 512);    
		_tprintf_s(_T("%s\n"), szErrorMsg);    
		return 1;
	} 
#endif

	// get data path if exists
	{
		std::ifstream datapathf("DataDirPath.txt");
		if(datapathf.is_open())
		{
			std::string datapath;
			std::getline(datapathf, datapath);
			if(datapath.size() > 0)
			{
				DataDirHandler::getInstance()->SetDataDirPath(datapath);
			}
		}
	}

	try
	{
		if (argc > 1)
		{
			DataDirHandler::getInstance()->SetEditorMode(true);
			if (argv[1][0] == '1')
			{
				// game editor
				// create engine
				LogHandler::getInstance()->LogToFile("Initializing the game engine...");
				boost::shared_ptr<EditorHandlerBase> editH(new EditorHandler);
				LbaNetEngine engine(NULL, "editor", editH);

				LogHandler::getInstance()->LogToFile("Running the game engine...");
				engine.run();

				// save config file
				ConfigurationManager::GetInstance()->SaveConfigFile();
				return 0;
			}
			else
			{
				// sound editor
				DataDirHandler::getInstance()->SetSoundEditorMode(true);
				// create engine
				LogHandler::getInstance()->LogToFile("Initializing the game engine...");
				boost::shared_ptr<EditorHandlerBase> editH(new EditLBA1AnimSound);
				LbaNetEngine engine(NULL, "editor", editH);

				LogHandler::getInstance()->LogToFile("Running the game engine...");
				engine.run();

				// save config file
				ConfigurationManager::GetInstance()->SaveConfigFile();
				return 0;
			}
		}
		else
		{
			// normal client
			DataDirHandler::getInstance()->SetEditorMode(false);
			LogHandler::getInstance()->LogToFile("Entering main program...");
			IceClient app;
			int ret = app.main(argc, argv, "config.client");
			filecout.close();
			filecerr.close();

			// save config file
			ConfigurationManager::GetInstance()->SaveConfigFile();
			return ret;
		}
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
