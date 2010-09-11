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

#include "OsgObjectHandler.h"
#include "ObjectsDescription.h"
#include "OSGHandler.h"
#include "LogHandler.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>


/***********************************************************
Constructor
***********************************************************/
OsgObjectHandler::OsgObjectHandler(osg::ref_ptr<osg::MatrixTransform> OsgObject)
: _OsgObject(OsgObject), _posX(0), _posY(0), _posZ(0)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Created new Osg object.");
	#endif

	UpdateMatrix();
}

/***********************************************************
destructor
***********************************************************/
OsgObjectHandler::~OsgObjectHandler()
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Destroyed Osg object.");
	#endif

	OsgHandler::getInstance()->RemoveActorNode(_OsgObject);
}


/***********************************************************
set object position in the world
***********************************************************/
void OsgObjectHandler::SetPosition(float X, float Y, float Z)
{
	_posX = X;
	_posY = Y; 
	_posZ = Z;
	UpdateMatrix();
}

/***********************************************************
set object rotation on X axis
***********************************************************/
void OsgObjectHandler::SetRotation(const LbaQuaternion& Q)
{
	_Q = Q;
	UpdateMatrix();
}

/***********************************************************
update matrix
***********************************************************/
void OsgObjectHandler::UpdateMatrix()
{
	if(_OsgObject)
	{
		osg::Matrixd Trans;
		osg::Matrixd Rotation;

		Trans.makeTranslate(_posX, _posY, _posZ);
		Rotation.makeRotate(osg::Quat(_Q.X, _Q.Y, _Q.Z, _Q.W));

		_OsgObject->setMatrix(Rotation * Trans);
	}
}
