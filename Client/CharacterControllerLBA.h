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

#if !defined(__LbaNetModel_1_CharacterController_h)
#define __LbaNetModel_1_CharacterController_h

#include <boost/shared_ptr.hpp>
#include "CommonTypes.h"
#include "ClientExtendedEvents.h"
#include "CharacterStates.h"
#include "CharacterModes.h"
#include "ScriptedActor.h"

#include <ClientServerEvents.h>

#include <map>
#include <fstream>

class PhysicalObjectHandlerBase;
class DynamicObject;




/***********************************************************************
 * Module:  CharacterController.h
 * Author:  vivien
 * Modified: mardi 14 juillet 2009 17:41:03
 * Purpose: Declaration of the class CharacterController
 ***********************************************************************/
class CharacterController : public ScriptedActor
{
public:
	//! constructor
	CharacterController();

	//! destructor
	virtual ~CharacterController();

	// set physcial character
	void SetPhysicalCharacter(boost::shared_ptr<DynamicObject> charac, 
								const LbaNet::ModelInfo &Info,
								bool AsGhost=false);


	//! key pressed
	void KeyPressed(LbanetKey keyid);

	//! key released
	void KeyReleased(LbanetKey keyid);

	//! process function
	void Process(double tnow, float tdiff, 
					ScriptEnvironmentBase* scripthandler);

	//! update player display
	void UpdateDisplay(LbaNet::DisplayObjectUpdateBasePtr update);

	//! update player physic
	void UpdatePhysic(LbaNet::PhysicObjectUpdateBasePtr update);

	//! server teleport player
	void Teleport(const LbaNet::PlayerMoveInfo &info);

	#ifdef _USE_QT_EDITOR_
	//! force the camera in ghost mode or not
	void ForceGhost(bool force)
	{
		_forcedghost = force;
	}
	#endif

	//! get player current position
	void GetPosition(float & PosX, float & PosY, float & PosZ);

	//! get player current rotation
	float GetRotation();

	//! get player current rotation
	LbaQuaternion GetRotationQuat();

	//! used by lua to update animation
	void UpdateAnimation(const std::string & AnimationString);

	//! update Mode
	void UpdateActorMode(const std::string & Mode );


	//! update Model
	void UpdateActorModel(const std::string & Model);

	//! update Model
	void UpdateActorOutfit(const std::string & Outfit);

	//! update Model
	void UpdateActorWeapon(const std::string & Weapon);

	//! update Model
	void SendSignal(int Signalnumber);

	//! get player current position
	void TeleportTo(float PosX, float PosY, float PosZ);

	//! set rotation
	void SetRotation(float angle);


protected:

	//! check if we need to send update to server
	void UpdateServer(double tnow, float tdiff);

	//! check if we should force the update
	bool ShouldforceUpdate();

	//! internaly update mode and state
	void UpdateModeAndState(const std::string &newmode,
								LbaNet::ModelState newstate,
								double tnow,
								float FallingSize = 0);


private:
	boost::shared_ptr<CharacterModeBase>		_currentmode;
	boost::shared_ptr<CharacterStateBase>		_currentstate;
	std::string									_currentmodestr;

	bool										_isGhost;
	bool										_forcedghost;

	CharKeyPressed								_pressedkeys;

	LbaNet::PlayerMoveInfo						_lastupdate;
	LbaNet::PlayerMoveInfo						_currentupdate;
	double										_lastupdatetime;
	float										_oldtdiff;

	// used for fall down check
	bool										_chefkiffall;
	float										_ycheckiffall;

};

#endif