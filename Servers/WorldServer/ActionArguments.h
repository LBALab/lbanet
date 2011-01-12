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

#ifndef _LBANET_ACTION_ARGS_H__
#define _LBANET_ACTION_ARGS_H__



//! base class used as action argument
class ActionArgumentBase
{
public:
	//! constructor
	ActionArgumentBase(){}
	
	//! destructor
	virtual ~ActionArgumentBase(void){}
};




//! base class used as action argument
class OffsetArgument : public ActionArgumentBase
{
public:
	//! constructor
	OffsetArgument()
		: _offsetX(0), _offsetY(0), _offsetZ(0)
	{}

	//! constructor
	OffsetArgument(float offsetX, float offsetY, float offsetZ)
		: _offsetX(offsetX), _offsetY(offsetY), _offsetZ(offsetZ)
	{}

	//! destructor
	virtual ~OffsetArgument(void){}


	float _offsetX;
	float _offsetY;
	float _offsetZ;
};



#endif
