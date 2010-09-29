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
class CharacterController
{
public:
	//! constructor
	CharacterController();

	//! destructor
	~CharacterController();

	// set physcial character
	void SetPhysicalCharacter(boost::shared_ptr<DynamicObject> charac, 
								const LbaNet::ModelInfo &Info,
								bool AsGhost=false);


	//! key pressed
	void KeyPressed(LbanetKey keyid);

	//! key released
	void KeyReleased(LbanetKey keyid);

	//! process function
	void Process(double tnow, float tdiff);

	//! update player display
	void UpdateDisplay(LbaNet::DisplayObjectUpdateBasePtr update);

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
	boost::shared_ptr<DynamicObject>			_character;
	boost::shared_ptr<CharacterModeBase>		_currentmode;
	boost::shared_ptr<CharacterStateBase>		_currentstate;
	std::string									_currentmodestr;
	LbaNet::ModelState 							_currentstatestr;

	bool										_isGhost;

	bool										_keyforward;
	bool										_keybackward;
	bool										_keyleft;
	bool										_keyright;
	bool										_keyup;
	bool										_keydown;

	LbaNet::PlayerMoveInfo						_lastupdate;
	LbaNet::PlayerMoveInfo						_currentupdate;
	double										_lastupdatetime;
	float										_oldtdiff;

	// used for fall down check
	bool										_chefkiffall;
	float										_ycheckiffall;

};

#endif