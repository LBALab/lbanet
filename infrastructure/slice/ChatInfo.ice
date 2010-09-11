#ifndef LBANET_CHAT_INFO
#define LBANET_CHAT_INFO

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

