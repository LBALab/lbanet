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


#ifndef _LBA_NET_JOURNAL_BOX_
#define _LBA_NET_JOURNAL_BOX_


namespace CEGUI
{
	class Window;
	class EventArgs;
	class Listbox;
	class String;
	class TreeItem;
}

#include <string>
#include <list>
#include <map>
#include <vector>
#include "GameGUIBase.h"

//*************************************************************************************************
//*                               class JournalBox
//*************************************************************************************************
/**
* @brief Class handling a JournalBox
*
*/
class JournalBox : public GameGUIBase
{
 public:
	//! constructor
	 JournalBox();

	//! destructor
	virtual ~JournalBox();


	//! handle windows closing event
	bool HandleClose (const CEGUI::EventArgs& e);

	//! handle event when list is selected
	bool HandleQuestTreeSelected (const CEGUI::EventArgs& e);

	//! handle event when list is selected
	bool HandleQuestDoneTreeSelected (const CEGUI::EventArgs& e);



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



protected:
	//! call to regenerate the quest book display
	void RebuildBook(bool reset);

	//! create description list
	void CreateTextList(std::string text, std::vector<CEGUI::String> & list);

	//! display description
	void DisplayDescription(const std::vector<CEGUI::String> & text, bool questdone);

private:
	CEGUI::Window*								_myBox;

	LbaNet::QuestsMap							_QuestsStarted;
	LbaNet::QuestsMap							_QuestsFinished;	

	std::map<std::string, CEGUI::TreeItem *>	_mapquestarea;
	std::map<std::string, CEGUI::TreeItem *>	_mapquestdonearea;

	std::vector<std::string>					_open_tree_quests;
	std::vector<std::string>					_open_tree_done_quests;
	std::string									_selected_tree_quests;
	std::string									_selected_tree_done_quests;
	bool										_first_book_init;
};

#endif
