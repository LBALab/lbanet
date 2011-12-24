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

#if !defined(__LbaNetModel_1_GameGUI_h)
#define __LbaNetModel_1_GameGUI_h

#include "GUI.h"
#include <string>
#include <list>
#include <boost/shared_ptr.hpp>

#include "ChatBox.h"
#include "CommunityBox.h"
#include "TeleportBox.h"
#include "GameGUIBase.h"


namespace CEGUI
{
	class Window;
	class EventArgs;
	class Animation;
	class Affector;
	class AnimationInstance;
}
struct TPInfo;
class Actor;

/***********************************************************************
 * Module:  GameGUI.h
 * Author:  Vivien
 * Modified: samedi 11 juillet 2009 12:48:06
 * Purpose: Declaration of the class GameGUI
 ***********************************************************************/
class GameGUI : public GUI
{
public:
	//! constructor
	GameGUI();

	//! destructor
	~GameGUI();

	//! init function
	virtual void Initialize(void);


	//! handle send button event
	bool HandleChatIconClicked (const CEGUI::EventArgs& e);

	//! handle send button event
	bool HandleComIconClicked (const CEGUI::EventArgs& e);

	//! handle send button event
	bool HandleTeleIconClicked (const CEGUI::EventArgs& e);

	//! handle send button event
	bool HandleQuitIconClicked (const CEGUI::EventArgs& e);

	//! handle send button event
	bool HandleSoundIconClicked (const CEGUI::EventArgs& e);

	//! handle send button event
	bool HandleChangeWorldIconClicked (const CEGUI::EventArgs& e);

	//! handle send button event
	bool HandleOptionIconClicked (const CEGUI::EventArgs& e);

	//! handle send button event
	bool HandleCloseTextClicked (const CEGUI::EventArgs& e);

	//! handle send button event
	bool HandleInventoryClicked (const CEGUI::EventArgs& e);

	//! handle send button event
	bool HandleShortcutClicked (const CEGUI::EventArgs& e);

	//! handle send button event
	bool HandleJournalClicked (const CEGUI::EventArgs& e);

	//! called to infrom the gui that it is displayed
	virtual void Displayed(){}


	//! refresh gui with info from server
	void RefreshGUI(const std::string & guiid, const LbaNet::GuiParamsSeq &Parameters, bool Show, bool Hide);

	//! update gui with info from server
	void UpdateGUI(const std::string & guiid,const LbaNet::GuiUpdatesSeq &Updates);

	//! show GUI
	void ShowGUI(const std::string & guiid);

	//! hide GUI
	void HideGUI(const std::string & guiid);

	//! show/hide GUI
	void ToggleDisplayGUI(const std::string & guiid);

	//! focus GUI
	void FocusGUI(const std::string & guiid, bool focus);

	//! save size of windows to be restored after resize of the application
	void SaveGUISizes(int oldscreenX, int oldscreenY);

	//! restore the correct size of the windows
	void RestoreGUISizes();

protected:
	//! refresh sound button
	void RefreshSOundButton();

	//! display game text
	bool DisplayGameText(long textid, bool show, bool hide);

	//! set player name
	void SetPlayerName(const std::string & name);


	//! refresh portrait
	void RefreshCharPortrait();

	//! CloseText
	void CloseText();

private:
	std::map<std::string, boost::shared_ptr<GameGUIBase> > _gameguis;

	CEGUI::Animation*			_textanim;
	CEGUI::Affector*			_textanimaffector;
	CEGUI::AnimationInstance*	_textaniminstance;
};

#endif