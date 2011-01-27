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
#include "InventoryBoxHandler.h"
#include "SharedDataHandler.h"


/***********************************************************
update gui with info from server
***********************************************************/
void InventoryBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::SwitchItemPosition
	if(info == typeid(LbaNet::SwitchItemPosition))
	{
		LbaNet::SwitchItemPosition * castedptr = 
			dynamic_cast<LbaNet::SwitchItemPosition *>(ptr);

		SharedDataHandler::getInstance()->PlayerSwitchItem(clientid, 
										(long)castedptr->ItemId, castedptr->NewPosition);
	}

	// LbaNet::InventoryItemUsed
	if(info == typeid(LbaNet::InventoryItemUsed))
	{
		LbaNet::InventoryItemUsed * castedptr = 
			dynamic_cast<LbaNet::InventoryItemUsed *>(ptr);

		SharedDataHandler::getInstance()->PlayerItemUsed(clientid, (long)castedptr->ItemId);
	}

	// LbaNet::CreateLetterUpdate
	if(info == typeid(LbaNet::CreateLetterUpdate))
	{
		LbaNet::CreateLetterUpdate * castedptr = 
			dynamic_cast<LbaNet::CreateLetterUpdate *>(ptr);


		SharedDataHandler::getInstance()->PlayerCreateLetter(clientid, 
											castedptr->Subject, castedptr->Message);
	}

	// LbaNet::DestroyItemUpdate
	if(info == typeid(LbaNet::DestroyItemUpdate))
	{
		LbaNet::DestroyItemUpdate * castedptr = 
			dynamic_cast<LbaNet::DestroyItemUpdate *>(ptr);

		SharedDataHandler::getInstance()->PlayerDestroyItem(clientid, (long)castedptr->ItemId);
	}
}

/***********************************************************
update gui with info from server
***********************************************************/
void InventoryBoxHandler::HideGUI(Ice::Long clientid)
{
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void InventoryBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
}