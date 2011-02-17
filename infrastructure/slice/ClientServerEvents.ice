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
		long			TeleportId;
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
		
		// indicate if the server teleport the player
		bool			ServerTeleport;	
	};
	
	
	// server inform client that a enters a new map
	class NewMapEvent extends ClientServerEventBase
	{
		string			MapName;
		string			InitializationScript;
		int			AutoCameraType;
	};
	
	
	// client ask server to get a refresh of all object on the maps
	class RefreshObjectRequestEvent extends ClientServerEventBase
	{
	};
	
	// server tell client that map is fully refreshed
	class RefreshEndEvent extends ClientServerEventBase
	{
	};
	
	// client tell server that he is ready to play
	class ReadyToPlayEvent extends ClientServerEventBase
	{
	};	
	
	// server tell client to update the display of 1 object
	class UpdateDisplayObjectEvent extends ClientServerEventBase
	{
		ObjectTypeEnum			TypeO;
		long				ObjectId;
		DisplayObjectUpdateBase		Update;
	};	
	
	// server tell client to update the display of 1 object
	class UpdatePhysicObjectEvent extends ClientServerEventBase
	{
		ObjectTypeEnum			TypeO;
		long				ObjectId;
		PhysicObjectUpdateBase		Update;
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
	
	// server tell server that client updated extra info
	class NewClientExtraInfoEvent extends ClientServerEventBase
	{
		ObjectExtraInfo 		ExtraInfo;
	};	
	
	
	// server tell client to execute lua script
	class StartClientScriptEvent extends ClientServerEventBase
	{
		string 				ScriptName;
		bool				InlineFunction;	
	};
	
	// client tell server that script is finished
	class ScriptExecutionFinishedEvent extends ClientServerEventBase
	{
		string 				ScriptName;
	};
	
	
	// server tell client to execute lua script
	class ClientExecuteScriptStringEvent extends ClientServerEventBase
	{
		string 				ScriptString;
	};
	
	
	// client tell server that an item has been used
	class PlayerItemUsedEvent extends ClientServerEventBase
	{
		long 				ItemId;
	};
	
	
	
	// server inform other that a npc moved
	class NpcChangedEvent extends ClientServerEventBase
	{
		long			NpcId;
		float			CurrPosX;
		float			CurrPosY;
		float			CurrPosZ;
		float			CurrRotation;		
		string			CurrAnimation;
		
		bool			ResetPosition;
		bool			ResetRotation;	
		
		NpcUpdateBase		Update;
	};
	
	
	
	// server send signal to client's player
	class SendSignalEvent extends ClientServerEventBase
	{
		int 				SignalId;
	};
	
	
	
	// server tell client to update the display of 1 object
	class ShowHideEvent extends ClientServerEventBase
	{
		ObjectTypeEnum			TypeO;
		long				ObjectId;
		bool				Show;
	};	
	
		
	// server send target to client
	class NpcTargetPlayerEvent extends ClientServerEventBase
	{
		long 				NpcId;
		long 				PlayerId;		
	};
	
	
};	

#endif

