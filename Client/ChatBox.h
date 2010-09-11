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


#ifndef _LBA_NET_CHAT_BOX_
#define _LBA_NET_CHAT_BOX_


namespace CEGUI
{
	class Window;
	class EventArgs;
	class Listbox;
	class String;
	class Listbox;
}

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include "GameGUIBase.h"


//*************************************************************************************************
//*                               class ChatBox
//*************************************************************************************************
/**
* @brief Class handling a chat box
*
*/
class ChatBox : public GameGUIBase
{
 public:
	//! constructor
	 ChatBox();

	//! destructor
	virtual ~ChatBox();

	//! handle send button event
	bool HandleSend (const CEGUI::EventArgs& e);

	//! handle send button event
	bool HandleBChannel (const CEGUI::EventArgs& e);

	//! handle enter key
	bool HandleEnterKey (const CEGUI::EventArgs& e);

	//! handle release key
	bool HandleReleaseKey (const CEGUI::EventArgs& e);

	//! handle event when list is selected
	bool HandleLbSelected (const CEGUI::EventArgs& e);

	//! handle enter key
	bool HandleCCOk (const CEGUI::EventArgs& e);

	//! handle event when list is selected
	bool HandleCCCancel (const CEGUI::EventArgs& e);

	//! handle enter key
	bool HandleCPOk (const CEGUI::EventArgs& e);

	//! handle event when list is selected
	bool HandleCPCancel (const CEGUI::EventArgs& e);

	//! handle event when the channel window is closed
	bool HandleCloseChatbox (const CEGUI::EventArgs& e);


	//! initalize the box
	virtual void Initialize(CEGUI::Window* Root);

	//! refresh gui with info from server
	virtual void Refresh(const LbaNet::GuiParamsSeq &Parameters);

	//! update gui with info from server
	virtual void Update(const LbaNet::GuiUpdatesSeq &Updates);

	//! show GUI
	virtual void Display();

	//! hide GUI
	virtual void Hide();

	//! show/hide GUI
	virtual void ToggleDisplay();

	//! focus GUI
	virtual void Focus(bool focus);


protected:
	//! set the current map of the game
	void SetCurrentMap(const std::string & WorldName, const std::string & MapName);

	// add a channel to the chat
	void AddChannel(const std::string & channel);

	// add a tab to the chat
	void AddTab(const std::string & tabName);

	// send text outside
	void SendText(const std::string & channel, const std::string & Text);

	//! add new text to the chatbox
	void AddText(std::string channel, std::string Sender, std::string Text);

	//! method to correctly add chat text
	void AddChatText(const CEGUI::String& pText, CEGUI::Listbox * listbox);

	//! replace a part of a string by another one
	void ReplaceStringPart(std::string &text, const std::string &toreplace, const std::string &replacement);

	//! protect part of the string containing character [
	void ProtectString(std::string &text);

	//! add a whisper channel
	void AddWhisperChanel(const std::string & name);

private:
	CEGUI::Window*			_myChat;
	CEGUI::Listbox*			_lb;
	CEGUI::Window*			_myChannels;
	CEGUI::Window*			_myChooseName;

	std::string				_currentWorld;
	std::string				_currentMap;
	std::list<std::string>	_channels;
	std::list<std::string>	_whisper_channels;
	std::list<std::string>	_lasttexts;
	std::list<std::string>::iterator	_itltext;

	std::string				_text_copyed;
	bool					_control_key_on;
	bool					_shift_key_on;
	int						_currSelectedch;


	size_t					mHistorySize;

	std::vector<std::pair<std::string, std::string> >	_replace_string_map;

	std::map<std::string, std::string>	_name_colors;
};

#endif
