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

#ifndef _INVENTORY_BOX_HANDLER_H__
#define _INVENTORY_BOX_HANDLER_H__


#include "ServerGUIBase.h"

//! take care of update comming from client MailBox GUI
class InventoryBoxHandler :	public ServerGUIBase
{
public:
	//! constructor
	InventoryBoxHandler(void){}

	//! destructor
	virtual ~InventoryBoxHandler(void){}

	//! update gui with info from server
	virtual void Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update);

	//! show the GUI for a certain player
	virtual void ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
						boost::shared_ptr<ShowGuiParamBase> params);

	//! hide the GUI for a certain player
	virtual void HideGUI(Ice::Long clientid);
};

#endif