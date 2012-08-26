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

#include <Ice/Application.h>

#include "WorldServerInterfaceServant.h"
#include "MaintenanceInterfaceServant.h"
#include "WorldChatHandler.h"
#include "SharedDataHandler.h"
#include "XmlReader.h"
#include "DataDirHandler.h"

#ifdef _LOCAL_TEST_
#include "LocalDatabaseHandler.h"
#else
#include "DatabaseHandler.h
#endif



#include <WorldRegistration.h>

class WorldServer : public Ice::Application
{
public:

    virtual int run(int argc, char* argv[])
    {
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


		Ice::PropertiesPtr prop = communicator()->getProperties();
		std::string wname = prop->getProperty("WorldName");

		// init classes
		WorldInformation worldinfo;
		if(!XmlReader::LoadWorldInfo(DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+wname+"/WorldDescription.xml", worldinfo))
		{
			std::cout<<"Could not read world configuration file "<<DataDirHandler::getInstance()->GetDataDirPath() + "/Worlds/"+wname+"/WorldDescription.xml"<<std::endl;
			return EXIT_FAILURE;
		}

		WorldChatHandler wch(communicator());
		#ifdef _LOCAL_TEST_
		boost::shared_ptr<DatabaseHandlerBase> dbH(new LocalDatabaseHandler("lbanet.sav"));
		#else
		boost::shared_ptr<DatabaseHandlerBase> dbH(new DatabaseHandler(
							prop->getProperty("dbname"), prop->getProperty("dbserver"),
							prop->getProperty("dbuser"), prop->getProperty("dbpassword")));
		#endif
		SharedDataHandler::getInstance()->SetDbManager(dbH);
		SharedDataHandler::getInstance()->SetWorldDefaultInformation(worldinfo);

		//first register interfaces
		_adapter = communicator()->createObjectAdapter(prop->getProperty("IdentityAdapter"));
		Ice::ObjectPrx worldi = _adapter->add(new WorldServerInterfaceServant(),
						communicator()->stringToIdentity(prop->getProperty("WorldIServantName")));

		Ice::ObjectPrx worldmi = _adapter->add(new MaintenanceInterfaceServant(communicator(), wname, &wch),
						communicator()->stringToIdentity(prop->getProperty("MaintenanceIServantName")));
		_adapter->activate();


		// then inform login server we are on
		try
		{
			WorldRegisterInterfacePrx loginserv = WorldRegisterInterfacePrx::checkedCast(communicator()->stringToProxy(
																			communicator()->getProperties()->getProperty("LoginServer")));

			if(loginserv)
				loginserv->RegisterWorld(worldinfo.Description, 
									WorldServerInterfacePrx::uncheckedCast(worldi),
									MaintenanceInterfacePrx::uncheckedCast(worldmi));
		}
		catch(const IceUtil::Exception& ex)
		{
			std::cout<<"Exception getting the login server. "<<ex.what()<<std::endl;
		}
		catch(...)
		{
			std::cout<<"Unknown exception getting the login server . "<<std::endl;
		}

		communicator()->waitForShutdown();


		// clean up
		SharedDataHandler::getInstance()->CleanUp();



		return EXIT_SUCCESS;
	}

private:
	Ice::ObjectAdapterPtr _adapter;
};


int main(int argc, char** argv)
{
    WorldServer app;
    return app.main(argc, argv/*, "config"*/);
}

