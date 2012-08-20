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

#include "LoginGUI.h"
#include <CEGUI.h>
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "MusicHandler.h"
#include "EventsQueue.h"
#include "ClientExtendedEvents.h"
#include "GUILocalizationCallback.h"
#include "Localizer.h"
#include "DataDirHandler.h"
#include <QMessageBox>


/***********************************************************
	Constructor
***********************************************************/
LoginGUI::LoginGUI()
{
}


/***********************************************************
	Destructor
***********************************************************/
LoginGUI::~LoginGUI()
{
}



/***********************************************************
init function
***********************************************************/
void LoginGUI::Initialize()
{
	try
	{
		_root = CEGUI::WindowManager::getSingleton().loadWindowLayout( "LoginWindow.layout",
								"", "", &MyPropertyCallback);


		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("ConnectB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&LoginGUI::HandleConnect, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("CancelB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&LoginGUI::HandleCancel, this));



		CEGUI::WindowManager::getSingleton().getWindow("LBaNetLogo")->disable();
		CEGUI::WindowManager::getSingleton().getWindow("LBaNetLogoCenter")->disable();

		CEGUI::Editbox * pt = static_cast<CEGUI::Editbox *> (
				CEGUI::WindowManager::getSingleton().getWindow("PasswordText"));
		if(pt)
			pt->setTextMasked(true);

		std::string name = ConfigurationManager::GetInstance()->GetValue<std::string>("Player.Name", "");
		CEGUI::Editbox * lt = static_cast<CEGUI::Editbox *> (
				CEGUI::WindowManager::getSingleton().getWindow("LoginText"));
		lt->setText(name);

		CEGUI::WindowManager::getSingleton().getWindow("DisplayLoginErrorFrame")->hide();


		static_cast<CEGUI::FrameWindow *>(
			CEGUI::WindowManager::getSingleton().getWindow("LoginWIndowFrame"))->setDragMovingEnabled(false);

		static_cast<CEGUI::FrameWindow *>(
			CEGUI::WindowManager::getSingleton().getWindow("LoginWIndowFrame"))->setRollupEnabled(false);


		static_cast<CEGUI::PushButton *> (CEGUI::WindowManager::getSingleton().getWindow("DisplayLoginErrorFrame/bok"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&LoginGUI::HandleCloseTextClicked, this));

		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("DisplayLoginErrorFrame"));
		frw->subscribeEvent (CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&LoginGUI::HandleCloseTextClicked, this));


		CEGUI::WindowManager::getSingleton().getWindow("PasswordText")->subscribeEvent(CEGUI::Window::EventKeyDown,
			CEGUI::Event::Subscriber (&LoginGUI::HandleEnterKey, this));
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
bool LoginGUI::HandleConnect(const CEGUI::EventArgs& e)
{
	try
	{
		CEGUI::WindowManager::getSingleton().getWindow("DisplayLoginErrorFrame")->hide();

		CEGUI::Editbox * lt = static_cast<CEGUI::Editbox *> (
				CEGUI::WindowManager::getSingleton().getWindow("LoginText"));
		CEGUI::Editbox * pt = static_cast<CEGUI::Editbox *> (
				CEGUI::WindowManager::getSingleton().getWindow("PasswordText"));

		CEGUI::Checkbox * cbl = static_cast<CEGUI::Checkbox *> (
				CEGUI::WindowManager::getSingleton().getWindow("LoginPlayLocalCb"));


		if(lt && pt && cbl)
		{
			bool seleplaylo = cbl->isSelected();
			std::string txtl = lt->getText().c_str();
			std::string txtt = pt->getText().c_str();
			if((txtl != "") && (txtl.size() <= 20) && (txtt.size() <= 20))
			{
				std::string samples = DataDirHandler::getInstance()->GetDataDirPath() + "/GUI/lba2launcherblob.wav";
				MusicHandler::getInstance()->PlaySample2D(samples, false, true);
				ConfigurationManager::GetInstance()->SetValue("Player.Name", txtl);
				pt->setText("");

				EventsQueue::getReceiverQueue()->AddEvent(new LoginEvent(txtl, txtt, seleplaylo));
			}
		}
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception trying to get connection info from the gui: ") + ex.getMessage().c_str());
		return false;
	}

	return true;
}


/***********************************************************
handle cancel button event
***********************************************************/
bool LoginGUI::HandleCancel (const CEGUI::EventArgs& e)
{
	EventsQueue::getReceiverQueue()->AddEvent(new QuitGameEvent());
	return true;
}


/***********************************************************
set the client version text
***********************************************************/
void LoginGUI::SetClientVersion(const std::string &clientversion)
{
	CEGUI::WindowManager::getSingleton().getWindow("ClientVersionText")->setText(clientversion);
}

/***********************************************************
set if the server is on or not
***********************************************************/
void LoginGUI::SetServrOn(bool ServerOn)
{
	try
	{
		CEGUI::Window * lt = static_cast<CEGUI::Window *> (
				CEGUI::WindowManager::getSingleton().getWindow("ServerOnLabel"));

		lt->setText((ServerOn ? (const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 78).c_str() 
								: (const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 79).c_str()));

		if(!ServerOn)
		{
			CEGUI::Checkbox* cb = static_cast<CEGUI::Checkbox *> (
					CEGUI::WindowManager::getSingleton().getWindow("LoginPlayLocalCb"));
			cb->setSelected(true);
		}
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception trying to set server state from the gui: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
inform the user the login failed
***********************************************************/
void LoginGUI::InformNotLoggedIn(int problem, const std::string & reason)
{
	try
	{
		std::string text;
		//CEGUI::MultiLineEditbox * txs =
		//static_cast<CEGUI::MultiLineEditbox *> (CEGUI::WindowManager::getSingleton().getWindow("DisplayLoginErrorFrame/text"));


		if(problem == 0)	// can not connect to the server
		{
			text += Localizer::getInstance()->GetText(Localizer::GUI, 80) + "\n" +
						Localizer::getInstance()->GetText(Localizer::GUI, 81).c_str();
			//txs->setText("");
			//txs->appendText((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 80).c_str());
			//txs->appendText((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 81).c_str());
		}

		if(problem == -1)	// wrong login / password
		{
			//txs->setText("");
			//txs->appendText((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 80).c_str());
			//txs->appendText((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 82).c_str());
			//txs->appendText(reason);

			text += Localizer::getInstance()->GetText(Localizer::GUI, 80) + "\n" +
						Localizer::getInstance()->GetText(Localizer::GUI, 82).c_str() + "\n" +
						reason;
		}

		if(problem == -2)	// got disconnected
		{
			//txs->setText("");
			//txs->appendText((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 83).c_str());
		
			text += Localizer::getInstance()->GetText(Localizer::GUI, 83);
		}

		//CEGUI::WindowManager::getSingleton().getWindow("DisplayLoginErrorFrame")->show();

		

		QMessageBox::warning(NULL, QString::fromUtf8(Localizer::getInstance()->GetText(Localizer::GUI, 30).c_str()),
								QString::fromUtf8(text.c_str()), QMessageBox::Ok, QMessageBox::Ok);


	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception showing login error window: ") + ex.getMessage().c_str());
		_root = NULL;
	}
}


/***********************************************************
handle cancel button event
***********************************************************/
bool LoginGUI::HandleCloseTextClicked (const CEGUI::EventArgs& e)
{
	try
	{
		CEGUI::WindowManager::getSingleton().getWindow("DisplayLoginErrorFrame")->hide();
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception hidding login error window: ") + ex.getMessage().c_str());
		_root = NULL;
	}

	return true;
}



/***********************************************************
called to infrom the gui that it is displayed
***********************************************************/
void LoginGUI::Displayed()
{
	CEGUI::WindowManager::getSingleton().getWindow("PasswordText")->activate();
	
}



/***********************************************************
catch key event
***********************************************************/
bool LoginGUI::HandleEnterKey (const CEGUI::EventArgs& e)
{
	const CEGUI::KeyEventArgs& we =
    static_cast<const CEGUI::KeyEventArgs&>(e);

	if(we.scancode == CEGUI::Key::Return)
	{	
		return HandleConnect(e);
	}

	return false;
}
