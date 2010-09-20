#include "PlayerHandler.h"


/***********************************************************
constructor
***********************************************************/
PlayerHandler::PlayerHandler(long clientid, const std::string &clientname, 
						const ClientInterfacePrx &proxy,
						boost::shared_ptr<DatabaseHandlerBase> dbH,
						const std::string &worldname,
						const SavedWorldInfo & savedinfo,
						const ModelInfo & modelinfo)
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
	}
}



/***********************************************************
get player current map
***********************************************************/
std::string PlayerHandler::GetCurrentMap()
{
	return _currentinfo.ppos.MapName;
}