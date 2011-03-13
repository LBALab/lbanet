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


#ifndef _LBANET_IMAGESET_HANDLER_H_
#define _LBANET_IMAGESET_HANDLER_H_


#include <string>

//*************************************************************************************************
//*                               class ImageSetHandler
//*************************************************************************************************
/**
* @brief Class handling imageset for the gui
*
*/
class ImageSetHandler
{
public:

	// get inventory image
	static std::string GetInventoryImage(std::string file);

	// get inventory image
	static std::string GetInventoryMiniImage(std::string file);

	// get image of stance
	static std::string GetStanceImage(int stance);

	// RefreshCharPortrait
	static std::string RefreshCharPortrait();

};


#endif
