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
	_worldname = worldname;
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


/***********************************************************
add/modify item
return item id in case of add
***********************************************************/
long InventoryItemHandler::AddOrModItem(long index, const LbaNet::ItemInfo &info)
{
	if(index < 0)
	{
		// add to map
		long res = _items.rbegin()->first + 1;
		_items[res] = info;
		_items[res].Id = res;
		return res;
	}
	else
	{
		_items[index] = info;
		return index;
	}
}

/***********************************************************
remove item
***********************************************************/
void InventoryItemHandler::RemoveItem(long index)
{
	std::map<long, LbaNet::ItemInfo>::iterator it = _items.find(index);
	if(it != _items.end())
		_items.erase(it);
}

/***********************************************************
save information into file
***********************************************************/
void InventoryItemHandler::SaveInformation()
{
	XmlReader::SaveInventoryFile("Data/Worlds/"+_worldname+"/Inventory.xml", _items);
}



/***********************************************************
get item info
***********************************************************/
std::string InventoryItemHandler::GetItemTypeString(long itemid)
{
	std::map<long, LbaNet::ItemInfo>::iterator it = _items.find(itemid);
	if(it != _items.end())
	{
		switch(it->second.Type)
		{
			case 1:
				return "Consumable";
			case 2:
				return "Key";
			case 3:
				return "Mount";
			case 4:
				return "Weapon";
			case 5:
				return "Quest";
			case 6:
				return "Other";
			case 7:
				return "Special";
			case 8:
				return "Letter";
			case 9:
				return "Outfit";
			case 10:
				return "Container";
		}
	}

	return "";
}
