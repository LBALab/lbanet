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


#if !defined(__LbaNetModel_1_ConnectionHandlerBase_h)
#define __LbaNetModel_1_ConnectionHandlerBase_h


#include <string>
#include "RunnableThread.h"


/***********************************************************************
 * Module:  ConnectionHandlerBase.h
 * Author:  vivien
 * Purpose: Base class to hanlde connection with server
 ***********************************************************************/

class ConnectionHandlerBase : public Runnable
{
public:
	//! constructor
	ConnectionHandlerBase(){}

	//! destructor
	virtual ~ConnectionHandlerBase(){}

	//! connect to the server
	//! return 1 in case of success
	//! else set the string reason
	virtual int Connect(const std::string &user, const std::string &password, std::string & reason) = 0;

	//! disconnect from the server
	virtual void Disconnect() = 0;

	//! ask server to change world
	virtual void ChangeWorld(const std::string & NewWorld) = 0;

	//! get the list of world to connect to
	virtual void RefreshWorldList() = 0;

	//! patch a world
	virtual void PatchWorld(const std::string & WorldName) = 0;

protected:
	
	//! start running the thread
	void StartThread()
	{
		_thread = new RunThread(this);
		_threadcontrol = _thread->start();
	}

	//! join started thread
	void JoinThread()
	{
		if(_thread)
		{
			_threadcontrol.join();
			_thread = NULL;
		}
	}

protected:
	// threading and mutex stuff
	IceUtil::ThreadControl									_threadcontrol;		
	IceUtil::ThreadPtr										_thread;
};

#endif