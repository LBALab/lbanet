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

#include "CommonTypes.h"
#include "DisplayHandlerBase.h"

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



class GuiHandler;
class OsgEventHandler;
class GraphicsWindowQt;
class EditorHandler;

static int ReceivesShadowTraversalMask = 0x1;
static int CastsShadowTraversalMask = 0x2;

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
#ifdef _USE_QT_EDITOR_
	void Initialize(const std::string &WindowName, const std::string &DataPath,
														boost::shared_ptr<GuiHandler> GuiH,
														boost::shared_ptr<EditorHandler> editorH);
#else
	void Initialize(const std::string &WindowName, const std::string &DataPath,
														boost::shared_ptr<GuiHandler> GuiH);
#endif


	//! finalize function
	void Finalize();


	//! change screen resolution
	void Resize(int resX, int resY, bool fullscreen);

	//! change screen resolution
	void Resize(int resX, int resY);

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

	//! delta update camera zenit
	void DeltaUpdateCameraZenit(double delta);

	//! set camera azimut
	void SetCameraAzimut(double azimut, bool forced = false);

	//! get current azimut
	double GetCameraAzimut()
	{ return _azimut;}

	//! delta update camera zenit
	void DeltaUpdateCameraAzimut(double delta);


	//! set camera target
	void SetCameraTarget(double TargetX, double TargetY, double TargetZ);
	void GetCameraTarget(double &TargetX, double &TargetY, double &TargetZ);

	//! clear all nodes of the display tree
	//! typically called when changing map
	//! set if new map uses lighning or not
	void ResetDisplayTree();

	//! update display - returns true if need to terminate
	bool Update();

	//! load osg files into a osg node
	osg::ref_ptr<osg::Node> LoadOSGFile(const std::string & filename);

	//! add a actor to the display list - return handler to actor position
	osg::ref_ptr<osg::MatrixTransform> AddActorNode(osg::ref_ptr<osg::Node> node,
														bool UseLight, bool CastShadow);


	//! add an empty actor to the display list - return handler to actor position
	osg::ref_ptr<osg::MatrixTransform> AddEmptyActorNode(bool WithLight);

	//! readd a removed actor to the display list
	void ReAddActorNode(osg::ref_ptr<osg::Node> node, bool WithLight);

	//! remove actor from the graph
	void RemoveActorNode(osg::ref_ptr<osg::Node> node, bool WithLight);

	//! set light
	void SetLight(const LbaMainLightInfo &LightInfo);


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
	{return _cameraType;}



	//! create simple display object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateSimpleObject(const std::string & filename,
															boost::shared_ptr<DisplayTransformation> Tr,
															bool UseLight, bool CastShadow,
															const LbaNet::ObjectExtraInfo &extrainfo);


	//! create capsule object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateCapsuleObject(float radius, float height, 
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															const LbaNet::ObjectExtraInfo &extrainfo);


	//! create box object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateBoxObject(float sizex, float sizey, float sizez, 
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															const LbaNet::ObjectExtraInfo &extrainfo);



	//! create cross object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> CreateCrossObject(float size,
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															const LbaNet::ObjectExtraInfo &extrainfo);

	//! create PAT
	osg::ref_ptr<osg::PositionAttitudeTransform> CreatePAT(boost::shared_ptr<DisplayTransformation> Tr);


	//! get windows handle (win32 only)
	void* GetWindowsHandle();


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

	bool	_displayShadow;


	// camera info
	int		_cameraType;
	int		_autoCameraType;
	double	_targetx;
	double	_targety;
	double	_targetz;
	double	_fov;
	double	_distance;
	double	_zenit;
	double	_azimut;
	float	_current_clip_layer;


	// osg handlers
	osg::ref_ptr<osgViewer::Viewer>					_viewer;


	osg::ref_ptr<osg::PositionAttitudeTransform>	_rootNode3d;
	osg::ref_ptr<osg::Group>						_root;
	osg::ref_ptr<osg::Group>						_rootNodeGui;
	osg::ref_ptr<osg::PositionAttitudeTransform>	_translNode;
	osg::ref_ptr<osg::LightSource>					_lightNode;
	osg::ref_ptr<osg::Group>						_sceneRootNode;
	osg::ref_ptr<osg::Group>						_sceneNoLightRootNode;

	osg::ref_ptr<osg::ClipNode>						_clipNode;
	osg::ref_ptr<osg::Camera>						_HUDcam;
};


#endif
