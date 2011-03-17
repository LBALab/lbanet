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

#include "ItemObject.h"
#include "DynamicObject.h"
#include "PhysicalObjectHandlerBase.h"

#include <math.h>


/***********************************************************
	Constructor
***********************************************************/
ItemObject::ItemObject(boost::shared_ptr<DynamicObject> obje)
: _obje(obje)
{

}

/***********************************************************
	Destructor
***********************************************************/
ItemObject::~ItemObject()
{
}


/***********************************************************
do all check to be done when idle
***********************************************************/
void ItemObject::Process(double tnow, float tdiff)
{
	if(!_obje)
		return;

	_obje->Process(tnow, tdiff);


	boost::shared_ptr<PhysicalObjectHandlerBase> physo = _obje->GetPhysicalObject();
	if(!physo)
		return;

	float gravity = (-0.01f * tdiff); //TODO - make the gravity configurable?
	physo->Move(0, gravity, 0);
}