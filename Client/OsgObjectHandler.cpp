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
default constructor
***********************************************************/
OsgObjectHandler::OsgObjectHandler(boost::shared_ptr<DisplayTransformation> Tr)
:  _posX(0), _posY(0), _posZ(0), _displayed(true)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Created empty Osg object.");
	#endif

	_OsgObject = OsgHandler::getInstance()->AddEmptyActorNode(true);
	_OsgObjectNoLight = OsgHandler::getInstance()->AddEmptyActorNode(false);

	if(Tr)
	{
		_osgpat = OsgHandler::getInstance()->CreatePAT(Tr);
		_OsgObject->addChild(_osgpat);

		_osgpatNoLight = OsgHandler::getInstance()->CreatePAT(Tr);
		_OsgObjectNoLight->addChild(_osgpatNoLight);
	}

	UpdateMatrix();
}


/***********************************************************
Constructor
***********************************************************/
OsgObjectHandler::OsgObjectHandler(osg::ref_ptr<osg::MatrixTransform> OsgObject, bool uselight)
: _posX(0), _posY(0), _posZ(0), _displayed(true)
{
	if(uselight)
		_OsgObject = OsgObject;
	else
		_OsgObjectNoLight = OsgObject;


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

	if(_displayed)
	{
		if(_OsgObject)
			OsgHandler::getInstance()->RemoveActorNode(_OsgObject, true);

		if(_OsgObjectNoLight)
			OsgHandler::getInstance()->RemoveActorNode(_OsgObjectNoLight, false);
	}

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
	osg::Matrixd Trans;
	osg::Matrixd Rotation;

	Trans.makeTranslate(_posX, _posY, _posZ);
	Rotation.makeRotate(osg::Quat(_Q.X, _Q.Y, _Q.Z, _Q.W));

	if(_OsgObject)
		_OsgObject->setMatrix(Rotation * Trans);

	if(_OsgObjectNoLight)
		_OsgObjectNoLight->setMatrix(Rotation * Trans);
}


/***********************************************************
show or hide the object
***********************************************************/
void OsgObjectHandler::ShowOrHide(bool Show)
{
	if(_OsgObject)
	{
		if(!Show && _displayed)
		{
			_displayed = false;
			OsgHandler::getInstance()->RemoveActorNode(_OsgObject, true);

			if(_OsgObjectNoLight)
				OsgHandler::getInstance()->RemoveActorNode(_OsgObjectNoLight, false);
		}

		if(Show && !_displayed)
		{
			_displayed = true;
			OsgHandler::getInstance()->ReAddActorNode(_OsgObject, true);

			if(_OsgObjectNoLight)
				OsgHandler::getInstance()->ReAddActorNode(_OsgObjectNoLight, false);
		}
	}
}


/***********************************************************
update display with current frame - used for animation
***********************************************************/
int OsgObjectHandler::Process(double time, float tdiff)
{
	return 0;
}

/***********************************************************
update display
***********************************************************/
int OsgObjectHandler::Update(LbaNet::DisplayObjectUpdateBasePtr update)
{
	return 0;
}

/***********************************************************
return root object
***********************************************************/
osg::ref_ptr<osg::Group> OsgObjectHandler::GetRoot()
{
	if(_osgpat)
		return _osgpat;
	else
		return _OsgObject;
}



/***********************************************************
 return root object on no light scene
***********************************************************/
osg::ref_ptr<osg::Group> OsgObjectHandler::GetRootNoLight()
{
	if(_osgpatNoLight)
		return _osgpatNoLight;
	else
		return _OsgObjectNoLight;
}
