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

#include "DynamicObject.h"


//!constructor
DynamicObject::DynamicObject(boost::shared_ptr<PhysicalObjectHandlerBase> phH,
				boost::shared_ptr<DisplayObjectHandlerBase> disH,
				boost::shared_ptr<SoundObjectHandlerBase> soundH,
				long id)
	: _phH(phH), _disH(disH), _id(id), _additionalMoveX(0),
		_additionalMoveY(0), _additionalMoveZ(0), _additionalMoveRotation(0),
		_show(true), _lastkey(-1), _soundH(soundH)
{
	if(disH)
		disH->SetParent(this);

	if(soundH)
		soundH->SetParent(this);
}



//! show or hide the object
void DynamicObject::ShowOrHide(bool Show)
{
	_show = Show;
	_phH->ShowOrHide(Show);
	_disH->ShowOrHide(Show);
}

//! check if is shown
bool DynamicObject::IsShown()
{ 
	return _show;
}

//! clear old signals
void DynamicObject::ClearSignals()
{
	_signalReceived.clear();
}

//! add a signal to object
void DynamicObject::AddSignal(int Signal)
{
	_signalReceived.push_back(Signal);
}

//! check if signal received and eat it up
bool DynamicObject::ReceivedSignal(int signal)
{
	std::vector<int>::iterator it = std::find(_signalReceived.begin(), _signalReceived.end(), signal);
	if(it != _signalReceived.end())
	{
		_signalReceived.erase(it);
		return true;
	}

	return false;
}



std::pair<int, int> DynamicObject::StartWaypoint(const LbaVec3 &point)
{
	_waypoints.push_back(std::vector<LbaVec3>());

	return AddWaypoint(point);
}


std::pair<int, int> DynamicObject::AddWaypoint(const LbaVec3 &point)
{
	if(_waypoints.size() == 0)
		_waypoints.push_back(std::vector<LbaVec3>());

	int index1 = _waypoints.size()-1;

	_waypoints[index1].push_back(point);

	int index2 = _waypoints[index1].size()-1;

	return std::make_pair<int, int>(index1, index2);
}

std::vector<LbaVec3> DynamicObject::GetWaypoints(int index)
{
	if(index >= 0 && index < (int)_waypoints.size())
		return _waypoints[index];

	return std::vector<LbaVec3>();
}

void DynamicObject::ClearWaypoints()
{
	_waypoints.clear();
}


void DynamicObject::SetAdditionalMoves(float mx, float my, float mz, float mr)
{
	_additionalMoveX = mx;
	_additionalMoveY = my;
	_additionalMoveZ = mz;
	_additionalMoveRotation = mr;
}

void DynamicObject::GetAdditionalMoves(float &mx, float &my, float &mz, float &mr)
{
	mx = _additionalMoveX;
	my = _additionalMoveY;
	mz = _additionalMoveZ;
	mr = _additionalMoveRotation;
}


//! add action to be executed on key frame
void DynamicObject::AddActionOnAnimation(int executionkeyframe, ActionOnAnimationHandlerBase* action)
{
	_actionsonanimation.push_back(std::make_pair<int, ActionOnAnimationHandlerBase* >(executionkeyframe, action));
}

void DynamicObject::RemoveActionOnAnimation(int executionkeyframe, ActionOnAnimationHandlerBase* action)
{
	std::pair<int, ActionOnAnimationHandlerBase* > searcho(executionkeyframe, action);
	std::vector<std::pair<int, ActionOnAnimationHandlerBase* > >::iterator it =
		std::find(_actionsonanimation.begin(), _actionsonanimation.end(), searcho);

	if(it != _actionsonanimation.end())
	{
		if(it->second)
			it->second->Destroy();

		_actionsonanimation.erase(it);
	}
}

void DynamicObject::ClearActionsOnAnimation()
{
	std::vector<std::pair<int, ActionOnAnimationHandlerBase* > > actionsonanimationtmp;
	actionsonanimationtmp.swap(_actionsonanimation);

	for(size_t i=0; i< actionsonanimationtmp.size(); ++i)
	{
		ActionOnAnimationHandlerBase* tmp = actionsonanimationtmp[i].second;
		if(tmp)
			tmp->Destroy();	
	}
}




//verify actions
void DynamicObject::VerifyActionOnAnim()
{
	if(_actionsonanimation.size() > 0)
	{
		if(_disH)
		{
			int currkey = _disH->GetCurrentKeyFrame();
			if(_lastkey != currkey)
			{
				std::vector<std::pair<int, ActionOnAnimationHandlerBase* > >::iterator it = _actionsonanimation.begin();
				while(it != _actionsonanimation.end())
				{
					if(currkey == it->first)
					{
						if(it->second->Execute())
							it = _actionsonanimation.erase(it);
						else
							++it;
					}
					else
						++it;
				}

				_lastkey = currkey;
			}
		}
	}
}



//! update sound with position
void DynamicObject::UpdateSoundPosition()
{
	if(_phH && _soundH)
	{
		float posX, posY, posZ;
		LbaQuaternion Quat;
		_phH->GetPosition(posX, posY, posZ);
		_phH->GetRotation(Quat);

		LbaVec3 ldX(Quat.GetDirection(LbaVec3(0, 0, 1)));
		_soundH->Update(posX, posY, posZ, ldX.x, ldX.y, ldX.z);
	}
}