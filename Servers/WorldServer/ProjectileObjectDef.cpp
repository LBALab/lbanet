#include "ProjectileObjectDef.h"
#include <fstream>
#include "ObjectsDescription.h"
#include "DynamicObject.h"
#include <math.h>


/***********************************************************
constructor
***********************************************************/
ProjectileObjectDef::ProjectileObjectDef()
{
	DisplayDesc.State = LbaNet::NoState;

	DisplayDesc.RotX = 0;
	DisplayDesc.RotY = 0;
	DisplayDesc.RotZ = 0;

	DisplayDesc.TransX = 0;
	DisplayDesc.TransY = 0;
	DisplayDesc.TransZ = 0;

	DisplayDesc.ScaleX = 1;
	DisplayDesc.ScaleY = 1;
	DisplayDesc.ScaleZ = 1;

	DisplayDesc.SkinColor = -1;
	DisplayDesc.EyesColor = -1;
	DisplayDesc.HairColor = -1;
	DisplayDesc.OutfitColor = -1;
	DisplayDesc.WeaponColor = -1;
	DisplayDesc.MountSkinColor = -1;
	DisplayDesc.MountHairColor = -1;

	DisplayDesc.ModelId = 0;
	DisplayDesc.ColorR = 1;
	DisplayDesc.ColorG = 1;
	DisplayDesc.ColorB = 1;
	DisplayDesc.ColorA = 1;

	DisplayDesc.UseBillboard = false;

	DisplayDesc.UseTransparentMaterial = false;
	DisplayDesc.MatAlpha = 1;
		
	DisplayDesc.TypeRenderer = LbaNet::NoRender;
	DisplayDesc.ColorMaterialType = 0;
	DisplayDesc.MatAmbientColorR = 0.2f;
	DisplayDesc.MatAmbientColorG = 0.2f;
	DisplayDesc.MatAmbientColorB = 0.2f;
	DisplayDesc.MatAmbientColorA = 1;			
	DisplayDesc.MatDiffuseColorR = 0.8f;
	DisplayDesc.MatDiffuseColorG = 0.8f;
	DisplayDesc.MatDiffuseColorB = 0.8f;
	DisplayDesc.MatDiffuseColorA = 1;
	DisplayDesc.MatSpecularColorR = 0;
	DisplayDesc.MatSpecularColorG = 0;
	DisplayDesc.MatSpecularColorB = 0;
	DisplayDesc.MatSpecularColorA = 1;	
	DisplayDesc.MatEmissionColorR = 0;
	DisplayDesc.MatEmissionColorG = 0;
	DisplayDesc.MatEmissionColorB = 0;
	DisplayDesc.MatEmissionColorA = 1;
	DisplayDesc.MatShininess = 0;	


	PhysicDesc.TypePhysO = LbaNet::DynamicAType;
	PhysicDesc.Density = 1;
	PhysicDesc.SizeX = 0.5f;
	PhysicDesc.SizeY = 0.5f;
	PhysicDesc.SizeZ = 0.5f;
	PhysicDesc.Pos.X = 0;
	PhysicDesc.Pos.Y = 0;
	PhysicDesc.Pos.Z = 0;
	PhysicDesc.Pos.Rotation = 0;
	PhysicDesc.Collidable = false;
	PhysicDesc.TypeShape = LbaNet::SphereShape;


	Power = 0;
	UseMana = 0;
	
	OffsetX = 0;
	OffsetY = 0;
	OffsetZ = 0;

	ForceX = 0;
	ForceY = 0;		
	ForceYOnImpact = 0;
	
	NbBounce = 1;
	IgnoreGravity = false;
	
	LifeTime = 1;
	Comeback = false;
	
	StartAnimFrame = -1;
	MultiShoot = false;
	UseTimer = false;
	Frequency = 1;
	
	AngleOffset = 0;
	
	ForceHurt = false;
}





/***********************************************************
	// set enum for render type as lua does not map enum
	//1 - RenderOsgModel
	//2 - RenderSprite
	//3 - RenderLba1M
	//4 - RenderLba2M
***********************************************************/
void ProjectileObjectDef::SetRenderType(int rtype)
{
	switch(rtype)
	{
		case 0:
			DisplayDesc.TypeRenderer = LbaNet::NoRender;
		break;
		case 1:
			DisplayDesc.TypeRenderer = LbaNet::RenderOsgModel;
		break;
		case 2:
			DisplayDesc.TypeRenderer = LbaNet::RenderSprite;
		break;
		case 3:
			DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
		break;
		case 4:
			DisplayDesc.TypeRenderer = LbaNet::RenderLba2M;
		break;
		case 5:
			DisplayDesc.TypeRenderer = LbaNet::RenderCross;
		break;
		case 6:
			DisplayDesc.TypeRenderer = LbaNet::RenderBox;
		break;
		case 7:
			DisplayDesc.TypeRenderer = LbaNet::RenderCapsule;
		break;
		case 8:
			DisplayDesc.TypeRenderer = LbaNet::RenderSphere;
		break;
	}
}


/***********************************************************
	// set enum for PhysicalShape as lua does not map enum
	//1 - NoShape
	//2 - BoxShape
	//3 - CapsuleShape
	//4 - SphereShape
	//5 - TriangleMeshShape
***********************************************************/
void ProjectileObjectDef::SetPhysicalShape(int shape)
{
	switch(shape)
	{
		case 1:
			PhysicDesc.TypeShape = LbaNet::NoShape;
		break;
		case 2:
			PhysicDesc.TypeShape = LbaNet::BoxShape;
		break;
		case 3:
			PhysicDesc.TypeShape = LbaNet::CapsuleShape;
		break;
		case 4:
			PhysicDesc.TypeShape = LbaNet::SphereShape;
		break;
		case 5:
			PhysicDesc.TypeShape = LbaNet::TriangleMeshShape;
		break;
	}
}

	
/***********************************************************
	// set enum for SetPhysicalActorType as lua does not map enum
	//1 - StaticAType
	//2 - KynematicAType
	//3 - DynamicAType
	//4 - CharControlAType
***********************************************************/
void ProjectileObjectDef::SetPhysicalActorType(int ptype)
{
	switch(ptype)
	{
		case 1:
			PhysicDesc.TypePhysO = LbaNet::StaticAType;
		break;
		case 2:
			PhysicDesc.TypePhysO = LbaNet::KynematicAType;
		break;
		case 3:
			PhysicDesc.TypePhysO = LbaNet::DynamicAType;
		break;
		case 4:
			PhysicDesc.TypePhysO = LbaNet::CharControlAType;
		break;
	}
}



/***********************************************************
accessor
***********************************************************/
int ProjectileObjectDef::GetRenderType()
{
	switch(DisplayDesc.TypeRenderer)
	{
		case LbaNet::RenderOsgModel:
			return 1;
		break;
		case LbaNet::RenderSprite:
			return 2;
		break;
		case LbaNet::RenderLba1M:
			return 3;
		break;
		case LbaNet::RenderLba2M:
			return 4;
		break;
		case LbaNet::RenderCross:
			return 5;
		break;
		case LbaNet::RenderBox:
			return 6;
		break;
		case LbaNet::RenderCapsule:
			return 7;
		break;
		case LbaNet::RenderSphere:
			return 8;
		break;
	}

	return 0;
}

/***********************************************************
accessor
***********************************************************/
int ProjectileObjectDef::GetPhysicalShape()
{
	switch(PhysicDesc.TypeShape)
	{
		case LbaNet::NoShape:
			return 1;
		break;
		case LbaNet::BoxShape:
			return 2;
		break;
		case LbaNet::CapsuleShape:
			return 3;
		break;
		case LbaNet::SphereShape:
			return 4;
		break;
		case LbaNet::TriangleMeshShape:
			return 5;
		break;
	}

	return 0;
}

/***********************************************************
accessor
***********************************************************/
int ProjectileObjectDef::GetPhysicalActorType()
{
	switch(PhysicDesc.TypePhysO)
	{
		case LbaNet::StaticAType:
			return 1;
		break;
		case LbaNet::KynematicAType:
			return 2;
		break;
		case LbaNet::DynamicAType:
			return 3;
		break;
		case LbaNet::CharControlAType:
			return 4;
		break;
	}

	return 0;
}


/***********************************************************
save to lua file
***********************************************************/
void ProjectileObjectDef::SaveToLuaFile(std::ostream & file, const std::string & nname)
{
	file<<"\t"<<nname<<" = ProjectileObjectDef()"<<std::endl;

	file<<"\t"<<nname<<":SetRenderType("<<GetRenderType()<<")"<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.ModelId = "<<DisplayDesc.ModelId<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.ModelName = \""<<DisplayDesc.ModelName<<"\""<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.Outfit = \""<<DisplayDesc.Outfit<<"\""<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.Weapon = \""<<DisplayDesc.Weapon<<"\""<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.Mode = \""<<DisplayDesc.Mode<<"\""<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.UseLight = "<<(DisplayDesc.UseLight?"true":"false")<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.CastShadow = "<<(DisplayDesc.CastShadow?"true":"false")<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.ColorR = "<<DisplayDesc.ColorR<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.ColorG = "<<DisplayDesc.ColorG<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.ColorB = "<<DisplayDesc.ColorB<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.ColorA = "<<DisplayDesc.ColorA<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.TransX = "<<DisplayDesc.TransX<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.TransY = "<<DisplayDesc.TransY<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.TransZ = "<<DisplayDesc.TransZ<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.ScaleX = "<<DisplayDesc.ScaleX<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.ScaleY = "<<DisplayDesc.ScaleY<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.ScaleZ = "<<DisplayDesc.ScaleZ<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.RotX = "<<DisplayDesc.RotX<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.RotY = "<<DisplayDesc.RotY<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.RotZ = "<<DisplayDesc.RotZ<<std::endl;
	file<<"\t"<<nname<<".DisplayDesc.UseBillboard = "<<(DisplayDesc.UseBillboard?"true":"false")<<std::endl;
	
	if(DisplayDesc.UseTransparentMaterial)
	{
		file<<"\t"<<nname<<".DisplayDesc.UseTransparentMaterial = true"<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatAlpha = "<<DisplayDesc.MatAlpha<<std::endl;
	}

	if(DisplayDesc.ColorMaterialType > 0)
	{
		file<<"\t"<<nname<<".DisplayDesc.ColorMaterialType = "<<DisplayDesc.ColorMaterialType<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatAmbientColorR = "<<DisplayDesc.MatAmbientColorR<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatAmbientColorG = "<<DisplayDesc.MatAmbientColorG<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatAmbientColorB = "<<DisplayDesc.MatAmbientColorB<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatAmbientColorA = "<<DisplayDesc.MatAmbientColorA<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatDiffuseColorR = "<<DisplayDesc.MatDiffuseColorR<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatDiffuseColorG = "<<DisplayDesc.MatDiffuseColorG<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatDiffuseColorB = "<<DisplayDesc.MatDiffuseColorB<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatDiffuseColorA = "<<DisplayDesc.MatDiffuseColorA<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatSpecularColorR = "<<DisplayDesc.MatSpecularColorR<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatSpecularColorG = "<<DisplayDesc.MatSpecularColorG<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatSpecularColorB = "<<DisplayDesc.MatSpecularColorB<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatSpecularColorA = "<<DisplayDesc.MatSpecularColorA<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatEmissionColorR = "<<DisplayDesc.MatEmissionColorR<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatEmissionColorG = "<<DisplayDesc.MatEmissionColorG<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatEmissionColorB = "<<DisplayDesc.MatEmissionColorB<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatEmissionColorA = "<<DisplayDesc.MatEmissionColorA<<std::endl;
		file<<"\t"<<nname<<".DisplayDesc.MatShininess = "<<DisplayDesc.MatShininess<<std::endl;
	}


	file<<"\t"<<nname<<".PhysicDesc.Pos.X = "<<PhysicDesc.Pos.X<<std::endl;
	file<<"\t"<<nname<<".PhysicDesc.Pos.Y = "<<PhysicDesc.Pos.Y<<std::endl;
	file<<"\t"<<nname<<".PhysicDesc.Pos.Z = "<<PhysicDesc.Pos.Z<<std::endl;
	file<<"\t"<<nname<<".PhysicDesc.Pos.Rotation = "<<PhysicDesc.Pos.Rotation<<std::endl;
	file<<"\t"<<nname<<".PhysicDesc.Density = "<<PhysicDesc.Density<<std::endl;
	file<<"\t"<<nname<<".PhysicDesc.Collidable = "<<(PhysicDesc.Collidable?"true":"false")<<std::endl;
	file<<"\t"<<nname<<".PhysicDesc.SizeX = "<<PhysicDesc.SizeX<<std::endl;
	file<<"\t"<<nname<<".PhysicDesc.SizeY = "<<PhysicDesc.SizeY<<std::endl;
	file<<"\t"<<nname<<".PhysicDesc.SizeZ = "<<PhysicDesc.SizeZ<<std::endl;
	file<<"\t"<<nname<<".PhysicDesc.AllowFreeMove = "<<(PhysicDesc.AllowFreeMove?"true":"false")<<std::endl;
	file<<"\t"<<nname<<".PhysicDesc.Filename = \""<<PhysicDesc.Filename<<"\""<<std::endl;
	file<<"\t"<<nname<<":SetPhysicalActorType("<<GetPhysicalActorType()<<")"<<std::endl;
	file<<"\t"<<nname<<":SetPhysicalShape("<<GetPhysicalShape()<<")"<<std::endl;


	file<<"\t"<<nname<<".UsableMode = \""<<UsableMode<<"\""<<std::endl;
		
	file<<"\t"<<nname<<".Power = "<<Power<<std::endl;
	file<<"\t"<<nname<<".UseMana = "<<UseMana<<std::endl;
	
	file<<"\t"<<nname<<".OffsetX = "<<OffsetX<<std::endl;
	file<<"\t"<<nname<<".OffsetY = "<<OffsetY<<std::endl;
	file<<"\t"<<nname<<".OffsetZ = "<<OffsetY<<std::endl;

	file<<"\t"<<nname<<".ForceX = "<<ForceX<<std::endl;
	file<<"\t"<<nname<<".ForceY = "<<ForceY<<std::endl;		
	file<<"\t"<<nname<<".ForceYOnImpact = "<<ForceYOnImpact<<std::endl;
	
	file<<"\t"<<nname<<".NbBounce = "<<NbBounce<<std::endl;
	file<<"\t"<<nname<<".IgnoreGravity = "<<(IgnoreGravity?"true":"false")<<std::endl;
	
	file<<"\t"<<nname<<".LifeTime = "<<LifeTime<<std::endl;
	file<<"\t"<<nname<<".Comeback = "<<(Comeback?"true":"false")<<std::endl;
	
	file<<"\t"<<nname<<".StartAnimFrame = "<<StartAnimFrame<<std::endl;
	
	file<<"\t"<<nname<<".AngleOffset = "<<AngleOffset<<std::endl;
	
	file<<"\t"<<nname<<".SoundAtStart = \""<<SoundAtStart<<"\""<<std::endl;
	file<<"\t"<<nname<<".SoundOnBounce = \""<<SoundOnBounce<<"\""<<std::endl;
	
	file<<"\t"<<nname<<".ForceHurt = "<<(ForceHurt?"true":"false")<<std::endl;

	file<<"\t"<<nname<<".MultiShoot = "<<(MultiShoot?"true":"false")<<std::endl;

	file<<"\t"<<nname<<".UseTimer = "<<(UseTimer?"true":"false")<<std::endl;
	file<<"\t"<<nname<<".Frequency = "<<Frequency<<std::endl;
}


/***********************************************************
get projectile info
***********************************************************/
bool ProjectileObjectDef::GetProjectileInfo(const std::string & mode, float manaleft, 
											LbaNet::ProjectileInfo & info)
{
	if(mode != UsableMode)
		return false;

	info.DisplayDesc = DisplayDesc;
	info.PhysicDesc = PhysicDesc;

	info.Comeback = Comeback;
	info.Power = Power;
	info.OffsetX = OffsetX;
	info.OffsetY = OffsetY;
	info.OffsetZ = OffsetZ;
	info.StartAnimFrame = StartAnimFrame;
	info.IgnoreGravity = IgnoreGravity;
	info.ForceX = ForceX;
	info.ForceY = ForceY;
	info.ForceYOnImpact = ForceYOnImpact;
	info.LifeTime = LifeTime;
	info.NbBounce = ((manaleft<UseMana) ? 1 : NbBounce);

	info.AngleOffset = AngleOffset;
	
	info.SoundAtStart = SoundAtStart;
	info.SoundOnBounce = SoundOnBounce;
	info.ForceHurt = ForceHurt;

	info.MultiShoot = MultiShoot;

	info.UseTimer = UseTimer;
	info.Frequency = Frequency;


	return true;
}