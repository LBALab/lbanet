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
add rotation to quaternion
***********************************************************/
void LbaQuaternion::AddRotation(float angle, LbaVec3 vec)
{
	NxQuat q(angle, NxVec3(vec.x, vec.y, vec.z));
	NxQuat current;
	current.setXYZW(X, Y, Z, W);

	current = q * current;

	X = current.x;
	Y = current.y;
	Z = current.z;
	W = current.w;
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
	return current.getAngle();
}
