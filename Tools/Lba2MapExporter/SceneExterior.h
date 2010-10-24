#ifndef SCENE_EXTERIOR_H
#define SCENE_EXTERIOR_H

#pragma once

#include <map>
#include <string>
#include <vector>

//#include "IScene.h"
#include "IslandSection.h"

//#include "../../Config.h"
#include "ImageManager.h"


class SceneExterior// : public IScene
{
public:
	SceneExterior();

	void	load(const std::string& name);
	void	unload();

private:
	
	void	loadEnvironment();
	void	loadSections();

private:

	std::string		mName;
	HQRReader		*mILE;
	HQRReader		*mOBL;

	//Ogre::SceneNode		*mMainNode;

	//Ogre::Entity		*mSky;
	//Ogre::SceneNode		*mSkyNode;
	//Ogre::Entity		*mSea;
	//Ogre::SceneNode		*mSeaNode;

	//Raw Texture Info
	unsigned char		mSeaSkyTexture[256 * 256];
	unsigned char		mGroundTexture[256 * 256];

	//Sections
	unsigned char					mLayout[256];
	int								mNumSections;
	std::vector<IslandSection *>	mSections;


	//Collision Heightmap
	//struct Tile
	//{
	//	float Height;
	//	bool Direction;		
	//};
	//std::vector<Tile>	mTileList;
	//Tile *mTile[1024][1024];


};

#endif /* SCENE_EXTERIOR_H */
