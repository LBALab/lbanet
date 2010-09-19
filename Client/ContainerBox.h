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


#ifndef _LBA_NET_CONTAINER_BOX_
#define _LBA_NET_CONTAINER_BOX_


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
#include "GuiCallbackableBase.h"
#include "GameGUIBase.h"


//*************************************************************************************************
//*                               class ContainerBox
//*************************************************************************************************
/**
* @brief Class handling a ContainerBox
*
*/
class ContainerBox : public GuiCallbackableBase, public GameGUIBase
{
 public:
	//! constructor
	 ContainerBox(int boxsize);

	//! destructor
	virtual ~ContainerBox();


	//! drag and drop
	bool handle_ItemDroppedInContainer(const CEGUI::EventArgs& args);
	bool handle_ItemDroppedInInventory(const CEGUI::EventArgs& args);
	bool handle_ItemDroppedInContainerItem(const CEGUI::EventArgs& args);
	bool handle_ItemDroppedInInventoryItem(const CEGUI::EventArgs& args);


	//! handle windows resize event
	bool HandleContainerItemClicked (const CEGUI::EventArgs& e);
	bool HandleInventoryItemClicked (const CEGUI::EventArgs& e);

	//! handle windows closing event
	bool HandleOk (const CEGUI::EventArgs& e);
		
	//! handle windows closing event
	bool HandleTakeAll (const CEGUI::EventArgs& e);

	//! handle windows closing event
	bool HandleCancel (const CEGUI::EventArgs& e);


	//! refresh inventory images
	void Refresh();

	 //! callback
	virtual void CallbackChooseNumber(long id, long choosennumber, bool flag);


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

	//! close box and send update to server
	void CloseAndUpdate();
	
	//! cancel changes
	void Cancel();

	//! take all item from container
	void TakeAll();

	//! clean container items
	void CleanContainer();

	//! resize inventory
	void ResizeInventory(int newsize);

	//! clean inventory
	void CleanInventory();

	//! refresh inventory
	void RefreshInventory();

	//! refresh Container
	void RefreshContainer();

	//! add item inside the container
	std::pair<CEGUI::Window*, CEGUI::Window*> AddInventoryItem(const LbaNet::ItemInfo & itinfo, 
																	CEGUI::Window* parent, 
																	bool tocontainer);

	
	//! add an item from container to inventory
	//! return the number taken
	int AddItemFromContainerToInventory(long Id, int number);

	//! switch item from container to inventory
	void switchfromcontainertoinventory(long Id, long number);


	//! update taken and put vectors with last change from user
	void UpdateTakenPut(long itid, int deltaupd);

	
	//! add an item from inventory to container
	//! return the number taken
	int AddItemFromInventoryToContainer(long Id, int number);
	
	//! switch item from inventory to container
	void switchfrominventorytocontainer(long Id, long number);

	//! find first empty space in container
	CEGUI::Window* FindFirstContainerEmptySpace();

	//! find first empty space in inventory
	CEGUI::Window* FindFirstInventoryEmptySpace();

	//! catch key event
	bool HandleEnterKey (const CEGUI::EventArgs& e);

private:
	CEGUI::Window*				_myBox;
	int							_boxsize;

	Ice::Long					_currContainerId;
	LbaNet::ItemsMap			_ContainerContentStatic;
	LbaNet::ItemsMap			_ContainerContent;
	LbaNet::ItemsMap			_InventoryContent;
	LbaNet::UpdateInvContainerPtr	_serverupdate;


	// container part
	std::vector<CEGUI::Window*>											_cont_boxes;
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >		_cont_objects;


	// inventory part
	int																	_inventory_size;
	std::vector<CEGUI::Window*>											_inv_boxes;
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >		_inv_objects;
};

#endif
