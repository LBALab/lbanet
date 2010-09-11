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

#if !defined(__LbaNetModel_1_GUI_h)
#define __LbaNetModel_1_GUI_h

namespace CEGUI
{
	class Window;
}

/***********************************************************************
 * Module:  GUI.h
 * Author:  Vivien
 * Modified: lundi 27 juillet 2009 19:42:09
 * Purpose: Declaration of the class GUI
 ***********************************************************************/
class GUI
{
public:
	//! constructor
	GUI();

	//! destructor
	virtual ~GUI();

	//! return the current gui root
	CEGUI::Window * GetRoot(void);

	//! process function
	virtual void Process(){}

	//! refresh the gui
	void Refresh();

	//! called to infrom the gui that it is displayed
	virtual void Displayed() = 0;

protected:
	// root window
	CEGUI::Window * _root;

};

#endif