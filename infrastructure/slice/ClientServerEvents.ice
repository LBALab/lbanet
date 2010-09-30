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
		ModelStance		NewStance;
	};
	
	// server send - player enter in a map
	class PlayerEnterEvent extends ClientServerEventBase
	{
		long			PlayerId;
	};
	
	
	// server send - player leave a map
	class PlayerLeaveEvent extends ClientServerEventBase
	{
		long			PlayerId;
	};
	
	
	// server tell client to add object
	class AddObjectEvent extends ClientServerEventBase
	{
		ObjectTypeEnum		TypeO;
		long			ObjectId;
		ModelInfo		DisplayDesc;
		ObjectPhysicDesc	PhysicDesc;
		LifeManaInfo		LifeInfo;
		ObjectExtraInfo		ExtraInfo;
	};
	
	
	// server tell client to remove object
	class RemoveObjectEvent extends ClientServerEventBase
	{
		ObjectTypeEnum		TypeO;
		long			ObjectId;
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
	
	
	// client/server inform other that a player moved
	class PlayerMovedEvent extends ClientServerEventBase
	{
		long			PlayerId;
		PlayerMoveInfo		info;
	};
	
	
	// server inform client that a enters a new map
	class NewMapEvent extends ClientServerEventBase
	{
		string			MapName;
		string			InitializationScript;
	};
	
	
	// client ask server to get a refresh of all object on the maps
	class RefreshObjectRequestEvent extends ClientServerEventBase
	{
	};
	
	// server tell client that map is fully refreshed
	class RefreshEndEvent extends ClientServerEventBase
	{
	};
	
	
	// server tell client to update the display of 1 object
	class UpdateDisplayObjectEvent extends ClientServerEventBase
	{
		ObjectTypeEnum			TypeO;
		long				ObjectId;
		DisplayObjectUpdateBase		Update;
	};	
	
	// client tell server that player state should be updated
	class UpdateStateEvent extends ClientServerEventBase
	{
		ModelState			NewState;
		float				FallingSize;
	};
	
	// client tell server that player should be raised from dead
	class RaiseFromDeadEvent extends ClientServerEventBase
	{
	};
	
};	

#endif

