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

#ifndef _SCRIPT_INIT_HANDLER_H__
#define _SCRIPT_INIT_HANDLER_H__


#include <map>
#include <string>
#include <boost/shared_ptr.hpp>


class TeleportDef;
class InventoryItemDef;
class Quest;



//! take care of shared data between process
class ScriptInitHandler
{
public:
	//! constructor
	ScriptInitHandler(void){}


	//! destructor
	virtual ~ScriptInitHandler(void){}



	//! add tp
	virtual void AddTeleport(boost::shared_ptr<TeleportDef> tp) = 0;

	//! remove tp
	virtual bool RemoveTeleport(long id) = 0;


	// get tp
	virtual boost::shared_ptr<TeleportDef> GetTeleport(long id) = 0;


	//! add quest
	virtual void AddQuest(boost::shared_ptr<Quest> quest) = 0;

	//! remove quest
	virtual void RemoveQuest(long id) = 0;

	//! get quest
	virtual boost::shared_ptr<Quest> GetQuest(long id) = 0;

	//! add item
	virtual void AddInventoryItem(boost::shared_ptr<InventoryItemDef> item) = 0;


};

#endif
