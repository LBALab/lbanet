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
		: _phH(phH), _disH(disH), _id(id)
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

	//! show or hide the object
	void ShowOrHide(bool Show)
	{
		_phH->ShowOrHide(Show);
		_disH->ShowOrHide(Show);
	}

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

protected:
	
	//! handler to physical object
	boost::shared_ptr<PhysicalObjectHandlerBase> _phH;

	//! handler to display object
	boost::shared_ptr<DisplayObjectHandlerBase> _disH;

	//! object id
	long										_id;


	std::vector<int>							_signalReceived;
};

#endif