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

#include "LetterEditorBox.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "OSGHandler.h"
#include "GUILocalizationCallback.h"

#include <iostream>
#include <algorithm>
#include <CEGUI.h>



/***********************************************************
constructor
***********************************************************/
LetterEditorBox::LetterEditorBox()
{

}


/***********************************************************
destructor
***********************************************************/
LetterEditorBox::~LetterEditorBox()
{
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("LetterEditorWIndowFrame"));

		int resX, resY; 
		bool fullscreen;
		OsgHandler::getInstance()->GetScreenAttributes(resX, resY, fullscreen);

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.PosX", vec.d_x.asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.PosY", vec.d_y.asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.SizeX", frw->getWidth().asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.SizeY", frw->getHeight().asRelative((float)resY));
	}
}


/***********************************************************
initalize the box
***********************************************************/
void LetterEditorBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "lettereditor.layout",
								"", "", &MyPropertyCallback);
		Root->addChildWindow(_myBox);

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("LEditGoB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&LetterEditorBox::HandleOK, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("LEditCancelB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&LetterEditorBox::HandleCancel, this));

		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("LetterEditorWIndowFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&LetterEditorBox::HandleCancel, this));

		_myBox->hide();


		float PosX, PosY, SizeX, SizeY;
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.PosX", PosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.PosY", PosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.SizeX", SizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.SizeY", SizeY);
		frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, 0), CEGUI::UDim(PosY, 0)));
		frw->setWidth(CEGUI::UDim(SizeX, 0));
		frw->setHeight(CEGUI::UDim(SizeY, 0));
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init LetterEditorBox: ") + ex.getMessage().c_str());
	}
}





/***********************************************************
handle connect button event
***********************************************************/
bool LetterEditorBox::HandleOK(const CEGUI::EventArgs& e)
{
	try
	{
		_myBox->hide();

		LbaNet::GuiUpdatesSeq updseq;
		LbaNet::CreateLetterUpdate * upd = 
			new LbaNet::CreateLetterUpdate(
					CEGUI::WindowManager::getSingleton().getWindow("LetterEditorSubjectEdit")->getText().c_str(),
					CEGUI::WindowManager::getSingleton().getWindow("LetterEditorMessage")->getText().c_str()
					);
		updseq.push_back(upd);
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), "InventoryBox", updseq));

	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception LetterEditorBox HandleOK: ") + ex.getMessage().c_str());
	}

	return true;
}

/***********************************************************
handle connect button event
***********************************************************/
bool LetterEditorBox::HandleCancel (const CEGUI::EventArgs& e)
{
	_myBox->hide();
	return true;
}



/***********************************************************
refresh gui with info from server
***********************************************************/
void LetterEditorBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{
}


/***********************************************************
update gui with info from server
***********************************************************/
void LetterEditorBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{
}


/***********************************************************
show GUI
***********************************************************/
void LetterEditorBox::Display()
{
	if(!_myBox->isVisible())
	{
		CEGUI::WindowManager::getSingleton().getWindow("LetterEditorSubjectEdit")->setText("");
		CEGUI::WindowManager::getSingleton().getWindow("LetterEditorMessage")->setText("");
		_myBox->show();
	}
}

/***********************************************************
hide GUI
***********************************************************/
void LetterEditorBox::Hide()
{
	_myBox->hide();
}

/***********************************************************
show/hide GUI
***********************************************************/
void LetterEditorBox::ToggleDisplay()
{
	if(_myBox->isVisible())
		_myBox->hide();
	else
	{
		CEGUI::WindowManager::getSingleton().getWindow("LetterEditorSubjectEdit")->setText("");
		CEGUI::WindowManager::getSingleton().getWindow("LetterEditorMessage")->setText("");
		_myBox->show();
		_myBox->activate();
	}
}

/***********************************************************
focus GUI
***********************************************************/
void LetterEditorBox::Focus(bool focus)
{

}


/***********************************************************
save size of windows to be restored after resize of the application
***********************************************************/
void LetterEditorBox::SaveGUISizes(int oldscreenX, int oldscreenY)
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("LetterEditorWIndowFrame"));

	CEGUI::UVector2 vec = frw->getPosition();
	_savedPosX = vec.d_x.asRelative((float)oldscreenX);
	_savedPosY = vec.d_y.asRelative((float)oldscreenY);
	_savedSizeX = frw->getWidth().asRelative((float)oldscreenX);
	_savedSizeY = frw->getHeight().asRelative((float)oldscreenY);
}


/***********************************************************
restore the correct size of the windows
***********************************************************/
void LetterEditorBox::RestoreGUISizes()
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("LetterEditorWIndowFrame"));

	frw->setPosition(CEGUI::UVector2(CEGUI::UDim(_savedPosX, 0), CEGUI::UDim(_savedPosY, 0)));
	frw->setWidth(CEGUI::UDim(_savedSizeX, 0));
	frw->setHeight(CEGUI::UDim(_savedSizeY, 0));
}


