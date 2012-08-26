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

#include <LbaTypes.h>

class PhysXEngine;
class DynamicObject;
class NxActor;
class NxController;
class NavMeshAgent;

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
	DisplayObjectDescriptionBase(int sceneid)
		: _sceneid(sceneid)
	{}

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


protected:
	int		_sceneid;
};



/***********************************************************************
This is the base class describing a sprite
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class SpriteDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	SpriteDescription(int sceneid, const std::string & spritefile, bool UseLight, bool CastShadow,
							float colorR, float colorG, float colorB, float colorA,
							const LbaNet::ObjectExtraInfo &extrainfo,
							const LbaNet::LifeManaInfo &lifeinfo, bool UseBillboard)
		: DisplayObjectDescriptionBase(sceneid), _spritefile(spritefile), 
				_UseLight(UseLight), _CastShadow(CastShadow),
				_colorR(colorR), _colorG(colorG), _colorB(colorB), _colorA(colorA), 
					_extrainfo(extrainfo), _lifeinfo(lifeinfo), _UseBillboard(UseBillboard)
	{}

	//! destructor
	virtual ~SpriteDescription(){}

#ifndef _LBANET_SERVER_SIDE_
	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const;
#endif

private:
	std::string					_spritefile;
	bool						_UseLight;
	bool						_CastShadow;
	bool						_UseBillboard;

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
	OsgSimpleObjectDescription(int sceneid, const std::string & filename, bool UseLight, bool CastShadow,
								const LbaNet::ObjectExtraInfo &extrainfo,
								const LbaNet::LifeManaInfo & lifeinfo)
		: DisplayObjectDescriptionBase(sceneid), _filename(filename), 
			_UseLight(UseLight), _CastShadow(CastShadow), 
			_extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	//! destructor
	virtual ~OsgSimpleObjectDescription(){}

#ifndef _LBANET_SERVER_SIDE_
	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																			DisplayHandlerBase * disH) const;
#endif

private:
	std::string		_filename;
	bool			_UseLight;
	bool			_CastShadow;

	LbaNet::ObjectExtraInfo	_extrainfo;
	LbaNet::LifeManaInfo	_lifeinfo;
};



/***********************************************************************
This is the base class describing an cross
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class OsgCrossDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	OsgCrossDescription(int sceneid, float size, float colorR, float colorG, float colorB, float colorA,
								const LbaNet::ObjectExtraInfo &extrainfo,
								const LbaNet::LifeManaInfo &lifeinfo)
		: DisplayObjectDescriptionBase(sceneid), _size(size), _colorR(colorR), 
				_colorG(colorG), _colorB(colorB), _colorA(colorA), 
				_extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	//! destructor
	virtual ~OsgCrossDescription(){}

#ifndef _LBANET_SERVER_SIDE_
	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const;
#endif

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
This is the base class describing an box
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class OsgBoxDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	OsgBoxDescription(int sceneid, float sizex, float sizey, float sizez, 
							float colorR, float colorG, float colorB, float colorA,
							const LbaNet::ObjectExtraInfo &extrainfo,
							const LbaNet::LifeManaInfo &lifeinfo)
		: DisplayObjectDescriptionBase(sceneid), _sizex(sizex), _sizey(sizey),
					_sizez(sizez), _colorR(colorR),
					_colorG(colorG), _colorB(colorB), _colorA(colorA), 
					_extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	//! destructor
	virtual ~OsgBoxDescription(){}

#ifndef _LBANET_SERVER_SIDE_
	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const;
#endif

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
	OsgOrientedCapsuleDescription(int sceneid, float height, float radius,
									float colorR, float colorG, float colorB, float colorA,
									const LbaNet::ObjectExtraInfo &extrainfo,
									const LbaNet::LifeManaInfo &lifeinfo)
		: DisplayObjectDescriptionBase(sceneid), _height(height), _radius(radius), _colorR(colorR),
					_colorG(colorG), _colorB(colorB), _colorA(colorA), 
					_extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	//! destructor
	virtual ~OsgOrientedCapsuleDescription(){}

#ifndef _LBANET_SERVER_SIDE_
	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const;
#endif

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
This is the base class describing an sphere
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class OsgSphereDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	OsgSphereDescription(int sceneid, float radius,
									float colorR, float colorG, float colorB, float colorA,
									const LbaNet::ObjectExtraInfo &extrainfo,
									const LbaNet::LifeManaInfo &lifeinfo)
		: DisplayObjectDescriptionBase(sceneid), _radius(radius), _colorR(colorR),
					_colorG(colorG), _colorB(colorB), _colorA(colorA), 
					_extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	//! destructor
	virtual ~OsgSphereDescription(){}

#ifndef _LBANET_SERVER_SIDE_
	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const;
#endif

private:
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
	Lba1ModelObjectDescription(int sceneid, const LbaNet::ModelInfo & info, float animationspeed,
								bool UseLight, bool CastShadow,
								const LbaNet::ObjectExtraInfo &extrainfo,
								const LbaNet::LifeManaInfo &lifeinfo,
								bool mainchar)
		: DisplayObjectDescriptionBase(sceneid), _info(info), _animationspeed(animationspeed), 
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
This is the base class describing an Oriented Capsule
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class ImageBGDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	ImageBGDescription(const std::string & imagefile,
							float colorR, float colorG, float colorB, float colorA)
		: DisplayObjectDescriptionBase(-1), _imagefile(imagefile), 
				_colorR(colorR), _colorG(colorG), _colorB(colorB), _colorA(colorA)
	{}

	//! destructor
	virtual ~ImageBGDescription(){}

#ifndef _LBANET_SERVER_SIDE_
	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const;
#endif

private:
	std::string					_imagefile;
	float						_colorR;
	float						_colorG;
	float						_colorB;
	float						_colorA;
};



/***********************************************************************
This is the base class describing an Oriented Capsule
See definition in OsgObjectHandler.cpp
 ***********************************************************************/
class OsgParticleDescription : public DisplayObjectDescriptionBase
{
public:
	//! constructor
	OsgParticleDescription(int sceneid, const LbaNet::ParticleType &type,
									const LbaNet::ParticleExtraInfoBasePtr &info,
									const LbaNet::ObjectExtraInfo &extrainfo,
									const LbaNet::LifeManaInfo &lifeinfo)
		: DisplayObjectDescriptionBase(sceneid), _type(type), _info(info), 
					_extrainfo(extrainfo), _lifeinfo(lifeinfo)
	{}

	//! destructor
	virtual ~OsgParticleDescription(){}

#ifndef _LBANET_SERVER_SIDE_
	//! build description into dynamic object
	virtual boost::shared_ptr<DisplayObjectHandlerBase> BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const;
#endif

private:
	LbaNet::ParticleType				_type;
	LbaNet::ParticleExtraInfoBasePtr	_info;

	LbaNet::ObjectExtraInfo				_extrainfo;
	LbaNet::LifeManaInfo				_lifeinfo;
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
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(int type, long id,
										boost::shared_ptr<PhysicalDescriptionBase> self) const = 0;

	//! change size
	virtual bool ResetSize(float sX, float sY, float sZ) {return false;}
	virtual NxActor* RebuildActor(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata){ return NULL;}
	virtual NxController* RebuildController(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata){ return NULL;}


	//! build description into dynamic object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildServer(long id,
										boost::shared_ptr<PhysicalDescriptionBase> self,
										boost::shared_ptr<NavMeshAgent> NavMAgent) const;

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
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(int type, long id,
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

	//! build description into a reald physic object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(int type, long id,
									boost::shared_ptr<PhysicalDescriptionBase> self) const
	{return boost::shared_ptr<PhysicalObjectHandlerBase>();}

	//! build description into dynamic object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildServer(long id,
										boost::shared_ptr<PhysicalDescriptionBase> self,
										boost::shared_ptr<NavMeshAgent> NavMAgent) const;
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
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(int type, long id,
										boost::shared_ptr<PhysicalDescriptionBase> self) const;

	//! change size
	virtual bool ResetSize(float sX, float sY, float sZ);

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
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(int type, long id,
										boost::shared_ptr<PhysicalDescriptionBase> self) const;

	//! change size
	virtual bool ResetSize(float sX, float sY, float sZ);

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
									bool Collidable,
									float Bounciness, float StaticFriction, float DynamicFriction);

	//! destructor
	virtual ~PhysicalDescriptionSphere();


	//! build description into a reald physic object
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(int type, long id,
										boost::shared_ptr<PhysicalDescriptionBase> self) const;

	//! change size
	virtual bool ResetSize(float sX, float sY, float sZ);

	virtual NxActor* RebuildActor(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata);
	virtual NxController* RebuildController(float X, float Y, float Z, boost::shared_ptr<ActorUserData> udata);

public:
	// radius of the sphere from capsule sphere
	float radius;

	// keep sizeY
	float sizeY;

	float bounciness;
	float staticFriction;
	float dynamicFriction;
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
	virtual boost::shared_ptr<PhysicalObjectHandlerBase> BuildSelf(int type, long id,
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
	ObjectInfo(int type, long oid, boost::shared_ptr<DisplayInfo> DInfo,
				boost::shared_ptr<PhysicalDescriptionBase> PInfo,
				bool Static);

	//! destructor
	virtual ~ObjectInfo();

	//! build description into dynamic object
	boost::shared_ptr<DynamicObject> BuildSelf(DisplayHandlerBase * disH) const;

	//! build description into dynamic object
	boost::shared_ptr<DynamicObject> BuildServer(boost::shared_ptr<NavMeshAgent> NavMAgent) const;


	//get object id
	long GetId() const {return Id;}

	// Extract display info
	static boost::shared_ptr<DisplayInfo> ExtractDisplayInfo(int sceneid, const LbaNet::ModelInfo &DisplayDesc,
																const LbaNet::ObjectExtraInfo &extrainfo,
																const LbaNet::LifeManaInfo &lifeinfo,
																bool mainchar, float SizeX);

public:
	boost::shared_ptr<DisplayInfo>				DisInfo;
	boost::shared_ptr<PhysicalDescriptionBase>	PhysInfo;
	bool										IsStatic;
	long										Id;
	int 						Type;
};



#endif
