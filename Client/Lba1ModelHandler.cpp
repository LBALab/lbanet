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
#include <osgText/Text>


/***********************************************************
Constructor
***********************************************************/
Lba1ModelHandler::Lba1ModelHandler(boost::shared_ptr<DisplayTransformation> Tr,
								   const LbaNet::ModelInfo & info, float animationspeed,
									const LbaNet::ObjectExtraInfo &extrainfo,
									const LbaNet::LifeManaInfo &lifeinfo)
: AnimatedObjectHandlerBase(Tr), _model(NULL), _animationspeed(animationspeed),
	_currAnimation(-1), _currModel(-1), _currBody(-1), _paused(false),
	_extrainfo(extrainfo), _lifeinfo(lifeinfo)
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
refresh text
***********************************************************/
void Lba1ModelHandler::RefreshText()
{
	osg::ref_ptr<osg::Group> root = GetRoot();
	if(root)
	{
		if(_textgeode)
		{
			root->removeChild(_textgeode);
			_textgeode = NULL;
		}

		_textgeode = new osg::Geode();
		osg::ref_ptr<osgText::Text> textd = new osgText::Text();
		textd->setText(_extrainfo.Name);
		textd->setColor(osg::Vec4(_extrainfo.NameColorR, _extrainfo.NameColorG, _extrainfo.NameColorB, 1));
		textd->setAxisAlignment(osgText::Text::SCREEN);
		textd->setCharacterSize(/*0.4f*/25);
		textd->setFont("Tahoma.ttf");
		textd->setAlignment(osgText::Text::CENTER_CENTER);
		textd->setPosition (osg::Vec3(0, 3.5f, 0));
		//textd->setAutoRotateToScreen(true);
		textd->setCharacterSizeMode(osgText::Text::SCREEN_COORDS);


		textd->setBackdropColor(osg::Vec4(0, 0, 0, 1));
		textd->setBackdropType(osgText::Text::OUTLINE);
		textd->setBackdropImplementation(osgText::Text::NO_DEPTH_BUFFER);
		textd->setBackdropOffset(0.1f);

		_textgeode->addDrawable(textd);
		root->addChild(_textgeode);

		osg::StateSet* stateSet = _textgeode->getOrCreateStateSet();
		stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
		stateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
		stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
		stateSet->setRenderBinDetails( 100, "RenderBin");
	}
}



/***********************************************************
update object extra info
***********************************************************/
void Lba1ModelHandler::UpdateExtraInfo(const LbaNet::ObjectExtraInfo &info)
{
	_extrainfo = info;
	RefreshText();
}

/***********************************************************
update object life info
***********************************************************/
void Lba1ModelHandler::UpdateLifeInfo(const LbaNet::LifeManaInfo &info)
{
	_lifeinfo = info;
}