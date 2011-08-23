#include "PlayerHandler.h"
#include "InventoryItemHandler.h"
#include "SynchronizedTimeHandler.h"
#include "MapHandler.h"
#include "Lba1ModelMapHandler.h"
#include "InventoryItemHandler.h"
#include "Randomizer.h"
#include "QuestHandler.h"
#include "Quest.h"

#include <math.h>

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
		_extrainfo(extrainfo), _ready(false), _saved(false), _currentchapter(1),
		_currentspeedX(0), _currentspeedY(0), _currentspeedZ(0)
{
	// get quest information
	if(_dbH) 
	{
		_dbH->GetQuestInfo(_worldname, _clientid, _questStarted, _questFinished);

		for(size_t i=0; i< _questStarted.size(); ++i)
		{
			// change chapter if needed
			int chap = QuestHandler::getInstance()->GetQuestChapter(_questStarted[i]);
			if(chap > _currentchapter)
				_currentchapter = chap;
		}

		for(size_t i=0; i< _questFinished.size(); ++i)
		{
			// change chapter if needed
			int chap = QuestHandler::getInstance()->GetQuestChapter(_questFinished[i]);
			if(chap > _currentchapter)
				_currentchapter = chap;
		}
	}


	//TODO - remove that and replace by a raising place system
	_spawningIno = savedinfo.ppos;


	// set default values
	_currentinfo.model.TransX = 0;
	_currentinfo.model.TransY = 0;
	_currentinfo.model.TransZ = 0;
	_currentinfo.model.RotX = 0;
	_currentinfo.model.RotY = 0;
	_currentinfo.model.RotZ = 0;
	_currentinfo.model.ScaleX = 1;
	_currentinfo.model.ScaleY = 1;
	_currentinfo.model.ScaleZ = 1;
	_currentinfo.model.ColorR = 1;
	_currentinfo.model.ColorG = 1;
	_currentinfo.model.ColorB = 1;
	_currentinfo.model.ColorA = 1;
	_currentinfo.model.UseLight = true;
	_currentinfo.model.CastShadow = true;
	_currentinfo.model.UseTransparentMaterial = false;

	_currentinfo.model.ColorMaterialType = 4;
	_currentinfo.model.MatAmbientColorR = -0.2f;
	_currentinfo.model.MatAmbientColorG = -0.2f;
	_currentinfo.model.MatAmbientColorB = -0.2f;
	_currentinfo.model.MatDiffuseColorR = 0.4f;
	_currentinfo.model.MatDiffuseColorG = 0.4f;
	_currentinfo.model.MatDiffuseColorB = 0.4f;
	_currentinfo.model.MatAlpha = 1;
	_currentinfo.model.MatAmbientColorA = 1;			
	_currentinfo.model.MatDiffuseColorA = 1;
	_currentinfo.model.MatSpecularColorR = 0;
	_currentinfo.model.MatSpecularColorG = 0;
	_currentinfo.model.MatSpecularColorB = 0;
	_currentinfo.model.MatSpecularColorA = 1;	
	_currentinfo.model.MatEmissionColorR = 0;
	_currentinfo.model.MatEmissionColorG = 0;
	_currentinfo.model.MatEmissionColorB = 0;
	_currentinfo.model.MatEmissionColorA = 1;
	_currentinfo.model.MatShininess = 0;	


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
					it->second.Info.IconName = "GUI/imagesets/Inventory/letter.png";
					it->second.Info.NameTextId = -1;
					it->second.Info.DescriptionId = -1;
					it->second.Info.LongDescriptionId = -1;
					it->second.Info.Max = 1;
					it->second.Info.BuyPrice = 0;
					it->second.Info.SellPrice = 0;

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

	// fix issues when player is dead and disconnect
	if(_currentinfo.lifemana.CurrentLife <= 0)
		_currentinfo.lifemana.CurrentLife = _currentinfo.lifemana.MaxLife; 


	// reinit model colors
	_currentinfo.model.OutfitColor = -1;
	_currentinfo.model.WeaponColor = -1;
	_currentinfo.model.MountSkinColor = -1;
	_currentinfo.model.MountHairColor = -1;
	if(_currentinfo.EquipedWeapon >= 0)
	{
		LbaNet::ItemInfo iinfo = InventoryItemHandler::getInstance()->GetItemInfo((long)_currentinfo.EquipedWeapon);
		_currentinfo.model.WeaponColor = iinfo.Color1;
	}
	if(_currentinfo.EquipedOutfit >= 0)
	{
		LbaNet::ItemInfo iinfo = InventoryItemHandler::getInstance()->GetItemInfo((long)_currentinfo.EquipedOutfit);
		_currentinfo.model.OutfitColor = iinfo.Color1;
	}
	if(_currentinfo.EquipedMount >= 0)
	{
		LbaNet::ItemInfo iinfo = InventoryItemHandler::getInstance()->GetItemInfo((long)_currentinfo.EquipedMount);
		_currentinfo.model.MountSkinColor = iinfo.Color1;
		_currentinfo.model.MountHairColor = iinfo.Color2;
	}


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
void PlayerHandler::UpdatePositionInWorld(const LbaNet::PlayerPosition& Position,
											float speedX, float speedY, float speedZ)
{
	// only update when on same map
	if(_currentinfo.ppos.MapName != Position.MapName)
		return;

	// keep track of last position
	SetLastPosition(LbaVec3(_currentinfo.ppos.X, _currentinfo.ppos.Y, _currentinfo.ppos.Z));


	_currentinfo.ppos = Position;

	_currentspeedX = speedX;
	_currentspeedY = speedY;
	_currentspeedZ = speedZ;
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
	{
		_questStarted.push_back(questid);

		// change chapter if needed
		int chap = QuestHandler::getInstance()->GetQuestChapter(questid);
		if(chap > _currentchapter)
			_currentchapter = chap;

		//inform client
		if(_proxy)
		{
			LbaNet::EventsSeq toplayer;
			LbaNet::GuiUpdatesSeq paramseq;
			QuestInfo qinfo;
			qinfo.Id = questid;
			QuestPtr qptr = QuestHandler::getInstance()->GetQuest(questid);
			qinfo.ChapterTextId = qptr->GetChapter();
			qinfo.QuestAreaTextId = qptr->GetLocationTextId();	
			qinfo.TittleTextId = qptr->GetTitleTextId();
			qinfo.DescriptionTextId = qptr->GetDescriptionTextId();
			qinfo.Visible = qptr->GetVisible();
			paramseq.push_back(new QuestUpdate(qinfo, false));
			toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"JournalBox", paramseq));

			try
			{
				_proxy->ServerEvents(toplayer);
			}
			catch(const IceUtil::Exception& ex)
			{
				std::cout<<"Exception in sending event to client: "<<ex.what()<<std::endl;
			}
			catch(...)
			{
				std::cout<<"Unknown exception in sending event to client. "<<std::endl;
			}
		}
	}
}

/***********************************************************
finish a quest
***********************************************************/
void PlayerHandler::FinishQuest(long questid)
{
	std::vector<long>::iterator it = std::find(_questStarted.begin(), _questStarted.end(), questid);
	if(it != _questStarted.end())
		_questStarted.erase(it);

	std::vector<long>::iterator it2 = std::find(_questFinished.begin(), _questFinished.end(), questid);
	if(it2 == _questFinished.end())
	{
		_questFinished.push_back(questid);

		//inform client
		if(_proxy)
		{
			LbaNet::EventsSeq toplayer;
			LbaNet::GuiUpdatesSeq paramseq;
			QuestInfo qinfo;
			qinfo.Id = questid;
			QuestPtr qptr = QuestHandler::getInstance()->GetQuest(questid);
			qinfo.ChapterTextId = qptr->GetChapter();
			qinfo.QuestAreaTextId = qptr->GetLocationTextId();	
			qinfo.TittleTextId = qptr->GetTitleTextId();
			qinfo.DescriptionTextId = qptr->GetDescriptionTextId();
			qinfo.Visible = qptr->GetVisible();
			paramseq.push_back(new QuestUpdate(qinfo, true));
			toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"JournalBox", paramseq));

			try
			{
				_proxy->ServerEvents(toplayer);
			}
			catch(const IceUtil::Exception& ex)
			{
				std::cout<<"Exception in sending event to client: "<<ex.what()<<std::endl;
			}
			catch(...)
			{
				std::cout<<"Unknown exception in sending event to client. "<<std::endl;
			}
		}
	}
}


/***********************************************************
check if quest started
***********************************************************/
bool PlayerHandler::QuestStarted(long questid)
{
	std::vector<long>::iterator it = std::find(_questStarted.begin(), _questStarted.end(), questid);
	if(it != _questStarted.end())
		return true;

	return false;
}

/***********************************************************
check if quest started
***********************************************************/
bool PlayerHandler::QuestFinished(long questid)
{
	std::vector<long>::iterator it = std::find(_questFinished.begin(), _questFinished.end(), questid);
	if(it != _questFinished.end())
		return true;

	return false;
}



/***********************************************************
check if quest available
***********************************************************/
bool PlayerHandler::QuestAvailable(long questid)
{
	return (!QuestStarted(questid) && !QuestFinished(questid));
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
							(long)_currentinfo.EquipedWeapon, (long)_currentinfo.EquipedOutfit,
							(long)_currentinfo.EquipedMount);
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
get player rotation
***********************************************************/
float PlayerHandler::GetPlayerRotation()
{
	return _currentinfo.ppos.Rotation;
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
										bool changefromserver, int mountid)
{
	long lastmountid = (long)_currentinfo.EquipedMount;

	//check if stance change is legal
	if(_currentstate && _currentstate->AllowChangeMode())
	{
		_currentinfo.EquipedMount = -1;
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
				{
					_currentinfo.EquipedMount = mountid;
					newmode = "Protopack";
				}
			break;

			case LbaNet::StanceHorse:
				if(changefromserver)
				{
					_currentinfo.EquipedMount = mountid;
					newmode = "Horse";
				}
			break;

			case LbaNet::StanceDinofly:
				if(changefromserver)
				{
					_currentinfo.EquipedMount = mountid;
					newmode = "Dinofly";
				}
			break;
		}

		// check if stance is already there
		if(_currentinfo.model.Mode != newmode || lastmountid != mountid)
		{
			if(mountid > 0)
			{
				LbaNet::ItemInfo iinfo = InventoryItemHandler::getInstance()->GetItemInfo(mountid);
				_currentinfo.model.MountSkinColor = iinfo.Color1;
				_currentinfo.model.MountHairColor = iinfo.Color2;
				ResetWeapon();
			}

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
		if(NewState != LbaNet::StUseWeapon || _currentstate->CanUseWeapon())
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
		if(_currentmode && _currentmode->CanChangeWeapon())
		{
			// if so check if already on this state
			if(_currentinfo.EquipedWeapon != ItemId || _currentinfo.model.Weapon != weapon)
			{
				_currentinfo.EquipedWeapon = ItemId;
				LbaNet::ItemInfo iinfo = InventoryItemHandler::getInstance()->GetItemInfo(ItemId);

				_currentinfo.model.Weapon = weapon;
				_currentinfo.model.WeaponColor = iinfo.Color1;

				return UpdatePlayerState(LbaNet::StPrepareWeapon, returnmodel);
			}
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
		// if so check if already on this state
		if(_currentinfo.EquipedOutfit != ItemId || _currentinfo.model.Outfit != outfit)
		{
			_currentinfo.EquipedOutfit = ItemId;
			LbaNet::ItemInfo iinfo = InventoryItemHandler::getInstance()->GetItemInfo(ItemId);

			_currentinfo.model.Outfit = outfit;
			_currentinfo.model.OutfitColor = iinfo.Color1;

			ResetWeapon();
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
		case LbaNet::StActivateSwitch:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateActivateSwitch());						
		}
		break;

		case LbaNet::StActivateGroundSwitch:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateActivateGroundSwitch());						
		}
		break;

		case LbaNet::StHappy:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StateHappy());						
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

			try
			{
				_proxy->ServerEvents(toplayer);
			}
			catch(const IceUtil::Exception& ex)
			{
				std::cout<<"Exception in sending event to client: "<<ex.what()<<std::endl;
			}
			catch(...)
			{
				std::cout<<"Unknown exception in sending event to client. "<<std::endl;
			}
		}


		return;
	}

	if(_dbH)
	{
		long id = _dbH->AddLetter(_clientid, subject, message);
		if(id >= 0)
		{
			id += _CUSTOM_OFFSET_;
			LbaNet::ItemPosInfo newitem;
			newitem.Position = -1;
			newitem.Count = 1;
			newitem.Info.IconName = "GUI/imagesets/Inventory/letter.png";
			newitem.Info.NameTextId = -1;
			newitem.Info.DescriptionId = -1;
			newitem.Info.LongDescriptionId = -1;
			newitem.Info.Max = 1;
			newitem.Info.BuyPrice = 0;
			newitem.Info.SellPrice = 0;
			newitem.Info.Type = 8;
			newitem.Info.Ephemere = false;
			newitem.Info.DescriptionTextExtra = "From: " + _extrainfo.Name + " Subject: " + subject;
			newitem.Info.Id = id;


			_currentinfo.inventory.InventoryStructure[id] = newitem;

			//send new item to client
			if(_proxy)
			{
				LbaNet::EventsSeq toplayer;
				LbaNet::GuiUpdatesSeq paramseq;
				paramseq.push_back(new LbaNet::UpdateInventoryItem(LbaNet::DontInform, newitem));
				toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														"InventoryBox", paramseq));

				try
				{
					_proxy->ServerEvents(toplayer);
				}
				catch(const IceUtil::Exception& ex)
				{
					std::cout<<"Exception in sending event to client: "<<ex.what()<<std::endl;
				}
				catch(...)
				{
					std::cout<<"Unknown exception in sending event to client. "<<std::endl;
				}
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
			paramseq.push_back(new LbaNet::UpdateInventoryItem(LbaNet::DontInform, it->second));
			toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"InventoryBox", paramseq));

			try
			{
				_proxy->ServerEvents(toplayer);
			}
			catch(const IceUtil::Exception& ex)
			{
				std::cout<<"Exception in sending event to client: "<<ex.what()<<std::endl;
			}
			catch(...)
			{
				std::cout<<"Unknown exception in sending event to client. "<<std::endl;
			}
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
get info about an item
***********************************************************/
LbaNet::ItemPosInfo PlayerHandler::GetCurrentWeaponInfo()
{
	return GetItemInfo((long)_currentinfo.EquipedWeapon);
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
				DeltaUpdateLife(deltalife);

				used = true;
				updatelife = true;
			}
			break;
			case 2: // mana potion
			{
				if(_currentinfo.lifemana.CurrentMana == _currentinfo.lifemana.MaxMana)
					return updatelife; // do nothing if mana is full

				float deltaMana = (it->second.Info.Effect * _currentinfo.lifemana.MaxMana / 100.0f);
				DeltaUpdateMana(deltaMana);

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
				DeltaUpdateLife(deltalife);

				float deltaMana = (it->second.Info.Effect * _currentinfo.lifemana.MaxMana / 100.0f);
				DeltaUpdateMana(deltaMana);

				used = true;
				updatelife = true;
			}
			break;

			case 4: // life potion
			{
				if(_currentinfo.lifemana.CurrentLife == _currentinfo.lifemana.MaxLife)
					return updatelife; // do nothing if life is full

				float deltalife = it->second.Info.Effect;
				DeltaUpdateLife(deltalife);

				used = true;
				updatelife = true;
			}
			break;
			case 5: // mana potion
			{
				if(_currentinfo.lifemana.CurrentMana == _currentinfo.lifemana.MaxMana)
					return updatelife; // do nothing if mana is full

				float deltaMana = it->second.Info.Effect;
				DeltaUpdateMana(deltaMana);

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
				DeltaUpdateLife(deltalife);

				float deltaMana = it->second.Info.Effect;
				DeltaUpdateMana(deltaMana);

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
				paramseq.push_back(new LbaNet::UpdateInventoryItem(LbaNet::InformChat, it->second));
				toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														"InventoryBox", paramseq));

				try
				{
					_proxy->ServerEvents(toplayer);
				}
				catch(const IceUtil::Exception& ex)
				{
					std::cout<<"Exception in sending event to client: "<<ex.what()<<std::endl;
				}
				catch(...)
				{
					std::cout<<"Unknown exception in sending event to client. "<<std::endl;
				}
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
			paramseq.push_back(new LbaNet::UpdateInventoryItem(LbaNet::DontInform, it->second));

			_currentinfo.inventory.InventoryStructure.erase(it++);
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

			try
			{
				_proxy->ServerEvents(toplayer);
			}
			catch(const IceUtil::Exception& ex)
			{
				std::cout<<"Exception in sending event to client: "<<ex.what()<<std::endl;
			}
			catch(...)
			{
				std::cout<<"Unknown exception in sending event to client. "<<std::endl;
			}
		}
	}

}


/***********************************************************
update player life
***********************************************************/
bool PlayerHandler::DeltaUpdateLife(float update, bool forcelooselife)
{
	//dont do anything on immune
	bool force = forcelooselife && _currentstate && _currentstate->IsHurt();
	if(!force && update < 0 && _currentstate && _currentstate->IsImmuneHurt())
		return false;

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

		//check if something went wrong
		if(sX < 0 || sX > 100)
			sX = 1;

		//check if something went wrong
		if(sY < 0 || sY > 100)
			sY = 5;

		//check if something went wrong
		if(sZ < 0 || sZ > 100)
			sZ = 1;
	}
}


/***********************************************************
Get current power
***********************************************************/
float PlayerHandler::GetPower()
{
	if(_currentinfo.EquipedWeapon >= 0)
		return InventoryItemHandler::getInstance()->GetItemInfo((long)_currentinfo.EquipedWeapon).Effect;

	return 0;
}

/***********************************************************
Get current armor
***********************************************************/
float PlayerHandler::GetArmor()
{
	if(_currentinfo.EquipedOutfit >= 0)
		return InventoryItemHandler::getInstance()->GetItemInfo((long)_currentinfo.EquipedOutfit).Effect;

	return 0;
}

/***********************************************************
update player inventory
***********************************************************/
void PlayerHandler::UpdateInventory(LbaNet::ItemList Taken, LbaNet::ItemList Put, 
													LbaNet::ItemClientInformType informtype)
{
	LbaNet::EventsSeq toplayer;
	LbaNet::GuiUpdatesSeq paramseq;

	// take from inventory
	LbaNet::ItemList::iterator ittaken = Taken.begin();
	LbaNet::ItemList::iterator endtaken = Taken.end();
	for(; ittaken != endtaken; ++ittaken)
	{
		LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.find(ittaken->first);
		if(it != _currentinfo.inventory.InventoryStructure.end())
		{
			it->second.Count -= ittaken->second;
			if(it->second.Count < 0)
				it->second.Count = 0;

			paramseq.push_back(new LbaNet::UpdateInventoryItem(informtype, it->second));

			if(it->second.Count == 0)
			{
				// remove from inventory
				_currentinfo.inventory.InventoryStructure.erase(it);
			}
		}
	}

	// put in inventory
	LbaNet::ItemList::iterator itput = Put.begin();
	LbaNet::ItemList::iterator endput = Put.end();
	for(; itput != endput; ++itput)
	{
		long replacedid = -1;
		LbaNet::ItemPosInfo newitempos;


		LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.find(itput->first);
		if(it != _currentinfo.inventory.InventoryStructure.end())
		{
			it->second.Count += itput->second;
			if(it->second.Count > it->second.Info.Max)
				it->second.Count = it->second.Info.Max;

			newitempos = it->second;
		}
		else
		{
			// add new object to inventory
			newitempos.Count = itput->second;
			newitempos.Position = -1;
			newitempos.Info = InventoryItemHandler::getInstance()->GetItemInfo((long)itput->first);

			if(newitempos.Count > newitempos.Info.Max)
				newitempos.Count = newitempos.Info.Max;

			if(newitempos.Count > 0)
				_currentinfo.inventory.InventoryStructure[itput->first] = newitempos;
		}

		if(newitempos.Info.ReplaceItem >= 0)
		{
			// check if we have item and remove it
			LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.find(newitempos.Info.ReplaceItem);
			if(it != _currentinfo.inventory.InventoryStructure.end())
			{
				it->second.Count -= itput->second;
				if(it->second.Count < 0)
					it->second.Count = 0;

				paramseq.push_back(new LbaNet::UpdateInventoryItem(LbaNet::DontInform, it->second));

				if(it->second.Count == 0)
				{
					// remove from inventory
					_currentinfo.inventory.InventoryStructure.erase(it);
				}
			}
		}

		if(newitempos.Count > 0)
			paramseq.push_back(new LbaNet::UpdateInventoryItem(informtype, newitempos));
	}

	if(_proxy)
	{
		toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
												"InventoryBox", paramseq));

		try
		{
			_proxy->ServerEvents(toplayer);
		}
		catch(const IceUtil::Exception& ex)
		{
			std::cout<<"Exception in sending event to client: "<<ex.what()<<std::endl;
		}
		catch(...)
		{
			std::cout<<"Unknown exception in sending event to client. "<<std::endl;
		}
	}
}


/***********************************************************
change player color
***********************************************************/
void PlayerHandler::ChangePlayerColor(int skinidx, int eyesidx, int hairidx, int outfitidx, 
									  int weaponidx, int mountidx, int mountidx2)
{
	_currentinfo.model.SkinColor = skinidx;
	_currentinfo.model.EyesColor = eyesidx;
	_currentinfo.model.HairColor = hairidx;

	if(outfitidx > -2)
		_currentinfo.model.OutfitColor = outfitidx;
	if(weaponidx > -2)
		_currentinfo.model.WeaponColor = weaponidx;
	if(mountidx > -2)
		_currentinfo.model.MountSkinColor = mountidx;
	if(mountidx2 > -2)
		_currentinfo.model.MountHairColor = mountidx2;
}



/***********************************************************
client open container
***********************************************************/
void PlayerHandler::OpenInventoryContainer(long itemid)
{
	LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.find(itemid);
	if(it != _currentinfo.inventory.InventoryStructure.end())
	{
		LbaNet::GuiUpdatesSeq paramseq;

		// add new items to inventory
		LbaNet::ItemsMap newitems = GetContainerItem(it->second.Info);
		LbaNet::ItemsMap::iterator itni = newitems.begin();
		LbaNet::ItemsMap::iterator endni = newitems.end();
		for(; itni != endni; ++itni)
		{
			LbaNet::ItemsMap::iterator itadded = _currentinfo.inventory.InventoryStructure.find(itni->second.Info.Id);
			if(itadded != _currentinfo.inventory.InventoryStructure.end())
			{	
				itadded->second.Count += itni->second.Count;
				if(itadded->second.Count > itadded->second.Info.Max)
					itadded->second.Count = itadded->second.Info.Max;

				paramseq.push_back(new LbaNet::UpdateInventoryItem(LbaNet::InformChat, itadded->second));	
			}
			else
			{
				// add it if possible
				if((int)_currentinfo.inventory.InventoryStructure.size() < _currentinfo.inventory.InventorySize)
				{
					_currentinfo.inventory.InventoryStructure[itni->first] = itni->second;
					paramseq.push_back(new LbaNet::UpdateInventoryItem(LbaNet::InformChat, itni->second));	
				}
			}
		}

		// remove container from inventory
		it->second.Count -= 1;

		paramseq.push_back(new LbaNet::UpdateInventoryItem(LbaNet::InformChat, it->second));	

		if(it->second.Count <= 0)
			_currentinfo.inventory.InventoryStructure.erase(it);

		if(_proxy)
		{
			LbaNet::EventsSeq toplayer;

			toplayer.push_back(new LbaNet::UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"InventoryBox", paramseq));

			try
			{
				_proxy->ServerEvents(toplayer);
			}
			catch(const IceUtil::Exception& ex)
			{
				std::cout<<"Exception in sending event to client: "<<ex.what()<<std::endl;
			}
			catch(...)
			{
				std::cout<<"Unknown exception in sending event to client. "<<std::endl;
			}
		}	
	}
}


/***********************************************************
prepare the container
***********************************************************/	
LbaNet::ItemsMap PlayerHandler::GetContainerItem(const LbaNet::ItemInfo &item)
{
	LbaNet::ItemsMap res;

	//fill container with items
	std::vector<LbaNet::ItemGroupElement>::const_iterator itc = item.List.begin();
	std::vector<LbaNet::ItemGroupElement>::const_iterator endc = item.List.end();

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
reset weapon if needed
***********************************************************/
void PlayerHandler::ResetWeapon()
{
	if(_currentinfo.EquipedWeapon >= 0)
	{
		LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.find(_currentinfo.EquipedWeapon);
		if(it != _currentinfo.inventory.InventoryStructure.end())
		{
			if(it->second.Info.StringFlag == "Saber")
			{
				_currentinfo.EquipedWeapon = -1;
				_currentinfo.model.Weapon = "";
				_currentinfo.model.WeaponColor = -1;

				// check for another weapon
				LbaNet::ItemsMap::iterator it = _currentinfo.inventory.InventoryStructure.begin();
				LbaNet::ItemsMap::iterator end = _currentinfo.inventory.InventoryStructure.end();
				for(; it != end; ++it)
				{
					if(it->second.Info.Type == 4)
					{
						if(it->second.Info.StringFlag == "MagicBall")
						{
							_currentinfo.EquipedWeapon = it->first;
							_currentinfo.model.Weapon = it->second.Info.StringFlag;
							_currentinfo.model.WeaponColor = it->second.Info.Color1;
							break;
						}
					}
				}		
			}
		}
		else
		{
			_currentinfo.EquipedWeapon = -1;
			_currentinfo.model.Weapon = "";
			_currentinfo.model.WeaponColor = -1;
		}
	}
}



/***********************************************************
get player hit contact power
***********************************************************/
float PlayerHandler::GetHitContactPower(bool withweapon)
{
	float res = -1;

	int hurtmove = _currentstate->HurtActorsOnMove();

	if(withweapon)
	{
		if(hurtmove == 2)
		{
			LbaNet::ItemInfo iinfo = InventoryItemHandler::getInstance()->GetItemInfo((long)_currentinfo.EquipedWeapon);
			if(iinfo.Id >= 0)
				return iinfo.Effect;
		}
	}
	else
	{
		if(hurtmove == 1)
		{
			LbaNet::ItemInfo iinfo = InventoryItemHandler::getInstance()->GetItemInfo((long)_currentinfo.EquipedOutfit);
			if(iinfo.Id >= 0)
				return iinfo.Effect2;
		}
	}


	return res;
}



/***********************************************************
return current position - centered on Y
***********************************************************/
LbaVec3 PlayerHandler::GetCurrentPhysPosition()
{
	float sX, sY, sZ;
	GetPlayerPhysicalSize(sX, sY, sZ);

	return LbaVec3(_currentinfo.ppos.X, _currentinfo.ppos.Y+sY/2, _currentinfo.ppos.Z);
}

 /***********************************************************
return last position - centered on Y
***********************************************************/
LbaVec3 PlayerHandler::GetLastPhysPosition()
{
	return _lastposition;
}

 /***********************************************************
set last position
***********************************************************/
void PlayerHandler::SetLastPosition(const LbaVec3 & pos)
{
	float sX, sY, sZ;
	GetPlayerPhysicalSize(sX, sY, sZ);

	_lastposition = pos;
	_lastposition.y += sY/2;
}


 /***********************************************************
get player physical radius
***********************************************************/
float PlayerHandler::GetPhysRadius()
{
	float sX, sY, sZ;
	GetPlayerPhysicalSize(sX, sY, sZ);

	return (sX + sZ)/4;
}



 /***********************************************************
return true if player can be targeted
***********************************************************/
bool PlayerHandler::CanBeTarget()
{
	return _currentstate->CanBeTarget();
}

 /***********************************************************
check if player is moving
***********************************************************/
bool PlayerHandler::IsMoving()
{
	float speed = _currentspeedX + _currentspeedY + _currentspeedZ;
	return (fabs(speed) > 0.0001f);
}


/***********************************************************
set DB flag
***********************************************************/
void PlayerHandler::SetDBFlag(const std::string & flagid, int value)
{
	if(_dbH)
		_dbH->SetDBFlag(_worldname, _clientid, flagid, value);

	_flagcache[flagid] = value;
}


/***********************************************************
get DB flag
***********************************************************/
int PlayerHandler::GetDBFlag(const std::string & flagid)
{
	std::map<std::string, int>::iterator itf = _flagcache.find(flagid);
	if(itf != _flagcache.end())
	{
		return itf->second;
	}
	else
	{
		if(_dbH)
		{
			int v = _dbH->GetDBFlag(_worldname, _clientid, flagid);
			_flagcache[flagid] = v;
			return v;
		}
		else
			return -1;
	}
}