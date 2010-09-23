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

#include "ExternalPlayer.h"
#include "SynchronizedTimeHandler.h"
#include "LogHandler.h"

#include <math.h>


/***********************************************************
	Constructor
***********************************************************/
ExternalPlayer::ExternalPlayer(boost::shared_ptr<DynamicObject> obje)
: _last_update(0), _obje(obje)
{
}

/***********************************************************
	Destructor
***********************************************************/
ExternalPlayer::~ExternalPlayer()
{
}


/***********************************************************
 update with external info
***********************************************************/
void ExternalPlayer::UpdateMove(double updatetime, const LbaNet::PlayerMoveInfo &info)
{
	if(updatetime > _last_update)
	{
		// update imediatly modifiable states
		_last_update = updatetime;

		boost::shared_ptr<PhysicalObjectHandlerBase> physo = _obje->GetPhysicalObject();


		_velocityX = info.CurrentSpeedX;
		_velocityY = info.CurrentSpeedY;
		_velocityZ = info.CurrentSpeedZ;
		_velocityR = info.CurrentSpeedRotation;

		if(_velocityX == 0 && _velocityY == 0 && _velocityZ == 0)
			physo->MoveTo(info.CurrentPosX,  info.CurrentPosY, info.CurrentPosZ);

		if(_velocityR == 0)
		{
			LbaQuaternion Q;
			Q.AddRotation(info.CurrentRotation, LbaVec3(0,1,0));
			physo->RotateTo(Q);
		}

		// update dead reckon for the rest
		_dr.Set(updatetime,
					info.CurrentPosX,  info.CurrentPosY, info.CurrentPosZ, info.CurrentRotation,
					info.CurrentSpeedX, info.CurrentSpeedY, info.CurrentSpeedZ, info.CurrentSpeedRotation);
	}
}



/***********************************************************
do all check to be done when idle
***********************************************************/
void ExternalPlayer::Process(double tnow, float tdiff)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _obje->GetPhysicalObject();

	// calculate prediction
	float predicted_posX, predicted_posY, predicted_posZ;
	physo->GetPosition(predicted_posX, predicted_posY, predicted_posZ);
	predicted_posX += (_velocityX*tdiff);
	predicted_posY += (_velocityY*tdiff);
	predicted_posZ += (_velocityZ*tdiff);


	float predicted_rotation = physo->GetRotationSingleAngle() + (_velocityR*tdiff);

	// calculate dead reckon
	_dr.Update(tnow);


	//// do interpolation X
	{
		float diffX = (_dr._predicted_posX - predicted_posX);
		if(fabs(diffX) > 8)
			predicted_posX = _dr._predicted_posX;
		else
			predicted_posX += diffX / 40;
	}


	//// do interpolation Y
	{
		float diffY = (_dr._predicted_posY - predicted_posY);
		if(fabs(diffY) > 8)
			predicted_posY = _dr._predicted_posY;
		else
			predicted_posY += diffY / 40;
	}


	//// do interpolation Z
	{
		float diffZ = (_dr._predicted_posZ - predicted_posZ);
		if(fabs(diffZ) > 8)
			predicted_posZ = _dr._predicted_posZ;
		else
			predicted_posZ += diffZ / 40;
	}


	//// do interpolation rotation
	{
		float diffR = (_dr._predicted_rotation - predicted_rotation);
		if(fabs(diffR) > 1)
			predicted_rotation = _dr._predicted_rotation;
		else
			predicted_rotation += diffR / 5;
	}


	physo->MoveTo(predicted_posX,  predicted_posY, predicted_posZ);
	LbaQuaternion Q;
	Q.AddRotation(predicted_rotation, LbaVec3(0,1,0));
	physo->RotateTo(Q);

	_obje->Process();
}