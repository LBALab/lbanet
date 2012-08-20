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

#include "GUI.h"
#include "GuiHandler.h"
#include "LoginGUI.h"
#include "LogHandler.h"
#include "ChooseWorldGUI.h"
#include "GameGUI.h"
#include "MenuGUI.h"
#include "MenuGUI.h"
#include "OptionsGUI.h"
#include "ConfigurationManager.h"
#include "SynchronizedTimeHandler.h"
#include "StringMorphInterpolator.h"

#include "DataDirHandler.h"

#include <CEGUI.h>
#include <RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
#include <CEGUIDefaultResourceProvider.h>
#include <CEGUIAnimation.h>




/***********************************************************
	Constructor
***********************************************************/
GuiHandler::GuiHandler()
: _currentGUI(-1), _gui_renderer(NULL), _game_gui(NULL), 
	_login_gui(NULL)
{

}


/***********************************************************
	Destructor
***********************************************************/
GuiHandler::~GuiHandler()
{
	std::vector<GUI *>::iterator it = _guis.begin();
	std::vector<GUI *>::iterator end = _guis.end();
	for(; it != end; ++it)
		delete *it;

    CEGUI::System::destroy();
    CEGUI::OpenGLRenderer::destroy(*_gui_renderer);
}


/***********************************************************
initialize function
***********************************************************/
void GuiHandler::Initialize(int screen_size_X, int screen_size_Y)
{
	try
	{
		_gui_renderer =  &CEGUI::OpenGLRenderer::create();
		_gui_renderer->enableExtraStateSettings(true);


		CEGUI::System::create( *_gui_renderer, 0, 0, 0, 0, "", LogHandler::getInstance()->GetGUIFilename().c_str() );

		// initialise the required dirs for the DefaultResourceProvider
		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
			(CEGUI::System::getSingleton().getResourceProvider());

		rp->setResourceGroupDirectory("schemes", DataDirHandler::getInstance()->GetDataDirPath() + "/GUI/schemes/");
		rp->setResourceGroupDirectory("imagesets", DataDirHandler::getInstance()->GetDataDirPath() + "/GUI/imagesets/");
		rp->setResourceGroupDirectory("fonts", DataDirHandler::getInstance()->GetDataDirPath() + "/GUI/fonts/");
		rp->setResourceGroupDirectory("layouts", DataDirHandler::getInstance()->GetDataDirPath() + "/GUI/layouts/");
		rp->setResourceGroupDirectory("looknfeels", DataDirHandler::getInstance()->GetDataDirPath() + "/GUI/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", DataDirHandler::getInstance()->GetDataDirPath() + "/GUI/lua_scripts/");

		// set the default resource groups to be used
		CEGUI::Imageset::setDefaultResourceGroup("imagesets");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");



		// load in the scheme file, which auto-loads the TaharezLook imageset
		CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );

		//! load font file
		CEGUI::FontManager::getSingleton().create( "abbey_m1-9.font" );


		ReloadFontSize();

		CEGUI::System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" );
		CEGUI::System::getSingleton().setDefaultTooltip( "TaharezLook/Tooltip" );

		// Load the Imageset that has the pictures for our button.
		CEGUI::ImagesetManager::getSingleton().create( "LogoBig.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "LogoCenter.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "lbaNetB.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "chatbutton.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "TeleportButton.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "HeadInterface.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "optionsbutton.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "soundbutton.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "changeworldbutton.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "quitbutton.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "MenuChar.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "tunic.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "quest.imageset" );
		CEGUI::ImagesetManager::getSingleton().create( "weapon.imageset" );

		CEGUI::ImagesetManager::getSingleton().create( "halo2.imageset" );



		CEGUI::ImagesetManager::getSingleton().create( "contourfont.imageset" );
		CEGUI::FontManager::getSingleton().create( "ContourFont.font" );

		// loading the smileys
		{
			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_biggrin", "smileys/biggrin.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_bloated", "smileys/bloated.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_confused", "smileys/confused.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_cool", "smileys/cool.png");
			ims.setAutoScalingEnabled(false);
			}
			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_dinofly", "smileys/dinofly.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_eek", "smileys/eek.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_embarrassment", "smileys/embarrassment.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_evil", "smileys/evil.png");
			ims.setAutoScalingEnabled(false);
			}
			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_evilwink", "smileys/evilwink.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_frown", "smileys/frown.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_funfrock", "smileys/funfrock.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_hmpf", "smileys/hmpf.png");
			ims.setAutoScalingEnabled(false);
			}
			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_hmz", "smileys/hmz.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_kiss", "smileys/kiss.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_lol", "smileys/lol.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_mad", "smileys/mad.png");
			ims.setAutoScalingEnabled(false);
			}
			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_proud", "smileys/proud.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_rabibunny", "smileys/rabibunny.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_rolleyes", "smileys/rolleyes.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_sad", "smileys/sad.png");
			ims.setAutoScalingEnabled(false);
			}
			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_sigh", "smileys/sigh.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_smilie", "smileys/smilie.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_stupid", "smileys/stupid.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_tdown", "smileys/tdown.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_tup", "smileys/tup.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_wink", "smileys/wink.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_zoe", "smileys/zoe.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_zombie", "smileys/zombie.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("sm_tongue", "smileys/tongue.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("mailb_new", "new_im.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("mailb_notnew", "nonew_im.png");
			ims.setAutoScalingEnabled(false);
			}

			{
			CEGUI::Imageset &ims = CEGUI::ImagesetManager::getSingleton().createFromImageFile("mailb_trash", "trash.png");
			ims.setAutoScalingEnabled(false);
			}	
		}
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init gui: ") + ex.getMessage().c_str());
	}



	// add interpolator
	CEGUI::AnimationManager::getSingleton().addInterpolator(new CEGUI::StringMorphInterpolator);

	//initialize the login gui
	_login_gui = new LoginGUI();
	_login_gui->Initialize();

	_guis.push_back(_login_gui);

	//initialize the choose world gui
	_chooseworld_gui = new ChooseWorldGUI();
	_chooseworld_gui->Initialize();
	_guis.push_back(_chooseworld_gui);

	//initialize the game gui
	_game_gui = new GameGUI();
	_game_gui->Initialize();
	_guis.push_back(_game_gui);

	//initialize the menu gui
	MenuGUI * menuG = new MenuGUI();
	menuG->Initialize();
	_guis.push_back(menuG);

	//initialize the option gui
	_option_gui = new OptionsGUI();
	_option_gui->Initialize();
	_guis.push_back(_option_gui);


	SwitchGUI(0);


    // clearing this queue actually makes sure it's created(!)
    //_gui_renderer->getDefaultRenderingRoot().clearGeometry(CEGUI::RQ_OVERLAY);

    // subscribe handler to render overlay items
    //_gui_renderer->getDefaultRenderingRoot().
    //    subscribeEvent(CEGUI::RenderingSurface::EventRenderQueueStarted,
    //        CEGUI::Event::Subscriber(&GuiHandler::overlayHandler, this));
}



/***********************************************************
set the list of available worlds
***********************************************************/
void GuiHandler::SetWorldList(const std::vector<LbaNet::WorldDesc> &list)
{
	_chooseworld_gui->SetWorldList(list);
}



/***********************************************************
inject time to the GUI
***********************************************************/
void GuiHandler::inject_time_pulse()
{
	/* get current "run-time" in seconds */
	double t = 0.001*SynchronizedTimeHandler::GetCurrentTimeDouble();
	/* inject the time that passed since the last call */
	CEGUI::System::getSingleton().injectTimePulse( float(t-m_last_time_pulse) );
	/* store the new time as the last time */
	m_last_time_pulse = t;
}


/***********************************************************
process function
***********************************************************/
void GuiHandler::Process(void)
{
   inject_time_pulse();
}


/***********************************************************
switch from current gui to another one
***********************************************************/
void GuiHandler::SwitchGUI(int GuiNumber)
{
	if(GuiNumber == _currentGUI)
	   return;

	try
	{
		CEGUI::Window * root = _guis[GuiNumber]->GetRoot();
		if(root)
		{
			CEGUI::System::getSingleton().setGUISheet( root );
			_guis[GuiNumber]->Displayed();
		}
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception changing gui: ") + ex.getMessage().c_str());
	}

	_currentGUI = GuiNumber;
}




/***********************************************************
called when the windows is resized
***********************************************************/
void GuiHandler::Resize(int screen_size_X, int screen_size_Y, int oldscreenX, int oldscreenY)
{
	if(oldscreenX > 1 && oldscreenY > 1)
	{
		if(_game_gui)
			_game_gui->SaveGUISizes(oldscreenX, oldscreenY);
	}

    CEGUI::System::getSingleton().
        notifyDisplaySizeChanged(CEGUI::Size((float)screen_size_X,(float)screen_size_Y));


	if(oldscreenX > 0 && oldscreenY > 0)
	{
		if(_game_gui)
			_game_gui->RestoreGUISizes();
	}

	_currentX = screen_size_X;
	_currentY = screen_size_Y;
}



/***********************************************************
called when font size changed
***********************************************************/
void GuiHandler::ReloadFontSize()
{
	// load in a font.  The first font loaded automatically becomes the default font.
	int fontsize = ConfigurationManager::GetInstance()->GetValue("Options.Gui.FontSize", 10);
	std::stringstream strs;
	strs<<"DejaVuSans-"<<fontsize;
	std::string fontfile = strs.str() + ".font";

	//if(!CEGUI::FontManager::getSingleton().isFontPresent( strs.str() ) )
	CEGUI::FontManager::getSingleton().create( (const unsigned char *)fontfile.c_str() );
	CEGUI::System::getSingleton().setDefaultFont( (const unsigned char *)strs.str().c_str() );

	int smallfontsize = (fontsize-2);
	if(smallfontsize < 3)
		smallfontsize = 3;

	std::stringstream strs2;
	strs2<<"DejaVuSans-"<<smallfontsize;
	std::string fontfile2 = strs2.str() + ".font";
	CEGUI::FontManager::getSingleton().create( (const unsigned char *)fontfile2.c_str() );

	ConfigurationManager::GetInstance()->SetSmallFontName(strs2.str());
}



/***********************************************************
inform the user the login failed
***********************************************************/
void GuiHandler::InformNotLoggedIn(int problem, const std::string & reason)
{
	if(_login_gui)
		_login_gui->InformNotLoggedIn(problem, reason);
}




/***********************************************************
handle overlay
***********************************************************/
bool GuiHandler::overlayHandler(const CEGUI::EventArgs& args)
{
    if (static_cast<const CEGUI::RenderQueueEventArgs&>(args).queueID != CEGUI::RQ_OVERLAY)
        return false;

	//_engine->DrawOverlay();

	return true;
}


/***********************************************************
display inventory
***********************************************************/
void GuiHandler::RefreshOption()
{
	if(_option_gui)
		_option_gui->SendNameColor();
}



/***********************************************************
set the client version text
***********************************************************/
void GuiHandler::SetClientVersion(const std::string &clientversion)
{
	if(_login_gui)
		_login_gui->SetClientVersion(clientversion);
}

/***********************************************************
set if the server is on or not
***********************************************************/
void GuiHandler::SetServrOn(bool ServerOn)
{
	if(_login_gui)
		_login_gui->SetServrOn(ServerOn);
}


/***********************************************************
refresh gui with info from server
***********************************************************/
void GuiHandler::RefreshGameGUI(const std::string & guiid, const LbaNet::GuiParamsSeq &Parameters, 
									bool Show, bool Hide)
{
	if(_game_gui)
		_game_gui->RefreshGUI(guiid, Parameters, Show, Hide);
}

/***********************************************************
update gui with info from server
***********************************************************/
void GuiHandler::UpdateGameGUI(const std::string & guiid,const LbaNet::GuiUpdatesSeq &Updates)
{
	if(_game_gui)
		_game_gui->UpdateGUI(guiid, Updates);
}

/***********************************************************
show GUI
***********************************************************/
void GuiHandler::ShowGameGUI(const std::string & guiid)
{
	if(_game_gui)
		_game_gui->ShowGUI(guiid);
}

/***********************************************************
hide GUI
***********************************************************/
void GuiHandler::HideGameGUI(const std::string & guiid)
{
	if(_game_gui)
		_game_gui->HideGUI(guiid);
}

/***********************************************************
show/hide GUI
***********************************************************/
void GuiHandler::ToggleDisplayGameGUI(const std::string & guiid)
{
	if(_game_gui)
		_game_gui->ToggleDisplayGUI(guiid);
}

/***********************************************************
focus GUI
***********************************************************/
void GuiHandler::FocusGameGUI(const std::string & guiid, bool focus)
{
	if(_game_gui)
		_game_gui->FocusGUI(guiid, focus);
}

/***********************************************************
activate or not the overlay
***********************************************************/
void GuiHandler::SetDrawOverlay(bool draw)
{
	_drawoverlay = draw;
}


/***********************************************************
get gui windows size
***********************************************************/
void GuiHandler::GetScreenSize(int &X, int &Y)
{
	X = _currentX;
	Y = _currentY;
}


/***********************************************************
update life mana info
***********************************************************/
void GuiHandler::UpdateLifeMana(float lifePerc, float ManaPerc)
{
	_lifepercent = lifePerc;
	_manapercent = ManaPerc;
}

/***********************************************************
update life mana info
***********************************************************/
void GuiHandler::GetLifeManaInfo(float &lifePerc, float &ManaPerc)
{
	lifePerc = _lifepercent;
	ManaPerc = _manapercent;
}

/***********************************************************
set world name
***********************************************************/
void GuiHandler::SetWorldName(const std::string &name)
{
	if(_option_gui)
		_option_gui->SetWorldName(name);
}


/***********************************************************
refresh player color
***********************************************************/
void GuiHandler::RefreshPlayerColor(int skin, int eyes, int hair)
{
	if(_option_gui)
		_option_gui->RefreshPlayerColor(skin, eyes, hair);
}

