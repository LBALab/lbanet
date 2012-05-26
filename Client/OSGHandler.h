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


#ifndef _LBANET_OSG_HANDLER_H_
#define _LBANET_OSG_HANDLER_H_

#include <vector>
#include <string>
#include <osg/ref_ptr>
#include <boost/shared_ptr.hpp>

#include "../shared/CommonTypes.h"
#include "../shared/DisplayHandlerBase.h"

namespace osg
{
	class Node;
	class PositionAttitudeTransform;
	class Group;
	class MatrixTransform;
	class LightSource;
	class ClipNode;
	class Camera;
}

namespace osgViewer
{
	class Viewer;
	class GraphicsWindow;
}

namespace osgShadow
{
	class ShadowedScene;
}

namespace osgAudio
{
	class SoundRoot;
}

// camera info
struct OsgHCameraInfo
{
	//constructor
	OsgHCameraInfo()
		: cameraType(0), targetx(10), targety(10), targetz(10), 
			fov(0), distance(0), zenit(0), azimut(0)
	{}

	int		cameraType;
	double	targetx;
	double	targety;
	double	targetz;
	double	fov;
	double	distance;
	double	zenit;
	double	azimut;
};


class GuiHandler;
class OsgEventHandler;
class GraphicsWindowQt;
class QT_Windows_base;
class CEGUIDrawable;

static int ReceivesShadowTraversalMask = 0x1;
static int CastsShadowTraversalMask = 0x2;

#define		_NB_OSG_SCENES_		2

//*************************************************************************************************
//*                               class OsgHandler
//*************************************************************************************************
/**
* @brief Class takign care of the OSG 3D engine
*
*/
class OsgHandler : public DisplayHandlerBase
{
public:

	// singleton pattern
	static OsgHandler * getInstance();

	//! destructor
	~OsgHandler();

	//! initialize
	void Initialize(const std::string &WindowName, const std::string &DataPath,
														boost::shared_ptr<GuiHandler> GuiH,
														boost::shared_ptr<QT_Windows_base> qtH);



	//! finalize function
	void Finalize();


	//! change screen resolution
	void Resize(int resX, int resY, bool fullscreen);

	//! change screen resolution
	void Resize(int resX, int resY);

	//! called when screen is resized
	void Resized(int resX, int resY);


	//! toggle fullscreen or windowed mode
	void ToggleFullScreen();
	
	//! set if the view is perspective or ortho
	//! 0 -> auto (depends on map)
	//! 1 -> orthogonal
	//! 2 -> perspective
	//! 3 -> free 3D
	void ToggleCameraType(int cameraType);
	
	//! set if the view is perspective or ortho
	//! 1 -> orthogonal
	//! 2 -> perspective
	//! 3 -> free 3D
	void ToggleAutoCameraType(int cameraType);

	//! set camera distance
	void SetCameraDistance(double distance, bool forced = false);

	//! delta update camera distance
	void DeltaUpdateCameraDistance(double delta);

	//! set camera zenit
	void SetCameraZenit(double zenit, bool forced = false);

	//! get current azimut
	double GetCameraZenit()
	{ return _caminfo.zenit;}

	//! delta update camera zenit
	void DeltaUpdateCameraZenit(double delta);

	//! set camera azimut
	void SetCameraAzimut(double azimut, bool forced = false);

	//! get current azimut
	double GetCameraAzimut()
	{ return _caminfo.azimut;}

	//! delta update camera zenit
	void DeltaUpdateCameraAzimut(double delta);


	//! set camera target
	void SetCameraTarget(double TargetX, double TargetY, double TargetZ, bool force=false);
	void GetCameraTarget(double &TargetX, double &TargetY, double &TargetZ);

	//! clear all nodes of the display tree
	//! typically called when changing map
	//! set if new map uses lighning or not
	void ResetDisplayTree(int sceneidx);

	//! update display - returns true if need to terminate
	bool Update();

	//! load osg files into a osg node
	osg::ref_ptr<osg::Node> LoadOSGFile(const std::string & filename);

	//! add a actor to the display list - return handler to actor position
	osg::ref_ptr<osg::MatrixTransform> AddActorNode(int sceneidx, osg::ref_ptr<osg::Node> node,
														bool UseLight, bool CastShadow);


	//! add an empty actor to the display list - return handler to actor position
	osg::ref_ptr<osg::MatrixTransform> AddEmptyActorNode(int sceneidx, bool WithLight);

	//! readd a removed actor to the display list
	void ReAddActorNode(int sceneidx, osg::ref_ptr<osg::Node> node, bool WithLight);

	//! remove actor from the graph
	void RemoveActorNode(int sceneidx, osg::ref_ptr<osg::Node> node, bool WithLight);

	//! set light
	void SetLight(int sceneidx, const LbaMainLightInfo &LightInfo);


	//! set clip plane cut layer
	void SetClipPlane(float layer);


	//! set screen attributes
	void GetScreenAttributes(int &resX, int &resY, bool &fullscreen);
	
	//! check if the view is perspective or ortho
	//! 0 -> auto (depends on map)
	//! 1 -> orthogonal
	//! 2 -> perspective
	//! 3 -> free 3D
	int CameraType()
	{return _caminfo.cameraType;}

	//! toggle shadow
	void ToggleShadow(int ShadowType);


	// create sprite object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateSpriteObject(int sceneidx, const std::string & spritefile, 
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															bool UseLight, bool CastShadow,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo,
															bool UseBillboard);

	//! create simple display object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateSimpleObject(int sceneidx, const std::string & filename,
															boost::shared_ptr<DisplayTransformation> Tr,
															bool UseLight, bool CastShadow,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo);

	//! create sphere object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateSphereObject(int sceneidx, float radius, 
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo);

	//! create capsule object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateCapsuleObject(int sceneidx, float radius, float height, 
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo);


	//! create box object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateBoxObject(int sceneidx, float sizex, float sizey, float sizez, 
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo);



	//! create cross object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateCrossObject(int sceneidx, float size,
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo);


	// create sprite object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateBackgroundImageObject(const std::string & filenamefile, 
															float colorR, float colorG, float colorB, float colorA);

	//! create grid object
	osg::ref_ptr<osg::MatrixTransform> CreateGridObject(int sceneidx, long sizeX, long sizeY,
															boost::shared_ptr<DisplayTransformation> Tr);

	//! create PAT
	osg::ref_ptr<osg::PositionAttitudeTransform> CreatePAT(boost::shared_ptr<DisplayTransformation> Tr);


	//! optimize the scene
	void OptimizeScene();


	// create sprite object
	osg::ref_ptr<osg::MatrixTransform> CreateSpriteObject(int sceneidx, const std::string & spritefile, 
												float colorR, float colorG, float colorB, float colorA,
												boost::shared_ptr<DisplayTransformation> Tr,
												bool UseLight, bool CastShadow,
												bool UseBillboard);

	//! create simple display object
	osg::ref_ptr<osg::MatrixTransform> CreateSimpleObject(int sceneidx, const std::string & filename,
															boost::shared_ptr<DisplayTransformation> Tr,
															bool UseLight, bool CastShadow);


	// create sprite object
	osg::ref_ptr<osg::MatrixTransform> CreateBackgroundImage(const std::string & imagefile, 
												float colorR, float colorG, float colorB, float colorA);



	//! render object to file
	void RenderObjectToFile(osg::ref_ptr<osg::Group> object, const std::string & filename);


	//! get gui drawable
	osg::ref_ptr<CEGUIDrawable> GetGUIDrawable();

	//! send sound root
	void SetSoundRoot(osg::ref_ptr<osgAudio::SoundRoot> sound_root);


	//! switch between the different scenes
	void SwitchScene(int newsceneidx);

	//! store camera info
	void StoreCameraInfo();

	//! reset camera info
	void ResetCameraInfo();


protected:
	//! constructor
	OsgHandler();

	//! set or reset screen
	void ResetScreen();

	//! set or reset camera projection matrix
	void ResetCameraProjectiomMatrix();

	//! set or reset camera transform
	void ResetCameraTransform();

	//! set or reset camera azimut
	void ResetCameraAzimut();

	//! reset camera distances when changeing cam type
	void ResetCameraDistances(double distance);

	//! set shadow node
	osg::ref_ptr<osg::Group> CreateShadowNode();

	//! get scene root node
	osg::ref_ptr<osg::Group> &GetSceneRootNode(); 

	//! get scene root node
	osg::ref_ptr<osg::Group> &GetSceneRootNodeNoLight(); 

	//! get scene root node
	osg::ref_ptr<osg::LightSource> &GetLigthNode(); 

	//! get scene root node
	osg::ref_ptr<osg::Group> & GetSceneRootNode(int sceneidx); 

	//! get scene root node
	osg::ref_ptr<osg::Group> & GetSceneRootNodeNoLight(int sceneidx); 

	//! get scene root node
	osg::ref_ptr<osg::LightSource> &GetLigthNode(int sceneidx); 

private:
	// singleton
	static OsgHandler * _singletonInstance;

	// pointer to the screen surface
	osgViewer::GraphicsWindow*		_gw;

	OsgEventHandler *				_eventH;


	// screen info
	bool	_isFullscreen;
	int		_posX;
	int		_posY;
	int		_resX;
	int		_resY;
	int		_viewportX;
	int		_viewportY;

	int		_ShadowType;


	float	_current_clip_layer;

	// camera info
	OsgHCameraInfo	_caminfo;
	OsgHCameraInfo	_savedcaminfo;
	int				_autoCameraType;

	// osg handlers
	osg::ref_ptr<osgViewer::Viewer>					_viewer;


	osg::ref_ptr<osg::PositionAttitudeTransform>	_rootNode3d;
	osg::ref_ptr<osg::Group>						_root;
	osg::ref_ptr<osg::Group>						_rootNodeGui;
	osg::ref_ptr<osg::Group>						_rootNodeBackground;
	osg::ref_ptr<osg::PositionAttitudeTransform>	_translNode;

	osg::ref_ptr<osg::LightSource>									_lightNodes[_NB_OSG_SCENES_];
	std::pair<osg::ref_ptr<osg::Group>, osg::ref_ptr<osg::Group> >	_sceneroots[_NB_OSG_SCENES_];
	int																_currentsceneroot;

	//osg::ref_ptr<osg::LightSource>				_lightNode;
	//osg::ref_ptr<osg::Group>						_sceneRootNode;
	//osg::ref_ptr<osg::Group>						_sceneNoLightRootNode;

	osg::ref_ptr<osg::ClipNode>						_clipNode;
	osg::ref_ptr<osg::Camera>						_HUDcam;
	osg::ref_ptr<osg::Camera>						_HUDcamBackground;

	osg::ref_ptr<CEGUIDrawable>						_guidraw;

	bool											_fixcamera;
};


#endif
