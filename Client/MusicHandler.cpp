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

#include "MusicHandler.h"
#include "ConfigurationManager.h"
#include "LogHandler.h"

#include <iostream>

#include <osgAudio/FileStream.h>
#include <osgAudio/SoundUpdateCB.h>
#include <osgAudio/SoundRoot.h>
#include <osgAudio/SoundManager.h>
#include <osgAudio/SoundState.h>
#include <osgAudio/Version.h>
#include <osgAudio/SoundNode.h>

#include <osg/Camera>

#include "OSGHandler.h"


MusicHandler* MusicHandler::_singletonInstance = NULL;


/***********************************************************
constructor
***********************************************************/
PlayingSoundHandler::PlayingSoundHandler(const std::string & filename, 
											osgAudio::SoundState* sound)
	: _filename(filename), _soundstate(sound), _paused(false)
{

}

/***********************************************************
destructor
***********************************************************/
PlayingSoundHandler::~PlayingSoundHandler()
{
	if(_soundstate)
	{
		_soundstate->setPlay(false);
		osgAudio::SoundManager::instance()->removeSoundState(_soundstate);
	}
		
}

/***********************************************************
pause playing
***********************************************************/
void PlayingSoundHandler::Pause()
{
	if(!_paused)
	{
		_paused = true;

		if(_soundstate)
			_soundstate->setPlay(false);
	}
}

/***********************************************************
resume playing
***********************************************************/
void PlayingSoundHandler::Resume()
{
	if(_paused)
	{
		_paused = false;

		if(_soundstate)
			_soundstate->setPlay(true);
	}
}

/***********************************************************
set soudn gain (from 0.0 to 1.0)
***********************************************************/
void PlayingSoundHandler::SetGain(float gain)
{
	if(_soundstate)
		_soundstate->setGain(gain);
}

/***********************************************************
set sound loop
***********************************************************/
void PlayingSoundHandler::SetLoop(bool loop)
{
	if(_soundstate)
		_soundstate->setLooping(loop);
}

/***********************************************************
check if sound is looping
***********************************************************/
bool PlayingSoundHandler::IsLooping()
{
	if(_soundstate)
		return _soundstate->getLooping();
	else
		return false;
}


/***********************************************************
return true if finished playing
***********************************************************/
bool PlayingSoundHandler::Finished()
{
	bool playing = false;
	if(_soundstate)	
		playing = _soundstate->isPlaying();

	return !_paused && !playing;
}



/***********************************************************
update sound position and direction
***********************************************************/
void PlayingSoundHandler::Update(float px, float py, float pz, float dx, float dy, float dz)
{
	if(_soundstate)
	{
		_soundstate->setPosition(osg::Vec3(px, py, pz));
		//_soundstate->setDirection(osg::Vec3(dx, dy, dz));
	}
}



/***********************************************************
check if paused
***********************************************************/
bool PlayingSoundHandler::Paused()
{
	return _paused;
}



/***********************************************************
singleton pattern
***********************************************************/
MusicHandler * MusicHandler::getInstance()
{
    if(!_singletonInstance)
    {
        _singletonInstance = new MusicHandler();
		return _singletonInstance;
    }
    else
    {
		return _singletonInstance;
    }
}


/***********************************************************
	Constructor
***********************************************************/
MusicHandler::MusicHandler()
: _soundEnabled(true), _counter(1)
{
	int volG, volM, volS;
	ConfigurationManager::GetInstance()->GetInt("Options.Sound.GeneralVolume", volG);
	ConfigurationManager::GetInstance()->GetInt("Options.Sound.MusicVolume", volM);
	ConfigurationManager::GetInstance()->GetInt("Options.Sound.SampleVolume", volS);
	ConfigurationManager::GetInstance()->GetBool("Options.Sound.SoundEnabled", _soundEnabled);
	_generalvolume = volG/ 100.0f;
	_musicvolume = volM / 100.0f;
	_samplevolume = volS / 100.0f;
}


/***********************************************************
	Denstructor
***********************************************************/
MusicHandler::~MusicHandler()
{

}



/***********************************************************
to be called in beginnning and end of program
***********************************************************/
void MusicHandler::Initialize()
{
    osgAudio::SoundManager::instance()->init(32, true);
    osgAudio::SoundManager::instance()->getEnvironment()->setDistanceModel(osgAudio::InverseDistance/*Linear*/);
    osgAudio::SoundManager::instance()->getEnvironment()->setDopplerFactor(0);
    osgAudio::SoundManager::instance()->getEnvironment()->setUnitScale(1);

	//osg::ref_ptr<osgAudio::SoundRoot> sound_root = new osgAudio::SoundRoot;
	//OsgHandler::getInstance()->SetSoundRoot(sound_root);
}




/***********************************************************
to be called in beginnning and end of program
***********************************************************/
void MusicHandler::Unitialize()
{
	_tmp_sounds.clear();
	osgAudio::SoundManager::instance()->shutdown();
}




/***********************************************************
need to be called once per frame
***********************************************************/
void MusicHandler::Update()
{
	osgAudio::SoundManager::instance()->update();
}



/***********************************************************
call to enable or disable sound
***********************************************************/
void MusicHandler::EnableDisableSound(bool Enable)
{
	_soundEnabled = Enable;

	if(_soundEnabled)
		osgAudio::SoundManager::instance()->getEnvironment()->setGain(_generalvolume);
	else
		osgAudio::SoundManager::instance()->getEnvironment()->setGain(0);
}


/***********************************************************
call to enable or disable sound
***********************************************************/
void MusicHandler::EnableDisableSound()
{
	EnableDisableSound(!_soundEnabled);
	ConfigurationManager::GetInstance()->SetBool("Options.Sound.SoundEnabled", _soundEnabled);
}


/***********************************************************
set the general sound volume
***********************************************************/
void MusicHandler::SetGeneralVolume(int vol)
{
	_generalvolume = vol / 100.0f;

	if(_soundEnabled)
		osgAudio::SoundManager::instance()->getEnvironment()->setGain(_generalvolume);
	else
		osgAudio::SoundManager::instance()->getEnvironment()->setGain(0);
}


/***********************************************************
set the music volume
***********************************************************/
void MusicHandler::SetMusicVolume(int vol)
{
	_musicvolume = vol / 100.0f;

	if(_playing_music)
		_playing_music->SetGain(_musicvolume);
}

/***********************************************************
set the sample volume / will not update currently playign samples
***********************************************************/
void MusicHandler::SetSampleVolume(int vol)
{
	_samplevolume = vol / 100.0f;
}







/***********************************************************
 play a music a number of time
 -1 for infinit
***********************************************************/
void MusicHandler::PlayMusic(const std::string & musicPath, bool loop)
{
	if(_playing_music && _playing_music->GetFilename() == musicPath)
	{
		_playing_music->Resume();
		_playing_music->SetLoop(loop);
		return;
	}

	// reset music
	_playing_music = boost::shared_ptr<PlayingSoundHandler>();

	try
	{
        // Create a new filestream that streams samples from a ogg-file.
        osgAudio::FileStream *musicStream = new osgAudio::FileStream(musicPath.c_str());
		if(musicStream)
		{
			// Create a named sound state.
			osgAudio::SoundState* sound_state = new osgAudio::SoundState(musicPath);
			sound_state->allocateSource(10, false);
			sound_state->setStream( musicStream );
			sound_state->setGain(_musicvolume); 
			sound_state->setAmbient(true);
			sound_state->setPlay(true);
			sound_state->setLooping(loop);
			osgAudio::SoundManager::instance()->addSoundState(sound_state);

			// set the reference pointer to the music
			_playing_music = boost::shared_ptr<PlayingSoundHandler>(new PlayingSoundHandler(musicPath, sound_state));
		}
	}
	catch(osgAudio::Error& ex) 
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception playing music:") + ex.what());
	}
	catch(std::exception& ex) 
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception playing music:") + ex.what());
	}
}


/***********************************************************
stop the music
***********************************************************/
void MusicHandler::StopMusic()
{
	_playing_music = boost::shared_ptr<PlayingSoundHandler>();
}


/***********************************************************
music accessor
***********************************************************/
std::string MusicHandler::GetCurrentMusic()
{
	if(_playing_music)
		return _playing_music->GetFilename();
	else
		return "";
}


/***********************************************************
play 2D sample
***********************************************************/
boost::shared_ptr<PlayingSoundHandler> MusicHandler::PlaySample2D(const std::string & samplepath, bool loop,
																	bool temporary)
{
	try
	{
		// Create a sample, load the sound file.
		osgAudio::Sample* sample = 
			osgAudio::SoundManager::instance()->getSample(samplepath.c_str(), false);

		if(sample)
		{
			// Create a named sound state.
			osgAudio::SoundState* sound_state = new osgAudio::SoundState(samplepath);
			sound_state->allocateSource(10, false);
			sound_state->setSample(sample);
			sound_state->setGain(_samplevolume); 
			sound_state->setAmbient(true);
			sound_state->setPlay(true);
			sound_state->setLooping(!temporary && loop);
			osgAudio::SoundManager::instance()->addSoundState(sound_state);

			boost::shared_ptr<PlayingSoundHandler> res(new PlayingSoundHandler(samplepath, sound_state));

			if(temporary)
			{
				CleanTmpSounds();
				_tmp_sounds.push_back(res);
				return boost::shared_ptr<PlayingSoundHandler>();
			}

			return res;
		}
	}
	catch(osgAudio::Error& ex) 
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception playing sample:") + ex.what());
	}
	catch(std::exception& ex) 
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception playing sample:") + ex.what());
	}

	return boost::shared_ptr<PlayingSoundHandler>();
}

/***********************************************************
play 3D sample
***********************************************************/
boost::shared_ptr<PlayingSoundHandler> MusicHandler::PlaySample3D(const std::string & samplepath, bool loop,
														bool temporary,
														float px, float py, float pz, float dx, float dy, float dz)
{
	try
	{
		// Create a sample, load the sound file.
		osgAudio::Sample* sample = 
			osgAudio::SoundManager::instance()->getSample(samplepath.c_str(), false);


		if(sample)
		{
			// Create a named sound state.
			osgAudio::SoundState* sound_state = new osgAudio::SoundState(samplepath);
			sound_state->allocateSource(10, false);
			sound_state->setSample(sample);
			sound_state->setGain(_samplevolume); 
			sound_state->setAmbient(false);
			sound_state->setReferenceDistance(10);
			sound_state->setOccluded(false);
			sound_state->setRelative(false);
			sound_state->setRolloffFactor(1);
			sound_state->setPitch(1);
			sound_state->setPlay(true);
			sound_state->setLooping(!temporary && loop);
			osgAudio::SoundManager::instance()->addSoundState(sound_state);

			//osg::ref_ptr< osgAudio::SoundUpdateCB > soundCB = new osgAudio::SoundUpdateCB();
			//soundCB->setSoundState(sound_state);
			//attachednode->AttachSound(soundCB.get());


			boost::shared_ptr<PlayingSoundHandler> res(new PlayingSoundHandler(samplepath, sound_state));
			res->Update(px, py, pz, dx, dy, dz);

			if(temporary)
			{
				CleanTmpSounds();
				_tmp_sounds.push_back(res);
				return boost::shared_ptr<PlayingSoundHandler>();
			}

			return res;
		}
	}
	catch(osgAudio::Error& ex) 
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception playing sample:") + ex.what());
	}
	catch(std::exception& ex) 
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception playing sample:") + ex.what());
	}

	return boost::shared_ptr<PlayingSoundHandler>();
}




/***********************************************************
temporary mute the sound
***********************************************************/
void MusicHandler::TemporaryMute()
{
	_savedsoundenabled = _soundEnabled;
	EnableDisableSound(false);
}

/***********************************************************
reset muted sound
***********************************************************/
void MusicHandler::ResetMute()
{
	EnableDisableSound(_savedsoundenabled);
}


/***********************************************************
update listener position and orientation
***********************************************************/
void MusicHandler::UpdateListener(float px, float py, float pz, float dx, float dy, float dz)
{
    osgAudio::SoundManager::instance()->getListener()->setPosition(px,py,pz);
	osgAudio::SoundManager::instance()->getListener()->setOrientation(dx,dy,dz,0,1,0);
}



/***********************************************************
clean temporary sounds
***********************************************************/
void MusicHandler::CleanTmpSounds()
{
	std::list<boost::shared_ptr<PlayingSoundHandler> >::iterator it = _tmp_sounds.begin();
	while(it != _tmp_sounds.end())
	{
		if((*it)->Finished())
			it = _tmp_sounds.erase(it);
		else
			++it;
	}
}

