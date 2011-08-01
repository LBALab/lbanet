#include "client.h"
#include "GraphicsWindowQt"
#include "EventsQueue.h"
#include "ClientExtendedEvents.h"

/***********************************************************
constructor
***********************************************************/
Client::Client(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags), _osgwindow(NULL)
{
	ui.setupUi(this);
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
	ui.verticalLayout->addWidget(_osgwindow->getGraphWidget());
	_osgwindow->getGraphWidget()->show();
}


/***********************************************************
override close event
***********************************************************/
void Client::closeEvent(QCloseEvent* event)
{
	EventsQueue::getReceiverQueue()->AddEvent(new QuitGameEvent());
}
