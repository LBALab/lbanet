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

#ifndef _LBA_POINTFLAG_H__
#define _LBA_POINTFLAG_H__


#include <map>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>


//! take care of shared data between process
class PointFlag
{
public:
	//! constructor
	PointFlag(long id)
		: _Id(id), _PosX(0), _PosY(0), _PosZ(0)
	{}

	//! destructor
	~PointFlag(void){}

	//! get quest id
	long GetId()
	{return _Id;}


	//! get pos X
	float GetPosX()
	{return _PosX;}

	//! get pos Y
	float GetPosY()
	{return _PosY;}

	//! get pos Z
	float GetPosZ()
	{return _PosZ;}


	//! get pos X
	void SetPosX(float v)
	{_PosX = v;}

	//! get pos Y
	void SetPosY(float v)
	{_PosY = v;}

	//! get pos Z
	void SetPosZ(float v)
	{_PosZ = v;}


	// save trigger to lua file
	virtual void SaveToLuaFile(std::ostream & file, std::string forcedid = "");

	//! span name
	std::string GetName()
	{return _Name;}

	//! span name
	void SetName(const std::string & name)
	{_Name = name;}

private:
	long							_Id;
	std::string 					_Name;
	float 							_PosX;
	float 							_PosY;
	float 							_PosZ;
};

#endif
