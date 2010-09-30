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
#include "CommunityBoxHandler.h"
#include "SharedDataHandler.h"
#include "SynchronizedTimeHandler.h"
#include "MapHandler.h"

/***********************************************************
update gui with info from server
***********************************************************/
void CommunityBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::AcceptFriend
	if(info == typeid(LbaNet::AcceptFriend))
	{
		LbaNet::AcceptFriend * castedptr = 
			dynamic_cast<LbaNet::AcceptFriend *>(ptr);

		boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
		if(dbh)
		{
			std::string friendname;
			std::string myname;
			if(dbh->AcceptFriend((long)clientid, (long)castedptr->FriendId, friendname, myname))
			{
				// inform first player that the friend request is accepted
				{
					ClientInterfacePrx prx = SharedDataHandler::getInstance()->GetProxy(clientid);
					if(prx)
					{
						EventsSeq toplayer;
						GuiUpdatesSeq paramseq;
						FriendInfo finfo;
						finfo.Id = (long)castedptr->FriendId;
						finfo.Pending = false;
						finfo.ToAccept = false;
						finfo.Name = friendname;
						finfo.Removed = false;

						paramseq.push_back(new FriendChangedUpdate(finfo));
						toplayer.push_back(new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																"CommunityBox", paramseq));

						IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
						t->start();	
					}
				}

				// inform second player that the friend request is accepted
				{
					ClientInterfacePrx prx = SharedDataHandler::getInstance()->GetProxy(castedptr->FriendId);
					if(prx)
					{
						EventsSeq toplayer;
						GuiUpdatesSeq paramseq;
						FriendInfo finfo;
						finfo.Id = (long)clientid;
						finfo.Pending = false;
						finfo.ToAccept = false;
						finfo.Name = myname;
						finfo.Removed = false;

						paramseq.push_back(new FriendChangedUpdate(finfo));
						toplayer.push_back(new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																"CommunityBox", paramseq));

						IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
						t->start();	
					}
				}
			}
		}
	}

	// LbaNet::RemoveFriend
	if(info == typeid(LbaNet::RemoveFriend))
	{
		LbaNet::RemoveFriend * castedptr = 
			dynamic_cast<LbaNet::RemoveFriend *>(ptr);

		boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
		if(dbh)
		{
			dbh->RemoveFriend((long)clientid, (long)castedptr->FriendId);

			{
				// inform first player that the friend is removed
				{
					ClientInterfacePrx prx = SharedDataHandler::getInstance()->GetProxy(clientid);
					if(prx)
					{
						EventsSeq toplayer;
						GuiUpdatesSeq paramseq;
						FriendInfo finfo;
						finfo.Id = (long)castedptr->FriendId;
						finfo.Pending = false;
						finfo.ToAccept = false;
						finfo.Removed = true;

						paramseq.push_back(new FriendChangedUpdate(finfo));
						toplayer.push_back(new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																"CommunityBox", paramseq));

						IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
						t->start();	
					}
				}

				// inform second player that the friend is removed
				{
					ClientInterfacePrx prx = SharedDataHandler::getInstance()->GetProxy(castedptr->FriendId);
					if(prx)
					{
						EventsSeq toplayer;
						GuiUpdatesSeq paramseq;
						FriendInfo finfo;
						finfo.Id = (long)clientid;
						finfo.Pending = false;
						finfo.ToAccept = false;
						finfo.Removed = true;

						paramseq.push_back(new FriendChangedUpdate(finfo));
						toplayer.push_back(new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																"CommunityBox", paramseq));

						IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
						t->start();	
					}
				}
			}
		}

	}

	// LbaNet::RefreshFriends
	if(info == typeid(LbaNet::RefreshFriends))
	{
		boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
		if(dbh)
		{
			// et list from db
			LbaNet::FriendsSeq friends = dbh->GetFriends((long)clientid);

			// send list to player
			ClientInterfacePrx prx = SharedDataHandler::getInstance()->GetProxy(clientid);
			if(prx)
			{
				EventsSeq toplayer;
				GuiParamsSeq paramseq;
				paramseq.push_back(new FriendListGuiParameter(friends));
				toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														"CommunityBox", paramseq, false, false));

				IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
				t->start();	
			}

		}
	}

	// LbaNet::AddFriend
	if(info == typeid(LbaNet::AddFriend))
	{
		LbaNet::AddFriend * castedptr = 
			dynamic_cast<LbaNet::AddFriend *>(ptr);

		boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
		if(dbh)
		{
			long friendid = -1;
			std::string myname;
			if(dbh->AskFriend((long)clientid, castedptr->FriendName, friendid, myname))
			{
				// inform first player that the friend request is processed
				{
					ClientInterfacePrx prx = SharedDataHandler::getInstance()->GetProxy(clientid);
					if(prx)
					{
						EventsSeq toplayer;
						GuiUpdatesSeq paramseq;
						FriendInfo finfo;
						finfo.Id = (long)friendid;
						finfo.Pending = true;
						finfo.ToAccept = false;
						finfo.Name = castedptr->FriendName;
						finfo.Removed = false;

						paramseq.push_back(new FriendChangedUpdate(finfo));
						toplayer.push_back(new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																"CommunityBox", paramseq));

						IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
						t->start();	
					}
				}

				// inform second player that there is a friend request
				{
					ClientInterfacePrx prx = SharedDataHandler::getInstance()->GetProxy(friendid);
					if(prx)
					{
						EventsSeq toplayer;
						GuiUpdatesSeq paramseq;
						FriendInfo finfo;
						finfo.Id = (long)clientid;
						finfo.Pending = false;
						finfo.ToAccept = true;
						finfo.Name = myname;
						finfo.Removed = false;

						paramseq.push_back(new FriendChangedUpdate(finfo));
						toplayer.push_back(new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
																"CommunityBox", paramseq));

						IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
						t->start();	
					}
				}
			}
		}
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void CommunityBoxHandler::HideGUI(Ice::Long clientid)
{
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void CommunityBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
}