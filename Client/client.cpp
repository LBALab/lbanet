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


#include "client.h"
#include "GraphicsWindowQt"
#include "EventsQueue.h"
#include "ClientExtendedEvents.h"
#include "OSGHandler.h"
#include "CEGUIDrawable.h"
#include "Localizer.h"
#include "vlc_on_qt.h"

#include "MusicHandler.h"

/***********************************************************
constructor
***********************************************************/
Client::Client(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags), _osgwindow(NULL), _currentview(CLV_Game),
	_fullscreen(false)
{
	ui.setupUi(this);


	ui.stackedWidget->setCurrentIndex(1);

	_videoplayer = new VLCPlayer();
	ui.page_Video->layout()->addWidget(_videoplayer);
	_videoplayer->show();

	connect(_videoplayer, SIGNAL(finished()) , this, SLOT(videofinished()));	
}

/***********************************************************
destructor
***********************************************************/
Client::~Client()
{
	delete _videoplayer;
}


/***********************************************************
process
***********************************************************/
void Client::Process(double tnow, float tdiff)
{
	switch(_currentview)
	{
		case CLV_ExtraGL:
		{
			osg::ref_ptr<CEGUIDrawable> guidraw = OsgHandler::getInstance()->GetGUIDrawable();
			if(guidraw)
				guidraw->Process(tnow, tdiff);
			return;
		}
	}
}



/***********************************************************
set osg windows
***********************************************************/
void Client::SetOsgWindow(GraphicsWindowQt *wind)
{
	_osgwindow = wind;
	ui.page_Game->layout()->addWidget(_osgwindow->getGraphWidget());

	ResetToGame();
}


/***********************************************************
override close event
***********************************************************/
void Client::closeEvent(QCloseEvent* event)
{
	event->ignore();

	if(_currentview == CLV_Video)
		_videoplayer->stop();		

	ResetToGame();
	EventsQueue::getReceiverQueue()->AddEvent(new QuitGameEvent());
}



/***********************************************************
play video
***********************************************************/
void Client::PlayVideo(const std::string & filename)
{
	ui.stackedWidget->setCurrentIndex(0);
	_currentview = CLV_Video;

	_videoplayer->playFile(filename.c_str());
}

/***********************************************************
hide video
***********************************************************/
void Client::ResetToGame()
{
	if(_currentview != CLV_Game)
	{
		//stop voice
		MusicHandler::getInstance()->PlayVoice(std::vector<std::string>());

		osg::ref_ptr<CEGUIDrawable> guidraw = OsgHandler::getInstance()->GetGUIDrawable();
		if(guidraw)
			guidraw->EndDrawExtraGL();

		ui.stackedWidget->setCurrentIndex(1);
		_currentview = CLV_Game;

		_osgwindow->getGraphWidget()->SetHandleKey(true);
	}
}


/***********************************************************
hide video
***********************************************************/
void Client::videofinished()
{
	EventsQueue::getReceiverQueue()->AddEvent(new VideoFinishedEvent());
}


/***********************************************************
override keyPressEvent
***********************************************************/
void Client::keyPressEvent (QKeyEvent * event)
{
	if(event->key()== Qt::Key_Escape)
	{
		switch(_currentview)
		{
			case CLV_Video:
			{
				_videoplayer->stop();	
				videofinished();
				return;
			}
			case CLV_ExtraGL:
			{
				EventsQueue::getReceiverQueue()->AddEvent(new DisplayExtraGLFinishedEvent());
				return;
			}	
		}
	}

	if(event->key()== Qt::Key_Space)
	{
		switch(_currentview)
		{
			case CLV_ExtraGL:
			{
				osg::ref_ptr<CEGUIDrawable> guidraw = OsgHandler::getInstance()->GetGUIDrawable();
				if(guidraw)
					guidraw->PressedSpace();
				return;
			}
		}
	}

	QWidget::keyPressEvent(event);
}


/***********************************************************
check the current view
***********************************************************/
ClientViewType Client::GetCurrentView()
{
	return _currentview;
}





/***********************************************************
switch to fixed image
***********************************************************/
void Client::SwitchToFixedImage(const std::string & imagepath, long NbSecondDisplay, 
								bool FadeIn, float FadeInColorR, float FadeInColorG, float FadeInColorB,
								bool FadeOut, float FadeOutColorR, float FadeOutColorG, float FadeOutColorB)
{
	_currentview = CLV_ExtraGL;

	osg::ref_ptr<CEGUIDrawable> guidraw = OsgHandler::getInstance()->GetGUIDrawable();
	if(guidraw)
		guidraw->StartFixedImage(imagepath, NbSecondDisplay, FadeIn, FadeInColorR, FadeInColorG, FadeInColorB,
									FadeOut, FadeOutColorR, FadeOutColorG, FadeOutColorB);

	_osgwindow->getGraphWidget()->SetHandleKey(false);

}

/***********************************************************
switch to text
***********************************************************/
void Client::SwitchToText(const std::string & imagepath, const std::vector<long> textIds)
{
	std::vector<std::vector<unsigned int> > _texts;
	std::vector<std::string>	_voices;
	for(size_t i=0; i< textIds.size(); ++i)
	{
		

		std::string tmp = Localizer::getInstance()->GetText(Localizer::Map, textIds[i]);
		if(tmp != "")
			_texts.push_back(QString::fromUtf8(tmp.c_str()).toUcs4().toStdVector());

		std::vector<std::string> vcs = Localizer::getInstance()->GetVoices(Localizer::Map, textIds[i]);
		for(size_t vv=0; vv<vcs.size(); ++vv)
			_voices.push_back("Data/" + vcs[vv]);
	}

	if(_texts.size() > 0)
	{
		_currentview = CLV_ExtraGL;

		osg::ref_ptr<CEGUIDrawable> guidraw = OsgHandler::getInstance()->GetGUIDrawable();
		if(guidraw)
			guidraw->StartScrollingText(imagepath, _texts);

		_osgwindow->getGraphWidget()->SetHandleKey(false);

		if(_voices.size() > 0)
			MusicHandler::getInstance()->PlayVoice(_voices);
	}
}



/***********************************************************
init display
***********************************************************/
void Client::InitDisplay(bool fullscreen, bool maximized)
{
	if(fullscreen)
	{
		showFullScreen();
	}
	else
	{
		if(maximized)
		{
			showMaximized();
		}
		else
		{
			if(_fullscreen)
				showNormal();
			else
				show();
		}
	}

	_fullscreen = fullscreen;
}