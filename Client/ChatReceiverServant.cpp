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

#include "ChatReceiverServant.h"
#include "ChatBox.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "ClientExtendedEvents.h"
#include "ClientExtendedTypes.h"


// callback function called when a message is received from IceStorm
void ChatReceiverServant::Message(const std::string& Sender, const std::string& Text, const Ice::Current&)
{
	if(Sender == "info")
	{
		if(Text.substr(0, 7) == "#joined")
		{
			LbaNet::PlayerOnline ev;
			ev.Joined = true;
			ev.Nickname = Text.substr(8);
			ev.Color = "FFFFFFFF";

			LbaNet::GuiUpdatesSeq updseq;
			LbaNet::PlayerStatusChanged * upd = 
				new LbaNet::PlayerStatusChanged(ev);
			updseq.push_back(upd);
			EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
				SynchronizedTimeHandler::GetCurrentTimeDouble(), "CommunityBox", updseq));
			return;
		}

		if(Text.substr(0, 5) == "#left")
		{
			LbaNet::PlayerOnline ev;
			ev.Joined = false;
			ev.Nickname = Text.substr(6);

			LbaNet::GuiUpdatesSeq updseq;
			LbaNet::PlayerStatusChanged * upd = 
				new LbaNet::PlayerStatusChanged(ev);
			updseq.push_back(upd);
			EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
				SynchronizedTimeHandler::GetCurrentTimeDouble(), "CommunityBox", updseq));
			return;
		}

		if(Text.substr(0, 7) == "#status")
		{	
			std::string tmptxt = Text.substr(8);
			std::string Nickname = tmptxt.substr(0, tmptxt.find(" "));
			tmptxt = tmptxt.substr(tmptxt.find(" ")+1);
			std::string Status = tmptxt.substr(0, tmptxt.find(" "));
			tmptxt = tmptxt.substr(tmptxt.find(" ")+1);
			std::string Color = tmptxt.substr(0, tmptxt.find(" "));
			tmptxt = tmptxt.substr(tmptxt.find(" ")+1);
			std::string Location = tmptxt;
			EventsQueue::getReceiverQueue()->AddEvent(new PlayerStatusUpdateEvent(Nickname, Status, Color, Location));
			return;
		}

	}

	// remove name from whisper
	std::string message = Text;
	if(message[0] == '/')
	{
		std::vector<std::string> tok;
		std::stringstream ss(message);
		std::string buf;
		while(ss >> buf)
		{
			tok.push_back(buf);
		}

		if(tok.size() > 1)
		{
			message = "";
			for(size_t i=1; i<tok.size(); ++i)
				message += tok[i] + " ";
		}
	}


	// send message to chatbox
	LbaNet::GuiUpdatesSeq updseq;
	LbaNet::ChatTextUpdate * upd = 
		new LbaNet::ChatTextUpdate(_RoomName, Sender, message);
	updseq.push_back(upd);
	EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));
}

