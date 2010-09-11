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


#ifndef _LBA_NET_MESSAGE_BOX_
#define _LBA_NET_MESSAGE_BOX_


namespace CEGUI
{
	class Window;
	class EventArgs;
	class Listbox;
}

#include <string>


//*************************************************************************************************
//*                               class CGMessageBox
//*************************************************************************************************
/**
* @brief Class handling a CGMessageBox
*
*/
class CGMessageBox
{
 public:

	// singleton pattern
   static CGMessageBox * getInstance();


	//! destructor
	virtual ~CGMessageBox();

	//! initalize the box
	void Initialize(CEGUI::Window* Root);

	//! display the chatbox on screen
	void Show(const std::string &Title, const std::string &Message);

	//! handle windows closing event
	bool HandleOk (const CEGUI::EventArgs& e);


protected:
	//! constructor
	 CGMessageBox();

private:
	CEGUI::Window*							_myBox;
	static CGMessageBox *		_singletonInstance;
};

#endif
