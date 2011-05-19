#include "ActorScriptPart.h"
#include <fstream>
#include "ActorHandler.h"



ActorScriptPartBasePtr ActorScriptPartBase::BuildScriptPart(const std::string & type, 
															float sPosX, float sPosY, float sPosZ)
{
	if(type == "ASPGoTo")
		return ActorScriptPartBasePtr(new ActorScriptPart_GoTo(sPosX, sPosY, sPosZ, 0.005f));
	if(type == "ASPWalkStraightTo")
		return ActorScriptPartBasePtr(new ActorScriptPart_WalkStraightTo(sPosX, sPosY, sPosZ));
	if(type == "ASPPlayAnimation")
		return ActorScriptPartBasePtr(new ActorScriptPart_PlayAnimation(true));
	if(type == "ASPRotate")
		return ActorScriptPartBasePtr(new ActorScriptPart_Rotate(90, 0.1f, true));
	if(type == "ASPSetRotation")
		return ActorScriptPartBasePtr(new ActorScriptPart_SetRotation(90));
	if(type == "ASPChangeAnimation")
		return ActorScriptPartBasePtr(new ActorScriptPart_ChangeAnimation("Stand"));
	if(type == "ASPChangeModel")
		return ActorScriptPartBasePtr(new ActorScriptPart_ChangeModel(""));
	if(type == "ASPChangeOutfit")
		return ActorScriptPartBasePtr(new ActorScriptPart_ChangeOutfit(""));
	if(type == "ASPChangeWeapon")
		return ActorScriptPartBasePtr(new ActorScriptPart_ChangeWeapon(""));
	if(type == "ASPChangeMode")
		return ActorScriptPartBasePtr(new ActorScriptPart_ChangeMode(""));
	if(type == "ASPWaitForSignal")
		return ActorScriptPartBasePtr(new ActorScriptPart_WaitForSignal(1));
	if(type == "ASPSendSignal")
		return ActorScriptPartBasePtr(new ActorScriptPart_SendSignal(1, -1));
	if(type == "ASPTeleportTo")
		return ActorScriptPartBasePtr(new ActorScriptPart_TeleportTo(sPosX, sPosY, sPosZ));
	if(type == "ASPCustom")
		return ActorScriptPartBasePtr(new ActorScriptPart_Custom(""));
	if(type == "ASPRotateFromPoint")
		return ActorScriptPartBasePtr(new ActorScriptPart_RotateFromPoint(90, sPosX, sPosY, sPosZ, 0.1f));
	if(type == "ASPFollowWaypoint")
		return ActorScriptPartBasePtr(new ActorScriptPart_FollowWaypoint(sPosX, sPosY, sPosZ));
	if(type == "ASPStartWaypoint")
		return ActorScriptPartBasePtr(new ActorScriptPart_StartWaypoint(sPosX, sPosY, sPosZ, true));
	if(type == "ASPShowHide")
		return ActorScriptPartBasePtr(new ActorScriptPart_ShowHide(true));
	if(type == "ASPAttachToActor")
		return ActorScriptPartBasePtr(new ActorScriptPart_AttachToActor(1, -1));
	if(type == "ASPDetachFromActor")
		return ActorScriptPartBasePtr(new ActorScriptPart_DetachFromActor(-1));

	return ActorScriptPartBasePtr();
}




/***********************************************************
constructor
***********************************************************/
ActorScriptPart_WalkStraightTo::ActorScriptPart_WalkStraightTo(float PosX, float PosY, float PosZ)
: _PosX(PosX), _PosY(PosY), _PosZ(PosZ)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_WalkStraightTo::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPWalkStraightTo("<<_PosX<<","<<_PosY<<","<<_PosZ<<")"<<std::endl;
}

/***********************************************************z
save action to lua file
***********************************************************/	
void ActorScriptPart_WalkStraightTo::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	file << "Position = LbaVec3("<<_PosX<<","<<_PosY<<","<<_PosZ<<")"<<std::endl;
	file<<"Environment:ActorStraightWalkTo(ScriptId,"<<actid<<",Position)"<<std::endl;
}



/***********************************************************
constructor
***********************************************************/
ActorScriptPart_GoTo::ActorScriptPart_GoTo(float PosX, float PosY, float PosZ, float speed)
: _PosX(PosX), _PosY(PosY), _PosZ(PosZ), _Speed(speed)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_GoTo::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPGoTo("<<_PosX<<","<<_PosY<<","<<_PosZ<<","<<_Speed<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_GoTo::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	file << "Position = LbaVec3("<<_PosX<<","<<_PosY<<","<<_PosZ<<")"<<std::endl;
	file<<"Environment:ActorGoTo(ScriptId,"<<actid<<",Position,"<<_Speed<<")"<<std::endl;
}


/***********************************************************
constructor
***********************************************************/
ActorScriptPart_PlayAnimation::ActorScriptPart_PlayAnimation(bool AnimationMove)
: _AnimationMove(AnimationMove)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_PlayAnimation::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPPlayAnimation("<<(_AnimationMove?"true":"false")<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_PlayAnimation::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	file<<"Environment:ActorAnimate(ScriptId,"<<actid<<","<<(_AnimationMove?"true":"false")<<")"<<std::endl;
}


/***********************************************************
constructor
***********************************************************/
ActorScriptPart_Rotate::ActorScriptPart_Rotate(float Angle, 
						float RotationSpeedPerSec, bool ManageAnimation)
: _Angle(Angle), _RotationSpeedPerSec(RotationSpeedPerSec), _ManageAnimation(ManageAnimation)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_Rotate::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPRotate("<<_Angle<<","<<_RotationSpeedPerSec
					<<","<<(_ManageAnimation?"true":"false")<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_Rotate::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	file<<"Environment:ActorRotate(ScriptId,"<<actid<<","<<_Angle<<","<<_RotationSpeedPerSec
					<<","<<(_ManageAnimation?"true":"false")<<")"<<std::endl;
}


/***********************************************************
constructor
***********************************************************/
ActorScriptPart_ChangeAnimation::ActorScriptPart_ChangeAnimation(const std::string & Animationstring)
: _Animationstring(Animationstring)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeAnimation::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPChangeAnimation(\""<<_Animationstring<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeAnimation::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	if(_Animationstring != "")
		file<<"Environment:UpdateActorAnimation("<<actid<<",\""<<_Animationstring<<"\")"<<std::endl;
}


/***********************************************************
constructor
***********************************************************/
ActorScriptPart_ChangeModel::ActorScriptPart_ChangeModel(const std::string & Name)
: _Name(Name)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeModel::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPChangeModel(\""<<_Name<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeModel::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	if(_Name != "")
		file<<"Environment:UpdateActorModel("<<actid<<",\""<<_Name<<"\")"<<std::endl;
}


/***********************************************************
constructor
***********************************************************/
ActorScriptPart_ChangeOutfit::ActorScriptPart_ChangeOutfit(const std::string & Name)
: _Name(Name)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeOutfit::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPChangeOutfit(\""<<_Name<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeOutfit::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	if(_Name != "")
		file<<"Environment:UpdateActorOutfit("<<actid<<",\""<<_Name<<"\")"<<std::endl;
}


/***********************************************************
constructor
***********************************************************/
ActorScriptPart_ChangeWeapon::ActorScriptPart_ChangeWeapon(const std::string & Name)
: _Name(Name)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeWeapon::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPChangeWeapon(\""<<_Name<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeWeapon::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	if(_Name != "")
		file<<"Environment:UpdateActorWeapon("<<actid<<",\""<<_Name<<"\")"<<std::endl;
}


/***********************************************************
constructor
***********************************************************/
ActorScriptPart_ChangeMode::ActorScriptPart_ChangeMode(const std::string & Name)
: _Name(Name)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeMode::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPChangeMode(\""<<_Name<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeMode::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	if(_Name != "")
		file<<"Environment:UpdateActorMode("<<actid<<",\""<<_Name<<"\")"<<std::endl;
}


/***********************************************************
constructor
***********************************************************/
ActorScriptPart_WaitForSignal::ActorScriptPart_WaitForSignal(int Signalnumber)
: _Signalnumber(Signalnumber)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_WaitForSignal::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPWaitForSignal("<<_Signalnumber<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_WaitForSignal::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	file<<"Environment:ActorWaitForSignal(ScriptId,"<<actid<<","<<_Signalnumber<<")"<<std::endl;
}


/***********************************************************
constructor
***********************************************************/
ActorScriptPart_SendSignal::ActorScriptPart_SendSignal(int Signalnumber, long ActorId)
: _Signalnumber(Signalnumber), _ActorId(ActorId)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_SendSignal::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPSendSignal("<<_Signalnumber<<","<<_ActorId<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_SendSignal::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	file<<"Environment:SendSignalToActor("<<_ActorId<<","<<_Signalnumber<<")"<<std::endl;
}


/***********************************************************
constructor
***********************************************************/
ActorScriptPart_Custom::ActorScriptPart_Custom(const std::string & fctName)
: _fctName(fctName)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_Custom::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPCustom(\""<<_fctName<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_Custom::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	if(_fctName != "")
		file<<_fctName<<"(ScriptId, Environment,"<<actid<<")"<<std::endl;
}


/***********************************************************
constructor
***********************************************************/
ActorScriptPart_TeleportTo::ActorScriptPart_TeleportTo(float PosX, float PosY, float PosZ)
: _PosX(PosX), _PosY(PosY), _PosZ(PosZ)
{

}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_TeleportTo::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPTeleportTo("<<_PosX<<","<<_PosY<<","<<_PosZ<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_TeleportTo::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	file << "Position = LbaVec3("<<_PosX<<","<<_PosY<<","<<_PosZ<<")"<<std::endl;
	file<<"Environment:TeleportActorTo(ScriptId,"<<actid<<",Position)"<<std::endl;
}



/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_SetRotation::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPSetRotation("<<_Angle<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_SetRotation::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	file<<"Environment:SetActorRotation("<<actid<<","<<_Angle<<")"<<std::endl;
}





/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_RotateFromPoint::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPRotateFromPoint("<<_Angle<<","<<_PosX<<","<<_PosY<<","
													<<_PosZ<<","<<_Speed<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_RotateFromPoint::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	file << "Position = LbaVec3("<<_PosX<<","<<_PosY<<","<<_PosZ<<")"<<std::endl;
	file<<"Environment:ActorRotateFromPoint(ScriptId,"<<actid<<","<<_Angle<<",Position,"<<_Speed<<")"<<std::endl;
}



/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_FollowWaypoint::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPFollowWaypoint("<<_PosX<<","<<_PosY<<","<<_PosZ<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_FollowWaypoint::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	std::pair<int, int> indexes = AH->AddWaypoint(LbaVec3(_PosX, _PosY, _PosZ));

	if(indexes.first >= 0)
	{
		file<<"Environment:ActorFollowWaypoint(ScriptId,"<<actid<<","<<indexes.first<<","<<indexes.second<<")"<<std::endl;
	}
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_StartWaypoint::SaveToLuaFile(std::ostream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPStartWaypoint("<<_PosX<<","<<_PosY<<","<<_PosZ
										<<","<<(_Forward?"true":"false")<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_StartWaypoint::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{	
	std::pair<int, int> indexes = AH->StartWaypoint(LbaVec3(_PosX, _PosY, _PosZ));

	if(indexes.first >= 0)
	{
		file<<"Environment:UpdateActorAnimation("<<actid<<",\""<<(_Forward?"MoveForward":"MoveBackward")<<"\")"<<std::endl;
		file<<"Environment:ActorFollowWaypoint(ScriptId,"<<actid<<","<<indexes.first<<","<<indexes.second<<")"<<std::endl;
	}
}




/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ShowHide::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = ASPShowHide("<<(_Show?"true":"false")<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ShowHide::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{
	file<<"Environment:ActorShowHide("<<actid<<","<<(_Show?"true":"false")<<")"<<std::endl;
}




/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_AttachToActor::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = ASPAttachToActor("<<_actortype<<","<<_actorid<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_AttachToActor::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{
	file<<"Environment:AttachActor("<<actid<<","<<_actortype<<","<<_actorid<<")"<<std::endl;
}



/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_DetachFromActor::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = ASPDetachFromActor("<<_actorid<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_DetachFromActor::WriteExecutionScript(std::ostream & file, long actid, ActorHandler * AH)
{
	file<<"Environment:DettachActor("<<actid<<","<<_actorid<<")"<<std::endl;
}



#ifdef _USE_QT_EDITOR_


/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_GoTo::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "PosX" << (double)_PosX;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "PosY" << (double)_PosY;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "PosZ" << (double)_PosZ;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "Moving Speed" << (double)_Speed;
	model->AppendRow(datachild, parentIdx);	
	}
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_WalkStraightTo::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "PosX" << (double)_PosX;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "PosY" << (double)_PosY;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "PosZ" << (double)_PosZ;
	model->AppendRow(datachild, parentIdx);	
	}
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_PlayAnimation::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "Animation Move Actor" << _AnimationMove;
	model->AppendRow(datachild, parentIdx);	
	}
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_Rotate::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "Angle" << (double)_Angle;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "Speed" << (double)_RotationSpeedPerSec;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "Update Animation" << _ManageAnimation;
	model->AppendRow(datachild, parentIdx);	
	}
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_ChangeAnimation::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	QVector<QVariant> datachild;
	datachild << "NewAnimation" << _Animationstring.c_str();
	model->AppendRow(datachild, parentIdx);	
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_ChangeModel::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	QVector<QVariant> datachild;
	datachild << "NewModel" << _Name.c_str();
	model->AppendRow(datachild, parentIdx);	
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_ChangeOutfit::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	QVector<QVariant> datachild;
	datachild << "NewOutfit" << _Name.c_str();
	model->AppendRow(datachild, parentIdx);	
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_ChangeWeapon::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	QVector<QVariant> datachild;
	datachild << "NewWeapon" << _Name.c_str();
	model->AppendRow(datachild, parentIdx);	
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_ChangeMode::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	QVector<QVariant> datachild;
	datachild << "NewMode" << _Name.c_str();
	model->AppendRow(datachild, parentIdx);	
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_WaitForSignal::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "Signal number" << _Signalnumber;
	model->AppendRow(datachild, parentIdx);	
	}
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_SendSignal::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "Send to id" << (int)_ActorId;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "Signal number" << _Signalnumber;
	model->AppendRow(datachild, parentIdx);	
	}
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_TeleportTo::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "PosX" << (double)_PosX;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "PosY" << (double)_PosY;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "PosZ" << (double)_PosZ;
	model->AppendRow(datachild, parentIdx);	
	}
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_Custom::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "Function name" << _fctName.c_str();
	model->AppendRow(datachild, parentIdx);	
	}
}




/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_SetRotation::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "Angle" << (double)_Angle;
	model->AppendRow(datachild, parentIdx);	
	}
}




/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_RotateFromPoint::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "Angle" << (double)_Angle;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "RotationPosX" << (double)_PosX;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "RotationPosY" << (double)_PosY;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "RotationPosZ" << (double)_PosZ;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "Rotation Speed" << (double)_Speed;
	model->AppendRow(datachild, parentIdx);	
	}
}

/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_FollowWaypoint::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "PosX" << (double)_PosX;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "PosY" << (double)_PosY;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "PosZ" << (double)_PosZ;
	model->AppendRow(datachild, parentIdx);	
	}
}

/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_StartWaypoint::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "PosX" << (double)_PosX;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "PosY" << (double)_PosY;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "PosZ" << (double)_PosZ;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "Move Forward" << _Forward;
	model->AppendRow(datachild, parentIdx);	
	}
}

/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_ShowHide::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "Show" << _Show;
	model->AppendRow(datachild, parentIdx);	
	}
}


/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_AttachToActor::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "Attached Actor Type" << _actortype;
	model->AppendRow(datachild, parentIdx);	
	}
	{
	QVector<QVariant> datachild;
	datachild << "Attached Actor Id" << (int)_actorid;
	model->AppendRow(datachild, parentIdx);	
	}
}

/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_DetachFromActor::WriteToQt(TreeModel *	model, const QModelIndex &parentIdx)
{
	{
	QVector<QVariant> datachild;
	datachild << "Attached Actor Id" << (int)_actorid;
	model->AppendRow(datachild, parentIdx);	
	}
}





/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_GoTo::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_PosX = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosY = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosZ = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_Speed = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_WalkStraightTo::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_PosX = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosY = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosZ = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_PlayAnimation::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_AnimationMove = model->data(model->GetIndex(1, rowidx, parentIdx)).toBool();
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_Rotate::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_Angle = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_RotationSpeedPerSec = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_ManageAnimation = model->data(model->GetIndex(1, rowidx, parentIdx)).toBool();
}



/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_SetRotation::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_Angle = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
}



/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_ChangeAnimation::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_Animationstring = model->data(model->GetIndex(1, rowidx, parentIdx)).toString().toAscii().data();
}


/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_ChangeModel::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_Name = model->data(model->GetIndex(1, rowidx, parentIdx)).toString().toAscii().data();
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_ChangeOutfit::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_Name = model->data(model->GetIndex(1, rowidx, parentIdx)).toString().toAscii().data();
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_ChangeWeapon::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_Name = model->data(model->GetIndex(1, rowidx, parentIdx)).toString().toAscii().data();
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_ChangeMode::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_Name = model->data(model->GetIndex(1, rowidx, parentIdx)).toString().toAscii().data();
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_WaitForSignal::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_Signalnumber = model->data(model->GetIndex(1, rowidx, parentIdx)).toInt();
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_SendSignal::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_ActorId = model->data(model->GetIndex(1, rowidx, parentIdx)).toInt();
	++rowidx;
	_Signalnumber = model->data(model->GetIndex(1, rowidx, parentIdx)).toInt();
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_TeleportTo::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_PosX = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosY = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosZ = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
}

/***********************************************************
// use by the editor
***********************************************************/
void ActorScriptPart_Custom::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_fctName = model->data(model->GetIndex(1, rowidx, parentIdx)).toString().toAscii().data();
}



/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_RotateFromPoint::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_Angle = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosX = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosY = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosZ = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_Speed = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
}


/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_FollowWaypoint::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_PosX = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosY = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosZ = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
}


/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_StartWaypoint::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_PosX = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosY = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_PosZ = model->data(model->GetIndex(1, rowidx, parentIdx)).toFloat();
	++rowidx;
	_Forward = model->data(model->GetIndex(1, rowidx, parentIdx)).toBool();
	++rowidx;
}



/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_ShowHide::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_Show = model->data(model->GetIndex(1, rowidx, parentIdx)).toBool();
}


/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_AttachToActor::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_actortype = model->data(model->GetIndex(1, rowidx, parentIdx)).toInt();
	++rowidx;
	_actorid = model->data(model->GetIndex(1, rowidx, parentIdx)).toInt();
}

/***********************************************************
// use by the editor
***********************************************************/	
void ActorScriptPart_DetachFromActor::UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx)
{
	_actorid = model->data(model->GetIndex(1, rowidx, parentIdx)).toInt();
}











/***********************************************************
// use by the editor
***********************************************************/	
ActorObjectInfo ActorScriptPartBase::GetEditorObject(long Actorid, int scriptnumber)
{
	return ActorObjectInfo();
}


/***********************************************************
// use by the editor
***********************************************************/	
ActorObjectInfo ActorScriptPart_GoTo::GetEditorObject(long Actorid, int scriptnumber)
{
	ActorObjectInfo ainfo(Actorid*1000 + scriptnumber + 5000000);
	ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
	ainfo.DisplayDesc.ModelName = "Object";
	ainfo.DisplayDesc.Outfit = "Flag";
	ainfo.DisplayDesc.Weapon = "No";
	ainfo.DisplayDesc.Mode = "Normal";
	ainfo.DisplayDesc.State = LbaNet::StNormal;
    ainfo.DisplayDesc.UseLight = true;
    ainfo.DisplayDesc.CastShadow = true;
    ainfo.DisplayDesc.TransX = 0;
    ainfo.DisplayDesc.TransY = 0;
    ainfo.DisplayDesc.TransZ = 0;
    ainfo.DisplayDesc.ScaleX = 1;
    ainfo.DisplayDesc.ScaleY = 1;
    ainfo.DisplayDesc.ScaleZ = 1;
    ainfo.DisplayDesc.RotX = 0;
    ainfo.DisplayDesc.RotY = 0;
    ainfo.DisplayDesc.RotZ = 0;

	LbaNet::Lba1ColorIndex cidx;
	cidx.Color = 80;
	cidx.ModelPart = LbaNet::PolygonColor;
	ainfo.DisplayDesc.ColorSwaps[cidx] = 91;


	ainfo.PhysicDesc.TypeShape = LbaNet::NoShape;
	ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
	ainfo.PhysicDesc.Pos.X = _PosX;
	ainfo.PhysicDesc.Pos.Y = _PosY;
	ainfo.PhysicDesc.Pos.Z = _PosZ;
	ainfo.PhysicDesc.Pos.Rotation = 0;

	std::stringstream strs;
	strs << "SP" <<scriptnumber;
	ainfo.ExtraInfo.Name = strs.str();
	ainfo.ExtraInfo.NameColorR = 0.5f;
	ainfo.ExtraInfo.NameColorG = 0.5f;
	ainfo.ExtraInfo.NameColorB = 1.0f;
	ainfo.LifeInfo.Display = true;
	ainfo.LifeInfo.Display = false;
	return ainfo;
}

/***********************************************************
// use by the editor
***********************************************************/
ActorObjectInfo ActorScriptPart_WalkStraightTo::GetEditorObject(long Actorid, int scriptnumber)
{
	ActorObjectInfo ainfo(Actorid*1000 + scriptnumber + 5000000);
	ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
	ainfo.DisplayDesc.ModelName = "Object";
	ainfo.DisplayDesc.Outfit = "Flag";
	ainfo.DisplayDesc.Weapon = "No";
	ainfo.DisplayDesc.Mode = "Normal";
	ainfo.DisplayDesc.State = LbaNet::StNormal;
    ainfo.DisplayDesc.UseLight = true;
    ainfo.DisplayDesc.CastShadow = true;
    ainfo.DisplayDesc.TransX = 0;
    ainfo.DisplayDesc.TransY = 0;
    ainfo.DisplayDesc.TransZ = 0;
    ainfo.DisplayDesc.ScaleX = 1;
    ainfo.DisplayDesc.ScaleY = 1;
    ainfo.DisplayDesc.ScaleZ = 1;
    ainfo.DisplayDesc.RotX = 0;
    ainfo.DisplayDesc.RotY = 0;
    ainfo.DisplayDesc.RotZ = 0;


	LbaNet::Lba1ColorIndex cidx;
	cidx.Color = 80;
	cidx.ModelPart = LbaNet::PolygonColor;
	ainfo.DisplayDesc.ColorSwaps[cidx] = 125;



	ainfo.PhysicDesc.TypeShape = LbaNet::NoShape;
	ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
	ainfo.PhysicDesc.Pos.X = _PosX;
	ainfo.PhysicDesc.Pos.Y = _PosY;
	ainfo.PhysicDesc.Pos.Z = _PosZ;
	ainfo.PhysicDesc.Pos.Rotation = 0;

	std::stringstream strs;
	strs << "SP" <<scriptnumber;
	ainfo.ExtraInfo.Name = strs.str();
	ainfo.ExtraInfo.NameColorR = 0.5f;
	ainfo.ExtraInfo.NameColorG = 0.5f;
	ainfo.ExtraInfo.NameColorB = 1.0f;
	ainfo.LifeInfo.Display = true;
	ainfo.LifeInfo.Display = false;
	return ainfo;
}




/***********************************************************
// use by the editor
***********************************************************/
ActorObjectInfo ActorScriptPart_TeleportTo::GetEditorObject(long Actorid, int scriptnumber)
{
	ActorObjectInfo ainfo(Actorid*1000 + scriptnumber + 5000000);
	ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
	ainfo.DisplayDesc.ModelName = "Object";
	ainfo.DisplayDesc.Outfit = "Flag";
	ainfo.DisplayDesc.Weapon = "No";
	ainfo.DisplayDesc.Mode = "Normal";
	ainfo.DisplayDesc.State = LbaNet::StNormal;
    ainfo.DisplayDesc.UseLight = true;
    ainfo.DisplayDesc.CastShadow = true;
    ainfo.DisplayDesc.TransX = 0;
    ainfo.DisplayDesc.TransY = 0;
    ainfo.DisplayDesc.TransZ = 0;
    ainfo.DisplayDesc.ScaleX = 1;
    ainfo.DisplayDesc.ScaleY = 1;
    ainfo.DisplayDesc.ScaleZ = 1;
    ainfo.DisplayDesc.RotX = 0;
    ainfo.DisplayDesc.RotY = 0;
    ainfo.DisplayDesc.RotZ = 0;


	LbaNet::Lba1ColorIndex cidx;
	cidx.Color = 80;
	cidx.ModelPart = LbaNet::PolygonColor;
	ainfo.DisplayDesc.ColorSwaps[cidx] = 156;



	ainfo.PhysicDesc.TypeShape = LbaNet::NoShape;
	ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
	ainfo.PhysicDesc.Pos.X = _PosX;
	ainfo.PhysicDesc.Pos.Y = _PosY;
	ainfo.PhysicDesc.Pos.Z = _PosZ;
	ainfo.PhysicDesc.Pos.Rotation = 0;

	std::stringstream strs;
	strs << "SP" <<scriptnumber;
	ainfo.ExtraInfo.Name = strs.str();
	ainfo.ExtraInfo.NameColorR = 0.5f;
	ainfo.ExtraInfo.NameColorG = 0.5f;
	ainfo.ExtraInfo.NameColorB = 1.0f;
	ainfo.LifeInfo.Display = true;
	ainfo.LifeInfo.Display = false;
	return ainfo;
}



/***********************************************************
// use by the editor
***********************************************************/
ActorObjectInfo ActorScriptPart_FollowWaypoint::GetEditorObject(long Actorid, int scriptnumber)
{
	ActorObjectInfo ainfo(Actorid*1000 + scriptnumber + 5000000);
	ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
	ainfo.DisplayDesc.ModelName = "Object";
	ainfo.DisplayDesc.Outfit = "Flag";
	ainfo.DisplayDesc.Weapon = "No";
	ainfo.DisplayDesc.Mode = "Normal";
	ainfo.DisplayDesc.State = LbaNet::StNormal;
    ainfo.DisplayDesc.UseLight = true;
    ainfo.DisplayDesc.CastShadow = true;
    ainfo.DisplayDesc.TransX = 0;
    ainfo.DisplayDesc.TransY = 0;
    ainfo.DisplayDesc.TransZ = 0;
    ainfo.DisplayDesc.ScaleX = 1;
    ainfo.DisplayDesc.ScaleY = 1;
    ainfo.DisplayDesc.ScaleZ = 1;
    ainfo.DisplayDesc.RotX = 0;
    ainfo.DisplayDesc.RotY = 0;
    ainfo.DisplayDesc.RotZ = 0;


	LbaNet::Lba1ColorIndex cidx;
	cidx.Color = 80;
	cidx.ModelPart = LbaNet::PolygonColor;
	ainfo.DisplayDesc.ColorSwaps[cidx] = 172;



	ainfo.PhysicDesc.TypeShape = LbaNet::NoShape;
	ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
	ainfo.PhysicDesc.Pos.X = _PosX;
	ainfo.PhysicDesc.Pos.Y = _PosY;
	ainfo.PhysicDesc.Pos.Z = _PosZ;
	ainfo.PhysicDesc.Pos.Rotation = 0;

	std::stringstream strs;
	strs << "SP" <<scriptnumber;
	ainfo.ExtraInfo.Name = strs.str();
	ainfo.ExtraInfo.NameColorR = 0.5f;
	ainfo.ExtraInfo.NameColorG = 0.5f;
	ainfo.ExtraInfo.NameColorB = 1.0f;
	ainfo.LifeInfo.Display = true;
	ainfo.LifeInfo.Display = false;
	return ainfo;
}




/***********************************************************
// use by the editor
***********************************************************/
ActorObjectInfo ActorScriptPart_StartWaypoint::GetEditorObject(long Actorid, int scriptnumber)
{
	ActorObjectInfo ainfo(Actorid*1000 + scriptnumber + 5000000);
	ainfo.DisplayDesc.TypeRenderer = LbaNet::RenderLba1M;
	ainfo.DisplayDesc.ModelName = "Object";
	ainfo.DisplayDesc.Outfit = "Flag";
	ainfo.DisplayDesc.Weapon = "No";
	ainfo.DisplayDesc.Mode = "Normal";
	ainfo.DisplayDesc.State = LbaNet::StNormal;
    ainfo.DisplayDesc.UseLight = true;
    ainfo.DisplayDesc.CastShadow = true;
    ainfo.DisplayDesc.TransX = 0;
    ainfo.DisplayDesc.TransY = 0;
    ainfo.DisplayDesc.TransZ = 0;
    ainfo.DisplayDesc.ScaleX = 1;
    ainfo.DisplayDesc.ScaleY = 1;
    ainfo.DisplayDesc.ScaleZ = 1;
    ainfo.DisplayDesc.RotX = 0;
    ainfo.DisplayDesc.RotY = 0;
    ainfo.DisplayDesc.RotZ = 0;


	LbaNet::Lba1ColorIndex cidx;
	cidx.Color = 80;
	cidx.ModelPart = LbaNet::PolygonColor;
	ainfo.DisplayDesc.ColorSwaps[cidx] = 216;



	ainfo.PhysicDesc.TypeShape = LbaNet::NoShape;
	ainfo.PhysicDesc.TypePhysO = LbaNet::StaticAType;
	ainfo.PhysicDesc.Pos.X = _PosX;
	ainfo.PhysicDesc.Pos.Y = _PosY;
	ainfo.PhysicDesc.Pos.Z = _PosZ;
	ainfo.PhysicDesc.Pos.Rotation = 0;

	std::stringstream strs;
	strs << "SP" <<scriptnumber;
	ainfo.ExtraInfo.Name = strs.str();
	ainfo.ExtraInfo.NameColorR = 0.5f;
	ainfo.ExtraInfo.NameColorG = 0.5f;
	ainfo.ExtraInfo.NameColorB = 1.0f;
	ainfo.LifeInfo.Display = true;
	ainfo.LifeInfo.Display = false;
	return ainfo;
}



#endif
