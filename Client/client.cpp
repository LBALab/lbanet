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
}

/***********************************************************
destructor
***********************************************************/
Client::~Client()
{

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
			case CLV_FixedImage:
			{
				EventsQueue::getReceiverQueue()->AddEvent(new FixedImageFinishedEvent());
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
void Client::SwitchToFixedImage(const std::string & imagepath)
{
	QPixmap image(imagepath.c_str());
	ui.label_fixedimage->setPixmap(image);

	ui.stackedWidget->setCurrentIndex(2);
	_currentview = CLV_FixedImage;
}


