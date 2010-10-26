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

#if !defined(__SCRIPTED_ACTOR_h)
#define __SCRIPTED_ACTOR_h

#include <boost/shared_ptr.hpp>

class DynamicObject;




/***********************************************************************
 * Module:  ScriptedActor.h
 * Author:  vivien
 * Purpose: Declaration of the class ScriptedActor
 ***********************************************************************/
class ScriptedActor
{
public:
	//! constructor
	ScriptedActor();

	//! destructor
	virtual ~ScriptedActor();

	//! process function
	void ProcessScript(double tnow, float tdiff);


protected:
	boost::shared_ptr<DynamicObject>			_character;
};

#endif