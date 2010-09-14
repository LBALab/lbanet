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

#include "ConnectedTrackerServant.h"
#include "PermissionsVerifierServant.h"
#include "SharedData.h"
#include "DatabaseHandler.h"


class LbaServer : public Ice::Application
{
public:

    virtual int run(int argc, char* argv[])
    {
		SharedData shd;

		Ice::PropertiesPtr prop = communicator()->getProperties();

		DatabaseHandler dbh(prop->getProperty("dbname"), prop->getProperty("dbserver"),
							prop->getProperty("dbuser"), prop->getProperty("dbpassword"));

		_adapter = communicator()->createObjectAdapter(prop->getProperty("IdentityAdapter"));
		_adapter->add(new ConnectedTrackerServant(communicator(), &shd, dbh), communicator()->stringToIdentity(prop->getProperty("ConnectedServantName")));
		_adapter->add(new PermissionsVerifierServant(&shd, dbh), communicator()->stringToIdentity(prop->getProperty("VerifierServantName")));
		_adapter->activate();

		communicator()->waitForShutdown();

		return EXIT_SUCCESS;
	}

private:
	Ice::ObjectAdapterPtr _adapter;
};


int main(int argc, char** argv)
{
	LbaServer app;
	return app.main(argc, argv/*, "config"*/);

}

