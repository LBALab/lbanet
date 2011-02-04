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

#ifndef LBA1ModelClassH
#define LBA1ModelClassH

#include "Entities.h"
#include <vector>
#include <set>
#include <osg/Node>
#include <osg/Geometry>
#include <osg/PositionAttitudeTransform>

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

class LBA1ModelClass
{
private:
	int currentEntity;

    TBodyHeader Header;
    TPoints *Points;
    TElements *Elements;
    TShades *Shades;
    TPolygons *Polygons;
    TLines *Lines;
    TSpheres *Spheres;

	float *dividedPointsX;
	float *dividedPointsY;
	float *dividedPointsZ;

	short int shadeTable[1000];

	int polyDataSize;

	int baseModelPosition[3];
	TBodyPoint computedPoints[1000];
	int currentRotation[3];
	int currentTranslation[3];
	int base[3];
	int currentKeyFrame;
	int lightPosition[3];

	char* lastAnimData;
	char* keyFramePtr;
	char* lastKeyFramePtr;

    unsigned char* bodyPtr;
    unsigned char* bodyHeaderPtr;
	unsigned char* animPtr;
	//int time;
	//int globalTime;
	//int lastTick;


	int X1;
	int X2;
	int Z1;
	int Z2;
	int Y1;
	int Y2;

    int boneIdx;
    int polyIdx;
    int pointIdx;
    int lineIdx;
    int sphereIdx;
    int filesize;
    int animsize;
    bool useAnim;

    void LoadModel(unsigned char* bodyPtr);

	TPoints* LoadPoints(unsigned char* bodyPtr);
	TElements* LoadElements(unsigned char* bodyPtr);
	TShades* LoadShades(unsigned char* bodyPtr);
	TPolygons* LoadPolys(unsigned char* bodyPtr);
	TLines* LoadLines(unsigned char* bodyPtr);
	TSpheres* LoadSpheres(unsigned char* bodyPtr);

	int getNumOfPointsInModel(unsigned char* bodyPtr);
	int getNumOfElementsInModel(unsigned char* bodyPtr);
	int getNumOfShadesInModel(unsigned char* bodyPtr);
	int getNumOfPolysInModel(unsigned char* bodyPtr);
	int getNumOfLinesInModel(unsigned char* bodyPtr);
	int getNumOfSpheresInModel(unsigned char* bodyPtr);

	unsigned char* getPointsPtr(unsigned char* bodyPtr);
	unsigned char* getElementsPtr(unsigned char* bodyPtr);
	unsigned char* getShadesPtr(unsigned char* bodyPtr);
	unsigned char* getPolysPtr(unsigned char* bodyPtr);
	unsigned char* getLinesPtr(unsigned char* bodyPtr);
	unsigned char* getSpheresPtr(unsigned char* bodyPtr);

	void ProcessRotatedElement(int rotX, int rotY, int rotZ, TElement* Element,TMatrix* matrixList,int i);
	void ProcessTranslatedElement(int rotX, int rotY, int rotZ, TElement* Element,TMatrix* matrixList,int i);

	void ApplyRotation(TMatrix* tempMatrix,TMatrix* currentMatrix);
	void ApplyRotationToPoints(TBodyPoint* point, int numOfPoints, TBodyPoint* dest,TMatrix* rotationMatrix);
	void ApplyTranslationToPoints(TBodyPoint* point, int numOfPoints, TBodyPoint* dest,TMatrix* rotationMatrix);

	int setAnimAtKeyFrame(int index, unsigned char *anim, TElements *Elements, bool reset);
	int ApplyAnim(int animState, char *animData, TElements *Elements);
	int getAnimMaxIndex(char *ptr);
   	int getAnimStartIndex(char *ptr);
	int getAnimOpcode(char **ptr);
	void ApplyAnimMode0(short int *ptr, float bp, float bx);
	void ApplyAnimMode1(short int *ptr, float bp, float bx);

	TMatrix matrixList[100];

	int lastCurrentX;
	int lastCurrentY;
	int lastCurrentZ;


	std::string m_animPath;

	bool m_softShade;
	int m_wireFrame;
	bool m_showSelectedPolygon;
	bool m_showBones;
	bool m_showPoint;
	bool m_showLine;
	bool m_showSphere;
	bool m_showCollisionBox;
	bool m_useAnimSteps;

	unsigned char*	m_paletteRGB;

	float cumutime;

	float m_animationspeed;

	double m_currentSpeedX;
	double m_currentSpeedY;
	double m_currentSpeedZ;


	osg::ref_ptr<osg::Geometry> m_myGeometry;
	std::vector<osg::ref_ptr<osg::PositionAttitudeTransform> > m_Spheres;
	osg::ref_ptr<osg::Geometry> m_myGeometrylines;
	osg::ref_ptr<osg::Geometry> m_myGeometrynorms;

	bool m_usesoftshadow;

public:

	short int processActorVar5;
	short int processActorSub2Var0;
	short int processActorVar6;
	short int processActorSub2Var1;

	int stepX;
	int stepY;

	int speed;

	short int currentX;
	short int currentY;
	short int currentZ;

	int globalAngleX;
	int globalAngleY;
	int globalAngleZ;

	int currentBone;

	int angle;


	LBA1ModelClass(entitiesTableStruct* entitiesData, const std::string &bodyPath, 
					const std::string &animPath, int entityNum=0,int bodyNum=0);
	~LBA1ModelClass();

    void LoadAnim(entitiesTableStruct* entitiesData, int animNum=0);

	void RenderizeModel(unsigned char alphac);

    void DrawSelectedPolygon(int index, unsigned char alphac);
    void DrawBones(int index, unsigned char alphac);
    void DrawPoints(int index, unsigned char alphac);
    void DrawLines(int index, unsigned char alphac);
    void DrawSpheres(int index, unsigned char alphac);
    void DrawColisionBox(unsigned char alphac);
    void DXFExport(char *fileName);

    void setBoneIdx(int value);
    void setPolyIdx(int value);
    void setPointIdx(int value);
    void setLineIdx(int value);
    void setSphereIdx(int value);

    void setPointX(int point, double x);
    void setPointY(int point, double y);
    void setPointZ(int point, double z);
    double getPointX(int point);
    double getPointY(int point);
    double getPointZ(int point);

    void setElementRotateX(int element, short int x);
    void setElementRotateY(int element, short int y);
    void setElementRotateZ(int element, short int z);
    short int getElementRotateX(int element);
    short int getElementRotateY(int element);
    short int getElementRotateZ(int element);
    short int getElementFlag(int element);
    void setElementFlag(int element, short int value);

    int getNumPoints();
    int getNumElements();
    int getNumShades();
    int getNumPolygons();
    int getNumVertexs();
    int getNumLines();
    int getNumSpheres();
    int getFileSize();
    bool canUseAnim();

	bool AnimateModel(float tdiff);
    void setModelParamElementFlag(int keyframe, int bone, int value);
	void setModelParamX(int keyframe, int bone, int X);
	void setModelParamY(int keyframe, int bone, int Y);
	void setModelParamZ(int keyframe, int bone, int Z);
	void setAtKeyFrame(int keyframe, bool reset);
    int getLoopKeyframe();
    void setLoopKeyframe(short int value);

	int getNumBones(void);
	int getNumKeyFrames(void);

	int getCurrentType(void);
	int getCurrentX(void);
	int getCurrentY(void);
	int getCurrentZ(void);

    void setPolygonColor(int index, short int color);
    short int getPolygonColor(int index);
    void changeAllPolygonColors(short int oldColor, short int newColor);
	std::set<short> GetAllUsedColors();

    int getKeyframe(void);
    void resetKeyframe();
    void setEntity(int index);

    void setLineColor(int index, short int color);
    short int getLineColor(int index);
    short int getLinePoint1(int index);
    short int getLinePoint2(int index);
    void setLinePoint1(int index, short int value);
    void setLinePoint2(int index, short int value);

    void setSphereColor(int index, short int color);
    short int getSphereColor(int index);
    short int getSphereSize(int index);
    short int getSphereCenter(int index);
    void setSphereSize(int index, short int value);
    void setSphereCenter(int index, short int value);

    void scaleModel(float factor);

    short int getStepPosX();
    short int getStepPosY();
    short int getStepPosZ();
    void resetStepPosX();
    void resetStepPosY();
    void resetStepPosZ();

    void setKeyframeLength(int keyframe, short int value);
    short int getKeyframeLength(int keyframe);

	double GetCurrentSpeedX() { return m_currentSpeedX; }
	double GetCurrentSpeedY() { return m_currentSpeedY; }
	double GetCurrentSpeedZ() { return m_currentSpeedZ; }

	// set the animation speed factor
	void SetAnimationSpeedFactor(float animationspeed)
	{m_animationspeed = animationspeed;}


	osg::ref_ptr<osg::Node> ExportOSGModel(bool usesoftshadow);
};

#endif