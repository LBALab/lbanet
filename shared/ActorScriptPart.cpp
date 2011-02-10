#include "ActorScriptPart.h"
#include <fstream>




ActorScriptPartBasePtr ActorScriptPartBase::BuildScriptPart(const std::string & type, 
															float sPosX, float sPosY, float sPosZ)
{
	if(type == "ASPWalkGoTo")
		return ActorScriptPartBasePtr(new ActorScriptPart_GoTo(sPosX, sPosY, sPosZ, 0.1));
	if(type == "ASPWalkStraightTo")
		return ActorScriptPartBasePtr(new ActorScriptPart_WalkStraightTo(sPosX, sPosY, sPosZ));
	if(type == "ASPPlayAnimation")
		return ActorScriptPartBasePtr(new ActorScriptPart_PlayAnimation(true));
	if(type == "ASPRotate")
		return ActorScriptPartBasePtr(new ActorScriptPart_Rotate(90, 0.1, true));
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
void ActorScriptPart_WalkStraightTo::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPWalkStraightTo("<<_PosX<<","<<_PosY<<","<<_PosZ<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_WalkStraightTo::WriteExecutionScript(std::ostream & file, long actid)
{	
	file<<"Environment:ActorStraightWalkTo(ScriptId, "<<actid<<","<<_PosX<<","<<_PosY<<","<<_PosZ<<")"<<std::endl;
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
void ActorScriptPart_GoTo::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPWalkGoTo("<<_PosX<<","<<_PosY<<","<<_PosZ<<","<<_Speed<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_GoTo::WriteExecutionScript(std::ostream & file, long actid)
{	
	file<<"Environment:ActorGoTo(ScriptId, "<<actid<<","<<_PosX<<","<<_PosY<<","<<_PosZ<<","<<_Speed<<")"<<std::endl;
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
void ActorScriptPart_PlayAnimation::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPPlayAnimation("<<(_AnimationMove?"true":"false")<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_PlayAnimation::WriteExecutionScript(std::ostream & file, long actid)
{	
	file<<"Environment:ActorAnimate(ScriptId, "<<actid<<","<<(_AnimationMove?"true":"false")<<")"<<std::endl;
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
void ActorScriptPart_Rotate::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPRotate("<<_Angle<<","<<_RotationSpeedPerSec
					<<","<<(_ManageAnimation?"true":"false")<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_Rotate::WriteExecutionScript(std::ostream & file, long actid)
{	
	file<<"Environment:ActorRotate(ScriptId, "<<actid<<","<<_Angle<<","<<_RotationSpeedPerSec
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
void ActorScriptPart_ChangeAnimation::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPChangeAnimation(\""<<_Animationstring<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeAnimation::WriteExecutionScript(std::ostream & file, long actid)
{	
	file<<"Environment:UpdateActorAnimation(\""<<_Animationstring<<"\")"<<std::endl;
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
void ActorScriptPart_ChangeModel::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPChangeModel(\""<<_Name<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeModel::WriteExecutionScript(std::ostream & file, long actid)
{	
	file<<"Environment:UpdateActorModel(\""<<_Name<<"\")"<<std::endl;
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
void ActorScriptPart_ChangeOutfit::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPChangeOutfit(\""<<_Name<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeOutfit::WriteExecutionScript(std::ostream & file, long actid)
{	
	file<<"Environment:UpdateActorOutfit(\""<<_Name<<"\")"<<std::endl;
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
void ActorScriptPart_ChangeWeapon::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPChangeWeapon(\""<<_Name<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeWeapon::WriteExecutionScript(std::ostream & file, long actid)
{	
	file<<"Environment:UpdateActorWeapon(\""<<_Name<<"\")"<<std::endl;
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
void ActorScriptPart_ChangeMode::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPChangeMode(\""<<_Name<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_ChangeMode::WriteExecutionScript(std::ostream & file, long actid)
{	
	file<<"Environment:UpdateActorMode(\""<<_Name<<"\")"<<std::endl;
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
void ActorScriptPart_WaitForSignal::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPWaitForSignal("<<_Signalnumber<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_WaitForSignal::WriteExecutionScript(std::ostream & file, long actid)
{	
	file<<"Environment:ActorWaitForSignal(ScriptId, "<<actid<<","<<_Signalnumber<<")"<<std::endl;
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
void ActorScriptPart_SendSignal::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPSendSignal("<<_Signalnumber<<","<<_ActorId<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_SendSignal::WriteExecutionScript(std::ostream & file, long actid)
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
void ActorScriptPart_Custom::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPCustom(\""<<_fctName<<"\")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_Custom::WriteExecutionScript(std::ostream & file, long actid)
{	
	if(_fctName != "")
		file<<_fctName<<"(ScriptId, Environment)"<<std::endl;
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
void ActorScriptPart_TeleportTo::SaveToLuaFile(std::ofstream & file, const std::string & name)
{	
	file<<"\t"<<name<<" = ASPTeleportTo("<<_PosX<<","<<_PosY<<","<<_PosZ<<")"<<std::endl;
}

/***********************************************************
save action to lua file
***********************************************************/	
void ActorScriptPart_TeleportTo::WriteExecutionScript(std::ostream & file, long actid)
{	
	file<<"Environment:TeleportActorTo(ScriptId, "<<actid<<","<<_PosX<<","<<_PosY<<","<<_PosZ<<")"<<std::endl;
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

#endif