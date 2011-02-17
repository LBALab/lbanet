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


#ifndef _LBA_NET_DIALOG_BOX_
#define _LBA_NET_DIALOG_BOX_


namespace CEGUI
{
	class Window;
	class EventArgs;
	class Listbox;
}

#include <string>
#include <list>
#include <map>
#include <vector>
#include "GameGUIBase.h"


//*************************************************************************************************
//*                               class NPCDialogBox
//*************************************************************************************************
/**
* @brief Class handling a NPCDialogBox
*
*/
class NPCDialogBox : public GameGUIBase
{
 public:
	//! constructor
	 NPCDialogBox();

	//! destructor
	virtual ~NPCDialogBox();


	//! handle windows closing event
	bool HandleClose(const CEGUI::EventArgs& e);

	//! handle listbox selected
	bool Handlelbelected(const CEGUI::EventArgs& e);

	//! catch key event
	bool HandleEnterKey (const CEGUI::EventArgs& e);
	
	//! catch mouse event
	bool HandleMouseEnter (const CEGUI::EventArgs& e);



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
	//! build dialog depending of the actor
	void BuildDialog(const LbaNet::DialogPartInfo &DialogPart);

	//! close dialog window
	void CloseDialog();

private:
	CEGUI::Window*			_myBox;

};

#endif
