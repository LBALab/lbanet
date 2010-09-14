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


#include "RoomManagerServant.h"


//! constructor
RoomManagerServant::RoomManagerServant(const Ice::CommunicatorPtr& communicator)
: _communicator(communicator)
{

}

//! the client join a chat room
ChatRoomObserverPrx RoomManagerServant::JoinChat(	const std::string& room,
														const ChatRoomObserverPrx& observer,
														const Ice::Current&)
{
	Lock sync(*this);

	// check if we already created this room
	std::map<std::string, IceStorm::TopicPrx>::const_iterator p = _chat_rooms.find(room);
	IceStorm::TopicPrx topic;


	// if not create the chat room
	if(p == _chat_rooms.end())
	{
		IceStorm::TopicManagerPrx manager;
		try
		{
			manager = IceStorm::TopicManagerPrx::uncheckedCast(
			_communicator->propertyToProxy("TopicManagerProxy"));
		}
		catch(const IceUtil::Exception& ex)
		{
			std::cout<<"Exception getting the topic manager: "<<ex.what()<<std::endl;
		}
		catch(...)
		{
			std::cout<<"Unknown exception getting the topic manager. "<<std::endl;
		}

		try
		{
			topic = manager->create(room);
		}
		catch(const IceStorm::TopicExists&)
		{
			topic = manager->retrieve(room);
		}
		catch(const IceUtil::Exception& ex)
		{
			std::cout<<"Exception creating topic "<<ex.what()<<std::endl;
		}
		catch(...)
		{
			std::cout<<"Unknown exception creating topic. "<<std::endl;
		}

		_chat_rooms.insert(make_pair(room, topic));
	}
	else
	{
		topic = p->second;
	}

	try
	{
		topic->subscribeAndGetPublisher(IceStorm::QoS(), observer);
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception subscribing "<<ex.what()<<std::endl;
	}
	catch(...)
	{
		std::cout<<"Unknown exception subscribing. "<<std::endl;
	}

	Ice::ObjectPrx pub;

	try
	{
		pub = topic->getPublisher();
		pub = pub->ice_oneway();
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception getting the publisher "<<ex.what()<<std::endl;
	}
	catch(...)
	{
		std::cout<<"Unknown exception getting the publisher. "<<std::endl;
	}

	//Ice::Context context;
	//context["_fwd"] = "Oz";
	return ChatRoomObserverPrx::uncheckedCast(pub/*->ice_context(context)*/);
}



//! the client leave a chat room
void RoomManagerServant::LeaveChat(	const std::string& room, const ChatRoomObserverPrx& observer,
										const Ice::Current&)
{
	Lock sync(*this);

	try
	{
		std::map<std::string, IceStorm::TopicPrx>::iterator p = _chat_rooms.find(room);
		if(p != _chat_rooms.end())
		{
			p->second->unsubscribe(observer);
		}
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception unsubscribing "<<ex.what()<<std::endl;
	}
	catch(...)
	{
		std::cout<<"Unknown exception unsubscribing. "<<std::endl;
	}
}


