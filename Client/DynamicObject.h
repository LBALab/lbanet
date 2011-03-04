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
					long id)
		: _phH(phH), _disH(disH), _id(id), _additionalMoveX(0),
			_additionalMoveY(0), _additionalMoveZ(0), _additionalMoveRotation(0),
			_show(true)
	{}

	//!destructor
   virtual ~DynamicObject(){}

	//! process function - will be called at each frame
	virtual int Process(double time, float tdiff) = 0;


	//! get physical object
	boost::shared_ptr<PhysicalObjectHandlerBase> GetPhysicalObject()
	{ return _phH;}

	//! get display object
	boost::shared_ptr<DisplayObjectHandlerBase> GetDisplayObject()
	{ return _disH;}


	//! get physical object
	void SetPhysicalObject(boost::shared_ptr<PhysicalObjectHandlerBase> newP)
	{_phH = newP;}


	//! show or hide the object
	void ShowOrHide(bool Show)
	{
		_show = Show;
		_phH->ShowOrHide(Show);
		_disH->ShowOrHide(Show);
	}

	//! check if is shown
	bool IsShown()
	{ return _show;}

	//! add a signal to object
	void AddSignal(int Signal)
	{
		_signalReceived.push_back(Signal);
	}

	//! check if signal received and eat it up
	bool ReceivedSignal(int signal)
	{
		std::vector<int>::iterator it = std::find(_signalReceived.begin(), _signalReceived.end(), signal);
		if(it != _signalReceived.end())
		{
			_signalReceived.erase(it);
			return true;
		}

		return false;
	}



	std::pair<int, int> StartWaypoint(const LbaVec3 &point)
	{
		_waypoints.push_back(std::vector<LbaVec3>());

		return AddWaypoint(point);
	}


	std::pair<int, int> AddWaypoint(const LbaVec3 &point)
	{
		if(_waypoints.size() == 0)
			_waypoints.push_back(std::vector<LbaVec3>());

		int index1 = _waypoints.size()-1;

		_waypoints[index1].push_back(point);

		int index2 = _waypoints[index1].size()-1;

		return std::make_pair<int, int>(index1, index2);
	}

	std::vector<LbaVec3> GetWaypoints(int index)
	{
		if(index >= 0 && index < (int)_waypoints.size())
			return _waypoints[index];

		return std::vector<LbaVec3>();
	}

	void ClearWaypoints()
	{
		_waypoints.clear();
	}


	void SetAdditionalMoves(float mx, float my, float mz, float mr)
	{
		_additionalMoveX = mx;
		_additionalMoveY = my;
		_additionalMoveZ = mz;
		_additionalMoveRotation = mr;
	}

	void GetAdditionalMoves(float &mx, float &my, float &mz, float &mr)
	{
		mx = _additionalMoveX;
		my = _additionalMoveY;
		mz = _additionalMoveZ;
		mr = _additionalMoveRotation;
	}

protected:
	
	//! handler to physical object
	boost::shared_ptr<PhysicalObjectHandlerBase> _phH;

	//! handler to display object
	boost::shared_ptr<DisplayObjectHandlerBase> _disH;

	//! object id
	long										_id;


	std::vector<int>							_signalReceived;

	std::vector<std::vector<LbaVec3> >			_waypoints;

	float										_additionalMoveX;
	float										_additionalMoveY;
	float										_additionalMoveZ;
	float										_additionalMoveRotation;

	bool										_show;
};

#endif