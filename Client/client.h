#ifndef CLIENT_H
#define CLIENT_H

#include <QtGui/QWidget>
#include "ui_client.h"
#include "QT_WindowsBase.h"

class Client : public QWidget, public QT_Windows_base
{
	Q_OBJECT

public:
	Client(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Client();

	//! set osg windows
	virtual void SetOsgWindow(GraphicsWindowQt *wind);

protected:
	//! override close event
	virtual void closeEvent(QCloseEvent* event);
private:
	Ui::ClientClass ui;

	GraphicsWindowQt * _osgwindow;
};

#endif // CLIENT_H
