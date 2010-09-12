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

//#include <iostream>
//#include <time.h>
//#include <osg/Node>
//#include <osg/MatrixTransform>
#include "GuiHandler.h"
//#include "ObjectsDescription.h"
//#include "PhysXEngine.h"
//#include "DynamicObject.h"

#include "LbaNetEngine.h"

#ifdef NDEBUG
#include "resource.h"
#include "OSGHandler.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main( int argc, char **argv )
#endif
{
	// create engine
	LbaNetEngine engine;

	// set windows icon in release mode
	#ifdef NDEBUG
	SendMessage((HWND)OsgHandler::getInstance()->GetWindowsHandle(), 
		WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(hInstance,  MAKEINTRESOURCE(IDI_ICON1)));
	#endif

	// start run loop
	engine.run();

	return 0;
}

