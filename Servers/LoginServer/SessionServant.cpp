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


#include "SessionServant.h"
#include <IceUtil/UUID.h>
#include <Ice/Ice.h>
#include "SynchronizedTimeHandler.h"
#include <ClientServerEvents.h>
#include "AvailableWorldsHandler.h"

#include <stdlib.h>

/***********************************************************
constructor
***********************************************************/
SessionServant::SessionServant(const std::string& userId, const RoomManagerPrx& manager,
					const ConnectedTrackerPrx& ctracker, std::string version,
					const Ice::CommunicatorPtr& communicator)
: _userName(userId), _manager(manager), _ctracker(ctracker),
	_userNumber(-1), _version(version), _currColor("FFFFFFFF"), _currentWorld(NULL),
	_communicator(communicator)
{
	try
	{
		_userNumber = _ctracker->Connect(_userName);
		_currextrainfo.Name = _userName;
		_currextrainfo.NameColorR = 1.0;
		_currextrainfo.NameColorG = 1.0;
		_currextrainfo.NameColorB = 1.0;
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during Connect: "<< ex.what()<<std::endl;
		_userNumber = -1;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during Connect"<<std::endl;
		_userNumber = -1;
    }
}




/***********************************************************
destroy the session
***********************************************************/
void SessionServant::destroy(const Ice::Current& current)
{
    Lock sync(*this);
	try
	{
		QuitCurrentWorld();
		_ctracker->Disconnect(_userNumber);
	}
	catch(...)
	{
		// Ignore. The ice mediated invocation can throw an
		// exception on shutdown.
	}

	std::map<std::string, ChatRoomParticipantPrx>::iterator worldit = _chat_rooms.find("World");
	if(worldit != _chat_rooms.end())
	{
		try
		{
			worldit->second->Say("info", "#left " + _userName);
		}
		catch(...)
		{
			// Ignore. The ice mediated invocation can throw an
			// exception on shutdown.
		}
	}

	try
	{
		current.adapter->remove(current.id);
	}
	catch(...)
	{
		// Ignore. The ice mediated invocation can throw an
		// exception on shutdown.
	}

	for(std::map<std::string, ChatRoomParticipantPrx>::const_iterator p = _chat_rooms.begin(); p != _chat_rooms.end(); ++p)
	{
		try
		{
			current.adapter->remove(p->second->ice_getIdentity());
		}
		catch(...)
		{
			// Ignore. The ice mediated invocation can throw an
			// exception on shutdown.
		}
	}

	try
	{
		_chat_rooms.clear();
	}
	catch(...)
	{
		// Ignore. The ice mediated invocation can throw an
		// exception on shutdown.
	}
}


/***********************************************************
inform connected world that player left
***********************************************************/
void SessionServant::QuitCurrentWorld()
{
	try
	{
		if(_currentWorld)
			_currentWorld->UnregisterClient(_userNumber);
	}
	catch(...)
	{
		// Ignore. The ice mediated invocation can throw an
		// exception on shutdown.
	}

	_currentWorld = NULL;
	_currWorldName = "";
}






/***********************************************************
client send interface to server
***********************************************************/
void SessionServant::SetClientInterface(const ClientInterfacePrx& winterface, const Ice::Current&)
{
    Lock sync(*this);
	_client = winterface;

	try
	{
		// send primary infos to clients
		EventsSeq seq;

		//send player id
		seq.push_back(new ClientIdEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), _userNumber));

		//send list of connected players
		GuiParamsSeq params;
		GuiUpdatesSeq upds;
		PlayerOnlinesSeq onlineps;
		{
			ConnectedL connectedlist = _ctracker->GetConnected();
			ConnectedL::iterator it = connectedlist.begin();
			ConnectedL::iterator end = connectedlist.end();
			for(; it != end; ++it)
			{
				PlayerOnline po;
				po.Joined = true;
				po.Nickname = it->first;
				po.Color = it->second.NameColor;
				po.Status = it->second.Status;
				po.Location = it->second.Location;

				onlineps.push_back(po);

				upds.push_back(new LbaNet::NameColorChangedUpdate(it->first, it->second.NameColor));
			}
		}
		params.push_back(new PlayerOnlineListGuiParameter(onlineps));
		seq.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
										"CommunityBox", params, false, false));

		seq.push_back(new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
										"ChatBox", upds));



		_client->ServerEvents(seq);
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during SetClientInterface: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during SetClientInterface"<<std::endl;
    }

}

/***********************************************************
client send events to server
***********************************************************/
void SessionServant::ClientEvents(const EventsSeq& evts, const Ice::Current&)
{
    Lock sync(*this);

	try
	{
		if(_currentWorld)
			_currentWorld->ClientEvents(_userNumber, evts);

		return;
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during ClientEvents: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during ClientEvents"<<std::endl;
    }


	// something wrong happened with world server - clean up
	_currentWorld = NULL;
	_currWorldName = "";

	//inform client
	try
	{
		EventsSeq seq;
		GuiUpdatesSeq upds;
		upds.push_back(new SystemMessageUpdate("World connection lost", "Connection has been lost with world server. Trying changing world to reconnect."));
		seq.push_back(new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
										"main", upds));

		_client->ServerEvents(seq);
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during inform client: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during inform client"<<std::endl;
    }
}


/***********************************************************
client ask server to change world
***********************************************************/
void SessionServant::ChangeWorld(const std::string& WorldName, const Ice::Current&)
{
    Lock sync(*this);

	if(_currWorldName == WorldName)
		return;

	// first quit old world
	QuitCurrentWorld();


	// then connect to new world
	_currentWorld = AvailableWorldsHandler::getInstance()->GetWorldProxy(WorldName);
	try
	{
		if(_currentWorld)
		{
			_currentWorld->RegisterClient(_userNumber, _client, _currextrainfo);
			_currWorldName = WorldName;
		}
		else
		{
			// inform client world is not reachable
			EventsSeq seq;
			GuiUpdatesSeq upds;
			upds.push_back(new SystemMessageUpdate("World server unreachable", "The server for the chosen world is not reachable. Try to conenct to another world."));
			seq.push_back(new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
											"main", upds));

			_client->ServerEvents(seq);
		}
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during ChangeWorld for client "<<_userNumber<<": "<< ex.what()<<std::endl;

		try
		{
			// inform client world is not reachable
			EventsSeq seq;
			GuiUpdatesSeq upds;
			upds.push_back(new SystemMessageUpdate("World server unreachable", std::string("Problem connecting to the world server:")+ex.what()));
			seq.push_back(new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
											"main", upds));

			_client->ServerEvents(seq);
		}
		catch(...){}
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during ChangeWorld"<<std::endl;
    }
}





/***********************************************************
the client join a chat room
***********************************************************/
ChatRoomParticipantPrx SessionServant::JoinChatChannel(	const std::string& room,
														const ChatRoomObserverPrx& observer,
														const Ice::Current& current)
{
    Lock sync(*this);

	std::map<std::string, ChatRoomParticipantPrx>::iterator it = _chat_rooms.find(room);
	if(it != _chat_rooms.end())
		return it->second;

	try
	{
		Ice::Identity id;
		id.category = "_" + _userName;
		id.name = IceUtil::generateUUID();

		ChatParticipantServant * cptr = new ChatParticipantServant(room, observer, _manager);
		ChatRoomParticipantPrx proxy = ChatRoomParticipantPrx::uncheckedCast(current.adapter->add(cptr, id));

		if(room == "World")
		{
			proxy->Say("info", "#joined " +_userName);
		}

		_chat_rooms[room] = proxy;
		return proxy;
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during JoinChatChannel: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during JoinChatChannel"<<std::endl;
    }

	return NULL;
}


/***********************************************************
the client leave a chat room
***********************************************************/
void SessionServant::LeaveChatChannel(	const std::string& room, const ChatRoomObserverPrx& observer,
										const Ice::Current& current)
{
    Lock sync(*this);
	try
	{
		std::map<std::string, ChatRoomParticipantPrx>::iterator it = _chat_rooms.find(room);
		if(it != _chat_rooms.end())
		{
			if(room == "World")
			{
				it->second->Say("info", "#left " + _userName);
				_ctracker->Disconnect(_userNumber);
			}

			current.adapter->remove(it->second->ice_getIdentity());
			_chat_rooms.erase(it);
		}
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during LeaveChatChannel: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during LeaveChatChannel"<<std::endl;
    }
}




/***********************************************************
change player status
***********************************************************/
void SessionServant::ChangeStatus(const std::string& Status, const Ice::Current&)
{
    Lock sync(*this);
	try
	{
		_currStatus = Status;
		_ctracker->ChangeStatus(_userName, Status);

		std::map<std::string, ChatRoomParticipantPrx>::iterator worldit = _chat_rooms.find("World");
		if(worldit != _chat_rooms.end())
		{
			worldit->second->Say("info", "#status " + _userName + " " + Status + " " + _currColor + " " + _currLocation);
		}
	}
	catch(...)
	{
		// Ignore. The ice mediated invocation can throw an
		// exception on shutdown.
	}
}


/***********************************************************
change name display color
***********************************************************/
void SessionServant::ChangeNameColor(const std::string& Color, const Ice::Current&)
{
    Lock sync(*this);
	try
	{
		_currColor = Color;
		_ctracker->ChangeNameColor(_userName, Color);

		int cR = 0;
		std::stringstream cRss;
		cRss << std::hex << Color.substr(2, 2);
		cRss >> cR;

		int cG = 0;
		std::stringstream cGss;
		cGss << std::hex << Color.substr(4, 2);
		cGss >> cG;

		int cB = 0;
		std::stringstream cBss;
		cBss << std::hex << Color.substr(6, 2);
		cBss >> cB;

		_currextrainfo.NameColorR = cR / 255.0f;
		_currextrainfo.NameColorG = cG / 255.0f;
		_currextrainfo.NameColorB = cB / 255.0f;
		_currextrainfo.Display = true;

		std::map<std::string, ChatRoomParticipantPrx>::iterator worldit = _chat_rooms.find("World");
		if(worldit != _chat_rooms.end())
		{
			worldit->second->Say("info", "#status " + _userName + " " + _currStatus + " " + Color + " " + _currLocation);
		}


		if(_currentWorld)
			_currentWorld->UpdateClientInfo(_userNumber, _currextrainfo);
	}
	catch(...)
	{
		// Ignore. The ice mediated invocation can throw an
		// exception on shutdown.
	}
}



/***********************************************************
change player status
***********************************************************/
void SessionServant::ChangeLocation(const std::string& Location, const Ice::Current&)
{
    Lock sync(*this);
	try
	{
		_currLocation = Location;
		_ctracker->ChangeLocation(_userName, Location);

		std::map<std::string, ChatRoomParticipantPrx>::iterator worldit = _chat_rooms.find("World");
		if(worldit != _chat_rooms.end())
		{
			worldit->second->Say("info", "#status " + _userName + " " + _currStatus + " " + _currColor + " " + _currLocation);
		}
	}
	catch(...)
	{
		// Ignore. The ice mediated invocation can throw an
		// exception on shutdown.
	}
}




/***********************************************************
get server version
***********************************************************/
std::string SessionServant::GetVersion(const Ice::Current&)
{
    Lock sync(*this);
	return _version;
}




/***********************************************************
set player wisper interface
***********************************************************/
void SessionServant::SetWhisperInterface(const LbaNet::ChatRoomObserverPrx& winterface, const Ice::Current&)
{
	try
	{
		if(_ctracker)
			_ctracker->SetWhisperInterface(_userName, winterface);
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during SetWhisperInterface: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during SetWhisperInterface"<<std::endl;
    }
}

/***********************************************************
a player wisper to another
***********************************************************/
bool SessionServant::Whisper(const std::string& To, const std::string& Message, const ::Ice::Current&)
{
	try
	{
		if(_ctracker)
			return _ctracker->Whisper(_userName, To, Message);
		else
			return false;
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during Whisper: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during Whisper"<<std::endl;
    }

	return false;
}



/***********************************************************
client ask to get the list of world available
***********************************************************/
void SessionServant::GetWorldList(const ::Ice::Current&)
{
    Lock sync(*this);

	try
	{
		// send infos to clients
		EventsSeq seq;

		//send list of available worlds
		WorldsSeq ws = AvailableWorldsHandler::getInstance()->GetWorldList();
		seq.push_back(new AvailableWorldsEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), ws));

		_client->ServerEvents(seq);
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during GetWorldList: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during GetWorldList"<<std::endl;
    }
}

	
/***********************************************************
return the patcher for a given world
***********************************************************/
IcePatch2::FileServerPrx SessionServant::GetPatcher(const std::string & worldName, const Ice::Current &)
{
	try
	{
		return IcePatch2::FileServerPrx::checkedCast(_communicator->stringToProxy(worldName+"Patch/server"));
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during GetPatcher: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during GetPatcher"<<std::endl;
    }

	return IcePatch2::FileServerPrx();
}

/***********************************************************
called in order to shutdown the world server, update the world data, then restart the server
***********************************************************/
std::string SessionServant::UpdateWorld(const std::string & WorldName, const Ice::Current &)
{
	try
	{
		if(_ctracker && _ctracker->IsWorldAdmin(_userNumber, WorldName))
		{
			if(AvailableWorldsHandler::getInstance()->ShutdownWorldServer(WorldName))
			{
				//TODO
				return "OK";
			}
			else
			{
				return "Error: not able to contact server for world: " + WorldName;
			}
		}
		else
		{
			return "Error: you are not authorized to update the world: " + WorldName;
		}
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during UpdateWorld: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during UpdateWorld"<<std::endl;
    }

	return "Error: exception when updating world: " + WorldName;	
}

	
/***********************************************************
start server for world if not yet started
***********************************************************/
std::string SessionServant::StartWorld(const std::string & WorldName, const Ice::Current &)
{
	try
	{
		if(_ctracker && _ctracker->IsWorldAdmin(_userNumber, WorldName))
		{
			if(AvailableWorldsHandler::getInstance()->ServerStarted(WorldName))
			{
				return "Error: server already started for world: " + WorldName;
			}
			else
			{
				if(system(("icegridadmin --Ice.Config=config.grid -e \"server start WorldServer-"+WorldName+"\"").c_str()))
					return "OK";
				else
					return "Error starting world: " + WorldName;
			}
		}
		else
		{
			return "Error: you are not authorized to update the world: " + WorldName;
		}
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during UpdateWorld: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during UpdateWorld"<<std::endl;
    }

	return "Error: exception when updating world: " + WorldName;
}

/***********************************************************
stop server for world if started
***********************************************************/
std::string SessionServant::ShutdownWorld(const std::string & WorldName, const Ice::Current &)
{
	try
	{
		if(_ctracker && _ctracker->IsWorldAdmin(_userNumber, WorldName))
		{
			if(AvailableWorldsHandler::getInstance()->ShutdownWorldServer(WorldName))
			{
				return "OK";
			}
			else
			{
				return "Error: not able to contact server for world: " + WorldName;
			}
		}
		else
		{
			return "Error: you are not authorized to update the world: " + WorldName;
		}
	}
    catch(const IceUtil::Exception& ex)
    {
		std::cout<<"SessionServant - Exception during UpdateWorld: "<< ex.what()<<std::endl;
    }
    catch(...)
    {
		std::cout<<"SessionServant - Unknown exception during UpdateWorld"<<std::endl;
    }

	return "Error: exception when updating world: " + WorldName;
}
	
/***********************************************************
check if server is started or not
***********************************************************/
bool SessionServant::GetWorldStatus(const std::string & WorldName, const Ice::Current &)
{
	return AvailableWorldsHandler::getInstance()->ServerStarted(WorldName);
}	