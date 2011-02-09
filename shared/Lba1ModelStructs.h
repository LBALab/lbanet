/*
------------------------[ LBA Screen Viewer Source ]-------------------------
Copyright (C) 2004
--------------------------------[ HQRLib.h ]---------------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Fri Aug 21 2004
Email : alexandrefontoura@oninetspeed.pt

Info: some codes from yazor TwinEngine taken and modified by me

-------------------------------[ GNU License ]-------------------------------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

-----------------------------------------------------------------------------
*/

#ifndef Lba1ModelStructs
#define Lba1ModelStructs


struct TBodyHeader
{
    unsigned short int BodyFlag;
	unsigned short int Unknown0;
	unsigned short int Unknown1;
	unsigned short int Unknown2;
	unsigned short int Unknown3;
	unsigned short int Unknown4;
	unsigned short int Unknown5;
	unsigned short int DummyOffset;
};

struct TBodyPoint
{
    double X; // double
    double Y;
    double Z;
};

struct TPoints
{
    int NumberOfPoints; // unsigned short
    TBodyPoint *PointsData;
};

struct TElement
{
    short int FirstPoint; // unsigned
	short int NumberOfPoints;
	short int BasePoint;
	short int BaseElement;
	short int ElementFlag;
	short int RotateZ;
	short int RotateY;
	short int RotateX;
	short int Unknown0;
	short int NumberOfShades;
	short int Unknown1;
	short int Unknown2;
	int Unknown3;
	int Y;
	int Unknown4;
	short int Unknown5;
};

struct TElements
{
    int NumberOfElements; // unsigned short
    TElement *ElementsData;
};

struct TShade
{
    short int Color1; // unsigned
    short int Color2;
    short int Color3;
    short int DivideColorsNum;
};

struct TShades
{
    int NumberOfShades; // unsigned short
    //TShade *ShadesData;
    char* ShadesData;
};

struct TVertex
{
    int Shade; // unsigned short
    int PointNum;
};

struct TPolygon
{
    int RenderType; // unsigned char
    int NumberOfVertexs; // unsigned char
    int ColorIdx; // unsigned short
    int Shade; // unsigned short
    TVertex *VertexsData;
};

struct TPolygons
{
    int NumberOfPolygons; // unsigned short
    TPolygon *PolygonsData;
};

struct TLine
{
    int Color;
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
    int Color;
    short int Size; // unsigned
    short int Center;
};

struct TSpheres
{
    int NumberOfSpheres;
    TSphere *SpheresData;
};

struct TMatrix
{
	double data[12];
};


#endif