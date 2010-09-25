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
#include "CommunityBoxHandler.h"


/***********************************************************
update gui with info from server
***********************************************************/
void CommunityBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::AcceptFriend
	if(info == typeid(LbaNet::AcceptFriend))
	{
		LbaNet::AcceptFriend * castedptr = 
			dynamic_cast<LbaNet::AcceptFriend *>(ptr);

		//TODO
		//Ice::Long FriendId;
	}

	// LbaNet::RemoveFriend
	if(info == typeid(LbaNet::RemoveFriend))
	{
		LbaNet::RemoveFriend * castedptr = 
			dynamic_cast<LbaNet::RemoveFriend *>(ptr);

		//TODO
		//Ice::Long FriendId;
	}

	// LbaNet::RefreshFriends
	if(info == typeid(LbaNet::RefreshFriends))
	{
		//TODO
	}

	// LbaNet::AddFriend
	if(info == typeid(LbaNet::AddFriend))
	{
		LbaNet::AddFriend * castedptr = 
			dynamic_cast<LbaNet::AddFriend *>(ptr);

		//TODO
		//std::string FriendName;
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void CommunityBoxHandler::HideGUI(Ice::Long clientid)
{
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void CommunityBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
}