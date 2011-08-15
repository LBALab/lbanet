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
	virtual int Update(LbaNet::DisplayObjectUpdateBasePtr update,
							bool updatestoredstate) = 0;

	//! only for animated model
	// get current animation Id
	virtual std::string GetCurrentAnimation() {return "";}

	//! only for animated model
	// get current associated speed
	virtual float GetCurrentAssociatedSpeedX() {return 0;}

	//! only for animated model
	// get current associated speed
	virtual float GetCurrentAssociatedSpeedY() {return 0;}

	//! only for animated model
	// get current associated speed
	virtual float GetCurrentAssociatedSpeedZ() {return 0;}

	//! only for animated model
	//! return animation key frame
	virtual int GetCurrentKeyFrame() {return -1;}


	//! get current model
	virtual LbaNet::ModelInfo GetCurrentModel(bool storedstate) {return LbaNet::ModelInfo();}


	//! set name of display object that will be returned during picking
	virtual void SetName(const std::string & name) = 0;


	// save current model state
	virtual void SaveState(){}

	// restore previously saved model state
	virtual void RestoreState(){}

	//! save object to file
	virtual void SaveToFile(const std::string & filename){}

	//! tore object copy
	virtual void StoreObjectCopy(){}

	//! check if can play animation
	virtual bool CanPlayAnimation(const std::string & anim) = 0;


	//! set transparency material
	virtual void SetTransparencyMaterial(bool OnOff, float Alpha) = 0;


	//! set color material
	virtual void SetColorMaterial(	int MaterialType, 		
							float	MatAmbientColorR,
							float	MatAmbientColorG,
							float	MatAmbientColorB,
							float	MatAmbientColorA,			
							float	MatDiffuseColorR,
							float	MatDiffuseColorG,
							float	MatDiffuseColorB,
							float	MatDiffuseColorA,
							float	MatSpecularColorR,
							float	MatSpecularColorG,
							float	MatSpecularColorB,
							float	MatSpecularColorA,	
							float	MatEmissionColorR,
							float	MatEmissionColorG,
							float	MatEmissionColorB,
							float	MatEmissionColorA,
							float	MatShininess) = 0;


	//! set shout text
	virtual void SetShoutText(const std::string & text, float size, 
								float colorR, float colorG, float colorB, int TTL) = 0;
};




#endif
