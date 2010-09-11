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
	//mMainNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(mName);	
	//mMainNode->setScale(100, 100, 100);

	mILE = new HQRReader(/*mConfig->mPATH_HQR + */name + ".ILE");
	mOBL = new HQRReader(/*mConfig->mPATH_HQR + */name + ".OBL");
		
	loadEnvironment();	
	loadSections();

	delete mILE;
	delete mOBL;
}

void	SceneExterior::unload()
{
	//Clear All Loaded Meshes and destroy master scenenode
	/*
	Destroy Sea Material
	Destroy Sea Texture	
	Destroy Sea Entity

	Destroy Sky Material
	Destroy Sky Texture	
	Destroy Sky Entity

	Destroy EnvPlane Mesh

	Destroy Object Textures
	Destroy Object Materials

	Destroy Ground Material
	Destroy Ground Texture
	
	SECTIONS - (for each section)
	--------
	Destroy Ground Mesh
	Destroy Ground Entity
	Destroy Object Meshes
	Destroy Object Entities
	--------
	*/

	//mMainNode->removeAndDestroyAllChildren();
}

/*
** Loaders
*/

void	SceneExterior::loadEnvironment()
{
	////Read the texture data
	//HQRReader ress(mConfig->mPATH_HQR + "RESS.HQR");
	//ress.LoadEntry(mConfig->mIslandInfo.find(mName)->second.skyIndex);
	//ress.Read(mSeaSkyTexture, 256 * 256);

	////Create textures and materials
	//ImageManager::getSingleton().createTexture(mName + "_SEA", 0, 0, 128, 128, mSeaSkyTexture);	
	//ImageManager::getSingleton().createMaterial(mName + "_SEA");
	//ImageManager::getSingleton().createTexture(mName + "_SKY", 128, 0, 128, 128, mSeaSkyTexture);	
	//ImageManager::getSingleton().createMaterial(mName + "_SKY");

	////Create the environment plane mesh
	//Ogre::Plane plane;
	//plane.normal = Vector3::UNIT_Y;	
	//Ogre::MeshManager::getSingleton().createPlane("ENVplane", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 32, 32, 1, 1, true, 1, 64, 64, Vector3::UNIT_Z);
	//
	////Create the Sky
	//mSky = mSceneMgr->createEntity("Sea", "ENVplane");
	//mSky->setMaterialName(mName + "_SEA");
	//mSkyNode = mMainNode->createChildSceneNode("Sea");
	//mSkyNode->setPosition(16.0, -0.001, -16.0);
	//mSkyNode->attachObject(mSky);

	////Create the Sea
	//mSky = mSceneMgr->createEntity("Sky", "ENVplane");
	//mSky->setMaterialName(mName + "_SKY");
	//mSkyNode = mMainNode->createChildSceneNode("Sky");
	//mSkyNode->setPosition(16.0, 1.45, -16.0);	
	//mSkyNode->roll(Ogre::Radian(Ogre::Math::PI));	
	//mSkyNode->attachObject(mSky);

	////Set environment settings
	//mSceneMgr->setFog(Ogre::FOG_LINEAR, mConfig->mIslandInfo.find(mName)->second.skyColor, 0.0, 400.0, mConfig->mIslandInfo.find(mName)->second.fogDistance);
	//Engine::getSingleton().setBackgroundColour(mConfig->mIslandInfo.find(mName)->second.skyColor);
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

	//unsigned char othertexture[256 * 256];
	//mILE->LoadEntry(3);
	//mILE->Read(othertexture, 256 * 256);
	//ImageManager::getSingleton()->createTexture(0, 0, 256, 256, 
	//									othertexture, "textureother.png", true);


	//unsigned char othertexture[256 * 256];
	//mILE->LoadEntry(4);
	//mILE->Read(othertexture, 256 * 256);
	//ImageManager::getSingleton()->createTexture(0, 0, 256, 256, 
	//									othertexture, "textureother2.png", true);



	//ImageManager::getSingleton().createMaterial(mName + "_GROUND", false);

	/* Loading sections */
    mNumSections = 0;

	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::Group> rootmap = new osg::Group();
	osg::ref_ptr<osg::Group> rootobject = new osg::Group();
	root->addChild(rootmap);
	root->addChild(rootobject);

	std::set<std::pair<unsigned short, unsigned short> > textureinfos;

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

			osg::ref_ptr<osg::Geode> geode = mSections.back()->load(textureinfos, *physinfo);
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

		KLN89FaceTexture->setFilter(osg::Texture::FilterParameter::MIN_FILTER, osg::Texture::FilterMode::LINEAR);
		KLN89FaceTexture->setFilter(osg::Texture::FilterParameter::MAG_FILTER, osg::Texture::FilterMode::LINEAR);
		KLN89FaceTexture->setUseHardwareMipMapGeneration(false);
		KLN89FaceTexture->setResizeNonPowerOfTwoHint(false);

		KLN89FaceTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_BORDER);
		KLN89FaceTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_BORDER);



  //      osg::TexEnvCombine* tec = new osg::TexEnvCombine;
  //      tec->setSource0_RGB(osg::TexEnvCombine::TEXTURE0);
  //      tec->setOperand0_RGB(osg::TexEnvCombine::ONE_MINUS_SRC_ALPHA);

  //      tec->setSource1_RGB(osg::TexEnvCombine::PRIMARY_COLOR);
  //      tec->setOperand1_RGB(osg::TexEnvCombine::SRC_COLOR);


  //      tec->setCombine_RGB(osg::TexEnvCombine::REPLACE);
		//stateSet->setTextureAttribute(0, tec);



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
	std::ofstream filephys((mName + ".hmap").c_str());
	filephys<<1040<<" "<<1040<<std::endl;
	for(int cc=(startPointX*65); cc<((EndPointX+1)*65); ++cc)
	{
		for(int cc2=(startPointY*65); cc2<((EndPointY+1)*65); ++cc2)
		{
			filephys<<((float)physinfo->physmap[cc][cc2])/125<<" ";
		}
		filephys<<std::endl;
	}
	filephys<<std::endl;
	for(int cc=(startPointX*65); cc<((EndPointX+1)*65); ++cc)
	{
		for(int cc2=(startPointY*65); cc2<((EndPointY+1)*65); ++cc2)
		{
			filephys<<physinfo->materialmap[cc][cc2]<<" ";
		}
		filephys<<std::endl;
	}
	delete physinfo;


	osgUtil::Optimizer optOSGFile;
	optOSGFile.optimize (root.get());
	osgDB::writeNodeFile(*root.get(), "0_" + mName + ".osgb", new osgDB::Options("Compressor=zlib"));
}
