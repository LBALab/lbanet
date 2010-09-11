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

namespace FMOD
{
	class System;
	class Sound;
	class Channel;
}

struct SoundInfo
{
	std::string path;
	FMOD::Sound * fsound;
	FMOD::Channel* channel;
	bool running;
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

	// constructor
	MusicHandler();

	// destructor
	~MusicHandler();

	// play a music a number of time
	// -1 for infinit
	void PlayMusic(const std::string & musicPath, int nbTimes);


	// stop the currently played music
	void StopMusic();


	// music accessor
	const std::string & GetCurrentMusic()
	{return _current_music;}


	// to be called in beginnning and end of program
	bool Initialize();
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

	// singleton pattern
   static MusicHandler * getInstance();

	//play sample - return the id of the sample played if you want to stop it
   unsigned long PlaySample(const std::string & samplepath, int nbTimes);

	//stop of played sample
	void StopSample(unsigned long sampleid);

protected:
	//! clean finished sound
	void cleanupsound(bool forced = false);

private:

	static MusicHandler *		_singletonInstance;

	FMOD::System *				_fsystem;
	FMOD::Sound *				_fsound;
	FMOD::Channel*				_channel;
	bool						_soundEnabled;

	std::string					_current_music;

	std::map<unsigned long, SoundInfo>	_played_sounds;


	float						_generalvolume;
	float						_musicvolume;

	unsigned long				_counter;
};


#endif
