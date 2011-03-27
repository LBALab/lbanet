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

#ifndef _LBA_NAV_MESH_AGENT_H__
#define _LBA_NAV_MESH_AGENT_H__


#include <map>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class dtCrowd;
class NaviMeshHandler;
class LbaQuaternion;
class LbaVec3;

//! take care of navigation mesh agents
class NavMeshAgent
{
public:
	//! constructor
	NavMeshAgent(boost::shared_ptr<dtCrowd> crowdcontroller,
					boost::shared_ptr<NaviMeshHandler>	navimesh,
					int agentid);

	//! destructor
	~NavMeshAgent(void);


	//! get object position in the world
	void GetPosition(float &X, float &Y, float &Z);

	//! set object position in the world
	void SetPosition(float X, float Y, float Z);

	//! return agent angle
	bool GetAngle(float &angle);

	//! return current velocity
	LbaVec3 GetVelocity();

	//! show or hide the object
	void ShowOrHide(bool Show);

	//! UpdateSpeed
	void UpdateSpeed(float SpeedX, float SpeeY, float SpeedZ);

	//! UpdateMaxSpeed
	void UpdateMaxSpeed(float Speed);

	//! set/reset target
	void SetResetTarget(bool set);

	//! set target position
	void SetTargetPosition(bool update, float pX, float pY, float pZ);

	//! is targeting
	bool IsTargeting()
	{ return m_targeting;}

private:
	boost::shared_ptr<NaviMeshHandler>		m_navimesh;
	boost::shared_ptr<dtCrowd>				m_crowdmanager;
	int										m_crowdagentid;
	float									m_lastSpeed;
	bool									m_targeting;

	float									m_lasttx;
	float									m_lastty;
	float									m_lasttz;
};

#endif
