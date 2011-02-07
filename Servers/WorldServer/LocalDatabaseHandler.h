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


#if !defined(__Agent_database_handler_h)
#define __Agent_database_handler_h

#include <string>
#include <vector>
#include <map>

#include <IceUtil/Mutex.h>

#include "DatabaseHandlerBase.h"


struct sqlite3;


/***********************************************************************
 * Module:  DatabaseHandler.h
 * Author:  vivien
 * Modified: lundi 27 juillet 2009 14:59:17
 * Purpose: Declaration of the class SharedData
 ***********************************************************************/
class LocalDatabaseHandler : public IceUtil::Mutex, public DatabaseHandlerBase
{
public:
	//! default construtor
	LocalDatabaseHandler(const std::string & filename);

	// player has changed world
	LbaNet::SavedWorldInfo ChangeWorld(const std::string& NewWorldName, long PlayerId, int defaultinventorysize = 30);

	// player update his current position in the world
	void UpdatePositionInWorld(const LbaNet::PlayerPosition& Position, 
								const std::string& WorldName,long PlayerId);

	// update player life information
	void UpdateLife(const LbaNet::LifeManaInfo & lifeinfo, 
								const std::string& WorldName,long PlayerId);
	
	// update player life information
	void UpdateModel(const LbaNet::ModelInfo & modelinfo, 
								const std::string& WorldName,long PlayerId,
								long equipedweapon, long equipedoutfit,
								long equipedmount);

	// quit current world
	void QuitWorld(const std::string& LastWorldName,long PlayerId);

	// update player inventory structure
	void UpdateInventory(const LbaNet::InventoryInfo &Inventory, const std::string& WorldName,long PlayerId);


    // add friend function
	bool AskFriend(long myId, const std::string &friendname, long & friendid,
							std::string &myname);

	// accept friend invitation
    bool AcceptFriend(long myId, long friendid, std::string &friendname,
							std::string &myname);

    // remove friend function
	void RemoveFriend(long myId, long friendid);

    // get friends function
    LbaNet::FriendsSeq GetFriends(long myId);


    // store letter to the server and return the letter id
    long AddLetter(long myId, const std::string& title, const std::string& message);
    
    // return letter info
    LbaNet::LetterInfo GetLetterInfo(Ice::Long LetterId);


	// get quest information
	void GetQuestInfo(const std::string& WorldName, long PlayerId, 
						std::vector<long> &questStarted, std::vector<long> &questFinished);


	// set quest information
	void SetQuestInfo(const std::string& WorldName, long PlayerId, 
						const std::vector<long> &questStarted, const std::vector<long> &questFinished);


	// record player kill
	void RecordKill(const std::string& WorldName, long KilledId, int Reason, long KillerId);



    // send a pm to someone
    void SendPM(const LbaNet::PMInfo &pm);
    
    // delete a pm
    void DeletePM(Ice::Long pmid);
    
    //mark pm as read
    void MarkReadPM(Ice::Long pmid);

    //get all pm in your mailbox
    LbaNet::PMsSeq GetInboxPM(long playerid);


	// delete letter
	void DeleteLetter(Ice::Long LetterId){}


protected:
	LocalDatabaseHandler(const LocalDatabaseHandler &);
	const LocalDatabaseHandler & operator=(const LocalDatabaseHandler &);


private:
	// database pointer
	 sqlite3 *	_db;

};

#endif