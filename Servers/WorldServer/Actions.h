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

#ifndef _LBANET_ACTION_H__
#define _LBANET_ACTION_H__

#include <LbaTypes.h>
#include <boost/shared_ptr.hpp>
class ScriptEnvironmentBase;

#include "ActionArguments.h"
#include "Conditions.h"
#include "ClientScript.h"

class ActionBase;
typedef boost::shared_ptr<ActionBase> ActionBasePtr;


//! base class used as action to be performed on trigger
class ActionBase
{
public:
	//! constructor
	ActionBase()
	{}
	
	//! destructor
	virtual ~ActionBase(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args){}

	//! get type of the action in string form
	virtual std::string GetTypeName(){ return "";}


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name){}

};



//! use to teleport the object to a new location
class TeleportAction : public ActionBase
{
public:
	//! constructor
	TeleportAction();
	
	//! destructor
	virtual ~TeleportAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "TeleportAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// acessor
	std::string GetMapName()
	{ return _NewMap;}

	// acessor
	long GetSpawning()
	{ return _SpawningId;}


	// acessor
	void SetMapName(std::string map)
	{ _NewMap = map;}

	// acessor
	void SetSpawning(long spawn)
	{ _SpawningId = spawn;}


private:
	std::string		_NewMap;
	long			_SpawningId;
};



//! use to start a script on client side
class ClientScriptAction : public ActionBase
{
public:
	//! constructor
	ClientScriptAction();
	
	//! destructor
	virtual ~ClientScriptAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ClientScriptAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// accessor
	ClientScriptBasePtr GetScript()
	{ return _Script;}

	void SetScript(ClientScriptBasePtr Script)
	{ _Script = Script;}

private:
	ClientScriptBasePtr		_Script;
};




//! use to perform a custom lua action
class CustomAction : public ActionBase
{
public:
	//! constructor
	CustomAction();
	
	//! destructor
	virtual ~CustomAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "CustomAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// accessor
	std::string GetLuaFunctionName()
	{ return _customluafunctionname;}

	void SetLuaFunctionName(std::string FunctionName)
	{ _customluafunctionname = FunctionName;}

private:
	std::string		_customluafunctionname;
};




//! use to display a text on client
class DisplayTextAction : public ActionBase
{
public:
	//! constructor
	DisplayTextAction();
	
	//! destructor
	virtual ~DisplayTextAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "DisplayTextAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// acessor
	long GetTextId()
	{ return _TextId;}

	// acessor
	void SetTextId(long id)
	{ _TextId = id;}


private:
	long			_TextId;
};



//! use to display a text on client
class ConditionalAction : public ActionBase
{
public:
	//! constructor
	ConditionalAction();
	
	//! destructor
	virtual ~ConditionalAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "ConditionalAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	//accessors
	void SetCondition(ConditionBasePtr	condition)
	{ _condition = condition; }

	ConditionBasePtr GetCondition()
	{ return _condition; }

	void SetActionTrue(ActionBasePtr act)
	{_actionTrue = act;}

	void SetActionFalse(ActionBasePtr act)
	{_actionFalse = act;}

	ActionBasePtr GetActionTrue()
	{ return _actionTrue; }

	ActionBasePtr GetActionFalse()
	{ return _actionFalse; }

private:
	ConditionBasePtr		_condition;

	ActionBasePtr			_actionTrue;
	ActionBasePtr			_actionFalse;
};




struct ContainerSharedInfo
{
	long				OpeningClient;
	LbaNet::ItemsMap	ContainerItems;
};

// work-around because lua did not work with LbaNet::ItemGroupElement ...
struct ContainerItemGroupElement
{
	ContainerItemGroupElement(long id, int min, int max, float proba, int group)
		: Id(id), Min(min), Max(max), Probability(proba), Group(group)
	{}

	long 			Id;
	int 			Min;
	int 			Max;
	float 			Probability;
	int 			Group;
};



//! use to display a text on client
class OpenContainerAction : public ActionBase
{
public:
	//! constructor
	OpenContainerAction();
	
	//! destructor
	virtual ~OpenContainerAction(void);

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "OpenContainerAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// acessor
	double GetTimeToReset()
	{ return _TimeToReset/1000;}

	// acessor
	void SetTimeToReset(double t)
	{ _TimeToReset = t*1000;}


	//add item to container start
	void AddItem(const ContainerItemGroupElement &item);

	// get items
	std::vector<ContainerItemGroupElement> &GetItems()
	{return _containerstartitems;}

	// check if item already in container
	bool ItemExist(long id);

protected:
	// prepare the container
	void PrepareContainer();

	//clear container
	void ClearContainer();

private:
	double									_lastResetTime;
	double									_TimeToReset;

	boost::shared_ptr<ContainerSharedInfo>	_shared;
	std::vector<ContainerItemGroupElement>	_containerstartitems;
};



//! use to display a text on client
class SendSignalAction : public ActionBase
{
public:
	//! constructor
	SendSignalAction()
		: _Actorid(-1), _signal(-1)
	{}
	
	//! destructor
	virtual ~SendSignalAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "SendSignalAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// acessor
	long GetActorId()
	{ return _Actorid;}

	// acessor
	void SetActorId(long id)
	{ _Actorid = id;}

	// acessor
	int GetSignal()
	{ return _signal;}

	// acessor
	void SetSignal(int s)
	{ _signal = s;}


protected:
	long	_Actorid;
	int		_signal;
};



//! use to display a text on client
class OpenDoorAction : public SendSignalAction
{
public:
	//! constructor
	OpenDoorAction()
	{
		_signal = 10;
	}
	
	//! destructor
	virtual ~OpenDoorAction(void){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "OpenDoorAction"; }

	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);
};


//! use to display a text on client
class CloseDoorAction : public SendSignalAction
{
public:
	//! constructor
	CloseDoorAction()
	{
		_signal = 11;
	}
	
	//! destructor
	virtual ~CloseDoorAction(void){}


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "CloseDoorAction"; }

	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);
};





//! use to display a text on client
class AddRemoveItemAction : public ActionBase
{
public:
	//! constructor
	AddRemoveItemAction()
		: _Itemid(-1), _number(1), _informClientType(1)
	{}
	
	//! destructor
	virtual ~AddRemoveItemAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "AddRemoveItemAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// acessor
	long GetItemId()
	{ return _Itemid;}

	// acessor
	void SetItemId(long id)
	{ _Itemid = id;}

	// acessor
	int GetNumber()
	{ return _number;}

	// acessor
	void SetNumber(int s)
	{ _number = s;}

	// acessor
	int GetInformClientType()
	{ return _informClientType;}

	// acessor
	void SetInformClientType(int s)
	{ _informClientType = s;}

	//! accessor
	std::string GetInformClientTypeString();

	//! accessor
	void SetInformClientTypeString(const std::string & anim);

private:
	long	_Itemid;
	int		_number;
	int		_informClientType;
};




//! use to display a text on client
class HurtAction : public ActionBase
{
public:
	//! constructor
	HurtAction()
		: _hurtvalue(0), _life(true),
			_playedanimation(0)
	{}
	
	//! destructor
	virtual ~HurtAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "HurtAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// acessor
	float GetHurtValue()
	{ return _hurtvalue;}

	// acessor
	void SetHurtValue(float v)
	{ _hurtvalue = v;}

	// acessor
	bool HurtLife()
	{ return _life;}

	// acessor
	void HurtLifeOrMana(bool Life)
	{ _life = Life;}

	// get played animation on hurt
	// 0 -> no
	// 1 -> hurtsmall
	// 2 -> hurtmedium
	// 3 -> hurtbig
	int GetPlayedAnimation()
	{ return _playedanimation; }

	void SetPlayedAnimation(int anim)
	{ _playedanimation = anim; }

	//! accessor
	std::string GetPlayAnimationString();

	//! accessor
	void SetAnimationString(const std::string & anim);

private:
	float	_hurtvalue;
	bool	_life;
	int		_playedanimation;
};



//! use to display a text on client
class KillAction : public ActionBase
{
public:
	//! constructor
	KillAction()
	{}
	
	//! destructor
	virtual ~KillAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "KillAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

};




//! use to display a text on client
class MultiAction : public ActionBase
{
public:
	//! constructor
	MultiAction()
	{}
	
	//! destructor
	virtual ~MultiAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "MultiAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);


	//! add action
	void AddAction(ActionBasePtr action);

	//! remove action
	void RemoveAction(ActionBasePtr action);

	//! get action list
	std::vector<ActionBasePtr> GetActions()
	{ return _actions;}

	//! replace old action by new one
	void ReplaceAction(ActionBasePtr olda, ActionBasePtr newa);

private:
	std::vector<ActionBasePtr>	_actions;

};



//! use to display a text on client
class SwitchAction : public ActionBase
{
public:
	//! constructor
	SwitchAction()
		: _actorid(-1), _switched(false)
	{}
	
	//! destructor
	virtual ~SwitchAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "SwitchAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// get actor id
	long GetActorId()
	{ return _actorid;}

	// set actor id
	void SetActorId(long id)
	{ _actorid = id;}


	// get actor id
	std::string GetSwitchModel()
	{ return _switchingmodel;}

	// set actor id
	void SetSwitchModel(const std::string id)
	{ _switchingmodel = id;}



	void SetActionTrue(ActionBasePtr act)
	{_actionTrue = act;}

	void SetActionFalse(ActionBasePtr act)
	{_actionFalse = act;}

	ActionBasePtr GetActionTrue()
	{ return _actionTrue; }

	ActionBasePtr GetActionFalse()
	{ return _actionFalse; }

private:
	ActionBasePtr			_actionTrue;
	ActionBasePtr			_actionFalse;

	long					_actorid;
	std::string				_switchingmodel;
	bool					_switched;

};




//! use to display a text on client
class StartQuestAction : public ActionBase
{
public:
	//! constructor
	StartQuestAction()
		: _QuestId(-1)
	{}
	
	//! destructor
	virtual ~StartQuestAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "StartQuestAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// acessor
	long GetQuestId()
	{ return _QuestId;}

	// acessor
	void SetQuestId(long id)
	{ _QuestId = id;}


private:
	long			_QuestId;
};



//! use to display a text on client
class FinishQuestAction : public ActionBase
{
public:
	//! constructor
	FinishQuestAction()
		: _QuestId(-1)
	{}
	
	//! destructor
	virtual ~FinishQuestAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "FinishQuestAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// acessor
	long GetQuestId()
	{ return _QuestId;}

	// acessor
	void SetQuestId(long id)
	{ _QuestId = id;}


private:
	long			_QuestId;
};





//! use to display a text on client
class OpenShopAction : public ActionBase
{
public:
	//! constructor
	OpenShopAction()
	{
		_currencyitem.Id = -1;
	}

	//! destructor
	virtual ~OpenShopAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "OpenShopAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);


	//add item to container start
	void AddItem(long item, int price);

	//add item to container start
	LbaNet::ItemInfo AddItemR(long item, int price);

	// get items
	const LbaNet::ItemsMap &GetItems()
	{return _items;}

	//remove item to container start
	void RemoveItem(long item);

	// get currency item
	long GetCurrencyItem();

	// set currency item
	void SetCurrencyItem(long it);


private:
	LbaNet::ItemsMap	_items;
	LbaNet::ItemInfo	_currencyitem;
};




//! use to display a text on client
class CutMapAction : public ActionBase
{
public:
	//! constructor
	CutMapAction()
		: _Y(-1)
	{}
	
	//! destructor
	virtual ~CutMapAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "CutMapAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

	// acessor
	float GetY()
	{ return _Y;}

	// acessor
	void SetY(float id)
	{ _Y = id;}


private:
	float			_Y;
};



//! use to display a text on client
class OpenLetterWritterAction : public ActionBase
{
public:
	//! constructor
	OpenLetterWritterAction()
	{}
	
	//! destructor
	virtual ~OpenLetterWritterAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "OpenLetterWritterAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

};


//! use to display a text on client
class OpenMailboxAction : public ActionBase
{
public:
	//! constructor
	OpenMailboxAction()
	{}
	
	//! destructor
	virtual ~OpenMailboxAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "OpenMailboxAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);

};



//! use to display a text on client
class PlaySoundAction : public ActionBase
{
public:
	//! constructor
	PlaySoundAction()
		: _toeveryone(false)
	{}
	
	//! destructor
	virtual ~PlaySoundAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "PlaySoundAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);


	// acessor
	bool GetToEveryone()
	{ return _toeveryone;}

	// acessor
	void SetToEveryone(bool v)
	{ _toeveryone = v;}

	// acessor
	std::string GetSoundPath()
	{ return _soundpath;}

	// acessor
	void SetSoundPath(const std::string& v)
	{ _soundpath = v;}


private:
	std::string			_soundpath;
	bool				_toeveryone;
};




//! use to display a text on client
class SetFlagAction : public ActionBase
{
public:
	//! constructor
	SetFlagAction()
		: _value(1)
	{}
	
	//! destructor
	virtual ~SetFlagAction(void){}

	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
	virtual void Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args);


	//! get type of the action in string form
	virtual std::string GetTypeName()
	{return "SetFlagAction"; }


	// save action to lua file
	virtual void SaveToLuaFile(std::ostream & file, const std::string & name);


	// acessor
	int GetValue()
	{ return _value;}

	// acessor
	void SetValue(int v)
	{ _value = v;}

	// acessor
	std::string GetFlagName()
	{ return _flag;}

	// acessor
	void SetFlagName(const std::string& v)
	{ _flag = v;}


private:
	std::string			_flag;
	int					_value;
};

#endif
