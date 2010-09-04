#ifndef TEXTURELOADER_H_INCLUDED
#define TEXTURELOADER_H_INCLUDED



class LBATextureLoader
{
public:
	LBATextureLoader();

	void	setData(unsigned char *textureData, bool white = false);
    void	setData(unsigned char *textureData, int x, int y, int w, int h);

 //   void    loadResource(Ogre::Resource *);
	//void	loadTexture(Ogre::Texture *);
	//void	loadTextureWhite(Ogre::Texture *);
	//void	loadSubTexture(Ogre::Texture *);

	//const Ogre::ColourValue	&getColour(unsigned char idx);

private:
    unsigned char   *mTextureData;

    int             mX;
    int             mY;
    int             mW;
    int             mH;

	enum Mode
	{
		TEXTURE,
		TEXTURE_WHITE,
		SUBTEXTURE
	}				mMode;
};

#endif // TEXTURELOADER_H_INCLUDED
