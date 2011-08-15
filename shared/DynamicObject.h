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

#if !defined(__LbaNetModel_1_DynamicObject_h)
#define __LbaNetModel_1_DynamicObject_h


#include "PhysicalObjectHandlerBase.h"
#include "DisplayObjectHandlerBase.h"
#include "SoundObjectHandlerBase.h"
#include "ActionOnAnimationHandlerBase.h"

#include <boost/shared_ptr.hpp>


/***********************************************************************
 * Module:  DynamicObject.h
 * Author:  vivien
 * Modified: mardi 14 juillet 2009 17:41:03
 * Purpose: Base class for any object needed update at each frame
 ***********************************************************************/
class DynamicObject
{
public:
	//!constructor
	DynamicObject(boost::shared_ptr<PhysicalObjectHandlerBase> phH,
					boost::shared_ptr<DisplayObjectHandlerBase> disH,
					boost::shared_ptr<SoundObjectHandlerBase> soundH,
					long id);

	//!destructor
   virtual ~DynamicObject(){}

	//! process function - will be called at each frame
	virtual int Process(double time, float tdiff) = 0;

	//! sync display and physic
	virtual void Synchronize(){}

	long GetId()
	{ return _id; }


	//! get physical object
	boost::shared_ptr<PhysicalObjectHandlerBase> GetPhysicalObject()
	{ return _phH;}

	//! get display object
	boost::shared_ptr<DisplayObjectHandlerBase> GetDisplayObject()
	{ return _disH;}

	//! get sound object
	boost::shared_ptr<SoundObjectHandlerBase> GetSoundObject()
	{ return _soundH;}


	//! get physical object
	void SetPhysicalObject(boost::shared_ptr<PhysicalObjectHandlerBase> newP)
	{_phH = newP;}


	//! show or hide the object
	void ShowOrHide(bool Show);

	//! check if is shown
	bool IsShown();

	//! clear old signals
	void ClearSignals();

	//! add a signal to object
	void AddSignal(int Signal);

	//! check if signal received and eat it up
	bool ReceivedSignal(int signal);


	std::pair<int, int> StartWaypoint(const LbaVec3 &point);


	std::pair<int, int> AddWaypoint(const LbaVec3 &point);

	std::vector<LbaVec3> GetWaypoints(int index);

	void ClearWaypoints();


	void SetAdditionalMoves(float mx, float my, float mz, float mr);

	void GetAdditionalMoves(float &mx, float &my, float &mz, float &mr);



	//! add action to be executed on key frame
	void AddActionOnAnimation(int executionkeyframe, ActionOnAnimationHandlerBase* action);
	void RemoveActionOnAnimation(int executionkeyframe, ActionOnAnimationHandlerBase* action);
	void ClearActionsOnAnimation();


	//! update sound with position
	void UpdateSoundPosition();

protected:
	//verify actions
	void VerifyActionOnAnim();



	
	//! handler to physical object
	boost::shared_ptr<PhysicalObjectHandlerBase> _phH;

	//! handler to display object
	boost::shared_ptr<DisplayObjectHandlerBase> _disH;

	//! handler to sound object
	boost::shared_ptr<SoundObjectHandlerBase>	_soundH;

	

	//! object id
	long										_id;


	std::vector<int>							_signalReceived;

	std::vector<std::vector<LbaVec3> >			_waypoints;

	float										_additionalMoveX;
	float										_additionalMoveY;
	float										_additionalMoveZ;
	float										_additionalMoveRotation;

	bool										_show;


	std::vector<std::pair<int, ActionOnAnimationHandlerBase* > >	_actionsonanimation;
	int																_lastkey;

};

#endif