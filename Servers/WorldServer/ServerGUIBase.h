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


#ifndef _LBANET_SERVER_GUI_BASE_H_
#define _LBANET_SERVER_GUI_BASE_H_


#include <ClientServerEvents.h>
#include <boost/shared_ptr.hpp>


class ContainerSharedInfo;


// base class containing params when showing a gui
class ShowGuiParamBase
{

};

// class containing text param
class TextBoxParam : public ShowGuiParamBase
{
public:
	//! constructor
	TextBoxParam(long TextId)
		: _textid(TextId){}

	long	_textid;
};


// class containing text param
class ContainerParam : public ShowGuiParamBase
{
public:
	//! constructor
	ContainerParam(boost::shared_ptr<ContainerSharedInfo> sharedinfo,
						const LbaNet::ItemsMap & inventory,
						int InventorySize)
		: _sharedinfo(sharedinfo), _inventory(inventory),
			_InventorySize(InventorySize)
	{}

	int											_InventorySize;
	boost::shared_ptr<ContainerSharedInfo>		_sharedinfo;
	LbaNet::ItemsMap							_inventory;
};


struct OpenedGuiInfo
{
	LbaNet::PlayerPosition		PositionAtOpening;
	double						TimeAtOpening;
	double						CloseTimer;
};

//*************************************************************************************************
//*                               class ServerGUIBase
//*************************************************************************************************
/**
* @brief Base class for GUIs hanlder
*
*/
class ServerGUIBase
{
public:

	//! constructor
	ServerGUIBase(){}


	//! destructor
	virtual ~ServerGUIBase(){}

	//! update gui with info from server
	virtual void Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update) = 0;


	//! show the GUI for a certain player
	virtual void ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
						boost::shared_ptr<ShowGuiParamBase> params) = 0;


	//! hide the GUI for a certain player
	virtual void HideGUI(Ice::Long clientid) = 0;


	//! a player quitted the map - check if we need to do something (e.g. close the gui)
	void PlayerLeftMap(Ice::Long clientid);

	//! a player moved - check if we need to do something (e.g. close the gui)
	void PlayerMoved(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition);

	//! process guis if needed
	void Process(double currenttime);

protected:
	//! add a player to the opened gui
	void AddOpenedGui(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
						double closetimer = -1);

	//! remove a player from the opened gui
	void RemoveOpenedGui(Ice::Long clientid);

	//! check if client has gui opened
	bool HasOpenedGui(Ice::Long clientid);

private:
	// used in mechanism to hide a gui if the player move away
	std::map<Ice::Long, OpenedGuiInfo>		_openedguis;

};


#endif
