#include "WorldChatHandler.h"



/***********************************************************
constructor
***********************************************************/
WorldChatHandler::WorldChatHandler(Ice::CommunicatorPtr communicator)
: _channelpublisher(NULL)
{
	IceStorm::TopicManagerPrx manager = NULL;
	IceStorm::TopicPrx topic = NULL;
	try
	{
		manager = IceStorm::TopicManagerPrx::uncheckedCast(
		communicator->propertyToProxy("TopicManagerProxy"));
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception getting the topic manager: "<<ex.what()<<std::endl;
		return;
	}
	catch(...)
	{
		std::cout<<"Unknown exception getting the topic manager. "<<std::endl;
		return;
	}

	try
	{
		topic = manager->create("World");
	}
	catch(const IceStorm::TopicExists&)
	{
		topic = manager->retrieve("World");
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception creating topic "<<ex.what()<<std::endl;
		return;
	}
	catch(...)
	{
		std::cout<<"Unknown exception creating topic. "<<std::endl;
		return;
	}


	Ice::ObjectPrx pub = NULL;

	try
	{
		pub = topic->getPublisher();
		pub = pub->ice_oneway();
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception getting the publisher "<<ex.what()<<std::endl;
		return;
	}
	catch(...)
	{
		std::cout<<"Unknown exception getting the publisher. "<<std::endl;
		return;
	}

	try
	{
		_channelpublisher = LbaNet::ChatRoomObserverPrx::uncheckedCast(pub);
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception casting the publisher "<<ex.what()<<std::endl;
		return;
	}
	catch(...)
	{
		std::cout<<"Unknown exception casting the publisher. "<<std::endl;
		return;
	}

}

/***********************************************************
destructor
***********************************************************/
WorldChatHandler::~WorldChatHandler(void)
{
}



/***********************************************************
send a system message to world chat
***********************************************************/
void WorldChatHandler::SendSystemMessage(const std::string text)
{
	try
	{
		if(_channelpublisher)
			_channelpublisher->Message("System", text);
	}
	catch(const IceUtil::Exception& ex)
	{
		std::cout<<"Exception by SendSystemMessage "<<ex.what()<<std::endl;
		return;
	}
	catch(...)
	{
		std::cout<<"Unknown exception by SendSystemMessage. "<<std::endl;
		return;
	}
}