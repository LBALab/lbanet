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

#include "JournalBox.h"
#include "GameGUI.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "DataLoader.h"
#include "StringHelperFuncs.h"
#include "Localizer.h"
#include "GUILocalizationCallback.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "OSGHandler.h"


#include <iostream>
#include <algorithm>
#include <CEGUI.h>




// Sample sub-class for ListboxTextItem that auto-sets the selection brush
// image.  This saves doing it manually every time in the code.
class MyTreeItem : public CEGUI::TreeItem
{
public:
	MyTreeItem (const CEGUI::String& text, const std::vector<CEGUI::String> & Desc, long QId = -1) 
		: CEGUI::TreeItem(text), Description(Desc), QuestId(QId)
    {
		if(Desc.size() > 0)
			setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    }

	long QuestId;
	std::vector<CEGUI::String> Description;
};


/***********************************************************
constructor
***********************************************************/
JournalBox::JournalBox()
: _first_book_init(true)
{



}


/***********************************************************
destructor
***********************************************************/
JournalBox::~JournalBox()
{
	try
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("JournalFrame"));

		int resX, resY; 
		bool fullscreen;
		OsgHandler::getInstance()->GetScreenAttributes(resX, resY, fullscreen);

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetValue("Gui.JournalBox.PosX", vec.d_x.asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetValue("Gui.JournalBox.PosY", vec.d_y.asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetValue("Gui.JournalBox.SizeX", frw->getWidth().asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetValue("Gui.JournalBox.SizeY", frw->getHeight().asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetValue("Gui.JournalBox.Visible", frw->isVisible());

		{
			std::string qtreedown;
			std::string selected;
			std::map<std::string, CEGUI::TreeItem *>::iterator itm =	_mapquestarea.begin();
			std::map<std::string, CEGUI::TreeItem *>::iterator endm =	_mapquestarea.end();
			for(; itm != endm; ++itm)
			{
				if(itm->second->getIsOpen())
				{
					qtreedown += "##" + itm->first;
				}

				std::vector<CEGUI::TreeItem*> items = itm->second->getItemList();
				for(size_t i=0; i<items.size(); ++i)
				{
					if(items[i]->isSelected())
						selected = items[i]->getText().c_str();
				}
			}

			ConfigurationManager::GetInstance()->SetValue("Gui.JournalBox.QuestTreeOpen", qtreedown);
			ConfigurationManager::GetInstance()->SetValue("Gui.JournalBox.QuestTreeSelected", selected);
		}

		{
			std::string qtreedown;
			std::string selected;
			std::map<std::string, CEGUI::TreeItem *>::iterator itm =	_mapquestdonearea.begin();
			std::map<std::string, CEGUI::TreeItem *>::iterator endm =	_mapquestdonearea.end();
			for(; itm != endm; ++itm)
			{
				if(itm->second->getIsOpen())
				{
					qtreedown += "##" + itm->first;
				}

				std::vector<CEGUI::TreeItem*> items = itm->second->getItemList();
				for(size_t i=0; i<items.size(); ++i)
				{
					if(items[i]->isSelected())
						selected = items[i]->getText().c_str();
				}
			}

			ConfigurationManager::GetInstance()->SetValue("Gui.JournalBox.QuestDoneTreeOpen", qtreedown);
			ConfigurationManager::GetInstance()->SetValue("Gui.JournalBox.QuestDoneTreeSelected", selected);
		}


	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception destructor Inventorybox: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
initalize the box
***********************************************************/
void JournalBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "questbook.layout",
								"", "", &MyPropertyCallback);
		Root->addChildWindow(_myBox);


		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("JournalFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&JournalBox::HandleClose, this));

		CEGUI::Tree * tree = static_cast<CEGUI::Tree *> (
			CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questtab/Tree"));

		tree->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,
							CEGUI::Event::Subscriber (&JournalBox::HandleQuestTreeSelected, this));


		CEGUI::Tree * tree2 = static_cast<CEGUI::Tree *> (
			CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questdonetab/Tree"));

		tree2->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,
							CEGUI::Event::Subscriber (&JournalBox::HandleQuestDoneTreeSelected, this));


		float PosX = ConfigurationManager::GetInstance()->GetValue("Gui.JournalBox.PosX", 0.65f);
		float PosY = ConfigurationManager::GetInstance()->GetValue("Gui.JournalBox.PosY", 0.56f);
		float SizeX = ConfigurationManager::GetInstance()->GetValue("Gui.JournalBox.SizeX", 0.35f);
		float SizeY = ConfigurationManager::GetInstance()->GetValue("Gui.JournalBox.SizeY", 0.34f);
		bool Visible = ConfigurationManager::GetInstance()->GetValue("Gui.JournalBox.Visible", false);
		frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, 0), CEGUI::UDim(PosY, 0)));
		frw->setWidth(CEGUI::UDim(SizeX, 0));
		frw->setHeight(CEGUI::UDim(SizeY, 0));

		if(Visible)
			frw->show();
		else
			frw->hide();


		// get quest topic tree which should be opened
		std::string treeqopen = ConfigurationManager::GetInstance()->GetValue<std::string>("Gui.JournalBox.QuestTreeOpen", "");
		std::string treedqopen = ConfigurationManager::GetInstance()->GetValue<std::string>("Gui.JournalBox.QuestDoneTreeOpen", "");

		_selected_tree_quests = ConfigurationManager::GetInstance()->GetValue<std::string>("Gui.JournalBox.QuestTreeSelected", "");
		_selected_tree_done_quests = ConfigurationManager::GetInstance()->GetValue<std::string>("Gui.JournalBox.QuestDoneTreeSelected", "");

		StringHelper::Tokenize(treeqopen, _open_tree_quests, "##");
		StringHelper::Tokenize(treedqopen, _open_tree_done_quests, "##");


		static_cast<CEGUI::TabControl *> (
			CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab"))->setSelectedTab("Root/JournalWin/tab/questtab");
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init InventoryBox: ") + ex.getMessage().c_str());
	}
}




/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool JournalBox::HandleClose (const CEGUI::EventArgs& e)
{
	_myBox->hide();
	return true;
}



/***********************************************************
display description
***********************************************************/
void JournalBox::DisplayDescription (const std::vector<CEGUI::String> & text, bool questdone)
{
	CEGUI::Window* descwin = NULL;
	if(questdone)
		descwin = CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questdonetab/Description");
	else
		descwin = CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questtab/Description");

	bool firsttime = true;
	descwin->setText("");

	for(size_t i=0; i<text.size(); ++i)
	{
		if(firsttime)
		{
			firsttime = false;
			descwin->setText(text[i]);
		}
		else
			descwin->appendText(text[i]);
	}
}


/***********************************************************
handle event when list is selected
***********************************************************/
bool JournalBox::HandleQuestTreeSelected (const CEGUI::EventArgs& e)
{
	CEGUI::Tree * tree = static_cast<CEGUI::Tree *> (
		CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questtab/Tree"));

	const MyTreeItem * it = static_cast<const MyTreeItem *>(tree->getFirstSelectedItem());
	if(it)
		DisplayDescription (it->Description, false);

	return true;
}


/***********************************************************
handle event when list is selected
***********************************************************/
bool JournalBox::HandleQuestDoneTreeSelected (const CEGUI::EventArgs& e)
{
	CEGUI::Tree * tree = static_cast<CEGUI::Tree *> (
		CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questdonetab/Tree"));

	const MyTreeItem * it = static_cast<const MyTreeItem *>(tree->getFirstSelectedItem());
	if(it)
		DisplayDescription (it->Description, true);
	

	return true;
}



/***********************************************************
call to regenerate the quest book display
***********************************************************/
void JournalBox::RebuildBook(bool reset)
{
	CEGUI::Tree * tree = static_cast<CEGUI::Tree *> (
		CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questtab/Tree"));

	CEGUI::Tree * tree2 = static_cast<CEGUI::Tree *> (
		CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questdonetab/Tree"));

	if(reset)
	{
		tree->resetList();
		tree2->resetList();
		_mapquestarea.clear();
		_mapquestdonearea.clear();
		CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questtab/Description")->setText("");
		CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questdonetab/Description")->setText("");
		_first_book_init = true;
	}


	// rebuild quests
	{
		// remove extra quests
		std::map<std::string, CEGUI::TreeItem *>::iterator itmap = _mapquestarea.begin();
		while(itmap != _mapquestarea.end())
		{
			bool remove = false;
			std::vector<CEGUI::TreeItem*> items = itmap->second->getItemList();
			for(size_t i=0; i<items.size(); ++i)
			{
				if(_QuestsStarted.find(static_cast<MyTreeItem *> (items[i])->QuestId) == _QuestsStarted.end())
				{	
					itmap->second->removeItem(items[i]);
					if(itmap->second->getItemCount() == 0)
						remove = true;
				}
			}

			if(remove)
			{
				tree->removeItem(itmap->second);
				itmap = _mapquestarea.erase(itmap);
			}
			else
				++itmap;
		}

		// add missing quests
		LbaNet::QuestsMap::const_iterator itstarted = _QuestsStarted.begin();
		LbaNet::QuestsMap::const_iterator endstarted = _QuestsStarted.end();
		for(; itstarted != endstarted; ++itstarted)
		{
			const LbaNet::QuestInfo &qi = itstarted->second;
			if(qi.Visible)
			{
				std::string Tittle = Localizer::getInstance()->GetText(Localizer::Quest, (long)qi.TittleTextId);
				std::string Description = Localizer::getInstance()->GetText(Localizer::Quest, (long)qi.DescriptionTextId);
				std::string QuestArea = Localizer::getInstance()->GetText(Localizer::Quest, (long)qi.QuestAreaTextId);

				if(QuestArea == "")
					QuestArea = "General";

				std::vector<CEGUI::String> listt;
				CreateTextList(Description, listt);



				std::map<std::string, CEGUI::TreeItem *>::iterator itm = _mapquestarea.find(QuestArea);
				if(itm != _mapquestarea.end())
				{
					bool found = false;
					std::vector<CEGUI::TreeItem*> items = itm->second->getItemList();
					for(size_t i=0; i<items.size(); ++i)
					{
						if(static_cast<MyTreeItem *> (items[i])->QuestId == qi.Id)
						{	
							found = true;
							break;
						}
					}

					if(!found)
					{
						MyTreeItem * titm = new MyTreeItem((const unsigned char *)Tittle.c_str(), listt, (long)qi.Id);
						itm->second->addItem(titm);

						if(_first_book_init)
						{
							if(_selected_tree_quests == Tittle)
							{
								titm->setSelected(true);
								DisplayDescription (titm->Description, false);
							}
						}
					}
				}
				else
				{
					MyTreeItem * titm = new MyTreeItem((const unsigned char *)Tittle.c_str(), listt, (long)qi.Id);
					std::vector<CEGUI::String> empty;
					CEGUI::TreeItem * root = new MyTreeItem((const unsigned char *)QuestArea.c_str(), empty);
					tree->addItem(root);
					root->addItem(titm);
					_mapquestarea[QuestArea] = root;

					if(_first_book_init)
					{
						if(_selected_tree_quests == Tittle)
						{
							titm->setSelected(true);
							DisplayDescription (titm->Description, false);
						}
					}
				}
			}
		}
	}


	// rebuild quests done
	{
		// remove extra quests
		std::map<std::string, CEGUI::TreeItem *>::iterator itmap = _mapquestdonearea.begin();
		while(itmap != _mapquestdonearea.end())
		{
			bool remove = false;
			std::vector<CEGUI::TreeItem*> items = itmap->second->getItemList();
			for(size_t i=0; i<items.size(); ++i)
			{
				if(_QuestsFinished.find(static_cast<MyTreeItem *> (items[i])->QuestId) == _QuestsFinished.end())
				{	
					itmap->second->removeItem(items[i]);
					if(itmap->second->getItemCount() == 0)
						remove = true;
				}
			}

			if(remove)
			{
				tree->removeItem(itmap->second);
				itmap = _mapquestdonearea.erase(itmap);
			}
			else
				++itmap;
		}

		// add missing quests
		LbaNet::QuestsMap::const_iterator itfinished = _QuestsFinished.begin();
		LbaNet::QuestsMap::const_iterator endfinished = _QuestsFinished.end();
		for(; itfinished != endfinished; ++itfinished)
		{
			const LbaNet::QuestInfo &qi = itfinished->second;
			if(qi.Visible)
			{
				std::string Tittle = Localizer::getInstance()->GetText(Localizer::Quest, (long)qi.TittleTextId);
				std::string Description = Localizer::getInstance()->GetText(Localizer::Quest, (long)qi.DescriptionTextId);
				std::string QuestArea = Localizer::getInstance()->GetText(Localizer::Quest, (long)qi.QuestAreaTextId);

				if(QuestArea == "")
					QuestArea = Localizer::getInstance()->GetText(Localizer::GUI, 84);

				std::vector<CEGUI::String> listt;
				CreateTextList(Description, listt);



				std::map<std::string, CEGUI::TreeItem *>::iterator itm = _mapquestdonearea.find(QuestArea);
				if(itm != _mapquestdonearea.end())
				{
					bool found = false;
					std::vector<CEGUI::TreeItem*> items = itm->second->getItemList();
					for(size_t i=0; i<items.size(); ++i)
					{
						if(static_cast<MyTreeItem *> (items[i])->QuestId == qi.Id)
						{	
							found = true;
							break;
						}
					}

					if(!found)
					{
						MyTreeItem * titm = new MyTreeItem((const unsigned char *)Tittle.c_str(), listt, (long)qi.Id);
						itm->second->addItem(titm);

						if(_first_book_init)
						{
							if(_selected_tree_done_quests == Tittle)
							{
								titm->setSelected(true);
								DisplayDescription (titm->Description, true);
							}
						}
					}
				}
				else
				{
					MyTreeItem * titm = new MyTreeItem((const unsigned char *)Tittle.c_str(), listt, (long)qi.Id);
					std::vector<CEGUI::String> empty;
					CEGUI::TreeItem * root = new MyTreeItem((const unsigned char *)QuestArea.c_str(), empty);
					tree2->addItem(root);
					root->addItem(titm);
					_mapquestdonearea[QuestArea] = root;

					if(_first_book_init)
					{
						if(_selected_tree_done_quests == Tittle)
						{
							titm->setSelected(true);
							DisplayDescription (titm->Description, true);
						}
					}
				}
			}
		}
	}


	if(!_first_book_init)
	{
		if(tree->getFirstSelectedItem() == NULL)
			CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questtab/Description")->setText("");
		
		if(tree2->getFirstSelectedItem() == NULL)
			CEGUI::WindowManager::getSingleton().getWindow("Root/JournalWin/tab/questdonetab/Description")->setText("");
	}

	if(_first_book_init)
	{
		_first_book_init = false;

		{
			std::map<std::string, CEGUI::TreeItem *>::iterator itm =	_mapquestarea.begin();
			std::map<std::string, CEGUI::TreeItem *>::iterator endm =	_mapquestarea.end();
			for(; itm != endm; ++itm)
			{
				if(std::find(_open_tree_quests.begin(), _open_tree_quests.end(), itm->first) != _open_tree_quests.end())
					itm->second->toggleIsOpen();
			}

		}

		{
			std::map<std::string, CEGUI::TreeItem *>::iterator itm =	_mapquestdonearea.begin();
			std::map<std::string, CEGUI::TreeItem *>::iterator endm =	_mapquestdonearea.end();
			for(; itm != endm; ++itm)
			{
				if(std::find(_open_tree_done_quests.begin(), _open_tree_done_quests.end(), itm->first) != _open_tree_done_quests.end())
					itm->second->toggleIsOpen();
			}
		}
	}

}



/***********************************************************
create description list
***********************************************************/
void JournalBox::CreateTextList(std::string text, std::vector<CEGUI::String> & list)
{
	int idxs = 0;
	while((idxs = text.find(" @ ")) != std::string::npos)
	{
		std::string tmp = text.substr(0, idxs);
		if(tmp == "")
			tmp = "\n";

		list.push_back((const unsigned char *)tmp.c_str());

		while(((idxs+4) < (int)text.size()) && (text[idxs+3] == '@') && (text[idxs+4] == ' '))
		{
			list.push_back("\n");
			idxs+= 2;
		}

		text = text.substr(idxs+3);
	}


	list.push_back((const unsigned char *)text.c_str());
}




/***********************************************************
refresh gui with info from server
***********************************************************/
void JournalBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{
	for(size_t i=0; i<Parameters.size(); ++i)
	{
		LbaNet::GuiParameterBase * ptr = Parameters[i].get();
		const std::type_info& info = typeid(*ptr);

		// shortcut updated
		if(info == typeid(LbaNet::QuestJournalGuiParameter))
		{
			LbaNet::QuestJournalGuiParameter * castedptr = 
				dynamic_cast<LbaNet::QuestJournalGuiParameter *>(ptr);

			_QuestsStarted = castedptr->QuestsStarted;
			_QuestsFinished = castedptr->QuestsFinished;	

			RebuildBook(true);
		}
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void JournalBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{
	for(size_t i=0; i<Updates.size(); ++i)
	{
		LbaNet::GuiUpdateBase * ptr = Updates[i].get();
		const std::type_info& info = typeid(*ptr);

		// QuestUpdate
		if(info == typeid(LbaNet::QuestUpdate))
		{
			LbaNet::QuestUpdate * castedptr = 
				dynamic_cast<LbaNet::QuestUpdate *>(ptr);

			const LbaNet::QuestInfo & QuestI = castedptr->Quest;

			if(castedptr->Finished)
			{
				_QuestsFinished[QuestI.Id] = QuestI;
				LbaNet::QuestsMap::iterator it = _QuestsStarted.find(QuestI.Id);
				if(it != _QuestsStarted.end())
					_QuestsStarted.erase(it);
			}
			else
			{
				_QuestsStarted[QuestI.Id] = QuestI;
				LbaNet::QuestsMap::iterator it = _QuestsFinished.find(QuestI.Id);
				if(it != _QuestsFinished.end())
					_QuestsFinished.erase(it);

				if(QuestI.Visible)
				{
					std::stringstream strs;
					strs << Localizer::getInstance()->GetText(Localizer::GUI, 97)<<": ";
					strs << Localizer::getInstance()->GetText(Localizer::Quest, (long)QuestI.TittleTextId);
			
					// send message to chatbox
					LbaNet::GuiUpdatesSeq updseq;
					LbaNet::ChatTextUpdate * upd = 
						new LbaNet::ChatTextUpdate("All", "info", strs.str());
					updseq.push_back(upd);
					EventsQueue::getReceiverQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
						SynchronizedTimeHandler::GetCurrentTimeDouble(), "ChatBox", updseq));
				}
			}

			RebuildBook(false);
		}
	}
}

/***********************************************************
show GUI
***********************************************************/
void JournalBox::Display()
{
	_myBox->show();
	_myBox->activate();
}

/***********************************************************
hide GUI
***********************************************************/
void JournalBox::Hide()
{
	_myBox->hide();
}

/***********************************************************
show/hide GUI
***********************************************************/
void JournalBox::ToggleDisplay()
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
void JournalBox::Focus(bool focus)
{

}


/***********************************************************
save size of windows to be restored after resize of the application
***********************************************************/
void JournalBox::SaveGUISizes(int oldscreenX, int oldscreenY)
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("JournalFrame"));

	CEGUI::UVector2 vec = frw->getPosition();
	_savedPosX = vec.d_x.asRelative((float)oldscreenX);
	_savedPosY = vec.d_y.asRelative((float)oldscreenY);
	_savedSizeX = frw->getWidth().asRelative((float)oldscreenX);
	_savedSizeY = frw->getHeight().asRelative((float)oldscreenY);
}


/***********************************************************
restore the correct size of the windows
***********************************************************/
void JournalBox::RestoreGUISizes()
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("JournalFrame"));

	frw->setPosition(CEGUI::UVector2(CEGUI::UDim(_savedPosX, 0), CEGUI::UDim(_savedPosY, 0)));
	frw->setWidth(CEGUI::UDim(_savedSizeX, 0));
	frw->setHeight(CEGUI::UDim(_savedSizeY, 0));
}
