#include "InventoryBoxHandler.h"


/***********************************************************
update gui with info from server
***********************************************************/
void InventoryBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::SwitchItemPosition
	if(info == typeid(LbaNet::SwitchItemPosition))
	{
		LbaNet::SwitchItemPosition * castedptr = 
			dynamic_cast<LbaNet::SwitchItemPosition *>(ptr);

		//TODO
		//Ice::Long ItemId;
		//Ice::Int NewPosition;
	}

	// LbaNet::InventoryItemUsed
	if(info == typeid(LbaNet::InventoryItemUsed))
	{
		LbaNet::InventoryItemUsed * castedptr = 
			dynamic_cast<LbaNet::InventoryItemUsed *>(ptr);

		//TODO
		//Ice::Long ItemId;
	}

	// LbaNet::CreateLetterUpdate
	if(info == typeid(LbaNet::CreateLetterUpdate))
	{
		LbaNet::CreateLetterUpdate * castedptr = 
			dynamic_cast<LbaNet::CreateLetterUpdate *>(ptr);

		//TODO
		//std::string Subject;
		//std::string Message;
	}

	// LbaNet::DestroyItemUpdate
	if(info == typeid(LbaNet::DestroyItemUpdate))
	{
		LbaNet::DestroyItemUpdate * castedptr = 
			dynamic_cast<LbaNet::DestroyItemUpdate *>(ptr);

		//TODO
		//Ice::Long ItemId;
	}
}

/***********************************************************
update gui with info from server
***********************************************************/
void InventoryBoxHandler::HideGUI(Ice::Long clientid)
{
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void InventoryBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
}