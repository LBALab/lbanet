/*
------------------------[ Lbanet Source ]-------------------------
Copyright (C) 2009
Author: Vivien Delage [Rincevent_123]
Email : vdelage@gmail.com

-------------------------------[ GNU License ]-------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

-----------------------------------------------------------------------------
*/

#include "ExtraGLWindowQt"
#include "FONT_FONT.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include "Localizer.h"
#include "LogHandler.h"

#include "EventsQueue.h"
#include "ClientExtendedEvents.h"
#include "SynchronizedTimeHandler.h"

#include <QString>

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


ExtraGLWidget::ExtraGLWidget(QWidget* parent)
: QGLWidget(parent), _scrolling(false), _scrollingtimediff(0),
	_loadedfont(NULL), _fontloaded(false), _imageloaded(false),
	_currentstate(XtGLw_Off), _textfinishdisplaytime(-1), 
	_currentfadestate(XtGLw_FDOff), _bgR(0), _bgG(0), _bgB(0), _bgA(1)
{
}

ExtraGLWidget::~ExtraGLWidget()
{
	DeleteFont();
	CleanImageTexture();
}



void ExtraGLWidget::initializeGL()
 {
    glGenTextures( 1, &_textureid);
	_fontloaded = true;
 }

 void ExtraGLWidget::resizeGL(int w, int h)
 {
	_windowW = w;
	_windowH = h;
	CreateLBAFont(min(h/30, 40));
 }



void ExtraGLWidget::write_line_black(const QVector<uint> &text, FONT_FONT &font, double x, double y, double space_size, int nbchar)
{
	glBegin(GL_QUADS);

	for(int i=0;i<nbchar && i<text.size();i++)
	{
		unsigned int n=text[i];
		if(n==' ')
			x+=space_size;
		else
		{
			glColor3d(0,0,0);

			glTexCoord2d((font.glyph[n].mapx/1024.),                                    (font.glyph[n].mapy)/1024.);
			glVertex3d(	(int)x+font.glyph[n].dx,                                        (int)y-font.origin,10);
			glTexCoord2d((font.glyph[n].mapx            +font.glyph[n].width)/1024.,    (font.glyph[n].mapy)/1024.);
			glVertex3d(	(int)x+font.glyph[n].dx         +font.glyph[n].width,           (int)y-font.origin,10);
			glTexCoord2d((font.glyph[n].mapx            +font.glyph[n].width)/1024.,    (font.glyph[n].mapy     +font.char_height)/1024.);
			glVertex3d(	(int)x+font.glyph[n].dx         +font.glyph[n].width,           (int)y-font.origin          +font.char_height,10);
			glTexCoord2d((font.glyph[n].mapx)/1024.,                                    (font.glyph[n].mapy     +font.char_height)/1024.);
			glVertex3d(	(int)x+font.glyph[n].dx,                                     (int)y-font.origin          +font.char_height,10);
			x+=font.glyph[n].advance;
		}
	}
	glEnd();
}



void ExtraGLWidget::write_line_white(const QVector<uint> &text, FONT_FONT &font, double x, double y, double space_size, int nbchar)
{
	glBegin(GL_QUADS);

	for(int i=0;i<nbchar && i<text.size();i++)
	{
		unsigned int n=text[i];
		if(n==' ')
			x+=space_size;
		else
		{
			glColor3d(min(0.8,(nbchar-i)/10.),
					  min(0.8,(nbchar-i)/10.),
					  min(0.8,(nbchar-i)/10.));

			glTexCoord2d((font.glyph[n].mapx/1024.),                                    (font.glyph[n].mapy)/1024.);
			glVertex3d(	(int)x+font.glyph[n].dx,                                        (int)y-font.origin,10);
			glTexCoord2d((font.glyph[n].mapx            +font.glyph[n].width)/1024.,    (font.glyph[n].mapy)/1024.);
			glVertex3d(	(int)x+font.glyph[n].dx         +font.glyph[n].width,           (int)y-font.origin,10);
			glTexCoord2d((font.glyph[n].mapx            +font.glyph[n].width)/1024.,    (font.glyph[n].mapy     +font.char_height)/1024.);
			glVertex3d(	(int)x+font.glyph[n].dx         +font.glyph[n].width,           (int)y-font.origin          +font.char_height,10);
			glTexCoord2d((font.glyph[n].mapx)/1024.,                                    (font.glyph[n].mapy     +font.char_height)/1024.);
			glVertex3d(	(int)x+font.glyph[n].dx,                                     (int)y-font.origin          +font.char_height,10);
			x+=font.glyph[n].advance;
		}
	}
	glEnd();
}


void ExtraGLWidget::write_text_white(const QVector<uint> &text, FONT_FONT &font, 
									double x, double y, double maxlenght, int maxchar)
{
    int space_size=font.average_advance;
    int nbwords=0;
    vector<QVector<uint> > words;
    vector<int> wordslengthpixel;
    int length=0;
    QVector<uint> s;
    for(int i=0;i<text.size();i++)
    {
        unsigned int c=text[i];
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
            s.append(c);
            length+=font.glyph[c].advance;
        }
    }
    words.push_back(s);
    wordslengthpixel.push_back(length);

    QVector<uint> line;
    line.clear();
    int linelengthchar=0;
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
			if(!returnline && linelengthpixel+wordslengthpixel[i]+(nbwords)*space_size<=maxlenght)
			{
				for(int sv=0; sv< words[i].size(); ++sv)
					line.append(words[i][sv]);
				line.append(' ');
				linelengthpixel+=wordslengthpixel[i];
				nbwords++;
				linelengthchar+=words[i].size()+1;
			}
			else
			{
				returnline = false;
				write_line_white(line,font,x,y,(maxlenght-linelengthpixel)/(nbwords-1),maxchar-nbchar);
				line.clear();
				nbchar+=linelengthchar;
				linelengthchar=0;
				linelengthpixel=0;

				for(int sv=0; sv< words[i].size(); ++sv)
					line.append(words[i][sv]);
				line.append(' ');
				linelengthpixel+=wordslengthpixel[i];
				linelengthchar=words[i].size()+1;
				y+=font.average_advance*2.;
				nbwords=1;
			}
		}
    }
    write_line_white(line, font, x, y, space_size, maxchar-nbchar);
}

void ExtraGLWidget::write_text_black(const QVector<uint> &text, FONT_FONT &font, 
									double x, double y, double maxlenght, int maxchar)
{
    int space_size=font.average_advance;
    int nbwords=0;
    vector<QVector<uint> >words;
    vector<int> wordslengthpixel;
    int length=0;
    QVector<uint> s;
    for(int i=0;i<text.size();i++)
    {
        unsigned int c=text[i];
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
            s.append(c);
            length+=font.glyph[c].advance;
        }
    }
    words.push_back(s);
    wordslengthpixel.push_back(length);

    QVector<uint> line;
    line.clear();
    int linelengthchar=0;
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
			if(!returnline && linelengthpixel+wordslengthpixel[i]+(nbwords)*space_size<=maxlenght)
			{
				for(int sv=0; sv< words[i].size(); ++sv)
					line.append(words[i][sv]);
				line.append(' ');
				linelengthpixel+=wordslengthpixel[i];
				nbwords++;
				linelengthchar+=words[i].size()+1;
			}
			else
			{
				returnline = false;
				write_line_black(line,font,x,y,(maxlenght-linelengthpixel)/(nbwords-1),maxchar-nbchar);
				line.clear();
				nbchar+=linelengthchar;
				linelengthchar=0;
				linelengthpixel=0;

				for(int sv=0; sv< words[i].size(); ++sv)
					line.append(words[i][sv]);
				line.append(' ');
				linelengthpixel+=wordslengthpixel[i];
				linelengthchar=words[i].size()+1;
				y+=font.average_advance*2.;
				nbwords=1;
			}
		}

    }
    write_line_black(line, font, x, y, space_size, maxchar-nbchar);
	
	int checkL = (maxchar-nbchar);
	int checkL2 = line.size();
	if(checkL >= checkL2)
	{
		_scrolling = false;
		_scrollingtimediff += 100000;
	}
}








void ExtraGLWidget::CreateLBAFont(int size)
{
	if(_loadedfont)
	{
		delete _loadedfont;
		_loadedfont = false;
	}

	_loadedfont = new FONT_FONT();
	load_ttf(*_loadedfont, "Data/GUI/fonts/lubalingraphstd-demi.otf", size);


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


void ExtraGLWidget::DeleteFont()
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



 void ExtraGLWidget::LoadGLTextures( const std::string& name )
{
	makeCurrent();
	CleanImageTexture();
	if(name == "")
		return;

    QImage img;
    if( ! img.load( name.c_str() ) )
    {
		LogHandler::getInstance()->LogToFile("error loading image to texture: " + name);
        return;
    }

	_imgtextureid = bindTexture(img, GL_TEXTURE_2D, GL_RGBA, 
							QGLContext::LinearFilteringBindOption | QGLContext::InvertedYBindOption);
	_imageloaded = true;
}


void ExtraGLWidget::CleanImageTexture()
{
	if(_imageloaded)
	{
		deleteTexture (_imgtextureid);
		_imageloaded = false;
	}
}



void ExtraGLWidget::Process(double tnow, float tdiff)
{
	if(_scrolling)
		_scrollingtimediff += tdiff;

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


	if(_currentstate != XtGLw_Off)
		updateGL();
}

// clean up display
void ExtraGLWidget::CleanUp()
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
void ExtraGLWidget::CleanAndReport()
{
	CleanUp();
	EventsQueue::getReceiverQueue()->AddEvent(new DisplayExtraGLFinishedEvent());
}


void ExtraGLWidget::PressedSpace()
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
			++_textidx;
			if(_textidx >= _texts.size())
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

void ExtraGLWidget::StartScrollingText(const std::string & imagepath, const std::vector<long> &textIds)
{
	//clean up old stuff
	CleanUp();

	_currentstate = XtGLw_Text;
	LoadGLTextures(imagepath);

	_scrolling = true;
	_scrollingtimediff = 0;
	_textidx = 0;
	_texts.clear();

	for(size_t i=0; i< textIds.size(); ++i)
	{
		std::string tmp = Localizer::getInstance()->GetText(Localizer::Map, textIds[i]);
		if(tmp != "")
			_texts.push_back(QString::fromUtf8(tmp.c_str()).toUcs4());
	}
}


void ExtraGLWidget::StartFixedImage(const std::string & imagepath, long NbSecondDisplay, 
							bool FadeIn, float FadeInColorR, float FadeInColorG, float FadeInColorB,
							bool FadeOut, float FadeOutColorR, float FadeOutColorG, float FadeOutColorB)
{
	//clean up old stuff
	CleanUp();

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




 void ExtraGLWidget::paintGL()
 {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,_windowW,_windowH,0,1000,-1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,_windowW,_windowH);

	glClearColor(_bgR, _bgG, _bgB, _bgA);
	glClear(GL_STENCIL_BUFFER_BIT|GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_FOG);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glEnable (GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);


	switch(_currentstate)
	{
		case XtGLw_Text:
		{
			DrawBGImage(1);

			if(!_scrolling)
			{
				glDisable(GL_TEXTURE_2D);
				glBegin(GL_TRIANGLES);
					glVertex2d(	_windowW-50,_windowH-20);
					glVertex2d(	_windowW-20,_windowH-20);
					glVertex2d(	_windowW-20,_windowH-50);
				glEnd();
			}

			glEnable(GL_TEXTURE_2D);
			glBindTexture( GL_TEXTURE_2D, _textureid );
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

			if(_textidx < _texts.size())
			{
				write_text_black(_texts[_textidx], *_loadedfont, _loadedfont->average_advance+2,
					_loadedfont->origin+22, _windowW-2*_loadedfont->average_advance, (int)(_scrollingtimediff/60));

				write_text_white(_texts[_textidx], *_loadedfont, _loadedfont->average_advance,
					_loadedfont->origin+20, _windowW-2*_loadedfont->average_advance, (int)(_scrollingtimediff/60));
			}
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
void ExtraGLWidget::DrawBGImage(float alpha)
{
	if(_imageloaded)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture( GL_TEXTURE_2D, _imgtextureid );
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);

		glColor4d(1.0,1.0,1.0,alpha);
		glBegin(GL_QUADS);
			glTexCoord2d(0, 1);
			glVertex2d(0, 0);
			glTexCoord2d(1, 1);
			glVertex2d(_windowW, 0);
			glTexCoord2d(1, 0);
			glVertex2d(_windowW, _windowH);
			glTexCoord2d(0, 0);
			glVertex2d(0, _windowH);
		glEnd();
	}
}


