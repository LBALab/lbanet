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

#if !defined(__LbaNetModel_1_OsgObjectHandler_h)
#define __LbaNetModel_1_OsgObjectHandler_h


#include "DisplayObjectHandlerBase.h"
#include <osg/ref_ptr>
#include <boost/shared_ptr.hpp>

namespace osg
{
	class MatrixTransform;
	class PositionAttitudeTransform;
	class Group;
	class AutoTransform;
	class ShapeDrawable;
}

class DisplayTransformation;

/***********************************************************************
 * Module:  OsgObjectHandler.h
 * Author:  vivien
 * Modified: mardi 14 juillet 2009 13:54:52
 * Purpose: Declaration of the class OsgObjectHandler
 ***********************************************************************/
class OsgObjectHandler : public DisplayObjectHandlerBase
{
public:
	//! default constructor
	OsgObjectHandler(boost::shared_ptr<DisplayTransformation> Tr,
						const LbaNet::ObjectExtraInfo &extrainfo,
						const LbaNet::LifeManaInfo &lifeinfo);

	//! constructor
	OsgObjectHandler(osg::ref_ptr<osg::MatrixTransform> OsgObject, bool uselight,
						const LbaNet::ObjectExtraInfo &extrainfo,
						const LbaNet::LifeManaInfo &lifeinfo);

	//! destructor
	virtual ~OsgObjectHandler();


	//!set object position in the world
	virtual void SetPosition(float X, float Y, float Z);

	//! set object rotation on X axis
	virtual void SetRotation(const LbaQuaternion& Q);

	//! show or hide the object
	virtual void ShowOrHide(bool Show);


	//! update display with current frame - used for animation
	virtual int Process(double time, float tdiff);

	//! update display
	virtual int Update(LbaNet::DisplayObjectUpdateBasePtr update,
							bool updatestoredstate);


	//! set name of display object that will be returned during picking
	virtual void SetName(const std::string & name);
	
protected:
	// update matrix
	void UpdateMatrix();

	// return root object
	osg::ref_ptr<osg::Group> GetRoot();

	// return root object on no light scene
	osg::ref_ptr<osg::Group> GetRootNoLight();

	// update object extra info
	virtual void UpdateExtraInfo(const LbaNet::ObjectExtraInfo &info);

	// refresh text
	void RefreshText();

	// set t dont optimize
	void ForbidOptimize();

	// update object life info
	void UpdateLifeInfo(const LbaNet::LifeManaInfo &info);

	// refresh life/mana bars
	void RefreshLifeManaBars();

	//! update model
	void UpdateModel(const LbaNet::ModelInfo &mInfo);


	//! extract name from string
	std::string ExtractName(const std::string &text);

	//! find shapdrawable
	osg::ShapeDrawable* findShapeDrawable();

protected:
	float											_posX;
	float											_posY; 
	float											_posZ;
	LbaQuaternion									_Q;
	bool											_displayed;
	bool											_uselight;

	osg::ref_ptr<osg::AutoTransform>				_textgroup;
	LbaNet::ObjectExtraInfo							_extrainfo;

	osg::ref_ptr<osg::AutoTransform>				_barsgroup;
	LbaNet::LifeManaInfo							_lifeinfo;

private:
	osg::ref_ptr<osg::MatrixTransform>				_OsgObject;
	osg::ref_ptr<osg::MatrixTransform>				_OsgObjectNoLight;
	osg::ref_ptr<osg::PositionAttitudeTransform>	_osgpat;
	osg::ref_ptr<osg::PositionAttitudeTransform>	_osgpatNoLight;
};




#endif