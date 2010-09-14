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

#include "ChatSessionManagerServant.h"
#include "ChatReceiverServant.h"
#include <RoomManager.h>
#include <ConnectedTracker.h>

class PollingChatServer : public Ice::Application
{
public:

    virtual int run(int argc, char* argv[])
    {
		_timer = new IceUtil::Timer();
		ChatReceiverServantPtr chatservant = new ChatReceiverServant();

		Ice::PropertiesPtr prop = communicator()->getProperties();

		// create chat session reaper
		int timeout = communicator()->getProperties()->getPropertyAsIntWithDefault("ReaperTimeout", 10);
		ReaperTaskPtr reaper = new ReaperTask(timeout, chatservant);
		_timer->scheduleRepeated(reaper, IceUtil::Time::seconds(timeout));


		_adapter = communicator()->createObjectAdapter(prop->getProperty("IdentityAdapter"));

		// get conencted tracker interface
		LbaNet::ConnectedTrackerPrx ctracker = LbaNet::ConnectedTrackerPrx::checkedCast(communicator()->stringToProxy(
																		prop->getProperty("ConnectedTracker")));



		// join chat world channel
		LbaNet::ChatRoomObserverPrx proxyChat;
		proxyChat = LbaNet::ChatRoomObserverPrx::uncheckedCast(_adapter->addWithUUID(chatservant));

		LbaNet::RoomManagerPrx roomM = LbaNet::RoomManagerPrx::checkedCast(communicator()->stringToProxy(
																			prop->getProperty("RoomManager")));
		LbaNet::ChatRoomObserverPrx chatobs = roomM->JoinChat("World", proxyChat);

		// create session manager
		ChatSessionManagerServant * smanager = 
						new ChatSessionManagerServant(reaper, chatobs, chatservant, ctracker);				
		reaper->SetCallback(smanager);
		_adapter->add(smanager, communicator()->stringToIdentity(prop->getProperty("SessionServantName")));

		// activate server
		_adapter->activate();

		// set web whisper
		ctracker->SetWebWisperInterface(proxyChat);

		communicator()->waitForShutdown();

		return EXIT_SUCCESS;
	}

private:
	Ice::ObjectAdapterPtr _adapter;
	IceUtil::TimerPtr _timer;
};


int main(int argc, char** argv)
{
    PollingChatServer app;
    return app.main(argc, argv/*, "config"*/);
}

