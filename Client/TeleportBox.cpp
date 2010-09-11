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

#include "TeleportBox.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"

#include <iostream>
#include <algorithm>
#include <CEGUI.h>



// Sample sub-class for ListboxTextItem that auto-sets the selection brush
// image.  This saves doing it manually every time in the code.
class MyTeleListItem : public CEGUI::ListboxTextItem
{
public:
    MyTeleListItem (const CEGUI::String& text) : CEGUI::ListboxTextItem(text)
    {
        setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    }
};


/***********************************************************
constructor
***********************************************************/
TeleportBox::TeleportBox()
{
}


/***********************************************************
destructor
***********************************************************/
TeleportBox::~TeleportBox()
{
	try
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("TeleportFrame"));

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.Teleportbox.PosX", vec.d_x.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Teleportbox.PosY", vec.d_y.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Teleportbox.SizeX", frw->getWidth().d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Teleportbox.SizeY", frw->getHeight().d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Teleportbox.OffsetPosX", vec.d_x.d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Teleportbox.OffsetPosY", vec.d_y.d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Teleportbox.OffsetSizeX", frw->getWidth().d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Teleportbox.OffsetSizeY", frw->getHeight().d_offset);
		ConfigurationManager::GetInstance()->SetBool("Gui.Teleportbox.Visible", frw->isVisible());
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception destructor teleport box: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
initalize the box
***********************************************************/
void TeleportBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "TeleportBox.layout" );
		Root->addChildWindow(_myBox);


		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("TeleportCancelButton"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&TeleportBox::HandleClose, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("TeleporGoButton"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&TeleportBox::HandleGoButton, this));


		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("TeleportFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&TeleportBox::HandleClose, this));

		float PosX, PosY, SizeX, SizeY, OPosX, OPosY, OSizeX, OSizeY;
		bool Visible;
		ConfigurationManager::GetInstance()->GetFloat("Gui.Teleportbox.PosX", PosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Teleportbox.PosY", PosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Teleportbox.SizeX", SizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Teleportbox.SizeY", SizeY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Teleportbox.OffsetPosX", OPosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Teleportbox.OffsetPosY", OPosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Teleportbox.OffsetSizeX", OSizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Teleportbox.OffsetSizeY", OSizeY);
		ConfigurationManager::GetInstance()->GetBool("Gui.Teleportbox.Visible", Visible);
		frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, OPosX), CEGUI::UDim(PosY, OPosY)));
		frw->setWidth(CEGUI::UDim(SizeX, OSizeX));
		frw->setHeight(CEGUI::UDim(SizeY, OSizeY));

		if(Visible)
			frw->show();
		else
			frw->hide();
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init teleport box: ") + ex.getMessage().c_str());
	}
}




/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool TeleportBox::HandleClose (const CEGUI::EventArgs& e)
{
	_myBox->hide();
	return true;
}




/***********************************************************
handle GO button pressed
***********************************************************/
bool TeleportBox::HandleGoButton (const CEGUI::EventArgs& e)
{
    CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
        CEGUI::WindowManager::getSingleton().getWindow("TeleportList"));

	MyTeleListItem * it = static_cast<MyTeleListItem *> (lb->getFirstSelectedItem());
	if(it != NULL)
	{
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::TeleportEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), it->getText().c_str()));

		HandleClose(e);
	}

	return true;
}


/***********************************************************
refresh gui with info from server
***********************************************************/
void TeleportBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{
	for(size_t i=0; i<Parameters.size(); ++i)
	{
		LbaNet::GuiParameterBase * ptr = Parameters[i].get();
		const std::type_info& info = typeid(*ptr);

		// got player teleport list refresh event
		if(info == typeid(LbaNet::TeleportGuiParameter))
		{
			LbaNet::TeleportGuiParameter * castedptr = 
				dynamic_cast<LbaNet::TeleportGuiParameter *>(ptr);

			CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
				CEGUI::WindowManager::getSingleton().getWindow("TeleportList"));
			lb->resetList();

			LbaNet::TeleportsSeq	&_tplist = castedptr->TeleportList;
			LbaNet::TeleportsSeq::const_iterator it = _tplist.begin();
			LbaNet::TeleportsSeq::const_iterator end = _tplist.end();
			for(; it != end; ++it)
				lb->addItem(new MyTeleListItem(*it));
		}
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void TeleportBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{

}

/***********************************************************
show GUI
***********************************************************/
void TeleportBox::Display()
{
	_myBox->show();
	_myBox->activate();
}

/***********************************************************
hide GUI
***********************************************************/
void TeleportBox::Hide()
{
	_myBox->hide();
}

/***********************************************************
show/hide GUI
***********************************************************/
void TeleportBox::ToggleDisplay()
{
	if(_myBox->isVisible())
		_myBox->hide();
	else
	{
		_myBox->show();
		_myBox->activate();
	}
}

/***********************************************************
focus GUI
***********************************************************/
void TeleportBox::Focus(bool focus)
{

}