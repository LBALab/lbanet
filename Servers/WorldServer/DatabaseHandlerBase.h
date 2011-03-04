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


#if !defined(__Agent_database_handler_base_h)
#define __Agent_database_handler_base_h

#include <string>
#include <vector>
#include <map>

#include <LbaTypes.h>


/***********************************************************************
 * Module:  DatabaseHandlerBase.h
 * Author:  vivien
 * Modified: lundi 27 juillet 2009 14:59:17
 * Purpose: Declaration of the class DatabaseHandlerBase
 ***********************************************************************/
class DatabaseHandlerBase
{
public:
	//! default construtor
	DatabaseHandlerBase(){}

	//! destrutor
	~DatabaseHandlerBase(){}



	// player has changed world
	virtual LbaNet::SavedWorldInfo ChangeWorld(const std::string& NewWorldName, 
							long PlayerId, int defaultinventorysize = 30) = 0;

	// player update his current position in the world
	virtual void UpdatePositionInWorld(const LbaNet::PlayerPosition& Position, 
										const std::string& WorldName,long PlayerId) = 0;

	// update player inventory structure
	virtual void UpdateInventory(const LbaNet::InventoryInfo &Inventory, 
								const std::string& WorldName,long PlayerId) = 0;
	
	// update player life information
	virtual void UpdateLife(const LbaNet::LifeManaInfo & lifeinfo, 
								const std::string& WorldName,long PlayerId) = 0;
	
	// update player life information
	virtual void UpdateModel(const LbaNet::ModelInfo & modelinfo, 
								const std::string& WorldName,long PlayerId,
								long equipedweapon, long equipedoutfit,
								long equipedmount) = 0;

	
	// quit current world
	virtual void QuitWorld(const std::string& LastWorldName,long PlayerId) = 0;



    // add friend function
	virtual bool AskFriend(long myId, const std::string &friendname, long & friendid,
							std::string &myname) = 0;

	// accept friend invitation
    virtual bool AcceptFriend(long myId, long friendid, std::string &friendname,
								std::string &myname) = 0;

    // remove friend function
	virtual void RemoveFriend(long myId, long friendid) = 0;

    // get friends function
    virtual LbaNet::FriendsSeq GetFriends(long myId) = 0;


    // store letter to the server and return the letter id
    virtual long AddLetter(long myId, const std::string& title, const std::string& message) = 0;
    
    // return letter info
    virtual LbaNet::LetterInfo GetLetterInfo(Ice::Long LetterId) = 0;

	// delete letter
    virtual void DeleteLetter(Ice::Long LetterId) = 0;

	// get quest information
	virtual void GetQuestInfo(const std::string& WorldName, long PlayerId, 
						std::vector<long> &questStarted, std::vector<long> &questFinished) = 0;


	// set quest information
	virtual void SetQuestInfo(const std::string& WorldName, long PlayerId, 
						const std::vector<long> &questStarted, const std::vector<long> &questFinished) = 0;


	// record player kill
	//! Reason : 1 - environment, 2 - fall down, 3 - npc, 4 - player, 5 - other, 6 - drown
	virtual void RecordKill(const std::string& WorldName, long KilledId, int Reason, long KillerId) = 0;



    // send a pm to someone
    virtual void SendPM(const LbaNet::PMInfo &pm) = 0;
    
    // delete a pm
    virtual void DeletePM(Ice::Long pmid) = 0;
    
    //mark pm as read
    virtual void MarkReadPM(Ice::Long pmid) = 0;

    //get all pm in your mailbox
    virtual LbaNet::PMsSeq GetInboxPM(long playerid) = 0;


};

#endif