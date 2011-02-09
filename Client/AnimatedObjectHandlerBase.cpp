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
														const LbaNet::ObjectExtraInfo &extrainfo,
														const LbaNet::LifeManaInfo &lifeinfo,
														const LbaNet::ModelInfo & info)
: OsgObjectHandler(Tr, extrainfo, lifeinfo), 
	_currentanimationstring("Stand"), _paused(false), 
	_currentmodelinfo(info)
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
int AnimatedObjectHandlerBase::Update(LbaNet::DisplayObjectUpdateBasePtr update,
											bool updatestoredstate)
{
	const std::type_info& info = typeid(*update);

	// ModelUpdate
	if(info == typeid(LbaNet::ModelUpdate))
	{
		LbaNet::ModelUpdate * castedptr = 
			dynamic_cast<LbaNet::ModelUpdate *>(update.get());

		if(updatestoredstate)
		{
			_savedmodelinfo = castedptr->Info;
			return 0;
		}
		else
		{
			_currentmodelinfo = castedptr->Info;
			return UpdateModel();
		}
	}

	// AnimationStringUpdate
	if(info == typeid(LbaNet::AnimationStringUpdate))
	{
		LbaNet::AnimationStringUpdate * castedptr = 
			dynamic_cast<LbaNet::AnimationStringUpdate *>(update.get());

		if(updatestoredstate)
		{
			_savedanimationstring = castedptr->Animation;
			return 0;
		}
		else
		{
			if(_currentanimationstring != castedptr->Animation)
			{
				_currentanimationstring = castedptr->Animation;
				return UpdateAnimation();
			}
			else
				return 0;
		}
	}

	// PauseAnimationUpdate
	if(info == typeid(LbaNet::PauseAnimationUpdate))
	{
		if(updatestoredstate)
			_savedpaused = true;
		else
			_paused = true;

		return 0;
	}

	return OsgObjectHandler::Update(update, updatestoredstate);
}



/***********************************************************
get current model
***********************************************************/
LbaNet::ModelInfo AnimatedObjectHandlerBase::GetCurrentModel(bool storedstate)
{
	if(storedstate)
		return _savedmodelinfo;
	else
		return _currentmodelinfo;
}


/***********************************************************
save current model state
***********************************************************/
void AnimatedObjectHandlerBase::SaveState()
{
	_savedmodelinfo = _currentmodelinfo;
	_savedanimationstring = _currentanimationstring;
	_savedpaused = _paused;
}


/***********************************************************
restore previously saved model state
***********************************************************/
void AnimatedObjectHandlerBase::RestoreState()
{
	_currentmodelinfo = _savedmodelinfo;
	_currentanimationstring = _savedanimationstring;
	_paused = _savedpaused;

}