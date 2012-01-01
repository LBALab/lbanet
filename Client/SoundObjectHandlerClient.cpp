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

#include "SoundObjectHandlerClient.h"
#include "MusicHandler.h"
#include "DynamicObject.h"



/***********************************************************
update sound position and direction
***********************************************************/
void SoundObjectHandlerClient::Update(float px, float py, float pz, float dx, float dy, float dz)
{
	for(int i=0; i<5; ++i)
	{
		boost::shared_ptr<PlayingSoundHandler> tmpS = _sounds[i];
		if(tmpS && !tmpS->Finished())
			tmpS->Update(px, py, pz, dx, dy, dz);
	}
}



/***********************************************************
make actor play a sound
***********************************************************/
void SoundObjectHandlerClient::APlaySound(int SoundChannel, const std::string & soundpath, bool loop)
{
	APlaySound(_sounds, SoundChannel, soundpath, loop);
}

/***********************************************************
make actor stop a sound
***********************************************************/
void SoundObjectHandlerClient::AStopSound(int SoundChannel)
{
	AStopSound(_sounds, SoundChannel);
}

/***********************************************************
make actor pause a sound
***********************************************************/
void SoundObjectHandlerClient::APauseSound(int SoundChannel)
{
	APauseSound(_sounds, SoundChannel);
}

/***********************************************************
make actor resume a sound
***********************************************************/
void SoundObjectHandlerClient::AResumeSound(int SoundChannel)
{
	AResumeSound(_sounds, SoundChannel);
}






/***********************************************************
make actor play a sound
***********************************************************/
void SoundObjectHandlerClient::APlaySound(boost::shared_ptr<PlayingSoundHandler> * buffer,
										  int SoundChannel, const std::string & soundpath, bool loop)
{
	if(SoundChannel >= 0 && SoundChannel < 5)
	{
		float posX=0, posY=0, posZ=0;

		//get actor starting position
		if(_parent)
		{
			boost::shared_ptr<PhysicalObjectHandlerBase> _phH = _parent->GetPhysicalObject();
			if(_phH)
				_phH->GetPosition(posX, posY, posZ);
		}


		buffer[SoundChannel] = MusicHandler::getInstance()->PlaySample3D(soundpath, loop, false, posX, posY, posZ, 0, 1, 0);
	}
}

/***********************************************************
make actor stop a sound
***********************************************************/
void SoundObjectHandlerClient::AStopSound(boost::shared_ptr<PlayingSoundHandler> * buffer,int SoundChannel)
{
	if(SoundChannel >= 0 && SoundChannel < 5)
		buffer[SoundChannel] = boost::shared_ptr<PlayingSoundHandler>();
}

/***********************************************************
make actor pause a sound
***********************************************************/
void SoundObjectHandlerClient::APauseSound(boost::shared_ptr<PlayingSoundHandler> * buffer,int SoundChannel)
{
	if(SoundChannel >= 0 && SoundChannel < 5)
	{
		if(buffer[SoundChannel])
			buffer[SoundChannel]->Pause();
	}
}

/***********************************************************
make actor resume a sound
***********************************************************/
void SoundObjectHandlerClient::AResumeSound(boost::shared_ptr<PlayingSoundHandler> * buffer,int SoundChannel)
{
	if(SoundChannel >= 0 && SoundChannel < 5)
	{
		if(buffer[SoundChannel])
			buffer[SoundChannel]->Resume();
	}
}












/***********************************************************
get sound vector
***********************************************************/
LbaNet::PlayingSoundSequence SoundObjectHandlerClient::GetSoundVector(bool storedstate)
{
	boost::shared_ptr<PlayingSoundHandler> * ptrsounds = _sounds;
	if(storedstate)
		ptrsounds = _storedsounds;

	LbaNet::PlayingSoundSequence res;
	for(int i=0; i<5; ++i)
	{
		boost::shared_ptr<PlayingSoundHandler> tmpS = ptrsounds[i];
		LbaNet::PlayingSound toadd;
		toadd.SoundChannel = i;

		if(tmpS)
		{
			if(tmpS->IsLooping())
			{
				toadd.SoundPath = tmpS->GetFilename();
				toadd.Paused = tmpS->Paused();
			}
		}

		res.push_back(toadd);
	}

	return res;
}

/***********************************************************
get sound
***********************************************************/
LbaNet::PlayingSound SoundObjectHandlerClient::GetSound(int SoundChannel, bool storedstate)
{
	boost::shared_ptr<PlayingSoundHandler> * ptrsounds = _sounds;
	if(storedstate)
		ptrsounds = _storedsounds;

	if(SoundChannel >= 0 && SoundChannel < 5)
	{
		boost::shared_ptr<PlayingSoundHandler> tmpS = ptrsounds[SoundChannel];
		LbaNet::PlayingSound res;
		res.SoundChannel = SoundChannel;

		if(tmpS)
		{
			if(tmpS->IsLooping())
			{
				res.SoundPath = tmpS->GetFilename();
				res.Paused = tmpS->Paused();
			}
		}
		return res;
	}

	LbaNet::PlayingSound res;
	res.SoundChannel = -1;
	return res;
}


/***********************************************************
set sound vector
***********************************************************/
void SoundObjectHandlerClient::SetSoundVector(const LbaNet::PlayingSoundSequence & vec,
												bool updatestoredstate)
{
	for(size_t i=0; i< vec.size(); ++i)
		SetSound(vec[i], updatestoredstate);
}


/***********************************************************
set sound
***********************************************************/
void SoundObjectHandlerClient::SetSound(const LbaNet::PlayingSound & vec,
												bool updatestoredstate)
{
	boost::shared_ptr<PlayingSoundHandler> * ptrsounds = _sounds;
	if(updatestoredstate)
		ptrsounds = _storedsounds;

	if(vec.SoundChannel >= 0 && vec.SoundChannel < 5)
	{
		if(vec.SoundPath == "")		
		{
			AStopSound(_sounds, vec.SoundChannel);
		}
		else
		{
			boost::shared_ptr<PlayingSoundHandler> toupdate = ptrsounds[vec.SoundChannel];
			if(!toupdate || toupdate->GetFilename() != vec.SoundPath)
				APlaySound(ptrsounds, vec.SoundChannel, vec.SoundPath, vec.Loop);

			if(updatestoredstate)
				APauseSound(ptrsounds, vec.SoundChannel);
		}

		if(updatestoredstate)
		{
			_storedplaying[vec.SoundChannel] = !vec.Paused;
		}
		else
		{
			if(vec.Paused)
				APauseSound(ptrsounds, vec.SoundChannel);
			else
				AResumeSound(ptrsounds, vec.SoundChannel);
		}
	}
}



/***********************************************************
//! update sound
//! the return value depends of the derived class type
***********************************************************/
void SoundObjectHandlerClient::Update(LbaNet::SoundObjectUpdateBasePtr update,
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
void SoundObjectHandlerClient::SaveState()
{
	for(int i=0; i<5; ++i)
	{
		if(_sounds[i])
			_storedplaying[i] = !_sounds[i]->Paused();
		else
			_storedplaying[i] = false;

		APauseSound(i);
		_storedsounds[i] = _sounds[i];
		_sounds[i] = boost::shared_ptr<PlayingSoundHandler>();
	}
}


/***********************************************************
restore previously saved model state
***********************************************************/
void SoundObjectHandlerClient::RestoreState()
{
	for(int i=0; i<5; ++i)
	{
		_sounds[i] = _storedsounds[i];
		_storedplaying[i] = boost::shared_ptr<PlayingSoundHandler>();

		if(_storedplaying[i])
			AResumeSound(i);
	}
}
