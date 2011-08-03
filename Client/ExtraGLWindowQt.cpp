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



ExtraGLWidget::ExtraGLWidget(QWidget* parent)
: QGLWidget(parent)
{
}


void ExtraGLWidget::initializeGL()
 {
    glGenTextures( 1, &texture[0]);
    glBindTexture( GL_TEXTURE_2D, texture[0] );
    char *map=new char[1024*1024*4];
    for(int i=0;i<font.map.size();i++)
    {
        map[i*4+0]=font.map[i];
        map[i*4+1]=font.map[i];
        map[i*4+2]=font.map[i];
        map[i*4+3]=font.map[i];
    }
    glTexImage2D(GL_TEXTURE_2D, 0, 4, 1024,1024, 0, GL_RGBA, GL_UNSIGNED_BYTE,map);
    delete map;
 }

 void ExtraGLWidget::resizeGL(int w, int h)
 {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,w,h,0,1000,-1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0,0,w,h);
 }


 void ExtraGLWidget::paintGL()
 {
     // draw the scene:
     ...
     glRotatef(...);
     glMaterialfv(...);
     glBegin(GL_QUADS);
     glVertex3f(...);
     glVertex3f(...);
     ...
     glEnd();
     ...
 }
