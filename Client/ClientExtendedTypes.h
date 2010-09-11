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


#if !defined(__LbaNetModel_ClientExtendedTypes_h)
#define __LbaNetModel_ClientExtendedTypes_h

#include <LbaTypes.h>



/*
************************************************************************************************************************
*                                                  class NameColorChangedUpdate
*
*	class used when a player as changed name color
************************************************************************************************************************
*/
class NameColorChangedUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	NameColorChangedUpdate(const std::string &Name, const std::string &Color)
		: _Name(Name), _Color(Color)
	{
	}

	std::string _Name;
	std::string _Color;
};


/*
************************************************************************************************************************
*                                                  class ChatTextReceivedUpdate
*
*	class used when server send chat text
************************************************************************************************************************
*/
class ChatTextReceivedUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	ChatTextReceivedUpdate(const std::string &Channel, const std::string &Sender, 
															const std::string &Text)
		: _Channel(Channel), _Sender(Sender), _Text(Text)
	{
	}

	std::string _Channel;
	std::string _Sender;
	std::string _Text;
};


/*
************************************************************************************************************************
*                                                  class AddWhisperChanelUpdate
*
*	class used when chatbox need to add a whisper channel
************************************************************************************************************************
*/
class AddWhisperChanelUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	AddWhisperChanelUpdate(const std::string &Name)
		: _Name(Name)
	{
	}

	std::string _Name;
};


/*
************************************************************************************************************************
*                                                  class RefreshSoundButtonUpdate
*
*	class used to refresh gui sound button
************************************************************************************************************************
*/
class RefreshSoundButtonUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	RefreshSoundButtonUpdate()
	{
	}

};


/*
************************************************************************************************************************
*                                                  class SetPlayerNameUpdate
*
*	class used when engine want to set player name in the gui
************************************************************************************************************************
*/
class SetPlayerNameUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	SetPlayerNameUpdate(const std::string &Name)
		: _Name(Name)
	{
	}

	std::string _Name;
};


/*
************************************************************************************************************************
*                                                  class UsedShorcutUpdate
*
*	class used when player used a key shortcut
************************************************************************************************************************
*/
class UsedShorcutUpdate : public LbaNet::GuiUpdateBase
{
public:
	//! constructor
	UsedShorcutUpdate(int shortcutid)
		: _shortcutid(shortcutid)
	{
	}

	int _shortcutid;
};

#endif