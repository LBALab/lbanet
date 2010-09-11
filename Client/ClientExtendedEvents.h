/*
------------------------[ Lbanet Source ]-------------------------
Copyright (C) 2009
Author: Vivien Delage [Rincevent_123]
Email : vdelage@gmail.com

-------------------------------[ GNU License ]-------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
*/


#if !defined(__LbaNetModel_ClientExtendedEvents_h)
#define __LbaNetModel_ClientExtendedEvents_h

#include <ClientServerEvents.h>



/*
************************************************************************************************************************
*                                                  class LoginEvent
*
*	class used during login
************************************************************************************************************************
*/
class LoginEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	LoginEvent(const std::string &Name, const std::string &Password, bool Local)
		: _Name(Name), _Password(Password), _Local(Local)
	{
	}

	std::string _Name;
	std::string _Password;
	bool _Local;
};

/*
************************************************************************************************************************
*                                                  class GuiExitEvent
*
*	used when the active gui is being quitted by the user
************************************************************************************************************************
*/
class GuiExitEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	GuiExitEvent()
	{
	}
};


/*
************************************************************************************************************************
*                                                  class QuitGameEvent
*
*	used when player quit the game
************************************************************************************************************************
*/
class QuitGameEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	QuitGameEvent()
	{
	}
};


/*
************************************************************************************************************************
*                                                  class ChangeWorldEvent
*
*	used when the user is changing world
************************************************************************************************************************
*/
class ChangeWorldEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	ChangeWorldEvent(const std::string & NewWorldName, const std::string & NewWorldDataPath)
		: _NewWorldName(NewWorldName), _NewWorldDataPath(NewWorldDataPath)
	{
	}

	std::string _NewWorldName;
	std::string _NewWorldDataPath;
};


/*
************************************************************************************************************************
*                                                  class FocusChatEvent
*
*	used to focus chat box edit line
************************************************************************************************************************
*/
class FocusChatEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	FocusChatEvent()
	{
	}
};


/*
************************************************************************************************************************
*                                                  class WhisperChannelEvent
*
*	used to add a whisper channel in chatbox
************************************************************************************************************************
*/
class WhisperChannelEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	WhisperChannelEvent(const std::string & ChannelName)
		: _ChannelName(ChannelName)
	{
	}

	std::string _ChannelName;
};

/*
************************************************************************************************************************
*                                                  class DisplayGUIEvent
*
*	used when the user is switching gui
************************************************************************************************************************
*/
class DisplayGUIEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	DisplayGUIEvent(int GuiNumber)
		: _GuiNumber(GuiNumber)
	{
	}

	int _GuiNumber;
};

/*
************************************************************************************************************************
*                                                  class AddChatChannelEvent
*
*	used when client add a channel to the chat
************************************************************************************************************************
*/
class AddChatChannelEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	AddChatChannelEvent(const std::string & channelname)
		: _channelname(channelname)
	{
	}

	std::string _channelname;
};


/*
************************************************************************************************************************
*                                                  class RemoveChatChannelEvent
*
*	used when client remove a channel to the chat
************************************************************************************************************************
*/
class RemoveChatChannelEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	RemoveChatChannelEvent(const std::string & channelname)
		: _channelname(channelname)
	{
	}

	std::string _channelname;
};



/*
************************************************************************************************************************
*                                                  class NewFontSizeEvent
*
*	used when client change font size
************************************************************************************************************************
*/
class NewFontSizeEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	NewFontSizeEvent()
	{
	}
};




/*
************************************************************************************************************************
*                                                  class PlayerNameColorChangedEvent
*
*	used when client change color of player name display
************************************************************************************************************************
*/
class PlayerNameColorChangedEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	PlayerNameColorChangedEvent(int R, int G, int B)
		: _R(R), _G(G), _B(B)
	{
	}

	int _R;
	int _G;
	int _B;
};



#endif