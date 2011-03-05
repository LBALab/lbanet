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
#include <osg/LineWidth>

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/CompositeViewer>

#include <osgDB/ReadFile>
#include <osgDB/FileUtils>

#include <osgShadow/ShadowedScene>
#include <osgShadow/StandardShadowMap>
#include <osgShadow/MinimalShadowMap>
#include <osgShadow/ShadowMap>
#include <osgParticle/PrecipitationEffect>
#include <osgDB/Registry>
#include <osgUtil/Optimizer>
#include <osgUtil/SmoothingVisitor>

// win32 only
#include <osgViewer/api/Win32/GraphicsWindowWin32>

#ifdef _USE_QT_EDITOR_
#include "editorhandler.h"
#endif


#include <math.h>
#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


//
//
//#include <osgOcean/Version>
//#include <osgOcean/OceanScene>
//#include <osgOcean/FFTOceanSurface>
//#include <osgOcean/SiltEffect>
//#include <osgOcean/ShaderManager>
//
//#include "SkyDome.h"
//
//// ----------------------------------------------------
////                  Scene Model
//// ----------------------------------------------------
//
//class SceneModel : public osg::Referenced
//{
//public:
//    enum SCENE_TYPE{ CLEAR, DUSK, CLOUDY };
//
//private:
//    SCENE_TYPE _sceneType;
//
//    osg::ref_ptr<osg::Group> _scene;
//
//    osg::ref_ptr<osgOcean::OceanScene> _oceanScene;
//    osg::ref_ptr<osgOcean::FFTOceanSurface> _oceanSurface;
//    osg::ref_ptr<osg::TextureCubeMap> _cubemap;
//    osg::ref_ptr<SkyDome> _skyDome;
//        
//    std::vector<std::string> _cubemapDirs;
//    std::vector<osg::Vec4f>  _lightColors;
//    std::vector<osg::Vec4f>  _fogColors;
//    std::vector<osg::Vec3f>  _underwaterAttenuations;
//    std::vector<osg::Vec4f>  _underwaterDiffuse;
//        
//    osg::ref_ptr<osg::Light> _light;
//
//    std::vector<osg::Vec3f>  _sunPositions;
//    std::vector<osg::Vec4f>  _sunDiffuse;
//    std::vector<osg::Vec4f>  _waterFogColors;
//
//public:
//    SceneModel( const osg::Vec2f& windDirection = osg::Vec2f(1.0f,1.0f),
//                float windSpeed = 12.f,
//                float depth = 10000.f,
//                float reflectionDamping = 0.35f,
//                float scale = 1e-8,
//                bool  isChoppy = true,
//                float choppyFactor = -2.5f,
//                float crestFoamHeight = 2.2f ):
//        _sceneType(CLEAR)
//    {
//        _cubemapDirs.push_back( "sky_clear" );
//        _cubemapDirs.push_back( "sky_dusk" );
//        _cubemapDirs.push_back( "sky_fair_cloudy" );
//
//        _fogColors.push_back( intColor( 199,226,255 ) );
//        _fogColors.push_back( intColor( 244,228,179 ) );
//        _fogColors.push_back( intColor( 172,224,251 ) );
//
//        _waterFogColors.push_back( intColor(27,57,109) );
//        _waterFogColors.push_back( intColor(44,69,106 ) );
//        _waterFogColors.push_back( intColor(84,135,172 ) );
//
//        _underwaterAttenuations.push_back( osg::Vec3f(0.015f, 0.0075f, 0.005f) );
//        _underwaterAttenuations.push_back( osg::Vec3f(0.015f, 0.0075f, 0.005f) );
//        _underwaterAttenuations.push_back( osg::Vec3f(0.008f, 0.003f, 0.002f) );
//
//        _underwaterDiffuse.push_back( intColor(27,57,109) );
//        _underwaterDiffuse.push_back( intColor(44,69,106) );
//        _underwaterDiffuse.push_back( intColor(84,135,172) );
//
//        _lightColors.push_back( intColor( 105,138,174 ) );
//        _lightColors.push_back( intColor( 105,138,174 ) );
//        _lightColors.push_back( intColor( 105,138,174 ) );
//
//        _sunPositions.push_back( osg::Vec3f(326.573, 1212.99 ,1275.19) );
//        _sunPositions.push_back( osg::Vec3f(520.f, 1900.f, 550.f ) );
//        _sunPositions.push_back( osg::Vec3f(-1056.89f, -771.886f, 1221.18f ) );
//
//        _sunDiffuse.push_back( intColor( 191, 191, 191 ) );
//        _sunDiffuse.push_back( intColor( 251, 251, 161 ) );
//        _sunDiffuse.push_back( intColor( 191, 191, 191 ) );
//
//        build(windDirection, windSpeed, depth, reflectionDamping, scale, isChoppy, choppyFactor, crestFoamHeight);
//    }
//
//    void build( const osg::Vec2f& windDirection,
//                float windSpeed,
//                float depth,
//                float reflectionDamping,
//                float waveScale,
//                bool  isChoppy,
//                float choppyFactor,
//                float crestFoamHeight )
//    {
//        {
//            _scene = new osg::Group; 
//
//            {
//                _cubemap = loadCubeMapTextures( _cubemapDirs[_sceneType] );
//            }
//
//            // Set up surface
//            {
//                _oceanSurface = new osgOcean::FFTOceanSurface( 64, 256, 17, 
//                    windDirection, windSpeed, depth, reflectionDamping, waveScale, isChoppy, choppyFactor, 10.f, 256 );  
//
//                _oceanSurface->setEnvironmentMap( _cubemap.get() );
//                _oceanSurface->setFoamBottomHeight( 2.2f );
//                _oceanSurface->setFoamTopHeight( 3.0f );
//                _oceanSurface->enableCrestFoam( true );
//                _oceanSurface->setLightColor( _lightColors[_sceneType] );
//                // Make the ocean surface track with the main camera position, giving the illusion
//                // of an endless ocean surface.
//                _oceanSurface->enableEndlessOcean(true);
//            }
//
//            // Set up ocean scene, add surface
//            {
//                osg::Vec3f sunDir = -_sunPositions[_sceneType];
//                sunDir.normalize();
//                
//                _oceanScene = new osgOcean::OceanScene( _oceanSurface.get() );
//                _oceanScene->setLightID(0);
//                _oceanScene->enableReflections(true);
//                _oceanScene->enableRefractions(false);
//
//                // Set the size of _oceanCylinder which follows the camera underwater. 
//                // This cylinder prevents the clear from being visible past the far plane 
//                // instead it will be the fog color.
//                // The size of the cylinder should be changed according the size of the ocean surface.
//                _oceanScene->setCylinderSize( 1900.f, 4000.f );
//                
//                _oceanScene->setAboveWaterFog(0.0012f, _fogColors[_sceneType] );
//                _oceanScene->setUnderwaterFog(0.002f,  _waterFogColors[_sceneType] );
//                _oceanScene->setUnderwaterDiffuse( _underwaterDiffuse[_sceneType] );
//                _oceanScene->setUnderwaterAttenuation( _underwaterAttenuations[_sceneType] );
//
//                _oceanScene->setSunDirection( sunDir );
//                _oceanScene->enableGodRays(false);
//                _oceanScene->enableSilt(false);
//                _oceanScene->enableUnderwaterDOF(false);
//                _oceanScene->enableDistortion(true);
//                _oceanScene->enableGlare(false);
//                _oceanScene->setGlareAttenuation(0.8f);
//
//                // create sky dome and add to ocean scene
//                // set masks so it appears in reflected scene and normal scene
//               // _skyDome = new SkyDome( 1900.f, 16, 16, _cubemap.get() );
//                ////_skyDome->setNodeMask( _oceanScene->getReflectedSceneMask() | _oceanScene->getNormalSceneMask() );
//
//               // _scene->addChild( _skyDome );
//
//                {
//                    // Create and add fake texture for use with nodes without any texture
//                    // since the OceanScene default scene shader assumes that texture unit 
//                    // 0 is used as a base texture map.
//                    osg::Image * image = new osg::Image;
//                    image->allocateImage( 1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE );
//                    *(osg::Vec4ub*)image->data() = osg::Vec4ub( 0xFF, 0xFF, 0xFF, 0xFF );
//                    
//                    osg::Texture2D* fakeTex = new osg::Texture2D( image );
//                    fakeTex->setWrap(osg::Texture2D::WRAP_S,osg::Texture2D::REPEAT);
//                    fakeTex->setWrap(osg::Texture2D::WRAP_T,osg::Texture2D::REPEAT);
//                    fakeTex->setFilter(osg::Texture2D::MIN_FILTER,osg::Texture2D::NEAREST);
//                    fakeTex->setFilter(osg::Texture2D::MAG_FILTER,osg::Texture2D::NEAREST);
//                    
//                    osg::StateSet* stateset = _oceanScene->getOrCreateStateSet();
//                    stateset->setTextureAttribute(0,fakeTex,osg::StateAttribute::ON);
//                    stateset->setTextureMode(0,GL_TEXTURE_1D,osg::StateAttribute::OFF);
//                    stateset->setTextureMode(0,GL_TEXTURE_2D,osg::StateAttribute::ON);
//                    stateset->setTextureMode(0,GL_TEXTURE_3D,osg::StateAttribute::OFF);
//                }
//
//            }
//
//            {
//                osg::LightSource* lightSource = new osg::LightSource;
//                lightSource->setLocalStateSetModes();
//
//                _light = lightSource->getLight();
//                _light->setLightNum(0);
//                _light->setAmbient( osg::Vec4d(0.3f, 0.3f, 0.3f, 1.0f ));
//                _light->setDiffuse( _sunDiffuse[_sceneType] );
//                _light->setSpecular(osg::Vec4d( 0.1f, 0.1f, 0.1f, 1.0f ) );
//                _light->setPosition( osg::Vec4f(_sunPositions[_sceneType], 1.f) ); // point light
//
//                _scene->addChild( lightSource );
//                _scene->addChild( _oceanScene.get() );
//                //_scene->addChild( sunDebug(_sunPositions[CLOUDY]) );
//            }
//        }
//    }
//
//    osgOcean::OceanTechnique* getOceanSurface( void )
//    {
//        return _oceanSurface.get();
//    }
//
//    osg::Group* getScene(void){
//        return _scene.get();
//    }
//
//    osgOcean::OceanScene* getOceanScene()
//    {
//        return _oceanScene.get();
//    }
//
//    void changeScene( SCENE_TYPE type )
//    {
//        _sceneType = type;
//
//        _cubemap = loadCubeMapTextures( _cubemapDirs[_sceneType] );
//        _skyDome->setCubeMap( _cubemap.get() );
//        _oceanSurface->setEnvironmentMap( _cubemap.get() );
//        _oceanSurface->setLightColor( _lightColors[type] );
//
//        _oceanScene->setAboveWaterFog(0.0012f, _fogColors[_sceneType] );
//        _oceanScene->setUnderwaterFog(0.002f,  _waterFogColors[_sceneType] );
//        _oceanScene->setUnderwaterDiffuse( _underwaterDiffuse[_sceneType] );
//        _oceanScene->setUnderwaterAttenuation( _underwaterAttenuations[_sceneType] );
//        
//        osg::Vec3f sunDir = -_sunPositions[_sceneType];
//        sunDir.normalize();
//
//        _oceanScene->setSunDirection( sunDir );
//
//        _light->setPosition( osg::Vec4f(_sunPositions[_sceneType],1.f) );
//        _light->setDiffuse( _sunDiffuse[_sceneType] ) ;
//    }
//
//    osg::ref_ptr<osg::TextureCubeMap> loadCubeMapTextures( const std::string& dir )
//    {
//        enum {POS_X, NEG_X, POS_Y, NEG_Y, POS_Z, NEG_Z};
//
//        std::string filenames[6];
//
//        filenames[POS_X] = "resources/textures/" + dir + "/east.png";
//        filenames[NEG_X] = "resources/textures/" + dir + "/west.png";
//        filenames[POS_Z] = "resources/textures/" + dir + "/north.png";
//        filenames[NEG_Z] = "resources/textures/" + dir + "/south.png";
//        filenames[POS_Y] = "resources/textures/" + dir + "/down.png";
//        filenames[NEG_Y] = "resources/textures/" + dir + "/up.png";
//
//        osg::ref_ptr<osg::TextureCubeMap> cubeMap = new osg::TextureCubeMap;
//        cubeMap->setInternalFormat(GL_RGBA);
//
//        cubeMap->setFilter( osg::Texture::MIN_FILTER,    osg::Texture::LINEAR_MIPMAP_LINEAR);
//        cubeMap->setFilter( osg::Texture::MAG_FILTER,    osg::Texture::LINEAR);
//        cubeMap->setWrap  ( osg::Texture::WRAP_S,        osg::Texture::CLAMP_TO_EDGE);
//        cubeMap->setWrap  ( osg::Texture::WRAP_T,        osg::Texture::CLAMP_TO_EDGE);
//
//        cubeMap->setImage(osg::TextureCubeMap::NEGATIVE_X, osgDB::readImageFile( filenames[NEG_X] ) );
//        cubeMap->setImage(osg::TextureCubeMap::POSITIVE_X, osgDB::readImageFile( filenames[POS_X] ) );
//        cubeMap->setImage(osg::TextureCubeMap::NEGATIVE_Y, osgDB::readImageFile( filenames[NEG_Y] ) );
//        cubeMap->setImage(osg::TextureCubeMap::POSITIVE_Y, osgDB::readImageFile( filenames[POS_Y] ) );
//        cubeMap->setImage(osg::TextureCubeMap::NEGATIVE_Z, osgDB::readImageFile( filenames[NEG_Z] ) );
//        cubeMap->setImage(osg::TextureCubeMap::POSITIVE_Z, osgDB::readImageFile( filenames[POS_Z] ) );
//
//        return cubeMap;
//    }
//
//    osg::Geode* sunDebug( const osg::Vec3f& position )
//    {
//        osg::ShapeDrawable* sphereDraw = new osg::ShapeDrawable( new osg::Sphere( position, 15.f ) );
//        sphereDraw->setColor(osg::Vec4f(1.f,0.f,0.f,1.f));
//        
//        osg::Geode* sphereGeode = new osg::Geode;
//        sphereGeode->addDrawable( sphereDraw );
//        
//        return sphereGeode;
//    }
//
//    osg::Vec4f intColor(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255 )
//    {
//        float div = 1.f/255.f;
//        return osg::Vec4f( div*(float)r, div*(float)g, div*float(b), div*(float)a );
//    }
//};















OsgHandler* OsgHandler::_singletonInstance = NULL;

/***********************************************************
use to restrict optimizer 
***********************************************************/
struct OptimizationAllowedCallback : public osgUtil::Optimizer::IsOperationPermissibleForObjectCallback
{
	virtual bool isOperationPermissibleForObjectImplementation (const osgUtil::Optimizer *optimizer, 
												const osg::Node *node, unsigned int option) const 
	{
		if(node->getUserData())
			return false;

		return osgUtil::Optimizer::IsOperationPermissibleForObjectCallback::
			isOperationPermissibleForObjectImplementation(optimizer, node, option);
	}

};


/***********************************************************
use to make sure that we share texture file and dont it multiple times
***********************************************************/
class FileReadOnceCallback : public osgDB::Registry::ReadFileCallback
{
private:
	typedef std::map<std::string,osg::ref_ptr<osg::Object> > PathPointerMap;
	PathPointerMap pathpointermap;

public:

	virtual osgDB::ReaderWriter::ReadResult readImage(const std::string& filename, 
											const osgDB::ReaderWriter::Options* options)
	{
		PathPointerMap::iterator itr=pathpointermap.find(filename);
		if (itr==pathpointermap.end())
		{
			osgDB::ReaderWriter::ReadResult result;
			result=osgDB::Registry::instance()->readImageImplementation(filename,options);
			osg::ref_ptr<osg::Image> refobj=result.getImage();
			if (result.validImage()) pathpointermap[filename]=refobj;
			return result;
		}
		else
		{
			osgDB::ReaderWriter::ReadResult result(itr->second.get(),osgDB::ReaderWriter::ReadResult::FILE_LOADED);
			return itr->second.get();
		}
	}
};








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
	_cameraType(0), _targetx(10), _targety(10), _targetz(10),
	_viewer(NULL), _root(NULL), _rootNode3d(NULL), _sceneRootNode(NULL), _translNode(NULL),
	_viewportX(800), _viewportY(600), _displayShadow(false), 
	_current_clip_layer(-1), _autoCameraType(1), _azimut(0)
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
#ifdef _USE_QT_EDITOR_
void OsgHandler::Initialize(const std::string &WindowName, const std::string &DataPath,
														boost::shared_ptr<GuiHandler> GuiH,
														boost::shared_ptr<EditorHandler> editorH)
#else
void OsgHandler::Initialize(const std::string &WindowName, const std::string &DataPath,
														boost::shared_ptr<GuiHandler> GuiH)
#endif
{
	osgDB::setDataFilePathList(DataPath);

    // set the osgDB::Registy read file callback to catch all requests for reading files.
    osgDB::Registry::instance()->setReadFileCallback(new FileReadOnceCallback());


	LogHandler::getInstance()->LogToFile("Initializing graphics window...");




	// get data from configuration file
	{
		LogHandler::getInstance()->LogToFile("Initializing camera...");
		int ctype;
		double camdistance, camzenit;
		ConfigurationManager::GetInstance()->GetDouble("Display.Camera.Distance", camdistance);
		ConfigurationManager::GetInstance()->GetDouble("Display.Camera.Zenit", camzenit);
		ConfigurationManager::GetInstance()->GetInt("Display.Camera.CameraType", ctype);
		ToggleCameraType(ctype);
		SetCameraDistance(camdistance);
		SetCameraZenit(camzenit);


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
	_viewer->setKeyEventSetsDone(0);



    // create the window to draw to.
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->x = _posX;
    traits->y = _posY;
    traits->width = _resX;
    traits->height = _resY;
#ifdef _USE_QT_EDITOR_
    traits->windowDecoration = false;
#else
    traits->windowDecoration = true;
#endif
    traits->doubleBuffer = true;
    traits->sharedContext = 0;
	traits->windowName = WindowName;
	traits->useCursor = false;

#ifdef _USE_QT_EDITOR_
	{
        GraphicsWindowQt *qtwin = new GraphicsWindowQt(traits.get());
		_viewer->getCamera()->setGraphicsContext(qtwin);

		editorH->SetOsgWindow(qtwin);
	}
#else
	{
		osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
		_gw = dynamic_cast<osgViewer::GraphicsWindow*>(gc.get());
		if (!_gw)
			return;

		_viewer->getCamera()->setGraphicsContext(gc.get());
	}
#endif


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
	_translNode->setName("TranslationNode");


	_rootNode3d->addChild(_translNode);
	_rootNode3d->setName("Root3D");


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
	_clipNode->setName("Clipnode");

	_eventH = new OsgEventHandler();
	//TODO remove static keys and make it configurable
	std::map<LbanetKey, int> kmap;
	kmap[LbanetKey_Forward] = osgGA::GUIEventAdapter::KEY_Up;
	kmap[LbanetKey_Backward] = osgGA::GUIEventAdapter::KEY_Down;
	kmap[LbanetKey_Left] = osgGA::GUIEventAdapter::KEY_Left;
	kmap[LbanetKey_Right] = osgGA::GUIEventAdapter::KEY_Right;
	kmap[LbanetKey_StrafeL] = 'l';
	kmap[LbanetKey_StrafeR] = 'm';
	kmap[LbanetKey_Up] = osgGA::GUIEventAdapter::KEY_Page_Up;
	kmap[LbanetKey_Down] = osgGA::GUIEventAdapter::KEY_Page_Down;
	kmap[LbanetKey_Action] = osgGA::GUIEventAdapter::KEY_Space;
	kmap[LbanetKey_NAction] = 'w';
	kmap[LbanetKey_Weapon] = osgGA::GUIEventAdapter::KEY_Alt_L;
	kmap[LbanetKey_Stance1] = osgGA::GUIEventAdapter::KEY_F1;
	kmap[LbanetKey_Stance2] = osgGA::GUIEventAdapter::KEY_F2;
	kmap[LbanetKey_Stance3] = osgGA::GUIEventAdapter::KEY_F3;
	kmap[LbanetKey_Stance4] = osgGA::GUIEventAdapter::KEY_F4;
	kmap[LbanetKey_CenterCamera] = osgGA::GUIEventAdapter::KEY_Shift_R;
	kmap[LbanetKey_Shortcut0] = '0';
	kmap[LbanetKey_Shortcut1] = '1';
	kmap[LbanetKey_Shortcut2] = '2';
	kmap[LbanetKey_Shortcut3] = '3';
	kmap[LbanetKey_Shortcut4] = '4';
	kmap[LbanetKey_Shortcut5] = '5';
	kmap[LbanetKey_Shortcut6] = '6';
	kmap[LbanetKey_Shortcut7] = '7';
	kmap[LbanetKey_Shortcut8] = '8';
	kmap[LbanetKey_Shortcut9] = '9';

	_eventH->SetKeyMap(kmap);

	// add the stats handler
	_viewer->addEventHandler(_eventH );

	osgViewer::StatsHandler *sth = new osgViewer::StatsHandler;
	sth->setKeyEventTogglesOnScreenStats(osgGA::GUIEventAdapter::KEY_F11);
	_viewer->addEventHandler(sth);

	osgViewer::ScreenCaptureHandler *screenshoth = new osgViewer::ScreenCaptureHandler;
	screenshoth->setKeyEventTakeScreenShot(osgGA::GUIEventAdapter::KEY_F10);
	screenshoth->setKeyEventToggleContinuousCapture(-1);
	_viewer->addEventHandler(screenshoth);


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
		ConfigurationManager::GetInstance()->SetInt("Display.Camera.CameraType", _cameraType);

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
void OsgHandler::Resize(int resX, int resY)
{
	Resize(resX, resY, _isFullscreen);
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

		#ifndef _USE_QT_EDITOR_
		ConfigurationManager::GetInstance()->SetInt("Display.Screen.ScreenResolutionX", _resX);
		ConfigurationManager::GetInstance()->SetInt("Display.Screen.ScreenResolutionY", _resY);
		ConfigurationManager::GetInstance()->SetBool("Display.Screen.Fullscreen", _isFullscreen);
		#endif
	}
}


/***********************************************************
toggle fullscreen or windowed mode
***********************************************************/
void OsgHandler::ToggleFullScreen()
{
	_isFullscreen = !_isFullscreen;
	ResetScreen();

	ConfigurationManager::GetInstance()->SetBool("Display.Screen.Fullscreen", _isFullscreen);
}



/***********************************************************
called when screen is resized
***********************************************************/
void OsgHandler::Resized(int resX, int resY)
{
	_resX = resX;
	_resY = resY;
	_viewportX = resX;
	_viewportY = resY;

	ResetCameraProjectiomMatrix();
	_HUDcam->setProjectionMatrix(osg::Matrix::ortho2D(0, _viewportX, 0, _viewportY));
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
			#ifndef _USE_QT_EDITOR_
			window->setWindowDecoration(false);
			window->setWindowRectangle(0, 0, screenWidth, screenHeight);
			#endif
			_viewportX = screenWidth;
			_viewportY = screenHeight;
			
		}
		else
		{
			#ifndef _USE_QT_EDITOR_
			window->setWindowDecoration(true);
			window->setWindowRectangle(_posX, _posY, _resX, _resY);
			#endif
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

	if(_cameraType > 1 || ((_cameraType == 0) && (_autoCameraType > 1)))
	{
		_viewer->getCamera()->setProjectionMatrixAsPerspective(_fov,_viewportX/(double)_viewportY, 0.01,2000);
	}
	else
	{
		float factorX = _viewportX * 0.0001;
		float factorY = _viewportY * 0.0001;

		_viewer->getCamera()->setProjectionMatrixAsOrtho(-factorX*_distance, factorX*_distance,
															-factorY*_distance, factorY*_distance,
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
		if(_cameraType > 1 || ((_cameraType == 0) && (_autoCameraType > 1)))
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

	ResetCameraAzimut();
}



/***********************************************************
set or reset camera Azimut
***********************************************************/
void OsgHandler::ResetCameraAzimut()
{
	if(_rootNode3d)
	{
		if(_cameraType == 3 || ((_cameraType == 0) && (_autoCameraType == 3)))
		{
			_rootNode3d->setAttitude(osg::Quat(osg::DegreesToRadians(180-_azimut), osg::Vec3(0,1,0)));
		}
		else
		{
			_rootNode3d->setAttitude(osg::Quat(osg::DegreesToRadians(-45.0), osg::Vec3(0,1,0)));
		}
	}
}


/***********************************************************
set if the view is perspective or ortho
***********************************************************/
void OsgHandler::ToggleCameraType(int cameraType)
{
	if(_cameraType != cameraType)
	{
		_cameraType = cameraType;

		double distance = 110;
		if(_cameraType == 2)
			distance = 15;
		if(_cameraType == 3)
			distance = 20;
		ResetCameraDistances(distance);

		ConfigurationManager::GetInstance()->SetInt("Display.Camera.CameraType", _cameraType);
	}
}


/***********************************************************
set if the view is perspective or ortho
***********************************************************/
void OsgHandler::ToggleAutoCameraType(int cameraType)
{
	if(_autoCameraType != cameraType)
	{
		_autoCameraType = cameraType;
		if(_cameraType == 0)
		{
			double distance = 110;
			if(_autoCameraType == 2)
				distance = 15;
			if(_autoCameraType == 3)
				distance = 20;
			ResetCameraDistances(distance);
		}
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
void OsgHandler::SetCameraDistance(double distance, bool forced)
{
	if(forced || _distance != distance)
	{
		_distance = distance;
		int maxdistance = 150;
		if(_cameraType == 1 || ((_cameraType == 0) && (_autoCameraType == 1)))
			maxdistance = 1000;

		int mindistance = 30;
		if(_cameraType > 1 || ((_cameraType == 0) && (_autoCameraType > 1)))
			mindistance = 4;


		if(_distance < mindistance)
			_distance = mindistance;
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
void OsgHandler::SetCameraZenit(double zenit, bool forced)
{
	if(forced || _zenit != zenit)
	{
		_zenit = zenit;

		int maxdistance = 70;

		int mindistance = 10;
		if(_cameraType > 2 || ((_cameraType == 0) && (_autoCameraType > 2)))
			mindistance = -70;


		if(_zenit < mindistance)
			_zenit = mindistance;
		if(_zenit > maxdistance)
			_zenit = maxdistance;

		ResetCameraTransform();
	}
}


/***********************************************************
set camera azimut
***********************************************************/
void OsgHandler::SetCameraAzimut(double azimut, bool forced)
{
	if(forced || _azimut != azimut)
	{
		_azimut = azimut;
		if(_azimut < 0)
			_azimut += 360;
		if(_azimut > 360)
			_azimut -= 360;

		ResetCameraAzimut();
	}
}


/***********************************************************
delta update camera zenit
***********************************************************/
void OsgHandler::DeltaUpdateCameraAzimut(double delta)
{
	SetCameraAzimut(_azimut+delta);
}



/***********************************************************
reset camera distances when changeing cam type
***********************************************************/
void OsgHandler::ResetCameraDistances(double distance)
{
	SetCameraDistance(distance, true);
	SetCameraZenit(_zenit, true);
	SetCameraAzimut(_azimut, true);
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
	_lightNode->setName("LightNode");

	// check if we use shadow or not
	if(_displayShadow)
	{
		osg::ref_ptr<osgShadow::ShadowedScene> shadowscene = new osgShadow::ShadowedScene();
		shadowscene->setReceivesShadowTraversalMask(ReceivesShadowTraversalMask);
		shadowscene->setCastsShadowTraversalMask(CastsShadowTraversalMask);

		osg::ref_ptr<osgShadow::StandardShadowMap> shmap = new osgShadow::StandardShadowMap();
		//osg::ref_ptr<osgShadow::MinimalShadowMap> shmap = new osgShadow::MinimalShadowMap();
		shadowscene->setShadowTechnique(shmap.get());
		_sceneRootNode = shadowscene;
	}
	else
	{
		_sceneRootNode = new osg::Group();	
	}
	_sceneRootNode->setName("SceneRootNode");

	_lightNode->addChild(_sceneRootNode);


	if(_sceneNoLightRootNode)
		_translNode->removeChild(_sceneNoLightRootNode);

	_sceneNoLightRootNode = new osg::Group();	
	_sceneNoLightRootNode->setName("SceneRootNodeNoLight");
	_translNode->addChild(_sceneNoLightRootNode);

 //   osg::ref_ptr<osgParticle::PrecipitationEffect> precipitationEffect = new osgParticle::PrecipitationEffect;

 //   float intensity = 1.0;
 //  // precipitationEffect->snow(intensity);
 //   precipitationEffect->rain(intensity);

 //   precipitationEffect->setParticleSize(0.01);

 //   precipitationEffect->setParticleColor(osg::Vec4(1,1,1,0.5));

 //   precipitationEffect->setWind(osg::Vec3(0, -10 , 0));
	////precipitationEffect->setParticleSpeed(0);
	////precipitationEffect->setNearTransition(1);
 //   //precipitationEffect->setFarTransition(1);
	////precipitationEffect->setMaximumParticleDensity(1);
	////precipitationEffect->setCellSize(osg::Vec3(1, 1, 1)); 


	//precipitationEffect->getFog()->setDensity(0.1);
 //   precipitationEffect->getFog()->setColor(osg::Vec4(1,1,1,0.5));
	//precipitationEffect->setUseFarLineSegments(true);  
 //   //_viewer.getCamera()->setClearColor( precipitationEffect->getFog()->getColor() );

	//_sceneNoLightRootNode->addChild(precipitationEffect.get());
	

	// grid to check dimensions
	//{
	//	osg::ref_ptr<osg::Geode> linesgeode = new osg::Geode();

	//	
	//	{
	//		osg::ref_ptr<osg::Geometry> myGeometry = new osg::Geometry();
	//		osg::Vec3Array* myVertices = new osg::Vec3Array;
	//		osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);

	//		for(int i=0; i<200; ++i)
	//		{
	//			myVertices->push_back(osg::Vec3(0, i, 0));
	//			myVertices->push_back(osg::Vec3(0, i, 200));

	//			myVertices->push_back(osg::Vec3(0, i, 0));
	//			myVertices->push_back(osg::Vec3(200, i, 0));

	//			myVertices->push_back(osg::Vec3(0, 0, i));
	//			myVertices->push_back(osg::Vec3(0, 200, i));

	//			myVertices->push_back(osg::Vec3(i, 0, 0));
	//			myVertices->push_back(osg::Vec3(i, 200, 0));
	//		}

	//		for(int i=0; i<1600; ++i)
	//			myprimitive->push_back(i);


	//		osg::Vec4Array* mycolors = new osg::Vec4Array;
	//		mycolors->push_back(osg::Vec4(1,1,1,1));
	//		myGeometry->setColorArray(mycolors);
	//		myGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	//		myGeometry->addPrimitiveSet(myprimitive);
	//		myGeometry->setVertexArray( myVertices ); 
	//		linesgeode->addDrawable(myGeometry.get());
	//	}

	//	osg::StateSet* stateSet = linesgeode->getOrCreateStateSet();
	//	stateSet->setMode(GL_TEXTURE_2D,osg::StateAttribute::OFF);
	//	stateSet->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

	//	_sceneNoLightRootNode->addChild(linesgeode);
	//}



	//set default light
	LbaMainLightInfo Linf;
	Linf.UseLight = false;
	SetLight(Linf);






	//test osgocean

 //   float windx = 1.1f, windy = 1.1f;
 //   osg::Vec2f windDirection(windx, windy);

 //   float windSpeed = 12.f;
 //   float depth = 1000.f;
 //   float reflectionDamping = 0.35f;
 //   float scale = 1e-8;
 //   bool isChoppy = true;
	//float choppyFactor = 2.5f;
 //   float crestFoamHeight = 2.2f;
 //   double oceanSurfaceHeight = 0.0f;
 //   bool testCollision = false;
 //   bool disableShaders = false;


 //   osgOcean::ShaderManager::instance().enableShaders(true);
 //   osg::ref_ptr<SceneModel> scene = new SceneModel(windDirection, windSpeed, depth, reflectionDamping, scale, isChoppy, choppyFactor, crestFoamHeight);
	//_sceneNoLightRootNode-> addChild(scene->getScene());
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
osg::ref_ptr<osg::MatrixTransform> OsgHandler::AddActorNode(osg::ref_ptr<osg::Node> node,
																bool UseLight, bool CastShadow)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Added Node to display engine");
	#endif

	if(CastShadow)
	{
		node->setNodeMask(ReceivesShadowTraversalMask | CastsShadowTraversalMask);
	}
	else
	{
		node->setNodeMask(ReceivesShadowTraversalMask);
	}

	osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform();
	transform->addChild(node);

	if(UseLight && _sceneRootNode)
		_sceneRootNode->addChild(transform);

	if(!UseLight && _sceneNoLightRootNode)
		_sceneNoLightRootNode->addChild(transform);

	return transform;
}


/***********************************************************
add an empty actor to the display list - return handler to actor position
***********************************************************/
osg::ref_ptr<osg::MatrixTransform> OsgHandler::AddEmptyActorNode(bool WithLight)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Added empty Node to display engine");
	#endif

	osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform();

	if(WithLight && _sceneRootNode)
		_sceneRootNode->addChild(transform);

	if(!WithLight && _sceneNoLightRootNode)
		_sceneNoLightRootNode->addChild(transform);



	return transform;
}


/***********************************************************
readd a removed actor to the display list
***********************************************************/
void OsgHandler::ReAddActorNode(osg::ref_ptr<osg::Node> node, bool WithLight)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("ReAdded Node to display engine");
	#endif

	if(WithLight && _sceneRootNode)
		_sceneRootNode->addChild(node);

	if(!WithLight && _sceneNoLightRootNode)
		_sceneNoLightRootNode->addChild(node);
}


/***********************************************************
remove actor from the graph
***********************************************************/
void OsgHandler::RemoveActorNode(osg::ref_ptr<osg::Node> node, bool WithLight)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Removed Node from display engine");
	#endif

	if(WithLight && _sceneRootNode)
		_sceneRootNode->removeChild(node);

	if(!WithLight && _sceneNoLightRootNode)
		_sceneNoLightRootNode->removeChild(node);
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
create sprite object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgHandler::CreateSpriteObject(const std::string & spritefile, 
															float colorR, float colorG, float colorB, float colorA,
															boost::shared_ptr<DisplayTransformation> Tr,
															bool UseLight, bool CastShadow,
															const LbaNet::ObjectExtraInfo &extrainfo,
															const LbaNet::LifeManaInfo &lifeinfo)
{
	osg::ref_ptr<osg::MatrixTransform> resnode = CreateSpriteObject(spritefile, 
												colorR, colorG, colorB, colorA, Tr,	UseLight, CastShadow);

	return boost::shared_ptr<DisplayObjectHandlerBase>(new OsgObjectHandler(resnode, UseLight, extrainfo, lifeinfo));
}





/***********************************************************
create simple display object
***********************************************************/
osg::ref_ptr<osg::MatrixTransform> OsgHandler::CreateSpriteObject(const std::string & spritefile, 
											float colorR, float colorG, float colorB, float colorA,
											boost::shared_ptr<DisplayTransformation> Tr,
											bool UseLight, bool CastShadow)
{
	// create geode
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	geode->addDrawable(geometry); 

	// Specify the vertices:
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	vertices->push_back( osg::Vec3(-1.5, 0, 0) );
	vertices->push_back( osg::Vec3(1.5, 0, 0) );
	vertices->push_back( osg::Vec3(1.5, 6, 0) ); 
	vertices->push_back( osg::Vec3(-1.5, 6, 0) ); 
	geometry->setVertexArray( vertices );

	// specify the base:
	osg::ref_ptr<osg::DrawElementsUInt> base = 
	new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	base->push_back(0);
	base->push_back(1);
	base->push_back(2);
	base->push_back(3);
	geometry->addPrimitiveSet(base);

	// specify the color:
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(colorR, colorG, colorB, colorA) ); 
	geometry->setColorArray(colors);
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	// specify thetexture coordinates:
	osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array(5);
	(*texcoords)[0].set(0, 0); 
	(*texcoords)[1].set(1, 0); 
	(*texcoords)[2].set(1, 1); 
	(*texcoords)[3].set(0, 1); 
	geometry->setTexCoordArray(0,texcoords);




	// Declare a group to act as root node of a scene:
	osg::ref_ptr<osg::Group> resnode = new osg::Group();
	resnode->addChild(geode);

	osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();

	if(colorA < 1.0f)
	{
		stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
		stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
		stateSet->setRenderBinDetails( 5000, "RenderBin");
	}

	//specify normal:
	if(!UseLight)
		stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	else
		osgUtil::SmoothingVisitor::smooth(*(geometry.get()));


	// attach texture to geometry:
	osg::ref_ptr<osg::Image> klnFace = osgDB::readImageFile(spritefile);
	if (klnFace)
	{
		osg::ref_ptr<osg::Texture2D> KLN89FaceTexture = new osg::Texture2D;
		KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC); 
		KLN89FaceTexture->setImage(klnFace);

		KLN89FaceTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
		KLN89FaceTexture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);

		stateSet->setTextureAttributeAndModes(0, KLN89FaceTexture, osg::StateAttribute::ON);
	}


	if(Tr)
	{
		osg::ref_ptr<osg::PositionAttitudeTransform> transform = new osg::PositionAttitudeTransform();
		transform->setPosition(osg::Vec3d(Tr->translationX, Tr->translationY, Tr->translationZ));
		transform->setAttitude(osg::Quat(Tr->rotation.X, Tr->rotation.Y, Tr->rotation.Z, Tr->rotation.W));
		transform->setScale(osg::Vec3d(Tr->scaleX, Tr->scaleY, Tr->scaleZ));

		transform->addChild(resnode);
		resnode = transform;
	}
	
	osg::ref_ptr<osg::MatrixTransform> mat = AddActorNode(resnode, UseLight, CastShadow);

	return mat;
}


/***********************************************************
create simple display object
***********************************************************/
osg::ref_ptr<osg::MatrixTransform> OsgHandler::CreateSimpleObject(const std::string & filename,
														boost::shared_ptr<DisplayTransformation> Tr,
														bool UseLight, bool CastShadow)
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

	osg::ref_ptr<osg::MatrixTransform> mat = AddActorNode(resnode, UseLight, CastShadow);

	return mat;
}


/***********************************************************
create simple display object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgHandler::CreateSimpleObject(const std::string & filename,
														boost::shared_ptr<DisplayTransformation> Tr,
														bool UseLight, bool CastShadow,
														const LbaNet::ObjectExtraInfo &extrainfo,
														const LbaNet::LifeManaInfo &lifeinfo)
{
	osg::ref_ptr<osg::MatrixTransform> resnode = CreateSimpleObject(filename, Tr,	UseLight, CastShadow);
	return boost::shared_ptr<DisplayObjectHandlerBase>(new OsgObjectHandler(resnode, UseLight, extrainfo, lifeinfo));
}




/***********************************************************
create capsule object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgHandler::CreateSphereObject(float radius, 
														float colorR, float colorG, float colorB, float colorA,
														boost::shared_ptr<DisplayTransformation> Tr,
														const LbaNet::ObjectExtraInfo &extrainfo,
														const LbaNet::LifeManaInfo &lifeinfo)
{
	osg::ref_ptr<osg::Group> resnode = new osg::Group();

	// create capsule
	osg::ref_ptr<osg::Geode> capsuleGeode(new osg::Geode());
	osg::ref_ptr<osg::Sphere> caps(new osg::Sphere(osg::Vec3(0,0,0),radius));
	osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
	capsdraw->setColor(osg::Vec4(colorR, colorG, colorB, colorA));
	capsuleGeode->setName("Colorable");
	capsuleGeode->addDrawable(capsdraw);
	resnode->addChild(capsuleGeode);

	osg::StateSet* stateset = capsuleGeode->getOrCreateStateSet();
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
	stateset->setRenderBinDetails( 9000, "RenderBin");

	if(Tr)
	{
		osg::ref_ptr<osg::PositionAttitudeTransform> transform = new osg::PositionAttitudeTransform();
		transform->setPosition(osg::Vec3d(Tr->translationX, Tr->translationY, Tr->translationZ));
		transform->setAttitude(osg::Quat(Tr->rotation.X, Tr->rotation.Y, Tr->rotation.Z, Tr->rotation.W));
		transform->setScale(osg::Vec3d(Tr->scaleX, Tr->scaleY, Tr->scaleZ));

		transform->addChild(resnode);
		resnode = transform;
	}
	
	osg::ref_ptr<osg::MatrixTransform> mat = AddActorNode(resnode, false, false);
	return boost::shared_ptr<DisplayObjectHandlerBase>(new OsgObjectHandler(mat, false, extrainfo, lifeinfo));
}



/***********************************************************
create capsule object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgHandler::CreateCapsuleObject(float radius, float height, 
														float colorR, float colorG, float colorB, float colorA,
														boost::shared_ptr<DisplayTransformation> Tr,
														const LbaNet::ObjectExtraInfo &extrainfo,
														const LbaNet::LifeManaInfo &lifeinfo)
{
	osg::ref_ptr<osg::Group> resnode = new osg::Group();

	// create capsule
	osg::ref_ptr<osg::Geode> capsuleGeode(new osg::Geode());
	osg::ref_ptr<osg::Capsule> caps(new osg::Capsule(osg::Vec3(0,0,0),radius,height));
	osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
	capsdraw->setColor(osg::Vec4(colorR, colorG, colorB, colorA));
	capsuleGeode->setName("Colorable");
	capsuleGeode->addDrawable(capsdraw);
	resnode->addChild(capsuleGeode);

	osg::StateSet* stateset = capsuleGeode->getOrCreateStateSet();
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
	stateset->setRenderBinDetails( 9000, "RenderBin");

	if(Tr)
	{
		osg::ref_ptr<osg::PositionAttitudeTransform> transform = new osg::PositionAttitudeTransform();
		transform->setPosition(osg::Vec3d(Tr->translationX, Tr->translationY, Tr->translationZ));
		transform->setAttitude(osg::Quat(Tr->rotation.X, Tr->rotation.Y, Tr->rotation.Z, Tr->rotation.W));
		transform->setScale(osg::Vec3d(Tr->scaleX, Tr->scaleY, Tr->scaleZ));

		transform->addChild(resnode);
		resnode = transform;
	}
	
	osg::ref_ptr<osg::MatrixTransform> mat = AddActorNode(resnode, false, false);
	return boost::shared_ptr<DisplayObjectHandlerBase>(new OsgObjectHandler(mat, false, extrainfo, lifeinfo));
}


/***********************************************************
create box object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgHandler::CreateBoxObject(float sizex, float sizey, float sizez, 
														float colorR, float colorG, float colorB, float colorA,
														boost::shared_ptr<DisplayTransformation> Tr,
														const LbaNet::ObjectExtraInfo &extrainfo,
														const LbaNet::LifeManaInfo &lifeinfo)
{
	osg::ref_ptr<osg::Group> resnode = new osg::Group();

	// create capsule
	osg::ref_ptr<osg::Geode> capsuleGeode(new osg::Geode());
	osg::ref_ptr<osg::Box> caps(new osg::Box(osg::Vec3(0,(sizey/2),0), sizex, sizey, sizez));
	osg::ref_ptr<osg::ShapeDrawable> capsdraw = new osg::ShapeDrawable(caps);
	capsdraw->setColor(osg::Vec4(colorR, colorG, colorB, colorA));
	capsuleGeode->setName("Colorable");
	capsuleGeode->addDrawable(capsdraw);
	resnode->addChild(capsuleGeode);

    osg::StateSet* stateset = capsuleGeode->getOrCreateStateSet();
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);
	stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
	stateset->setRenderBinDetails( 9000, "RenderBin");

	if(Tr)
	{
		osg::ref_ptr<osg::PositionAttitudeTransform> transform = new osg::PositionAttitudeTransform();
		transform->setPosition(osg::Vec3d(Tr->translationX, Tr->translationY, Tr->translationZ));
		transform->setAttitude(osg::Quat(Tr->rotation.X, Tr->rotation.Y, Tr->rotation.Z, Tr->rotation.W));
		transform->setScale(osg::Vec3d(Tr->scaleX, Tr->scaleY, Tr->scaleZ));

		transform->addChild(resnode);
		resnode = transform;
	}
	
	osg::ref_ptr<osg::MatrixTransform> mat = AddActorNode(resnode, false, false);
	return boost::shared_ptr<DisplayObjectHandlerBase>(new OsgObjectHandler(mat, false, extrainfo, lifeinfo));
}



/***********************************************************
create box object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgHandler::CreateCrossObject(float size,  
														float colorR, float colorG, float colorB, float colorA,
														boost::shared_ptr<DisplayTransformation> Tr,
														const LbaNet::ObjectExtraInfo &extrainfo,
														const LbaNet::LifeManaInfo &lifeinfo)
{
	osg::ref_ptr<osg::Group> resnode = new osg::Group();


	// create orientation line
	osg::Geode* lineGeode = new osg::Geode();
	osg::Geometry* lineGeometry = new osg::Geometry();
	lineGeode->addDrawable(lineGeometry); 

	osg::Vec3Array* lineVertices = new osg::Vec3Array();
	lineVertices->push_back( osg::Vec3( -size/2, 0, 0) );
	lineVertices->push_back( osg::Vec3(size/2, 0, 0) );
	lineVertices->push_back( osg::Vec3(0 , 0, -size/2) );
	lineVertices->push_back( osg::Vec3(0 , 0, size/2) );
	lineGeometry->setVertexArray( lineVertices ); 

	osg::Vec4Array* linecolor = new osg::Vec4Array();
	linecolor->push_back( osg::Vec4( colorR, colorG, colorB, colorA) );
	lineGeometry->setColorArray(linecolor);
	lineGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	osg::DrawElementsUInt* dunit = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
	dunit->push_back(0);
	dunit->push_back(1);
	dunit->push_back(2);
	dunit->push_back(3);
	lineGeometry->addPrimitiveSet(dunit); 
	resnode->addChild(lineGeode);

    osg::StateSet* stateset = lineGeometry->getOrCreateStateSet();
    osg::LineWidth* linewidth = new osg::LineWidth();

    linewidth->setWidth(4.0f);
    stateset->setAttributeAndModes(linewidth,osg::StateAttribute::ON);
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF);
	stateset->setRenderingHint( osg::StateSet::OPAQUE_BIN );
	stateset->setRenderBinDetails( 9000, "RenderBin");

	if(Tr)
	{
		osg::ref_ptr<osg::PositionAttitudeTransform> transform = new osg::PositionAttitudeTransform();
		transform->setPosition(osg::Vec3d(Tr->translationX, Tr->translationY, Tr->translationZ));
		transform->setAttitude(osg::Quat(Tr->rotation.X, Tr->rotation.Y, Tr->rotation.Z, Tr->rotation.W));
		transform->setScale(osg::Vec3d(Tr->scaleX, Tr->scaleY, Tr->scaleZ));

		transform->addChild(resnode);
		resnode = transform;
	}
	
	osg::ref_ptr<osg::MatrixTransform> mat = AddActorNode(resnode, false, false);
	return boost::shared_ptr<DisplayObjectHandlerBase>(new OsgObjectHandler(mat, false, extrainfo, lifeinfo));
}


/***********************************************************
create PAT
***********************************************************/
osg::ref_ptr<osg::PositionAttitudeTransform> OsgHandler::CreatePAT(boost::shared_ptr<DisplayTransformation> Tr)
{
	if(Tr)
	{
		osg::ref_ptr<osg::PositionAttitudeTransform> transform = new osg::PositionAttitudeTransform();
		transform->setPosition(osg::Vec3d(Tr->translationX, Tr->translationY, Tr->translationZ));
		transform->setAttitude(osg::Quat(Tr->rotation.X, Tr->rotation.Y, Tr->rotation.Z, Tr->rotation.W));
		transform->setScale(osg::Vec3d(Tr->scaleX, Tr->scaleY, Tr->scaleZ));

		return transform;
	}

	return osg::ref_ptr<osg::PositionAttitudeTransform>();
}


/***********************************************************
optimize the scene
***********************************************************/
void OsgHandler::OptimizeScene()
{
    // run optimization over the scene graph
    osgUtil::Optimizer optimizer;
	optimizer.setIsOperationPermissibleForObjectCallback(new OptimizationAllowedCallback());
    optimizer.optimize(_rootNode3d);
}
