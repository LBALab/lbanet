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

#include "Lba1ModelHandler.h"
#include "LBA1ModelClass.h"
#include "DataLoader.h"
#include "Entities.h"
#include "LogHandler.h"
#include "Lba1ModelMapHandler.h"
#include "OSGHandler.h"

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/AutoTransform>



/***********************************************************
Constructor
***********************************************************/
Lba1ModelHandler::Lba1ModelHandler(boost::shared_ptr<DisplayTransformation> Tr,
								   const LbaNet::ModelInfo & info, float animationspeed,
									const LbaNet::ObjectExtraInfo &extrainfo,
									const LbaNet::LifeManaInfo &lifeinfo)
: AnimatedObjectHandlerBase(Tr, extrainfo), _model(NULL), _animationspeed(animationspeed),
	_currAnimation(-1), _currModel(-1), _currBody(-1), _paused(false), _lifeinfo(lifeinfo)
{
	UpdateModel(info);
}

/***********************************************************
destructor
***********************************************************/
Lba1ModelHandler::~Lba1ModelHandler()
{
	// delete old model
	if(_model)
		delete _model;

	// delete old node
	osg::ref_ptr<osg::Group> root = GetRoot();
	if(root && _osgnode)
		root->removeChild(_osgnode);
}

/***********************************************************
update display with current frame - used for animation
***********************************************************/
int Lba1ModelHandler::Process(double time, float tdiff)
{
	bool animationfinished = false;

	if(!_paused && _model)
		animationfinished = _model->AnimateModel(tdiff);

	if(animationfinished)
		return 1;	// return 1 if animation is terminated
	else
		return 0;	// return 0 else
}

/***********************************************************
get current animation Id
***********************************************************/
std::string Lba1ModelHandler::GetCurrentAnimation()
{
	return _currentanimationstring;
}

/***********************************************************
get current associated speed
***********************************************************/
float Lba1ModelHandler::GetCurrentAssociatedSpeedX()
{
	if(_model)
		return _model->GetCurrentSpeedX();

	return 0;
}

/***********************************************************
get current associated speed
***********************************************************/
float Lba1ModelHandler::GetCurrentAssociatedSpeedY()
{
	if(_model)
		return _model->GetCurrentSpeedY();

	return 0;
}


/***********************************************************
get current associated speed
***********************************************************/
float Lba1ModelHandler::GetCurrentAssociatedSpeedZ()
{
	if(_model)
		return _model->GetCurrentSpeedZ();

	return 0;
}

/***********************************************************
update model
***********************************************************/
int Lba1ModelHandler::UpdateModel(const LbaNet::ModelInfo & info)
{
	_currentmodelinfo = info;
	return RefreshModel();
}


/***********************************************************
update animation
***********************************************************/
int Lba1ModelHandler::UpdateAnimation(const std::string & AnimString)
{
	if(_currentanimationstring != AnimString)
	{
		_currentanimationstring = AnimString;
		return RefreshModel();
	}

	return 0;
}




/***********************************************************
refresh model
***********************************************************/
int Lba1ModelHandler::RefreshModel()
{
	int newmodel=0;
	int newbody=0;
	std::vector<int> newanimations;
	int res = Lba1ModelMapHandler::getInstance()->GetModelInfo(	_currentmodelinfo.ModelName,
																_currentmodelinfo.Outfit,
																_currentmodelinfo.Weapon,
																_currentmodelinfo.Mode,
																_currentanimationstring,
																newmodel,
																newbody,
																newanimations);
	// model invalid or not existing
	if(res < 0)
		return res;


	entitiesTableStruct* tmpstrcut = DataLoader::getInstance()->GetEntitiesInfo();


	// do nothing if same model loaded already
	if( (newmodel != _currModel) || (newbody != _currBody) ) 
	{
		std::stringstream strs;
		strs<<"Loading new lba1 model with entity "<<newmodel<<" and body "<<newbody<<std::endl;
		LogHandler::getInstance()->LogToFile(strs.str());

		// delete old model
		if(_model)
			delete _model;

		// delete old node
		osg::ref_ptr<osg::Group> root = GetRoot();
		if(root && _osgnode)
			root->removeChild(_osgnode);

		// reset current animation
		_currModel = newmodel;
		_currBody = newbody;
		_currAnimation = 0;

		_model = new LBA1ModelClass(	tmpstrcut, 
										Lba1ModelDataPath+"BODY.HQR", 
										Lba1ModelDataPath+"ANIM.HQR", 
										_currModel,
										tmpstrcut->entitiesTable[_currModel].bodyList[_currBody].body);

		_model->SetAnimationSpeedFactor(_animationspeed);

		_model->LoadAnim(	tmpstrcut,
							tmpstrcut->entitiesTable[_currModel].animList[_currAnimation].index);

		_osgnode = _model->ExportOSGModel(true);
		if(root)
			root->addChild(_osgnode);

		_paused = false;
	}

	// do nothing if same animation loaded already
	if(_currAnimation != newanimations[0]) // TODO change to use animation vector
	{
		_currAnimation = newanimations[0];
		_model->LoadAnim(	tmpstrcut,
							tmpstrcut->entitiesTable[_currModel].animList[_currAnimation].index);

		_paused = false;
	}


	// refresh text part
	RefreshText();

	// refresh life part
	RefreshLifeManaBars();

	return 0;
}


/***********************************************************
pause current running animation
***********************************************************/
void Lba1ModelHandler::PauseAnimation()
{
	_paused = true;
}





/***********************************************************
refresh life/mana bars
***********************************************************/
void Lba1ModelHandler::RefreshLifeManaBars()
{
	osg::ref_ptr<osg::Group> root = GetRootNoLight();
	if(root)
	{
		if(_barsgroup)
		{
			root->removeChild(_barsgroup);
			_barsgroup = NULL;
		}

		_barsgroup = new osg::AutoTransform();
		//_barsgroup->setScale(osg::Vec3(0.04f, 0.04f, 0.04f));
		_barsgroup->setPosition(osg::Vec3(0, -1, 0));
		_barsgroup->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_SCREEN);
		_barsgroup->setMinimumScale(0.0004);
		_barsgroup->setMaximumScale(0.4);
		_barsgroup->setAutoScaleToScreen(true);


		osg::ref_ptr<osg::Geode> barsgeode = new osg::Geode();
		float sizebar=20;
		
		// add bars
		{
			osg::ref_ptr<osg::Geometry> myGeometry = new osg::Geometry();
			osg::Vec2Array* myVertices = new osg::Vec2Array;
			osg::Vec4Array* myColors = new osg::Vec4Array;

			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec2(-sizebar,0));
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec2(sizebar,0));		
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec2(sizebar,4));	
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec2(-sizebar,4));	

			myColors->push_back(osg::Vec4(11/255.f, 11/255.f, 71/255.f, 1));
			myVertices->push_back(osg::Vec2(-sizebar,0));	
			myColors->push_back(osg::Vec4(11/255.f, 11/255.f, 71/255.f, 1));
			myVertices->push_back(osg::Vec2(-sizebar+(sizebar*2*_lifeinfo.CurrentMana/_lifeinfo.MaxMana),0));	
			myColors->push_back(osg::Vec4(13/255.f, 12/255.f, 150/255.f, 1));
			myVertices->push_back(osg::Vec2(-sizebar+(sizebar*2*_lifeinfo.CurrentMana/_lifeinfo.MaxMana),4));	
			myColors->push_back(osg::Vec4(13/255.f, 12/255.f, 150/255.f, 1));
			myVertices->push_back(osg::Vec2(-sizebar,4));	


			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec2(-sizebar,6));
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec2(sizebar,6));		
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec2(sizebar,10));	
			myColors->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 0.3f));
			myVertices->push_back(osg::Vec2(-sizebar,10));	

			myColors->push_back(osg::Vec4(115/255.f, 0.f, 2/255.f, 1));
			myVertices->push_back(osg::Vec2(-sizebar,6));	
			myColors->push_back(osg::Vec4(115/255.f, 0.f, 2/255.f, 1));
			myVertices->push_back(osg::Vec2(-sizebar+(sizebar*2*_lifeinfo.CurrentLife/_lifeinfo.MaxLife),6));	
			myColors->push_back(osg::Vec4(254/255.f, 0.f, 3/255.f, 1));
			myVertices->push_back(osg::Vec2(-sizebar+(sizebar*2*_lifeinfo.CurrentLife/_lifeinfo.MaxLife),10));	
			myColors->push_back(osg::Vec4(254/255.f, 0.f, 3/255.f, 1));
			myVertices->push_back(osg::Vec2(-sizebar,10));	


			osg::DrawElementsUInt* myprimitive = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
			for(int i=0; i<16; ++i)
				myprimitive->push_back(i);


			myGeometry->addPrimitiveSet(myprimitive);
			myGeometry->setVertexArray( myVertices ); 
			myGeometry->setColorArray(myColors);
			myGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
			barsgeode->addDrawable(myGeometry.get());
		}

		// add contour
		{
			osg::ref_ptr<osg::Geometry> myGeometry = new osg::Geometry();
			osg::Vec2Array* myVertices = new osg::Vec2Array;
			osg::Vec4Array* myColors = new osg::Vec4Array;



			myColors->push_back(osg::Vec4(0.f, 104/255.f, 107/255.f, 0.7f));
			myVertices->push_back(osg::Vec2(-sizebar,0));
			myColors->push_back(osg::Vec4(0.f, 104/255.f, 107/255.f, 0.7f));
			myVertices->push_back(osg::Vec2(sizebar,0));		
			myColors->push_back(osg::Vec4(115/255.f, 252/255.f, 252/255.f, 0.7f));
			myVertices->push_back(osg::Vec2(sizebar,4));	
			myColors->push_back(osg::Vec4(115/255.f, 252/255.f, 252/255.f, 0.7f));
			myVertices->push_back(osg::Vec2(-sizebar,4));	


			myColors->push_back(osg::Vec4(0.f, 104/255.f, 107/255.f, 0.7f));
			myVertices->push_back(osg::Vec2(-sizebar,6));
			myColors->push_back(osg::Vec4(0.f, 104/255.f, 107/255.f, 0.7f));
			myVertices->push_back(osg::Vec2(sizebar,6));		
			myColors->push_back(osg::Vec4(115/255.f, 252/255.f, 252/255.f, 0.7f));
			myVertices->push_back(osg::Vec2(sizebar,10));	
			myColors->push_back(osg::Vec4(115/255.f, 252/255.f, 252/255.f, 0.7f));
			myVertices->push_back(osg::Vec2(-sizebar,10));	


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
			barsgeode->addDrawable(myGeometry.get());
		}

		osg::StateSet* stateSet = barsgeode->getOrCreateStateSet();
		stateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
		stateSet->setMode(GL_TEXTURE_2D,osg::StateAttribute::OFF);
		stateSet->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
		stateSet->setRenderBinDetails( 10000, "RenderBin");

		_barsgroup->addChild(barsgeode);
		root->addChild(_barsgroup);
	}
}





/***********************************************************
update object life info
***********************************************************/
void Lba1ModelHandler::UpdateLifeInfo(const LbaNet::LifeManaInfo &info)
{
	_lifeinfo = info;
	RefreshLifeManaBars();
}