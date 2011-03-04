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
class PhysicalObjectHandlerBase;


/*
************************************************************************************************************************
*                                                 class ProjectileHandler
************************************************************************************************************************
*/
class ProjectileHandler
{
public:
	//constructor
	ProjectileHandler(boost::shared_ptr<DynamicObject> obje,
						const LbaNet::ProjectileInfo & Info,
						bool Manage,
						boost::shared_ptr<PhysicalObjectHandlerBase> ownerobj);

	//destructor
	~ProjectileHandler();


	// do all check to be done when idle
	// return true if projectile should be destroyed
	virtual bool Process(double tnow, float tdiff);

	//! check if player is the owner
	bool IsPlayerOwner(long id);

private:
	boost::shared_ptr<DynamicObject>	_obje;
	 LbaNet::ProjectileInfo				_projInfo;
	 bool								_Manage;
	 int								_bounced;
	 bool								_comingback;

	 boost::shared_ptr<PhysicalObjectHandlerBase>	_ownerobj;
};


#endif