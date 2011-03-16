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
		_simpledialog(false), _npcnametextid(-1),
		_killable(false), _fighting(false), _attack_activation_distance(0),
		_attack_activation_distance_discrete(0), _dead(false),
		_attack_activation_distance_hidden(0), _respwantime(-1),
		_armor(0), _weapon1power(0), _weapon2power(0)
{
	_lifeinfo.MaxLife = 0;
	_lifeinfo.MaxMana = 0;
	_lifeinfo.CurrentLife = 0;
	_lifeinfo.CurrentMana = 0;
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
	if(_fighting) // should not happen when fighting
		return;

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
	if(_fighting) // cant activate if fighting
		return;

	if(ObjectMode != "Normal")
		return;

	boost::shared_ptr<PhysicalObjectHandlerBase> physO = _character->GetPhysicalObject();
	if(!physO)
		return;

	if(std::find(_targetedplayers.begin(), _targetedplayers.end(), PlayerId) != _targetedplayers.end())
		return;

	if(_rootdialog->GetChilds().size() == 0)
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


/***********************************************************
start fight
***********************************************************/
void NPCHandler::StartFight(Ice::Long TargetedPlayerId)
{
	// check if already fighting
	if(!_fighting) 
	{
		// set fighting flag
		_fighting = true;

		// pause script
		Pause();

		// if was talking to player, reset that
		if(_targetedplayers.size() > 0)
		{
			_events.push_back(new LbaNet::NpcUnTargetPlayerEvent(
								SynchronizedTimeHandler::GetCurrentTimeDouble(), 
								_targetedplayers[0]));

			_targetedplayers.clear();
		}

		// start action
		if(_action_on_attack_activation)
			_action_on_attack_activation->Execute(m_scripthandler, 2, TargetedPlayerId, NULL);
	}

	// add player to target vector
	if(std::find(_targetedplayers.begin(), _targetedplayers.end(), TargetedPlayerId) == _targetedplayers.end())
		_targetedplayers.push_back(TargetedPlayerId);

	// inform clients
	if(_targetedplayers.size() == 1)
		TargetAttackPlayer(TargetedPlayerId);
}


/***********************************************************
die
***********************************************************/
void NPCHandler::Die()
{
	if(_dead)
		return;

	//set dead flag
	_dead = true;

	//set die time
	_dietime = SynchronizedTimeHandler::GetCurrentTimeDouble();

	//hide
	ShowHideInternal(false);

	if(_hurtingplayers.size() > 0)
	{
		//todo - record player kill

		//todo - give item to player
	}

	// clear target
	_targetedplayers.clear();
	_hurtingplayers.clear();
}


/***********************************************************
respawn
***********************************************************/
void NPCHandler::Respawn()
{
	if(!_dead)
		return;

	//reset dead flag
	_dead = false;

	// remove fighting flag
	_fighting = false;

	// reset position - reset and start script
	ResetActor();

	// unhide
	ShowHideInternal(true);
}


/***********************************************************
process child
***********************************************************/
void NPCHandler::ProcessChild(double tnow, float tdiff)
{
	if(_killable && !_fighting)
	{
		//todo - target player that are too close
	}


	//if dead - respawn
	if(_dead && _respwantime >= 0)
	{
		if((tnow - _dietime) > _respwantime)
		{
			Respawn();
		}
	}
}


/***********************************************************
hurt life
***********************************************************/
void NPCHandler::HurtLife(float amount, bool UseArmor, Ice::Long HurtingPlayerId)
{
	if(!_killable)
		return;

	//remove armor
	if(UseArmor)
		amount += _armor;

	// if no hit then do nothing
	if(amount >= 0)
		return;


	//target hurting player
	if(HurtingPlayerId >= 0)
	{
		StartFight(HurtingPlayerId);

		// add to hurt list
		if(std::find(_hurtingplayers.begin(), _hurtingplayers.end(), HurtingPlayerId) == _hurtingplayers.end())
			_hurtingplayers.push_back(HurtingPlayerId);	
	}


	// if not invincible
	if(_lifeinfo.MaxLife > 0)
	{
		//substract life
		_lifeinfo.CurrentLife += amount;
		if(_lifeinfo.CurrentLife <= 0)
		{
			_lifeinfo.CurrentLife = 0;
			Die();
		}

		//todo - play hurt animation
	}
}

/***********************************************************
hurt mana
***********************************************************/
void NPCHandler::HurtMana(float amount)
{
	if(!_killable)
		return;

	// if not invincible
	if(_lifeinfo.MaxMana > 0)
	{
		// substract mana
		_lifeinfo.CurrentMana += amount;
		if(_lifeinfo.CurrentMana < 0)
			_lifeinfo.CurrentMana = 0;
	}
}


/***********************************************************
kill actor
***********************************************************/
void NPCHandler::Kill()
{
	if(!_killable)
		return;

	Die();
}



/***********************************************************
check trigger on player leave map
***********************************************************/
void NPCHandler::PlayerLeaveMap(Ice::Long PlayerId)
{
	if(!_killable || !_fighting)
		return;

	// remove from hurt list
	std::vector<Ice::Long>::iterator ith = 
		std::find(_hurtingplayers.begin(), _hurtingplayers.end(), PlayerId);
	if(ith != _hurtingplayers.end())
		_hurtingplayers.erase(ith);	


	// remove from target list
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
					TargetAttackPlayer(_targetedplayers[0]);
				else
					StopAttackTarget(PlayerId);
			}
			break;
		}
	}
}

/***********************************************************
check trigger on player dead
***********************************************************/
void NPCHandler::PlayerDead(Ice::Long PlayerId)
{
	// remove from targets on death
	PlayerLeaveMap(PlayerId);
}


/***********************************************************
target player
***********************************************************/
void NPCHandler::TargetAttackPlayer(Ice::Long PlayerId)
{
	//todo - inform client that npc target player
}


/***********************************************************
stop target player
***********************************************************/
void NPCHandler::StopAttackTarget(Ice::Long PlayerId)
{
	//todo - inform client that npc stop target player
}
