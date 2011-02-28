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


#ifndef __LBA_NET_OBJECTS_DESCRIPTION_H__
#define __LBA_NET_OBJECTS_DESCRIPTION_H__

#include <boost/shared_ptr.hpp>
#include "PhysicalObjectHandlerBase.h"
#include "DisplayObjectHandlerBase.h"
#include "CommonTypes.h"
#include "DisplayHandlerBase.h"

class PhysXEngine;
class DynamicObject;
class NxActor;
class NxController;

/***********************************************************************
This class describe the tranformation applied by the display object
before being drwan on the screen
 ***********************************************************************/
class DisplayTransformation
{
public:
	//! constructor
	DisplayTransformation();

	//! destructor
	~DisplayTransformation();

public:
	// translations
	float translationX;
	float translationY;
	float translationZ;

	//rotations
	LbaQuaternion rotation;

	//scaling
	float scaleX;
	float scaleY;
	float scaleZ;
};


/***********************************************************************
This is the base class describing the object to be drawn
 ***********************************************************************/
class DisplayObjectDescriptionBase
{
public:
	//! constructor
	DisplayObjectDescriptionBase(){}

	//! destructor
	virtual ~DisplayObjectDescriptionBase(){}

#ifndef _LBANET_SERVER_SIDE_
	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr,
																	DisplayHandlerBase * disH) const = 0;
#endif

	//! build description into dynamic object for server
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildServer()
	{return boost::shared_ptr<DisplayObjectHandlerBase>();}

};



/***********************************************************************
This is the base class describing an Oriented Capsule
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class SpriteDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	SpriteDescription(const std::string & spritefile, bool UseLight, bool CastShadow,
							float colorR, float colorG, float colorB, float colorA,
							const LbaNet::ObjectExtraInfo &extrainfo,
							const LbaNet::LifeManaInfo &lifeinfo)
		: _spritefile(spritefile), _UseLight(UseLight), _CastShadow(CastShadow),
				_colorR(colorR), _colorG(colorG), _colorB(colorB), _colorA(colorA), 
					_extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	//! destructor
	virtual ~SpriteDescription(){}


	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const;


private:
	std::string					_spritefile;
	bool						_UseLight;
	bool						_CastShadow;

	float						_colorR;
	float						_colorG;
	float						_colorB;
	float						_colorA;

	LbaNet::ObjectExtraInfo		_extrainfo;
	LbaNet::LifeManaInfo		_lifeinfo;
};



/***********************************************************************
This is the base class describing a simple OSG object loaded from file
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class OsgSimpleObjectDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	OsgSimpleObjectDescription(const std::string & filename, bool UseLight, bool CastShadow,
								const LbaNet::ObjectExtraInfo &extrainfo,
								const LbaNet::LifeManaInfo & lifeinfo)
		: _filename(filename), _UseLight(UseLight), _CastShadow(CastShadow), 
			_extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	//! destructor
	virtual ~OsgSimpleObjectDescription(){}

	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																			DisplayHandlerBase * disH) const;


private:
	std::string		_filename;
	bool			_UseLight;
	bool			_CastShadow;

	LbaNet::ObjectExtraInfo	_extrainfo;
	LbaNet::LifeManaInfo	_lifeinfo;

};



/***********************************************************************
This is the base class describing an Oriented Capsule
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class OsgCrossDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	OsgCrossDescription(float size, float colorR, float colorG, float colorB, float colorA,
								const LbaNet::ObjectExtraInfo &extrainfo,
								const LbaNet::LifeManaInfo &lifeinfo)
		: _size(size), _colorR(colorR), _colorG(colorG), _colorB(colorB), _colorA(colorA), 
				_extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	//! destructor
	virtual ~OsgCrossDescription(){}


	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const;

private:
	float _size;

	float _colorR;
	float _colorG;
	float _colorB;
	float _colorA;

	LbaNet::ObjectExtraInfo	_extrainfo;
	LbaNet::LifeManaInfo	_lifeinfo;
};


/***********************************************************************
This is the base class describing an Oriented Capsule
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class OsgBoxDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	OsgBoxDescription(float sizex, float sizey, float sizez, 
							float colorR, float colorG, float colorB, float colorA,
							const LbaNet::ObjectExtraInfo &extrainfo,
							const LbaNet::LifeManaInfo &lifeinfo)
		: _sizex(sizex), _sizey(sizey), _sizez(sizez), _colorR(colorR),
					_colorG(colorG), _colorB(colorB), _colorA(colorA), 
					_extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	//! destructor
	virtual ~OsgBoxDescription(){}


	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const;

private:
	float _sizex;
	float _sizey;
	float _sizez;

	float _colorR;
	float _colorG;
	float _colorB;
	float _colorA;

	LbaNet::ObjectExtraInfo	_extrainfo;
	LbaNet::LifeManaInfo	_lifeinfo;
};




/***********************************************************************
This is the base class describing an Oriented Capsule
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class OsgOrientedCapsuleDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	OsgOrientedCapsuleDescription(float height, float radius,
									float colorR, float colorG, float colorB, float colorA,
									const LbaNet::ObjectExtraInfo &extrainfo,
									const LbaNet::LifeManaInfo &lifeinfo)
		: _height(height), _radius(radius), _colorR(colorR),
					_colorG(colorG), _colorB(colorB), _colorA(colorA), 
					_extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	//! destructor
	virtual ~OsgOrientedCapsuleDescription(){}


	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const;

private:
	float _height;
	float _radius;

	float _colorR;
	float _colorG;
	float _colorB;
	float _colorA;

	LbaNet::ObjectExtraInfo	_extrainfo;
	LbaNet::LifeManaInfo	_lifeinfo;
};





/***********************************************************************
This is the base class describing a Lba1 model
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class Lba1ModelObjectDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	Lba1ModelObjectDescription(const LbaNet::ModelInfo & info, float animationspeed,
								bool UseLight, bool CastShadow,
								const LbaNet::ObjectExtraInfo &extrainfo,
								const LbaNet::LifeManaInfo &lifeinfo,
								bool mainchar)
		: _info(info), _animationspeed(animationspeed), 
				_extrainfo(extrainfo), _lifeinfo(lifeinfo), _UseLight(UseLight),
				_CastShadow(CastShadow), _mainchar(mainchar)
	{}

	//! destructor
	virtual ~Lba1ModelObjectDescription(){}

#ifndef _LBANET_SERVER_SIDE_
	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																			DisplayHandlerBase * disH) const;
#endif


	//! build description into dynamic object for server
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildServer();


private:
	LbaNet::ModelInfo		_info;
	float					_animationspeed;
	bool					_UseLight;
	bool					_CastShadow;

	LbaNet::ObjectExtraInfo	_extrainfo;
	LbaNet::LifeManaInfo	_lifeinfo;
	bool					_mainchar;
};




/***********************************************************************
This class regroup the object display description and transformation
 ***********************************************************************/
class DisplayInfo
{
public:
	//! constructor
	DisplayInfo(boost::shared_ptr<DisplayTransformation> Tr,
					boost::shared_ptr<DisplayObjectDescriptionBase> Ds);

	//! destructor
	~DisplayInfo();

	//! build description into dynamic object
	boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(DisplayHandlerBase * disH) const;

	//! build description into dynamic object
	boost::shared_ptr<DisplayObjectHandlerBase> BuildServer() const;

public:
	boost::shared_ptr<DisplayTransformation>		Transform;
	boost::shared_ptr<DisplayObjectDescriptionBase> DisplayDesc;
};




/***********************************************************************
This base class describe the physicall information of an object
E.g. position in world - shape of the physical object
 ***********************************************************************/
class PhysicalDescriptionBase
{
public:
	//! constructor
	PhysicalDescriptionBase(float posX, float posY, float posZ, const LbaQuaternion &rot);


	//! destructor
	virtual ~PhysicalDescriptionBase();

	//! build description into a reald physic object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(long id,
										boost::shared_ptr<PhysicalDescriptionBase> self) const = 0;

	//! change size
	virtual void ResetSize(float sX, float sY, float sZ) {}
	virtual NxActor* RebuildActor(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata){ return NULL;}
	virtual NxController* RebuildController(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata){ return NULL;}


	//! build description into dynamic object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildServer(long id,
										boost::shared_ptr<PhysicalDescriptionBase> self) const;

public:
	//position of the object in the world
	float positionX;
	float positionY;
	float positionZ;

	// rotation applied to the shape
	LbaQuaternion rotation;
};


/***********************************************************************
This base class describe physical object with no shape
 ***********************************************************************/
class PhysicalDescriptionNoShape : public PhysicalDescriptionBase
{
public:
	//! constructor
	PhysicalDescriptionNoShape(float posX, float posY, float posZ, const LbaQuaternion &rot);

	//! destructor
	virtual ~PhysicalDescriptionNoShape();

	//! build description into a reald physic object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(long id,
										boost::shared_ptr<PhysicalDescriptionBase> self) const;

};


/***********************************************************************
This base class describe physical object with shape
 ***********************************************************************/
class PhysicalDescriptionWithShape : public PhysicalDescriptionBase
{
public:
	//! constructor
	PhysicalDescriptionWithShape(float posX, float posY, float posZ,
									LbaNet::PhysicalActorType Otype, float Odensity,
									const LbaQuaternion &rot,
									bool Collidable);

	//! destructor
	virtual ~PhysicalDescriptionWithShape();

public:

	// type of physical shape
	// 1= static
	// 2= kynematic
	// 3= dynamic
	// 4= character controller
	LbaNet::PhysicalActorType ActorType;

	// density of the object
	float density;

	// flag if object is collidable or not
	bool collidable;
};


/***********************************************************************
This class describe a box shape
See definition in PhysXObjectHandlerBase.cpp
 ***********************************************************************/
class PhysicalDescriptionBox : public PhysicalDescriptionWithShape
{
public:
	//! constructor
	PhysicalDescriptionBox(float posX, float posY, float posZ,
									LbaNet::PhysicalActorType Otype, float Odensity,
									const LbaQuaternion &rot,
									float sX, float sY, float sZ,
									bool Collidable);
	//! destructor
	virtual ~PhysicalDescriptionBox();


	//! build description into a reald physic object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(long id,
										boost::shared_ptr<PhysicalDescriptionBase> self) const;

	//! change size
	virtual void ResetSize(float sX, float sY, float sZ);

	virtual NxActor* RebuildActor(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata);
	virtual NxController* RebuildController(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata);

public:
	// size of the box from the box center
	float sizeX;
	float sizeY;
	float sizeZ;
};


/***********************************************************************
This class describe a capsule shape
See definition in PhysXObjectHandlerBase.cpp
 ***********************************************************************/
class PhysicalDescriptionCapsule : public PhysicalDescriptionWithShape
{
public:
	//! constructor
	PhysicalDescriptionCapsule(float posX, float posY, float posZ,
									LbaNet::PhysicalActorType Otype, float Odensity,
									const LbaQuaternion &rot,
									float sX, float sY,
									bool Collidable);

	//! destructor
	virtual ~PhysicalDescriptionCapsule();


	//! build description into a reald physic object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(long id,
										boost::shared_ptr<PhysicalDescriptionBase> self) const;

	//! change size
	virtual void ResetSize(float sX, float sY, float sZ);

	virtual NxActor* RebuildActor(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata);
	virtual NxController* RebuildController(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata);

public:
	// radius of the capsule from capsule center
	float radius;

	// height of the capsule
	float height;

	// keep sizeY
	float sizeY;
};


/***********************************************************************
This class describe a sphere shape
See definition in PhysXObjectHandlerBase.cpp
 ***********************************************************************/
class PhysicalDescriptionSphere : public PhysicalDescriptionWithShape
{
public:
	//! constructor
	PhysicalDescriptionSphere(float posX, float posY, float posZ,
									LbaNet::PhysicalActorType Otype, float Odensity,
									const LbaQuaternion &rot,
									float sY,
									bool Collidable);

	//! destructor
	virtual ~PhysicalDescriptionSphere();


	//! build description into a reald physic object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(long id,
										boost::shared_ptr<PhysicalDescriptionBase> self) const;

	//! change size
	virtual void ResetSize(float sX, float sY, float sZ);

	virtual NxActor* RebuildActor(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata);
	virtual NxController* RebuildController(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata);

public:
	// radius of the sphere from capsule sphere
	float radius;

	// keep sizeY
	float sizeY;
};


/***********************************************************************
This class describe a triangle mesh shape
Only use for static shape object with no rotation
See definition in PhysXObjectHandlerBase.cpp
 ***********************************************************************/
class PhysicalDescriptionTriangleMesh : public PhysicalDescriptionWithShape
{
public:
	//! constructor
	PhysicalDescriptionTriangleMesh(float posX, float posY, float posZ,
										const LbaQuaternion &rot,
										const std::string &FileName,
										bool Collidable);
	//! destructor
	virtual ~PhysicalDescriptionTriangleMesh();


	//! build description into a reald physic object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(long id,
										boost::shared_ptr<PhysicalDescriptionBase> self) const;


public:
	// path of the file describing the mesh
	std::string MeshInfoDataFileName;
};




/***********************************************************************
This class describe an object physical shape and display shape
 ***********************************************************************/
class ObjectInfo
{
public:
	//! default constructor
	ObjectInfo(){}

	//! constructor
	ObjectInfo(long oid, boost::shared_ptr<DisplayInfo> DInfo,
				boost::shared_ptr<PhysicalDescriptionBase> PInfo,
				bool Static);

	//! destructor
	virtual ~ObjectInfo();

	//! build description into dynamic object
	boost::shared_ptr<DynamicObject> BuildSelf(DisplayHandlerBase * disH) const;

	//! build description into dynamic object
	boost::shared_ptr<DynamicObject> BuildServer() const;


	//get object id
	long GetId() const {return Id;}

public:
	boost::shared_ptr<DisplayInfo>				DisInfo;
	boost::shared_ptr<PhysicalDescriptionBase>	PhysInfo;
	bool										IsStatic;
	long										Id;
};



#endif
