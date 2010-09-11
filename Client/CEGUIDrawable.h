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
#ifndef _LBANET_CEGUI_DRAWABLE_H_
#define _LBANET_CEGUI_DRAWABLE_H_

#include <osg/Drawable>
#include <boost/shared_ptr.hpp>


class GuiHandler;



class CEGUIDrawable : public osg::Drawable
{
public:

    CEGUIDrawable(/*boost::shared_ptr<GuiHandler> GuiH*/);

    /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
    CEGUIDrawable(const CEGUIDrawable& drawable,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY)
					: Drawable(drawable,copyop) {}
    
    META_Object(osg,CEGUIDrawable);
    

    void drawImplementation(osg::RenderInfo& renderInfo) const;

protected:    

    virtual ~CEGUIDrawable();

    unsigned int _activeContextID;
};


#endif