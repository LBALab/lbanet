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
#include "GUILocalizationCallback.h"
#include <iostream>
#include "Localizer.h"


/***********************************************************
callback
***********************************************************/
bool MyPropertyCallback(CEGUI::Window* window, CEGUI::String& propname, CEGUI::String& propvalue, void* userdata)
{
	if(propname == "Text" || propname == "Tooltip")
	{
		if(propvalue.size() > 1)
			if(propvalue[0] == '#')
			{
				std::istringstream iss(propvalue.substr(1).c_str());
				long id;
				iss >> id;
				propvalue = CEGUI::String((const unsigned char *)Localizer::getInstance()->GetText(Localizer::GUI, id).c_str());
			}
	}

	return true;
}
