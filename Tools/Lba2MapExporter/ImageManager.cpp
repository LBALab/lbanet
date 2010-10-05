#include "ImageManager.h"

#include <IL/il.h>
#include <IL/ilu.h>

//template<> ImageManager *Ogre::Singleton<ImageManager>::ms_Singleton = 0;

ImageManager* ImageManager::_singletonInstance = NULL;


ImageManager::ImageManager()
{	
	loadPalette();
}

ImageManager::~ImageManager()
{
	//...
}


/***********************************************************
singleton pattern
***********************************************************/
ImageManager * ImageManager::getSingleton()
{
    if(!_singletonInstance)
    {
        _singletonInstance = new ImageManager();
		return _singletonInstance;
    }
    else
    {
		return _singletonInstance;
    }
}


void ImageManager::loadPalette()
{
	//HQRReader palFile(Config::getSingleton().mPATH_HQR + "RESS.HQR");
	HQRReader palFile("RESS.HQR");
	palFile.LoadEntry(1);

	//Read directly from the file into our palette buffer
	palFile.Read(mRawPalette, 256 * 3);

	//The first colour needs to be transparent
	mPalette[0] = colorrgba(1.0, 1.0, 1.0, 0.0);

    for (int i = 1; i < 256; ++i)
    {
        mPalette[i].r = ((float)mRawPalette[i * 3]) / 255.0f;
        mPalette[i].g = ((float)mRawPalette[i * 3 + 1]) / 255.0f;
        mPalette[i].b = ((float)mRawPalette[i * 3 + 2]) / 255.0f;
        mPalette[i].a = 1.0f;
    }
}

const colorrgba	&ImageManager::getColour(unsigned char ID)
{
	return mPalette[ID];
}

//return true if part of texture is transparent
bool ImageManager::createTexture(int OffsetX, int OffsetY, int Width, int Height, 
									unsigned char *Data, const std::string &filename, bool AddWhite)
{
	bool res = false;
	int OffsetWidth = Width + ((AddWhite) ? 256 : 0);


	unsigned char* pData = new unsigned char[OffsetWidth * Height * 4];

	// need this for shader so that the blank area also have transparent alpha
	if (AddWhite)
		memset(pData, 0/*255*/, OffsetWidth * Height * 4);


	//Fill Texture Buffer
	for (int iX = 0; iX < Width; ++iX)
	{
		for (int iY = 0; iY < Height; ++iY)
		{
			int palettePos = Data[(iY + OffsetY) * 256 + (iX + OffsetX)];
			pData[(iY * OffsetWidth + iX) * 4 + 0] = mRawPalette[palettePos * 3 + 0];
            pData[(iY * OffsetWidth + iX) * 4 + 1] = mRawPalette[palettePos * 3 + 1];
            pData[(iY * OffsetWidth + iX) * 4 + 2] = mRawPalette[palettePos * 3 + 2];
            pData[(iY * OffsetWidth + iX) * 4 + 3] = (palettePos) ? 255 : 0;

			if(!palettePos)
				res = true;
		}
	}
	

	ILuint imn;
	ilGenImages(1, &imn);
	ilBindImage(imn);
	ilTexImage( OffsetWidth, Height, 1, 4, IL_RGBA, IL_UNSIGNED_BYTE, pData);
	ilSaveImage(filename.c_str());
	ilDeleteImages(1, &imn);


	return res;
}









//
//Ogre::MaterialPtr ImageManager::createMaterial(const std::string &TextureName, bool Filtering)
//{
//	Ogre::MaterialPtr m = Ogre::MaterialManager::getSingleton().create(TextureName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
//    
//	Ogre::Pass *p = m->getTechnique(0)->getPass(0);
//    p->setLightingEnabled(false);
//	p->setAlphaRejectFunction(Ogre::CMPF_GREATER);
//    p->setAlphaRejectValue(128);
//    p->setVertexColourTracking(Ogre::TVC_AMBIENT);
//
//	Ogre::TextureUnitState *t = p->createTextureUnitState();
//	t->setTextureName(TextureName);
//		
//	if (Filtering)
//		t->setTextureFiltering(Ogre::TFO_BILINEAR);
//	else
//		t->setTextureFiltering(Ogre::TFO_NONE);
//
//	return m;
//}
