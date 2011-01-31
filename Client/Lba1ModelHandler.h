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
namespace osg
{
	class Node;
	class Geode;
	class AutoTransform;
}

/***********************************************************************
 * Module:  Lba1ModelHandler.h
 * Purpose: class for animated Lba1 models
 ***********************************************************************/
class Lba1ModelHandler : public AnimatedObjectHandlerBase
{
public:
	//! constructor
	Lba1ModelHandler(boost::shared_ptr<DisplayTransformation> Tr,
						const LbaNet::ModelInfo & info, float animationspeed,
						const LbaNet::ObjectExtraInfo &extrainfo,
						const LbaNet::LifeManaInfo &lifeinfo);

	//! destructor
	virtual ~Lba1ModelHandler();


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


protected:
	// refresh model
	int RefreshModel();


private:
	LBA1ModelClass*									_model;
	osg::ref_ptr<osg::Node>							_osgnode;
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