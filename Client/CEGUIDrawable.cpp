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

	//draw overlay
	if(_GuiH && _GuiH->ShouldDrawOverlay())
	{
		int sX, sY;
		_GuiH->GetScreenSize(sX, sY);

		float life, mana;
		_GuiH->GetLifeManaInfo(life, mana);
		

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, sX, sY, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);

		//glBindTexture(GL_TEXTURE_2D, m_halo_texture);
		//glColor3f(246/255.0f,181/255.0f,24/255.0f);
		//glBegin(GL_QUADS);
		//	glTexCoord2f(1, 1);
		//	glVertex2f(60,0);	
		//	glTexCoord2f(0, 1);
		//	glVertex2f(0,0);
		//	glTexCoord2f(0, 0);
		//	glVertex2f(0,84);	
		//	glTexCoord2f(1, 0);
		//	glVertex2f(60,84);	
		//glEnd();


		//glBindTexture(GL_TEXTURE_2D, m_char_texture);
		//glColor3f(1,1,1);
		//glBegin(GL_QUADS);
		//	glTexCoord2f(1, 1);
		//	glVertex2f(55,0);	
		//	glTexCoord2f(0, 1);
		//	glVertex2f(5,0);	
		//	glTexCoord2f(0, 0);
		//	glVertex2f(5,69);
		//	glTexCoord2f(1, 0);
		//	glVertex2f(55,69);	
		//glEnd();

		int offsetx = 67;
		int sizex = 79;
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
			glColor3f(115/255.f, 0.f, 2/255.f);
			glVertex2f(offsetx,11);					
			glVertex2f(offsetx+(sizex*life),11);	
			glColor3f(254/255.f, 0.f, 3/255.f);
			glVertex2f(offsetx+(sizex*life),7);					
			glVertex2f(offsetx,7);	

			glColor3f(11/255.f, 11/255.f, 71/255.f);
			glVertex2f(offsetx,20);					
			glVertex2f(offsetx+(sizex*mana),20);	
			glColor3f(13/255.f, 12/255.f, 150/255.f);
			glVertex2f(offsetx+(sizex*mana),16);					
			glVertex2f(offsetx,16);	
		glEnd();


		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW); 
	}

    
    state->checkGLErrors("CEGUIDrawable::drawImplementation");
}
