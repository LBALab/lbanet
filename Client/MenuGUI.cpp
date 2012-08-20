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

#include "MenuGUI.h"
#include <CEGUI.h>
#include <iostream>
#include "LogHandler.h"
#include "EventsQueue.h"
#include "ClientExtendedEvents.h"
#include "GUILocalizationCallback.h"
#include "DataDirHandler.h"

/***********************************************************
constructor
***********************************************************/
MenuGUI::MenuGUI()
{
}


/***********************************************************
destructor
***********************************************************/
MenuGUI::~MenuGUI()
{
}

/***********************************************************
initialize the GUI
***********************************************************/
void MenuGUI::Initialize()
{
	try
	{
		// Load the Imageset that has the pictures for our button.
		_root = CEGUI::WindowManager::getSingleton().loadWindowLayout( "MenuWindow.layout",
								"", "", &MyPropertyCallback);

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("MenubResume"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MenuGUI::HandleResume, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("MenubInventory"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MenuGUI::HandleInventory, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("MenubOption"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MenuGUI::HandleOption, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("MenubSwitchWorld"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MenuGUI::HandleSwitchWorld, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("MenubDisconnect"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MenuGUI::HandleDisconnect, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("MenubQuit"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MenuGUI::HandleQuit, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("MenubCredits"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MenuGUI::HandleCredits, this));
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init login gui: ") + ex.getMessage().c_str());
		_root = NULL;
	}
}



/***********************************************************
handle connect button event
***********************************************************/
bool MenuGUI::HandleResume(const CEGUI::EventArgs& e)
{
	EventsQueue::getReceiverQueue()->AddEvent(new GuiExitEvent());
	return true;
}


/***********************************************************
handle connect button event
***********************************************************/
bool MenuGUI::HandleInventory (const CEGUI::EventArgs& e)
{
	EventsQueue::getReceiverQueue()->AddEvent(new DisplayGUIEvent(5));
	return true;
}


/***********************************************************
handle connect button event
***********************************************************/
bool MenuGUI::HandleOption (const CEGUI::EventArgs& e)
{
	EventsQueue::getReceiverQueue()->AddEvent(new DisplayGUIEvent(4));
	return true;
}


/***********************************************************
handle connect button event
***********************************************************/
bool MenuGUI::HandleSwitchWorld(const CEGUI::EventArgs& e)
{
	if(!DataDirHandler::getInstance()->IsInEditorMode())
		EventsQueue::getReceiverQueue()->AddEvent(new DisplayGUIEvent(1));

	return true;
}


/***********************************************************
handle connect button event
***********************************************************/
bool MenuGUI::HandleDisconnect (const CEGUI::EventArgs& e)
{
	if(!DataDirHandler::getInstance()->IsInEditorMode())
		EventsQueue::getReceiverQueue()->AddEvent(new DisplayGUIEvent(0));

	return true;
}


/***********************************************************
handle connect button event
***********************************************************/
bool MenuGUI::HandleQuit(const CEGUI::EventArgs& e)
{
	EventsQueue::getReceiverQueue()->AddEvent(new QuitGameEvent());
	return true;
}


/***********************************************************
handle connect button event
***********************************************************/
bool MenuGUI::HandleCredits (const CEGUI::EventArgs& e)
{
	return true;
}


