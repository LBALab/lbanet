#include	<sstream>
#include	"IslandSection.h"
#include	"LBATextureLoader.h"


#include <osg/Node>
#include <osg/PolygonMode>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include<osg/LineWidth>
#include <osgUtil/SmoothingVisitor>
#include <osgUtil/Optimizer>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>


//using namespace Ogre;

#define PI 3.14159265

IslandSection::IslandSection(const std::string& islandName, HQRReader *ILE, HQRReader *OBL, int idx, int xpos, int ypos)
:	mIslandName(islandName),
	mILE(ILE),
	mOBL(OBL),
	mIndex(idx),
	mXpos(xpos),
	mYpos(ypos)
{
	//...
}

osg::ref_ptr<osg::Geode>	IslandSection::load(std::set<std::pair<unsigned short, unsigned short> > & texturesinfos,
									PhysicalInfo & physinfo)
{
	//Adjust node into island position relative to the entire island
	//mNode->setPosition(((mXpos - 7) * 64) / 32.0f, 0, (((16 - mYpos) - 7) * 64) / 32.0f);
	//mNode->setPosition(mXpos * 2.0f, 0, -mYpos * 2.0f);
	
	//Heightmapped terrain
	return loadGround(texturesinfos, physinfo);	

	//Object Loading
	//loadObjects();
}

osg::ref_ptr<osg::Geode>	IslandSection::loadGround(std::set<std::pair<unsigned short, unsigned short> > & texturesinfos,
															PhysicalInfo & physinfo)
{
	osg::Vec3Array* myVerticesPoly = new osg::Vec3Array;
	osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	osg::Vec4Array* colors = new osg::Vec4Array;
	osg::Vec2Array* myTexts = new osg::Vec2Array;

	std::stringstream issss;
	issss << "GROUND_" << mIndex;

	std::string iss = issss.str();
	
	/* GROUND MESH */
	//MeshPtr msh = MeshManager::getSingleton().createManual(iss, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	//SubMesh* sub = msh->createSubMesh();

	/* Preparing vertex array */
	short heightmap[65][65];
	short maxHeight = 0;
	mILE->LoadEntry(3 + mIndex * 6 + 5);
	mILE->Read(heightmap, 65 * 65 * 2);
	std::vector<float> vertices;
	vertices.reserve(9 * 64 * 64 * 4 * 2);


	for(int cc=0; cc<65; ++cc)
	{
		for(int cc2=0; cc2<65; ++cc2)
		{
			physinfo.physmap[(mXpos*65)+cc][(mYpos*65)+cc2] = heightmap[cc][cc2];
		}
	}

	/* Preparing texture info array */
	GroundTextureInfo *textureInfo;
	mILE->LoadEntry(3 + mIndex * 6 + 4);
	textureInfo = new GroundTextureInfo[mILE->getSize() / 12];
	mILE->Read(textureInfo, mILE->getSize());

	//for(int i=0; i< mILE->getSize() / 12; ++i)
	//{
	//	texturesinfos.insert(std::make_pair<unsigned short, unsigned short>(textureInfo[i].uv[0].u, textureInfo[i].uv[0].v));
	//	texturesinfos.insert(std::make_pair<unsigned short, unsigned short>(textureInfo[i].uv[1].u, textureInfo[i].uv[1].v));
	//	texturesinfos.insert(std::make_pair<unsigned short, unsigned short>(textureInfo[i].uv[2].u, textureInfo[i].uv[2].v));
	//}

	/* Preparing intensity array */
	unsigned char intensity[65][65];
	mILE->LoadEntry(3 + mIndex * 6 + 6);
	mILE->Read(intensity, 65 * 65);

	/* getting material */
	unsigned char material[65][65];
	mILE->LoadEntry(3 + mIndex * 6 + 3);
	mILE->Read(material, 65 * 65);

	for(int cc=0; cc<65; ++cc)
	{
		for(int cc2=0; cc2<65; ++cc2)
		{
			int mat = (material[cc][cc2] >> 4);
			int mat2 = material[cc][cc2] & unsigned char(15);

			int sound = 0;
			switch(mat2)
			{
				case 0:
					sound =0;
				break;
				case 1:
					sound =1;
				break;
				case 2:
					sound =1;
				break;
				case 3:
					sound =3;
				break;
				case 4:
					sound =4;
				break;
				case 5:
					sound =5;
				break;
				case 6:
					sound =6;
				break;
				case 7:
					sound =7;
				break;
				case 8:
					sound =8;
				break;
				case 9:
					sound =9;
				break;
				case 10:
					sound =10;
				break;
				case 11:
					sound =11;
				break;
				case 12:
					sound =6;
				break;
				case 13:
					sound =13;
				break;
				case 14:
					sound =1;
				break;
			}

			if(mat == 1 || mat == 15)
			{
				sound = 17;
			}
			if(mat == 9 || mat == 13)
			{
				sound = 19;
			}
			if( mat == 11 || mat == 14)
			{
				sound = 18;
			}

			physinfo.materialmap[(mXpos*65)+cc][(mYpos*65)+cc2] = sound;
		}

	}


	/* Preparing index array */
	GroundSquare squares[64][64];
	mILE->LoadEntry(3 + mIndex * 6 + 3);
	mILE->Read(squares, 64 * 64 * 8);
	std::vector<unsigned short> faces;
	faces.reserve(6 * 64 * 64);

	/* Loading data */
	//Vertex Count - In order of verts that make tris
	unsigned short  idx = 0;
	unsigned short uvOrder[6] = {0, 1, 2, 2, 0, 1};
	unsigned short idxOrder1[6] = {0, 2, 3, 0, 3, 1};
	unsigned short idxOrder2[6] = {0, 2, 1, 1, 2, 3};

	//For Every QUAD
	for (int x = 0; x < 64; ++x)
	{
		for (int y = 0; y < 64; ++y)
		{
			//Pass the pointer from the quad database to this quad (2 triangles passed)
			GroundTriangle *tri = squares[x][y].triangle;
			//Orientation
			unsigned short *idxOrder = (tri[0].orientation == 0) ? idxOrder1 : idxOrder2;

			//For both tris in this quad...
			for (int t = 0; t < 2; ++t)
			{
				//Data Usage for this Tri
				int mdMax = 0;


				if (tri[t].useColor || tri[t].useTexture )
					mdMax++;
				//if (tri[t].useTexture)
				//	mdMax++;

				//For all the data usage in this tri
				for (int md = 0; md < mdMax; ++md)
				{
					//For each vertex, offset by triangle num in quad
					for (int i = 3 * t; i < (3 + 3 * t); ++i)
					{
						int xi = x + idxOrder[i] / 2;
						int yi = y + idxOrder[i] % 2;

						/* Vertex position */
						vertices.push_back(((float)(xi) - 32) / 0x20);
						vertices.push_back(((float)(heightmap[xi][yi])) / 0x4000);
						vertices.push_back(((float)(64 - yi) - 32) / 0x20);

						myVerticesPoly->push_back(osg::Vec3(	(((float)(xi) - 32) / 0x20) + (mXpos * 2.0f),
																(((float)(heightmap[xi][yi])) / 0x4000),
																(((float)(64 - yi) - 32) / 0x20) - (mYpos * 2.0f)
															));


						if (heightmap[xi][yi] > maxHeight)
							maxHeight = heightmap[xi][yi];

						/* Vertex color and UV */
						if (tri[t].useTexture/* && (mdMax < 2 || md == 1)*/)
						{
							float intens = intensity[xi][yi] / 16.0f + 0.3f;
							
							if (intens > 1.0)
								intens = 1.0;

							if (tri[t].useColor)
							{
								unsigned char color = (tri[t].textureBank * 16) + intensity[xi][yi];
								colorrgba colorVal = ImageManager::getSingleton()->getColour(color);
								
								vertices.push_back(colorVal.r);
								vertices.push_back(colorVal.g);
								vertices.push_back(colorVal.b);

								// check shader to know why intens is put as alpha
								colors->push_back(osg::Vec4(colorVal.r,colorVal.g,colorVal.b, intens));
							}
							else
							{
								vertices.push_back(intens);
								vertices.push_back(intens);
								vertices.push_back(intens);

								// check shader to know why intens is put as alpha
								colors->push_back(osg::Vec4(intens,intens,intens, intens));
							}


							vertices.push_back(1.0);
							vertices.push_back((textureInfo[tri[t].textureIndex].uv[uvOrder[i]].u / 65535.0f) * 0.5f);
							vertices.push_back(textureInfo[tri[t].textureIndex].uv[uvOrder[i]].v / 65535.0f);

							
							//colors->push_back(osg::Vec4(1.0f,1.0f,1.0f, 1.0f));
							myTexts->push_back(osg::Vec2((textureInfo[tri[t].textureIndex].uv[uvOrder[i]].u / 65535.0f) * 0.5f, 
															textureInfo[tri[t].textureIndex].uv[uvOrder[i]].v / 65535.0f));


							//texturesinfos.insert(std::make_pair<unsigned short, unsigned short>
							//	((textureInfo[tri[t].textureIndex].uv[uvOrder[i]].u / 257), 
							//	textureInfo[tri[t].textureIndex].uv[uvOrder[i]].v / 257));


						}
						else/* if (mdMax < 2 || md == 0)*/
						{
							unsigned char color = (tri[t].textureBank * 16) + intensity[xi][yi];
							colorrgba colorVal = ImageManager::getSingleton()->getColour(color);
							
							vertices.push_back(colorVal.r);
							vertices.push_back(colorVal.g);
							vertices.push_back(colorVal.b);
							vertices.push_back(1.0);
							vertices.push_back(0.75f);
							vertices.push_back(0.5f);

							colors->push_back(osg::Vec4(colorVal.r,colorVal.g,colorVal.b, 1.0f));
							myTexts->push_back(osg::Vec2(0.75f, 0.5f));

						}
					}

					/* Index */
					faces.push_back(idx);
					faces.push_back(idx + 1);
					faces.push_back(idx + 2);
					myprimitive->push_back(idx);
					myprimitive->push_back(idx + 1);
					myprimitive->push_back(idx + 2);

					idx += 3;
				}
			}
		}
	}

	osg::ref_ptr<osg::Geode> myGeode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> m_myGeometry = new osg::Geometry();
	myGeode->addDrawable(m_myGeometry.get());
	m_myGeometry->setVertexArray( myVerticesPoly ); 
	m_myGeometry->addPrimitiveSet(myprimitive);
	m_myGeometry->setColorArray(colors);
	m_myGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	m_myGeometry->setTexCoordArray( 0, myTexts);

	//osgUtil::Optimizer optOSGFile;
	//optOSGFile.optimize (myGeode.get());

	osgUtil::SmoothingVisitor::smooth(*(m_myGeometry.get()));


	return myGeode;


}

osg::ref_ptr<osg::Group> IslandSection::loadObjects(std::map<int, osg::ref_ptr<osg::Group> > &mObjLibrary)
{
	osg::ref_ptr<osg::Group> root = new osg::Group();


	unsigned char objInfo[40];
	mILE->LoadEntry(3 + mIndex * 6 + 1);
	mILE->Read(objInfo, 40);
	
	mNumObjects = *((unsigned int *)(objInfo + 8));

	if (mNumObjects > 0)
	{
		mObjectInfo = new IslandObjectInfo [mNumObjects];
		mILE->LoadEntry(3 + mIndex * 6 + 2);
		mILE->Read(mObjectInfo, mILE->getSize());
		for (unsigned int i = 0; i < mNumObjects; ++i)
		{			
			osg::ref_ptr<osg::PositionAttitudeTransform> PAT = new osg::PositionAttitudeTransform();
			PAT->setPosition (osg::Vec3(	(mObjectInfo[i].oz / 16384.0f - 1)  + (mXpos * 2.0f), 
											(mObjectInfo[i].oy / 16384.0f), 
											(-mObjectInfo[i].ox / 16384.0f + 1)  - (mYpos * 2.0f)
										));
			PAT->setAttitude(osg::Quat(((mObjectInfo[i].angle + 4) * PI) / 8, osg::Vec3(0, 1, 0)));
			osg::ref_ptr<osg::Group> tmpobject = loadSingleObject(&mObjectInfo[i], mObjLibrary);

			PAT->addChild(tmpobject);
			root->addChild(PAT);
			
			//SceneNode *node = mNode->createChildSceneNode(iss.str());

			//node->setPosition(mObjectInfo[i].oz / 16384.0f - 1, mObjectInfo[i].oy / 16384.0f, -mObjectInfo[i].ox / 16384.0f + 1);
			//node->rotate(Ogre::Vector3(0, 1, 0), Ogre::Radian(((mObjectInfo[i].angle + 4) * PI) / 8));
		}
		delete [] mObjectInfo;
	}

	return root;
}

void	IslandSection::addPolygonSection(unsigned char *buffer, OBLPolygonHeader *header, 
										 std::map<unsigned int, CutGroup>& cutGroups, 
										 CutGroup &subColor, std::vector<float>& vertices, 
										 int& currentIndex, OBLMinMaxBox& mMBox,
											osg::Vec3Array* myVertices/*,
											osg::DrawElementsUInt* myprimitive,
											osg::Vec4Array* colors,
											osg::Vec2Array* myTexts*/)
{
	unsigned int blockSize = (header->size - 8) / header->numPolygon;
	IslandObjectHeader *oBLheader = (IslandObjectHeader *)buffer;
	OBLVertex *oBLvertices = (OBLVertex *)(buffer + 0x68);

	OBLIntensity *oBLintensities = (OBLIntensity *)(buffer + 0x68 + 8 * oBLheader->numVerticesType1);


	// for some weird reason there is a section with a block size of 16 
	// (CITABEAU the cup containing some soup on the table)
	// added it and made an execption for it so that it use color and not texture
	if ((blockSize == 12 || blockSize == 16 || blockSize == 24 || blockSize == 32))
	{
		OBLPolygon *polygon = (OBLPolygon *)(((char *)header) + 8);
		for (int i = 0; i < header->numPolygon; ++i)
		{
			CutGroup* cut = &subColor;
			float uvFactor = 1;
			if (header->id >= 7)
			{
				unsigned int cutID;
				unsigned char cutInfo;
				if (blockSize == 32)
					cutInfo = *((unsigned char *)(((char *)polygon) + 28));
				else if (blockSize == 16)
					cutInfo = *((unsigned char *)(((char *)polygon) + 6));
				else
					cutInfo = *((unsigned char *)(((char *)polygon) + 6));
				cutID = ((unsigned int *)(buffer + oBLheader->cutSectionOffset))[cutInfo];
				if (cutID != 0xFFFF0000)
					uvFactor = *((unsigned char *)(((char *)polygon) + 9));

				std::map<unsigned int, CutGroup>::iterator itm = cutGroups.find(cutID);
				if(itm != cutGroups.end())
					cut = &(itm->second);
			}
			int numPoints = (header->type & 0x80) ? 4 : 3;
			for (int j = 0; j < numPoints; ++j)
			{
				if (oBLvertices[polygon->idx[j]].x < mMBox.mx)
					mMBox.mx = oBLvertices[polygon->idx[j]].x;
				if (oBLvertices[polygon->idx[j]].y < mMBox.my)
					mMBox.my = oBLvertices[polygon->idx[j]].y;
				if (oBLvertices[polygon->idx[j]].z < mMBox.mz)
					mMBox.mz = oBLvertices[polygon->idx[j]].z;
				if (oBLvertices[polygon->idx[j]].x > mMBox.Mx)
					mMBox.Mx = oBLvertices[polygon->idx[j]].x;
				if (oBLvertices[polygon->idx[j]].y > mMBox.My)
					mMBox.My = oBLvertices[polygon->idx[j]].y;
				if (oBLvertices[polygon->idx[j]].z > mMBox.Mz)
					mMBox.Mz = oBLvertices[polygon->idx[j]].z;
				/* Position */
				vertices.push_back(oBLvertices[polygon->idx[j]].x  / 16384.0f);
				vertices.push_back(oBLvertices[polygon->idx[j]].y  / 16384.0f);
				vertices.push_back(oBLvertices[polygon->idx[j]].z  / 16384.0f);

				cut->myVerticesPoly->push_back(osg::Vec3(	(oBLvertices[polygon->idx[j]].x  / 16384.0f),
															(oBLvertices[polygon->idx[j]].y  / 16384.0f),
															(oBLvertices[polygon->idx[j]].z  / 16384.0f)
														));


				/* Color */
				if (/*header->id >= 7 && */cut->usetexture)
				{
					vertices.push_back(1);
					vertices.push_back(1);
					vertices.push_back(1);
					vertices.push_back(1);

					cut->colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

					cut->myTexts->push_back(osg::Vec2(	((polygon->uv[j].u * uvFactor) / 65536.0f)/* * 0.5f*/, 
													((polygon->uv[j].v * uvFactor) / 65536.0f)
															));

				}
				else
				{
					const colorrgba& color = ImageManager::getSingleton()->getColour(polygon->color + oBLintensities[polygon->idx[j]].i[1] / 32);
					vertices.push_back(color.r);
					vertices.push_back(color.g);
					vertices.push_back(color.b);
					vertices.push_back(1);

					cut->colors->push_back(osg::Vec4(color.r,color.g,color.b, 1.0f));

					//cut->myTexts->push_back(osg::Vec2(0.75f, 0.5f));
				}
				/* UVs */
				vertices.push_back((polygon->uv[j].u * uvFactor) / 65536.0f);
				vertices.push_back((polygon->uv[j].v * uvFactor) / 65536.0f);

			}
			cut->indices.push_back(currentIndex);
			cut->indices.push_back(currentIndex + 1);
			cut->indices.push_back(currentIndex + 2);

			cut->myprimitive->push_back(cut->currentIndex);
			cut->myprimitive->push_back(cut->currentIndex + 1);
			cut->myprimitive->push_back(cut->currentIndex + 2);

			if (header->type & 0x80)
			{
				cut->indices.push_back(cut->currentIndex);
				cut->indices.push_back(cut->currentIndex + 2);
				cut->indices.push_back(cut->currentIndex + 3);

				cut->myprimitive->push_back(cut->currentIndex);
				cut->myprimitive->push_back(cut->currentIndex + 2);
				cut->myprimitive->push_back(cut->currentIndex + 3);
			}
			cut->currentIndex += numPoints;
			cut->myprimitivenumpoints.push_back(numPoints);
			polygon = (OBLPolygon *)(((char *)polygon) + blockSize);
		}
	}

}

osg::ref_ptr<osg::Group>	IslandSection::loadSingleObject(IslandObjectInfo *objInfo,
															std::map<int, osg::ref_ptr<osg::Group> > &mObjLibrary)
{

	//osg::Vec3Array* myVerticesPoly = new osg::Vec3Array;
	//osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	//osg::Vec4Array* colors = new osg::Vec4Array;
	//osg::Vec2Array* myTexts = new osg::Vec2Array;

	//std::string textname = name+".png";


	//Check if we have this OBL Index Logged
	if (mObjLibrary.find(objInfo->index + 1) != mObjLibrary.end())
	{
		//std::cout << "Dupe Found\n";
		return mObjLibrary[objInfo->index + 1];
	}
	else
	{
		osg::ref_ptr<osg::Group> root = new osg::Group;


		/* Loading the data */
		mOBL->LoadEntry(objInfo->index + 1);

		//if(objInfo->index + 1 == 84)
		//	std::cout<<"plpop"<<std::endl;
		//else
		//	return root;

		const int bufSize = mOBL->getSize();
		unsigned char *objBuffer = new unsigned char [bufSize];
		mOBL->Read(objBuffer, bufSize);
		IslandObjectHeader *header = (IslandObjectHeader *)objBuffer;

		/* Preparing the mesh */
		//MeshPtr msh = MeshManager::getSingleton().createManual(name, "");
		std::map<unsigned int, CutGroup> cutGroups;
		loadCutGroups(objBuffer, /*msh, */cutGroups);
		CutGroup colorSub("OBLnoTexture", 0, 0, 0, 0, false);
		colorSub.usetexture = false;
		int currentIndex = 0;
		std::vector<float> vertices;
		vertices.reserve(2000);

		osg::Vec3Array *myVertices(new osg::Vec3Array);
		{
			IslandObjectHeader *oBLheader = (IslandObjectHeader *)objBuffer;
			OBLVertex *oBLvertices = (OBLVertex *)(objBuffer + 0x68);

			// push vertices for points and spheres
			for(int i=0; i<oBLheader->numVerticesType1; ++i)
			{
				myVertices->push_back(osg::Vec3(	(oBLvertices[i].x  / 16384.0f),
													(oBLvertices[i].y  / 16384.0f),
													(oBLvertices[i].z  / 16384.0f)
														));
			}
		}



		/* Loading the polygons */
		OBLMinMaxBox mMBox;
		OBLPolygonHeader *polyHead = (OBLPolygonHeader *)(objBuffer + header->polygonSectionOffset);
		while (polyHead->size > 0 && ((unsigned char*)polyHead) < (objBuffer + header->lineSectionOffset))
		{
			addPolygonSection(objBuffer, polyHead, cutGroups, colorSub, vertices, currentIndex, mMBox, myVertices/*, 
									myVerticesPoly,myprimitive,colors,myTexts*/);

			polyHead = (OBLPolygonHeader *)(((unsigned char *)polyHead) + polyHead->size);
		}


		cutGroups.insert(std::pair<unsigned int, CutGroup>(0, colorSub));
		std::map<unsigned int, CutGroup>::iterator it, end;
		for (it = cutGroups.begin(), end = cutGroups.end(); it != end; ++it)
		{
			if (it->second.indices.size() != 0)
			{
				// if part is transparent we need one geode per geometry for correct depth sorting
				//if(!it->second.istransparent)
				//{
					osg::ref_ptr<osg::Geode> myGeode = new osg::Geode();
					osg::ref_ptr<osg::Geometry> m_myGeometry = new osg::Geometry();
					myGeode->addDrawable(m_myGeometry.get());
					m_myGeometry->setVertexArray( it->second.myVerticesPoly ); 
					m_myGeometry->addPrimitiveSet(it->second.myprimitive);
					//if(!it->second.usetexture)
					{
						m_myGeometry->setColorArray(it->second.colors);
						m_myGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
					}

					if(it->second.usetexture)
					{
						m_myGeometry->setTexCoordArray( 0, it->second.myTexts);

						osg::StateSet* stateSet = myGeode->getOrCreateStateSet();

						// Enable blending, select transparent bin.
						if(it->second.istransparent)
						{
							stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
							stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
							stateSet->setRenderBinDetails(1, "DepthSortedBin");
						}
						else
						{
							stateSet->setRenderingHint( osg::StateSet::OPAQUE_BIN );
						}


						osg::ref_ptr<osg::Texture2D> KLN89FaceTexture = new osg::Texture2D;

						// protect from being optimized away as static state:
						KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC); 

						// load an image by reading a file: 
						osg::Image* klnFace = osgDB::readImageFile(it->second.materialName);

						// Assign the texture to the image we read from file: 
						KLN89FaceTexture->setImage(klnFace);

						KLN89FaceTexture->setFilter(osg::Texture::FilterParameter::MIN_FILTER, osg::Texture::FilterMode::/*NEAREST*/LINEAR);
						KLN89FaceTexture->setFilter(osg::Texture::FilterParameter::MAG_FILTER, osg::Texture::FilterMode::/*NEAREST*/LINEAR);
						KLN89FaceTexture->setUseHardwareMipMapGeneration(false);
						KLN89FaceTexture->setResizeNonPowerOfTwoHint(false);

						KLN89FaceTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
						KLN89FaceTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);

						// Assign texture unit 0 of our new StateSet to the texture 
						// we just created and enable the texture.
						stateSet->setTextureAttributeAndModes
						  (0,KLN89FaceTexture,osg::StateAttribute::ON);
					}

					osgUtil::SmoothingVisitor::smooth(*(m_myGeometry.get()));
					root->addChild(myGeode);
				//}
				//else
				//{
				//	osg::ref_ptr<osg::Group> roottransparent = new osg::Group;

				//	int cc=0;
				//	for(size_t i=0; i< it->second.myprimitivenumpoints.size(); ++i)
				//	{
				//		osg::ref_ptr<osg::Geode> myGeode = new osg::Geode();
				//		osg::ref_ptr<osg::Geometry> m_myGeometry = new osg::Geometry();
				//		myGeode->addDrawable(m_myGeometry.get());

				//		
				//		osg::Vec3Array*				myVerticesPoly = new osg::Vec3Array();
				//		osg::DrawElementsUInt*		myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
				//		osg::Vec4Array*				colors = new osg::Vec4Array();
				//		osg::Vec2Array*				myTexts = new osg::Vec2Array();

				//		int end = cc + it->second.myprimitivenumpoints[i];
				//		for(; cc< end; ++cc)
				//		{
				//			myVerticesPoly->push_back((*it->second.myVerticesPoly)[cc]);
				//			colors->push_back((*it->second.colors)[cc]);
				//			myTexts->push_back((*it->second.myTexts)[cc]);
				//		}
				//		myprimitive->push_back(0);					
				//		myprimitive->push_back(1);
				//		myprimitive->push_back(2);
				//		if(it->second.myprimitivenumpoints[i] > 3)
				//		{
				//			myprimitive->push_back(0);					
				//			myprimitive->push_back(2);
				//			myprimitive->push_back(3);
				//		}

				//		m_myGeometry->setVertexArray(myVerticesPoly); 
				//		m_myGeometry->addPrimitiveSet(myprimitive);
				//		m_myGeometry->setTexCoordArray( 0, myTexts);
				//		m_myGeometry->setColorArray(colors);
				//		m_myGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

				//		osgUtil::SmoothingVisitor::smooth(*(m_myGeometry.get()));
				//		roottransparent->addChild(myGeode);
				//	}

				//	{
				//		osg::StateSet* stateSet = roottransparent->getOrCreateStateSet();

				//		// Enable blending, select transparent bin.
				//		stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
				//		stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
				//		stateSet->setRenderBinDetails(1, "DepthSortedBin");


				//		osg::ref_ptr<osg::Texture2D> KLN89FaceTexture = new osg::Texture2D;

				//		// protect from being optimized away as static state:
				//		KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC); 

				//		// load an image by reading a file: 
				//		osg::Image* klnFace = osgDB::readImageFile(it->second.materialName);

				//		// Assign the texture to the image we read from file: 
				//		KLN89FaceTexture->setImage(klnFace);

				//		KLN89FaceTexture->setFilter(osg::Texture::FilterParameter::MIN_FILTER, osg::Texture::FilterMode::/*NEAREST*/LINEAR);
				//		KLN89FaceTexture->setFilter(osg::Texture::FilterParameter::MAG_FILTER, osg::Texture::FilterMode::/*NEAREST*/LINEAR);
				//		KLN89FaceTexture->setUseHardwareMipMapGeneration(false);
				//		KLN89FaceTexture->setResizeNonPowerOfTwoHint(false);

				//		KLN89FaceTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
				//		KLN89FaceTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);

				//		// Assign texture unit 0 of our new StateSet to the texture 
				//		// we just created and enable the texture.
				//		stateSet->setTextureAttributeAndModes
				//		  (0,KLN89FaceTexture,osg::StateAttribute::ON);
				//	}

				//	root->addChild(roottransparent);
				//}
			}
		}


		// load lines
		{
			
			int numOfLines = header->lineSectionSize;
			if(numOfLines > 0)
			{
				TLines* localData= new TLines();
				localData->NumberOfLines=numOfLines;
				localData->LinesData = new TLine[numOfLines];

				osg::ref_ptr<osg::Geode> myGeodeLines = new osg::Geode();
				osg::ref_ptr<osg::Geometry> m_myGeometrylines = new osg::Geometry();
				myGeodeLines->addDrawable(m_myGeometrylines.get());
				osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);


				osg::Vec4Array* colors = new osg::Vec4Array;
				osg::Vec3Array *myVerticesPoints(new osg::Vec3Array);

				unsigned char* sourcePtr=(objBuffer + header->lineSectionOffset);
				int indexp=0;
				for(int i=0;i<numOfLines;i++)
				{
					memcpy(&localData->LinesData[i],sourcePtr,8);
					sourcePtr+=8;

					myVerticesPoints->push_back((*myVertices)[localData->LinesData[i].PointNum1]);
					myVerticesPoints->push_back((*myVertices)[localData->LinesData[i].PointNum2]);
					myprimitive->push_back(indexp++);
					myprimitive->push_back(indexp++);

					const colorrgba& color = ImageManager::getSingleton()->getColour(localData->LinesData[i].Color);
					colors->push_back(osg::Vec4(color.r,color.g,color.b, 1.0f));
				}
				m_myGeometrylines->addPrimitiveSet(myprimitive);
				
				m_myGeometrylines->setVertexArray( myVerticesPoints); 
				m_myGeometrylines->setColorArray(colors);
				m_myGeometrylines->setColorBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);


				osg::StateSet* stateset = m_myGeometrylines->getOrCreateStateSet();
				//osg::LineWidth* linewidth = new osg::LineWidth();
				//linewidth->setWidth(1.0f);
				//stateset->setAttributeAndModes(linewidth,osg::StateAttribute::ON);
				stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

				root->addChild(myGeodeLines);

				delete[] localData->LinesData;
				delete localData;
			}	
		}


		// load spheres
		{
			int numOfSpheres = header->sphereSectionSize;
			if(numOfSpheres > 0)
			{
				TSpheres* localData= new TSpheres();

				localData->NumberOfSpheres=numOfSpheres;
				localData->SpheresData= new TSphere[numOfSpheres];

				unsigned char* sourcePtr=(objBuffer + header->sphereSectionOffset);
				for(int i=0;i<numOfSpheres;i++)
				{
					memcpy(&localData->SpheresData[i],sourcePtr,8);
					sourcePtr+=8;

					osg::ref_ptr<osg::TessellationHints> hints_low = new osg::TessellationHints;
					hints_low->setDetailRatio(0.4f); 
					osg::ref_ptr<osg::Geode> Geodesphere = new osg::Geode();

					osg::Vec3 center((*myVertices)[localData->SpheresData[i].Center]);
					osg::ref_ptr<osg::Sphere> unitSphere = new osg::Sphere(center, ((float)localData->SpheresData[i].Size)/16384.0f);
					osg::ShapeDrawable* unitSphereDrawable = new osg::ShapeDrawable(unitSphere, hints_low.get());

					const colorrgba& color = ImageManager::getSingleton()->getColour(localData->SpheresData[i].Color);
					unitSphereDrawable->setColor(osg::Vec4(color.r,color.g,color.b, 1.0f));
					Geodesphere->addDrawable(unitSphereDrawable);
					root->addChild(Geodesphere);
				}

				delete[] localData->SpheresData;
				delete localData;
			}
		}


		/* Loading the hardware vertex buffer */
		//msh->sharedVertexData = new VertexData;
		//msh->sharedVertexData->vertexCount = vertices.size() / 9;
		//VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
		//size_t offset = 0;
		//decl->addElement(0, 0, VET_FLOAT3, VES_POSITION);
		//offset += VertexElement::getTypeSize(VET_FLOAT3);
		//decl->addElement(0, offset, VET_FLOAT4, VES_DIFFUSE);
		//offset += VertexElement::getTypeSize(VET_FLOAT4);
		//decl->addElement(0, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);
		//offset += VertexElement::getTypeSize(VET_FLOAT2);
		//HardwareVertexBufferSharedPtr vbuf = HardwareBufferManager::getSingleton().createVertexBuffer(offset, msh->sharedVertexData->vertexCount, HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		//vbuf->writeData(0, vbuf->getSizeInBytes(), &(vertices[0]), true);
		//VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding; 
		//bind->setBinding(0, vbuf);

		/* Loading the hardware buffers */
		//cutGroups.insert(std::pair<unsigned int, CutGroup>(0, colorSub));
		//std::map<unsigned int, CutGroup>::iterator it, end;
		//for (it = cutGroups.begin(), end = cutGroups.end(); it != end; ++it)
		//{
		//	if (it->second.indices.size() != 0)
		//	{
		//		it->second.subMesh = msh->createSubMesh();
		//		SubMesh *sub = it->second.subMesh;
		//		/* Loading the hardware index buffer */
		//		HardwareIndexBufferSharedPtr ibuf = HardwareBufferManager::getSingleton().createIndexBuffer(HardwareIndexBuffer::IT_16BIT, it->second.indices.size(), HardwareBuffer::HBU_STATIC_WRITE_ONLY);
		//		ibuf->writeData(0, ibuf->getSizeInBytes(), &(it->second.indices[0]), true);
		//		sub->useSharedVertices = true;
		//		sub->indexData->indexBuffer = ibuf;
		//		sub->indexData->indexCount = it->second.indices.size();
		//		sub->indexData->indexStart = 0;
		//		sub->setMaterialName(it->second.materialName);
		//	}
		//}

		///* Finalizing */
		//msh->_setBounds(AxisAlignedBox(mMBox.mx / 16384.0f, mMBox.my / 16384.0f, mMBox.mz / 16384.0f, mMBox.Mx / 16384.0f, mMBox.My / 16384.0f, mMBox.Mz / 16384.0f));
		//msh->_setBoundingSphereRadius(Math::Sqrt(8));
		//msh->load();

		delete [] objBuffer;


		//root->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);



		//osgUtil::Optimizer optOSGFile;
		//optOSGFile.optimize (root.get());


		mObjLibrary[objInfo->index + 1] = root;


		std::stringstream iss;
		iss << mIslandName << "_OBJ_" << objInfo->index + 1 << ".osgb";


		osg::StateSet* statesetroot = root->getOrCreateStateSet();
		statesetroot->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
		//statesetroot->setMode(GL_CULL_FACE, osg::StateAttribute::OFF);



		osgUtil::Optimizer optOSGFile;
		optOSGFile.optimize (root.get());

		//osgDB::writeNodeFile(*root.get(), iss.str());
		osgDB::writeNodeFile(*root.get(), iss.str(), new osgDB::Options("Compressor=zlib"));



		return root;
	}

	/* Creating entity */
	//Entity *ent = mSceneMgr->createEntity(name, mObjLibrary[objInfo->index + 1]);
	//
	//objNode->attachObject(ent);	

	//osg::ref_ptr<osg::Geode> myGeode = new osg::Geode();
	//osg::ref_ptr<osg::Geometry> m_myGeometry = new osg::Geometry();
	//myGeode->addDrawable(m_myGeometry.get());
	//m_myGeometry->setVertexArray( myVerticesPoly ); 
	//m_myGeometry->addPrimitiveSet(myprimitive);
	//m_myGeometry->setColorArray(colors);
	//m_myGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	//m_myGeometry->setTexCoordArray( 0, myTexts);



	//osg::StateSet* stateSet = myGeode->getOrCreateStateSet();

	// Enable blending, select transparent bin.
	//stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
	//stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );


	//osg::ref_ptr<osg::Texture2D> KLN89FaceTexture = new osg::Texture2D;

	//// protect from being optimized away as static state:
	//KLN89FaceTexture->setDataVariance(osg::Object::DYNAMIC); 

	//// load an image by reading a file: 
	//osg::Image* klnFace = osgDB::readImageFile(textname);

	//// Assign the texture to the image we read from file: 
	//KLN89FaceTexture->setImage(klnFace);

	//KLN89FaceTexture->setFilter(osg::Texture::FilterParameter::MIN_FILTER, osg::Texture::FilterMode::LINEAR);
	//KLN89FaceTexture->setFilter(osg::Texture::FilterParameter::MAG_FILTER, osg::Texture::FilterMode::LINEAR);
	//KLN89FaceTexture->setUseHardwareMipMapGeneration(true);
	//KLN89FaceTexture->setResizeNonPowerOfTwoHint(false);

	//// Assign texture unit 0 of our new StateSet to the texture 
	//// we just created and enable the texture.
	//stateSet->setTextureAttributeAndModes
	//  (0,KLN89FaceTexture,osg::StateAttribute::ON);



	//if(myVerticesPoly->size() == 0)
	//	empty = true;


	//return myGeode;
}

void	IslandSection::loadCutGroups(unsigned char *objBuffer, std::map<unsigned int, CutGroup>& cutGroups)
{
	/* Loading subtextures */
	IslandObjectHeader *header = (IslandObjectHeader *)objBuffer;
	unsigned int *cutInt = (unsigned int *)(objBuffer + header->cutSectionOffset);
	unsigned char *cutChar = objBuffer + header->cutSectionOffset;



	/* Loading texture buffer */
	unsigned char texture[256 * 256];
	mILE->LoadEntry(3);
	mILE->Read(texture, 256 * 256);
	
	for (unsigned int i = 0; i < header->cutSectionSize; ++i)
	{
		std::stringstream iss;
		
		unsigned char x = cutChar[0];
		unsigned char y = cutChar[1];
		unsigned char width = cutChar[2];
		unsigned char height = cutChar[3];
		
		iss << mIslandName << "_OBJ_CUT_" << (int)x << "_" << (int)y << "_" << (int)width << "_" << (int)height <<".png";

		bool transparent = ImageManager::getSingleton()->createTexture(x, y, width, height, texture, iss.str(), false);

		cutGroups.insert(std::pair<unsigned int, CutGroup>(*cutInt, CutGroup(iss.str(), x, y, width, height, transparent)));
		cutInt++;
		
		cutChar += 4;


		//Create Texture

	//	if (!(MaterialManager::getSingleton().resourceExists(iss.str())))
	//	{
	//		/* Loading texture buffer */
	//		unsigned char texture[256 * 256];
	//		mILE->LoadEntry(3);
	//		mILE->Read(texture, 256 * 256);

	//		//Create Texture
	//		ImageManager::getSingleton().createTexture(iss.str(), x, y, width, height, texture);

	//		//Create Material
	//		MaterialPtr m = MaterialManager::getSingleton().getDefaultSettings()->clone(iss.str(), false);
	//		Pass *p = m->getTechnique(0)->getPass(0);
	//		p->setLightingEnabled(false);
	//		p->setAlphaRejectFunction(CMPF_GREATER);
	//		p->setAlphaRejectValue(128);
	//		p->setVertexColourTracking(TVC_AMBIENT);
	//		TextureUnitState *t = p->createTextureUnitState();
	//		t->setTextureName(iss.str());
	//		t->setColourOperationEx(LBX_MODULATE, LBS_TEXTURE, LBS_DIFFUSE);
	//		t->setTextureFiltering(TFO_NONE);
	//	}
	}
	//if (!(MaterialManager::getSingleton().resourceExists("OBLnoTexture")))
	//{
	//	MaterialPtr m = Ogre::MaterialManager::getSingleton().getDefaultSettings()->clone("OBLnoTexture", false);
	//	Pass *p = m->getTechnique(0)->getPass(0);
	//	p->setLightingEnabled(false);
	//	p->setVertexColourTracking(Ogre::TVC_DIFFUSE);
	//}
}

CutGroup::CutGroup(const std::string& mat, unsigned char x, unsigned char y, unsigned char width, 
				   unsigned char height, bool transparent)
	:	materialName(mat),
		//subMesh(NULL),
		x(x),
		y(y),
		width(width),
		height(height),
		currentIndex(0), usetexture(true),
		myVerticesPoly(new osg::Vec3Array),
		myprimitive(new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0)),
		colors(new osg::Vec4Array),
		myTexts(new osg::Vec2Array),
		istransparent(transparent)
{
	indices.reserve(1000);
}

OBLMinMaxBox::OBLMinMaxBox() :
	mx(32000),
	my(32000),
	mz(32000),
	Mx(-32000),
	My(-32000),
	Mz(-32000)
{
}