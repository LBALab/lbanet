#ifndef LBANET_CHAT_INFO
#define LBANET_CHAT_INFO

[["java:package:net.lbanet.generated"]]
module LbaNet
{
	interface ChatRoomObserver
	{
	    void Message(string Sender, string data);
	};
	
	interface ChatRoomParticipant
	{
	    void Say(string Sender, string data);
	};	
};

#endif

