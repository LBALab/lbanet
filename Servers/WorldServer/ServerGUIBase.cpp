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

#include "ServerGUIBase.h"
#include <math.h>
#include "SynchronizedTimeHandler.h"


#define	_MAX_DISTANCE_PLAYER_OBJECT_SQUARE_	16



/***********************************************************
a player quitted the map - check if we need to do something (e.g. close the gui)
***********************************************************/
void ServerGUIBase::PlayerLeftMap(Ice::Long clientid)
{
	std::map<Ice::Long, OpenedGuiInfo>::iterator it = _openedguis.find(clientid);
	if(it != _openedguis.end())
	{
		HideGUI(clientid);
	}
}


/***********************************************************
a player moved - check if we need to do something (e.g. close the gui)
***********************************************************/
void ServerGUIBase::PlayerMoved(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition)
{
	std::map<Ice::Long, OpenedGuiInfo>::iterator it = _openedguis.find(clientid);
	if(it != _openedguis.end())
	{
		float distanceX = (it->second.PositionAtOpening.X - curPosition.X);
		float distanceY = (it->second.PositionAtOpening.Y - curPosition.Y);
		float distanceZ = (it->second.PositionAtOpening.Z - curPosition.Z);
		float distance = (distanceX*distanceX) + (distanceY*distanceY) + (distanceZ*distanceZ);
		
		// check distance between player and object
		if(distance > _MAX_DISTANCE_PLAYER_OBJECT_SQUARE_)
			HideGUI(clientid);
	}
}


/***********************************************************
process guis if needed
***********************************************************/
void ServerGUIBase::Process(double currenttime)
{
	std::map<Ice::Long, OpenedGuiInfo>::iterator it = _openedguis.begin();
	std::map<Ice::Long, OpenedGuiInfo>::iterator end = _openedguis.end();
	for(;it != end; ++it)
	{
		if(it->second.CloseTimer > 0)
		{
			if((it->second.TimeAtOpening - currenttime) > it->second.CloseTimer)
				HideGUI(it->first);
		}
	}
}



/***********************************************************
add a player to the opened gui
***********************************************************/
void ServerGUIBase::AddOpenedGui(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
									double closetimer)
{
	// remove old gui if present when new gui open
	if(HasOpenedGui(clientid))
		HideGUI(clientid);

	OpenedGuiInfo oginfo;
	oginfo.PositionAtOpening = curPosition;
	oginfo.CloseTimer = closetimer;

	if(closetimer >= 0)
		oginfo.TimeAtOpening = SynchronizedTimeHandler::GetCurrentTimeDouble();

	_openedguis[clientid] = oginfo;
}


/***********************************************************
remove a player from the opened gui
***********************************************************/
void ServerGUIBase::RemoveOpenedGui(Ice::Long clientid)
{
	std::map<Ice::Long, OpenedGuiInfo>::iterator it = _openedguis.find(clientid);
	if(it != _openedguis.end())
		_openedguis.erase(it);
}

/***********************************************************
check if client has gui opened
***********************************************************/
bool ServerGUIBase::HasOpenedGui(Ice::Long clientid)
{
	std::map<Ice::Long, OpenedGuiInfo>::iterator it = _openedguis.find(clientid);
	if(it != _openedguis.end())
		return true;

	return false;
}