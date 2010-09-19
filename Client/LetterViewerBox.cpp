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

#include "LetterViewerBox.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "ClientExtendedTypes.h"
#include "OSGHandler.h"

#include <iostream>
#include <algorithm>
#include <CEGUI.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/local_time_adjustor.hpp>
#include <boost/date_time/c_local_time_adjustor.hpp>


/***********************************************************
constructor
***********************************************************/
LetterViewerBox::LetterViewerBox()
{

}


/***********************************************************
destructor
***********************************************************/
LetterViewerBox::~LetterViewerBox()
{
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("LetterViewerWIndowFrame"));

		int resX, resY; 
		bool fullscreen;
		OsgHandler::getInstance()->GetScreenAttributes(resX, resY, fullscreen);

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterViewerFrame.PosX", vec.d_x.asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterViewerFrame.PosY", vec.d_y.asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterViewerFrame.SizeX", frw->getWidth().asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.LetterViewerFrame.SizeY", frw->getHeight().asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetBool("Gui.LetterViewerFrame.Visible", frw->isVisible());
	}
}


/***********************************************************
initalize the box
***********************************************************/
void LetterViewerBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "letterviewer.layout" );
		Root->addChildWindow(_myBox);

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("LetterViewerGoB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&LetterViewerBox::HandleOK, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("LetterViewerDestroyB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&LetterViewerBox::HandleCancel, this));

		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("LetterViewerWIndowFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&LetterViewerBox::HandleOK, this));

		_myBox->hide();


		float PosX, PosY, SizeX, SizeY;
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterViewerFrame.PosX", PosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterViewerFrame.PosY", PosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterViewerFrame.SizeX", SizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.LetterViewerFrame.SizeY", SizeY);
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
display the chatbox on screen
***********************************************************/
void LetterViewerBox::SetLetter(long LetterId, const std::string & date, const std::string & from, 
							const std::string & subject, const std::string & message)
{
	_LetterId = LetterId;

	try
	{
		CEGUI::String str = "";
		if(date != "")
		{
			try
			{
				boost::posix_time::ptime pt = boost::posix_time::time_from_string(date);
				typedef boost::date_time::c_local_adjustor<boost::posix_time::ptime> local_adj;
				boost::posix_time::ptime converted = local_adj::utc_to_local(pt);
				str += CEGUI::String((const unsigned char *)boost::posix_time::to_simple_string(converted).c_str());
				str += " - ";
			}
			catch(...){}
		}
		str += "Letter from ";
		str += CEGUI::String((const unsigned char *)from.c_str());
		CEGUI::WindowManager::getSingleton().getWindow("LetterViewerWIndowFrame")->setText(str);

		CEGUI::String strsub((const unsigned char *)subject.c_str());
		CEGUI::WindowManager::getSingleton().getWindow("LetterViewerSubjectEdit")->setText(strsub);

		CEGUI::String strmess((const unsigned char *)message.c_str());
		CEGUI::WindowManager::getSingleton().getWindow("LetterViewerMessage")->setText(strmess);


		if(!_myBox->isVisible())
			_myBox->show();
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception LetterViewerBox Show: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
handle connect button event
***********************************************************/
bool LetterViewerBox::HandleOK(const CEGUI::EventArgs& e)
{
	_myBox->hide();
	_LetterId = -1;
	return true;
}

/***********************************************************
handle connect button event
***********************************************************/
bool LetterViewerBox::HandleCancel (const CEGUI::EventArgs& e)
{
	_myBox->hide();

	LbaNet::GuiUpdatesSeq updseq;
	LbaNet::DestroyItemUpdate * upd = 
		new LbaNet::DestroyItemUpdate(_LetterId);
	updseq.push_back(upd);
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "InventoryBox", updseq));


	_LetterId = -1;
	return true;
}





/***********************************************************
refresh gui with info from server
***********************************************************/
void LetterViewerBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{
	for(size_t i=0; i<Parameters.size(); ++i)
	{
		LbaNet::GuiParameterBase * ptr = Parameters[i].get();
		const std::type_info& info = typeid(*ptr);

		// shortcut updated
		if(info == typeid(LbaNet::LetterViewerGuiParameter))
		{
			LbaNet::LetterViewerGuiParameter * castedptr = 
				dynamic_cast<LbaNet::LetterViewerGuiParameter *>(ptr);

			const LbaNet::LetterInfo & linfo = castedptr->ToDisplayInfo;
			SetLetter((long)linfo.LetterId, linfo.Date, linfo.From, linfo.Subject, linfo.Message);
		}
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void LetterViewerBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{
}

/***********************************************************
show GUI
***********************************************************/
void LetterViewerBox::Display()
{
	_myBox->show();
}

/***********************************************************
hide GUI
***********************************************************/
void LetterViewerBox::Hide()
{
	_myBox->hide();
}

/***********************************************************
show/hide GUI
***********************************************************/
void LetterViewerBox::ToggleDisplay()
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
void LetterViewerBox::Focus(bool focus)
{

}



/***********************************************************
save size of windows to be restored after resize of the application
***********************************************************/
void LetterViewerBox::SaveGUISizes(int oldscreenX, int oldscreenY)
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("LetterViewerWIndowFrame"));

	CEGUI::UVector2 vec = frw->getPosition();
	_savedPosX = vec.d_x.asRelative((float)oldscreenX);
	_savedPosY = vec.d_y.asRelative((float)oldscreenY);
	_savedSizeX = frw->getWidth().asRelative((float)oldscreenX);
	_savedSizeY = frw->getHeight().asRelative((float)oldscreenY);
}


/***********************************************************
restore the correct size of the windows
***********************************************************/
void LetterViewerBox::RestoreGUISizes()
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("LetterViewerWIndowFrame"));

	frw->setPosition(CEGUI::UVector2(CEGUI::UDim(_savedPosX, 0), CEGUI::UDim(_savedPosY, 0)));
	frw->setWidth(CEGUI::UDim(_savedSizeX, 0));
	frw->setHeight(CEGUI::UDim(_savedSizeY, 0));
}