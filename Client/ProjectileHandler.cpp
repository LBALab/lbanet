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
#include "LbaNetModel.h"


#include <math.h>


/***********************************************************
	Constructor
***********************************************************/
ProjectileHandler::ProjectileHandler(LbaNetModel *	lbanetmodelH,
										const LbaNet::ProjectileInfo & Info, bool Manage,
										boost::shared_ptr<DynamicObject> ownerobj,
										float AngleOffset, const std::string &SoundAtStart,
										const std::string &SoundOnBounce)
: _projInfo(Info), _Manage(Manage), _ownerobj(ownerobj), _AngleOffset(AngleOffset),
	_SoundAtStart(SoundAtStart), _SoundOnBounce(SoundOnBounce), _lbanetmodelH(lbanetmodelH),
	_destroy(false)
{
	if(Info.StartAnimFrame > 0 && _ownerobj)
		_ownerobj->AddActionOnAnimation(Info.StartAnimFrame, this); //wait for anim to launch
	else
		Execute(); // launch directly
}

/***********************************************************
	Destructor
***********************************************************/
ProjectileHandler::~ProjectileHandler()
{
	Clear();
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
	// do nothing if no launched projectiles
	if(_launchedobjects.size() == 0)
		return false;

	float speedcomeback = 0.02f;


	std::vector<LaunchedProjectile>::iterator itp = _launchedobjects.begin();

	while(itp != _launchedobjects.end())
	{
		itp->projobject->Process(tnow, tdiff);

		boost::shared_ptr<PhysicalObjectHandlerBase> physobj = itp->projobject->GetPhysicalObject();
		boost::shared_ptr<PhysicalObjectHandlerBase> ownerphysobj = _ownerobj->GetPhysicalObject();
		if(itp->comingback)
		{
			float myposX, myposY, myposZ;
			physobj->GetPosition(myposX, myposY, myposZ);
			
			float ownerposX, ownerposY, ownerposZ;
			ownerphysobj->GetPosition(ownerposX, ownerposY, ownerposZ);
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

			physobj->Move(movex, movey, movez, false);	

			if(finishedx && finishedy && finishedz)
			{
				// inform server of destroy
				if(_Manage && ((_destroy && (_launchedobjects.size() == 1)) || !_projInfo.MultiShoot))
					EventsQueue::getSenderQueue()->AddEvent(new LbaNet::DestroyProjectileEvent(
														SynchronizedTimeHandler::GetCurrentTimeDouble(),
														_projInfo.Id, -1, -1));		


				itp = _launchedobjects.erase(itp);

				if(!_projInfo.MultiShoot)
					return true;
			}
			else
				++itp;
		}
		else
		{
			bool destroy = false;
			int touchedactortype = -1;
			long touchedactorid = -1;
			float posYP = 0;

			//check user data for collision
			boost::shared_ptr<ActorUserData> userdata;
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
					++itp->bounced;
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
							MusicHandler::getInstance()->PlaySample("Data/"+_SoundOnBounce, 0);

						physobj->AddForce(0, _projInfo.ForceYOnImpact, 0);
					}
				}
			} 


			// if bounced too much then destroy
			if(itp->bounced >= _projInfo.NbBounce)
				destroy = true;

			// check if time is up
			if((tnow-itp->launchedtime) > _projInfo.LifeTime)
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
					if(physobj)
					{
						LbaQuaternion Q;
						float myposX, myposY, myposZ;
						physobj->GetPosition(myposX, myposY, myposZ);
						physobj->GetRotation(Q);
						itp->projobject->SetPhysicalObject(
							boost::shared_ptr<PhysicalObjectHandlerBase>(
							new SimplePhysicalObjectHandler(myposX, myposY, myposZ, Q)));
					}


					//make display half transparent
					boost::shared_ptr<DisplayObjectHandlerBase> diso = itp->projobject->GetDisplayObject();
					if(diso)
						diso->Update(new LbaNet::ObjectAlphaColorUpdate(0.6f), false);


					// set come back flag
					itp->comingback = true;


					// inform server of touched actors
					if(touchedactorid >= 0)
					{
						// inform server of hit
						if(_Manage)
							EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ProjectileHittedActorEvent(
															SynchronizedTimeHandler::GetCurrentTimeDouble(),
															_projInfo.Id, touchedactortype, touchedactorid));	
					}

					++itp;
				}
				else
				{
					// inform server of destroy
					if(_Manage)
					{
						if(_projInfo.MultiShoot && (!_destroy || (_launchedobjects.size() > 1)))
						{
							EventsQueue::getSenderQueue()->AddEvent(new LbaNet::ProjectileHittedActorEvent(
															SynchronizedTimeHandler::GetCurrentTimeDouble(),
															_projInfo.Id, touchedactortype, touchedactorid));

							itp = _launchedobjects.erase(itp);	
						}
						else
						{
							EventsQueue::getSenderQueue()->AddEvent(new LbaNet::DestroyProjectileEvent(
															SynchronizedTimeHandler::GetCurrentTimeDouble(),
															_projInfo.Id, touchedactortype, touchedactorid));

							itp = _launchedobjects.erase(itp);	
							return true;
						}
					}					
				}
			}
			else
				++itp;
		}
	}


	return !_projInfo.MultiShoot && _destroy;
}

/***********************************************************
check if player is the owner
***********************************************************/
void ProjectileHandler::Launch()
{
	if(!_lbanetmodelH|| !_ownerobj)
		return;

	// create new proj
	LaunchedProjectile newproj;
	newproj.projobject = _lbanetmodelH->CreateProjectileObject(_projInfo);
	newproj.bounced = 0;
	newproj.comingback = false;
	newproj.launchedtime = SynchronizedTimeHandler::GetCurrentTimeDouble();

	//add force to object
	boost::shared_ptr<PhysicalObjectHandlerBase> physobj = newproj.projobject->GetPhysicalObject();
	boost::shared_ptr<PhysicalObjectHandlerBase> ownerphysobj = _ownerobj->GetPhysicalObject();
	if(physobj && ownerphysobj)
	{
		physobj->IgnoreCollisionWith(ownerphysobj.get());
		physobj->EnableDisableGravity(!_projInfo.IgnoreGravity);

		LbaQuaternion Q;
		ownerphysobj->GetRotation(Q);
		LbaQuaternion Qoffset(_AngleOffset, LbaVec3(0, 1, 0));
		LbaQuaternion resQ(Q*Qoffset);

		//std::cout<<Q.GetRotationSingleAngle()<<" "<<Q.W<<" "<<Q.Y<<std::endl;

		LbaVec3 current_directionX(resQ.GetDirection(LbaVec3(0, 0, 1)));

		float ajustedoffsetx = _projInfo.OffsetX*current_directionX.x;
		float ajustedoffsetz = _projInfo.OffsetX*current_directionX.z;

		float X, Y, Z;
		ownerphysobj->GetPosition(X, Y, Z);
		physobj->SetPosition(X+ajustedoffsetx, Y+_projInfo.OffsetY, Z+ajustedoffsetz);


		physobj->AddForce(_projInfo.ForceX*current_directionX.x, _projInfo.ForceY, _projInfo.ForceX*current_directionX.z);
	
		//TODO - change to 3d sound
		if(_SoundAtStart != "")
			MusicHandler::getInstance()->PlaySample("Data/"+_SoundAtStart, 0);
	}

	// add to projs list
	_launchedobjects.push_back(newproj);
}


/***********************************************************
execute the action
***********************************************************/
bool ProjectileHandler::Execute()
{
	if(!_projInfo.MultiShoot && _launchedobjects.size() > 0)
		return true;

	Launch();

	return (_destroy || !_projInfo.MultiShoot);
}


/***********************************************************
clear projectile
***********************************************************/
void ProjectileHandler::Clear()
{
	// stop owner to spawn projectiles
	if(_projInfo.StartAnimFrame > 0 && _ownerobj)
		_ownerobj->RemoveActionOnAnimation(_projInfo.StartAnimFrame, this);

	// clear launched projs
	_launchedobjects.clear();

	// clear owner object
	_ownerobj = boost::shared_ptr<DynamicObject>();
}


/***********************************************************
destroy projectile at next cycle
***********************************************************/
void ProjectileHandler::Destroy()
{
	_destroy = true;
}