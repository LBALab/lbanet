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

/***********************************************************
constructor
***********************************************************/
Client::Client(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags), _osgwindow(NULL), _currentview(CLV_Game)
{
	ui.setupUi(this);

	connect(ui.videoPlayer, SIGNAL(finished()) , this, SLOT(videofinished()));	
	
	ui.page_ExtraGL->layout()->addWidget(&_glwidget);

	ui.stackedWidget->setCurrentIndex(1);
}

/***********************************************************
destructor
***********************************************************/
Client::~Client()
{

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
			_glwidget.Process(tnow, tdiff);
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
		ui.videoPlayer->stop();		

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

	Phonon::MediaSource ms(filename.c_str());
	ui.videoPlayer->play(ms);
}

/***********************************************************
hide video
***********************************************************/
void Client::ResetToGame()
{
	if(_currentview != CLV_Game)
	{
		ui.stackedWidget->setCurrentIndex(1);

		_glwidget.doneCurrent();
		_osgwindow->getGraphWidget()->makeCurrent();
		_currentview = CLV_Game;
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
				ui.videoPlayer->stop();	
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
				_glwidget.PressedSpace();
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
	ui.stackedWidget->setCurrentIndex(2);
	_currentview = CLV_ExtraGL;

	_osgwindow->getGraphWidget()->doneCurrent();
	_glwidget.makeCurrent();
	_glwidget.StartFixedImage(imagepath, NbSecondDisplay, FadeIn, FadeInColorR, FadeInColorG, FadeInColorB,
									FadeOut, FadeOutColorR, FadeOutColorG, FadeOutColorB);
}

/***********************************************************
switch to text
***********************************************************/
void Client::SwitchToText(const std::string & imagepath, const std::vector<long> textIds)
{
	ui.stackedWidget->setCurrentIndex(2);
	_currentview = CLV_ExtraGL;

	_osgwindow->getGraphWidget()->doneCurrent();
	_glwidget.makeCurrent();
	_glwidget.StartScrollingText(imagepath, textIds);
}