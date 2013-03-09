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

#ifdef _DEBUG_NPC_
std::ofstream filecheck("checknpc.txt");
#endif

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
		_agentstatenum(0), _targetedattackplayer(-1),
		m_minimalchasingdistance(1), m_weapon1type(-1), m_weapon2type(-1),
		_weapon1reachdistance(1), _weapon2reachdistance(1),
		_fightscriptrunning(false), _fightscriptpartrunning(false),
		_weaponanimatstart(true), _weaponanimating(false)
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
	res<<"NPCHandler(lmap.Actor)";

	return res.str();
}



/***********************************************************
write extra lua
***********************************************************/
void NPCHandler::ExtraLua(std::ostream & file, const std::string & name)
{
	std::stringstream named;
	named<<name<<"_dia";
	_rootdialog->SaveToLuaFile(file, named.str());

	file<<"\t"<<name<<":SetRootDialog("<<named.str()<<")"<<std::endl;
	file<<"\t"<<name<<":SetNpcName("<<_npcnametextid<<")"<<std::endl;
	file<<"\t"<<name<<":SetSimpleDialog("<<(_simpledialog?"true":"false")<<")"<<std::endl;

	file<<"\t"<<name<<":SetLife("<<_lifeinfo.MaxLife<<")"<<std::endl;
	file<<"\t"<<name<<":SetMana("<<_lifeinfo.MaxMana<<")"<<std::endl;
	file<<"\t"<<name<<":SetArmor("<<_armor<<")"<<std::endl;


	LbaNet::ContainedItemList::iterator iti = _itemsgivenatdeath.begin();
	LbaNet::ContainedItemList::iterator endi = _itemsgivenatdeath.end();
	for(; iti != endi; ++iti)
	{
		file<<"\t"<<name<<":AddGivenItem("<<iti->Id<<","<<iti->Min<<","<<iti->Max
			<<","<<iti->Probability<<","<<iti->Group<<")"<<std::endl;
	}

	if(_aggresive)
	{
		file<<"\t"<<name<<":SetAggresive("<<"true"<<")"<<std::endl;

		file<<"\t"<<name<<":SetAttackActiDist("<<_attack_activation_distance<<")"<<std::endl;
		file<<"\t"<<name<<":SetAttackActiDistDiscrete("<<_attack_activation_distance_discrete<<")"<<std::endl;
		file<<"\t"<<name<<":SetAttackActiDistHidden("<<_attack_activation_distance_hidden<<")"<<std::endl;
		file<<"\t"<<name<<":SetAttackStopDist("<<_stop_attack_distance<<")"<<std::endl;
		file<<"\t"<<name<<":SetRespawnTimeInSec("<<_respwantime<<")"<<std::endl;
		file<<"\t"<<name<<":SetWeaponAnimAtStart("<<(_weaponanimatstart?"true":"false")<<")"<<std::endl;

		if(m_weapon1type > 0)
		{
			file<<"\t"<<name<<":SetWeapon1Type("<<m_weapon1type<<")"<<std::endl;

			file<<"\t"<<name<<":SetWeapon1Power("<<_weapon1power<<")"<<std::endl;

			file<<"\t"<<name<<":SetWeapon1ReachDistance("<<_weapon1reachdistance<<")"<<std::endl;

			if(m_useweapon1animation != "")
				file<<"\t"<<name<<":Setuseweapon1animation(\""<<m_useweapon1animation<<"\")"<<std::endl;

			for(size_t i=0; i< _projectilesweapon1.size(); ++i)
			{
				std::stringstream aname;
				aname<<name<<"_weapon1proj"<<i;
				_projectilesweapon1[i]->SaveToLuaFile(file, aname.str());

				file<<"\t"<<name<<":AddProjectileWeapon1("<<aname.str()<<")"<<std::endl;
			}
		}

		if(m_weapon2type > 0)
		{
			file<<"\t"<<name<<":SetWeapon2Type("<<m_weapon2type<<")"<<std::endl;

			file<<"\t"<<name<<":SetWeapon2Power("<<_weapon2power<<")"<<std::endl;

			file<<"\t"<<name<<":SetWeapon2ReachDistance("<<_weapon2reachdistance<<")"<<std::endl;

			if(m_useweapon2animation != "")
				file<<"\t"<<name<<":Setuseweapon2animation(\""<<m_useweapon2animation<<"\")"<<std::endl;

			for(size_t i=0; i< _projectilesweapon2.size(); ++i)
			{
				std::stringstream aname;
				aname<<name<<"_weapon2proj"<<i;
				_projectilesweapon2[i]->SaveToLuaFile(file, aname.str());

				file<<"\t"<<name<<":AddProjectileWeapon2("<<aname.str()<<")"<<std::endl;
			}
		}


		if(m_attackfunctionname != "")
			file<<"\t"<<name<<":SetAttackFunction(\""<<m_attackfunctionname<<"\")"<<std::endl;

		if(m_chasinganimation != "")
			file<<"\t"<<name<<":Setchasinganimation(\""<<m_chasinganimation<<"\")"<<std::endl;



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
#ifdef _DEBUG_NPC_
	filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"Start fight"<<std::endl;
#endif

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
	if(std::find(_targetedattackplayers.begin(), _targetedattackplayers.end(), TargetedPlayerId) == _targetedattackplayers.end())
		_targetedattackplayers.push_back(TargetedPlayerId);

	// start target player
	if(_targetedattackplayers.size() == 1 && !_fightscriptrunning)
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
	_targetedattackplayers.clear();
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
	if(_fightscriptrunning)
	{
		//process NPC animation
		int pout = _character->Process(tnow, tdiff);
		animfinished = (pout == 1);


		if(_weaponanimating)
		{
			// wait until prepare weapon anim finished before processing with attack script
			if(animfinished)
				_weaponanimating = false;
		}
		else
		{
			if(!_fightscriptpartrunning && m_scripthandler && m_attackfunctionname != "")
				m_scripthandler->RunAttackScript(GetId(), m_attackfunctionname);
		}
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
			#ifdef _DEBUG_NPC_
			filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"hurt finished"<<std::endl;
			#endif

			// revert back to previous state
			if(ChangeState(_savedstate))
				UpdateActorAnimation(_savedanim, false, false);		
		}
		else
			movewithanimation = true;
	}

	// in case of use weapon
	if(_agentstatenum == 6)
	{
		if(animfinished)
		{
			#ifdef _DEBUG_NPC_
			filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"use weapon finished"<<std::endl;
			#endif

			//stop hurt player
			m_currenthitpower = -1;
			_immuneplayers.clear();

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
		if(fabs(rotdiff) <= m_rotationtargettolerance)
		{
			#ifdef _DEBUG_NPC_
			filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"rotate finished"<<std::endl;
			#endif

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
					physo->RotateYAxis(std::min((m_rotationtargetspeed*tdiff), (float)(fabs(rotdiff))));	
				else
					physo->RotateYAxis(std::max((-m_rotationtargetspeed*tdiff), (float)(-fabs(rotdiff))));
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
			if((tnow-_lastchasingchecktime) > 500)
			{
				boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
				if(physo)
				{
					float checkX, checkY, checkZ;
					physo->GetPosition(checkX, checkY, checkZ);

					float diff =	fabs(checkX-_lastchasingcheckposX) +
									fabs(checkY-_lastchasingcheckposY) +
									fabs(checkZ-_lastchasingcheckposZ);

					if(diff < 0.3f)
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
			if(diff <= 0.6f)
			{
				//rotate back to starting point
				ChangeState(8);
			}
			else if((tnow-_lastchasingchecktime) > 500)//check if did not get stuck
			{
				float difftt =	fabs(curX-_lastchasingcheckposX) +
								fabs(curY-_lastchasingcheckposY) +
								fabs(curZ-_lastchasingcheckposZ);

				//reset target
				if(difftt < 0.3f && m_NavMAgent)
				{
					++_counterresetchasing;
					if(_counterresetchasing >= 8)
					{
						//stop chasing if we get stuck too long
						ChangeState(8);
					}
					else
						m_NavMAgent->SetTargetPosition(false, m_saved_X, m_saved_Y, m_saved_Z);
				}

				_lastchasingcheckposX = curX;
				_lastchasingcheckposY = curY;
				_lastchasingcheckposZ = curZ;


				_lastchasingchecktime = tnow;
			}
		}
	}

	//if rotating back
	if(_agentstatenum == 8)
	{
		//check if we arrived
		boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
		if(physo)
		{
			float currrot = physo->GetRotationYAxis();

			float rdiff = fmod((m_saved_rot - currrot), 360);
			if(rdiff > 180)
				rdiff = rdiff - 360;
			if(rdiff < -180)
				rdiff = rdiff + 360;

			if(fabs(rdiff) <= 4)
			{
				EndChasing();
			}
			else
			{
				//rotate to direction
				if((rdiff > 0 && rdiff < 180) || (rdiff < -180))
					physo->RotateYAxis(std::min((0.1f*tdiff), (float)(fabs(rdiff))));	
				else
					physo->RotateYAxis(std::max((-0.1f*tdiff), (float)(-fabs(rdiff))));
			}
		}
	}
}


/***********************************************************
hurt life
***********************************************************/
void NPCHandler::HurtLife(float amount, bool UseArmor, int HurtingActorType, 
							Ice::Long HurtingActorId, bool forcelooselife)
{
	if(!_aggresive)
		return;

	//check if can be hurt
	bool force = forcelooselife && _agentState->IsHurt();
	if(!force && _agentState->IsImmuneHurt())
		return;

	#ifdef _DEBUG_NPC_
	filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"hurted by player"<<std::endl;
	#endif

	//target hurting player
	if((HurtingActorType == 2) && (HurtingActorId >= 0))
	{
		StartFight(HurtingActorId);

		// add to hurt list
		if(std::find(_hurtingplayers.begin(), _hurtingplayers.end(), HurtingActorId) == _hurtingplayers.end())
			_hurtingplayers.push_back(HurtingActorId);	
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


	//stop target player
	UntargetAttackPlayer(PlayerId);
}


/***********************************************************
stop targetting player
***********************************************************/
void NPCHandler::UntargetAttackPlayer(Ice::Long PlayerId)
{
	// remove from target list
	int cc=0;
	std::vector<Ice::Long>::iterator it = _targetedattackplayers.begin();
	std::vector<Ice::Long>::iterator end = _targetedattackplayers.end();
	for(; it != end; ++it, ++cc)
	{
		if(*it == PlayerId)
		{
			_targetedattackplayers.erase(it);

			if(cc == 0)
			{
				if(_targetedattackplayers.size() > 0)
					TargetAttackPlayer(_targetedattackplayers[0]);
				else
					StopAttackTarget(PlayerId);

				//stop shooting bullets
				ClearProjectiles();
				m_currenthitpower = -1;
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
	//stop old script
	_targetedattackplayer = -1;
	StopAttackScript();

	// record target
	_targetedattackplayer = PlayerId;

	// get target position
	if(m_scripthandler)
		_lasttargetposition = m_scripthandler->GetPlayerPosition((long)_targetedattackplayer);


	// start action before attack
	if(_action_on_attack_activation)
		_action_on_attack_activation->Execute(m_scripthandler, 1, m_actorinfo.ObjectId, NULL);

	#ifdef _DEBUG_NPC_
	filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"start script"<<std::endl;
	#endif

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
			// tell agent to go move back to starting point
			if(m_NavMAgent)
				m_NavMAgent->SetTargetPosition(false, m_saved_X, m_saved_Y, m_saved_Z);

			//come back to starting point
			ChangeState(5);
		}
		else
		{
			//change state back to normal
			ChangeState(1);

			//rotate back to starting point
			ChangeState(8);
		}
	}
}


/***********************************************************
play hurt animation
***********************************************************/
void NPCHandler::PlayHurt(int hurttype)
{
	std::string hurtanimstring;


	// check if we can play animation - if not try smaller hurt
	for(; hurttype > 0; --hurttype)
	{
		if(hurttype == 3)
		{
			if(CanPlayAnimation("HurtBig"))
			{
				hurtanimstring = "HurtBig";
				break;
			}
		}

		if(hurttype == 2)
		{
			if(CanPlayAnimation("HurtMedium"))
			{
				hurtanimstring = "HurtMedium";
				break;
			}
		}

		if(hurttype == 1)
		{
			if(CanPlayAnimation("HurtSmall"))
			{
				hurtanimstring = "HurtSmall";
				break;
			}
		}
	}

	if(hurtanimstring == "")
		ChangeState(_savedstate); // cant play hurt - go back to normal
	else
		UpdateActorAnimation(hurtanimstring, false, false); // update to hurt animation

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

	// only can change to normal state from dead state
	//if(_agentstatenum == 3 && newstate != 1)
	//	return false;

	#ifdef _DEBUG_NPC_
	filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"change state to "<<newstate<<std::endl;
	#endif

	// clear current projectiles
	if((_agentstatenum == 6) && (newstate != 7)) // exception for rotate as we still want to fire during rotating
	{
		ClearProjectiles();
		m_currenthitpower = -1;
	}

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

			#ifdef _DEBUG_NPC_
			filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"change state to normal"<<std::endl;
			#endif
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

			#ifdef _DEBUG_NPC_
			filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"change state to hurt"<<std::endl;
			#endif
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

			#ifdef _DEBUG_NPC_
			filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"change state to die"<<std::endl;
			#endif
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
			_counterresetchasing = 0;

			//change anim to chasing anim
			if(m_chasinganimation != "")
				UpdateActorAnimation(m_chasinganimation, false, false);
			else
				UpdateActorAnimation("MoveForward", false, false);


			#ifdef _DEBUG_NPC_
			filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"change state to chase"<<std::endl;
			#endif
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
			_counterresetchasing = 0;

			//change anim to walking
			UpdateActorAnimation("MoveForward", false, false);

			#ifdef _DEBUG_NPC_
			filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"change state to come back"<<std::endl;
			#endif
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

			#ifdef _DEBUG_NPC_
			filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"change state to use weapon"<<std::endl;
			#endif
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

			#ifdef _DEBUG_NPC_
			filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"change state to rotate to target"<<std::endl;
			#endif
		}
		break;


		// rotate back state
		case 8:
		{
			_agentState = boost::shared_ptr<CharacterStateBase>(new StateRotatingBack());

			if(m_NavMAgent)
				m_NavMAgent->SetResetTarget(false);

			_freemove = true;
			_lastupdate.AnimationIdx  = "";

			//change anim to walking
			UpdateActorAnimation("TurnLeft", false, false);

			#ifdef _DEBUG_NPC_
			filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"change state to rotate back"<<std::endl;
			#endif
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
									const LbaNet::PlayerPosition &endposition,
									const LbaNet::ModelState & state,
									const std::string & mode, bool cantarget)
{
	if(!_fightscriptrunning && _aggresive && _agentState->CanChase() && cantarget)
	{
		boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
		if(!physo)
			return;

		// get current position
		float px, py, pz;
		physo->GetPosition(px, py, pz);

		bool conditionpassed = true;
		if(_attack_activation_condition && m_scripthandler)
			conditionpassed = _attack_activation_condition->Passed(m_scripthandler, 2, PlayerId);

		if(conditionpassed)
		{
			bool target = ShouldAttackPlayer(px, py, pz, endposition.X, endposition.Y, endposition.Z, state, mode);

			if(target)
				StartFight(PlayerId);
		}
	}

	if(_targetedattackplayer == PlayerId)
	{
		// record last position
		_lasttargetposition = endposition;

		// check if target out of reach
		if(_stop_attack_distance > 0)
		{
			boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
			if(!physo)
				return;

			// get current position
			float px, py, pz;
			physo->GetPosition(px, py, pz);

			float dx = (endposition.X - px);
			float dy = (endposition.Y - py);
			float dz = (endposition.Z - pz);

			float diff = dx*dx + dy*dy + dz*dz;
			if(diff >= (_stop_attack_distance*_stop_attack_distance))
			{
				//stop target player
				UntargetAttackPlayer(PlayerId);

				return;
			}
		}


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
used by lua to get an actor Position
***********************************************************/
LbaVec3 NPCHandler::GetActorPosition(bool fromattackscript)
{
	if(fromattackscript && _freemove)
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
		return ActorHandler::GetActorPosition(fromattackscript);
}


/***********************************************************
start attack script
***********************************************************/
void NPCHandler::StartAttackScript()
{
	#ifdef _DEBUG_NPC_
	filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"start atack script"<<std::endl;
	#endif

	if(_fightscriptrunning)
		StopAttackScript();	//stop old script


	// start the script
	if(m_attackfunctionname != "" && m_scripthandler)
	{
		_fightscriptrunning = true;

		if(_weaponanimatstart)
		{
			if(CanPlayAnimation("PrepareWeapon"))
			{
				UpdateActorAnimation("PrepareWeapon", false, false); 
				_weaponanimating = true;
			}
		}
	}
		//m_scripthandler->StartScript(m_attackfunctionname, GetId(), false, m_launchedattackscript);
}

/***********************************************************
stop attack script
***********************************************************/
void NPCHandler::StopAttackScript()
{
	#ifdef _DEBUG_NPC_
	filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"stop atack script"<<std::endl;
	#endif

	YieldRunningScript();
	_fightscriptrunning = false;
}


/***********************************************************
npc follow player
***********************************************************/
void NPCHandler::FollowTargettedPlayer(int ScriptId, float DistanceStopFollow)
{
	#ifdef _DEBUG_NPC_
	filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"start follow player"<<std::endl;
	#endif

	YieldRunningScript();
	_fightscriptpartrunning = true;

	if(_targetedattackplayer < 0)
	{
		ChangeState(1);
		YieldRunningScript();
		return;
	}

	// set minimal distance
	m_minimalchasingdistance = DistanceStopFollow;



	// tell agent to follow player
	if(m_NavMAgent && m_scripthandler)
	{
		LbaVec3 pos = m_scripthandler->GetPlayerPositionVec((long)_targetedattackplayer);
		m_NavMAgent->SetTargetPosition(false, pos.x, pos.y, pos.z);
	}


	// change state to chasing
	ChangeState(4);


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
	#ifdef _DEBUG_NPC_
	filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"start rotate to player"<<std::endl;
	#endif

	YieldRunningScript();
	_fightscriptpartrunning = true;

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
void NPCHandler::UseWeapon(int ScriptId, int WeaponNumber, bool multishot)
{
	#ifdef _DEBUG_NPC_
	filecheck<<SynchronizedTimeHandler::GetTimeString()<<" "<<"use weapon"<<std::endl;
	#endif

	YieldRunningScript();
	_fightscriptpartrunning = true;

	if(_targetedattackplayer < 0)
	{
		ChangeState(1);
		YieldRunningScript();
		return;
	}


	int weapontype = -1;
	std::string useanim;
	std::vector<ProjectileObjectDefPtr>* projectiles = NULL;
	float weaponpower = 0;

	switch(WeaponNumber)
	{
		// first contact weapon
		case 1:
			if(m_weapon1type == 1)
			{
				weapontype = m_weapon1type;
				useanim = m_useweapon1animation;		
				projectiles = &_projectilesweapon1;
				weaponpower = _weapon1power;
			}
			else if (m_weapon2type == 1)
			{
				weapontype = m_weapon2type;
				useanim = m_useweapon2animation;		
				projectiles = &_projectilesweapon2;		
				weaponpower = _weapon2power;		
			}
		break;

		// first distance weapon
		case 2:
			if(m_weapon1type == 2)
			{
				weapontype = m_weapon1type;
				useanim = m_useweapon1animation;		
				projectiles = &_projectilesweapon1;		
				weaponpower = _weapon1power;		
			}
			else if (m_weapon2type == 2)
			{
				weapontype = m_weapon2type;
				useanim = m_useweapon2animation;			
				projectiles = &_projectilesweapon2;		
				weaponpower = _weapon2power;	
			}
		break;

		// second contact weapon
		case 3:
			if(m_weapon2type == 1)
			{
				weapontype = m_weapon2type;
				useanim = m_useweapon2animation;			
				projectiles = &_projectilesweapon2;	
				weaponpower = _weapon2power;				
			}
		break;

		// second distance weapon
		case 4:
			if(m_weapon2type == 2)
			{
				weapontype = m_weapon2type;
				useanim = m_useweapon2animation;			
				projectiles = &_projectilesweapon2;	
				weaponpower = _weapon2power;				
			}
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
		UpdateActorAnimation(useanim, false, false);
		

	// do specific weapon actions
	switch(weapontype)
	{
		case 1: // contact weapon
		{
			m_currenthitpower = weaponpower;
			_immuneplayers.clear();
		}
		break;

		case 2: // ditance weapon
			if(projectiles)
			{
				if(multishot && _launchedprojs.size() > 0)
					return; // do nothing if multishot and already launched

				std::vector<ProjectileObjectDefPtr>::iterator itp = projectiles->begin();
				std::vector<ProjectileObjectDefPtr>::iterator endp = projectiles->end();
				for(;itp != endp; ++itp)
				{
					LbaNet::ProjectileInfo newProj;
					if((*itp)->GetProjectileInfo("", _lifeinfo.CurrentMana, 
													2, (long)_targetedattackplayer, newProj))
					{
						// update projectile ids
						newProj.ManagingClientId = _targetedattackplayer;
						newProj.OwnerActorType = 1;
						newProj.OwnerActorId = GetId();
						newProj.MultiShoot = multishot;

						// update projectile position
						boost::shared_ptr<PhysicalObjectHandlerBase> physo = _character->GetPhysicalObject();
						if(physo)
							physo->GetPosition(	newProj.PhysicDesc.Pos.X, 
												newProj.PhysicDesc.Pos.Y, 
												newProj.PhysicDesc.Pos.Z);

						//update mana left
						DeltaUpdateMana(-(*itp)->UseMana);

						// launch projectile
						if( m_scripthandler)
						{
							long projid = m_scripthandler->LaunchProjectile(newProj);
							if(multishot)
								_launchedprojs.push_back(projid);
						}
					}		
				}
			}
		break;
	}

}



/***********************************************************
yield running script
***********************************************************/
void NPCHandler::YieldRunningScript()
{
	_fightscriptpartrunning = false;
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
		if(YNPC < 0)
			YNPC += 360;


		float diff = fmod((YTarget - YNPC),360);
		if(diff > 180)
			diff = diff - 360;
		if(diff < -180)
			diff = diff + 360;

		return diff;
	}

	return 360;
}


/***********************************************************
delta update mana
***********************************************************/
void NPCHandler::DeltaUpdateMana(float deltamana)
{
	_lifeinfo.CurrentMana += deltamana;
	if(_lifeinfo.CurrentMana < 0)
		_lifeinfo.CurrentMana = 0;

	if(_lifeinfo.CurrentMana > _lifeinfo.MaxMana)
		_lifeinfo.CurrentMana = _lifeinfo.MaxMana;
}


/***********************************************************
remove projectile
***********************************************************/
void NPCHandler::RemoveProjectileWeapon1(ProjectileObjectDefPtr proj)
{
	std::vector<ProjectileObjectDefPtr>::iterator it = std::find(_projectilesweapon1.begin(), _projectilesweapon1.end(), proj);
	if(it != _projectilesweapon1.end())
		_projectilesweapon1.erase(it);
}

/***********************************************************
remove projectile
***********************************************************/
void NPCHandler::RemoveProjectileWeapon2(ProjectileObjectDefPtr proj)
{
	std::vector<ProjectileObjectDefPtr>::iterator it = std::find(_projectilesweapon2.begin(), _projectilesweapon2.end(), proj);
	if(it != _projectilesweapon2.end())
		_projectilesweapon2.erase(it);
}



/***********************************************************
//! get weapon distance
//! 1-> first contact weapon, 2 -> first distance weapon
//! 3-> second contact weapon, 4 -> second distance weapon
***********************************************************/
float NPCHandler::GetWeaponReachDistance(int WeaponNumber)
{
	switch(WeaponNumber)
	{
		// first contact weapon
		case 1:
			if(m_weapon1type == 1)
			{
				return (_weapon1reachdistance*_weapon1reachdistance);
			}
			else if (m_weapon2type == 1)
			{
				return (_weapon2reachdistance*_weapon2reachdistance);	
			}
		break;

		// first distance weapon
		case 2:
			if(m_weapon1type == 2)
			{
				return (_weapon1reachdistance*_weapon1reachdistance);
			}
			else if (m_weapon2type == 2)
			{
				return (_weapon2reachdistance*_weapon2reachdistance);	
			}
		break;

		// second contact weapon
		case 3:
			if(m_weapon2type == 1)
			{
				return (_weapon2reachdistance*_weapon2reachdistance);				
			}
		break;

		// second distance weapon
		case 4:
			if(m_weapon2type == 2)
			{
				return (_weapon2reachdistance*_weapon2reachdistance);			
			}
		break;
	}

	return 0;
}


/***********************************************************
clear launched projectiles
***********************************************************/
void NPCHandler::ClearProjectiles()
{
	if(!m_scripthandler)
		return;

	std::vector<long>::iterator it = _launchedprojs.begin();
	std::vector<long>::iterator end = _launchedprojs.end();
	for(; it!= end; ++it)
		m_scripthandler->DestroyProjectile(*it);	


	_launchedprojs.clear();
}


/***********************************************************
check if should attack player
***********************************************************/
bool NPCHandler::ShouldAttackPlayer(float px, float py, float pz, 
										float playerposx, float playerposy, float playerposz, 
										const LbaNet::ModelState & playerstate,
										const std::string & playermode)
{
	float dx = playerposx-px;
	float dy = playerposy-py;
	float dz = playerposz-pz;
	float dist = dx*dx + dy*dy + dz*dz;

	if(playerstate == LbaNet::StHidden)
	{
		if(_attack_activation_distance_hidden > 0)
		{
			return (dist < (_attack_activation_distance_hidden*_attack_activation_distance_hidden) );
		}
		else
			return false;
	}
	else
	{
		if(playermode == "Discrete")
		{
			if(_attack_activation_distance_discrete > 0)
			{
				return (dist < (_attack_activation_distance_discrete*_attack_activation_distance_discrete) );
			}
			else
				return false;
		}
		else
		{
			if(_attack_activation_distance > 0)
			{
				return (dist < (_attack_activation_distance*_attack_activation_distance) );
			}
			else
				return false;
		}	
	}
}

	
/***********************************************************
check if script is attack script
***********************************************************/
bool NPCHandler::IsAttackScript(int ScriptId) 
{
	return ScriptId == -33;
}

		
/***********************************************************
check if script is attack script
***********************************************************/
bool NPCHandler::IsAttacking() 
{
	return _fightscriptrunning || (_agentstatenum == 5);
}


		
/***********************************************************
check if reset position
***********************************************************/
bool NPCHandler::IsDead()
{
	return (_agentstatenum == 3);
}

		
/***********************************************************
check if player is immune from us
***********************************************************/
bool NPCHandler::PlayerImune(long playerid)
{
	return (_immuneplayers.find(playerid) != _immuneplayers.end());
}
		
/***********************************************************
inform that npc touched player
***********************************************************/
void NPCHandler::TouchedPlayer(long playerid, bool killed)
{
	_immuneplayers.insert(playerid);
}