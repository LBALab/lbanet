#include "CEGUIDrawable.h"
#include "GuiHandler.h"


#include <CEGUI.h>
#include <RendererModules/OpenGL/CEGUIOpenGLRenderer.h>
#include <CEGUIScriptModule.h>
#include <CEGUIFontManager.h>
#include <CEGUISchemeManager.h>
#include <CEGUIWindowManager.h>
#include <CEGUIExceptions.h>

#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>
#include <osgDB/ReadFile> 

#include <iostream>


#include "FONT_FONT.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include "LogHandler.h"

#include "EventsQueue.h"
#include "ClientExtendedEvents.h"
#include "SynchronizedTimeHandler.h"


// load font from TTF file
static bool load_ttf(FONT_FONT	&font, string fontfilename,int average_advance)
{
	FT_Library    library;
	FT_Face       face;
	FT_GlyphSlot  slot;
	FT_Error      error;

	FT_Init_FreeType( &library );              /* initialize library */
	FT_New_Face( library, fontfilename.c_str(), 0, &face ); /* create face object */
	slot = face->glyph;

	if(FT_Select_Charmap(face,FT_ENCODING_UNICODE)!=0)
	{
		LogHandler::getInstance()->LogToFile("font file not found or no UNICODE char map for this font: " + fontfilename);
		return false;
	}

	font.name.clear();
	font.name.append(fontfilename.substr(0,fontfilename.length()-4).c_str());
	int fontsize=0;
	int temp=0;
	while(1) //incrementing "fontsize" until average advance math user value.
	{
		fontsize++;
		FT_Set_Pixel_Sizes(face,fontsize,fontsize);
		temp=0;
		for ( int n = 65; n < 91; n++ )
		{
			FT_Load_Char( face, n, FT_LOAD_RENDER );
			temp+=slot->metrics.horiAdvance;
		}
		for ( int n = 97; n < 123; n++ )
		{
			FT_Load_Char( face, n, FT_LOAD_RENDER );
			temp+=slot->metrics.horiAdvance;
		}
		temp/=52;
		if(temp/64<=average_advance)
			font.average_advance=temp/64;
		else 
			break;
	}
	fontsize--;
	FT_Set_Pixel_Sizes(face,fontsize,fontsize);

	int ymax=0;
	int ymin=0;
	for ( int n = 0; n < 256; n++ )
	{
		FT_Load_Char( face, n, FT_LOAD_RENDER );
		if(slot->metrics.horiBearingY>ymax)ymax=slot->metrics.horiBearingY;
		if(slot->metrics.horiBearingY-slot->metrics.height<ymin)ymin=slot->metrics.horiBearingY-slot->metrics.height;
	}
	font.origin=ymax/64;
	font.char_height=(ymax-ymin)/64;
	for(int i=0;i<1024*1024;i++)
	font.map.push_back(0);
	int cursorx=0,cursory=0;
	for(int n=0;n<256;n++)
	{
		FONT_GLYPH glyph;
		FT_Load_Char( face, n, FT_LOAD_RENDER );
		FT_Bitmap*  bitmap=&slot->bitmap;
		glyph.width=bitmap->width;
		glyph.dx=slot->metrics.horiBearingX/64;
		glyph.advance=slot->metrics.horiAdvance/64 ;
		if(cursorx+glyph.width>1024)cursorx=0,cursory+=font.char_height;
		if(cursory>=1024-font.char_height)
		{
			LogHandler::getInstance()->LogToFile("cannot export font in a 1024x1024 texture, try to reduce font average width");
			return false;
		}
		for ( int x = 0; x < bitmap->width; x++)
		{
			for ( int y = 0; y < bitmap->rows; y++)
			{
			  int dy=ymax/64-slot->metrics.horiBearingY/64;
			  //glyph[n].map[(j+dy)*width+i] = bitmap->buffer[q * width + p];
			  font.map[(cursory+y+dy)*1024+cursorx+x]=bitmap->buffer[y * glyph.width + x];//glyph[n].map[y*glyph[n].width+x];
			}
		}

		glyph.mapx=cursorx;
		glyph.mapy=cursory;
		cursorx+=glyph.width;
		font.glyph.push_back(glyph);
	}
	FT_Done_Face    ( face );
	FT_Done_FreeType( library );
	return true;
}

struct CEGUIEventCallback : public osgGA::GUIEventHandler
{
	int lastwidth;
	int lastheight;
	boost::shared_ptr<GuiHandler>	_GuiH;

    CEGUIEventCallback(boost::shared_ptr<GuiHandler> GuiH) 
	{
		lastwidth = -1;
		lastheight = -1;
		_GuiH = GuiH;
	}
    
	bool CEGUIEventCallback::handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa, osg::Object* obj, osg::NodeVisitor* nv)
	{
		float x = ea.getX();
		float y = ea.getY();
		bool injectionRetVal = false;

		// CEGUI wants 0,0 in the top left corner; osg has 0,0 in the bottom left corner
		y = ea.getWindowHeight() - y;

		switch(ea.getEventType())
		{

		case(osgGA::GUIEventAdapter::RESIZE):
			{
				int width = ea.getWindowWidth();
				int height = ea.getWindowHeight();
				if((width != lastwidth) || (height != lastheight))
				{
					if(_GuiH)
						_GuiH->Resize(width, height, lastwidth, lastheight);

					lastwidth = width;
					lastheight = height;
				}
				break;
			}


		default:
			break;
		}
		

		CEGUI::Window* window = CEGUI::System::getSingleton().getGUISheet()->getCaptureWindow();
		if (window/* && window->getParent()*/) // does not work on redim
		{
			return injectionRetVal;
		}

		// do not consume the event, forward on to osg::Viewer
		return false;
	}
};

/***********************************************************
constructor
***********************************************************/
CEGUIDrawable::CEGUIDrawable()
: _drawXtraGL(false), _scrolling(false), _scrollingtimediff(0),
	_loadedfont(NULL), _fontloaded(false), _imageloaded(false),
	_currentstate(XtGLw_Off), _textfinishdisplaytime(-1), 
	_currentfadestate(XtGLw_FDOff), _bgR(0), _bgG(0), _bgB(0), _bgA(1),
	_fontsize(10)
{
	setSupportsDisplayList(false);
	_keepcallbakc = new CEGUIEventCallback(boost::shared_ptr<GuiHandler>());
	setEventCallback(_keepcallbakc);
	_activeContextID = 0;
}


/***********************************************************
constructor
***********************************************************/
CEGUIDrawable::CEGUIDrawable(int resX, int resY, boost::shared_ptr<GuiHandler> GuiH)
: _GuiH(GuiH), _drawXtraGL(false), _scrolling(false), _scrollingtimediff(0),
	_loadedfont(NULL), _fontloaded(false), _imageloaded(false),
	_currentstate(XtGLw_Off), _textfinishdisplaytime(-1), 
	_currentfadestate(XtGLw_FDOff), _bgR(0), _bgG(0), _bgB(0), _bgA(1)
{
	try
	{
		setSupportsDisplayList(false);

		_keepcallbakc = new CEGUIEventCallback(_GuiH);
		setEventCallback(_keepcallbakc);

		if(_GuiH)
			_GuiH->Initialize(resX, resY);

		_activeContextID = 0;
	}
	catch(CEGUI::Exception &ex)
	{
		std::cout<<  ex.getMessage().c_str()<<std::endl;
	}

}


/***********************************************************
destructor
***********************************************************/
CEGUIDrawable::~CEGUIDrawable()
{
	DeleteFont();
	CleanImageTexture();
}

/***********************************************************
release stuff
***********************************************************/
void CEGUIDrawable::Release()
{
	DeleteFont();
	CleanImageTexture();

	_GuiH = boost::shared_ptr<GuiHandler>();
	_keepcallbakc->_GuiH = boost::shared_ptr<GuiHandler>();
}



/***********************************************************
drawImplementation
***********************************************************/
void CEGUIDrawable::drawImplementation(osg::RenderInfo& renderInfo) const
{
    osg::State* state = renderInfo.getState();
    if (state->getContextID()!=_activeContextID) 
		return;

	// draw cegui stuff
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    state->disableAllVertexArrays();

    CEGUI::System::getSingleton().renderGUI();
    glPopAttrib();



	int sX, sY;
	_GuiH->GetScreenSize(sX, sY);

	//draw overlay
	if(_GuiH && _GuiH->ShouldDrawOverlay())
	{
		float life, mana;
		_GuiH->GetLifeManaInfo(life, mana);
		
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, sX, sY, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);

		int offsetx = 67;
		int sizex = 79;
		glDisable(GL_TEXTURE_2D);
		glBegin(GL_QUADS);
			glColor3f(115/255.f, 0.f, 2/255.f);
			glVertex2f(offsetx,11);					
			glVertex2f(offsetx+(sizex*life),11);	
			glColor3f(254/255.f, 0.f, 3/255.f);
			glVertex2f(offsetx+(sizex*life),7);					
			glVertex2f(offsetx,7);	

			glColor3f(11/255.f, 11/255.f, 71/255.f);
			glVertex2f(offsetx,20);					
			glVertex2f(offsetx+(sizex*mana),20);	
			glColor3f(13/255.f, 12/255.f, 150/255.f);
			glVertex2f(offsetx+(sizex*mana),16);					
			glVertex2f(offsetx,16);	
		glEnd();


		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW); 
	}

	if(_drawXtraGL)
	{
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0, sX, sY, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glEnable(GL_TEXTURE_2D);
		//glDisable(GL_LIGHTING);
		//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
		//glHint(GL_POLYGON_SMOOTH, GL_NICEST);

		paintXtraGL();

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW); 
	}

    
    state->checkGLErrors("CEGUIDrawable::drawImplementation");
}


		
void CEGUIDrawable::write_line(const std::vector<unsigned int> &text, bool black,
									double x, double y, double space_size, int nbchar) const
{
	glBegin(GL_QUADS);

	for(int i=0;i<nbchar && i<text.size();i++)
	{
		unsigned int n=text[i];
		if(n==' ')
			x+=space_size;
		else
		{
			if(black)
			{
				glColor3d(0,0,0);
			}
			else
			{
				glColor3d(min(0.8,(nbchar-i)/10.),
						  min(0.8,(nbchar-i)/10.),
						  min(0.8,(nbchar-i)/10.));
			}


			glTexCoord2d((_loadedfont->glyph[n].mapx)/1024.,											(_loadedfont->glyph[n].mapy			+_loadedfont->char_height)/1024.);
			glVertex2f(	(int)x+_loadedfont->glyph[n].dx,												(int)y-_loadedfont->origin          +_loadedfont->char_height);
			glTexCoord2d((_loadedfont->glyph[n].mapx            +_loadedfont->glyph[n].width)/1024.,    (_loadedfont->glyph[n].mapy			+_loadedfont->char_height)/1024.);
			glVertex2f(	(int)x+_loadedfont->glyph[n].dx         +_loadedfont->glyph[n].width,           (int)y-_loadedfont->origin          +_loadedfont->char_height);		
			glTexCoord2d((_loadedfont->glyph[n].mapx            +_loadedfont->glyph[n].width)/1024.,    (_loadedfont->glyph[n].mapy)/1024.);
			glVertex2f(	(int)x+_loadedfont->glyph[n].dx         +_loadedfont->glyph[n].width,           (int)y-_loadedfont->origin);			
			glTexCoord2d((_loadedfont->glyph[n].mapx/1024.),											(_loadedfont->glyph[n].mapy)/1024.);
			glVertex2f(	(int)x+_loadedfont->glyph[n].dx,												(int)y-_loadedfont->origin);
			x+=_loadedfont->glyph[n].advance;
		}
	}
	glEnd();
}


void CEGUIDrawable::CreateLBAFont(int size)
{
	DeleteFont();

	if(_loadedfont)
	{
		delete _loadedfont;
		_loadedfont = false;
	}

	_loadedfont = new FONT_FONT();
	load_ttf(*_loadedfont, "Data/GUI/fonts/lubalingraphstd-demi.otf", size);


    glGenTextures( 1, &_textureid);
	_fontloaded = true;

    glBindTexture( GL_TEXTURE_2D, _textureid );
    char *map=new char[1024*1024*4];
    for(int i=0;i<_loadedfont->map.size();i++)
    {
        map[i*4+0]=_loadedfont->map[i];
        map[i*4+1]=_loadedfont->map[i];
        map[i*4+2]=_loadedfont->map[i];
        map[i*4+3]=_loadedfont->map[i];
    }
    glTexImage2D(GL_TEXTURE_2D, 0, 4, 1024,1024, 0, GL_RGBA, GL_UNSIGNED_BYTE,map);
    delete map;
}


void CEGUIDrawable::DeleteFont()
{
	if(_loadedfont)
	{
		delete _loadedfont;
		_loadedfont = false;
	}

	if(_fontloaded)
	{
		glDeleteTextures(1, &_textureid);
		_fontloaded = false;
	}
}



 void CEGUIDrawable::LoadGLTextures( const std::string& name )
{
	CleanImageTexture();
	if(name == "")
		return;

    osg::ref_ptr<osg::Image> klnFace = osgDB::readImageFile(name);
    if(!klnFace)
    {
		LogHandler::getInstance()->LogToFile("error loading image to texture: " + name);
        return;
    }

    glGenTextures( 1, &_imgtextureid);
    glBindTexture( GL_TEXTURE_2D, _imgtextureid );
    glTexImage2D(GL_TEXTURE_2D, 0, klnFace->getInternalTextureFormat(), 
					klnFace->s(),klnFace->t(), 0, klnFace->getPixelFormat(), 
					klnFace->getDataType(), klnFace->getDataPointer());
	_imageloaded = true;
}


void CEGUIDrawable::CleanImageTexture()
{
	if(_imageloaded)
	{
		glDeleteTextures(1, &_imgtextureid);
		_imageloaded = false;
	}
}



void CEGUIDrawable::Process(double tnow, float tdiff)
{
	if(_currentstate == XtGLw_Text)
	{
		if(_scrolling)
			_scrollingtimediff += tdiff;

		if(_textpageidx < _precalculated_text.size())
			prepare_text(_precalculated_text[_textpageidx], (int)(_scrollingtimediff/60));
	}
	else
	{
		// do fading/timeout
		switch(_currentfadestate)
		{
			case XtGLw_FDIn:
			{
				_bgR=_fiR;
				_bgG=_fiG;
				_bgB=_fiB;

				_currentalpha += 0.02f;
				if(_currentalpha >= 1)
				{
					_currentalpha = 1;
					_currentfadestate = XtGLw_FDOff;
				}
			}
			break;

			case XtGLw_FDOut:
			{
				_bgR=_foR;
				_bgG=_foG;
				_bgB=_foB;

				_currentalpha -= 0.02f;
				if(_currentalpha <= 0)
				{
					_currentalpha = 0;
					_currentfadestate = XtGLw_FDOff;
					CleanAndReport();
				}
			}
			break;

			case XtGLw_FDOff:
			{
				//fixed image timeout
				if((_textfinishdisplaytime > 0) && (_textfinishdisplaytime <= tnow))
				{
					_textfinishdisplaytime = -1;
					if(_fadingout)
					{
						_currentalpha = 1;
						_currentfadestate = XtGLw_FDOut;
					}
					else
						CleanAndReport();
				}
			}
		}
	}
}


// clean up display
void CEGUIDrawable::CleanUp()
{
	_textfinishdisplaytime = -1;
	_currentstate = XtGLw_Off;
	_currentfadestate = XtGLw_FDOff;
	_bgR = 0;
	_bgG = 0;
	_bgB = 0;
	_bgA = 1;
	CleanImageTexture();
}

// clean up display and report termination
void CEGUIDrawable::CleanAndReport()
{
	CleanUp();
	EventsQueue::getReceiverQueue()->AddEvent(new DisplayExtraGLFinishedEvent());
}


void CEGUIDrawable::PressedSpace()
{
	if(_currentstate == XtGLw_Text)
	{
		if(_scrolling)
		{
			_scrolling = false;
			_scrollingtimediff += 100000;
		}
		else
		{
			++_textpageidx;
			if(_textpageidx >= _precalculated_text.size())
			{
				CleanAndReport();
			}
			else
			{
				_scrolling = true;
				_scrollingtimediff = 0;
			}
		}
	}
}

void CEGUIDrawable::StartScrollingText(const std::string & imagepath, 
									   std::vector<std::vector<unsigned int> > &textIds) 
{
	//clean up old stuff
	CleanUp();



	_drawXtraGL = true;
	_currentstate = XtGLw_Text;
	LoadGLTextures(imagepath);

	_scrolling = true;
	_scrollingtimediff = 0;
	_texts.clear();
	_texts.swap(textIds);

	CreateLBAFont(_fontsize);
	precalculate_text(_windowW-2*_loadedfont->average_advance, _windowH);
}


void CEGUIDrawable::StartFixedImage(const std::string & imagepath, long NbSecondDisplay, 
							bool FadeIn, float FadeInColorR, float FadeInColorG, float FadeInColorB,
							bool FadeOut, float FadeOutColorR, float FadeOutColorG, float FadeOutColorB)
{
	//clean up old stuff
	CleanUp();


	_drawXtraGL = true;
	_currentstate = XtGLw_Image;
	LoadGLTextures(imagepath);

	if(NbSecondDisplay > 0)
		_textfinishdisplaytime = SynchronizedTimeHandler::GetCurrentTimeDouble() + (NbSecondDisplay*1000);
	else
		_textfinishdisplaytime = -1;

	_fadingin = FadeIn;
	_fiR = FadeInColorR;
	_fiG = FadeInColorG;
	_fiB = FadeInColorB;
	_fadingout = FadeOut;
	_foR = FadeOutColorR;
	_foG = FadeOutColorG;
	_foB = FadeOutColorB;

	if(_fadingin)
	{
		_currentfadestate = XtGLw_FDIn;
		_currentalpha = 0;
	}
	else
	{
		_currentalpha = 1;
	}
}


void CEGUIDrawable::EndDrawExtraGL()
{
	_drawXtraGL = false;
}


 void CEGUIDrawable::paintXtraGL() const
 {
	glColor4f(_bgR, _bgG, _bgB, _bgA);
	glBegin(GL_QUADS);
		glVertex2f(0, _windowH);
		glVertex2f(_windowW, _windowH);
		glVertex2f(_windowW, 0);
		glVertex2f(0, 0);
	glEnd();




	switch(_currentstate)
	{
		case XtGLw_Text:
		{
			DrawBGImage(1);

			if(!_scrolling && (_textpageidx < _precalculated_text.size()-1))
			{
				glColor3d(0.8,0.8,0.8);

				glDisable(GL_TEXTURE_2D);
				glBegin(GL_TRIANGLES);
					glVertex2f(	_windowW-_loadedfont->average_advance-30,_windowH-_loadedfont->average_advance);
					glVertex2f(	_windowW-_loadedfont->average_advance,_windowH-_loadedfont->average_advance);
					glVertex2f(	_windowW-_loadedfont->average_advance,_windowH-_loadedfont->average_advance-30);
				glEnd();
			}

			glEnable(GL_TEXTURE_2D);
			glBindTexture( GL_TEXTURE_2D, _textureid );
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

			if(_textpageidx < _precalculated_text.size())
				write_text(_loadedfont->average_advance, _loadedfont->origin+20);
		}
		break;

		case XtGLw_Image:
		{
			DrawBGImage(_currentalpha);
		}
		break;
	}
 }


//! display image if exist
void CEGUIDrawable::DrawBGImage(float alpha) const
{
	if(_imageloaded)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture( GL_TEXTURE_2D, _imgtextureid );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		glColor4d(1.0,1.0,1.0,alpha);
		glBegin(GL_QUADS);
			glTexCoord2d(0, 0);
			glVertex2f(0, _windowH);
			glTexCoord2d(1, 0);
			glVertex2f(_windowW, _windowH);
			glTexCoord2d(1, 1);
			glVertex2f(_windowW, 0);
			glTexCoord2d(0, 1);
			glVertex2f(0, 0);
		glEnd();
	}
}


 void CEGUIDrawable::resizedGL(int w, int h)
 {
	_windowW = w;
	_windowH = h;
	_fontsize = min(h/25, 40);


	if(_currentstate == XtGLw_Text)
	{
		CreateLBAFont(_fontsize);
		precalculate_text(_windowW-2*_loadedfont->average_advance, _windowH);
	}
 }


//! prepare text to be drawn
void CEGUIDrawable::prepare_text(const std::vector<linetodraw> &texttoprep, int maxchar)
{
	_textstodraw.clear();

	int sizedone = 0;
	std::vector<linetodraw>::const_iterator it = texttoprep.begin();
	std::vector<linetodraw>::const_iterator end = texttoprep.end();
	for(; (it != end) && (sizedone < maxchar); ++it)
	{
		linetodraw tmp;
		tmp.nbchar = maxchar-sizedone;
		tmp.space_size = it->space_size;
		tmp.text = it->text;
		_textstodraw.push_back(tmp);

		sizedone += (int)it->text.size();
	}

	if(sizedone < maxchar)
	{
		_scrolling = false;
		_scrollingtimediff += 100000;
	}
}

//! draw text on screen
void CEGUIDrawable::write_text(double x, double y) const
{
	std::vector<linetodraw>::const_iterator it = _textstodraw.begin();
	std::vector<linetodraw>::const_iterator end = _textstodraw.end();
	for(; it != end; ++it)
	{
		write_line(it->text, true, x+2, y+2, it->space_size, it->nbchar);
		write_line(it->text, false, x, y, it->space_size, it->nbchar);
		y+=_loadedfont->average_advance*2.;
	}
}


//! precalculate text to display to screen
void CEGUIDrawable::precalculate_text(double sizeX, double sizeY)
{
	_precalculated_text.clear();
	_textpageidx = 0;
	size_t maxtextpage = (size_t)((sizeY-40) / _loadedfont->char_height);

	std::vector<std::vector<unsigned int> >::iterator it = _texts.begin();
	std::vector<std::vector<unsigned int> >::iterator end = _texts.end();
	for(; it != end; ++it)
	{
		std::vector<linetodraw> textpage;
		std::vector<unsigned int>& tmpvec = *it;

		// separate words
	    int space_size=_loadedfont->average_advance;
		int nbwords=0;
		vector<std::vector<unsigned int> >words;
		vector<int> wordslengthpixel;
		int length=0;
		std::vector<unsigned int> s;
		for(int i=0;i<tmpvec.size();i++)
		{
			unsigned int c=tmpvec[i];
			if(c==' ')
			{
				nbwords++;
				wordslengthpixel.push_back(length);
				words.push_back(s);
				s.clear();
				length=0;

			}
			else
			{
				// avoid problem with undrawable chars
				if(c >= _loadedfont->glyph.size())
					c = ' ';

				s.push_back(c);
				length+=_loadedfont->glyph[c].advance;
			}
		}
		words.push_back(s);
		wordslengthpixel.push_back(length);

		std::vector<unsigned int> line;
		int linelengthpixel=0;
		nbwords=0;
		int nbchar=0;
		bool returnline = false;
		for(int i=0;i<words.size();i++)
		{
			if(words[i].size() == 1 && 	words[i][0] == '@')
			{
				returnline = true;
			}
			else
			{
				if(!returnline && linelengthpixel+wordslengthpixel[i]+(nbwords)*space_size<=sizeX)
				{
					for(int sv=0; sv< words[i].size(); ++sv)
						line.push_back(words[i][sv]);
					line.push_back(' ');
					linelengthpixel+=wordslengthpixel[i];
					nbwords++;
				}
				else
				{
					linetodraw tmp;
					tmp.space_size = returnline ? space_size : (sizeX-linelengthpixel)/(nbwords-1);
					tmp.text.swap(line);
					textpage.push_back(tmp);
					if(textpage.size() >= maxtextpage)
					{
						_precalculated_text.push_back(textpage);
						textpage.clear();
					}

					line.clear();
					linelengthpixel=0;

					for(int sv=0; sv< words[i].size(); ++sv)
						line.push_back(words[i][sv]);
					line.push_back(' ');
					linelengthpixel+=wordslengthpixel[i];
					nbwords=1;

					returnline = false;
				}
			}

		}

		if(line.size() > 0)
		{
			linetodraw tmp;
			tmp.space_size = space_size;
			tmp.text.swap(line);
			textpage.push_back(tmp);
		}

		if(textpage.size() > 0)
			_precalculated_text.push_back(textpage);
	}
}