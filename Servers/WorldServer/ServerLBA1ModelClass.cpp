/*
------------------------[ LBAnimator studio Source ]-------------------------
Copyright (C) 2004
--------------------------------[ HQRLib.h ]---------------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Fri Aug 21 2004
Email : alexandrefontoura@gmail.com

Info: some codes from yazor TwinEngine taken and modified by alexfont
Sligtly modified by Rincevent_123 to fit lbanet

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

#pragma hdrstop

#include <time.h>

#include "ServerLBA1ModelClass.h"
#include "RotationTable.h"
#include "HQRlib.h"
#include "LogHandler.h"
#include "Lba1ModelMapHandler.h"

#include <stdlib.h>
#include <stdio.h>
#include <cstring>

#include "HQRHandler.h"


#include <iostream>



static float factormul_lba1_toosg = 32;
static float factortransY_lba1_toosg = 0;//-0.1;



ServerLBA1ModelClass::~ServerLBA1ModelClass()
{
	free(Points->PointsData);
	free(Points);
	free(Elements->ElementsData);
	free(Elements);
    free(Shades->ShadesData);
	free(Shades);

	for(int i=0; i < Polygons->NumberOfPolygons;i++)
		free(Polygons->PolygonsData[i].VertexsData);

	free(Polygons->PolygonsData);
	free(Polygons);

	free(Lines->LinesData);
	free(Lines);

	free(Spheres->SpheresData);
	free(Spheres);

    free(bodyPtr);
    free(bodyHeaderPtr);
	free(animPtr);

	free(dividedPointsX);
	free(dividedPointsY);
	free(dividedPointsZ);

	delete m_paletteRGB;
}


ServerLBA1ModelClass::ServerLBA1ModelClass(entitiesTableStruct* entitiesData, const std::string &bodyPath,
								const std::string &animPath, int entityNum,int bodyNum)
: bodyPtr(NULL), animPtr(NULL), m_currentSpeedX(0), m_currentSpeedY(0), m_currentSpeedZ(0),
	m_animationspeed(1), cumutime(0), rotTablePtr(rotTable)
{

	HQRHandler HQH(Lba1ModelDataPath+"RESS.HQR");
	unsigned int paletteSize;
	m_paletteRGB = HQH.Load_HQR(0, paletteSize);

	m_animPath = animPath;
	m_softShade = true;
	m_wireFrame = 0;

	m_showSelectedPolygon=false;
	m_showBones=false;
	m_showPoint=false;
	m_showLine=false;
	m_showSphere=false;
	m_showCollisionBox=false;
	m_useAnimSteps=false;

	Points=NULL;
	Elements=NULL;
	entitiesTableEntry* localEntry;

	speed=15;
	angle=0;

	globalAngleX=0;
	globalAngleY=0;
	globalAngleZ=0;

	lightPosition[0]=0;
	lightPosition[1]=40;
	lightPosition[2]=40;

	currentBone=0;

	if(!entitiesData) // no entities data, can't load model...
	{
		LogHandler::getInstance()->LogToFile("No entity data, can not load the model...");
		return;
	}

	localEntry=&(entitiesData->entitiesTable[entityNum]);

	for(int i=0;i<localEntry->numOfBody;i++)
	{
		if(localEntry->bodyList[i].body==bodyNum)
		{
			if(bodyPtr)
				free(bodyPtr);

            filesize = loadResource(bodyPath.c_str(),localEntry->bodyList[i].index,&bodyPtr);

			if(localEntry->bodyList[i].useColBox)
			{
				X1=localEntry->bodyList[i].X1;
				Z1=localEntry->bodyList[i].Z1;
				Y1=localEntry->bodyList[i].Y1;
				X2=localEntry->bodyList[i].X2;
				Z2=localEntry->bodyList[i].Z2;
				Y2=localEntry->bodyList[i].Y2;
			}


            if(*((short int *)bodyPtr) & 0x02)
                useAnim = true;
            else
                useAnim = false;

            LoadModel(bodyPtr);

            currentEntity=entityNum;
			break;
		}
	}

	lastCurrentX =0;
	lastCurrentY =0;
	lastCurrentZ =0;
}


void ServerLBA1ModelClass::LoadAnim(entitiesTableStruct* entitiesData, int animNum)
{
	if(animPtr)
		free(animPtr);

	unsigned char* localAnim; // changed unsigned

	m_currentSpeedX = 0;
	m_currentSpeedY = 0;
	m_currentSpeedZ= 0;


	currentKeyFrame=0;
    animsize = loadResource(m_animPath.c_str(),animNum, &localAnim);

	lastCurrentX =0;
	lastCurrentY =0;
	lastCurrentZ =0;

	currentX =0;
	currentY =0;
	currentZ =0;

	setAnimAtKeyFrame(0,(unsigned char*)localAnim,Elements,true);

	animPtr=(unsigned char*)localAnim;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::LoadModel(unsigned char* bodyPtr)
{
	bodyHeaderPtr = (unsigned char*)malloc(26);
	for(int a=0; a<26; a++)
		*(bodyHeaderPtr+a) = *(bodyPtr+a);

    Points=LoadPoints(bodyPtr);
	Elements=LoadElements(bodyPtr);
	Shades=LoadShades(bodyPtr);
	Polygons=LoadPolys(bodyPtr);
	Lines=LoadLines(bodyPtr);
	Spheres=LoadSpheres(bodyPtr);
}



//---------------------------------------------------------------------------

TPoints* ServerLBA1ModelClass::LoadPoints(unsigned char* model)
{
	TPoints* localData;
	int numOfPoints;
	short int *sourcePtr;
	int i;

	localData=(TPoints*)malloc(sizeof(TPoints));

	numOfPoints=getNumOfPointsInModel(model);

	localData->PointsData=(TBodyPoint*)malloc(sizeof(TBodyPoint)*numOfPoints);
	localData->NumberOfPoints=numOfPoints;

	sourcePtr=(short int*)(model+0x1C);

	for(i=0;i<numOfPoints;i++)
	{
		localData->PointsData[i].X=*(sourcePtr++);
		localData->PointsData[i].Y=*(sourcePtr++);
		localData->PointsData[i].Z=*(sourcePtr++);
	}

	dividedPointsX=(float*)malloc(sizeof(float)*numOfPoints);
	dividedPointsY=(float*)malloc(sizeof(float)*numOfPoints);
	dividedPointsZ=(float*)malloc(sizeof(float)*numOfPoints);

	return(localData);
}

//---------------------------------------------------------------------------

TElements* ServerLBA1ModelClass::LoadElements(unsigned char* model)
{
	TElements* localData;
	int numOfElements;
	unsigned char* ptr;
	int i;

	localData=(TElements*)malloc(sizeof(TElements));

	numOfElements=getNumOfElementsInModel(model);

	localData->ElementsData=(TElement*)malloc(sizeof(TElement)*numOfElements);
	localData->NumberOfElements=numOfElements;

	ptr=getElementsPtr(model)+2;

	for(i=0;i<numOfElements;i++)
	{
		memcpy(&localData->ElementsData[i],ptr,38);
        if(i!=0)
            localData->ElementsData[i].BaseElement = (short int)((localData->ElementsData[i].BaseElement*36)/38);
		ptr+=38;
	}

	return(localData);
}

//---------------------------------------------------------------------------

TShades* ServerLBA1ModelClass::LoadShades(unsigned char* model)
{
	TShades* localData;
	int numOfShades;

	localData=(TShades*)malloc(sizeof(TShades));

	numOfShades=getNumOfShadesInModel(model);

	localData->NumberOfShades=numOfShades;
	localData->ShadesData=(char*)malloc(numOfShades*8);

	memcpy(localData->ShadesData,getShadesPtr(model)+2,numOfShades*8);

	return(localData);
}

//---------------------------------------------------------------------------

TPolygons* ServerLBA1ModelClass::LoadPolys(unsigned char* model)
{
	unsigned char* backupModelPtr;

	struct polyHeader
	{
		unsigned char polyRenderType;
		unsigned char numOfVertex;
		unsigned short int colorIndex;
	};

	struct shadedVertexHeader
	{
		unsigned short int shadeEntry;
		unsigned short int dataOffset;
	};

	struct unshadedVertexHeader
	{
		unsigned short int dataOffset;
	};

	TPolygons* localData;
	int numOfPolys;
	int i;
	int j;
	unsigned char* ptr;

	localData=(TPolygons*)malloc(sizeof(TPolygons));

	numOfPolys=getNumOfPolysInModel(model);

	localData->PolygonsData=(TPolygon*)malloc(sizeof(TPolygon)*numOfPolys);
	localData->NumberOfPolygons=numOfPolys;

	ptr=getPolysPtr(model)+2;
	backupModelPtr=ptr-2;

	for(i=0;i<numOfPolys;i++)
	{
		localData->PolygonsData[i].RenderType=((polyHeader*)ptr)->polyRenderType;
		localData->PolygonsData[i].NumberOfVertexs=((polyHeader*)ptr)->numOfVertex;
		localData->PolygonsData[i].ColorIdx=((polyHeader*)ptr)->colorIndex;
		localData->PolygonsData[i].Shade=-1;

		localData->PolygonsData[i].VertexsData=(TVertex*)malloc(sizeof(TVertex)*localData->PolygonsData[i].NumberOfVertexs);

		if(localData->PolygonsData[i].RenderType>=9)
		{
			localData->PolygonsData[i].RenderType-=2;

			ptr+=4;

			for(j=0;j<localData->PolygonsData[i].NumberOfVertexs;j++)
			{
				localData->PolygonsData[i].VertexsData[j].Shade=(((shadedVertexHeader*)ptr)->shadeEntry);
				localData->PolygonsData[i].VertexsData[j].PointNum=(((shadedVertexHeader*)ptr)->dataOffset)/6;

				ptr+=4;
			}
		}
		else
		if(localData->PolygonsData[i].RenderType>=7)
		{
			localData->PolygonsData[i].RenderType-=7;

			ptr+=4;

			localData->PolygonsData[i].Shade=*(short int*)ptr;

			ptr+=2;

			for(j=0;j<localData->PolygonsData[i].NumberOfVertexs;j++)
			{
				localData->PolygonsData[i].VertexsData[j].PointNum=(((unshadedVertexHeader*)ptr)->dataOffset)/6;

				ptr+=2;
			}
		}
		else
		{
			ptr+=4;

			for(j=0;j<localData->PolygonsData[i].NumberOfVertexs;j++)
			{
				localData->PolygonsData[i].VertexsData[j].PointNum=(((unshadedVertexHeader*)ptr)->dataOffset)/6;

				ptr+=2;
			}
		}

	}

	polyDataSize=ptr-backupModelPtr;

	return(localData);
}

//---------------------------------------------------------------------------

TLines* ServerLBA1ModelClass::LoadLines(unsigned char* model)
{
	TLines* localData;
	int numOfLines;

	localData=(TLines*)malloc(sizeof(TLines));

	numOfLines=getNumOfLinesInModel(model);

	localData->NumberOfLines=numOfLines;
	localData->LinesData=(TLine*)malloc(numOfLines*sizeof(TLine));

	int i;
	unsigned char* sourcePtr=getLinesPtr(model)+2;

	for(i=0;i<numOfLines;i++)
	{
		memcpy(&localData->LinesData[i],sourcePtr,8);

		sourcePtr+=8;
	}

	return(localData);
}

//---------------------------------------------------------------------------

TSpheres* ServerLBA1ModelClass::LoadSpheres(unsigned char* model)
{
	TSpheres* localData;
	int numOfSpheres;

	localData=(TSpheres*)malloc(sizeof(TSpheres));

	numOfSpheres=getNumOfSpheresInModel(model);

	localData->NumberOfSpheres=numOfSpheres;
	localData->SpheresData=(TSphere*)malloc(numOfSpheres*sizeof(TSphere));

	int i;
	unsigned char* sourcePtr=getSpheresPtr(model)+2;

	for(i=0;i<numOfSpheres;i++)
	{
		memcpy(&localData->SpheresData[i],sourcePtr,8);

		sourcePtr+=8;
	}

	return(localData);
}

//---------------------------------------------------------------------------

unsigned char* ServerLBA1ModelClass::getPointsPtr(unsigned char* model)
{
	return(model+0x1A);
}

//---------------------------------------------------------------------------

unsigned char* ServerLBA1ModelClass::getElementsPtr(unsigned char* model)
{
	unsigned char* temp;

	temp=getPointsPtr(model);
	return(temp+2+(*(short int*)temp)*6);
}

//---------------------------------------------------------------------------

unsigned char* ServerLBA1ModelClass::getShadesPtr(unsigned char* model)
{
	unsigned char* temp;

	temp=getElementsPtr(model);
	return(temp+2+(*(short int*)temp)*38);
}

//---------------------------------------------------------------------------

unsigned char* ServerLBA1ModelClass::getPolysPtr(unsigned char* model)
{
	unsigned char* temp;

	temp=getShadesPtr(model);
	return(temp+2+(*(short int*)temp)*8);
}

//---------------------------------------------------------------------------

unsigned char* ServerLBA1ModelClass::getLinesPtr(unsigned char* model)
{
	unsigned char* temp;

	temp=getPolysPtr(model);
	return(temp+polyDataSize);
}

//---------------------------------------------------------------------------

unsigned char* ServerLBA1ModelClass::getSpheresPtr(unsigned char* model)
{
	unsigned char* temp;

	temp=getLinesPtr(model);
	return(temp+(*(short int*)temp)*8+2);
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumOfPointsInModel(unsigned char* model)
{
	return(*(short int*)getPointsPtr(model));
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumOfElementsInModel(unsigned char* model)
{
	return(*(short int*)getElementsPtr(model));
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumOfShadesInModel(unsigned char* model)
{
	return(*(short int*)getShadesPtr(model));
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumOfPolysInModel(unsigned char* model)
{
	return(*(short int*)getPolysPtr(model));
}


//---------------------------------------------------------------------------
int ServerLBA1ModelClass::getNumOfLinesInModel(unsigned char* model)
{
	return(*(short int*)getLinesPtr(model));
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumOfSpheresInModel(unsigned char* model)
{
	return(*(short int*)getSpheresPtr(model));
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumPoints()
{
    return Points->NumberOfPoints;
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumElements()
{
    return Elements->NumberOfElements;
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumShades()
{
    return Shades->NumberOfShades;
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumPolygons()
{
    return Polygons->NumberOfPolygons;
}

//---------------------------------------------------------------------------

bool ServerLBA1ModelClass::canUseAnim()
{
    return useAnim;
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumVertexs()
{
    int numVertexs=0;

    for(int poly=0; poly < Polygons->NumberOfPolygons; poly++)
    {
        numVertexs += Polygons->PolygonsData[poly].NumberOfVertexs;
    }

    return numVertexs;
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumLines()
{
    return Lines->NumberOfLines;
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumSpheres()
{
    return Spheres->NumberOfSpheres;
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getFileSize()
{
    return filesize;
}

void ServerLBA1ModelClass::ApplyRotation(TMatrix* tempMatrix,TMatrix* currentMatrix)
{
	TMatrix localMatrixX;
	TMatrix localMatrixY;

	short int rotationX1;
	short int rotationX2;
	short int rotationY1;
	short int rotationY2;
	short int rotationZ1;
	short int rotationZ2;

	if(currentRotation[0])
	{
		rotationX1=rotTablePtr[currentRotation[0]&0x3FF];
		rotationX2=rotTablePtr[(currentRotation[0]+0x100)&0x3FF];

		double* source=currentMatrix->data;
		double* dest=localMatrixX.data;

		int var0=(int)*(source++);
		int var1=(int)*(source++);
		int var2=(int)*(source++);

		*(dest++) = var0;
		*(dest++) = (var2 * rotationX1 + var1 * rotationX2) >> 14;
	    *(dest++) = (var2 * rotationX2 - var1 * rotationX1) >> 14;

		var0=(int)*(source++);
		var1=(int)*(source++);
		var2=(int)*(source++);

		*(dest++) = var0;
		*(dest++) = (var2 * rotationX1 + var1 * rotationX2) >> 14;
	    *(dest++) = (var2 * rotationX2 - var1 * rotationX1) >> 14;

		var0=(int)*(source++);
		var1=(int)*(source++);
		var2=(int)*(source++);

		*(dest++) = var0;
		*(dest++) = (var2 * rotationX1 + var1 * rotationX2) >> 14;
	    *(dest++) = (var2 * rotationX2 - var1 * rotationX1) >> 14;

	}
	else
	{
		double* source=currentMatrix->data;
		double* dest=localMatrixX.data;

		for(int i=0;i<9;i++)
		    *(dest++)=*(source++);
	}

	if(currentRotation[1])
	{
		rotationY1=rotTablePtr[currentRotation[1]&0x3FF];
		rotationY2=rotTablePtr[(currentRotation[1]+0x100)&0x3FF];

		double* source=localMatrixX.data;
		double* dest=localMatrixY.data;

		int var0=(int)*(source++);
		int var1=(int)*(source++);
		int var2=(int)*(source++);

	    *(dest++) = (var1 * rotationY1 + var0 * rotationY2) >> 14;
	    *(dest++) = (var1 * rotationY2 - var0 * rotationY1) >> 14;
	    *(dest++) = var2;

		var0=(int)*(source++);
		var1=(int)*(source++);
		var2=(int)*(source++);

	    *(dest++) = (var1 * rotationY1 + var0 * rotationY2) >> 14;
	    *(dest++) = (var1 * rotationY2 - var0 * rotationY1) >> 14;
		*(dest++) = var2;

		var0=(int)*(source++);
		var1=(int)*(source++);
		var2=(int)*(source++);

	    *(dest++) = (var1 * rotationY1 + var0 * rotationY2) >> 14;
	    *(dest++) = (var1 * rotationY2 - var0 * rotationY1) >> 14;
		*(dest++) = var2;
	}
	else
	{
		double* source=localMatrixX.data;
		double* dest=localMatrixY.data;

		for(int i=0;i<9;i++)
		    *(dest++)=*(source++);
	}

	if(currentRotation[2])
	{
		rotationZ1=rotTablePtr[currentRotation[2]&0x3FF];
		rotationZ2=rotTablePtr[(currentRotation[2]+0x100)&0x3FF];

		double* source=localMatrixY.data;
		double* dest=tempMatrix->data;

		int var0=(int)*(source++);
		int var1=(int)*(source++);
		int var2=(int)*(source++);

	    *(dest++) = (var0 * rotationZ2 - var2 * rotationZ1) >> 14;
		*(dest++) = var1;
	    *(dest++) = (var0 * rotationZ1 + var2 * rotationZ2) >> 14;

		var0=(int)*(source++);
		var1=(int)*(source++);
		var2=(int)*(source++);

	    *(dest++) = (var0 * rotationZ2 - var2 * rotationZ1) >> 14;
		*(dest++) = var1;
	    *(dest++) = (var0 * rotationZ1 + var2 * rotationZ2) >> 14;

		var0=(int)*(source++);
		var1=(int)*(source++);
		var2=(int)*(source++);

	    *(dest++) = (var0 * rotationZ2 - var2 * rotationZ1) >> 14;
		*(dest++) = var1;
	    *(dest++) = (var0 * rotationZ1 + var2 * rotationZ2) >> 14;
	}
	else
	{
		double* source=localMatrixY.data;
		double* dest=tempMatrix->data;

		for(int i=0;i<9;i++)
		    *(dest++)=*(source++);
	}
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::ApplyRotationToPoints(TBodyPoint* point, int numOfPoints, TBodyPoint* dest, TMatrix* rotationMatrix)
{
	int i;

	for(i=0;i<numOfPoints;i++)
	{
		dest->X = (short int)(((rotationMatrix->data[0] * point->X + rotationMatrix->data[1] * point->Y + rotationMatrix->data[2] * point->Z) / 16384) + base[0]);
	        dest->Y = (short int)(((rotationMatrix->data[3] * point->X + rotationMatrix->data[4] * point->Y + rotationMatrix->data[5] * point->Z) / 16384) + base[1]);
	        dest->Z = (short int)(((rotationMatrix->data[6] * point->X + rotationMatrix->data[7] * point->Y + rotationMatrix->data[8] * point->Z) / 16384) + base[2]);

		dest++;
		point++;
	}
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::ApplyTranslationToPoints(TBodyPoint* point, int numOfPoints, TBodyPoint* dest, TMatrix* rotationMatrix)
{
	int i;

	for(i=0;i<numOfPoints;i++)
	{
		dest->X = (short int)((rotationMatrix->data[0] * (point->X+currentTranslation[0]) + rotationMatrix->data[1] * (point->Y+currentTranslation[2]) + rotationMatrix->data[2] * (point->Z+currentTranslation[1])) / 16384) + base[0];
	        dest->Y = (short int)((rotationMatrix->data[3] * (point->X+currentTranslation[0]) + rotationMatrix->data[4] * (point->Y+currentTranslation[2]) + rotationMatrix->data[5] * (point->Z+currentTranslation[1])) / 16384) + base[1];
	        dest->Z = (short int)((rotationMatrix->data[6] * (point->X+currentTranslation[0]) + rotationMatrix->data[7] * (point->Y+currentTranslation[2]) + rotationMatrix->data[8] * (point->Z+currentTranslation[1])) / 16384) + base[2];

		dest++;
		point++;
	}
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::ProcessRotatedElement(int rotX, int rotY, int rotZ, TElement* Element, TMatrix* matrixList,int i)
{
	TMatrix* currentMatrix;
	TMatrix* temporaryMatrix;
	TMatrix baseMatrix;

	temporaryMatrix=&matrixList[i];

	memset(&baseMatrix,0,sizeof(TMatrix));
	baseMatrix.data[0]=0x4000;
	baseMatrix.data[4]=0x4000;
	baseMatrix.data[8]=0x4000;

	currentRotation[0]=rotX;
	currentRotation[1]=rotY;
	currentRotation[2]=rotZ;

	if(Element->BaseElement==-1)
	{
		currentMatrix=&baseMatrix;

		base[0]=currentX;
		base[1]=currentY;
		base[2]=currentZ;
	}
	else
	{
		currentMatrix=&matrixList[Element->BaseElement/36];

		base[0]=(int)computedPoints[Element->BasePoint/6].X;
		base[1]=(int)computedPoints[Element->BasePoint/6].Y;
		base[2]=(int)computedPoints[Element->BasePoint/6].Z;
	}

	ApplyRotation(temporaryMatrix,currentMatrix);
	ApplyRotationToPoints(&Points->PointsData[Element->FirstPoint/6], Element->NumberOfPoints, &computedPoints[Element->FirstPoint/6],temporaryMatrix);
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::ProcessTranslatedElement(int transX, int transY, int transZ, TElement* Element,TMatrix* matrixList,int i)
{
	TMatrix* currentMatrix;
	TMatrix* temporaryMatrix;
	TMatrix baseMatrix;

	temporaryMatrix=&matrixList[i];

	memset(&baseMatrix,0,sizeof(TMatrix));
	baseMatrix.data[0]=0x4000;
	baseMatrix.data[4]=0x4000;
	baseMatrix.data[8]=0x4000;

	temporaryMatrix=&matrixList[i];

	currentTranslation[0]=transX;
	currentTranslation[1]=transY;
	currentTranslation[2]=transZ;

        if (Element->BaseElement==-1)	// base point
	{
		base[0]=currentX;
		base[1]=currentY;
		base[2]=currentZ;

		double* source=baseMatrix.data;
		double* dest=temporaryMatrix->data;

	        for(int i=0;i<9;i++)
		    *(dest++)=*(source++);
	}
        else			// dependent
	{
		base[0]=(int)computedPoints[Element->BasePoint/6].X;
		base[1]=(int)computedPoints[Element->BasePoint/6].Y;
		base[2]=(int)computedPoints[Element->BasePoint/6].Z;

		currentMatrix=&matrixList[Element->BaseElement/36];

		double* source=currentMatrix->data;
		double* dest=temporaryMatrix->data;

	        for(int i=0;i<9;i++)
		    *(dest++)=*(source++);
	}

    ApplyTranslationToPoints(&Points->PointsData[Element->FirstPoint/6], Element->NumberOfPoints, &computedPoints[Element->FirstPoint/6],temporaryMatrix);
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::RenderizeModel(unsigned char alphac)
{
	memset(matrixList,0,sizeof(TMatrix)*100);

	baseModelPosition[0]=0;
	baseModelPosition[1]=0;
	baseModelPosition[2]=0;

	TElement* elementPtr=Elements->ElementsData;

	ProcessRotatedElement(globalAngleX,globalAngleZ,globalAngleY,elementPtr,matrixList,0);
    ProcessTranslatedElement(globalAngleX,globalAngleZ,globalAngleY,elementPtr++,matrixList,0);

    for(int i=1;i<Elements->NumberOfElements;i++)
	{
	    if(elementPtr->ElementFlag==0)
    		ProcessRotatedElement(elementPtr->RotateX,elementPtr->RotateZ,elementPtr->RotateY,elementPtr,matrixList,i);
	    else if(elementPtr->ElementFlag==1)
		    ProcessTranslatedElement(elementPtr->RotateX,elementPtr->RotateZ,elementPtr->RotateY,elementPtr,matrixList,i);

		elementPtr++;
	}
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setBoneIdx(int value)
{
    boneIdx = value;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setPolyIdx(int value)
{
    polyIdx = value;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setPointIdx(int value)
{
    pointIdx = value;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setLineIdx(int value)
{
    lineIdx = value;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setSphereIdx(int value)
{
    sphereIdx = value;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setPointX(int point, double x)
{
    Points->PointsData[point].X = x;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setPointY(int point, double y)
{
    Points->PointsData[point].Y = y;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setPointZ(int point, double z)
{
    Points->PointsData[point].Z = z;
}

//---------------------------------------------------------------------------

double ServerLBA1ModelClass::getPointX(int point)
{
    return Points->PointsData[point].X;
}

//---------------------------------------------------------------------------

double ServerLBA1ModelClass::getPointY(int point)
{
    return Points->PointsData[point].Y;
}

//---------------------------------------------------------------------------

double ServerLBA1ModelClass::getPointZ(int point)
{
    return Points->PointsData[point].Z;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setElementRotateX(int element, short int x)
{
    Elements->ElementsData[element].RotateX = x;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setElementRotateY(int element, short int y)
{
    Elements->ElementsData[element].RotateY = y;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setElementRotateZ(int element, short int z)
{
    Elements->ElementsData[element].RotateZ = z;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getElementRotateX(int element)
{
    return Elements->ElementsData[element].RotateX;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getElementRotateY(int element)
{
    return Elements->ElementsData[element].RotateY;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getElementRotateZ(int element)
{
    return Elements->ElementsData[element].RotateZ;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getElementFlag(int element)
{
    return Elements->ElementsData[element].ElementFlag;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setElementFlag(int element, short int value)
{
    Elements->ElementsData[element].ElementFlag = value;
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::setAnimAtKeyFrame(int index, unsigned char *anim, TElements *elements, bool reset)
{
    short int numOfIndexInAnim;
    short int numOfPointInAnim;
    short int *ptrToData;
    int i;

	//m_cumuSpeed = 0;
	//m_cumuSpeedY = 0;
    currentKeyFrame = index;

    numOfIndexInAnim = *(short int *) anim;

    if (index >= numOfIndexInAnim)
	return (numOfIndexInAnim);

    numOfPointInAnim = *(short int *) (anim + 2);

    ptrToData = (short int *) ((numOfPointInAnim * 8 + 8) * index + anim + 8);

	lastAnimData=(char*)ptrToData;
	//time=globalTime;
	cumutime = 0;

	if (numOfPointInAnim > Elements->NumberOfElements)
	{
	    numOfPointInAnim = (short int)Elements->NumberOfElements;
	}

    ptrToData += 4;

	for(i=0;i<numOfPointInAnim;i++)
	{
		Elements->ElementsData[i].ElementFlag=*(ptrToData++);
		Elements->ElementsData[i].RotateX=*(ptrToData++);
		Elements->ElementsData[i].RotateY=*(ptrToData++);
		Elements->ElementsData[i].RotateZ=*(ptrToData++);
	}

    if(reset)
    {
        currentX = *(short int *) ptrToData;
        currentY = *(short int *) (ptrToData + 2);
        currentZ = *(short int *) (ptrToData + 4);
    }

    /*processActorVar5 = *(short int *) (ptrToData + 6);
    processActorSub2Var0 = *(short int *) (ptrToData + 8);
    processActorVar6 = *(short int *) (ptrToData + 10);
    processActorSub2Var1 = *(short int *) (ptrToData + 12); */

    return (1);
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::ApplyAnim(int animState, char *animPtr, TElements *elements)
{
    short int animOpcode;

    //int eax;
    float keyFrameLength;
    int numOfPointInAnim;
    char *keyFramePtrOld;

    numOfPointInAnim = *(short int *) (animPtr + 2);

    keyFramePtr = ((numOfPointInAnim * 8 + 8) * animState) + animPtr + 8;
    keyFrameLength = (*(short int *) keyFramePtr) * 10.0f * m_animationspeed;

	if (numOfPointInAnim > Elements->NumberOfElements)
	{
	    numOfPointInAnim = Elements->NumberOfElements;
	}

	lastKeyFramePtr=lastAnimData;
    //eax = globalTime - time;

	//std::cout<<cumutime<<" "<<keyFrameLength<<std::endl;

    if (cumutime >= keyFrameLength)
	{
	    short int *sourcePtr;
		int i;

		if(cumutime > 2*keyFrameLength)
			cumutime = 0;
		else
			cumutime -= keyFrameLength;

		//time=globalTime;
		lastAnimData=keyFramePtr;

	    sourcePtr = (short int *) (keyFramePtr + 8);

		for(i=0;i<numOfPointInAnim;i++)
		{
			Elements->ElementsData[i].ElementFlag=*(sourcePtr++);
			Elements->ElementsData[i].RotateX=*(sourcePtr++);
			Elements->ElementsData[i].RotateY=*(sourcePtr++);
			Elements->ElementsData[i].RotateZ=*(sourcePtr++);
		}

		keyFramePtr+=2;

		currentX = *(short int *) keyFramePtr;
		currentY = *(short int *) (keyFramePtr + 2);
		currentZ = *(short int *) (keyFramePtr + 4);


		/*processActorVar5 = *(short int *) (keyFramePtr + 6); // is jumping
		processActorSub2Var0 = *(short int *) (keyFramePtr + 8);
		processActorVar6 = *(short int *) (keyFramePtr + 10); // modelRotation
		processActorSub2Var1 = *(short int *) (keyFramePtr + 12);*/

	    return (1);
	}
    else
	{
		int i;

		keyFramePtrOld = keyFramePtr+2;

		currentX = ((*(short int *) keyFramePtrOld) * cumutime) / keyFrameLength;
		currentY = ((*(short int *) (keyFramePtrOld + 2)) * cumutime) / keyFrameLength;
		currentZ = ((*(short int *) (keyFramePtrOld + 4)) * cumutime) / keyFrameLength;

		//std::cout<<"curr"<<currentX<<" "<<currentY<<" "<<currentZ<<std::endl;
		m_currentSpeedX = (*(short int *) (keyFramePtrOld + 4)) / (keyFrameLength*512);
		m_currentSpeedY = (*(short int *) (keyFramePtrOld + 2)) / (keyFrameLength*256);
		m_currentSpeedZ = (*(short int *) (keyFramePtrOld)) / (keyFrameLength*512);

		/*processActorVar5 = *(short int *) (keyFramePtrOld + 6);
		processActorSub2Var0 = *(short int *) (keyFramePtrOld + 8);
		processActorVar6 = *(short int *) (keyFramePtrOld + 10);
		processActorSub2Var1 = *(short int *) (keyFramePtrOld + 12);*/

	    lastKeyFramePtr += 8;
	    keyFramePtr += 8;

	    lastKeyFramePtr += 8;
	    keyFramePtr += 8;

		for(i=1;i<numOfPointInAnim;i++)
		{
			animOpcode = Elements->ElementsData[i].ElementFlag;

		    lastKeyFramePtr += 2;
			keyFramePtr += 2;


			    switch (animOpcode)
				{
				case 0:
				   {
				       ApplyAnimMode0(&Elements->ElementsData[i].RotateX, cumutime, keyFrameLength);
				       ApplyAnimMode0(&Elements->ElementsData[i].RotateY, cumutime, keyFrameLength);
				       ApplyAnimMode0(&Elements->ElementsData[i].RotateZ, cumutime, keyFrameLength);
				       break;
				   }
				case 1:
				   {
				       ApplyAnimMode1(&Elements->ElementsData[i].RotateX, cumutime, keyFrameLength);
				       ApplyAnimMode1(&Elements->ElementsData[i].RotateY, cumutime, keyFrameLength);
				       ApplyAnimMode1(&Elements->ElementsData[i].RotateZ, cumutime, keyFrameLength);
				       break;
				   }
				case 2:
				   {
				       ApplyAnimMode1(&Elements->ElementsData[i].RotateX, cumutime, keyFrameLength);
				       ApplyAnimMode1(&Elements->ElementsData[i].RotateY, cumutime, keyFrameLength);
				       ApplyAnimMode1(&Elements->ElementsData[i].RotateZ, cumutime, keyFrameLength);
				       break;
				   }
				default:
				   {
				       printf("Unsupported rotaton mode %d in draw3D1!\n", animOpcode);
				       exit(1);
				   }
				}
	}
	}

    return (0);
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getAnimMaxIndex(char *ptr)
{
    return (*(short int *) ptr);
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getAnimStartIndex(char *ptr)
{
    return (*(short int *) (ptr + 4));
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getAnimOpcode(char **ptr)
{
    short int opcode;

    opcode = *(short int *) keyFramePtr;

    keyFramePtr += 2;
    *(ptr) = *(ptr) + 2;
    lastKeyFramePtr += 2;

    return (opcode);
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::ApplyAnimMode0(short int *ptr, float bp, float bx)
{
    short int lastAngle;
    short int newAngle;
    short int angleDif;
    short int computedAngle;

    lastAngle = *(short int *) lastKeyFramePtr;
    lastKeyFramePtr += 2;

    newAngle = *(short int *) keyFramePtr;
    keyFramePtr += 2;

    lastAngle &= 0x3FF;
    newAngle &= 0x3FF;

    angleDif = newAngle - lastAngle;

    if (angleDif)
	{
	    if (angleDif < -0x200)
		{
		    angleDif += 0x400;
		}
	    else if (angleDif > 0x200)
		{
		    angleDif -= 0x400;
		}

	    computedAngle = lastAngle + (angleDif * bp) / bx;
	}
    else
	{
	    computedAngle = lastAngle;
	}

    *ptr = computedAngle & 0x3FF;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::ApplyAnimMode1(short int *ptr, float bp, float bx)
{
    short int lastAngle;
    short int newAngle;
    short int angleDif;
    short int computedAngle;

    lastAngle = *(short int *) lastKeyFramePtr;
    lastKeyFramePtr += 2;

    newAngle = *(short int *) keyFramePtr;
    keyFramePtr += 2;

    angleDif = newAngle - lastAngle;

    if (angleDif)
	{
	    computedAngle = lastAngle + (angleDif * bp) / bx;
	}
    else
	{
	    computedAngle = lastAngle;
	}

    *ptr = computedAngle;

}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setModelParamElementFlag(int keyframe, int bone, int value)
{
  	int i;
	int numOfPointInAnim = *(short int *) (animPtr + 2);
        unsigned char *keyFramePtr = ((numOfPointInAnim * 8 + 8) * keyframe) + animPtr + 8;

	keyFramePtr += 8;

	for(i=0;i<bone;i++)
	{
		keyFramePtr += 8;
	}

	*(short int*)keyFramePtr = value;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setModelParamX(int keyframe, int bone, int X)
{
  	int i;
	int numOfPointInAnim = *(short int *) (animPtr + 2);
        unsigned char *keyFramePtr = ((numOfPointInAnim * 8 + 8) * keyframe) + animPtr + 8;

	keyFramePtr += 8;

	for(i=0;i<bone;i++)
	{
		keyFramePtr += 8;
	}

	keyFramePtr += 2;

	*(short int*)keyFramePtr = X;

	//Elements->ElementsData[bone].RotateX = X;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setModelParamY(int keyframe, int bone, int Y)
{
	int i;
	int numOfPointInAnim = *(short int *) (animPtr + 2);
        unsigned char *keyFramePtr = ((numOfPointInAnim * 8 + 8) * keyframe) + animPtr + 8;

	keyFramePtr += 8;

	for(i=0;i<bone;i++)
	{
		keyFramePtr += 8;
	}

	keyFramePtr += 4;

	*(short int*)keyFramePtr = Y;

   //	Elements->ElementsData[bone].RotateY = Y;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setModelParamZ(int keyframe, int bone, int Z)
{
	int i;
	int numOfPointInAnim = *(short int *) (animPtr + 2);
        unsigned char *keyFramePtr = ((numOfPointInAnim * 8 + 8) * keyframe) + animPtr + 8;

	keyFramePtr += 8;

	for(i=0;i<bone;i++)
	{
		keyFramePtr += 8;
	}

	keyFramePtr += 6;

	*(short int*)keyFramePtr = Z;

   //	Elements->ElementsData[bone].RotateZ = Z;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setAtKeyFrame(int keyframe, bool reset)
{
	setAnimAtKeyFrame(keyframe,animPtr,Elements, reset);
}

//---------------------------------------------------------------------------

bool ServerLBA1ModelClass::AnimateModel(float tdiff)
{
	//m_currentSpeed = 0;
	//m_currentSpeedY = 0;

	//long int oldTick;

	//oldTick = lastTick;
 //	lastTick=clock();

	//globalTime += (lastTick - oldTick)/10;
	cumutime += tdiff;


    lastCurrentX = currentX;
 	lastCurrentY = currentY;
 	lastCurrentZ = currentZ;

 	int keyFrameState=ApplyAnim(currentKeyFrame,(char*)animPtr,Elements);



        // CALCULATE STEP SIZE -----
 	int angle1;
	int angle2;

	if (!angle)
	{
		stepX = currentX;
		stepY = currentZ;
	}
   	else
   	{
		angle1 = rotTablePtr[angle & 0x3FF];
		angle2 = rotTablePtr[(angle + 0x100) & 0x3FF];

		stepX= (currentX * angle2 + currentZ * angle1) >> 14;
		stepY= (currentZ * angle2 - currentX * angle1) >> 14;
	}

        currentX = stepX;
       	currentZ = stepY;

		//m_currentSpeed = (currentZ /512.) - m_cumuSpeed;
		//m_cumuSpeed = (currentZ /512.);

		//m_currentSpeedY = (currentY /256.) - m_cumuSpeedY;
		//m_cumuSpeedY = (currentY /256.);
		

        if(m_useAnimSteps)
        {
            currentX = currentX/5 + lastCurrentX;
  	        currentY = currentY/5 + lastCurrentY;
            currentZ = currentZ/5 + lastCurrentZ;
        }
        else
        {
            currentX = 0;//lastCurrentX;
  	        currentY = 0;//lastCurrentY;
            currentZ = 0;//lastCurrentZ;
        }

        if(abs(currentX)>=7816 || abs(currentY)>=3908 || abs(currentZ)>=7816)
        {
                setAtKeyFrame(0,true);
        }



		//update geometry
		{
			memset(matrixList,0,sizeof(TMatrix)*100);

			baseModelPosition[0]=0;
			baseModelPosition[1]=0;
			baseModelPosition[2]=0;

			TElement* elementPtr=Elements->ElementsData;

			ProcessRotatedElement(globalAngleX,globalAngleZ,globalAngleY,elementPtr,matrixList,0);
			ProcessTranslatedElement(globalAngleX,globalAngleZ,globalAngleY,elementPtr++,matrixList,0);

			for(int i=1;i<Elements->NumberOfElements;i++)
			{
				if(elementPtr->ElementFlag==0)
    				ProcessRotatedElement(elementPtr->RotateX,elementPtr->RotateZ,elementPtr->RotateY,elementPtr,matrixList,i);
				else if(elementPtr->ElementFlag==1)
					ProcessTranslatedElement(elementPtr->RotateX,elementPtr->RotateZ,elementPtr->RotateY,elementPtr,matrixList,i);

				elementPtr++;
			}

			// POINTS CALCULATIONS -----------
			float* tempPtrX=dividedPointsX;
			float* tempPtrY=dividedPointsY;
			float* tempPtrZ=dividedPointsZ;

			TBodyPoint* tempPoint=computedPoints;

			for(int i=0;i<Points->NumberOfPoints;i++)
			{
				*(tempPtrX++)=(((float)tempPoint->X)/16384)*factormul_lba1_toosg;
				*(tempPtrY++)=((((float)tempPoint->Y)/16384)*factormul_lba1_toosg) + factortransY_lba1_toosg;
				*(tempPtrZ++)=(((float)tempPoint->Z)/16384)*factormul_lba1_toosg;

				tempPoint++;
			}
		}


		//{
		//	int count = 0;
		//	TPolygon* polyPtr;
		//	TVertex* vertexPtr;
		//	polyPtr=Polygons->PolygonsData;
		//	for(int i=0;i<Polygons->NumberOfPolygons;i++)
		//	{
		//		vertexPtr=polyPtr->VertexsData;
		//		for(int j=0;j<polyPtr->NumberOfVertexs;j++)
		//		{
		//			++count;
		//			vertexPtr++;
		//		}
		//		polyPtr++;
		//	}

		//	std::cout<<count<<std::endl;
		//}


        if(keyFrameState)
 	    {
			//m_cumuSpeed = 0;
			//m_cumuSpeedY = 0;
  		    currentKeyFrame++;
      		if(currentKeyFrame==getAnimMaxIndex((char*)animPtr))
  	    	{
 		    	currentKeyFrame=getAnimStartIndex((char*)animPtr);
				return true;
     		}
	    }

		return false;
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumBones(void)
{
	return(Elements->NumberOfElements-1);
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getNumKeyFrames(void)
{
	return(getAnimMaxIndex((char*)animPtr)-1);
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getCurrentType(void)
{
	return(Elements->ElementsData[currentBone].ElementFlag);
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getCurrentX(void)
{
	return(Elements->ElementsData[currentBone].RotateX);
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getCurrentY(void)
{
	return(Elements->ElementsData[currentBone].RotateY);
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getCurrentZ(void)
{
	return(Elements->ElementsData[currentBone].RotateZ);
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getPolygonColor(int index)
{
    return Polygons->PolygonsData[index].ColorIdx&0xFF;
}

//---------------------------------------------------------------------------
void ServerLBA1ModelClass::setPolygonColor(int index, short int color)
{
    Polygons->PolygonsData[index].ColorIdx = color&0xFF;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::changeAllPolygonColors(short int oldColor, short int newColor)
{
    for(int i=0; i < Polygons->NumberOfPolygons; i++)
    {
        if(getPolygonColor(i)==oldColor)
            setPolygonColor(i, newColor);
    }
}


//---------------------------------------------------------------------------
std::set<short> ServerLBA1ModelClass::GetAllPolygonColors()
{
	std::set<short> res;

    for(int i=0; i < Polygons->NumberOfPolygons; i++)
       res.insert(getPolygonColor(i));

	return res;
}



//---------------------------------------------------------------------------

void ServerLBA1ModelClass::changeAllLineColors(short int oldColor, short int newColor)
{
    for(int i=0; i < Lines->NumberOfLines; i++)
    {
        if(getLineColor(i)==oldColor)
            setLineColor(i, newColor);
    }
}


//---------------------------------------------------------------------------
std::set<short> ServerLBA1ModelClass::GetAllLineColors()
{
	std::set<short> res;

    for(int i=0; i < Lines->NumberOfLines; i++)
       res.insert(getLineColor(i));

	return res;
}


//---------------------------------------------------------------------------

void ServerLBA1ModelClass::changeAllSphereColors(short int oldColor, short int newColor)
{
    for(int i=0; i < Spheres->NumberOfSpheres; i++)
    {
        if(getSphereColor(i)==oldColor)
            setSphereColor(i, newColor);
    }
}


//---------------------------------------------------------------------------
std::set<short> ServerLBA1ModelClass::GetAllSphereColors()
{
	std::set<short> res;

    for(int i=0; i < Spheres->NumberOfSpheres; i++)
       res.insert(getSphereColor(i));

	return res;
}




//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getKeyframe(void)
{
	return currentKeyFrame;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::resetKeyframe()
{
	//m_cumuSpeed = 0;
	//m_cumuSpeedY = 0;
	currentKeyFrame = 0;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setEntity(int index)
{
	currentEntity = index;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setLineColor(int index, short int color)
{
    Lines->LinesData[index].Color = (color&0xFF)<<8;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getLineColor(int index)
{
    return (Lines->LinesData[index].Color&0xFF00)>>8;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getLinePoint1(int index)
{
    return Lines->LinesData[index].PointNum1/6;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getLinePoint2(int index)
{
    return Lines->LinesData[index].PointNum2/6;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setLinePoint1(int index, short int value)
{
    Lines->LinesData[index].PointNum1 = value * 6;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setLinePoint2(int index, short int value)
{
    Lines->LinesData[index].PointNum2 = value * 6;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setSphereColor(int index, short int color)
{
    Spheres->SpheresData[index].Color = (color&0xFF)<<8;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getSphereColor(int index)
{
    return (Spheres->SpheresData[index].Color&0xFF00)>>8;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getSphereSize(int index)
{
    return Spheres->SpheresData[index].Size; // /16384;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getSphereCenter(int index)
{
    return Spheres->SpheresData[index].Center/6;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setSphereSize(int index, short int value)
{
    Spheres->SpheresData[index].Size = value;// * 16384;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setSphereCenter(int index, short int value)
{
    Spheres->SpheresData[index].Center = value * 6;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::scaleModel(float factor)
{
    // scale points
    for(int p=0; p < Points->NumberOfPoints; p++)
    {
        Points->PointsData[p].X = (short int)(Points->PointsData[p].X * factor);
        Points->PointsData[p].Y = (short int)(Points->PointsData[p].Y * factor);
        Points->PointsData[p].Z = (short int)(Points->PointsData[p].Z * factor);
    }
    // scale spheres
    for(int sp=0; sp < Spheres->NumberOfSpheres; sp++)
    {
        Spheres->SpheresData[sp].Size = (short int)(Spheres->SpheresData[sp].Size * factor);
    }
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getStepPosX()
{
        return currentX;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getStepPosY()
{
        return currentY;
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getStepPosZ()
{
        return currentZ;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::resetStepPosX()
{
        currentX = 0;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::resetStepPosY()
{
        currentY = 0;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::resetStepPosZ()
{
        currentZ = 0;
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setKeyframeLength(int keyframe, short int value)
{
	int numOfPointInAnim = *(short int *) (animPtr + 2);
        unsigned char *keyFramePtr = ((numOfPointInAnim * 8 + 8) * keyframe) + animPtr + 8;

        keyFramePtr = ((numOfPointInAnim * 8 + 8) * keyframe) + animPtr + 8;
        *(short int *) keyFramePtr = value; // keyFrameLength
}

//---------------------------------------------------------------------------

short int ServerLBA1ModelClass::getKeyframeLength(int keyframe)
{
	int numOfPointInAnim = *(short int *) (animPtr + 2);
        unsigned char *keyFramePtr = ((numOfPointInAnim * 8 + 8) * keyframe) + animPtr + 8;

        keyFramePtr = ((numOfPointInAnim * 8 + 8) * keyframe) + animPtr + 8;
        return *(short int *) keyFramePtr; // keyFrameLength
}

//---------------------------------------------------------------------------

int ServerLBA1ModelClass::getLoopKeyframe()
{
    return (*(short int *) (animPtr + 4));
}

//---------------------------------------------------------------------------

void ServerLBA1ModelClass::setLoopKeyframe(short int value)
{
    (*(short int *) (animPtr + 4)) = value;
}
