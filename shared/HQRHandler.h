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

#ifndef __LBA_HQR_HAND__
#define __LBA_HQR_HAND__

#include <string>



/*
************************************************************************************************************************
*                                                 class HQRHandler
************************************************************************************************************************
*/
class HQRHandler
{
public:
	HQRHandler(const std::string & fileName);
	unsigned char *Load_HQR(int imageNumber, unsigned int &dataSize);


private:
	std::string m_fileName;

	void HQR_Expand(int decompressedSize, unsigned char *destination, unsigned char *source);
};


#endif