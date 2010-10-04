#include "OsgEventHandler.h"
#include "OSGHandler.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include <CEGUI.h>




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
		case(osgGA::GUIEventAdapter::PUSH):
		{
			if(ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
			{			
				_mouse_Y = ea.getY();
				_right_button_pressed = true;

				EventsQueue::getReceiverQueue()->AddEvent(new FocusChatEvent(false));
				return true;
			}
		}

		case(osgGA::GUIEventAdapter::RELEASE):
		{
			if(ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
			{
				_right_button_pressed = false;
				return true;
			}
		}

		// update Zenit on mouse move with right button pressed
		case(osgGA::GUIEventAdapter::DRAG):
		{
			if(_right_button_pressed)
			{
				OsgHandler::getInstance()->DeltaUpdateCameraZenit(_mouse_Y-ea.getY());
				_mouse_Y = ea.getY();
				return true;
			}
		}

		// zoom on mouse scroll
		case(osgGA::GUIEventAdapter::SCROLL):
		{
			if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_DOWN)
				OsgHandler::getInstance()->DeltaUpdateCameraDistance(5);

			if(ea.getScrollingMotion() == osgGA::GUIEventAdapter::SCROLL_UP)
				OsgHandler::getInstance()->DeltaUpdateCameraDistance(-5);

			return true;
		}

		// key press
		case(osgGA::GUIEventAdapter::KEYDOWN):
		{
			int kkk = ea.getKey();

			// for check if CEGUI handle the event
			if(CEGUI::System::getSingleton().injectKeyDown( static_cast<CEGUI::uint>(OSGKeyToCEGUIKey(kkk)) )
			|| CEGUI::System::getSingleton().injectChar( static_cast<CEGUI::utf32>( kkk ) ))
				return true;

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
					EventsQueue::getSenderQueue()->AddEvent(new LbaNet::PressedWeaponKeyEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble()));

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
			}
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

			}
		}
	}

	return false;
}

