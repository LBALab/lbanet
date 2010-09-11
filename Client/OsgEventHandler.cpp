#include "OsgEventHandler.h"
#include "OSGHandler.h"


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

		// notify OSG of the screen being resized
		case(osgGA::GUIEventAdapter::RESIZE):
		{
			OsgHandler::getInstance()->NotifyResized();
		}

		default:
			return false;
	}
}

