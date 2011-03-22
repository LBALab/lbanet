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


#ifndef __LBA_NET_NAVMESH_OBJECTS_HANDLERS_H__
#define __LBA_NET_NAVMESH_OBJECTS_HANDLERS_H__

#include <boost/shared_ptr.hpp>
#include "PhysicalObjectHandlerBase.h"

class PhysicalDescriptionBase;
class NavMeshAgent;

/***********************************************************************
 * Handler on a physX object
 ***********************************************************************/
class NavMeshObjectHandler : public SimplePhysicalObjectHandler
{
public:
	//! constructor
	NavMeshObjectHandler(boost::shared_ptr<NavMeshAgent> agent,
							float pX, float pY, float pZ,
							const LbaQuaternion& Q);

	//! destructor
	virtual ~NavMeshObjectHandler(){}

	//! process physic
	virtual void Process(double tnow, float tdiff,
							float animSpeedX, float animSpeedY, float animSpeedZ);


	//! get object position in the world
	virtual void GetPosition(float &X, float &Y, float &Z);


	//! set object position in the world
	virtual void SetPosition(float X, float Y, float Z);


	//! move object in the world
	virtual void Move(float deltaX, float deltaY, float deltaZ, bool checkcollision = true);

	//! move object to a position in the world
	virtual void MoveTo(float X, float Y, float Z);

	//! show or hide the object
	virtual void ShowOrHide(bool Show);


protected:
	boost::shared_ptr<NavMeshAgent>		_agent;
	float								_lasttdiff;
};


#endif