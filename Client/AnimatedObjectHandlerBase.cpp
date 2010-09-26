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
AnimatedObjectHandlerBase::AnimatedObjectHandlerBase()
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
void AnimatedObjectHandlerBase::Update(LbaNet::DisplayObjectUpdateBasePtr update)
{
	const std::type_info& info = typeid(*update);

	// ModelUpdate
	if(info == typeid(LbaNet::ModelUpdate))
	{
		LbaNet::ModelUpdate * castedptr = 
			dynamic_cast<LbaNet::ModelUpdate *>(update.get());

		UpdateModel(castedptr->Info);
		return;
	}

	// AnimationStringUpdate
	if(info == typeid(LbaNet::AnimationStringUpdate))
	{
		LbaNet::AnimationStringUpdate * castedptr = 
			dynamic_cast<LbaNet::AnimationStringUpdate *>(update.get());

		UpdateAnimation(castedptr->Animation);
		return;
	}

	// AnimationIdUpdate
	if(info == typeid(LbaNet::AnimationIdUpdate))
	{
		LbaNet::AnimationIdUpdate * castedptr = 
			dynamic_cast<LbaNet::AnimationIdUpdate *>(update.get());

		UpdateAnimation(castedptr->AnimationId);
		return;
	}

	OsgObjectHandler::Update(update);
}