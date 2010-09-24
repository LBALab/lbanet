#include "ShortcutBoxHandler.h"


/***********************************************************
update gui with info from server
***********************************************************/
void ShortcutBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::ShortcutUpdate
	if(info == typeid(LbaNet::ShortcutUpdate))
	{
		LbaNet::ShortcutUpdate * castedptr = 
			dynamic_cast<LbaNet::ShortcutUpdate *>(ptr);

		//TODO
		//Ice::Int Position;
		//Ice::Long ItemId;
	}
}

/***********************************************************
update gui with info from server
***********************************************************/
void ShortcutBoxHandler::HideGUI(Ice::Long clientid)
{
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void ShortcutBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
}