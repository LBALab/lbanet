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

	//! target player
	void TargetAttackPlayer(Ice::Long PlayerId);

	//! stop target player
	void StopAttackTarget(Ice::Long PlayerId);



protected:
	long						_npcnametextid;
	bool						_simpledialog;
	DialogPartPtr				_rootdialog;

	std::vector<Ice::Long>		_targetedplayers;
	std::vector<Ice::Long>		_hurtingplayers;


	bool						_killable;
	bool						_fighting;
	bool						_dead;
	LbaNet::LifeManaInfo		_lifeinfo;

	float						_armor;
	float						_weapon1power;
	float						_weapon2power;

	float						_attack_activation_distance;
	float						_attack_activation_distance_discrete;
	float						_attack_activation_distance_hidden;
	ConditionBasePtr			_attack_activation_condition;
	ActionBasePtr				_action_on_attack_activation;

	float						_respwantime;
	double						_dietime;

	std::vector<std::pair<long, int> >	_itemsgivenatdeath;
};

#endif
