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
#include "Localizer.h"

#include <IceUtil/Thread.h>


#ifdef _USE_QT_EDITOR_
#include <QtGui/QApplication>
#include <QtGui/QtEvents>
#include "editorhandler.h"
#endif


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
	m_gui_handler = boost::shared_ptr<GuiHandler>();
	m_lbaNetModel = boost::shared_ptr<LbaNetModel>();

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
	// first get the language to use
	std::string language;
	ConfigurationManager::GetInstance()->GetString("Options.General.Language", language);
	if(language == "")
		language = "en";
	Localizer::getInstance()->SetLanguage(language);


#ifdef _USE_QT_EDITOR_
	m_editor_handler= boost::shared_ptr<EditorHandler>(new EditorHandler());
#endif

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
	#ifdef _USE_QT_EDITOR_
	OsgHandler::getInstance()->Initialize("LBANet", "./Data", m_gui_handler, m_editor_handler);
	#else
	OsgHandler::getInstance()->Initialize("LBANet", "./Data", m_gui_handler);
	#endif


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
	//	boost::shared_ptr<DisplayObjectDescriptionBase>(new OsgSimpleObjectDescription("Worlds/Lba1Original/Grids/map0.osgb"))));

	//boost::shared_ptr<PhysicalDescriptionBase> PInfo(new PhysicalDescriptionTriangleMesh(0, 0, 0,
	//																			"Worlds/Lba1Original/Grids/map0.phy",
	//																			true));
	//ObjectInfo objinfo(1, DInfo, PInfo,	true);
	//boost::shared_ptr<DynamicObject> ground = objinfo.BuildSelf(OsgHandler::getInstance());

	//m_lbaNetModel->AddObject(1, objinfo);

	//SwitchGuiToGame();

	// done in order to solve bug at startup with GUI mouse
	int resX, resY;
	bool fullscreen;
	OsgHandler::getInstance()->GetScreenAttributes(resX, resY, fullscreen);
	OsgHandler::getInstance()->Resize(resX+1, resY+1, fullscreen);
	OsgHandler::getInstance()->Resize(resX, resY, fullscreen);


#ifdef _USE_QT_EDITOR_
	m_editor_handler->RefreshDisplay();
	TryLogin("Editor", "", true);
	SwitchGuiToGame();
#endif


	try
	{
		// init time
		long waittime = SynchronizedTimeHandler::GetCurrentTimeInt();
		double timetodiff = SynchronizedTimeHandler::GetCurrentTimeDouble();
		float tdiff = TIME_PER_FRAME;

		// Loop until a quit event is found
		while(!m_shouldexit && !OsgHandler::getInstance()->Update())
		{
			//get physic results
			PhysXEngine::getInstance()->GetPhysicsResults();

#ifdef _USE_QT_EDITOR_
			// process Qt events - this handles both events and paints the browser image
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
#endif

			// process stuff between frame
			Process(timetodiff, tdiff);


			// pause the program for a few milliseconds
			long currwtime = SynchronizedTimeHandler::GetCurrentTimeInt();
			long wdiff = (currwtime-waittime);
			if(wdiff < TIME_PER_FRAME)
				IceUtil::ThreadControl::sleep(IceUtil::Time::milliSeconds(TIME_PER_FRAME-wdiff));


			// mesure the time used to do one cycle
			waittime = SynchronizedTimeHandler::GetCurrentTimeInt();
			double tdouble = SynchronizedTimeHandler::GetCurrentTimeDouble();
			tdiff = (float)(tdouble-timetodiff);
			timetodiff = tdouble;

			//start physic calculation
			PhysXEngine::getInstance()->StartPhysics(tdiff);
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
void LbaNetEngine::Process(double tnow, float tdiff)
{
	//handle game events
	HandleGameEvents();

	// process model (update display stuff)
	m_lbaNetModel->Process(tnow, tdiff);

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
	LbaNet::EventsSeq::const_iterator it = events.begin();
	LbaNet::EventsSeq::const_iterator end = events.end();
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
			continue;
		}

		
		
		// server send list of available worlds to client
		if(info == typeid(LbaNet::AvailableWorldsEvent))
		{
			LbaNet::AvailableWorldsEvent * castedptr = 
				dynamic_cast<LbaNet::AvailableWorldsEvent *>(&obj);

			m_gui_handler->SetWorldList(castedptr->Worlds);
			continue;
		}
		
		
		
		// server ask client to refresh a certain GUI in game
		if(info == typeid(LbaNet::RefreshGameGUIEvent))
		{
			LbaNet::RefreshGameGUIEvent * castedptr = 
				dynamic_cast<LbaNet::RefreshGameGUIEvent *>(&obj);

			m_gui_handler->RefreshGameGUI(castedptr->GUIId, castedptr->Parameters, 
											castedptr->Show, castedptr->Hide);
			continue;
		}
		

		// client/server update something in part of the GUI
		if(info == typeid(LbaNet::UpdateGameGUIEvent))
		{
			LbaNet::UpdateGameGUIEvent * castedptr = 
				dynamic_cast<LbaNet::UpdateGameGUIEvent *>(&obj);

			m_gui_handler->UpdateGameGUI(castedptr->GUIId, castedptr->Updates);
			continue;
		}


		// LoginEvent
		if(info == typeid(LoginEvent))
		{
			LoginEvent * castedptr = 
				dynamic_cast<LoginEvent *>(&obj);

			TryLogin(castedptr->_Name, castedptr->_Password, castedptr->_Local);
			continue;
		}


		// GuiExitEvent
		if(info == typeid(GuiExitEvent))
		{
			ExitGui();
			continue;
		}

		// QuitGameEvent
		if(info == typeid(QuitGameEvent))
		{
			m_shouldexit = true;
			continue;
		}


		// ChangeWorldEvent
		if(info == typeid(ChangeWorldEvent))
		{
			ChangeWorldEvent * castedptr = 
				dynamic_cast<ChangeWorldEvent *>(&obj);

			// update 
			ChangeWorld(castedptr->_NewWorldName);
			continue;
		}


		// FocusChatEvent
		if(info == typeid(FocusChatEvent))
		{
			FocusChatEvent * castedptr = 
				dynamic_cast<FocusChatEvent *>(&obj);

			m_gui_handler->FocusGameGUI("ChatBox", castedptr->_focus);
			continue;
		}


		// WhisperChannelEvent
		if(info == typeid(DisplayGUIEvent))
		{
			DisplayGUIEvent * castedptr = 
				dynamic_cast<DisplayGUIEvent *>(&obj);

			DisplayGUI(castedptr->_GuiNumber);
			continue;
		}


		// NewFontSizeEvent
		if(info == typeid(NewFontSizeEvent))
		{
			m_gui_handler->ReloadFontSize();
			continue;
		}


		// PlayerNameColorChangedEvent
		if(info == typeid(PlayerNameColorChangedEvent))
		{
			PlayerNameColorChangedEvent * castedptr = 
				dynamic_cast<PlayerNameColorChangedEvent *>(&obj);

			// inform server
			if(m_chatH)
				m_chatH->ChangeNameColor(castedptr->_color);

			continue;
		}


		// SendChatTextEvent
		if(info == typeid(SendChatTextEvent))
		{
			SendChatTextEvent * castedptr = 
				dynamic_cast<SendChatTextEvent *>(&obj);

			// inform server
			if(m_chatH)
				m_chatH->SendChatText(castedptr->_text);

			continue;
		}


		// PlayerStatusUpdateEvent
		if(info == typeid(PlayerStatusUpdateEvent))
		{
			PlayerStatusUpdateEvent * castedptr = 
				dynamic_cast<PlayerStatusUpdateEvent *>(&obj);

			// update chat
			{
				LbaNet::GuiUpdatesSeq updseq;
				LbaNet::NameColorChangedUpdate * upd = 
					new LbaNet::NameColorChangedUpdate(castedptr->_name, castedptr->_color);
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

			continue;
		}


		// NewMapEvent
		if(info == typeid(LbaNet::NewMapEvent))
		{
			LbaNet::NewMapEvent * castedptr = 
				dynamic_cast<LbaNet::NewMapEvent *>(&obj);

			#ifdef _USE_QT_EDITOR_
			m_editor_handler->SetMapInfo(castedptr->MapName);
			#endif

			// update model
			m_lbaNetModel->NewMap(castedptr->MapName, castedptr->InitializationScript, 
																castedptr->AutoCameraType);

			//set chat map name
			LbaNet::GuiUpdatesSeq upd;
			upd.push_back(new ChatMapNameUpdate(castedptr->MapName));
			m_gui_handler->UpdateGameGUI("ChatBox", upd);

			// update music
			if(castedptr->MusicPath != "")
				MusicHandler::getInstance()->PlayMusic("Data/"+castedptr->MusicPath, castedptr->RepeatMusic);


			continue;
		}


		// AddObjectEvent
		if(info == typeid(LbaNet::AddObjectEvent))
		{
			LbaNet::AddObjectEvent * castedptr = 
				dynamic_cast<LbaNet::AddObjectEvent *>(&obj);

			m_lbaNetModel->AddObject(castedptr->TypeO, castedptr->ObjectId, 
									castedptr->DisplayDesc, castedptr->PhysicDesc,
									castedptr->ExtraInfo, castedptr->LifeInfo);

			continue;
		}

		// RemoveObjectEvent
		if(info == typeid(LbaNet::RemoveObjectEvent))
		{
			LbaNet::RemoveObjectEvent * castedptr = 
				dynamic_cast<LbaNet::RemoveObjectEvent *>(&obj);

			m_lbaNetModel->RemoveObject(castedptr->TypeO, castedptr->ObjectId);

			continue;
		}

		// UpdateObjectDisplayEvent
		if(info == typeid(LbaNet::UpdateDisplayObjectEvent))
		{
			LbaNet::UpdateDisplayObjectEvent * castedptr = 
				dynamic_cast<LbaNet::UpdateDisplayObjectEvent *>(&obj);

			m_lbaNetModel->UpdateObjectDisplay(castedptr->TypeO, castedptr->ObjectId, castedptr->Update);

			continue;
		}


		// UpdatePhysicObjectEvent
		if(info == typeid(LbaNet::UpdatePhysicObjectEvent))
		{
			LbaNet::UpdatePhysicObjectEvent * castedptr = 
				dynamic_cast<LbaNet::UpdatePhysicObjectEvent *>(&obj);

			m_lbaNetModel->UpdateObjectPhysic(castedptr->TypeO, castedptr->ObjectId, castedptr->Update);

			continue;
		}

		// PlayerKeyPressedEvent
		if(info == typeid(PlayerKeyPressedEvent))
		{
			PlayerKeyPressedEvent* castedptr = 
				dynamic_cast<PlayerKeyPressedEvent *>(&obj);

			m_lbaNetModel->KeyPressed(castedptr->_keyid);

			continue;
		}

		// PlayerKeyReleasedEvent
		if(info == typeid(PlayerKeyReleasedEvent))
		{
			PlayerKeyReleasedEvent* castedptr = 
				dynamic_cast<PlayerKeyReleasedEvent *>(&obj);

			m_lbaNetModel->KeyReleased(castedptr->_keyid);

			continue;
		}

		// PlayerKeyReleasedEvent
		if(info == typeid(LbaNet::PlayerMovedEvent))
		{
			LbaNet::PlayerMovedEvent* castedptr = 
				dynamic_cast<LbaNet::PlayerMovedEvent *>(&obj);

			m_lbaNetModel->PlayerMovedUpdate(castedptr->PlayerId, castedptr->Time, 
												castedptr->info, castedptr->ServerTeleport);

			continue;
		}

		// NpcMovedEvent
		if(info == typeid(LbaNet::NpcChangedEvent))
		{
			LbaNet::NpcChangedEvent* castedptr = 
				dynamic_cast<LbaNet::NpcChangedEvent *>(&obj);

			m_lbaNetModel->NpcChangedUpdate(castedptr->NpcId, castedptr->Time, 
												castedptr->CurrPosX, castedptr->CurrPosY,
												castedptr->CurrPosZ, castedptr->CurrRotation,
												castedptr->CurrAnimation,
												castedptr->ResetPosition, castedptr->ResetRotation,
												castedptr->Update);

			continue;
		}


		// RefreshEndEvent
		if(info == typeid(LbaNet::RefreshEndEvent))
		{
			m_lbaNetModel->RefreshEnd();
			continue;
		}

		// UpdateGuiLifeEvent
		if(info == typeid(UpdateGuiLifeEvent))
		{
			UpdateGuiLifeEvent* castedptr = 
				dynamic_cast<UpdateGuiLifeEvent *>(&obj);

			if(m_gui_handler)
				m_gui_handler->UpdateLifeMana(castedptr->_lifepercent, castedptr->_manapercent);

			continue;
		}

		// CenterCameraEvent
		if(info == typeid(CenterCameraEvent))
		{
			m_lbaNetModel->CenterCamera();
			continue;
		}


		// StartClientScriptEvent
		if(info == typeid(LbaNet::StartClientScriptEvent))
		{
			LbaNet::StartClientScriptEvent* castedptr = 
				dynamic_cast<LbaNet::StartClientScriptEvent *>(&obj);


			if(m_lbaNetModel->StartScript(castedptr->ScriptName, castedptr->InlineFunction) < 0)
			{
				// send back to server if script failed
				EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ScriptExecutionFinishedEvent(
					SynchronizedTimeHandler::GetCurrentTimeDouble(), castedptr->ScriptName));
			}

			continue;
		}




		// EditorPlayerMovedEvent
		#ifdef _USE_QT_EDITOR_
		if(info == typeid(EditorPlayerMovedEvent))
		{
			EditorPlayerMovedEvent* castedptr = 
				dynamic_cast<EditorPlayerMovedEvent *>(&obj);

			m_editor_handler->PlayerMoved(castedptr->_posx, castedptr->_posy, castedptr->_posz);
			continue;
		}
		#endif


		// EditorPlayerMovedEvent
		#ifdef _USE_QT_EDITOR_
		if(info == typeid(EditorTeleportEvent))
		{
			EditorTeleportEvent* castedptr = 
				dynamic_cast<EditorTeleportEvent *>(&obj);

			m_lbaNetModel->EditorTpPlayer(castedptr->_posx, castedptr->_posy, castedptr->_posz);
			continue;
		}
		#endif
		

		// EditorCameraChangeEvent
		#ifdef _USE_QT_EDITOR_
		if(info == typeid(EditorCameraChangeEvent))
		{
			EditorCameraChangeEvent* castedptr = 
				dynamic_cast<EditorCameraChangeEvent *>(&obj);

			m_lbaNetModel->ForceGhost(castedptr->_forceghost);
			continue;
		}
		#endif


		// ObjectPickedEvent
		if(info == typeid(ObjectPickedEvent))
		{
			ObjectPickedEvent* castedptr = 
				dynamic_cast<ObjectPickedEvent *>(&obj);

			#ifdef _USE_QT_EDITOR_
			m_editor_handler->PickedObject(castedptr->_name);
			#endif

			continue;
		}
		

		// PickedArrowMovedEvent
		#ifdef _USE_QT_EDITOR_
		if(info == typeid(PickedArrowMovedEvent))
		{
			PickedArrowMovedEvent* castedptr = 
				dynamic_cast<PickedArrowMovedEvent *>(&obj);

			m_editor_handler->PickedArrowMoved(castedptr->_pickedarrow);
			continue;
		}
		#endif

		// ClientExecuteScriptStringEvent
		if(info == typeid(LbaNet::ClientExecuteScriptStringEvent))
		{
			LbaNet::ClientExecuteScriptStringEvent* castedptr = 
				dynamic_cast<LbaNet::ClientExecuteScriptStringEvent *>(&obj);

			m_lbaNetModel->ExecuteScriptString(castedptr->ScriptString);
			continue;
		}
		
		// RefreshLuaEvent
		if(info == typeid(RefreshLuaEvent))
		{
			m_lbaNetModel->RefreshLua();
			continue;
		}


		// SendSignalEvent
		if(info == typeid(LbaNet::SendSignalEvent))
		{
			LbaNet::SendSignalEvent* castedptr = 
				dynamic_cast<LbaNet::SendSignalEvent *>(&obj);

			if(m_lbaNetModel)
				m_lbaNetModel->SendSignalToActor(-1, castedptr->SignalId);

			continue;
		}
		

		// ShowHideEvent
		if(info == typeid(LbaNet::ShowHideEvent))
		{
			LbaNet::ShowHideEvent* castedptr = 
				dynamic_cast<LbaNet::ShowHideEvent *>(&obj);

			if(m_lbaNetModel)
				m_lbaNetModel->ShowHideActor(castedptr->TypeO, (long)castedptr->ObjectId, castedptr->Show);

			continue;
		}


		// InternalUpdateStateEvent
		if(info == typeid(InternalUpdateStateEvent))
		{
			InternalUpdateStateEvent* castedptr = 
				dynamic_cast<InternalUpdateStateEvent *>(&obj);

			if(m_lbaNetModel)
				m_lbaNetModel->UpdatePlayerState(castedptr->_NewState);

			continue;
		}

		// NpcTargetPlayerEvent
		if(info == typeid(LbaNet::NpcTargetPlayerEvent))
		{
			LbaNet::NpcTargetPlayerEvent* castedptr = 
				dynamic_cast<LbaNet::NpcTargetPlayerEvent *>(&obj);

			if(m_lbaNetModel)
				m_lbaNetModel->NpcTargetPlayer((long)castedptr->NpcId, (long)castedptr->PlayerId);

			continue;
		}

		// NpcUnTargetPlayerEvent
		if(info == typeid(LbaNet::NpcUnTargetPlayerEvent))
		{
			LbaNet::NpcUnTargetPlayerEvent* castedptr = 
				dynamic_cast<LbaNet::NpcUnTargetPlayerEvent *>(&obj);

			if(m_lbaNetModel)
				m_lbaNetModel->NpcUnTargetPlayer((long)castedptr->NpcId);

			continue;
		}

		// CutMapEvent
		if(info == typeid(LbaNet::CutMapEvent))
		{
			LbaNet::CutMapEvent* castedptr = 
				dynamic_cast<LbaNet::CutMapEvent *>(&obj);

			OsgHandler::getInstance()->SetClipPlane(castedptr->Y);

			continue;
		}

		// CreateProjectileEvent
		if(info == typeid(LbaNet::CreateProjectileEvent))
		{
			LbaNet::CreateProjectileEvent* castedptr = 
				dynamic_cast<LbaNet::CreateProjectileEvent *>(&obj);

			if(m_lbaNetModel)
				m_lbaNetModel->CreateProjectile(castedptr->Info);

			continue;
		}

		// DestroyProjectileEvent
		if(info == typeid(LbaNet::DestroyProjectileEvent))
		{
			LbaNet::DestroyProjectileEvent* castedptr = 
				dynamic_cast<LbaNet::DestroyProjectileEvent *>(&obj);

			if(m_lbaNetModel)
				m_lbaNetModel->DestroyProjectile((long)castedptr->Id);

			continue;
		}

		// GuiRefreshPlayerColorEvent
		if(info == typeid(GuiRefreshPlayerColorEvent))
		{
			GuiRefreshPlayerColorEvent* castedptr = 
				static_cast<GuiRefreshPlayerColorEvent *>(&obj);

			if(m_gui_handler)
				m_gui_handler->RefreshPlayerColor(castedptr->_skincolor, castedptr->_eyescolor, castedptr->_haircolor);

			continue;
		}

		// GuiRefreshPlayerColorEvent
		if(info == typeid(GuiRefreshPlayerColorEvent))
		{
			GuiRefreshPlayerColorEvent* castedptr = 
				static_cast<GuiRefreshPlayerColorEvent *>(&obj);

			if(m_gui_handler)
				m_gui_handler->RefreshPlayerColor(castedptr->_skincolor, castedptr->_eyescolor, castedptr->_haircolor);

			continue;
		}


		// DestroyProjectileEvent
		if(info == typeid(LbaNet::NpcAttachActorEvent))
		{
			LbaNet::NpcAttachActorEvent* castedptr = 
				dynamic_cast<LbaNet::NpcAttachActorEvent *>(&obj);

			if(m_lbaNetModel)
				m_lbaNetModel->NpcAttachActor((long)castedptr->NpcId, castedptr->AttachedType, (long)castedptr->AttachedId);

			continue;
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

	if(m_gui_handler)
		m_gui_handler->SetDrawOverlay(false);
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


	// ask server for the list of worlds
	if(m_serverConH)
		m_serverConH->RefreshWorldList();

	if(m_gui_handler)
		m_gui_handler->SetDrawOverlay(false);
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

	m_lbaNetModel->Resume();
	m_gui_handler->SwitchGUI(2);
	m_gui_handler->RefreshOption();

	m_oldstate = m_currentstate;
	m_currentstate = EGaming;

	if(m_gui_handler)
		m_gui_handler->SetDrawOverlay(true);
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

	if(m_gui_handler)
		m_gui_handler->SetDrawOverlay(false);
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

	if(m_gui_handler)
		m_gui_handler->SetDrawOverlay(false);
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

	LbaNet::GuiUpdatesSeq seq;
	seq.push_back(new SetPlayerNameUpdate(Name));
	m_gui_handler->UpdateGameGUI("main", seq);

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

	// update options
	m_gui_handler->SetWorldName(NewWorld);


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
	std::string mmusic = "Data/Worlds/Lba1Original/Music/LBA1-Track9.mp3";

	std::string tmp = MusicHandler::getInstance()->GetCurrentMusic();
	if(tmp != mmusic)
	{
		m_lastmusic = tmp;
		MusicHandler::getInstance()->PlayMusic(mmusic, -1);
	}
}

