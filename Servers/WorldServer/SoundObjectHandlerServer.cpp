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

#include "SoundObjectHandlerServer.h"

/***********************************************************
constructor
***********************************************************/
SoundObjectHandlerServer::SoundObjectHandlerServer()
{
	for(int i=0; i<5; ++i)
	{
		LbaNet::PlayingSound si;
		si.SoundChannel = i;
		m_playingsound.push_back(si);
	}
}


/***********************************************************
make actor play a sound
***********************************************************/
void SoundObjectHandlerServer::APlaySound(int SoundChannel, const std::string & soundpath, int numberTime, bool randomPitch)
{
	if(numberTime != 1 && SoundChannel >= 0 && SoundChannel < 5)
	{
		LbaNet::PlayingSound si;
		si.SoundChannel = SoundChannel;
		si.SoundPath = soundpath;
		si.Paused = false;
		si.NbTime = numberTime;
		si.RandomPitch = randomPitch;
		m_playingsound[SoundChannel] = si;
	}
}

/***********************************************************
make actor stop a sound
***********************************************************/
void SoundObjectHandlerServer::AStopSound(int SoundChannel)
{
	if(SoundChannel >= 0 && SoundChannel < 5)
		m_playingsound[SoundChannel].SoundPath = "";
}

/***********************************************************
make actor pause a sound
***********************************************************/
void SoundObjectHandlerServer::APauseSound(int SoundChannel)
{
	if(SoundChannel >= 0 && SoundChannel < 5)
		m_playingsound[SoundChannel].Paused = true;
}

/***********************************************************
make actor resume a sound
***********************************************************/
void SoundObjectHandlerServer::AResumeSound(int SoundChannel)
{
	if(SoundChannel >= 0 && SoundChannel < 5)
		m_playingsound[SoundChannel].Paused = false;
}







/***********************************************************
get sound vector
***********************************************************/
LbaNet::PlayingSoundSequence SoundObjectHandlerServer::GetSoundVector(bool storedstate)
{
	if(storedstate)
		return m_savedsound;
	else
		return m_playingsound;
}


/***********************************************************
get sound
***********************************************************/
LbaNet::PlayingSound SoundObjectHandlerServer::GetSound(int SoundChannel, bool storedstate)
{
	if(SoundChannel >= 0 && SoundChannel < 5)
	{
		if(storedstate)
			return m_savedsound[SoundChannel];
		else
			return m_playingsound[SoundChannel];
	}
	else
	{
		LbaNet::PlayingSound res;
		res.SoundChannel = -1;
		return res;
	}
}


/***********************************************************
set sound vector
***********************************************************/
void SoundObjectHandlerServer::SetSoundVector(const LbaNet::PlayingSoundSequence & vec,
												bool updatestoredstate)
{
	if(updatestoredstate)
		m_savedsound = vec;
	else
		m_playingsound = vec;
}


/***********************************************************
set sound
***********************************************************/
void SoundObjectHandlerServer::SetSound(const LbaNet::PlayingSound & vec,
												bool updatestoredstate)
{
	if(vec.SoundChannel >= 0 && vec.SoundChannel < 5)
		if(updatestoredstate)
			m_savedsound[vec.SoundChannel] = vec;
		else
			m_playingsound[vec.SoundChannel] = vec;
}



/***********************************************************
//! update sound
//! the return value depends of the derived class type
***********************************************************/
void SoundObjectHandlerServer::Update(LbaNet::SoundObjectUpdateBasePtr update,
										bool updatestoredstate)
{
	const std::type_info& info = typeid(*update);

	// PlaySoundUpdate
	if(info == typeid(LbaNet::PlaySoundUpd))
	{
		LbaNet::PlaySoundUpd * castedptr = 
			dynamic_cast<LbaNet::PlaySoundUpd *>(update.get());

		SetSound(castedptr->Si, updatestoredstate);	
	}

	// PlaySoundUpdate seq
	if(info == typeid(LbaNet::PlaySoundSeqUpd))
	{
		LbaNet::PlaySoundSeqUpd * castedptr = 
			dynamic_cast<LbaNet::PlaySoundSeqUpd *>(update.get());

		SetSoundVector(castedptr->Sis, updatestoredstate);	
	}
}


/***********************************************************
save current model state
***********************************************************/
void SoundObjectHandlerServer::SaveState()
{
	m_savedsound = m_playingsound;
}


/***********************************************************
restore previously saved model state
***********************************************************/
void SoundObjectHandlerServer::RestoreState()
{
	m_playingsound = m_savedsound;
}
