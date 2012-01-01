#include "editlba1animsound.h"
#include <QtGui/QApplication>

#include "LbaNetEngine.h"
#include "resource.h"
#include "OSGHandler.h"
#include "LogHandler.h"

#include "editlba1animsound.h"





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

	QApplication a(argc, argv);

	try
	{
		// create engine
		LogHandler::getInstance()->LogToFile("Initializing the game engine...");
		boost::shared_ptr<EditorHandlerBase> editH(new EditLBA1AnimSound);
		LbaNetEngine engine(NULL, "editor", editH);

		LogHandler::getInstance()->LogToFile("Running the game engine...");
		engine.run();
		return 0;

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
