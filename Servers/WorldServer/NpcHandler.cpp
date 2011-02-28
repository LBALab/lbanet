#include "NpcHandler.h"
#include "DynamicObject.h"
#include "ScriptEnvironmentBase.h"
#include "SynchronizedTimeHandler.h"

#include <math.h>
#include <fstream>


/***********************************************************
update position of the script
***********************************************************/
NPCHandler::NPCHandler(const ActorObjectInfo & actorinfo)
	: ActorHandler(actorinfo), _rootdialog(new DialogPart()),
		_simpledialog(false), _npcnametextid(-1)
{
	
}

/***********************************************************
return the build class
***********************************************************/
std::string NPCHandler::LuaBuildClass()
{
	std::stringstream res;
	res<<"NPCHandler(Actor_"<<m_actorinfo.ObjectId<<")";

	return res.str();
}



/***********************************************************
write extra lua
***********************************************************/
void NPCHandler::ExtraLua(std::ofstream & file, const std::string & name)
{
	std::stringstream named;
	named<<name<<"_dia";
	_rootdialog->SaveToLuaFile(file, named.str());

	file<<"\t"<<name<<":SetRootDialog("<<named.str()<<")"<<std::endl;
	file<<"\t"<<name<<":SetNpcName("<<_npcnametextid<<")"<<std::endl;
	file<<"\t"<<name<<":SetSimpleDialog("<<(_simpledialog?"true":"false")<<")"<<std::endl;
}


/***********************************************************
UntargetPlayer
***********************************************************/
void NPCHandler::UntargetPlayer(Ice::Long PlayerId)
{
	std::vector<Ice::Long>::iterator it = _targetedplayers.begin();
	std::vector<Ice::Long>::iterator end = _targetedplayers.end();
	for(int cc=0; it != end; ++it, ++cc)
	{
		if(*it == PlayerId)
		{
			_targetedplayers.erase(it);

			if(cc == 0)
			{
				if(_targetedplayers.size() > 0)
					TargetPlayer(_targetedplayers[0]);
				else
					StopTarget();
			}
			break;
		}
	}
}



/***********************************************************
check trigger on object action
***********************************************************/
void NPCHandler::PlayerAction(Ice::Long PlayerId, const LbaNet::PlayerPosition &info,
									const std::string &ObjectMode)
{
	if(ObjectMode != "Normal")
		return;

	boost::shared_ptr<PhysicalObjectHandlerBase> physO = _character->GetPhysicalObject();
	if(!physO)
		return;

	if(std::find(_targetedplayers.begin(), _targetedplayers.end(), PlayerId) != _targetedplayers.end())
		return;


	float posX, posY, posZ;
	physO->GetPosition(posX, posY, posZ);

	float diffX = (info.X - posX);
	float diffY = (info.Y - posY);
	float diffZ = (info.Z - posZ);

	float distance = (diffX*diffX) + (diffY*diffY) + (diffZ*diffZ);
	if(distance <= 9)
	{
		LbaVec3 lvec(-diffX, -diffY, -diffZ);
		float angle = LbaQuaternion::GetAngleFromVector(lvec);
		float angle1a = (angle - 50);
		float angle1b = (angle - 50);

		float angle2a = (angle + 50);
		float angle2b = (angle + 50);



		if(angle1a < 0)
		{
			angle1a += 360;
			angle2a += 360;
			angle1b = 0;		
		}

		if(angle2b > 360)
		{
			angle1b -= 360;
			angle2b -= 360;
			angle2a = 360;
		}

		if(	((info.Rotation > angle1a) && (info.Rotation < angle2a)) ||
			((info.Rotation > angle1b) && (info.Rotation < angle2b)) )
		{
			// start dialog
			if(m_scripthandler)
				m_scripthandler->StartDialog((long)PlayerId, m_actorinfo.ObjectId, 
										_npcnametextid, _simpledialog, _rootdialog);

			// target player
			_targetedplayers.push_back(PlayerId);
			if(_targetedplayers.size() == 1)
				TargetPlayer(PlayerId);
		}
	}
}



/***********************************************************
target player
***********************************************************/
void NPCHandler::TargetPlayer(Ice::Long PlayerId)
{
	Pause();

	_events.push_back(new LbaNet::NpcTargetPlayerEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), 
						m_actorinfo.ObjectId, PlayerId));
}


/***********************************************************
stop target player
***********************************************************/
void NPCHandler::StopTarget()
{
	Resume();

	_events.push_back(new LbaNet::NpcUnTargetPlayerEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), 
						m_actorinfo.ObjectId));
}