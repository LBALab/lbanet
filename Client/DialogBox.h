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
	class Animation;
	class Affector;
	class AnimationInstance;
}

#include <string>
#include <list>
#include <map>
#include <vector>
#include "GameGUIBase.h"
#include "MusicHandler.h"

class NPCDialogBox;

//*************************************************************************************************
//*                               class NPCDialogActionBase
//*************************************************************************************************
/**
* @brief used when building dialog
*
*/
class NPCDialogActionBase : public VoiceEndCallbackBase
{
public:
	//! constructor
	NPCDialogActionBase(NPCDialogBox * dialoghandler)
		: _dialoghandler(dialoghandler){}

	//! destructor
	virtual ~NPCDialogActionBase(){}

	//! execute function
	virtual void Execute() = 0;

	//! execute function
	virtual void ExecuteEndScrollText(){}

	//! voice callback
	virtual void VoiceFinished()
	{ Execute(); }

protected:
	NPCDialogBox * _dialoghandler;
};


class FinishAnimDialogAction : public NPCDialogActionBase
{
public:
	//! constructor
	FinishAnimDialogAction(NPCDialogBox * dialoghandler, 
		boost::shared_ptr<NPCDialogActionBase>	nextaction, bool directnext)
		: NPCDialogActionBase(dialoghandler), _nextaction(nextaction), _directnext(directnext){}

	//! destructor
	virtual ~FinishAnimDialogAction(){}

	//! execute function
	virtual void Execute();

	//! execute function
	virtual void ExecuteEndScrollText(){Execute();}

private:
	boost::shared_ptr<NPCDialogActionBase>	_nextaction;
	bool									_directnext;
};


class CloseDialogAction : public NPCDialogActionBase
{
public:
	//! constructor
	CloseDialogAction(NPCDialogBox * dialoghandler)
		: NPCDialogActionBase(dialoghandler){}

	//! destructor
	virtual ~CloseDialogAction(){}

	//! execute function
	virtual void Execute();

};


class ShowPChoiceDialogAction : public NPCDialogActionBase
{
public:
	//! constructor
	ShowPChoiceDialogAction(NPCDialogBox * dialoghandler,
		const std::vector<long> & pchoices)
		: NPCDialogActionBase(dialoghandler), _pchoices(pchoices){}

	//! destructor
	virtual ~ShowPChoiceDialogAction(){}

	//! execute function
	virtual void Execute();

private:
	std::vector<long> _pchoices;
};


class Show1ChoiceDialogAction : public NPCDialogActionBase
{
public:
	//! constructor
	Show1ChoiceDialogAction(NPCDialogBox * dialoghandler,
									long pchoice)
		: NPCDialogActionBase(dialoghandler), _pchoice(pchoice){}

	//! destructor
	virtual ~Show1ChoiceDialogAction(){}

	//! execute function
	virtual void Execute();

private:
	long _pchoice;
};


class PlayerPChoiceVoiceDialogAction : public NPCDialogActionBase
{
public:
	//! constructor
	PlayerPChoiceVoiceDialogAction(NPCDialogBox * dialoghandler)
		: NPCDialogActionBase(dialoghandler){}

	//! destructor
	virtual ~PlayerPChoiceVoiceDialogAction(){}

	//! execute function
	virtual void Execute();
};


class SendChoiceToServerDialogAction : public NPCDialogActionBase
{
public:
	//! constructor
	SendChoiceToServerDialogAction(NPCDialogBox * dialoghandler, int choice)
		: NPCDialogActionBase(dialoghandler), _choice(choice){}

	//! destructor
	virtual ~SendChoiceToServerDialogAction(){}

	//! execute function
	virtual void Execute();

private:
	int _choice;
};




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

	//! called when animation is finished
	bool handleAnimFinished (const CEGUI::EventArgs& e);


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


	//! finish text anim
	void FinishTextAnim();

	//! set action executed on space bar
	void SetSpaceAction(boost::shared_ptr<NPCDialogActionBase>  act);

	//! display player choice list
	void DisplayPChoices(std::vector<long> pchoices);

	//! display player choice 
	void DisplayPChoice(long pchoice);

	//! play voice of player choice
	void PlayPChoice();

	//! send selected player choice to server
	void SendPlayerChoice(int choice);

	//! close dialog window
	void CloseDialog();


protected:
	//! build dialog depending of the actor
	void BuildDialog(const LbaNet::DialogPartInfo &DialogPart);

	//! show or hide player answer list from window
	void ShowHidePlayerList(bool Show);

	//! display scrolling text
	void DisplayScrollingText(long textid, long actorid);

	//! move player choice selection up/down
	void ChangeSelection(bool up);

private:
	CEGUI::Window*			_myBox;
	std::string				_playername;

	bool					_plist_shown;

	boost::shared_ptr<NPCDialogActionBase>  _space_act;

	std::vector<long>		_currentPchoices;


	CEGUI::Animation*			_textanim;
	CEGUI::Affector*			_textanimaffector;
	CEGUI::AnimationInstance*	_textaniminstance;

	long						_currentnpcid;
};

#endif
