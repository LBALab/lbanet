#include "TextBoxHandler.h"


/***********************************************************
update gui with info from server
***********************************************************/
void TextBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::GuiClosedUpdate
	if(info == typeid(LbaNet::GuiClosedUpdate))
	{
		RemoveOpenedGui(clientid);
	}
}

/***********************************************************
update gui with info from server
***********************************************************/
void TextBoxHandler::HideGUI(Ice::Long clientid)
{
	// TODO

	RemoveOpenedGui(clientid);
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void TextBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
	// TODO
}