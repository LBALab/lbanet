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

#include "ChooseNumberBox.h"
#include <CEGUI.h>
#include "LogHandler.h"

ChooseNumberBox* ChooseNumberBox::_singletonInstance = NULL;



/***********************************************************
singleton pattern
***********************************************************/
ChooseNumberBox * ChooseNumberBox::getInstance()
{
    if(!_singletonInstance)
    {
        _singletonInstance = new ChooseNumberBox();
		return _singletonInstance;
    }
    else
    {
		return _singletonInstance;
    }

}


/***********************************************************
constructor
***********************************************************/
ChooseNumberBox::ChooseNumberBox()
: _currCallback(NULL)
{
}


/***********************************************************
destructor
***********************************************************/
ChooseNumberBox::~ChooseNumberBox()
{
}


/***********************************************************
initalize the box
***********************************************************/
void ChooseNumberBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "choosenumberbox.layout" );
		Root->addChildWindow(_myBox);


		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("ChooseNumberBoxFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&ChooseNumberBox::HandleCancel, this));


		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("ChooseNumberBoxFrame/bOk"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&ChooseNumberBox::HandleOk, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("ChooseNumberBoxFrame/bCancel"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&ChooseNumberBox::HandleCancel, this));

		_myBox->hide();
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init ChooseNumberBox: ") + ex.getMessage().c_str());
	}
}



	
/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool ChooseNumberBox::HandleOk (const CEGUI::EventArgs& e)
{
	_myBox->hide();
	long choosenV = (long)static_cast<CEGUI::Spinner *> (
		CEGUI::WindowManager::getSingleton().getWindow("ChooseNumberBoxFrame/spinner"))
		->getCurrentValue();

	if(_currCallback)
		_currCallback->CallbackChooseNumber(_currId, choosenV, _currFlag);
	return true;
}
	

/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool ChooseNumberBox::HandleCancel (const CEGUI::EventArgs& e)
{
	_myBox->hide();
	return true;
}



/***********************************************************
display the chatbox on screen
***********************************************************/
void ChooseNumberBox::Show(GuiCallbackableBase * callback, long id, long maxnumber, bool flag)
{
	_currId = id;
	_currMaxNum = maxnumber;
	_currFlag = flag;
	_currCallback = callback;

	static_cast<CEGUI::Spinner *> (
		CEGUI::WindowManager::getSingleton().getWindow("ChooseNumberBoxFrame/spinner"))
		->setMaximumValue(_currMaxNum);

	static_cast<CEGUI::Spinner *> (
		CEGUI::WindowManager::getSingleton().getWindow("ChooseNumberBoxFrame/spinner"))
		->setCurrentValue(_currMaxNum);	

	_myBox->show();
	_myBox->activate();
}


