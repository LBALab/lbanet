#include "CEGUIDrawable.h"
#include "GuiHandler.h"


#include <CEGUI.h>
#include <RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
#include <CEGUIScriptModule.h>
#include <CEGUIFontManager.h>
#include <CEGUISchemeManager.h>
#include <CEGUIWindowManager.h>
#include <CEGUIExceptions.h>

#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>

#include <iostream>


 /************************************************************************
     Translate a OSGKey to the proper CEGUI::Key
 *************************************************************************/
 CEGUI::uint OSGKeyToCEGUIKey(int &key)
 {
     using namespace CEGUI;
     switch (key)
     {
	 case osgGA::GUIEventAdapter::KEY_BackSpace:    return Key::Backspace;
     case osgGA::GUIEventAdapter::KEY_Tab:          return Key::Tab;
     case osgGA::GUIEventAdapter::KEY_Return:       return Key::Return;
     case osgGA::GUIEventAdapter::KEY_Pause:        return Key::Pause;
     case osgGA::GUIEventAdapter::KEY_Escape:       return Key::Escape;
     case osgGA::GUIEventAdapter::KEY_Space:		 return Key::Space;
     //case SDLK_COMMA:        return Key::Comma;
     //case SDLK_MINUS:        return Key::Minus;
     //case SDLK_PERIOD:       return Key::Period;
     //case SDLK_SLASH:        return Key::Slash;
     //case SDLK_0:            return Key::Zero;
     //case SDLK_1:            return Key::One;
     //case SDLK_2:            return Key::Two;
     //case SDLK_3:            return Key::Three;
     //case SDLK_4:            return Key::Four;
     //case SDLK_5:            return Key::Five;
     //case SDLK_6:            return Key::Six;
     //case SDLK_7:            return Key::Seven;
     //case SDLK_8:            return Key::Eight;
     //case SDLK_9:            return Key::Nine;
     //case SDLK_COLON:        return Key::Colon;
     //case SDLK_SEMICOLON:    return Key::Semicolon;
     //case SDLK_EQUALS:       return Key::Equals;
     //case SDLK_LEFTBRACKET:  return Key::LeftBracket;
     //case SDLK_BACKSLASH:    return Key::Backslash;
     //case SDLK_RIGHTBRACKET: return Key::RightBracket;
     //case SDLK_a:            return Key::A;
     //case SDLK_b:            return Key::B;
     //case SDLK_c:            return Key::C;
     //case SDLK_d:            return Key::D;
     //case SDLK_e:            return Key::E;
     //case SDLK_f:            return Key::F;
     //case SDLK_g:            return Key::G;
     //case SDLK_h:            return Key::H;
     //case SDLK_i:            return Key::I;
     //case SDLK_j:            return Key::J;
     //case SDLK_k:            return Key::K;
     //case SDLK_l:            return Key::L;
     //case SDLK_m:            return Key::M;
     //case SDLK_n:            return Key::N;
     //case SDLK_o:            return Key::O;
     //case SDLK_p:            return Key::P;
     //case SDLK_q:            return Key::Q;
     //case SDLK_r:            return Key::R;
     //case SDLK_s:            return Key::S;
     //case SDLK_t:            return Key::T;
     //case SDLK_u:            return Key::U;
     //case SDLK_v:            return Key::V;
     //case SDLK_w:            return Key::W;
     //case SDLK_x:            return Key::X;
     //case SDLK_y:            return Key::Y;
     //case SDLK_z:            return Key::Z;
     case '*':            return Key::Multiply;
     case osgGA::GUIEventAdapter::KEY_Delete:       return Key::Delete;
     case osgGA::GUIEventAdapter::KEY_KP_0:  
      {
		  key = '0';
         return CEGUI::Key::Numpad0;
      }
     case osgGA::GUIEventAdapter::KEY_KP_1:
      {
		  key = '1';
         return CEGUI::Key::Numpad1;
      }
     case osgGA::GUIEventAdapter::KEY_KP_2:
      {
		  key = '2';
         return CEGUI::Key::Numpad2;
      }
     case osgGA::GUIEventAdapter::KEY_KP_3:
      {
		  key = '3';
         return CEGUI::Key::Numpad3;
      }
     case osgGA::GUIEventAdapter::KEY_KP_4:
      {
		  key = '4';
         return CEGUI::Key::Numpad4;
      }
     case osgGA::GUIEventAdapter::KEY_KP_5:
      {
		  key = '5';
         return CEGUI::Key::Numpad5;
      }
     case osgGA::GUIEventAdapter::KEY_KP_6:
      {
		  key = '6';
         return CEGUI::Key::Numpad6;
      }
     case osgGA::GUIEventAdapter::KEY_KP_7:
      {
		  key = '7';
         return CEGUI::Key::Numpad7;
      }
     case osgGA::GUIEventAdapter::KEY_KP_8:
      {
		  key = '8';
         return CEGUI::Key::Numpad8;
      }
     case osgGA::GUIEventAdapter::KEY_KP_9:
      {
		  key = '9';
         return CEGUI::Key::Numpad9;
      }
	//case osgGA::GUIEventAdapter::KEY_KP_Separator:
	//{
	//	  key = ',';
	//   return Key::Decimal;
	//} 
     case osgGA::GUIEventAdapter::KEY_KP_Divide:
      {
		  key = '/';
         return Key::Divide;
      }       
     case osgGA::GUIEventAdapter::KEY_KP_Multiply:
      {
		  key = '*';
         return Key::Multiply;
      }     
     case osgGA::GUIEventAdapter::KEY_KP_Subtract:
      {
		  key = '-';
         return Key::Subtract;
      }        
     case osgGA::GUIEventAdapter::KEY_KP_Add:
      {
		  key = '+';
         return Key::Add;
      }   
     case osgGA::GUIEventAdapter::KEY_KP_Decimal:
      {
		  key = '.';
         return Key::Decimal;
      }  

	  
     case osgGA::GUIEventAdapter::KEY_KP_Enter:     return Key::NumpadEnter;
     case osgGA::GUIEventAdapter::KEY_KP_Equal:    return Key::NumpadEquals;
     case osgGA::GUIEventAdapter::KEY_Up:           return Key::ArrowUp;
     case osgGA::GUIEventAdapter::KEY_Down:         return Key::ArrowDown;
     case osgGA::GUIEventAdapter::KEY_Right:        return Key::ArrowRight;
     case osgGA::GUIEventAdapter::KEY_Left:         return Key::ArrowLeft;
     case osgGA::GUIEventAdapter::KEY_Insert:       return Key::Insert;
     case osgGA::GUIEventAdapter::KEY_Home:         return Key::Home;
     case osgGA::GUIEventAdapter::KEY_End:          return Key::End;
     case osgGA::GUIEventAdapter::KEY_Page_Up:       return Key::PageUp;
     case osgGA::GUIEventAdapter::KEY_Page_Down:     return Key::PageDown;
     case osgGA::GUIEventAdapter::KEY_F1:           return Key::F1;
     case osgGA::GUIEventAdapter::KEY_F2:           return Key::F2;
     case osgGA::GUIEventAdapter::KEY_F3:           return Key::F3;
     case osgGA::GUIEventAdapter::KEY_F4:           return Key::F4;
     case osgGA::GUIEventAdapter::KEY_F5:           return Key::F5;
     case osgGA::GUIEventAdapter::KEY_F6:           return Key::F6;
     case osgGA::GUIEventAdapter::KEY_F7:           return Key::F7;
     case osgGA::GUIEventAdapter::KEY_F8:           return Key::F8;
     case osgGA::GUIEventAdapter::KEY_F9:           return Key::F9;
     case osgGA::GUIEventAdapter::KEY_F10:          return Key::F10;
     case osgGA::GUIEventAdapter::KEY_F11:          return Key::F11;
     case osgGA::GUIEventAdapter::KEY_F12:          return Key::F12;
     case osgGA::GUIEventAdapter::KEY_F13:          return Key::F13;
     case osgGA::GUIEventAdapter::KEY_F14:          return Key::F14;
     case osgGA::GUIEventAdapter::KEY_F15:          return Key::F15;
     case osgGA::GUIEventAdapter::KEY_Num_Lock:      return Key::NumLock;
     case osgGA::GUIEventAdapter::KEY_Scroll_Lock:    return Key::ScrollLock;
     case osgGA::GUIEventAdapter::KEY_Shift_R:       return Key::RightShift;
     case osgGA::GUIEventAdapter::KEY_Shift_L:       return Key::LeftShift;
     case osgGA::GUIEventAdapter::KEY_Control_R:        return Key::RightControl;
     case osgGA::GUIEventAdapter::KEY_Control_L:        return Key::LeftControl;
     case osgGA::GUIEventAdapter::KEY_Alt_R:         return Key::RightAlt;
     case osgGA::GUIEventAdapter::KEY_Alt_L:         return Key::LeftAlt;
     case osgGA::GUIEventAdapter::KEY_Super_L:       return Key::LeftWindows;
     case osgGA::GUIEventAdapter::KEY_Super_R:       return Key::RightWindows;
     case osgGA::GUIEventAdapter::KEY_Sys_Req:       return Key::SysRq;
     case osgGA::GUIEventAdapter::KEY_Menu:         return Key::AppMenu;
     case osgGA::GUIEventAdapter::KEY_Caps_Lock:         return Key::Capital;
     //case SDLK_POWER:        return Key::Power;

 
      case osgGA::GUIEventAdapter::KEY_KP_Insert:
      {
		  key = '0';
         return CEGUI::Key::Numpad0;
      }
      case osgGA::GUIEventAdapter::KEY_KP_End:
      {
		  key = '1';
         return CEGUI::Key::Numpad1;
      }
      case osgGA::GUIEventAdapter::KEY_KP_Down:
      {
		  key = '2';
         return CEGUI::Key::Numpad2;
      }
      case osgGA::GUIEventAdapter::KEY_KP_Page_Down:
      {
		  key = '3';
         return CEGUI::Key::Numpad3;
      }
      case osgGA::GUIEventAdapter::KEY_KP_Left:
      {
		  key = '4';
         return CEGUI::Key::Numpad4;
      }
      case osgGA::GUIEventAdapter::KEY_KP_Begin:
      {
		  key = '5';
         return CEGUI::Key::Numpad5;
      }
      case osgGA::GUIEventAdapter::KEY_KP_Right:
      {
		  key = '6';
         return CEGUI::Key::Numpad6;
      }
	  case osgGA::GUIEventAdapter::KEY_KP_Home:
      {
		  key = '7';
         return CEGUI::Key::Numpad7;
      }
      case osgGA::GUIEventAdapter::KEY_KP_Up:
      {
		  key = '8';
         return CEGUI::Key::Numpad8;
      }
      case osgGA::GUIEventAdapter::KEY_KP_Page_Up:
      {
		  key = '9';
         return CEGUI::Key::Numpad9;
      }
      case osgGA::GUIEventAdapter::KEY_KP_Delete:
      {
		// cegui does not handle the numpad '.' correctly
		  key = '.';
      }
	  

     }
     return key;
 }




struct CEGUIEventCallback : public osgGA::GUIEventHandler
{
	int lastwidth;
	int lastheight;
	boost::shared_ptr<GuiHandler>	_GuiH;

    CEGUIEventCallback(boost::shared_ptr<GuiHandler> GuiH) 
	{
		lastwidth = -1;
		lastheight = -1;
		_GuiH = GuiH;
	}
    
	bool CEGUIEventCallback::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor* nv)
	{
		float x = ea.getX();
		float y = ea.getY();
		bool injectionRetVal = false;

		// CEGUI wants 0,0 in the top left corner; osg has 0,0 in the bottom left corner
		y = ea.getWindowHeight() - y;

		switch(ea.getEventType())
		{

		case(osgGA::GUIEventAdapter::RESIZE):
			{
				int width = ea.getWindowWidth();
				int height = ea.getWindowHeight();
				if((width != lastwidth) || (height != lastheight))
				{
					if(_GuiH)
						_GuiH->Resize(width, height, lastwidth, lastheight);

					lastwidth = width;
					lastheight = height;
				}
				break;
			}

		case(osgGA::GUIEventAdapter::DRAG):
			{
				injectionRetVal = CEGUI::System::getSingleton().injectMousePosition(x, y);
				break;
			}

		case(osgGA::GUIEventAdapter::MOVE):
			{
				CEGUI::System::getSingleton().injectMousePosition(x,y);
				break;
			}

		case(osgGA::GUIEventAdapter::PUSH):
			{
				CEGUI::System::getSingleton().injectMousePosition(x, y);

				if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)  // left
					injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
				else if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON)  // middle
					injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
				else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)  // right
					injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);

				break;
			}

		case(osgGA::GUIEventAdapter::RELEASE):
			{
				CEGUI::System::getSingleton().injectMousePosition(x, y);

				if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)  // left
					injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
				else if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON)  // middle
					injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
				else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)  // right
					injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);

				break;
			}

		case(osgGA::GUIEventAdapter::DOUBLECLICK):
			{
				CEGUI::System::getSingleton().injectMousePosition(x, y);

				if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)  // left
					injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);

				else if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON)  // middle
					injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);

				else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)  // right
					injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
				break;
			}

		case(osgGA::GUIEventAdapter::SCROLL):
			{
				if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP)
					injectionRetVal = (CEGUI::System::getSingleton().injectMouseWheelChange( 1 ));

				if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_DOWN)
					injectionRetVal = (CEGUI::System::getSingleton().injectMouseWheelChange( -1 ));
			}

		case(osgGA::GUIEventAdapter::KEYDOWN):
			{
				int localkey = ea.getKey();
				injectionRetVal = CEGUI::System::getSingleton().injectKeyDown( static_cast<CEGUI::uint>(OSGKeyToCEGUIKey(localkey)) );
				injectionRetVal |= CEGUI::System::getSingleton().injectChar( static_cast<CEGUI::utf32>( localkey ) );
				break;
			}

		case(osgGA::GUIEventAdapter::KEYUP):
			{
				int localkey = ea.getKey();
				injectionRetVal = CEGUI::System::getSingleton().injectKeyUp( static_cast<CEGUI::uint>(OSGKeyToCEGUIKey(localkey)) );			
				break;
			}

		default:
			break;
		}
		

		CEGUI::Window* window = CEGUI::System::getSingleton().getGUISheet()->getCaptureWindow();
		if (window/* && window->getParent()*/) // does not work on redim
		{
			return injectionRetVal;
		}

		// do not consume the event, forward on to osg::Viewer
		return false;
	}
};

/***********************************************************
constructor
***********************************************************/
CEGUIDrawable::CEGUIDrawable()
{
	setSupportsDisplayList(false);
	setEventCallback(new CEGUIEventCallback(boost::shared_ptr<GuiHandler>()));
	_activeContextID = 0;
}


/***********************************************************
constructor
***********************************************************/
CEGUIDrawable::CEGUIDrawable(int resX, int resY, boost::shared_ptr<GuiHandler> GuiH)
: _GuiH(GuiH)
{
	try
	{
		setSupportsDisplayList(false);
		setEventCallback(new CEGUIEventCallback(_GuiH));

		if(_GuiH)
			_GuiH->Initialize(resX, resY);

	 //   CEGUI::OpenGLRenderer& gui_renderer = CEGUI::OpenGLRenderer::create();
		//gui_renderer.enableExtraStateSettings(true);
		//CEGUI::System::create( gui_renderer );
	 //   
		//// initialise the required dirs for the DefaultResourceProvider
		//CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
		//	(CEGUI::System::getSingleton().getResourceProvider());

		//rp->setResourceGroupDirectory("schemes", "./Data/GUI/schemes/");
		//rp->setResourceGroupDirectory("imagesets", "./Data/GUI/imagesets/");
		//rp->setResourceGroupDirectory("fonts", "./Data/GUI/fonts/");
		//rp->setResourceGroupDirectory("layouts", "./Data/GUI/layouts/");
		//rp->setResourceGroupDirectory("looknfeels", "./Data/GUI/looknfeel/");
		//rp->setResourceGroupDirectory("lua_scripts", "./Data/GUI/lua_scripts/");

		//// set the default resource groups to be used
		//CEGUI::Imageset::setDefaultResourceGroup("imagesets");
		//CEGUI::Font::setDefaultResourceGroup("fonts");
		//CEGUI::Scheme::setDefaultResourceGroup("schemes");
		//CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
		//CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		//CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

		//// load in the scheme file, which auto-loads the TaharezLook imageset
		//CEGUI::SchemeManager::getSingleton().create( "TaharezLook.scheme" );

		////! load font file
		//CEGUI::FontManager::getSingleton().create( "abbey_m1-9.font" );

		//CEGUI::System::getSingleton().setDefaultMouseCursor( "TaharezLook", "MouseArrow" );
		//CEGUI::System::getSingleton().setDefaultTooltip( "TaharezLook/Tooltip" );


		//CEGUI::Window * root = CEGUI::WindowManager::getSingleton().loadWindowLayout( "chatbox.layout" );
		//CEGUI::System::getSingleton().setGUISheet( root );


		_activeContextID = 0;
	}
	catch(CEGUI::Exception &ex)
	{
		std::cout<<  ex.getMessage().c_str()<<std::endl;
	}

}


/***********************************************************
destructor
***********************************************************/
CEGUIDrawable::~CEGUIDrawable()
{
    // delete CEGUI??
}



/***********************************************************
drawImplementation
***********************************************************/
void CEGUIDrawable::drawImplementation(osg::RenderInfo& renderInfo) const
{
    osg::State* state = renderInfo.getState();

    if (state->getContextID()!=_activeContextID) 
		return;

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    state->disableAllVertexArrays();

    CEGUI::System::getSingleton().renderGUI();

    glPopAttrib();
    
    state->checkGLErrors("CEGUIDrawable::drawImplementation");
}
