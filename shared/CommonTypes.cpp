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

#include <math.h>
#include <vector>

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif




/***********************************************************
distance between 2 vectors
***********************************************************/
float LbaVec3::Distance(const LbaVec3 & v) const
{
	float dx = x - v.x;
	float dy = y - v.y;
	float dz = z - v.z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}


/***********************************************************
normalize vector
***********************************************************/
float LbaVec3::Length()
{
	return sqrt(x * x + y * y + z * z);
}


/***********************************************************
normalize vector
***********************************************************/
void LbaVec3::Normalize()
{
	float L = Length();
	x /= L;
	y /= L;
	z /= L;
}

/***********************************************************
cross product
***********************************************************/
void LbaVec3::cross(const LbaVec3 &left, const LbaVec3 & right)
{
	float a = (left.y * right.z) - (left.z * right.y);
	float b = (left.z * right.x) - (left.x * right.z);
	float c = (left.x * right.y) - (left.y * right.x);

	x = a;
	y = b;
	z = c;
}


/***********************************************************
operator !=
***********************************************************/
bool LbaVec3::operator !=(const LbaVec3 & q) const
{
	float diff = (x-q.x) + (y-q.y) + (z-q.z);
	return (fabs(diff) > 0.01f);
}


/***********************************************************
operator -
***********************************************************/
LbaVec3 LbaVec3::operator -(const LbaVec3 & q) const
{
	return LbaVec3(x-q.x, y-q.y, z-q.z);
}



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
	X = vec.x;
	Y = vec.y;
	Z = vec.z;

	// Normalize the axis
	const float i_length =  1.0f / sqrt( X*X + Y*Y + Z*Z );
	X = X * i_length;
	Y = Y * i_length;
	Z = Z * i_length;

	// now make a Quaternion out of it
	float Half = 0.01745329251994329547f * angle * 0.5f;

	W = cos(Half);
	const float sin_theta_over_two = sin(Half);
	X = X * sin_theta_over_two;
	Y = Y * sin_theta_over_two;
	Z = Z * sin_theta_over_two;
}


/***********************************************************
constructor from 3 angles
***********************************************************/
LbaQuaternion::LbaQuaternion(float anglex, float angley, float anglez)
{
	LbaQuaternion qx(anglex, LbaVec3(1, 0, 0));
	LbaQuaternion qy(angley, LbaVec3(0, 1, 0));
	LbaQuaternion qz(anglez, LbaVec3(0, 0, 1));
	LbaQuaternion res = (qx * qy * qz);

	X = res.X;
	Y = res.Y;
	Z = res.Z;
	W = res.W;
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

	LbaQuaternion q(tochange, vec);
	X = q.X;
	Y = q.Y;
	Z = q.Z;
	W = q.W;
}


/***********************************************************
get direction vector
***********************************************************/
LbaVec3 LbaQuaternion::GetDirection(const LbaVec3 &vec) const
{
	LbaVec3 dir(vec);
	rotate(dir);
	return dir;
}


/***********************************************************
get object rotation on a single angle
***********************************************************/
float LbaQuaternion::GetRotationSingleAngle() const
{
    float angle = acos(W) * 2.0f;
    float sa = sqrt(1.0f - W*W);
	if (sa)
		angle *= 57.29577951308232286465f;

	return angle;
}



/***********************************************************
get the angle between a vector and the 0 angle
***********************************************************/
float LbaQuaternion::GetAngleFromVector(const LbaVec3 &vec)
{
	float res = GetSignedAngleFromVector(vec);
	if(res < 0)
		res += 360;
	return res;

}



/***********************************************************
get the angle between a vector and the 0 angle
***********************************************************/
float LbaQuaternion::GetSignedAngleFromVector(const LbaVec3 &vec)
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


/***********************************************************
operator *
***********************************************************/
LbaQuaternion LbaQuaternion::operator *(const LbaQuaternion & q) const
{
	return LbaQuaternion(	W*q.X + q.W*X + Y*q.Z - q.Y*Z,
							W*q.Y + q.W*Y + Z*q.X - q.Z*X,
							W*q.Z + q.W*Z + X*q.Y - q.X*Y,
							W*q.W - X*q.X - Y*q.Y - Z*q.Z);
}


/***********************************************************
rotate a vector by the quaternion
***********************************************************/
void LbaQuaternion::rotate(LbaVec3 & v) const
{
	LbaQuaternion myInverse(-X, -Y, -Z, W);

	LbaQuaternion left;
	left.multiply(*this, v);

	v.x =left.W*myInverse.X + myInverse.W*left.X + left.Y*myInverse.Z - myInverse.Y*left.Z;
	v.y =left.W*myInverse.Y + myInverse.W*left.Y + left.Z*myInverse.X - myInverse.Z*left.X;
	v.z =left.W*myInverse.Z + myInverse.W*left.Z + left.X*myInverse.Y - myInverse.X*left.Y;
}



/***********************************************************
 set current quat as left * right
***********************************************************/
void LbaQuaternion::multiply(const LbaQuaternion& left, const LbaVec3& right)
{
	W = - left.X*right.x - left.Y*right.y - right.z*left.Z;
	X =   left.W*right.x + left.Y*right.z - right.y*left.Z;
	Y =   left.W*right.y + left.Z*right.x - right.z*left.X;
	Z =   left.W*right.z + left.X*right.y - right.x*left.Y;
}



/***********************************************************
Return true if r1 and r2 are real
***********************************************************/
bool CollisionTester::QuadraticFormula(const float a, const float b, const float c,
									float& r1, //first
									float& r2 //and second roots
									)
{
    const float q = b*b - 4*a*c;
    if( q >= 0 )
    {
        const float sq = sqrt(q);
        const float d = 1 / (2*a);
        r1 = ( -b + sq ) * d;
        r2 = ( -b - sq ) * d;
        return true;//real roots
    }

	return false;//complex roots
}

/***********************************************************
sphere sphere sweep test
***********************************************************/
bool CollisionTester::SphereSphereSweep(const float ra, //radius of sphere A
											const LbaVec3& A0, //previous position of sphere A
											const LbaVec3& A1, //current position of sphere A
											const float rb, //radius of sphere B
											const LbaVec3& B0, //previous position of sphere B
											const LbaVec3& B1, //current position of sphere B
											float& u0, //normalized time of first collision
											float& u1 //normalized time of second collision
											)
{
    //vector from A0 to A1
    const LbaVec3 va = A1 - A0;

    //vector from B0 to B1
    const LbaVec3 vb = B1 - B0;

    //vector from A0 to B0
    const LbaVec3 AB = B0 - A0;


     //relative velocity (in normalized time)
	const LbaVec3 vab = vb - va;


    const float rab = ra + rb;
	const float ab2 = AB.dot(AB);
	const float rab2 = rab*rab;
	const float fpdot2 = AB.dot(LbaVec3(0,0,0)-vab);


    //check if they're currently overlapping
    if( ab2 <= rab2 )
    {
        u0 = 0;
        u1 = 0;
        return true;
    }


	//TODO - doesnt work...
  //  //u*u coefficient
  //  const float a = vab.dot(vab);

  //  //u coefficient
  //  const float b = 2*fpdot2;//vab.dot(AB);

  //  //constant term 
  //  const float c = ab2 - rab2;


  //  //check if they hit each other
  //  // during the frame
  //  if( QuadraticFormula( a, b, c, u0, u1 ) )
  //  {
  //      if( u0 > u1 )
		//	SWAP( u0, u1 );

		//if(u1 > 1)
		//	return false;

		//if(u0 < 0)
		//	return false;

  //      return true;
  //  }

    return false;
} 
