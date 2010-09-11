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


#ifndef __LBA_NET_SERIALIZER_BASE_H__
#define __LBA_NET_SERIALIZER_BASE_H__

#include <string>

/***********************************************************************
Base class for serialization component
 ***********************************************************************/
class SerializerBase
{
public:
	//! constructor
	SerializerBase()
	{}

	//! destructor
	virtual ~SerializerBase(){}


	// function using to build tree structures
	virtual void startChildObjectList(const std::string &name) = 0;
	virtual void nextChildObject(const std::string &name) = 0;
	virtual void finishChildObjectList(const std::string &name) = 0;


	// data will be stored as a bool on 1bit
	virtual void addBool(bool data, const std::string &id) = 0;
	virtual void getBool(const std::string &id, bool & res) = 0;

	// data will be stored as a unsigned short using 8bits
	virtual void addUShort(unsigned short data, const std::string &id) = 0;
	virtual void getUShort(const std::string &id, unsigned short & res) = 0;

	// data will be stored as a unsigned int using 16bits
	virtual void addUInt(unsigned int data, const std::string &id) = 0;
	virtual void getUInt(const std::string &id, unsigned int & res) = 0;

	// data will be stored as a unsigned long using 32bits
	virtual void addULong(unsigned long data, const std::string &id) = 0;
	virtual void getULong(const std::string &id, unsigned long & res) = 0;


	// data will be stored as a signed short using 8bits
	virtual void addShort(short data, const std::string &id) = 0;
	virtual void getShort(const std::string &id, short & res) = 0;

	// data will be stored as a signed int using 16bits
	virtual void addInt(int data, const std::string &id) = 0;
	virtual void getInt(const std::string &id, int & res) = 0;

	// data will be stored as a signed long using 32bits
	virtual void addLong(long data, const std::string &id) = 0;
	virtual void getLong(const std::string &id, long & res) = 0;

	// data will be stored as a float using 32bits
	virtual void addFloat(float data, const std::string &id) = 0;
	virtual void getFloat(const std::string &id, float & res) = 0;

	// data will be stored as a string of dynamic dimension
	// however the size of the string should not be larger than 250 characters
	virtual void addString(const std::string &data, const std::string &id) = 0;
	virtual void getString(const std::string &id, std::string & res) = 0;

};

#endif
