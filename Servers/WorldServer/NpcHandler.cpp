#include "NpcHandler.h"
#include "DynamicObject.h"
#include "ScriptEnvironmentBase.h"
#include "SynchronizedTimeHandler.h"
#include "Randomizer.h"
#include "InventoryItemHandler.h"
#include "CharacterStates.h"
#include "NavMeshAgent.h"

#include <math.h>
#include <fstream>


/***********************************************************
update position of the script
***********************************************************/
NPCHandler::NPCHandler(const ActorObjectInfo & actorinfo)
	: ActorHandler(actorinfo), _rootdialog(new DialogPart()),
		_simpledialog(false), _npcnametextid(-1),
		_aggresive(false), _attack_activation_distance(0),
		_attack_activation_distance_discrete(0), 
		_attack_activation_distance_hidden(0), _respwantime(-1),
		_armor(0), _weapon1power(0), _weapon2power(0), _stop_attack_distance(0),
		_agentstatenum(1), _targetedattackplayer(-1)
{
	_lifeinfo.MaxLife = 0;
	_lifeinfo.MaxMana = 0;
	_lifeinfo.CurrentLife = 0;
	_lifeinfo.CurrentMana = 0;

	_agentState = boost::shared_ptr<CharacterStateBase>(new StateNormal());
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


	if(_aggresive)
	{
		file<<"\t"<<name<<":SetAggresive("<<"true"<<")"<<std::endl;
		file<<"\t"<<name<<":SetLife("<<_lifeinfo.MaxLife<<")"<<std::endl;
		file<<"\t"<<name<<":SetMana("<<_lifeinfo.MaxMana<<")"<<std::endl;
		file<<"\t"<<name<<":SetArmor("<<_armor<<")"<<std::endl;
		file<<"\t"<<name<<":SetWeapon1Power("<<_weapon1power<<")"<<std::endl;
		file<<"\t"<<name<<":SetWeapon2Power("<<_weapon2power<<")"<<std::endl;
		file<<"\t"<<name<<":SetAttackActiDist("<<_attack_activation_distance<<")"<<std::endl;
		file<<"\t"<<name<<":SetAttackActiDistDiscrete("<<_attack_activation_distance_discrete<<")"<<std::endl;
		file<<"\t"<<name<<":SetAttackActiDistHidden("<<_attack_activation_distance_hidden<<")"<<std::endl;
		file<<"\t"<<name<<":SetAttackStopDist("<<_stop_attack_distance<<")"<<std::endl;
		file<<"\t"<<name<<":SetRespawnTimeInSec("<<_respwantime<<")"<<std::endl;

		if(_attack_activation_condition)
		{
			std::stringstream condname;
			condname<<name<<"_condAttack";
			_attack_activation_condition->SaveToLuaFile(file, condname.str());

			file<<"\t"<<name<<":SetAttackActivationCondition("<<condname.str()<<")"<<std::endl;
		}

		if(_action_on_attack_activation)
		{
			std::stringstream aname;
			aname<<name<<"_actAttack";
			_action_on_attack_activation->SaveToLuaFile(file, aname.str());

			file<<"\t"<<name<<":SetActionOnAttackActivation("<<aname.str()<<")"<<std::endl;
		}

		LbaNet::ContainedItemList::iterator iti = _itemsgivenatdeath.begin();
		LbaNet::ContainedItemList::iterator endi = _itemsgivenatdeath.end();
		for(; iti != endi; ++iti)
		{
			file<<"\t"<<name<<":AddGivenItem("<<iti->Id<<","<<iti->Min<<","<<iti->Max
				<<","<<iti->Probability<<","<<iti->Group<<")"<<std::endl;
		}

	}
}


/***********************************************************
UntargetPlayer
***********************************************************/
void NPCHandler::UntargetPlayer(Ice::Long PlayerId)
{
	if(!_agentState->CanTalk())
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
	if(!_agentState->CanTalk())
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
	if(ChangeState(4)) 
	{
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

	// start target player
	if(_targetedplayers.size() == 1)
		TargetAttackPlayer(TargetedPlayerId);
}


/***********************************************************
die
***********************************************************/
void NPCHandler::Die()
{
	if(!ChangeState(3)) 
		return;

	//set die time
	_dietime = SynchronizedTimeHandler::GetCurrentTimeDouble();

	//hide
	ShowHideInternal(false);

	if(_hurtingplayers.size() > 0)
	{
		//record player kill - and give item to player
		if(m_scripthandler)
		m_scripthandler->PlayerKilledNpc((long)_hurtingplayers[0], GetId(), GetGivenItems());
	}

	// clear target
	_targetedplayers.clear();
	_hurtingplayers.clear();

	// reset target
	_targetedattackplayer = -1;
}


/***********************************************************
respawn
***********************************************************/
void NPCHandler::Respawn()
{
	if(!_agentState->IsDead())
		return;

	if(!ChangeState(1)) 
		return;


	// reset life
	_lifeinfo.CurrentLife = _lifeinfo.MaxLife;
	_lifeinfo.CurrentMana = _lifeinfo.MaxMana;


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
	bool animfinished = false;

	//process char in case we are not scripted
	if(m_paused || m_launchedscript < 0)
	{
		int pout = _character->Process(tnow, tdiff);
		animfinished = (pout == 1);
	}


	if(_aggresive && _agentState->CanChase())
	{
		//todo - target player that are too close
	}


	//in case of hurt
	if(_agentState->IsHurt())
	{
		if(animfinished)
		{
			// revert back to previous state
			if(ChangeState(_savedstate))
				UpdateActorAnimation(_savedanim, false);		
		}
		else
		{
			// move agent depending of animation
			boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
			boost::shared_ptr<DisplayObjectHandlerBase> disso = _character->GetDisplayObject();

			// get animation speed
			float speedX = disso->GetCurrentAssociatedSpeedX();
			float speedY = disso->GetCurrentAssociatedSpeedY();
			float speedZ = disso->GetCurrentAssociatedSpeedZ();

			LbaQuaternion Q;
			physo->GetRotation(Q);
			LbaVec3 current_directionX(Q.GetDirection(LbaVec3(0, 0, 1)));
			LbaVec3 current_directionZ(Q.GetDirection(LbaVec3(1, 0, 0)));
			float ajustedspeedx = speedX*current_directionX.x + speedZ*current_directionZ.x;
			float ajustedspeedZ = speedX*current_directionX.z + speedZ*current_directionZ.z;

			if(speedX != 0 || speedY != 0 || speedZ != 0)
				physo->Move(ajustedspeedx*tdiff, speedY*tdiff, ajustedspeedZ*tdiff, false);
		}
	}


	//if dead - respawn
	if(_agentState->IsDead() && _respwantime >= 0)
	{
		if((tnow - _dietime) > (_respwantime*1000))
		{
			Respawn();
		}
	}

	//if coming back
	if(_agentState->IsComingBack())
	{
		//check if we arrived
		boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
		if(physo)
		{
			float curX, curY, curZ;
			physo->GetPosition(curX, curY, curZ);
			float diff = fabs(m_saved_X-curX) + fabs(m_saved_Y-curY) + fabs(m_saved_Z-curZ);
			if(diff <= 0.01)
			{
				EndChasing();
			}
		}
	}
}


/***********************************************************
hurt life
***********************************************************/
void NPCHandler::HurtLife(float amount, bool UseArmor, Ice::Long HurtingPlayerId)
{
	if(!_aggresive)
		return;


	//target hurting player
	if(HurtingPlayerId >= 0)
	{
		StartFight(HurtingPlayerId);

		// add to hurt list
		if(std::find(_hurtingplayers.begin(), _hurtingplayers.end(), HurtingPlayerId) == _hurtingplayers.end())
			_hurtingplayers.push_back(HurtingPlayerId);	
	}


	if(!ChangeState(2)) // check if already hurt
		return;

	//remove armor
	if(UseArmor)
		amount += _armor;

	// if no hit then do nothing
	if(amount >= 0)
		return;

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
		else
		{
			if(amount < -19.9)
				PlayHurt(3);
			else if(amount < -9.9)
				PlayHurt(2);
			else
				PlayHurt(1);
		}
	}
}

/***********************************************************
hurt mana
***********************************************************/
void NPCHandler::HurtMana(float amount)
{
	if(!_aggresive)
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
	if(!_aggresive)
		return;

	Die();
}



/***********************************************************
check trigger on player leave map
***********************************************************/
void NPCHandler::PlayerLeaveMap(Ice::Long PlayerId)
{
	if(!_aggresive)
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
	//change anim to walking
	UpdateActorAnimation("MoveForward", false);

	// tell agent to follow player
	if(m_NavMAgent && m_scripthandler)
	{
		LbaVec3 pos = m_scripthandler->GetPlayerPositionVec(PlayerId);
		m_NavMAgent->SetTargetPosition(true, pos.x, pos.y, pos.z);
	}

	_targetedattackplayer = PlayerId;

	//todo - inform client that npc target player


}


/***********************************************************
stop target player
***********************************************************/
void NPCHandler::StopAttackTarget(Ice::Long PlayerId)
{
	if(PlayerId != _targetedattackplayer)
		return;

	_targetedattackplayer = -1;

	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
	if(physo)
	{
		float curX, curY, curZ;
		physo->GetPosition(curX, curY, curZ);
		float diff = fabs(m_saved_X-curX) + fabs(m_saved_Y-curY) + fabs(m_saved_Z-curZ);

		if(diff > 0.001)
		{
			//come back to starting point
			if(ChangeState(5))
			{
				//change anim to walking
				UpdateActorAnimation("MoveForward", false);

				// tell agent to go move back to starting point
				if(m_NavMAgent)
					m_NavMAgent->SetTargetPosition(true, m_saved_X, m_saved_Y, m_saved_Z);
			}
		}
		else
		{
			EndChasing();
		}
	}
}


/***********************************************************
play hurt animation
***********************************************************/
void NPCHandler::PlayHurt(int hurttype)
{
	boost::shared_ptr<DisplayObjectHandlerBase> disO = _character->GetDisplayObject();
	if(!disO)
		return;

	std::string hurtanimstring;


	// check if we can play animation - if not try smaller hurt
	for(; hurttype > 0; --hurttype)
	{
		if(hurttype == 3)
		{
			if(disO->CanPlayAnimation("HurtBig"))
			{
				hurtanimstring = "HurtBig";
				break;
			}
		}

		if(hurttype == 2)
		{
			if(disO->CanPlayAnimation("HurtMedium"))
			{
				hurtanimstring = "HurtMedium";
				break;
			}
		}

		if(hurttype == 1)
		{
			if(disO->CanPlayAnimation("HurtSmall"))
			{
				hurtanimstring = "HurtSmall";
				break;
			}
		}
	}

	if(hurtanimstring == "")
		ChangeState(_savedstate); // cant play hurt - go back to normal
	else
		UpdateActorAnimation(hurtanimstring, false); // update to hurt animation

}


/***********************************************************
accessor
***********************************************************/
void NPCHandler::AddGivenItem(long id, int min, int max, float proba, int group)
{
	LbaNet::ItemGroupElement elem;
    elem.Id = id;
    elem.Min = min;
    elem.Max = max;
    elem.Probability = proba;
    elem.Group = group;
	_itemsgivenatdeath.push_back(elem);
}


/***********************************************************
get given items
***********************************************************/	
LbaNet::ItemsMap NPCHandler::GetGivenItems()
{
	LbaNet::ItemsMap res;

	//fill container with items
	std::vector<LbaNet::ItemGroupElement>::const_iterator itc = _itemsgivenatdeath.begin();
	std::vector<LbaNet::ItemGroupElement>::const_iterator endc = _itemsgivenatdeath.end();

	std::map<int, std::vector<LbaNet::ItemGroupElement> > groups;
	for(; itc != endc; ++itc)
	{
		if(itc->Group < 0)
		{
			bool add = true;
			if(itc->Probability < 1)
				if(Randomizer::getInstance()->Rand() > itc->Probability)
					add = false;

			if(add)
			{
				LbaNet::ItemPosInfo newitem;
				newitem.Position = -1;
				newitem.Info = InventoryItemHandler::getInstance()->GetItemInfo((long)itc->Id);
				newitem.Count = Randomizer::getInstance()->RandInt(itc->Min, itc->Max);
				res[itc->Id] = newitem;
			}
		}
		else
		{
			//item part of a group
			groups[itc->Group].push_back(*itc);
		}
	}


	// take care of the groups
	std::map<int, std::vector<LbaNet::ItemGroupElement> >::iterator itm = groups.begin();
	std::map<int, std::vector<LbaNet::ItemGroupElement> >::iterator endm = groups.end();
	for(; itm != endm; ++itm)
	{
		float currp = 0;
		float proba = (float)Randomizer::getInstance()->Rand();
		std::vector<LbaNet::ItemGroupElement>::iterator itcc = itm->second.begin();
		std::vector<LbaNet::ItemGroupElement>::iterator endcc = itm->second.end();
		for(; itcc != endcc; ++itcc)
		{
			currp += itcc->Probability;
			if(currp > proba)
			{
				// add item
				LbaNet::ItemPosInfo newitem;
				newitem.Position = -1;
				newitem.Info = InventoryItemHandler::getInstance()->GetItemInfo((long)itcc->Id);
				newitem.Count = Randomizer::getInstance()->RandInt(itcc->Min, itcc->Max);
				res[itcc->Id] = newitem;

				break;
			}
		}
	}

	return res;
}


/***********************************************************
target player
***********************************************************/
void NPCHandler::ForceTargetAttackPlayer(Ice::Long PlayerId)
{
	StartFight(PlayerId);
}

/***********************************************************
stop target player
***********************************************************/
void NPCHandler::ForceStopAttackTarget(Ice::Long PlayerId)
{
	StopAttackTarget(PlayerId);
}


/***********************************************************
change NPC state
***********************************************************/
bool NPCHandler::ChangeState(int newstate)
{
	if(_agentstatenum == newstate)
		return false;

	switch(newstate)
	{
		// normal state
		case 1:
		{
			_agentState = boost::shared_ptr<CharacterStateBase>(new StateNormal());
			if(m_NavMAgent)
				m_NavMAgent->SetResetTarget(false);
		}
		break;

		// hurt state
		case 2:
		{
			// save state and animation
			_savedstate = _agentstatenum;
			boost::shared_ptr<DisplayObjectHandlerBase> disO = _character->GetDisplayObject();
			if(disO)
				_savedanim = disO->GetCurrentAnimation();

			_agentState = boost::shared_ptr<CharacterStateBase>(new StateSmallHurt());

			if(m_NavMAgent)
				m_NavMAgent->SetResetTarget(false);
		}
		break;

		//die state
		case 3:
		{
			_agentState = boost::shared_ptr<CharacterStateBase>(new StateDying());

			if(m_NavMAgent)
				m_NavMAgent->SetResetTarget(false);
		}
		break;

		// chase state
		case 4:
		{
			_agentState = boost::shared_ptr<CharacterStateBase>(new StateChasing());

			if(m_NavMAgent)
				m_NavMAgent->SetResetTarget(true);
		}
		break;

		// come back state
		case 5:
		{
			_agentState = boost::shared_ptr<CharacterStateBase>(new StateComingBack());

			if(m_NavMAgent)
				m_NavMAgent->SetResetTarget(true);
		}
		break;
	}



	_agentstatenum = newstate;
	return true;
}


/***********************************************************
check trigger on player move
***********************************************************/
void NPCHandler::PlayerMoved(Ice::Long PlayerId, const LbaNet::PlayerPosition &startposition,
									const LbaNet::PlayerPosition &endposition)
{
	if(_aggresive && _agentState->CanChase())
	{
		//todo - target player that are too close
	}

	//move chasing target
	if(_targetedattackplayer == PlayerId)
	{
		if(m_NavMAgent)
			m_NavMAgent->SetTargetPosition(true, endposition.X, endposition.Y, endposition.Z);
	}
}


/***********************************************************
agent come back to normal
***********************************************************/
void NPCHandler::EndChasing()
{
	//todo - maybe tell client?

	//reset script
	Resume();
}