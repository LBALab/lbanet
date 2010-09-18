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
	ChangeWorldEvent(const std::string & NewWorldName)
		: _NewWorldName(NewWorldName)
	{
	}

	std::string _NewWorldName;
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
	PlayerNameColorChangedEvent(const std::string &color)
		: _color(color)
	{
	}

	std::string _color;
};




/*
************************************************************************************************************************
*                                                  class SendChatTextEvent
*
*	used by chatbox to inform engine to send chat text
************************************************************************************************************************
*/
class SendChatTextEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	SendChatTextEvent(const std::string & text)
		: _text(text)
	{
	}

	std::string _text;
};



/*
************************************************************************************************************************
*                                                  class PlayerStatusUpdateEvent
*
*	used when a player update its status
************************************************************************************************************************
*/
class PlayerStatusUpdateEvent : public LbaNet::ClientServerEventBase
{
public:
	//! constructor
	PlayerStatusUpdateEvent(const std::string & name, const std::string & status, 
															const std::string & color)
		: _name(name), _status(status), _color(color)
	{
	}

	std::string _name;
	std::string _status;
	std::string _color;
};




#endif