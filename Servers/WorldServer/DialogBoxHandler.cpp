#include "DialogBoxHandler.h"


/***********************************************************
update gui with info from server
***********************************************************/
void DialogBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::DialogSelectedUpdate
	if(info == typeid(LbaNet::DialogSelectedUpdate))
	{
		LbaNet::DialogSelectedUpdate * castedptr = 
			dynamic_cast<LbaNet::DialogSelectedUpdate *>(ptr);

		//TODO
		//Ice::Long NPCId;
		//Ice::Int SelectedId;
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
void DialogBoxHandler::HideGUI(Ice::Long clientid)
{
	// TODO

	RemoveOpenedGui(clientid);
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void DialogBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
	// TODO
}