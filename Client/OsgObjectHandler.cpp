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
#include "Localizer.h"
#include "SynchronizedTimeHandler.h"
#include "DataDirHandler.h"

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/AutoTransform>
#include <osgText/Text>
#include <osg/LineWidth>
#include <osg/Material>


static  osg::Node* findNamedNode(const std::string& searchName,  osg::Node* currNode)
{
   osg::Group* currGroup;
   osg::Node* foundNode;

   // check to see if we have a valid (non-NULL) node.
   // if we do have a null node, return NULL.
   if ( !currNode)
   {
      return NULL;
   }

   // We have a valid node, check to see if this is the node we 
   // are looking for. If so, return the current node.
   if (currNode->getName() == searchName)
   {
      return currNode;
   }

   // We have a valid node, but not the one we are looking for.
   // Check to see if it has children (non-leaf node). If the node
   // has children, check each of the child nodes by recursive call.
   // If one of the recursive calls returns a non-null value we have
   // found the correct node, so return this node.
   // If we check all of the children and have not found the node,
   // return NULL
   currGroup = currNode->asGroup(); // returns NULL if not a group.
   if ( currGroup ) 
   {
      for (unsigned int i = 0 ; i < currGroup->getNumChildren(); i ++)
      { 
         foundNode = findNamedNode(searchName, currGroup->getChild(i));
         if (foundNode)
            return foundNode; // found a match!
      }
      return NULL; // We have checked each child node - no match found.
   }
   else 
   {
      return NULL; // leaf node, no match 
   }
}


/***********************************************************
findShapeDrawable
***********************************************************/
osg::ShapeDrawable* OsgObjectHandler::findShapeDrawable()
{

	osg::ShapeDrawable* shpdraw = NULL;
	if(_OsgObject)
	{
		osg::Node* node = findNamedNode("Colorable",  _OsgObject);
		if(node)
		{
			osg::Geode* geode = node->asGeode();
			if(geode)
			{
				osg::Drawable* drawable = geode->getDrawable(0);
				shpdraw = dynamic_cast<osg::ShapeDrawable*>(drawable);
			}
		}
	}

	if(!shpdraw)
	{
		if(_OsgObjectNoLight)
		{
			osg::Node* node = findNamedNode("Colorable",  _OsgObjectNoLight);
			if(node)
			{
				osg::Geode* geode = node->asGeode();
				if(geode)
				{
					osg::Drawable* drawable = geode->getDrawable(0);
					shpdraw = dynamic_cast<osg::ShapeDrawable*>(drawable);
				}
			}
		}
	}

	return shpdraw;
}





/***********************************************************
default constructor
***********************************************************/
OsgObjectHandler::OsgObjectHandler(int sceneidx, boost::shared_ptr<DisplayTransformation> Tr,
									const LbaNet::ObjectExtraInfo &extrainfo,
									const LbaNet::LifeManaInfo &lifeinfo)
:  _posX(0), _posY(0), _posZ(0), _displayed(true), _extrainfo(extrainfo), _uselight(true),
		_lifeinfo(lifeinfo), _useTransparentMaterial(false), _MaterialType(0), _sceneidx(sceneidx)
{
	#ifdef _DEBUG
		LogHandler::getInstance()->LogToFile("Created empty Osg object.");
	#endif

	_OsgObject = OsgHandler::getInstance()->AddEmptyActorNode(_sceneidx, true);
	_OsgObjectNoLight = OsgHandler::getInstance()->AddEmptyActorNode(_sceneidx,false);

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
OsgObjectHandler::OsgObjectHandler(int sceneidx, osg::ref_ptr<osg::MatrixTransform> OsgObject, bool uselight,
										const LbaNet::ObjectExtraInfo &extrainfo,
										const LbaNet::LifeManaInfo &lifeinfo)
: _posX(0), _posY(0), _posZ(0), _displayed(true), _extrainfo(extrainfo), _uselight(uselight),
		_lifeinfo(lifeinfo), _sceneidx(sceneidx)
{
	if(uselight)
	{
		_OsgObject = OsgObject;
		_OsgObjectNoLight = OsgHandler::getInstance()->AddEmptyActorNode(_sceneidx,false);
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
			OsgHandler::getInstance()->RemoveActorNode(_sceneidx,_OsgObject, true);

		if(_OsgObjectNoLight)
			OsgHandler::getInstance()->RemoveActorNode(_sceneidx,_OsgObjectNoLight, false);
	}

	osg::ref_ptr<osg::Group> root = GetRootNoLight();
	if(root)
	{
		if(_textgroup)
		{
			root->removeChild(_textgroup);
			_textgroup = NULL;
		}

		if(_shouttextgroup)
		{
			root->removeChild(_shouttextgroup);
			_shouttextgroup = NULL;
		}
		
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
			OsgHandler::getInstance()->RemoveActorNode(_sceneidx, _OsgObject, true);

			if(_OsgObjectNoLight)
				OsgHandler::getInstance()->RemoveActorNode(_sceneidx, _OsgObjectNoLight, false);
		}

		if(Show && !_displayed)
		{
			_displayed = true;
			OsgHandler::getInstance()->ReAddActorNode(_sceneidx, _OsgObject, true);

			if(_OsgObjectNoLight)
				OsgHandler::getInstance()->ReAddActorNode(_sceneidx, _OsgObjectNoLight, false);
		}
	}
}


/***********************************************************
update display with current frame - used for animation
***********************************************************/
int OsgObjectHandler::Process(double time, float tdiff)
{
	if(_shouttextgroup && (time >= _ttlshout))
	{
		osg::ref_ptr<osg::Group> root = GetRootNoLight();
		if(root)
			root->removeChild(_shouttextgroup);
		_shouttextgroup = NULL;
	}

	return ProcessInternal(time, tdiff); 
}

/***********************************************************
update display
***********************************************************/
int OsgObjectHandler::Update(LbaNet::DisplayObjectUpdateBasePtr update,
									bool updatestoredstate)
{
	const std::type_info& info = typeid(*update);

	// ObjectExtraInfoUpdate
	if(info == typeid(LbaNet::ObjectExtraInfoUpdate))
	{
		LbaNet::ObjectExtraInfoUpdate * castedptr = 
			dynamic_cast<LbaNet::ObjectExtraInfoUpdate *>(update.get());

		UpdateExtraInfo(castedptr->Update);
		return 0;
	}

	// ObjectLifeInfoUpdate
	if(info == typeid(LbaNet::ObjectLifeInfoUpdate))
	{
		LbaNet::ObjectLifeInfoUpdate * castedptr = 
			dynamic_cast<LbaNet::ObjectLifeInfoUpdate *>(update.get());

		UpdateLifeInfo(castedptr->Update);
		return 0;
	}


	// ModelUpdate
	if(info == typeid(LbaNet::ModelUpdate))
	{
		LbaNet::ModelUpdate * castedptr = 
			dynamic_cast<LbaNet::ModelUpdate *>(update.get());

		UpdateModel(castedptr->Info);
		return 0;
	}


	// ObjectColorUpdate
	if(info == typeid(LbaNet::ObjectColorUpdate))
	{
		LbaNet::ObjectColorUpdate * castedptr = 
			dynamic_cast<LbaNet::ObjectColorUpdate *>(update.get());

		osg::Vec4 colors(castedptr->R, castedptr->G, castedptr->B, castedptr->A);
		osg::ShapeDrawable* draw = findShapeDrawable();
		if(draw)
			draw->setColor(colors);
		return 0;
	}

	// ObjectAlphaColorUpdate
	if(info == typeid(LbaNet::ObjectAlphaColorUpdate))
	{
		LbaNet::ObjectAlphaColorUpdate * castedptr = 
			dynamic_cast<LbaNet::ObjectAlphaColorUpdate *>(update.get());

		osg::ShapeDrawable* draw = findShapeDrawable();
		if(draw)
		{
			osg::Vec4 colors = draw->getColor();	
			colors[3] = castedptr->A;
			draw->setColor(colors);
		}

		return 0;
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
			if(DataDirHandler::getInstance()->IsInEditorMode() || _extrainfo.Display)
			{
				std::string name = ExtractName(_extrainfo.Name);

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
					if(name.find("Spawn") == 0)
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
				textd->setText(name);
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
				stateSet->setRenderBinDetails( 500, "DepthSortedBin");

				_textgroup->addChild(_textgeode);
				root->addChild(_textgroup);
				root->dirtyBound();
			}
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

/***********************************************************
update object life info
***********************************************************/
void OsgObjectHandler::UpdateLifeInfo(const LbaNet::LifeManaInfo &info)
{
	_lifeinfo = info;
	RefreshLifeManaBars();
}



/***********************************************************
refresh life/mana bars
***********************************************************/
void OsgObjectHandler::RefreshLifeManaBars()
{
	osg::ref_ptr<osg::Group> root = GetRootNoLight();
	if(root)
	{
		if(_barsgroup)
		{
			root->removeChild(_barsgroup);
			_barsgroup = NULL;
		}

		if(!_lifeinfo.Display)
			return;


		_barsgroup = new osg::AutoTransform();
		//_barsgroup->setScale(osg::Vec3(0.04f, 0.04f, 0.04f));
		_barsgroup->setPosition(osg::Vec3(0, -1, 0));
		_barsgroup->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
		_barsgroup->setMinimumScale(0.0004);
		_barsgroup->setMaximumScale(0.4);
		_barsgroup->setAutoScaleToScreen(true);


		osg::ref_ptr<osg::Geode> barsgeode = new osg::Geode();
		float sizebar=20;

		// add contour
		{
			osg::ref_ptr<osg::Geometry> myGeometry = new osg::Geometry();
			osg::Vec3Array* myVertices = new osg::Vec3Array;
			osg::Vec4Array* myColors = new osg::Vec4Array;



			myColors->push_back(osg::Vec4(0.f, 104/255.f, 107/255.f, 0.7f));
			myVertices->push_back(osg::Vec3(-sizebar,0, 0));
			myColors->push_back(osg::Vec4(0.f, 104/255.f, 107/255.f, 0.7f));
			myVertices->push_back(osg::Vec3(sizebar,0, 0));		
			myColors->push_back(osg::Vec4(115/255.f, 252/255.f, 252/255.f, 0.7f));
			myVertices->push_back(osg::Vec3(sizebar,4, 0));	
			myColors->push_back(osg::Vec4(115/255.f, 252/255.f, 252/255.f, 0.7f));
			myVertices->push_back(osg::Vec3(-sizebar,4, 0));	


			myColors->push_back(osg::Vec4(0.f, 104/255.f, 107/255.f, 0.7f));
			myVertices->push_back(osg::Vec3(-sizebar,6, 0));
			myColors->push_back(osg::Vec4(0.f, 104/255.f, 107/255.f, 0.7f));
			myVertices->push_back(osg::Vec3(sizebar,6, 0));		
			myColors->push_back(osg::Vec4(115/255.f, 252/255.f, 252/255.f, 0.7f));
			myVertices->push_back(osg::Vec3(sizebar,10, 0));	
			myColors->push_back(osg::Vec4(115/255.f, 252/255.f, 252/255.f, 0.7f));
			myVertices->push_back(osg::Vec3(-sizebar,10, 0));	


			osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::LINES, 0);
			myprimitive->push_back(0);
			myprimitive->push_back(1);
			myprimitive->push_back(1);
			myprimitive->push_back(2);
			myprimitive->push_back(2);
			myprimitive->push_back(3);
			myprimitive->push_back(3);
			myprimitive->push_back(0);

			myprimitive->push_back(4);
			myprimitive->push_back(5);
			myprimitive->push_back(5);
			myprimitive->push_back(6);
			myprimitive->push_back(6);
			myprimitive->push_back(7);
			myprimitive->push_back(7);
			myprimitive->push_back(4);

			myGeometry->addPrimitiveSet(myprimitive);
			myGeometry->setVertexArray( myVertices ); 
			myGeometry->setColorArray(myColors);
			myGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);


			osg::StateSet* stateset = myGeometry->getOrCreateStateSet();
			osg::LineWidth* linewidth = new osg::LineWidth();
			linewidth->setWidth(2.0f);
			stateset->setAttributeAndModes(linewidth,osg::StateAttribute::ON);


			barsgeode->addDrawable(myGeometry.get());
		}

		
		// add bars
		{
			osg::ref_ptr<osg::Geometry> myGeometry = new osg::Geometry();
			osg::Vec3Array* myVertices = new osg::Vec3Array;
			osg::Vec4Array* myColors = new osg::Vec4Array;

			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec3(-sizebar,0, 0));
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec3(sizebar,0, 0));		
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec3(sizebar,4, 0));	
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec3(-sizebar,4, 0));	

			myColors->push_back(osg::Vec4(11/255.f, 11/255.f, 71/255.f, 1));
			myVertices->push_back(osg::Vec3(-sizebar,0, 0));	
			myColors->push_back(osg::Vec4(11/255.f, 11/255.f, 71/255.f, 1));
			myVertices->push_back(osg::Vec3(-sizebar+(sizebar*2*_lifeinfo.CurrentMana/_lifeinfo.MaxMana),0, 0));	
			myColors->push_back(osg::Vec4(13/255.f, 12/255.f, 150/255.f, 1));
			myVertices->push_back(osg::Vec3(-sizebar+(sizebar*2*_lifeinfo.CurrentMana/_lifeinfo.MaxMana),4, 0));	
			myColors->push_back(osg::Vec4(13/255.f, 12/255.f, 150/255.f, 1));
			myVertices->push_back(osg::Vec3(-sizebar,4, 0));	


			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec3(-sizebar,6, 0));
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec3(sizebar,6, 0));		
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec3(sizebar,10, 0));	
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec3(-sizebar,10, 0));	

			myColors->push_back(osg::Vec4(115/255.f, 0.f, 2/255.f, 1));
			myVertices->push_back(osg::Vec3(-sizebar,6, 0));	
			myColors->push_back(osg::Vec4(115/255.f, 0.f, 2/255.f, 1));
			myVertices->push_back(osg::Vec3(-sizebar+(sizebar*2*_lifeinfo.CurrentLife/_lifeinfo.MaxLife),6, 0));	
			myColors->push_back(osg::Vec4(254/255.f, 0.f, 3/255.f, 1));
			myVertices->push_back(osg::Vec3(-sizebar+(sizebar*2*_lifeinfo.CurrentLife/_lifeinfo.MaxLife),10, 0));	
			myColors->push_back(osg::Vec4(254/255.f, 0.f, 3/255.f, 1));
			myVertices->push_back(osg::Vec3(-sizebar,10, 0));	


			osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
			for(int i=0; i<16; ++i)
				myprimitive->push_back(i);


			myGeometry->addPrimitiveSet(myprimitive);
			myGeometry->setVertexArray( myVertices ); 
			myGeometry->setColorArray(myColors);
			myGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
			barsgeode->addDrawable(myGeometry.get());
		}



		osg::StateSet* stateSet = barsgeode->getOrCreateStateSet();
		stateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
		stateSet->setMode(GL_TEXTURE_2D,osg::StateAttribute::OFF);
		stateSet->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		stateSet->setRenderBinDetails( 500, "DepthSortedBin");

		_barsgroup->addChild(barsgeode);
		root->addChild(_barsgroup);
		root->dirtyBound();
	}
}


/***********************************************************
update model
***********************************************************/
void OsgObjectHandler::UpdateModel(const LbaNet::ModelInfo &mInfo)
{
	if(_uselight)
	{
		if(_OsgObject)
			OsgHandler::getInstance()->RemoveActorNode(_sceneidx, _OsgObject, true);
	}
	else
	{
		if(_OsgObjectNoLight)
			OsgHandler::getInstance()->RemoveActorNode(_sceneidx, _OsgObjectNoLight, false);
	}

	osg::ref_ptr<osg::MatrixTransform> node;
	boost::shared_ptr<DisplayTransformation> Tr(new DisplayTransformation());;
	Tr->translationX = mInfo.TransX;
	Tr->translationY = mInfo.TransY;
	Tr->translationZ = mInfo.TransZ;
	Tr->rotation = LbaQuaternion(mInfo.RotX, mInfo.RotY, mInfo.RotZ);
	Tr->scaleX = mInfo.ScaleX;
	Tr->scaleY = mInfo.ScaleY;
	Tr->scaleZ = mInfo.ScaleZ;

	if(mInfo.TypeRenderer == LbaNet::RenderSprite)
	{
		node = OsgHandler::getInstance()->CreateSpriteObject(_sceneidx, mInfo.ModelName, 
											mInfo.ColorR, mInfo.ColorG, mInfo.ColorB, mInfo.ColorA,
											Tr,	mInfo.UseLight,	mInfo.CastShadow,
											mInfo.UseBillboard);
	}
	else
	{
		if(mInfo.ModelName != "")
			node = OsgHandler::getInstance()->CreateSimpleObject(_sceneidx, mInfo.ModelName, Tr,
																mInfo.UseLight,	mInfo.CastShadow);
	}

	if(_uselight)
		_OsgObject = node;
	else
		_OsgObjectNoLight = node;


	UpdateMatrix();
	RefreshText();
}


/***********************************************************
extract name from string
***********************************************************/
std::string OsgObjectHandler::ExtractName(const std::string &text)
{
	std::string res = text;

	if(text[0] == '#')
	{
		res = text.substr(1);
		long textid = atol(res.c_str());
		res = Localizer::getInstance()->GetText(Localizer::Name, textid);
	}
	else
	{
		int index = text.find(": #");
		if(index != std::string::npos)
		{
			res = text.substr(index+3);
			long textid = atol(res.c_str());
			res = text.substr(0, index+2) + Localizer::getInstance()->GetText(Localizer::Name, textid);
		}
	}

	return res;
}


/***********************************************************
save object to file
***********************************************************/
void OsgObjectHandler::SaveToFile(const std::string & filename)
{
	if(_ObjectCopy)
		OsgHandler::getInstance()->RenderObjectToFile(_ObjectCopy, filename);

	_ObjectCopy = NULL;
}

/***********************************************************
store object copy
***********************************************************/
void OsgObjectHandler::StoreObjectCopy()
{
	osg::CopyOp cpo(osg::CopyOp::DEEP_COPY_ALL);

	if(_OsgObject)
		_ObjectCopy = (osg::MatrixTransform*)_OsgObject->clone(cpo);
	else if(_OsgObjectNoLight)
		_ObjectCopy = (osg::MatrixTransform*)_OsgObjectNoLight->clone(cpo);

	if(_ObjectCopy)
	{
		osg::StateSet* stateset = _ObjectCopy->getOrCreateStateSet();
		stateset->removeAttribute(osg::StateAttribute::MATERIAL);

		//stateset->setMode(GL_COLOR_MATERIAL, osg::StateAttribute::OVERRIDE|osg::StateAttribute::OFF); 
		stateset->setRenderingHint( osg::StateSet::DEFAULT_BIN );
	}
}



/***********************************************************
set transparency material
***********************************************************/
void OsgObjectHandler::SetTransparencyMaterial(bool OnOff, float Alpha)
{
	_useTransparentMaterial = OnOff;
	_materialAlpha = Alpha;

	RefreshMaterial();
}



/***********************************************************
set color material
***********************************************************/
void OsgObjectHandler::SetColorMaterial(	int MaterialType, 		
											float	MatAmbientColorR,
											float	MatAmbientColorG,
											float	MatAmbientColorB,
											float	MatAmbientColorA,			
											float	MatDiffuseColorR,
											float	MatDiffuseColorG,
											float	MatDiffuseColorB,
											float	MatDiffuseColorA,
											float	MatSpecularColorR,
											float	MatSpecularColorG,
											float	MatSpecularColorB,
											float	MatSpecularColorA,	
											float	MatEmissionColorR,
											float	MatEmissionColorG,
											float	MatEmissionColorB,
											float	MatEmissionColorA,
											float	MatShininess)
{
	_MaterialType = MaterialType;
	_MatAmbientColorR = MatAmbientColorR;
	if(_MatAmbientColorR < -1)
		_MatAmbientColorR = -1;
	if(_MatAmbientColorR > 1)
		_MatAmbientColorR = 1;

	_MatAmbientColorG = MatAmbientColorG;
	if(_MatAmbientColorG < -1)
		_MatAmbientColorG = -1;
	if(_MatAmbientColorG > 1)
		_MatAmbientColorG = 1;

	_MatAmbientColorB = MatAmbientColorB;
	if(_MatAmbientColorB < -1)
		_MatAmbientColorB = -1;
	if(_MatAmbientColorB > 1)
		_MatAmbientColorB = 1;

	_MatAmbientColorA = MatAmbientColorA;
	if(_MatAmbientColorA < -1)
		_MatAmbientColorA = -1;
	if(_MatAmbientColorA > 1)
		_MatAmbientColorA = 1;
			
	_MatDiffuseColorR = MatDiffuseColorR;
	if(_MatDiffuseColorR < -1)
		_MatDiffuseColorR = -1;
	if(_MatDiffuseColorR > 1)
		_MatDiffuseColorR = 1;

	_MatDiffuseColorG = MatDiffuseColorG;
	if(_MatDiffuseColorG < -1)
		_MatDiffuseColorG = -1;
	if(_MatDiffuseColorG > 1)
		_MatDiffuseColorG = 1;

	_MatDiffuseColorB = MatDiffuseColorB;
	if(_MatDiffuseColorB < -1)
		_MatDiffuseColorB = -1;
	if(_MatDiffuseColorB > 1)
		_MatDiffuseColorB = 1;

	_MatDiffuseColorA = MatDiffuseColorA;
	if(_MatDiffuseColorA < -1)
		_MatDiffuseColorA = -1;
	if(_MatDiffuseColorA > 1)
		_MatDiffuseColorA = 1;

	_MatSpecularColorR = MatSpecularColorR;
	if(_MatSpecularColorR < -1)
		_MatSpecularColorR = -1;
	if(_MatSpecularColorR > 1)
		_MatSpecularColorR = 1;

	_MatSpecularColorG = MatSpecularColorG;
	if(_MatSpecularColorG < -1)
		_MatSpecularColorG = -1;
	if(_MatSpecularColorG > 1)
		_MatSpecularColorG = 1;

	_MatSpecularColorB = MatSpecularColorB;
	if(_MatSpecularColorB < -1)
		_MatSpecularColorB = -1;
	if(_MatSpecularColorB > 1)
		_MatSpecularColorB = 1;

	_MatSpecularColorA = MatSpecularColorA;
	if(_MatSpecularColorA < -1)
		_MatSpecularColorA = -1;
	if(_MatSpecularColorA > 1)
		_MatSpecularColorA = 1;

	_MatEmissionColorR = MatEmissionColorR;
	if(_MatEmissionColorR < -1)
		_MatEmissionColorR = -1;
	if(_MatEmissionColorR > 1)
		_MatEmissionColorR = 1;

	_MatEmissionColorG = MatEmissionColorG;
	if(_MatEmissionColorG < -1)
		_MatEmissionColorG = -1;
	if(_MatEmissionColorG > 1)
		_MatEmissionColorG = 1;

	_MatEmissionColorB = MatEmissionColorB;
	if(_MatEmissionColorB < -1)
		_MatEmissionColorB = -1;
	if(_MatEmissionColorB > 1)
		_MatEmissionColorB = 1;

	_MatEmissionColorA = MatEmissionColorA;
	if(_MatEmissionColorA < -1)
		_MatEmissionColorA = -1;
	if(_MatEmissionColorA > 1)
		_MatEmissionColorA = 1;

	_MatShininess = MatShininess;
	if(_MatShininess < 0)
		_MatShininess = 0;
	if(_MatShininess > 128)
		_MatShininess = 128;


	RefreshMaterial();
}


/***********************************************************
refresh object material
***********************************************************/
void OsgObjectHandler::RefreshMaterial()
{
	osg::ref_ptr<osg::Node> node;
	if(_OsgObject)
		node = _OsgObject;
	else if(_OsgObjectNoLight)
		node = _OsgObjectNoLight;

	if(node)
	{
		if(_useTransparentMaterial || _MaterialType > 0)
		{
			osg::StateSet* stateset = node->getOrCreateStateSet();
			osg::Material* material = new osg::Material;

			if(_useTransparentMaterial)
			{
				material->setAlpha(osg::Material::FRONT, _materialAlpha); 
				stateset->setMode( GL_BLEND, osg::StateAttribute::ON );
				stateset->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
				stateset->setRenderBinDetails( 30, "DepthSortedBin");
			}

			if(_MaterialType > 0)
			{
				material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(_MatAmbientColorR, _MatAmbientColorG, _MatAmbientColorB, _MatAmbientColorA)); 
				material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(_MatDiffuseColorR, _MatDiffuseColorG, _MatDiffuseColorB, _MatDiffuseColorA)); 
				material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(_MatSpecularColorR, _MatSpecularColorG, _MatSpecularColorB, _MatSpecularColorA)); 
				material->setEmission(osg::Material::FRONT_AND_BACK, osg::Vec4(_MatEmissionColorR, _MatEmissionColorG, _MatEmissionColorB, _MatEmissionColorA)); 			
				material->setShininess(osg::Material::FRONT_AND_BACK, _MatShininess); 

				osg::Material::ColorMode colormode;
				switch(_MaterialType)
				{
					case 1:
						colormode = osg::Material::AMBIENT;
					break;
					case 2:
						colormode = osg::Material::DIFFUSE;
					break;
					case 3:
						colormode = osg::Material::SPECULAR;
					break;
					case 4:
						colormode = osg::Material::EMISSION;
					break;
					case 5:
						colormode = osg::Material::AMBIENT_AND_DIFFUSE;
					break;
				}
				material->setColorMode(colormode); 

			}

			stateset->setAttributeAndModes(material, 
							osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON); 
		}
		else
		{
			osg::StateSet* stateset = node->getOrCreateStateSet();
			stateset->removeAttribute(osg::StateAttribute::MATERIAL);

			//stateset->setMode(GL_COLOR_MATERIAL, osg::StateAttribute::OFF); 
			stateset->setRenderingHint( osg::StateSet::DEFAULT_BIN );
		}
	}
}


/***********************************************************
set shout text
***********************************************************/
void OsgObjectHandler::SetShoutText(const std::string & text, float size, 
								float colorR, float colorG, float colorB, int TTL)
{
	osg::ref_ptr<osg::Group> root = GetRootNoLight();
	if(root)
	{
		if(_shouttextgroup)
		{
			root->removeChild(_shouttextgroup);
			_shouttextgroup = NULL;
		}

		if(text!= "")
		{
			_ttlshout = SynchronizedTimeHandler::GetCurrentTimeDouble() + (TTL*1000);

			osg::Vec3 posT;
			if(_uselight)
			{
				osg::BoundingSphere bs = GetRoot()->computeBound();
				posT = bs.center()+ osg::Vec3(0,size/15,0);		
			}
			else
			{
				osg::BoundingSphere bs = GetRootNoLight()->computeBound();
				posT = bs.center()+ osg::Vec3(0,size/15,0);	
			}

			_shouttextgroup = new osg::AutoTransform();
			_shouttextgroup->setPosition(posT);
			_shouttextgroup->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
			_shouttextgroup->setMinimumScale(0.01);
			_shouttextgroup->setMaximumScale(0.5);
			_shouttextgroup->setAutoScaleToScreen(true);

			osg::ref_ptr<osg::Geode> _textgeode = new osg::Geode();
			osg::ref_ptr<osgText::Text> textd = new osgText::Text();
			textd->setText(text);
			textd->setColor(osg::Vec4(colorR, colorG, colorB, 1));
			textd->setCharacterSize(size);
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
			stateSet->setRenderBinDetails( 500, "DepthSortedBin");

			_shouttextgroup->addChild(_textgeode);
			root->addChild(_shouttextgroup);
		}
	}	
}

/***********************************************************
display talking icon
***********************************************************/
void OsgObjectHandler::DisplayOrHideTalkingIcon(bool display, bool left)
{
	osg::ref_ptr<osg::Group> root = GetRootNoLight();
	if(root)
	{
		if(!display)
		{
			if(_OsgVoiceSprite)
			{
				root->removeChild(_OsgVoiceSprite);
				_OsgVoiceSprite = NULL;
			}

			if(_textgroup)
				root->addChild(_textgroup);
		}
		else
		{
			std::string spritef = "GUI/imagesets/bubble-big.png";
			//if(left)
			//	spritef = "Worlds/Lba1Original/Sprites/sprite090.png";

			boost::shared_ptr<DisplayTransformation> Tr = 
				boost::shared_ptr<DisplayTransformation>(new DisplayTransformation());

			Tr->translationY = 3;
			Tr->scaleX = 0.5f;
			Tr->scaleY = 0.2f;
			Tr->scaleZ = 0.5f;

			_OsgVoiceSprite = OsgHandler::getInstance()->CreateSpriteObject(_sceneidx, spritef, 1, 1, 1, 0.95f, 
																Tr, false, false, true);
			if(_OsgVoiceSprite)
				root->addChild(_OsgVoiceSprite);

			if(_textgroup)
				root->removeChild(_textgroup);
		}
	}
}