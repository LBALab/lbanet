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

#ifndef _LBANET_TRIGGERS_H__
#define _LBANET_TRIGGERS_H__

#include "Actions.h"
#include "ActorHandler.h"
#include "DelayedExecutionHandler.h"


#include <boost/shared_ptr.hpp>
#include <set>

struct TriggerInfo
{
	//! constructor
	TriggerInfo()
		: id(-1) {}

	//! constructor
	TriggerInfo(long Id, const std::string & Name,
					bool cplayer, bool cnpc, bool cmovable)
		: id(Id), name(Name), CheckPlayers(cplayer), CheckNpcs(cnpc), CheckMovableObjects(cmovable)
	{}

	long id;
	std::string name;
	bool CheckPlayers;
	bool CheckNpcs;
	bool CheckMovableObjects;
};


//! base class handling game triggers
class TriggerBase
{
public:
	//! constructor
	TriggerBase(const TriggerInfo & triggerinfo)
		: _triggerinfo(triggerinfo),
			_posX(0), _posY(0), _posZ(0)
	{}
	
	//! destructor
	virtual ~TriggerBase(void){}

	//! set the map owning the trigger
	void SetOwner(ScriptEnvironmentBase * owner)
	{ _owner = owner; }


	//! set trigger position in world
	void SetPosition(float X, float Y, float Z)
	{
		_posX = X;
		_posY = Y;
		_posZ = Z;
	}


	//! get trigger id
	long GetId()
	{ return _triggerinfo.id;}

	//! get trigger name
	std::string GetName()
	{ return _triggerinfo.name;}

	//! set trigger name
	void SetName(const std::string & name)
	{ _triggerinfo.name = name;}

	//! set trigger info
	void SetTriggerInfo(const TriggerInfo& triggerinfo)
	{ _triggerinfo = triggerinfo;}

	//! set action1
	void SetAction1(ActionBasePtr action)
	{_action1 = action;}

	//! set action2
	void SetAction2(ActionBasePtr action)
	{_action2 = action;}

	//! set action3
	void SetAction3(ActionBasePtr action)
	{_action3 = action;}


	//! get action1
	ActionBasePtr GetAction1()
	{ return _action1;}

	//! get action2
	ActionBasePtr GetAction2()
	{ return _action2;}

	//! get action3
	ActionBasePtr GetAction3()
	{ return _action3;}

	// acessor
	float GetPosX()
	{ return _posX;}

	// acessor
	float GetPosY()
	{ return _posY;}

	// acessor
	float GetPosZ()
	{ return _posZ;}

	//accessor
	bool CheckPlayer()
	{return _triggerinfo.CheckPlayers;}

	//accessor
	bool CheckNpcs()
	{return _triggerinfo.CheckNpcs;}

	//accessor
	bool CheckMovableObjects()
	{return _triggerinfo.CheckMovableObjects;}



	//! get type of the action in string form
	virtual std::string GetTypeName(){ return "";}

	//! check trigger on object enter map
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectEnterMap(DelayedExecutionHandler * delayedactH, int ObjectType, Ice::Long ObjectId){}

	//! check trigger on object leave map
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectLeaveMap(DelayedExecutionHandler * delayedactH, int ObjectType, Ice::Long ObjectId){}

	//! check trigger on object move
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectMoved(DelayedExecutionHandler * delayedactH, int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerPosition &startposition,
										const LbaNet::PlayerPosition &endposition,
										const LbaNet::ModelState &state){}


	//! check trigger on object action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	// ObjectMode give the mode the object was when performing the action
	virtual void ObjectAction(DelayedExecutionHandler * delayedactH, int ObjectType, Ice::Long ObjectId,
														const LbaNet::PlayerPosition &info,
														const std::string &ObjectMode){}


	//! check trigger on each fram
	//! warning - this can reduce performance!
	virtual void NewFrame(DelayedExecutionHandler * delayedactH, double tnow, float tdiff){}


	//! get object to display for editor
	virtual ActorObjectInfo GetDisplayObject()
	{
		return ActorObjectInfo();
	}

	// save trigger to lua file
	virtual void SaveToLuaFile(std::ostream & file){}

protected:
	TriggerInfo							_triggerinfo;

	ScriptEnvironmentBase *				_owner;
	float								_posX;
	float								_posY;
	float								_posZ;

	ActionBasePtr						_action1;
	ActionBasePtr						_action2;
	ActionBasePtr						_action3;

};



//! class handling triggers when player/object enter/leave zone
class ZoneTrigger : public TriggerBase
{
public:
	//! constructor
	//! AllowMultiActivation is used as flag to know if the trigger should be activated
	//! again if an object is already inside the zone and a second object enters
	//! as an example for door trigger, we would set the flag to false as only 
	//! the first player entering would open
	//! the door, any other player entering the zone will do nothing
	//! as well, the door will close only when the last player leave the zone
	ZoneTrigger( const TriggerInfo & triggerinfo,
					float sizeX, float sizeY, float sizeZ, 
					bool AllowMultiActivation);
	
	//! destructor
	virtual ~ZoneTrigger(void);

	//! check trigger on object move
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectMoved(DelayedExecutionHandler * delayedactH, int ObjectType, Ice::Long ObjectId,
										const LbaNet::PlayerPosition &StartPosition,
										const LbaNet::PlayerPosition &EndPosition,
										const LbaNet::ModelState &state);

	//! check trigger on object leave map
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void ObjectLeaveMap(DelayedExecutionHandler * delayedactH, int ObjectType, Ice::Long ObjectId);

	//! check trigger on each fram
	//! warning - this can reduce performance!
	virtual void NewFrame(DelayedExecutionHandler * delayedactH, double tnow, float tdiff);


	//! get type of the action in string form
	virtual std::string GetTypeName(){ return "ZoneTrigger";}

	// acessor
	float GetSizeX()
	{ return _sizeX*2;}

	// acessor
	float GetSizeY()
	{ return _sizeY;}

	// acessor
	float GetSizeZ()
	{ return _sizeZ*2;}

	// set size
	void SetSize(float X, float Y, float Z)
	{
		_sizeX = X / 2;
		_sizeY = Y;
		_sizeZ = Z / 2;
	}

	// acessor
	bool MultiActivation()
	{ return _AllowMultiActivation;}

	// acessor
	void SetMultiActivation(bool allow)
	{_AllowMultiActivation = allow;}


	//! get object to display for editor
	virtual ActorObjectInfo GetDisplayObject();

	// save trigger to lua file
	virtual void SaveToLuaFile(std::ostream & file);


	void SetStayUpdateFrequency(double StayUpdateFrequency)
	{ _StayUpdateFrequency = StayUpdateFrequency;}

	double GetStayUpdateFrequency()
	{ return _StayUpdateFrequency;}

	void SetActivateOnJump(bool Activate)
	{ _activateOnJump = Activate;}

	bool GetActivateOnJump()
	{ return _activateOnJump;}


protected:

	struct Point  
	{  
		float x,y,z;  
	};  
	  
	struct Box  
	{  
		Point min,max;  
	};  


	//! when object entered
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	void Entered(int ObjectType, Ice::Long ObjectId,
						float offsetX, float offsetY, float offsetZ);

	//! when object left
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	void Left(int ObjectType, Ice::Long ObjectId);


	//perform a sweep test
	bool SweepTest(	const LbaNet::PlayerPosition &StartPosition,
					const LbaNet::PlayerPosition &EndPosition,
					LbaNet::PlayerPosition &CollisionPoint);


private:
	float													_sizeX;
	float													_sizeY;
	float													_sizeZ;
	bool													_AllowMultiActivation;

	double													_StayUpdateFrequency;
	bool													_activateOnJump;


	std::map<std::pair<int, Ice::Long>, double >			_objectsinside;
};




//! class handling triggers when player/object use action at a certain distance of an object
class ActivationTrigger : public TriggerBase
{
public:
	//! constructor
	//! can configure up to 2 modes to be accepted for trigger the action
	ActivationTrigger( const TriggerInfo & triggerinfo,
							float MaxDistance, 
							const std::string & AcceptedMode1, 
							const std::string & AcceptedMode2);
	
	//! destructor
	virtual ~ActivationTrigger(void);


	//! check trigger on object action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	// ObjectMode give the mode the object was when performing the action
	virtual void ObjectAction(DelayedExecutionHandler * delayedactH, int ObjectType, Ice::Long ObjectId,
													const LbaNet::PlayerPosition &info,
													const std::string &ObjectMode);

	//! get type of the action in string form
	virtual std::string GetTypeName(){ return "ActivationTrigger";}

	//! get distance
	float GetDistance();

	//! set distance
	void SetDistance(float distance);

	// acessor
	std::string GetAcceptedMode1()
	{return _AcceptedMode1;}

	// acessor
	std::string GetAcceptedMode2()
	{return _AcceptedMode2;}

	// acessor
	void SetMode1(const std::string & mode)
	{_AcceptedMode1 = mode;}

	// acessor
	void SetMode2(const std::string & mode)
	{_AcceptedMode2 = mode;}


	//! get object to display for editor
	virtual ActorObjectInfo GetDisplayObject();

	// save trigger to lua file
	virtual void SaveToLuaFile(std::ostream & file);

	//! accessor
	bool GetPlayAnimation()
	{ return _PlayAnimation;}

	//! accessor
	void SetPlayAnimation(bool play)
	{ _PlayAnimation = play;}

private:
	float									_MaxSquaredDistance; 
	std::string								_AcceptedMode1; 
	std::string								_AcceptedMode2;
	bool									_PlayAnimation;
};



//! class handling triggers when player/object use action in a zone
class ZoneActionTrigger : public TriggerBase
{
public:
	//! constructor
	ZoneActionTrigger( const TriggerInfo & triggerinfo,
						float sizeX, float sizeY, float sizeZ, 
							const std::string & AcceptedMode1, 
							const std::string & AcceptedMode2);
	
	//! destructor
	virtual ~ZoneActionTrigger(void);


	//! check trigger on object action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	// ObjectMode give the mode the object was when performing the action
	virtual void ObjectAction(DelayedExecutionHandler * delayedactH, int ObjectType, Ice::Long ObjectId,
													const LbaNet::PlayerPosition &info,
													const std::string &ObjectMode);

	//! get type of the action in string form
	virtual std::string GetTypeName(){ return "ZoneActionTrigger";}

	// acessor
	float GetSizeX()
	{ return _sizeX*2;}

	// acessor
	float GetSizeY()
	{ return _sizeY;}

	// acessor
	float GetSizeZ()
	{ return _sizeZ*2;}

	// set size
	void SetSize(float X, float Y, float Z)
	{
		_sizeX = X / 2;
		_sizeY = Y;
		_sizeZ = Z / 2;
	}

	// acessor
	std::string GetAcceptedMode1()
	{return _AcceptedMode1;}

	// acessor
	std::string GetAcceptedMode2()
	{return _AcceptedMode2;}

	// acessor
	void SetMode1(const std::string & mode)
	{_AcceptedMode1 = mode;}

	// acessor
	void SetMode2(const std::string & mode)
	{_AcceptedMode2 = mode;}

	//! get object to display for editor
	virtual ActorObjectInfo GetDisplayObject();

	// save trigger to lua file
	virtual void SaveToLuaFile(std::ostream & file);

	//! accessor
	bool GetPlayAnimation()
	{ return _PlayAnimation;}

	//! accessor
	void SetPlayAnimation(bool play)
	{ _PlayAnimation = play;}
private:


	float									_sizeX;
	float									_sizeY;
	float									_sizeZ;

	std::string								_AcceptedMode1; 
	std::string								_AcceptedMode2;
	bool									_PlayAnimation;
};


//! class handling triggers happening on regular timer
class TimerTrigger : public TriggerBase
{
public:
	//! constructor
	TimerTrigger( const TriggerInfo & triggerinfo,
						long TimeInMillisecond);
	
	//! destructor
	virtual ~TimerTrigger(void);


	//! check trigger on each fram
	//! warning - this can reduce performance!
	virtual void NewFrame(DelayedExecutionHandler * delayedactH, double tnow, float tdiff);

	//! get type of the action in string form
	virtual std::string GetTypeName(){ return "TimerTrigger";}


	// save trigger to lua file
	virtual void SaveToLuaFile(std::ostream & file);

	// acessor
	long GetTimeinMs()
	{ return _TimeInMillisecond;}

	// acessor
	void SetTime(long ms)
	{ _TimeInMillisecond = ms;}

private:
	long	_TimeInMillisecond;
	double	_lasttime;
};


#endif
