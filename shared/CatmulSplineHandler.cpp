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

#include "CatmulSplineHandler.h"

#include <math.h>

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif


/***********************************************************
//! constructor
***********************************************************/
CatmullSplineHandler::CatmullSplineHandler()
: _currIndex(-1)
{

}

/***********************************************************
//! set the waypoints use by the alogirthm to calculate the positions
***********************************************************/
void CatmullSplineHandler::SetWaypoints(const std::vector<LbaVec3> &waypoints)
{
	_waypoints = waypoints;
	if(_waypoints.size() == 6)
		UpdateCurrentPoint(3, LbaVec3());
}


/***********************************************************
//! update point indexes of P1 and P2
***********************************************************/
void CatmullSplineHandler::UpdateCurrentPoint(int waypointindexP2, const LbaVec3 & defaultP1Position)
{
	if(_currIndex == waypointindexP2)
		return;

	_currIndex = waypointindexP2;

	if(waypointindexP2 < (int)_waypoints.size())
	{
		_P2 =  _waypoints[waypointindexP2];

		if((waypointindexP2+1) < (int)_waypoints.size())
			_P3 = _waypoints[waypointindexP2+1];
		else
			_P3 = _P2;

		if((waypointindexP2+2) < (int)_waypoints.size())
			_P4 = _waypoints[waypointindexP2+2];
		else
			_P4 = _P2;

		--waypointindexP2;
		if(waypointindexP2 >= 0)
			_P1 =  _waypoints[waypointindexP2];
		else
			_P1 = defaultP1Position;

		--waypointindexP2;
		if(waypointindexP2 >= 0)
			_P0 =  _waypoints[waypointindexP2];
		else
			_P0 =  _P1;

		--waypointindexP2;
		if(waypointindexP2 >= 0)
			_Pm1 =  _waypoints[waypointindexP2];
		else
			_Pm1 =  _P1;
	}
}

/***********************************************************
//! return approximative distance between P1 et P2
***********************************************************/
float CatmullSplineHandler::GetApproximateDistance()
{
	return GetArcLength(_P0, _P1, _P2, _P3, 1000);
}

/***********************************************************
//! compute a position and rotation for a given ratio between P1 and P2
***********************************************************/
void CatmullSplineHandler::Compute(float ratio, LbaVec3 & resPosition, 
								   LbaVec3 &tangent1, LbaVec3 &tangent2)
{
	resPosition = CatmullSpline(_P0, _P1, _P2, _P3, ratio);

	float r1 = ratio-0.1f;
	if(r1 < 0)
	{
		r1 += 1;
		tangent1 = CatmullSpline(_Pm1, _P0, _P1, _P2, r1);
	}
	else
		tangent1 = CatmullSpline(_P0, _P1, _P2, _P3, r1);

	float r2 = ratio+0.1f;
	if(r2 > 1)
	{
		r2 -= 1;
		tangent2 = CatmullSpline(_P1, _P2, _P3, _P4, r2);
	}
	else
		tangent2 = CatmullSpline(_P0, _P1, _P2, _P3, r2);
}


/***********************************************************
//! compute a position and rotation for a given ratio between P1 and P2
***********************************************************/
void CatmullSplineHandler::Compute(float ratio, bool lookForward, LbaVec3 & resPosition, float &resRotation)
{
	LbaVec3 tang1;
	LbaVec3 tang2;

	Compute(ratio, resPosition, tang1, tang2);

	LbaVec3 diff(	tang2.x-tang1.x, 
					tang2.y-tang1.y, 
					tang2.z-tang1.z);

	resRotation = LbaQuaternion::GetSignedAngleFromVector(diff);
	if(!lookForward)
		resRotation += 180;
}


/***********************************************************
//! return the current number of waypoints
***********************************************************/
int CatmullSplineHandler::NbWayPoints()
{
	return static_cast<int>(_waypoints.size());
}

/***********************************************************
//! return waypoint
***********************************************************/
const LbaVec3 & CatmullSplineHandler::GetWaypoint(int index)
{
	return _waypoints.at(index);
}


/***********************************************************
//! calculate spline from to between 0 and 1
***********************************************************/
float CatmullSplineHandler::CatmullSpline(float P0, float P1, float P2, float P3, float t)
{
	float res =	0.5f *( (2 * P1) + (-P0 + P2) * t 
				+ (2*P0 - 5*P1 + 4*P2 - P3) * t*t 
				+ (-P0 + 3*P1- 3*P2 + P3) * t*t*t);

	return res;
}


/***********************************************************
calculate spline of vector from to between 0 and 1
***********************************************************/
LbaVec3 CatmullSplineHandler::CatmullSpline(const LbaVec3 &P0, const LbaVec3 &P1, 
												const LbaVec3 &P2, const LbaVec3 &P3, float t)
{
	LbaVec3 res;
	res.x = CatmullSpline(P0.x, P1.x, P2.x, P3.x, t);
	res.y = CatmullSpline(P0.y, P1.y, P2.y, P3.y, t);
	res.z = CatmullSpline(P0.z, P1.z, P2.z, P3.z, t);

	return res;
}


/***********************************************************
calculate arc length
***********************************************************/
float CatmullSplineHandler::GetArcLength(const LbaVec3 &P0, const LbaVec3 &P1, 
											 const LbaVec3 &P2, const LbaVec3 &P3, int nbsamples)
{
	float res = 0;
	LbaVec3 currpoint = P1;
	for(int i=0; i < nbsamples; ++i)
	{
		float t = (1.0f / nbsamples) * i;
		LbaVec3 respoint = CatmullSpline(P0, P1, P2, P3, t);
		res += respoint.Distance(currpoint);
		currpoint = respoint;
	}

	return res;
}
