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

#include "OSGHandler.h"
#include "LogHandler.h"
#include "ConfigurationManager.h"
#include "OsgObjectHandler.h"
#include "ObjectsDescription.h"
#include "CEGUIDrawable.h"
#include "OsgEventHandler.h"
#include "GuiHandler.h"


#include <osg/PositionAttitudeTransform>
#include <osg/ClipNode>
#include <osg/ShapeDrawable>
#include <osg/CullFace>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

#include <osgShadow/ShadowedScene>
#include <osgShadow/StandardShadowMap>
#include <osgShadow/ShadowMap>

// win32 only
#include <osgViewer/api/Win32/GraphicsWindowWin32>



#include <math.h>
#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif

static int ReceivesShadowTraversalMask = 0x1;
static int CastsShadowTraversalMask = 0x2;


OsgHandler* OsgHandler::_singletonInstance = NULL;





/***********************************************************
singleton pattern
***********************************************************/
OsgHandler * OsgHandler::getInstance()
{
    if(!_singletonInstance)
        _singletonInstance = new OsgHandler();

	return _singletonInstance;
}


/***********************************************************
constructor
***********************************************************/
OsgHandler::OsgHandler()
: _isFullscreen(false), _resX(800), _resY(600),
	_isPerspective(true), _targetx(10), _targety(10), _targetz(10),
	_viewer(NULL), _root(NULL), _rootNode3d(NULL), _sceneRootNode(NULL), _translNode(NULL),
	_viewportX(800), _viewportY(600), _displayShadow(false), 
	_current_clip_layer(-1)
{
	SetCameraDistance(30);
	SetCameraZenit(30);
}


/***********************************************************
destructor
***********************************************************/
OsgHandler::~OsgHandler()
{

}




/***********************************************************
initialize
***********************************************************/
void OsgHandler::Initialize(const std::string &WindowName, const std::string &DataPath,
							boost::shared_ptr<GuiHandler> GuiH)
{
	osgDB::setDataFilePathList(DataPath);


	LogHandler::getInstance()->LogToFile("Initializing graphics window...");




	// get data from configuration file
	{
		LogHandler::getInstance()->LogToFile("Initializing camera...");
		bool perspec;
		double camdistance, camzenit;
		ConfigurationManager::GetInstance()->GetDouble("Display.Camera.Distance", camdistance);
		ConfigurationManager::GetInstance()->GetDouble("Display.Camera.Zenit", camzenit);
		ConfigurationManager::GetInstance()->GetBool("Display.Camera.Perspective", perspec);
		SetCameraDistance(camdistance);
		SetCameraZenit(camzenit);
		TogglePerspectiveView(perspec);

		ConfigurationManager::GetInstance()->GetInt("Display.Screen.PositionX", _posX);
		ConfigurationManager::GetInstance()->GetInt("Display.Screen.PositionY", _posY);
		ConfigurationManager::GetInstance()->GetInt("Display.Screen.ScreenResolutionX", _resX);
		ConfigurationManager::GetInstance()->GetInt("Display.Screen.ScreenResolutionY", _resY);
		ConfigurationManager::GetInstance()->GetBool("Display.Screen.Fullscreen", _isFullscreen);

		ConfigurationManager::GetInstance()->GetBool("Display.ShadowOn", _displayShadow);
	}


	// set SDL screen
	LogHandler::getInstance()->LogToFile("Initializing screen display...");

    _viewer = new osgViewer::Viewer();


    // create the window to draw to.
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->x = _posX;
    traits->y = _posY;
    traits->width = _resX;
    traits->height = _resY;
    traits->windowDecoration = true;
    traits->doubleBuffer = true;
    traits->sharedContext = 0;
	traits->windowName = WindowName;
	traits->useCursor = false;
    osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
    _gw = dynamic_cast<osgViewer::GraphicsWindow*>(gc.get());
    if (!_gw)
        return;

    _viewer->getCamera()->setGraphicsContext(gc.get());
	_viewer->getCamera()->setClearColor(osg::Vec4(0, 0, 0, 1));
    _viewer->getCamera()->setViewport(0,0,_resX,_resY);

	_viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
	_viewer->realize();
	_viewer->getCamera()->getGraphicsContext()->makeCurrent(); 
	_viewer->setReleaseContextAtEndOfFrameHint(false);





	// create the root node used for camera transformation
	_rootNode3d = new osg::PositionAttitudeTransform();
	_rootNode3d->setScale(osg::Vec3d(1, 0.5, 1));
	_rootNode3d->setAttitude(osg::Quat(osg::DegreesToRadians(-45.0), osg::Vec3(0,1,0)));
	_translNode = new osg::PositionAttitudeTransform();
	_rootNode3d->addChild(_translNode);



	_root=new osg::Group;
	_rootNodeGui=new osg::Group;
	osg::setNotifyLevel(osg::ALWAYS );

	osg::ref_ptr<osg::Geode> guiGeom=new osg::Geode;
	_HUDcam = new osg::Camera;

	_HUDcam->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	_HUDcam->setClearMask(0);
	_HUDcam->setRenderOrder(osg::Camera::POST_RENDER, 100000);

	_HUDcam->setAllowEventFocus(false);
	_HUDcam->getOrCreateStateSet()->setMode(GL_DEPTH_TEST,osg::StateAttribute::OVERRIDE | 
														osg::StateAttribute::OFF);
    _HUDcam->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OVERRIDE |
														osg::StateAttribute::OFF);
    _HUDcam->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

    _HUDcam->getOrCreateStateSet()->setRenderBinDetails(100,"RenderBin");
    _HUDcam->getOrCreateStateSet()->setMode(GL_BLEND,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON);
    _HUDcam->getOrCreateStateSet()->setTextureMode(0, GL_TEXTURE_2D, osg::StateAttribute::OVERRIDE|
																			osg::StateAttribute::ON);
    _HUDcam->setProjectionMatrix(osg::Matrix::ortho2D(0,_resX,0,_resY));

	osg::CullFace *cull = new osg::CullFace();
	cull->setMode(osg::CullFace::BACK);
	_HUDcam->getOrCreateStateSet()->setAttributeAndModes(cull, osg::StateAttribute::ON);
	_HUDcam->addChild(_rootNodeGui.get());





	osg::ref_ptr<CEGUIDrawable> cd = new CEGUIDrawable(_resX, _resY, GuiH);
	_root->addChild(_rootNode3d.get());
	_root->addChild(_HUDcam.get());

	guiGeom->addDrawable(cd.get());
	_rootNodeGui->addChild(guiGeom.get());


	_viewer->setSceneData(_root.get());
	_viewer->setCameraManipulator(NULL);



	_clipNode = new osg::ClipNode();
	_clipNode->setStateSetModes(*_translNode->getOrCreateStateSet(),osg::StateAttribute::ON|osg::StateAttribute::PROTECTED|osg::StateAttribute::OVERRIDE);
	_translNode->addChild(_clipNode);




	// add the stats handler
	_viewer->addEventHandler( new OsgEventHandler() );

	 osgViewer::StatsHandler *sth = new osgViewer::StatsHandler;
	 sth->setKeyEventTogglesOnScreenStats(osgGA::GUIEventAdapter::KEY_F11);
	 _viewer->addEventHandler(sth);


    _viewer->realize();

	// reset camera
	ResetCameraProjectiomMatrix();

	//set default root node
	ResetDisplayTree();

	// put everything in the right place
	LogHandler::getInstance()->LogToFile("Initializing of graphics window done.");


}

/***********************************************************
get windows handle (win32 only)
***********************************************************/
void* OsgHandler::GetWindowsHandle()
{
	osgViewer::GraphicsWindowWin32* gw32 =  dynamic_cast<osgViewer::GraphicsWindowWin32*>(_gw);
	if(gw32)
		return (void*)gw32->getHWND();
		
	return NULL;
}



/***********************************************************
finalize function
***********************************************************/
void OsgHandler::Finalize()
{

	// write data to configuration file
	{
		ConfigurationManager::GetInstance()->SetDouble("Display.Camera.Distance", _distance);
		ConfigurationManager::GetInstance()->SetDouble("Display.Camera.Zenit", _zenit);
		ConfigurationManager::GetInstance()->SetBool("Display.Camera.Perspective", _isPerspective);

		ConfigurationManager::GetInstance()->SetInt("Display.Screen.PositionX", _posX);
		ConfigurationManager::GetInstance()->SetInt("Display.Screen.PositionY", _posY);
		ConfigurationManager::GetInstance()->SetInt("Display.Screen.ScreenResolutionX", _resX);
		ConfigurationManager::GetInstance()->SetInt("Display.Screen.ScreenResolutionY", _resY);
		ConfigurationManager::GetInstance()->SetBool("Display.Screen.Fullscreen", _isFullscreen);

		ConfigurationManager::GetInstance()->SetBool("Display.ShadowOn", _displayShadow);
	}

	// clean up everything
	ResetScreen();
	_sceneRootNode = NULL;
	_rootNode3d = NULL;
	_root = NULL;
	_viewer = NULL;
	_translNode =NULL;
	_HUDcam =NULL;
	_rootNodeGui =NULL;
	_lightNode =NULL;
	_clipNode =NULL;
}



/***********************************************************
change screen resolution
***********************************************************/
void OsgHandler::Resize(int resX, int resY, bool fullscreen)
{
	if(resX != _resX || resY != _resY || fullscreen != _isFullscreen)
	{
		_resX = resX;
		_resY = resY;
		_isFullscreen = fullscreen;

		ResetScreen();

		ConfigurationManager::GetInstance()->SetInt("Display.Screen.ScreenResolutionX", _resX);
		ConfigurationManager::GetInstance()->SetInt("Display.Screen.ScreenResolutionY", _resY);
		ConfigurationManager::GetInstance()->SetBool("Display.Screen.Fullscreen", _isFullscreen);
	}
}


/***********************************************************
toggle fullscreen or windowed mode
***********************************************************/
void OsgHandler::ToggleFullScreen()
{
	_isFullscreen = !_isFullscreen;
	ResetScreen();
}


/***********************************************************
set or reset screen
***********************************************************/
void OsgHandler::ResetScreen()
{
	LogHandler::getInstance()->LogToFile("Resetting screen resolution...");


	// iterate over all windows
	osgViewer::Viewer::Windows windows;
    _viewer->getWindows(windows);
    for(osgViewer::Viewer::Windows::iterator itr = windows.begin();  itr != windows.end(); ++itr)
    {
		osgViewer::GraphicsWindow *window = *itr;

		osg::GraphicsContext::WindowingSystemInterface    *wsi = osg::GraphicsContext::getWindowingSystemInterface();
		if (wsi == NULL) 
		{
			LogHandler::getInstance()->LogToFile("Error, no WindowSystemInterface available, cannot toggle window resolution change.");
			return;
		}

		unsigned int    screenWidth;
		unsigned int    screenHeight;
		wsi->getScreenResolution(*(window->getTraits()), screenWidth, screenHeight);

		if(_isFullscreen)
		{
			window->setWindowDecoration(false);
			window->setWindowRectangle(0, 0, screenWidth, screenHeight);
			_viewportX = screenWidth;
			_viewportY = screenHeight;
			
		}
		else
		{
			window->setWindowDecoration(true);
			window->setWindowRectangle(_posX, _posY, _resX, _resY);
			_viewportX = _resX;
			_viewportY = _resY;
		}

		_viewer->getCamera()->setViewport(0,0,_viewportX,_viewportY);
		window->grabFocus();
		window->raiseWindow();
    }

	ResetCameraProjectiomMatrix();

	_HUDcam->setProjectionMatrix(osg::Matrix::ortho2D(0,_resX,0,_resY));
}





/***********************************************************
set or reset camera projection matrix
***********************************************************/
void OsgHandler::ResetCameraProjectiomMatrix()
{
	if(!_viewer)
		return;

	if(_isPerspective)
	{
		_viewer->getCamera()->setProjectionMatrixAsPerspective(_fov,_viewportX/(double)_viewportY, 0.01,2000);
	}
	else
	{
		_viewer->getCamera()->setProjectionMatrixAsOrtho(-0.12*_distance, 0.12*_distance,
															-0.12*_distance, 0.12*_distance,
															-2000, 2000);
	}

	ResetCameraTransform();
}



/***********************************************************
set or reset camera transform
***********************************************************/
void OsgHandler::ResetCameraTransform()
{
	if(_viewer)
	{
		osg::Matrixd viewMatrix;
		if(_isPerspective)
		{
			osg::Matrixd cameraRotation1;
			osg::Matrixd cameraTrans;

			cameraRotation1.makeRotate(osg::DegreesToRadians(_zenit), osg::Vec3(1,0,0));
			cameraTrans.makeTranslate( 0,0,-_distance );
			viewMatrix = cameraRotation1* cameraTrans;
		}
		else
		{
			osg::Matrixd cameraRotation1;
			osg::Matrixd cameraTrans;

			cameraRotation1.makeRotate(osg::DegreesToRadians(30.0), osg::Vec3(1,0,0));
			cameraTrans.makeTranslate( 0,0,-1000 );
			viewMatrix = cameraRotation1 * cameraTrans;
		}


		_viewer->getCamera()->setViewMatrix(viewMatrix);
	}
}



/***********************************************************
set if the view is perspective or ortho
***********************************************************/
void OsgHandler::TogglePerspectiveView(bool Perspective)
{
	if(_isPerspective != Perspective)
	{
		_isPerspective = Perspective;
		ResetCameraProjectiomMatrix();

		ConfigurationManager::GetInstance()->SetBool("Display.Camera.Perspective", _isPerspective);
	}
}

/***********************************************************
delta update camera distance
***********************************************************/
void OsgHandler::DeltaUpdateCameraDistance(double delta)
{
	SetCameraDistance(_distance+delta);
}


/***********************************************************
set camera distance
***********************************************************/
void OsgHandler::SetCameraDistance(double distance)
{
	if(_distance != distance)
	{
		_distance = distance;
		int maxdistance = 150;
		if(!_isPerspective)
			maxdistance = 1000;

		if(_distance < 10)
			_distance = 10;
		if(_distance > maxdistance)
			_distance = maxdistance;

		_fov=atan(40./_distance)*180./M_PI;

		ResetCameraProjectiomMatrix();
	}
}


/***********************************************************
delta update camera zenit
***********************************************************/
void OsgHandler::DeltaUpdateCameraZenit(double delta)
{
	SetCameraZenit(_zenit+delta);
}

/***********************************************************
set camera zenit
***********************************************************/
void OsgHandler::SetCameraZenit(double zenit)
{
	if(_zenit != zenit)
	{
		_zenit = zenit;

		if(_zenit < 10)
			_zenit = 10;
		if(_zenit > 70)
			_zenit = 70;

		ResetCameraTransform();
	}
}


/***********************************************************
set camera target
***********************************************************/
void OsgHandler::SetCameraTarget(double TargetX, double TargetY, double TargetZ)
{
	_targetx = TargetX;
	_targety = TargetY;
	_targetz = TargetZ;

	//ResetCameraTransform();
	if(_translNode)
		_translNode->setPosition(osg::Vec3d( -_targetx,-_targety,-_targetz ));
}
/***********************************************************
set camera target
***********************************************************/
void OsgHandler::GetCameraTarget(double &TargetX, double &TargetY, double &TargetZ)
{
	TargetX = _targetx;
	TargetY = _targety;
	TargetZ = _targetz;

}

/***********************************************************
set light
***********************************************************/
void OsgHandler::SetLight(const LbaMainLightInfo &LightInfo)
{
	if(!_lightNode)
		return;

	if(LightInfo.UseLight)
	{
		osg::Light* myLight1 = new osg::Light();
		myLight1->setLightNum(0);

		osg::Vec4 lightpos;
		lightpos.set(LightInfo.LOnPosX, LightInfo.LOnPosY, LightInfo.LOnPosZ,0.0f);
		myLight1->setPosition(lightpos);

		if(LightInfo.DirectionalLight)
		{
			osg::Vec3 lightdirection;
			lightdirection.set(LightInfo.LOnDirectionX, LightInfo.LOnDirectionY, LightInfo.LOnDirectionZ);
			myLight1->setDirection(lightdirection);
		}

		myLight1->setAmbient(osg::Vec4(LightInfo.LOnAmbientR,LightInfo.LOnAmbientG,LightInfo.LOnAmbientB, 1.0));
		myLight1->setDiffuse(osg::Vec4(LightInfo.LOnDiffuseR,LightInfo.LOnDiffuseG,LightInfo.LOnDiffuseB, 1.0));
		myLight1->setSpecular(osg::Vec4(LightInfo.LOnSpecularR,LightInfo.LOnSpecularG,LightInfo.LOnSpecularB, 1.0));

		if(LightInfo.UseAttenuation)
		{
			myLight1->setConstantAttenuation(LightInfo.Constant_attenuation);
			myLight1->setLinearAttenuation(LightInfo.Linear_attenuation);
			myLight1->setQuadraticAttenuation(LightInfo.Quadratic_attenuation);
		}

		if(LightInfo.UseExtendedSpotInfo)
		{
			myLight1->setSpotExponent(LightInfo.Spot_exponent);
			myLight1->setSpotCutoff(LightInfo.Spot_cutoff);
		}

		_lightNode->setLight(myLight1);
		_lightNode->setLocalStateSetModes(osg::StateAttribute::ON);
		_lightNode->setStateSetModes(*_translNode->getOrCreateStateSet(),osg::StateAttribute::ON);
	}
	else
	{
		_lightNode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OVERRIDE|osg::StateAttribute::OFF);
	}

}


/***********************************************************
clear all nodes of the display tree
typically called when changing map
***********************************************************/
void OsgHandler::ResetDisplayTree()
{
	if(!_translNode)
		return;

	if(_lightNode)
		_translNode->removeChild(_lightNode);

	_lightNode = new osg::LightSource();
	_translNode->addChild(_lightNode);


	// check if we use shadow or not
	if(_displayShadow)
	{
		osg::ref_ptr<osgShadow::ShadowedScene> shadowscene = new osgShadow::ShadowedScene();
		shadowscene->setReceivesShadowTraversalMask(ReceivesShadowTraversalMask);
		shadowscene->setCastsShadowTraversalMask(CastsShadowTraversalMask);

		osg::ref_ptr<osgShadow::StandardShadowMap> shmap = new osgShadow::StandardShadowMap();
		shadowscene->setShadowTechnique(shmap.get());
		_sceneRootNode = shadowscene;
	}
	else
	{
		_sceneRootNode = new osg::Group();	
	}

	_lightNode->addChild(_sceneRootNode);


	//set default light
	LbaMainLightInfo Linf;
	Linf.UseLight = false;
	SetLight(Linf);
}



/***********************************************************
update display - returns true if need to terminate
***********************************************************/
bool OsgHandler::Update()
{
	if(!_viewer->done())
	{
		// draw the new frame
		_viewer->frame();

		return false;
	}

	return true;
}


/***********************************************************
load osg files into a osg node
***********************************************************/
osg::ref_ptr<osg::Node> OsgHandler::LoadOSGFile(const std::string & filename)
{
	return osgDB::readNodeFile(filename);
}



/***********************************************************
add a actor to the display list - return handler to actor position
***********************************************************/
osg::ref_ptr<osg::MatrixTransform> OsgHandler::AddActorNode(osg::ref_ptr<osg::Node> node)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Added Node to display engine");
	#endif

	node->setNodeMask(ReceivesShadowTraversalMask | CastsShadowTraversalMask);
	osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform();
	transform->addChild(node);

	if(_sceneRootNode)
		_sceneRootNode->addChild(transform);

	return transform;
}


/***********************************************************
readd a removed actor to the display list
***********************************************************/
void OsgHandler::ReAddActorNode(osg::ref_ptr<osg::Node> node)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("ReAdded Node to display engine");
	#endif

	if(_sceneRootNode)
		_sceneRootNode->addChild(node);
}


/***********************************************************
remove actor from the graph
***********************************************************/
void OsgHandler::RemoveActorNode(osg::ref_ptr<osg::Node> node)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Removed Node from display engine");
	#endif

	if(_sceneRootNode)
		_sceneRootNode->removeChild(node);
}




/***********************************************************
set clip plane cut layer
***********************************************************/
void OsgHandler::SetClipPlane(float layer)
{
	if(_current_clip_layer == layer)
		return;

	_current_clip_layer = layer;

	_clipNode->setStateSetModes(*_translNode->getOrCreateStateSet(),osg::StateAttribute::OFF);
	_clipNode->removeClipPlane((unsigned int)0);


	if(layer > 0)
	{
		osg::ref_ptr<osg::ClipPlane> clipplane = new osg::ClipPlane();
		clipplane->setClipPlane(0, -1, 0, layer+0.01);
		_clipNode->addClipPlane(clipplane);
		_clipNode->setStateSetModes(*_translNode->getOrCreateStateSet(),osg::StateAttribute::ON);
	}
}



/***********************************************************
set screen attributes
***********************************************************/
void OsgHandler::GetScreenAttributes(int &resX, int &resY, bool &fullscreen)
{
	fullscreen = _isFullscreen;
	resX = _resX;
	resY = _resY;
}





/***********************************************************
create simple display object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgHandler::CreateSimpleObject(const std::string & filename,
														boost::shared_ptr<DisplayTransformation> Tr)
{
	osg::ref_ptr<osg::Node> resnode = LoadOSGFile(filename);

	if(Tr)
	{
		osg::ref_ptr<osg::PositionAttitudeTransform> transform = new osg::PositionAttitudeTransform();
		transform->setPosition(osg::Vec3d(Tr->translationX, Tr->translationY, Tr->translationZ));
		transform->setAttitude(osg::Quat(Tr->rotation.X, Tr->rotation.Y, Tr->rotation.Z, Tr->rotation.W));
		transform->setScale(osg::Vec3d(Tr->scaleX, Tr->scaleY, Tr->scaleZ));

		transform->addChild(resnode);
		resnode = transform;
	}
	
	osg::ref_ptr<osg::MatrixTransform> mat = AddActorNode(resnode);
	return boost::shared_ptr<DisplayObjectHandlerBase>(new OsgObjectHandler(mat));
}



/***********************************************************
create capsule object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgHandler::CreateCapsuleObject(float radius, float height, 
														float colorR, float colorG, float colorB, float colorA,
														boost::shared_ptr<DisplayTransformation> Tr)
{
	osg::ref_ptr<osg::Group> resnode = new osg::Group();

	// create capsule
	osg::ref_ptr<osg::Geode> capsuleGeode(new osg::Geode());
	osg::ref_ptr<osg::Capsule> caps(new osg::Capsule(osg::Vec3(0,0,0),radius,height));
	osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
	//capsdraw->setColor(osg::Vec4(colorR, colorG, colorB, colorA));
	capsuleGeode->addDrawable(capsdraw);
	resnode->addChild(capsuleGeode);


	if(Tr)
	{
		osg::ref_ptr<osg::PositionAttitudeTransform> transform = new osg::PositionAttitudeTransform();
		transform->setPosition(osg::Vec3d(Tr->translationX, Tr->translationY, Tr->translationZ));
		transform->setAttitude(osg::Quat(Tr->rotation.X, Tr->rotation.Y, Tr->rotation.Z, Tr->rotation.W));
		transform->setScale(osg::Vec3d(Tr->scaleX, Tr->scaleY, Tr->scaleZ));

		transform->addChild(resnode);
		resnode = transform;
	}
	
	osg::ref_ptr<osg::MatrixTransform> mat = AddActorNode(resnode);
	return boost::shared_ptr<DisplayObjectHandlerBase>(new OsgObjectHandler(mat));
}
