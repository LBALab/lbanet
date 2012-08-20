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

#if !defined(__LbaNetModel_1_CameraController_h)
#define __LbaNetModel_1_CameraController_h

#include <boost/shared_ptr.hpp>
#include "CommonTypes.h"
#include "CharacterModes.h"
#include "ClientExtendedEvents.h"

class DynamicObject;


/***********************************************************************
 * Module:  CameraController.h
 * Author:  vivien
 * Modified: mardi 14 juillet 2009 17:41:03
 * Purpose: Declaration of the class CameraController
 ***********************************************************************/
class CameraController
{
public:
	//! constructor
	CameraController();

	//! destructor
	~CameraController();

	//! set character to control
	void SetCharacter(boost::shared_ptr<DynamicObject> charac, bool AsGhost=false);

	//! process function
	void Process(double tnow, float tdiff);

	// center camera on player
	void Center();

	//! force the camera in ghost mode or not
	void ForceGhost(bool force)
	{
		_forcedghost = force;
	}


	//! key pressed
	void KeyPressed(LbanetKey keyid);

	//! key released
	void KeyReleased(LbanetKey keyid);

private:
	boost::shared_ptr<DynamicObject> _character;

	bool											_isGhost;
	bool											_forcedghost;

	// camera internal info
	double											_lastactX;
	double											_lastactY;
	double											_lastactZ;
	bool											_movecamera;

	CharKeyPressed									_pressedkeys;
};

#endif