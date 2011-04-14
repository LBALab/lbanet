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


#ifndef _LBANET_ACT_ANIM_HANDLER_BASE_H_
#define _LBANET_ACT_ANIM_HANDLER_BASE_H_



//*************************************************************************************************
//*                               class ActionOnAnimationHandlerBase
//*************************************************************************************************
/**
* @brief Base class for executing action when animation finish
*
*/
class ActionOnAnimationHandlerBase
{
public:

	//! constructor
	ActionOnAnimationHandlerBase(){}


	//! destructor
	virtual ~ActionOnAnimationHandlerBase(){}

	// execute the action
	virtual void Execute() = 0;

};


#endif
