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

#include "ObjectsDescription.h"
#include "WorldToDisplayObjectSynchronizer.h"
#include "StaticObject.h"

#ifndef _LBANET_SERVER_SIDE_
#include "Lba1ModelHandler.h"
#include "SoundObjectHandlerClient.h"
#endif
#include "ServerLba1ModelHandler.h"
#include "NavMeshObjectHandlers.h"
#include "SoundObjectHandlerServer.h"


/***********************************************************
	Constructor
***********************************************************/
DisplayTransformation::DisplayTransformation()
:translationX(0), translationY(0), translationZ(0),
	scaleX(1),	scaleY(1), scaleZ(1)
{
}




/***********************************************************
	destructor
***********************************************************/
DisplayTransformation::~DisplayTransformation()
{

}




/***********************************************************
	Constructor
***********************************************************/
DisplayInfo::DisplayInfo(boost::shared_ptr<DisplayTransformation> Tr, 
					boost::shared_ptr<DisplayObjectDescriptionBase> Ds)
	: Transform(Tr), DisplayDesc(Ds)
{

}



/***********************************************************
	Destructor
***********************************************************/
DisplayInfo::~DisplayInfo()
{

}





/***********************************************************
build description into dynamic object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> DisplayInfo::BuildServer() const
{
	if(DisplayDesc)
		return DisplayDesc->BuildServer();
	
	return boost::shared_ptr<DisplayObjectHandlerBase>();
}



/***********************************************************
	Constructor
***********************************************************/
PhysicalDescriptionBase::PhysicalDescriptionBase(float posX, float posY, float posZ, 
												 const LbaQuaternion &rot)
: 	positionX(posX), positionY(posY), positionZ(posZ), rotation(rot)
{

}


/***********************************************************
	Destructor
***********************************************************/
PhysicalDescriptionBase::~PhysicalDescriptionBase()
{

}




/***********************************************************
	Constructor
***********************************************************/
PhysicalDescriptionNoShape::PhysicalDescriptionNoShape(float posX, float posY, float posZ, 
													   const LbaQuaternion &rot)
: PhysicalDescriptionBase(posX, posY, posZ, rot)
{

}

/***********************************************************
	destructor
***********************************************************/
PhysicalDescriptionNoShape::~PhysicalDescriptionNoShape()
{

}


/***********************************************************
 build description into a reald physic object
***********************************************************/
boost::shared_ptr<PhysicalObjectHandlerBase> PhysicalDescriptionNoShape::BuildSelf(int type, long id,
												boost::shared_ptr<PhysicalDescriptionBase> self) const
{
	return boost::shared_ptr<PhysicalObjectHandlerBase>( 
				new SimplePhysicalObjectHandler(positionX, positionY, positionZ, rotation));
}






/***********************************************************
	Constructor
***********************************************************/
PhysicalDescriptionWithShape::PhysicalDescriptionWithShape(float posX, float posY, float posZ,
															LbaNet::PhysicalActorType Otype, float Odensity,
															const LbaQuaternion &rot,
															bool Collidable)
: PhysicalDescriptionBase(posX, posY, posZ, rot), ActorType(Otype), 
	density(Odensity), collidable(Collidable)
{

}

/***********************************************************
	destructor
***********************************************************/
PhysicalDescriptionWithShape::~PhysicalDescriptionWithShape()
{

}


/***********************************************************
	Constructor
***********************************************************/
ObjectInfo::ObjectInfo(int type, long oid, boost::shared_ptr<DisplayInfo> DInfo,
				boost::shared_ptr<PhysicalDescriptionBase> PInfo,
				bool Static)
	: DisInfo(DInfo), PhysInfo(PInfo), IsStatic(Static), Id(oid), Type(type)
{

}



/***********************************************************
	destructor
***********************************************************/
ObjectInfo::~ObjectInfo()
{

}

#ifndef _LBANET_SERVER_SIDE_


/***********************************************************
build description into dynamic object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> DisplayInfo::BuildSelf(DisplayHandlerBase * disH) const
{
	if(DisplayDesc)
		return DisplayDesc->BuildSelf(Transform, disH);
	
	return boost::shared_ptr<DisplayObjectHandlerBase>();
}

/***********************************************************
build description into dynamic object
***********************************************************/
boost::shared_ptr<DynamicObject> ObjectInfo::BuildSelf(DisplayHandlerBase * disH) const
{
	boost::shared_ptr<PhysicalObjectHandlerBase> phH;
	boost::shared_ptr<DisplayObjectHandlerBase> disoH;
	if(PhysInfo)
		phH = PhysInfo->BuildSelf(Type, Id, PhysInfo);
	if(DisInfo)
		disoH = DisInfo->BuildSelf(disH);

	if(!IsStatic && phH && disH)
		return boost::shared_ptr<DynamicObject>(new WorldToDisplayObjectSynchronizer(phH, disoH,
		boost::shared_ptr<SoundObjectHandlerBase>(new SoundObjectHandlerClient()), Id));
	else
		return boost::shared_ptr<DynamicObject>(new StaticObject(phH, disoH,
		boost::shared_ptr<SoundObjectHandlerBase>(new SoundObjectHandlerClient()), Id));
}





/***********************************************************
build description into dynamic object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> SpriteDescription::BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const
{
	if(disH)
		return disH->CreateSpriteObject(_spritefile, _colorR, _colorG, _colorB, _colorA, 
											Tr, _UseLight, _CastShadow, _extrainfo, _lifeinfo, _UseBillboard);

	return boost::shared_ptr<DisplayObjectHandlerBase> ();
}





/***********************************************************
build description into dynamic object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgSimpleObjectDescription::BuildSelf(
															boost::shared_ptr<DisplayTransformation> Tr,
															DisplayHandlerBase * disH) const
{
	if(disH)
		return disH->CreateSimpleObject(_filename, Tr, _UseLight, _CastShadow, _extrainfo, _lifeinfo);

	return boost::shared_ptr<DisplayObjectHandlerBase> ();
}


/***********************************************************
build description into dynamic object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgCrossDescription::BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const
{
	if(disH)
		return disH->CreateCrossObject(_size, _colorR, _colorG, _colorB, _colorA, Tr, _extrainfo, _lifeinfo);

	return boost::shared_ptr<DisplayObjectHandlerBase> ();
}


/***********************************************************
build description into dynamic object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgBoxDescription::BuildSelf(boost::shared_ptr<DisplayTransformation> Tr, 
																				DisplayHandlerBase * disH) const
{
	if(disH)
		return disH->CreateBoxObject(_sizex, _sizey, _sizez, _colorR, _colorG, _colorB, _colorA, Tr, _extrainfo, _lifeinfo);

	return boost::shared_ptr<DisplayObjectHandlerBase> ();
}


/***********************************************************
build description into dynamic object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgOrientedCapsuleDescription::BuildSelf(
															boost::shared_ptr<DisplayTransformation> Tr,
															DisplayHandlerBase * disH) const
{
	if(disH)
		return disH->CreateCapsuleObject(_radius, _height, _colorR, _colorG, _colorB, _colorA, Tr, _extrainfo, _lifeinfo);

	return boost::shared_ptr<DisplayObjectHandlerBase> ();
}


/***********************************************************
build description into dynamic object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> OsgSphereDescription::BuildSelf(
															boost::shared_ptr<DisplayTransformation> Tr,
															DisplayHandlerBase * disH) const
{
	if(disH)
		return disH->CreateSphereObject(_radius, _colorR, _colorG, _colorB, _colorA, Tr, _extrainfo, _lifeinfo);

	return boost::shared_ptr<DisplayObjectHandlerBase> ();
}



/***********************************************************
build description into dynamic object
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> Lba1ModelObjectDescription::BuildSelf(
															boost::shared_ptr<DisplayTransformation> Tr,
															DisplayHandlerBase * disH) const
{
	return boost::shared_ptr<DisplayObjectHandlerBase> (
					new Lba1ModelHandler( Tr, _info, _animationspeed, _UseLight, 
												_CastShadow, _extrainfo, _lifeinfo, _mainchar));
}

#endif

/***********************************************************
 build description into a reald physic object
***********************************************************/
boost::shared_ptr<PhysicalObjectHandlerBase> PhysicalDescriptionBase::BuildServer(long id,
												boost::shared_ptr<PhysicalDescriptionBase> self,
												boost::shared_ptr<NavMeshAgent> NavMAgent) const
{
	return boost::shared_ptr<PhysicalObjectHandlerBase>( 
				new SimplePhysicalObjectHandler(positionX, positionY, positionZ, rotation));
}


/***********************************************************
build description into dynamic object for server
***********************************************************/
boost::shared_ptr<DisplayObjectHandlerBase> Lba1ModelObjectDescription::BuildServer()
{
	return boost::shared_ptr<DisplayObjectHandlerBase> (
					new ServerLba1ModelHandler( _info, _animationspeed ));
}



/***********************************************************
build description into dynamic object for server
***********************************************************/
boost::shared_ptr<DynamicObject> ObjectInfo::BuildServer(boost::shared_ptr<NavMeshAgent> NavMAgent) const
{
	boost::shared_ptr<PhysicalObjectHandlerBase> phH;
	boost::shared_ptr<DisplayObjectHandlerBase> disoH;
	if(PhysInfo)
		phH = PhysInfo->BuildServer(Id, PhysInfo, NavMAgent);
	if(DisInfo)
		disoH = DisInfo->BuildServer();


	return boost::shared_ptr<DynamicObject>(new StaticObject(phH, disoH, 
		boost::shared_ptr<SoundObjectHandlerBase>(new SoundObjectHandlerServer()), Id));
}


/***********************************************************
 build description into a reald physic object
***********************************************************/
boost::shared_ptr<PhysicalObjectHandlerBase> PhysicalDescriptionWithShape::BuildServer(long id,
													boost::shared_ptr<PhysicalDescriptionBase> self,
													boost::shared_ptr<NavMeshAgent> NavMAgent) const
{
	if(NavMAgent && ActorType != LbaNet::StaticAType)
		return boost::shared_ptr<PhysicalObjectHandlerBase>( 
				new NavMeshObjectHandler(NavMAgent, positionX, positionY, positionZ, rotation));
	else
		return boost::shared_ptr<PhysicalObjectHandlerBase>( 
				new SimplePhysicalObjectHandler(positionX, positionY, positionZ, rotation));
}
