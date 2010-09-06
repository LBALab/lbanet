#include <osgDB/FileUtils>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>

#include <osgAnimation/MorphGeometry>
#include <osgAnimation/BasicAnimationManager>
#include <osgUtil/Optimizer>

#include <osg/Light>
#include <osg/LightSource>
#include <osg/StateAttribute>
#include <osg/Point>
#include <osgUtil/SmoothingVisitor>
#include <osg/ShapeDrawable>

#include	"SceneExterior.h"

#include <IL/il.h>
#include <IL/ilu.h>

int main( int argc, char **argv )

{
	ilInit();
	iluInit();

	std::vector<std::string> listile;
	//listile.push_back("ASCENCE");
	//listile.push_back("CELEBRA2");
	//listile.push_back("CELEBRAT");
	listile.push_back("CITABAU");
	//listile.push_back("CITADEL");
	//listile.push_back("DESERT");
	//listile.push_back("EMERAUDE");
	//listile.push_back("ILOTCX");
	//listile.push_back("KNARTAS");
	//listile.push_back("MOON");
	//listile.push_back("MOSQUIBE");
	//listile.push_back("OTRINGAL");
	//listile.push_back("PLATFORM");
	//listile.push_back("SOUSCELB");



	for(size_t i=0; i< listile.size(); ++i)
	{
		SceneExterior* sc = new SceneExterior();
		sc->load(listile[i]);
		delete sc;
	}


	//osgDB::setDataFilePathList("./Data");

	//int currmodel = 0;
	//int currbody = 0;
	//int curranim = 0;

	//entitiesTableStruct*  estruct = parseEntities("FILE3D.HQR");
	//LBA1ModelClass *_modelRenderer = new LBA1ModelClass(estruct, "BODY.HQR", "ANIM.HQR", currmodel,
	//									estruct->entitiesTable[currmodel].bodyList[currbody].body);

	//_modelRenderer->SetAnimationSpeedFactor(1.8f);

	//_modelRenderer->LoadAnim(estruct,
	//	estruct->entitiesTable[currmodel].animList[curranim].index);



	//int _resX = 800;
	//int _resY = 600;
	//osgViewer::Viewer viewer;

 //   osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
 //   traits->x = 50;
 //   traits->y = 50;
 //   traits->width = _resX;
 //   traits->height = _resY;
 //   traits->windowDecoration = true;
 //   traits->doubleBuffer = true;
 //   traits->sharedContext = 0;
	//traits->windowName = "anim";
 //   osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
 //   osgViewer::GraphicsWindow* gw = dynamic_cast<osgViewer::GraphicsWindow*>(gc.get());

 //   viewer.getCamera()->setGraphicsContext(gc.get());
 //   viewer.getCamera()->setViewport(0,0,_resX,_resY);

	//

	////_modelRenderer->setAtKeyFrame(0, true);
	//osg::ref_ptr<osg::Node> node = _modelRenderer->ExportOSGModel();
	//

 //   // create a room made of foor walls, a floor, a roof, and swinging light fitting.
 //   osg::Node* rootnode = createRoom(node);


 //   // let's run !
 //   viewer.setSceneData( rootnode );

	//KeyboardEventHandler * keybh = new KeyboardEventHandler(_modelRenderer, estruct, currmodel, viewer);
 //   viewer.addEventHandler(new osgViewer::StatsHandler());
 //   viewer.addEventHandler(new osgViewer::WindowSizeHandler());
 //   viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
	//viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	//viewer.addEventHandler(keybh);

	//viewer.realize();



	//double lasttime = osg::Timer::instance()->tick();
 //   while (!viewer.done())
 //   {
	//	double newtime = osg::Timer::instance()->tick();
	//	double delta = osg::Timer::instance()->delta_m(lasttime, newtime);
	//	lasttime = newtime;

	//	keybh->GetModelRenderer()->AnimateModel((float)delta);
 //       viewer.frame();
 //   }

	return 0;
}
