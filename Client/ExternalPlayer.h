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

#ifndef __LBA_EXTERNAL_PLAYER__
#define __LBA_EXTERNAL_PLAYER__

#include <boost/shared_ptr.hpp>
#include <map>
#include <ClientServerEvents.h>

#include "DynamicObject.h"


class ExternalReckon
{
public:

	double			_time;
	float			_posX;
	float			_posY;
	float			_posZ;
	float			_rotation;

	float			_velocityX;
	float			_velocityY;
	float			_velocityZ;
	float			_velocityR;


	float			_predicted_posX;
	float			_predicted_posY;
	float			_predicted_posZ;
	float			_predicted_rotation;

	// set reckon value
	void Set(const double & time, float posX, float posY, float posZ,
				float rotation, float velocityX, float velocityY,
				float velocityZ, float velocityR)
	{
		_time = time;

		_posX = posX;
		_posY = posY;
		_posZ = posZ;
		_rotation = rotation;

		_velocityX = velocityX;
		_velocityY = velocityY;
		_velocityZ = velocityZ;
		_velocityR = velocityR;
	}


	// calculate reackon prediction on each tick
	void Update(const double & currtime)
	{
		float tdiff = (float)(currtime - _time);

		_predicted_posX = _posX + (_velocityX*tdiff);
		_predicted_posY = _posY + (_velocityY*tdiff);
		_predicted_posZ = _posZ + (_velocityZ*tdiff);
		_predicted_rotation = _rotation + (_velocityR*tdiff);

		if(_predicted_rotation > 360)
			_predicted_rotation = _predicted_rotation - 360;
		if(_predicted_rotation < 0)
			_predicted_rotation = 360 + _predicted_rotation;
	}

};


/*
************************************************************************************************************************
*                                                 class ExternalPlayer
************************************************************************************************************************
*/
class ExternalPlayer
{
public:
	//constructor
	ExternalPlayer(boost::shared_ptr<DynamicObject> obje);

	//destructor
	~ExternalPlayer();

	// do all check to be done when idle
	void Process(double tnow, float tdiff);

	// update with external info
	void UpdateMove(double updatetime, const LbaNet::PlayerMoveInfo &info);


private:
	double									_last_update;

	boost::shared_ptr<DynamicObject>		_obje;

	float 									_velocityX;
	float 									_velocityY;
	float 									_velocityZ;
	float 									_velocityR;

	ExternalReckon							_dr;
};


#endif