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

#include "MessageBox.h"
#include <CEGUI.h>
#include "LogHandler.h"

CGMessageBox* CGMessageBox::_singletonInstance = NULL;



/***********************************************************
singleton pattern
***********************************************************/
CGMessageBox * CGMessageBox::getInstance()
{
    if(!_singletonInstance)
    {
        _singletonInstance = new CGMessageBox();
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
CGMessageBox::CGMessageBox()
{
}


/***********************************************************
destructor
***********************************************************/
CGMessageBox::~CGMessageBox()
{
}


/***********************************************************
initalize the box
***********************************************************/
void CGMessageBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "textbox.layout" );
		Root->addChildWindow(_myBox);


		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("MessageBoxFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&CGMessageBox::HandleOk, this));


		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("MessageBoxFrame/bok"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&CGMessageBox::HandleOk, this));


		_myBox->hide();
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init MessageBox: ") + ex.getMessage().c_str());
	}
}



	
/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool CGMessageBox::HandleOk (const CEGUI::EventArgs& e)
{
	_myBox->hide();
	return true;
}
	


/***********************************************************
display the chatbox on screen
***********************************************************/
void CGMessageBox::Show(const std::string &Title, const std::string &Message)
{
	CEGUI::WindowManager::getSingleton().getWindow("MessageBoxFrame")->setText(Title);
	CEGUI::WindowManager::getSingleton().getWindow("MessageBoxFrame/text")->setText(Message);

	if(_myBox->isVisible())
		_myBox->hide();
	else
	{
		_myBox->show();
		_myBox->activate();
	}

}


