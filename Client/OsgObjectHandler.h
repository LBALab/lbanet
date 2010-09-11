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

namespace osg
{
	class MatrixTransform;
}

/***********************************************************************
 * Module:  OsgObjectHandler.h
 * Author:  vivien
 * Modified: mardi 14 juillet 2009 13:54:52
 * Purpose: Declaration of the class OsgObjectHandler
 ***********************************************************************/
class OsgObjectHandler : public DisplayObjectHandlerBase
{
public:
	//! constructor
	OsgObjectHandler(osg::ref_ptr<osg::MatrixTransform> OsgObject);

	//! destructor
	~OsgObjectHandler();


	//! set object position in the world
	virtual void SetPosition(float X, float Y, float Z);

	//! set object rotation on X axis
	virtual void SetRotation(const LbaQuaternion& Q);


protected:
	// update matrix
	void UpdateMatrix();

private:
	osg::ref_ptr<osg::MatrixTransform>	_OsgObject;
	float								_posX;
	float								_posY; 
	float								_posZ;
	LbaQuaternion						_Q;
};




#endif