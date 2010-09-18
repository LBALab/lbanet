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

#ifndef _MAP_HANDLER_H__
#define _MAP_HANDLER_H__


#include <ClientInterface.h>

#include "RunnableThread.h"


using namespace LbaNet;

//! take care of a map of the world
class MapHandler : public Runnable
{
public:
	//! constructor
	MapHandler(const MapInfo & mapinfo);

	//! desructor
	~MapHandler(void);

	//! start run function
	void StartThread();

	// running function of the thread
	virtual void run();

protected:
	// process events
	void ProcessEvents(const std::map<Ice::Long, EventsSeq> & evts);

private:
	// threading and mutex stuff
	IceUtil::Monitor<IceUtil::Mutex>						_monitor;
	bool													_Trunning;
	IceUtil::ThreadControl									_threadcontrol;
	IceUtil::ThreadPtr										_thread;

	MapInfo													_mapinfo;
};


#endif