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
#include "DialogBoxHandler.h"
#include "SharedDataHandler.h"
#include "SynchronizedTimeHandler.h"
#include "MapHandler.h"
#include "DialogPart.h"


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

		SelectDialog((long)clientid, castedptr->SelectedId);
	}

	// LbaNet::GuiClosedUpdate
	if(info == typeid(LbaNet::GuiClosedUpdate))
	{
		HideGUI(clientid);
	}
}

/***********************************************************
update gui with info from server
***********************************************************/
void DialogBoxHandler::HideGUI(Ice::Long clientid)
{
	ClientProxyBasePtr prx = SharedDataHandler::getInstance()->GetProxy(clientid);
	if(prx)
	{
		EventsSeq toplayer;
		toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
												"DialogBox", GuiParamsSeq(), false, true));

		IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
		t->start();	
	}

	RemoveOpenedGui(clientid);



	// remove from map
	std::map<long, DialogInfo>::iterator it = _openeddialog.find((long)clientid);
	if(it != _openeddialog.end())
	{
		long npcid = it->second.actorid;
		_openeddialog.erase(it);

		if(_owner)
			_owner->NpcUntargetPlayer(npcid, (long)clientid);
	}
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void DialogBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
	ShowGuiParamBase * ptr = params.get();
	DialogParam * castedptr = static_cast<DialogParam *>(params.get());

	ClientProxyBasePtr prx = SharedDataHandler::getInstance()->GetProxy(clientid);
	if(prx)
	{
		if(castedptr->_dialogroot)
		{
			DialogPartPtr dialptr = castedptr->_dialogroot->GetNpcNextDialog(_owner, (long)clientid);
			if(dialptr)
			{
				EventsSeq toplayer;
				GuiParamsSeq seq;
				DialogPartInfo dialpart;
				dialpart.NpcTextId = dialptr->PickText();

				std::vector<DialogPartPtr>  dials = dialptr->GetPlayerNextDialog(_owner, (long)clientid);
				for(size_t i=0; i<dials.size(); ++i)
					dialpart.PlayerTextsId.push_back(dials[i]->PickText());

				seq.push_back(new DialogGuiParameter(castedptr->_npcnametextid, 
														castedptr->_simpledialog, dialpart));

				toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														"DialogBox", seq, true, false));

				IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
				t->start();	

				// add gui to the list to be removed later
				AddOpenedGui(clientid, curPosition);

				// store info
				DialogInfo dinfo;
				dinfo.rootdialog = castedptr->_dialogroot;
				dinfo.currdialog = dials;
				dinfo.actorid = castedptr->_npcid;
				_openeddialog[(long)clientid] = dinfo;
			}
		}
	}
}

/***********************************************************
select dialog
***********************************************************/
void DialogBoxHandler::SelectDialog(long clientid, int selecteid)
{
	std::map<long, DialogInfo>::iterator it = _openeddialog.find(clientid);
	if(it != _openeddialog.end())
	{
		const std::vector<DialogPartPtr> &curr = it->second.currdialog;
		if(selecteid < 0 || selecteid >= (int)curr.size())
		{
			HideGUI(clientid);
			return;
		}

		boost::shared_ptr<DialogPart> selecteddial = curr[selecteid];
		if(selecteddial)
		{
			// execute action if any
			ActionBasePtr act = selecteddial->GetAction();
			if(act)
				act->Execute(_owner, 2, clientid, NULL);


			// check if dialog reset
			if(selecteddial->ResetDialog())
				selecteddial = it->second.rootdialog;


			// build next dialog part
			DialogPartPtr dialptr = selecteddial->GetNpcNextDialog(_owner, clientid);
			if(dialptr)
			{
				EventsSeq toplayer;
				GuiUpdatesSeq seq;
				DialogPartInfo dialpart;
				dialpart.NpcTextId = dialptr->PickText();

				std::vector<DialogPartPtr>  dials = dialptr->GetPlayerNextDialog(_owner, clientid);
				for(size_t i=0; i<dials.size(); ++i)
					dialpart.PlayerTextsId.push_back(dials[i]->PickText());

				seq.push_back(new DialogUpdate(dialpart));

				toplayer.push_back(new UpdateGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
														"DialogBox", seq));

				ClientProxyBasePtr prx = SharedDataHandler::getInstance()->GetProxy(clientid);
				if(prx)
				{
					IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
					t->start();	

					// store info
					it->second.currdialog = dials;
					return;
				}
			}
		}
	}

	// hide gui in case of problems
	HideGUI(clientid);
}