#ifndef CLIENT_H
#define CLIENT_H

#include <QtGui/QWidget>
#include "ui_client.h"
#include "QT_WindowsBase.h"
#include "ExtraGLWindowQt"

enum ClientViewType { CLV_Game = 0, CLV_Video, CLV_FixedImage, CLV_ExtraGL };

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

	//! reset to game screen
	void ResetToGame();

	//! check the current view
	ClientViewType GetCurrentView();

	//! switch to fixed image
	void SwitchToFixedImage(const std::string & imagepath);

	//! process
	void Process(double tnow, float tdiff);

	//! switch to text
	void SwitchToText(long TextId);


public slots:
	//! called when a video is finished playing
	void videofinished();


protected:
	//! override close event
	virtual void closeEvent(QCloseEvent* event);

	//! override keyPressEvent
	virtual void keyPressEvent (QKeyEvent * event);


private:
	Ui::ClientClass			ui;
	GraphicsWindowQt *		_osgwindow;
	ClientViewType			_currentview;
	ExtraGLWidget			_glwidget;
};

#endif // CLIENT_H
