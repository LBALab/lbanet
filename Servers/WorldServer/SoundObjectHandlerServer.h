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


#ifndef _LBANET_SOUND_OBJECT_HANDLER_SERVER_H_
#define _LBANET_SOUND_OBJECT_HANDLER_SERVER_H_

#include "SoundObjectHandlerBase.h"
#include <boost/shared_ptr.hpp>

//*************************************************************************************************
//*                               class SoundObjectHandlerServer
//*************************************************************************************************
/**
* @brief Pure virtual class for handling 3D sound on an object
*
*/
class SoundObjectHandlerServer : public SoundObjectHandlerBase
{
public:

	//! constructor
	SoundObjectHandlerServer();

	//! destructor
	virtual ~SoundObjectHandlerServer(){}

	// update sound position and direction
	virtual void Update(float px, float py, float pz, float dx, float dy, float dz){}


	//! make actor play a sound
	virtual void APlaySound(int SoundChannel, const std::string & soundpath, bool loop);

	//! make actor stop a sound
	virtual void AStopSound(int SoundChannel);

	//! mZake actor pause a sound
	virtual void APauseSound(int SoundChannel);

	//! make actor resume a sound
	virtual void AResumeSound(int SoundChannel);

	//! get sound vector
	virtual LbaNet::PlayingSoundSequence GetSoundVector(bool storedstate);

	//! get sound
	virtual LbaNet::PlayingSound GetSound(int SoundChannel, bool storedstate);

	//! set sound vector
	virtual void SetSoundVector(const LbaNet::PlayingSoundSequence & vec,
								bool updatestoredstate);

	//! set sound
	virtual void SetSound(const LbaNet::PlayingSound & vec,
									bool updatestoredstate);


	//! update sound
	//! the return value depends of the derived class type
	virtual void Update(LbaNet::SoundObjectUpdateBasePtr update,
							bool updatestoredstate);

	// save current model state
	virtual void SaveState();

	// restore previously saved model state
	virtual void RestoreState();



protected:
	std::vector<LbaNet::PlayingSound>					m_playingsound;
	std::vector<LbaNet::PlayingSound>					m_savedsound;
};




#endif
