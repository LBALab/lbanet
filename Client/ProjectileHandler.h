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

#ifndef __LBA_PROJECTILE_HANDLER__
#define __LBA_PROJECTILE_HANDLER__

#include <boost/shared_ptr.hpp>
#include <LbaTypes.h>
class DynamicObject;
class LbaNetModel;


#include "ActionOnAnimationHandlerBase.h"


struct LaunchedProjectile
{
	boost::shared_ptr<DynamicObject>		projobject;
	int										bounced;
	bool									comingback;

	double									launchedtime;
};


/*
************************************************************************************************************************
*                                                 class ProjectileHandler
************************************************************************************************************************
*/
class ProjectileHandler : public ActionOnAnimationHandlerBase
{
public:
	//constructor
	ProjectileHandler(LbaNetModel *	lbanetmodelH,
						const LbaNet::ProjectileInfo & Info, bool Manage,
						boost::shared_ptr<DynamicObject> ownerobj,
						float AngleOffset, const std::string &SoundAtStart,
						const std::string &SoundOnBounce);

	//destructor
	~ProjectileHandler();


	// do all check to be done when idle
	// return true if projectile should be destroyed
	virtual bool Process(double tnow, float tdiff);

	//! check if player is the owner
	bool IsPlayerOwner(long id);


	// execute the action
	virtual bool Execute();

	//! destroy projectile at next cycle
	void Destroy();

	//! clear projectile
	void Clear();


protected:
	//! launch proj
	void Launch();

private:
	LbaNet::ProjectileInfo							_projInfo;
	bool											_Manage;
	bool											_destroy;

	float											_AngleOffset;
	
	std::string										_SoundAtStart;
	std::string										_SoundOnBounce;

	std::vector<LaunchedProjectile>					_launchedobjects;

	LbaNetModel *									_lbanetmodelH;
};


#endif