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
#include "MusicHandler.h"

#include <math.h>


/***********************************************************
	Constructor
***********************************************************/
ProjectileHandler::ProjectileHandler(boost::shared_ptr<DynamicObject> obje,
										const LbaNet::ProjectileInfo & Info,
										bool Manage,
										boost::shared_ptr<PhysicalObjectHandlerBase> ownerobj,
										float AngleOffset, const std::string &SoundAtStart,
										const std::string &SoundOnBounce)
: _obje(obje), _projInfo(Info), _Manage(Manage), _bounced(0), _ownerobj(ownerobj),
	_comingback(false), _launched(false), _AngleOffset(AngleOffset),
	_SoundAtStart(SoundAtStart), _SoundOnBounce(SoundOnBounce)
{
	//add force to object
	boost::shared_ptr<PhysicalObjectHandlerBase> physobj = _obje->GetPhysicalObject();
	if(physobj && _ownerobj)
	{
		physobj->IgnoreCollisionWith(ownerobj.get());
		physobj->EnableDisableGravity(false);
	}
	_obje->ShowOrHide(false);

	_startedball = SynchronizedTimeHandler::GetCurrentTimeDouble();
}

/***********************************************************
	Destructor
***********************************************************/
ProjectileHandler::~ProjectileHandler()
{
}


/***********************************************************
check if player is the owner
***********************************************************/
bool ProjectileHandler::IsPlayerOwner(long id)
{
	return ((_projInfo.OwnerActorType == 2) && (_projInfo.OwnerActorId == id));
}


/***********************************************************
do all check to be done when idle
***********************************************************/
bool ProjectileHandler::Process(double tnow, float tdiff)
{
	if(!_obje)
		return true;

	// check for delay launch
	if(!_launched)
	{
		if((_projInfo.Delay < 0) || ((tnow-_startedball) >= _projInfo.Delay))
		{
			_launched = true;
			_startedball = SynchronizedTimeHandler::GetCurrentTimeDouble();
			_obje->ShowOrHide(true);

			boost::shared_ptr<PhysicalObjectHandlerBase> physobj = _obje->GetPhysicalObject();
			if(physobj && _ownerobj)
			{
				LbaQuaternion Q;
				_ownerobj->GetRotation(Q);
				Q.AddSingleRotation(_AngleOffset, LbaVec3(0, 0, 1));

				LbaVec3 current_directionX(Q.GetDirection(LbaVec3(0, 0, 1)));

				float ajustedoffsetx = _projInfo.OffsetX*current_directionX.x;
				float ajustedoffsetz = _projInfo.OffsetX*current_directionX.z;

				float X, Y, Z;
				_ownerobj->GetPosition(X, Y, Z);
				physobj->SetPosition(X+ajustedoffsetx, Y+_projInfo.OffsetY, Z+ajustedoffsetz);

				if(!_projInfo.IgnoreGravity)
					physobj->EnableDisableGravity(true);

				physobj->AddForce(_projInfo.ForceX*current_directionX.x, _projInfo.ForceY, _projInfo.ForceX*current_directionX.z);
			
				//TODO - change to 3d sound
				if(_SoundAtStart != "")
					MusicHandler::getInstance()->PlaySample(_SoundAtStart, 0);
			}
		}

		return false;
	}



	float speedcomeback = 0.02f;
	_obje->Process(tnow, tdiff);

	// special case when ball come back
	if(_comingback)
	{
		float myposX, myposY, myposZ;
		_obje->GetPhysicalObject()->GetPosition(myposX, myposY, myposZ);
		
		float ownerposX, ownerposY, ownerposZ;
		_ownerobj->GetPosition(ownerposX, ownerposY, ownerposZ);
		ownerposY += _projInfo.OffsetY;

		float diffX = (ownerposX - myposX);
		float diffY = (ownerposY - myposY);
		float diffZ = (ownerposZ - myposZ);

		LbaVec3 moveV(diffX, diffY, diffZ);
		moveV.Normalize();

		float movex = moveV.x * tdiff * speedcomeback;
		float movey = moveV.y * tdiff * speedcomeback;
		float movez = moveV.z * tdiff * speedcomeback;	

		bool finishedx=false, finishedy=false, finishedz=false;

		if(abs(movex) >= abs(diffX))
		{
			movex = diffX;
			finishedx = true;
		}

		if(abs(movey) >= abs(diffY))
		{
			movey = diffY;
			finishedy = true;
		}

		if(abs(movez) >= abs(diffZ))
		{
			movez = diffZ;
			finishedz = true;
		}

		_obje->GetPhysicalObject()->Move(movex, movey, movez, false);	

		if(finishedx && finishedy && finishedz)
		{
			// inform server of destroy
			if(_Manage)
				EventsQueue::getSenderQueue()->AddEvent(new LbaNet::DestroyProjectileEvent(
													SynchronizedTimeHandler::GetCurrentTimeDouble(),
													_projInfo.Id, -1, -1));			

			return true;
		}

		return false;
	}




	bool destroy = false;
	int touchedactortype = -1;
	long touchedactorid = -1;
	float posYP = 0;

	//check user data for collision
	boost::shared_ptr<ActorUserData> userdata;
	boost::shared_ptr<PhysicalObjectHandlerBase> physobj = _obje->GetPhysicalObject();
	if(physobj)
	{
		float tmp1, tmp2;
		userdata = physobj->GetUserData();
		physobj->GetPosition(tmp1, posYP, tmp2);
	}

	if(userdata)
	{
		std::vector<HitInfo> hitted;
		userdata->GetHittedActors(hitted);	
		for(size_t cc=0; cc<hitted.size(); ++cc)
		{
			++_bounced;
			HitInfo &hiti = hitted[cc];
			if(hiti.ActorObjType == 1 || hiti.ActorObjType == 2)	
			{
				if(hiti.ActorPhysType != LbaNet::StaticAType)
				{
					//hitted something - destroy and inform hit
					destroy = true;
					touchedactortype = hiti.ActorObjType;
					touchedactorid = hiti.ActorId;
				}
			}

			if(!destroy)
			{
				//TODO - change to 3d sound
				if(_SoundOnBounce != "")
					MusicHandler::getInstance()->PlaySample(_SoundOnBounce, 0);

				physobj->AddForce(0, _projInfo.ForceYOnImpact, 0);
			}
		}
	} 


	// if bounced too much then destroy
	if(_bounced >= _projInfo.NbBounce)
		destroy = true;

	// check if time is up
	if((tnow-_startedball) > _projInfo.LifeTime)
		destroy = true;

	// if ball fall down too low
	if(posYP < -5)
		destroy = true;


	// destroy if needed
	if(destroy)
	{
		if(_projInfo.Comeback)
		{
			//replace physic by ghost
			boost::shared_ptr<PhysicalObjectHandlerBase> physo = _obje->GetPhysicalObject();
			if(physo)
			{
				LbaQuaternion Q;
				float myposX, myposY, myposZ;
				physo->GetPosition(myposX, myposY, myposZ);
				physo->GetRotation(Q);
				_obje->SetPhysicalObject(
					boost::shared_ptr<PhysicalObjectHandlerBase>(
					new SimplePhysicalObjectHandler(myposX, myposY, myposZ, Q)));
			}


			//make display half transparent
			boost::shared_ptr<DisplayObjectHandlerBase> diso = _obje->GetDisplayObject();
			if(diso)
				diso->Update(new LbaNet::ObjectAlphaColorUpdate(0.6f), false);


			// set come back flag
			_comingback = true;


			// inform server of touched actors
			if(touchedactorid >= 0)
			{
			// inform server of hit
				if(_Manage)
					EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ProjectileHittedActorEvent(
													SynchronizedTimeHandler::GetCurrentTimeDouble(),
													_projInfo.Id, touchedactortype, touchedactorid));	
			}
		}
		else
		{
			// inform server of destroy
			if(_Manage)
				EventsQueue::getSenderQueue()->AddEvent(new LbaNet::DestroyProjectileEvent(
													SynchronizedTimeHandler::GetCurrentTimeDouble(),
													_projInfo.Id, touchedactortype, touchedactorid));	

			return true;
		}
	}


	return false;
}