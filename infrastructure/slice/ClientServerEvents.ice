#ifndef LBANET_CLIENT_SERVER_EVENTS
#define LBANET_CLIENT_SERVER_EVENTS

#include <LbaTypes.ice>

module LbaNet
{
	// base class for all event exchanged between client and server
	class ClientServerEventBase 
	{
	    	double			Time;
	};
	
		
	sequence<ClientServerEventBase> EventsSeq;	
	
	
	// server send his id to the client
	class ClientIdEvent extends ClientServerEventBase
	{
		long			Id;
	};
	
	
	// server send list of available worlds to client
	class AvailableWorldsEvent extends ClientServerEventBase
	{
		WorldsSeq		Worlds;
	};
	
	
	
	// server ask client to refresh a certain GUI in game
	class RefreshGameGUIEvent extends ClientServerEventBase
	{
		string			GUIId;
		GuiParamsSeq		Parameters;
		bool			Show;	// will display GUI if true
		bool			Hide;	// will hide GUI if true
	};
	

	// client/server update something in part of the GUI
	class UpdateGameGUIEvent extends ClientServerEventBase
	{
		string			GUIId;
		GuiUpdatesSeq		Updates;
	};	

	// client ask server to be teleported
	class TeleportEvent extends ClientServerEventBase
	{
		string			TeleportId;
	};
	
	// client/server tell the other to change stance
	class ChangeStanceEvent extends ClientServerEventBase
	{
		int			NewStanceId;
	};
	
	// player enter in a map
	class PlayerEnterEvent extends ClientServerEventBase
	{
		long			PlayerId;
	};
	
	
	// player leave a map
	class PlayerLeaveEvent extends ClientServerEventBase
	{
		long			PlayerId;
	};
	
	
	// server tell client to add object
	class AddObjectEvent extends ClientServerEventBase
	{
		// 1 -> static object
		// 2 -> cpu controlled
		// 3 -> movable by player
		// 4 -> player object
		// 5 -> ghost object
		int			Type;
		long			ObjectId;
		ModelInfo		DisplayDesc;
		ObjectPhysicDesc	PhysicDesc;		
	};
	
	
	// server tell client to remove object
	class RemoveObjectEvent extends ClientServerEventBase
	{
		int			Type;
		long			ObjectId;
	};
	
	
	// server tell client to update object
	class UpdateObjectDisplayEvent extends ClientServerEventBase
	{
		int			Type;
		long			ObjectId;
		ModelInfo		DisplayDesc;
	};
	
	
	// server tell client to update object
	class UpdateObjectPhysicEvent extends ClientServerEventBase
	{
		int			Type;
		long			ObjectId;
		ObjectPhysicDesc	PhysicDesc;
	};
	
	
	// client tell server that he pressed action key
	class PressedActionKeyEvent extends ClientServerEventBase
	{
		bool			ForcedNormalAction;
	};
	
	
	// client tell server that he pressed weapon key
	class PressedWeaponKeyEvent extends ClientServerEventBase
	{
	};
	

};	

#endif

