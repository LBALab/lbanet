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

#include "InventoryItemHandler.h"
#include "XmlReader.h"

InventoryItemHandler* InventoryItemHandler::_singletonInstance = NULL;



/***********************************************************
singleton pattern
***********************************************************/
InventoryItemHandler * InventoryItemHandler::getInstance()
{
    if(!_singletonInstance)
    {
        _singletonInstance = new InventoryItemHandler();
		return _singletonInstance;
    }
    else
    {
		return _singletonInstance;
    }
}


/***********************************************************
Constructor
***********************************************************/
InventoryItemHandler::InventoryItemHandler()
{

}

/***********************************************************
Destructor
***********************************************************/
InventoryItemHandler::~InventoryItemHandler()
{

}

/***********************************************************
set current world
***********************************************************/
void InventoryItemHandler::SetCurrentWorld(const std::string worldname)
{
	_items.clear();
	XmlReader::LoadInventoryFile("Data/Worlds/"+worldname+"/Inventory.xml", _items);
}

/***********************************************************
get item info
***********************************************************/
LbaNet::ItemInfo InventoryItemHandler::GetItemInfo(long itemid)
{
	if(_items.find(itemid) != _items.end())
		return _items[itemid];

	// in case not found
	LbaNet::ItemInfo res;
	res.Id = -1;
	return res;
}

