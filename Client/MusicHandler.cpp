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

#include "EventsQueue.h"
#include "ClientExtendedEvents.h"

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
Play
***********************************************************/
void PlayingSoundHandler::Play()
{
	if(_soundstate)
		_soundstate->setPlay(true);
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
constructor
***********************************************************/
VoicesHandler::VoicesHandler(const std::vector<std::string> & voicePath, float Gain,
								boost::shared_ptr<VoiceEndCallbackBase>	callback,
								long actorid)
: _currentindex(0), _callback(callback), _actorid(actorid)
{
	for(size_t i=0; i< voicePath.size(); ++i)
	{
		try
		{
			// Create a new filestream that streams samples from a ogg-file.
			osgAudio::FileStream *musicStream = new osgAudio::FileStream(voicePath[i].c_str());
			if(musicStream)
			{
				// Create a named sound state.
				osgAudio::SoundState* sound_state = new osgAudio::SoundState(voicePath[i]);
				sound_state->allocateSource(10, false);
				sound_state->setStream( musicStream );
				sound_state->setGain(Gain); 
				sound_state->setAmbient(true);
				if(i==0)
					sound_state->setPlay(true);

				sound_state->setLooping(false);
				osgAudio::SoundManager::instance()->addSoundState(sound_state);

				// set the reference pointer to the music
				_voices.push_back(boost::shared_ptr<PlayingSoundHandler>(new PlayingSoundHandler(voicePath[i], sound_state)));

				if(_actorid > -2)
					EventsQueue::getReceiverQueue()->AddEvent(new ShowHideVoiceSpriteEvent(_actorid, true, true));
			}
		}
		catch(osgAudio::Error& ex) 
		{
			LogHandler::getInstance()->LogToFile(std::string("Exception playing voice:") + ex.what());
		}
		catch(std::exception& ex) 
		{
			LogHandler::getInstance()->LogToFile(std::string("Exception playing voice:") + ex.what());
		}
	}
}


/***********************************************************
destructor
***********************************************************/
VoicesHandler::~VoicesHandler()
{
	if(_actorid > -2)
		EventsQueue::getReceiverQueue()->AddEvent(new ShowHideVoiceSpriteEvent(_actorid, false, true));
}

/***********************************************************
need to be called once per frame
***********************************************************/
void VoicesHandler::Update()
{
	if(_currentindex < _voices.size())
	{
		if(_voices[_currentindex]->Finished())
		{
			++_currentindex;
			if(_currentindex < _voices.size())
				_voices[_currentindex]->Play();
			else
			{
				_voices.clear();
				if(_callback)
					_callback->VoiceFinished();

				if(_actorid > -2)
				{
					EventsQueue::getReceiverQueue()->AddEvent(new ShowHideVoiceSpriteEvent(_actorid, false, true));
					_actorid = -2;
				}
			}
		}
	}
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

#ifdef _USE_SOUND_EDITOR
	_generalvolume = 1;
	_musicvolume = 0;
	_samplevolume = 1;
#endif
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

	EnableDisableSound(_soundEnabled);

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

	if(_playing_voice)
		_playing_voice->Update();
}



/***********************************************************
call to enable or disable sound
***********************************************************/
void MusicHandler::EnableDisableSound(bool Enable)
{
#ifndef _USE_SOUND_EDITOR
	_soundEnabled = Enable;

	if(_soundEnabled)
		osgAudio::SoundManager::instance()->getEnvironment()->setGain(_generalvolume);
	else
		osgAudio::SoundManager::instance()->getEnvironment()->setGain(0);
#endif
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
#ifndef _USE_SOUND_EDITOR
	_generalvolume = vol / 100.0f;

	if(_soundEnabled)
		osgAudio::SoundManager::instance()->getEnvironment()->setGain(_generalvolume);
	else
		osgAudio::SoundManager::instance()->getEnvironment()->setGain(0);
#endif
}


/***********************************************************
set the music volume
***********************************************************/
void MusicHandler::SetMusicVolume(int vol)
{
#ifndef _USE_SOUND_EDITOR
	_musicvolume = vol / 100.0f;

	if(_playing_music)
		_playing_music->SetGain(_musicvolume);
#endif
}

/***********************************************************
set the sample volume / will not update currently playign samples
***********************************************************/
void MusicHandler::SetSampleVolume(int vol)
{
#ifndef _USE_SOUND_EDITOR
	_samplevolume = vol / 100.0f;
#endif
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
		LogHandler::getInstance()->LogToFile(std::string("Exception playing music: ") + musicPath + std::string(": ") + ex.what());
	}
	catch(std::exception& ex) 
	{
		LogHandler::getInstance()->LogToFile(std::string("Exception playing music:") + musicPath + std::string(": ") +ex.what());
	}
}



/***********************************************************
play voice
***********************************************************/
void MusicHandler::PlayVoice(const std::vector<std::string> & voicePath, long actorid,
					boost::shared_ptr<VoiceEndCallbackBase>	callback)
{
	// set voice
	if(voicePath.size() > 0)
		_playing_voice = boost::shared_ptr<VoicesHandler>
		(new VoicesHandler(voicePath, _samplevolume, callback, actorid));
	else
		_playing_voice = boost::shared_ptr<VoicesHandler>();
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
			sound_state->setReferenceDistance(8);
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


/***********************************************************
get floor sound path
***********************************************************/
std::string MusicHandler::GetFloorSoundPath(short floormaterial, int id)
{
	switch(floormaterial)
	{
		case  1: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES127.wav":"Worlds/Lba1Original/Sound/SAMPLES142.wav");
		case  2: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES131.wav":"Worlds/Lba1Original/Sound/SAMPLES146.wav");
		case  3: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES130.wav":"Worlds/Lba1Original/Sound/SAMPLES145.wav");
		case  4: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES133.wav":"Worlds/Lba1Original/Sound/SAMPLES148.wav");
		case  5: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES137.wav":"Worlds/Lba1Original/Sound/SAMPLES152.wav");
		case  6: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES129.wav":"Worlds/Lba1Original/Sound/SAMPLES144.wav");
		case  7: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES132.wav":"Worlds/Lba1Original/Sound/SAMPLES147.wav");
		case  8: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES128.wav":"Worlds/Lba1Original/Sound/SAMPLES143.wav");
		case  9: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES136.wav":"Worlds/Lba1Original/Sound/SAMPLES151.wav");
		case  10: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES130.wav":"Worlds/Lba1Original/Sound/SAMPLES145.wav");
		case  11: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES134.wav":"Worlds/Lba1Original/Sound/SAMPLES149.wav");
		case  12: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES135.wav":"Worlds/Lba1Original/Sound/SAMPLES150.wav");
		case  13: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES132.wav":"Worlds/Lba1Original/Sound/SAMPLES147.wav");
		case  14: return ((id==1)?"Worlds/Lba2Original/Sound/SAMPLES042.wav":"Worlds/Lba2Original/Sound/SAMPLES057.wav");
		case  15: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES132.wav":"Worlds/Lba1Original/Sound/SAMPLES147.wav");
		case  16: return ((id==1)?"Worlds/Lba1Original/Sound/SAMPLES138.wav":"Worlds/Lba1Original/Sound/SAMPLES153.wav");
	}

	return "";
}