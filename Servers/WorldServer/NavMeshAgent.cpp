#include "NavMeshAgent.h"
#include "DetourCrowd.h"
#include "NaviMeshHandler.h"
#include "DetourNavMeshQuery.h"
#include "CommonTypes.h"

#include <Math.h>


/***********************************************************
constructor
***********************************************************/
NavMeshAgent::NavMeshAgent(boost::shared_ptr<dtCrowd> crowdcontroller,
							boost::shared_ptr<NaviMeshHandler>	navimesh,
							int agentid)
: m_crowdmanager(crowdcontroller), m_navimesh(navimesh),
	m_crowdagentid(agentid), m_lastSpeed(-1), m_targeting(false)
{

}


/***********************************************************
destructor
***********************************************************/
NavMeshAgent::~NavMeshAgent(void)
{
	if(m_crowdmanager)
		m_crowdmanager->removeAgent(m_crowdagentid);
}


/***********************************************************
get object position in the world
***********************************************************/
void NavMeshAgent::GetPosition(float &X, float &Y, float &Z)
{
	if(m_crowdmanager)
	{
		const dtCrowdAgent* dtagent = m_crowdmanager->getAgent(m_crowdagentid);
		if(dtagent)
		{
			X = dtagent->npos[0];
			Y = dtagent->npos[1];
			Z = dtagent->npos[2];
		}
	}
}

/***********************************************************
set object position in the world
***********************************************************/
void NavMeshAgent::SetPosition(float X, float Y, float Z)
{
	if(m_crowdmanager)
	{
		const dtCrowdAgent* dtagent = m_crowdmanager->getAgent(m_crowdagentid);
		if(dtagent)
		{
			dtCrowdAgentParams params;
			memcpy(&params, &dtagent->params, sizeof(dtCrowdAgentParams));

			m_crowdmanager->removeAgent(m_crowdagentid);

			float pos[3];
			pos[0] = X;
			pos[1] = Y;
			pos[2] = Z;
			m_crowdagentid = m_crowdmanager->addAgent(pos, &params);
		}
	}
}

/***********************************************************
show or hide the object
***********************************************************/
void NavMeshAgent::ShowOrHide(bool Show)
{
	//todo - show or hide agent on nav mesh
}

/***********************************************************
UpdateSpeed
***********************************************************/
void NavMeshAgent::UpdateSpeed(float SpeedX, float SpeeY, float SpeedZ)
{
	if(m_crowdmanager)
	{
		float speed[3];
		speed[0] = SpeedX*1000;
		speed[1] = SpeeY*1000;
		speed[2] = SpeedZ*1000;
		m_crowdmanager->requestMoveVelocity(m_crowdagentid, speed);
	}
}


/***********************************************************
UpdateMaxSpeed
***********************************************************/
void NavMeshAgent::UpdateMaxSpeed(float Speed)
{
	//only update if changed
	float diff = fabs(m_lastSpeed-Speed);
	if(diff < 0.00001)
		return;

	m_lastSpeed = Speed;

	if(m_crowdmanager)
	{
		const dtCrowdAgent* dtagent = m_crowdmanager->getAgent(m_crowdagentid);
		if(dtagent)
		{
			dtCrowdAgentParams params;
			memcpy(&params, &dtagent->params, sizeof(dtCrowdAgentParams));
			params.maxSpeed = Speed*1000;
			m_crowdmanager->updateAgentParameters(m_crowdagentid, &params);
		}
	}
}


/***********************************************************
set/reset target
***********************************************************/
void NavMeshAgent::SetResetTarget(bool set)
{
	if(m_crowdmanager)
	{
		m_crowdmanager->requestSetResetTarget(m_crowdagentid, set);
		m_targeting = set;
	}
}


/***********************************************************
set target position
***********************************************************/
void NavMeshAgent::SetTargetPosition(bool update, float pX, float pY, float pZ)
{
	if(m_crowdmanager)
	{
		float pos[3], respos[3];
		pos[0] = pX;
		pos[1] = pY;
		pos[2] = pZ;

		// Find nearest point on navmesh and set move request to that location.
		dtNavMeshQuery* navquery = m_navimesh->getNavMeshQuery();
		if(navquery)
		{
			const dtQueryFilter* filter = m_crowdmanager->getFilter();
			const float* ext = m_crowdmanager->getQueryExtents();
			dtPolyRef m_targetRef;
			navquery->findNearestPoly(pos, ext, filter, &m_targetRef, respos);

			if(update)
				m_crowdmanager->adjustMoveTarget(m_crowdagentid, m_targetRef, respos);
			else
				m_crowdmanager->requestMoveTarget(m_crowdagentid, m_targetRef, respos);
		}
	}
}


/***********************************************************
return agent angle
***********************************************************/
float NavMeshAgent::GetAngle()
{
	if(m_crowdmanager)
	{
		const dtCrowdAgent* agent = m_crowdmanager->getAgent(m_crowdagentid);
		if(agent)
		{
			LbaVec3 velvec(agent->vel[0], agent->vel[1], agent->vel[2]);
			return LbaQuaternion::GetAngleFromVector(velvec);
		}
	}
	
	return 0;
}