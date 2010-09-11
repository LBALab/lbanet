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

#if !defined(__LbaNetModel_1_MenuGUI_h)
#define __LbaNetModel_1_MenuGUI_h

#include "GUI.h"

namespace CEGUI
{
	class Window;
	class EventArgs;
}


/***********************************************************************
 * Module:  MenuGUI.h
 * Author:  Vivien
 * Modified: samedi 11 juillet 2009 09:41:39
 * Purpose: Declaration of the class MenuGUI
 ***********************************************************************/
class MenuGUI : public GUI
{
public:
	//! constructor
	MenuGUI();

	//! destructor
	~MenuGUI();

	//! init function
	virtual void Initialize(void);

	//! handle connect button event
	bool HandleResume(const CEGUI::EventArgs& e);

	//! handle cancel button event
	bool HandleInventory (const CEGUI::EventArgs& e);

	//! handle cancel button event
	bool HandleOption (const CEGUI::EventArgs& e);

	//! handle connect button event
	bool HandleSwitchWorld(const CEGUI::EventArgs& e);

	//! handle cancel button event
	bool HandleDisconnect (const CEGUI::EventArgs& e);

	//! handle connect button event
	bool HandleQuit(const CEGUI::EventArgs& e);

	//! handle cancel button event
	bool HandleCredits (const CEGUI::EventArgs& e);


	//! called to infrom the gui that it is displayed
	void Displayed(){}

private:

};

#endif