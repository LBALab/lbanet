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
#include "ContainerBoxHandler.h"
#include "SharedDataHandler.h"
#include "SynchronizedTimeHandler.h"
#include "MapHandler.h"
#include "Actions.h"
#include "InventoryItemHandler.h"

#define _NB_BOX_CONTAINER_ 18

/***********************************************************
update gui with info from server
***********************************************************/
void ContainerBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::UpdateInvContainer
	if(info == typeid(LbaNet::UpdateInvContainer))
	{
		LbaNet::UpdateInvContainer * castedptr = 
			dynamic_cast<LbaNet::UpdateInvContainer *>(ptr);

		UpdateContainer((long)clientid, castedptr->Taken, castedptr->Put);

		HideGUI(clientid);
	}
}

/***********************************************************
update gui with info from server
***********************************************************/
void ContainerBoxHandler::HideGUI(Ice::Long clientid)
{
	ClientProxyBasePtr prx = SharedDataHandler::getInstance()->GetProxy(clientid);
	if(prx)
	{
		EventsSeq toplayer;
		toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
															"ContainerBox", GuiParamsSeq(), false, true));

		IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
		t->start();	
	}

	RemoveOpenedGui(clientid);

	std::map<long, boost::shared_ptr<ContainerSharedInfo> >::iterator itm = _openedcontainers.find(clientid);
	if(itm != _openedcontainers.end())
	{
		itm->second->OpeningClient = -1;
		_openedcontainers.erase(itm);
	}
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void ContainerBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
	ShowGuiParamBase * ptr = params.get();
	ContainerParam * castedptr = 
		static_cast<ContainerParam *>(params.get());

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
			seq.push_back(new ContainerGuiParameter(castedptr->_InventorySize,
														castedptr->_sharedinfo->ContainerItems,
														castedptr->_inventory));
			toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"ContainerBox", seq, true, false));

			IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
			t->start();	

			// add gui to the list to be removed later
			AddOpenedGui(clientid, curPosition);

			// store container info
			_openedcontainers[clientid] = castedptr->_sharedinfo;
		}
	}
}


/***********************************************************
update container
***********************************************************/
void ContainerBoxHandler::UpdateContainer(long clientid, LbaNet::ItemList Taken, LbaNet::ItemList Put)
{
	int inventorysize = 0;
	LbaNet::ItemsMap inventory = SharedDataHandler::getInstance()->GetInventory(clientid, inventorysize);
	LbaNet::ItemsMap &ContainerItems = _openedcontainers[clientid]->ContainerItems;

	// taken part
	{
		LbaNet::ItemList::iterator ittaken = Taken.begin();
		LbaNet::ItemList::iterator endtaken = Taken.end();
		for(; ittaken != endtaken; ++ittaken)
		{
			// check if container has listed items available
			LbaNet::ItemsMap::iterator itcont = ContainerItems.find(ittaken->first);
			if(itcont != ContainerItems.end())
			{
				LbaNet::ItemsMap::iterator itinv = inventory.find(ittaken->first);
				if(itinv != inventory.end())
				{
					int diff = itinv->second.Info.Max - itinv->second.Count;
					if(ittaken->second > diff)
						ittaken->second = diff;
				}
				else
				{
					if(ittaken->second > itcont->second.Info.Max)
						ittaken->second = itcont->second.Info.Max;	

					if(inventory.size() >= inventorysize) // check if inventory full
						ittaken->second = 0;	
				}


				itcont->second.Count -= ittaken->second;
				if(itcont->second.Count < 0)
				{
					ittaken->second += itcont->second.Count;
					itcont->second.Count = 0;
				}

				// remove item from container
				if(itcont->second.Count == 0)
					ContainerItems.erase(itcont);
			}
			else
				ittaken->second = 0;
		}
	}

	// put part
	{
		LbaNet::ItemList::iterator itput = Put.begin();
		LbaNet::ItemList::iterator endput = Put.end();
		for(; itput != endput; ++itput)
		{
			// check if inventory has listed items available
			LbaNet::ItemsMap::iterator itinv = inventory.find(itput->first);
			if(itinv != inventory.end())
			{
				// only allowed to put normal items in container
				if((itinv->second.Info.Type != 1) && (itinv->second.Info.Type != 6) && 
					(itinv->second.Info.Type != 8))
					itput->second = 0;

				if(itinv->second.Count < itput->second)
					itput->second = itinv->second.Count;

				LbaNet::ItemsMap::iterator itcont = ContainerItems.find(itput->first);
				if(itcont != ContainerItems.end())
				{	
					itcont->second.Count += itput->second;
					if(itcont->second.Count > itcont->second.Info.Max)
					{
						itput->second -= (itcont->second.Count-itcont->second.Info.Max);
						itcont->second.Count = itcont->second.Info.Max;
					}
				}
				else
				{
					if(ContainerItems.size() >= _NB_BOX_CONTAINER_) //container full
						itput->second = 0;

					// add new item to container
					LbaNet::ItemPosInfo newitem;
					newitem.Count = itput->second;
					newitem.Position = -1;
					newitem.Info = InventoryItemHandler::getInstance()->GetItemInfo(itput->first);

					if(newitem.Count > newitem.Info.Max)
					{
						itput->second -= (newitem.Count-newitem.Info.Max);
						newitem.Count = newitem.Info.Max;
					}

					if(newitem.Count > 0)
						ContainerItems[itput->first] = newitem;
				}
			}
			else
				itput->second = 0;
		}
	}


	//update inventory
	SharedDataHandler::getInstance()->UpdateInventory(clientid, Put, Taken, LbaNet::DontInform);
}