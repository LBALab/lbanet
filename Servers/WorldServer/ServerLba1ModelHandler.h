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

#if !defined(__LbaNetModel_1_server_LBA1ModelHandler_h)
#define __LbaNetModel_1_server_LBA1ModelHandler_h


#include "DisplayObjectHandlerBase.h"

class ServerLBA1ModelClass;

/***********************************************************************
 * Module:  Lba1ModelHandler.h
 * Purpose: class for animated Lba1 models
 ***********************************************************************/
class ServerLba1ModelHandler : public DisplayObjectHandlerBase
{
public:
	//! constructor
	ServerLba1ModelHandler(const LbaNet::ModelInfo & info, float animationspeed);

	//! destructor
	virtual ~ServerLba1ModelHandler();

	//! update display
	virtual int Update(LbaNet::DisplayObjectUpdateBasePtr update,
							bool updatestoredstate);

	//! update display with current frame - used for animation
	//! return 1 if current animation finishes - 0 else
	virtual int Process(double time, float tdiff);

	// get current animation Id
	virtual std::string GetCurrentAnimation();

	// get current associated speed
	virtual float GetCurrentAssociatedSpeedX();

	// get current associated speed
	virtual float GetCurrentAssociatedSpeedY();

	// get current associated speed
	virtual float GetCurrentAssociatedSpeedZ();

	//! get current model
	virtual LbaNet::ModelInfo GetCurrentModel();

	// update model
	virtual int UpdateModel(const LbaNet::ModelInfo & info);

	// update animation
	virtual int UpdateAnimation(const std::string & AnimString);

	// pause current running animation
	virtual void PauseAnimation();

	// save current model state
	virtual void SaveState();

	// restore previously saved model state
	virtual void RestoreState();



	//! set object position in the world
	virtual void SetPosition(float X, float Y, float Z){}

	//! set object rotation on X axis
	virtual void SetRotation(const LbaQuaternion& Q){}

	//! show or hide the object
	virtual void ShowOrHide(bool Show){}

	//! set name of display object that will be returned during picking
	virtual void SetName(const std::string & name){}



protected:
	// refresh model
	int RefreshModel(bool forcecolor = false);


private:
	ServerLBA1ModelClass*							_model;
	bool											_paused;


	float											_animationspeed;

	LbaNet::ModelInfo								_currentmodelinfo;
	std::string										_currentanimationstring;

	int												_currModel;
	int												_currBody;
	int												_currAnimation;


	LbaNet::ModelInfo								_savedmodelinfo;
	std::string										_savedanimationstring;
};




#endif