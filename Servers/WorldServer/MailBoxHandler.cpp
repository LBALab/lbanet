#include "MailBoxHandler.h"
#include "SharedDataHandler.h"
#include "SynchronizedTimeHandler.h"
#include "MapHandler.h"

/***********************************************************
update gui with info from server
***********************************************************/
void MailBoxHandler::Update(Ice::Long clientid, const LbaNet::GuiUpdateBasePtr &Update)
{
	LbaNet::GuiUpdateBase * ptr = Update.get();
	const std::type_info& info = typeid(*ptr);

	// LbaNet::DeletePMUpdate
	if(info == typeid(LbaNet::DeletePMUpdate))
	{
		LbaNet::DeletePMUpdate * castedptr = 
			dynamic_cast<LbaNet::DeletePMUpdate *>(ptr);

		boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
		if(dbh)
			dbh->DeletePM(castedptr->PMid);
	}

	// LbaNet::MarkReadPMUpdate
	if(info == typeid(LbaNet::MarkReadPMUpdate))
	{
		LbaNet::MarkReadPMUpdate * castedptr = 
			dynamic_cast<LbaNet::MarkReadPMUpdate *>(ptr);

		boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
		if(dbh)
			dbh->MarkReadPM(castedptr->PMid);
	}

	// LbaNet::SendPMUpdate
	if(info == typeid(LbaNet::SendPMUpdate))
	{
		LbaNet::SendPMUpdate * castedptr = 
			dynamic_cast<LbaNet::SendPMUpdate *>(ptr);

		boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
		if(dbh)
			dbh->SendPM(castedptr->PM);
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
void MailBoxHandler::HideGUI(Ice::Long clientid)
{
	ClientInterfacePrx prx = SharedDataHandler::getInstance()->GetProxy(clientid);
	if(prx)
	{
		EventsSeq toplayer;
		toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
												"MailBox", GuiParamsSeq(), false, true));

		IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
		t->start();	
	}

	RemoveOpenedGui(clientid);
}


/***********************************************************
show the GUI for a certain player
***********************************************************/
void MailBoxHandler::ShowGUI(Ice::Long clientid, const LbaNet::PlayerPosition &curPosition,
					boost::shared_ptr<ShowGuiParamBase> params)
{
	ClientInterfacePrx prx = SharedDataHandler::getInstance()->GetProxy(clientid);
	if(prx)
	{
		boost::shared_ptr<DatabaseHandlerBase> dbh = SharedDataHandler::getInstance()->GetDatabase();
		if(dbh)
		{
			EventsSeq toplayer;
			GuiParamsSeq seq;
			seq.push_back(new MailboxGuiParameter(dbh->GetInboxPM((long)clientid)));
			toplayer.push_back(new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), 
													"MailBox", seq, true, false));

			IceUtil::ThreadPtr t = new EventsSender(toplayer, prx);
			t->start();	

			// add gui to the list to be removed later
			AddOpenedGui(clientid, curPosition);
		}
	}
}