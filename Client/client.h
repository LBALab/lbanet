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


	//! play video
	void PlayVideo(const std::string & filename);

	//! hide video
	void HideVideo();

public slots:
	//! called when a video is finished playing
	void videofinished();


protected:
	//! override close event
	virtual void closeEvent(QCloseEvent* event);

	//! override keyPressEvent
	virtual void keyPressEvent (QKeyEvent * event);

private:
	Ui::ClientClass ui;

	GraphicsWindowQt *		_osgwindow;
	bool					_Playingvid;
};

#endif // CLIENT_H
