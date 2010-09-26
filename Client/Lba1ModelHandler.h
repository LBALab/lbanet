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

#if !defined(__LbaNetModel_1_LBA1ModelHandler_h)
#define __LbaNetModel_1_LBA1ModelHandler_h


#include "AnimatedObjectHandlerBase.h"

class LBA1ModelClass;


/***********************************************************************
 * Module:  Lba1ModelHandler.h
 * Purpose: class for animated Lba1 models
 ***********************************************************************/
class Lba1ModelHandler : public AnimatedObjectHandlerBase
{
public:
	//! constructor
	Lba1ModelHandler(const LbaNet::ModelInfo & info, float animationspeed);

	//! destructor
	virtual ~Lba1ModelHandler();


	//! update display with current frame - used for animation
	virtual void Process(double time, float tdiff);

	// get current animation Id
	virtual int GetCurrentAnimation();

	// get current associated speed
	virtual float GetCurrentAssociatedSpeedX();

	// get current associated speed
	virtual float GetCurrentAssociatedSpeedY();

	// get current associated speed
	virtual float GetCurrentAssociatedSpeedZ();

	// update model
	virtual void UpdateModel(const LbaNet::ModelInfo & info);

	// update animation
	virtual void UpdateAnimation(const std::string & AnimString);

	// update animation
	virtual void UpdateAnimation(int AnimIdx);


private:
	LBA1ModelClass*			_model;

	float					_animationspeed;

};




#endif