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


#if !defined(__LbaNetModel_1_DataDirHandler_h)
#define __LbaNetModel_1_DataDirHandler_h

#include <string>


/***********************************************************************
 * Module:  DataDirHandler.h
 * Author:  vivien
 * Modified: lundi 27 juillet 2009 14:56:34
 * Purpose: Declaration of the class DataDirHandler
 ***********************************************************************/
class DataDirHandler
{
public:

	//! destructor
	~DataDirHandler();

	// singleton pattern
	static DataDirHandler * getInstance();

	// set the path to the data dir
	void SetDataDirPath(const std::string & datapath);
	
	// get the path to the data dir
	const std::string & GetDataDirPath();

	bool IsInEditorMode()
	{
		return _editorMode;
	}

	void SetEditorMode(bool v)
	{
		_editorMode = v;
	}
	
	bool IsInSoundEditorMode()
	{
		return _soundeditorMode;
	}

	void SetSoundEditorMode(bool v)
	{
		_soundeditorMode = v;
	}
protected:
	//! constructor
   DataDirHandler();

private:
	static DataDirHandler *		_singletonInstance;

	std::string				_dataDirPath;
	bool					_editorMode;
	bool					_soundeditorMode;
};

#endif