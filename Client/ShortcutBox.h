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


#ifndef _LBA_NET_SHORTCUT_BOX_
#define _LBA_NET_SHORTCUT_BOX_

namespace CEGUI
{
	class Window;
	class EventArgs;
	class Listbox;
	class Vector2;
}

class InventoryBox;

#include <string>
#include <list>
#include <map>
#include <vector>
#include "GameGUIBase.h"

//*************************************************************************************************
//*                               class ShortcutBox
//*************************************************************************************************
/**
* @brief Class handling a InventoryBox
*
*/
class ShortcutBox : public GameGUIBase
{
 public:
	//! constructor
	 ShortcutBox(int boxsize, InventoryBox * inventoryptr);

	//! destructor
	virtual ~ShortcutBox();

	//! called by resize of the screen to fix the boxes correctly
	void Resize();

	//! handle windows resize event
	bool HandleResize (const CEGUI::EventArgs& e);


	//! handle windows resize event
	bool HandleChangeStance (const CEGUI::EventArgs& e);

	//! handle windows resize event
	bool HandleObjectClicked (const CEGUI::EventArgs& e);

	//! drag and drop
	bool handle_ItemDropped(const CEGUI::EventArgs& args);

	//! on window move
	bool onWindowMove(const CEGUI::EventArgs& pEventArgs);

	//! handle windows resize event
	bool HandleObjectPressed (const CEGUI::EventArgs& e);

	//! handle windows resize event
	bool HandleObjectReleased (const CEGUI::EventArgs& e);


	//! handle windows resize event
	bool HandleObjectPressedStances (const CEGUI::EventArgs& e);

	//! handle windows resize event
	bool HandleObjectReleasedStances (const CEGUI::EventArgs& e);


	//! refresh inventory images
	void Refresh();



	//! initalize the box
	virtual void Initialize(CEGUI::Window* Root);

	//! refresh gui with info from server
	virtual void Refresh(const LbaNet::GuiParamsSeq &Parameters);

	//! update gui with info from server
	virtual void Update(const LbaNet::GuiUpdatesSeq &Updates);

	//! show GUI
	virtual void Display();

	//! hide GUI
	virtual void Hide();

	//! show/hide GUI
	virtual void ToggleDisplay();

	//! focus GUI
	virtual void Focus(bool focus);

	//! save size of windows to be restored after resize of the application
	virtual void SaveGUISizes(int oldscreenX, int oldscreenY);

	//! restore the correct size of the windows
	virtual void RestoreGUISizes();

protected:
	void SetShorcut(CEGUI::Window* box, const LbaNet::ItemInfo &iteminfo);

	// refresh visible part depending of the visibility number
	void RefreshVivsibleStuff();

private:
	CEGUI::Window*					_myBox;
	CEGUI::Window*					_myStances;
	InventoryBox *					_inventoryptr;

	int								_boxsize;

	std::vector<CEGUI::Window*>		_inv_boxes;
	LbaNet::ShortcutsSeq			_shortcutinfo;

	CEGUI::Vector2*					mMousePosInWindow;
	bool							_moving;

	CEGUI::Vector2*					mMousePosInWindow_stances;
	bool							_moving_stances;

	int								_currentvisibility;

	float							_savestancePosX;
	float							_savestancePosY;


};

#endif
