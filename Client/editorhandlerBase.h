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

#ifndef EDITORHANDLERBASE_H
#define EDITORHANDLERBASE_H

class QWidget;

//! base class to take care of editor
class EditorHandlerBase
{

public:
	//! constructor
	EditorHandlerBase(){}

	//! constructor
	virtual ~EditorHandlerBase(){}

	//! set the osg window
	virtual void SetOsgWindow(QWidget *osgwindow) = 0;

	//! refresh display
	virtual void RefreshDisplay() = 0;

	//! refresh gui with map info
	virtual void SetMapInfo(const std::string & mapname) = 0;

	//! inform that map Finished Loaded;
	virtual void MapFinishedLoaded() = 0;

	//! player moved
	virtual void PlayerMoved(float posx, float posy, float posz) = 0;

	// called when an object is picked
	virtual void PickedObject(const std::string & name, float px, float py, float pz) = 0;

	//! when an editor arrow was dragged by mouse
	virtual void PickedArrowMoved(int pickedarrow) = 0;

};

#endif // EDITORHANDLERNASE_H
