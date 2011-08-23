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

#include "ServerLba1ModelHandler.h"
#include "ServerLBA1ModelClass.h"
#include "Entities.h"
#include "Lba1ModelMapHandler.h"
#include "LogHandler.h"
#include <LbaTypes.h>
#include <typeinfo>


entitiesTableStruct* ServerLba1ModelHandler::_estruct = NULL;


/***********************************************************
Constructor
***********************************************************/
ServerLba1ModelHandler::ServerLba1ModelHandler(const LbaNet::ModelInfo & info, float animationspeed)
:  _model(NULL), _animationspeed(animationspeed),
	_currAnimation(-1), _currModel(-1), _currBody(-1), _paused(false), 
	_currentanimationstring("Stand"), _currentmodelinfo(info)
{
	if(_estruct == NULL)
		_estruct = parseEntities(Lba1ModelDataPath+"FILE3D.HQR");

	UpdateModel();
}


/***********************************************************
destructor
***********************************************************/
ServerLba1ModelHandler::~ServerLba1ModelHandler()
{
	// delete old model
	if(_model)
		delete _model;
}


/***********************************************************
update display with current frame - used for animation
***********************************************************/
int ServerLba1ModelHandler::Process(double time, float tdiff)
{
	bool animationfinished = false;

	if(!_paused && _model)
		animationfinished = _model->AnimateModel(tdiff);

	if(animationfinished)
		return 1;	// return 1 if animation is terminated
	else
		return 0;	// return 0 else
}

/***********************************************************
get current animation Id
***********************************************************/
std::string ServerLba1ModelHandler::GetCurrentAnimation()
{
	return _currentanimationstring;
}

/***********************************************************
get current associated speed
***********************************************************/
float ServerLba1ModelHandler::GetCurrentAssociatedSpeedX()
{
	if(_model)
		return (float)_model->GetCurrentSpeedX();

	return 0;
}

/***********************************************************
get current associated speed
***********************************************************/
float ServerLba1ModelHandler::GetCurrentAssociatedSpeedY()
{
	if(_model)
		return (float)_model->GetCurrentSpeedY();

	return 0;
}


/***********************************************************
get current associated speed
***********************************************************/
float ServerLba1ModelHandler::GetCurrentAssociatedSpeedZ()
{
	if(_model)
		return (float)_model->GetCurrentSpeedZ();

	return 0;
}



/***********************************************************
get current model
***********************************************************/
LbaNet::ModelInfo ServerLba1ModelHandler::GetCurrentModel()
{
	return _currentmodelinfo;
}

/***********************************************************
update model
***********************************************************/
int ServerLba1ModelHandler::UpdateModel()
{
	return RefreshModel(true);
}


/***********************************************************
update animation
***********************************************************/
int ServerLba1ModelHandler::UpdateAnimation()
{
	return RefreshModel();
}



/***********************************************************
update display
***********************************************************/
int ServerLba1ModelHandler::Update(LbaNet::DisplayObjectUpdateBasePtr update,
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


	return 0;
}


/***********************************************************
refresh model
***********************************************************/
int ServerLba1ModelHandler::RefreshModel(bool forcecolor)
{
	bool modelchanged = false;
	int newmodel=0;
	int newbody=0;
	std::vector<int> newanimations;
	int res = Lba1ModelMapHandler::getInstance()->GetModelInfo(	_currentmodelinfo.ModelName,
																_currentmodelinfo.Outfit,
																_currentmodelinfo.Weapon,
																_currentmodelinfo.Mode,
																_currentanimationstring,
																newmodel,
																newbody,
																newanimations);
	// model invalid or not existing
	if(res < 0)
		return res;



	// do nothing if same model loaded already
	if( forcecolor || (newmodel != _currModel) || (newbody != _currBody) ) 
	{
		std::stringstream strs;
		strs<<"Loading new lba1 model with entity "<<newmodel<<" and body "<<newbody<<std::endl;
		LogHandler::getInstance()->LogToFile(strs.str());

		// delete old model
		if(_model)
			delete _model;


		// reset current animation
		_currModel = newmodel;
		_currBody = newbody;
		_currAnimation = 0;

		_model = new ServerLBA1ModelClass(	_estruct, 
											Lba1ModelDataPath+"BODY.HQR", 
											Lba1ModelDataPath+"ANIM.HQR", 
											_currModel,
											_estruct->entitiesTable[_currModel].bodyList[_currBody].body);


		_model->SetAnimationSpeedFactor(_animationspeed);

		_model->LoadAnim(	_estruct,
							_estruct->entitiesTable[_currModel].animList[_currAnimation].index);

		_paused = false;
		modelchanged = true;
	}

	// do nothing if same animation loaded already
	if(_currAnimation != newanimations[0]) // TODO change to use animation vector
	{
		_currAnimation = newanimations[0];
		_model->LoadAnim(	_estruct,
							_estruct->entitiesTable[_currModel].animList[_currAnimation].index);

		_paused = false;
	}


	return 0;
}




/***********************************************************
save current model state
***********************************************************/
void ServerLba1ModelHandler::SaveState()
{
	_savedmodelinfo = _currentmodelinfo;
	_savedanimationstring = _currentanimationstring;
	_savedpaused = _paused;
}


/***********************************************************
restore previously saved model state
***********************************************************/
void ServerLba1ModelHandler::RestoreState()
{
	_currentmodelinfo = _savedmodelinfo;
	_currentanimationstring = _savedanimationstring;
	_paused = _savedpaused;
	RefreshModel();
}

/***********************************************************
get current model
***********************************************************/
LbaNet::ModelInfo ServerLba1ModelHandler::GetCurrentModel(bool storedstate)
{
	if(storedstate)
		return _savedmodelinfo;
	else
		return _currentmodelinfo;
}




/***********************************************************
check if can play animation
***********************************************************/
bool ServerLba1ModelHandler::CanPlayAnimation(const std::string & anim)
{
	return Lba1ModelMapHandler::getInstance()->CanPlayAnimation(	_currentmodelinfo.ModelName,
																	_currentmodelinfo.Outfit,
																	_currentmodelinfo.Weapon,
																	_currentmodelinfo.Mode,
																	anim);
}