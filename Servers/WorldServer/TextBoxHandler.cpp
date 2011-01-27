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
#include "TextBoxHandler.h"
#include "SharedDataHandler.h"
#include "SynchronizedTimeHandler.h"
#include "MapHandler.h"

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
	ClientProxyBasePtr prx = SharedDataHandler::getInstance()->GetProxy(clientid);
	if(prx)
	{
		EventsSeq toplayer;
		toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
												"TextBox", GuiParamsSeq(), false, true));

		IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
		t->start();	
	}

	RemoveOpenedGui(clientid);
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void TextBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
	ShowGuiParamBase * ptr = params.get();
	const std::type_info& info = typeid(*ptr);

	// TextBoxParam
	if(info == typeid(TextBoxParam))
	{
		TextBoxParam * castedptr = 
			static_cast<TextBoxParam *>(ptr);


		ClientProxyBasePtr prx = SharedDataHandler::getInstance()->GetProxy(clientid);
		if(prx)
		{
			boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
			if(dbh)
			{
				EventsSeq toplayer;
				GuiParamsSeq seq;
				seq.push_back(new DisplayGameText(castedptr->_textid));
				toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														"TextBox", seq, true, false));

				IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
				t->start();	

				// add gui to the list to be removed later
				AddOpenedGui(clientid, curPosition);
			}
		}

	}
}