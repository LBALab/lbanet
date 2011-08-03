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
			printf("cannot export %s in a 1024x1024 texture, try to reduce font average width < %d, will exit...",font.name.c_str(),font.average_advance);
			getchar();
			exit(0);
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
		printf("texture coordinates of glyph %d : x=%d y=%d\n",n,cursorx,cursory);

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
	_loadedfont(NULL), _loaded(false)
{

}

ExtraGLWidget::~ExtraGLWidget()
{
	DeleteFont();
}



void ExtraGLWidget::CreateFont(int size)
{
	DeleteFont();

	_loadedfont = new FONT_FONT();
	_loaded = load_ttf(*_loadedfont, "Data/GUI/fonts/lubalingraphstd-demi.otf", size);

    glGenTextures( 1, &_textureid);
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

	if(_loaded)
	{
		glDeleteTextures(1, &_textureid);
		_loaded = false;
	}
}

void ExtraGLWidget::StartScrollingText(long TextId)
{
	_scrolling = true;
	_scrollingtimediff = 0;
	//TODO
}

void ExtraGLWidget::PressedSpace()
{
	if(_scrolling)
	{
		_scrolling = false;
		_scrollingtimediff += 100000;
	}
	else
	{
		//TODO
		_scrolling = true;
		_scrollingtimediff = 0;
	}
}

void ExtraGLWidget::Process(double tnow, float tdiff)
{
	if(_loaded)
	{
		if(_scrolling)
			_scrollingtimediff += tdiff;
		updateGL();
	}
}


void ExtraGLWidget::initializeGL()
 {

 }

 void ExtraGLWidget::resizeGL(int w, int h)
 {
	_windowW = w;
	_windowH = h;
	CreateFont(min(h/30, 40));
 }



void ExtraGLWidget::write_line_black(string text, FONT_FONT &font, double x, double y, double space_size, int nbchar)
{
	glBegin(GL_QUADS);

	for(int i=0;i<nbchar && i<text.length();i++)
	{
		unsigned char n=text[i];
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



void ExtraGLWidget::write_line_white(string text, FONT_FONT &font, double x, double y, double space_size, int nbchar)
{
	glBegin(GL_QUADS);

	for(int i=0;i<nbchar && i<text.length();i++)
	{
		unsigned char n=text[i];
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


void ExtraGLWidget::write_text_white(string text, FONT_FONT &font, 
									double x, double y, double maxlenght, int maxchar)
{
    int space_size=font.average_advance;
    int nbwords=0;
    vector<string>words;
    vector<int>wordslengthpixel;
    int length=0;
    string s;
    for(int i=0;i<text.length();i++)
    {
        unsigned char c=text[i];
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
            s=s+(char)c;
            length+=font.glyph[c].advance;
        }
    }
    words.push_back(s);
    wordslengthpixel.push_back(length);

    string line;
    line.clear();
    int linelengthchar=0;
    int linelengthpixel=0;
    nbwords=0;
    int nbchar=0;
    for(int i=0;i<words.size();i++)
    {
        if(linelengthpixel+wordslengthpixel[i]+(nbwords)*space_size<=maxlenght)
        {
            line.append(words[i]);
            line+=' ';
            linelengthpixel+=wordslengthpixel[i];
            nbwords++;
            linelengthchar+=words[i].length()+1;
        }
        else
        {
            write_line_white(line,font,x,y,(maxlenght-linelengthpixel)/(nbwords-1),maxchar-nbchar);
            line.clear();
            nbchar+=linelengthchar;
            linelengthchar=0;
            linelengthpixel=0;
            line.append(words[i]);
            line+=' ';
            linelengthpixel+=wordslengthpixel[i];
            linelengthchar=words[i].length()+1;
            y+=font.average_advance*2.;
            nbwords=1;
        }

    }
    write_line_white(line, font, x, y, space_size, maxchar-nbchar);
}

void ExtraGLWidget::write_text_black(string text, FONT_FONT &font, 
									double x, double y, double maxlenght, int maxchar)
{
    int space_size=font.average_advance;
    int nbwords=0;
    vector<string>words;
    vector<int>wordslengthpixel;
    int length=0;
    string s;
    for(int i=0;i<text.length();i++)
    {
        unsigned char c=text[i];
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
            s=s+(char)c;
            length+=font.glyph[c].advance;
        }
    }
    words.push_back(s);
    wordslengthpixel.push_back(length);

    string line;
    line.clear();
    int linelengthchar=0;
    int linelengthpixel=0;
    nbwords=0;
    int nbchar=0;
    for(int i=0;i<words.size();i++)
    {
        if(linelengthpixel+wordslengthpixel[i]+(nbwords)*space_size<=maxlenght)
        {
            line.append(words[i]);
            line+=' ';
            linelengthpixel+=wordslengthpixel[i];
            nbwords++;
            linelengthchar+=words[i].length()+1;
        }
        else
        {
            write_line_black(line,font,x,y,(maxlenght-linelengthpixel)/(nbwords-1),maxchar-nbchar);
            line.clear();
            nbchar+=linelengthchar;
            linelengthchar=0;
            linelengthpixel=0;
            line.append(words[i]);
            line+=' ';
            linelengthpixel+=wordslengthpixel[i];
            linelengthchar=words[i].length()+1;
            y+=font.average_advance*2.;
            nbwords=1;
        }

    }
    write_line_black(line, font, x, y, space_size, maxchar-nbchar);
}




 void ExtraGLWidget::paintGL()
 {
	if(!_loaded)
		return;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,_windowW,_windowH,0,1000,-1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,_windowW,_windowH);


	glClearColor (1.0, 0.0, 0.0, 0.0);
	glClear(GL_STENCIL_BUFFER_BIT|GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_FOG);
	glDisable(GL_DEPTH_TEST);
	glColor3d(1,1,1);
	glDisable(GL_LIGHTING);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POLYGON_SMOOTH, GL_NICEST);
	glDisable(GL_TEXTURE_2D);


	glColor4d(0.0,0.0,0.0,0.5);
	glBegin(GL_QUADS);
		glVertex2d(	10,10);
		glVertex2d(	_windowW-10, 10);
		glVertex2d(	_windowW-10,_windowH-10);
		glVertex2d(	10,_windowH-10);
	glEnd();

	glColor4d(1,1,1,1);
	glBegin(GL_LINE_LOOP);
		glVertex2d(	10,10);
		glVertex2d(	_windowW-10,10);
		glVertex2d(	_windowW-10,_windowH-10);
		glVertex2d(	10,_windowH-10);
	glEnd();

	if(!_scrolling)
	{
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);




	string text="Situé en périphérie d'une galaxie peu fréquentée, Twinsun est un planétoïde récent. Mû d'une lente rotation sur lui-même, c'est un monde stabilisé entre deux soleils. A l'équateur s'est formée une haute chaîne montagneuse, le divisant en deux hémisphères éclairés chacun par un soleil.";

	write_text_black(text, *_loadedfont, _loadedfont->average_advance+2,
		_loadedfont->origin+22, _windowW-2*_loadedfont->average_advance, (int)(_scrollingtimediff/60));

	write_text_white(text, *_loadedfont, _loadedfont->average_advance,
		_loadedfont->origin+20, _windowW-2*_loadedfont->average_advance, (int)(_scrollingtimediff/60));
 }
