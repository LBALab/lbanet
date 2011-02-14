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

#ifndef _DOOR_HANDLER_H__
#define _DOOR_HANDLER_H__

#include "ActorHandler.h"

/***********************************************************************
class taking care of the maping between lua and the server interfaces
 ***********************************************************************/
class DoorHandler : public ActorHandler
{
public:
	
// cant use enum for lua
//otype:
//	0- translation
//  1- rotation

//odirection:
//	0- right
//  1- left
//	2- top
//  3- bottom


public:
	//! constructor
	DoorHandler(const ActorObjectInfo & actorinfo, int otype, 
					int odirection, float openingvalue, float openingspeed,
					bool Refreshscript);
	
	//! destructor
	virtual ~DoorHandler(void){}

	//! catch opening-closing signals
	virtual void SendSignal(int Signalnumber);

	//! return actor type
	virtual std::string ActorType()
	{ return "Door";}


	//! return opening type
	std::string GetOpeningType();

	//! return opening direction
	std::string GetOpeningDirection();

	//! accessor
	float GetOpeningValue()
	{return _openingvalue;}

	//! accessor
	float GetOpeningSpeed()
	{return _openingspeed;}


	//! return opening type
	void SetOpeningType(const std::string & type);

	//! return opening direction
	void SetOpeningDirection(const std::string & direction);

	//! accessor
	void SetOpeningValue(float value);

	//! accessor
	void SetOpeningSpeed(float value);



protected:
	//! refresh door script
	void RefreshScript();

	//! return the build class
	virtual std::string LuaBuildClass();

private:
	int				_openingcounter;

	int				_otype; 
	int				_odirection; 
	float			_openingvalue;
	float			_openingspeed;
};

#endif
