#include "OsgEventHandler.h"
#include "OSGHandler.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "ClientExtendedTypes.h"

#include <CEGUI.h>

#include <osgViewer/Viewer>
#include <osgUtil/PolytopeIntersector>
#include <osg/io_utils>

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
	  

	  case '0':
	  {
		return CEGUI::Key::Zero;	
	  }
	  case '1':
	  {
		return CEGUI::Key::One;	
	  }
	  case '2':
	  {
		return CEGUI::Key::Two;	
	  }
	  case '3':
	  {
		return CEGUI::Key::Three;	
	  }
	  case '4':
	  {
		return CEGUI::Key::Four;	
	  }
	  case '5':
	  {
		return CEGUI::Key::Five;	
	  }
	  case '6':
	  {
		return CEGUI::Key::Six;	
	  }
	  case '7':
	  {
		return CEGUI::Key::Seven;	
	  }
	  case '8':
	  {
		return CEGUI::Key::Eight;	
	  }
	  case '9':
	  {
		return CEGUI::Key::Nine;	
	  }

     }
     return key;
 }





/***********************************************************
handle inputs
***********************************************************/
bool OsgEventHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
		case(osgGA::GUIEventAdapter::MOVE):
		{
			float x = ea.getX();
			float y = ea.getWindowHeight() - ea.getY();

			CEGUI::System::getSingleton().injectMousePosition(x,y);
			break;
		}



		case(osgGA::GUIEventAdapter::DOUBLECLICK):
		{
			float x = ea.getX();
			float y = ea.getWindowHeight() - ea.getY();

			CEGUI::System::getSingleton().injectMousePosition(x, y);
			bool injectionRetVal = false;

			if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)  // left
				injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);

			else if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON)  // middle
				injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);

			else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)  // right
				injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);

			if(injectionRetVal)
				return true;

			break;
		}


		case(osgGA::GUIEventAdapter::PUSH):
		{
			float x = ea.getX();
			float y = ea.getWindowHeight() - ea.getY();

			CEGUI::System::getSingleton().injectMousePosition(x, y);
			bool injectionRetVal = false;

			if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)  // left
				injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
			else if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON)  // middle
				injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
			else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)  // right
				injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);

			if(injectionRetVal)
				return true;


			if(ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
			{	
				osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
				pick(view, ea);
				return false;
			}


			if(ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
			{	
				_mouse_X = ea.getX();
				_mouse_Y = ea.getY();
				_right_button_pressed = true;

				EventsQueue::getReceiverQueue()->AddEvent(new FocusChatEvent(false));
				return true;
			}
		}

		case(osgGA::GUIEventAdapter::RELEASE):
		{
			float x = ea.getX();
			float y = ea.getWindowHeight() - ea.getY();

			CEGUI::System::getSingleton().injectMousePosition(x, y);
			bool injectionRetVal = false;

			if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)  // left
				injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
			else if (ea.getButton() == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON)  // middle
				injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
			else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)  // right
				injectionRetVal = CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);

			if(injectionRetVal)
				return true;


			if(ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
			{
				_right_button_pressed = false;
				return true;
			}
		}

		// update Zenit on mouse move with right button pressed
		case(osgGA::GUIEventAdapter::DRAG):
		{
			float x = ea.getX();
			float y = ea.getWindowHeight() - ea.getY();

			CEGUI::System::getSingleton().injectMousePosition(x, y);

			if(_right_button_pressed)
			{
				OsgHandler::getInstance()->DeltaUpdateCameraAzimut(_mouse_X-ea.getX());
				OsgHandler::getInstance()->DeltaUpdateCameraZenit(_mouse_Y-ea.getY());
				_mouse_X = ea.getX();
				_mouse_Y = ea.getY();
				return true;
			}
		}

		// zoom on mouse scroll
		case(osgGA::GUIEventAdapter::SCROLL):
		{
			if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_DOWN)
			{
				if(!(CEGUI::System::getSingleton().injectMouseWheelChange( -1 )))
					OsgHandler::getInstance()->DeltaUpdateCameraDistance(5);
			}

			if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP)
			{
				if(!(CEGUI::System::getSingleton().injectMouseWheelChange( 1 )))
					OsgHandler::getInstance()->DeltaUpdateCameraDistance(-5);
			}

			return true;
		}

		// key press
		case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			int kkk = ea.getKey();
			int convertedk = OSGKeyToCEGUIKey(kkk);

			// for check if CEGUI handle the event
			if(CEGUI::System::getSingleton().injectKeyDown( static_cast<CEGUI::uint>(convertedk) )
				|| CEGUI::System::getSingleton().injectChar( static_cast<CEGUI::utf32>( kkk )))
			{
				return true;
			}


			{
				// enter key
				if(kkk == osgGA::GUIEventAdapter::KEY_Return)
				{
					EventsQueue::getReceiverQueue()->AddEvent(new FocusChatEvent(true));
					return true;	
				}

				// escape key
				if(kkk == osgGA::GUIEventAdapter::KEY_Escape)
				{
					// go to menu GUI
					EventsQueue::getReceiverQueue()->AddEvent(new DisplayGUIEvent(3));
					return true;	
				}

				// move forward
				if(kkk == _keymap[LbanetKey_Forward])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyPressedEvent(LbanetKey_Forward));
					return true;	
				}


				// move backward
				if(kkk == _keymap[LbanetKey_Backward])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyPressedEvent(LbanetKey_Backward));
					return true;	
				}


				// move left
				if(kkk == _keymap[LbanetKey_Left])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyPressedEvent(LbanetKey_Left));
					return true;	
				}


				// move right
				if(kkk == _keymap[LbanetKey_Right])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyPressedEvent(LbanetKey_Right));
					return true;	
				}


				// strafe left
				if(kkk == _keymap[LbanetKey_StrafeL])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyPressedEvent(LbanetKey_StrafeL));
					return true;	
				}


				// strafe right
				if(kkk == _keymap[LbanetKey_StrafeR])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyPressedEvent(LbanetKey_StrafeR));
					return true;	
				}


				// move up
				if(kkk == _keymap[LbanetKey_Up])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyPressedEvent(LbanetKey_Up));
					return true;	
				}


				// move down
				if(kkk == _keymap[LbanetKey_Down])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyPressedEvent(LbanetKey_Down));
					return true;	
				}


				// action key
				if(kkk == _keymap[LbanetKey_Action])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyPressedEvent(LbanetKey_Action));				
					EventsQueue::getSenderQueue()->AddEvent(new LbaNet::PressedActionKeyEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), false));
					return true;	
				}


				// normal action key
				if(kkk == _keymap[LbanetKey_NAction])
				{
					EventsQueue::getSenderQueue()->AddEvent(new LbaNet::PressedActionKeyEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), true));

					return true;	
				}


				// weapon key
				if(kkk == _keymap[LbanetKey_Weapon])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyPressedEvent(LbanetKey_Weapon));		

					return true;	
				}


				// stance1
				if(kkk == _keymap[LbanetKey_Stance1])
				{
					EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ChangeStanceEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), LbaNet::StanceNormal));

					return true;	
				}


				// stance2
				if(kkk == _keymap[LbanetKey_Stance2])
				{
					EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ChangeStanceEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), LbaNet::StanceSporty));
					return true;	
				}


				// stance3
				if(kkk == _keymap[LbanetKey_Stance3])
				{
					EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ChangeStanceEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), LbaNet::StanceAggresive));
					return true;	
				}


				// stance4
				if(kkk == _keymap[LbanetKey_Stance4])
				{
					EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ChangeStanceEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), LbaNet::StanceDiscrete));
					return true;	
				}

				// fullscreen
				if(kkk == osgGA::GUIEventAdapter::KEY_F12)
				{
					OsgHandler::getInstance()->ToggleFullScreen();
					return true;	
				}

				// CenterCameraEvent
				if(kkk == _keymap[LbanetKey_CenterCamera])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new CenterCameraEvent());
					return true;	
				}

				// shortcut 0
				if(kkk == _keymap[LbanetKey_Shortcut0])
				{
					LbaNet::GuiUpdatesSeq updseq;
					updseq.push_back(new UsedShorcutUpdate(0));
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", updseq));

					return true;	
				}

				// shortcut 1
				if(kkk == _keymap[LbanetKey_Shortcut1])
				{
					LbaNet::GuiUpdatesSeq updseq;
					updseq.push_back(new UsedShorcutUpdate(1));
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", updseq));

					return true;	
				}

				// shortcut 2
				if(kkk == _keymap[LbanetKey_Shortcut2])
				{
					LbaNet::GuiUpdatesSeq updseq;
					updseq.push_back(new UsedShorcutUpdate(2));
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", updseq));

					return true;	
				}

				// shortcut 3
				if(kkk == _keymap[LbanetKey_Shortcut3])
				{
					LbaNet::GuiUpdatesSeq updseq;
					updseq.push_back(new UsedShorcutUpdate(3));
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", updseq));

					return true;	
				}

				// shortcut 4
				if(kkk == _keymap[LbanetKey_Shortcut4])
				{
					LbaNet::GuiUpdatesSeq updseq;
					updseq.push_back(new UsedShorcutUpdate(4));
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", updseq));

					return true;	
				}

				// shortcut 5
				if(kkk == _keymap[LbanetKey_Shortcut5])
				{
					LbaNet::GuiUpdatesSeq updseq;
					updseq.push_back(new UsedShorcutUpdate(5));
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", updseq));

					return true;	
				}

				// shortcut 6
				if(kkk == _keymap[LbanetKey_Shortcut6])
				{
					LbaNet::GuiUpdatesSeq updseq;
					updseq.push_back(new UsedShorcutUpdate(6));
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", updseq));

					return true;	
				}

				// shortcut 7
				if(kkk == _keymap[LbanetKey_Shortcut7])
				{
					LbaNet::GuiUpdatesSeq updseq;
					updseq.push_back(new UsedShorcutUpdate(7));
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", updseq));

					return true;	
				}

				// shortcut 8
				if(kkk == _keymap[LbanetKey_Shortcut8])
				{
					LbaNet::GuiUpdatesSeq updseq;
					updseq.push_back(new UsedShorcutUpdate(8));
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", updseq));

					return true;	
				}

				// shortcut 9
				if(kkk == _keymap[LbanetKey_Shortcut9])
				{
					LbaNet::GuiUpdatesSeq updseq;
					updseq.push_back(new UsedShorcutUpdate(9));
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ShortcutBox", updseq));

					return true;	
				}				
			}
		}

		case(osgGA::GUIEventAdapter::RESIZE):
		{
			int width = ea.getWindowWidth();
			int height = ea.getWindowHeight();
			//#ifdef _USE_QT_EDITOR_
			OsgHandler::getInstance()->Resize(width, height);
			//#else
			//OsgHandler::getInstance()->Resized(width, height);
			//#endif
			break;
		}



		// key release  
		case(osgGA::GUIEventAdapter::KEYUP):
		{
			int kkk = ea.getKey();

			// for check if CEGUI handle the event
			if(CEGUI::System::getSingleton().injectKeyUp( static_cast<CEGUI::uint>(OSGKeyToCEGUIKey(kkk)) ))
				return true;

			{
				// move forward
				if(kkk == _keymap[LbanetKey_Forward])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyReleasedEvent(LbanetKey_Forward));
					return true;	
				}

				// move backward
				if(kkk == _keymap[LbanetKey_Backward])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyReleasedEvent(LbanetKey_Backward));
					return true;	
				}


				// move left
				if(kkk == _keymap[LbanetKey_Left])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyReleasedEvent(LbanetKey_Left));
					return true;	
				}


				// move right
				if(kkk == _keymap[LbanetKey_Right])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyReleasedEvent(LbanetKey_Right));
					return true;	
				}


				// strafe left
				if(kkk == _keymap[LbanetKey_StrafeL])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyReleasedEvent(LbanetKey_StrafeL));
					return true;	
				}


				// strafe right
				if(kkk == _keymap[LbanetKey_StrafeR])
				{
					// go to menu GUI
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyReleasedEvent(LbanetKey_StrafeR));
					return true;	
				}


				// move up
				if(kkk == _keymap[LbanetKey_Up])
				{
					// go to menu GUI
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyReleasedEvent(LbanetKey_Up));
					return true;	
				}


				// move down
				if(kkk == _keymap[LbanetKey_Down])
				{
					// go to menu GUI
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyReleasedEvent(LbanetKey_Down));
					return true;	
				}


				// action key
				if(kkk == _keymap[LbanetKey_Action])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyReleasedEvent(LbanetKey_Action));
					
					return true;	
				}


				// weapon key
				if(kkk == _keymap[LbanetKey_Weapon])
				{
					EventsQueue::getReceiverQueue()->AddEvent(new PlayerKeyReleasedEvent(LbanetKey_Weapon));		

					return true;	
				}

			}
		}
	}

	return false;
}




/***********************************************************
pick object in the scene
***********************************************************/
void OsgEventHandler::pick(osgViewer::View* view, const osgGA::GUIEventAdapter& ea)
{
    osg::Viewport* viewport = view->getCamera()->getViewport();
    double mx = viewport->x() + (int)((double )viewport->width()*(ea.getXnormalized()*0.5+0.5));
    double my = viewport->y() + (int)((double )viewport->height()*(ea.getYnormalized()*0.5+0.5));
    double w = 5.0f;
    double h = 5.0f;
    osgUtil::PolytopeIntersector* picker = new 
		osgUtil::PolytopeIntersector( osgUtil::Intersector::WINDOW, mx-w, my-h, mx+w, my+h );

    osgUtil::IntersectionVisitor iv(picker);
    view->getCamera()->accept(iv);

	std::string keepname;
	float px=0, py=0, pz=0;

    if (picker->containsIntersections())
    {
        osgUtil::PolytopeIntersector::Intersections intersections = picker->getIntersections();

        for(osgUtil::PolytopeIntersector::Intersections::iterator hitr = intersections.begin();
				hitr != intersections.end();  ++hitr)
        {
			osg::NodePath::reverse_iterator it = hitr->nodePath.rbegin();
			osg::NodePath::reverse_iterator end = hitr->nodePath.rend();
			for(; it != end; ++it)
			{
				std::string name = (*it)->getName();
				if(name.size() > 2 && name[1] == '_')
				{
					if(keepname == "")
					{
						keepname = name;
						px = hitr->localIntersectionPoint.x();
						py = hitr->localIntersectionPoint.y();
						pz = hitr->localIntersectionPoint.z();
					}
					else
					{
						// take editor stuff before actors
						char c1 = keepname[0];
						char c2 = name[0];
						if(c2 == 'E' && c1 == 'A')
						{
							keepname = name;
							px = hitr->localIntersectionPoint.x();
							py = hitr->localIntersectionPoint.y();
							pz = hitr->localIntersectionPoint.z();
						}

						// always take player stuff before anything
						if(c2 == 'M' || c1 == 'P')
						{
							px = hitr->localIntersectionPoint.x();
							py = hitr->localIntersectionPoint.y();
							pz = hitr->localIntersectionPoint.z();
							EventsQueue::getReceiverQueue()->AddEvent(new ObjectPickedEvent(name, px, py, pz)); 
							return;
						}
					}
				}
			}
        }
    }

	EventsQueue::getReceiverQueue()->AddEvent(new ObjectPickedEvent(keepname, px, py, pz));      
}