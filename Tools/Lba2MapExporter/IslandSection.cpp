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

osg::ref_ptr<osg::Geode>	IslandSection::load(PhysicalInfo & physinfo)
{
	//Heightmapped terrain
	return loadGround(physinfo);	
}

osg::ref_ptr<osg::Geode>	IslandSection::loadGround(PhysicalInfo & physinfo)
{
	osg::Vec3Array* myVerticesPoly = new osg::Vec3Array;
	osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	osg::Vec4Array* colors = new osg::Vec4Array;
	osg::Vec2Array* myTexts = new osg::Vec2Array;

	std::stringstream issss;
	issss << "GROUND_" << mIndex;

	std::string iss = issss.str();
	

	/* Preparing vertex array */
	short heightmap[65][65];
	short maxHeight = 0;
	mILE->LoadEntry(3 + mIndex * 6 + 5);
	mILE->Read(heightmap, 65 * 65 * 2);
	std::vector<float> vertices;
	vertices.reserve(9 * 64 * 64 * 4 * 2);

	/* Preparing texture info array */
	GroundTextureInfo *textureInfo;
	mILE->LoadEntry(3 + mIndex * 6 + 4);
	textureInfo = new GroundTextureInfo[mILE->getSize() / 12];
	mILE->Read(textureInfo, mILE->getSize());



	/* Preparing intensity array */
	unsigned char intensity[65][65];
	mILE->LoadEntry(3 + mIndex * 6 + 6);
	mILE->Read(intensity, 65 * 65);



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
						physinfo.vertexes.push_back(	((((float)(xi) - 32)) + (mXpos * 64.0f)));
						physinfo.vertexes.push_back(	(((float)(heightmap[xi][yi])) / 256));
						physinfo.vertexes.push_back(1024+((((float)(64 - yi) - 32)) - (mYpos * 64.0f)));

						myVerticesPoly->push_back(osg::Vec3(	((((float)(xi) - 32)) + (mXpos * 64.0f)),
																((((float)(heightmap[xi][yi])) / 256)),
																(1024+(((float)(64 - yi) - 32)) - (mYpos * 64.0f))
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

								// check shader to understand why intens is used as alpha
								colors->push_back(osg::Vec4(colorVal.r,colorVal.g,colorVal.b, intens));
							}
							else
							{
								// check shader to understand why intens is used as alpha
								colors->push_back(osg::Vec4(intens,intens,intens, intens));
							}
					
							myTexts->push_back(osg::Vec2((textureInfo[tri[t].textureIndex].uv[uvOrder[i]].u / 65535.0f) * 0.5f, 
															textureInfo[tri[t].textureIndex].uv[uvOrder[i]].v / 65535.0f));


						}
						else/* if (mdMax < 2 || md == 0)*/
						{
							unsigned char color = (tri[t].textureBank * 16) + intensity[xi][yi];
							colorrgba colorVal = ImageManager::getSingleton()->getColour(color);

							colors->push_back(osg::Vec4(colorVal.r,colorVal.g,colorVal.b, 1.0f));
							myTexts->push_back(osg::Vec2(0.75f, 0.5f));

						}
					}

					/* Index */
					physinfo.indices.push_back(physinfo.indices.size());
					physinfo.indices.push_back(physinfo.indices.size());
					physinfo.indices.push_back(physinfo.indices.size());
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

osg::ref_ptr<osg::Group> IslandSection::loadObjects(std::map<int, bool > &mObjLibrary,
														int & objcounter)
{
	osg::ref_ptr<osg::Group> root = new osg::Group();


	unsigned char objInfo[40];
	mILE->LoadEntry(3 + mIndex * 6 + 1);
	mILE->Read(objInfo, 40);
	
	mNumObjects = *((unsigned int *)(objInfo + 8));

	std::ofstream luafile((mIslandName+"_server.lua").c_str(), std::ios::app);

	if (mNumObjects > 0)
	{
		mObjectInfo = new IslandObjectInfo [mNumObjects];
		mILE->LoadEntry(3 + mIndex * 6 + 2);
		mILE->Read(mObjectInfo, mILE->getSize());
		for (unsigned int i = 0; i < mNumObjects; ++i, ++objcounter)
		{			
			//osg::ref_ptr<osg::PositionAttitudeTransform> PAT = new osg::PositionAttitudeTransform();
			//PAT->setPosition (osg::Vec3(	(mObjectInfo[i].oz / 512.0f - 32)  + (mXpos * 64.0f), 
			//								(mObjectInfo[i].oy / 256.0f), 
			//								1024+((-mObjectInfo[i].ox / 512.0f + 32)  - (mYpos * 64.0f))
			//							));
			//PAT->setAttitude(osg::Quat(((mObjectInfo[i].angle + 4) * PI) / 8, osg::Vec3(0, 1, 0)));
			bool physicfile = loadSingleObject(&mObjectInfo[i], mObjLibrary);

			//PAT->addChild(tmpobject);
			//root->addChild(PAT);


			float posX = (mObjectInfo[i].oz / 512.0f - 32)  + (mXpos * 64.0f);
			float posY = (mObjectInfo[i].oy / 256.0f);
			float posZ = 1024+((-mObjectInfo[i].ox / 512.0f + 32)  - (mYpos * 64.0f));
			float rotation = (((((mObjectInfo[i].angle + 4) * PI) / 8) / PI) * 180);

			std::stringstream objname;
			objname<< mIslandName << "_OBJ_" << mObjectInfo[i].index + 1;
			luafile<<std::endl<<std::endl;
			luafile<<"	OBJ_"<<objcounter<<" = ActorObjectInfo("<<objcounter<<")"<<std::endl;
			luafile<<"	OBJ_"<<objcounter<<":SetRenderType(1)"<<std::endl;
			luafile<<"	OBJ_"<<objcounter<<".DisplayDesc.ModelName = \"Worlds/Lba2Original/Islands/"<<objname.str()<<".osgb\""<<std::endl;
			luafile<<"	OBJ_"<<objcounter<<".DisplayDesc.UseLight = false"<<std::endl;	
			luafile<<"	OBJ_"<<objcounter<<":SetModelState(1)"<<std::endl;
			luafile<<"	OBJ_"<<objcounter<<".PhysicDesc.Pos.X = "<<posX<<std::endl;
			luafile<<"	OBJ_"<<objcounter<<".PhysicDesc.Pos.Y = "<<posY<<std::endl;
			luafile<<"	OBJ_"<<objcounter<<".PhysicDesc.Pos.Z = "<<posZ<<std::endl;
			luafile<<"	OBJ_"<<objcounter<<".PhysicDesc.Pos.Rotation = "<<rotation<<std::endl;
			luafile<<"	OBJ_"<<objcounter<<":SetPhysicalActorType(1)"<<std::endl;

			if(physicfile)
			{
				luafile<<"	OBJ_"<<objcounter<<":SetPhysicalShape(5)"<<std::endl;
				luafile<<"	OBJ_"<<objcounter<<".PhysicDesc.Collidable = true"<<std::endl;
				luafile<<"	OBJ_"<<objcounter<<".PhysicDesc.Filename = \"Worlds/Lba2Original/Islands/"<<objname.str()<<".phy\""<<std::endl;
			}
			else
			{
				luafile<<"	OBJ_"<<objcounter<<":SetPhysicalShape(1)"<<std::endl;
				luafile<<"	OBJ_"<<objcounter<<".PhysicDesc.Collidable = false"<<std::endl;
			}

			luafile<<"	"<<"Map_"<<mIslandName<<":AddActorObject("<<"OBJ_"<<objcounter<<")"<<std::endl;
		}
		delete [] mObjectInfo;
	}

	return root;
}

void	IslandSection::addPolygonSection(unsigned char *buffer, OBLPolygonHeader *header, 
										 std::map<unsigned int, CutGroup>& cutGroups, 
										 CutGroup &subColor, PhysicalInfo & physinfo, 
										 int& currentIndex, OBLMinMaxBox& mMBox,
											osg::Vec3Array* myVertices)
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
				physinfo.vertexes.push_back(oBLvertices[polygon->idx[j]].x  / 512.0f);
				physinfo.vertexes.push_back(oBLvertices[polygon->idx[j]].y  / 256.0f);
				physinfo.vertexes.push_back(oBLvertices[polygon->idx[j]].z  / 512.0f);

				cut->myVerticesPoly->push_back(osg::Vec3(	(oBLvertices[polygon->idx[j]].x  / 512.0f),
															(oBLvertices[polygon->idx[j]].y  / 512.0f),
															((oBLvertices[polygon->idx[j]].z  / 512.0f))
														));


				/* Color */
				if (/*header->id >= 7 && */cut->usetexture)
				{
					cut->colors->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));

					cut->myTexts->push_back(osg::Vec2(	((polygon->uv[j].u * uvFactor) / 65536.0f)/* * 0.5f*/, 
													((polygon->uv[j].v * uvFactor) / 65536.0f)
															));

				}
				else
				{
					const colorrgba& color = ImageManager::getSingleton()->getColour(polygon->color + oBLintensities[polygon->idx[j]].i[1] / 32);
					cut->colors->push_back(osg::Vec4(color.r,color.g,color.b, 1.0f));

					//cut->myTexts->push_back(osg::Vec2(0.75f, 0.5f));
				}

			}
			cut->myprimitive->push_back(cut->currentIndex);
			cut->myprimitive->push_back(cut->currentIndex + 1);
			cut->myprimitive->push_back(cut->currentIndex + 2);

			physinfo.indices.push_back(currentIndex);
			physinfo.indices.push_back(currentIndex + 1);
			physinfo.indices.push_back(currentIndex + 2);


			if (header->type & 0x80)
			{
				cut->myprimitive->push_back(cut->currentIndex);
				cut->myprimitive->push_back(cut->currentIndex + 2);
				cut->myprimitive->push_back(cut->currentIndex + 3);

				physinfo.indices.push_back(currentIndex);
				physinfo.indices.push_back(currentIndex + 2);
				physinfo.indices.push_back(currentIndex + 3);
			}
			cut->currentIndex += numPoints;
			currentIndex += numPoints;
			cut->myprimitivenumpoints.push_back(numPoints);
			polygon = (OBLPolygon *)(((char *)polygon) + blockSize);
		}
	}

}

bool	IslandSection::loadSingleObject(IslandObjectInfo *objInfo,
															std::map<int, bool > &mObjLibrary)
{
	//Check if we have this OBL Index Logged
	if (mObjLibrary.find(objInfo->index + 1) != mObjLibrary.end())
	{
		//std::cout << "Dupe Found\n";
		return mObjLibrary[objInfo->index + 1];
	}
	else
	{
		osg::ref_ptr<osg::PositionAttitudeTransform> root = new osg::PositionAttitudeTransform;
		root->setScale(osg::Vec3(1,2,1));

		PhysicalInfo physinfo;


		/* Loading the data */
		mOBL->LoadEntry(objInfo->index + 1);


		const int bufSize = mOBL->getSize();
		unsigned char *objBuffer = new unsigned char [bufSize];
		mOBL->Read(objBuffer, bufSize);
		IslandObjectHeader *header = (IslandObjectHeader *)objBuffer;

		/* Preparing the mesh */
		std::map<unsigned int, CutGroup> cutGroups;
		loadCutGroups(objBuffer, /*msh, */cutGroups);
		CutGroup colorSub("OBLnoTexture", 0, 0, 0, 0, false);
		colorSub.usetexture = false;
		int currentIndex = 0;
		//std::vector<float> vertices;
		//vertices.reserve(2000);

		osg::Vec3Array *myVertices(new osg::Vec3Array);
		{
			IslandObjectHeader *oBLheader = (IslandObjectHeader *)objBuffer;
			OBLVertex *oBLvertices = (OBLVertex *)(objBuffer + 0x68);

			// push vertices for points and spheres
			for(int i=0; i<oBLheader->numVerticesType1; ++i)
			{
				myVertices->push_back(osg::Vec3(	(oBLvertices[i].x  / 512.0f),
													(oBLvertices[i].y  / 512.0f),
													((oBLvertices[i].z  / 512.0f))
														));
			}
		}



		/* Loading the polygons */
		OBLMinMaxBox mMBox;
		OBLPolygonHeader *polyHead = (OBLPolygonHeader *)(objBuffer + header->polygonSectionOffset);
		while (polyHead->size > 0 && ((unsigned char*)polyHead) < (objBuffer + header->lineSectionOffset))
		{
			addPolygonSection(objBuffer, polyHead, cutGroups, colorSub, physinfo, currentIndex, mMBox, myVertices/*, 
									myVerticesPoly,myprimitive,colors,myTexts*/);

			polyHead = (OBLPolygonHeader *)(((unsigned char *)polyHead) + polyHead->size);
		}


		cutGroups.insert(std::pair<unsigned int, CutGroup>(0, colorSub));
		std::map<unsigned int, CutGroup>::iterator it, end;
		for (it = cutGroups.begin(), end = cutGroups.end(); it != end; ++it)
		{
			if (it->second.myprimitive->size() != 0)
			{
				osg::ref_ptr<osg::Geode> myGeode = new osg::Geode();
				osg::ref_ptr<osg::Geometry> m_myGeometry = new osg::Geometry();
				myGeode->addDrawable(m_myGeometry.get());
				m_myGeometry->setVertexArray( it->second.myVerticesPoly ); 
				m_myGeometry->addPrimitiveSet(it->second.myprimitive);
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

					KLN89FaceTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::/*NEAREST*/LINEAR);
					KLN89FaceTexture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::/*NEAREST*/LINEAR);
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
					osg::ref_ptr<osg::Sphere> unitSphere = new osg::Sphere(center, ((float)localData->SpheresData[i].Size)/512.0f);
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

		delete [] objBuffer;


		std::stringstream iss;
		iss << mIslandName << "_OBJ_" << objInfo->index + 1;


		osg::StateSet* statesetroot = root->getOrCreateStateSet();
		statesetroot->setMode(GL_LIGHTING, osg::StateAttribute::OFF);


		osgUtil::Optimizer optOSGFile;
		optOSGFile.optimize (root.get());

		osgDB::writeNodeFile(*root.get(), iss.str() + ".osgb", new osgDB::Options("Compressor=zlib"));


		if(physinfo.vertexes.size() > 0 && physinfo.indices.size() > 0)
		{
			std::ofstream filebit((iss.str() + ".phy").c_str(), std::ofstream::binary);
			unsigned int sizevertex = physinfo.vertexes.size();
			unsigned int sizeindices = physinfo.indices.size();
			unsigned int sizematerials = physinfo.materials.size();
			filebit.write((char*)&sizevertex, sizeof(unsigned int));
			filebit.write((char*)&sizeindices, sizeof(unsigned int));
			filebit.write((char*)&sizematerials, sizeof(unsigned int));

			filebit.write((char*)&physinfo.vertexes[0], sizevertex*sizeof(float));
			filebit.write((char*)&physinfo.indices[0], sizeindices*sizeof(unsigned int));
			if(sizematerials > 0)
				filebit.write((char*)&physinfo.materials[0], sizematerials*sizeof(short));

			mObjLibrary[objInfo->index + 1] = true;
			return true;
		}

		mObjLibrary[objInfo->index + 1] = false;
		return false;
	}
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
	}
}

CutGroup::CutGroup(const std::string& mat, unsigned char x, unsigned char y, unsigned char width, 
				   unsigned char height, bool transparent)
	:	materialName(mat),
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