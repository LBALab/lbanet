#ifndef ROOM_MANAGER_ICE
#define ROOM_MANAGER_ICE

#include <ChatInfo.ice>

module LbaNet
{
	interface RoomManager
	{
	    ChatRoomObserver* JoinChat(string room, ChatRoomObserver* view);
	    void LeaveChat(string room, ChatRoomObserver* view);   
	};

};

#endif

