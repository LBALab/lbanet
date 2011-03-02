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

#include "ProjectileHandler.h"
#include "SynchronizedTimeHandler.h"
#include "EventsQueue.h"

#include "DynamicObject.h"
#include "PhysicalObjectHandlerBase.h"
#include "ActorUserData.h"

#include <math.h>


/***********************************************************
	Constructor
***********************************************************/
ProjectileHandler::ProjectileHandler(boost::shared_ptr<DynamicObject> obje,
										const LbaNet::ProjectileInfo & Info,
										bool Manage)
: _obje(obje), _projInfo(Info), _Manage(Manage), _bounced(0)
{
	//add force to object
	boost::shared_ptr<PhysicalObjectHandlerBase> physobj = _obje->GetPhysicalObject();
	if(physobj)
		physobj->AddForce(Info.ForceX, Info.ForceY, Info.ForceZ);
}

/***********************************************************
	Destructor
***********************************************************/
ProjectileHandler::~ProjectileHandler()
{
}


/***********************************************************
do all check to be done when idle
***********************************************************/
bool ProjectileHandler::Process(double tnow, float tdiff)
{
	if(!_obje)
		return true;

	_obje->Process(tnow, tdiff);

	bool destroy = false;
	int touchedactortype = -1;
	long touchedactorid = -1;

	//check user data for collision
	boost::shared_ptr<ActorUserData> userdata;
	boost::shared_ptr<PhysicalObjectHandlerBase> physobj = _obje->GetPhysicalObject();
	if(physobj)
		userdata = physobj->GetUserData();

	if(userdata)
	{
		std::vector<HitInfo> hitted;
		userdata->GetHittedActors(hitted);	
		for(size_t cc=0; cc<hitted.size(); ++cc)
		{
			++_bounced;
			HitInfo &hiti = hitted[cc];
			if(hiti.ActorObjType == LbaNet::NpcObject || hiti.ActorObjType == LbaNet::PlayerObject)	
			{
				if(hiti.ActorPhysType != LbaNet::StaticAType)
				{
					//hitted something - destroy and inform hit
					destroy = true;
					touchedactortype = hiti.ActorObjType;
					touchedactorid = hiti.ActorId;
				}
			}
		}
	} 


	// if bounced too much then destroy
	if(_bounced >= _projInfo.NbBounce)
		destroy = true;


	// destroy if needed
	if(destroy)
	{
		if(_Manage)
		{
			EventsQueue::getSenderQueue()->AddEvent(new LbaNet::DestroyProjectileEvent(
												SynchronizedTimeHandler::GetCurrentTimeDouble(),
												_projInfo.Id, touchedactortype, touchedactorid));		
		}

		return true;
	}


	return false;
}