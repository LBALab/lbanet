/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This application is open source and may be redistributed and/or modified   
 * freely and without restriction, both in commericial and non commericial applications,
 * as long as this copyright notice is maintained.
 * 
 * This application is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osgUtil/Optimizer>
#include <osgViewer/Viewer>
#include <osg/CoordinateSystemNode>
#include <osg/MatrixTransform>
#include <osgGA/GUIEventAdapter>
#include <osgDB/FileUtils>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osg/CullFace>


#include <CEGUI.h>
#include <RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
#include <CEGUIScriptModule.h>
#include <CEGUIFontManager.h>
#include <CEGUISchemeManager.h>
#include <CEGUIWindowManager.h>
#include <CEGUIExceptions.h>

#include <iostream>
#include <time.h>

#include "CEGUIDrawable.h"

   //         KEY_Meta_L          = 0xFFE7,        /* Left meta */
   //         KEY_Meta_R          = 0xFFE8,        /* Right meta */
   //         KEY_Hyper_L         = 0xFFED,        /* Left hyper */
   //         KEY_Hyper_R         = 0xFFEE         /* Right hyper */         

   //         KEY_Linefeed        = 0xFF0A,        /* Linefeed, LF */
   //         KEY_Clear           = 0xFF0B,
   //         KEY_Prior           = 0xFF55,        /* Prior, previous */
   //         KEY_Next            = 0xFF56,        /* Next */
   //         KEY_Begin           = 0xFF58,        /* BOL */
   //         KEY_Select          = 0xFF60,        /* Select, mark */
   //         KEY_Print           = 0xFF61,
   //         KEY_Execute         = 0xFF62,        /* Execute, run, do */
   //         KEY_Undo            = 0xFF65,        /* Undo, oops */
   //         KEY_Redo            = 0xFF66,        /* redo, again */
   //         KEY_Find            = 0xFF68,        /* Find, search */
   //         KEY_Cancel          = 0xFF69,        /* Cancel, stop, abort, exit */
   //         KEY_Help            = 0xFF6A,        /* Help */
   //         KEY_Break           = 0xFF6B,
   //         KEY_Mode_switch     = 0xFF7E,        /* Character set switch */
   //         KEY_Script_switch   = 0xFF7E,        /* Alias for mode_switch */
   //         KEY_Shift_Lock      = 0xFFE6,        /* Shift lock */

			//case KEY_KP_Space:       = 0xFF80,        /* space */
			//case KEY_KP_Tab:          = 0xFF89,
			//case KEY_KP_F1:           = 0xFF91,        /* PF1, KP_A, ... */
			//case KEY_KP_F2:          = 0xFF92,
			//case KEY_KP_F3:           = 0xFF93,
			//case KEY_KP_F4:           = 0xFF94,
			//case KEY_KP_Home:         = 0xFF95,
			//case KEY_KP_Left:         = 0xFF96,
			//case KEY_KP_Up:           = 0xFF97,
			//case KEY_KP_Right:        = 0xFF98,
			//case KEY_KP_Down:         = 0xFF99,
			//case KEY_KP_Prior:        = 0xFF9A,
			//case KEY_KP_Page_Up:      = 0xFF9A,
			//case KEY_KP_Next:         = 0xFF9B,
			//case KEY_KP_Page_Down:    = 0xFF9B,
			//case KEY_KP_End:          = 0xFF9C,
			//case KEY_KP_Begin:        = 0xFF9D,
			//case KEY_KP_Insert:       = 0xFF9E,
			//case KEY_KP_Delete:       = 0xFF9F,
			//case KEY_KP_Decimal:      = 0xFFAE,



////////////////////////////////////////////////////////////////////////////////
// CEGUI::uint OSGKeyToCEGUIKey(int key)
//{
//   switch(key)
//   {
//      case osgGA::GUIEventAdapter::KEY_Escape:
//      {
//         return CEGUI::Key::Escape;
//      }
//      case osgGA::GUIEventAdapter::KEY_F1:
//      {
//         return CEGUI::Key::F1;
//      }
//      case osgGA::GUIEventAdapter::KEY_F2:
//      {
//         return CEGUI::Key::F2;
//      }
//      case osgGA::GUIEventAdapter::KEY_F3:
//      {
//         return CEGUI::Key::F3;
//      }
//      case osgGA::GUIEventAdapter::KEY_F4:
//      {
//         return CEGUI::Key::F4;
//      }
//      case osgGA::GUIEventAdapter::KEY_F5:
//      {
//         return CEGUI::Key::F5;
//      }
//      case osgGA::GUIEventAdapter::KEY_F6:
//      {
//         return CEGUI::Key::F6;
//      }
//      case osgGA::GUIEventAdapter::KEY_F7:
//      {
//         return CEGUI::Key::F7;
//      }
//      case osgGA::GUIEventAdapter::KEY_F8:
//      {
//         return CEGUI::Key::F8;
//      }
//      case osgGA::GUIEventAdapter::KEY_F9:
//      {
//         return CEGUI::Key::F9;
//      }
//      case osgGA::GUIEventAdapter::KEY_F10:
//      {
//         return CEGUI::Key::F10;
//      }
//      case osgGA::GUIEventAdapter::KEY_F11:
//      {
//         return CEGUI::Key::F11;
//      }
//      case osgGA::GUIEventAdapter::KEY_F12:
//      {
//         return CEGUI::Key::F12;
//      }
//      case osgGA::GUIEventAdapter::KEY_F13:
//      {
//         return CEGUI::Key::F13;
//      }
//      case osgGA::GUIEventAdapter::KEY_F14:
//      {
//         return CEGUI::Key::F14;
//      }
//      case osgGA::GUIEventAdapter::KEY_F15:
//      {
//         return CEGUI::Key::F15;
//      }
//      case '`':
//      {
//         return CEGUI::Key::Apostrophe;
//      }
//      case '1':
//      {
//         return CEGUI::Key::One;
//      }
//      case '2':
//      {
//         return CEGUI::Key::Two;
//      }
//      case '3':
//      {
//         return CEGUI::Key::Three;
//      }
//      case '4':
//      {
//         return CEGUI::Key::Four;
//      }
//      case '5':
//      {
//         return CEGUI::Key::Five;
//      }
//      case '6':
//      {
//         return CEGUI::Key::Six;
//      }
//      case '7':
//      {
//         return CEGUI::Key::Seven;
//      }
//      case '8':
//      {
//         return CEGUI::Key::Eight;
//      }
//      case '9':
//      {
//         return CEGUI::Key::Nine;
//      }
//      case '0':
//      {
//         return CEGUI::Key::Zero;
//      }
//      case '-':
//      {
//         return CEGUI::Key::Minus;
//      }
//      case '=':
//      {
//         return CEGUI::Key::Equals;
//      }
//      case osgGA::GUIEventAdapter::KEY_BackSpace:
//      {
//         return CEGUI::Key::Backspace;
//      }
//      case osgGA::GUIEventAdapter::KEY_Tab:
//      {
//         return CEGUI::Key::Tab;
//      }
//      case 'A':
//      {
//         return CEGUI::Key::A;
//      }
//      case 'B':
//      {
//         return CEGUI::Key::B;
//      }
//      case 'C':
//      {
//         return CEGUI::Key::C;
//      }
//      case 'D':
//      {
//         return CEGUI::Key::D;
//      }
//      case 'E':
//      {
//         return CEGUI::Key::E;
//      }
//      case 'F':
//      {
//         return CEGUI::Key::F;
//      }
//      case 'G':
//      {
//         return CEGUI::Key::G;
//      }
//      case 'H':
//      {
//         return CEGUI::Key::H;
//      }
//      case 'I':
//      {
//         return CEGUI::Key::I;
//      }
//      case 'J':
//      {
//         return CEGUI::Key::J;
//      }
//      case 'K':
//      {
//         return CEGUI::Key::K;
//      }
//      case 'L':
//      {
//         return CEGUI::Key::L;
//      }
//      case 'M':
//      {
//         return CEGUI::Key::M;
//      }
//      case 'N':
//      {
//         return CEGUI::Key::N;
//      }
//      case 'O':
//      {
//         return CEGUI::Key::O;
//      }
//      case 'P':
//      {
//         return CEGUI::Key::P;
//      }
//      case 'Q':
//      {
//         return CEGUI::Key::Q;
//      }
//      case 'R':
//      {
//         return CEGUI::Key::R;
//      }
//      case 'S':
//      {
//         return CEGUI::Key::S;
//      }
//      case 'T':
//      {
//         return CEGUI::Key::T;
//      }
//      case 'U':
//      {
//         return CEGUI::Key::U;
//      }
//      case 'V':
//      {
//         return CEGUI::Key::V;
//      }
//      case 'W':
//      {
//         return CEGUI::Key::W;
//      }
//      case 'X':
//      {
//         return CEGUI::Key::X;
//      }
//      case 'Y':
//      {
//         return CEGUI::Key::Y;
//      }
//      case 'Z':
//      {
//         return CEGUI::Key::Z;
//      }
//      case '(':
//      {
//         return CEGUI::Key::LeftBracket;
//      }
//      case ')':
//      {
//         return CEGUI::Key::RightBracket;
//      }
//      case '\\':
//      {
//         return CEGUI::Key::Backslash;
//      }
//      case osgGA::GUIEventAdapter::KEY_Shift_Lock:
//      {
//         return CEGUI::Key::Capital;
//      }
//      case ';':
//      {
//         return CEGUI::Key::Semicolon;
//      }
//      case '\'':
//      {
//         return CEGUI::Key::Apostrophe;
//      }
//      case osgGA::GUIEventAdapter::KEY_Return:
//      {
//         return CEGUI::Key::Return;
//      }
//      case osgGA::GUIEventAdapter::KEY_Shift_L:
//      {
//         return CEGUI::Key::LeftShift;
//      }
//      case ',':
//      {
//         return CEGUI::Key::Comma;
//      }
//      case '.':
//      {
//         return CEGUI::Key::Period;
//      }
//      case '/':
//      {
//         return CEGUI::Key::Slash;
//      }
//      case osgGA::GUIEventAdapter::KEY_Shift_R:
//      {
//         return CEGUI::Key::RightShift;
//      }
//      case osgGA::GUIEventAdapter::KEY_Control_L:
//      {
//         return CEGUI::Key::LeftControl;
//      }
//      case osgGA::GUIEventAdapter::KEY_Super_L:
//      {
//         return Key::LeftWindows;
//      }
//      case ' ':
//      {
//         return CEGUI::Key::Space;
//      }
//      case osgGA::GUIEventAdapter::KEY_Alt_L:
//      {
//         return CEGUI::Key::LeftAlt;
//      }
//      case osgGA::GUIEventAdapter::KEY_Alt_R:
//      {
//         return CEGUI::Key::RightAlt;
//      }
//      case osgGA::GUIEventAdapter::KEY_Super_R:
//      {
//         return Key::RightWindows;
//      }
//      case osgGA::GUIEventAdapter::KEY_Menu:
//      {
//         return CEGUI::Key::Scan(0);//?
//      }
//      case osgGA::GUIEventAdapter::KEY_Control_R:
//      {
//         return CEGUI::Key::RightControl;
//      }
//      case osgGA::GUIEventAdapter::KEY_Print:
//      {
//         return CEGUI::Key::SysRq;
//      }
//      case osgGA::GUIEventAdapter::KEY_Scroll_Lock:
//      {
//         return CEGUI::Key::ScrollLock;
//      }
//      case osgGA::GUIEventAdapter::KEY_Pause:
//      {
//         return CEGUI::Key::Pause;
//      }
//      case osgGA::GUIEventAdapter::KEY_Home:
//      {
//         return CEGUI::Key::Home;
//      }
//      case osgGA::GUIEventAdapter::KEY_Page_Up:
//      {
//         return CEGUI::Key::PageUp;
//      }
//      case osgGA::GUIEventAdapter::KEY_End:
//      {
//         return CEGUI::Key::End;
//      }
//      case osgGA::GUIEventAdapter::KEY_Page_Down:
//      {
//         return CEGUI::Key::PageDown;
//      }
//      case osgGA::GUIEventAdapter::KEY_Delete:
//      {
//         return CEGUI::Key::Delete;
//      }
//      case osgGA::GUIEventAdapter::KEY_Insert:
//      {
//         return CEGUI::Key::Insert;
//      }
//      case osgGA::GUIEventAdapter::KEY_Left:
//      {
//         return CEGUI::Key::ArrowLeft;
//      }
//      case osgGA::GUIEventAdapter::KEY_Up:
//      {
//         return CEGUI::Key::ArrowUp;
//      }
//      case osgGA::GUIEventAdapter::KEY_Right:
//      {
//         return CEGUI::Key::ArrowRight;
//      }
//      case osgGA::GUIEventAdapter::KEY_Down:
//      {
//         return CEGUI::Key::ArrowDown;
//      }
//      case osgGA::GUIEventAdapter::KEY_Num_Lock:
//      {
//         return CEGUI::Key::NumLock;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Divide:
//      {
//         return CEGUI::Key::Divide;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Multiply:
//      {
//         return CEGUI::Key::Multiply;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Subtract:
//      {
//         return CEGUI::Key::Subtract;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Add:
//      {
//         return CEGUI::Key::Add;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Home:
//      {
//         return CEGUI::Key::Numpad7;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Up:
//      {
//         return CEGUI::Key::Numpad8;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Page_Up:
//      {
//         return CEGUI::Key::Numpad9;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Left:
//      {
//         return CEGUI::Key::Numpad4;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Begin:
//      {
//         return CEGUI::Key::Scan(0); //?
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Right:
//      {
//         return CEGUI::Key::Numpad6;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_End:
//      {
//         return CEGUI::Key::Numpad1;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Down:
//      {
//         return CEGUI::Key::Numpad2;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Page_Down:
//      {
//         return CEGUI::Key::Numpad3;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Insert:
//      {
//         return CEGUI::Key::Numpad0;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Delete:
//      {
//         return CEGUI::Key::Decimal;
//      }
//      case osgGA::GUIEventAdapter::KEY_KP_Enter:
//      {
//         return CEGUI::Key::NumpadEnter;
//      }
//      default:
//      {
//         return CEGUI::Key::Scan(0);
//      }
//   }
//}








void Resize(osgViewer::Viewer * _viewer, bool _isFullscreen, int _resX, int _resY)
{
	// iterate over all windows
	osgViewer::Viewer::Windows windows;
    _viewer->getWindows(windows);
    for(osgViewer::Viewer::Windows::iterator itr = windows.begin();  itr != windows.end(); ++itr)
    {
		osgViewer::GraphicsWindow *window = *itr;

		osg::GraphicsContext::WindowingSystemInterface    *wsi = osg::GraphicsContext::getWindowingSystemInterface();
		if (wsi == NULL) 
		{
			//LogHandler::getInstance()->LogToFile("Error, no WindowSystemInterface available, cannot toggle window resolution change.");
			return;
		}

		unsigned int    screenWidth;
		unsigned int    screenHeight;
		int _viewportX, _viewportY;
		wsi->getScreenResolution(*(window->getTraits()), screenWidth, screenHeight);

		if(_isFullscreen)
		{
			window->setWindowDecoration(false);
			window->setWindowRectangle(0, 0, screenWidth, screenHeight);
			_viewportX = screenWidth;
			_viewportY = screenHeight;
			
		}
		else
		{
			window->setWindowDecoration(true);
			window->setWindowRectangle((screenWidth - _resX) / 2, (screenHeight - _resY) / 2, _resX, _resY);
			_viewportX = _resX;
			_viewportY = _resY;
		}

		_viewer->getCamera()->setViewport(0,0,_viewportX,_viewportY);
		window->raiseWindow();
		window->grabFocus();
		//window->grabFocusIfPointerInWindow();
    }
}


int main( int argc, char **argv )
{

    // use an ArgumentParser object to manage the program arguments.
    //osg::ArgumentParser arguments(&argc,argv);
    
	osgDB::setDataFilePathList("./Data");
    // construct the viewer.
    osgViewer::Viewer viewer;

    // create the window to draw to.
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->x = 100;
    traits->y = 100;
    traits->width = 800;
    traits->height = 600;
    traits->windowDecoration = true;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;
	traits->windowName = "Test";
	traits->useCursor = false;
    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
    osgViewer::GraphicsWindow* gw = dynamic_cast<osgViewer::GraphicsWindow*>(gc.get());
    if (!gw)
        return 0;


    viewer.getCamera()->setGraphicsContext(gc.get());
	viewer.getCamera()->setClearColor(osg::Vec4(0, 0, 0, 1));
    viewer.getCamera()->setViewport(0,0,800,600);

	viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	viewer.realize();
	viewer.getCamera()->getGraphicsContext()->makeCurrent(); 

	osg::ref_ptr<osg::Group> root=new osg::Group;
	osg::ref_ptr<osg::Group> scene= new osg::Group;
	osg::ref_ptr<osg::Group> gui=new osg::Group;
	osg::setNotifyLevel(osg::ALWAYS );

	osg::ref_ptr<osg::Geode> guiGeom=new osg::Geode;
	osg::ref_ptr<osg::Camera> HUDcam = new osg::Camera;

	HUDcam->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	HUDcam->setClearMask(0);
	HUDcam->setRenderOrder(osg::Camera::POST_RENDER, 100000);

	HUDcam->setAllowEventFocus(false);
	HUDcam->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::OVERRIDE | 
														osg::StateAttribute::OFF);
    HUDcam->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OVERRIDE |
														osg::StateAttribute::OFF);
    HUDcam->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    HUDcam->getOrCreateStateSet()->setRenderBinDetails(100,"RenderBin");
    HUDcam->getOrCreateStateSet()->setMode(GL_BLEND,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
    HUDcam->getOrCreateStateSet()->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::OVERRIDE|
																			osg::StateAttribute::ON);
    HUDcam->setProjectionMatrix(osg::Matrix::ortho2D(0,800,0,600));

	osg::CullFace *cull = new osg::CullFace();

	cull->setMode(osg::CullFace::BACK);
	HUDcam->getOrCreateStateSet()->setAttributeAndModes(cull, osg::StateAttribute::ON);

	scene->setName("3d_scene");
	root->setName("root");
	gui->setName("gui");

	HUDcam->addChild(gui.get());

	// load the scene.
	osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile("map0.osgb");
	//osgUtil::Optimizer optOSGFile;
	//optOSGFile.optimize (loadedModel.get(), osgUtil::Optimizer::ALL_OPTIMIZATIONS);
	//osgDB::writeNodeFile(*loadedModel.get(), "map0.osgb", new osgDB::Options("WriteImageHint=IncludeData Compressor=zlib"));

	scene->addChild(loadedModel.get());



	osg::ref_ptr<CEGUIDrawable> cd = new CEGUIDrawable();
	root->addChild(scene.get());
	root->addChild(HUDcam.get());

	guiGeom->addDrawable(cd.get());

	gui->addChild(guiGeom.get());

	viewer.setSceneData(root.get());


	 viewer.setCameraManipulator(new osgGA::TrackballManipulator);
	 osgViewer::StatsHandler *sth = new osgViewer::StatsHandler;
	 sth->setKeyEventTogglesOnScreenStats(osgGA::GUIEventAdapter::KEY_F11);
	 viewer.addEventHandler(sth);
	 osgViewer::WindowSizeHandler *wsh = new osgViewer::WindowSizeHandler;
	 wsh->setKeyEventToggleFullscreen(osgGA::GUIEventAdapter::KEY_F12);
	 viewer.addEventHandler(wsh);

	 viewer.setReleaseContextAtEndOfFrameHint(false);

	CEGUI::OpenGLRenderer *glRenderer=static_cast<CEGUI::OpenGLRenderer *>(CEGUI::System::getSingleton().getRenderer());
	glRenderer->grabTextures();
	CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Size((float)800,(float)600));
	glRenderer->restoreTextures(); 


	osg::Timer_t start_tick = osg::Timer::instance()->tick();

	Resize(&viewer, true, 800, 600);

    // run the viewer
	while (!viewer.done()) 
	{
		osg::Timer_t end_tick = osg::Timer::instance()->tick();

		/* inject the time that passed since the last call */
		CEGUI::System::getSingleton().injectTimePulse( float(osg::Timer::instance()->delta_s(start_tick,end_tick)) );
		/* store the new time as the last time */
		start_tick = end_tick;

		viewer.frame();
	}

    return 0;
}

