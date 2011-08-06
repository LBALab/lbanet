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
#include "Localizer.h"

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
	if(_owner)
	{
		EventsSeq toplayer;
		toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
												"ShopBox", GuiParamsSeq(), false, true));
		_owner->SendEvents((long)clientid, toplayer);
	}


	RemoveOpenedGui(clientid);

	std::map<long, ShopParam>::iterator itm = _openedshops.find((long)clientid);
	if(itm != _openedshops.end())
		_openedshops.erase(itm);

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


	if(HasOpenedGui(clientid))
	{
		//close already opened box
		HideGUI(clientid);
	}
	else
	{
		if(_owner)
		{
			EventsSeq toplayer;
			GuiParamsSeq seq;
			seq.push_back(new ShopGuiParameter(castedptr->_shopinventory,
														castedptr->_currencyitem.IconName));
			toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"ShopBox", seq, true, false));

			toplayer.push_back(UpdateMoney((long)castedptr->_currencyitem.Id, (long)clientid));

			_owner->SendEvents((long)clientid, toplayer);
		}


		// add gui to the list to be removed later
		AddOpenedGui(clientid, curPosition);

		// store container info
		_openedshops[(long)clientid] = *castedptr;
	}

}

/***********************************************************
buy item
***********************************************************/
void ShopBoxHandler::BuyItem(long clientid, long ItemId)
{
	if(!_owner)
		return;

	int inventorysize = 0;
	LbaNet::ItemsMap inventory = _owner->GetInventory(clientid, inventorysize);
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
					if((int)inventory.size() >= inventorysize) // check if inventory full
						buy = false;
				}	
			}
			else
			{
				buy = false;

				// send no kash message to chatbox
				LbaNet::GuiUpdatesSeq updseq;
				LbaNet::ChatTextUpdate * upd = 
					new LbaNet::ChatTextUpdate("All", "info", Localizer::getInstance()->GetText(Localizer::GUI, 106));
				updseq.push_back(upd);		
				EventsSeq toplayer;
				toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));
				_owner->SendEvents(clientid, toplayer);
			}

			if(buy)
			{
				//update inventory
				LbaNet::ItemList Taken, Put;
				Taken[ShopItems._currencyitem.Id] = itcont->second.Info.BuyPrice;
				Put[ItemId] = 1;
				_owner->UpdateInventory(clientid, Taken, Put, LbaNet::InformChat);

				if(_owner)
				{
					EventsSeq toplayer;
					toplayer.push_back(UpdateMoney((long)ShopItems._currencyitem.Id, (long)clientid));
					_owner->SendEvents(clientid, toplayer);
				}
			}
		}
	}
}


/***********************************************************
buy item
***********************************************************/
LbaNet::ClientServerEventBase * ShopBoxHandler::UpdateMoney(long currencyid, long clientid)
{
	int count = 0;
	int inventorysize = 0;
	LbaNet::ItemsMap inventory = _owner->GetInventory(clientid, inventorysize);
	LbaNet::ItemsMap::iterator it = inventory.find(currencyid);
	if(it != inventory.end())
		count = it->second.Count;

	LbaNet::GuiUpdatesSeq updseq;
	LbaNet::PlayerMoneyUpdate * upd = 
		new LbaNet::PlayerMoneyUpdate(count);
	updseq.push_back(upd);
	return new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
											"ShopBox", updseq);
}