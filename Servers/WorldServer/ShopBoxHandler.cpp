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
#include "ShopBoxHandler.h"
#include "SharedDataHandler.h"
#include "SynchronizedTimeHandler.h"
#include "MapHandler.h"

/***********************************************************
update gui with info from server
***********************************************************/
void ShopBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::BuyItemUpdate
	if(info == typeid(LbaNet::BuyItemUpdate))
	{
		LbaNet::BuyItemUpdate * castedptr = 
			dynamic_cast<LbaNet::BuyItemUpdate *>(ptr);

		BuyItem((long)clientid, (long)castedptr->ItemId);
	}

	// LbaNet::GuiClosedUpdate
	if(info == typeid(LbaNet::GuiClosedUpdate))
	{
		HideGUI(clientid);
	}
}

/***********************************************************
update gui with info from server
***********************************************************/
void ShopBoxHandler::HideGUI(Ice::Long clientid)
{
	ClientProxyBasePtr prx = SharedDataHandler::getInstance()->GetProxy(clientid);
	if(prx)
	{
		EventsSeq toplayer;
		toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
												"ShopBox", GuiParamsSeq(), false, true));

		IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
		t->start();	
	}

	RemoveOpenedGui(clientid);
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void ShopBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
	ShowGuiParamBase * ptr = params.get();
	ShopParam * castedptr = 
		static_cast<ShopParam *>(params.get());

	ClientProxyBasePtr prx = SharedDataHandler::getInstance()->GetProxy(clientid);
	if(prx)
	{
		if(HasOpenedGui(clientid))
		{
			//close already opened box
			HideGUI(clientid);
		}
		else
		{
			EventsSeq toplayer;
			GuiParamsSeq seq;
			seq.push_back(new ShopGuiParameter(castedptr->_shopinventory,
														castedptr->_currencyitem.IconName));
			toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"ShopBox", seq, true, false));

			IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
			t->start();	

			// add gui to the list to be removed later
			AddOpenedGui(clientid, curPosition);

			// store container info
			_openedshops[clientid] = *castedptr;
		}
	}
}

/***********************************************************
buy item
***********************************************************/
void ShopBoxHandler::BuyItem(long clientid, long ItemId)
{
	int inventorysize = 0;
	LbaNet::ItemsMap inventory = SharedDataHandler::getInstance()->GetInventory(clientid, inventorysize);
	ShopParam &ShopItems = _openedshops[clientid];


	// check if shop has listed items available
	LbaNet::ItemsMap::iterator itcont = ShopItems._shopinventory.find(ItemId);
	if(itcont != ShopItems._shopinventory.end())
	{
		// check if player has enough money
		LbaNet::ItemsMap::iterator itinv = inventory.find(ShopItems._currencyitem.Id);
		if(itinv != inventory.end())
		{
			bool buy = true;
			if(itinv->second.Count >= itcont->second.Info.BuyPrice)
			{
				LbaNet::ItemsMap::iterator itinv2 = inventory.find(ItemId);
				if(itinv2 != inventory.end())
				{
					// check if too much item of this type
					int diff = (itinv2->second.Info.Max - itinv2->second.Count);
					if(diff <= 0)
						buy = false;
				}
				else
				{
					if(inventory.size() >= inventorysize) // check if inventory full
						buy = false;
				}	
			}

			if(buy)
			{
				//update inventory
				LbaNet::ItemList Taken, Put;
				Taken[ShopItems._currencyitem.Id] = itcont->second.Info.BuyPrice;
				Put[ItemId] = 1;
				SharedDataHandler::getInstance()->UpdateInventory(clientid, Taken, Put, LbaNet::DontInform);
			}
		}
	}
}
