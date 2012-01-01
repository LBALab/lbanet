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
#include <fstream>

#include <boost/shared_ptr.hpp>
#include <Ice/Application.h>
#include "ConnectionHandlerBase.h"

class PhysXEngine;
class GuiHandler;
class LbaNetModel;
class ChatServerHandler;
class Client;
class SwitchToFixedImageEvent;

#ifdef _USE_QT_EDITOR_
#include "editorhandlerBase.h"
#endif



/***********************************************************************
 * Module:  LbaNetEngine.h
 * Author:  vivien
 * Modified: mardi 14 juillet 2009 17:41:03
 * Purpose: Declaration of the class LbaNetEngine
 ***********************************************************************/
class LbaNetEngine
{
public:

#ifdef _USE_QT_EDITOR_
	//!constructor
	LbaNetEngine(Ice::CommunicatorPtr communicator, const std::string & clientV,
					boost::shared_ptr<EditorHandlerBase> editH);
#else
	LbaNetEngine(Ice::CommunicatorPtr communicator, const std::string & clientV);
#endif

	//!destructor
   ~LbaNetEngine();

	//! entry point of the engine
	void run(void);

	//! switch to fixed image - exception: only there because we are sure it is called from the same thread
	void SwitchToFixedImage(SwitchToFixedImageEvent * evtptr);

protected:
	//! process function
	void Process(double tnow, float tdiff);

	//! initialize the class
	void Initialize(void);

	//! called to check for game events and handle them
	void HandleGameEvents();

	//! try to login to the server
	void TryLogin(const std::string &Name, const std::string &Passwordl, bool uselocalserver);

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

	//! disconnect from server
	void Disconnect();

	//! resize client window
	void ResizeClientWindow(int sx, int sy, bool fullscreen);


	//! start playing a video sequence
	void PlayVideoSequence(const std::string & filename);

	//! end a video sequence
	void EndVideoSequence();


	//! switch to music
	void SwitchMusic(const std::string &musicpath, int nbtime);

	//! reset to previous music
	void ResetMusic();

	//! check if LBA1 file exist 
	void CheckLBA1Files();

private:
	boost::shared_ptr<GuiHandler>					m_gui_handler;				// pointer on gui class
	boost::shared_ptr<LbaNetModel>					m_lbaNetModel;				// game model
	boost::shared_ptr<ConnectionHandlerBase>		m_serverConH;				// connection to server
	boost::shared_ptr<ChatServerHandler>			m_chatH;					// connection to chat server

	Ice::CommunicatorPtr							m_communicator;
	std::string										m_clientV;
	bool											m_shouldexit;
	std::string										m_currentworld;

	// game states
	enum EngineState {ELogin=0, EChoosingWorld, EGaming, EMenu, EOption };
	EngineState										m_currentstate;
	EngineState										m_oldstate;

	// last music played
	std::string										m_lastmusic;

#ifdef _USE_QT_EDITOR_
	boost::shared_ptr<EditorHandlerBase>			m_editor_handler;
#endif
	boost::shared_ptr<Client>						m_client_window;



};

#endif