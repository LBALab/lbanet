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

#define	_MAX_DISTANCE_PLAYER_OBJECT_	6



/***********************************************************
a player quitted the map - check if we need to do something (e.g. close the gui)
***********************************************************/
void ServerGUIBase::PlayerLeftMap(Ice::Long clientid)
{
	std::map<Ice::Long, LbaNet::PlayerPosition>::iterator it = _openedguis.find(clientid);
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
	std::map<Ice::Long, LbaNet::PlayerPosition>::iterator it = _openedguis.find(clientid);
	if(it != _openedguis.end())
	{
		float distanceX = (it->second.X - curPosition.X);
		float distanceY = (it->second.Y - curPosition.Y);
		float distanceZ = (it->second.Z - curPosition.Z);
		float distance = sqrt((distanceX*distanceX) + (distanceY*distanceY) + (distanceZ*distanceZ));
		
		// check distance between plaer and object
		if(distance > _MAX_DISTANCE_PLAYER_OBJECT_)
			HideGUI(clientid);
	}
}


/***********************************************************
add a player to the opened gui
***********************************************************/
void ServerGUIBase::AddOpenedGui(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition)
{
	_openedguis[clientid] = curPosition;
}


/***********************************************************
remove a player from the opened gui
***********************************************************/
void ServerGUIBase::RemoveOpenedGui(Ice::Long clientid)
{
	std::map<Ice::Long, LbaNet::PlayerPosition>::iterator it = _openedguis.find(clientid);
	if(it != _openedguis.end())
		_openedguis.erase(it);
}