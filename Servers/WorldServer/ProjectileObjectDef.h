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

#ifndef _PROJECTILE_OBJ_DEF_H__
#define _PROJECTILE_OBJ_DEF_H__

#include <string>
#include <LbaTypes.h>
#include "CommonTypes.h"

#include <boost/shared_ptr.hpp>

/***********************************************************************
class used by lua to add projectile objects on the map
 ***********************************************************************/
struct ProjectileObjectDef
{
public:
	//constructor
	ProjectileObjectDef();


	// set enum for render type as lua does not map enum
	//1 - RenderOsgModel
	//2 - RenderSprite
	//3 - RenderLba1M
	//4 - RenderLba2M
	void SetRenderType(int rtype);

	// set enum for PhysicalShape as lua does not map enum
	//1 - NoShape
	//2 - BoxShape
	//3 - CapsuleShape
	//4 - SphereShape
	//5 - TriangleMeshShape
	void SetPhysicalShape(int shape);

	// set enum for SetPhysicalActorType as lua does not map enum
	//1 - StaticAType - used for static npc
	//2 - KynematicAType - used for moving npc
	//3 - DynamicAType - used for dynamic object (not implemented)
	//4 - CharControlAType - used for object movable by the player
	void SetPhysicalActorType(int ptype);

	// accessors
	int GetRenderType();
	int GetPhysicalShape();
	int GetPhysicalActorType();


	// save to lua file
	void SaveToLuaFile(std::ostream & file, const std::string & nname);

	// get projectile info
	bool GetProjectileInfo(const std::string & mode, float manaleft, LbaNet::ProjectileInfo & info);


	LbaNet::ModelInfo			DisplayDesc;
	LbaNet::ObjectPhysicDesc	PhysicDesc;

	std::string					UsableMode;
		
	float						Power;
	float						UseMana;
	
	float						OffsetX;
	float						OffsetY;

	float						ForceX;
	float						ForceY;		
	float						ForceYOnImpact;
	
	int							NbBounce;
	bool						IgnoreGravity;
	
	float						LifeTime;
	bool						Comeback;
	
	int							StartAnimFrame;

	
	float						AngleOffset;
	
	std::string					SoundAtStart;
	std::string					SoundOnBounce;
	
	bool						ForceHurt;

		
	bool						MultiShoot;
		
	bool						UseTimer;
	float						Frequency;
};

typedef boost::shared_ptr<ProjectileObjectDef>	ProjectileObjectDefPtr;

#endif
