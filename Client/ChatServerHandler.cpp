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

#include "ChatServerHandler.h"
#include "ChatReceiverServant.h"
#include "LogHandler.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "ClientExtendedEvents.h"
#include "ClientExtendedTypes.h"

#include <cctype>
#include <Ice/Application.h>


#define _CHAT_THREAD_WAIT_TIME_	100


/***********************************************************
constructor
***********************************************************/
ChatServerHandler::ChatServerHandler()
: _Trunning(false)
{

}


/***********************************************************
destructor
***********************************************************/
ChatServerHandler::~ChatServerHandler()
{
	if(_thread)
	{
		_threadcontrol.join();
		_thread = NULL;
	}
}

/***********************************************************
initialize
***********************************************************/
void ChatServerHandler::Initialize(const std::string PlayerName,
								   const Ice::ObjectAdapterPtr& adapter,
									const LbaNet::ClientSessionPrx& session,
									const std::string& category)
{
	_adapter = adapter;
	_session = session;
	_category = category;
	_main_name = PlayerName;

	try
	{
		// add the whisper interface
		Ice::Identity id2;
		id2.name = "ChatObserver.Whisper";
		id2.category = _category;
		LbaNet::ChatRoomObserverPrx observer = LbaNet::ChatRoomObserverPrx::uncheckedCast(
		_adapter->add(new ChatReceiverServant("Whisper"), id2)->ice_oneway());
		_chat_observers.insert(std::make_pair("Whisper", observer));
		_session->SetWhisperInterface(observer);
	}
    catch(const IceUtil::Exception& ex)
    {
		LogHandler::getInstance()->LogToFile(std::string("Exception creating Actor observer: ") + ex.what());
    }
    catch(...)
    {
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception creating Actor observer. "));
    }


	// join world chat channel automatically
	JoinChatChannel("World");

	// create thread
	_thread = new RunThread(this);
	_threadcontrol = _thread->start();
}



/***********************************************************
disconnect from server
***********************************************************/
void ChatServerHandler::Disconnect()
{
	// stop thread
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	_Trunning = false;
	_main_name = "";
	_monitor.notifyAll();
}



/***********************************************************
find a chat room if we already joined
***********************************************************/
LbaNet::ChatRoomParticipantPrx ChatServerHandler::FindChatRoom(const std::string& room) const
{
	std::map<std::string, LbaNet::ChatRoomParticipantPrx>::const_iterator p = _chat_publishers.find(room);
	LbaNet::ChatRoomParticipantPrx r;
	if(p != _chat_publishers.end())
	{
		r = p->second;
	}
	else
	{
		std::string upercroom = room;
		upercroom[0] = std::toupper(upercroom[0]);

		p = _chat_publishers.find(upercroom);
		if(p != _chat_publishers.end())
		{
			r = p->second;
		}
	}
	return r;
}


/***********************************************************
join a chat channel
***********************************************************/
bool ChatServerHandler::JoinChatChannel(const std::string& roomName)
{
	bool succed = true;

	try
	{
		Ice::Identity id;
		id.name = "ChatObserver." + roomName;
		id.category = _category;
		LbaNet::ChatRoomObserverPrx observer = LbaNet::ChatRoomObserverPrx::uncheckedCast(
		_adapter->add(new ChatReceiverServant(roomName), id)->ice_oneway());

		LbaNet::ChatRoomParticipantPrx pub = _session->JoinChatChannel(roomName, observer);

		_chat_observers.insert(make_pair(roomName, observer));
		_chat_publishers.insert(make_pair(roomName, pub));
	}
    catch(const IceUtil::Exception& ex)
    {
		LogHandler::getInstance()->LogToFile(std::string("Exception entering chat room ") + ex.what());
		succed = false;
    }
    catch(...)
    {
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception entering chat room ") + roomName);
		succed = false;
    }

	return succed;
}


/***********************************************************
leave a chat channel
***********************************************************/
bool ChatServerHandler::LeaveChatChannel(const std::string& roomName)
{
	bool succed = true;

	try
	{
		std::map<std::string, LbaNet::ChatRoomObserverPrx>::iterator it = _chat_observers.find(roomName);
		if(it != _chat_observers.end())
		{
			_session->LeaveChatChannel(roomName, it->second);
			_adapter->remove(it->second->ice_getIdentity());
			_chat_observers.erase(roomName);
			_chat_publishers.erase(roomName);
		}
	}
    catch(const IceUtil::Exception& ex)
    {
		LogHandler::getInstance()->LogToFile(std::string("Exception leaving chat room ") + roomName + ex.what());
		succed = false;
    }
    catch(...)
    {
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception leaving chat room ") + roomName);
		succed = false;
    }

	return succed;
}



/***********************************************************
ChangeMap
***********************************************************/
void ChatServerHandler::ChangeMap(const std::string & NewWorld, const std::string & NewMap)
{
	// disconnect the old map chat channel
	if(_current_world != "" && _current_map != "")
		LeaveChatChannel(_current_world + "_" + _current_map);

	// connect to the new map channel
	JoinChatChannel(NewWorld + "_" + NewMap);

	_current_world = NewWorld;
	_current_map = NewMap;
}


/***********************************************************
process a line of text
***********************************************************/
void ChatServerHandler::ProcessText(const std::string & Text)
{
	// return if text is empty
	if(Text == "")
		return;

	// if it is a command - preproccess it
	if(Text[0] == '/')
	{
		std::vector<std::string> tok;
		std::stringstream ss(Text);
		std::string buf;
		while(ss >> buf)
		{
			tok.push_back(buf);
		}

		if(tok.size() > 0)
		{
			if(tok[0] == "/join")
			{
				if(tok.size() != 2)
				{
					LbaNet::GuiUpdatesSeq updseq;
					LbaNet::ChatTextUpdate * upd =
						new LbaNet::ChatTextUpdate("All", "info", "You need to specify a room to join.");
					updseq.push_back(upd);
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));
					return;
				}

				std::string roomName = tok[1];
				if(FindChatRoom(roomName))
				{
					LbaNet::GuiUpdatesSeq updseq;
					LbaNet::ChatTextUpdate * upd =
						new LbaNet::ChatTextUpdate("All", "info", "You already joined channel "+roomName);
					updseq.push_back(upd);
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));
					return;
				}

				JoinChatChannel(roomName);
				return;
			}

			if(tok[0] == "/leave")
			{
				if(tok.size() != 2)
				{
					LbaNet::GuiUpdatesSeq updseq;
					LbaNet::ChatTextUpdate * upd =
						new LbaNet::ChatTextUpdate("All", "info", "You need to specify a room to leave.");
					updseq.push_back(upd);
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));
					return;
				}

				std::string roomName = tok[1];
				LeaveChatChannel(roomName);
				return;
			}

			if(tok[0] == "/w")
			{
				if(tok.size() < 3)
				{
					LbaNet::GuiUpdatesSeq updseq;
					LbaNet::ChatTextUpdate * upd =
						new LbaNet::ChatTextUpdate("All", "info", "Incorrect command.");
					updseq.push_back(upd);
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));
					return;
				}

				std::string playername = tok[1];
				std::string message;
				for(size_t i=2; i<tok.size(); ++i)
					message += tok[i] + " ";

				if(!Whisper(playername, message))
				{
					LbaNet::GuiUpdatesSeq updseq;
					LbaNet::ChatTextUpdate * upd =
						new LbaNet::ChatTextUpdate("All", "info", "The player " + playername + " is not available.");
					updseq.push_back(upd);
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));
				}
				else
				{
					LbaNet::GuiUpdatesSeq updseq;
					updseq.push_back(
						new LbaNet::ChatTextUpdate("All", "to " + playername, message));

					updseq.push_back(new AddWhisperChanelUpdate(playername));

					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));
				}
				return;
			}

			if(tok[0] == "/afk")
			{
				ChangeStatus("away");
				return;
			}

			if(tok[0] == "/back")
			{
				ChangeStatus("");
				return;
			}

			LbaNet::ChatRoomParticipantPrx room = FindChatRoom(tok[0].substr(1));
			if(room)
			{
				SendChat(room, Text.substr(Text.find_first_of(' ')+1));
				return;
			}
			else
			{
					LbaNet::GuiUpdatesSeq updseq;
					LbaNet::ChatTextUpdate * upd =
						new LbaNet::ChatTextUpdate("All", "info", "Incorrect command: " + tok[0]);
					updseq.push_back(upd);
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));
				return;
			}
		}
	}
	else
	{
		LbaNet::ChatRoomParticipantPrx room = FindChatRoom(_current_world + "_" + _current_map);
		if(room)
			SendChat(room, Text);
	}
}



/***********************************************************
send chat to room
***********************************************************/
void ChatServerHandler::SendChat(LbaNet::ChatRoomParticipantPrx room, const std::string & Text)
{
	try
	{
		room->Say(_main_name, Text);
	}
    catch(const IceUtil::Exception& ex)
    {
		LogHandler::getInstance()->LogToFile(std::string("Exception on SendChat: ") + ex.what());
    }
    catch(...)
    {
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception on SendChat"));
    }
}


/***********************************************************
change status
***********************************************************/
void ChatServerHandler::ChangeStatus(const std::string & NewStatus)
{
	try
	{
		_session->ChangeStatus(NewStatus);
	}
    catch(const IceUtil::Exception& ex)
    {
		LogHandler::getInstance()->LogToFile(std::string("Exception on ChangeStatus: ") + ex.what());
    }
    catch(...)
    {
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception on ChangeStatus"));
    }
}



/***********************************************************
change name color
***********************************************************/
void ChatServerHandler::ChangeNameColor(const std::string & Color)
{
	try
	{
		_session->ChangeNameColor(Color);
	}
    catch(const IceUtil::Exception& ex)
    {
		LogHandler::getInstance()->LogToFile(std::string("Exception on ChangeNameColor: ") + ex.what());
    }
    catch(...)
    {
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception on ChangeNameColor"));
    }
}


/***********************************************************
change status
***********************************************************/
void ChatServerHandler::ChangeLocation(const std::string & Location)
{
	try
	{
		_session->ChangeLocation(Location);
	}
    catch(const IceUtil::Exception& ex)
    {
		LogHandler::getInstance()->LogToFile(std::string("Exception on ChangeLocation: ") + ex.what());
    }
    catch(...)
    {
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception on ChangeLocation"));
    }
}



/***********************************************************
whisper to a player
***********************************************************/
bool ChatServerHandler::Whisper(const std::string & playername, const std::string & message)
{
	try
	{
		return _session->Whisper(playername, message);
	}
    catch(const IceUtil::Exception& ex)
    {
		LogHandler::getInstance()->LogToFile(std::string("Exception on ChangeStatus: ") + ex.what());
    }
    catch(...)
    {
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception on ChangeStatus"));
    }

	return false;
}



/***********************************************************
send chat text to server
***********************************************************/
void ChatServerHandler::SendChatText(const std::string & Text)
{
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	_texttoprocess.push_back(Text);
}



/***********************************************************
running function of the thread
***********************************************************/
void ChatServerHandler::run()
{
	// start thread for sending message to server
	IceUtil::Monitor<IceUtil::Mutex>::Lock lock(_monitor);
	_Trunning = true;

	while(_Trunning)
	{
		std::vector<std::string> texts;
		texts.swap(_texttoprocess);

		// process texts
		for(size_t i = 0; i < texts.size(); ++i)
			ProcessText(texts[i]);


		// wait for a few milliseconds
		IceUtil::Time t = IceUtil::Time::milliSeconds(_CHAT_THREAD_WAIT_TIME_);
		_monitor.timedWait(t);
	}
}
