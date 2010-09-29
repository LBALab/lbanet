#include "OsgEventHandler.h"
#include "OSGHandler.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"

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

