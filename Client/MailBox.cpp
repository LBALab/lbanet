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

#include "MailBox.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "ClientExtendedTypes.h"
#include "CommunityBox.h"

#include <iostream>
#include <algorithm>
#include <CEGUI.h>


// Sample sub-class for ListboxTextItem that auto-sets the selection brush
// image.  This saves doing it manually every time in the code.
class MyListItemmail : public CEGUI::ListboxTextItem
{
public:
    MyListItemmail (const CEGUI::String& text) : CEGUI::ListboxTextItem(text)
    {
       // setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    }
};

class MyListItemcombocontact : public CEGUI::ListboxTextItem
{
public:
    MyListItemcombocontact (const CEGUI::String& text) : CEGUI::ListboxTextItem(text)
    {
       setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    }
};


/***********************************************************
util function
***********************************************************/
void replaceAll(std::string& context, const std::string& from, const std::string& to)
{
    size_t lookHere = 0;
    size_t foundHere;
    while((foundHere = context.find(from, lookHere)) != std::string::npos)
    {
          context.replace(foundHere, from.size(), to);
          lookHere = foundHere + to.size();
    }
}

/***********************************************************
constructor
***********************************************************/
MailBox::MailBox(CommunityBox * combox)
: _hidemailbox(false), _combox(combox)
{

}


/***********************************************************
destructor
***********************************************************/
MailBox::~MailBox()
{
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("Mailbox"));

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.PosX", vec.d_x.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.PosY", vec.d_y.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.SizeX", frw->getWidth().d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.SizeY", frw->getHeight().d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.OffsetPosX", vec.d_x.d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.OffsetPosY", vec.d_y.d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.OffsetSizeX", frw->getWidth().d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.OffsetSizeY", frw->getHeight().d_offset);

		CEGUI::MultiColumnList * mlist = static_cast<CEGUI::MultiColumnList *> (
			CEGUI::WindowManager::getSingleton().getWindow("Mailbox/list"));

		CEGUI::UDim dimcol0 = mlist->getColumnHeaderWidth(0);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.column0Size", dimcol0.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.column0Offset", dimcol0.d_offset);

		CEGUI::UDim dimcol1 = mlist->getColumnHeaderWidth(1);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.column1Size", dimcol1.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.column1Offset", dimcol1.d_offset);

		CEGUI::UDim dimcol2 = mlist->getColumnHeaderWidth(2);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.column2Size", dimcol2.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.column2Offset", dimcol2.d_offset);

		CEGUI::UDim dimcol3 = mlist->getColumnHeaderWidth(3);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.column3Size", dimcol3.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.column3Offset", dimcol3.d_offset);

		CEGUI::UDim dimcol4 = mlist->getColumnHeaderWidth(4);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.column4Size", dimcol4.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.Mailbox.column4Offset", dimcol4.d_offset);

		ConfigurationManager::GetInstance()->SetInt("Gui.Mailbox.SortColumn", mlist->getSortColumn());
		ConfigurationManager::GetInstance()->SetInt("Gui.Mailbox.SortDirection", mlist->getSortDirection());
	}

	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("ReadMailFrame"));

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.ReadMailFrame.PosX", vec.d_x.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.ReadMailFrame.PosY", vec.d_y.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.ReadMailFrame.SizeX", frw->getWidth().d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.ReadMailFrame.SizeY", frw->getHeight().d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.ReadMailFrame.OffsetPosX", vec.d_x.d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.ReadMailFrame.OffsetPosY", vec.d_y.d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.ReadMailFrame.OffsetSizeX", frw->getWidth().d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.ReadMailFrame.OffsetSizeY", frw->getHeight().d_offset);
	}

	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame"));

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.WriteMailFrame.PosX", vec.d_x.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.WriteMailFrame.PosY", vec.d_y.d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.WriteMailFrame.SizeX", frw->getWidth().d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.WriteMailFrame.SizeY", frw->getHeight().d_scale);
		ConfigurationManager::GetInstance()->SetFloat("Gui.WriteMailFrame.OffsetPosX", vec.d_x.d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.WriteMailFrame.OffsetPosY", vec.d_y.d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.WriteMailFrame.OffsetSizeX", frw->getWidth().d_offset);
		ConfigurationManager::GetInstance()->SetFloat("Gui.WriteMailFrame.OffsetSizeY", frw->getHeight().d_offset);
	}
}


/***********************************************************
initalize the box
***********************************************************/
void MailBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "mailbox.layout" );
		Root->addChildWindow(_myBox);
		_myBox->hide();


		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("Mailbox"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&MailBox::HandleQuit, this));


		CEGUI::MultiColumnList * mlist = static_cast<CEGUI::MultiColumnList *> (
			CEGUI::WindowManager::getSingleton().getWindow("Mailbox/list"));
		mlist->setSelectionMode(CEGUI::MultiColumnList::CellSingle);

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("Mailbox/ComposeB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MailBox::HandleCompose, this));



		mlist->subscribeEvent(CEGUI::MultiColumnList::EventSelectionChanged,
									CEGUI::Event::Subscriber (&MailBox::Handlelistselected, this));

		float PosX, PosY, SizeX, SizeY, OPosX, OPosY, OSizeX, OSizeY;
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.PosX", PosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.PosY", PosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.SizeX", SizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.SizeY", SizeY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.OffsetPosX", OPosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.OffsetPosY", OPosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.OffsetSizeX", OSizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.OffsetSizeY", OSizeY);
		frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, OPosX), CEGUI::UDim(PosY, OPosY)));
		frw->setWidth(CEGUI::UDim(SizeX, OSizeX));
		frw->setHeight(CEGUI::UDim(SizeY, OSizeY));


		CEGUI::UDim dimcol0, dimcol1, dimcol2, dimcol3, dimcol4;
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.column0Size", dimcol0.d_scale);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.column0Offset", dimcol0.d_offset);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.column1Size", dimcol1.d_scale);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.column1Offset", dimcol1.d_offset);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.column2Size", dimcol2.d_scale);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.column2Offset", dimcol2.d_offset);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.column3Size", dimcol3.d_scale);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.column3Offset", dimcol3.d_offset);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.column4Size", dimcol4.d_scale);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Mailbox.column4Offset", dimcol4.d_offset);

		mlist->setColumnHeaderWidth(0, dimcol0);
		mlist->setColumnHeaderWidth(1, dimcol1);
		mlist->setColumnHeaderWidth(2, dimcol2);
		mlist->setColumnHeaderWidth(3, dimcol3);
		mlist->setColumnHeaderWidth(4, dimcol4);

		int SortColumn, SortDir;
		ConfigurationManager::GetInstance()->GetInt("Gui.Mailbox.SortColumn", SortColumn);
		ConfigurationManager::GetInstance()->GetInt("Gui.Mailbox.SortDirection", SortDir);
		mlist->setSortColumn(SortColumn);
		mlist->setSortDirection((CEGUI::ListHeaderSegment::SortDirection)SortDir);
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init MailBox: ") + ex.getMessage().c_str());
	}


	try
	{
		_readMailBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "readmail.layout" );
		Root->addChildWindow(_readMailBox);
		_readMailBox->hide();

		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("ReadMailFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&MailBox::HandleCloseRead, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("ReadMailFrame/ReplyB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MailBox::HandleReadReply, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("ReadMailFrame/DestroyB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MailBox::HandleReadDelete, this));		

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("ReadMailFrame/CloseB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MailBox::HandleCloseRead, this));	

		float PosX, PosY, SizeX, SizeY, OPosX, OPosY, OSizeX, OSizeY;
		ConfigurationManager::GetInstance()->GetFloat("Gui.ReadMailFrame.PosX", PosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.ReadMailFrame.PosY", PosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.ReadMailFrame.SizeX", SizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.ReadMailFrame.SizeY", SizeY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.ReadMailFrame.OffsetPosX", OPosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.ReadMailFrame.OffsetPosY", OPosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.ReadMailFrame.OffsetSizeX", OSizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.ReadMailFrame.OffsetSizeY", OSizeY);
		frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, OPosX), CEGUI::UDim(PosY, OPosY)));
		frw->setWidth(CEGUI::UDim(SizeX, OSizeX));
		frw->setHeight(CEGUI::UDim(SizeY, OSizeY));
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init MailBox: ") + ex.getMessage().c_str());
	}


	try
	{
		_writeMailBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "writemail.layout" );
		Root->addChildWindow(_writeMailBox);
		_writeMailBox->hide();
	
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&MailBox::HandleWriteCancel, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame/GoB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MailBox::HandleWriteSend, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame/CancelB"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&MailBox::HandleWriteCancel, this));	

		static_cast<CEGUI::Combobox *> (
		CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame/contacts"))->subscribeEvent
		(CEGUI::Combobox::EventListSelectionAccepted,
			CEGUI::Event::Subscriber (&MailBox::Handlecontactselected, this));

		float PosX, PosY, SizeX, SizeY, OPosX, OPosY, OSizeX, OSizeY;
		ConfigurationManager::GetInstance()->GetFloat("Gui.WriteMailFrame.PosX", PosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.WriteMailFrame.PosY", PosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.WriteMailFrame.SizeX", SizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.WriteMailFrame.SizeY", SizeY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.WriteMailFrame.OffsetPosX", OPosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.WriteMailFrame.OffsetPosY", OPosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.WriteMailFrame.OffsetSizeX", OSizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.WriteMailFrame.OffsetSizeY", OSizeY);
		frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, OPosX), CEGUI::UDim(PosY, OPosY)));
		frw->setWidth(CEGUI::UDim(SizeX, OSizeX));
		frw->setHeight(CEGUI::UDim(SizeY, OSizeY));
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init MailBox: ") + ex.getMessage().c_str());
	}
		
}



/***********************************************************
update mailbox content
***********************************************************/
void MailBox::UpdateMailbox(const LbaNet::PMsSeq &pms)
{
	_currentpms = pms;

	// removing crap from uddeim
	for(size_t i=0; i<_currentpms.size(); ++i)
	{
		LbaNet::PMInfo &pm = _currentpms[i];
		replaceAll(pm.Text, "[b]", "");
		replaceAll(pm.Text, "[/b]", "");
		replaceAll(pm.Text, "[url=", "");
		replaceAll(pm.Text, "[/url]", "");
		replaceAll(pm.Text, "\\n", "");
	}



	try
	{
		CEGUI::MultiColumnList * mlist = static_cast<CEGUI::MultiColumnList *> (
			CEGUI::WindowManager::getSingleton().getWindow("Mailbox/list"));

		CEGUI::ListHeaderSegment::SortDirection save = mlist->getSortDirection();
		mlist->setSortDirection(CEGUI::ListHeaderSegment::None);

		mlist->resetList();

		if(mlist)
		{
			for(size_t i=0; i<_currentpms.size(); ++i)
			{
				mlist->addRow(i);
				{
				CEGUI::String tmp("[image='set:mailb_trash image:full_image' MousePassThroughEnabled='True']");
				CEGUI::ListboxTextItem * itm = new MyListItemmail(tmp);
				itm->setTooltipText("delete");
				itm->setID((long)_currentpms[i].PMId);
				mlist->setItem(itm, 1, i);
				
				}

				if(_currentpms[i].Opened)
				{
					CEGUI::String tmp("[image='set:mailb_notnew image:full_image']");
					CEGUI::ListboxTextItem * itm = new MyListItemmail(tmp);
					itm->setTooltipText("read");
					itm->setID(i);
					mlist->setItem(itm, 2, i);
				}
				else
				{
					CEGUI::String tmp("[image='set:mailb_new image:full_image']");
					CEGUI::ListboxTextItem * itm = new MyListItemmail(tmp);
					itm->setTooltipText("unread");
					itm->setID(i);
					mlist->setItem(itm, 2, i);
				}

				{
				CEGUI::String tmp((const unsigned char *)_currentpms[i].Date.c_str());
				CEGUI::ListboxTextItem * itm = new MyListItemmail(tmp);
				itm->setTooltipText("Date");
				itm->setID(i);
				mlist->setItem(itm, 3, i);
				}
				{
				CEGUI::String tmp((const unsigned char *)_currentpms[i].FromName.c_str());
				CEGUI::ListboxTextItem * itm = new MyListItemmail(tmp);
				itm->setID(i);
				mlist->setItem(itm, 4, i);
				}
				{
				std::string txt = _currentpms[i].Text.substr(0, 25);
				replaceAll(txt, "\n", "");
				txt +="...";
				CEGUI::String tmp((const unsigned char *)txt.c_str());
				CEGUI::ListboxTextItem * itm = new MyListItemmail(tmp);
				itm->setID(i);
				mlist->setItem(itm, 5, i);
				}
			}
		}

		mlist->handleUpdatedItemData();
		mlist->setSortDirection(save);
		mlist->handleUpdatedItemData();
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init MailBox Show: ") + ex.getMessage().c_str());
	}

}


/***********************************************************
handle close button event
***********************************************************/
bool MailBox::HandleQuit(const CEGUI::EventArgs& e)
{
	_myBox->hide();
	return true;
}


/***********************************************************
handle list selected event
***********************************************************/
bool MailBox::Handlelistselected(const CEGUI::EventArgs& e)
{
	try
	{
		CEGUI::MultiColumnList * mlist = static_cast<CEGUI::MultiColumnList *> (
			CEGUI::WindowManager::getSingleton().getWindow("Mailbox/list"));

		if(mlist)
		{
			CEGUI::ListboxItem* li = mlist->getFirstSelectedItem();
			if(li)
			{
				long mid = (long)li->getID();

				if(li->getTooltipText() == "delete")
				{
					LbaNet::GuiUpdatesSeq updseq;
					LbaNet::DeletePMUpdate * upd = 
						new LbaNet::DeletePMUpdate(mid);
					updseq.push_back(upd);
					EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "MailBox", updseq));
				}
				else
				{
					DisplayMail(_currentpms[mid]);
				}
			}
		}
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init MailBox Handlelistselected: ") + ex.getMessage().c_str());
	}

	return true;
}


/***********************************************************
display a mail on the screen
***********************************************************/
void MailBox::DisplayMail(const LbaNet::PMInfo & pm)
{
	_currentread = pm.PMId;
	_currentcomposeTo = pm.FromName;
	_currentcomposeText = "\n\n\n__________\n"+pm.Text;

	try
	{
		CEGUI::String tmp1((const unsigned char *)pm.FromName.c_str());
		CEGUI::String tmp2((const unsigned char *)pm.Text.c_str());
		CEGUI::WindowManager::getSingleton().getWindow("ReadMailFrame/FromEdit")->setText(tmp1);
		CEGUI::WindowManager::getSingleton().getWindow("ReadMailFrame/Message")->setText(tmp2);
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init MailBox DisplayMail: ") + ex.getMessage().c_str());
	}

	_hidemailbox = true;
	_readMailBox->show();
	_myBox->hide();
	_writeMailBox->hide();

	if(!pm.Opened)
	{
		LbaNet::GuiUpdatesSeq updseq;
		LbaNet::MarkReadPMUpdate * upd = 
			new LbaNet::MarkReadPMUpdate(_currentread);
		updseq.push_back(upd);
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), "MailBox", updseq));
	}
}




/***********************************************************
handle list selected event
***********************************************************/
bool MailBox::HandleCloseRead(const CEGUI::EventArgs& e)
{
	SwitchToMailBox();
	return true;
}


/***********************************************************
handle list selected event
***********************************************************/
bool MailBox::HandleReadDelete(const CEGUI::EventArgs& e)
{
	LbaNet::GuiUpdatesSeq updseq;
	LbaNet::DeletePMUpdate * upd = 
		new LbaNet::DeletePMUpdate(_currentread);
	updseq.push_back(upd);
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "MailBox", updseq));

	SwitchToMailBox();
	return true;
}	


/***********************************************************
handle list selected event
***********************************************************/
bool MailBox::HandleReadReply(const CEGUI::EventArgs& e)
{
	_replyto = _currentread;
	DisplayWriteMail();
	return true;
}


/***********************************************************
switch to mailbox
***********************************************************/
void MailBox::SwitchToMailBox()
{
	_myBox->show();
	_readMailBox->hide();
	_writeMailBox->hide();
	_hidemailbox = false;
}


/***********************************************************
handle list selected event
***********************************************************/
bool MailBox::HandleCompose(const CEGUI::EventArgs& e)
{
	_replyto = 0;
	_currentcomposeTo = "";
	_currentcomposeText = "";
	DisplayWriteMail();
	return true;
}

/***********************************************************
display a write mail on the screen
***********************************************************/
void MailBox::DisplayWriteMail()
{
	try
	{
		CEGUI::String tmp1((const unsigned char *)_currentcomposeTo.c_str());
		CEGUI::String tmp2((const unsigned char *)_currentcomposeText.c_str());
		CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame/ToEdit")->setText(tmp1);
		CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame/Message")->setText(tmp2);
		
		std::vector<std::string> fl = _combox->GetFriendList();

		CEGUI::Combobox * contlist = static_cast<CEGUI::Combobox *> (
		CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame/contacts"));
		contlist->resetList();
		
		for(size_t i=0; i<fl.size(); ++i)
		{
			CEGUI::String tmp((const unsigned char *)fl[i].c_str());
			contlist->addItem(new MyListItemcombocontact(tmp));
		}
		contlist->setText("Friends");
		contlist->setReadOnly(true);

	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init MailBox DisplayMail: ") + ex.getMessage().c_str());
	}


	_hidemailbox = true;
	_readMailBox->hide();
	_myBox->hide();
	_writeMailBox->show();


}

/***********************************************************
handle list selected event
***********************************************************/
bool MailBox::HandleWriteSend(const CEGUI::EventArgs& e)
{
	SwitchToMailBox();
	LbaNet::PMInfo pm;
	pm.ReplyId = _replyto;
	pm.ToName = CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame/ToEdit")->getText().c_str();
	pm.Text = CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame/Message")->getText().c_str();

	LbaNet::GuiUpdatesSeq updseq;
	LbaNet::SendPMUpdate * upd = 
		new LbaNet::SendPMUpdate(pm);
	updseq.push_back(upd);
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "MailBox", updseq));

	return true;
}

/***********************************************************
handle list selected event
***********************************************************/
bool MailBox::HandleWriteCancel(const CEGUI::EventArgs& e)
{
	SwitchToMailBox();
	return true;
}


/***********************************************************
handle list selected event
***********************************************************/
bool MailBox::Handlecontactselected(const CEGUI::EventArgs& e)
{
	try
	{
		CEGUI::Combobox * contlist = static_cast<CEGUI::Combobox *> (
		CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame/contacts"));

		if(contlist)
		{
			CEGUI::ListboxItem* li = contlist->getSelectedItem();
			if(li)
			{
				CEGUI::Window * totext = CEGUI::WindowManager::getSingleton().getWindow("WriteMailFrame/ToEdit");
				CEGUI::String currentt = totext->getText();
				if(currentt.empty())
					currentt = li->getText();
				else
					currentt += "," + li->getText();

				totext->setText(currentt);
			}

			contlist->setText("Friends");
		}
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init MailBox Handlelistselected: ") + ex.getMessage().c_str());
	}

	return true;
}



/***********************************************************
 hide mails
***********************************************************/
void MailBox::HideMails()
{
	_hidemailbox = false;
	_readMailBox->hide();
	_myBox->hide();
	_writeMailBox->hide();
}



/***********************************************************
refresh gui with info from server
***********************************************************/
void MailBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{
	for(size_t i=0; i<Parameters.size(); ++i)
	{
		LbaNet::GuiParameterBase * ptr = Parameters[i].get();
		const std::type_info& info = typeid(*ptr);

		// shortcut updated
		if(info == typeid(LbaNet::MailboxGuiParameter))
		{
			LbaNet::MailboxGuiParameter * castedptr = 
				dynamic_cast<LbaNet::MailboxGuiParameter *>(ptr);

			UpdateMailbox(castedptr->MailboxContent);
		}
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void MailBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{
}

/***********************************************************
show GUI
***********************************************************/
void MailBox::Display()
{
	if(!_myBox->isVisible() && !_hidemailbox)
		_myBox->show();
}

/***********************************************************
hide GUI
***********************************************************/
void MailBox::Hide()
{
	HideMails();
}

/***********************************************************
show/hide GUI
***********************************************************/
void MailBox::ToggleDisplay()
{
	if(_myBox->isVisible())
		_myBox->hide();
	else
	{
		_myBox->show();
		_myBox->activate();
	}
}

/***********************************************************
focus GUI
***********************************************************/
void MailBox::Focus(bool focus)
{

}