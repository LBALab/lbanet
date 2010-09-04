#ifndef ILE_DATA_STRUCTURES_H_
# define ILE_DATA_STRUCTURES_H_

#pragma once

/* This structure is used to map the triangle declarations in the ILE files */
struct GroundTriangle
{
	unsigned int textureBank : 4;
	unsigned int useTexture : 2;
	unsigned int useColor : 2;
	unsigned int unk1 : 4 ;
	unsigned int unk2 : 4;
	unsigned int orientation : 1;
	unsigned int unk3 : 1;
	unsigned int unk4 : 1;
	unsigned int textureIndex : 13;
};

/* This structure maps the grid's quad declaration in the ILE files */
struct GroundSquare
{
	GroundTriangle	triangle[2];
};

struct IslandUV
{
	unsigned short u;
	unsigned short v;


	//bool operator <(const IslandUV & tocmp) const
	//{
	//	return (u < tocmp.u) || ((u == tocmp.u) && (v < tocmp.v));
	//}

	//bool operator ==(const IslandUV & tocmp) const
	//{
	//	return (u == tocmp.u) && (v == tocmp.v);
	//}
};

/* This structure maps an UV declaration entry in the ILE files */
struct GroundTextureInfo
{
	IslandUV uv[3];

	//bool operator <(const GroundTextureInfo & tocmp) const
	//{
	//	return (uv[0] < tocmp.uv[0]) 
	//			|| ((uv[0] == tocmp.uv[0]) 
	//			&& ((uv[1] < tocmp.uv[1]) || ((uv[1] == tocmp.uv[1]) && (uv[2] < tocmp.uv[2])))
	//		);
	//}
};

/* This structure maps an object positioning, index in OBL, and rotation data entry in the ILE files */
struct IslandObjectInfo
{
	unsigned int index;
	int ox;
	int oy;
	int oz;
	unsigned short a5;
	unsigned short a5bis;
	unsigned char a6;
	unsigned char angle;
	unsigned short a6bis;
	unsigned short a7;
	unsigned short a7bis;
	unsigned short a8;
	unsigned short a8bis;
	unsigned short a9;
	unsigned short a9bis;
	unsigned short a10;
	unsigned short a10bis;
	unsigned short a11;
	unsigned short a11bis;
	unsigned short a12;
	unsigned short a12bis;
};

/* This structure maps an object header in the OBL files */
struct IslandObjectHeader
{
	unsigned char	unk0[0x44];
	unsigned int	polygonSectionOffset;
	unsigned int	lineSectionSize;
	unsigned int	lineSectionOffset;
	unsigned int	sphereSectionSize;
	unsigned int	sphereSectionOffset;
	unsigned int	cutSectionSize;
	unsigned int	cutSectionOffset;
	unsigned int	unk1;
	unsigned short	numVerticesType1;
	unsigned short	numVerticesType2;
};

struct OBLVertex
{
	short	x;
	short	y;
	short	z;
	short	unk0;
};

struct OBLIntensity
{
	unsigned char	i[8];
};

struct OBLPolygonHeader
{
	unsigned char	id;
	unsigned char	type;
	unsigned short	numPolygon;
	unsigned short	size;
	unsigned char	unk0;
	unsigned char	unk1;
};

struct	OBLPolygon
{
	unsigned short	idx[4];
	unsigned char	color;
	unsigned char	unk0[3];
	IslandUV		uv[4];	
};

struct TLine
{
	unsigned char	unk1;
	unsigned char	unk2;
	unsigned char	Color;
	unsigned char	unk4;
    short int PointNum1; // unsigned
    short int PointNum2; // unsigned
};

struct TLines
{
    int NumberOfLines; // unsigned short
    TLine *LinesData;
};

struct TSphere
{
	unsigned char	unk1;
	unsigned char	unk2;
	unsigned char	Color;
	unsigned char	unk4;
    short int Center;
    short int Size; // unsigned
};

struct TSpheres
{
    int NumberOfSpheres;
    TSphere *SpheresData;
};



#endif /* ILE_DATA_STRUCTURES_H_ */
