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


#ifndef _LBA_NET_COMMUNITY_BOX_
#define _LBA_NET_COMMUNITY_BOX_


namespace CEGUI
{
	class Window;
	class EventArgs;
	class Listbox;
	class ListboxItem;
}


#include <string>
#include <list>
#include <vector>
#include <map>
#include "GameGUIBase.h"


//*************************************************************************************************
//*                               class CommunityBox
//*************************************************************************************************
/**
* @brief Class handling a CommunityBox box
*
*/
class CommunityBox : public GameGUIBase
{
 public:
	//! constructor
	 CommunityBox();

	//! destructor
	virtual ~CommunityBox();


	//! handle event when the CommunityBox is closed
	bool HandleClose(const CEGUI::EventArgs& e);

	//! handle event when add friend clicked
	bool HandleAddFriend(const CEGUI::EventArgs& e);

	//! handle event when remove friend clicked
	bool HandleRemoveFriend(const CEGUI::EventArgs& e);

	//! handle event when remove friend clicked
	bool HandleRefreshFriend(const CEGUI::EventArgs& e);

	//! handle enter key
	bool HandleCPOk (const CEGUI::EventArgs& e);

	//! handle event when list is selected
	bool HandleCPCancel (const CEGUI::EventArgs& e);

	//! handle event when list is double clicked
	bool HandleListdblClick (const CEGUI::EventArgs& e);

	//! handle event when list is double clicked
	bool HandleConnecteddblClick (const CEGUI::EventArgs& e);

	//! get friend list
	std::vector<std::string> GetFriendList();



	//! initalize the box
	virtual void Initialize(CEGUI::Window* Root);

	//! refresh gui with info from server
	virtual void Refresh(const LbaNet::GuiParamsSeq &Parameters);

	//! update gui with info from server
	virtual void Update(const LbaNet::GuiUpdatesSeq &Updates);

	//! show GUI
	virtual void Display();

	//! hide GUI
	virtual void Hide();

	//! show/hide GUI
	virtual void ToggleDisplay();

	//! focus GUI
	virtual void Focus(bool focus);


	//! save size of windows to be restored after resize of the application
	virtual void SaveGUISizes(int oldscreenX, int oldscreenY);

	//! restore the correct size of the windows
	virtual void RestoreGUISizes();


protected:

	//! add people online
	void AddOnline(const std::string &_online, 
						const std::string &_status, const std::string &color,
						const std::string &location);

	//! remove people online
	void RemoveOnline( const std::string &_offline);

	//! clear the list
	void ClearList();

	//! clear the friend list
	void ClearFriends();

	//! add people friend
	void UpdateFriend(const LbaNet::FriendInfo & frd);

	//! remove people friend
	//void RemoveFriend(long frid);


	//! update friend online status
	void UpdateFriendOnlineStatus(const std::string & name);


private:
	CEGUI::Window*			_myBox;
	CEGUI::Window*			_myChooseName;

	std::map<std::string, std::pair<CEGUI::ListboxItem *, CEGUI::ListboxItem *> > _onlines;

	typedef std::map<Ice::Long, std::pair<LbaNet::FriendInfo, CEGUI::ListboxItem *> > T_friendmap;
	T_friendmap				_friends;
};

#endif
