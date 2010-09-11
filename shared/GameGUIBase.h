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


#ifndef _LBANET_GAME_GUI_BASE_H_
#define _LBANET_GAME_GUI_BASE_H_


#include <ClientServerEvents.h>

namespace CEGUI
{
	class Window;
}

//*************************************************************************************************
//*                               class GameGUIBase
//*************************************************************************************************
/**
* @brief Base class for game GUIs
*
*/
class GameGUIBase
{
public:

	//! constructor
	GameGUIBase(){}


	//! destructor
	virtual ~GameGUIBase(){}

	//! initalize the box
	virtual void Initialize(CEGUI::Window* Root) = 0;


	//! refresh gui with info from server
	virtual void Refresh(const LbaNet::GuiParamsSeq &Parameters) = 0;

	//! update gui with info from server
	virtual void Update(const LbaNet::GuiUpdatesSeq &Updates) = 0;

	//! show GUI
	virtual void Display() = 0;

	//! hide GUI
	virtual void Hide() = 0;

	//! show/hide GUI
	virtual void ToggleDisplay() = 0;

	//! focus GUI
	virtual void Focus(bool focus) = 0;
};


#endif
