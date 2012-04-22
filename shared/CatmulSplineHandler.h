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

#if !defined(__CATMULSPLINE_H_h)
#define __CATMULSPLINE_H_h

#include <list>
#include "CommonTypes.h"


/***********************************************************************
 * Module:  CatmullSplineHandler.h
 * Author:  vivien
 * Purpose: Declaration of the class CatmullSplineHandler
 ***********************************************************************/
class CatmullSplineHandler
{
public:

	//! constructor
	CatmullSplineHandler();

	//! set the points used by the algorithm to calculate the position and rotation
	void SetWaypoints(const std::vector<LbaVec3> &waypoints);

	//! update point indexes of P1 and P2
	void UpdateCurrentPoint(int waypointindexP2, const LbaVec3 & defaultP1Position);

	//! return approximative distance between P1 et P2
	float GetApproximateDistance();

	//! compute a position and rotation for a given ratio between P1 and P2
	void Compute(float ratio, bool lookForward, LbaVec3 & resPosition, float &resRotation);
	void Compute(float ratio, LbaVec3 & resPosition, LbaVec3 &tangent1, LbaVec3 &tangent2);

	//! return the current number of waypoints
	int NbWayPoints();

	//! return waypoint
	const LbaVec3 & GetWaypoint(int index);


protected:
	//! calculate spline from to between 0 and 1
	float CatmullSpline(float P0, float P1, float P2, float P3, float t);

	//! calculate spline of vector from to between 0 and 1
	LbaVec3 CatmullSpline(const LbaVec3 &P0, const LbaVec3 &P1, const LbaVec3 &P2, const LbaVec3 &P3, float t);

	//! calculate arc length
	float GetArcLength(const LbaVec3 &P0, const LbaVec3 &P1, const LbaVec3 &P2, const LbaVec3 &P3, int nbsamples);

private:
	std::vector<LbaVec3> _waypoints;
	int					_currIndex;

	LbaVec3			_Pm1;
	LbaVec3			_P0;
	LbaVec3			_P1;
	LbaVec3			_P2;
	LbaVec3			_P3;
	LbaVec3			_P4;
};


#endif