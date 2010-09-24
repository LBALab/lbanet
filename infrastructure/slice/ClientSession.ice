#ifndef CLIENT_SESSION_ICE
#define CLIENT_SESSION_ICE

#include <Glacier2/Session.ice>
#include <ClientServerEvents.ice>
#include <ChatInfo.ice>
#include <ClientInterface.ice>

module LbaNet
{
	interface ClientSession extends Glacier2::Session
	{
		// return the server version - used for client initialization
	 	string GetVersion();
	 	
	 	//client send interface to server
	 	void SetClientInterface(ClientInterface * winterface);
	 	
	 	//client send events to server
	 	void ClientEvents(EventsSeq evts);
	 	
	 	
	 	// client ask server to change world
	 	void ChangeWorld(string WorldName);
	 	
	 	// client ask to get the list of world available
	 	void GetWorldList();
	 	
	 	
	 	
	 	// chat management
	 	ChatRoomParticipant* JoinChatChannel(string room, ChatRoomObserver* view);
	    	void LeaveChatChannel(string room, ChatRoomObserver* view);
	    	
	    	// whisper management
	    	void SetWhisperInterface(ChatRoomObserver * winterface);
		bool Whisper(string To, string Message);    	
	    	
		// set status
		void ChangeStatus(string Status);
		void ChangeNameColor(string Color);    	
	};

};

#endif

