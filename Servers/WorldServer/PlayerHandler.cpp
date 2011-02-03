#include "PlayerHandler.h"
#include "InventoryItemHandler.h"
#include "SynchronizedTimeHandler.h"
#include "MapHandler.h"
#include "Lba1ModelMapHandler.h"
#include "InventoryItemHandler.h"
#define	_CUSTOM_OFFSET_	10000000


/***********************************************************
constructor
***********************************************************/
PlayerHandler::PlayerHandler(long clientid, ClientProxyBasePtr proxy,
						boost::shared_ptr<DatabaseHandlerBase> dbH,
						const std::string &worldname,
						const LbaNet::SavedWorldInfo & savedinfo,
						const LbaNet::ObjectExtraInfo& extrainfo)
	: _clientid(clientid), _proxy(proxy), 
		_dbH(dbH), _currentinfo(savedinfo), _worldname(worldname),
		_extrainfo(extrainfo), _ready(false), _saved(false)
{
	// get quest information
	if(_dbH) 
		_dbH->GetQuestInfo(_worldname, _clientid, _questStarted, _questFinished);


	//TODO - remove that and replace by a raising place system
	_spawningIno = savedinfo.ppos;




	//unfold inventory information and shortcut information
	{
		// inventory info
		{
			LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.begin();
			LbaNet::ItemsMap::iterator end = _currentinfo.inventory.InventoryStructure.end();
			for(; it != end; ++it)
			{
				if(it->first >= _CUSTOM_OFFSET_) // custom item
				{
					it->second.Info.IconName = "letter";
					it->second.Info.DescriptionId = 0;
					it->second.Info.Max = 1;
					it->second.Info.Price = 0;

					it->second.Info.Type = 8;
					it->second.Info.Ephemere = false;
					it->second.Info.Id = it->first;

					if(_dbH)
					{
						LbaNet::LetterInfo info = _dbH->GetLetterInfo(it->first-_CUSTOM_OFFSET_); //TODO- check if correct
						it->second.Info.DescriptionTextExtra = "From: " + info.From + " Subject: " + info.Subject;
					}
				}
				else
				{
					it->second.Info = InventoryItemHandler::getInstance()->GetItemInfo((long)it->first);
				}
			}
		}

		// complete shortcut info
		{
			LbaNet::ShortcutsSeq::iterator it = _currentinfo.inventory.UsedShorcuts.begin();
			LbaNet::ShortcutsSeq::iterator end = _currentinfo.inventory.UsedShorcuts.end();
			for(; it != end; ++it)
			{
				if(it->Id >= 0)
					*it = InventoryItemHandler::getInstance()->GetItemInfo((long)it->Id);
			}
		}
	}



	// check outfit/weapon
	if(_currentinfo.EquipedOutfit < 0)
	{
		// check if we have corresponding outfit in inventory - if so equip it
		LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.begin();
		LbaNet::ItemsMap::iterator end = _currentinfo.inventory.InventoryStructure.end();
		for(; it != end; ++it)
		{
			if(it->second.Info.Type == 9)
			{
				if(it->second.Info.StringFlag == _currentinfo.model.Outfit)
				{
					_currentinfo.EquipedOutfit = it->first;
					break;
				}
			}
		}
	}

	if(_currentinfo.EquipedWeapon < 0)
	{
		// check if we have corresponding weapon in inventory - if so equip it
		LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.begin();
		LbaNet::ItemsMap::iterator end = _currentinfo.inventory.InventoryStructure.end();
		for(; it != end; ++it)
		{
			if(it->second.Info.Type == 4)
			{
				if(it->second.Info.StringFlag == _currentinfo.model.Weapon)
				{
					_currentinfo.EquipedWeapon = it->first;
					break;
				}
			}
		}
	}

	_currentinfo.lifemana.Display = true;
	_extrainfo.Display = true;


	// create model and state classes
	UpdateStateModeClass();
}



/***********************************************************
destructor
***********************************************************/
PlayerHandler::~PlayerHandler(void)
{
	// save info back in the database before closing
	SaveCurrentInfo();

	if(_dbH)
		_dbH->QuitWorld(_worldname, _clientid);
}


/***********************************************************
get current size of inventory
***********************************************************/
int PlayerHandler::GetInventorySize()
{
	return _currentinfo.inventory.InventorySize;
}

/***********************************************************
update player life and mana
***********************************************************/
void PlayerHandler::UpdateLifeMana(const LbaNet::LifeManaInfo & lifeinfo)
{
	_currentinfo.lifemana = lifeinfo;
}


/***********************************************************
update current position in the world
***********************************************************/
void PlayerHandler::UpdatePositionInWorld(const LbaNet::PlayerPosition& Position)
{
	// only update when on same map
	if(_currentinfo.ppos.MapName != Position.MapName)
		return;

	_currentinfo.ppos = Position;
}

/***********************************************************
update current position in the world
***********************************************************/
void PlayerHandler::Teleport(const LbaNet::PlayerPosition& Position)
{
	_currentinfo.ppos = Position;
	_ready = false;	// player not ready to play yet

	// player goes back to normal state when changing map
	_currentinfo.model.State = LbaNet::StNormal;
	UpdateStateModeClass();


	//TODO - remove that and replace by a raising place system
	_spawningIno = Position;
}


/***********************************************************
start a quest
***********************************************************/
void PlayerHandler::StartQuest(long questid)
{
	std::vector<long>::iterator it = std::find(_questStarted.begin(), _questStarted.end(), questid);
	if(it == _questStarted.end())
		_questStarted.push_back(questid);
}

/***********************************************************
finish a quest
***********************************************************/
void PlayerHandler::FinishQuest(long questid)
{
	std::vector<long>::iterator it = std::find(_questStarted.begin(), _questStarted.end(), questid);
	if(it != _questStarted.end())
		_questStarted.erase(it);

	_questFinished.push_back(questid);
}



/***********************************************************
save current info in database
***********************************************************/
void PlayerHandler::SaveCurrentInfo()
{
	if(_dbH)
	{
		// update current position in the world
		_dbH->UpdatePositionInWorld(_currentinfo.ppos, _worldname, _clientid);

		// update player inventory structure
		_dbH->UpdateInventory(_currentinfo.inventory, _worldname, _clientid);

		// update player life
		_dbH->UpdateLife(_currentinfo.lifemana, _worldname, _clientid);

		// set quest information
		_dbH->SetQuestInfo(_worldname, _clientid, _questStarted, _questFinished);

		//set player model
		_dbH->UpdateModel(_currentinfo.model, _worldname, _clientid, 
							_currentinfo.EquipedWeapon, _currentinfo.EquipedOutfit);
	}
}



/***********************************************************
get player current map
***********************************************************/
std::string PlayerHandler::GetCurrentMap()
{
	return _currentinfo.ppos.MapName;
}


/***********************************************************
get player position
***********************************************************/
LbaNet::PlayerPosition PlayerHandler::GetPlayerPosition()
{
	return _currentinfo.ppos;
}

/***********************************************************
get player mode string
***********************************************************/
std::string PlayerHandler::GetPlayerModeString()
{
	return _currentinfo.model.Mode;
}


/***********************************************************
//!  update player stance
//! return true if state has been updated
***********************************************************/
bool PlayerHandler::UpdatePlayerStance(LbaNet::ModelStance NewStance, LbaNet::ModelInfo & returnmodel,
										bool changefromserver)
{

	//check if stance change is legal
	if(_currentstate && _currentstate->AllowChangeMode())
	{
		std::string newmode = "Normal";
		switch(NewStance)
		{
			case LbaNet::StanceNormal:
				newmode = "Normal";
			break;

			case LbaNet::StanceSporty:
				newmode = "Sport";
			break;

			case LbaNet::StanceAggresive:
				newmode = "Angry";
			break;

			case LbaNet::StanceDiscrete:
				newmode = "Discrete";
			break;

			case LbaNet::StanceProtopack:
				if(changefromserver)
					newmode = "Protopack";
			break;

			case LbaNet::StanceHorse:
				if(changefromserver)
					newmode = "Horse";
			break;

			case LbaNet::StanceDinofly:
				if(changefromserver)
					newmode = "Dinofly";
			break;
		}

		// check if stance is already there
		if(_currentinfo.model.Mode != newmode)
		{
			_currentinfo.model.Mode = newmode;
			_currentinfo.model.State = LbaNet::StNormal;
			UpdateStateModeClass();
			returnmodel = _currentinfo.model;
			return true;
		}
	}

	
	return false;
}


/***********************************************************
//!  update player state
//! return true if state has been updated
***********************************************************/
bool PlayerHandler::UpdatePlayerState(LbaNet::ModelState NewState,LbaNet::ModelInfo & returnmodel)
{
	//check if state is legal
	if(_currentstate && _currentstate->ChangeLegal(NewState))
	{
		// if so check if already on this state
		if(_currentinfo.model.State != NewState)
		{
			_currentinfo.model.State = NewState;
			UpdateStateModeClass();
			returnmodel = _currentinfo.model;
			return true;
		}
	}

	return false;
}





/***********************************************************
//!  update player weapon
//! return true if state has been updated
***********************************************************/
bool PlayerHandler::UpdatePlayerWeapon(const std::string & weapon, LbaNet::ModelInfo & returnmodel, 
										long ItemId)
{
	//check if state is legal
	if(_currentstate && _currentstate->AllowChangeMode())
	{
		_currentinfo.EquipedWeapon = ItemId;

		// if so check if already on this state
		if(_currentinfo.model.Weapon != weapon)
		{
			_currentinfo.model.Weapon = weapon;
			return UpdatePlayerState(LbaNet::StPrepareWeapon, returnmodel);
		}
	}

	return false;
}

/***********************************************************
//!  update player outfit
//! return true if state has been updated
***********************************************************/
bool PlayerHandler::UpdatePlayerOutfit(const std::string & outfit,	LbaNet::ModelInfo & returnmodel, 
										long ItemId)
{
	//check if state is legal
	if(_currentstate && _currentstate->AllowChangeMode())
	{
		_currentinfo.EquipedOutfit = ItemId;

		// if so check if already on this state
		if(_currentinfo.model.Outfit != outfit)
		{
			_currentinfo.model.Outfit = outfit;
			UpdateStateModeClass();
			returnmodel = _currentinfo.model;
			return true;
		}
	}

	return false;
}



/***********************************************************
save player state
***********************************************************/
void PlayerHandler::SavePlayerState()
{
	_saved = true;
	_savedState = _currentinfo.model.State;
}

/***********************************************************
restore player state
***********************************************************/
bool PlayerHandler::RestorePlayerState(LbaNet::ModelInfo & returnmodel)
{
	if(_saved)
	{
		_saved = false;
		_currentinfo.model.State = _savedState;
		UpdateStateModeClass();
		returnmodel = _currentinfo.model;
		return true;
	}

	return false;
}




/***********************************************************
update state and mode class from modelinfo
***********************************************************/
void PlayerHandler::UpdateStateModeClass()
{
	if(_currentinfo.model.Mode == "Normal")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new NormalCharacterMode());
	}

	if(_currentinfo.model.Mode == "Sport")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new SportyCharacterMode());
	}

	if(_currentinfo.model.Mode == "Angry")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new AggresiveCharacterMode());
	}

	if(_currentinfo.model.Mode == "Discrete")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new DiscreteCharacterMode());
	}		

	if(_currentinfo.model.Mode == "Protopack")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new ProtopackCharacterMode());
	}

	if(_currentinfo.model.Mode == "Horse")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new HorseCharacterMode());
	}

	if(_currentinfo.model.Mode == "Dinofly")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new DinoflyCharacterMode());
	}		

	switch(_currentinfo.model.State)
	{
		case LbaNet::StNormal:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateNormal());
		}
		break;
		case LbaNet::StDying:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateDying());			
		}
		break; 
		case LbaNet::StDrowning:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateDrowning());			
		}
		break; 
		case LbaNet::StDrowningGas:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateDrowningGas());		
		}
		break; 
		case LbaNet::StBurning:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateBurning());						
		}
		break; 
		case LbaNet::StSmallHurt:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateSmallHurt());						
		}
		break; 
		case LbaNet::StMediumHurt:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateMediumHurt());						
		}
		break; 
		case LbaNet::StBigHurt:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateBigHurt());						
		}
		break; 
		case LbaNet::StHurtFall:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateHurtFall());						
		}
		break; 
		case LbaNet::StFinishedFall:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateFinishedFall());						
		}
		break;	
		case LbaNet::StFalling:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateFalling());					
		}
		break; 
		case LbaNet::StJumping:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateJumping());						
		}
		break; 
		case LbaNet::StMovingObject:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateMovingObject());						
		}
		break; 
		case LbaNet::StRestrictedMovingObject:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateRestrictedMovingObject());						
		}
		break; 
		case LbaNet::StUseWeapon:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateUseWeapon());						
		}
		break; 
		case LbaNet::StImmune:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateImmune());						
		}
		break; 
		case LbaNet::StProtectedHurt:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateProtectedHurt());						
		}
		break; 
		case LbaNet::StHidden:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateHidden());						
		}
		break; 
		case LbaNet::StScripted:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateScripted());						
		}
		break;
		case LbaNet::StFighting:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateFighting());						
		}
		break;
		case LbaNet::StPrepareWeapon:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StatePrepareWeapon());						
		}
		break;
	}
}


/***********************************************************
get the place to respawn in case of death
***********************************************************/
LbaNet::PlayerPosition PlayerHandler::GetSpawningPlace()
{
	return _spawningIno;
}


/***********************************************************
	//!  raised player from dead
	//! return true if raised
***********************************************************/
bool PlayerHandler::RaiseFromDead(LbaNet::ModelInfo & returnmodel)
{
	//TODO - check if raise is legal
	if(_currentstate && _currentstate->IsDead())
	{
		_currentinfo.model.State = LbaNet::StNormal;
		UpdateStateModeClass();
		returnmodel = _currentinfo.model;

		// update life and mana
		_currentinfo.lifemana.CurrentLife = _currentinfo.lifemana.MaxLife;
		_currentinfo.lifemana.CurrentMana = _currentinfo.lifemana.MaxMana;


		return true;
	}

	return false;
}


/***********************************************************
player update on the shorcut
***********************************************************/
void PlayerHandler::UpdateShortcut(int Position, long ItemId)
{
	LbaNet::ItemInfo info;
	info.Id = -1;
	if(ItemId >= 0) 
		info = InventoryItemHandler::getInstance()->GetItemInfo(ItemId);

	if(Position >= 0 && Position < (int)_currentinfo.inventory.UsedShorcuts.size())
		_currentinfo.inventory.UsedShorcuts[Position] = info;
}


/***********************************************************
player switch item
***********************************************************/
void PlayerHandler::SwitchItem(long ItemId, int NewPosition)
{
	LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.find(ItemId);
	if(it != _currentinfo.inventory.InventoryStructure.end())
	{
		if(NewPosition >= 0 && NewPosition < _currentinfo.inventory.InventorySize)
			it->second.Position = NewPosition;
	}
}

/***********************************************************
Player Create Letter
***********************************************************/
void PlayerHandler::CreateLetter(const std::string & subject, const std::string & message)
{
	//check if inventory full
	if((int)_currentinfo.inventory.InventoryStructure.size() >= _currentinfo.inventory.InventorySize)
	{
		//inform client
		if(_proxy)
		{
			LbaNet::EventsSeq toplayer;
			LbaNet::GuiUpdatesSeq paramseq;
			paramseq.push_back(new LbaNet::SystemMessageUpdate("Inventory full", "Inventory full - can not create letter!"));
			toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"main", paramseq));

			IceUtil::ThreadPtr t = new EventsSender(toplayer, _proxy);
			t->start();	
		}


		return;
	}

	if(_dbH)
	{
		long id = _dbH->AddLetter(_clientid, subject, message);
		if(id >= 0)
		{
			LbaNet::ItemPosInfo newitem;
			newitem.Position = -1;
			newitem.Count = 1;
			newitem.Info.IconName = "letter";
			newitem.Info.DescriptionId = 0;
			newitem.Info.Max = 1;
			newitem.Info.Price = 0;
			newitem.Info.Type = 8;
			newitem.Info.Ephemere = false;
			newitem.Info.DescriptionTextExtra = "From: " + _extrainfo.Name + " Subject: " + subject;
			newitem.Info.Id = id + _CUSTOM_OFFSET_;

			_currentinfo.inventory.InventoryStructure[id] = newitem;

			//send new item to client
			if(_proxy)
			{
				LbaNet::EventsSeq toplayer;
				LbaNet::GuiUpdatesSeq paramseq;
				paramseq.push_back(new LbaNet::UpdateInventoryItem(newitem));
				toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														"InventoryBox", paramseq));

				IceUtil::ThreadPtr t = new EventsSender(toplayer, _proxy);
				t->start();	
			}
		}
	}
}

/***********************************************************
Player Destroy Item
***********************************************************/
void PlayerHandler::DestroyItem(long ItemId)
{
	LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.find(ItemId);
	if(it != _currentinfo.inventory.InventoryStructure.end())
	{
		it->second.Count = 0;

		//send destroy item to client
		if(_proxy)
		{
			LbaNet::EventsSeq toplayer;
			LbaNet::GuiUpdatesSeq paramseq;
			paramseq.push_back(new LbaNet::UpdateInventoryItem(it->second));
			toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"InventoryBox", paramseq));

			IceUtil::ThreadPtr t = new EventsSender(toplayer, _proxy);
			t->start();	
		}	

		// if letter then delete it
		if(it->second.Info.Type == 8 && _dbH)
			_dbH->DeleteLetter(ItemId-_CUSTOM_OFFSET_);

		// remove from inventory
		_currentinfo.inventory.InventoryStructure.erase(it);
	}
}


	
/***********************************************************
get info about an item
***********************************************************/
LbaNet::ItemPosInfo PlayerHandler::GetItemInfo(long ItemId)
{
	LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.find(ItemId);
	if(it != _currentinfo.inventory.InventoryStructure.end())
		return it->second;


	LbaNet::ItemPosInfo res;
	res.Info.Id = -1;
	return res;
}

/***********************************************************
item consumed - return true if life is updated
***********************************************************/
bool PlayerHandler::ConsumeItem(long ItemId)
{
	bool updatelife = false;

	LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.find(ItemId);
	if(it != _currentinfo.inventory.InventoryStructure.end())
	{
		bool used = false;

		switch(it->second.Info.Flag)
		{
			case 1: // life potion
			{
				if(_currentinfo.lifemana.CurrentLife == _currentinfo.lifemana.MaxLife)
					return updatelife; // do nothing if life is full

				float deltalife = (it->second.Info.Effect * _currentinfo.lifemana.MaxLife / 100.0f);
				_currentinfo.lifemana.CurrentLife += deltalife;
				if(_currentinfo.lifemana.CurrentLife > _currentinfo.lifemana.MaxLife)
					_currentinfo.lifemana.CurrentLife = _currentinfo.lifemana.MaxLife;

				used = true;
				updatelife = true;
			}
			break;
			case 2: // mana potion
			{
				if(_currentinfo.lifemana.CurrentMana == _currentinfo.lifemana.MaxMana)
					return updatelife; // do nothing if mana is full

				float deltaMana = (it->second.Info.Effect * _currentinfo.lifemana.MaxMana / 100.0f);
				_currentinfo.lifemana.CurrentMana += deltaMana;
				if(_currentinfo.lifemana.CurrentMana > _currentinfo.lifemana.MaxMana)
					_currentinfo.lifemana.CurrentMana = _currentinfo.lifemana.MaxMana;

				used = true;
				updatelife = true;
			}
			break;
			case 3: // life and mana potion
			{
				if(_currentinfo.lifemana.CurrentMana == _currentinfo.lifemana.MaxMana
					&& _currentinfo.lifemana.CurrentLife == _currentinfo.lifemana.MaxLife)
					return updatelife; // do nothing if life & mana is full

				float deltalife = (it->second.Info.Effect * _currentinfo.lifemana.MaxLife / 100.0f);
				_currentinfo.lifemana.CurrentLife += deltalife;
				if(_currentinfo.lifemana.CurrentLife > _currentinfo.lifemana.MaxLife)
					_currentinfo.lifemana.CurrentLife = _currentinfo.lifemana.MaxLife;

				float deltaMana = (it->second.Info.Effect * _currentinfo.lifemana.MaxMana / 100.0f);
				_currentinfo.lifemana.CurrentMana += deltaMana;
				if(_currentinfo.lifemana.CurrentMana > _currentinfo.lifemana.MaxMana)
					_currentinfo.lifemana.CurrentMana = _currentinfo.lifemana.MaxMana;

				used = true;
				updatelife = true;
			}
			break;

			case 4: // life potion
			{
				if(_currentinfo.lifemana.CurrentLife == _currentinfo.lifemana.MaxLife)
					return updatelife; // do nothing if life is full

				float deltalife = it->second.Info.Effect;
				_currentinfo.lifemana.CurrentLife += deltalife;
				if(_currentinfo.lifemana.CurrentLife > _currentinfo.lifemana.MaxLife)
					_currentinfo.lifemana.CurrentLife = _currentinfo.lifemana.MaxLife;

				used = true;
				updatelife = true;
			}
			break;
			case 5: // mana potion
			{
				if(_currentinfo.lifemana.CurrentMana == _currentinfo.lifemana.MaxMana)
					return updatelife; // do nothing if mana is full

				float deltaMana = it->second.Info.Effect;
				_currentinfo.lifemana.CurrentMana += deltaMana;
				if(_currentinfo.lifemana.CurrentMana > _currentinfo.lifemana.MaxMana)
					_currentinfo.lifemana.CurrentMana = _currentinfo.lifemana.MaxMana;

				used = true;
				updatelife = true;
			}
			break;
			case 6: // life and mana potion
			{
				if(_currentinfo.lifemana.CurrentMana == _currentinfo.lifemana.MaxMana
					&& _currentinfo.lifemana.CurrentLife == _currentinfo.lifemana.MaxLife)
					return updatelife; // do nothing if life & mana is full

				float deltalife = it->second.Info.Effect;
				_currentinfo.lifemana.CurrentLife += deltalife;
				if(_currentinfo.lifemana.CurrentLife > _currentinfo.lifemana.MaxLife)
					_currentinfo.lifemana.CurrentLife = _currentinfo.lifemana.MaxLife;

				float deltaMana = it->second.Info.Effect;
				_currentinfo.lifemana.CurrentMana += deltaMana;
				if(_currentinfo.lifemana.CurrentMana > _currentinfo.lifemana.MaxMana)
					_currentinfo.lifemana.CurrentMana = _currentinfo.lifemana.MaxMana;

				used = true;
				updatelife = true;
			}
			break;
		}

		if(used)
		{
			// decrease item count and inform client
			it->second.Count -= 1;

			if(_proxy)
			{
				LbaNet::EventsSeq toplayer;
				LbaNet::GuiUpdatesSeq paramseq;
				paramseq.push_back(new LbaNet::UpdateInventoryItem(it->second));
				toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														"InventoryBox", paramseq));

				IceUtil::ThreadPtr t = new EventsSender(toplayer, _proxy);
				t->start();	
			}	

			if(it->second.Count == 0) // delete item if empty
				_currentinfo.inventory.InventoryStructure.erase(it);
		}
	}

	return updatelife;
}


/***********************************************************
remove ephemere from player inventory
***********************************************************/
void PlayerHandler::RemoveEphemere()
{
	LbaNet::GuiUpdatesSeq paramseq;
	LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.begin();

	while(it != _currentinfo.inventory.InventoryStructure.end())
	{
		if(it->second.Info.Ephemere)
		{
			it->second.Count = 0;
			paramseq.push_back(new LbaNet::UpdateInventoryItem(it->second));

			it = _currentinfo.inventory.InventoryStructure.erase(it);
		}
		else
			++it;
	}

	// inform client
	if(paramseq.size() > 0)
	{
		if(_proxy)
		{
			LbaNet::EventsSeq toplayer;
			toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"InventoryBox", paramseq));

			IceUtil::ThreadPtr t = new EventsSender(toplayer, _proxy);
			t->start();	
		}
	}

}


/***********************************************************
update player life
***********************************************************/
bool PlayerHandler::DeltaUpdateLife(float update)
{
	_currentinfo.lifemana.CurrentLife += update;
	if(_currentinfo.lifemana.CurrentLife > _currentinfo.lifemana.MaxLife)
		_currentinfo.lifemana.CurrentLife = _currentinfo.lifemana.MaxLife;

	if(_currentinfo.lifemana.CurrentLife <= 0) // die
	{
		_currentinfo.lifemana.CurrentLife = 0;
		return true;
	}

	return false;
}


/***********************************************************
update player mana
***********************************************************/
bool PlayerHandler::DeltaUpdateMana(float update)
{
	_currentinfo.lifemana.CurrentMana += update;
	if(_currentinfo.lifemana.CurrentMana > _currentinfo.lifemana.MaxMana)
		_currentinfo.lifemana.CurrentMana = _currentinfo.lifemana.MaxMana;

	if(_currentinfo.lifemana.CurrentMana <= 0) //oom
	{
		_currentinfo.lifemana.CurrentMana = 0;
		return true;
	}

	return false;
}


/***********************************************************
get player physcial size
***********************************************************/
void PlayerHandler::GetPlayerPhysicalSize(float &sX, float &sY, float &sZ)
{
	// set default size
	sX = 1;
	sY = 5;
	sZ = 1;

	if(_currentinfo.model.TypeRenderer == LbaNet::RenderLba1M)
	{
		int resWeaponType;
		ModelSize resSize;

		int res = Lba1ModelMapHandler::getInstance()->GetModelExtraInfo(_currentinfo.model.ModelName,
																		_currentinfo.model.Outfit,
																		_currentinfo.model.Weapon,
																		_currentinfo.model.Mode,
																		resWeaponType, resSize);

		if(res >= 0)
		{
			sX = resSize.X;
			sY = resSize.Y;
			sZ = resSize.Z;
		}
	}
}


/***********************************************************
Get current power
***********************************************************/
float PlayerHandler::GetPower()
{
	if(_currentinfo.EquipedWeapon >= 0)
		return InventoryItemHandler::getInstance()->GetItemInfo(_currentinfo.EquipedWeapon).Effect;

	return 0;
}

/***********************************************************
Get current armor
***********************************************************/
float PlayerHandler::GetArmor()
{
	if(_currentinfo.EquipedOutfit >= 0)
		return InventoryItemHandler::getInstance()->GetItemInfo(_currentinfo.EquipedOutfit).Effect;

	return 0;
}