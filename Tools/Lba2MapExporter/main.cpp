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
	listile.push_back("ASCENCE");
	listile.push_back("CELEBRA2");
	listile.push_back("CELEBRAT");
	listile.push_back("CITABAU");
	listile.push_back("CITADEL");
	listile.push_back("DESERT");
	listile.push_back("EMERAUDE");
	listile.push_back("ILOTCX");
	listile.push_back("KNARTAS");
	listile.push_back("MOON");
	listile.push_back("MOSQUIBE");
	listile.push_back("OTRINGAL");
	listile.push_back("PLATFORM");
	listile.push_back("SOUSCELB");


	for(size_t i=0; i< listile.size(); ++i)
	{
		SceneExterior* sc = new SceneExterior();
		sc->load(listile[i]);
		delete sc;
	}

	return 0;
}
