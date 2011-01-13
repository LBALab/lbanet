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

#include "ShopBox.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "ImageSetHandler.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "DataLoader.h"
#include "OSGHandler.h"
#include "Localizer.h"
#include "GUILocalizationCallback.h"

#include <iostream>
#include <algorithm>
#include <CEGUI.h>


#define _NB_BOX_TRADE_ 20



/***********************************************************
constructor
***********************************************************/
NPCShopBox::NPCShopBox(int boxsize)
: _current_npc_actor(-1), _boxsize(boxsize), 
	_currentmoney(-1)
{



}


/***********************************************************
destructor
***********************************************************/
NPCShopBox::~NPCShopBox()
{
	try
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("DialogTraderFrame"));

		int resX, resY; 
		bool fullscreen;
		OsgHandler::getInstance()->GetScreenAttributes(resX, resY, fullscreen);

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.ShopBox.PosX", vec.d_x.asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.ShopBox.PosY", vec.d_y.asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetFloat("Gui.ShopBox.SizeX", frw->getWidth().asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.ShopBox.SizeY", frw->getHeight().asRelative((float)resY));
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception destructor chatbox: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
initalize the box
***********************************************************/
void NPCShopBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_mytradeBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "trader.layout",
								"", "", &MyPropertyCallback);
		Root->addChildWindow(_mytradeBox);


		CEGUI::FrameWindow * frw2 = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("DialogTraderFrame"));
		frw2->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&NPCShopBox::HandleClose, this));

		frw2->subscribeEvent(
			CEGUI::FrameWindow::EventSized,
			CEGUI::Event::Subscriber (&NPCShopBox::HandleResize, this));	


		{
			float PosX, PosY, SizeX, SizeY;
			ConfigurationManager::GetInstance()->GetFloat("Gui.ShopBox.PosX", PosX);
			ConfigurationManager::GetInstance()->GetFloat("Gui.ShopBox.PosY", PosY);
			ConfigurationManager::GetInstance()->GetFloat("Gui.ShopBox.SizeX", SizeX);
			ConfigurationManager::GetInstance()->GetFloat("Gui.ShopBox.SizeY", SizeY);
			frw2->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, 0), CEGUI::UDim(PosY, 0)));
			frw2->setWidth(CEGUI::UDim(SizeX, 0));
			frw2->setHeight(CEGUI::UDim(SizeY, 0));
		}




		CEGUI::Window*	pane = CEGUI::WindowManager::getSingleton().getWindow("DialogTraderFrame/boxpart");
		CEGUI::Window*	tmpwindow;
		for(int i=0; i<_NB_BOX_TRADE_; ++i)
		{
			int x = i / 3;
			int y = i % 3;

			tmpwindow = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText");
			tmpwindow->setArea(CEGUI::UDim(0,5+((float)_boxsize+2)*y), CEGUI::UDim(0,5+((float)_boxsize+2)*x), 
								CEGUI::UDim(0, (float)_boxsize), CEGUI::UDim(0, (float)_boxsize));
			pane->addChildWindow(tmpwindow);

			tmpwindow->setID(i);
			_inv_boxes.push_back(tmpwindow);
		}

		ResizeBox();

		_mytradeBox->hide();

	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init DialogBox: ") + ex.getMessage().c_str());
	}
}




/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool NPCShopBox::HandleClose (const CEGUI::EventArgs& e)
{
	CloseDialog();
	return true;
}


/***********************************************************
handle windows resize event
***********************************************************/
bool NPCShopBox::HandleResize (const CEGUI::EventArgs& e)
{
	ResizeBox();
	return false;
}


/***********************************************************
clean current items
***********************************************************/
bool NPCShopBox::HandleObjectClicked (const CEGUI::EventArgs& e)
{
	const CEGUI::MouseEventArgs& dd_args = static_cast<const CEGUI::MouseEventArgs&>(e);

	// use object
	if(dd_args.button == CEGUI::RightButton)
	{
		unsigned int id = dd_args.window->getID();

		LbaNet::GuiUpdatesSeq updseq;
		LbaNet::BuyItemUpdate * upd = 
			new LbaNet::BuyItemUpdate(_current_npc_actor, id);
		updseq.push_back(upd);
		
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShopBox", updseq));
	}


    return true;
}




/***********************************************************
close dialog and inform actor
***********************************************************/
void NPCShopBox::CloseDialog()
{
	_mytradeBox->hide();
	_current_npc_actor  = -1;

	LbaNet::GuiUpdatesSeq updseq;
	LbaNet::GuiClosedUpdate * upd = 
		new LbaNet::GuiClosedUpdate();
	updseq.push_back(upd);
	
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShopBox", updseq));
}





/***********************************************************
open trading dialog
***********************************************************/
void NPCShopBox::RefreshTradeDialog()
{
	RefreshMoney();
	CleanItems();

	LbaNet::ItemsMap::iterator it = _inventoryshop.begin();
	for(size_t i=0; it != _inventoryshop.end(); ++i, ++it)
	{
		AddItem(it->second, _inv_boxes[i]);	 
	}
}



/***********************************************************
resize inventory
***********************************************************/
void NPCShopBox::ResizeBox()
{
	CEGUI::Window*	win = CEGUI::WindowManager::getSingleton().getWindow("DialogTraderFrame/boxpart");
	CEGUI::Rect rect = win->getInnerRectClipper();
	float width = rect.getSize().d_width;
	int nbboxhori = (int)width / (_boxsize+2);

	if(nbboxhori > 0)
	{
		for(int i=0; i<(int)_inv_boxes.size(); ++i)
		{
			int x = i / nbboxhori;
			int y = i % nbboxhori;

			_inv_boxes[i]->setPosition(CEGUI::UVector2(CEGUI::UDim(0,((float)_boxsize+2.0f)*y), 
														CEGUI::UDim(0,((float)_boxsize+2.0f)*x)));
		}
	}
}


/***********************************************************
set player money
***********************************************************/
void NPCShopBox::RefreshMoney()
{
	std::stringstream strs;
	strs<<"You have "<<_currentmoney<<" [image='set:"<<ImageSetHandler::GetInventoryMiniImage(_MoneyIconName)<<" image:full_image']";
	CEGUI::WindowManager::getSingleton().getWindow("DialogTraderFrame/kashes")->setText(strs.str());
}


/***********************************************************
set player money
***********************************************************/
void NPCShopBox::AddItem(const LbaNet::ItemInfo &itinfo, CEGUI::Window* parent)
{
	CEGUI::Window*	tmp = CEGUI::WindowManager::getSingleton().createWindow("DragContainer");
	tmp->setArea(CEGUI::UDim(0,0), CEGUI::UDim(0,0), CEGUI::UDim(1, 0), CEGUI::UDim(1, 0));
	tmp->setID((unsigned int)itinfo.Id);

	CEGUI::Window*	tmp2 = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage");
	tmp2->setArea(CEGUI::UDim(0,5), CEGUI::UDim(0,8), CEGUI::UDim(0, (float)_boxsize-10), CEGUI::UDim(0, (float)_boxsize-20));

	std::string imagesetname = ImageSetHandler::GetInventoryImage(itinfo.IconName);
	tmp2->setProperty("Image", "set:" + imagesetname + " image:full_image");
	tmp2->setProperty("MousePassThroughEnabled", "True");

	CEGUI::Window*	tmp3 = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticText");
	tmp3->setArea(CEGUI::UDim(0,2), CEGUI::UDim(0,34), CEGUI::UDim(1, -1), CEGUI::UDim(0, 14));
	tmp3->setProperty("FrameEnabled", "False");
	tmp3->setProperty("BackgroundEnabled", "False");
	tmp3->setProperty("MousePassThroughEnabled", "True");
	tmp3->setProperty("Font" , "contourfont");
	tmp3->setAlwaysOnTop(true);
	std::stringstream strs2;
	strs2<<itinfo.Price;
	tmp3->setText(strs2.str().c_str());


	std::string itemdescription = itinfo.DescriptionTextExtra;
	if(itemdescription == "")
		itemdescription = Localizer::getInstance()->GetText(Localizer::Inventory, (long)itinfo.DescriptionId);


	std::stringstream strs;
	strs<<"<"<<itinfo.Price<<" kashes> "<<itemdescription;
	CEGUI::String tmpstr((const unsigned char *)strs.str().c_str());
	tmp->setProperty("Tooltip", tmpstr);
	tmp->addChildWindow(tmp2);
	tmp->addChildWindow(tmp3);

    tmp->subscribeEvent (CEGUI::Window::EventMouseClick,
							CEGUI::Event::Subscriber (&NPCShopBox::HandleObjectClicked, this));

	parent->addChildWindow(tmp);

	_objects.push_back(tmp);
}


/***********************************************************
clean current items
***********************************************************/
void NPCShopBox::CleanItems()
{
	std::vector<CEGUI::Window*>::iterator it = _objects.begin();
	std::vector<CEGUI::Window*>::iterator end = _objects.end();
	for(;it != end; ++it)
		(*it)->destroy();

	_objects.clear();	
}




/***********************************************************
refresh gui with info from server
***********************************************************/
void NPCShopBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{
	for(size_t i=0; i<Parameters.size(); ++i)
	{
		LbaNet::GuiParameterBase * ptr = Parameters[i].get();
		const std::type_info& info = typeid(*ptr);

		// shortcut updated
		if(info == typeid(LbaNet::ShopGuiParameter))
		{
			LbaNet::ShopGuiParameter * castedptr = 
				dynamic_cast<LbaNet::ShopGuiParameter *>(ptr);

			// set NPC id
			_current_npc_actor = castedptr->NPCId;

			//set icon for money
			_MoneyIconName = castedptr->MoneyIconName;

			// set shop inventory
			_inventoryshop = castedptr->ShopContent;

			// refresh
			RefreshTradeDialog();
		}
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void NPCShopBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{
	for(size_t i=0; i<Updates.size(); ++i)
	{
		LbaNet::GuiUpdateBase * ptr = Updates[i].get();
		const std::type_info& info = typeid(*ptr);

		// PlayerMoneyUpdate
		if(info == typeid(LbaNet::PlayerMoneyUpdate))
		{
			LbaNet::PlayerMoneyUpdate * castedptr = 
				dynamic_cast<LbaNet::PlayerMoneyUpdate *>(ptr);

			int money = castedptr->Quantity;
			if(money != _currentmoney)
			{
				_currentmoney = money;
				RefreshMoney();
			}
		}
	}
}

/***********************************************************
show GUI
***********************************************************/
void NPCShopBox::Display()
{
	_mytradeBox->show();
	_mytradeBox->activate();
}

/***********************************************************
hide GUI
***********************************************************/
void NPCShopBox::Hide()
{
	_mytradeBox->hide();
}

/***********************************************************
show/hide GUI
***********************************************************/
void NPCShopBox::ToggleDisplay()
{
	if(_mytradeBox->isVisible())
		_mytradeBox->hide();
	else
	{
		_mytradeBox->show();
		_mytradeBox->activate();
	}
}

/***********************************************************
focus GUI
***********************************************************/
void NPCShopBox::Focus(bool focus)
{

}


/***********************************************************
save size of windows to be restored after resize of the application
***********************************************************/
void NPCShopBox::SaveGUISizes(int oldscreenX, int oldscreenY)
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogTraderFrame"));

	CEGUI::UVector2 vec = frw->getPosition();
	_savedPosX = vec.d_x.asRelative((float)oldscreenX);
	_savedPosY = vec.d_y.asRelative((float)oldscreenY);
	_savedSizeX = frw->getWidth().asRelative((float)oldscreenX);
	_savedSizeY = frw->getHeight().asRelative((float)oldscreenY);
}


/***********************************************************
restore the correct size of the windows
***********************************************************/
void NPCShopBox::RestoreGUISizes()
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogTraderFrame"));

	frw->setPosition(CEGUI::UVector2(CEGUI::UDim(_savedPosX, 0), CEGUI::UDim(_savedPosY, 0)));
	frw->setWidth(CEGUI::UDim(_savedSizeX, 0));
	frw->setHeight(CEGUI::UDim(_savedSizeY, 0));
}