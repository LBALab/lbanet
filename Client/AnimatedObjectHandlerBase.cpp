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

#include "AnimatedObjectHandlerBase.h"

/***********************************************************
Constructor
***********************************************************/
AnimatedObjectHandlerBase::AnimatedObjectHandlerBase(boost::shared_ptr<DisplayTransformation> Tr,
														const LbaNet::ObjectExtraInfo &extrainfo)
: OsgObjectHandler(Tr, extrainfo)
{
}

/***********************************************************
destructor
***********************************************************/
AnimatedObjectHandlerBase::~AnimatedObjectHandlerBase()
{
}

/***********************************************************
update display
***********************************************************/
int AnimatedObjectHandlerBase::Update(LbaNet::DisplayObjectUpdateBasePtr update)
{
	const std::type_info& info = typeid(*update);

	// ModelUpdate
	if(info == typeid(LbaNet::ModelUpdate))
	{
		LbaNet::ModelUpdate * castedptr = 
			dynamic_cast<LbaNet::ModelUpdate *>(update.get());

		return UpdateModel(castedptr->Info);
	}

	// AnimationStringUpdate
	if(info == typeid(LbaNet::AnimationStringUpdate))
	{
		LbaNet::AnimationStringUpdate * castedptr = 
			dynamic_cast<LbaNet::AnimationStringUpdate *>(update.get());

		return UpdateAnimation(castedptr->Animation);
	}

	// PauseAnimationUpdate
	if(info == typeid(LbaNet::PauseAnimationUpdate))
	{
		PauseAnimation();
	}

	// ObjectLifeInfoUpdate
	if(info == typeid(LbaNet::ObjectLifeInfoUpdate))
	{
		LbaNet::ObjectLifeInfoUpdate * castedptr = 
			dynamic_cast<LbaNet::ObjectLifeInfoUpdate *>(update.get());

		UpdateLifeInfo(castedptr->Update);
	}

	


	return OsgObjectHandler::Update(update);
}