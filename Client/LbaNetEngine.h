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

#if !defined(__LbaNetModel_1_LbaNetEngine_h)
#define __LbaNetModel_1_LbaNetEngine_h


#include <string>

#include <boost/shared_ptr.hpp>


class PhysXEngine;
class GuiHandler;
class LbaNetModel;


/***********************************************************************
 * Module:  LbaNetEngine.h
 * Author:  vivien
 * Modified: mardi 14 juillet 2009 17:41:03
 * Purpose: Declaration of the class LbaNetEngine
 ***********************************************************************/
class LbaNetEngine
{
public:
	//!constructor
	LbaNetEngine();

	//!destructor
   ~LbaNetEngine();

	//! entry point of the engine
	void run(void);

protected:
	//! process function
	void Process(void);

	//! initialize the class
	void Initialize(void);

	//! called to check for game events and handle them
	void HandleGameEvents();

	//! try to login to the server
	void TryLogin(const std::string &Name, const std::string &Passwordl);

	//! switch gui helpers
	void SwitchGuiToLogin();
	void SwitchGuiToChooseWorld();
	void SwitchGuiToGame();
	void SwitchGuiToMenu();
	void SwitchGuiToOption();

	// display a specific gui
	void DisplayGUI(int guinumber);

	// exit current active gui
	void ExitGui();

	// change the world
	void ChangeWorld(const std::string & NewWorld);

	// called to play the assigned music when menu
	void PlayMenuMusic();

	// called when need to connect to game server
	void ConnectToGameServer(const std::string &ServerName, const std::string &ServerAddress);


private:
	boost::shared_ptr<GuiHandler>	m_gui_handler;		// pointer on gui class
	boost::shared_ptr<LbaNetModel>	m_lbaNetModel;		// game model

	std::string						m_userlogin;
	std::string						m_userpass;

	// game states
	enum EngineState {ELogin=0, EChoosingWorld, EGaming, EMenu, EOption };
	EngineState							m_currentstate;
	EngineState							m_oldstate;

	// last music played
	std::string							m_lastmusic;
};

#endif