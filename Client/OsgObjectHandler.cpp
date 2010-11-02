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
#include <osg/AutoTransform>
#include <osgText/Text>


/***********************************************************
default constructor
***********************************************************/
OsgObjectHandler::OsgObjectHandler(boost::shared_ptr<DisplayTransformation> Tr,
									const LbaNet::ObjectExtraInfo &extrainfo)
:  _posX(0), _posY(0), _posZ(0), _displayed(true), _extrainfo(extrainfo), _uselight(true)
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
	RefreshText();
}


/***********************************************************
Constructor
***********************************************************/
OsgObjectHandler::OsgObjectHandler(osg::ref_ptr<osg::MatrixTransform> OsgObject, bool uselight,
										const LbaNet::ObjectExtraInfo &extrainfo)
: _posX(0), _posY(0), _posZ(0), _displayed(true), _extrainfo(extrainfo), _uselight(uselight)
{
	if(uselight)
	{
		_OsgObject = OsgObject;
		_OsgObjectNoLight = OsgHandler::getInstance()->AddEmptyActorNode(false);
	}
	else
		_OsgObjectNoLight = OsgObject;


	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Created new Osg object.");
	#endif

	UpdateMatrix();
	RefreshText();
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
	const std::type_info& info = typeid(*update);

	// ObjectExtraInfoUpdate
	if(info == typeid(LbaNet::ObjectExtraInfoUpdate))
	{
		LbaNet::ObjectExtraInfoUpdate * castedptr = 
			dynamic_cast<LbaNet::ObjectExtraInfoUpdate *>(update.get());

		UpdateExtraInfo(castedptr->Update);
	}

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



/***********************************************************
update object extra info
***********************************************************/
void OsgObjectHandler::UpdateExtraInfo(const LbaNet::ObjectExtraInfo &info)
{
	_extrainfo = info;
	RefreshText();
}


/***********************************************************
refresh text
***********************************************************/
void OsgObjectHandler::RefreshText()
{
	osg::ref_ptr<osg::Group> root = GetRootNoLight();
	if(root)
	{
		if(_textgroup)
		{
			root->removeChild(_textgroup);
			_textgroup = NULL;
		}

		if(_extrainfo.Name != "")
		{
			osg::Vec3 posT;
			if(_uselight)
			{
				osg::BoundingSphere bs = GetRoot()->computeBound();
				posT = bs.center()+ osg::Vec3(0,1,0);		
			}
			else
			{
				osg::BoundingSphere bs = GetRootNoLight()->computeBound();
				posT = bs.center()+ osg::Vec3(0,1,0);	
				if(_extrainfo.Name.find("Spawn") == 0)
					posT = osg::Vec3(0,1,0);	
			}

			_textgroup = new osg::AutoTransform();
			_textgroup->setPosition(posT);
			_textgroup->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
			_textgroup->setMinimumScale(0.01);
			_textgroup->setMaximumScale(0.5);
			_textgroup->setAutoScaleToScreen(true);

			osg::ref_ptr<osg::Geode> _textgeode = new osg::Geode();
			osg::ref_ptr<osgText::Text> textd = new osgText::Text();
			textd->setText(_extrainfo.Name);
			textd->setColor(osg::Vec4(_extrainfo.NameColorR, _extrainfo.NameColorG, _extrainfo.NameColorB, 1));
			textd->setCharacterSize(/*0.4f*/10);
			textd->setFont("Tahoma.ttf");
			textd->setAlignment(osgText::Text::CENTER_CENTER);



			textd->setBackdropColor(osg::Vec4(0, 0, 0, 1));
			textd->setBackdropType(osgText::Text::OUTLINE);
			textd->setBackdropImplementation(osgText::Text::NO_DEPTH_BUFFER);
			textd->setBackdropOffset(0.1f);

			_textgeode->addDrawable(textd);

			osg::StateSet* stateSet = _textgeode->getOrCreateStateSet();
			stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
			stateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
			stateSet->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
			stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
			stateSet->setRenderBinDetails( 10000, "RenderBin");

			_textgroup->addChild(_textgeode);
			root->addChild(_textgroup);
		}
	}
}

/***********************************************************
sett dont optimize
***********************************************************/
void OsgObjectHandler::ForbidOptimize()
{
	if(_osgpat)
		_osgpat->setUserData(new osg::Node());


	if(_osgpatNoLight)
		_osgpatNoLight->setUserData(new osg::Node());
}



/***********************************************************
set name of display object that will be returned during picking
***********************************************************/
void OsgObjectHandler::SetName(const std::string & name)
{
	if(_osgpat)
		_osgpat->setName(name);

	if(_OsgObject)
		_OsgObject->setName(name);

	if(_osgpatNoLight)
		_osgpatNoLight->setName(name);

	if(_OsgObjectNoLight)
		_OsgObjectNoLight->setName(name);
}