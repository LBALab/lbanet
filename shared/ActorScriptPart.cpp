#include "ActorScriptPart.h"
#include <fstream>


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
