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

#ifndef _NPC_HANDLER_H__
#define _NPC_HANDLER_H__

#include "ActorHandler.h"
#include "DialogPart.h"

class CharacterStateBase;

/***********************************************************************
class taking care of the maping between lua and the server interfaces
 ***********************************************************************/
class NPCHandler : public ActorHandler
{
public:
	


public:
	//! constructor
	NPCHandler(const ActorObjectInfo & actorinfo);
	
	//! destructor
	virtual ~NPCHandler(void){}

	//! return actor type
	virtual std::string ActorType()
	{ return "Npc";}

	//! get root dialog
	DialogPartPtr GetRootDialog()
	{return _rootdialog;}

	//! set root dialog
	void SetRootDialog(DialogPartPtr root)
	{_rootdialog = root;}


	//! get root dialog
	bool GetSimpleDialog()
	{return _simpledialog;}

	//! set root dialog
	void SetSimpleDialog(bool simple)
	{_simpledialog = simple;}


	//! get root dialog
	long GetNpcName()
	{return _npcnametextid;}

	//! set root dialog
	void SetNpcName(long name)
	{_npcnametextid = name;}


	//! stop target player
	virtual void UntargetPlayer(Ice::Long PlayerId);

	//! check trigger on player action
	virtual void PlayerAction(Ice::Long PlayerId, const LbaNet::PlayerPosition &info,
									const std::string &ObjectMode);


	//! hurt life
	virtual void HurtLife(float amount, bool UseArmor, Ice::Long HurtingPlayerId);

	//! hurt mana
	virtual void HurtMana(float amount);

	//! kill actor
	virtual void Kill();


	//! check trigger on player leave map
	virtual void PlayerLeaveMap(Ice::Long PlayerId);

	//! check trigger on player dead
	virtual void PlayerDead(Ice::Long PlayerId);

	//! check trigger on player move
	virtual void PlayerMoved(Ice::Long PlayerId, const LbaNet::PlayerPosition &startposition,
										const LbaNet::PlayerPosition &endposition);




	//! accessor
	bool GetAggresive()
	{return _aggresive;}

	//! accessor
	void SetAggresive(bool v)
	{_aggresive = v;}


	//! accessor
	float GetLife()
	{return _lifeinfo.MaxLife;}

	//! accessor
	void SetLife(float v)
	{_lifeinfo.MaxLife = _lifeinfo.CurrentLife = v;}

	//! accessor
	float GetMana()
	{return _lifeinfo.MaxMana;}

	//! accessor
	void SetMana(float v)
	{_lifeinfo.MaxMana = _lifeinfo.CurrentMana = v;}

	//! accessor
	float GetArmor()
	{return _armor;}

	//! accessor
	void SetArmor(float v)
	{_armor = v;}

	//! accessor
	float GetWeapon1Power()
	{return _weapon1power;}

	//! accessor
	void SetWeapon1Power(float v)
	{_weapon1power = v;}

	//! accessor
	float GetWeapon2Power()
	{return _weapon2power;}

	//! accessor
	void SetWeapon2Power(float v)
	{_weapon2power = v;}

	//! accessor
	float GetAttackActiDist()
	{return _attack_activation_distance;}

	//! accessor
	void SetAttackActiDist(float v)
	{_attack_activation_distance = v;}

	//! accessor
	float GetAttackActiDistDiscrete()
	{return _attack_activation_distance_discrete;}

	//! accessor
	void SetAttackActiDistDiscrete(float v)
	{_attack_activation_distance_discrete = v;}

	//! accessor
	float GetAttackActiDistHidden()
	{return _attack_activation_distance_hidden;}

	//! accessor
	void SetAttackActiDistHidden(float v)
	{_attack_activation_distance_hidden = v;}

	//! accessor
	float GetAttackStopDist()
	{return _stop_attack_distance;}

	//! accessor
	void SetAttackStopDist(float v)
	{_stop_attack_distance = v;}

	//! accessor
	float GetRespawnTimeInSec()
	{return _respwantime;}

	//! accessor
	void SetRespawnTimeInSec(float v)
	{_respwantime = v;}


	//! accessor
	ConditionBasePtr GetAttackActivationCondition()
	{return _attack_activation_condition;}

	//! accessor
	void SetAttackActivationCondition(ConditionBasePtr v)
	{_attack_activation_condition = v;}


	//! accessor
	ActionBasePtr GetActionOnAttackActivation()
	{return _action_on_attack_activation;}

	//! accessor
	void SetActionOnAttackActivation(ActionBasePtr v)
	{_action_on_attack_activation = v;}

	//! accessor
	void AddGivenItem(long id, int min, int max, float proba, int group);

	//! accessor
	LbaNet::ContainedItemList &GetGivenItemList()
	{return _itemsgivenatdeath;}


	//! target player
	virtual void ForceTargetAttackPlayer(Ice::Long PlayerId);

	//! stop target player
	virtual void ForceStopAttackTarget(Ice::Long PlayerId);


protected:

	//! return the build class
	virtual std::string LuaBuildClass();

	//! write extra lua
	virtual void ExtraLua(std::ofstream & file, const std::string & name);

	//! target player
	void TargetPlayer(Ice::Long PlayerId);

	//! stop target player
	void StopTarget();

	//! start fight
	void StartFight(Ice::Long TargetedPlayerId);

	//! die
	void Die();

	//! respawn
	void Respawn();

	//! process child
	virtual void ProcessChild(double tnow, float tdiff);


	//! play hurt animation
	void PlayHurt(int hurttype);

	//! get given items
	LbaNet::ItemsMap GetGivenItems();


	//! target player
	void TargetAttackPlayer(Ice::Long PlayerId);

	//! stop target player
	void StopAttackTarget(Ice::Long PlayerId);


	//! change NPC state
	//! 1-> Normal, 2-> hurt, 3-> dead, 4-> chasing, 5-> come back
	//! return true if change was succesfull
	bool ChangeState(int newstate);


	//! agent come back to normal
	void EndChasing();

	//! check if update client
	void UpdateClients(double tnow, float tdiff);
	bool ShouldforceUpdate();



protected:
	long						_npcnametextid;
	bool						_simpledialog;
	DialogPartPtr				_rootdialog;

	std::vector<Ice::Long>		_targetedplayers;
	std::vector<Ice::Long>		_hurtingplayers;


	bool						_aggresive;

	LbaNet::LifeManaInfo		_lifeinfo;

	float						_armor;
	float						_weapon1power;
	float						_weapon2power;

	float						_attack_activation_distance;
	float						_attack_activation_distance_discrete;
	float						_attack_activation_distance_hidden;
	float						_stop_attack_distance;

	ConditionBasePtr			_attack_activation_condition;
	ActionBasePtr				_action_on_attack_activation;

	float						_respwantime;
	double						_dietime;

	LbaNet::ContainedItemList	_itemsgivenatdeath;

	boost::shared_ptr<CharacterStateBase>		_agentState;
	int											_agentstatenum;
	int											_savedstate;
	std::string									_savedanim;

	Ice::Long									_targetedattackplayer;

	LbaNet::PlayerMoveInfo						_lastupdate;
	LbaNet::PlayerMoveInfo						_currentupdate;
	float										_oldtdiff;
	bool										_freemove;

	double										_lastchasingchecktime;
	float										_lastchasingcheckposX;
	float										_lastchasingcheckposY;
	float										_lastchasingcheckposZ;
};

#endif
