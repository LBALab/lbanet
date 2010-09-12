/*
------------------------[ Lbanet Source ]-------------------------
Copyright (C) 2009
Author: adaptation from Miguel Gomez's code on gamasutra
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


#ifndef __LBA_NET_VECTOR_H__
#define __LBA_NET_VECTOR_H__

#include <math.h>

// A floating point number
//
typedef float SCALAR;


#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
 
//*************************************************************************************************
//*                                      class VECTOR
//*************************************************************************************************
class VECTOR
{

public:

	SCALAR x,y,z; //x,y,z coordinates

public:
	//! constructor
	VECTOR()
	: x(0), y(0), z(0)
	{}

	//! constructor
	VECTOR( const SCALAR& a, const SCALAR& b, const SCALAR& c )
	: x(a), y(b), z(c)
	{}


	//index a component
	//NOTE: returning a reference allows
	//you to assign the indexed element
	SCALAR& operator [] ( const long i )
	{
		return *((&x) + i);
	}

	const SCALAR& operator [] ( const long i ) const
	{
		return *((&x) + i);
	}


	//compare
	const bool operator == ( const VECTOR& v ) const
	{
		return (v.x==x && v.y==y && v.z==z);

	}

	const bool operator != ( const VECTOR& v ) const
	{
		return !(v == *this);
	}

	const bool operator < ( const VECTOR& v ) const
	{
		if(v.x < x)
			return true;

		if(v.x == x)
		{
			if(v.y < y)
				return true;

			if(v.y == y)
			{
				if(v.z < z)
					return true;
			}
		}

		return false;
	}


	//negate
	const VECTOR operator - () const
	{
		return VECTOR( -x, -y, -z );
	}

	//assign
	const VECTOR& operator = ( const VECTOR& v )
	{
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	//increment
	const VECTOR& operator += ( const VECTOR& v )
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;

		return *this;
	}

	//decrement
	const VECTOR& operator -= ( const VECTOR& v )
	{
		x-=v.x;
		y-=v.y;
		z-=v.z;

		return *this;
	}

	//self-multiply
	const VECTOR& operator *= ( const SCALAR& s )
	{
		x*=s;
		y*=s;
		z*=s;

		return *this;
	}

	//self-divide
	const VECTOR& operator /= ( const SCALAR& s )
	{
		const SCALAR r = 1 / s;

		x *= r;
		y *= r;
		z *= r;

		return *this;
	}

	//add
	const VECTOR operator + ( const VECTOR& v ) const
	{
		return VECTOR(x + v.x, y + v.y, z + v.z);
	}

	//subtract
	const VECTOR operator - ( const VECTOR& v ) const
	{
		return VECTOR(x - v.x, y - v.y, z - v.z);
	}

	//post-multiply by a scalar
	const VECTOR operator * ( const SCALAR& s ) const
	{
		return VECTOR( x*s, y*s, z*s );
	}

	//pre-multiply by a scalar
	friend inline const VECTOR operator * ( const SCALAR& s, const VECTOR& v )
	{
		return v * s;
	}

	//divide
	const VECTOR operator / (SCALAR s) const
	{
		s = 1/s;

		return VECTOR( s*x, s*y, s*z );
	}

	//cross product
	const VECTOR cross( const VECTOR& v ) const
	{
		//Davis, Snider, "Introduction to Vector Analysis", p. 44
		return VECTOR( y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x );
	}

	//scalar dot product
	const SCALAR dot( const VECTOR& v ) const
	{
		return x*v.x + y*v.y + z*v.z;
	}

	//length
	const SCALAR length() const
	{
		return (SCALAR)sqrt( (double)this->dot(*this) );
	}

	//unit vector
	const VECTOR unit() const
	{
		return (*this) / length();
	}

	//make this a unit vector
	void normalize()
	{
		(*this) /= length();
	}

	//equal within an error ‘e’
	const bool nearlyEquals( const VECTOR& v, const SCALAR e ) const
	{
		return (fabs(x-v.x) < e);
	}

};



 
//*************************************************************************************************
//*                                      axis oriented AABB bounding box class
//*************************************************************************************************
class AABB
{
public: 
	VECTOR P; //position
	VECTOR E; //x,y,z extents

public: 
	//! constructor
	AABB()
	{}

	//! constructor
	AABB(const VECTOR& p, const VECTOR& e)
		: P(p), E(e)
	{}



	//returns true if this is overlapping b
	const bool overlaps( const AABB& b ) const
	{
		const VECTOR T = b.P - P;//vector from A to B
		return (fabs(T.x) <= (E.x + b.E.x) )
				&& (fabs(T.y) <= (E.y + b.E.y))
				&& (fabs(T.z) <= (E.z + b.E.z));
	}


	//min x, y, or z
	const SCALAR min(long i) const
	{
		return (P[i] - E[i]); 
	}

	//max x, y, or z
	const SCALAR max(long i) const
	{
		return (P[i] + E[i]); 
	}



	// bounding box sweep test
	const bool AABBSweep(	const VECTOR& va, //displacement of A
							const AABB& B, //boundingbox of b
							const VECTOR& vb, //displacement of B 
							SCALAR& u0, //normalized time of first collision
							SCALAR& u1 //normalized time of second collision 
						  )
	{
		//the problem is solved in A's frame of reference
		VECTOR v = (vb - va);
	    
		//relative velocity (in normalized time)
		VECTOR u_0(0,0,0);
	   
		//first times of overlap along each axis
		VECTOR u_1(1,1,1);
	   
		//last times of overlap along each axis

		//check if they were overlapping
		// on the previous frame
		if( overlaps(B) )
		{
			u0 = u1 = 0;
			return true;
		}


		//find the possible first and last times
		//of overlap along each axis
		for( long i=0 ; i<3 ; i++ )
		{
			if( max(i)<B.min(i) && v[i]<0 )
			{
				u_0[i] = (max(i) - B.min(i)) / v[i]; 
			}
			else if( B.max(i)<min(i) && v[i]>0 )
			{
				u_0[i] = (min(i) - B.max(i)) / v[i]; 
			}

			if( B.max(i)>min(i) && v[i]<0 )
			{
				u_1[i] = (min(i) - B.max(i)) / v[i]; 
			}
			else if( max(i)>B.min(i) && v[i]>0 )
			{
				u_1[i] = (max(i) - B.min(i)) / v[i]; 
			}
		}


		//possible first time of overlap
		u0 = MAX( u_0.x, MAX(u_0.y, u_0.z) );

		//possible last time of overlap
		u1 = MIN( u_1.x, MIN(u_1.y, u_1.z) );

		//they could have only collided if
		//the first time of overlap occurred
		//before the last time of overlap
		return (u0 <= u1);
	} 
}; 

 
//*************************************************************************************************
//*		2D square class
//*************************************************************************************************
class Square2D
{
public:
	//! constructor
	Square2D()
		: _minX(0), _minZ(0), _maxX(0), _maxZ(0)
	{}

	//! constructor
	Square2D(float minX, float minZ, float maxX, float maxZ)
		: _minX(minX), _minZ(minZ), _maxX(maxX), _maxZ(maxZ)
	{}

	//! overlap
	bool Overlap(const Square2D & B) const
	{
		if( (_minX >= B._maxX) || (_maxX <= B._minX) )
			return false;

		if( (_minZ >= B._maxZ) || (_maxZ <= B._minZ) )
			return false;

		return true;
	}

	//! overlap
	bool Overlap(float ptX, float ptZ) const
	{
		if( (ptX > _minX) && (ptX < _maxX) )
			if( (ptZ > _minZ) && (ptZ < _maxZ) )
			return true;

		return false;
	}


	float _minX;
	float _minZ;
	float _maxX;
	float _maxZ;
};


#endif