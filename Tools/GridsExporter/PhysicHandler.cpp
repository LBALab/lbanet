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

#include "PhysicHandler.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <math.h>
#include <set>
#include <algorithm>
#include <map>


#include "vector.h"




bool PlaneSortX (const PlaneInfo &i, const PlaneInfo &j) { return (i.StartX<j.StartX); }
bool PlaneSortY (const PlaneInfo &i, const PlaneInfo &j) { return (i.StartY<j.StartY); }
bool PlaneSortZ (const PlaneInfo &i, const PlaneInfo &j) { return (i.StartZ<j.StartZ); }
bool StairSortY (const StairInfo &i, const StairInfo &j) { return (i.C4Y<j.C4Y); }



unsigned int findvertexinmap(std::map<VECTOR, unsigned int> & map, unsigned int & curridx, 
								  std::vector<float> & vertexes, const VECTOR & vertex)
{
	std::map<VECTOR, unsigned int>::iterator itm = map.find(vertex);
	if(itm != map.end())
		return itm->second;

	map[vertex] = curridx;
	vertexes.push_back(vertex.x);
	vertexes.push_back(vertex.y);
	vertexes.push_back(vertex.z);
	return curridx++;
}





/*
--------------------------------------------------------------------------------------------------
- constructor
--------------------------------------------------------------------------------------------------
*/
PhysicHandler::PhysicHandler()
: _physicCube(NULL), _materialCube(NULL)
{

}

/*
--------------------------------------------------------------------------------------------------
- destructor
--------------------------------------------------------------------------------------------------
*/
PhysicHandler::~PhysicHandler()
{
	ClearMemory();
}

/*
--------------------------------------------------------------------------------------------------
- load a map into memory
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::Allocate(int sizeX, int sizeY, int sizeZ)
{
	ClearMemory();
	AllocateMemory(sizeX, sizeY, sizeZ);
}

/*
--------------------------------------------------------------------------------------------------
- save the map physics to a file
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SaveMap(const std::string Filename)
{
	if(!_physicCube)
		return;

	std::ofstream file(Filename.c_str());

	if(file.is_open())
	{
		short *	physicCubePtr = _physicCube;

		for(int y=0; y<_sizeY; ++y)
		{
			for(int x=0; x<_sizeX; ++x)
			{
				for(int z=0; z<_sizeZ; ++z)
				{
					file << std::hex << *physicCubePtr << " ";
					++physicCubePtr;
				}
				file << std::endl;
			}
			file << std::endl;
		}
	}
}


/*
--------------------------------------------------------------------------------------------------
- clean the memory
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::ClearMemory()
{
	if(_physicCube != NULL)
		delete _physicCube;

	if(_materialCube != NULL)
		delete _materialCube;

	_physicCube = NULL;
	_materialCube =NULL;
}


/*
--------------------------------------------------------------------------------------------------
- allocate a memory buffer of given size
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::AllocateMemory(int sizeX, int sizeY, int sizeZ)
{
	_physicCube = new short [sizeY*sizeX*sizeZ];
	_materialCube = new short [sizeY*sizeX*sizeZ];

	_sizeX = sizeX;
	_sizeY = sizeY;
	_sizeZ = sizeZ;
}



/*
--------------------------------------------------------------------------------------------------
- return true if the brick asked contain a solid
- structure - return false otherwise
--------------------------------------------------------------------------------------------------
*/
bool PhysicHandler::IsSolid(int X, int Y, int Z)
{
	short brickS = GetStructure(X, Y, Z);
	return (brickS == 1 || brickS > 13);
}

/*
--------------------------------------------------------------------------------------------------
- return true if the brick asked contain a empty
- structure - return false otherwise
--------------------------------------------------------------------------------------------------
*/
bool PhysicHandler::IsEmpty(int X, int Y, int Z)
{
	short brickS = GetStructure(X, Y, Z);
	return (brickS == 0);
}

/*
--------------------------------------------------------------------------------------------------
- return true if the actor is stepping on empty place
--------------------------------------------------------------------------------------------------
*/
bool PhysicHandler::EmptyUnderActor(double X, double Y, double Z,
						double actorSizeX, double actorSizeY, double actorSizeZ)
{
	int XBegin = (int)(X-actorSizeX);
	int XEnd = (int)(X+actorSizeX);
	int ZBegin = (int)(Z-actorSizeZ);
	int ZEnd = (int)(Z+actorSizeZ);

	for(; XBegin<=XEnd; ++XBegin)
		for(; ZBegin<=ZEnd; ++ZBegin)
			if(!IsEmpty(XBegin, (int)Y, ZBegin))
				return false;

	return true;
}



/*
--------------------------------------------------------------------------------------------------
- return the structure of a specific brick
--------------------------------------------------------------------------------------------------
*/
short PhysicHandler::GetStructure(int X, int Y, int Z)
{
	if(X < 0 || Y < 0 || Z < 0 || X >= _sizeX || Y >= _sizeY || Z >= _sizeZ)
		return 0;

	if(!_physicCube)
		return 0;

	short res = _physicCube[Y*_sizeX*_sizeZ + X*_sizeZ + Z];
	//if(res == 0)
	//	res = _localAH->GetStructure(X, Y, Z);
	//if(res == 0)
	//	res = _EAH->GetStructure(X, Y, Z);

	return res;
}



/*
--------------------------------------------------------------------------------------------------
- return the structure of a specific brick
--------------------------------------------------------------------------------------------------
*/
short PhysicHandler::GetMaterial(int X, int Y, int Z)
{
	if(X < 0 || Y < 0 || Z < 0 || X >= _sizeX || Y >= _sizeY || Z >= _sizeZ)
		return 0;

	if(!_physicCube)
		return 0;

	short res = _materialCube[Y*_sizeX*_sizeZ + X*_sizeZ + Z];
	return res;
}




/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchWallX()
{
	SearchWallXNormal(_sizeY, _sizeX, _sizeZ);
	SearchWallXHidden(_sizeY, _sizeX, _sizeZ);
}

/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchWallXNormal(int sizeX, int sizeY, int sizeZ)
{
	_wallsX.clear();

	short * buffer = new short[sizeX*sizeY*sizeZ];
	for(int k=0; k<sizeY; ++k)
	{
		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = _physicCube[(i*_sizeX*_sizeZ)+(k*_sizeZ)+j];
			}
		}
	}



	for(int k=0; k<sizeY; ++k)
	{
		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				if((k+1)<sizeY)
				{
					if(buffer[((k+1)*sizeX*sizeZ)+(i*sizeZ)+j] == 1)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

					if(buffer[((k+1)*sizeX*sizeZ)+(i*sizeZ)+j] == 2)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

					if(buffer[((k+1)*sizeX*sizeZ)+(i*sizeZ)+j] == 5)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

					//if( buffer[(k*sizeX*sizeZ)+((i+1)*sizeZ)+j] > 1)
					//	buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;
				}
			}
		}
	}


	short * ptr = buffer;
	for(int i=0; i<sizeY; ++i)
	{
		SearchFloors(ptr, i, _wallsX, sizeX, sizeY, sizeZ, 0);
		ptr += sizeX*sizeZ;
	}


	delete[] buffer;
}




/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchWallXHidden(int sizeX, int sizeY, int sizeZ)
{
	_wallsXhidden.clear();

	short * buffer = new short[sizeX*sizeY*sizeZ];
	for(int k=0; k<sizeY; ++k)
	{
		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = _physicCube[(i*_sizeX*_sizeZ)+(k*_sizeZ)+j];
			}
		}
	}


	for(int k=sizeY-1; k>=0; --k)
	{
		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				if((k-1)>=0)
				{
					if(buffer[((k-1)*sizeX*sizeZ)+(i*sizeZ)+j] == 1)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

					if(buffer[((k-1)*sizeX*sizeZ)+(i*sizeZ)+j] == 2)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

					if(buffer[((k-1)*sizeX*sizeZ)+(i*sizeZ)+j] == 5)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;


					//if( buffer[(k*sizeX*sizeZ)+((i+1)*sizeZ)+j] > 1)
					//	buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;
				}
			}
		}
	}

	short * ptr = buffer;
	for(int i=0; i<sizeY; ++i)
	{
		SearchFloors(ptr, i, _wallsXhidden, sizeX, sizeY, sizeZ, 0);
		ptr += sizeX*sizeZ;
	}


	delete[] buffer;
}





/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchWallZ()
{
	SearchWallZNormal(_sizeX, _sizeZ, _sizeY);
	SearchWallZHidden(_sizeX, _sizeZ, _sizeY);
}

/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchWallZNormal(int sizeX, int sizeY, int sizeZ)
{
	_wallsZ.clear();

	short * buffer = new short[sizeX*sizeY*sizeZ];
	for(int k=0; k<sizeY; ++k)
	{
		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = _physicCube[(j*_sizeX*_sizeZ)+(i*_sizeZ)+k];
			}
		}
	}


	for(int k=0; k<sizeY; ++k)
	{
		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				if((k+1)<sizeY)
				{
					if(buffer[((k+1)*sizeX*sizeZ)+(i*sizeZ)+j] == 1)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

					if(buffer[((k+1)*sizeX*sizeZ)+(i*sizeZ)+j] == 3)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

					if(buffer[((k+1)*sizeX*sizeZ)+(i*sizeZ)+j] == 4)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

					//if( buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j+1] > 1)
					//	buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;
				}
			}
		}
	}


	short * ptr = buffer;
	for(int i=0; i<sizeY; ++i)
	{
		SearchFloors(ptr, i, _wallsZ, sizeX, sizeY, sizeZ, 0);
		ptr += sizeX*sizeZ;
	}


	delete[] buffer;
}




/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchWallZHidden(int sizeX, int sizeY, int sizeZ)
{
	_wallsZhidden.clear();

	short * buffer = new short[sizeX*sizeY*sizeZ];
	for(int k=0; k<sizeY; ++k)
	{
		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = _physicCube[(j*_sizeX*_sizeZ)+(i*_sizeZ)+k];
			}
		}
	}


	for(int k=sizeY-1; k>=0; --k)
	{
		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				if((k-1)>=0)
				{
					if(buffer[((k-1)*sizeX*sizeZ)+(i*sizeZ)+j] == 1)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

					if(buffer[((k-1)*sizeX*sizeZ)+(i*sizeZ)+j] == 3)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

					if(buffer[((k-1)*sizeX*sizeZ)+(i*sizeZ)+j] == 4)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

					//if( buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j+1] > 1)
					//	buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;
				}
			}
		}
	}

	short * ptr = buffer;
	for(int i=0; i<sizeY; ++i)
	{
		SearchFloors(ptr, i, _wallsZhidden, sizeX, sizeY, sizeZ, 0);
		ptr += sizeX*sizeZ;
	}


	delete[] buffer;
}




/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchFloors()
{
	//SearchFloorsNormal(_sizeX, _sizeY, _sizeZ);
	//SearchFloorsSee(_sizeX, _sizeY, _sizeZ);

	_planes.clear();
	for(short i=0; i<20; ++i)
		SearchFloorsWithMaterial(_sizeX, _sizeY, _sizeZ, i);

	SearchFloorsHidden(_sizeX, _sizeY, _sizeZ);
}





/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
//void PhysicHandler::SearchFloorsNormal(int sizeX, int sizeY, int sizeZ)
//{
//	_planes.clear();
//
//	short * buffer = new short[sizeX*sizeY*sizeZ];
//	memcpy ( buffer, _physicCube, sizeX*sizeY*sizeZ*sizeof(short) );
//
//
//	for(int k=1; k<(sizeY-1); ++k)
//	{
//		for(int i=0; i<sizeX; ++i)
//		{
//			for(int j=0; j<sizeZ; ++j)
//			{
//				if( _physicCube[((k+1)*sizeX*sizeZ)+(i*sizeZ)+j] != 0 )
//					buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;
//			}
//		}
//	}
//
//
//	short * ptr = buffer;
//	for(int i=0; i<sizeY; ++i)
//	{
//		SearchFloors(ptr, i, _planes, sizeX, sizeY, sizeZ, 0);
//		ptr += sizeX*sizeZ;
//	}
//
//
//	delete[] buffer;
//}
//



/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchFloorsWithMaterial(int sizeX, int sizeY, int sizeZ, short Material)
{
	short * buffer = new short[sizeX*sizeY*sizeZ];
	memcpy ( buffer, _physicCube, sizeX*sizeY*sizeZ*sizeof(short) );


	for(int k=0; k<sizeY; ++k)
	{
		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				if((k+1)<sizeY)
				{
					if(buffer[((k+1)*sizeX*sizeZ)+(i*sizeZ)+j] != 0)
						buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;
				}
			}
		}
	}


	for(int k=0; k<sizeY; ++k)
	{
		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				if(_materialCube[(k*sizeX*sizeZ)+(i*sizeZ)+j] != Material)
					buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;
			}
		}
	}


	short * ptr = buffer;
	for(int i=0; i<sizeY; ++i)
	{
		SearchFloors(ptr, i, _planes, sizeX, sizeY, sizeZ, Material);
		ptr += sizeX*sizeZ;
	}


	delete[] buffer;
}


/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchFloorsHidden(int sizeX, int sizeY, int sizeZ)
{
	_planeshidden.clear();

	short * buffer = new short[sizeX*sizeY*sizeZ];
	memcpy ( buffer, _physicCube, sizeX*sizeY*sizeZ*sizeof(short) );


	for(int k=1; k<(sizeY-1); ++k)
	{
		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				if(_physicCube[((k-1)*sizeX*sizeZ)+(i*sizeZ)+j] != 0 )
					buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;

				if( _physicCube[((k+1)*sizeX*sizeZ)+(i*sizeZ)+j] > 1)
					buffer[(k*sizeX*sizeZ)+(i*sizeZ)+j] = 0;
			}
		}
	}


	short * ptr = buffer;
	for(int i=0; i<sizeY; ++i)
	{
		SearchFloors(ptr, i, _planeshidden, sizeX, sizeY, sizeZ, 0);
		ptr += sizeX*sizeZ;
	}


	delete[] buffer;
}





/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchFloors(short * thisY, int Y, std::vector<PlaneInfo> &planes, 
									int sizeX, int sizeY, int sizeZ, short material, int minareasize)
{
	bool found = true;

	while(found)
	{
		short * ptr = thisY;
		int maxsize = 0;
		int maxsX = 0;
		int maxsZ = 0;
		int maxeX = 0;
		int maxeZ = 0;
		found = false;

		for(int i=0; i<sizeX; ++i)
		{
			for(int j=0; j<sizeZ; ++j)
			{
				int startX, startZ, endX, endZ;
				int areasize = SearchMaxFloor(ptr, i, j, startX, startZ, endX, endZ, sizeX, sizeY, sizeZ);
				if(areasize > 0)
				{
					bool issquare = ((endX-startX) == (endZ-startZ));
					if(issquare)
					{
						if(areasize >= maxsize)
						{
							maxsize = areasize;
							maxsX = startX;
							maxsZ = startZ;
							maxeX = endX;
							maxeZ = endZ;
							found = true;
						}
					}
					else
					{
						if(areasize > maxsize)
						{
							maxsize = areasize;
							maxsX = startX;
							maxsZ = startZ;
							maxeX = endX;
							maxeZ = endZ;
							found = true;
						}
					}
				}

				++ptr;
			}
		}

		if(found)
		{
			PlaneInfo pif;
			pif.StartX = maxsX;
			pif.StartY = Y;
			pif.StartZ = maxsZ;

			pif.EndX = maxeX;
			pif.EndY = Y;
			pif.EndZ = maxeZ;
			pif.material = material;

			if(maxsize >= minareasize)
				planes.push_back(pif);

			for(int i=maxsX; i<maxeX; ++i)
			{
				for(int j=maxsZ; j<maxeZ; ++j)
				{
					thisY[i*sizeZ+j] = 0;
				}
			}
		}
	}

}


/*
--------------------------------------------------------------------------------------------------
look for floors  in the map
--------------------------------------------------------------------------------------------------
*/
int PhysicHandler::SearchMaxFloor(short * center, int idxX, int idxZ,
									int &startX, int &startZ,
									int &endX, int &endZ, int sizeX, int sizeY, int sizeZ)
{
	if(*center != 1)
		return 0;

	int squaresize = 1;

	// look for the biggest centered square
	while(true)
	{
		//check first corner
		--idxX;
		--idxZ;
		++squaresize;
		center -= (sizeZ+1);

		if((idxX >= 0) && (idxZ >= 0))
		{
			if(IsSolidHorLine(center, squaresize, sizeX, sizeY, sizeZ))
			{
				if(IsSolidVerLine(center, squaresize, sizeX, sizeY, sizeZ))
				{
					continue;
				}
			}
		}

		++idxX;
		++idxZ;
		--squaresize;
		center += (sizeZ+1);
		break;
	}


	int squaresizeX = squaresize;
	int squaresizeZ = squaresize;


	int maxX = idxX;
	int maxsizeX = squaresizeX;
	int maxZ = idxZ;
	int maxsizeZ = squaresizeZ;


	// try to build bigger rectangles on X
	{
		short * ptr = center;

		while(true)
		{
			ptr -= sizeZ;
			--maxX;
			++maxsizeX;
			if(maxX >= 0)
			{
				if(IsSolidHorLine(ptr, squaresizeZ, sizeX, sizeY, sizeZ))
					continue;
			}

			ptr += sizeZ;
			++maxX;
			--maxsizeX;
			break;
		}


		ptr += (maxsizeX-1)*sizeZ;
		while(true)
		{
			ptr += sizeZ;
			++maxsizeX;
			if((maxX+maxsizeX) <= sizeX)
			{
				if(IsSolidHorLine(ptr, squaresizeZ, sizeX, sizeY, sizeZ))
					continue;
			}

			--maxsizeX;
			break;
		}

	}


	// try to build bigger rectangles on Z
	{
		short * ptr = center;

		while(true)
		{
			--ptr;
			--maxZ;
			++maxsizeZ;
			if(maxZ >= 0)
			{
				if(IsSolidVerLine(ptr, squaresizeX, sizeX, sizeY, sizeZ))
					continue;
			}

			++ptr;
			++maxZ;
			--maxsizeZ;
			break;
		}



		ptr += (maxsizeZ-1);
		while(true)
		{
			++ptr;
			++maxsizeZ;
			if((maxZ+maxsizeZ) <= sizeZ)
			{
				if(IsSolidVerLine(ptr, squaresizeX, sizeX, sizeY, sizeZ))
					continue;
			}

			--maxsizeZ;
			break;
		}	
	}


	if(maxsizeX >= maxsizeZ)
	{
		idxX=maxX;
		squaresizeX=maxsizeX;
	}
	else
	{
		idxZ=maxZ;
		squaresizeZ=maxsizeZ;
	}



	startX=idxX;
	startZ=idxZ;
	endX=startX+squaresizeX;
	endZ=startZ+squaresizeZ;


	return (squaresizeX*squaresizeZ);
}



/*
--------------------------------------------------------------------------------------------------
IsSolidHorLine
--------------------------------------------------------------------------------------------------
*/
bool PhysicHandler::IsSolidHorLine(short * start, int size, int sizeX, int sizeY, int sizeZ)
{
	for(int i=0; i<size; ++i)
	{
		if(*start != 1)
			return false;

		++start;
	}
	
	return true;
}

/*
--------------------------------------------------------------------------------------------------
IsSolidVerLine
--------------------------------------------------------------------------------------------------
*/
bool PhysicHandler::IsSolidVerLine(short * start, int size, int sizeX, int sizeY, int sizeZ)
{
	for(int i=0; i<size; ++i)
	{
		if(*start != 1)
			return false;

		start+=sizeZ;
	}
	
	return true;
}






/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
int PhysicHandler::SearchMaxTexture(short * center, int idxX, int idxY,
										int &startX, int &startY,
										int &endX, int &endY, int sizeX, int sizeY, TextInfo * txi)
{
	if(*center != txi->GetTexture(idxX, idxY))
		return 0;

	int squaresize = 1;

	// look for the biggest centered square
	while(true)
	{
		//check first corner
		--idxX;
		--idxY;
		++squaresize;
		center -= (sizeY+1);

		if((idxX >= 0) && (idxY >= 0))
		{
			if(IsTexHorLine(center, squaresize, sizeX, sizeY, idxX, idxY, txi))
			{
				if(IsTexVerLine(center, squaresize, sizeX, sizeY, idxX, idxY, txi))
				{
					continue;
				}
			}
		}

		++idxX;
		++idxY;
		--squaresize;
		center += (sizeY+1);
		break;
	}


	int squaresizeX = squaresize;
	int squaresizeY = squaresize;


	int maxX = idxX;
	int maxsizeX = squaresizeX;
	int maxY = idxY;
	int maxsizeY = squaresizeY;


	// try to build bigger rectangles on X
	{
		short * ptr = center;

		while(true)
		{
			ptr -= sizeY;
			--maxX;
			++maxsizeX;
			if(maxX >= 0)
			{
				if(IsTexHorLine(ptr, squaresizeY, sizeX, sizeY, maxX, idxY, txi))
					continue;
			}

			ptr += sizeY;
			++maxX;
			--maxsizeX;
			break;
		}


		ptr += (maxsizeX-1)*sizeY;
		while(true)
		{
			ptr += sizeY;
			++maxsizeX;
			if((maxX+maxsizeX) <= sizeX)
			{
				if(IsTexHorLine(ptr, squaresizeY, sizeX, sizeY, maxX, idxY, txi))
					continue;
			}

			--maxsizeX;
			break;
		}

	}


	// try to build bigger rectangles on Y
	{
		short * ptr = center;

		while(true)
		{
			--ptr;
			--maxY;
			++maxsizeY;
			if(maxY >= 0)
			{
				if(IsTexVerLine(ptr, squaresizeX, sizeX, sizeY, idxX, maxY, txi))
					continue;
			}

			++ptr;
			++maxY;
			--maxsizeY;
			break;
		}



		ptr += (maxsizeY-1);
		while(true)
		{
			++ptr;
			++maxsizeY;
			if((maxY+maxsizeY) <= sizeY)
			{
				if(IsTexVerLine(ptr, squaresizeX, sizeX, sizeY, idxX, maxY, txi))
					continue;
			}

			--maxsizeY;
			break;
		}	
	}


	if(maxsizeX >= maxsizeY)
	{
		idxX=maxX;
		squaresizeX=maxsizeX;
	}
	else
	{
		idxY=maxY;
		squaresizeY=maxsizeY;
	}



	startX=idxX;
	startY=idxY;
	endX=startX+squaresizeX;
	endY=startY+squaresizeY;


	return (squaresizeX*squaresizeY);
}



/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
bool PhysicHandler::IsTexHorLine(short * start, int size, int sizeX, int sizeY, 
								 int idxX, int idxY, TextInfo * txi)
{
	for(int i=0; i<size; ++i)
	{
		if(*start != txi->GetTexture(idxX, idxY))
			return false;

		++start;
		++idxY;
	}
	
	return true;
}



/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
bool PhysicHandler::IsTexVerLine(short * start, int size, int sizeX, int sizeY, 
								 int idxX, int idxY, TextInfo * txi)
{
	for(int i=0; i<size; ++i)
	{
		if(*start != txi->GetTexture(idxX, idxY))
			return false;

		start+=sizeY;
		++idxX;
	}
	
	return true;
}



/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchStairs()
{
	_stairs.clear();
	_cornerstairs.clear();

	short * generalbuffer = new short[_sizeX*_sizeY*_sizeZ];
	memcpy ( generalbuffer, _physicCube, _sizeX*_sizeY*_sizeZ*sizeof(short) );
	for(int k=0; k<_sizeY; ++k)
	{
		for(int i=0; i<_sizeX; ++i)
		{
			for(int j=0; j<_sizeZ; ++j)
			{
				if(generalbuffer[(k*_sizeX*_sizeZ)+(i*_sizeZ)+j] == 1)
					generalbuffer[(k*_sizeX*_sizeZ)+(i*_sizeZ)+j] = 0;
			}
		}
	}
	for(int k=0; k<_sizeY; ++k)
	{
		for(int i=0; i<_sizeX; ++i)
		{
			for(int j=0; j<_sizeZ; ++j)
			{
				if((k+1)<_sizeY)
				{
					if(generalbuffer[((k+1)*_sizeX*_sizeZ)+(i*_sizeZ)+j] != 0)
						generalbuffer[(k*_sizeX*_sizeZ)+(i*_sizeZ)+j] = 0;
				}
			}
		}
	}


	for(short i=0; i<20; ++i)
	{
		short Material = i;

		short * buffer = new short[_sizeX*_sizeY*_sizeZ];
		memcpy ( buffer, generalbuffer, _sizeX*_sizeY*_sizeZ*sizeof(short) );


		for(int k=0; k<_sizeY; ++k)
		{
			for(int i=0; i<_sizeX; ++i)
			{
				for(int j=0; j<_sizeZ; ++j)
				{
					if(_materialCube[(k*_sizeX*_sizeZ)+(i*_sizeZ)+j] != Material)
						buffer[(k*_sizeX*_sizeZ)+(i*_sizeZ)+j] = 0;
				}
			}
		}

		SearchCornerStairsWithMaterial(buffer, generalbuffer, _sizeX, _sizeY, _sizeZ, _cornerstairs, Material);
		delete[] buffer;
	}


	for(short i=0; i<20; ++i)
	{
		short Material = i;

		short * buffer = new short[_sizeX*_sizeY*_sizeZ];
		memcpy ( buffer, generalbuffer, _sizeX*_sizeY*_sizeZ*sizeof(short) );


		for(int k=0; k<_sizeY; ++k)
		{
			for(int i=0; i<_sizeX; ++i)
			{
				for(int j=0; j<_sizeZ; ++j)
				{
					if(_materialCube[(k*_sizeX*_sizeZ)+(i*_sizeZ)+j] != Material)
						buffer[(k*_sizeX*_sizeZ)+(i*_sizeZ)+j] = 0;
				}
			}
		}

		SearchStairsWithMaterial(buffer, _sizeX, _sizeY, _sizeZ, _stairs, Material);
		delete[] buffer;
	}
	

	delete generalbuffer;
}


/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchCornerStairsWithMaterial(short * start, short * tomodify, int sizeX, 
												   int sizeY, int sizeZ, 
													std::vector<CornerStairInfo> & stairs, short Material)
{
	for(int Y=0; Y< sizeY; ++Y)
	{
		for(int X=0; X< sizeX; ++X)
		{
			for(int Z=0; Z< sizeZ; ++Z)
			{
				Search6CornerStairs(start, tomodify, sizeX, sizeY, sizeZ, X, Y, Z, stairs, Material);
				Search7CornerStairs(start, tomodify, sizeX, sizeY, sizeZ, X, Y, Z, stairs, Material);
				Search8CornerStairs(start, tomodify, sizeX, sizeY, sizeZ, X, Y, Z, stairs, Material);
				Search9CornerStairs(start, tomodify, sizeX, sizeY, sizeZ, X, Y, Z, stairs, Material);
				Search10CornerStairs(start, tomodify, sizeX, sizeY, sizeZ, X, Y, Z, stairs, Material);
				Search11CornerStairs(start, tomodify, sizeX, sizeY, sizeZ, X, Y, Z, stairs, Material);
				Search12CornerStairs(start, tomodify, sizeX, sizeY, sizeZ, X, Y, Z, stairs, Material);
				Search13CornerStairs(start, tomodify, sizeX, sizeY, sizeZ, X, Y, Z, stairs, Material);
			}
		}
	}

}


/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SearchStairsWithMaterial(short * start, int sizeX, int sizeY, int sizeZ,
												std::vector<StairInfo> & stairs, short Material)
{
	for(int Y=0; Y< sizeY; ++Y)
	{
		for(int X=0; X< sizeX; ++X)
		{
			for(int Z=0; Z< sizeZ; ++Z)
			{
				StairInfo stri = PhysicHandler::FindStairUp(start, X, Y, Z, sizeX, sizeY, sizeZ, true);
				
				if(stri.length > 0)
				{
					if(stri.type == 2 || stri.type == 5)
					{
						for(int lZ=Z+1; lZ< sizeZ; ++lZ)
						{
							StairInfo stri2 = PhysicHandler::FindStairUp(start, X, Y, lZ, sizeX, sizeY, sizeZ, false);
							if(stri2.length == stri.length && stri2.type == stri.type)
							{
								stri.C2X = stri2.C2X;
								stri.C2Y = stri2.C2Y;
								stri.C2Z = stri2.C2Z;

								stri.C4X = stri2.C4X;
								stri.C4Y = stri2.C4Y;
								stri.C4Z = stri2.C4Z;

								 PhysicHandler::FindStairUp(start, X, Y, lZ, sizeX, sizeY, sizeZ, true);
							}
							else
								break;
						}
					}

					if(stri.type == 3 || stri.type == 4)
					{
						for(int lX=X+1; lX< sizeX; ++lX)
						{
							StairInfo stri2 = PhysicHandler::FindStairUp(start, lX, Y, Z, sizeX, sizeY, sizeZ, false);
							if(stri2.length == stri.length && stri2.type == stri.type)
							{
								stri.C2X = stri2.C2X;
								stri.C2Y = stri2.C2Y;
								stri.C2Z = stri2.C2Z;

								stri.C4X = stri2.C4X;
								stri.C4Y = stri2.C4Y;
								stri.C4Z = stri2.C4Z;

								 PhysicHandler::FindStairUp(start, lX, Y, Z, sizeX, sizeY, sizeZ, true);
							}
							else
								break;
						}
					}

					stri.material = Material;
					stairs.push_back(stri);
				}
			}
		}
	}


}


/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
StairInfo PhysicHandler::FindStairUp(short * start, int idX, int idY, int idZ,  
								int sizeX, int sizeY, int sizeZ, bool overwrite)
{
	StairInfo res;
	res.length = 0;

	int proto = start[idY*sizeX*sizeZ + idX*sizeZ + idZ];
	if(proto == 2 || proto == 3 || proto == 4 || proto == 5)
	{
		++res.length;
		res.type = proto;

		if(overwrite)
			start[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;

		int offsetX = 0;
		int offsetZ = 0;
		int minoffsetX = 0;
		int minoffsetZ = 0;


		if(res.type == 2)
			++offsetZ;
		if(res.type == 3)
			++offsetX;
		if(res.type == 4)
		{
			++offsetX;
			++minoffsetZ;
		}
		if(res.type == 5)
		{
			++offsetZ;
			++minoffsetX;
		}


		res.C1X = idX+minoffsetX;
		res.C1Y = idY-1;
		res.C1Z = idZ+minoffsetZ;

		res.C2X = idX+offsetX+minoffsetX;
		res.C2Y = idY-1;
		res.C2Z = idZ+offsetZ+minoffsetZ;

		res.C3X = 0+minoffsetX;
		res.C3Y = -1;
		res.C3Z = 0+minoffsetZ;

		res.C4X = offsetX+minoffsetX;
		res.C4Y = -1;
		res.C4Z = offsetZ+minoffsetZ;


		while(true)
		{
			++idY;

			if(res.type == 2)
				++idX;
			if(res.type == 3)
				++idZ;
			if(res.type == 4)
				--idZ;
			if(res.type == 5)
				--idX;

			if((idY) < sizeY && (idY) >= 0)
			{
				if((idX) < sizeX && (idX) >= 0)
				{
					if((idZ) < sizeZ && (idZ) >= 0)
					{
						if(start[idY*sizeX*sizeZ + idX*sizeZ + idZ] == res.type)
						{
							if(overwrite)
								start[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;
							++res.length;
							continue;
						}
					}
				}
			}
			break;
		}


		res.C3X += idX;
		res.C3Y += idY;
		res.C3Z += idZ;	

		res.C4X += idX;
		res.C4Y += idY;
		res.C4Z += idZ;
	}

	return res;
}




/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::Search6CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material)
{
	if(start[idY*sizeX*sizeZ + idX*sizeZ + idZ] == 6)
	{
		tomodify[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;
		start[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;

		CornerStairInfo cif;
		cif.C1X = idX;
		cif.C1Y = idY-1;
		cif.C1Z = idZ;

		cif.C2X = idX+1;
		cif.C2Y = idY;
		cif.C2Z = idZ+1;

		cif.C3X = idX;
		cif.C3Y = idY;
		cif.C3Z = idZ+1;

		CornerStairInfo cif2;
		cif2.C1X = idX;
		cif2.C1Y = idY-1;
		cif2.C1Z = idZ;

		cif2.C2X = idX+1;
		cif2.C2Y = idY;
		cif2.C2Z = idZ+1;

		cif2.C3X = idX+1;
		cif2.C3Y = idY;
		cif2.C3Z = idZ;

		cif.material = Material;
		cif2.material = Material;

		int localX=idX;
		int localY=idY;
		int localZ=idZ;

		int keepX1=idX;
		int keepY1=idY;
		int keepZ1=idZ;

		int keepX2=idX;
		int keepY2=idY;
		int keepZ2=idZ;


		while(true)
		{
			++localX;
			++localY;
			++localZ;
			if(localY< sizeY)
			{
				if(localX< sizeX)
				{
					if(localZ< sizeZ)
					{
						if(start[localY*sizeX*sizeZ + localX*sizeZ + localZ] == 6)
						{
							tomodify[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;
							start[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;

							//check left triangle side
							{
								bool truetriangle = true;
								for(int tmpX=keepX1; tmpX<localX; ++tmpX)
								{
									if(start[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] != 3)
										truetriangle = false;
								}

								if(truetriangle)
								{
									for(int tmpX=keepX1; tmpX<localX; ++tmpX)
									{
										tomodify[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
										start[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
									}

									cif.C2X = localX+1;
									cif.C2Y = localY;
									cif.C2Z = localZ+1;

									cif.C3Y = localY;
									cif.C3Z = localZ+1;
								}
								else
								{
									stairs.push_back(cif);
									cif.C1X = localX;
									cif.C1Y = localY-1;
									cif.C1Z = localZ;

									cif.C2X = localX+1;
									cif.C2Y = localY;
									cif.C2Z = localZ+1;

									cif.C3X = localX;
									cif.C3Y = localY;
									cif.C3Z = localZ+1;

									keepX1 = localX;
									keepY1 = localY;
									keepZ1 = localY;
								}
							}

							//check right triangle side
							{
								bool truetriangle = true;
								for(int tmpZ=keepZ2; tmpZ<localZ; ++tmpZ)
								{
									if(start[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] != 2)
										truetriangle = false;
								}

								if(truetriangle)
								{
									for(int tmpZ=keepZ2; tmpZ<localZ; ++tmpZ)
									{
										tomodify[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
										start[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
									}

									cif2.C2X = localX+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ+1;

									cif2.C3X = localX+1;
									cif2.C3Y = localY;
								}
								else
								{
									stairs.push_back(cif2);
									cif2.C1X = localX;
									cif2.C1Y = localY-1;
									cif2.C1Z = localZ;

									cif2.C2X = localX+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ+1;

									cif2.C3X = localX+1;
									cif2.C3Y = localY;
									cif2.C3Z = localZ;

									keepX2 = localX;
									keepY2 = localY;
									keepZ2 = localY;
								}
							}

							continue;
						}
					}
				}
			}

			stairs.push_back(cif);
			stairs.push_back(cif2);
			break;
		}
	}
}



/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::Search7CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material)
{
	if(start[idY*sizeX*sizeZ + idX*sizeZ + idZ] == 7)
	{
		tomodify[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;
		start[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;

		CornerStairInfo cif;
		cif.C1X = idX+1;
		cif.C1Y = idY-1;
		cif.C1Z = idZ+1;

		cif.C2X = idX-1+1;
		cif.C2Y = idY;
		cif.C2Z = idZ-1+1;

		cif.C3X = idX+1;
		cif.C3Y = idY;
		cif.C3Z = idZ-1+1;

		CornerStairInfo cif2;
		cif2.C1X = idX+1;
		cif2.C1Y = idY-1;
		cif2.C1Z = idZ+1;

		cif2.C2X = idX-1+1;
		cif2.C2Y = idY;
		cif2.C2Z = idZ-1+1;

		cif2.C3X = idX-1+1;
		cif2.C3Y = idY;
		cif2.C3Z = idZ+1;

		cif.material = Material;
		cif2.material = Material;


		int localX=idX;
		int localY=idY;
		int localZ=idZ;

		int keepX1=idX;
		int keepY1=idY;
		int keepZ1=idZ;

		int keepX2=idX;
		int keepY2=idY;
		int keepZ2=idZ;


		while(true)
		{
			--localX;
			++localY;
			--localZ;
			if(localY< sizeY)
			{
				if(localX>= 0)
				{
					if(localZ>= 0)
					{
						if(start[localY*sizeX*sizeZ + localX*sizeZ + localZ] == 7)
						{
							tomodify[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;
							start[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;

							//check left triangle side
							{
								bool truetriangle = true;
								for(int tmpX=keepX1; tmpX>localX; --tmpX)
								{
									if(start[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] != 4)
										truetriangle = false;
								}

								if(truetriangle)
								{
									for(int tmpX=keepX1; tmpX>localX; --tmpX)
									{
										tomodify[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
										start[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
									}

									cif.C2X = localX-1+1;
									cif.C2Y = localY;
									cif.C2Z = localZ-1+1;

									cif.C3Y = localY;
									cif.C3Z = localZ-1+1;
								}
								else
								{
									stairs.push_back(cif);
									cif.C1X = localX+1;
									cif.C1Y = localY-1;
									cif.C1Z = localZ+1;

									cif.C2X = localX-1+1;
									cif.C2Y = localY;
									cif.C2Z = localZ-1+1;

									cif.C3X = localX+1;
									cif.C3Y = localY;
									cif.C3Z = localZ-1+1;

									keepX1 = localX;
									keepY1 = localY;
									keepZ1 = localY;
								}
							}

							//check right triangle side
							{
								bool truetriangle = true;
								for(int tmpZ=keepZ2; tmpZ>localZ; --tmpZ)
								{
									if(start[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] != 5)
										truetriangle = false;
								}

								if(truetriangle)
								{
									for(int tmpZ=keepZ2; tmpZ>localZ; --tmpZ)
									{
										tomodify[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
										start[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
									}

									cif2.C2X = localX-1+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ-1+1;

									cif2.C3X = localX-1+1;
									cif2.C3Y = localY;
								}
								else
								{
									stairs.push_back(cif2);
									cif2.C1X = localX+1;
									cif2.C1Y = localY-1;
									cif2.C1Z = localZ+1;

									cif2.C2X = localX-1+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ-1+1;

									cif2.C3X = localX-1+1;
									cif2.C3Y = localY;
									cif2.C3Z = localZ+1;

									keepX2 = localX;
									keepY2 = localY;
									keepZ2 = localY;
								}
							}

							continue;
						}
					}
				}
			}

			stairs.push_back(cif);
			stairs.push_back(cif2);
			break;
		}
	}
}





/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::Search8CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material)
{
	if(start[idY*sizeX*sizeZ + idX*sizeZ + idZ] == 8)
	{
		tomodify[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;
		start[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;

		CornerStairInfo cif;
		cif.C1X = idX;
		cif.C1Y = idY-1;
		cif.C1Z = idZ+1;

		cif.C2X = idX+1;
		cif.C2Y = idY;
		cif.C2Z = idZ;

		cif.C3X = idX+1;
		cif.C3Y = idY;
		cif.C3Z = idZ+1;

		CornerStairInfo cif2;
		cif2.C1X = idX;
		cif2.C1Y = idY-1;
		cif2.C1Z = idZ+1;

		cif2.C2X = idX+1;
		cif2.C2Y = idY;
		cif2.C2Z = idZ;

		cif2.C3X = idX;
		cif2.C3Y = idY;
		cif2.C3Z = idZ;

		cif.material = Material;
		cif2.material = Material;


		int localX=idX;
		int localY=idY;
		int localZ=idZ;

		int keepX1=idX;
		int keepY1=idY;
		int keepZ1=idZ;

		int keepX2=idX;
		int keepY2=idY;
		int keepZ2=idZ;


		while(true)
		{
			++localX;
			++localY;
			--localZ;
			if(localY< sizeY)
			{
				if(localX< sizeX)
				{
					if(localZ>= 0)
					{
						if(start[localY*sizeX*sizeZ + localX*sizeZ + localZ] == 8)
						{
							tomodify[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;
							start[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;

							//check left triangle side
							{
								bool truetriangle = true;
								for(int tmpX=keepX1; tmpX<localX; ++tmpX)
								{
									if(start[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] != 4)
										truetriangle = false;
								}

								if(truetriangle)
								{
									for(int tmpX=keepX1; tmpX<localX; ++tmpX)
									{
										tomodify[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
										start[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
									}

									cif2.C2X = localX+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ;

									cif2.C3Z = localZ;
									cif2.C3Y = localY;

								}
								else
								{
									stairs.push_back(cif2);
									cif2.C1X = localX;
									cif2.C1Y = localY-1;
									cif2.C1Z = localZ+1;

									cif2.C2X = localX+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ;

									cif2.C3X = localX;
									cif2.C3Y = localY;
									cif2.C3Z = localZ;

									keepX1 = localX;
									keepY1 = localY;
									keepZ1 = localY;
								}
							}

							//check right triangle side
							{
								bool truetriangle = true;
								for(int tmpZ=keepZ2; tmpZ>localZ; --tmpZ)
								{
									if(start[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] != 2)
										truetriangle = false;
								}

								if(truetriangle)
								{
									for(int tmpZ=keepZ2; tmpZ>localZ; --tmpZ)
									{
										tomodify[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
										start[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
									}

									cif.C2X = localX+1;
									cif.C2Y = localY;
									cif.C2Z = localZ;

									cif.C3X = localX+1;
									cif.C3Y = localY;
								}
								else
								{
									stairs.push_back(cif);
									cif.C1X = localX;
									cif.C1Y = localY-1;
									cif.C1Z = localZ+1;

									cif.C2X = localX+1;
									cif.C2Y = localY;
									cif.C2Z = localZ;

									cif.C3X = localX+1;
									cif.C3Y = localY;
									cif.C3Z = localZ+1;

									keepX2 = localX;
									keepY2 = localY;
									keepZ2 = localY;
								}
							}

							continue;
						}
					}
				}
			}

			stairs.push_back(cif);
			stairs.push_back(cif2);
			break;
		}
	}
}



/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::Search9CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material)
{
	if(start[idY*sizeX*sizeZ + idX*sizeZ + idZ] == 9)
	{
		tomodify[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;
		start[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;

		CornerStairInfo cif;
		cif.C1X = idX;
		cif.C1Y = idY;
		cif.C1Z = idZ+1;

		cif.C2X = idX+1;
		cif.C2Y = idY-1;
		cif.C2Z = idZ;

		cif.C3X = idX+1;
		cif.C3Y = idY;
		cif.C3Z = idZ+1;

		CornerStairInfo cif2;
		cif2.C1X = idX;
		cif2.C1Y = idY;
		cif2.C1Z = idZ+1;

		cif2.C2X = idX+1;
		cif2.C2Y = idY-1;
		cif2.C2Z = idZ;

		cif2.C3X = idX;
		cif2.C3Y = idY;
		cif2.C3Z = idZ;

		cif.material = Material;
		cif2.material = Material;


		int localX=idX;
		int localY=idY;
		int localZ=idZ;

		int keepX1=idX;
		int keepY1=idY;
		int keepZ1=idZ;

		int keepX2=idX;
		int keepY2=idY;
		int keepZ2=idZ;


		while(true)
		{
			--localX;
			++localY;
			++localZ;
			if(localY< sizeY)
			{
				if(localX>= 0)
				{
					if(localZ>= 0)
					{
						if(start[localY*sizeX*sizeZ + localX*sizeZ + localZ] == 9)
						{
							tomodify[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;
							start[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;

							//check left triangle side
							{
								bool truetriangle = true;
								for(int tmpX=keepX1; tmpX>localX; --tmpX)
								{
									if(start[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] != 3)
										truetriangle = false;
								}

								if(truetriangle)
								{
									for(int tmpX=keepX1; tmpX>localX; --tmpX)
									{
										tomodify[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
										start[localY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
									}

									cif.C1X = localX;
									cif.C1Y = localY;
									cif.C1Z = localZ+1;

									cif.C3Y = localY;
									cif.C3Z = localZ+1;
								}
								else
								{
									stairs.push_back(cif);
									cif.C1X = localX;
									cif.C1Y = localY;
									cif.C1Z = localZ+1;

									cif.C2X = localX+1;
									cif.C2Y = localY-1;
									cif.C2Z = localZ;

									cif.C3X = localX+1;
									cif.C3Y = localY;
									cif.C3Z = localZ+1;

									keepX1 = localX;
									keepY1 = localY;
									keepZ1 = localY;
								}
							}

							//check right triangle side
							{
								bool truetriangle = true;
								for(int tmpZ=keepZ2; tmpZ<localZ; ++tmpZ)
								{
									if(start[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] != 5)
										truetriangle = false;
								}

								if(truetriangle)
								{
									for(int tmpZ=keepZ2; tmpZ<localZ; ++tmpZ)
									{
										tomodify[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
										start[localY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
									}

									cif2.C1X = localX;
									cif2.C1Y = localY;
									cif2.C1Z = localZ+1;

									cif2.C3X = localX;
									cif2.C3Y = localY;
								}
								else
								{
									stairs.push_back(cif2);
									cif2.C1X = localX;
									cif2.C1Y = localY;
									cif2.C1Z = localZ+1;

									cif2.C2X = localX+1;
									cif2.C2Y = localY-1;
									cif2.C2Z = localZ;

									cif2.C3X = localX;
									cif2.C3Y = localY;
									cif2.C3Z = localZ;

									keepX2 = localX;
									keepY2 = localY;
									keepZ2 = localY;
								}
							}

							continue;
						}
					}
				}
			}

			stairs.push_back(cif);
			stairs.push_back(cif2);
			break;
		}
	}
}





/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::Search10CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material)
{
	if(start[idY*sizeX*sizeZ + idX*sizeZ + idZ] == 10)
	{
		tomodify[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;
		start[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;

		CornerStairInfo cif;
		cif.C1X = idX;
		cif.C1Y = idY-1;
		cif.C1Z = idZ;

		cif.C2X = idX+1;
		cif.C2Y = idY;
		cif.C2Z = idZ+1;

		cif.C3X = idX;
		cif.C3Y = idY-1;
		cif.C3Z = idZ+1;

		CornerStairInfo cif2;
		cif2.C1X = idX;
		cif2.C1Y = idY-1;
		cif2.C1Z = idZ;

		cif2.C2X = idX+1;
		cif2.C2Y = idY;
		cif2.C2Z = idZ+1;

		cif2.C3X = idX+1;
		cif2.C3Y = idY-1;
		cif2.C3Z = idZ;

		cif.material = Material;
		cif2.material = Material;


		int localX=idX;
		int localY=idY;
		int localZ=idZ;

		int keepX1=idX;
		int keepY1=idY;
		int keepZ1=idZ;

		int keepX2=idX;
		int keepY2=idY;
		int keepZ2=idZ;

		while(true)
		{
			++localX;
			++localY;
			++localZ;
			if(localY< sizeY)
			{
				if(localX< sizeX)
				{
					if(localZ< sizeZ)
					{
						if(start[localY*sizeX*sizeZ + localX*sizeZ + localZ] == 10)
						{
							tomodify[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;
							start[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;

							//check left triangle side
							{
								bool truetriangle = true;
								int tmpY=keepY1;
								for(int tmpX=keepX1; tmpX<localX; ++tmpX, ++tmpY)
								{
									if(start[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] != 2)
										truetriangle = false;
								}

								if(truetriangle)
								{
									int tmpY=keepY1;
									for(int tmpX=keepX1; tmpX<localX; ++tmpX, ++tmpY)
									{
										tomodify[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
										start[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
									}

									cif.C2X = localX+1;
									cif.C2Y = localY;
									cif.C2Z = localZ+1;

									cif.C3Z = localZ+1;
								}
								else
								{
									stairs.push_back(cif);
									cif.C1X = localX;
									cif.C1Y = localY-1;
									cif.C1Z = localZ;

									cif.C2X = localX+1;
									cif.C2Y = localY;
									cif.C2Z = localZ+1;

									cif.C3X = localX;
									cif.C3Y = localY-1;
									cif.C3Z = localZ+1;

									keepX1 = localX;
									keepY1 = localY;
									keepZ1 = localY;
								}
							}

							//check right triangle side
							{
								bool truetriangle = true;
								int tmpY=keepY2;
								for(int tmpZ=keepZ2; tmpZ<localZ; ++tmpZ, ++tmpY)
								{
									if(start[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] != 3)
										truetriangle = false;
								}

								if(truetriangle)
								{
									int tmpY=keepY2;
									for(int tmpZ=keepZ2; tmpZ<localZ; ++tmpZ, ++tmpY)
									{
										tomodify[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
										start[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
									}

									cif2.C2X = localX+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ+1;

									cif2.C3X = localX+1;
								}
								else
								{
									stairs.push_back(cif2);
									cif2.C1X = localX;
									cif2.C1Y = localY-1;
									cif2.C1Z = localZ;

									cif2.C2X = localX+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ+1;

									cif2.C3X = localX+1;
									cif2.C3Y = localY-1;
									cif2.C3Z = localZ;

									keepX2 = localX;
									keepY2 = localY;
									keepZ2 = localY;
								}
							}

							continue;
						}
					}
				}
			}

			stairs.push_back(cif);
			stairs.push_back(cif2);
			break;
		}
	}
}



/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::Search11CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material)
{
	if(start[idY*sizeX*sizeZ + idX*sizeZ + idZ] == 11)
	{
		tomodify[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;
		start[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;

		CornerStairInfo cif;
		cif.C1X = idX+1;
		cif.C1Y = idY-1;
		cif.C1Z = idZ+1;

		cif.C2X = idX-1+1;
		cif.C2Y = idY;
		cif.C2Z = idZ-1+1;

		cif.C3X = idX+1;
		cif.C3Y = idY-1;
		cif.C3Z = idZ-1+1;

		CornerStairInfo cif2;
		cif2.C1X = idX+1;
		cif2.C1Y = idY-1;
		cif2.C1Z = idZ+1;

		cif2.C2X = idX-1+1;
		cif2.C2Y = idY;
		cif2.C2Z = idZ-1+1;

		cif2.C3X = idX-1+1;
		cif2.C3Y = idY-1;
		cif2.C3Z = idZ+1;

		cif.material = Material;
		cif2.material = Material;

		int localX=idX;
		int localY=idY;
		int localZ=idZ;

		int keepX1=idX;
		int keepY1=idY;
		int keepZ1=idZ;

		int keepX2=idX;
		int keepY2=idY;
		int keepZ2=idZ;

		while(true)
		{
			--localX;
			++localY;
			--localZ;
			if(localY< sizeY)
			{
				if(localX>= 0)
				{
					if(localZ>= 0)
					{
						if(start[localY*sizeX*sizeZ + localX*sizeZ + localZ] == 11)
						{
							tomodify[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;
							start[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;

							//check left triangle side
							{
								bool truetriangle = true;
								int tmpY=keepY1;
								for(int tmpX=keepX1; tmpX>localX; --tmpX, ++tmpY)
								{
									if(start[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] != 5)
										truetriangle = false;
								}

								if(truetriangle)
								{
									int tmpY=keepY1;
									for(int tmpX=keepX1; tmpX>localX; --tmpX, ++tmpY)
									{
										tomodify[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
										start[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
									}

									cif.C2X = localX-1+1;
									cif.C2Y = localY;
									cif.C2Z = localZ-1+1;

									cif.C3Z = localZ-1+1;
								}
								else
								{
									stairs.push_back(cif);
									cif.C1X = localX+1;
									cif.C1Y = localY-1;
									cif.C1Z = localZ+1;

									cif.C2X = localX-1+1;
									cif.C2Y = localY;
									cif.C2Z = localZ-1+1;

									cif.C3X = localX+1;
									cif.C3Y = localY-1;
									cif.C3Z = localZ-1+1;

									keepX1 = localX;
									keepY1 = localY;
									keepZ1 = localY;
								}
							}

							//check right triangle side
							{
								bool truetriangle = true;
								int tmpY=keepY2;
								for(int tmpZ=keepZ2; tmpZ>localZ; --tmpZ, ++tmpY)
								{
									if(start[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] != 4)
										truetriangle = false;
								}

								if(truetriangle)
								{
									int tmpY=keepY2;
									for(int tmpZ=keepZ2; tmpZ>localZ; --tmpZ, ++tmpY)
									{
										tomodify[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
										start[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
									}

									cif2.C2X = localX-1+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ-1+1;

									cif2.C3X = localX-1+1;
								}
								else
								{
									stairs.push_back(cif2);
									cif2.C1X = localX+1;
									cif2.C1Y = localY-1;
									cif2.C1Z = localZ+1;

									cif2.C2X = localX-1+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ-1+1;

									cif2.C3X = localX-1+1;
									cif2.C3Y = localY-1;
									cif2.C3Z = localZ+1;

									keepX2 = localX;
									keepY2 = localY;
									keepZ2 = localY;
								}
							}

							continue;
						}
					}
				}
			}

			stairs.push_back(cif);
			stairs.push_back(cif2);
			break;
		}
	}
}



/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::Search12CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material)
{
	if(start[idY*sizeX*sizeZ + idX*sizeZ + idZ] == 12)
	{
		tomodify[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;
		start[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;

		CornerStairInfo cif;
		cif.C1X = idX;
		cif.C1Y = idY-1;
		cif.C1Z = idZ+1;

		cif.C2X = idX+1;
		cif.C2Y = idY;
		cif.C2Z = idZ;

		cif.C3X = idX+1;
		cif.C3Y = idY-1;
		cif.C3Z = idZ+1;

		CornerStairInfo cif2;
		cif2.C1X = idX;
		cif2.C1Y = idY-1;
		cif2.C1Z = idZ+1;

		cif2.C2X = idX+1;
		cif2.C2Y = idY;
		cif2.C2Z = idZ;

		cif2.C3X = idX;
		cif2.C3Y = idY-1;
		cif2.C3Z = idZ;

		cif.material = Material;
		cif2.material = Material;


		int localX=idX;
		int localY=idY;
		int localZ=idZ;

		int keepX1=idX;
		int keepY1=idY;
		int keepZ1=idZ;

		int keepX2=idX;
		int keepY2=idY;
		int keepZ2=idZ;

		while(true)
		{
			++localX;
			++localY;
			--localZ;
			if(localY< sizeY)
			{
				if(localX< sizeX)
				{
					if(localZ>= 0)
					{
						if(start[localY*sizeX*sizeZ + localX*sizeZ + localZ] == 12)
						{
							tomodify[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;
							start[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;

							//check left triangle side
							{
								bool truetriangle = true;
								int tmpY=keepY1;
								for(int tmpX=keepX1; tmpX<localX; ++tmpX, ++tmpY)
								{
									if(start[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] != 2)
										truetriangle = false;
								}

								if(truetriangle)
								{
									int tmpY=keepY1;
									for(int tmpX=keepX1; tmpX<localX; ++tmpX, ++tmpY)
									{
										tomodify[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
										start[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
									}

									cif2.C2X = localX+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ;

									cif2.C3Z = localZ;
								}
								else
								{
									stairs.push_back(cif2);
									cif2.C1X = localX;
									cif2.C1Y = localY-1;
									cif2.C1Z = localZ+1;

									cif2.C2X = localX+1;
									cif2.C2Y = localY;
									cif2.C2Z = localZ;

									cif2.C3X = localX;
									cif2.C3Y = localY-1;
									cif2.C3Z = localZ;

									keepX1 = localX;
									keepY1 = localY;
									keepZ1 = localY;
								}
							}

							//check right triangle side
							{
								bool truetriangle = true;
								int tmpY=keepY2;
								for(int tmpZ=keepZ2; tmpZ>localZ; --tmpZ, ++tmpY)
								{
									if(start[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] != 4)
										truetriangle = false;
								}

								if(truetriangle)
								{
									int tmpY=keepY2;
									for(int tmpZ=keepZ2; tmpZ>localZ; --tmpZ, ++tmpY)
									{
										tomodify[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
										start[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
									}

									cif.C2X = localX+1;
									cif.C2Y = localY;
									cif.C2Z = localZ;

									cif.C3X = localX+1;
								}
								else
								{
									stairs.push_back(cif);
									cif.C1X = localX;
									cif.C1Y = localY-1;
									cif.C1Z = localZ+1;

									cif.C2X = localX+1;
									cif.C2Y = localY;
									cif.C2Z = localZ;

									cif.C3X = localX+1;
									cif.C3Y = localY-1;
									cif.C3Z = localZ+1;

									keepX2 = localX;
									keepY2 = localY;
									keepZ2 = localY;
								}
							}

							continue;
						}
					}
				}
			}

			stairs.push_back(cif);
			stairs.push_back(cif2);
			break;
		}
	}
}




/*
--------------------------------------------------------------------------------------------------
split rectangle into part with same textures
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::Search13CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material)
{
	if(start[idY*sizeX*sizeZ + idX*sizeZ + idZ] == 13)
	{
		tomodify[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;
		start[idY*sizeX*sizeZ + idX*sizeZ + idZ] = 0;

		CornerStairInfo cif;
		cif.C1X = idX;
		cif.C1Y = idY;
		cif.C1Z = idZ+1;

		cif.C2X = idX+1;
		cif.C2Y = idY-1;
		cif.C2Z = idZ;

		cif.C3X = idX+1;
		cif.C3Y = idY-1;
		cif.C3Z = idZ+1;

		CornerStairInfo cif2;
		cif2.C1X = idX;
		cif2.C1Y = idY;
		cif2.C1Z = idZ+1;

		cif2.C2X = idX+1;
		cif2.C2Y = idY-1;
		cif2.C2Z = idZ;

		cif2.C3X = idX;
		cif2.C3Y = idY-1;
		cif2.C3Z = idZ;

		cif.material = Material;
		cif2.material = Material;


		int localX=idX;
		int localY=idY;
		int localZ=idZ;

		int keepX1=idX;
		int keepY1=idY;
		int keepZ1=idZ;

		int keepX2=idX;
		int keepY2=idY;
		int keepZ2=idZ;

		while(true)
		{
			--localX;
			++localY;
			++localZ;
			if(localY< sizeY)
			{
				if(localX>= 0)
				{
					if(localZ>= 0)
					{
						if(start[localY*sizeX*sizeZ + localX*sizeZ + localZ] == 13)
						{
							tomodify[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;
							start[localY*sizeX*sizeZ + localX*sizeZ + localZ] = 0;

							//check left triangle side
							{
								bool truetriangle = true;
								int tmpY=keepY1;
								for(int tmpX=keepX1; tmpX>localX; --tmpX, ++tmpY)
								{
									if(start[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] != 5)
										truetriangle = false;
								}

								if(truetriangle)
								{
									int tmpY=keepY1;
									for(int tmpX=keepX1; tmpX>localX; --tmpX, ++tmpY)
									{
										tomodify[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
										start[tmpY*sizeX*sizeZ + tmpX*sizeZ + localZ] = 0;
									}

									cif.C1X = localX;
									cif.C1Y = localY;
									cif.C1Z = localZ+1;

									//cif.C3Y = localY;
									cif.C3Z = localZ+1;
								}
								else
								{
									stairs.push_back(cif);
									cif.C1X = localX;
									cif.C1Y = localY;
									cif.C1Z = localZ+1;

									cif.C2X = localX+1;
									cif.C2Y = localY-1;
									cif.C2Z = localZ;

									cif.C3X = localX+1;
									cif.C3Y = localY-1;
									cif.C3Z = localZ+1;

									keepX1 = localX;
									keepY1 = localY;
									keepZ1 = localY;
								}
							}

							//check right triangle side
							{
								bool truetriangle = true;
								int tmpY=keepY2;
								for(int tmpZ=keepZ2; tmpZ<localZ; ++tmpZ, ++tmpY)
								{
									if(start[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] != 3)
										truetriangle = false;
								}

								if(truetriangle)
								{
									int tmpY=keepY2;
									for(int tmpZ=keepZ2; tmpZ<localZ; ++tmpZ, ++tmpY)
									{
										tomodify[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
										start[tmpY*sizeX*sizeZ + localX*sizeZ + tmpZ] = 0;
									}

									cif2.C1X = localX;
									cif2.C1Y = localY;
									cif2.C1Z = localZ+1;

									cif2.C3X = localX;
									//cif2.C3Y = localY;
								}
								else
								{
									stairs.push_back(cif2);
									cif2.C1X = localX;
									cif2.C1Y = localY;
									cif2.C1Z = localZ+1;

									cif2.C2X = localX+1;
									cif2.C2Y = localY-1;
									cif2.C2Z = localZ;

									cif2.C3X = localX;
									cif2.C3Y = localY-1;
									cif2.C3Z = localZ;

									keepX2 = localX;
									keepY2 = localY;
									keepZ2 = localY;
								}
							}

							continue;
						}
					}
				}
			}

			stairs.push_back(cif);
			stairs.push_back(cif2);
			break;
		}
	}
}






/*
--------------------------------------------------------------------------------------------------
SavePlanes
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::SavePlanes(const std::string & filename)
{
	std::map<VECTOR, unsigned int> vertexmap;
	std::vector<float> vertexes;
	std::vector<unsigned int> indices;
	std::vector<short> materials;
	unsigned int indiceidx = 0;


	std::vector<float> vertexesroof;
	std::vector<unsigned int> indicesroof;
	std::map<VECTOR, unsigned int> vertexmaproof;
	unsigned int indiceroofidx = 0;



	std::ofstream filebit(filename.c_str(), std::ofstream::binary);

	{
		for(size_t i=0; i<_planesRoof.size(); ++i)
		{
			float _minX = (float)MIN(_planesRoof[i].StartX, _planesRoof[i].EndX);
			float _maxX = (float)MAX(_planesRoof[i].StartX, _planesRoof[i].EndX);
			float _minZ = (float)MIN(_planesRoof[i].StartZ, _planesRoof[i].EndZ);
			float _maxZ = (float)MAX(_planesRoof[i].StartZ, _planesRoof[i].EndZ);

			VECTOR p1((float)_minX, (float)_planesRoof[i].StartY, (float)_minZ);
			VECTOR p2((float)_minX, (float)_planesRoof[i].StartY, (float)_maxZ);
			VECTOR p3((float)_maxX, (float)_planesRoof[i].StartY, (float)_maxZ);
			VECTOR p4((float)_maxX, (float)_planesRoof[i].StartY, (float)_minZ);

			indicesroof.push_back(findvertexinmap(vertexmaproof, indiceroofidx, vertexesroof, p1));
			indicesroof.push_back(findvertexinmap(vertexmaproof, indiceroofidx, vertexesroof, p3));
			indicesroof.push_back(findvertexinmap(vertexmaproof, indiceroofidx, vertexesroof, p2));
			indicesroof.push_back(findvertexinmap(vertexmaproof, indiceroofidx, vertexesroof, p4));
			indicesroof.push_back(findvertexinmap(vertexmaproof, indiceroofidx, vertexesroof, p3));
			indicesroof.push_back(findvertexinmap(vertexmaproof, indiceroofidx, vertexesroof, p1));
		}
	}



	{
		for(size_t i=0; i<_planes.size(); ++i)
		{
			float _minX = (float)MIN(_planes[i].StartX, _planes[i].EndX);
			float _maxX = (float)MAX(_planes[i].StartX, _planes[i].EndX);
			float _minZ = (float)MIN(_planes[i].StartZ, _planes[i].EndZ);
			float _maxZ = (float)MAX(_planes[i].StartZ, _planes[i].EndZ);

			VECTOR p1((float)_minX, (float)_planes[i].StartY, (float)_minZ);
			VECTOR p2((float)_minX, (float)_planes[i].StartY, (float)_maxZ);
			VECTOR p3((float)_maxX, (float)_planes[i].StartY, (float)_maxZ);
			VECTOR p4((float)_maxX, (float)_planes[i].StartY, (float)_minZ);

			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p2));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p4));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));

			materials.push_back(_planes[i].material);
			materials.push_back(_planes[i].material);
		}
	}


	{
		for(size_t i=0; i<_stairs.size(); ++i)
		{
			VECTOR C1((float)_stairs[i].C1X, (float)_stairs[i].C1Y, (float)_stairs[i].C1Z);
			VECTOR C2((float)_stairs[i].C2X, (float)_stairs[i].C2Y, (float)_stairs[i].C2Z);
			VECTOR C3((float)_stairs[i].C3X, (float)_stairs[i].C3Y, (float)_stairs[i].C3Z);
			VECTOR C4((float)_stairs[i].C4X, (float)_stairs[i].C4Y, (float)_stairs[i].C4Z);

			// added 2 triangles in each side of the stairs so that char can not fall down on stair side
			VECTOR TR1Bottom((float)_stairs[i].C3X, (float)_stairs[i].C1Y, (float)_stairs[i].C3Z);
			VECTOR TR2Bottom((float)_stairs[i].C4X, (float)_stairs[i].C2Y, (float)_stairs[i].C4Z);
	
			VECTOR norm1 = ((C3 - C1).cross(C2-C1)).unit();
			VECTOR norm2 = ((C2 - C4).cross(C3-C4)).unit();

			if(norm1.y < 0.5)
			{
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C1));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C2));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C3));

				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C1));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C3));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, TR1Bottom));

			}
			else
			{
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C1));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C3));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C2));

				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C1));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, TR1Bottom));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C3));
			}

			if(norm2.y < 0.5)
			{
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C4));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C3));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C2));

				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C2));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, TR2Bottom));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C4));

			}
			else
			{
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C4));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C2));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C3));

				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C2));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C4));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, TR2Bottom));
			}


			materials.push_back(_stairs[i].material);
			materials.push_back(_stairs[i].material);

			materials.push_back(0);
			materials.push_back(0);
		}
	}

	{
		for(size_t i=0; i<_cornerstairs.size(); ++i)
		{
			VECTOR C1((float)_cornerstairs[i].C1X, (float)_cornerstairs[i].C1Y, (float)_cornerstairs[i].C1Z);
			VECTOR C2((float)_cornerstairs[i].C2X, (float)_cornerstairs[i].C2Y, (float)_cornerstairs[i].C2Z);
			VECTOR C3((float)_cornerstairs[i].C3X, (float)_cornerstairs[i].C3Y, (float)_cornerstairs[i].C3Z);

			VECTOR norm1 = ((C3 - C1).cross(C2-C1)).unit();
			if(norm1.y < 0.5)
			{
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C1));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C2));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C3));
			}
			else
			{
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C1));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C3));
				indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C2));
			}

			materials.push_back(_cornerstairs[i].material);
		}
	}


	{
		for(size_t i=0; i<_planeshidden.size(); ++i)
		{
			float _minX = (float)MIN(_planeshidden[i].StartX, _planeshidden[i].EndX);
			float _maxX = (float)MAX(_planeshidden[i].StartX, _planeshidden[i].EndX);
			float _minZ = (float)MIN(_planeshidden[i].StartZ, _planeshidden[i].EndZ);
			float _maxZ = (float)MAX(_planeshidden[i].StartZ, _planeshidden[i].EndZ);

			VECTOR p1((float)_minX, (float)_planeshidden[i].StartY, (float)_minZ);
			VECTOR p2((float)_minX, (float)_planeshidden[i].StartY, (float)_maxZ);
			VECTOR p3((float)_maxX, (float)_planeshidden[i].StartY, (float)_maxZ);
			VECTOR p4((float)_maxX, (float)_planeshidden[i].StartY, (float)_minZ);

			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p2));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p4));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
		}
	}


	{
		for(size_t i=0; i<_wallsX.size(); ++i)
		{
			_wallsX[i].StartY += 1;
			_wallsX[i].StartX -= 1;
			_wallsX[i].EndX -= 1;

			float _minX = (float)MIN(_wallsX[i].StartX, _wallsX[i].EndX);
			float _maxX = (float)MAX(_wallsX[i].StartX, _wallsX[i].EndX);
			float _minZ = (float)MIN(_wallsX[i].StartZ, _wallsX[i].EndZ);
			float _maxZ = (float)MAX(_wallsX[i].StartZ, _wallsX[i].EndZ);

			VECTOR p1((float)_wallsX[i].StartY, (float)_minX, (float)_minZ);
			VECTOR p2((float)_wallsX[i].StartY, (float)_minX, (float)_maxZ);
			VECTOR p3((float)_wallsX[i].StartY, (float)_maxX, (float)_maxZ);
			VECTOR p4((float)_wallsX[i].StartY, (float)_maxX, (float)_minZ);

			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p2));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p4));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
		}

		for(size_t i=0; i<_wallsXhidden.size(); ++i)
		{
			_wallsXhidden[i].StartX -= 1;
			_wallsXhidden[i].EndX -= 1;

			float _minX = (float)MIN(_wallsXhidden[i].StartX, _wallsXhidden[i].EndX);
			float _maxX = (float)MAX(_wallsXhidden[i].StartX, _wallsXhidden[i].EndX);
			float _minZ = (float)MIN(_wallsXhidden[i].StartZ, _wallsXhidden[i].EndZ);
			float _maxZ = (float)MAX(_wallsXhidden[i].StartZ, _wallsXhidden[i].EndZ);

			VECTOR p1((float)_wallsXhidden[i].StartY, (float)_minX, (float)_minZ);
			VECTOR p2((float)_wallsXhidden[i].StartY, (float)_minX, (float)_maxZ);
			VECTOR p3((float)_wallsXhidden[i].StartY, (float)_maxX, (float)_maxZ);
			VECTOR p4((float)_wallsXhidden[i].StartY, (float)_maxX, (float)_minZ);

			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p2));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p4));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));
		}
	}

	{
		for(size_t i=0; i<_wallsZ.size(); ++i)
		{
			_wallsZ[i].StartY += 1;
			_wallsZ[i].StartZ -= 1;
			_wallsZ[i].EndZ -= 1;

			float _minX = (float)MIN(_wallsZ[i].StartX, _wallsZ[i].EndX);
			float _maxX = (float)MAX(_wallsZ[i].StartX, _wallsZ[i].EndX);
			float _minZ = (float)MIN(_wallsZ[i].StartZ, _wallsZ[i].EndZ);
			float _maxZ = (float)MAX(_wallsZ[i].StartZ, _wallsZ[i].EndZ);

			VECTOR p1((float)_minX, (float)_minZ, (float)_wallsZ[i].StartY);
			VECTOR p2((float)_minX, (float)_maxZ, (float)_wallsZ[i].StartY);
			VECTOR p3((float)_maxX, (float)_maxZ, (float)_wallsZ[i].StartY);
			VECTOR p4((float)_maxX, (float)_minZ, (float)_wallsZ[i].StartY);

			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p2));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p4));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
		}

		for(size_t i=0; i<_wallsZhidden.size(); ++i)
		{
			_wallsZhidden[i].StartZ -= 1;
			_wallsZhidden[i].EndZ -= 1;

			float _minX = (float)MIN(_wallsZhidden[i].StartX, _wallsZhidden[i].EndX);
			float _maxX = (float)MAX(_wallsZhidden[i].StartX, _wallsZhidden[i].EndX);
			float _minZ = (float)MIN(_wallsZhidden[i].StartZ, _wallsZhidden[i].EndZ);
			float _maxZ = (float)MAX(_wallsZhidden[i].StartZ, _wallsZhidden[i].EndZ);

			VECTOR p1((float)_minX, (float)_minZ, (float)_wallsZhidden[i].StartY);
			VECTOR p2((float)_minX, (float)_maxZ, (float)_wallsZhidden[i].StartY);
			VECTOR p3((float)_maxX, (float)_maxZ, (float)_wallsZhidden[i].StartY);
			VECTOR p4((float)_maxX, (float)_minZ, (float)_wallsZhidden[i].StartY);

			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p2));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p4));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p1));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, p3));
		}
	}

	{
		for(size_t i=0; i<_wallsout.size(); ++i)
		{
			VECTOR C1((float)_wallsout[i].C1X, (float)_wallsout[i].C1Y, (float)_wallsout[i].C1Z);
			VECTOR C2((float)_wallsout[i].C2X, (float)_wallsout[i].C2Y, (float)_wallsout[i].C2Z);
			VECTOR C3((float)_wallsout[i].C3X, (float)_wallsout[i].C3Y, (float)_wallsout[i].C3Z);

			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C1));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C2));
			indices.push_back(findvertexinmap(vertexmap, indiceidx, vertexes, C3));
		}
	}


	unsigned int sizevertex = vertexes.size();
	unsigned int sizeindices = indices.size();
	unsigned int sizematerials = materials.size();

	unsigned int sizevertexroof = vertexesroof.size();
	unsigned int sizeindicesroof = indicesroof.size();



	filebit.write((char*)&sizevertex, sizeof(unsigned int));
	filebit.write((char*)&sizeindices, sizeof(unsigned int));
	filebit.write((char*)&sizematerials, sizeof(unsigned int));
	//filebit.write((char*)&sizevertexroof, sizeof(unsigned int));
	//filebit.write((char*)&sizeindicesroof, sizeof(unsigned int));

	filebit.write((char*)&vertexes[0], sizevertex*sizeof(float));
	filebit.write((char*)&indices[0], sizeindices*sizeof(unsigned int));

	if(sizematerials > 0)
		filebit.write((char*)&materials[0], sizematerials*sizeof(short));

	//if(sizevertexroof > 0)
	//{
	//	filebit.write((char*)&vertexesroof[0], sizevertexroof*sizeof(float));
	//	filebit.write((char*)&indicesroof[0], sizeindicesroof*sizeof(unsigned int));
	//}
}


/*
--------------------------------------------------------------------------------------------------
search roof in the scene
--------------------------------------------------------------------------------------------------
*/
void PhysicHandler::MakeSurroundingPlanes()
{
	int topy = _sizeY + 5;


	// roof-1
	{
	CornerStairInfo csi;
	csi.C1X = 0;
	csi.C1Y = topy;
	csi.C1Z = 0;
	csi.C2X = _sizeX;
	csi.C2Y = topy;
	csi.C2Z = 0;
	csi.C3X = 0;
	csi.C3Y = topy;
	csi.C3Z = _sizeZ;
	_wallsout.push_back(csi);
	}

	// roof-2
	{
	CornerStairInfo csi;
	csi.C1X = _sizeX;
	csi.C1Y = topy;
	csi.C1Z = _sizeZ;
	csi.C2X = 0;
	csi.C2Y = topy;
	csi.C2Z = _sizeZ;
	csi.C3X = _sizeX;
	csi.C3Y = topy;
	csi.C3Z = 0;
	_wallsout.push_back(csi);
	}

	//wallA-1
	{
	CornerStairInfo csi;
	csi.C1X = 0;
	csi.C1Y = 0;
	csi.C1Z = 0;
	csi.C2X = 0;
	csi.C2Y = topy;
	csi.C2Z = _sizeZ;
	csi.C3X = 0;
	csi.C3Y = 0;
	csi.C3Z = _sizeZ;
	_wallsout.push_back(csi);
	}

	//wallA-2
	{
	CornerStairInfo csi;
	csi.C1X = 0;
	csi.C1Y = 0;
	csi.C1Z = 0;
	csi.C2X = 0;
	csi.C2Y = topy;
	csi.C2Z = 0;
	csi.C3X = 0;
	csi.C3Y = topy;
	csi.C3Z = _sizeZ;
	_wallsout.push_back(csi);
	}

	//wallB-1
	{
	CornerStairInfo csi;
	csi.C1X = 0;
	csi.C1Y = 0;
	csi.C1Z = 0;
	csi.C2X = _sizeX;
	csi.C2Y = 0;
	csi.C2Z = 0;
	csi.C3X = _sizeX;
	csi.C3Y = topy;
	csi.C3Z = 0;
	_wallsout.push_back(csi);
	}

	//wallB-2
	{
	CornerStairInfo csi;
	csi.C1X = 0;
	csi.C1Y = 0;
	csi.C1Z = 0;
	csi.C2X = _sizeX;
	csi.C2Y = topy;
	csi.C2Z = 0;
	csi.C3X = 0;
	csi.C3Y = topy;
	csi.C3Z = 0;
	_wallsout.push_back(csi);
	}


	//wallC-1
	{
	CornerStairInfo csi;
	csi.C1X = _sizeX;
	csi.C1Y = 0;
	csi.C1Z = _sizeZ;
	csi.C2X = 0;
	csi.C2Y = 0;
	csi.C2Z = _sizeZ;
	csi.C3X = 0;
	csi.C3Y = topy;
	csi.C3Z = _sizeZ;
	_wallsout.push_back(csi);
	}

	//wallC-2
	{
	CornerStairInfo csi;
	csi.C1X = _sizeX;
	csi.C1Y = 0;
	csi.C1Z = _sizeZ;
	csi.C2X = 0;
	csi.C2Y = topy;
	csi.C2Z = _sizeZ;
	csi.C3X = _sizeX;
	csi.C3Y = topy;
	csi.C3Z = _sizeZ;
	_wallsout.push_back(csi);
	}


	//wallD-1
	{
	CornerStairInfo csi;
	csi.C1X = _sizeX;
	csi.C1Y = 0;
	csi.C1Z = _sizeZ;
	csi.C2X = _sizeX;
	csi.C2Y = topy;
	csi.C2Z = 0;
	csi.C3X = _sizeX;
	csi.C3Y = 0;
	csi.C3Z = 0;
	_wallsout.push_back(csi);
	}

	//wallD-2
	{
	CornerStairInfo csi;
	csi.C1X = _sizeX;
	csi.C1Y = 0;
	csi.C1Z = _sizeZ;
	csi.C2X = _sizeX;
	csi.C2Y = topy;
	csi.C2Z = _sizeZ;
	csi.C3X = _sizeX;
	csi.C3Y = topy;
	csi.C3Z = 0;
	_wallsout.push_back(csi);
	}
}
