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

#ifndef _LBA_NET_INV_ITEM_HANDLER_H_
#define _LBA_NET_INV_ITEM_HANDLER_H_

#include <map>
#include <string>
#include <LbaTypes.h>

/***********************************
*	class taking care of the log
*************************************/
class InventoryItemHandler
{
public:
	// constructor
	InventoryItemHandler();

	// destructor
	~InventoryItemHandler();

	// singleton pattern
	static InventoryItemHandler * getInstance();

	// set current world
	void SetCurrentWorld(const std::string worldname);

	// get item info
	LbaNet::ItemInfo GetItemInfo(long itemid);

private:

	// singleton
	static InventoryItemHandler *		_singletonInstance;

	// item list
	std::map<long, LbaNet::ItemInfo>			_items;
};


#endif
