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
		int			TypeO;
		long			ObjectId;
		long			OwnerId;		
		ModelInfo		DisplayDesc;
		ObjectPhysicDesc	PhysicDesc;
		LifeManaInfo		LifeInfo;
		ObjectExtraInfo		ExtraInfo;
	};
	
	
	// server tell client to remove object
	class RemoveObjectEvent extends ClientServerEventBase
	{
		int			TypeO;
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
		
		string			MusicPath;
		int			RepeatMusic;		
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
		int				TypeO;
		long				ObjectId;
		DisplayObjectUpdateBase		Update;
	};	
	
	// server tell client to update the display of 1 object
	class UpdatePhysicObjectEvent extends ClientServerEventBase
	{
		int				TypeO;
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
	
	
	// server inform other that a npc moved
	class NpcAttachActorEvent extends ClientServerEventBase
	{
		long			NpcId;	
	
		int 			AttachedType;
		long 			AttachedId;	
	};	
	
	
	
	// server send signal to client's player
	class SendSignalEvent extends ClientServerEventBase
	{
		int 				SignalId;
	};
	
	
	
	// server tell client to update the display of 1 object
	class ShowHideEvent extends ClientServerEventBase
	{
		int				TypeO;
		long				ObjectId;
		bool				Show;
	};	
	
		
	// server send target to client
	class NpcTargetPlayerEvent extends ClientServerEventBase
	{
		long 				NpcId;
		long 				PlayerId;		
	};
		
	// server send target to client
	class NpcUnTargetPlayerEvent extends ClientServerEventBase
	{
		long 				NpcId;

	};	
	
	
	
	// client ask server to get a refresh of all tps
	class RefreshTpRequestEvent extends ClientServerEventBase
	{
	};
	
	
	// server tell client to cut the map with a clip plane on the Y axis
	class CutMapEvent extends ClientServerEventBase
	{
		float				Y;
	};
	
	
	// server tell client to create projectile
	class CreateProjectileEvent extends ClientServerEventBase
	{
		ProjectileInfo			Info;
	};
	
	// server tell client to destroy projectile
	class ProjectileHittedActorEvent extends ClientServerEventBase
	{
		long			Id;

		int			TouchedActorType;
		long			TouchedActorId;
	};
	
	// server tell client to destroy projectile
	class DestroyProjectileEvent extends ClientServerEventBase
	{
		long			Id;

		int			TouchedActorType;
		long			TouchedActorId;
	};
	
	// client tell server to update player color
	class UpdatePlayerColorEvent extends ClientServerEventBase
	{
		int			SkinColor;
		int			EyesColor;
		int			HairColor;
	};
	
	// client tell server he hitted an actor
	class PlayerHittedContactActorEvent extends ClientServerEventBase
	{
		bool			WithWeapon;

		int			TouchedActorType;
		long			TouchedActorId;
	};


	// client/server inform other that a NPC moved
	class NPCMovedEvent extends ClientServerEventBase
	{
		long			ActorId;
		PlayerMoveInfo		info;
	};	
	
	// client/server inform other that a ghost moved
	class GhostMovedEvent extends ClientServerEventBase
	{
		long			GhostId;
		PlayerMoveInfo		info;
	};
	
	// client inform server that it loot an item
	class ItemLootEvent extends ClientServerEventBase
	{
		long			ItemId;
	};
	
	// client inform server that it loot an item
	class PlaySoundEvent extends ClientServerEventBase
	{
		SoundInfo		Sound;
	};
		
};	

#endif

