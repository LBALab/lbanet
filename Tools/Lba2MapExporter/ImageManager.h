#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#pragma once

#include "HQRReader.h"
//#include "Config.h"


struct colorrgba
{
	colorrgba()
		: r(0), g(0), b(0), a(0)
	{}

	colorrgba(float R, float G, float B, float A)
		: r(R), g(G), b(B), a(A)
	{}

	float r;
	float g;
	float b;
	float a;
};


class ImageManager
{
public:

	ImageManager();
	~ImageManager();

	//Game Palette
	unsigned char		mRawPalette[256*3];
    colorrgba			mPalette[256];

	 static ImageManager * getSingleton();


	const colorrgba	&getColour(unsigned char ID);

	bool createTexture(int OffsetX, int OffsetY, int Width, int Height, 
						unsigned char *Data, const std::string &filename, bool AddWhite = false);

private:

	static ImageManager *		_singletonInstance;

	void loadPalette();
};

#endif
