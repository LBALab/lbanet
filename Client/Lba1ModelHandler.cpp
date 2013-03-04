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
#include "OSGHandler.h"
#include "Randomizer.h"
#include "ClientExtendedTypes.h"
#include "DynamicObject.h"
#include "SoundObjectHandlerBase.h"
#include "MusicHandler.h"
#include "StringHelperFuncs.h"
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
Lba1ModelHandler::Lba1ModelHandler(int sceneidx, boost::shared_ptr<DisplayTransformation> Tr,
								   const LbaNet::ModelInfo & info, float animationspeed,
								   bool UseLight, bool CastShadow,
									const LbaNet::ObjectExtraInfo &extrainfo,
									const LbaNet::LifeManaInfo &lifeinfo,
									bool mainchar)
: AnimatedObjectHandlerBase(sceneidx, Tr, extrainfo, lifeinfo, info), _model(NULL), _animationspeed(animationspeed),
	_currAnimation(-1), _currModel(-1), _currBody(-1),
	_UseLight(UseLight), _CastShadow(CastShadow), _mainchar(mainchar)
{
	if(_estruct == NULL)
		_estruct = parseEntities(Lba1ModelDataPath()+"FILE3D.HQR");

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
	{
		animationfinished = _model->AnimateModel(tdiff);

		int kf = _model->getKeyframe();
		if(_currkeyframe != kf)
		{
			_currkeyframe = kf;
			for(size_t oo=0; oo<_obvservers.size(); ++oo)
				_obvservers[oo]->UpdateCurrentKeyframe(_currkeyframe);

			PlayKeyFrameSound(kf);
		}
	}

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

	// RegisterAnimationObserver
	if(info == typeid(RegisterAnimationObserver))
	{
		RegisterAnimationObserver * castedptr = 
			static_cast<RegisterAnimationObserver *>(update.get());

		if(castedptr->_observer)
		{
			_obvservers.push_back(castedptr->_observer);

			if(_model)
			{
				int nbkf = _model->getNumKeyFrames();
				castedptr->_observer->UpdateNumberKeyframe(nbkf);
			}
		}

		_currkeyframe = -1;
		return 0;
	}

	// SetAnimationKeyframe
	if(info == typeid(SetAnimationKeyframe))
	{
		SetAnimationKeyframe * castedptr = 
			static_cast<SetAnimationKeyframe *>(update.get());

		_currkeyframe = castedptr->_keyframe;
		if(_model)
		{
			_model->setAtKeyFrame(_currkeyframe, true);
			_model->AnimateModel(1);
		}
		
		return 0;
	}
	
	// UpdateAnimationKeyframeInfo
	if(info == typeid(UpdateAnimationKeyframeInfo))
	{
		UpdateAnimationKeyframeInfo * castedptr = 
			static_cast<UpdateAnimationKeyframeInfo *>(update.get());

		if(castedptr->_frameid < 0)
		{
			_curraniminfo.repeatedsoundpath = castedptr->_afd->soundpath;
			RefrehAnimRepeatingSound();
		}
		else
			_curraniminfo.animationframes[castedptr->_frameid] = *(castedptr->_afd);
		
		delete castedptr->_afd;
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
										Lba1ModelDataPath()+"BODY.HQR", 
										Lba1ModelDataPath()+"ANIM.HQR", 
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

		RetrieveAnimInfo();

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

		RetrieveAnimInfo();

		_paused = false;

		int nbkf = _model->getNumKeyFrames();
		for(size_t oo=0; oo<_obvservers.size(); ++oo)
			_obvservers[oo]->UpdateNumberKeyframe(nbkf);
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


/***********************************************************
RefrehAnimRepeatingSound
***********************************************************/
void Lba1ModelHandler::RefrehAnimRepeatingSound()
{
	if(_curraniminfo.repeatedsoundpath == "")
		PlaySound("", 4, false);
	else
		PlaySound(DataDirHandler::getInstance()->GetDataDirPath() + "/"+_curraniminfo.repeatedsoundpath, 4, true);
}

/***********************************************************
play sound
***********************************************************/
void Lba1ModelHandler::PlaySound(const std::string & path, int channel, bool repeat)
{
	if(_parent)
	{
		boost::shared_ptr<SoundObjectHandlerBase> soundH = _parent->GetSoundObject();
		if(soundH)
		{
			LbaNet::PlayingSound snd;
			snd.SoundChannel = channel;
			snd.SoundPath = "";
			snd.NbTime = repeat ? -1 : 1;
			snd.Paused = false;
			snd.RandomPitch = false;
			soundH->SetSound(snd, false); // first reset

			snd.SoundPath = path;
			soundH->SetSound(snd, false); // then play
		}
	} 
}


/***********************************************************
retrieve anim info
***********************************************************/
void Lba1ModelHandler::RetrieveAnimInfo()
{
	int res = Lba1ModelMapHandler::getInstance()->GetModelAnimationInfo(_currentmodelinfo.ModelName,
																_currentmodelinfo.Outfit,
																_currentmodelinfo.Weapon,
																_currentmodelinfo.Mode,
																_currentanimationstring,
																_curraniminfo);

	RefrehAnimRepeatingSound();
}


/***********************************************************
play sound at keyframe
***********************************************************/
void Lba1ModelHandler::PlayKeyFrameSound(int keyframe)
{
	std::map<int, AnimationFrameData >::iterator it = _curraniminfo.animationframes.find(keyframe);
	if(it != _curraniminfo.animationframes.end())
	{
		std::string sp = it->second.soundpath;

		if(DataDirHandler::getInstance()->IsInSoundEditorMode())
		{
			if(sp == "#ground1")
				sp = "Worlds/Lba1Original/Sound/SAMPLES127.wav";
			if(sp == "#ground2")
				sp = "Worlds/Lba1Original/Sound/SAMPLES142.wav";
		}
		else
		{
			if(sp == "#ground1")
				sp = GetFloorSoundPath(1);
			if(sp == "#ground2")
				sp = GetFloorSoundPath(2);
		}

		if(sp != "")
		{
			if(sp[0] == '*')
			{
				std::vector<std::string> tokens;

				// random sounds
				sp = sp.substr(1);
				StringHelper::Tokenize(sp, tokens, "@");
				sp = tokens[Randomizer::getInstance()->RandInt(tokens.size())];
			}

			sp=DataDirHandler::getInstance()->GetDataDirPath() + "/"+sp;
			PlaySound(sp,( _togglesoundC?2:3), false);
			_togglesoundC = !_togglesoundC;
		}
	}
	
}


/***********************************************************
GetFloorSoundPath
***********************************************************/
std::string Lba1ModelHandler::GetFloorSoundPath(int id)
{
	if(_parent)
	{
		boost::shared_ptr<PhysicalObjectHandlerBase> physH = _parent->GetPhysicalObject();
		if(physH)
		{
			short material = physH->GetFloorMaterial();
			if(material > 0)
			{
				return MusicHandler::getInstance()->GetFloorSoundPath(material, id);
			}
		}
	} 

	return "";
}