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
#include "Entities.h"
#include "LogHandler.h"
#include "Lba1ModelMapHandler.h"
#include "OSGHandler.h"
#include "Randomizer.h"

#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/AutoTransform>
#include <osgUtil/SmoothingVisitor>


entitiesTableStruct* Lba1ModelHandler::_estruct = NULL;

/***********************************************************
Constructor
***********************************************************/
Lba1ModelHandler::Lba1ModelHandler(boost::shared_ptr<DisplayTransformation> Tr,
								   const LbaNet::ModelInfo & info, float animationspeed,
								   bool UseLight, bool CastShadow,
									const LbaNet::ObjectExtraInfo &extrainfo,
									const LbaNet::LifeManaInfo &lifeinfo,
									bool mainchar)
: AnimatedObjectHandlerBase(Tr, extrainfo, lifeinfo, info), _model(NULL), _animationspeed(animationspeed),
	_currAnimation(-1), _currModel(-1), _currBody(-1),
	_UseLight(UseLight), _CastShadow(CastShadow), _mainchar(mainchar)
{
	if(_estruct == NULL)
		_estruct = parseEntities(Lba1ModelDataPath+"FILE3D.HQR");

	UpdateModel();

	// forbid optimization on this node
	ForbidOptimize();
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
	{
		osg::ref_ptr<osg::Group> root;
		if(_UseLight)
			root = GetRoot();
		else
			root = GetRootNoLight();

		if(root && _osgnode)
			root->removeChild(_osgnode);
	}

	{
		osg::ref_ptr<osg::Group> root = GetRootNoLight();
		if(root)
		{
			if(_barsgroup)
			{
				root->removeChild(_barsgroup);
				_barsgroup = NULL;
			}
		}
	}
}

/***********************************************************
update display with current frame - used for animation
***********************************************************/
int Lba1ModelHandler::ProcessInternal(double time, float tdiff)
{
	bool animationfinished = false;

	if(!_paused && _model)
		animationfinished = _model->AnimateModel(tdiff);

	if(animationfinished)
	{
		RefreshModel(false);
		return 1;	// return 1 if animation is terminated
	}
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
int Lba1ModelHandler::UpdateModel()
{
	// update colors if needed
	{
		if(_currentmodelinfo.SkinColor >= 0)
		{
			std::vector<LbaNet::Lba1ColorIndex>	defaultc;
			std::vector<int>	alternativec;

			int res = Lba1ModelMapHandler::getInstance()->GetModelColorAlternative(_currentmodelinfo.ModelName,
																			_currentmodelinfo.Outfit,
																			_currentmodelinfo.Weapon,
																			_currentmodelinfo.Mode,
																			"SkinColor",
																			_currentmodelinfo.SkinColor,
																			defaultc, alternativec);

			if(defaultc.size() == alternativec.size())
				for(size_t cc=0; cc<defaultc.size(); ++cc)
					_currentmodelinfo.ColorSwaps[defaultc[cc]] = alternativec[cc];
		}

		if(_currentmodelinfo.EyesColor >= 0)
		{
			std::vector<LbaNet::Lba1ColorIndex>	defaultc;
			std::vector<int>	alternativec;

			int res = Lba1ModelMapHandler::getInstance()->GetModelColorAlternative(_currentmodelinfo.ModelName,
																			_currentmodelinfo.Outfit,
																			_currentmodelinfo.Weapon,
																			_currentmodelinfo.Mode,
																			"EyesColor",
																			_currentmodelinfo.EyesColor,
																			defaultc, alternativec);

			if(defaultc.size() == alternativec.size())
				for(size_t cc=0; cc<defaultc.size(); ++cc)
					_currentmodelinfo.ColorSwaps[defaultc[cc]] = alternativec[cc];
		}

		if(_currentmodelinfo.HairColor >= 0)
		{
			std::vector<LbaNet::Lba1ColorIndex>	defaultc;
			std::vector<int>	alternativec;

			int res = Lba1ModelMapHandler::getInstance()->GetModelColorAlternative(_currentmodelinfo.ModelName,
																			_currentmodelinfo.Outfit,
																			_currentmodelinfo.Weapon,
																			_currentmodelinfo.Mode,
																			"HairColor",
																			_currentmodelinfo.HairColor,
																			defaultc, alternativec);

			if(defaultc.size() == alternativec.size())
				for(size_t cc=0; cc<defaultc.size(); ++cc)
					_currentmodelinfo.ColorSwaps[defaultc[cc]] = alternativec[cc];
		}

		if(_currentmodelinfo.OutfitColor >= 0)
		{
			std::vector<LbaNet::Lba1ColorIndex>	defaultc;
			std::vector<int>	alternativec;

			int res = Lba1ModelMapHandler::getInstance()->GetModelColorAlternative(_currentmodelinfo.ModelName,
																			_currentmodelinfo.Outfit,
																			_currentmodelinfo.Weapon,
																			_currentmodelinfo.Mode,
																			"OutfitColor",
																			_currentmodelinfo.OutfitColor,
																			defaultc, alternativec);

			if(defaultc.size() == alternativec.size())
				for(size_t cc=0; cc<defaultc.size(); ++cc)
					_currentmodelinfo.ColorSwaps[defaultc[cc]] = alternativec[cc];
		}

		if(_currentmodelinfo.WeaponColor >= 0)
		{
			std::vector<LbaNet::Lba1ColorIndex>	defaultc;
			std::vector<int>	alternativec;

			int res = Lba1ModelMapHandler::getInstance()->GetModelColorAlternative(_currentmodelinfo.ModelName,
																			_currentmodelinfo.Outfit,
																			_currentmodelinfo.Weapon,
																			_currentmodelinfo.Mode,
																			"WeaponColor",
																			_currentmodelinfo.WeaponColor,
																			defaultc, alternativec);

			if(defaultc.size() == alternativec.size())
				for(size_t cc=0; cc<defaultc.size(); ++cc)
					_currentmodelinfo.ColorSwaps[defaultc[cc]] = alternativec[cc];
		}

		if(_currentmodelinfo.MountSkinColor >= 0)
		{
			std::vector<LbaNet::Lba1ColorIndex>	defaultc;
			std::vector<int>	alternativec;

			int res = Lba1ModelMapHandler::getInstance()->GetModelColorAlternative(_currentmodelinfo.ModelName,
																			_currentmodelinfo.Outfit,
																			_currentmodelinfo.Weapon,
																			_currentmodelinfo.Mode,
																			"MountSkinColor",
																			_currentmodelinfo.MountSkinColor,
																			defaultc, alternativec);

			if(defaultc.size() == alternativec.size())
				for(size_t cc=0; cc<defaultc.size(); ++cc)
					_currentmodelinfo.ColorSwaps[defaultc[cc]] = alternativec[cc];
		}

		if(_currentmodelinfo.MountHairColor >= 0)
		{
			std::vector<LbaNet::Lba1ColorIndex>	defaultc;
			std::vector<int>	alternativec;

			int res = Lba1ModelMapHandler::getInstance()->GetModelColorAlternative(_currentmodelinfo.ModelName,
																			_currentmodelinfo.Outfit,
																			_currentmodelinfo.Weapon,
																			_currentmodelinfo.Mode,
																			"MountHairColor",
																			_currentmodelinfo.MountHairColor,
																			defaultc, alternativec);

			if(defaultc.size() == alternativec.size())
				for(size_t cc=0; cc<defaultc.size(); ++cc)
					_currentmodelinfo.ColorSwaps[defaultc[cc]] = alternativec[cc];
		}
	}


	return RefreshModel(true);
}


/***********************************************************
update animation
***********************************************************/
int Lba1ModelHandler::UpdateAnimation()
{
	return RefreshModel();
}



/***********************************************************
update display
***********************************************************/
int Lba1ModelHandler::Update(LbaNet::DisplayObjectUpdateBasePtr update,
								bool updatestoredstate)
{
	const std::type_info& info = typeid(*update);

	// Lba1ModelColorUpdate
	if(info == typeid(LbaNet::Lba1ModelColorUpdate))
	{
		LbaNet::Lba1ModelColorUpdate * castedptr = 
			dynamic_cast<LbaNet::Lba1ModelColorUpdate *>(update.get());

		LbaNet::Lba1ColorIndex colorpair;
		colorpair.ModelPart = castedptr->Colorpart;
		colorpair.Color = castedptr->OldColor;
		_currentmodelinfo.ColorSwaps[colorpair] = castedptr->NewColor;
		RefreshModel(true);

		return 0;
	}



	return AnimatedObjectHandlerBase::Update(update, updatestoredstate);
}


/***********************************************************
refresh model
***********************************************************/
int Lba1ModelHandler::RefreshModel(bool forcecolor)
{
	bool modelchanged = false;
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




	// do nothing if same model loaded already
	if( forcecolor || (newmodel != _currModel) || (newbody != _currBody) ) 
	{
		std::stringstream strs;
		strs<<"Loading new lba1 model with entity "<<newmodel<<" and body "<<newbody<<std::endl;
		LogHandler::getInstance()->LogToFile(strs.str());

		// delete old model
		if(_model)
			delete _model;

		// delete old node
		osg::ref_ptr<osg::Group> root;
		if(_UseLight)
			root = GetRoot();
		else
			root = GetRootNoLight();

		if(root && _osgnode)
			root->removeChild(_osgnode);

		// reset current animation
		_currModel = newmodel;
		_currBody = newbody;
		_currAnimation = 0;

		_model = new LBA1ModelClass(	_estruct, 
										Lba1ModelDataPath+"BODY.HQR", 
										Lba1ModelDataPath+"ANIM.HQR", 
										_currModel,
										_estruct->entitiesTable[_currModel].bodyList[_currBody].body);


		// set colors
		{
			std::map<LbaNet::Lba1ColorIndex, int>::iterator itcolo = _currentmodelinfo.ColorSwaps.begin();
			std::map<LbaNet::Lba1ColorIndex, int>::iterator endcolo = _currentmodelinfo.ColorSwaps.end();
			for(; itcolo != endcolo; ++itcolo)
			{
				switch(itcolo->first.ModelPart)
				{
					case LbaNet::PolygonColor:
						_model->changeAllPolygonColors(itcolo->first.Color, itcolo->second);
					break;

					case LbaNet::SphereColor:
						// special case - horse hair and twinsen hairs are the same
						if(itcolo->first.Color == 999)
							_model->change1SphereColors(6, itcolo->second);
						else
						{
							if(itcolo->first.Color == 998)
								_model->change1SphereColors(3, itcolo->second);
							else
								_model->changeAllSphereColors(itcolo->first.Color, itcolo->second);	
						}
					break;

					case LbaNet::LineColor:
						_model->changeAllLineColors(itcolo->first.Color, itcolo->second);
					break;
				}
			}
		}


		_model->SetAnimationSpeedFactor(_animationspeed);

		_model->LoadAnim(	_estruct,
							_estruct->entitiesTable[_currModel].animList[_currAnimation].index);

		_osgnode = _model->ExportOSGModel(true, _mainchar);

		if(_CastShadow)
			_osgnode->setNodeMask(ReceivesShadowTraversalMask | CastsShadowTraversalMask);
		else
			_osgnode->setNodeMask(ReceivesShadowTraversalMask);

		if(root)
		{
			root->addChild(_osgnode);
		}

		_paused = false;
		modelchanged = true;
	}

	int pickedanimation;
	if(newanimations.size() == 1)
		pickedanimation = 0;
	else
		pickedanimation = Randomizer::getInstance()->RandInt((int)newanimations.size()-1);


	// do nothing if same animation loaded already
	if(_currAnimation != newanimations[pickedanimation]) // TODO change to use animation vector
	{
		_currAnimation = newanimations[pickedanimation];
		_model->LoadAnim(	_estruct,
							_estruct->entitiesTable[_currModel].animList[_currAnimation].index);

		_paused = false;
	}

	
	if(modelchanged)
	{
		// refresh text part
		RefreshText();

		// refresh life part
		RefreshLifeManaBars();
	}

	return 0;
}



/***********************************************************
save current model state
***********************************************************/
void Lba1ModelHandler::SaveState()
{
	AnimatedObjectHandlerBase::SaveState();
}

/***********************************************************
restore previously saved model state
***********************************************************/
void Lba1ModelHandler::RestoreState()
{
	AnimatedObjectHandlerBase::RestoreState();
	RefreshModel();
}


/***********************************************************
check if can play animation
***********************************************************/
bool Lba1ModelHandler::CanPlayAnimation(const std::string & anim)
{
	return Lba1ModelMapHandler::getInstance()->CanPlayAnimation(	_currentmodelinfo.ModelName,
																	_currentmodelinfo.Outfit,
																	_currentmodelinfo.Weapon,
																	_currentmodelinfo.Mode,
																	anim);
}


/***********************************************************
return animation key frame
***********************************************************/
int Lba1ModelHandler::GetCurrentKeyFrame()
{
	if(_model)
		return _model->getKeyframe();

	return -1;
}