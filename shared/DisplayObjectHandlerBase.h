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


#ifndef _LBANET_DISPLAY_OBJECT_HANDLER_BASE_H_
#define _LBANET_DISPLAY_OBJECT_HANDLER_BASE_H_

#include "CommonTypes.h"
#include <LbaTypes.h>

//*************************************************************************************************
//*                               class DisplayObjectHandlerBase
//*************************************************************************************************
/**
* @brief Pure virtual class for handling the transformation of an object before displaying it
* (e.g. translation, rotation, etc.)
*
*/
class DisplayObjectHandlerBase
{
public:

	//! constructor
	DisplayObjectHandlerBase(){}

	//! destructor
	virtual ~DisplayObjectHandlerBase(){}

	//! set object position in the world
	virtual void SetPosition(float X, float Y, float Z) = 0;

	//! set object rotation on X axis
	virtual void SetRotation(const LbaQuaternion& Q) = 0;

	//! show or hide the object
	virtual void ShowOrHide(bool Show) = 0;

	//! update display with current frame - used for animation
	//! the return value depends of the derived class type
	virtual int Process(double time, float tdiff) = 0;

	//! update display
	//! the return value depends of the derived class type
	virtual int Update(LbaNet::DisplayObjectUpdateBasePtr update) = 0;

	//! only for animated model
	// get current animation Id
	virtual std::string GetCurrentAnimation() {return 0;}

	//! only for animated model
	// get current associated speed
	virtual float GetCurrentAssociatedSpeedX() {return 0;}

	//! only for animated model
	// get current associated speed
	virtual float GetCurrentAssociatedSpeedY() {return 0;}

	//! only for animated model
	// get current associated speed
	virtual float GetCurrentAssociatedSpeedZ() {return 0;}

	//! set name of display object that will be returned during picking
	virtual void SetName(const std::string & name) = 0;
};


#endif
