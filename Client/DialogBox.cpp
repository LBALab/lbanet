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

#include "DialogBox.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "ImageSetHandler.h"
#include "EventsQueue.h"
#include "SynchronizedTimeHandler.h"
#include "DataLoader.h"
#include "OSGHandler.h"

#include <iostream>
#include <algorithm>
#include <CEGUI.h>


// Sample sub-class for ListboxTextItem that auto-sets the selection brush
// image.  This saves doing it manually every time in the code.
class MyDialogItem : public CEGUI::ListboxTextItem
{
private:
	CEGUI::FormattedRenderedString * d_formattedRenderedString;

public:
    MyDialogItem (const CEGUI::String& text, size_t index) 
		: CEGUI::ListboxTextItem(text), _SelectionIdx(index)
    {
        setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");

        d_formattedRenderedString =
            new CEGUI::RenderedStringWordWrapper
                <CEGUI::LeftAlignedRenderedString>(d_renderedString);
    }

	//! destructor
    ~MyDialogItem ()
    {
        delete d_formattedRenderedString;
    }

	/*************************************************************************
		Required implementations of pure virtuals from the base class.
	*************************************************************************/
    CEGUI::Size getPixelSize(void) const
	{
		using namespace CEGUI;

		if (!d_renderedStringValid)
			parseTextString();

		CEGUI::Size parentsi = getOwnerWindow()->getInnerRectClipper().getSize();
		parentsi.d_width -= 20; // TODO - change constant by the real value of the scrollbar
		
        d_formattedRenderedString->format(parentsi);
		return CEGUI::Size(parentsi.d_width, d_formattedRenderedString->getVerticalExtent());
	}


    void draw(CEGUI::GeometryBuffer& buffer, const CEGUI::Rect& targetRect, float alpha, 
					const CEGUI::Rect* clipper) const
	{
		using namespace CEGUI;

		if (d_selected && d_selectBrush != 0)
			d_selectBrush->draw(buffer, targetRect, clipper,
								getModulateAlphaColourRect(d_selectCols, alpha));

		if (!d_renderedStringValid)
			parseTextString();

        d_formattedRenderedString->format(targetRect.getSize());

		const ColourRect final_colours(
			getModulateAlphaColourRect(ColourRect(0xFFFFFFFF), alpha));

        d_formattedRenderedString->draw(buffer,
                                        targetRect.getPosition(),									
										&final_colours, clipper);
	}

	size_t _SelectionIdx;
};




/***********************************************************
constructor
***********************************************************/
NPCDialogBox::NPCDialogBox()
{



}


/***********************************************************
destructor
***********************************************************/
NPCDialogBox::~NPCDialogBox()
{
	try
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("DialogFrame"));

		int resX, resY; 
		bool fullscreen;
		OsgHandler::getInstance()->GetScreenAttributes(resX, resY, fullscreen);

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.DialogBox.PosX", vec.d_x.asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.DialogBox.PosY", vec.d_y.asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetFloat("Gui.DialogBox.SizeX", frw->getWidth().asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.DialogBox.SizeY", frw->getHeight().asRelative((float)resY));
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception destructor chatbox: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
initalize the box
***********************************************************/
void NPCDialogBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myBox = CEGUI::WindowManager::getSingleton().loadWindowLayout( "dialog.layout" );
		Root->addChildWindow(_myBox);


		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("DialogFrame"));
		frw->subscribeEvent (
			CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&NPCDialogBox::HandleClose, this));

		frw->subscribeEvent(CEGUI::Window::EventKeyDown,
			CEGUI::Event::Subscriber (&NPCDialogBox::HandleEnterKey, this));


		CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
			CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/listbox"));
		lb->subscribeEvent(CEGUI::Listbox::EventMouseClick,
						CEGUI::Event::Subscriber (&NPCDialogBox::Handlelbelected, this));
		lb->subscribeEvent(CEGUI::Listbox::EventMouseMove,
			CEGUI::Event::Subscriber (&NPCDialogBox::HandleMouseEnter, this));


		{
			float PosX, PosY, SizeX, SizeY;
			ConfigurationManager::GetInstance()->GetFloat("Gui.DialogBox.PosX", PosX);
			ConfigurationManager::GetInstance()->GetFloat("Gui.DialogBox.PosY", PosY);
			ConfigurationManager::GetInstance()->GetFloat("Gui.DialogBox.SizeX", SizeX);
			ConfigurationManager::GetInstance()->GetFloat("Gui.DialogBox.SizeY", SizeY);
			frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, 0), CEGUI::UDim(PosY, 0)));
			frw->setWidth(CEGUI::UDim(SizeX, 0));
			frw->setHeight(CEGUI::UDim(SizeY, 0));
		}

		_myBox->hide();
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init DialogBox: ") + ex.getMessage().c_str());
	}
}




/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool NPCDialogBox::HandleClose (const CEGUI::EventArgs& e)
{
	CloseDialog();
	return true;
}


/***********************************************************
catch key event
***********************************************************/
bool NPCDialogBox::HandleEnterKey (const CEGUI::EventArgs& e)
{
	const CEGUI::KeyEventArgs& we =
    static_cast<const CEGUI::KeyEventArgs&>(e);

	if(we.scancode == CEGUI::Key::Space || we.scancode == CEGUI::Key::W)
	{
		CloseDialog();
		return true;
	}

	return false;
}



/***********************************************************
catch mouse enter event
***********************************************************/
bool NPCDialogBox::HandleMouseEnter (const CEGUI::EventArgs& e)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/listbox"));

	const CEGUI::MouseEventArgs& wine =
    static_cast<const CEGUI::MouseEventArgs&>(e);

	CEGUI::ListboxItem * itm = lb->getItemAtPoint(wine.position);
	if(itm)
		lb->setItemSelectState(itm, true);

	return true;
}





/***********************************************************
handle listbox selected
***********************************************************/
bool NPCDialogBox::Handlelbelected(const CEGUI::EventArgs& e)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/listbox"));

	const MyDialogItem * it = static_cast<const MyDialogItem *>(lb->getFirstSelectedItem());
	if(it)
	{
		LbaNet::GuiUpdatesSeq updseq;
		LbaNet::DialogSelectedUpdate * upd = 
			new LbaNet::DialogSelectedUpdate(_current_dialoged_actor, it->_SelectionIdx);
		updseq.push_back(upd);
		
		EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
			SynchronizedTimeHandler::GetCurrentTimeDouble(), "DialogBox", updseq));

		return true;
	}

	return true;
}






/***********************************************************
close dialog and inform actor
***********************************************************/
void NPCDialogBox::CloseDialog()
{
	_myBox->hide();
	_current_dialoged_actor  = -1;

	LbaNet::GuiUpdatesSeq updseq;
	LbaNet::GuiClosedUpdate * upd = 
		new LbaNet::GuiClosedUpdate();
	updseq.push_back(upd);
	
	EventsQueue::getSenderQueue()->AddEvent(new LbaNet::UpdateGameGUIEvent(
		SynchronizedTimeHandler::GetCurrentTimeDouble(), "DialogBox", updseq));
}




/***********************************************************
build dialog depending of the actor
***********************************************************/
void NPCDialogBox::BuildDialog(const LbaNet::DialogPartInfo &DialogPart)
{
	CEGUI::Listbox * lb = static_cast<CEGUI::Listbox *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/listbox"));
	
	if(lb)
	{
		lb->resetList();

		// display NPC dialog text
		{
			CEGUI::Window* txs = CEGUI::WindowManager::getSingleton().getWindow("DialogFrame/multiline");
			std::string str = DataLoader::getInstance()->GetText((long)DialogPart.NpcTextId);
			int idxs = 0;
			bool firsttime=true;
			while((idxs = str.find(" @ ")) != std::string::npos)
			{
				std::string tmp = str.substr(0, idxs);
				if(tmp == "")
					tmp = "\n";

				if(firsttime)
				{
					firsttime = false;
					txs->setText((const unsigned char *)tmp.c_str());
				}
				else
					txs->appendText((const unsigned char *)tmp.c_str());

				while(((idxs+4) < (int)str.size()) && (str[idxs+3] == '@') && (str[idxs+4] == ' '))
				{
					txs->appendText("\n");
					idxs+= 2;
				}

				str = str.substr(idxs+3);
			}

			// set left over text
			if(firsttime)
			{
				firsttime = false;
				txs->setText((const unsigned char *)str.c_str());
			}
			else
				txs->appendText((const unsigned char *)str.c_str());
		}


		for(size_t i=0; i<DialogPart.PlayerTextsId.size(); ++i)
		{
			std::string str = DataLoader::getInstance()->GetText((long)DialogPart.PlayerTextsId[i]);	
			CEGUI::ListboxItem *it = new MyDialogItem((const unsigned char *)str.c_str(), i);
			lb->addItem(it);		
		}
	}
}




/***********************************************************
refresh gui with info from server
***********************************************************/
void NPCDialogBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{
	for(size_t i=0; i<Parameters.size(); ++i)
	{
		LbaNet::GuiParameterBase * ptr = Parameters[i].get();
		const std::type_info& info = typeid(*ptr);

		// shortcut updated
		if(info == typeid(LbaNet::DialogGuiParameter))
		{
			LbaNet::DialogGuiParameter * castedptr = 
				dynamic_cast<LbaNet::DialogGuiParameter *>(ptr);

			// set NPC id
			_current_dialoged_actor = castedptr->NPCId;

			// set dialog title
			std::string title = "Dialog with "+ DataLoader::getInstance()->GetNameText((long)castedptr->TittleTextId);
			static_cast<CEGUI::FrameWindow *> (
				CEGUI::WindowManager::getSingleton().getWindow("DialogFrame"))
				->setText((const unsigned char *)title.c_str());

			// build rest of dialog
			BuildDialog(castedptr->DialogPart);
		}
	}
}


/***********************************************************
update gui with info from server
***********************************************************/
void NPCDialogBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{
	for(size_t i=0; i<Updates.size(); ++i)
	{
		LbaNet::GuiUpdateBase * ptr = Updates[i].get();
		const std::type_info& info = typeid(*ptr);

		// DialogUpdate
		if(info == typeid(LbaNet::DialogUpdate))
		{
			LbaNet::DialogUpdate * castedptr = 
				dynamic_cast<LbaNet::DialogUpdate *>(ptr);

			// set NPC id
			_current_dialoged_actor = castedptr->NPCId;

			//set dialog
			BuildDialog(castedptr->DialogPartUpdate);
		}
	}
}

/***********************************************************
show GUI
***********************************************************/
void NPCDialogBox::Display()
{
	_myBox->show();
	_myBox->activate();
}

/***********************************************************
hide GUI
***********************************************************/
void NPCDialogBox::Hide()
{
	_myBox->hide();
}

/***********************************************************
show/hide GUI
***********************************************************/
void NPCDialogBox::ToggleDisplay()
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
void NPCDialogBox::Focus(bool focus)
{

}


/***********************************************************
save size of windows to be restored after resize of the application
***********************************************************/
void NPCDialogBox::SaveGUISizes(int oldscreenX, int oldscreenY)
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogFrame"));

	CEGUI::UVector2 vec = frw->getPosition();
	_savedPosX = vec.d_x.asRelative((float)oldscreenX);
	_savedPosY = vec.d_y.asRelative((float)oldscreenY);
	_savedSizeX = frw->getWidth().asRelative((float)oldscreenX);
	_savedSizeY = frw->getHeight().asRelative((float)oldscreenY);
}


/***********************************************************
restore the correct size of the windows
***********************************************************/
void NPCDialogBox::RestoreGUISizes()
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("DialogFrame"));

	frw->setPosition(CEGUI::UVector2(CEGUI::UDim(_savedPosX, 0), CEGUI::UDim(_savedPosY, 0)));
	frw->setWidth(CEGUI::UDim(_savedSizeX, 0));
	frw->setHeight(CEGUI::UDim(_savedSizeY, 0));
}