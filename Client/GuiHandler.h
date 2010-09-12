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

#if !defined(__LbaNetModel_1_GuiHandler_h)
#define __LbaNetModel_1_GuiHandler_h


class GUI;
class GameGUI;
class LoginGUI;
class OptionsGUI;
class ChooseWorldGUI;

#include <string>
#include <vector>
#include <list>
#include <map>

#include <LbaTypes.h>

namespace CEGUI
{
	class OpenGLRenderer;
	class EventArgs;
}




/***********************************************************************
 * Module:  GuiHandler.h
 * Author:  vivien
 * Modified: lundi 27 juillet 2009 14:59:34
 * Purpose: Declaration of the class GuiHandler
 ***********************************************************************/
class GuiHandler
{
public:
	//! constructor
	GuiHandler();

	//! destructor
	~GuiHandler();

	//! initialize function
	void Initialize(int screen_size_X, int screen_size_Y);

	// process function
	void Process(void);

	//! switch from current gui to another one
	void SwitchGUI(int GuiNumber);

	//! redraw the scene on screen
	void Redraw(void);

	//! called when the windows is resized
	void Resize(int screen_size_X, int screen_size_Y);
	void grabTextures();
	void restoreTextures();

	//! called when font size changed
	void ReloadFontSize();

	//! set the list of available worlds
	void SetWorldList(const std::vector<LbaNet::WorldDesc> &list);

	//! inform the user the login failed
	void InformNotLoggedIn(int problem, const std::string & reason);

	//! handle overlay
	bool overlayHandler(const CEGUI::EventArgs& args);

	// refresh options
	void RefreshOption();

	//! set the client version text
	void SetClientVersion(const std::string &clientversion);

	//! set if the server is on or not
	void SetServrOn(bool ServerOn);


	//! refresh gui with info from server
	void RefreshGameGUI(const std::string & guiid, const LbaNet::GuiParamsSeq &Parameters, bool Show, bool Hide);

	//! update gui with info from server
	void UpdateGameGUI(const std::string & guiid,const LbaNet::GuiUpdatesSeq &Updates);

	//! show GUI
	void ShowGameGUI(const std::string & guiid);

	//! hide GUI
	void HideGameGUI(const std::string & guiid);

	//! show/hide GUI
	void ToggleDisplayGameGUI(const std::string & guiid);

	//! focus GUI
	void FocusGameGUI(const std::string & guiid, bool focus);

protected:
	//! inject time to the GUI
	void inject_time_pulse();

private:
	CEGUI::OpenGLRenderer *	_gui_renderer;
	std::vector<GUI *>		_guis;
	LoginGUI *				_login_gui;
	ChooseWorldGUI *		_chooseworld_gui;
	GameGUI *				_game_gui;
	OptionsGUI *			_option_gui;
	int						_currentGUI;
	double					m_last_time_pulse;
};

#endif