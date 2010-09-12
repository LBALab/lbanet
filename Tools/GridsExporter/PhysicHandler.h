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

#ifndef __LBA_NET_PHYSIC_HANDLER_H__
#define __LBA_NET_PHYSIC_HANDLER_H__

#include <string>
#include <vector>



struct StairInfo
{
	int C1X;
	int C1Y;
	int C1Z;

	int C2X;
	int C2Y;
	int C2Z;

	int C3X;
	int C3Y;
	int C3Z;

	int C4X;
	int C4Y;
	int C4Z;

	int type;
	int length;
	short material;
};

struct CornerStairInfo
{
	int C1X;
	int C1Y;
	int C1Z;

	int C2X;
	int C2Y;
	int C2Z;

	int C3X;
	int C3Y;
	int C3Z;

	int type;
	short material;
};


struct PlaneInfo
{
	int StartX;
	int StartY;
	int StartZ;

	int EndX;
	int EndY;
	int EndZ;

	short material;
};



//struct TexNodeInfo
//{
//	int Px;
//	int Py;
//	int TexCoor1x;
//	int TexCoor1y;
//};

struct TexPlaneInfo
{
	//std::vector<TexNodeInfo> texinfo;
	int textureid;


	int StartX;
	int StartY;

	int EndX;
	int EndY;
};


class TextInfo
{
public: 
	//! constructor
	TextInfo(){}

	//! denstructor
	virtual ~TextInfo(){}

	virtual int GetTexture(int X, int Y) = 0;
};



class SingleTextInfo : public TextInfo
{
public: 
	//! constructor
	SingleTextInfo(int TexId)
	: _TexId(TexId){}

	//! denstructor
	virtual ~SingleTextInfo(){}

	virtual int GetTexture(int X, int Y)
	{ return _TexId;}

private:
	int _TexId;
};



class DuoTextInfoX : public TextInfo
{
public: 
	//! constructor
	DuoTextInfoX(int TexId, int TextId2)
	: _TexId(TexId), _TextId2(TextId2){}

	//! denstructor
	virtual ~DuoTextInfoX(){}

	virtual int GetTexture(int X, int Y)
	{ 
		if ( X & 1)
			return _TextId2;
		else
			return _TexId;
	}

private:
	int _TexId;
	int _TextId2;
};


class DuoTextInfoY : public TextInfo
{
public: 
	//! constructor
	DuoTextInfoY(int TexId, int TextId2)
	: _TexId(TexId), _TextId2(TextId2){}

	//! denstructor
	virtual ~DuoTextInfoY(){}

	virtual int GetTexture(int X, int Y)
	{ 
		if ( Y & 1)
			return _TextId2;
		else
			return _TexId;
	}

private:
	int _TexId;
	int _TextId2;
};


class QuadraTextInfo : public TextInfo
{
public: 
	//! constructor
	QuadraTextInfo(int TexId, int TextId2, int TexId3, int TextId4)
	: _TexId(TexId), _TextId2(TextId2), _TexId3(TexId3), _TextId4(TextId4)
	{}

	//! denstructor
	virtual ~QuadraTextInfo(){}

	virtual int GetTexture(int X, int Y)
	{ 
		if ( X & 1)
		{
			if ( Y & 1)
				return _TextId4;
			else
				return _TexId3;
		}
		else
		{
			if ( Y & 1)
				return _TextId2;
			else
				return _TexId;
		}
	}

private:
	int _TexId;
	int _TextId2;
	int _TexId3;
	int _TextId4;
};



//*************************************************************************************************
//*                                      class PhysicHandler
//*************************************************************************************************

class PhysicHandler
{
public:

	//! constructor
	PhysicHandler();

	//! destructor
	~PhysicHandler();


	// load a map into memory
	void Allocate(int sizeX, int sizeY, int sizeZ);

	// save the map physics to a file
	void SaveMap(const std::string Filename);


	// return pointer to the physic buffer in order to fill it
	short * GetBufferPtr()
	{ return _physicCube; }

	short * GetMaterialBufferPtr()
	{ return _materialCube; }




	// return the structure of a specific brick
	short GetStructure(int X, int Y, int Z);


	// clean the memory
	void ClearMemory();




	//! look for floors  in the map
	void SearchFloors();
	void SearchFloorsHidden(int sizeX, int sizeY, int sizeZ);
	void SearchFloorsWithMaterial(int sizeX, int sizeY, int sizeZ, short Material);

	void SearchWallX();
	void SearchWallXNormal(int sizeX, int sizeY, int sizeZ);
	void SearchWallXHidden(int sizeX, int sizeY, int sizeZ);

	void SearchWallZ();
	void SearchWallZNormal(int sizeX, int sizeY, int sizeZ);
	void SearchWallZHidden(int sizeX, int sizeY, int sizeZ);


	void SearchStairs();
	void SearchCornerStairsWithMaterial(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										std::vector<CornerStairInfo> & stairs, short Material);

	void SearchStairsWithMaterial(short * start, int sizeX, int sizeY, int sizeZ, 
									std::vector<StairInfo> & stairs, short Material);

	StairInfo FindStairUp(short * start, int idX, int idY, int idZ, 
						int sizeX, int sizeY, int sizeZ, bool overwrite);

	std::vector<PlaneInfo> GetPlanes()
	{ return _planes; }

	std::vector<PlaneInfo> GetPlanesHidden()
	{ return _planeshidden; }

	std::vector<PlaneInfo> GetWallsX()
	{ return _wallsX; }

	std::vector<PlaneInfo> GetWallsXHidden()
	{ return _wallsXhidden; }

	std::vector<PlaneInfo> GetWallsZ()
	{ return _wallsZ; }

	std::vector<PlaneInfo> GetWallsZHidden()
	{ return _wallsZhidden; }

	std::vector<StairInfo> GetStairs()
	{ return _stairs; }

	std::vector<CornerStairInfo> GetCornerStairs()
	{ return _cornerstairs; }


	std::vector<CornerStairInfo> GetOutWalls()
	{ return _wallsout; }


	void SavePlanes(const std::string & filename);

	void MakeSurroundingPlanes();

protected:

	// allocate a memory buffer of given size
	void AllocateMemory(int sizeX, int sizeY, int sizeZ);

	// return true if the brick asked contain a solid
	// structure - return false otherwise
	bool IsSolid(int X, int Y, int Z);

	// return true if the brick asked contain an empty
	// structure - return false otherwise
	bool IsEmpty(int X, int Y, int Z);


	// return true if the actor is stepping on empty place
	bool EmptyUnderActor(double X, double Y, double Z,
							double actorSizeX, double actorSizeY, double actorSizeZ);


	//! look for floors  in the map
	void SearchFloors(short * thisY, int Y, std::vector<PlaneInfo> &planes, 
						int sizeX, int sizeY, int sizeZ, short material, int minareasize = 0);


	//! look for floors  in the map
	int SearchMaxFloor(short * center, int idxX, int idxZ,
						int &startX, int &startZ,
						int &endX, int &endZ, int sizeX, int sizeY, int sizeZ);

	bool IsSolidHorLine(short * start, int size, int sizeX, int sizeY, int sizeZ);
	bool IsSolidVerLine(short * start, int size, int sizeX, int sizeY, int sizeZ);



	//! look for floors  in the map
	int SearchMaxTexture(short * center, int idxX, int idxY,
							int &startX, int &startY,
							int &endX, int &endY, int sizeX, int sizeY, TextInfo * txi);

	bool IsTexHorLine(short * start, int size, int sizeX, int sizeY, 
							int idxX, int idxY, TextInfo * txi);

	bool IsTexVerLine(short * start, int size, int sizeX, int sizeY, 
							int idxX, int idxY, TextInfo * txi);



	void Search6CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material);

	void Search7CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material);

	void Search8CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material);

	void Search9CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material);

	void Search10CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material);

	void Search11CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material);

	void Search12CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material);

	void Search13CornerStairs(short * start, short * tomodify, int sizeX, int sizeY, int sizeZ, 
										int idX, int idY, int idZ,
									   std::vector<CornerStairInfo> & stairs, short Material);


	short GetMaterial(int X, int Y, int Z);

private:

	// cube representing the map physic
	short *	_physicCube;
	short *	_materialCube;


	// size of the cube
	int			_sizeX;
	int			_sizeY;
	int			_sizeZ;

	std::vector<PlaneInfo> _planes;
	std::vector<PlaneInfo> _planeshidden;
	std::vector<PlaneInfo> _planesRoof;

	std::vector<PlaneInfo> _wallsX;
	std::vector<PlaneInfo> _wallsXhidden;

	std::vector<PlaneInfo> _wallsZ;
	std::vector<PlaneInfo> _wallsZhidden;

	std::vector<StairInfo> _stairs;
	std::vector<CornerStairInfo> _cornerstairs;

	std::vector<CornerStairInfo> _wallsout;
};

#endif
