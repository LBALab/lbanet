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
	
	
	
	// event sent by client when user send chat text
	class ChatTextEvent extends ClientServerEventBase 
	{
		string			Sender;
	    	string			Text;
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
};	

#endif

