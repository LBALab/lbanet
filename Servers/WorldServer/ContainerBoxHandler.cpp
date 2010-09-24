#include "ContainerBoxHandler.h"


/***********************************************************
update gui with info from server
***********************************************************/
void ContainerBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::UpdateInvContainer
	if(info == typeid(LbaNet::UpdateInvContainer))
	{
		LbaNet::UpdateInvContainer * castedptr = 
			dynamic_cast<LbaNet::UpdateInvContainer *>(ptr);

		//TODO
		//Ice::Long Containerid;
		//LbaNet::ItemList Taken;
		//LbaNet::ItemList Put;	

		RemoveOpenedGui(clientid);
	}
}

/***********************************************************
update gui with info from server
***********************************************************/
void ContainerBoxHandler::HideGUI(Ice::Long clientid)
{
	// TODO

	RemoveOpenedGui(clientid);
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void ContainerBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
	// TODO
}