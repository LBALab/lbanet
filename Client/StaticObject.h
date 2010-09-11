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


#ifndef _LBANET_STATIC_OBJECT__H_
#define _LBANET_STATIC_OBJECT__H_

#include <boost/shared_ptr.hpp>

#include "DynamicObject.h"
#include "CommonTypes.h"

//*************************************************************************************************
//*                               class WorldToDisplayObjectSynchronizer
//*************************************************************************************************
/**
* @brief Static object will never synchronize - use it in case of static object
*			or if you have an object with no display
*
*
*/
class StaticObject : public DynamicObject
{
public:

	//! constructor
	StaticObject(boost::shared_ptr<PhysicalObjectHandlerBase> phH,
								boost::shared_ptr<DisplayObjectHandlerBase> disH,
								long id);

	//! destructor
	virtual ~StaticObject();


	//! synchronization function - will typically be called on every frames
	virtual void Process(void){}

};


#endif
