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

#ifndef _PLAYER_HANDLER_H__
#define _PLAYER_HANDLER_H__


#include <boost/shared_ptr.hpp>
#include <ClientInterface.h>

#include "DatabaseHandlerBase.h"
#include "CharacterStates.h"
#include "CharacterModes.h"
#include "ClientProxyHandler.h"


//! take care of a specific player inside the server
class PlayerHandler
{
public:
	//! constructor
	PlayerHandler(long clientid, ClientProxyBasePtr proxy,
							boost::shared_ptr<DatabaseHandlerBase> dbH,
							const std::string &worldname,
							const LbaNet::SavedWorldInfo & savedinfo,
							const LbaNet::ObjectExtraInfo& extrainfo);
	
	//! destructor
	~PlayerHandler(void);


	//! accessor on id
	Ice::Long GetId() {return _clientid;}

	//! accessor on proxy
	ClientProxyBasePtr GetProxy() {return _proxy;}

	//! accessor on model
	LbaNet::ModelInfo GetModelInfo() {return _currentinfo.model;}

	//! get inventory
	LbaNet::ItemsMap GetInventory() {return _currentinfo.inventory.InventoryStructure;}

	// get shortcuts
	LbaNet::ShortcutsSeq GetShorcuts() {return _currentinfo.inventory.UsedShorcuts;}

	// player update on the shorcut
	void UpdateShortcut(int Position, long ItemId);

	// get current size of inventory
	int GetInventorySize();


	//! get player current map
	std::string GetCurrentMap();

	//! get player extra info
	LbaNet::LifeManaInfo GetLifeManaInfo()
	{ return _currentinfo.lifemana;}

	//! update player life and mana
	void UpdateLifeMana(const LbaNet::LifeManaInfo & lifeinfo);

	// update current position in the world
	void UpdatePositionInWorld(const LbaNet::PlayerPosition& Position);

	// update current position in the world
	void Teleport(const LbaNet::PlayerPosition& Position);

	// start a quest
	void StartQuest(long questid);

	// finish a quest
	void FinishQuest(long questid);

	//! save current info in database
	void SaveCurrentInfo();

	//! get player info
	LbaNet::SavedWorldInfo GetInfo(){ return _currentinfo;}

	//!  get player position
	LbaNet::PlayerPosition GetPlayerPosition();

	//! get player mode string
	std::string GetPlayerModeString();

	//!  update player stance
	//! return true if state has been updated
	bool UpdatePlayerStance(LbaNet::ModelStance NewStance, LbaNet::ModelInfo & returnmodel,
								bool changefromserver = false);


	//!  update player state
	//! return true if state has been updated
	bool UpdatePlayerState(LbaNet::ModelState NewState, LbaNet::ModelInfo & returnmodel);


	//!  update player weapon
	//! return true if state has been updated
	bool UpdatePlayerWeapon(const std::string & weapon,	LbaNet::ModelInfo & returnmodel, long ItemId);

	//!  update player outfit
	//! return true if state has been updated
	bool UpdatePlayerOutfit(const std::string & outfit,	LbaNet::ModelInfo & returnmodel, long ItemId);


	//!  save player state
	void SavePlayerState();

	//!  restore player state
	bool RestorePlayerState(LbaNet::ModelInfo & returnmodel);



	//! set player extra info
	void SetExtraInfo(const LbaNet::ObjectExtraInfo& extrainfo)
	{_extrainfo = extrainfo;}

	//! get player extra info
	LbaNet::ObjectExtraInfo GetExtraInfo()
	{ return _extrainfo;}



	//! get the place to respawn in case of death
	LbaNet::PlayerPosition GetSpawningPlace();

	//!  raised player from dead
	//! return true if raised
	bool RaiseFromDead(LbaNet::ModelInfo & returnmodel);

	//! set player ready to play
	void SetReady()
	{_ready = true;}

	//! ask if player ready to play
	bool IsReady()
	{return _ready;}


	//! player switch item
	void SwitchItem(long ItemId, int NewPosition);

	//! Player Create Letter
	void CreateLetter(const std::string & subject, const std::string & message);

	//! Player Destroy Item
	void DestroyItem(long ItemId);

	//! get info about an item
	LbaNet::ItemPosInfo GetItemInfo(long ItemId);

	//! item consumed - return true if life is updated
	bool ConsumeItem(long ItemId);

	//! remove ephemere from player inventory
	void RemoveEphemere();

	//! update player life
	//! return true if no life
	bool DeltaUpdateLife(float update);

	//! update player mana
	//! return true if no mana
	bool DeltaUpdateMana(float update);

	//! get player physcial size
	void GetPlayerPhysicalSize(float &sX, float &sY, float &sZ);

	//! Get current power
	float GetPower();

	//! Get current armor
	float GetArmor();


protected:
	// update state and mode class from modelinfo
	void UpdateStateModeClass();

private:
	long										_clientid;
	ClientProxyBasePtr							_proxy;
	boost::shared_ptr<DatabaseHandlerBase>		_dbH;
	bool										_ready;

	std::string									_worldname;
	LbaNet::SavedWorldInfo						_currentinfo;
	LbaNet::ObjectExtraInfo						_extrainfo;
	LbaNet::PlayerPosition						_spawningIno;

	std::vector<long>							_questStarted;
	std::vector<long>							_questFinished;


	boost::shared_ptr<CharacterModeBase>		_currentmode;
	boost::shared_ptr<CharacterStateBase>		_currentstate;

	bool										_saved;
	LbaNet::ModelState							_savedState;
};

#endif
