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

#include "StaticObject.h"
#include "LogHandler.h"


#include <sstream>

/***********************************************************
constructor
***********************************************************/
StaticObject::StaticObject(boost::shared_ptr<PhysicalObjectHandlerBase> phH,
							boost::shared_ptr<DisplayObjectHandlerBase> disH,
							long id)
	: DynamicObject(phH, disH, id)
{
	#ifdef _DEBUG
		std::stringstream strs;
		strs<<"Created new StaticObject of id "<<id;
		LogHandler::getInstance()->LogToFile(strs.str());
	#endif

	if(_phH && _disH)
	{
		float posX, posY, posZ;
		LbaQuaternion Q;

		// get value from physic object
		_phH->GetPosition(posX, posY, posZ);
		_phH->GetRotation(Q);

		// set it to display object
		_disH->SetPosition(posX, posY, posZ);
		_disH->SetRotation(Q);
	}
}

/***********************************************************
destructor
***********************************************************/
StaticObject::~StaticObject()
{
	#ifdef _DEBUG
		std::stringstream strs;
		strs<<"Destroyed new StaticObject of id "<<_id;
		LogHandler::getInstance()->LogToFile(strs.str());
	#endif
}


/***********************************************************
synchronization function - will typically be called on every frames
***********************************************************/
int StaticObject::Process(double time, float tdiff)
{
	float animX=0, animY=0, animZ=0;
	if(_disH)
	{
		animX = _disH->GetCurrentAssociatedSpeedX();
		animY = _disH->GetCurrentAssociatedSpeedY();
		animZ = _disH->GetCurrentAssociatedSpeedZ();
	}

	if(_phH)
	{
		_phH->ResetMove();
		_phH->Process(time, tdiff, animX, animY, animZ);
	}

	if(_disH)
		return _disH->Process(time, tdiff);

	return 0;
}
