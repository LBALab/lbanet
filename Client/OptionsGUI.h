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

#ifndef _LBANET_OPTIONS_GUI_H_
#define _LBANET_OPTIONS_GUI_H_


#include "GUI.h"
#include <string>

namespace CEGUI
{
	class Window;
	class EventArgs;
}

//*************************************************************************************************
//*                               class OptionsGUI
//*************************************************************************************************
/**
* @brief Class taking care of the user interface in game
*
*/
class OptionsGUI : public GUI
{
public:

	// constructor
	OptionsGUI();

	// destructor
	~OptionsGUI();

	// initialize the GUI
	void Initialize();


	//! handle connect button event
	bool HandleOK(const CEGUI::EventArgs& e);

	//! handle cancel button event
	bool HandleCancel (const CEGUI::EventArgs& e);

	//! handle cancel button event
	bool HandleApply (const CEGUI::EventArgs& e);

	//! called to infrom the gui that it is displayed
	void Displayed();

	//! send name color
	void SendNameColor();

protected:
	//! apply new changes
	void Apply();

	//! cancel changes
	void Cancel();

	//! quit windows
	void Quit();


private:
	// general part
	int				_textR;
	int				_textG;
	int				_textB;
	int				_nameR;
	int				_nameG;
	int				_nameB;
	std::string		_lang;


	// video part
	int				_currScreenX;
	int				_currScreenY;
	bool			_currFullscreen;
	bool			_currDisplayFPS;
	bool			_currPerspective;
	bool			_currDisplayExit;

	// sound part
	int				_currGenVolume;
	int				_currMusicVolume;


	// gui part
	int				_fontSize;

};


#endif
