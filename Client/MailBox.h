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


#ifndef _LBA_NET_MAIL_BOX_
#define _LBA_NET_MAIL_BOX_

class CommunityBox;

namespace CEGUI
{
	class Window;
	class EventArgs;
	class Listbox;
	class Vector2;
}

#include <string>
#include <list>
#include <map>
#include <vector>
#include "GameGUIBase.h"


//*************************************************************************************************
//*                               class MailBox
//*************************************************************************************************
/**
* @brief Class handling a MailBox
*
*/
class MailBox : public GameGUIBase
{
 public:
	//! constructor
	 MailBox(CommunityBox * combox);

	//! destructor
	virtual ~MailBox();


	//! handle close button event
	bool HandleQuit(const CEGUI::EventArgs& e);	

	//! handle list selected event
	bool Handlelistselected(const CEGUI::EventArgs& e);	

	//! handle list selected event
	bool HandleCloseRead(const CEGUI::EventArgs& e);	

	//! handle list selected event
	bool HandleReadDelete(const CEGUI::EventArgs& e);	

	//! handle list selected event
	bool HandleReadReply(const CEGUI::EventArgs& e);

	//! handle list selected event
	bool HandleCompose(const CEGUI::EventArgs& e);

	//! handle list selected event
	bool HandleWriteSend(const CEGUI::EventArgs& e);

	//! handle list selected event
	bool HandleWriteCancel(const CEGUI::EventArgs& e);

	//! handle list selected event
	bool Handlecontactselected(const CEGUI::EventArgs& e);	



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
	//! hide mails
	void HideMails();

	//! update mailbox content
	void UpdateMailbox(const LbaNet::PMsSeq &pms);

	//! display a mail on the screen
	void DisplayMail(const LbaNet::PMInfo & pm);

	//! display a write mail on the screen
	void DisplayWriteMail();

	//! switch to mailbox
	void SwitchToMailBox();

	//! delete pm
	void DeletePM(Ice::Long pmid);

private:
	CEGUI::Window*					_myBox;
	CEGUI::Window*					_readMailBox;
	CEGUI::Window*					_writeMailBox;

	CommunityBox *					_combox;

	LbaNet::PMsSeq					_currentpms;
	Ice::Long						_currentread;
	std::string						_currentcomposeTo;
	std::string						_currentcomposeText;

	Ice::Long						_replyto;
	bool							_hidemailbox;

	float							_sizecollumn0;
	float							_sizecollumn1;
	float							_sizecollumn2;
	float							_sizecollumn3;
	float							_sizecollumn4;

	float							_savePosXRead;
	float							_savePosYRead;
	float							_saveSizeXRead;
	float							_saveSizeYRead;

	float							_savePosXWrite;
	float							_savePosYWrite;
	float							_saveSizeXWrite;
	float							_saveSizeYWrite;


};

#endif
