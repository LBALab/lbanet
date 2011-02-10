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

#ifndef _LBANET_ACTOR_SCRIPT_PART_H__
#define _LBANET_ACTOR_SCRIPT_PART_H__

#include <boost/shared_ptr.hpp>
#include <LbaTypes.h>

class ActorScriptPartBase;
typedef boost::shared_ptr<ActorScriptPartBase> ActorScriptPartBasePtr;

#include <string>


#ifdef _USE_QT_EDITOR_
#include <QAbstractTableModel>
#include <QObject>
#include "treemodel.h"
#include <QtCore/QVariant>
#include <QModelIndex>
#include <QVector>
#endif



//! base class used as an actor script
class ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPartBase()
	{}
	
	//! destructor
	virtual ~ActorScriptPartBase(void){}

	//! get type of the script in string form
	virtual std::string GetTypeName(){ return "";}


	// save script to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name){}


	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid){}

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx){}

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx){}
#endif


	static ActorScriptPartBasePtr BuildScriptPart(const std::string & type, 
													float sPosX, float sPosY, float sPosZ);
};



//! use to start a script on client side
class ActorScriptPart_GoTo : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_GoTo(float PosX, float PosY, float PosZ, float speed);
	
	//! destructor
	virtual ~ActorScriptPart_GoTo(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPWalkGoTo"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif

private:
	float	_PosX;
	float	_PosY;
	float	_PosZ;
	float	_Speed;
};



//! use to start a script on client side
class ActorScriptPart_WalkStraightTo : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_WalkStraightTo(float PosX, float PosY, float PosZ);
	
	//! destructor
	virtual ~ActorScriptPart_WalkStraightTo(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPWalkStraightTo"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	float	_PosX;
	float	_PosY;
	float	_PosZ;
};



//! use to start a script on client side
class ActorScriptPart_PlayAnimation : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_PlayAnimation(bool AnimationMove);
	
	//! destructor
	virtual ~ActorScriptPart_PlayAnimation(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPPlayAnimation"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	bool	_AnimationMove;
};




//! use to start a script on client side
class ActorScriptPart_Rotate : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_Rotate(float Angle, 
						float RotationSpeedPerSec, bool ManageAnimation);
	
	//! destructor
	virtual ~ActorScriptPart_Rotate(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPRotate"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	float	_Angle; 
	float	_RotationSpeedPerSec;
	bool	_ManageAnimation;
};




//! use to start a script on client side
class ActorScriptPart_ChangeAnimation : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_ChangeAnimation(const std::string & Animationstring);
	
	//! destructor
	virtual ~ActorScriptPart_ChangeAnimation(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPChangeAnimation"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	std::string		_Animationstring;
};


//! use to start a script on client side
class ActorScriptPart_ChangeModel : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_ChangeModel(const std::string & Name);
	
	//! destructor
	virtual ~ActorScriptPart_ChangeModel(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPChangeModel"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	std::string		_Name;
};


//! use to start a script on client side
class ActorScriptPart_ChangeOutfit : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_ChangeOutfit(const std::string & Name);
	
	//! destructor
	virtual ~ActorScriptPart_ChangeOutfit(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPChangeOutfit"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	std::string		_Name;
};


//! use to start a script on client side
class ActorScriptPart_ChangeWeapon : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_ChangeWeapon(const std::string & Name);
	
	//! destructor
	virtual ~ActorScriptPart_ChangeWeapon(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPChangeWeapon"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	std::string		_Name;
};



//! use to start a script on client side
class ActorScriptPart_ChangeMode : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_ChangeMode(const std::string & Name);
	
	//! destructor
	virtual ~ActorScriptPart_ChangeMode(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPChangeMode"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	std::string		_Name;
};



//! use to start a script on client side
class ActorScriptPart_WaitForSignal : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_WaitForSignal(int Signalnumber);
	
	//! destructor
	virtual ~ActorScriptPart_WaitForSignal(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPWaitForSignal"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	int		_Signalnumber;
};




//! use to start a script on client side
class ActorScriptPart_SendSignal : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_SendSignal(int Signalnumber, long ActorId);
	
	//! destructor
	virtual ~ActorScriptPart_SendSignal(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPSendSignal"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	int		_Signalnumber;
	long	_ActorId;
};



//! use to start a script on client side
class ActorScriptPart_TeleportTo : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_TeleportTo(float PosX, float PosY, float PosZ);
	
	//! destructor
	virtual ~ActorScriptPart_TeleportTo(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPTeleportTo"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	float	_PosX;
	float	_PosY;
	float	_PosZ;
};





//! use to start a script on client side
class ActorScriptPart_Custom : public ActorScriptPartBase
{
public:
	//! constructor
	ActorScriptPart_Custom(const std::string & fctName);
	
	//! destructor
	virtual ~ActorScriptPart_Custom(){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ASPCustom"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ofstream & file, const std::string & name);

	// save script to lua file
	virtual void WriteExecutionScript(std::ostream & file, long actid);

#ifdef _USE_QT_EDITOR_
	// use by the editor
	virtual void WriteToQt(TreeModel *	model, const QModelIndex &parentIdx);

	virtual void UpdateFromQt(TreeModel *	model, const QModelIndex &parentIdx, int rowidx);
#endif



private:
	std::string		_fctName;
};





#endif
