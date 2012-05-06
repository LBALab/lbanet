#include "servermaintenancetool.h"
#include "LoginDialog.h"
#include "RemoteConnectionHandler.h"

#include "FileUtil.h"

#include <QtGui/QApplication>
#include <Ice/Application.h>
#include <QMessageBox>

class IceClient : public Ice::Application
{
public:
	IceClient(QApplication & qa)
		: _qa(qa), _w(_rc), _rc(_w)
	{}

    virtual int run(int argc, char* argv[])
    {
		shutdownOnInterrupt();
		LoginDialog ld(&_w);
		while(true)
		{
			if(ld.exec() == 0)
				return 0;
			else
			{
				std::string reason;
				int connected = _rc.Connect(communicator(), ld.UserName(), ld.Password(), reason);

				if(connected < 1)
				{
					QMessageBox::warning(&ld, "Can not login", reason.c_str());
				}
				else
				{
					break;
				}
			}
		}

		// set the available worlds
		std::vector<std::string> worlds;
		FileUtil::ListDirsNoPathInDir("Data/Worlds", worlds);
		_w.SetWorldsList(worlds);


		_w.show();
		int res = _qa.exec();

		_rc.reset();

		communicator()->shutdown();
		communicator()->waitForShutdown();
		return res;
	}
private:
	QApplication & _qa;
	ServerMaintenanceTool _w;
	RemoteConnectionHandler	_rc;
};


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	IceClient app(a);
	return app.main(argc, argv, "config.client");
}
