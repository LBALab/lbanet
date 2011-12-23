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

#ifndef _LBANET_MUSIC_HANDLER_H_
#define _LBANET_MUSIC_HANDLER_H_

#include <string>
#include <map>
#include <list>
#include <boost/shared_ptr.hpp>

#include "DisplayObjectHandlerBase.h"


namespace osgAudio
{
	class SoundState;
}


//*************************************************************************************************
//*                               class PlayingSoundHandler
//*************************************************************************************************
/**
* @brief Class keeping track of a plyaing sound
*
*/
class PlayingSoundHandler
{
public:
	// constructor
	PlayingSoundHandler(const std::string & filename, 
							osgAudio::SoundState* sound);

	// destructor
	~PlayingSoundHandler();

	//Play
	void Play();

	//pause playing
	void Pause();

	//resume playing
	void Resume();

	//set soudn gain (from 0.0 to 1.0)
	void SetGain(float gain);

	//set sound loop
	void SetLoop(bool loop);

	// check if paused
	bool Paused();

	// check if sound is looping
	bool IsLooping();


	// return music filename
	std::string GetFilename()
	{ return _filename;}

	// return true if finished playing
	bool Finished();

	// update sound position and direction
	void Update(float px, float py, float pz, float dx, float dy, float dz);

private:
	std::string					_filename;
	osgAudio::SoundState*		_soundstate;
	bool						_paused;

};


//*************************************************************************************************
//*                               class VoicesHandler
//*************************************************************************************************
/**
* @brief Class keeping track of a plyaing voices
*
*/
class VoicesHandler
{
public:
	// constructor
	VoicesHandler(const std::vector<std::string> & voicePath, float Gain);

	// need to be called once per frame
	void Update();

private:
	std::vector<boost::shared_ptr<PlayingSoundHandler> >		_voices;
	size_t														_currentindex;
};



//*************************************************************************************************
//*                               class MusicHandler
//*************************************************************************************************
/**
* @brief Class taking care of the music
*
*/
class MusicHandler
{
public:

	// destructor
	~MusicHandler();

	// singleton pattern
	static MusicHandler * getInstance();


	// to be called in beginnning and end of program
	void Initialize();
	void Unitialize();

	// need to be called once per frame
	void Update();


	// call to enable or disable sound
	void EnableDisableSound();

	// return tru if the sound is enabled
	bool IsSoundEnabled()
	{return _soundEnabled;}

	//! set the general sound volume
	void SetGeneralVolume(int vol);

	//! set the music volume
	void SetMusicVolume(int vol);

	//! set the sample volume / will not update currently playign samples
	void SetSampleVolume(int vol);



	// play a music (looping or not)
	void PlayMusic(const std::string & musicPath, bool loop);

	// stop the currently played music
	void StopMusic();

	// music accessor
	std::string GetCurrentMusic();


	//play 2D sample
	boost::shared_ptr<PlayingSoundHandler> PlaySample2D(const std::string & samplepath, bool loop,
															bool temporary);

	//play 3D sample
	boost::shared_ptr<PlayingSoundHandler> PlaySample3D(const std::string & samplepath, bool loop, 
															bool temporary,
															float px, float py, float pz, float dx, float dy, float dz);



	// play voice
	void PlayVoice(const std::vector<std::string> & voicePath);


	// temporary mute the sound
	void TemporaryMute();

	// rest muted sound
	void ResetMute();

	// update listener position and orientation
	void UpdateListener(float px, float py, float pz, float dx, float dy, float dz);


protected:

	// constructor
	MusicHandler();

	//! Enable/disable sounde
	void EnableDisableSound(bool Enable);

	//! clean temporary sounds
	void CleanTmpSounds();


private:

	static MusicHandler *									_singletonInstance;

	bool													_soundEnabled;
	float													_generalvolume;
	float													_musicvolume;
	float													_samplevolume;


	boost::shared_ptr<PlayingSoundHandler>					_playing_music;
	std::list<boost::shared_ptr<PlayingSoundHandler> >		_tmp_sounds;
	boost::shared_ptr<VoicesHandler>						_playing_voice;


	unsigned long											_counter;

	bool													_savedsoundenabled;
};


#endif
