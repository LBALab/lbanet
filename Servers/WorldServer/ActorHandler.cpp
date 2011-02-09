#include "ActorHandler.h"
#include <fstream>
#include "ScriptEnvironmentBase.h"
#include "ObjectsDescription.h"
#include "DynamicObject.h"


#define	_LBA1_MODEL_ANIMATION_SPEED_	1.8f


/***********************************************************
constructor
***********************************************************/
ActorObjectInfo::ActorObjectInfo(long id)
: ObjectId(id)
{
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
}





/***********************************************************
	// set enum for render type as lua does not map enum
	//1 - RenderOsgModel
	//2 - RenderSprite
	//3 - RenderLba1M
	//4 - RenderLba2M
***********************************************************/
void ActorObjectInfo::SetRenderType(int rtype)
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
void ActorObjectInfo::SetPhysicalShape(int shape)
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
void ActorObjectInfo::SetPhysicalActorType(int ptype)
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
	// set the model state - used by lua instead of  the enum
	//1 - NoState
	//2 - StNormal
	//3 - StDying
	//4 - StDrowning
	//5 - StDrowningGas
	//6 - StBurning
	//7 - StSmallHurt
	//8 - StMediumHurt
	//9 - StBigHurt
	//10 - StHurtFall
	//11 - StFinishedFall
	//12 - StFalling
	//13 - StJumping
	//14 - StMovingObject
	//15 - StUseWeapon
	//16 - StImmune
	//17 - StHidden
	//18 - StScripted
	//19 - StProtectedHurt
	//20 - StRestrictedMovingObject
	//21 - StFighting
***********************************************************/
void ActorObjectInfo::SetModelState(int state)
{
	switch(state)
	{
		case 1:
			DisplayDesc.State = LbaNet::NoState;
		break;
		case 2:
			DisplayDesc.State = LbaNet::StNormal;
		break;
		case 3:
			DisplayDesc.State = LbaNet::StDying;
		break;
		case 4:
			DisplayDesc.State = LbaNet::StDrowning;
		break;
		case 5:
			DisplayDesc.State = LbaNet::StDrowningGas;
		break;
		case 6:
			DisplayDesc.State = LbaNet::StBurning;
		break;
		case 7:
			DisplayDesc.State = LbaNet::StSmallHurt;
		break;
		case 8:
			DisplayDesc.State = LbaNet::StMediumHurt;
		break;
		case 9:
			DisplayDesc.State = LbaNet::StBigHurt;
		break;
		case 10:
			DisplayDesc.State = LbaNet::StHurtFall;
		break;
		case 11:
			DisplayDesc.State = LbaNet::StFinishedFall;
		break;
		case 12:
			DisplayDesc.State = LbaNet::StFalling;
		break;
		case 13:
			DisplayDesc.State = LbaNet::StJumping;
		break;
		case 14:
			DisplayDesc.State = LbaNet::StMovingObject;
		break;
		case 15:
			DisplayDesc.State = LbaNet::StUseWeapon;
		break;
		case 16:
			DisplayDesc.State = LbaNet::StImmune;
		break;
		case 17:
			DisplayDesc.State = LbaNet::StHidden;
		break;
		case 18:
			DisplayDesc.State = LbaNet::StScripted;
		break;
		case 19:
			DisplayDesc.State = LbaNet::StProtectedHurt;
		break;
		case 20:
			DisplayDesc.State = LbaNet::StRestrictedMovingObject;
		break;
		case 21:
			DisplayDesc.State = LbaNet::StFighting;
		break;
	}
}


/***********************************************************
accessor
***********************************************************/
int ActorObjectInfo::GetRenderType()
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
	}

	return 0;
}

/***********************************************************
accessor
***********************************************************/
int ActorObjectInfo::GetPhysicalShape()
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
int ActorObjectInfo::GetPhysicalActorType()
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
accessor
***********************************************************/
int ActorObjectInfo::GetModelState()
{
	switch(DisplayDesc.State)
	{
		case LbaNet::NoState:
			return 1;
		break;
		case LbaNet::StNormal:
			return 2;
		break;
		case LbaNet::StDying:
			return 3;
		break;
		case LbaNet::StDrowning:
			return 4;
		break;
		case LbaNet::StDrowningGas:
			return 5;
		break;
		case LbaNet::StBurning:
			return 6;
		break;
		case LbaNet::StSmallHurt:
			return 7;
		break;
		case LbaNet::StMediumHurt:
			return 8;
		break;
		case LbaNet::StBigHurt:
			return 9;
		break;
		case LbaNet::StHurtFall:
			return 10;
		break;
		case LbaNet::StFinishedFall:
			return 11;
		break;
		case LbaNet::StFalling:
			return 12;
		break;
		case LbaNet::StJumping:
			return 13;
		break;
		case LbaNet::StMovingObject:
			return 14;
		break;
		case LbaNet::StUseWeapon:
			return 15;
		break;
		case LbaNet::StImmune:
			return 16;
		break;
		case LbaNet::StHidden:
			return 17;
		break;
		case LbaNet::StScripted:
			return 18;
		break;
		case LbaNet::StProtectedHurt:
			return 19;
		break;
		case LbaNet::StRestrictedMovingObject:
			return 20;
		break;
		case LbaNet::StFighting:
			return 21;
		break;
	}

	return 0;
}


 /***********************************************************
used by lua to add color swap to object info
***********************************************************/
void ActorObjectInfo::AddColorSwap(int modelpart, int oldcolor, int newcolor)
{
	switch(modelpart)
	{
		case 1:
		{
			LbaNet::Lba1ColorIndex idx;
			idx.ModelPart = LbaNet::PolygonColor;
			idx.Color = oldcolor;
			DisplayDesc.ColorSwaps[idx] = newcolor;
		}
		break;

		case 2:
		{
			LbaNet::Lba1ColorIndex idx;
			idx.ModelPart = LbaNet::SphereColor;
			idx.Color = oldcolor;
			DisplayDesc.ColorSwaps[idx] = newcolor;
		}
		break;

		case 3:
		{
			LbaNet::Lba1ColorIndex idx;
			idx.ModelPart = LbaNet::LineColor;
			idx.Color = oldcolor;
			DisplayDesc.ColorSwaps[idx] = newcolor;
		}
		break;
	}
}









/***********************************************************
constructor
***********************************************************/
ActorHandler::ActorHandler(const ActorObjectInfo & actorinfo)
: m_launchedscript(-1), m_paused(false), m_scripthandler(NULL)
{
	SetActorInfo(actorinfo);
}


/***********************************************************
destructor
***********************************************************/
ActorHandler::~ActorHandler(void)
{
	//destroy launched script
	if(m_launchedscript > 0 && m_scripthandler)
		m_scripthandler->StropThread(m_launchedscript);
}


/***********************************************************
set script handler
***********************************************************/
void ActorHandler::SetScriptHandler(ScriptEnvironmentBase* scripthandler)
{
	m_scripthandler = scripthandler;
}


/***********************************************************
set actor info
***********************************************************/
void ActorHandler::SetActorInfo(const ActorObjectInfo & ainfo)
{
	m_actorinfo = ainfo;

	//TODO - maybe not always the case
	m_actorinfo.LifeInfo.Display = false;
	m_actorinfo.ExtraInfo.Display = false;

	CreateActor();
}




/***********************************************************
save actor to lua file
***********************************************************/
void ActorHandler::SaveToLuaFile(std::ofstream & file)
{
	file<<"\tActor_"<<m_actorinfo.ObjectId<<" = ActorObjectInfo("<<m_actorinfo.ObjectId<<")"<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<":SetRenderType("<<m_actorinfo.GetRenderType()<<")"<<std::endl;

	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.ModelId = "<<m_actorinfo.DisplayDesc.ModelId<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.ModelName = \""<<m_actorinfo.DisplayDesc.ModelName<<"\""<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.Outfit = \""<<m_actorinfo.DisplayDesc.Outfit<<"\""<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.Weapon = \""<<m_actorinfo.DisplayDesc.Weapon<<"\""<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.Mode = \""<<m_actorinfo.DisplayDesc.Mode<<"\""<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.UseLight = "<<(m_actorinfo.DisplayDesc.UseLight?"true":"false")<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.CastShadow = "<<(m_actorinfo.DisplayDesc.CastShadow?"true":"false")<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.ColorR = "<<m_actorinfo.DisplayDesc.ColorR<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.ColorG = "<<m_actorinfo.DisplayDesc.ColorG<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.ColorB = "<<m_actorinfo.DisplayDesc.ColorB<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.ColorA = "<<m_actorinfo.DisplayDesc.ColorA<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.TransX = "<<m_actorinfo.DisplayDesc.TransX<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.TransY = "<<m_actorinfo.DisplayDesc.TransY<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.TransZ = "<<m_actorinfo.DisplayDesc.TransZ<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.ScaleX = "<<m_actorinfo.DisplayDesc.ScaleX<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.ScaleY = "<<m_actorinfo.DisplayDesc.ScaleY<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.ScaleZ = "<<m_actorinfo.DisplayDesc.ScaleZ<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.RotX = "<<m_actorinfo.DisplayDesc.RotX<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.RotY = "<<m_actorinfo.DisplayDesc.RotY<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".DisplayDesc.RotZ = "<<m_actorinfo.DisplayDesc.RotZ<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<":SetModelState("<<m_actorinfo.GetModelState()<<")"<<std::endl;

	// add color swaps
	{
		LbaNet::Lba1ColorChangeSeq::iterator itsw = m_actorinfo.DisplayDesc.ColorSwaps.begin();
		LbaNet::Lba1ColorChangeSeq::iterator endsw = m_actorinfo.DisplayDesc.ColorSwaps.end();
		for(;itsw != endsw; ++itsw)
		{
			int swaptype;
			switch(itsw->first.ModelPart)
			{
				case LbaNet::PolygonColor:
					swaptype = 1;
				break;

				case LbaNet::SphereColor:
					swaptype = 2;
				break;

				case LbaNet::LineColor:
					swaptype = 3;
				break;
			}

			file<<"\tActor_"<<m_actorinfo.ObjectId<<":AddColorSwap("<<swaptype<<","<<itsw->first.Color<<","<<itsw->second<<")"<<std::endl;
		}
	}



	file<<"\tActor_"<<m_actorinfo.ObjectId<<".PhysicDesc.Pos.X = "<<m_actorinfo.PhysicDesc.Pos.X<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".PhysicDesc.Pos.Y = "<<m_actorinfo.PhysicDesc.Pos.Y<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".PhysicDesc.Pos.Z = "<<m_actorinfo.PhysicDesc.Pos.Z<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".PhysicDesc.Pos.Rotation = "<<m_actorinfo.PhysicDesc.Pos.Rotation<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".PhysicDesc.Density = "<<m_actorinfo.PhysicDesc.Density<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".PhysicDesc.Collidable = "<<(m_actorinfo.PhysicDesc.Collidable?"true":"false")<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".PhysicDesc.SizeX = "<<m_actorinfo.PhysicDesc.SizeX<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".PhysicDesc.SizeY = "<<m_actorinfo.PhysicDesc.SizeY<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".PhysicDesc.SizeZ = "<<m_actorinfo.PhysicDesc.SizeZ<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".PhysicDesc.Filename = \""<<m_actorinfo.PhysicDesc.Filename<<"\""<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<":SetPhysicalActorType("<<m_actorinfo.GetPhysicalActorType()<<")"<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<":SetPhysicalShape("<<m_actorinfo.GetPhysicalShape()<<")"<<std::endl;

	file<<"\tActor_"<<m_actorinfo.ObjectId<<".ExtraInfo.Name = \""<<m_actorinfo.ExtraInfo.Name<<"\""<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".ExtraInfo.NameColorR = "<<m_actorinfo.ExtraInfo.NameColorR<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".ExtraInfo.NameColorG = "<<m_actorinfo.ExtraInfo.NameColorG<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".ExtraInfo.NameColorB = "<<m_actorinfo.ExtraInfo.NameColorB<<std::endl;
	file<<"\tActor_"<<m_actorinfo.ObjectId<<".ExtraInfo.Display = "<<m_actorinfo.ExtraInfo.Display<<std::endl;

	file<<"\tActor_"<<m_actorinfo.ObjectId<<".LifeInfo.Display = "<<m_actorinfo.LifeInfo.Display<<std::endl;

	if(m_actorinfo.Condition)
	{
		std::stringstream condname;
		condname<<"Actor_"<<m_actorinfo.ObjectId<<"_cond";
		m_actorinfo.Condition->SaveToLuaFile(file, condname.str());

		file<<"\tActor_"<<m_actorinfo.ObjectId<<".Condition = "<<condname.str()<<std::endl;
	}


	file<<"\tActor_"<<m_actorinfo.ObjectId<<"H = ActorHandler(Actor_"<<m_actorinfo.ObjectId<<")"<<std::endl;
	file<<"\tenvironment:AddActorObject(Actor_"<<m_actorinfo.ObjectId<<"H)"<<std::endl<<std::endl;
}



/***********************************************************
clear color swap info
***********************************************************/
void ActorHandler::ClearColorSwap()
{
	m_actorinfo.DisplayDesc.ColorSwaps.clear();
}



/***********************************************************
used by lua to get an actor Position
***********************************************************/
LbaVec3 ActorHandler::GetActorPosition()
{
	if(m_paused)
		return LbaVec3(m_saved_X, m_saved_Y, m_saved_Z);

	if(_character)
	{
		boost::shared_ptr<PhysicalObjectHandlerBase> physO = _character->GetPhysicalObject();
		if(physO)
		{
			float X, Y, Z;
			physO->GetPosition(X, Y, Z);
			return LbaVec3(X, Y, Z);
		}
	}

	return LbaVec3();
}

/***********************************************************
used by lua to get an actor Rotation
***********************************************************/
float ActorHandler::GetActorRotation()
{
	if(m_paused)
		return m_saved_rot;

	if(_character)
	{
		boost::shared_ptr<PhysicalObjectHandlerBase> physO = _character->GetPhysicalObject();
		if(physO)
			return physO->GetRotationYAxis();
	}

	return 0;
}

/***********************************************************
used by lua to get an actor Rotation
***********************************************************/
LbaQuaternion ActorHandler::GetActorRotationQuat()
{
	if(m_paused)
		return m_saved_Q;

	if(_character)
	{
		boost::shared_ptr<PhysicalObjectHandlerBase> physO = _character->GetPhysicalObject();
		if(physO)
		{
			LbaQuaternion Q;
			physO->GetRotation(Q);
			return Q;
		}
	}

	return LbaQuaternion();
}

/***********************************************************
used by lua to update an actor animation
***********************************************************/
void ActorHandler::UpdateActorAnimation(const std::string & AnimationString)
{
	if(_character)
	{
		boost::shared_ptr<DisplayObjectHandlerBase> disO = _character->GetDisplayObject();
		if(disO)
			disO->Update(new LbaNet::AnimationStringUpdate(AnimationString), m_paused);
	}
}

/***********************************************************
used by lua to update an actor mode
***********************************************************/
void ActorHandler::UpdateActorMode(const std::string & Mode)
{
	if(_character)
	{
		boost::shared_ptr<DisplayObjectHandlerBase> disO = _character->GetDisplayObject();
		if(disO)
		{
			LbaNet::ModelInfo model = disO->GetCurrentModel(m_paused);
			model.Mode = Mode;
			disO->Update(new LbaNet::ModelUpdate(model, false), m_paused);
		}
	}
}



/***********************************************************
called when a script has finished
***********************************************************/
void ActorHandler::ScriptFinished(int scriptid, const std::string & functioname)
{
	if(m_launchedscript == scriptid)
		m_launchedscript = -1;
}



/***********************************************************
process actor
***********************************************************/
void ActorHandler::Process(double tnow, float tdiff)
{

	//TODO - NPC - monster -> target player


	if(!m_scripthandler)
		return;

	// process script in normal case
	if(m_launchedscript > 0 && !m_paused)
		ProcessScript(tnow, tdiff, m_scripthandler);

}


/***********************************************************
create actor
***********************************************************/
void ActorHandler::CreateActor()
{
	boost::shared_ptr<DisplayInfo> DInfo;

	// create display object
	switch(m_actorinfo.DisplayDesc.TypeRenderer)
	{
		//2 -> LBA1 model 
		case LbaNet::RenderLba1M:
		{
			//TODO animation speed
			boost::shared_ptr<DisplayObjectDescriptionBase> dispobdesc
				(new Lba1ModelObjectDescription(m_actorinfo.DisplayDesc, _LBA1_MODEL_ANIMATION_SPEED_,
												m_actorinfo.DisplayDesc.UseLight, 
												m_actorinfo.DisplayDesc.CastShadow, 
												m_actorinfo.ExtraInfo,
												m_actorinfo.LifeInfo));

			DInfo = boost::shared_ptr<DisplayInfo>(new DisplayInfo(
								boost::shared_ptr<DisplayTransformation>(), dispobdesc));
		}
		break;

		//3-> LBA2 model
		case LbaNet::RenderLba2M:
		{
			//TODO
		}
		break;
	}

	// create physic object
	boost::shared_ptr<PhysicalDescriptionBase> PInfo(new 
					PhysicalDescriptionNoShape(m_actorinfo.PhysicDesc.Pos.X, m_actorinfo.PhysicDesc.Pos.Y, 
													m_actorinfo.PhysicDesc.Pos.Z, 
										LbaQuaternion(m_actorinfo.PhysicDesc.Pos.Rotation, LbaVec3(0, 1, 0))));


	ObjectInfo obj((long)m_actorinfo.ObjectId, DInfo, PInfo, 
			(m_actorinfo.PhysicDesc.TypePhysO == LbaNet::StaticAType));

	_character = obj.BuildServer();
}




/***********************************************************
pause the playing script
***********************************************************/
void ActorHandler::Pause()
{
	if(!m_paused)
	{
		m_paused = true;
		if(_character)
		{
			boost::shared_ptr<DisplayObjectHandlerBase> disO = _character->GetDisplayObject();
			if(disO)
				disO->SaveState();

			// store physical info
			boost::shared_ptr<PhysicalObjectHandlerBase> physO = _character->GetPhysicalObject();
			if(physO)
			{
				physO->GetPosition(m_saved_X, m_saved_Y, m_saved_Z);
				m_saved_rot = physO->GetRotationYAxis();
				physO->GetRotation(m_saved_Q);
			}
		}
	}
}


/***********************************************************
resume the playing script
***********************************************************/
void ActorHandler::Resume()
{
	if(m_paused)
	{
		m_paused = false;
		if(_character)
		{
			boost::shared_ptr<DisplayObjectHandlerBase> disO = _character->GetDisplayObject();
			if(disO)
				disO->RestoreState();

			// restore physical info
			boost::shared_ptr<PhysicalObjectHandlerBase> physO = _character->GetPhysicalObject();
			if(physO)
			{
				physO->SetPosition(m_saved_X, m_saved_Y, m_saved_Z);
				physO->SetRotation(m_saved_Q);	
			}
		}
	}
}




//TODO - send position to all clients