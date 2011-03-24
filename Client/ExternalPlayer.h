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
#include <fstream>

#include "DynamicObject.h"
#include "CharacterStates.h"
#include "CharacterModes.h"
#include "ScriptedActor.h"


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
	void Set(float posX, float posY, float posZ,
				float rotation, float velocityX, float velocityY,
				float velocityZ, float velocityR)
	{
		// keep last update
		_posX = posX;
		_posY = posY;
		_posZ = posZ;
		_rotation = rotation;


		_predicted_posX = posX;
		_predicted_posY = posY;
		_predicted_posZ = posZ;
		_predicted_rotation = rotation;


		_velocityX = velocityX;
		_velocityY = velocityY;
		_velocityZ = velocityZ;
		_velocityR = velocityR;
	}


	// calculate reackon prediction on each tick
	void Update(double tnow, float tdiff)
	{
		_predicted_posX += (_velocityX*tdiff);
		_predicted_posY += (_velocityY*tdiff);
		_predicted_posZ += (_velocityZ*tdiff);
		_predicted_rotation += (_velocityR*tdiff);

		while(_predicted_rotation > 360)
			_predicted_rotation -= 360;
		while(_predicted_rotation < 0)
			_predicted_rotation += 360;
	}

};


/*
************************************************************************************************************************
*                                                 class ExternalPlayer
************************************************************************************************************************
*/
class ExternalPlayer : public ScriptedActor
{
public:
	//constructor
	ExternalPlayer(boost::shared_ptr<DynamicObject> obje, 
								const LbaNet::ModelInfo &Info);

	//destructor
	~ExternalPlayer();

	// do all check to be done when idle
	virtual void Process(double tnow, float tdiff, 
					ScriptEnvironmentBase* scripthandler);

	// update with external info
	void UpdateMove(double updatetime, const LbaNet::PlayerMoveInfo &info, bool teleport);


	//! update player display
	void UpdateDisplay(LbaNet::DisplayObjectUpdateBasePtr update, bool updatefromlua);

	//! update player physic
	void UpdatePhysic(LbaNet::PhysicObjectUpdateBasePtr update);

	//! set the actor/player as playing script
	virtual void SetPlayingScript(bool playing);

	//! get actor position
	void GetPosition(float &X, float &Y, float &Z);

	//! get actor position
	float GetRotationYAxis();

	//! get rotation
	void GetRotation(LbaQuaternion& Q);

	//! update Mode
	void UpdateActorMode( const std::string & Mode, bool updatefromlua);

	//! update Model
	void UpdateActorModel(const std::string & Model, bool updatefromlua);

	//! update Model
	void UpdateActorOutfit(const std::string & Outfit, bool updatefromlua);

	//! update Model
	void UpdateActorWeapon(const std::string & Weapon, bool updatefromlua);

	//! update Model
	void SendSignal(int Signalnumber);

	//! get player current position
	void TeleportTo(float PosX, float PosY, float PosZ);

	//! set rotation
	void SetRotation(float angle);

	//! show/hide
	void ShowHide(bool Show);


	//! get physic object
	boost::shared_ptr<PhysicalObjectHandlerBase> GetPhysicalObject()
	{ return _character->GetPhysicalObject();}


protected:
	//! internaly update mode and state
	void UpdateModeAndState(const std::string &newmode,
								LbaNet::ModelState newstate);


	//! get display object
	boost::shared_ptr<DisplayObjectHandlerBase> GetDisplayObject()
	{ return _character->GetDisplayObject();}


protected:
	double										_last_update;

	float 										_velocityX;
	float 										_velocityY;
	float 										_velocityZ;
	float 										_velocityR;

	ExternalReckon								_dr;
	bool										_shouldupdate;

	boost::shared_ptr<CharacterModeBase>		_currentmode;
	boost::shared_ptr<CharacterStateBase>		_currentstate;
	bool										_playingscript;
	bool										_freemove;
};


#endif