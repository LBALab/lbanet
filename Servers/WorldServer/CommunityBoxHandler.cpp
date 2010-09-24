#include "CommunityBoxHandler.h"


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

		//TODO
		//Ice::Long FriendId;
	}

	// LbaNet::RemoveFriend
	if(info == typeid(LbaNet::RemoveFriend))
	{
		LbaNet::RemoveFriend * castedptr = 
			dynamic_cast<LbaNet::RemoveFriend *>(ptr);

		//TODO
		//Ice::Long FriendId;
	}

	// LbaNet::RefreshFriends
	if(info == typeid(LbaNet::RefreshFriends))
	{
		//TODO
	}

	// LbaNet::AddFriend
	if(info == typeid(LbaNet::AddFriend))
	{
		LbaNet::AddFriend * castedptr = 
			dynamic_cast<LbaNet::AddFriend *>(ptr);

		//TODO
		//std::string FriendName;
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