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

		//TODO
		//Ice::Long Containerid;
		//LbaNet::ItemList Taken;
		//LbaNet::ItemList Put;	

		RemoveOpenedGui(clientid);
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

//
//
///***********************************************************
//update container content
//***********************************************************/
//void ContainerBoxHandler::UpdateContent(long itemid, int deltanumber, ContainerSharedInfo container)
//{
//
//	// if we add content
//	if(deltanumber > 0)
//	{
//		std::map<long, int>::iterator itlocal = container.find(itemid);
//		if(itlocal != _currentContent.end())
//			itlocal->second += deltanumber;
//		else
//			container[itemid] = deltanumber;
//	}
//	else // if we remove content
//	{
//		std::map<long, int>::iterator itlocal = _currentContent.find(itemid);
//		if(itlocal != _currentContent.end())
//		{
//			itlocal->second += deltanumber;
//			if(itlocal->second <= 0)
//			{
//				// remove link
//				_currentContent.erase(itlocal);
//
//				// remove link to spawn list to tell that the item has been looted
//				std::map<long, int>::iterator itlink = _linktolootlist.find(itemid);
//				if(itlink != _linktolootlist.end())
//				{
//					_lootList[itlink->second].currpicked = -1;
//					if(resettime)
//						_lootList[itlink->second].lastSpawningTime = 0;
//					else
//						_lootList[itlink->second].lastSpawningTime = IceUtil::Time::now().toMilliSecondsDouble();
//					_linktolootlist.erase(itlink);
//				}
//			}
//		}
//	}
//}