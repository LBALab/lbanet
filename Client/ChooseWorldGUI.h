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


#if !defined(__LbaNetModel_1_ChooseWorldGUI_h)
#define __LbaNetModel_1_ChooseWorldGUI_h

#include "GUI.h"
#include <LbaTypes.h>

#include <vector>


namespace CEGUI
{
	class EventArgs;
}
/***********************************************************************
 * Module:  ChooseWorldGUI.h
 * Author:  Vivien
 * Modified: samedi 11 juillet 2009 10:09:14
 * Purpose: Declaration of the class ChooseWorldGUI
 ***********************************************************************/
class ChooseWorldGUI : public GUI
{
public:
	//! constructor
	ChooseWorldGUI();

	//! destructor
	~ChooseWorldGUI();

	//initialize function
	virtual void Initialize(void);

	//! set the list of available worlds
	void SetWorldList(const std::vector<LbaNet::WorldDesc> &list);

	//! handle connect button event
	bool HandleConnect(const CEGUI::EventArgs& e);

	//! handle cancel button event
	bool HandleCancel (const CEGUI::EventArgs& e);

	//! handle reset button event
	bool HandleReset (const CEGUI::EventArgs& e);

	
	//! handle world selected event
	bool HandleWorldSelected (const CEGUI::EventArgs& e);

	//! called to infrom the gui that it is displayed
	void Displayed();

	//! catch key event
	bool HandleEnterKey (const CEGUI::EventArgs& e);


private:
	std::vector<LbaNet::WorldDesc>	_wlist;
	std::string				_selectedworld;
};

#endif