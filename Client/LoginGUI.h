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

#if !defined(__LbaNetModel_1_LoginGUI_h)
#define __LbaNetModel_1_LoginGUI_h

#include "GUI.h"

namespace CEGUI
{
	class EventArgs;
}

#include <string>

/***********************************************************************
 * Module:  LoginGUI.h
 * Author:  Vivien
 * Modified: samedi 11 juillet 2009 09:41:34
 * Purpose: Declaration of the class LoginGUI
 **********************************************************************/
class LoginGUI : public GUI
{
public:

	//! constructor
   LoginGUI();

	//! destructor
   ~LoginGUI();

   //! init function
   void Initialize(const std::string &clientversion);

	//! handle connect button event
	bool HandleConnect(const CEGUI::EventArgs& e);

	//! handle cancel button event
	bool HandleCancel (const CEGUI::EventArgs& e);

	//! handle connect button event
	bool Handlebplus(const CEGUI::EventArgs& e);

	//! handle cancel button event
	bool Handlebminus (const CEGUI::EventArgs& e);

	//! handle connect button event
	bool Handlecplus(const CEGUI::EventArgs& e);

	//! handle cancel button event
	bool Handlecminus (const CEGUI::EventArgs& e);

	//! handle cancel button event
	bool HandleCloseTextClicked (const CEGUI::EventArgs& e);

	//! called to infrom the gui that it is displayed
	void Displayed();

	//! set if the server is on or not
	void SetServrOn(bool ServerOn);

	//! inform the user the login failed
	void InformNotLoggedIn(int problem, const std::string & reason);

	//! catch key event
	bool HandleEnterKey (const CEGUI::EventArgs& e);

private:

};

#endif