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



#ifndef LBANET_QT_CLIENT_H
#define LBANET_QT_CLIENT_H

#include <QtGui/QWidget>
#include "ui_client.h"
#include "QT_WindowsBase.h"

class VLCPlayer;

enum ClientViewType { CLV_Game = 0, CLV_Video, CLV_ExtraGL };

class Client : public QWidget, public QT_Windows_base
{
	Q_OBJECT

public:
	//! constructor
	Client(QWidget *parent = 0, Qt::WFlags flags = 0);
	
	//! destructor
	~Client();

	//! process
	void Process(double tnow, float tdiff);

	//! set osg windows
	virtual void SetOsgWindow(GraphicsWindowQt *wind);


	//! play video
	void PlayVideo(const std::string & filename);

	//! reset to game screen
	void ResetToGame();

	//! check the current view
	ClientViewType GetCurrentView();

	//! switch to fixed image
	void SwitchToFixedImage(const std::string & imagepath, long NbSecondDisplay, 
								bool FadeIn, float FadeInColorR, float FadeInColorG, float FadeInColorB,
								bool FadeOut, float FadeOutColorR, float FadeOutColorG, float FadeOutColorB);

	//! switch to text
	void SwitchToText(const std::string & imagepath, const std::vector<long> textIds);


	//! init display
	void InitDisplay(bool fullscreen, bool maximized);


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
	VLCPlayer*				_videoplayer;

	bool					_fullscreen;
};

#endif // CLIENT_H
