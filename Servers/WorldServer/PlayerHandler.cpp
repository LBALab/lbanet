#include "PlayerHandler.h"


/***********************************************************
constructor
***********************************************************/
PlayerHandler::PlayerHandler(long clientid, const std::string &clientname, 
						const LbaNet::ClientInterfacePrx &proxy,
						boost::shared_ptr<DatabaseHandlerBase> dbH,
						const std::string &worldname,
						const LbaNet::SavedWorldInfo & savedinfo,
						const LbaNet::ModelInfo & modelinfo)
	: _clientid(clientid), _clientname(clientname), _proxy(proxy), 
		_dbH(dbH), _currentinfo(savedinfo), _worldname(worldname),
		_currentmodelinfo(modelinfo)
{

	// get quest information
	if(_dbH) 
		_dbH->GetQuestInfo(_worldname, _clientid, _questStarted, _questFinished);


	//complete item information
	{
		//TODO
		//{
		//	InventoryMap::iterator it = savedinfo.inventory.InventoryStructure.begin();
		//	InventoryMap::iterator end = savedinfo.inventory.InventoryStructure.end();
		//	for(; it != end; ++it)
		//	{
		//		if(it->Id >= 10000000) // custom item
		//		{
		//			it->first.
		//		}
		//	}
		//}

		// complete shortcut info
		//{
		//	ShortcutsSeq::iterator it = savedinfo.inventory.UsedShorcuts.begin();
		//	ShortcutsSeq::iterator end = savedinfo.inventory.UsedShorcuts.end();
		//	for(; it != end; ++it)
		//	{
		//		if(it->Id >= 0)
		//		{
		//			InventoryMap::iterator itm = savedinfo.inventory.InventoryStructure.find(it->Id)
		//			if(itm != savedinfo.inventory.InventoryStructure.end())
		//				*it = itm->second;
		//			else
		//				it->Id = -1;
		//		}
		//	}
		//}
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
void PlayerHandler::UpdatePositionInWorld(const LbaNet::PlayerPosition& Position)
{
	_currentinfo.ppos = Position;
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
		//TODO convert inventory back first from map
		_dbH->UpdateInventory(_currentinfo.inventory, _worldname, _clientid);

		// update player life
		_dbH->UpdateLife(_currentinfo.lifemana, _worldname, _clientid);

		// set quest information
		_dbH->SetQuestInfo(_worldname, _clientid, _questStarted, _questFinished);

		//set player model
		_dbH->UpdateModel(_currentinfo.model, _worldname, _clientid);
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
//!  update player stance
//! return true if state has been updated
***********************************************************/
bool PlayerHandler::UpdatePlayerStance(LbaNet::ModelStance NewStance, LbaNet::ModelInfo & returnmodel)
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
		}

		// check if stance is already there
		if(_currentmodelinfo.Mode != newmode)
		{
			_currentmodelinfo.Mode = newmode;
			_currentmodelinfo.State = LbaNet::StNormal;
			UpdateStateModeClass();
			returnmodel = _currentmodelinfo;
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
	//TODO - check if state is legal
	if(_currentstate && _currentstate->ChangeLegal(NewState))
	{
		// if so check if already on this state
		if(_currentmodelinfo.State != NewState)
		{
			_currentmodelinfo.State = NewState;
			UpdateStateModeClass();
			returnmodel = _currentmodelinfo;
			return true;
		}
	}

	return false;
}

/***********************************************************
update state and mode class from modelinfo
***********************************************************/
void PlayerHandler::UpdateStateModeClass()
{
	if(_currentmodelinfo.Mode == "Normal")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new NormalCharacterMode());
	}

	if(_currentmodelinfo.Mode == "Sport")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new SportyCharacterMode());
	}

	if(_currentmodelinfo.Mode == "Angry")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new AggresiveCharacterMode());
	}

	if(_currentmodelinfo.Mode == "Discrete")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new DiscreteCharacterMode());
	}		

	if(_currentmodelinfo.Mode == "Protopack")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new ProtopackCharacterMode());
	}

	if(_currentmodelinfo.Mode == "Horse")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new HorseCharacterMode());
	}

	if(_currentmodelinfo.Mode == "Dinofly")
	{
		_currentmode = boost::shared_ptr<CharacterModeBase>(new DinoflyCharacterMode());
	}		

	switch(_currentmodelinfo.State)
	{
		case LbaNet::StNormal:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StNormal());
		}
		break;
		case LbaNet::StDying:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StDying());			
		}
		break; 
		case LbaNet::StDrowning:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StDrowning());			
		}
		break; 
		case LbaNet::StDrowningGas:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StDrowningGas());		
		}
		break; 
		case LbaNet::StBurning:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StBurning());						
		}
		break; 
		case LbaNet::StSmallHurt:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StSmallHurt());						
		}
		break; 
		case LbaNet::StMediumHurt:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StMediumHurt());						
		}
		break; 
		case LbaNet::StBigHurt:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StBigHurt());						
		}
		break; 
		case LbaNet::StHurtFall:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StHurtFall());						
		}
		break; 
		case LbaNet::StFinishedFall:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StFinishedFall());						
		}
		break;	
		case LbaNet::StFalling:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StFalling());					
		}
		break; 
		case LbaNet::StJumping:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StJumping());						
		}
		break; 
		case LbaNet::StMovingObject:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StMovingObject());						
		}
		break; 
		case LbaNet::StRestrictedMovingObject:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StRestrictedMovingObject());						
		}
		break; 
		case LbaNet::StUseWeapon:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StUseWeapon());						
		}
		break; 
		case LbaNet::StImmune:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StImmune());						
		}
		break; 
		case LbaNet::StProtectedHurt:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StProtectedHurt());						
		}
		break; 
		case LbaNet::StHidden:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StHidden());						
		}
		break; 
		case LbaNet::StScripted:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StScripted());						
		}
		break;
		case LbaNet::StFighting:
		{
			_currentstate = boost::shared_ptr<CharacterStateBase>(new StFighting());						
		}
		break;
	}
}