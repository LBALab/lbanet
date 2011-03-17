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

#include "InventoryBox.h"
#include "GameGUI.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "ImageSetHandler.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "DataLoader.h"
#include "OSGHandler.h"
#include "Localizer.h"
#include "GUILocalizationCallback.h"
#include "ClientExtendedEvents.h"

#include <iostream>
#include <algorithm>
#include <CEGUI.h>


/***********************************************************
constructor
***********************************************************/
InventoryBox::InventoryBox(int boxsize)
: _inventory_size(0), _boxsize(boxsize)
{



}


/***********************************************************
destructor
***********************************************************/
InventoryBox::~InventoryBox()
{
	try
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("InventoryFrame"));

		int resX, resY; 
		bool fullscreen;
		OsgHandler::getInstance()->GetScreenAttributes(resX, resY, fullscreen);

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.Inventorybox.PosX", vec.d_x.asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Inventorybox.PosY", vec.d_y.asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Inventorybox.SizeX", frw->getWidth().asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Inventorybox.SizeY", frw->getHeight().asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetBool("Gui.Inventorybox.Visible", frw->isVisible());
	
		CEGUI::FrameWindow * frw2 = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("InventoryInformHappyFrame"));

		CEGUI::UVector2 vec2 = frw2->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.Inventoryboxhappy.PosX", vec2.d_x.asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Inventoryboxhappy.PosY", vec2.d_y.asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Inventoryboxhappy.SizeX", frw2->getWidth().asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Inventoryboxhappy.SizeY", frw2->getHeight().asRelative((float)resY));	
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception destructor Inventorybox: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
initalize the box
***********************************************************/
void InventoryBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "inventory.layout",
								"", "", &MyPropertyCallback);
		Root->addChildWindow(_myBox);


		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("InventoryFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&InventoryBox::HandleClose, this));

		frw->subscribeEvent(
			CEGUI::FrameWindow::EventSized,
			CEGUI::Event::Subscriber (&InventoryBox::HandleResize, this));

		{
		float PosX, PosY, SizeX, SizeY;
		bool Visible;
		ConfigurationManager::GetInstance()->GetFloat("Gui.Inventorybox.PosX", PosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Inventorybox.PosY", PosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Inventorybox.SizeX", SizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Inventorybox.SizeY", SizeY);
		ConfigurationManager::GetInstance()->GetBool("Gui.Inventorybox.Visible", Visible);
		frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, 0), CEGUI::UDim(PosY, 0)));
		frw->setWidth(CEGUI::UDim(SizeX, 0));
		frw->setHeight(CEGUI::UDim(SizeY, 0));

		if(Visible)
			frw->show();
		else
			frw->hide();	
		}



		_myBox2 = CEGUI::WindowManager::getSingleton().loadWindowLayout( "inventoryhappy.layout",
								"", "", &MyPropertyCallback);
		Root->addChildWindow(_myBox2);
		_myBox2->hide();

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("InventoryInformHappyFrame/bok"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&InventoryBox::HandleHappyOkButton, this));



		{
		CEGUI::FrameWindow * frw2 = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("InventoryInformHappyFrame"));

		float PosX, PosY, SizeX, SizeY;
		ConfigurationManager::GetInstance()->GetFloat("Gui.Inventoryboxhappy.PosX", PosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Inventoryboxhappy.PosY", PosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Inventoryboxhappy.SizeX", SizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Inventoryboxhappy.SizeY", SizeY);
		frw2->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, 0), CEGUI::UDim(PosY, 0)));
		frw2->setWidth(CEGUI::UDim(SizeX, 0));
		frw2->setHeight(CEGUI::UDim(SizeY, 0));
	
		frw2->subscribeEvent(CEGUI::Window::EventKeyDown,
								CEGUI::Event::Subscriber (&InventoryBox::HandleEnterKey, this));

		}


	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init InventoryBox: ") + ex.getMessage().c_str());
	}
}




/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool InventoryBox::HandleClose (const CEGUI::EventArgs& e)
{
	_myBox->hide();
	return true;
}





/***********************************************************
handle windows resize event
***********************************************************/
bool InventoryBox::HandleResize (const CEGUI::EventArgs& e)
{
	ResizeBox();
	return false;
}


/***********************************************************
resize inventory
***********************************************************/
void InventoryBox::ResizeBox()
{
	CEGUI::Window*	win = CEGUI::WindowManager::getSingleton().getWindow("InventoryFrame");
	CEGUI::Rect rect = win->getInnerRectClipper();
	float width = rect.getSize().d_width-5;
	int nbboxhori = (int)width / (_boxsize+2);
	if(nbboxhori > 0)
	{
		for(int i=0; i<(int)_inv_boxes.size(); ++i)
		{
			int x = i / nbboxhori;
			int y = i % nbboxhori;

			_inv_boxes[i]->setPosition(CEGUI::UVector2(CEGUI::UDim(0.0f,(float)5+((_boxsize+2)*y)), 
														CEGUI::UDim(0.0f,(float)((_boxsize+2)*x))
														));
		}
	}
}



/***********************************************************
update item to the inventory
if item didnt exist add it to the inventory
if number = 0 remove it from inventory
if no more place in inventory when adding then return false
***********************************************************/
bool InventoryBox::UpdateItem(long Id, const std::string & Description,
								long number, const std::string & iconname, int PlaceInInventory)
{
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator it = _objects.find(Id);

	// if we already have object in inventory just update it
	if(it != _objects.end())
	{
		// if number is 0 then destroy the object
		if(number <= 0)
		{
			it->second.first->destroy();
			_objects.erase(it);
		}
		else // else update the object number
		{
			std::stringstream strs;
			strs<<number;
			CEGUI::Window*	tmp = it->second.second;
			if(tmp)
				tmp->setText(strs.str().c_str());	
		}
	}
	else
	{
		if(number > 0)
		{
			CEGUI::Window* parent = NULL;
			if(PlaceInInventory >= 0)
				parent = _inv_boxes[PlaceInInventory];
			else
			{
				parent = FindFirstEmptySpace();
				if(parent != NULL)
				{
					LbaNet::GuiUpdatesSeq updseq;
					LbaNet::SwitchItemPosition * upd = 
						new LbaNet::SwitchItemPosition(Id, parent->getID());
					updseq.push_back(upd);
					_inventoryinfo[Id].Position = parent->getID();

					EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "InventoryBox", updseq));
				}
			}

			if(parent == NULL)
				return false;

			CEGUI::Window*	tmp = CEGUI::WindowManager::getSingleton().createWindow("DragContainer");
			tmp->setArea(CEGUI::UDim(0,0), CEGUI::UDim(0,0), CEGUI::UDim(1, 0), CEGUI::UDim(1, 0));
			tmp->setID(Id);

			CEGUI::Window*	tmp2 = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage");
			tmp2->setArea(CEGUI::UDim(0.0f,5.0f), CEGUI::UDim(0.0f,12.0f), CEGUI::UDim(0.0f, (float)(_boxsize-10)), CEGUI::UDim(0.0f, (float)(_boxsize-20)));

			std::string imagesetname = ImageSetHandler::GetInventoryImage(iconname);
			tmp2->setProperty("Image", "set:" + imagesetname + " image:full_image");
			tmp2->setProperty("MousePassThroughEnabled", "True");



			CEGUI::Window*	tmp3 = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText");
			tmp3->setArea(CEGUI::UDim(0,2), CEGUI::UDim(0,4), CEGUI::UDim(1, -1), CEGUI::UDim(0, 14));
			tmp3->setProperty("FrameEnabled", "False");
			tmp3->setProperty("BackgroundEnabled", "False");
			tmp3->setProperty("MousePassThroughEnabled", "True");
			tmp3->setProperty("Font" , "contourfont");
			tmp3->setAlwaysOnTop(true);
			std::stringstream strs;
			strs<<number;
			tmp3->setText(strs.str().c_str());
			tmp3->setID(1);


			CEGUI::String tmpstr((const unsigned char *)Description.c_str());
			tmp->setProperty("Tooltip", tmpstr);
			tmp->addChildWindow(tmp2);
			tmp->addChildWindow(tmp3);
			parent->addChildWindow(tmp);


            tmp->subscribeEvent(
						CEGUI::Window::EventDragDropItemDropped,
						CEGUI::Event::Subscriber(&InventoryBox::handle_ItemDroppedOnItem, this));


            tmp->subscribeEvent (CEGUI::Window::EventMouseClick,
									CEGUI::Event::Subscriber (&InventoryBox::HandleObjectClicked, this));
			

			_objects[Id] = std::make_pair<CEGUI::Window*, CEGUI::Window*>(tmp, tmp3);
		}
	}

	return true;
}



/***********************************************************
find first empty space in inventory
***********************************************************/
CEGUI::Window* InventoryBox::FindFirstEmptySpace()
{
	for(size_t i=0; i<_inv_boxes.size(); ++i)
	{
		if(_inv_boxes[i]->getChildCount() == 2)
			return _inv_boxes[i];
	}

	return NULL;
}



/***********************************************************
drag and drop
***********************************************************/
bool InventoryBox::handle_ItemDropped(const CEGUI::EventArgs& args)
{
    using namespace CEGUI;

    // cast the args to the 'real' type so we can get access to extra fields
    const DragDropEventArgs& dd_args =
        static_cast<const DragDropEventArgs&>(args);

	// make sure we drop a valid item
	if((dd_args.dragDropItem->getChildCount() > 1) && dd_args.dragDropItem->getChildAtIdx(1)->getID() == 1)
	{
		if (dd_args.window->getChildCount() == 2)
		{
			// add dragdrop item as child of target if target has no item already
			dd_args.window->addChildWindow(dd_args.dragDropItem);

			// Now we must reset the item position from it's 'dropped' location,
			// since we're now a child of an entirely different window
			dd_args.dragDropItem->setPosition(UVector2(UDim(0, 0),UDim(0, 0)));


			LbaNet::GuiUpdatesSeq updseq;
				LbaNet::SwitchItemPosition * upd = 
					new LbaNet::SwitchItemPosition(dd_args.dragDropItem->getID(), dd_args.window->getID());
				updseq.push_back(upd);
				_inventoryinfo[dd_args.dragDropItem->getID()].Position = dd_args.window->getID();

				EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
					SynchronizedTimeHandler::GetCurrentTimeDouble(), "InventoryBox", updseq));
		}
	}

    return true;
}



/***********************************************************
drag and drop
***********************************************************/
bool InventoryBox::handle_ItemDroppedOnItem(const CEGUI::EventArgs& args)
{
    using namespace CEGUI;

    // cast the args to the 'real' type so we can get access to extra fields
    const DragDropEventArgs& dd_args =
        static_cast<const DragDropEventArgs&>(args);

	// make sure we drop a valid item
	if((dd_args.dragDropItem->getChildCount() > 1) && dd_args.dragDropItem->getChildAtIdx(1)->getID() == 1)
	{
		CEGUI::Window* parent1 = dd_args.window->getParent();
		CEGUI::Window* parent2 = dd_args.dragDropItem->getParent();

		parent1->addChildWindow(dd_args.dragDropItem);
		dd_args.dragDropItem->setPosition(UVector2(UDim(0, 0),UDim(0, 0)));

		parent2->addChildWindow(dd_args.window);
		dd_args.window->setPosition(UVector2(UDim(0, 0),UDim(0, 0)));


		LbaNet::GuiUpdatesSeq updseq;
		LbaNet::SwitchItemPosition * upd = 
			new LbaNet::SwitchItemPosition(dd_args.dragDropItem->getID(), parent1->getID());
		updseq.push_back(upd);
		_inventoryinfo[dd_args.dragDropItem->getID()].Position = parent1->getID();

		LbaNet::SwitchItemPosition * upd2 = 
			new LbaNet::SwitchItemPosition(dd_args.window->getID(), parent2->getID());
		updseq.push_back(upd2);		
		_inventoryinfo[dd_args.window->getID()].Position = parent2->getID();


		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), "InventoryBox", updseq));
	}

    return true;
}


/***********************************************************
object clicked
***********************************************************/
bool InventoryBox::HandleObjectClicked (const CEGUI::EventArgs& e)
{
	const CEGUI::MouseEventArgs& dd_args = static_cast<const CEGUI::MouseEventArgs&>(e);

	// use object
	if(dd_args.button == CEGUI::RightButton)
	{
		unsigned int id = dd_args.window->getID();


		LbaNet::GuiUpdatesSeq updseq;
		LbaNet::InventoryItemUsed * upd = 
			new LbaNet::InventoryItemUsed(id);
		updseq.push_back(upd);

		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), "InventoryBox", updseq));
	}


    return true;
}



/***********************************************************
handle GO button pressed
***********************************************************/
bool InventoryBox::HandleHappyOkButton (const CEGUI::EventArgs& e)
{
	EventsQueue::getReceiverQueue()->AddEvent(new InternalUpdateStateEvent(LbaNet::StNormal));

	try
	{
		_myBox2->hide();
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception hide happy windows: ") + ex.getMessage().c_str());
	}

	return true;
}


/***********************************************************
empty the inventory
***********************************************************/
void InventoryBox::CleanInventory()
{
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator it = _objects.begin();
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator end = _objects.end();
	for(;it != end; ++it)
		it->second.first->destroy();

	_objects.clear();
}


/***********************************************************
resize inventory
***********************************************************/
void InventoryBox::ResizeInventory(int newsize)
{
	if(_inventory_size == newsize)
		return;

	_inventory_size = newsize;
	for(size_t i=0; i<_inv_boxes.size(); ++i)
		_inv_boxes[i]->destroy();

	_inv_boxes.clear();


	CEGUI::Window*	pane = CEGUI::WindowManager::getSingleton().getWindow("InventoryFrame/Scrollable");
	CEGUI::Window*	tmpwindow;
	for(int i=0; i<_inventory_size; ++i)
	{
		tmpwindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText");
		tmpwindow->setArea(CEGUI::UDim(0,0), CEGUI::UDim(0,0), 
							CEGUI::UDim(0, (float)_boxsize), CEGUI::UDim(0, (float)_boxsize));
		pane->addChildWindow(tmpwindow);

        tmpwindow->subscribeEvent(
					CEGUI::Window::EventDragDropItemDropped,
					CEGUI::Event::Subscriber(&InventoryBox::handle_ItemDropped, this));

		tmpwindow->setID(i);
		_inv_boxes.push_back(tmpwindow);
	}

	ResizeBox();
}



/***********************************************************
refresh inventory images
***********************************************************/
void InventoryBox::Refresh()
{
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator it = _objects.begin();
	std::map<Ice::Long, std::pair<CEGUI::Window*, CEGUI::Window*> >::iterator end = _objects.end();
	for(; it != end; ++it)
	{
		std::string imagesetname = ImageSetHandler::GetInventoryImage(_inventoryinfo[it->first].Info.IconName);
		it->second.first->getChildAtIdx(0)->setProperty("Image", "set:" + imagesetname + " image:full_image");
	}
}



/***********************************************************
refresh gui with info from server
***********************************************************/
void InventoryBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{
	for(size_t i=0; i<Parameters.size(); ++i)
	{
		LbaNet::GuiParameterBase * ptr = Parameters[i].get();
		const std::type_info& info = typeid(*ptr);

		// got player online list refresh event
		if(info == typeid(LbaNet::InventoryGuiParameter))
		{
			LbaNet::InventoryGuiParameter * castedptr = 
				dynamic_cast<LbaNet::InventoryGuiParameter *>(ptr);

			CleanInventory();

			int inventorysize = castedptr->InventorySize;	
			if(inventorysize > 500)
			{
				LogHandler::getInstance()->LogToFile("Problem with inventory size - much bigger than expected!!");
				inventorysize = 500;
			}
			ResizeInventory(inventorysize);

			_inventoryinfo = castedptr->InventoryContent;
			RefreshInventory();
		}
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void InventoryBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{
	for(size_t i=0; i<Updates.size(); ++i)
	{
		LbaNet::GuiUpdateBase * ptr = Updates[i].get();
		const std::type_info& info = typeid(*ptr);

		// UpdateInventorySize
		if(info == typeid(LbaNet::UpdateInventorySize))
		{
			LbaNet::UpdateInventorySize * castedptr = 
				dynamic_cast<LbaNet::UpdateInventorySize *>(ptr);

			CleanInventory();

			int inventorysize = castedptr->NewSize;
			if(inventorysize > 500)
			{
				LogHandler::getInstance()->LogToFile("Problem with inventory size - much bigger than expected!!");
				inventorysize = 500;
			}
			ResizeInventory(inventorysize);
			RefreshInventory();
		}

		// UpdateInventoryItem
		if(info == typeid(LbaNet::UpdateInventoryItem))
		{
			LbaNet::UpdateInventoryItem * castedptr = 
				dynamic_cast<LbaNet::UpdateInventoryItem *>(ptr);

			LbaNet::ItemPosInfo & itinfo = castedptr->Info;

			std::string itemdescription = itinfo.Info.DescriptionTextExtra;
			if(itemdescription == "")
			{
				itemdescription = Localizer::getInstance()->GetText(Localizer::Inventory, (long)itinfo.Info.NameTextId);
				itemdescription += ": ";
				itemdescription += Localizer::getInstance()->GetText(Localizer::Inventory, (long)itinfo.Info.DescriptionId);
			}

			int oldcount = 0;
			LbaNet::ItemsMap::iterator it = _inventoryinfo.find(itinfo.Info.Id);
			if(it != _inventoryinfo.end())
				oldcount = it->second.Count;


			std::string itedesc = itinfo.Info.DescriptionTextExtra;
			if(itedesc == "")
				itedesc = Localizer::getInstance()->GetText(Localizer::Inventory, (long)itinfo.Info.DescriptionId);
			std::string nametxtdesc = Localizer::getInstance()->GetText(Localizer::Inventory, (long)itinfo.Info.NameTextId);
			std::string itelongdesc = Localizer::getInstance()->GetText(Localizer::Inventory, (long)itinfo.Info.LongDescriptionId);


			InformUserItemUpdate((long)itinfo.Info.Id, castedptr->Informtype, itinfo.Count-oldcount,
									nametxtdesc, itedesc, itelongdesc, itinfo.Info.IconName);

			if(itinfo.Count > 0)
				_inventoryinfo[itinfo.Info.Id] = itinfo;
			else
			{
				// destroy object if exist
				
				if(it != _inventoryinfo.end())
					_inventoryinfo.erase(it);
			}


			UpdateItem((long)itinfo.Info.Id, itemdescription, itinfo.Count, itinfo.Info.IconName, itinfo.Position);
		}
	}
}

/***********************************************************
show GUI
***********************************************************/
void InventoryBox::Display()
{
	_myBox->show();
	_myBox->activate();
}

/***********************************************************
hide GUI
***********************************************************/
void InventoryBox::Hide()
{
	_myBox->hide();
}

/***********************************************************
show/hide GUI
***********************************************************/
void InventoryBox::ToggleDisplay()
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
void InventoryBox::Focus(bool focus)
{

}



/***********************************************************
refresh inventory display
***********************************************************/
void InventoryBox::RefreshInventory()
{	
	LbaNet::ItemsMap::const_iterator it = _inventoryinfo.begin();
	LbaNet::ItemsMap::const_iterator  end = _inventoryinfo.end();
	for(; it != end; ++it)
	{
		std::string itemdescription = it->second.Info.DescriptionTextExtra;
		if(itemdescription == "")
		{
			itemdescription = Localizer::getInstance()->GetText(Localizer::Inventory, (long)it->second.Info.NameTextId);
			itemdescription += ": ";
			itemdescription += Localizer::getInstance()->GetText(Localizer::Inventory, (long)it->second.Info.DescriptionId);
		}

		if(it->second.Count > 0)
			UpdateItem((long)it->first, itemdescription, it->second.Count, it->second.Info.IconName, it->second.Position);
	}
}



/***********************************************************
get info about an item in inventory
***********************************************************/
LbaNet::ItemInfo InventoryBox::GetItemInfo(Ice::Long itemid)
{
	LbaNet::ItemsMap::iterator it = _inventoryinfo.find(itemid);
	if(it != _inventoryinfo.end())
		return it->second.Info;
	else
	{
		LbaNet::ItemInfo res;
		res.Id = -1;
		return res;
	}
}




/***********************************************************
save size of windows to be restored after resize of the application
***********************************************************/
void InventoryBox::SaveGUISizes(int oldscreenX, int oldscreenY)
{
	{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("InventoryFrame"));

	CEGUI::UVector2 vec = frw->getPosition();
	_savedPosX = vec.d_x.asRelative((float)oldscreenX);
	_savedPosY = vec.d_y.asRelative((float)oldscreenY);
	_savedSizeX = frw->getWidth().asRelative((float)oldscreenX);
	_savedSizeY = frw->getHeight().asRelative((float)oldscreenY);
	}

	{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("InventoryInformHappyFrame"));

	CEGUI::UVector2 vec = frw->getPosition();
	_savedPosX2 = vec.d_x.asRelative((float)oldscreenX);
	_savedPosY2 = vec.d_y.asRelative((float)oldscreenY);
	_savedSizeX2 = frw->getWidth().asRelative((float)oldscreenX);
	_savedSizeY2 = frw->getHeight().asRelative((float)oldscreenY);
	}
}


/***********************************************************
restore the correct size of the windows
***********************************************************/
void InventoryBox::RestoreGUISizes()
{
	{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("InventoryFrame"));

	frw->setPosition(CEGUI::UVector2(CEGUI::UDim(_savedPosX, 0), CEGUI::UDim(_savedPosY, 0)));
	frw->setWidth(CEGUI::UDim(_savedSizeX, 0));
	frw->setHeight(CEGUI::UDim(_savedSizeY, 0));
	}

	{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("InventoryInformHappyFrame"));

	frw->setPosition(CEGUI::UVector2(CEGUI::UDim(_savedPosX2, 0), CEGUI::UDim(_savedPosY2, 0)));
	frw->setWidth(CEGUI::UDim(_savedSizeX2, 0));
	frw->setHeight(CEGUI::UDim(_savedSizeY2, 0));
	}
}



/***********************************************************
inform user of item update
***********************************************************/
void InventoryBox::InformUserItemUpdate(long itemId, LbaNet::ItemClientInformType Informtype, int count,
											const std::string & name, const std::string & Description,
											const std::string & LongDescription, const std::string & iconname)
{
	switch(Informtype)
	{
		case LbaNet::InformChat:
		{
			InformChat(itemId, count, name, Description, Description, iconname);
		}
		break;

		case LbaNet::InformHappy:
		{
			if(count < 0)
				InformChat(itemId, count, name, Description, LongDescription, iconname);
			else
				InformHappy(itemId, count, name, Description, LongDescription, iconname);
		}
		break;
	}
}


/***********************************************************
inform user of item update
***********************************************************/
void InventoryBox::InformChat(long itemId, int count, const std::string & name, const std::string & Description,
								const std::string & LongDescription, const std::string & iconname)
{
	if(count == 0)
		return;

	std::stringstream strs;
	if(count > 0)
		strs<<Localizer::getInstance()->GetText(Localizer::GUI, 93)<<" "<<count;
	else
		strs<<Localizer::getInstance()->GetText(Localizer::GUI, 94)<<" "<<-count;

	strs<<" [colour='FFFFFFFF'][image='set:"<<ImageSetHandler::GetInventoryMiniImage(iconname)<<"   image:full_image']"; 

	// send message to chatbox
	LbaNet::GuiUpdatesSeq updseq;
	LbaNet::ChatTextUpdate * upd = 
		new LbaNet::ChatTextUpdate("All", "info", strs.str());
	updseq.push_back(upd);
	EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));

}




/***********************************************************
inform user of item update
***********************************************************/
void InventoryBox::InformHappy(long itemId, int count,	const std::string & name, const std::string & Description,
									const std::string & LongDescription, const std::string & iconname)
{
	if(count == 0)
		return;

	EventsQueue::getReceiverQueue()->AddEvent(new InternalUpdateStateEvent(LbaNet::StHappy));

	try
	{
		std::string showtext= Description;
		if(LongDescription != "")
			showtext = LongDescription;

		std::string  imagetxt = "set:"+ImageSetHandler::GetInventoryImage(iconname)+" image:full_image";

		CEGUI::WindowManager::getSingleton().getWindow("InventoryInformHappyFrame/name")->setText(name.c_str());
		CEGUI::WindowManager::getSingleton().getWindow("InventoryInformHappyFrame/text")->setText(showtext.c_str());

		CEGUI::WindowManager::getSingleton().getWindow("InventoryInformHappyFrame/InventoryLogo")->setProperty("Image", imagetxt.c_str());
	
		_myBox2->show();

		CEGUI::FrameWindow * frw2 = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("InventoryInformHappyFrame"));
		frw2->activate();
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception inform happy: ") + ex.getMessage().c_str());
	}
}



/***********************************************************
handle send button event
***********************************************************/
bool InventoryBox::HandleEnterKey (const CEGUI::EventArgs& e)
{
	const CEGUI::KeyEventArgs& we =
    static_cast<const CEGUI::KeyEventArgs&>(e);


	if(we.scancode == CEGUI::Key::Space)
	{
		return HandleHappyOkButton(e);
	}

    return false;
}
