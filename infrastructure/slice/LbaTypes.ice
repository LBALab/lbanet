#ifndef LBANET_TYPES
#define LBANET_TYPES

module LbaNet
{
	// give information about a world
	struct WorldDesc
	{
		string 			WorldName;
		string 			Description;
		string 			News;
	};
	
	sequence<WorldDesc>		WorldsSeq;
	
	
	

	// teleport information
	struct TeleportInfo
	{
		string 			Name;
		string 			MapName;
		string 			SpawningName;
	};

	dictionary<string, TeleportInfo> ServerTeleportsSeq;
	sequence<string> 		TeleportsSeq;
	sequence<string> 		FilesSeq;


	// spawning information
	struct SpawningInfo
	{
		string 			Name;
		float 			PosX;
		float 			PosY;
		float 			PosZ;
		bool			ForceRotation;
		float 			Rotation;	
	};
	
	dictionary<string, SpawningInfo> SpawningsSeq;
	
	
	// map information
	struct MapInfo
	{
		string 			Name;
		string 			Description;
		string			Type;
		string 			ObjectFile;
		string			MusicFile;
		int			RepatMusic;
		
		SpawningsSeq 		Spawnings;

	};	
	dictionary<string, MapInfo> 	MapsSeq;


	struct PlayerStartingInfo
	{
		int			InventorySize;
		float			StartingLife;
		float			StartingMana;
		string			StartingMap;
		string			Spawning;
	};


	// give full information about a world
	struct WorldInformation
	{
		WorldDesc 		Description;
		ServerTeleportsSeq 	TeleportInfo;
		FilesSeq		FileUsedInfo;
		MapsSeq			Maps;
		
		PlayerStartingInfo	StartingInfo;
	};	
	
	
	
	
	
	
	// give information about a friend of a player
	struct FriendInfo
	{
		long 			Id;
		bool 			Pending;
		bool 			ToAccept;
		string 			Name;
		bool 			Removed;
	};
	
	sequence<FriendInfo> 		FriendsSeq;
	
	// give information about a private message received by player
	struct PMInfo
	{
		long 			PMId;
		long 			ReplyId;
		string 			FromName;
		string 			ToName;
		string 			Text;
		bool 			Opened;
		string 			Date;
	};
	
	sequence<PMInfo> 		PMsSeq;
	
	
	// give information about an item
	struct ItemInfo
	{
		long 			Id;
		string 			IconName;
		long 			DescriptionId;
		int 			Count;
		int 			Max;
		int 			Price;
		string 			DescriptionTextExtra;
		int 			Position;
	};
		
	// map an item with a position in display grid
	dictionary<long, ItemInfo> 	ItemsMap;
	
	dictionary<long, int> 		ItemList;
	
	
	// give information about a player status
	struct PlayerOnline
	{
		bool 			Joined;
		string 			Nickname;
		string 			Status;
		string 			Color;
	};
	
	sequence<PlayerOnline> 		PlayerOnlinesSeq;



	struct PlayerPosition
	{
		// actor name
		string			MapName;

		// actor coordinates
		float			X;
		float			Y;
		float			Z;
		float			Rotation;
	};
	
	
	struct InventoryItem
	{
		int 			Number;
		int 			PlaceInInventory;
	};
		
	dictionary<long, InventoryItem> InventoryMap;
	
	
	sequence<long> 			ShortcutsSeq;

	
	struct InventoryInfo
	{
		int 			InventorySize;
		InventoryMap 		InventoryStructure;
		ShortcutsSeq 		UsedShorcuts;
	};
	
	struct LifeManaInfo
	{
		float			CurrentLife;
		float			MaxLife;
		float			CurrentMana;
		float			MaxMana;
	};	
	
	
	struct SavedWorldInfo
	{
		PlayerPosition 		ppos;
		InventoryInfo 		inventory;
		
		// life/mana info
		LifeManaInfo		lifemana;
	};	
		
	
	
	
	
	// give information about a letter written by a player	
	struct LetterInfo
	{
		long 			LetterId;
		string 			Date;
		string 			From;
		string 			Subject;
		string 			Message;
	};
	
		
	// give information about a quest
	struct QuestInfo
	{
		long			Id;
		long 			ChapterTextId;		
		long 			QuestAreaTextId;	
		long	 		TittleTextId;
		long 			DescriptionTextId;
		
		bool			Visible;
	};
	
	dictionary<long, QuestInfo> 	QuestsMap;	
	
	
	// dialog part info
	sequence<long> 			PlayerChoicesSeq;	
	struct DialogPartInfo
	{
		long			NpcTextId;
		PlayerChoicesSeq 	PlayerTextsId;		
	};
	
	


	// player status information
	struct PlayerInfo
	{
		long 			Id;
		string 			Status;
		string 			NameColor;
	};


	// list of connected players
	dictionary<string, PlayerInfo> ConnectedL;
	








	// base class used to give client GUI parameters on how to display
	class GuiParameterBase
	{
	};
	
	sequence<GuiParameterBase> GuiParamsSeq;
	
	// server send inventory content to clien	
	class InventoryGuiParameter extends GuiParameterBase
	{
		int			InventorySize;
		ItemsMap		InventoryContent;	
	};
	
	// server send container content to client	
	class ContainerGuiParameter extends GuiParameterBase
	{
		long			ContainerId;
		int			InventorySize;		
		ItemsMap		ContainerContent;
		ItemsMap		InventoryContent;	
	};
	
	// server send list of item in shop to client
	class ShopGuiParameter extends GuiParameterBase
	{
		long			NPCId;
		ItemsMap		ShopContent;
		string			MoneyIconName;
	};
	
	
	// server send list of mails to display to client
	class MailboxGuiParameter extends GuiParameterBase
	{
		PMsSeq			MailboxContent;
	};	
	
	
	// server send updated friend list to client
	class FriendListGuiParameter extends GuiParameterBase
	{
		FriendsSeq		FriendList;
	};	
	
	// server send list of player online to client
	class PlayerOnlineListGuiParameter extends GuiParameterBase
	{
		PlayerOnlinesSeq	PlayerList;
	};	
	
	
	// server send list of teleport places to client
	class TeleportGuiParameter extends GuiParameterBase
	{
		TeleportsSeq		TeleportList;
	};
	
	// server send list of shortcut to client
	class ShortcutGuiParameter extends GuiParameterBase
	{
		ShortcutsSeq		ShorcutList;
	};	
	
	// server send letter to display to client	
	class LetterViewerGuiParameter extends GuiParameterBase
	{
		LetterInfo		ToDisplayInfo;
	};
	
	// server send letter to display to client	
	class QuestJournalGuiParameter extends GuiParameterBase
	{
		QuestsMap		QuestsStarted;
		QuestsMap		QuestsFinished;		
	};

	
	// server send dialog to display to client	
	class DialogGuiParameter extends GuiParameterBase
	{
		long			NPCId;
		long			TittleTextId;
		DialogPartInfo		DialogPart;
	};










	// base class used to exchange updates between client and server concerning GUI
	class GuiUpdateBase
	{
	};
			
	sequence<GuiUpdateBase> GuiUpdatesSeq;	
	
	
	
	// client add a friend
	class AddFriend extends GuiUpdateBase
	{
		string			FriendName;
	};
	
	// client accept a friend
	class AcceptFriend extends GuiUpdateBase
	{
		long			FriendId;
	};	
	
	// client remove a friend
	class RemoveFriend extends GuiUpdateBase
	{
		long			FriendId;
	};		
	
	// client ask server to get a refreshed list of friends
	class RefreshFriends extends GuiUpdateBase
	{
	};
	
	// server send an update from a specific friend
	class FriendChangedUpdate extends GuiUpdateBase
	{
		FriendInfo		NewInfo;
	};	
	
	// server send inventory size to client
	class UpdateInventorySize extends GuiUpdateBase
	{
		int			NewSize;
	};
	
	// server send inventory update to client
	class UpdateInventoryItem extends GuiUpdateBase
	{
		ItemInfo		Info;
	};	
	
	// client update item position
	class SwitchItemPosition extends GuiUpdateBase
	{
		long			ItemId;
		int			NewPosition;
	};
	
	// client tell server than an object is used
	class InventoryItemUsed extends GuiUpdateBase
	{
		long			ItemId;
	};	
	
	
	// server update player online info
	class PlayerStatusChanged extends GuiUpdateBase
	{
		PlayerOnline		NewInfo;
	};
	
	
	// server tell client gui to display text
	class DisplayGameText extends GuiUpdateBase
	{
		long 			Textid;
		bool			Show;
	};	
	
	// client tell server to update container content
	class UpdateInvContainer extends GuiUpdateBase
	{
		long 			Containerid;
		LbaNet::ItemList 	Taken;
		LbaNet::ItemList 	Put;
	};

	// server ask client to display a system message
	class SystemMessageUpdate extends GuiUpdateBase
	{
		string			Title;
		string			Message;		
	};
	

	// client tell server that shortcut has changed
	class ShortcutUpdate extends GuiUpdateBase
	{
		int			Position;
		long			ItemId;		
	};	

	// client tell server to destroy an item in inventory
	class DestroyItemUpdate extends GuiUpdateBase
	{
		long			ItemId;		
	};

	// client tell server to create a new written letter
	class CreateLetterUpdate extends GuiUpdateBase
	{
		string			Subject;
		string			Message;
	};
	

	// client send PM
	class SendPMUpdate extends GuiUpdateBase
	{
		PMInfo			PM;
	};	
	

	// client delete PM
	class DeletePMUpdate extends GuiUpdateBase
	{
		long			PMid;
	};
	

	// client mark read PM
	class MarkReadPMUpdate extends GuiUpdateBase
	{
		long			PMid;
	};
	

	// server send quest update to client
	class QuestUpdate extends GuiUpdateBase
	{
		QuestInfo		Quest;
		bool			Finished;
	};
	
	
	// client tell server that a dialog part was selected
	class DialogSelectedUpdate extends GuiUpdateBase
	{
		long			NPCId;
		int			SelectedId;
	};
	
	// server update dialog to display to client
	class DialogUpdate extends GuiUpdateBase
	{
		long			NPCId;
		DialogPartInfo		DialogPartUpdate;
	};
	
	
	// client inform server that the gui has been closed
	class GuiClosedUpdate extends GuiUpdateBase
	{
	};
	
	
	// server tell client how much money he has left
	class PlayerMoneyUpdate extends GuiUpdateBase
	{
		int			Quantity;
	};
	
	// client tell server to buy an item
	class BuyItemUpdate extends GuiUpdateBase
	{
		long			NPCId;	
		long			ItemId;
	};	
	
	
	
	// text received by client from server
	class ChatTextUpdate extends GuiUpdateBase 
	{
		string			Channel;
		string			Sender;
	    	string			Text;
	};
		
	
};	

#endif

