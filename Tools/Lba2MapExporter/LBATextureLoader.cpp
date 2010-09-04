
#include "LBATextureLoader.h"
#include "HQRReader.h"

//#include "../../Config.h"

#include "ImageManager.h"

//template<> LBATextureLoader *Ogre::Singleton<LBATextureLoader>::ms_Singleton = 0;

LBATextureLoader::LBATextureLoader()
{
	//...
}

void		LBATextureLoader::setData(unsigned char *textureData, bool white)
{
	mTextureData = textureData;
	if (white)
		mMode = TEXTURE_WHITE;
	else
		mMode = TEXTURE;
}

void		LBATextureLoader::setData(unsigned char *textureData, int x, int y, int w, int h)
{
	mTextureData = textureData;
	mX = x;
	mY = y;
	mW = w;
	mH = h;
	mMode = SUBTEXTURE;
}
//
//void        LBATextureLoader::loadResource(Ogre::Resource *res)
//{
//    Ogre::Texture *ptex = static_cast<Ogre::Texture *>(res);
//	switch (mMode)
//	{
//		case TEXTURE:
//			loadTexture(ptex);
//			break;
//		case TEXTURE_WHITE:
//			loadTextureWhite(ptex);
//			break;
//		case SUBTEXTURE:
//			loadSubTexture(ptex);
//			break;
//	}
//}
//
//void	LBATextureLoader::loadTexture(Ogre::Texture *ptex)
//{
//	mW = 256;
//	mH = 256;
//	mX = 0;
//	mY = 0;
//	loadSubTexture(ptex);
//}
//
//void	LBATextureLoader::loadTextureWhite(Ogre::Texture *ptex)
//{
//    unsigned char *endTexture = new unsigned char [512 * 256 * 4];
//	memset(endTexture, 255, 512 * 256 * 4);
//    for (int i = 0; i < 256; ++i)
//        for (int j = 0; j < 256; ++j)
//        {
//            /*
//			Ogre::ColourValue& color = Engine::getSingleton().mPalette[ mTextureData[j * 256 + i] ];
//            endTexture[(j * 512 + i) * 4] = (unsigned char)(color.r * 255.0);
//            endTexture[(j * 512 + i) * 4 + 1] = (unsigned char)(color.g * 255.0);
//            endTexture[(j * 512 + i) * 4 + 2] = (unsigned char)(color.b * 255.0);
//            endTexture[(j * 512 + i) * 4 + 3] = (mTextureData[j * 256 + i]) ? 255 : 0;
//			*/
//
//			int palettePos = mTextureData[j * 256 + i];
//            endTexture[(j * 512 + i) * 4 + 0] = ImageManager::getSingleton().mRawPalette[palettePos * 3 + 0];
//            endTexture[(j * 512 + i) * 4 + 1] = ImageManager::getSingleton().mRawPalette[palettePos * 3 + 1];
//            endTexture[(j * 512 + i) * 4 + 2] = ImageManager::getSingleton().mRawPalette[palettePos * 3 + 2];
//            endTexture[(j * 512 + i) * 4 + 3] = (palettePos) ? 255 : 0;
//        }
//
//    ptex->getBuffer(0, 0)->blitFromMemory(Ogre::PixelBox(512, 256, 1, Ogre::PF_BYTE_RGBA, endTexture));
//    delete [] endTexture;
//}
//
//void	LBATextureLoader::loadSubTexture(Ogre::Texture *ptex)
//{
//    unsigned char *subTextureData = new unsigned char [mW * mH * 4];
//    for (int i = 0; i < mW; ++i)
//        for (int j = 0; j < mH; ++j)
//        {
//            int si = i + mX;
//            int sj = j + mY;
//            /*
//			Ogre::ColourValue& color = Engine::getSingleton().mPalette[ mTextureData[sj * 256 + si] ];
//            subTextureData[(j * mW + i) * 4] = (unsigned char)(color.r * 255.0);
//            subTextureData[(j * mW + i) * 4 + 1] = (unsigned char)(color.g * 255.0);
//            subTextureData[(j * mW + i) * 4 + 2] = (unsigned char)(color.b * 255.0);
//            subTextureData[(j * mW + i) * 4 + 3] = (mTextureData[sj * 256 + si]) ? 255 : 0;
//			*/
//
//			int palettePos =  mTextureData[sj * 256 + si];
//            subTextureData[(j * mW + i) * 4 + 0] = ImageManager::getSingleton().mRawPalette[palettePos * 3 + 0];
//            subTextureData[(j * mW + i) * 4 + 1] = ImageManager::getSingleton().mRawPalette[palettePos * 3 + 1];
//            subTextureData[(j * mW + i) * 4 + 2] = ImageManager::getSingleton().mRawPalette[palettePos * 3 + 2];
//            subTextureData[(j * mW + i) * 4 + 3] = (palettePos) ? 255 : 0;
//        }
//    ptex->getBuffer(0, 0)->blitFromMemory(Ogre::PixelBox(mW, mH, 1, Ogre::PF_BYTE_RGBA, subTextureData));
//    delete [] subTextureData;
//}
//
//const Ogre::ColourValue	&LBATextureLoader::getColour(unsigned char idx)
//{
//	return ImageManager::getSingleton().mPalette[idx];
//}
