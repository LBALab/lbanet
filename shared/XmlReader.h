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


#ifndef __LBA_NET_XML_READER_H__
#define __LBA_NET_XML_READER_H__


#include <LbaTypes.h>

using namespace LbaNet;

//*************************************************************************************************
//*                                      class XmlReader
//*************************************************************************************************

class XmlReader
{
public:
	// load a world information into memory
	static  bool LoadWorldInfo(const std::string &Filename, WorldInformation &res);

	// load a world description into memory
	static  bool LoadWorldDesc(const std::string &Filename, WorldDesc &res);
};


#endif
