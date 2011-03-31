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
		_agentstatenum(0), _targetedattackplayer(-1), _oldtdiff(1), 
		m_launchedattackscript(-1), m_runningscript(-1),
		m_weapon2type(-1), m_minimalchasingdistance(1),
		m_useweapon1animation("UseWeapon"), m_weapon1type(1)
{
	_lifeinfo.MaxLife = 0;
	_lifeinfo.MaxMana = 0;
	_lifeinfo.CurrentLife = 0;
	_lifeinfo.CurrentMana = 0;

	ChangeState(1);
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

		if(m_attackfunctionname != "")
			file<<"\t"<<name<<":SetAttackFunction(\""<<m_attackfunctionname<<"\")"<<std::endl;

		if(m_chasinganimation != "")
			file<<"\t"<<name<<":Setchasinganimation(\""<<m_chasinganimation<<"\")"<<std::endl;

		if(m_useweapon1animation != "")
			file<<"\t"<<name<<":Setuseweapon1animation(\""<<m_useweapon1animation<<"\")"<<std::endl;

		if(m_useweapon2animation != "")
			file<<"\t"<<name<<":Setuseweapon2animation(\""<<m_useweapon2animation<<"\")"<<std::endl;

		file<<"\t"<<name<<":SetWeapon1Type("<<m_weapon1type<<")"<<std::endl;
		file<<"\t"<<name<<":SetWeapon2Type("<<m_weapon2type<<")"<<std::endl;



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
	StopAttackScript();
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

	// process attack script
	if((m_launchedattackscript >= 0) && (_currentScripts.size() > 0))
	{
		ProcessScript(tnow, tdiff, m_scripthandler);
	}
	else
	{
		//process char in case we are not scripted
		if(m_paused || m_launchedscript < 0)
		{
			int pout = _character->Process(tnow, tdiff);
			animfinished = (pout == 1);
		}
	}

	//target players that are too close
	if(_aggresive && _targetedattackplayer < 0)
	{
		//todo - target player that are too close
	}

	//flag saying if we should move according to animations
	bool movewithanimation = false;

	//in case of hurt
	if(_agentstatenum == 2)
	{
		if(animfinished)
		{
			// revert back to previous state
			if(ChangeState(_savedstate))
				UpdateActorAnimation(_savedanim, false);		
		}
		else
			movewithanimation = true;
	}

	// in case of use weapon
	if(_agentstatenum == 6)
	{
		if(animfinished)
		{
			//stop hurt player
			m_currenthitpower = -1;

			// inform script
			YieldRunningScript();	
		}
		else
			movewithanimation = true;
	}

	// in case we rotate to target
	if(_agentstatenum == 7)
	{
		float rotdiff = GetTargetRotationDiff();
		if(rotdiff <= m_rotationtargettolerance)
		{
			// inform script
			YieldRunningScript();
		}
		else
		{
			//rotate to direction
			boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
			if(physo)
			{
				if((rotdiff > 0 && rotdiff < 180) || (rotdiff < -180))
					physo->RotateYAxis(std::max((-m_rotationtargetspeed*tdiff), (-fabs(rotdiff))));
				else
					physo->RotateYAxis(std::min((m_rotationtargetspeed*tdiff), (fabs(rotdiff))));
			}
		}
	}




	// move agent depending of animation
	if(movewithanimation)
	{
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


	//if dead - respawn
	if(_agentState->IsDead() && _respwantime >= 0)
	{
		if((tnow - _dietime) > (_respwantime*1000))
		{
			Respawn();
		}
	}

	//if chasing
	if(_agentstatenum == 4)
	{
		// check if we arrive at destination
		if(IsTargetInRange(m_minimalchasingdistance))
		{
			// inform script
			YieldRunningScript();	
		}
		else
		{
			//check if did not get stuck
			if((tnow-_lastchasingchecktime) > 1000)
			{
				boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
				if(physo)
				{
					float checkX, checkY, checkZ;
					physo->GetPosition(checkX, checkY, checkZ);

					float diff =	fabs(checkX-_lastchasingcheckposX) +
									fabs(checkY-_lastchasingcheckposY) +
									fabs(checkZ-_lastchasingcheckposZ);

					if(diff < 0.1f)
					{
						//reset target
						if(_targetedattackplayer > 0 && m_NavMAgent && m_scripthandler)
						{
							LbaVec3 pos = m_scripthandler->GetPlayerPositionVec((long)_targetedattackplayer);
							m_NavMAgent->SetTargetPosition(false, pos.x, pos.y, pos.z);
						}
					}

					_lastchasingcheckposX = checkX;
					_lastchasingcheckposY = checkY;
					_lastchasingcheckposZ = checkZ;
				}

				_lastchasingchecktime = tnow;
			}
		}
	}

	//if coming back
	if(_agentstatenum == 5)
	{
		//check if we arrived
		boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
		if(physo)
		{
			float curX, curY, curZ;
			physo->GetPosition(curX, curY, curZ);
			float diff = fabs(m_saved_X-curX) + fabs(m_saved_Y-curY) + fabs(m_saved_Z-curZ);
			if(diff <= 0.5f)
			{
				EndChasing();
			}
		}
	}

	//check if update clients
	if(_freemove)
		UpdateClients(tnow, tdiff);
}


/***********************************************************
hurt life
***********************************************************/
void NPCHandler::HurtLife(float amount, bool UseArmor, Ice::Long HurtingPlayerId)
{
	if(!_aggresive)
		return;


	//check if can be hurt
	if(_agentState->IsImmuneHurt())
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
	// record target
	_targetedattackplayer = PlayerId;

	// get target position
	if(m_scripthandler)
		_lasttargetposition = m_scripthandler->GetPlayerPosition(_targetedattackplayer);


	// start action before attack
	if(_action_on_attack_activation)
		_action_on_attack_activation->Execute(m_scripthandler, 2, PlayerId, NULL);

	// start script
	StartAttackScript();
}


/***********************************************************
stop target player
***********************************************************/
void NPCHandler::StopAttackTarget(Ice::Long PlayerId)
{
	if(PlayerId != _targetedattackplayer)
		return;

	_targetedattackplayer = -1;
	StopAttackScript();

	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
	if(physo)
	{
		float curX, curY, curZ;
		physo->GetPosition(curX, curY, curZ);
		float diff = fabs(m_saved_X-curX) + fabs(m_saved_Y-curY) + fabs(m_saved_Z-curZ);

		if(diff > 0.001)
		{
			//come back to starting point
			ChangeState(5);

			// tell agent to go move back to starting point
			if(m_NavMAgent)
				m_NavMAgent->SetTargetPosition(false, m_saved_X, m_saved_Y, m_saved_Z);
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

			_freemove = false;
			_lastupdate.AnimationIdx  = "";
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

			_freemove = true;
			_lastupdate.AnimationIdx  = "";
		}
		break;

		//die state
		case 3:
		{
			_agentState = boost::shared_ptr<CharacterStateBase>(new StateDying());

			if(m_NavMAgent)
				m_NavMAgent->SetResetTarget(false);

			_freemove = false;
			_lastupdate.AnimationIdx  = "";
		}
		break;

		// chase state
		case 4:
		{
			_agentState = boost::shared_ptr<CharacterStateBase>(new StateChasing());

			if(m_NavMAgent)
				m_NavMAgent->SetResetTarget(true);

			_freemove = true;
			_lastupdate.AnimationIdx  = "";

			//change anim to chasing anim
			if(m_chasinganimation != "")
				UpdateActorAnimation(m_chasinganimation, false);
			else
				UpdateActorAnimation("MoveForward", false);
		}
		break;

		// come back state
		case 5:
		{
			_agentState = boost::shared_ptr<CharacterStateBase>(new StateComingBack());

			if(m_NavMAgent)
				m_NavMAgent->SetResetTarget(true);

			_freemove = true;
			_lastupdate.AnimationIdx  = "";

			//change anim to walking
			UpdateActorAnimation("MoveForward", false);
		}
		break;

		// use weapon state
		case 6:
		{
			_agentState = boost::shared_ptr<CharacterStateBase>(new StateUseWeapon());

			if(m_NavMAgent)
				m_NavMAgent->SetResetTarget(false);

			_freemove = true;
			_lastupdate.AnimationIdx  = "";
		}
		break;

		// rotate to target state
		case 7:
		{
			_agentState = boost::shared_ptr<CharacterStateBase>(new StateNormal());

			if(m_NavMAgent)
				m_NavMAgent->SetResetTarget(false);

			_freemove = true;
			_lastupdate.AnimationIdx  = "";
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

	if(_targetedattackplayer == PlayerId)
	{
		// record last position
		_lasttargetposition = endposition;

		//move chasing target
		if(_agentState->IsChasing())
		{
			float diff =	fabs(startposition.X - endposition.X) +
							fabs(startposition.Y - endposition.Y) +
							fabs(startposition.Z - endposition.Z);

			if(diff > 0.001 && m_NavMAgent)
				m_NavMAgent->SetTargetPosition(true, endposition.X, endposition.Y, endposition.Z);
		}
	}
}


/***********************************************************
agent come back to normal
***********************************************************/
void NPCHandler::EndChasing()
{
	//reset normal behavior
	Resume();
}


/***********************************************************
check if we need to send update to server
***********************************************************/
void NPCHandler::UpdateClients(double tnow, float tdiff)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
	if(!physo)
		return;

	// get current position
	physo->GetPosition(_currentupdate.CurrentPos.X,
							_currentupdate.CurrentPos.Y,
							_currentupdate.CurrentPos.Z);


	// get current rotation
	_currentupdate.CurrentPos.Rotation = physo->GetRotationYAxis();


	// set speed
	_currentupdate.CurrentSpeedX = (_currentupdate.CurrentPos.X-_lastupdate.CurrentPos.X) / _oldtdiff;
	_currentupdate.CurrentSpeedY = (_currentupdate.CurrentPos.Y-_lastupdate.CurrentPos.Y) / _oldtdiff;
	_currentupdate.CurrentSpeedZ = (_currentupdate.CurrentPos.Z-_lastupdate.CurrentPos.Z) / _oldtdiff;

	//calculate angle speed
	_currentupdate.CurrentSpeedRotation = (_currentupdate.CurrentPos.Rotation-
													_lastupdate.CurrentPos.Rotation);
	while(_currentupdate.CurrentSpeedRotation < -180)
		_currentupdate.CurrentSpeedRotation += 360;
	while(_currentupdate.CurrentSpeedRotation > 180)
		_currentupdate.CurrentSpeedRotation -= 360;


	_currentupdate.CurrentSpeedRotation /= tdiff;


	_oldtdiff = tdiff;


	boost::shared_ptr<DisplayObjectHandlerBase> diso = _character->GetDisplayObject();

	// set animation
	if(diso)
		_currentupdate.AnimationIdx = diso->GetCurrentAnimation();



	// check if we should force the update
	_currentupdate.ForcedChange = ShouldforceUpdate();


	//send to server if needed
	if(_currentupdate.ForcedChange && m_scripthandler)
	{
		LbaNet::EventsSeq evseq;
		evseq.push_back(new LbaNet::NPCMovedEvent(tnow, GetId(), _currentupdate));
		m_scripthandler->SendEvents(-2, evseq);
	}

	_lastupdate = _currentupdate;
}


/***********************************************************
check if we should force the update
***********************************************************/
bool NPCHandler::ShouldforceUpdate()
{
	if(_lastupdate.AnimationIdx != _currentupdate.AnimationIdx)
		return true;

	if(fabs(_lastupdate.CurrentSpeedX - _currentupdate.CurrentSpeedX) > 0.00001f)
		return true;

	if(fabs(_lastupdate.CurrentSpeedY - _currentupdate.CurrentSpeedY) > 0.00001f)
		return true;

	if(fabs(_lastupdate.CurrentSpeedZ - _currentupdate.CurrentSpeedZ) > 0.00001f)
		return true;

	if(fabs(_lastupdate.CurrentSpeedRotation - _currentupdate.CurrentSpeedRotation) > 0.01f)
		return true;



	float diffpos = fabs(_lastupdate.CurrentPos.X - _currentupdate.CurrentPos.X)
					+ fabs(_lastupdate.CurrentPos.Y - _currentupdate.CurrentPos.Y)
					+  fabs(_lastupdate.CurrentPos.Z - _currentupdate.CurrentPos.Z);
	if(diffpos > 10)
		return true;


	double diffrot = fabs(_lastupdate.CurrentPos.Rotation - _currentupdate.CurrentPos.Rotation);
	if(diffrot > 10)
		return true;


	return false;
}


/***********************************************************
used by lua to get an actor Position
***********************************************************/
LbaVec3 NPCHandler::GetActorPosition()
{
	if(_freemove)
	{
		if(_character)
		{
			boost::shared_ptr<PhysicalObjectHandlerBase> physO = _character->GetPhysicalObject();
			if(physO)
			{
				float X, Y, Z;
				physO->GetPosition(X, Y, Z);
				return LbaVec3(X, Y, Z);
			}
		}

		return LbaVec3();
	}
	else
		return ActorHandler::GetActorPosition();
}


/***********************************************************
start attack script
***********************************************************/
void NPCHandler::StartAttackScript()
{
	if(m_launchedattackscript > 0)
		StopAttackScript();	//stop old script

	// start the script
	if(m_attackfunctionname != "" && m_scripthandler)
		m_launchedattackscript = m_scripthandler->StartScript(m_attackfunctionname, GetId(), false);
}

/***********************************************************
stop attack script
***********************************************************/
void NPCHandler::StopAttackScript()
{
	YieldRunningScript();

	if(m_launchedattackscript > 0 && m_scripthandler)
		m_scripthandler->StropThread(m_launchedattackscript);	

	m_launchedattackscript = -1;
}


/***********************************************************
npc follow player
***********************************************************/
void NPCHandler::FollowTargettedPlayer(int ScriptId, float DistanceStopFollow)
{
	YieldRunningScript();
	m_runningscript = ScriptId;

	if(_targetedattackplayer < 0)
	{
		ChangeState(1);
		YieldRunningScript();
		return;
	}

	// set minimal distance
	m_minimalchasingdistance = DistanceStopFollow*DistanceStopFollow;


	// change state to chasing
	ChangeState(4);


	// tell agent to follow player
	if(m_NavMAgent && m_scripthandler)
	{
		LbaVec3 pos = m_scripthandler->GetPlayerPositionVec((long)_targetedattackplayer);
		m_NavMAgent->SetTargetPosition(false, pos.x, pos.y, pos.z);
	}

	// record last chasing position and time
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
	if(physo)
		physo->GetPosition(_lastchasingcheckposX, _lastchasingcheckposY, _lastchasingcheckposZ);

	_lastchasingchecktime = SynchronizedTimeHandler::GetCurrentTimeDouble();
}



/***********************************************************
npc rotate to player
***********************************************************/
void NPCHandler::RotateToTargettedPlayer(int ScriptId, float ToleranceAngle, float speed)
{
	YieldRunningScript();
	m_runningscript = ScriptId;

	if(_targetedattackplayer < 0)
	{
		ChangeState(1);
		YieldRunningScript();
		return;
	}

	m_rotationtargetspeed = speed;
	m_rotationtargettolerance = ToleranceAngle;

	ChangeState(7);
}


/***********************************************************
npc use weapon
***********************************************************/
void NPCHandler::UseWeapon(int ScriptId, int WeaponNumber)
{
	YieldRunningScript();
	m_runningscript = ScriptId;

	if(_targetedattackplayer < 0)
	{
		ChangeState(1);
		YieldRunningScript();
		return;
	}


	int weapontype = -1;
	std::string useanim;


	switch(WeaponNumber)
	{
		case 1:
			weapontype = m_weapon1type;
			useanim = m_useweapon1animation;
		break;

		case 2:
			weapontype = m_weapon1type;
			useanim = m_useweapon1animation;
		break;
	}

	if(weapontype < 0)
	{
		ChangeState(1);
		YieldRunningScript(); // no weapon found
		return;
	}


	// change state to use weapon
	ChangeState(6);

	// start weapon use anim
	if(useanim != "")
		UpdateActorAnimation(useanim, false);
		

	// do specific weapon actions
	switch(weapontype)
	{
		case 1: // contact weapon
			//todo - set hurt life amount
			// m_currenthitpower = ?
		break;

		case 2: // ditance weapon
			//todo - launch projectile
		break;
	}

}



/***********************************************************
yield running script
***********************************************************/
void NPCHandler::YieldRunningScript()
{
	if(m_runningscript < 0)
		return;

	//tell script handler that script part is finished
	if(m_scripthandler)
	{
		int scriptid = m_runningscript;
		m_runningscript = -1;
		m_scripthandler->ScriptFinished(scriptid, false);
	}
}


/***********************************************************
return touch hit power - used to make player loose life if actor touch him/hit him
***********************************************************/
float NPCHandler::GetTouchHitPower(bool & IgnoreArmor)
{
	IgnoreArmor = false;
	if(m_currenthitpower > 0)
		return m_currenthitpower;

	return ActorHandler::GetTouchHitPower(IgnoreArmor);
}


/***********************************************************
check if target is in range
***********************************************************/
bool NPCHandler::IsTargetInRange(float MaxDistance)
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
	if(physo)
	{
		LbaVec3 Npcpos;
		physo->GetPosition(Npcpos.x, Npcpos.y, Npcpos.z);

		LbaVec3 Targetpos(_lasttargetposition.X, _lasttargetposition.Y, _lasttargetposition.Z);
		LbaVec3 diff = Targetpos-Npcpos;
		if(diff.FastLength() <= MaxDistance)
		{
			//check if in line of sight
			if(m_NavMAgent && m_NavMAgent->RaycastTarget(Targetpos))
				return true;
		}
	}

	return false;
}


/***********************************************************
check if target is in rotation range
***********************************************************/
float NPCHandler::GetTargetRotationDiff()
{
	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
	if(physo)
	{
		LbaVec3 Npcpos;
		physo->GetPosition(Npcpos.x, Npcpos.y, Npcpos.z);
		LbaVec3 Targetpos(_lasttargetposition.X, _lasttargetposition.Y, _lasttargetposition.Z);
		LbaVec3 diffvec = Targetpos-Npcpos;

		float YTarget = LbaQuaternion::GetAngleFromVector(diffvec);
		float YNPC = physo->GetRotationYAxis();


		float diff = fmod(fabs(YTarget - YNPC),360);
		if(diff > 180)
			diff = 360 - diff;

		return diff;
	}

	return 360;
}