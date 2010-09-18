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

#include "LbaNetEngine.h"
#include "OSGHandler.h"
#include "LogHandler.h"
#include "PhysXEngine.h"
#include "MusicHandler.h"
#include "ConfigurationManager.h"
#include "SynchronizedTimeHandler.h"
#include "GuiHandler.h"
#include "EventsQueue.h"
#include "ClientExtendedEvents.h"
#include "ClientExtendedTypes.h"
#include "LbaNetModel.h"
#include "RemoteConnectionHandler.h"
#include "LocalConnectionHandler.h"
#include "ChatServerHandler.h"


#include <IceUtil/Thread.h>

#define TIME_PER_FRAME 17

/***********************************************************
	Constructor
***********************************************************/
LbaNetEngine::LbaNetEngine(Ice::CommunicatorPtr communicator, const std::string & clientV)
: m_currentstate(EGaming), m_oldstate(ELogin), m_clientV(clientV),
	m_communicator(communicator), m_shouldexit(false)
{
	Initialize();
	SwitchGuiToLogin();
}


/***********************************************************
	Destructor
***********************************************************/
LbaNetEngine::~LbaNetEngine()
{	
	LogHandler::getInstance()->LogToFile("Finalizing Game...");


	// finalize music handler
	LogHandler::getInstance()->LogToFile("Finalizing sound engine...");
	MusicHandler::getInstance()->Unitialize();

	// finalize OSG
	LogHandler::getInstance()->LogToFile("Finalizing Display engine...");
	OsgHandler::getInstance()->Finalize();

	// delete physic engine
	LogHandler::getInstance()->LogToFile("Finalizing physic engine...");
	PhysXEngine::getInstance()->Quit();
}



/***********************************************************
initialize the class
***********************************************************/
void LbaNetEngine::Initialize(void)
{
	// init gui
	m_gui_handler = boost::shared_ptr<GuiHandler>(new GuiHandler());


	//int model
	m_lbaNetModel = boost::shared_ptr<LbaNetModel>(new LbaNetModel());


	LogHandler::getInstance()->LogToFile("Initializing Game...");

	// init music handler
	LogHandler::getInstance()->LogToFile("Initializing sound engine...");
	MusicHandler::getInstance()->Initialize();


	// init OSG
	LogHandler::getInstance()->LogToFile("Initializing display engine...");
	OsgHandler::getInstance()->Initialize("LBANet", "./Data", m_gui_handler);


	//init physic engine
	LogHandler::getInstance()->LogToFile("Initialize physic engine...");
	float gravity = -1.0;
	ConfigurationManager::GetInstance()->GetFloat("Physic.GlobalGravity", gravity);
	PhysXEngine::getInstance()->Init(gravity);



	//check if server is online
	LogHandler::getInstance()->LogToFile("Test connection with server...");
	bool serveronline = RemoteConnectionHandler::IsServerOn(m_communicator);
	m_gui_handler->SetServrOn(serveronline);
	m_gui_handler->SetClientVersion(m_clientV);

	LogHandler::getInstance()->LogToFile("Initializing Completed.");
}


/***********************************************************
entry point of the engine
***********************************************************/
void LbaNetEngine::run(void)
{
	//TODO - for test - to remove
	//boost::shared_ptr<DisplayInfo> DInfo(new DisplayInfo(boost::shared_ptr<DisplayTransformation>(),
	//	boost::shared_ptr<DisplayObjectDescriptionBase>(new OsgSimpleObjectDescription("Worlds/Lba1/Grids/map0.osgb"))));

	//boost::shared_ptr<PhysicalDescriptionBase> PInfo(new PhysicalDescriptionTriangleMesh(0, 0, 0,
	//																			"Worlds/Lba1/Grids/map0.phy",
	//																			true));
	//ObjectInfo objinfo(1, DInfo, PInfo,	true);
	//boost::shared_ptr<DynamicObject> ground = objinfo.BuildSelf(OsgHandler::getInstance());

	//m_lbaNetModel->AddObject(objinfo, false);

	//SwitchGuiToGame();


	try
	{
		// init time
		double lasttime = SynchronizedTimeHandler::GetCurrentTimeDouble();
		double waittime = lasttime;

		// Loop until a quit event is found
		while(!m_shouldexit && !OsgHandler::getInstance()->Update())
		{
			//get physic results
			PhysXEngine::getInstance()->GetPhysicsResults();


			// process stuff between frame
			Process();


			// pause the program for a few milliseconds
			double currwtime = SynchronizedTimeHandler::GetCurrentTimeDouble();
			double wdiff = (currwtime-waittime);
			long timelong = (long)(wdiff);
			if(timelong < TIME_PER_FRAME)
				IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(TIME_PER_FRAME-timelong));


			// mesure the time used to do one cycle
			waittime = SynchronizedTimeHandler::GetCurrentTimeDouble();

			//start physic calculation
			PhysXEngine::getInstance()->StartPhysics();
		}
	}
	catch(std::exception & ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Unhandled exception catched:") + ex.what());
	}
	catch(...)
	{
		LogHandler::getInstance()->LogToFile(std::string("Unknown exception catched"));
	}

	LogHandler::getInstance()->LogToFile("Quitting the game.");


	//disconnect from server
	Disconnect();
}



/***********************************************************
process function
***********************************************************/
void LbaNetEngine::Process(void)
{
	//handle game events
	HandleGameEvents();

	// process model (update display stuff)
	m_lbaNetModel->Process();

	// process GUI
	m_gui_handler->Process();

	//process sound
	MusicHandler::getInstance()->Update();
}




/***********************************************************
called to check for game events and handle them
***********************************************************/
void LbaNetEngine::HandleGameEvents()
{
	// fetch all pending events
	LbaNet::EventsSeq events;
	EventsQueue::getReceiverQueue()->GetEvents(events);
	LbaNet::EventsSeq::iterator it = events.begin();
	LbaNet::EventsSeq::iterator end = events.end();
	for(;it != end; ++it)
	{
		LbaNet::ClientServerEventBasePtr ptr = *it;
		LbaNet::ClientServerEventBase & obj = *ptr;
		const std::type_info& info = typeid(obj);

		// server send his id to the client
		if(info == typeid(LbaNet::ClientIdEvent))
		{
			LbaNet::ClientIdEvent * castedptr = 
				dynamic_cast<LbaNet::ClientIdEvent *>(&obj);

			m_lbaNetModel->SetPlayerId((long)castedptr->Id);
		}

		
		
		// server send list of available worlds to client
		if(info == typeid(LbaNet::AvailableWorldsEvent))
		{
			LbaNet::AvailableWorldsEvent * castedptr = 
				dynamic_cast<LbaNet::AvailableWorldsEvent *>(&obj);

			m_gui_handler->SetWorldList(castedptr->Worlds);
		}
		
		
		
		// server ask client to refresh a certain GUI in game
		if(info == typeid(LbaNet::RefreshGameGUIEvent))
		{
			LbaNet::RefreshGameGUIEvent * castedptr = 
				dynamic_cast<LbaNet::RefreshGameGUIEvent *>(&obj);

			m_gui_handler->RefreshGameGUI(castedptr->GUIId, castedptr->Parameters, 
											castedptr->Show, castedptr->Hide);
		}
		

		// client/server update something in part of the GUI
		if(info == typeid(LbaNet::UpdateGameGUIEvent))
		{
			LbaNet::UpdateGameGUIEvent * castedptr = 
				dynamic_cast<LbaNet::UpdateGameGUIEvent *>(&obj);

			m_gui_handler->UpdateGameGUI(castedptr->GUIId, castedptr->Updates);
		}


		// LoginEvent
		if(info == typeid(LoginEvent))
		{
			LoginEvent * castedptr = 
				dynamic_cast<LoginEvent *>(&obj);

			TryLogin(castedptr->_Name, castedptr->_Password, castedptr->_Local);
		}


		// GuiExitEvent
		if(info == typeid(GuiExitEvent))
		{
			ExitGui();
		}

		// QuitGameEvent
		if(info == typeid(QuitGameEvent))
		{
			m_shouldexit = true;
		}


		// ChangeWorldEvent
		if(info == typeid(ChangeWorldEvent))
		{
			ChangeWorldEvent * castedptr = 
				dynamic_cast<ChangeWorldEvent *>(&obj);

			// update 
			ChangeWorld(castedptr->_NewWorldName);
		}


		// FocusChatEvent
		if(info == typeid(FocusChatEvent))
		{
			m_gui_handler->FocusGameGUI("ChatBox", true);
		}


		// WhisperChannelEvent
		if(info == typeid(DisplayGUIEvent))
		{
			DisplayGUIEvent * castedptr = 
				dynamic_cast<DisplayGUIEvent *>(&obj);

			DisplayGUI(castedptr->_GuiNumber);
		}


		// NewFontSizeEvent
		if(info == typeid(NewFontSizeEvent))
		{
			m_gui_handler->ReloadFontSize();
		}


		// PlayerNameColorChangedEvent
		if(info == typeid(PlayerNameColorChangedEvent))
		{
			PlayerNameColorChangedEvent * castedptr = 
				dynamic_cast<PlayerNameColorChangedEvent *>(&obj);

			// inform server
			if(m_chatH)
				m_chatH->ChangeNameColor(castedptr->_color);
		}


		// SendChatTextEvent
		if(info == typeid(SendChatTextEvent))
		{
			SendChatTextEvent * castedptr = 
				dynamic_cast<SendChatTextEvent *>(&obj);

			// inform server
			if(m_chatH)
				m_chatH->SendChatText(castedptr->_text);
		}


		// PlayerStatusUpdateEvent
		if(info == typeid(PlayerStatusUpdateEvent))
		{
			PlayerStatusUpdateEvent * castedptr = 
				dynamic_cast<PlayerStatusUpdateEvent *>(&obj);

			// update chat
			{
				LbaNet::GuiUpdatesSeq updseq;
				NameColorChangedUpdate * upd = 
					new NameColorChangedUpdate(castedptr->_name, castedptr->_color);
				updseq.push_back(upd);
				m_gui_handler->UpdateGameGUI("ChatBox", updseq);
			}

			// update community box
			{
				LbaNet::PlayerOnline NewInfo;
				NewInfo.Joined = true;
				NewInfo.Nickname = castedptr->_name;
				NewInfo.Status = castedptr->_status;
				NewInfo.Color = castedptr->_color;
				LbaNet::GuiUpdatesSeq updseq;
				LbaNet::PlayerStatusChanged * upd = new LbaNet::PlayerStatusChanged(NewInfo);
				updseq.push_back(upd);
				m_gui_handler->UpdateGameGUI("CommunityBox", updseq);
			}
		}
	}
}

/***********************************************************
disconnect from server
***********************************************************/
void LbaNetEngine::Disconnect()
{
	if(m_serverConH)
		m_serverConH->Disconnect();

	m_chatH = boost::shared_ptr<ChatServerHandler>();
	m_serverConH = boost::shared_ptr<ConnectionHandlerBase>();
}


/***********************************************************
switch gui helpers
***********************************************************/
void LbaNetEngine::SwitchGuiToLogin()
{
	if(m_currentstate == ELogin)
		return;

	// disconnect from servers
	Disconnect();

	// clean up the world on disconnect
	m_lbaNetModel->CleanupWorld();

	PlayMenuMusic();

	m_gui_handler->SwitchGUI(0);
	m_oldstate = m_currentstate;
	m_currentstate = ELogin;
}

/***********************************************************
switch gui helpers
***********************************************************/
void LbaNetEngine::SwitchGuiToChooseWorld()
{
	if(m_currentstate == EChoosingWorld)
		return;

	m_lbaNetModel->Pause();

	PlayMenuMusic();
	m_gui_handler->SwitchGUI(1);
	m_oldstate = m_currentstate;
	m_currentstate = EChoosingWorld;
}

/***********************************************************
switch gui helpers
***********************************************************/
void LbaNetEngine::SwitchGuiToGame()
{
	if(m_currentstate == EGaming)
		return;

	if(m_lastmusic != "")
		MusicHandler::getInstance()->PlayMusic(m_lastmusic, 0);

	m_lbaNetModel->Resume(false);
	m_gui_handler->SwitchGUI(2);
	m_gui_handler->RefreshOption();

	m_oldstate = m_currentstate;
	m_currentstate = EGaming;
}

/***********************************************************
switch gui helpers
***********************************************************/
void LbaNetEngine::SwitchGuiToMenu()
{
	if(m_currentstate == EMenu)
	{
		SwitchGuiToGame();
		return;
	}

	if(m_currentstate == EGaming)
	{
		m_lbaNetModel->Pause();
		m_gui_handler->SwitchGUI(3);
		m_oldstate = m_currentstate;
		m_currentstate = EMenu;
	}
}

/***********************************************************
switch gui helpers
***********************************************************/
void LbaNetEngine::SwitchGuiToOption()
{
	if(m_currentstate == EOption)
		return;

	m_lbaNetModel->Pause();
	m_gui_handler->SwitchGUI(4);
	m_oldstate = m_currentstate;
	m_currentstate = EOption;
}



/***********************************************************
try to login to the server
***********************************************************/
void LbaNetEngine::TryLogin(const std::string &Name, const std::string &Password, bool uselocalserver)
{
	if(uselocalserver)
	{
		m_serverConH = boost::shared_ptr<ConnectionHandlerBase>(new LocalConnectionHandler());
	}
	else
	{
		m_chatH = boost::shared_ptr<ChatServerHandler>(new ChatServerHandler());
		m_serverConH = boost::shared_ptr<ConnectionHandlerBase>(new RemoteConnectionHandler(m_communicator, m_chatH));
	}

	std::string reason;
	int res = m_serverConH->Connect(Name, Password, reason);
	// check if connection to server failed
	if(res < 1)
	{
		if(res == 0)
			m_gui_handler->SetServrOn(false);

		m_gui_handler->InformNotLoggedIn(res, reason);
		return;
	}


	m_gui_handler->SetServrOn(true);
	m_gui_handler->RefreshOption();

	// change gui to change world
	DisplayGUI(1);
}



/***********************************************************
exit current active gui
***********************************************************/
void LbaNetEngine::ExitGui()
{
	switch(m_oldstate)
	{
		case ELogin:
			SwitchGuiToLogin();
		break;
		case EChoosingWorld:
			SwitchGuiToChooseWorld();
		break;
		case EGaming: case EMenu: case EOption:
			SwitchGuiToGame();
		break;
	}
}


/***********************************************************
change the world
***********************************************************/
void LbaNetEngine::ChangeWorld(const std::string & NewWorld)
{
	//clean up old world
	m_lbaNetModel->ChangeWorld(NewWorld);

	//set chat world name
	LbaNet::GuiUpdatesSeq upd;
	upd.push_back(new ChatWorldNameUpdate(NewWorld));
	m_gui_handler->UpdateGameGUI("ChatBox", upd);


	//change gui to game gui
	SwitchGuiToGame();

	// inform server
	if(m_serverConH)
		m_serverConH->ChangeWorld(NewWorld);
}

/***********************************************************
display a specific gui
***********************************************************/
void LbaNetEngine::DisplayGUI(int guinumber)
{
	switch(guinumber)
	{
		case -1: // got disconnected from server
			SwitchGuiToLogin();
			m_gui_handler->InformNotLoggedIn(-2, "");
		break;
		case 0:
			SwitchGuiToLogin();
		break;
		case 1:
			SwitchGuiToChooseWorld();
		break;
		case 2:
			SwitchGuiToGame();
		break;
		case 3:
			SwitchGuiToMenu();
		break;
		case 4:
			SwitchGuiToOption();
		break;
		case 5: // inventory
			SwitchGuiToGame();
			m_gui_handler->ShowGameGUI("InventoryBox");
		break;
	}
}


/***********************************************************
called to play the assigned music when menu
***********************************************************/
void LbaNetEngine::PlayMenuMusic()
{
	std::string mmusic = "Data/Lba1/Music/LBA1-Track9.mp3";

	std::string tmp = MusicHandler::getInstance()->GetCurrentMusic();
	if(tmp != mmusic)
	{
		m_lastmusic = tmp;
		MusicHandler::getInstance()->PlayMusic(mmusic, -1);
	}
}

