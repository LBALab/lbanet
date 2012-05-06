#ifndef ROOM_MANAGER_ICE
#define ROOM_MANAGER_ICE

#include <LbaTypes.ice>
#include <ChatInfo.ice>

[["java:package:net.lbanet.generated"]]
module LbaNet
{
	interface ConnectedTracker
	{	
		// return the id of the player
		long Connect(string Nickname);
		void Disconnect(long PlayerId);
		void ChangeStatus(string Nickname, string NewStatus);
		void ChangeNameColor(string Nickname, string Color);	
		void ChangeLocation(string Nickname, string Location);	
		
		void SetWebWisperInterface(ChatRoomObserver * winterface);
		void ConnectFromWebChat(string Nickname);
		void DisconnectFromWebChat(string Nickname);	

		ConnectedL GetConnected();
		
		void SetWhisperInterface(string Nickname, ChatRoomObserver * winterface);
		bool Whisper(string From, string To, string Message);
		
		bool IsWorldAdmin(long PlayerId, string Worldname);
	};

};

#endif

