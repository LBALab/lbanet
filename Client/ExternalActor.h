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

#ifndef __LBA_EXTERNAL_ACTOR__
#define __LBA_EXTERNAL_ACTOR__

#include "ExternalPlayer.h"


/*
************************************************************************************************************************
*                                                 class ExternalPlayer
************************************************************************************************************************
*/
class ExternalActor : public ExternalPlayer
{
public:
	//constructor
	ExternalActor(boost::shared_ptr<DynamicObject> obje, 
								const LbaNet::ModelInfo &Info);

	//destructor
	~ExternalActor();


	//! when update npc position
	void NpcChangedUpdate(double updatetime, 
									float CurrPosX, float CurrPosY, float CurrPosZ,
									float CurrRotation, const std::string &CurrAnimation,
									bool ResetPosition, bool ResetRotation,
									LbaNet::NpcUpdateBasePtr Update);


	// do all check to be done when idle
	virtual void Process(double tnow, float tdiff, 
					ScriptEnvironmentBase* scripthandler);

	//! set the actor/player as playing script
	virtual void SetPlayingScript(bool playing);

	//! target object
	void Target(boost::shared_ptr<PhysicalObjectHandlerBase> object);

	//! untarget
	void UnTarget();

private:
	boost::shared_ptr<ScriptPartBase>			_currentScripts;
	float										_differencePosX;
	float										_differencePosY;
	float										_differencePosZ;
	float										_differenceRotation;


	bool										_shouldreset;

	bool										_targetting;
	boost::shared_ptr<ScriptPartBase>			_targetsavedScripts;
	float										_targetsavedangle;

};


#endif