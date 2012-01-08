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
#include "HolomapHandler.h"
#include "Holomap.h"
#include "MusicHandler.h"
#include "ObjectsDescription.h"
#include "StaticObject.h"

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


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

		case CLV_Holomap:
		{
			UpdateHolomap(tnow, tdiff);

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
		HideHolomap();

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
			case CLV_Holomap:
			{
				HideHolomap();
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

			case CLV_Holomap:
			{
				bool finish = true;
				osg::ref_ptr<CEGUIDrawable> guidraw = OsgHandler::getInstance()->GetGUIDrawable();
				if(guidraw)
					finish = guidraw->PressedSpace(false);

				if(finish)
					HideHolomap();
				return;
			}
		}
	}

	if(event->key()== Qt::Key_Right)
	{
		switch(_currentview)
		{
			case CLV_Holomap:
			{
				if(_currHolomapMode == 1)
					UpdateSelectedLocation(true);
				return;
			}
		}
	}

	if(event->key()== Qt::Key_Left)
	{
		switch(_currentview)
		{
			case CLV_Holomap:
			{
				if(_currHolomapMode == 1)
					UpdateSelectedLocation(false);
				return;
			}
		}
	}


	if(event->key()== Qt::Key_Up)
	{
		switch(_currentview)
		{
			case CLV_Holomap:
			{
				if(_currHolomapMode == 1)
					ChangeHolomapUpDown(true);
				return;
			}
		}
	}

	if(event->key()== Qt::Key_Down)
	{
		switch(_currentview)
		{
			case CLV_Holomap:
			{
				if(_currHolomapMode == 1)
					ChangeHolomapUpDown(false);
				return;
			}
		}
	}

	if(event->key()== Qt::Key_Return)
	{
		switch(_currentview)
		{
			case CLV_Holomap:
			{
				if(_currHolomapMode == 1)
					ChangeHolomapUpDown(false);
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
Draw text
***********************************************************/
void Client::DrawRectangleText(long textid, bool drawborder, DrawRectangle rect,
								float bgcolorR, float bgcolorG, float bgcolorB, float bgcolorA)
{
	std::vector<std::vector<unsigned int> > _texts;
	std::string tmp = Localizer::getInstance()->GetText(Localizer::Map, textid);
	if(tmp != "")
		_texts.push_back(QString::fromUtf8(tmp.c_str()).toUcs4().toStdVector());

	//if(_texts.size() > 0)
	{
		osg::ref_ptr<CEGUIDrawable> guidraw = OsgHandler::getInstance()->GetGUIDrawable();
		if(guidraw)
			guidraw->StartScrollingText("", _texts, drawborder, rect,
											bgcolorR, bgcolorG, bgcolorB, bgcolorA);
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


/***********************************************************
HideHolomap
***********************************************************/
void Client::HideHolomap()
{
	if(_currentview == CLV_Holomap)
	{
		osg::ref_ptr<CEGUIDrawable> guidraw = OsgHandler::getInstance()->GetGUIDrawable();
		if(guidraw)
			guidraw->StartStopHolomap(false);

		//clean old stuff
		{
			_currHolomapPtr = HolomapPtr();
			_currHoloLocationPtr = HolomapLocationPtr();
			_currHoloPathPtr = HolomapTravelPathPtr();
			_drawnlocs.clear();
			_currPlayer3DLocPtr = HolomapLocationPtr();
			_holodispobjects.clear();
		}

		// switch back to game scene
		OsgHandler::getInstance()->SwitchScene(0);
		OsgHandler::getInstance()->ResetCameraInfo();

		_currentview = CLV_Game;
		_osgwindow->getGraphWidget()->SetHandleKey(true);
	}
}

/***********************************************************
display holomap
***********************************************************/
void Client::DisplayHolomap(int Mode, long HolomapLocationOrPathId,
					const std::vector<long> &questholoids, const LbaVec3 &playerpos)
{
	osg::ref_ptr<CEGUIDrawable> guidraw = OsgHandler::getInstance()->GetGUIDrawable();
	if(guidraw)
	{
		_currentview = CLV_Holomap;
		guidraw->StartStopHolomap(false);
		guidraw->StartStopHolomap(true);

		// prepare display scene
		OsgHandler::getInstance()->StoreCameraInfo();
		OsgHandler::getInstance()->SwitchScene(1);
		_osgwindow->getGraphWidget()->SetHandleKey(false);



		_currHolomapMode = Mode;
		_currHolomapLocationOrPathId = HolomapLocationOrPathId;
		_currHolomapquestholoids = questholoids; 
		_currHolomapplayerpos = playerpos;

		//clean old stuff
		{
			_currHolomapPtr = HolomapPtr();
			_currHoloLocationPtr = HolomapLocationPtr();
			_currHoloPathPtr = HolomapTravelPathPtr();
			_drawnlocs.clear();
			_currPlayer3DLocPtr = HolomapLocationPtr();
			_holodispobjects.clear();
		}


		switch(_currHolomapMode)
		{
			// 0 -> map only
			case 0:
			{
				_currHolomapPtr = HolomapHandler::getInstance()->GetHolomap(HolomapLocationOrPathId);
				break;
			}

			//1 -> map + locations
			//3 -> map + 1loc editor
			case 1: case 3:
			{
				_currHoloLocationPtr = 
					HolomapHandler::getInstance()->GetHolomapLoc(HolomapLocationOrPathId);

				if(_currHoloLocationPtr)
				{	
					_currHolomapPtr = 
						HolomapHandler::getInstance()->GetHolomap(_currHoloLocationPtr->GetParentHoloId());
					
					DrawHoloText(_currHoloLocationPtr);
				}

				if(_currHolomapPtr)
					_currHoloLocationPtr = FindLocationOnHolo(_currHolomapPtr->GetId(), 
																HolomapLocationOrPathId);

				// generate player 3D location
				_currPlayer3DLocPtr = Generated3DLoc(_currHolomapPtr, -1);
				
				break;
			}
			
			//2 -> map + path
			//4 -> map + path editor 
			case 2: case 4:
			{
				_currHoloPathPtr = 
					HolomapHandler::getInstance()->GetHolomapPath(HolomapLocationOrPathId);

				if(_currHoloPathPtr)
				{	
					_currHolomapPtr = 
						HolomapHandler::getInstance()->GetHolomap(_currHoloPathPtr->GetParentHoloId());
				}

				break;
			}
		}

		//! draw the current holomap
		DrawHolomap();
	}

	_camerafollowloc = true;
}


/***********************************************************
draw holo location text
***********************************************************/
void Client::DrawHoloText(HolomapLocationPtr hololoc)
{
	if(!hololoc)
		return;

	DrawRectangle rect;
	rect.topX = 0.15;
	rect.topY = 0.65;
	rect.bottomX = 0.85;
	rect.bottomY = 0.95;
	DrawRectangleText(hololoc->GetTextId(), true, rect, 0.1f, 0.1f, 0.1f, 0.3f);
}


/***********************************************************
draw the current holomap
***********************************************************/
void Client::DrawHolomap()
{
	if(!_currHolomapPtr)
		return;

	// reset display
	_holodispobjects.clear();
	OsgHandler::getInstance()->ResetDisplayTree(1);
	LbaMainLightInfo lightinfo;//(0, 100, 50);
	OsgHandler::getInstance()->SetLight(1, lightinfo);


	// set camera
	if(_currHolomapPtr->Get3DMap())
		OsgHandler::getInstance()->ToggleCameraType(3);
	else
		OsgHandler::getInstance()->ToggleCameraType(1);


	// add map object
	{
		const LbaNet::ModelInfo & modinfo = _currHolomapPtr->GetMapModel();
		LbaNet::ObjectExtraInfo extrainfo;
		extrainfo.Display = false;
		LbaNet::LifeManaInfo lifeinfo;
		lifeinfo.Display = false;
		boost::shared_ptr<DisplayInfo> disinfo = ObjectInfo::ExtractDisplayInfo(1, modinfo, 
																	extrainfo, lifeinfo, false, 0);
		
		if(disinfo)
		{
			boost::shared_ptr<DisplayObjectHandlerBase> tmp =
				disinfo->BuildSelf(OsgHandler::getInstance());

			if(tmp)
			{
				boost::shared_ptr<PhysicalObjectHandlerBase> phystmp(
					new SimplePhysicalObjectHandler(0, 0, 0, LbaQuaternion()));

				boost::shared_ptr<StaticObject> sto(new StaticObject(phystmp, 
												tmp, boost::shared_ptr<SoundObjectHandlerBase>(), -1));
				_holodispobjects.push_back(sto);
			}
		}
	}


	// add player location
	if(_currHolomapMode == 1 || _currHolomapMode == 3)
	{
		_drawnlocs.clear();
		HolomapLocationPtr locplayer = FindLocationOnHolo(_currHolomapPtr->GetId(), _currHolomapLocationOrPathId);

		int modeltouse = 1;
		if(_currHolomapMode == 1)
		{
			modeltouse = 2;

			// add quest locations
			for(size_t i=0; i< _currHolomapquestholoids.size(); ++i)
			{
				HolomapLocationPtr loctmp = FindLocationOnHolo(_currHolomapPtr->GetId(), _currHolomapquestholoids[i]);
				if(loctmp)
				{
					if(loctmp == locplayer)
						modeltouse = 3; // same as player - change arrow type for player
					else
						_drawnlocs.insert(loctmp);
				}
			}

			// draw quest locations
			std::set<HolomapLocationPtr>::iterator itql = _drawnlocs.begin();
			std::set<HolomapLocationPtr>::iterator endql = _drawnlocs.end();
			for(; itql != endql; ++itql)
				DrawLocation(_currHolomapPtr, *itql, 1);
		}

		// draw player location
		if(locplayer)
		{
			DrawLocation(_currHolomapPtr, locplayer, modeltouse);
			_drawnlocs.insert(locplayer);
		}
		else
		{
			// else draw player position location
			if(_currPlayer3DLocPtr)
			{
				DrawLocation(_currHolomapPtr, _currPlayer3DLocPtr, 2);
				_drawnlocs.insert(_currPlayer3DLocPtr);
			}
		}
	}


	// add path
	if(_currHolomapMode == 2 || _currHolomapMode == 4)
	{
		//TODO
	}

	if(_currHolomapMode == 0)
	{
		//also draw example of location models
		boost::shared_ptr<DynamicObject> do1 = DrawLocationModel(_currHolomapPtr, 1, 10 , 15, 10, 0, 0, 0);
		boost::shared_ptr<DynamicObject> do2 = DrawLocationModel(_currHolomapPtr, 2, 10 , 5, 10, 0, 0, 0);
		boost::shared_ptr<DynamicObject> do3 = DrawLocationModel(_currHolomapPtr, 3, 10 , -5, 10, 0, 0, 0);
		boost::shared_ptr<DynamicObject> do4 = DrawLocationModel(_currHolomapPtr, 4, 10 , -15, 10, 0, 0, 0);
	}
}



/***********************************************************
find nearest location on the current holomap
***********************************************************/
HolomapLocationPtr  Client::FindLocationOnHolo(long HolomapId, long LocationId)
{
	HolomapLocationPtr ptr = HolomapHandler::getInstance()->GetHolomapLoc(LocationId);
	return FindLocationOnHolo(HolomapId, ptr);
}



/***********************************************************
find nearest location on the current holomap
***********************************************************/
HolomapLocationPtr  Client::FindLocationOnHolo(long HolomapId, HolomapLocationPtr Location)
{
	HolomapLocationPtr ptr = Location;
	while(ptr != NULL)
	{
		if(ptr->GetParentHoloId() == HolomapId)
			break;
		else
			ptr = HolomapHandler::getInstance()->GetHolomapLoc(ptr->GetParentLocId());
	}

	return ptr;
}


/***********************************************************
draw location
***********************************************************/
void Client::DrawLocation(HolomapPtr holomap, HolomapLocationPtr location, int arrowtype)
{
	if(!holomap ||!location)
		return;

	HoloCoordinate holoc = location->GetCoordinate();
	float posX=0, posY=0, posZ=0, rotX=0, rotY=0, rotZ=0;
	TransformHoloCoordinate(holoc, posX, posY, posZ, rotX, rotY, rotZ);
	DrawLocationModel(holomap, arrowtype, posX, posY, posZ, rotX, rotY, rotZ);
}

/***********************************************************
draw location
***********************************************************/
boost::shared_ptr<DynamicObject> Client::DrawLocationModel(HolomapPtr holomap, int modeltype, 
														   float posX, float posY, float posZ, 
															float rotX, float rotY, float rotZ)
{
	if(!holomap)
		return boost::shared_ptr<StaticObject>();

	// retrieve model info
	LbaNet::ModelInfo modelinfo;
	modelinfo.TypeRenderer = LbaNet::NoRender;
	switch(modeltype)
	{
		case 1:
			modelinfo = holomap->GetArrowModel();
		break;
		case 2:
			modelinfo = holomap->GetPlayerModel();
		break;
		case 3:
			modelinfo = holomap->GetArrowPlayerModel();
		break;
		case 4:
			modelinfo = holomap->GetTravelDotModel();
		break;
	}
	modelinfo.RotX += rotX;
	modelinfo.RotY += rotY;
	modelinfo.RotZ += rotZ;

	LbaNet::ObjectExtraInfo extrainfo;
	extrainfo.Display = false;
	LbaNet::LifeManaInfo lifeinfo;
	lifeinfo.Display = false;
	boost::shared_ptr<DisplayInfo> disinfo = ObjectInfo::ExtractDisplayInfo(1, modelinfo, 
																extrainfo, lifeinfo, false, 0);
	
	if(disinfo)
	{
		boost::shared_ptr<DisplayObjectHandlerBase> tmp =
			disinfo->BuildSelf(OsgHandler::getInstance());

		if(tmp)
		{
			boost::shared_ptr<PhysicalObjectHandlerBase> phystmp(
				new SimplePhysicalObjectHandler(posX, posY, posZ, LbaQuaternion()));

			boost::shared_ptr<StaticObject> sto(new StaticObject(phystmp, 
											tmp, boost::shared_ptr<SoundObjectHandlerBase>(), -1));
			_holodispobjects.push_back(sto);

			return sto;
		}
	}

	return boost::shared_ptr<StaticObject>();
}

/***********************************************************
TransformHoloCoordinate
***********************************************************/
void Client::TransformHoloCoordinate(const HoloCoordinate &holoc, 
									 float &posX, float &posY, float &posZ, 
									 float &rotX, float &rotY, float &rotZ)
{
	if(holoc.polarcoords)
	{
		float x = holoc.posZ*cos(holoc.posX*M_PI/180.0f);
		float y = holoc.posZ*sin(holoc.posX*M_PI/180.0f);

		float x2 = x*cos(holoc.posY*M_PI/180.0f);
		float z = x*sin(holoc.posY*M_PI/180.0f);

		posX = z;
		posY = y;
		posZ = x2;

		rotX = -holoc.posX;
		rotY = holoc.posY;
		rotZ = 0;
	}
	else
	{
		posX = holoc.posX;
		posY = holoc.posY;
		posZ = holoc.posZ;
		rotX = holoc.dir_cen_X;
		rotY = holoc.dir_cen_Y;
		rotZ = holoc.dir_cen_Z;
	}
}

/***********************************************************
update holomap stuff on frame basis
***********************************************************/
void Client::UpdateHolomap(double tnow, float tdiff)
{
	for(size_t i=0; i< _holodispobjects.size(); ++i)
		_holodispobjects[i]->Process(tnow, tdiff);

	if(_currHolomapMode == 1 || _currHolomapMode == 3)
		CameraFollowHoloLocation(tnow, tdiff);
}

/***********************************************************
CameraFollowHoloLocation
***********************************************************/
void Client::CameraFollowHoloLocation(double tnow, float tdiff)
{
	if(!_currHoloLocationPtr)
		return;

	if(!_camerafollowloc)
		return;

	HoloCoordinate  coords = _currHoloLocationPtr->GetCoordinate();
	if(coords.polarcoords)
	{
		double currzenit = OsgHandler::getInstance()->GetCameraZenit();
		double currazimut = OsgHandler::getInstance()->GetCameraAzimut();


		double diffazi = 180+(double)coords.posY - currazimut;
		while(diffazi > 180)
			diffazi -= 360;
		while(diffazi < -180)
			diffazi += 360;

		double diffzenit = (double)coords.posX - currzenit;
		while(diffzenit > 180)
			diffzenit -= 360;
		while(diffzenit < -180)
			diffzenit += 360;

		double norm = sqrt(diffazi * diffazi + diffzenit * diffzenit);
		if(norm == 0)
			norm = 1;



		bool finishedx=false, finishedy=false;
		double moveazi = ((diffazi > 0) ? 0.2 : -0.2) * tdiff * fabs(diffazi)/norm;
		if(fabs(moveazi) >= fabs(diffazi))
		{
			moveazi = diffazi;
			finishedx = true;
		}

		double movezenit = ((diffzenit > 0) ? 0.2 : -0.2) * tdiff * fabs(diffzenit)/norm;
		if(fabs(movezenit) >= fabs(diffzenit))
		{
			movezenit = diffzenit;
			finishedy = true;
		}

		_camerafollowloc = !(finishedx && finishedy);

		OsgHandler::getInstance()->SetCameraZenit(currzenit+movezenit);
		OsgHandler::getInstance()->SetCameraAzimut(currazimut+moveazi);
		OsgHandler::getInstance()->SetCameraTarget(0, 0, 0, true);
	}
	else
	{
		double TargetX, TargetY, TargetZ;
		OsgHandler::getInstance()->GetCameraTarget(TargetX, TargetY, TargetZ);

		double diffX = (double)coords.posX - TargetX;
		double diffY = (double)coords.posY - TargetY;
		double diffZ = (double)coords.posZ - TargetZ;

		double norm = sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
		if(norm == 0)
			norm = 1;


		bool finishedx=false, finishedy=false, finishedz=false;
		double moveX = ((diffX > 0) ? 0.05 : -0.05) * tdiff * fabs(diffX)/norm;
		if(fabs(moveX) >= fabs(diffX))
		{
			moveX = diffX;
			finishedx = true;
		}

		double moveY = ((diffY > 0) ? 0.05 : -0.05) * tdiff * fabs(diffY)/norm;
		if(fabs(moveY) >= fabs(diffY))
		{
			moveY = diffY;
			finishedy = true;
		}

		double moveZ = ((diffZ > 0) ? 0.05 : -0.05) * tdiff * fabs(diffZ)/norm;
		if(fabs(moveZ) >= fabs(diffZ))
		{
			moveZ = diffZ;
			finishedz = true;
		}

		_camerafollowloc = !(finishedx && finishedy && finishedz);

		OsgHandler::getInstance()->SetCameraTarget(TargetX+moveX, TargetY+moveY, TargetZ+moveZ, true);
	}
}





/***********************************************************
UpdateSelectedLocation
***********************************************************/
void Client::UpdateSelectedLocation(bool up)
{
	if(!_currHoloLocationPtr)
		return;

	std::set<HolomapLocationPtr>::iterator it = _drawnlocs.begin();
	std::set<HolomapLocationPtr>::iterator end = _drawnlocs.end();
	for(; it != end; ++it)
		if(*it == _currHoloLocationPtr)
			break;

	if(it == end)
		return;

	if(up)
	{
		++it;
		if(it == end)
			it = _drawnlocs.begin();
	}
	else
	{
		--it;
		if(it == end)
			it  = --(_drawnlocs.rbegin().base());
	}

	if(it != end)
	{
		_currHoloLocationPtr = *it;
		_camerafollowloc = true;
		
		DrawHoloText(_currHoloLocationPtr);
	}
}

/***********************************************************
ChangeHolomapUpDown
***********************************************************/
void Client::ChangeHolomapUpDown(bool up)
{
	if(!_currHoloLocationPtr)
		return;

	if(up)
	{
		long locid = _currHoloLocationPtr->GetParentLocId();
		if(locid >= 0)
		{
			HolomapLocationPtr newloc = HolomapHandler::getInstance()->GetHolomapLoc(locid);
			if(newloc)
			{
				_currHoloLocationPtr = newloc;
				_camerafollowloc = true;
				DrawHoloText(_currHoloLocationPtr);	
		

				_currHolomapPtr = 
					HolomapHandler::getInstance()->GetHolomap(_currHoloLocationPtr->GetParentHoloId());

				// generate player 3D location
				_currPlayer3DLocPtr = Generated3DLoc(_currHolomapPtr, -1);

				//! redraw the holomap
				DrawHolomap();
			}
		}
	}
	else
	{
		long holoid = _currHoloLocationPtr->GetChildHoloId();
		if(holoid >= 0 &&
			(_currHolomapPtr = HolomapHandler::getInstance()->GetHolomap(holoid)))
		{
			// generate player 3D location
			_currPlayer3DLocPtr = Generated3DLoc(_currHolomapPtr, _currHoloLocationPtr->GetId());
			

			////////////
			// we have to find one location on this holomap

			//first check player location
			HolomapLocationPtr loctmp = FindLocationOnHolo(_currHolomapPtr->GetId(),_currHolomapLocationOrPathId);
			if(loctmp)
			{
				_currHoloLocationPtr = loctmp;
				_camerafollowloc = true;
				DrawHoloText(_currHoloLocationPtr);	
			}
			else if(_currPlayer3DLocPtr) 
			{
				// else check player 3D coordinate
				_currHoloLocationPtr = _currPlayer3DLocPtr;
				_camerafollowloc = true;
				DrawHoloText(_currHoloLocationPtr);	
			}
			else
			{
				// then check quest location
				for(size_t i=0; i< _currHolomapquestholoids.size(); ++i)
				{
					HolomapLocationPtr loctmp = FindLocationOnHolo(_currHolomapPtr->GetId(), _currHolomapquestholoids[i]);
					if(loctmp)
					{
						_currHoloLocationPtr = loctmp;
						_camerafollowloc = true;
						DrawHoloText(_currHoloLocationPtr);	
						break;
					}
				}
			}
		

			//! redraw the holomap
			DrawHolomap();
		}
		else
		{
			// no holo available under -> we have to go back to the very top holomap available
			while(_currHoloLocationPtr->GetParentLocId() > 0)
			{
				HolomapLocationPtr tmploc = 
					HolomapHandler::getInstance()->
					GetHolomapLoc(_currHoloLocationPtr->GetParentLocId());

				if(tmploc)
				{
					_currHoloLocationPtr = tmploc;
					_camerafollowloc = true;
					DrawHoloText(_currHoloLocationPtr);	
				}
				else
					break;
			}

			long holoid = _currHoloLocationPtr->GetParentHoloId();
			if(holoid >= 0 &&
				(_currHolomapPtr = HolomapHandler::getInstance()->GetHolomap(holoid)))
			{
				//! redraw the holomap
				DrawHolomap();
			}
		}
	}
}

/***********************************************************
generate a location using player 3D position
***********************************************************/
HolomapLocationPtr Client::Generated3DLoc(HolomapPtr holomap, long parentlocid)
{
	HolomapLocationPtr res;
	if(!holomap)
		return res;

	if(holomap->GetUsePCoordinates())
	{
		res = HolomapLocationPtr(new HolomapLocation(-2));
		res->SetParentLocId(parentlocid);
		res->SetParentHoloId(holomap->GetId());

		//TODO
		HoloCoordinate coord;
		coord.polarcoords = false;
		coord.posX = _currHolomapplayerpos.x*holomap->Get3DCoordinateScaleX();
		coord.posY = _currHolomapplayerpos.y*holomap->Get3DCoordinateScaleY();
		coord.posZ = _currHolomapplayerpos.z*holomap->Get3DCoordinateScaleZ();
		coord.dir_cen_X = -90;
		res->SetCoordinate(coord);
	}
	
	return res;
}