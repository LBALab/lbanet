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


#ifndef _LBA_NET_INVENTORY_BOX_
#define _LBA_NET_INVENTORY_BOX_

namespace CEGUI
{
	class Window;
	class EventArgs;
	class Listbox;
}

#include <string>
#include <list>
#include <map>
#include <vector>
#include "GameGUIBase.h"

//*************************************************************************************************
//*                               class InventoryBox
//*************************************************************************************************
/**
* @brief Class handling a InventoryBox
*
*/
class InventoryBox : public GameGUIBase
{
 public:
	//! constructor
	 InventoryBox(int boxsize);

	//! destructor
	virtual ~InventoryBox();

	//! handle windows closing event
	bool HandleClose (const CEGUI::EventArgs& e);


	//! handle windows resize event
	bool HandleResize (const CEGUI::EventArgs& e);

	//! drag and drop
	bool handle_ItemDropped(const CEGUI::EventArgs& args);

	//! drag and drop
	bool handle_ItemDroppedOnItem(const CEGUI::EventArgs& args);

	//! handle windows resize event
	bool HandleObjectClicked (const CEGUI::EventArgs& e);



	//! refresh inventory images
	void Refresh();

	//! get info about an item in inventory
	LbaNet::ItemInfo GetItemInfo(Ice::Long itemid);


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
	//! resize inventory
	void ResizeBox();

	//! find first empty space in inventory
	CEGUI::Window* FindFirstEmptySpace();

	//! empty the inventory
	void CleanInventory();

	//! resize inventory
	void ResizeInventory(int newsize);


	//! update item to the inventory
	//! if item didnt exist add it to the inventory
	//! if number = 0 remove it from inventory
	//! if no more place in inventory when adding then return false
	bool UpdateItem(long Id, const std::string & Description,
						long number, const std::string & iconname, int PlaceInInventory = -1);


	//! refresh inventory display
	void RefreshInventory();

	//! inform user of item update
	void InformUserItemUpdate(long itemId, LbaNet::ItemClientInformType Informtype, int count,
								const std::string & Description, const std::string & iconname);

private:
	CEGUI::Window*														_myBox;

	LbaNet::ItemsMap													_inventoryinfo;

	int																	_boxsize;
	int																	_inventory_size;
	std::vector<CEGUI::Window*>											_inv_boxes;
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >		_objects;
};

#endif
