#include	<sstream>
#include	<fstream>
#include	"SceneExterior.h"


#include <osg/Node>
#include <osg/PolygonMode>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include<osg/LineWidth>
#include <osgUtil/SmoothingVisitor>
#include <osgUtil/Optimizer>
#include <osgDB/WriteFile>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgDB/FileUtils>
#include <osgUtil/Optimizer>


//#include	"../../Engine.h"

//using namespace Ogre;

/*
** Main methods
*/

SceneExterior::SceneExterior() 
//:	IScene(sceneMgr, CollisionManager)
{
	//...
}

void	SceneExterior::load(const std::string& name)
{	
	mName = name;

	mILE = new HQRReader(/*mConfig->mPATH_HQR + */name + ".ILE");
	mOBL = new HQRReader(/*mConfig->mPATH_HQR + */name + ".OBL");
		
	loadEnvironment();	
	loadSections();

	delete mILE;
	delete mOBL;
}

void	SceneExterior::unload()
{
}

/*
** Loaders
*/

void	SceneExterior::loadEnvironment()
{
}

void	SceneExterior::loadSections()
{
	std::map<int, osg::ref_ptr<osg::Group> > mObjLibrary;

	//Reading Section Layout
    mILE->LoadEntry(1);
	mILE->Read(mLayout, 256);

	/* Loading ground texture */	
	mILE->LoadEntry(2);
	mILE->Read(mGroundTexture, 256 * 256);
	
	ImageManager::getSingleton()->createTexture(0, 0, 256, 256, 
										mGroundTexture, mName + ".png", true);


	/* Loading sections */
    mNumSections = 0;

	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::Group> rootmap = new osg::Group();
	osg::ref_ptr<osg::Group> rootobject = new osg::Group();
	root->addChild(rootmap);
	root->addChild(rootobject);

	PhysicalInfo *physinfo = new PhysicalInfo();

	int startPointX=20, startPointY=20, EndPointX=0, EndPointY=0;

    for (int i = 0; i < 256; ++i)
		if (mLayout[i])
		{
			int x = i / 16;
			int y = i % 16;
			if(x < startPointX)
				startPointX = x;

			if(y < startPointY)
				startPointY = y;

			if(x > EndPointX)
				EndPointX = x;

			if(y > EndPointY)
				EndPointY = y;
		}

	//256 Section Chunks
    for (int i = 0; i < 256; ++i)
		//If there is a section in this chunk...
        if (mLayout[i])
		{
            ++mNumSections;

			//std::stringstream iss;
			//iss << "SECTION_" << mNumSections - 1;

			//SceneNode *node = mMainNode->createChildSceneNode("SECTION_" + Ogre::StringConverter::toString(mNumSections - 1));
			
			mSections.push_back
			(
				new IslandSection
				(
					mName,
					//mSceneMgr,
					mILE,
					mOBL,
					mNumSections - 1,
					i / 16, i % 16//,
					//node
				)
			);

			osg::ref_ptr<osg::Geode> geode = mSections.back()->load(*physinfo);
			rootmap->addChild(geode);
			rootobject->addChild(mSections.back()->loadObjects(mObjLibrary));
		}





	{
		osg::StateSet* stateSet = rootmap->getOrCreateStateSet();

		// Enable blending, select transparent bin.
		//stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
		stateSet->setRenderingHint( osg::StateSet::OPAQUE_BIN );


		osg::ref_ptr<osg::Texture2D> KLN89FaceTexture = new osg::Texture2D;

		// protect from being optimized away as static state:
		KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC); 

		// load an image by reading a file: 
		osg::Image* klnFace = osgDB::readImageFile(mName + ".png");

		// Assign the texture to the image we read from file: 
		KLN89FaceTexture->setImage(klnFace);

		KLN89FaceTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR);
		KLN89FaceTexture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
		KLN89FaceTexture->setUseHardwareMipMapGeneration(false);
		KLN89FaceTexture->setResizeNonPowerOfTwoHint(false);

		KLN89FaceTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_BORDER);
		KLN89FaceTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_BORDER);



		// Assign texture unit 0 of our new StateSet to the texture 
		// we just created and enable the texture.
		stateSet->setTextureAttributeAndModes
		  (0,KLN89FaceTexture,osg::StateAttribute::ON);


		std::string shadersrc = "uniform sampler2D tex; \
		void main() \
		{ \
			vec4 texel; \
			texel = texture2D(tex,gl_TexCoord[0].st); \
			 \
			 if(texel.a > 0.5) \
				 gl_FragColor = vec4(gl_Color.a*texel.rgb, 1); \
			else \
				 gl_FragColor = vec4(gl_Color.rgb, 1); \
		}";

		//gl_FragColor = vec4((gl_Color.rgb*texel.rgb*gl_Color.a)+(texel.rgb*(1-gl_Color.a)), gl_Color.a); \

		osg::Program* brickProgramObject = new osg::Program;
		osg::Shader* brickFragmentObject = new osg::Shader( osg::Shader::FRAGMENT );
		brickProgramObject->addShader( brickFragmentObject );
		brickFragmentObject->setShaderSource(shadersrc);
		stateSet->setAttributeAndModes(brickProgramObject, osg::StateAttribute::ON);

	}


	osg::StateSet* statesetroot = root->getOrCreateStateSet();
	statesetroot->setMode(GL_LIGHTING, osg::StateAttribute::OFF);



	// save the heightmap to phys file
	std::ofstream filebit((mName + ".phy").c_str(), std::ofstream::binary);
	unsigned int sizevertex = physinfo->vertexes.size();
	unsigned int sizeindices = physinfo->indices.size();
	unsigned int sizematerials = physinfo->materials.size();
	filebit.write((char*)&sizevertex, sizeof(unsigned int));
	filebit.write((char*)&sizeindices, sizeof(unsigned int));
	filebit.write((char*)&sizematerials, sizeof(unsigned int));
	filebit.write((char*)&physinfo->vertexes[0], sizevertex*sizeof(float));
	filebit.write((char*)&physinfo->indices[0], sizeindices*sizeof(unsigned int));
	if(sizematerials > 0)
		filebit.write((char*)&physinfo->materials[0], sizematerials*sizeof(short));


	delete physinfo;


	osgUtil::Optimizer optOSGFile;
	optOSGFile.optimize (root.get());
	osgDB::writeNodeFile(*root.get(), "0_" + mName + ".osgb", new osgDB::Options("Compressor=zlib"));
}
