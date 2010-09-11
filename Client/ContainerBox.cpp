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

#include "ContainerBox.h"
#include <iostream>
#include <algorithm>
#include <CEGUI.h>
#include "GameGUI.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "ImageSetHandler.h"
#include "SynchronizedTimeHandler.h"
#include "MessageBox.h"
#include "ChooseNumberBox.h"
#include "EventsQueue.h"
#include "DataLoader.h"


#define _NB_BOX_CONTAINER_ 12


/***********************************************************
constructor
***********************************************************/
ContainerBox::ContainerBox(int boxsize)
: _boxsize(boxsize), _inventory_size(0), 
	_serverupdate(new LbaNet::UpdateInvContainer(-1, LbaNet::ItemList(), LbaNet::ItemList()))
{
	_currContainerId = -1;
}


/***********************************************************
destructor
***********************************************************/
ContainerBox::~ContainerBox()
{
	try
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("ContainerFrame"));
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception destructor Inventorybox: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
initalize the box
***********************************************************/
void ContainerBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "container.layout" );
		Root->addChildWindow(_myBox);


		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("ContainerFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&ContainerBox::HandleCancel, this));


		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("ContainerFrame/OK"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&ContainerBox::HandleOk, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("ContainerFrame/TakeAll"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&ContainerBox::HandleTakeAll, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("ContainerFrame/Cancel"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&ContainerBox::HandleCancel, this));


		CEGUI::Window*	pane = CEGUI::WindowManager::getSingleton().getWindow("ContainerFrame/ConScrollable");
		CEGUI::Window*	tmpwindow;
		for(int i=0; i<_NB_BOX_CONTAINER_; ++i)
		{
			int x = i / 3;
			int y = i % 3;

			tmpwindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText");
			tmpwindow->setArea(CEGUI::UDim(0,5+((float)_boxsize+2)*y), CEGUI::UDim(0,5+((float)_boxsize+2)*x), 
								CEGUI::UDim(0, (float)_boxsize), CEGUI::UDim(0, (float)_boxsize));
			pane->addChildWindow(tmpwindow);

			tmpwindow->subscribeEvent(
						CEGUI::Window::EventDragDropItemDropped,
						CEGUI::Event::Subscriber(&ContainerBox::handle_ItemDroppedInContainer, this));

			tmpwindow->setID(i);
			_cont_boxes.push_back(tmpwindow);
		}



		frw->show();
		_myBox->hide();

		frw->subscribeEvent(CEGUI::Window::EventKeyDown,
			CEGUI::Event::Subscriber (&ContainerBox::HandleEnterKey, this));
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init ContainerBox: ") + ex.getMessage().c_str());
	}
}



	
/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool ContainerBox::HandleOk (const CEGUI::EventArgs& e)
{
	CloseAndUpdate();
	return true;
}
	
/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool ContainerBox::HandleTakeAll (const CEGUI::EventArgs& e)
{
	TakeAll();
	CloseAndUpdate();
	return true;
}

/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool ContainerBox::HandleCancel (const CEGUI::EventArgs& e)
{
	Cancel();
	CloseAndUpdate();
	return true;
}




/***********************************************************
drag and drop
***********************************************************/
bool ContainerBox::handle_ItemDroppedInContainer(const CEGUI::EventArgs& args)
{
    using namespace CEGUI;

    // cast the args to the 'real' type so we can get access to extra fields
    const DragDropEventArgs& dd_args =
        static_cast<const DragDropEventArgs&>(args);

	// make sure we drop a valid item
	if((dd_args.dragDropItem->getChildCount() > 1) && dd_args.dragDropItem->getChildAtIdx(1)->getID() == 2)
	{
		long Id = dd_args.dragDropItem->getID();
		LbaNet::ItemsMap::iterator itcontent = _InventoryContent.find(Id);
		if(itcontent != _InventoryContent.end())
			ChooseNumberBox::getInstance()->Show(this, Id, itcontent->second.Max, true);
	}

    return true;
}


/***********************************************************
drag and drop
***********************************************************/
bool ContainerBox::handle_ItemDroppedInInventory(const CEGUI::EventArgs& args)
{
    using namespace CEGUI;

    // cast the args to the 'real' type so we can get access to extra fields
    const DragDropEventArgs& dd_args =
        static_cast<const DragDropEventArgs&>(args);

	// make sure we drop a valid item
	if((dd_args.dragDropItem->getChildCount() > 1) && dd_args.dragDropItem->getChildAtIdx(1)->getID() == 3)
	{
		long Id = dd_args.dragDropItem->getID();
		LbaNet::ItemsMap::iterator itcontent = _ContainerContent.find(Id);
		if(itcontent != _ContainerContent.end())
			ChooseNumberBox::getInstance()->Show(this, Id, itcontent->second.Max, false);
	}

    return true;
}

/***********************************************************
drag and drop
***********************************************************/
bool ContainerBox::handle_ItemDroppedInContainerItem(const CEGUI::EventArgs& args)
{
    using namespace CEGUI;

    // cast the args to the 'real' type so we can get access to extra fields
    const DragDropEventArgs& dd_args =
        static_cast<const DragDropEventArgs&>(args);

	// make sure we drop a valid item
	if((dd_args.dragDropItem->getChildCount() > 1) && dd_args.dragDropItem->getChildAtIdx(1)->getID() == 2)
	{
		long Id = dd_args.dragDropItem->getID();
		LbaNet::ItemsMap::iterator itcontent = _InventoryContent.find(Id);
		if(itcontent != _InventoryContent.end())
			ChooseNumberBox::getInstance()->Show(this, Id, itcontent->second.Max, true);
	}

    return true;
}


/***********************************************************
drag and drop
***********************************************************/
bool ContainerBox::handle_ItemDroppedInInventoryItem(const CEGUI::EventArgs& args)
{
    using namespace CEGUI;

    // cast the args to the 'real' type so we can get access to extra fields
    const DragDropEventArgs& dd_args =
        static_cast<const DragDropEventArgs&>(args);

	// make sure we drop a valid item
	if((dd_args.dragDropItem->getChildCount() > 1) && dd_args.dragDropItem->getChildAtIdx(1)->getID() == 3)
	{
		long Id = dd_args.dragDropItem->getID();
		LbaNet::ItemsMap::iterator itcontent = _ContainerContent.find(Id);
		if(itcontent != _ContainerContent.end())
			ChooseNumberBox::getInstance()->Show(this, Id, itcontent->second.Max, false);
	}

    return true;
}





/***********************************************************
object clicked
***********************************************************/
bool ContainerBox::HandleContainerItemClicked (const CEGUI::EventArgs& e)
{
	const CEGUI::MouseEventArgs& dd_args = static_cast<const CEGUI::MouseEventArgs&>(e);

	// use object
	if(dd_args.button == CEGUI::RightButton)
	{
		switchfromcontainertoinventory(dd_args.window->getID(), 1);
	}

    return true;
}


/***********************************************************
object clicked
***********************************************************/
bool ContainerBox::HandleInventoryItemClicked (const CEGUI::EventArgs& e)
{
	const CEGUI::MouseEventArgs& dd_args = static_cast<const CEGUI::MouseEventArgs&>(e);

	// use object
	if(dd_args.button == CEGUI::RightButton)
	{
		switchfrominventorytocontainer(dd_args.window->getID(), 1);
	}

    return true;
}



/***********************************************************
close box and send update to server
***********************************************************/
void ContainerBox::CloseAndUpdate()
{
	_myBox->hide();
	if(_currContainerId >= 0)
	{
		LbaNet::GuiUpdatesSeq updseq;
		_serverupdate->Containerid = _currContainerId;
		updseq.push_back(_serverupdate);
		
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), "ContainerBox", updseq));
	}

	_currContainerId = -1;
}


/***********************************************************
cancel changes
***********************************************************/
void ContainerBox::Cancel()
{
	_serverupdate = new LbaNet::UpdateInvContainer(-1, LbaNet::ItemList(), LbaNet::ItemList());
}

/***********************************************************
take all item from container
***********************************************************/
void ContainerBox::TakeAll()
{
	Cancel();
	LbaNet::ItemsMap::const_iterator it = _ContainerContentStatic.begin();
	LbaNet::ItemsMap::const_iterator end = _ContainerContentStatic.end();
	for(; it != end; ++it)
		_serverupdate->Taken[it->first] = it->second.Count;
}




/***********************************************************
add an item inside the container
***********************************************************/
std::pair<CEGUI::Window*, CEGUI::Window*> ContainerBox::AddInventoryItem(const LbaNet::ItemInfo & itinfo, 
																			CEGUI::Window* parent, 
																			bool tocontainer)
{
	CEGUI::Window*	tmp = CEGUI::WindowManager::getSingleton().createWindow("DragContainer");
	tmp->setArea(CEGUI::UDim(0,0), CEGUI::UDim(0,0), CEGUI::UDim(1, 0), CEGUI::UDim(1, 0));
	tmp->setID((unsigned int)itinfo.Id);

	CEGUI::Window*	tmp2 = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage");
	tmp2->setArea(CEGUI::UDim(0,5.0f), CEGUI::UDim(0,12.0f), CEGUI::UDim(0, (float)_boxsize-10.0f), CEGUI::UDim(0, (float)_boxsize-20.0f));

	std::string imagesetname = ImageSetHandler::GetInventoryImage(itinfo.IconName);
	tmp2->setProperty("Image", "set:" + imagesetname + " image:full_image");
	tmp2->setProperty("MousePassThroughEnabled", "True");



	CEGUI::Window*	tmp3 = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText");
	tmp3->setArea(CEGUI::UDim(0,2), CEGUI::UDim(0,4), CEGUI::UDim(1, -1), CEGUI::UDim(0, 14));
	tmp3->setProperty("FrameEnabled", "False");
	tmp3->setProperty("BackgroundEnabled", "False");
	tmp3->setProperty("MousePassThroughEnabled", "True");
	tmp3->setAlwaysOnTop(true);
	tmp3->setProperty("Font" , "contourfont");

	std::stringstream strs;
	strs<<itinfo.Count;
	tmp3->setText(strs.str().c_str());
	if(tocontainer)
		tmp3->setID(3);
	else
		tmp3->setID(2);


	std::string itemdescription = itinfo.DescriptionTextExtra;
	if(itemdescription == "")
		itemdescription = DataLoader::getInstance()->GetInventoryText((long)itinfo.DescriptionId);

	CEGUI::String tmpstr((const unsigned char *)itemdescription.c_str());
	tmp->setProperty("Tooltip", tmpstr);
	tmp->addChildWindow(tmp2);
	tmp->addChildWindow(tmp3);
	parent->addChildWindow(tmp);

	if(tocontainer)
	{
		tmp->subscribeEvent(
					CEGUI::Window::EventDragDropItemDropped,
					CEGUI::Event::Subscriber(&ContainerBox::handle_ItemDroppedInContainerItem, this));
	
		tmp->subscribeEvent (CEGUI::Window::EventMouseClick,
								CEGUI::Event::Subscriber (&ContainerBox::HandleContainerItemClicked, this));
	}
	else
	{
		tmp->subscribeEvent(
					CEGUI::Window::EventDragDropItemDropped,
					CEGUI::Event::Subscriber(&ContainerBox::handle_ItemDroppedInInventoryItem, this));
	
		tmp->subscribeEvent (CEGUI::Window::EventMouseClick,
								CEGUI::Event::Subscriber (&ContainerBox::HandleInventoryItemClicked, this));
	}


	return std::make_pair<CEGUI::Window*, CEGUI::Window*>(tmp, tmp3);
}



/***********************************************************
clean container items
***********************************************************/
void ContainerBox::CleanContainer()
{
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator it = _cont_objects.begin();
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator end = _cont_objects.end();
	for(;it != end; ++it)
		it->second.first->destroy();

	_cont_objects.clear();
}


/***********************************************************
refresh Container
***********************************************************/
void ContainerBox::RefreshContainer()
{
	CleanContainer();
	LbaNet::ItemsMap::const_iterator itm = _ContainerContent.begin();
	LbaNet::ItemsMap::const_iterator endm = _ContainerContent.end();
	for(int cc=0;itm != endm && cc < _NB_BOX_CONTAINER_; ++itm, ++cc)
		_cont_objects[itm->first] = AddInventoryItem(itm->second, _cont_boxes[cc], true);
}

/***********************************************************
resize inventory
***********************************************************/
void ContainerBox::ResizeInventory(int newsize)
{
	if(_inventory_size == newsize)
		return;

	_inventory_size = newsize;
	for(size_t i=0; i<_inv_boxes.size(); ++i)
		_inv_boxes[i]->destroy();

	_inv_boxes.clear();


	CEGUI::Window*	pane = CEGUI::WindowManager::getSingleton().getWindow("ContainerFrame/InvScrollable");
	CEGUI::Window*	tmpwindow;
	for(int i=0; i<_inventory_size; ++i)
	{
		int x = i / 4;
		int y = i % 4;

		tmpwindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText");
		tmpwindow->setArea(CEGUI::UDim(0,5+((float)_boxsize+2)*y), CEGUI::UDim(0,5+((float)_boxsize+2.0f)*x),
							CEGUI::UDim(0, (float)_boxsize), CEGUI::UDim(0, (float)_boxsize));
		pane->addChildWindow(tmpwindow);

        tmpwindow->subscribeEvent(
					CEGUI::Window::EventDragDropItemDropped,
					CEGUI::Event::Subscriber(&ContainerBox::handle_ItemDroppedInInventory, this));

		tmpwindow->setID(i);
		_inv_boxes.push_back(tmpwindow);
	}

	CleanInventory();
}



/***********************************************************
clean inventory
***********************************************************/
void ContainerBox::CleanInventory()
{
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator it = _inv_objects.begin();
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator end = _inv_objects.end();
	for(;it != end; ++it)
		it->second.first->destroy();

	_inv_objects.clear();
}


/***********************************************************
refresh inventory
***********************************************************/
void ContainerBox::RefreshInventory()
{
	CleanInventory();

	LbaNet::ItemsMap::const_iterator itm = _InventoryContent.begin();
	LbaNet::ItemsMap::const_iterator endm = _InventoryContent.end();
	for(;itm != endm; ++itm)
		_inv_objects[itm->first] = AddInventoryItem(itm->second, _inv_boxes[itm->second.Position], false);
}

		
/***********************************************************
add an item from container to inventory
return the number taken
***********************************************************/
int ContainerBox::AddItemFromContainerToInventory(long Id, int number)
{
	// check if we already have an item of this type
	LbaNet::ItemsMap::iterator itc = _InventoryContent.find(Id);
	if(itc == _InventoryContent.end())
	{
		// if not check for an empty space in inventory	
		CEGUI::Window*  parent = FindFirstInventoryEmptySpace();

		// if container full then return
		if(parent == NULL)
			return 0;

		LbaNet::ItemsMap::iterator inventoryptr = _ContainerContent.find(Id);
		if(inventoryptr != _ContainerContent.end())
		{
			LbaNet::ItemInfo tmp = inventoryptr->second;
			tmp.Count = 0;
			_InventoryContent[Id] = tmp;
			itc = _InventoryContent.find(Id);

			// add container item
			_inv_objects[Id] = AddInventoryItem(tmp, parent, false);
		}
		else
			return 0;

	}

	// update numbers
	int max = itc->second.Max;
	int current = itc->second.Count;
	int taken = std::min((max-current), number);

	if(taken > 0)
	{
		itc->second.Count = (current+taken);
		std::stringstream strs;
		strs<<(current+taken);
		_inv_objects[Id].second->setText(strs.str().c_str());
	}

	return taken;
}



/***********************************************************
add an item from container to inventory
return the number taken
***********************************************************/
int ContainerBox::AddItemFromInventoryToContainer(long Id, int number)
{
	// check if we already have an item of this type
	LbaNet::ItemsMap::iterator itc = _ContainerContent.find(Id);
	if(itc == _ContainerContent.end())
	{
		// if not check for an empty space in inventory	
		CEGUI::Window*  parent = FindFirstContainerEmptySpace();

		// if container full then return
		if(parent == NULL)
			return 0;

		LbaNet::ItemsMap::iterator inventoryptr = _InventoryContent.find(Id);
		if(inventoryptr != _InventoryContent.end())
		{
			LbaNet::ItemInfo tmp = inventoryptr->second;
			tmp.Count = 0;
			_ContainerContent[Id] = tmp;
			itc = _ContainerContent.find(Id);

			// add container item
			_cont_objects[Id] = AddInventoryItem(tmp, parent, true);
		}
		else
			return 0;

	}

	// update numbers
	int max = itc->second.Max;
	int current = itc->second.Count;
	int taken = std::min((max-current), number);

	if(taken > 0)
	{
		itc->second.Count = (current+taken);
		std::stringstream strs;
		strs<<(current+taken);
		_cont_objects[Id].second->setText(strs.str().c_str());
	}

	return taken;
}


/***********************************************************
switch item from container to inventory
***********************************************************/
void ContainerBox::switchfromcontainertoinventory(long Id, long number)
{
	LbaNet::ItemsMap::iterator itcontent = _ContainerContent.find(Id);
	if(itcontent != _ContainerContent.end())
	{
		int taken = AddItemFromContainerToInventory(Id, number);
		if(taken > 0)
		{
			std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator itcont = 
																_cont_objects.find(itcontent->first);
			itcontent->second.Count -= taken;
			if(itcontent->second.Count <= 0)
			{
				if(itcont != _cont_objects.end())
				{
					CEGUI::WindowManager::getSingleton().destroyWindow(itcont->second.first);
					_cont_objects.erase(itcont);
				}
				_ContainerContent.erase(itcontent);
			}
			else
			{
				if(itcont != _cont_objects.end())
				{	
					std::stringstream strs;
					strs<<itcontent->second.Count;
					itcont->second.second->setText(strs.str().c_str());
				}
			}

			UpdateTakenPut(Id, -taken);
		}
	}
}


/***********************************************************
switch item from inventory to container
***********************************************************/
void ContainerBox::switchfrominventorytocontainer(long Id, long number)
{
	LbaNet::ItemsMap::iterator itinv = _InventoryContent.find(Id);
	if(itinv != _InventoryContent.end())
	{
		int taken = AddItemFromInventoryToContainer(Id, number);
		if(taken > 0)
		{
			std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator itcont = 
																_inv_objects.find(itinv->first);
			itinv->second.Count -= taken;
			if(itinv->second.Count <= 0)
			{
				if(itcont != _inv_objects.end())
				{
					CEGUI::WindowManager::getSingleton().destroyWindow(itcont->second.first);
					_cont_objects.erase(itcont);
				}
				_InventoryContent.erase(itinv);
			}
			else
			{
				if(itcont != _cont_objects.end())
				{	
					std::stringstream strs;
					strs<<itinv->second.Count;
					itcont->second.second->setText(strs.str().c_str());
				}
			}

			UpdateTakenPut(Id, -taken);
		}
	}
}


/***********************************************************
update taken and put vectors with last change from user
***********************************************************/
void ContainerBox::UpdateTakenPut(long itid, int deltaupd)
{
	// nothing to do
	if(deltaupd == 0)
		return;

	// we take an item from container
	if(deltaupd < 0)
	{
		// check if we have same item in put vector
		LbaNet::ItemList::iterator itp = _serverupdate->Put.find(itid);
		if(itp != _serverupdate->Put.end())
		{
			int nb = itp->second;
			if(nb <= -deltaupd)
			{
				deltaupd += nb;
				_serverupdate->Put.erase(itp);
			}
			else
			{
				itp->second += deltaupd;
				deltaupd = 0;
			}

			// nothing more to do
			if(deltaupd == 0)
				return;
		}

		//now add item to taken part
		LbaNet::ItemList::iterator itt = _serverupdate->Taken.find(itid);
		if(itt != _serverupdate->Taken.end())
			itt->second += -deltaupd;
		else
			_serverupdate->Taken[itid] = -deltaupd;
	}
	else // we add an item to container
	{
		// check if we have same item in taken vector
		LbaNet::ItemList::iterator itt = _serverupdate->Taken.find(itid);
		if(itt != _serverupdate->Taken.end())
		{
			int nb = itt->second;
			if(nb <= deltaupd)
			{
				deltaupd -= nb;
				_serverupdate->Taken.erase(itt);
			}
			else
			{
				itt->second -= deltaupd;
				deltaupd = 0;
			}

			// nothing more to do
			if(deltaupd == 0)
				return;
		}

		//now add item to put part
		LbaNet::ItemList::iterator itp = _serverupdate->Put.find(itid);
		if(itp != _serverupdate->Put.end())
			itp->second += deltaupd;
		else
			_serverupdate->Put[itid] = deltaupd;
	}
}



/***********************************************************
find first empty space in container
***********************************************************/
CEGUI::Window*  ContainerBox::FindFirstContainerEmptySpace()
{
	for(size_t i=0; i<_cont_boxes.size(); ++i)
	{
		if(_cont_boxes[i]->getChildCount() == 2)
			return _cont_boxes[i];
	}

	return NULL;
}


/***********************************************************
find first empty space in inventory
***********************************************************/
CEGUI::Window* ContainerBox::FindFirstInventoryEmptySpace()
{
	for(size_t i=0; i<_inv_boxes.size(); ++i)
	{
		if(_inv_boxes[i]->getChildCount() == 2)
			return _inv_boxes[i];
	}

	return NULL;
}




/***********************************************************
refresh inventory images
***********************************************************/
void  ContainerBox::Refresh()
{
	if(_myBox->isVisible())
	{
		_myBox->hide();
		_myBox->show();
		_myBox->activate();
	}

	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator it = _cont_objects.begin();
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator end = _cont_objects.end();
	for(; it != end; ++it)
	{
		
		std::string imagesetname = ImageSetHandler::GetInventoryImage(_ContainerContent[it->first].IconName);
		it->second.first->getChildAtIdx(0)->setProperty("Image", "set:" + imagesetname + " image:full_image");
	}

	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator it2 = _inv_objects.begin();
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator end2 = _inv_objects.end();
	for(; it2 != end2; ++it2)
	{
		std::string imagesetname = ImageSetHandler::GetInventoryImage(_InventoryContent[it2->first].IconName);
		it2->second.first->getChildAtIdx(0)->setProperty("Image", "set:" + imagesetname + " image:full_image");
	}
}



/***********************************************************
callback
***********************************************************/
void ContainerBox::CallbackChooseNumber(long id, long choosennumber, bool flag)
{
	if(flag)
		switchfrominventorytocontainer(id, choosennumber);
	else
		switchfromcontainertoinventory(id, choosennumber);
}



/***********************************************************
catch key event
***********************************************************/
bool ContainerBox::HandleEnterKey (const CEGUI::EventArgs& e)
{
	const CEGUI::KeyEventArgs& we =
    static_cast<const CEGUI::KeyEventArgs&>(e);

	if(we.scancode == CEGUI::Key::Space || we.scancode == CEGUI::Key::W)
	{
		return HandleTakeAll(e);
	}

	return false;
}



/***********************************************************
refresh gui with info from server
***********************************************************/
void ContainerBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{
	for(size_t i=0; i<Parameters.size(); ++i)
	{
		LbaNet::GuiParameterBase * ptr = Parameters[i].get();
		const std::type_info& info = typeid(*ptr);

		// got player online list refresh event
		if(info == typeid(LbaNet::ContainerGuiParameter))
		{
			LbaNet::ContainerGuiParameter * castedptr = 
				dynamic_cast<LbaNet::ContainerGuiParameter *>(ptr);

			_currContainerId = castedptr->ContainerId;

			_ContainerContentStatic = castedptr->ContainerContent;
			_ContainerContent = castedptr->ContainerContent;
			_InventoryContent = castedptr->InventoryContent;
			_serverupdate = new LbaNet::UpdateInvContainer(-1, LbaNet::ItemList(), LbaNet::ItemList());

			// update container part
			RefreshContainer();

			//update inventory part
			ResizeInventory(castedptr->InventorySize);
			RefreshInventory();
		}
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void ContainerBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{

}

/***********************************************************
show GUI
***********************************************************/
void ContainerBox::Display()
{
	_myBox->show();
	_myBox->activate();
}

/***********************************************************
hide GUI
***********************************************************/
void ContainerBox::Hide()
{
	_myBox->hide();
}

/***********************************************************
show/hide GUI
***********************************************************/
void ContainerBox::ToggleDisplay()
{
	if(_myBox->isVisible())
		_myBox->hide();
	else
	{
		_myBox->show();
		_myBox->activate();
	}
}

/***********************************************************
focus GUI
***********************************************************/
void ContainerBox::Focus(bool focus)
{

}
