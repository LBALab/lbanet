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

#ifndef _HOLO_HANDLER_H__
#define _HOLO_HANDLER_H__

#include <map>
#include <boost/shared_ptr.hpp>


class Holomap;
typedef boost::shared_ptr<Holomap>	HolomapPtr;
class HolomapLocation;
typedef boost::shared_ptr<HolomapLocation>	HolomapLocationPtr;
class HolomapTravelPath;
typedef boost::shared_ptr<HolomapTravelPath>	HolomapTravelPathPtr;



//! take care of shared data between process
class HolomapHandler
{
public:
	// singleton pattern
	static HolomapHandler * getInstance();

	//! destructor
	~HolomapHandler(void){}

	//! clear all
	void clear()
	{
		_holomaps.clear();
		_holomaplocs.clear();
		_holomappaths.clear();
	}


	//! add holomap
	void AddHolomap(HolomapPtr holo);

	//! remove holomap
	void RemoveHolomap(long id);

	//! get holomap
	HolomapPtr GetHolomap(long id);

	//! get holomaps
	std::map<long, HolomapPtr> &GetHolomaps()
	{ return _holomaps;}


	//! add holomap loc
	void AddHolomapLoc(HolomapLocationPtr holo);

	//! remove holomap loc
	void RemoveHolomapLoc(long id);

	//! get holomap loc
	HolomapLocationPtr GetHolomapLoc(long id);

	//! get holomaps loc
	std::map<long, HolomapLocationPtr> &GetHolomapLocs()
	{ return _holomaplocs;}


	//! add holomap loc
	void AddHolomapPath(HolomapTravelPathPtr holo);

	//! remove holomap loc
	void RemoveHolomapPath(long id);

	//! get holomap loc
	HolomapTravelPathPtr GetHolomapPath(long id);

	//! get holomaps loc
	std::map<long, HolomapTravelPathPtr> &GetHolomapPaths()
	{ return _holomappaths;}

	//! generate id
	long GenerateHolomapId();

	//! generate id
	long GenerateHolomapLocId();

	//! generate id
	long GenerateHolomapPathId();

protected:
	//! constructor
	HolomapHandler(void){}

private:
	static HolomapHandler *						_Instance;
	
	std::map<long, HolomapPtr>					_holomaps;
	std::map<long, HolomapLocationPtr>			_holomaplocs;
	std::map<long, HolomapTravelPathPtr>		_holomappaths;

};

#endif
