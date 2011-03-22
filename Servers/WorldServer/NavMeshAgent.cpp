#include "NavMeshAgent.h"
#include "DetourCrowd.h"

/***********************************************************
constructor
***********************************************************/
NavMeshAgent::NavMeshAgent(boost::shared_ptr<dtCrowd> crowdcontroller,
							int agentid)
: m_crowdmanager(crowdcontroller), m_crowdagentid(agentid)
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