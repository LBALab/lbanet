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

#include "OSGHandler.h"

#include <iostream>
#include <time.h>
#include <osg/Node>
#include <osg/MatrixTransform>
#include "GuiHandler.h"

int main( int argc, char **argv )
{
	boost::shared_ptr<GuiHandler> ghptr (new GuiHandler());

	OsgHandler::getInstance()->Initialize("Lbanet", "./Data", ghptr);


	//gH.Initialize(resX, resY, false, "v0.999");


	OsgHandler::getInstance()->AddActorNode(OsgHandler::getInstance()->LoadOSGFile("map0.osgb"));

	while(!OsgHandler::getInstance()->Update())
	{

	}

	OsgHandler::getInstance()->Finalize();

	return 0;

	//CEGUI::OpenGLRenderer *glRenderer=static_cast<CEGUI::OpenGLRenderer *>(CEGUI::System::getSingleton().getRenderer());
	//glRenderer->grabTextures();
	//CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Size((float)800,(float)600));
	//glRenderer->restoreTextures(); 


	//osg::Timer_t start_tick = osg::Timer::instance()->tick();



 //   // run the viewer
	//while (!viewer.done()) 
	//{
	//	osg::Timer_t end_tick = osg::Timer::instance()->tick();

	//	/* inject the time that passed since the last call */
	//	CEGUI::System::getSingleton().injectTimePulse( float(osg::Timer::instance()->delta_s(start_tick,end_tick)) );
	//	/* store the new time as the last time */
	//	start_tick = end_tick;

	//	viewer.frame();
	//}

    //return 0;
}

