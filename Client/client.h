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
#include <boost/shared_ptr.hpp>
#include "CommonTypes.h"
#include "CatmulSplineHandler.h"
#include "Holomap.h"
#include <set>

class VLCPlayer;
class Holomap;
typedef boost::shared_ptr<Holomap>	HolomapPtr;
class HolomapLocation;
typedef boost::shared_ptr<HolomapLocation>	HolomapLocationPtr;
class HolomapTravelPath;
typedef boost::shared_ptr<HolomapTravelPath>	HolomapTravelPathPtr;
class StaticObject;
class DynamicObject;
struct DrawRectangle;

namespace LbaNet
{
	struct ModelInfo;
}


enum ClientViewType { CLV_Game = 0, CLV_Video, CLV_ExtraGL, CLV_Holomap };

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

	//! display holomap
	//! mode:
	//! 0 -> edit holomap model
	//! 1 -> display holomap with player location and quests locations
	//! 2 -> display holomap with path and moving vehicle
	//! 3 -> edit mode of 1 holomap location
	//! 4 -> edit mode of 1 holomap path
	void DisplayHolomap(int Mode, long HolomapLocationOrPathId,
						const std::vector<long> &questholoids, const LbaVec3 &playerpos);

	//! Draw text
	void DrawRectangleText(long textid, bool drawborder, DrawRectangle rect,
							float bgcolorR=0, float bgcolorG=0, float bgcolorB=0, float bgcolorA=1);

public slots:
	//! called when a video is finished playing
	void videofinished();


protected:
	//! override close event
	virtual void closeEvent(QCloseEvent* event);

	//! override keyPressEvent
	virtual void keyPressEvent (QKeyEvent * event);

	//! draw the current holomap
	void DrawHolomap();

	//! find nearest location on the current holomap
	HolomapLocationPtr FindLocationOnHolo(long HolomapId, long LocationId);

	//! find nearest location on the current holomap
	HolomapLocationPtr FindLocationOnHolo(long HolomapId, HolomapLocationPtr Location);


	//! draw location
	void DrawLocation(HolomapPtr holomap, HoloCoordinate location, int arrowtype);

	//! HideHolomap
	void HideHolomap();

	//! draw location
	boost::shared_ptr<DynamicObject> DrawLocationModel(HolomapPtr holomap, 
												LbaNet::ModelInfo modelinfo, 
												float posX, float posY, float posZ, 
												float rotX, float rotY, float rotZ);

	//! draw location
	boost::shared_ptr<DynamicObject> DrawLocationModel(HolomapPtr holomap, int modeltype, 
												float posX, float posY, float posZ, 
												float rotX, float rotY, float rotZ);

	//! TransformHoloCoordinate
	void TransformHoloCoordinate(const HoloCoordinate &holoc, 
										 float &posX, float &posY, float &posZ, 
										 float &rotX, float &rotY, float &rotZ);

	//! update holomap stuff on frame basis
	void UpdateHolomap(double tnow, float tdiff);

	//! CameraFollowHoloLocation
	void CameraFollowHoloLocation(double tnow, float tdiff, const HoloCoordinate  &coords,
									bool force = false);

	//! update selected location
	void UpdateSelectedLocation(bool up);

	//! ChangeHolomapUpDown
	void ChangeHolomapUpDown(bool up);

	//! generate a location using player 3D position
	HolomapLocationPtr Generated3DLoc(HolomapPtr holomap, long parentlocid);

	//! draw holo location text
	void DrawHoloText(HolomapLocationPtr hololoc);

	//! draw the path points
	float DrawPath(int NbWayPoints);

private:
	Ui::ClientClass			ui;
	GraphicsWindowQt *		_osgwindow;
	ClientViewType			_currentview;
	VLCPlayer*				_videoplayer;

	bool					_fullscreen;


	int						_currHolomapMode;
	long					_currHolomapLocationOrPathId;
	std::vector<long>		_currHolomapquestholoids; 
	LbaVec3 				_currHolomapplayerpos;

	HolomapPtr						_currHolomapPtr;
	HolomapLocationPtr				_currHoloLocationPtr;
	HolomapTravelPathPtr			_currHoloPathPtr;
	std::set<HolomapLocationPtr>	_drawnlocs;

	HolomapLocationPtr				_currPlayer3DLocPtr;

	CatmullSplineHandler			_catmullH;
	int								_currWaypoint;
	float							_currDistance;
	float							_accumulatedPointDistance;
	boost::shared_ptr<DynamicObject>	_drawnVehicle;
	HoloCoordinate						_posLastDot;

	std::vector<boost::shared_ptr<StaticObject> >	_holodispobjects;
	bool							_camerafollowloc;
};

#endif // CLIENT_H
