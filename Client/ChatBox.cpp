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

#include "ChatBox.h"
#include <iostream>
#include <algorithm>
#include <CEGUI.h>

#include "EventsQueue.h"
#include "GameGUI.h"
#include "ConfigurationManager.h"
#include "LogHandler.h"
#include "SynchronizedTimeHandler.h"
#include "ClientExtendedEvents.h"
#include "ClientExtendedTypes.h"
#include "OSGHandler.h"
#include "GUILocalizationCallback.h"
#include "Localizer.h"

// Sample sub-class for ListboxTextItem that auto-sets the selection brush
// image.  This saves doing it manually every time in the code.
class MyListItem : public CEGUI::ListboxTextItem
{
public:
    MyListItem (const CEGUI::String& text, const CEGUI::String& text2) 
		: CEGUI::ListboxTextItem(text), _text2(text2)
    {
        setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
    }

	CEGUI::String	_text2;
};


class LeftWrappedListItem : public CEGUI::ListboxTextItem
{
private:
	CEGUI::FormattedRenderedString * d_formattedRenderedString;

public:
	//! constructor
    LeftWrappedListItem (const CEGUI::String& text) 
		: CEGUI::ListboxTextItem(text)
    {
        d_formattedRenderedString =
            new CEGUI::RenderedStringWordWrapper
                <CEGUI::LeftAlignedRenderedString>(d_renderedString);
    }

	//! destructor
    ~LeftWrappedListItem ()
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
};


/***********************************************************
constructor
***********************************************************/
ChatBox::ChatBox()
: _control_key_on(false), _shift_key_on(false),
	_currSelectedch(0), 
	_itltext(_lasttexts.end()), mHistorySize(50)
{
	_channels.push_back("World");
	_channels.push_back("Map");

	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":)", "[colour='FFFFFFFF'][image='set:sm_smilie image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":-)", "[colour='FFFFFFFF'][image='set:sm_smilie image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(";)", "[colour='FFFFFFFF'][image='set:sm_wink image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(";-)", "[colour='FFFFFFFF'][image='set:sm_wink image:full_image']"));	
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":/", "[colour='FFFFFFFF'][image='set:sm_hmz image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":-/", "[colour='FFFFFFFF'][image='set:sm_hmz image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":p", "[colour='FFFFFFFF'][image='set:sm_tongue image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":-p", "[colour='FFFFFFFF'][image='set:sm_tongue image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":P", "[colour='FFFFFFFF'][image='set:sm_tongue image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":(", "[colour='FFFFFFFF'][image='set:sm_frown image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":-(", "[colour='FFFFFFFF'][image='set:sm_frown image:full_image']"));	
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":D", "[colour='FFFFFFFF'][image='set:sm_biggrin image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":-D", "[colour='FFFFFFFF'][image='set:sm_biggrin image:full_image']"));	
	_replace_string_map.push_back(std::make_pair<std::string, std::string>("|D", "[colour='FFFFFFFF'][image='set:sm_proud image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":o", "[colour='FFFFFFFF'][image='set:sm_embarrassment image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":x", "[colour='FFFFFFFF'][image='set:sm_kiss image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":mad:", "[colour='FFFFFFFF'][image='set:sm_mad image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":eek:", "[colour='FFFFFFFF'][image='set:sm_eek image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":cool:", "[colour='FFFFFFFF'][image='set:sm_cool image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":rolleyes:", "[colour='FFFFFFFF'][image='set:sm_rolleyes image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":lol:", "[colour='FFFFFFFF'][image='set:sm_lol image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":'(", "[colour='FFFFFFFF'][image='set:sm_sad image:full_image']"));	
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":sad:", "[colour='FFFFFFFF'][image='set:sm_sad image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":evilwink:", "[colour='FFFFFFFF'][image='set:sm_evilwink image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":stupid:", "[colour='FFFFFFFF'][image='set:sm_stupid image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":bloated:", "[colour='FFFFFFFF'][image='set:sm_bloated image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":hmpf:", "[colour='FFFFFFFF'][image='set:sm_hmpf image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":zombie:", "[colour='FFFFFFFF'][image='set:sm_zombie image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":tup:", "[colour='FFFFFFFF'][image='set:sm_tup image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":tdown:", "[colour='FFFFFFFF'][image='set:sm_tdown image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":zoe:", "[colour='FFFFFFFF'][image='set:sm_zoe image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":dino:", "[colour='FFFFFFFF'][image='set:sm_dinofly image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":funfrock:", "[colour='FFFFFFFF'][image='set:sm_funfrock image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>(":bunny:", "[colour='FFFFFFFF'][image='set:sm_rabibunny image:full_image']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>("[red]", "[colour='FFFF0000']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>("[green]", "[colour='FF00FF00']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>("[blue]", "[colour='FF0000FF']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>("[violet]", "[colour='FFFF00FF']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>("[cyan]", "[colour='FF00FFFF']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>("[yellow]", "[colour='FFFFFF00']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>("[black]", "[colour='FF000000']"));
	_replace_string_map.push_back(std::make_pair<std::string, std::string>("[white]", "[colour='FFFFFFFF']"));
}


/***********************************************************
destructor
***********************************************************/
ChatBox::~ChatBox()
{
	try
	{
		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("ChatFrame"));

		int resX, resY; 
		bool fullscreen;
		OsgHandler::getInstance()->GetScreenAttributes(resX, resY, fullscreen);

		CEGUI::UVector2 vec = frw->getPosition();
		ConfigurationManager::GetInstance()->SetFloat("Gui.Chatbox.PosX", vec.d_x.asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Chatbox.PosY", vec.d_y.asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Chatbox.SizeX", frw->getWidth().asRelative((float)resX));
		ConfigurationManager::GetInstance()->SetFloat("Gui.Chatbox.SizeY", frw->getHeight().asRelative((float)resY));
		ConfigurationManager::GetInstance()->SetBool("Gui.Chatbox.Visible", frw->isVisible());
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception destructor chatbox: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
initalize the box
***********************************************************/
void ChatBox::Initialize(CEGUI::Window* Root)
{
	try
	{
		_myChat = CEGUI::WindowManager::getSingleton().loadWindowLayout( "chatbox.layout",
								"", "", &MyPropertyCallback);
		Root->addChildWindow(_myChat);
		//tc->setProperty( "InheritsAlpha", "false" );

		AddTab(Localizer::getInstance()->GetText(Localizer::GUI, 68));
		AddTab(Localizer::getInstance()->GetText(Localizer::GUI, 69));
		AddTab(Localizer::getInstance()->GetText(Localizer::GUI, 70));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("Chat/bChannel"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&ChatBox::HandleBChannel, this));

		static_cast<CEGUI::PushButton *> (
			CEGUI::WindowManager::getSingleton().getWindow("Chat/bSend"))->subscribeEvent (
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber (&ChatBox::HandleSend, this));

		static_cast<CEGUI::Editbox *> (
			CEGUI::WindowManager::getSingleton().getWindow("Chat/edit"))->subscribeEvent (
			CEGUI::Editbox::EventKeyDown,
			CEGUI::Event::Subscriber (&ChatBox::HandleEnterKey, this));

		static_cast<CEGUI::Editbox *> (
			CEGUI::WindowManager::getSingleton().getWindow("Chat/edit"))->subscribeEvent (
			CEGUI::Editbox::EventKeyUp,
			CEGUI::Event::Subscriber (&ChatBox::HandleReleaseKey, this));

		_lb = static_cast<CEGUI::Listbox *>
			(CEGUI::WindowManager::getSingleton().createWindow( "TaharezLook/Listbox", "Chat/listchannel" ));

		_lb->subscribeEvent(CEGUI::Listbox::EventSelectionChanged,
							CEGUI::Event::Subscriber (&ChatBox::HandleLbSelected, this));


		_lb->setProperty("Text", Localizer::getInstance()->GetText(Localizer::GUI, 71));
		_lb->setProperty("UnifiedMaxSize", "{{1,0},{1,0}}");
		_lb->setProperty("UnifiedAreaRect", "{{0,10},{1,-160},{0,120},{1,-40}}");
		_lb->setProperty("AlwaysOnTop", "True");

		_myChat->addChildWindow(_lb);
		_lb->hide();

		_myChannels = CEGUI::WindowManager::getSingleton().loadWindowLayout( "choosechannel.layout",
								"", "", &MyPropertyCallback);

		_myChannels->setProperty("AlwaysOnTop", "True");
		Root->addChildWindow(_myChannels);
		_myChannels->hide();

		_myChooseName = CEGUI::WindowManager::getSingleton().loadWindowLayout( "choosePlayerName.layout",
								"", "", &MyPropertyCallback);

		_myChooseName->setProperty("AlwaysOnTop", "True");
		Root->addChildWindow(_myChooseName);
		_myChooseName->hide();


		{
			CEGUI::FrameWindow * fw = static_cast<CEGUI::FrameWindow *>(_myChannels);
			fw->subscribeEvent (	CEGUI::FrameWindow::EventCloseClicked,
									CEGUI::Event::Subscriber (&ChatBox::HandleCCCancel, this) );

			static_cast<CEGUI::PushButton *> (
				CEGUI::WindowManager::getSingleton().getWindow("Chat/chooseChannel/bOk"))->subscribeEvent (
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber (&ChatBox::HandleCCOk, this));

			static_cast<CEGUI::PushButton *> (
				CEGUI::WindowManager::getSingleton().getWindow("Chat/chooseChannel/bCancel"))->subscribeEvent (
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber (&ChatBox::HandleCCCancel, this));
		}


		{
			CEGUI::FrameWindow * fw = static_cast<CEGUI::FrameWindow *>(_myChooseName);
			fw->subscribeEvent (	CEGUI::FrameWindow::EventCloseClicked,
									CEGUI::Event::Subscriber (&ChatBox::HandleCPCancel, this) );

			static_cast<CEGUI::PushButton *> (
				CEGUI::WindowManager::getSingleton().getWindow("Chat/choosePlayerName/bOk"))->subscribeEvent (
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber (&ChatBox::HandleCPOk, this));

			static_cast<CEGUI::PushButton *> (
				CEGUI::WindowManager::getSingleton().getWindow("Chat/choosePlayerName/bCancel"))->subscribeEvent (
				CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber (&ChatBox::HandleCPCancel, this));
		}


		CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
			CEGUI::WindowManager::getSingleton().getWindow("ChatFrame"));
		frw->subscribeEvent (CEGUI::FrameWindow::EventCloseClicked,
			CEGUI::Event::Subscriber (&ChatBox::HandleCloseChatbox, this));

		float PosX, PosY, SizeX, SizeY;
		bool Visible;
		ConfigurationManager::GetInstance()->GetFloat("Gui.Chatbox.PosX", PosX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Chatbox.PosY", PosY);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Chatbox.SizeX", SizeX);
		ConfigurationManager::GetInstance()->GetFloat("Gui.Chatbox.SizeY", SizeY);
		ConfigurationManager::GetInstance()->GetBool("Gui.Chatbox.Visible", Visible);
		frw->setPosition(CEGUI::UVector2(CEGUI::UDim(PosX, 0), CEGUI::UDim(PosY, 0)));
		frw->setWidth(CEGUI::UDim(SizeX, 0));
		frw->setHeight(CEGUI::UDim(SizeY, 0));

		if(Visible)
			frw->show();
		else
			frw->hide();
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception init chatbox: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
add new text to the chatbox
***********************************************************/
void ChatBox::AddText(std::string channel, std::string Sender, std::string Text)
{
	for(size_t i=0; i< _replace_string_map.size(); ++i)
		ReplaceStringPart(Text, _replace_string_map[i].first, _replace_string_map[i].second);

	if(Sender == "info")
	{
		if(Text.size() > 1 && Text[0] == '#')
		{
			int textidx = atoi(Text.substr(1).c_str());
			Text = Localizer::getInstance()->GetText(Localizer::GUI, textidx);
		}
	}

	ProtectString(Text);

	std::string namecol = "[colour='";
	std::map<std::string, std::string>::iterator itcolor = _name_colors.find(Sender);
	if(itcolor != _name_colors.end())
		namecol += itcolor->second;
	else
		namecol += "FFFFFFFF";
	namecol += "']";

	if(channel == (_currentWorld + "_" + _currentMap))
		channel = "Map";

	if(channel == "Whisper")
	{
		if(CEGUI::WindowManager::getSingleton().isWindowPresent("Chat/Tab_All/editMulti"))
		{
			CEGUI::String tmp((const unsigned char *)Text.c_str());
			CEGUI::String tmp2((const unsigned char *)Sender.c_str());

			CEGUI::Listbox * txt2 = static_cast<CEGUI::Listbox *>(CEGUI::WindowManager::getSingleton().getWindow("Chat/Tab_All/editMulti"));
			AddChatText(namecol + tmp2 + " whispers: [colour='FFFFFFFF']"+ tmp, txt2);
		}
	}
	else if(channel == "All")
	{
		if(CEGUI::WindowManager::getSingleton().isWindowPresent("Chat/Tab_All/editMulti"))
		{
			CEGUI::String tmp((const unsigned char *)Text.c_str());
			CEGUI::String tmp2((const unsigned char *)Sender.c_str());

			CEGUI::Listbox * txt2 = static_cast<CEGUI::Listbox *>(CEGUI::WindowManager::getSingleton().getWindow("Chat/Tab_All/editMulti"));
			AddChatText(namecol + tmp2 + ": [colour='FFFFFFFF']"+ tmp, txt2);
		}
	}
	else if(CEGUI::WindowManager::getSingleton().isWindowPresent("Chat/Tab_"+channel+"/editMulti"))
	{
		CEGUI::String tmp((const unsigned char *)Text.c_str());
		CEGUI::String tmp2((const unsigned char *)Sender.c_str());

		CEGUI::Listbox * txt = static_cast<CEGUI::Listbox *>(CEGUI::WindowManager::getSingleton().getWindow("Chat/Tab_"+channel+"/editMulti"));
		AddChatText(namecol + tmp2 + ": [colour='FFFFFFFF']"+ tmp, txt);
		

		if(CEGUI::WindowManager::getSingleton().isWindowPresent("Chat/Tab_All/editMulti"))
		{
			CEGUI::Listbox * txt2 = static_cast<CEGUI::Listbox *>(CEGUI::WindowManager::getSingleton().getWindow("Chat/Tab_All/editMulti"));
			CEGUI::String tmp3((const unsigned char *)channel.c_str());
			AddChatText(namecol + tmp2 + "@" + tmp3+ ": [colour='FFFFFFFF']"+ tmp, txt2);
		}
	}

}

/***********************************************************
add a tab to the chat
***********************************************************/
void ChatBox::AddTab(const std::string & tabName)
{
    CEGUI::TabControl *tc = static_cast<CEGUI::TabControl *>(CEGUI::WindowManager::getSingleton().getWindow ("Chat/TabControl"));

	CEGUI::FrameWindow* fWnd = static_cast<CEGUI::FrameWindow *>(CEGUI::WindowManager::getSingleton().createWindow( "DefaultGUISheet", "Chat/Tab_"+tabName ));
	fWnd->setProperty("Text", (const unsigned char *)tabName.c_str());


	CEGUI::Listbox* txt = static_cast<CEGUI::Listbox *>(CEGUI::WindowManager::getSingleton().createWindow( "TaharezLook/Listbox", "Chat/Tab_"+tabName+"/editMulti" ));
	txt->setProperty("UnifiedMaxSize", "{{1,0},{1,0}}");
	txt->setProperty("UnifiedAreaRect", "{{0,0},{0,1},{1,0},{1,0}}");
	txt->setProperty("ForceVertScrollbar", "True");
	fWnd->addChildWindow(txt);

	tc->addTab (fWnd);
}

/***********************************************************
handle send button event
***********************************************************/
bool ChatBox::HandleSend (const CEGUI::EventArgs& e)
{
    CEGUI::PushButton * bch = static_cast<CEGUI::PushButton *>
		(CEGUI::WindowManager::getSingleton().getWindow("Chat/bChannel"));
	std::string curChannel = bch->getProperty("Text").c_str();

	CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
		(CEGUI::WindowManager::getSingleton().getWindow("Chat/edit"));


	std::string currText = bed->getProperty("Text").c_str();
	if(currText != "")
	{
		SendText(curChannel, currText);
		bed->setProperty("Text", "");
	}

    return true;
}


/***********************************************************
handle send button event
***********************************************************/
bool ChatBox::HandleBChannel(const CEGUI::EventArgs& e)
{
	if(!_lb->isVisible())
	{
		_lb->resetList();

		std::list<std::string>::const_iterator it = _channels.begin();
		std::list<std::string>::const_iterator end = _channels.end();
		for(; it != end; ++it)
		{
			std::string tmp = *it;
			if(tmp == "World")
				tmp = Localizer::getInstance()->GetText(Localizer::GUI, 69);
			if(tmp == "Map")
				tmp = Localizer::getInstance()->GetText(Localizer::GUI, 70);
			_lb->addItem(new MyListItem((const unsigned char *)tmp.c_str(), (const unsigned char *)it->c_str()));
		}


		std::list<std::string>::const_iterator itw = _whisper_channels.begin();
		std::list<std::string>::const_iterator endw = _whisper_channels.end();
		for(; itw != endw; ++itw)
		{
			std::string wchtmp = "w:" + *itw;
			_lb->addItem(new MyListItem((const unsigned char *)wchtmp.c_str(), (const unsigned char *)wchtmp.c_str()));
		}



		_lb->addItem(new MyListItem((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 72).c_str(), "Whisper.."));
		_lb->addItem(new MyListItem((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, 73).c_str(), "New.."));

		_lb->show();
	}
	else
	{
		_lb->hide();
	}
    return true;
}


/***********************************************************
send text outside
***********************************************************/
void ChatBox::SendText(const std::string & channel, const std::string & Text)
{
	_lasttexts.push_front(Text);
	if(_lasttexts.size() > 10)
		_lasttexts.pop_back();

	if(Text == "")
		return;

	{
		if(Text[0] == '/')
			EventsQueue::getReceiverQueue()->AddEvent(new SendChatTextEvent(Text));
		else
		{
			if(channel.size() > 2 && channel[0] == 'w' && channel[1] == ':') // in case of whisper
			{
				std::string tosend("/w ");
				tosend += channel.substr(2);
				tosend += " ";
				tosend += Text;
				EventsQueue::getReceiverQueue()->AddEvent(new SendChatTextEvent(tosend));
			}
			else
			{
				std::string tosend("/");
				if(channel == "Map")
					tosend += _currentWorld + "_" + _currentMap;
				else
					tosend +=channel;

				tosend += " ";
				tosend += Text;

				EventsQueue::getReceiverQueue()->AddEvent(new SendChatTextEvent(tosend));
			}
		}
	}
}


/***********************************************************
set the current map of the game
***********************************************************/
void ChatBox::SetCurrentMap(const std::string & WorldName, const std::string & MapName)
{
	try
	{
		_currentWorld = WorldName;
		_currentMap = MapName;

		CEGUI::Window * chatfw = CEGUI::WindowManager::getSingleton().getWindow("ChatFrame");
		if(chatfw)
			chatfw->setProperty("Text", (const unsigned char *)(Localizer::getInstance()->GetText(Localizer::GUI, 2) + " - " + _currentWorld + "/" + _currentMap).c_str());
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception setting map name on chat box: ") + ex.getMessage().c_str());
	}
}


/***********************************************************
handle send button event
***********************************************************/
bool ChatBox::HandleEnterKey (const CEGUI::EventArgs& e)
{
	const CEGUI::KeyEventArgs& we =
    static_cast<const CEGUI::KeyEventArgs&>(e);

	const CEGUI::WindowEventArgs& wine =
    static_cast<const CEGUI::WindowEventArgs&>(e);


	if(we.scancode == CEGUI::Key::LeftControl || we.scancode == CEGUI::Key::RightControl)
	{
		_control_key_on = true;
		return true;
	}

	if(we.scancode == CEGUI::Key::LeftShift || we.scancode == CEGUI::Key::RightShift)
	{
		_shift_key_on = true;
		return true;
	}

	if(we.scancode == CEGUI::Key::LeftAlt || we.scancode == CEGUI::Key::RightAlt)
	{
		return true;
	}

	if(wine.window->getName() == "Chat/edit")
	{
		if(we.scancode == CEGUI::Key::Return)
		{
			HandleSend (e);

			CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
			(CEGUI::WindowManager::getSingleton().getWindow("Chat/edit"));
			bed->deactivate();
			return true;
		}

		if(we.scancode == CEGUI::Key::ArrowUp)
		{
			if(_itltext == _lasttexts.end())
				_itltext = _lasttexts.begin();
			else
			{
				std::list<std::string>::iterator ittmp = _itltext;
				++ittmp;
				if(ittmp != _lasttexts.end())
					++_itltext;
			}

			try
			{
				CEGUI::Window *windowchat = CEGUI::WindowManager::getSingleton().getWindow("Chat/edit");
				std::string text = "";
				if(_itltext != _lasttexts.end())
					text = *_itltext;

				if(windowchat)
					windowchat->setText((const unsigned char *)text.c_str());
			}
			catch(...){}

			//++_currSelectedch;
			//if(_currSelectedch >= (int)_channels.size())
			//	--_currSelectedch;
			//else
			//{
			//	std::list<std::string>::const_iterator it = _channels.begin();
			//	std::list<std::string>::const_iterator end = _channels.end();
			//	for(int cc=0; cc<_currSelectedch && it != end; ++it, ++cc);

			//	CEGUI::PushButton * bch = static_cast<CEGUI::PushButton *>
			//		(CEGUI::WindowManager::getSingleton().getWindow("Chat/bChannel"));
			//	bch->setProperty("Text", *it);
			//}



			return true;
		}
		if(we.scancode == CEGUI::Key::ArrowDown)
		{
			if(_itltext != _lasttexts.end())
			{
				if(_itltext != _lasttexts.begin())
					--_itltext;
				else
					_itltext = _lasttexts.end();
			}

			CEGUI::Window *windowchat = CEGUI::WindowManager::getSingleton().getWindow("Chat/edit");
			std::string text = "";
			if(_itltext != _lasttexts.end())
				text = *_itltext;

			if(windowchat)
				windowchat->setText((const unsigned char *)text.c_str());


			//--_currSelectedch;
			//if(_currSelectedch < 0)
			//	++_currSelectedch;
			//else
			//{
			//	std::list<std::string>::const_iterator it = _channels.begin();
			//	std::list<std::string>::const_iterator end = _channels.end();
			//	for(int cc=0; cc<_currSelectedch && it != end; ++it, ++cc);

			//	CEGUI::PushButton * bch = static_cast<CEGUI::PushButton *>
			//		(CEGUI::WindowManager::getSingleton().getWindow("Chat/bChannel"));
			//	bch->setProperty("Text", *it);
			//}

			return true;
		}


		if(we.scancode == CEGUI::Key::ArrowUp || we.scancode == CEGUI::Key::ArrowDown)
			return true;



		// paste text
		if(we.scancode == CEGUI::Key::V && _control_key_on)
		{
			CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
				(CEGUI::WindowManager::getSingleton().getWindow("Chat/edit"));
			if(bed && bed->isActive())
			{
				if(_text_copyed != "")
				{
					size_t selB = bed->getSelectionStartIndex();
					size_t selE = bed->getSelectionLength();
					CEGUI::String str = bed->getText();
					if(selE > 0)
					{
						str = str.erase(selB, selE);
					}

					if(str.size() + _text_copyed.size() < bed->getMaxTextLength())
					{
						size_t idx = bed->getCaratIndex();
						str = str.insert(idx, (unsigned char *)_text_copyed.c_str());
						bed->setText(str);
						bed->setCaratIndex(idx + _text_copyed.size());
					}
				}

				return true;
			}
		}
	}



	// copy text
	if(we.scancode == CEGUI::Key::C && _control_key_on)
	{
		CEGUI::Window * actw = _myChat->getActiveChild();
		if(actw != NULL)
		{
			if(actw->getName() == "Chat/edit")
			{
				CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *> (actw);
				size_t selB = bed->getSelectionStartIndex();
				size_t selE = bed->getSelectionLength();
				if(selE > 0)
				{
					CEGUI::String str = bed->getText().substr(selB, selE);
					_text_copyed = str.c_str();
				}

				return true;
			}
			else
			{
				CEGUI::MultiLineEditbox* txt = static_cast<CEGUI::MultiLineEditbox *>(actw);
				size_t selB = txt->getSelectionStartIndex();
				size_t selE = txt->getSelectionLength();
				if(selE > 0)
				{
					CEGUI::String str = txt->getText().substr(selB, selE);
					_text_copyed = str.c_str();
				}

				return true;
			}
		}

	}

    return false;
}


/***********************************************************
handle event when list is selected
***********************************************************/
bool ChatBox::HandleLbSelected (const CEGUI::EventArgs& e)
{
	const MyListItem * it = static_cast<const MyListItem *>(_lb->getFirstSelectedItem());
	if(!it)
		return false;

	std::string txt = it->_text2.c_str();
	if(txt == "New..")
	{
		_myChannels->show();
		CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
			(CEGUI::WindowManager::getSingleton().getWindow("Chat/chooseChannel/edit"));
		bed->activate();
		_myChat->setEnabled(false);
	}
	else if(txt == "Whisper..")
	{
		_myChooseName->show();
		CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
			(CEGUI::WindowManager::getSingleton().getWindow("Chat/choosePlayerName/edit"));
		bed->activate();
		_myChat->setEnabled(false);
	}
	else
	{
		CEGUI::PushButton * bch = static_cast<CEGUI::PushButton *>
			(CEGUI::WindowManager::getSingleton().getWindow("Chat/bChannel"));
		bch->setProperty("Text", it->getText());


		_currSelectedch= (int)_lb->getItemIndex(it);
	}

	_lb->hide();

	return true;
}


/***********************************************************
add a channel to the chat
***********************************************************/
void ChatBox::AddChannel(const std::string & channel)
{
	std::list<std::string>::iterator it = std::find(_channels.begin(), _channels.end(), channel);
	if(it != _channels.end())
		return;

	_channels.push_back(channel);
	AddTab(channel);

	CEGUI::PushButton * bch = static_cast<CEGUI::PushButton *>
		(CEGUI::WindowManager::getSingleton().getWindow("Chat/bChannel"));
	bch->setProperty("Text", (const unsigned char *)channel.c_str());


	// inform engine to add a channel
	{
		std::string tosend("/join ");
		tosend +=channel;
		EventsQueue::getReceiverQueue()->AddEvent(new SendChatTextEvent(tosend));
	}
}


/***********************************************************
handle event when list is selected
***********************************************************/
bool ChatBox::HandleCCOk (const CEGUI::EventArgs& e)
{
	CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
	(CEGUI::WindowManager::getSingleton().getWindow("Chat/chooseChannel/edit"));

	std::string strc = bed->getProperty("Text").c_str();

	if(strc != "")
	{
		AddChannel(strc);
		bed->setProperty("Text", "");
		_myChannels->hide();
		_myChat->setEnabled(true);
	}
	else
	{
		bed->activate();
	}

	return true;
}

/***********************************************************
handle event when list is selected
***********************************************************/
bool ChatBox::HandleCCCancel (const CEGUI::EventArgs& e)
{
	CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
	(CEGUI::WindowManager::getSingleton().getWindow("Chat/chooseChannel/edit"));

	bed->setProperty("Text", "");
	_myChannels->hide();
	_myChat->setEnabled(true);
	return true;
}




/***********************************************************
handle event when list is selected
***********************************************************/
bool ChatBox::HandleCPOk (const CEGUI::EventArgs& e)
{
	CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
	(CEGUI::WindowManager::getSingleton().getWindow("Chat/choosePlayerName/edit"));

	std::string strc = bed->getProperty("Text").c_str();

	if(strc != "")
	{
		AddWhisperChanel(strc);
		bed->setProperty("Text", "");
		_myChooseName->hide();
		_myChat->setEnabled(true);
	}
	else
	{
		bed->activate();
	}

	return true;
}

/***********************************************************
handle event when list is selected
***********************************************************/
bool ChatBox::HandleCPCancel (const CEGUI::EventArgs& e)
{
	CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
	(CEGUI::WindowManager::getSingleton().getWindow("Chat/choosePlayerName/edit"));

	bed->setProperty("Text", "");
	_myChooseName->hide();
	_myChat->setEnabled(true);
	return true;
}


/***********************************************************
handle release key
***********************************************************/
bool ChatBox::HandleReleaseKey (const CEGUI::EventArgs& e)
{
	const CEGUI::KeyEventArgs& we =
    static_cast<const CEGUI::KeyEventArgs&>(e);

	if(we.scancode == CEGUI::Key::LeftControl || we.scancode == CEGUI::Key::RightControl)
		_control_key_on = false;

	if(we.scancode == CEGUI::Key::LeftShift || we.scancode == CEGUI::Key::RightShift)
		_shift_key_on = false;

	return false;
}





/***********************************************************
handle event when the channel window is closed
***********************************************************/
bool ChatBox::HandleCloseChatbox (const CEGUI::EventArgs& e)
{
	_myChat->hide();
	return true;
}







/***********************************************************
method to correctly add chat text
***********************************************************/
void ChatBox::AddChatText(const CEGUI::String& pText, CEGUI::Listbox * listbox)
{
	using namespace CEGUI;

	// If there's text then add it
	if(pText.size())
	{
		// Add the Editbox text to the history Listbox
		LeftWrappedListItem* chatItem;
		if(listbox->getItemCount() == mHistorySize)
		{
			/* We have reached the capacity of the Listbox so re-use the first Listbox item.
			   This code is a little crafty.  By default the ListboxTextItem is created with
			   the auto-delete flag set to true, which results in its automatic deletion when
			   removed from the Listbox.  So we change that flag to false, extract the item
			   from the Listbox, change its text, put the auto-delete flag back to true, and
			   finally put the item back into the Listbox. */
			chatItem = static_cast<LeftWrappedListItem*>(listbox->getListboxItemFromIndex(0));
			chatItem->setAutoDeleted(false);
			listbox->removeItem(chatItem);
			chatItem->setAutoDeleted(true);
			chatItem->setText(pText);
		}
		else
		{
			// Create a new listbox item
			chatItem = new LeftWrappedListItem(pText);
		}
		listbox->addItem(chatItem);
		listbox->ensureItemIsVisible(listbox->getItemCount());
	}
}




/***********************************************************
replace a part of a string by another one
***********************************************************/
void ChatBox::ReplaceStringPart(std::string &text, const std::string &toreplace, 
									const std::string &replacement)
{
	size_t pos=text.find(toreplace);
	while(pos != std::string::npos)
	{
		text.replace(pos, toreplace.size(), replacement); 
		pos=text.find(toreplace);
	}
}


/***********************************************************
protect part of the string containing character [
***********************************************************/
void ChatBox::ProtectString(std::string &text)
{
	size_t pos=text.find("[");
	while(pos != std::string::npos)
	{
		if((text.size() > pos+2) && ((text[pos+1] == 'c' && text[pos+2] == 'o') || (text[pos+1] == 'i' && text[pos+2] == 'm')))
			pos=text.find("[", pos+1);	
		else
		{
			text.insert(pos, "\\"	);
			pos=text.find("[", pos+2);	
		}
	}
}



/***********************************************************
add a whisper channel
***********************************************************/
void ChatBox::AddWhisperChanel(const std::string & name)
{
	std::string wchtmp = "w:" + name;

	if(std::find(_whisper_channels.begin(), _whisper_channels.end(), name) == _whisper_channels.end())
	{
		_whisper_channels.push_back(name);

		if(_whisper_channels.size() > 3)
			_whisper_channels.pop_front();
	}

	CEGUI::PushButton * bch = static_cast<CEGUI::PushButton *>
		(CEGUI::WindowManager::getSingleton().getWindow("Chat/bChannel"));

	bch->setProperty("Text", (const unsigned char *)wchtmp.c_str());
}



/***********************************************************
refresh gui with info from server
***********************************************************/
void ChatBox::Refresh(const LbaNet::GuiParamsSeq &Parameters)
{

}

/***********************************************************
update gui with info from server
***********************************************************/
void ChatBox::Update(const LbaNet::GuiUpdatesSeq &Updates)
{
	for(size_t i=0; i<Updates.size(); ++i)
	{
		LbaNet::GuiUpdateBase * ptr = Updates[i].get();
		const std::type_info& info = typeid(*ptr);

		// NameColorChangedUpdate
		if(info == typeid(LbaNet::NameColorChangedUpdate))
		{
			LbaNet::NameColorChangedUpdate * castedptr = 
				dynamic_cast<LbaNet::NameColorChangedUpdate *>(ptr);

			_name_colors[castedptr->Name] = castedptr->Color;

		}

		// ChatTextReceivedUpdate
		if(info == typeid(LbaNet::ChatTextUpdate))
		{
			LbaNet::ChatTextUpdate * castedptr = 
				dynamic_cast<LbaNet::ChatTextUpdate *>(ptr);

			AddText(castedptr->Channel, castedptr->Sender, castedptr->Text);
		}


		// AddWhisperChanelUpdate
		if(info == typeid(AddWhisperChanelUpdate))
		{
			AddWhisperChanelUpdate * castedptr = 
				dynamic_cast<AddWhisperChanelUpdate *>(ptr);

			AddWhisperChanel(castedptr->_Name);
		}


		// ChatWorldNameUpdate
		if(info == typeid(ChatWorldNameUpdate))
		{
			ChatWorldNameUpdate * castedptr = 
				dynamic_cast<ChatWorldNameUpdate *>(ptr);

			SetCurrentMap(castedptr->_name, "");
		}

		// ChatMapNameUpdate
		if(info == typeid(ChatMapNameUpdate))
		{
			ChatMapNameUpdate * castedptr = 
				dynamic_cast<ChatMapNameUpdate *>(ptr);

			SetCurrentMap(_currentWorld, castedptr->_name);
		}
		
	}
}

/***********************************************************
show GUI
***********************************************************/
void ChatBox::Display()
{
	_myChat->show();
	_myChat->activate();
}

/***********************************************************
hide GUI
***********************************************************/
void ChatBox::Hide()
{
	_myChat->hide();
}

/***********************************************************
show/hide GUI
***********************************************************/
void ChatBox::ToggleDisplay()
{
	if(_myChat->isVisible())
		_myChat->hide();
	else
	{
		_myChat->show();
		_myChat->activate();
	}
}

/***********************************************************
focus GUI
***********************************************************/
void ChatBox::Focus(bool focus)
{
	try
	{
		CEGUI::Editbox * bed = static_cast<CEGUI::Editbox *>
		(CEGUI::WindowManager::getSingleton().getWindow("Chat/edit"));

		if(focus)
			bed->activate();
		else
			bed->deactivate();
	}
	catch(CEGUI::Exception &ex)
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception Focus chatbox: ") + ex.getMessage().c_str());
	}
}



/***********************************************************
save size of windows to be restored after resize of the application
***********************************************************/
void ChatBox::SaveGUISizes(int oldscreenX, int oldscreenY)
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("ChatFrame"));

	CEGUI::UVector2 vec = frw->getPosition();
	_savedPosX = vec.d_x.asRelative((float)oldscreenX);
	_savedPosY = vec.d_y.asRelative((float)oldscreenY);
	_savedSizeX = frw->getWidth().asRelative((float)oldscreenX);
	_savedSizeY = frw->getHeight().asRelative((float)oldscreenY);
}


/***********************************************************
restore the correct size of the windows
***********************************************************/
void ChatBox::RestoreGUISizes()
{
	CEGUI::FrameWindow * frw = static_cast<CEGUI::FrameWindow *> (
		CEGUI::WindowManager::getSingleton().getWindow("ChatFrame"));

	frw->setPosition(CEGUI::UVector2(CEGUI::UDim(_savedPosX, 0), CEGUI::UDim(_savedPosY, 0)));
	frw->setWidth(CEGUI::UDim(_savedSizeX, 0));
	frw->setHeight(CEGUI::UDim(_savedSizeY, 0));
}
