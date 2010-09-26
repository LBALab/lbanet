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

#include "Lba1ModelHandler.h"
#include "LBA1ModelClass.h"


/***********************************************************
Constructor
***********************************************************/
Lba1ModelHandler::Lba1ModelHandler(const LbaNet::ModelInfo & info, float animationspeed)
: _model(NULL), _animationspeed(animationspeed)
{
	UpdateModel(info);
}

/***********************************************************
destructor
***********************************************************/
Lba1ModelHandler::~Lba1ModelHandler()
{
}

/***********************************************************
update display with current frame - used for animation
***********************************************************/
void Lba1ModelHandler::Process(double time, float tdiff)
{

}

/***********************************************************
get current animation Id
***********************************************************/
int Lba1ModelHandler::GetCurrentAnimation()
{
	if(_model)
		return _model->GetCurrentSpeedX();

	return 0;
}

/***********************************************************
get current associated speed
***********************************************************/
float Lba1ModelHandler::GetCurrentAssociatedSpeedX()
{
	if(_model)
		return _model->GetCurrentSpeedX();

	return 0;
}

/***********************************************************
get current associated speed
***********************************************************/
float Lba1ModelHandler::GetCurrentAssociatedSpeedY()
{
	if(_model)
		return _model->GetCurrentSpeedY();

	return 0;
}


/***********************************************************
get current associated speed
***********************************************************/
float Lba1ModelHandler::GetCurrentAssociatedSpeedZ()
{
	if(_model)
		return _model->GetCurrentSpeedZ();

	return 0;
}

/***********************************************************
update model
***********************************************************/
void Lba1ModelHandler::UpdateModel(const LbaNet::ModelInfo & info)
{
	if(_model)
		delete _model;

	//_model = new LBA1ModelClass(_estruct, "BODY.HQR", "ANIM.HQR", _currmodel,
	//									_estruct->entitiesTable[_currmodel].bodyList[_currbody].body);



	//_model->SetAnimationSpeedFactor(_animationspeed);

	//_model->LoadAnim(_estruct,
	//	_estruct->entitiesTable[_currmodel].animList[_curranim].index);

	//osg::ref_ptr<osg::Node> node = _model->ExportOSGModel();
}


/***********************************************************
update animation
***********************************************************/
void Lba1ModelHandler::UpdateAnimation(const std::string & AnimString)
{

}

/***********************************************************
update animation
***********************************************************/
void Lba1ModelHandler::UpdateAnimation(int AnimIdx)
{

}