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


#include "DatabaseHandler.h"
#include "StringHelperFuncs.h"


#include <IceUtil/Time.h>


/***********************************************************
constructor
***********************************************************/
DatabaseHandler::DatabaseHandler(const std::string db, const std::string server,
									const std::string user, const std::string password)
				: _mysqlH(NULL), _db(db), _server(server), _user(user), _password(password)
{

	Connect();
}



/***********************************************************
clear db connection
***********************************************************/
void DatabaseHandler::Clear()
{
	if(_mysqlH)
	{
		if(_mysqlH->connected())
			_mysqlH->disconnect();

		delete _mysqlH;
		_mysqlH = NULL;
	}
}

/***********************************************************
connect to database
***********************************************************/
void DatabaseHandler::Connect()
{
	try
	{
		Clear();
		_mysqlH = new mysqlpp::Connection(false);

		if (!_mysqlH->connect(_db.c_str(), _server.c_str(), _user.c_str(), _password.c_str()))
		{
			std::cerr<<IceUtil::Time::now()<<": LBA_Server - DB connection failed: " << _mysqlH->error() << std::endl;
		}
	}
	catch(...){}
}


/***********************************************************
player has changed world
***********************************************************/
LbaNet::SavedWorldInfo DatabaseHandler::ChangeWorld(const std::string& NewWorldName, long PlayerId,
														int defaultinventorysize)
{
	long worldid = -1;
	LbaNet::SavedWorldInfo resP;


	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return resP;
		}
	}

	mysqlpp::Query query(_mysqlH, false);
	query << "SELECT uw.id, uw.lastmap, uw.lastposx, uw.lastposy, uw.lastposz, uw.lastrotation, uw.InventorySize, uw.Shortcuts, uw.LifePoint, uw.ManaPoint, uw.MaxLife, uw.MaxMana, w.id, uw.ModelName, uw.ModelOutfit, uw.ModelWeapon, uw.ModelMode, uw.RendererType, uw.EquipedWeapon, uw.EquipedOutfit, uw.EquipedMount, uw.SkinColor, uw.EyesColor, uw.HairColor";
	query << " FROM lba_usertoworld uw, lba_worlds w";
	query << " WHERE uw.userid = '"<<PlayerId<<"'";
	query << " AND w.name = '"<<NewWorldName<<"'";
	query << " AND uw.worldid = w.id";
	if (mysqlpp::StoreQueryResult res = query.store())
	{
		if(res.size() > 0)
		{
			//set the user as connected
			query.clear();
			query << "UPDATE lba_usertoworld SET lastvisited = UTC_TIMESTAMP() WHERE id = '"<<res[0][0]<<"'";
			if(!query.exec())
				std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update usertoworldmap.lastvisited failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;

			// player pos part
			resP.ppos.MapName = res[0][1].c_str();
			resP.ppos.X = res[0][2];
			resP.ppos.Y = res[0][3];
			resP.ppos.Z = res[0][4];
			resP.ppos.Rotation = res[0][5];

			// player inventory part
			resP.inventory.InventorySize = res[0][6];

			if(resP.inventory.InventorySize > 1000)
				resP.inventory.InventorySize = 30; // in case of crash


			std::vector<std::string> tokens;
			std::string shortcutstr = res[0][7].c_str();
			if(shortcutstr == "")
				shortcutstr = "-1#-1#-1#-1#-1#-1#-1#-1#-1#-1"; // in case of crash


			StringHelper::Tokenize(shortcutstr, tokens, "#");
			for(size_t i=0; i<tokens.size(); ++i)
			{
				LbaNet::ItemInfo itm;
				itm.Id = atol(tokens[i].c_str());
				resP.inventory.UsedShorcuts.push_back(itm);
			}

			resP.lifemana.CurrentLife = res[0][8];
			resP.lifemana.CurrentMana = res[0][9];
			resP.lifemana.MaxLife = res[0][10];
			resP.lifemana.MaxMana = res[0][11];


			resP.model.ModelName = res[0][13].c_str();
			resP.model.Outfit = res[0][14].c_str();
			resP.model.Weapon = res[0][15].c_str();
			resP.model.Mode = res[0][16].c_str();
			resP.model.State = LbaNet::StNormal;

			int renderT = res[0][17];
			switch(renderT)
			{
				case 0: // -> osg model
					resP.model.TypeRenderer = LbaNet::RenderOsgModel;
				break;

				case 1: // 1 -> sprite
					resP.model.TypeRenderer = LbaNet::RenderSprite;
				break;

				case 2: // -> LBA1 model
					resP.model.TypeRenderer = LbaNet::RenderLba1M;
				break;

				case 3: // -> LBA2 model
					resP.model.TypeRenderer = LbaNet::RenderLba2M;
				break;
			}

			resP.EquipedWeapon = res[0][18];
			resP.EquipedOutfit = res[0][19];
			resP.EquipedMount = res[0][20];

			resP.model.SkinColor = res[0][21];
			resP.model.EyesColor = res[0][22];
			resP.model.HairColor = res[0][23];


			worldid = res[0][12];

			query.clear();
			query << "SELECT * FROM lba_inventory";
			query << " WHERE worldid = '"<<res[0][0]<<"'";
			if (mysqlpp::StoreQueryResult res2 = query.store())
			{
				for(size_t i=0; i<res2.size(); ++i)
				{
					LbaNet::ItemPosInfo itm;
					itm.Count = res2[i][2];
					itm.Position = res2[i][3];
					resP.inventory.InventoryStructure[res2[i][1]] = itm;
				}
			}

		}
		else
		{
			query.clear();
			query <<"SELECT id FROM lba_worlds WHERE name = '"<<NewWorldName<<"'";
			if (mysqlpp::StoreQueryResult res = query.store())
			{
				if(res.size() > 0)
				{
					worldid = res[0][0];

					query.clear();
					query << "INSERT INTO lba_usertoworld (userid, worldid, lastvisited, ModelName, ModelOutfit, ModelWeapon, ModelMode) VALUES('";
					query << PlayerId << "', '"<<worldid<<"', UTC_TIMESTAMP(), '', '', '', '')";
					if(!query.exec())
						std::cerr<<IceUtil::Time::now()<<": LBA_Server - INSERT lba_usertoworld failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;
				}
			}



			resP.inventory.InventorySize = defaultinventorysize;
			for(int i=0; i<10; ++i)
			{
				LbaNet::ItemInfo itm;
				itm.Id = -1;
				resP.inventory.UsedShorcuts.push_back(itm);
			}
		}

		//insert world name into user
		{
			query.clear();
			query << "UPDATE lba_users SET currentworldid = '"<<worldid<<"' WHERE id = '"<<PlayerId<<"'";
			if(!query.exec())
				std::cerr<<IceUtil::Time::now()<<": LBA_Server - UPDATE users failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;
		}
	}
	else
	{
		Clear();
	}



	return resP;
}


/***********************************************************
player update his current position in the world
***********************************************************/
void DatabaseHandler::UpdatePositionInWorld(const LbaNet::PlayerPosition& Position,
											const std::string& WorldName, long PlayerId)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	mysqlpp::Query query(_mysqlH, false);
	query << "UPDATE lba_usertoworld SET lastmap = '"<<Position.MapName<<"',";
	query << "lastposx = '"<<Position.X<<"',";
	query << "lastposy = '"<<Position.Y<<"',";
	query << "lastposz = '"<<Position.Z<<"',";
	query << "lastrotation = '"<<Position.Rotation<<"'";
	query << " WHERE userid = '"<<PlayerId<<"'";
	query << " AND worldid = (SELECT id FROM lba_worlds WHERE name = '"<<WorldName<<"')";
	if(!query.exec())
	{
		std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update UpdatePositionInWorld failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;
		Clear();
	}

}


/***********************************************************
update player life information
***********************************************************/
void DatabaseHandler::UpdateLife(const LbaNet::LifeManaInfo & lifeinfo,
								const std::string& WorldName,long PlayerId)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}


	// quit previous world
	if(WorldName != "")
	{
		mysqlpp::Query query(_mysqlH, false);
		query << "UPDATE lba_usertoworld SET LifePoint = '"<<lifeinfo.CurrentLife<<"'";
		query << ", ManaPoint = '"<<lifeinfo.CurrentMana<<"'";
		query << ", MaxLife = '"<<lifeinfo.MaxLife<<"'";
		query << ", MaxMana = '"<<lifeinfo.MaxMana<<"'";
		query << " WHERE userid = '"<<PlayerId<<"'";
		query << " AND worldid = (SELECT id FROM lba_worlds WHERE name = '"<<WorldName<<"')";
		if(!query.exec())
		{
			std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update life info failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;
			Clear();
		}
	}
}


/***********************************************************
update player life information
***********************************************************/
void DatabaseHandler::UpdateModel(const LbaNet::ModelInfo & modelinfo,
							const std::string& WorldName,long PlayerId,
								long equipedweapon, long equipedoutfit,
								long equipedmount)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}


	// quit previous world
	if(WorldName != "")
	{
		mysqlpp::Query query(_mysqlH, false);
		query << "UPDATE lba_usertoworld SET ModelName = '"<<modelinfo.ModelName<<"'";
		query << ", ModelOutfit = '"<<modelinfo.Outfit<<"'";
		query << ", ModelWeapon = '"<<modelinfo.Weapon<<"'";
		query << ", ModelMode = '"<<modelinfo.Mode<<"'";
		query << ", EquipedWeapon = '"<<equipedweapon<<"'";
		query << ", EquipedOutfit = '"<<equipedoutfit<<"'";
		query << ", EquipedMount = '"<<equipedmount<<"'";
		query << ", SkinColor = '"<<modelinfo.SkinColor<<"'";
		query << ", EyesColor = '"<<modelinfo.EyesColor<<"'";
		query << ", HairColor = '"<<modelinfo.HairColor<<"'";

		int rtype = 0;
		switch(modelinfo.TypeRenderer)
		{
			case LbaNet::RenderOsgModel:
				rtype = 0;
			break;

			case LbaNet::RenderSprite:
				rtype = 1;
			break;

			case LbaNet::RenderLba1M:
				rtype = 2;
			break;

			case LbaNet::RenderLba2M:
				rtype = 3;
			break;
		}

		query << ", RendererType = '"<<rtype<<"'";
		query << " WHERE userid = '"<<PlayerId<<"'";
		query << " AND worldid = (SELECT id FROM lba_worlds WHERE name = '"<<WorldName<<"')";
		if(!query.exec())
		{
			std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update model info failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;
			Clear();
		}
	}
}

/***********************************************************
quit current world
***********************************************************/
void DatabaseHandler::QuitWorld(const std::string& LastWorldName,long PlayerId)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	// quit previous world
	if(LastWorldName != "")
	{
		mysqlpp::Query query(_mysqlH, false);
		query << "UPDATE lba_usertoworld SET timeplayedmin = timeplayedmin + TIMESTAMPDIFF(MINUTE, lastvisited, UTC_TIMESTAMP())";
		query << " WHERE userid = '"<<PlayerId<<"'";
		query << " AND worldid = (SELECT id FROM lba_worlds WHERE name = '"<<LastWorldName<<"')";
		if(!query.exec())
		{
			std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update usertoworldmap.timeplayedmin failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;
			Clear();
		}
	}
}



/***********************************************************
update player inventory structure
***********************************************************/
void DatabaseHandler::UpdateInventory(const LbaNet::InventoryInfo &Inventory, const std::string& WorldName,
									  long PlayerId)
{
	if(WorldName == "")
		return;

	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	std::stringstream shortcutstring;
	LbaNet::ShortcutsSeq::const_iterator it = Inventory.UsedShorcuts.begin();
	LbaNet::ShortcutsSeq::const_iterator end = Inventory.UsedShorcuts.end();
	if(it != end)
	{
		shortcutstring<<it->Id;
		++it;
	}
	for(;it != end; ++it)
		shortcutstring<<"#"<<it->Id;


	mysqlpp::Query query(_mysqlH, false);
	query << "SELECT id FROM lba_usertoworld";
	query << " WHERE userid = '"<<PlayerId<<"'";
	query << " AND worldid = (SELECT id FROM lba_worlds WHERE name = '"<<WorldName<<"')";;
	if (mysqlpp::StoreQueryResult res = query.store())
	{
		if(res.size() > 0)
		{
			query.clear();
			query << "UPDATE lba_usertoworld SET InventorySize = '"<<Inventory.InventorySize<<"',";
			query << "Shortcuts = '"<<shortcutstring.str()<<"' ";
			query << " WHERE id = '"<<res[0][0]<<"'";
			if(!query.exec())
				std::cout<<"LBA_Server - Update usertoworldmap_inv failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;


			query.clear();
			query << "DELETE FROM lba_inventory";
			query << " WHERE worldid = '"<<res[0][0]<<"'";
			if(!query.exec())
				std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update DELETE failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;

			LbaNet::ItemsMap::const_iterator iti = Inventory.InventoryStructure.begin();
			LbaNet::ItemsMap::const_iterator endi = Inventory.InventoryStructure.end();
			for(;iti != endi; ++iti)
			{
				query.clear();
				query << "INSERT INTO lba_inventory (worldid, objectid, number, InventoryPlace) VALUES('";
				query << res[0][0] << "', '" << iti->first << "', '" << iti->second.Count << "', '" << iti->second.Position << "')";
				if(!query.exec())
					std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update INSERT usertoworldmap failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;

			}
		}
	}
	else
	{
		Clear();
	}
}

/***********************************************************
add friend function
***********************************************************/
bool DatabaseHandler::AskFriend(long myId, const std::string &friendname, long & friendid,
									std::string &myname)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return false;
		}
	}

	mysqlpp::Query query(_mysqlH, false);

	query << "SELECT ju.id, lu.id FROM jos_users ju, lba_users lu";
	query << " WHERE ju.id = lu.josiid AND WHERE ju.username = '"<<friendname<<"'";
	if (mysqlpp::StoreQueryResult res = query.store())
	{
		if(res.size() > 0)
		{
			long juid = res[0][0];
			friendid = res[0][1];

			// get my jos id
			query.clear();
			query << "SELECT ju.id, ju.username FROM jos_users ju, lba_users lu";
			query << " WHERE ju.id = lu.josiid AND lu.id = '"<<myId<<"'";
			if (mysqlpp::StoreQueryResult res = query.store())
			{
				if(res.size() > 0)
				{
					myId = res[0][0];
					myname = res[0][1].c_str();

					//check if there is no existing connexion - if it is the case then do nothing
					query.clear();
					query << "SELECT accepted FROM jos_comprofiler_members";
					query << " WHERE referenceid = '"<<myId<<"'";
					query << " AND memberid = '"<<juid<<"'";
					if (mysqlpp::StoreQueryResult res = query.store())
					{
						if(res.size() > 0)
							return false;
					}

					// else add the connexion
					query.clear();
					query << "INSERT INTO jos_comprofiler_members (referenceid, memberid, accepted, pending, membersince, reason, type) VALUES";
					query << "('" << myId << "', '" << juid << "', '1', '1', NOW(), 'Friend request from Lbanet', 'Friend')";
					query << ",('" << juid << "', '" << myId << "', '0', '0', NOW(), 'Friend request from Lbanet', 'Friend')";
					if(!query.exec())
					{
						std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update INSERT friends failed for user id "<<myId<<" : "<<query.error()<<std::endl;
						return false;
					}

					return true;
				}
			}
		}
	}
	else
	{
		Clear();
	}

	return false;
}

/***********************************************************
accept friend invitation
***********************************************************/
bool DatabaseHandler::AcceptFriend(long myId, long friendid, std::string &friendname,
									std::string &myname)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return false;
		}
	}

	mysqlpp::Query query(_mysqlH, false);

	query << "SELECT ju.id, ju.username FROM jos_users ju, lba_users lu";
	query << " WHERE ju.id = lu.josiid AND lu.id = '"<<friendid<<"'";
	if (mysqlpp::StoreQueryResult res = query.store())
	{
		if(res.size() > 0)
		{
			long juid = res[0][0];
			friendname = res[0][1].c_str();

			// get my jos id
			query.clear();
			query << "SELECT ju.id, ju.username FROM jos_users ju, lba_users lu";
			query << " WHERE ju.id = lu.josiid AND lu.id = '"<<myId<<"'";
			if (mysqlpp::StoreQueryResult res = query.store())
			{
				if(res.size() > 0)
				{
					myId = res[0][0];
					myname = res[0][1].c_str();

					// check if we are in pending state
					query.clear();
					query << "SELECT accepted, pending FROM jos_comprofiler_members";
					query << " WHERE (referenceid = '"<<myId<<"' AND memberid = '"<<juid<<"')";
					if (res = query.store())
					{
						if(res.size() > 0)
						{
							int acpt= res[0][0];
							int pend= res[0][1];
							if(acpt == 0 && pend == 0)
							{
								query.clear();
								query << "UPDATE jos_comprofiler_members SET accepted = '1', pending = '0' ";
								query << " WHERE (referenceid = '"<<myId<<"' AND memberid = '"<<juid<<"')";
								query << " OR (referenceid = '"<<juid<<"' AND memberid = '"<<myId<<"')";
								if(!query.exec())
									std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update UPDATE friends failed for user id "<<myId<<" : "<<query.error()<<std::endl;


								return true;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		Clear();
	}

	return false;
}

/***********************************************************
remove friend function
***********************************************************/
void DatabaseHandler::RemoveFriend(long myId, long friendid)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	mysqlpp::Query query(_mysqlH, false);

	query << "SELECT ju.id FROM jos_users ju, lba_users lu";
	query << " WHERE ju.id = lu.josiid AND lu.id = '"<<friendid<<"'";
	if (mysqlpp::StoreQueryResult res = query.store())
	{
		if(res.size() > 0)
		{
			long juid = res[0][0];

			// get my jos id
			query.clear();
			query << "SELECT ju.id FROM jos_users ju, lba_users lu";
			query << " WHERE ju.id = lu.josiid AND lu.id = '"<<myId<<"'";
			if (mysqlpp::StoreQueryResult res = query.store())
			{
				if(res.size() > 0)
				{
					myId = res[0][0];

					query.clear();
					query << "DELETE FROM jos_comprofiler_members";
					query << " WHERE (referenceid = '"<<myId<<"' AND memberid = '"<<juid<<"')";
					query << " OR (referenceid = '"<<juid<<"' AND memberid = '"<<myId<<"')";
					if(!query.exec())
						std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update DELETE friends failed for user id "<<myId<<" : "<<query.error()<<std::endl;
				}
			}
		}
	}
	else
	{
		Clear();
	}
}

/***********************************************************
get friends function
***********************************************************/
LbaNet::FriendsSeq DatabaseHandler::GetFriends(long myId)
{
	LbaNet::FriendsSeq resF;


	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return resF;
		}
	}

	mysqlpp::Query query(_mysqlH, false);

	query << "SELECT cm.memberid, cm.pending, cm.accepted";
	query << " FROM jos_comprofiler_members cm, jos_users ju, lba_users lu";
	query << " WHERE ju.id = cm.referenceid";
	query << " AND ju.id = lu.josiid";
	query << " AND lu.id = '"<<myId<<"'";
	if (mysqlpp::StoreQueryResult res = query.store())
	{
		if(res.size() > 0)
		{
			for(size_t i=0; i<res.size(); ++i)
			{
				long juid = res[i][0];
				int pending=res[i][1];
				int accepted=res[i][2];
				query.clear();
				query << "SELECT ju.username, lu.id";
				query << " FROM jos_users ju, lba_users lu";
				query << " WHERE ju.id = '"<<juid<<"'";
				query << " AND ju.id = lu.josiid";

				if (mysqlpp::StoreQueryResult res2 = query.store())
				{
					if(res2.size() > 0)
					{
						LbaNet::FriendInfo ftmp;
						ftmp.Id = res2[0][1];
						ftmp.Name = res2[0][0].c_str();
						ftmp.Pending = (pending == 1);
						ftmp.ToAccept = (accepted == 0);
						ftmp.Removed = false;
						resF.push_back(ftmp);
					}
				}
			}

		}
	}
	else
	{
		std::cerr<<IceUtil::Time::now()<<": LBA_Server - GetFriends failed: "<<query.error()<<std::endl;
		Clear();
	}

	return resF;
}



/***********************************************************
store letter to the server and return the letter id
***********************************************************/
long DatabaseHandler::AddLetter(long myId, const std::string& title, const std::string& message)
{
	long resF = -1;

	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return resF;
		}
	}

	{
	mysqlpp::Query query(_mysqlH, false);
	query << "SET character_set_client=utf8";
	query.execute();
	}

	mysqlpp::Query query(_mysqlH, false);
	query << "INSERT INTO lba_letters (userid, creationdate, title, message) VALUES('";
	query << myId << "', UTC_TIMESTAMP(), "<<mysqlpp::quote<< title <<", " <<mysqlpp::quote<< message << ")";
	if(!query.exec())
	{
		std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update INSERT letters failed for user id "<<myId<<" : "<<query.error()<<std::endl;
		Clear();
	}
	else
	{
		resF = (long) query.insert_id();
	}

	return resF;
}


/***********************************************************
return letter info
***********************************************************/
LbaNet::LetterInfo DatabaseHandler::GetLetterInfo(Ice::Long LetterId)
{
	LbaNet::LetterInfo resF;
	resF.LetterId = -1;


	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return resF;
		}
	}

	{
	mysqlpp::Query query(_mysqlH, false);
	query << "SET character_set_results=utf8";
	query.execute();
	}

	mysqlpp::Query query(_mysqlH, false);
	query << "SELECT ju.username, l.creationdate, l.title, l.message";
	query << " FROM lba_users u, lba_letters l, jos_users ju";
	query << " WHERE ju.id = u.josiid";
	query << " AND u.id = l.userid";
	query << " AND l.id = '"<<LetterId<<"'";
	if (mysqlpp::StoreQueryResult res = query.store())
	{
		if(res.size() > 0)
		{
			resF.LetterId = LetterId;
			resF.From = res[0][0].c_str();
			res[0][1].to_string(resF.Date);
			resF.Subject= res[0][2].c_str();
			resF.Message= res[0][3].c_str();
		}
	}
	else
	{
		std::cerr<<IceUtil::Time::now()<<": LBA_Server - GetLetterInfo failed: "<<query.error()<<std::endl;
		Clear();
	}

	return resF;
}



/***********************************************************
delete letter
***********************************************************/
void DatabaseHandler::DeleteLetter(Ice::Long LetterId)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	mysqlpp::Query query(_mysqlH, false);
	query << "DELETE FROM lba_letters";
	query << " WHERE id = '"<<LetterId<<"'";
	if(!query.exec())
		std::cerr<<IceUtil::Time::now()<<": LBA_Server - Update DELETE failed for letter id "<<LetterId<<" : "<<query.error()<<std::endl;

}



/***********************************************************
get quest information
***********************************************************/
void DatabaseHandler::GetQuestInfo(const std::string& WorldName, long PlayerId,
					std::vector<long> &questStarted, std::vector<long> &questFinished)
{
	if(WorldName == "")
		return;

	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	mysqlpp::Query query(_mysqlH, false);
	query << "SELECT id FROM lba_usertoworld";
	query << " WHERE userid = '"<<PlayerId<<"'";
	query << " AND worldid = (SELECT id FROM lba_worlds WHERE name = '"<<WorldName<<"')";
	if (mysqlpp::StoreQueryResult res = query.store())
	{
		if(res.size() > 0)
		{
			query.clear();
			query << "SELECT questid, status FROM lba_quests";
			query << " WHERE worldid = '"<<res[0][0]<<"'";
			if (mysqlpp::StoreQueryResult res2 = query.store())
			{
				for(size_t i=0; i<res2.size(); ++i)
				{
					int status = res2[i][1];
					if(status == 0)
						questStarted.push_back(res2[i][0]);

					if(status == 1)
						questFinished.push_back(res2[i][0]);
				}
			}
			else
				std::cerr<<IceUtil::Time::now()<<": LBA_Server - Quest SELECT failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;
		}
	}
	else
	{
		Clear();
	}
}


/***********************************************************
set quest information
***********************************************************/
void DatabaseHandler::SetQuestInfo(const std::string& WorldName, long PlayerId,
					const std::vector<long> &questStarted, const std::vector<long> &questFinished)
{
	if(WorldName == "")
		return;

	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	mysqlpp::Query query(_mysqlH, false);
	query << "SELECT id FROM lba_usertoworld";
	query << " WHERE userid = '"<<PlayerId<<"'";
	query << " AND worldid = (SELECT id FROM lba_worlds WHERE name = '"<<WorldName<<"')";
	if (mysqlpp::StoreQueryResult res = query.store())
	{
		if(res.size() > 0)
		{
			query.clear();
			query << "DELETE FROM lba_quests";
			query << " WHERE worldid = '"<<res[0][0]<<"'";
			if(!query.exec())
				std::cerr<<IceUtil::Time::now()<<": LBA_Server - Quest DELETE failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;

			std::vector<long>::const_iterator iti = questStarted.begin();
			std::vector<long>::const_iterator endi = questStarted.end();
			for(;iti != endi; ++iti)
			{
				query.clear();
				query << "INSERT INTO lba_quests (worldid, questid, status) VALUES('";
				query << res[0][0] << "', '" << *iti << "', '" << 0  << "')";
				if(!query.exec())
					std::cerr<<IceUtil::Time::now()<<": LBA_Server - Quest INSERT failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;
			}

			iti = questFinished.begin();
			endi = questFinished.end();
			for(;iti != endi; ++iti)
			{
				query.clear();
				query << "INSERT INTO lba_quests (worldid, questid, status) VALUES('";
				query << res[0][0] << "', '" << *iti << "', '" << 1  << "')";
				if(!query.exec())
					std::cerr<<IceUtil::Time::now()<<": LBA_Server - Quest INSERT failed for user id "<<PlayerId<<" : "<<query.error()<<std::endl;
			}
		}
	}
	else
	{
		Clear();
	}
}


/***********************************************************
record player kill
***********************************************************/
void DatabaseHandler::RecordKill(const std::string& WorldName, long KilledId, int Reason, long KillerId)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	if(WorldName != "")
	{
		mysqlpp::Query query(_mysqlH, false);
		query << "UPDATE lba_usertoworld ";
		switch(Reason)
		{
			case 2:
				query << "SET FallDeath = FallDeath + 1";
			break;
			case 3:
				query << "SET MonsterDeath = MonsterDeath + 1";
			break;
			case 4:
				query << "SET PvpDeath = PvpDeath + 1";
			break;
			case 6:
				query << "SET DrowningDeath = DrowningDeath + 1";
			break;
			default:
				query << "SET OtherDeath = OtherDeath + 1";
			break;
		}
		query << " WHERE userid = '"<<KilledId<<"'";
		query << " AND worldid = (SELECT id FROM lba_worlds WHERE name = '"<<WorldName<<"')";
		if(!query.exec())
		{
			std::cerr<<IceUtil::Time::now()<<": LBA_Server - RecordKill failed for user id "<<KilledId<<" : "<<query.error()<<std::endl;
			Clear();
		}
	}

	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	if(WorldName != "")
	{
		if(Reason == 4)
		{
			mysqlpp::Query query(_mysqlH, false);
			query << "UPDATE lba_usertoworld ";
			query << "SET PvpKill = PvpKill + 1";
			query << " WHERE userid = '"<<KillerId<<"'";
			query << " AND worldid = (SELECT id FROM lba_worlds WHERE name = '"<<WorldName<<"')";
			if(!query.exec())
			{
				std::cerr<<IceUtil::Time::now()<<": LBA_Server - RecordKiller failed for user id "<<KillerId<<" : "<<query.error()<<std::endl;
				Clear();
			}
		}
	}
}


/***********************************************************
send a pm to someone
***********************************************************/
void DatabaseHandler::SendPM(const LbaNet::PMInfo &pm)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	{
	mysqlpp::Query query(_mysqlH, false);
	query << "SET character_set_client=utf8";
	query.execute();
	}

	std::vector<std::string> tos;
	StringHelper::Tokenize(pm.ToName, tos, ",");
	for(size_t i=0; i<tos.size(); ++i)
	{
		mysqlpp::Query query(_mysqlH, false);
		query << "INSERT INTO jos_uddeim (replyid, fromid, toid, message, datum) VALUES(";
		query << "'"<<pm.ReplyId<<"'"; // __________
		query << ",(SELECT id FROM jos_users WHERE username = "<<mysqlpp::quote<<pm.FromName<<")";
		query << ",(SELECT id FROM jos_users WHERE username = "<<mysqlpp::quote<<tos[i]<<")";
		query << ","<<mysqlpp::quote<<pm.Text;
		query << ", UNIX_TIMESTAMP() )";
		if(!query.exec())
		{
			std::cerr<<IceUtil::Time::now()<<": LBA_Server - SendPM failed for user id "<<pm.FromName<<" : "<<query.error()<<std::endl;
		}

	}
}

/***********************************************************
delete a pm
***********************************************************/
void DatabaseHandler::DeletePM(Ice::Long pmid)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	mysqlpp::Query query(_mysqlH, false);
	query << "UPDATE jos_uddeim SET totrash='1', totrashdate=UNIX_TIMESTAMP() WHERE id = '"<<pmid<<"'";
	if(!query.exec())
	{
		std::cerr<<IceUtil::Time::now()<<": LBA_Server - DeletePM failed for id "<<pmid<<" : "<<query.error()<<std::endl;
		Clear();
	}

}

/***********************************************************
MarkReadPM
***********************************************************/
void DatabaseHandler::MarkReadPM(Ice::Long pmid)
{
	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return;
		}
	}

	mysqlpp::Query query(_mysqlH, false);
	query << "UPDATE jos_uddeim SET toread='1' WHERE id = '"<<pmid<<"'";
	if(!query.exec())
	{
		std::cerr<<IceUtil::Time::now()<<": LBA_Server - MarkReadPM failed for id "<<pmid<<" : "<<query.error()<<std::endl;
		Clear();
	}

}


/***********************************************************
get all pm in your mailbox
***********************************************************/
LbaNet::PMsSeq DatabaseHandler::GetInboxPM(long playerid)
{
	LbaNet::PMsSeq pmsres;

	Lock sync(*this);
	if(!_mysqlH || !_mysqlH->connected())
	{
		Connect();
		if(!_mysqlH->connected())
		{
			Clear();
			return pmsres;
		}
	}

	{
	mysqlpp::Query query(_mysqlH, false);
	query << "SET character_set_results=utf8";
	query.execute();
	}


	mysqlpp::Query query(_mysqlH, false);
	query << "SELECT pm.id,	pm.fromid, pm.message, FROM_UNIXTIME(pm.datum), pm.toread, pm.replyid";
	query << " FROM jos_uddeim pm, jos_users ju, lba_users lu";
	query << " WHERE ju.id = lu.josiid";
	query << " AND ju.id = pm.toid";
	query << " AND pm.totrash = '0'";
	query << " AND lu.id = '"<<playerid<<"'";
	if (mysqlpp::StoreQueryResult res = query.store())
	{
		for(size_t i=0; i<res.size(); ++i)
		{
			LbaNet::PMInfo pi;
			pi.PMId = res[i][0];
			pi.Text = res[i][2].c_str();
			pi.Date = res[i][3].c_str();
			pi.Opened = ((int)res[i][4] == 1);
			pi.ReplyId = res[i][5];

			long senderid = res[i][1];

			query.clear();
			query << "SELECT username";
			query << " FROM jos_users";
			query << " WHERE id = '"<<senderid<<"'";

			if (mysqlpp::StoreQueryResult res2 = query.store())
			{
				if(res2.size() > 0)
				{
					pi.FromName = res2[0][0].c_str();
					pmsres.push_back(pi);
				}
			}

		}
	}
	else
	{
		std::cerr<<IceUtil::Time::now()<<": LBA_Server - GetInboxPM failed for playerid "<<playerid<<" : "<<query.error()<<std::endl;
		Clear();
	}

	return pmsres;
}