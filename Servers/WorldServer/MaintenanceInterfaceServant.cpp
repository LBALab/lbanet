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


#include "MaintenanceInterfaceServant.h"


//! thread taking care of shutting down the server
class ShutdownThread : public IceUtil::Thread 
{
public:

	//! constructor
	ShutdownThread(Ice::CommunicatorPtr communicator, const std::string & worldname,
									WorldChatHandler * wcH)
		: _communicator(communicator), _worldname(worldname), _wcH(wcH)
	{}


	//! thread run function
    virtual void run() 
	{
		if(_wcH)
		{
			// send a world message sending that server will shutdown
			_wcH->SendSystemMessage("Server for world " + _worldname + " will shutdown in 1 minute...");

			// wait 30 seconds
			IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(30));

			// send a world 2nd message sending that server will shutdown
			_wcH->SendSystemMessage("Server for world " + _worldname + " will shutdown in 30 seconds...");

			// wait 20 seconds
			IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(20));

			// send a world 3nd message sending that server will shutdown
			_wcH->SendSystemMessage("Server for world " + _worldname + " will shutdown in 10 seconds...");

			// wait remaining time
			IceUtil::ThreadControl::sleep(IceUtil::Time::seconds(10));

		}

		// then shutdown
		_communicator->shutdown();
    }

private:
	Ice::CommunicatorPtr	_communicator;
	std::string				_worldname;
	WorldChatHandler *		_wcH;
};



/***********************************************************
tell the server to shutdown
***********************************************************/
void MaintenanceInterfaceServant::Shutdown(const Ice::Current&)
{
	IceUtil::ThreadPtr t = new ShutdownThread(_communicator, _worldname, _wcH);
	t->start();
}


