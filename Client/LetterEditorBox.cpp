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

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.PosX", vec.d_x.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.PosY", vec.d_y.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.SizeX", frw->getWidth().d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.SizeY", frw->getHeight().d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.OffsetPosX", vec.d_x.d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.OffsetPosY", vec.d_y.d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.OffsetSizeX", frw->getWidth().d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterEditorFrame.OffsetSizeY", frw->getHeight().d_offset);
	}
}


/***********************************************************
initalize the box
***********************************************************/
void LetterEditorBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "lettereditor.layout" );
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


		float PosX, PosY, SizeX, SizeY, OPosX, OPosY, OSizeX, OSizeY;
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.PosX", PosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.PosY", PosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.SizeX", SizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.SizeY", SizeY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.OffsetPosX", OPosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.OffsetPosY", OPosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.OffsetSizeX", OSizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterEditorFrame.OffsetSizeY", OSizeY);
		frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, OPosX), CEGUI::UDim(PosY, OPosY)));
		frw->setWidth(CEGUI::UDim(SizeX, OSizeX));
		frw->setHeight(CEGUI::UDim(SizeY, OSizeY));
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

