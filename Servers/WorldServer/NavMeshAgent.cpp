#include "NavMeshAgent.h"
#include "DetourCrowd.h"

#include <Math.h>

/***********************************************************
constructor
***********************************************************/
NavMeshAgent::NavMeshAgent(boost::shared_ptr<dtCrowd> crowdcontroller,
							int agentid)
: m_crowdmanager(crowdcontroller), m_crowdagentid(agentid), m_lastSpeed(-1)
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
		speed[0] = SpeedX;
		speed[1] = SpeeY;
		speed[2] = SpeedZ;
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
			params.maxSpeed = Speed;
			m_crowdmanager->updateAgentParameters(m_crowdagentid, &params);
		}
	}
}