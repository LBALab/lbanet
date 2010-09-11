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

#include <iostream>
#ifdef _WIN32
	#include <fmod.hpp>
#else
	#include <fmodex/fmod.hpp>
#endif


MusicHandler* MusicHandler::_singletonInstance = NULL;



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
: _fsystem(NULL), _fsound(NULL), _channel(NULL),
	_current_music(""), _soundEnabled(true), _counter(1)
{
	System_Create(&_fsystem);

	int volG, volM;
	ConfigurationManager::GetInstance()->GetInt("Options.Sound.GeneralVolume", volG);
	ConfigurationManager::GetInstance()->GetInt("Options.Sound.MusicVolume", volM);
	ConfigurationManager::GetInstance()->GetBool("Options.Sound.SoundEnabled", _soundEnabled);
	_generalvolume = volG/ 100.0f;
	_musicvolume = volM / 100.0f;
}


/***********************************************************
	Denstructor
***********************************************************/
MusicHandler::~MusicHandler()
{

}


/***********************************************************
 play a music a number of time
 -1 for infinit
***********************************************************/
void MusicHandler::PlayMusic(const std::string & musicPath, int nbTimes)
{
	if(_current_music == musicPath)
		return;

	StopMusic();

	FMOD_RESULT result = _fsystem->createStream(musicPath.c_str(),
							FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, NULL, &_fsound);

	if (result == FMOD_OK)
	{
		_fsound->setLoopCount(nbTimes);
		_fsystem->playSound(FMOD_CHANNEL_FREE, _fsound, false, &_channel);
		_current_music = musicPath;

		if(!_soundEnabled)
			_channel->setPaused(true);

		_channel->setVolume(_generalvolume * _musicvolume);
	}
	else
		_fsound = NULL;


}


/***********************************************************
stop the music
***********************************************************/
void MusicHandler::StopMusic()
{
	if(_channel)
		_channel->stop();

	if(_fsound)
	{
		_fsound->release();
		_fsound = NULL;
	}

	_current_music = "";
}



/***********************************************************
to be called in beginnning and end of program
***********************************************************/
bool MusicHandler::Initialize()
{
	FMOD_RESULT result = _fsystem->init(32, FMOD_INIT_NORMAL, 0);
	return (result == FMOD_OK);
}



/***********************************************************
to be called in beginnning and end of program
***********************************************************/
void MusicHandler::Unitialize()
{
	StopMusic();
	cleanupsound(true);
	_fsystem->close();
}




/***********************************************************
need to be called once per frame
***********************************************************/
void MusicHandler::Update()
{
   //result = system.set3DListenerAttributes(0, listenerPos, velocity, forward, up);
   // ERRCHECK(result);

	_fsystem->update();
}




/***********************************************************
call to enable or disable sound
***********************************************************/
void MusicHandler::EnableDisableSound()
{
	if(_soundEnabled)
		_channel->setPaused(true);
	else
		_channel->setPaused(false);

	_soundEnabled = !_soundEnabled;
	ConfigurationManager::GetInstance()->SetBool("Options.Sound.SoundEnabled", _soundEnabled);
}


/***********************************************************
set the general sound volume
***********************************************************/
void MusicHandler::SetGeneralVolume(int vol)
{
	_generalvolume = vol / 100.0f;
	_channel->setVolume(_generalvolume * _musicvolume);
}


/***********************************************************
set the music volume
***********************************************************/
void MusicHandler::SetMusicVolume(int vol)
{
	_musicvolume = vol / 100.0f;
	_channel->setVolume(_generalvolume * _musicvolume);
}



/***********************************************************
play sample - return the id of the sample played if you want to stop it
***********************************************************/
unsigned long MusicHandler::PlaySample(const std::string & samplepath, int nbTimes)
{
	cleanupsound();

	SoundInfo si;
	si.path = samplepath;

	FMOD_RESULT result = _fsystem->createSound(samplepath.c_str(),
							FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, NULL, &si.fsound);


	if (result == FMOD_OK)
	{
		si.fsound->setLoopCount(nbTimes);
		_fsystem->playSound(FMOD_CHANNEL_FREE, si.fsound, false, &si.channel);

		if(!_soundEnabled)
			si.channel->setPaused(true);

		si.channel->setVolume(_generalvolume);
		si.running = true;

		_played_sounds[_counter] = si;
		++_counter;
		return (_counter -1);
	}

	return 0;
}

/***********************************************************
stop of played sample
***********************************************************/
void MusicHandler::StopSample(unsigned long sampleid)
{
	std::map<unsigned long, SoundInfo>::iterator it = _played_sounds.find(sampleid);

	if(it !=  _played_sounds.end())
	{
		SoundInfo &si = it->second;
		if(si.channel)
		{
			si.channel->stop();
			si.channel = NULL;
		}

		if(si.fsound)
		{
			si.fsound->release();
			si.fsound = NULL;
		}

		_played_sounds.erase(it);
	}
}

/***********************************************************
clean finished sound
***********************************************************/
void MusicHandler::cleanupsound(bool forced)
{
	std::map<unsigned long, SoundInfo>::iterator it = _played_sounds.begin();
	while(it != _played_sounds.end())
	{
		SoundInfo &si = it->second;
		bool isplaying;
		si.channel->isPlaying(&isplaying);

		if(!isplaying || forced)
		{
			si.channel->stop();
			si.channel = NULL;

			if(si.fsound)
			{
				si.fsound->release();
				si.fsound = NULL;
			}

			it = _played_sounds.erase(it);
		}
		else
			++it;
	}
}
