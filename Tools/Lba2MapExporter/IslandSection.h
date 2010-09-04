#ifndef ISLANDSECTION_H_
#define ISLANDSECTION_H_

#pragma once

#include <map>
#include <vector>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>

#include "HQRReader.h"
#include "ILEdataStructures.h"

#include "ImageManager.h"

struct OBLMinMaxBox
{
	OBLMinMaxBox();
	short	mx;
	short	my;
	short	mz;
	short	Mx;
	short	My;
	short	Mz;
};

struct CutGroup
{
	CutGroup(const std::string&, unsigned char, unsigned char, unsigned char, unsigned char);
	std::string					materialName;
	//Ogre::SubMesh				*subMesh;
	std::vector<unsigned short>	indices;
	unsigned char				x;
	unsigned char				y;
	unsigned char				width;
	unsigned char				height;

	osg::Vec3Array*				myVerticesPoly;
	osg::DrawElementsUInt*		myprimitive;
	osg::Vec4Array*				colors;
	osg::Vec2Array*				myTexts;

	int							currentIndex;

	bool						usetexture;

};

class IslandSection
{
public:
	IslandSection(const std::string& islandName, HQRReader *ILE, HQRReader *OBL, int idx, int xpos, int ypos);
	osg::ref_ptr<osg::Geode> load(std::set<std::pair<unsigned short, unsigned short> > & texturesinfos);
	osg::ref_ptr<osg::Group>	loadObjects(std::map<int, osg::ref_ptr<osg::Group> > &mObjLibrary);


private:
	osg::ref_ptr<osg::Geode>	loadGround(std::set<std::pair<unsigned short, unsigned short> > & texturesinfos);

	osg::ref_ptr<osg::Group>	loadSingleObject(IslandObjectInfo *objInfo,
													std::map<int, osg::ref_ptr<osg::Group> > &mObjLibrary);
	void	addPolygonSection(unsigned char *, OBLPolygonHeader *, std::map<unsigned int, CutGroup>&, 
								CutGroup&, std::vector<float>&, int&, OBLMinMaxBox&,
											osg::Vec3Array* myVertices/*,
											osg::DrawElementsUInt* myprimitive,
											osg::Vec4Array* colors,
											osg::Vec2Array* myTexts*/);
	void	loadCutGroups(unsigned char *, std::map<unsigned int, CutGroup>&);

private:
	HQRReader	*mILE;
	HQRReader	*mOBL;

	std::string			mIslandName;
	//Ogre::SceneManager *mSceneMgr;
	int					mIndex;
	int					mXpos;
	int					mYpos;
	//Ogre::SceneNode		*mNode;
	//Ogre::Entity		*mGround;
	//Ogre::SceneNode		*mGroundNode;
	unsigned int		mNumObjects;
	IslandObjectInfo	*mObjectInfo;
};

#endif /* ISLANDSECTION_H_ */
