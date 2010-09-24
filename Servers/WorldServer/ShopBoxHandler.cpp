#include "ShopBoxHandler.h"


/***********************************************************
update gui with info from server
***********************************************************/
void ShopBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::BuyItemUpdate
	if(info == typeid(LbaNet::BuyItemUpdate))
	{
		LbaNet::BuyItemUpdate * castedptr = 
			dynamic_cast<LbaNet::BuyItemUpdate *>(ptr);

		//TODO
		//Ice::Long NPCId;
		//Ice::Long ItemId;
	}

	// LbaNet::GuiClosedUpdate
	if(info == typeid(LbaNet::GuiClosedUpdate))
	{
		RemoveOpenedGui(clientid);
	}
}

/***********************************************************
update gui with info from server
***********************************************************/
void ShopBoxHandler::HideGUI(Ice::Long clientid)
{
	// TODO

	RemoveOpenedGui(clientid);
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void ShopBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
	// TODO
}
