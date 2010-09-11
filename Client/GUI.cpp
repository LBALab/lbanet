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

#include "GUI.h"
#include <CEGUI.h>

/***********************************************************
	Constructor
***********************************************************/
GUI::GUI()
{
}


/***********************************************************
	Destructor
***********************************************************/
GUI::~GUI()
{
}



/***********************************************************
return the current gui root
***********************************************************/
CEGUI::Window * GUI::GetRoot(void)
{
   return _root;
}


/***********************************************************
refresh the gui
***********************************************************/
void GUI::Refresh()
{
	_root->hide();
	_root->show();
}


