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


using namespace LbaNet;



//! take care of a specific player inside the server
class PlayerHandler
{
public:
	//! constructor
	PlayerHandler(long clientid, const std::string &clientname, 
							const ClientInterfacePrx &proxy,
							boost::shared_ptr<DatabaseHandlerBase> dbH,
							const std::string &worldname,
							const SavedWorldInfo & savedinfo,
							const ModelInfo & modelinfo);
	
	//! destructor
	~PlayerHandler(void);


	//! accessor on id
	Ice::Long GetId() {return _clientid;}

	//! accessor on name
	std::string GetName() {return _clientname;}

	//! accessor on proxy
	ClientInterfacePrx GetProxy() {return _proxy;}

	//! accessor on model
	ModelInfo GetModelInfo() {return _currentmodelinfo;}

	//! get inventory
	ItemsMap GetInventory() {return _currentinventory;}

	// get shortcuts
	ShortcutsSeq GetShorcuts() {return _currentshortcuts;}

	// player update on of the shorcut - TODO
	void UpdateShortcut(int Position, long ItemId);

	// get current size of inventory
	int GetInventorySize();


	//! get player current map
	std::string GetCurrentMap();


	//! update player life and mana
	void UpdateLifeMana(const LbaNet::LifeManaInfo & lifeinfo);

	// update current position in the world
	void UpdatePositionInWorld(const LbaNet::PlayerPosition& Position);

	// start a quest
	void StartQuest(long questid);

	// finish a quest
	void FinishQuest(long questid);

	//! save current info in database
	void SaveCurrentInfo();

	//! get player info
	SavedWorldInfo GetInfo(){ return _currentinfo;}

	//!  get player position
	PlayerPosition GetPlayerPosition();


private:
	long										_clientid;
	std::string									_clientname; 
	ClientInterfacePrx							_proxy;
	boost::shared_ptr<DatabaseHandlerBase>		_dbH;

	std::string									_worldname;
	SavedWorldInfo								_currentinfo;
	ModelInfo									_currentmodelinfo;
	ItemsMap									_currentinventory;
	ShortcutsSeq								_currentshortcuts;


	std::vector<long>							_questStarted;
	std::vector<long>							_questFinished;


};

#endif
