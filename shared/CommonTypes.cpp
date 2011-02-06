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

#include "CommonTypes.h"
#include <NxQuat.h>


#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif

/***********************************************************
Constructor
***********************************************************/
LbaQuaternion::LbaQuaternion()
: X(0), Y(0), Z(0), W(1)
{

}


/***********************************************************
constructor with angle and vec
***********************************************************/
LbaQuaternion::LbaQuaternion(float angle, LbaVec3 vec)
{
	NxQuat q(angle, NxVec3(vec.x, vec.y, vec.z));
	X = q.x;
	Y = q.y;
	Z = q.z;
	W = q.w;
}


/***********************************************************
constructor from 3 angles
***********************************************************/
LbaQuaternion::LbaQuaternion(float anglex, float angley, float anglez)
{
	NxQuat qx(anglex, NxVec3(1, 0, 0));
	NxQuat qy(angley, NxVec3(0, 1, 0));
	NxQuat qz(anglez, NxVec3(0, 0, 1));
	NxQuat res = qx * qy * qz;

	X = res.x;
	Y = res.y;
	Z = res.z;
	W = res.w;
}


/***********************************************************
add rotation to quaternion
***********************************************************/
void LbaQuaternion::AddSingleRotation(float angle, const LbaVec3 &vec)
{
	float tochange = GetRotationSingleAngle() + angle;
	if(tochange < 0)
		tochange += 360;
	if(tochange > 360)
		tochange -= 360;

	NxQuat q(tochange, NxVec3(vec.x, vec.y, vec.z));
	X = q.x;
	Y = q.y;
	Z = q.z;
	W = q.w;
}


/***********************************************************
get direction vector
***********************************************************/
LbaVec3 LbaQuaternion::GetDirection(const LbaVec3 &vec)
{
	NxVec3 dir(vec.x, vec.y, vec.z);
	NxQuat current;
	current.setXYZW(X, Y, Z, W);

	current.rotate(dir);

	return LbaVec3(dir.x, dir.y, dir.z);
}


/***********************************************************
get object rotation on a single angle
***********************************************************/
float LbaQuaternion::GetRotationSingleAngle()
{
	NxQuat current;
	current.setXYZW(X, Y, Z, W);
	NxVec3 nvec;

	float Yangle;
	current.getAngleAxis(Yangle, nvec);
	return Yangle;
}



/***********************************************************
get the angle between a vector and the 0 angle
***********************************************************/
float LbaQuaternion::GetAngleFromVector(const LbaVec3 &vec)
{
	float norm = sqrt((vec.x * vec.x) + (vec.z * vec.z));
	if(norm)
	{
		float nx = -vec.x / norm;
		float nz = vec.z / norm;

		float res = 0;
		res = atan2(nz, nx) - atan2(1.0f,0.0f);
		res = 180 * res / M_PI;
		return res;
	}

	return 0;
}
