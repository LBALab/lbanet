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


#ifndef _LBANET_EDITOR_SHARED_DATA_H_
#define _LBANET_EDITOR_SHARED_DATA_H_



#include <string>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>

//*************************************************************************************************
//*                               class EditorSharedData
//*************************************************************************************************
/**
* @brief Class handling configuration file
*
*/
class EditorSharedData
{
public:
	// destructor
	~EditorSharedData(){}

	// get singleton instance
	static EditorSharedData *	GetInstance();

	// set functions
	bool GetFly();
	void SetFly(bool fly);


protected:
	// constructor
	EditorSharedData()
		: m_editorfly(false){}

private:

	static EditorSharedData *		_singletonInstance;
	boost::mutex					m_mutex;

	bool							m_editorfly;
};


#endif
