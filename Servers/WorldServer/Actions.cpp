#include "Actions.h"
#include "ScriptEnvironmentBase.h"
#include "SynchronizedTimeHandler.h"
#include <fstream>
#include "Randomizer.h"
#include "InventoryItemHandler.h"
#include "ClientProxyHandler.h"
#include "SharedDataHandler.h"
#include "MapHandler.h"
#include "Randomizer.h"

/***********************************************************
constructor
***********************************************************/
TeleportAction::TeleportAction()
: _SpawningId(-1)
{

}

/***********************************************************
destructor
***********************************************************/
TeleportAction::~TeleportAction(void)
{

}

/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void TeleportAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	if(owner)
	{
		float offsetX=0, offsetY=0, offsetZ=0;
		if(args)
		{
			ActionArgumentBase & obj = *args;
			const std::type_info& info = typeid(obj);

			// player updated position
			if(info == typeid(OffsetArgument))
			{
				OffsetArgument* castedptr =
					static_cast<OffsetArgument *>(args);

				offsetX = castedptr->_offsetX;
				offsetY = castedptr->_offsetY;
				offsetZ = castedptr->_offsetZ;
			}
		}

		owner->Teleport(ObjectType, (long)ObjectId, _NewMap, _SpawningId,
							offsetX, offsetY, offsetZ);
	}
}


/***********************************************************
save action to lua file
***********************************************************/
void TeleportAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = TeleportAction()"<<std::endl;
	file<<"\t"<<name<<":SetMapName(\""<<_NewMap<<"\")"<<std::endl;
	file<<"\t"<<name<<":SetSpawning("<<_SpawningId<<")"<<std::endl;
}




/***********************************************************
constructor
***********************************************************/
ClientScriptAction::ClientScriptAction()
{

}

/***********************************************************
destructor
***********************************************************/
ClientScriptAction::~ClientScriptAction(void)
{

}

/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void ClientScriptAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	if(_Script)
		_Script->Execute(owner, ObjectType, ObjectId);
}


/***********************************************************
save action to lua file
***********************************************************/
void ClientScriptAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = ClientScriptAction()"<<std::endl;

	if(_Script)
	{
		std::stringstream csname;
		csname<<name<<"_cs";
		_Script->SaveToLuaFile(file, csname.str());
		file<<"\t"<<name<<":SetScript("<<csname.str()<<")"<<std::endl;
	}
}






/***********************************************************
constructor
***********************************************************/
CustomAction::CustomAction()
{

}

/***********************************************************
destructor
***********************************************************/
CustomAction::~CustomAction(void)
{

}

/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void CustomAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	if(owner && _customluafunctionname != "")
		owner->ExecuteCustomAction(ObjectType, (long)ObjectId, _customluafunctionname, args);
}


/***********************************************************
save action to lua file
***********************************************************/
void CustomAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = CustomAction()"<<std::endl;
	file<<"\t"<<name<<":SetLuaFunctionName(\""<<_customluafunctionname<<"\")"<<std::endl;
}




/***********************************************************
constructor
***********************************************************/
DisplayTextAction::DisplayTextAction()
: _TextId(0)
{

}

/***********************************************************
destructor
***********************************************************/
DisplayTextAction::~DisplayTextAction(void)
{

}

/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void DisplayTextAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	if(owner)
		owner->DisplayTxtAction(ObjectType, (long)ObjectId, _TextId);
}


/***********************************************************
save action to lua file
***********************************************************/
void DisplayTextAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = DisplayTextAction()"<<std::endl;
	file<<"\t"<<name<<":SetTextId("<<_TextId<<")"<<std::endl;
}




/***********************************************************
constructor
***********************************************************/
ConditionalAction::ConditionalAction()
{

}


/***********************************************************
destructor
***********************************************************/
ConditionalAction::~ConditionalAction(void)
{

}

/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void ConditionalAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
											ActionArgumentBase* args)
{
	if(_condition && _condition->Passed(owner, ObjectType, ObjectId))
	{
		if(_actionTrue)
			_actionTrue->Execute(owner, ObjectType, ObjectId, 0);
	}
	else
	{
		if(_actionFalse)
			_actionFalse->Execute(owner, ObjectType, ObjectId, 0);
	}
}




/***********************************************************
save action to lua file
***********************************************************/
void ConditionalAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = ConditionalAction()"<<std::endl;

	if(_actionTrue)
	{
		std::stringstream aname;
		aname<<name<<"_act1";
		_actionTrue->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name<<":SetActionTrue("<<aname.str()<<")"<<std::endl;
	}

	if(_actionFalse)
	{
		std::stringstream aname;
		aname<<name<<"_act2";
		_actionFalse->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name<<":SetActionFalse("<<aname.str()<<")"<<std::endl;
	}

	if(_condition)
	{
		std::stringstream condname;
		condname<<name<<"_cond";
		_condition->SaveToLuaFile(file, condname.str());

		file<<"\t"<<name<<":SetCondition("<<condname.str()<<")"<<std::endl;
	}

}



/***********************************************************
	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
***********************************************************/
void SendSignalAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args)
{
	if(owner && _Actorid >= 0 && _signal >= 0)
		owner->SendSignalToActor(_Actorid, _signal);
}



/***********************************************************
save action to lua file
***********************************************************/
void SendSignalAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = SendSignalAction()"<<std::endl;
	file<<"\t"<<name<<":SetActorId("<<_Actorid<<")"<<std::endl;
	file<<"\t"<<name<<":SetSignal("<<_signal<<")"<<std::endl;
}




/***********************************************************
save action to lua file
***********************************************************/
void OpenDoorAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = OpenDoorAction()"<<std::endl;
	file<<"\t"<<name<<":SetActorId("<<_Actorid<<")"<<std::endl;
}



/***********************************************************
save action to lua file
***********************************************************/
void CloseDoorAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = CloseDoorAction()"<<std::endl;
	file<<"\t"<<name<<":SetActorId("<<_Actorid<<")"<<std::endl;
}






/***********************************************************
constructor
***********************************************************/
OpenContainerAction::OpenContainerAction()
: _lastResetTime(0), _TimeToReset(600000) // set to 10 min
{
	_shared = boost::shared_ptr<LbaNet::ContainerSharedInfo>(new LbaNet::ContainerSharedInfo());
	_shared->OpeningClient = -1;
}


/***********************************************************
destructor
***********************************************************/
OpenContainerAction::~OpenContainerAction(void)
{

}


/***********************************************************
	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
***********************************************************/
void OpenContainerAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args)
{
	long clientid = -1;

	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return;

	// check if container already opened
	if(_shared->OpeningClient > 0)
	{
		// do nothing if same client
		if(_shared->OpeningClient == clientid)
			return;

		// if so send error message to client
		if(owner)
			owner->SendErrorMessage(clientid, "Container used", "The container is already in use by another player.");

		return;
	}

	// set client as opener
	_shared->OpeningClient = clientid;


	//prepare item set
	PrepareContainer();


	// send container to client
	if(owner)
		owner->OpenContainer(clientid, _shared);
}



/***********************************************************
prepare the container
***********************************************************/
void OpenContainerAction::PrepareContainer()
{
	double currtime = SynchronizedTimeHandler::GetCurrentTimeDouble();
	if((currtime-_lastResetTime) > _TimeToReset)
	{
		_lastResetTime = currtime;

		//reset container
		ClearContainer();


		//fill container with items
		std::vector<ContainerItemGroupElement>::iterator itc = _containerstartitems.begin();
		std::vector<ContainerItemGroupElement>::iterator endc = _containerstartitems.end();

		std::map<int, std::vector<ContainerItemGroupElement> > groups;
		for(; itc != endc; ++itc)
		{
			if(itc->Group < 0)
			{
				bool add = true;
				if(itc->Probability < 1)
					if(Randomizer::getInstance()->Rand() > itc->Probability)
						add = false;

				if(add)
				{
					LbaNet::ItemPosInfo newitem;
					newitem.Position = 1;
					newitem.Info = InventoryItemHandler::getInstance()->GetItemInfo(itc->Id);
					newitem.Count = Randomizer::getInstance()->RandInt(itc->Min, itc->Max);
					_shared->ContainerItems[itc->Id] = newitem;
				}
			}
			else
			{
				//item part of a group
				groups[itc->Group].push_back(*itc);
			}
		}


		// take care of the groups
		std::map<int, std::vector<ContainerItemGroupElement> >::iterator itm = groups.begin();
		std::map<int, std::vector<ContainerItemGroupElement> >::iterator endm = groups.end();
		for(; itm != endm; ++itm)
		{
			float currp = 0;
			float proba = (float)Randomizer::getInstance()->Rand();
			std::vector<ContainerItemGroupElement>::iterator itcc = itm->second.begin();
			std::vector<ContainerItemGroupElement>::iterator endcc = itm->second.end();
			for(; itcc != endcc; ++itcc)
			{
				currp += itcc->Probability;
				if(currp > proba)
				{
					// add item
					LbaNet::ItemPosInfo newitem;
					newitem.Position = 1;
					newitem.Info = InventoryItemHandler::getInstance()->GetItemInfo(itcc->Id);
					newitem.Count = Randomizer::getInstance()->RandInt(itcc->Min, itcc->Max);
					_shared->ContainerItems[itcc->Id] = newitem;

					break;
				}
			}
		}


	}
}



/***********************************************************
save action to lua file
***********************************************************/
void OpenContainerAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = OpenContainerAction()"<<std::endl;
	file<<"\t"<<name<<":SetTimeToReset("<<GetTimeToReset()<<")"<<std::endl;
	for(size_t i=0; i< _containerstartitems.size(); ++i)
	{
		std::stringstream itname;
		itname<<name<<"ContItem"<<i;
		file<<"\t\t"<<itname.str()<<" = ContainerItemGroupElement("
			<<_containerstartitems[i].Id<<","
			<<_containerstartitems[i].Min<<","
			<<_containerstartitems[i].Max<<","
			<<_containerstartitems[i].Probability<<","
			<<_containerstartitems[i].Group<<")"<<std::endl;
		file<<"\t\t"<<name<<":AddItem("<<itname.str()<<")"<<std::endl;
	}
}


/***********************************************************
add item to container start
***********************************************************/
void OpenContainerAction::AddItem(const ContainerItemGroupElement &item)
{
	_containerstartitems.push_back(item);
}


/***********************************************************
clear container
***********************************************************/
void OpenContainerAction::ClearContainer()
{
	LbaNet::ItemsMap toswap;
	LbaNet::ItemsMap & map = _shared->ContainerItems;
	LbaNet::ItemsMap::iterator itm = map.begin();

	for(;itm != map.end(); ++itm)
	{
		if(itm->second.Position <= 0)
			toswap[itm->first] =itm->second;
	}

	toswap.swap(map);
}


/***********************************************************
check if item already in container
***********************************************************/
bool OpenContainerAction::ItemExist(long id)
{
	for(size_t i=0; i< _containerstartitems.size(); ++i)
		if(_containerstartitems[i].Id == id)
			return true;

	return false;
}





/***********************************************************
	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
***********************************************************/
void AddRemoveItemAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args)
{
	long clientid = -1;

	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return;

	if(owner)
		owner->AddOrRemoveItem(clientid, _Itemid, _number, _informClientType);
}



/***********************************************************
save action to lua file
***********************************************************/
void AddRemoveItemAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = AddRemoveItemAction()"<<std::endl;
	file<<"\t"<<name<<":SetItemId("<<_Itemid<<")"<<std::endl;
	file<<"\t"<<name<<":SetNumber("<<_number<<")"<<std::endl;
	file<<"\t"<<name<<":SetInformClientType("<<_informClientType<<")"<<std::endl;
}


/***********************************************************
accessor
***********************************************************/
std::string AddRemoveItemAction::GetInformClientTypeString()
{
	std::string res = "No";

	if(_informClientType == 1)
		res = "Chat";
	if(_informClientType == 2)
		res = "Happy";

	return res;
}



/***********************************************************
accessor
***********************************************************/
void AddRemoveItemAction::SetInformClientTypeString(const std::string & anim)
{
	_informClientType = 0;

	if(anim == "Chat")
		_informClientType = 1;
	if(anim == "Happy")
		_informClientType = 2;
}



/***********************************************************
	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
***********************************************************/
void HurtAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args)
{
	if(owner)
		owner->HurtActor(ObjectType, (long)ObjectId, _hurtvalue, _life, _playedanimation);
}



/***********************************************************
save action to lua file
***********************************************************/
void HurtAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = HurtAction()"<<std::endl;
	file<<"\t"<<name<<":SetHurtValue("<<_hurtvalue<<")"<<std::endl;
	file<<"\t"<<name<<":SetPlayedAnimation("<<_playedanimation<<")"<<std::endl;
	file<<"\t"<<name<<":HurtLifeOrMana("<<(_life?"true":"false")<<")"<<std::endl;
}



/***********************************************************
accessor
***********************************************************/
std::string HurtAction::GetPlayAnimationString()
{
	std::string res = "No";

	if(_playedanimation == 1)
		res = "SmallHurt";
	if(_playedanimation == 2)
		res = "MediumHurt";
	if(_playedanimation == 3)
		res = "BigHurt";

	return res;
}



/***********************************************************
accessor
***********************************************************/
void HurtAction::SetAnimationString(const std::string & anim)
{
	_playedanimation = 0;

	if(anim == "SmallHurt")
		_playedanimation = 1;
	if(anim == "MediumHurt")
		_playedanimation = 2;
	if(anim == "BigHurt")
		_playedanimation = 3;
}



/***********************************************************
	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
***********************************************************/
void KillAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args)
{
	if(owner)
		owner->KillActor(ObjectType, (long)ObjectId);
}



/***********************************************************
save action to lua file
***********************************************************/
void KillAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = KillAction()"<<std::endl;
}




/***********************************************************
	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
***********************************************************/
void MultiAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args)
{
	for(size_t i=0; i< _actions.size(); ++i)
		_actions[i]->Execute(owner, ObjectType, ObjectId, args);
}



/***********************************************************
save action to lua file
***********************************************************/
void MultiAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = MultiAction()"<<std::endl;
	for(size_t i=0; i< _actions.size(); ++i)
	{
		std::stringstream aname;
		aname<<name<<"_act"<<i;
		_actions[i]->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name<<":AddAction("<<aname.str()<<")"<<std::endl;
	}
}



/***********************************************************
add action
***********************************************************/
void MultiAction::AddAction(ActionBasePtr action)
{
	_actions.push_back(action);
}

/***********************************************************
remove action
***********************************************************/
void MultiAction::RemoveAction(ActionBasePtr action)
{
	std::vector<ActionBasePtr>::iterator it = std::find(_actions.begin(), _actions.end(), action);
	if(it != _actions.end())
		_actions.erase(it);
}


/***********************************************************
replace old action by new one
***********************************************************/
void MultiAction::ReplaceAction(ActionBasePtr olda, ActionBasePtr newa)
{
	std::vector<ActionBasePtr>::iterator it = std::find(_actions.begin(), _actions.end(), olda);
	if(it != _actions.end())
		*it = newa;
}



/***********************************************************
	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
***********************************************************/
void SwitchAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args)
{
	_switched = !_switched;

	if(_switched)
	{
		owner->SwitchActorModel(_actorid, _switchingmodel);

		if(_actionTrue)
			_actionTrue->Execute(owner, ObjectType, ObjectId, args);
	}
	else
	{
		owner->RevertActorModel(_actorid);

		if(_actionFalse)
			_actionFalse->Execute(owner, ObjectType, ObjectId, args);
	}
}



/***********************************************************
save action to lua file
***********************************************************/
void SwitchAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = SwitchAction()"<<std::endl;
	file<<"\t"<<name<<":SetActorId("<<_actorid<<")"<<std::endl;
	file<<"\t"<<name<<":SetSwitchModel(\""<<_switchingmodel<<"\")"<<std::endl;

	if(_actionTrue)
	{
		std::stringstream aname;
		aname<<name<<"_act"<<1;
		_actionTrue->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name<<":SetActionTrue("<<aname.str()<<")"<<std::endl;
	}

	if(_actionFalse)
	{
		std::stringstream aname;
		aname<<name<<"_act"<<1;
		_actionFalse->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name<<":SetActionFalse("<<aname.str()<<")"<<std::endl;
	}
}


/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void StartQuestAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	long clientid = -1;

	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return;

	if(owner)
		owner->StartQuest(clientid, _QuestId);
}


/***********************************************************
save action to lua file
***********************************************************/
void StartQuestAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = StartQuestAction()"<<std::endl;
	file<<"\t"<<name<<":SetQuestId("<<_QuestId<<")"<<std::endl;
}




/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void FinishQuestAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	long clientid = -1;

	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return;

	if(owner)
		owner->TriggerQuestEnd(clientid, _QuestId);
}


/***********************************************************
save action to lua file
***********************************************************/
void FinishQuestAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = FinishQuestAction()"<<std::endl;
	file<<"\t"<<name<<":SetQuestId("<<_QuestId<<")"<<std::endl;
}






/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void OpenShopAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	long clientid = -1;

	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return;

	if(owner)
		owner->OpenShop(clientid, _items, _currencyitem);
}


/***********************************************************
save action to lua file
***********************************************************/
void OpenShopAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = OpenShopAction()"<<std::endl;
	file<<"\t"<<name<<":SetCurrencyItem("<<_currencyitem.Id<<")"<<std::endl;

	LbaNet::ItemsMap::iterator it =	_items.begin();
	LbaNet::ItemsMap::iterator end = _items.end();
	for(; it != end; ++it)
		file<<"\t"<<name<<":AddItem("<<it->first<<", "<<it->second.Info.BuyPrice<<")"<<std::endl;
}



/***********************************************************
add item to container start
***********************************************************/
void OpenShopAction::AddItem(long item, int price)
{
	if(item >= 0)
	{
		LbaNet::ItemPosInfo itposinfo;
		itposinfo.Info = InventoryItemHandler::getInstance()->GetItemInfo(item);
		if(price >= 0)
			itposinfo.Info.BuyPrice = price;

		itposinfo.Count = 1;
		itposinfo.Position = -1;

		_items[item] = itposinfo;
	}
}


/***********************************************************
add item to container start
***********************************************************/
LbaNet::ItemInfo OpenShopAction::AddItemR(long item, int price)
{
	if(item >= 0)
	{
		LbaNet::ItemPosInfo itposinfo;
		itposinfo.Info = InventoryItemHandler::getInstance()->GetItemInfo(item);
		if(price >= 0)
			itposinfo.Info.BuyPrice = price;

		itposinfo.Count = 1;
		itposinfo.Position = -1;

		_items[item] = itposinfo;

		return itposinfo.Info;
	}

	return LbaNet::ItemInfo();
}


/***********************************************************
remove item to container start
***********************************************************/
void OpenShopAction::RemoveItem(long item)
{
	LbaNet::ItemsMap::iterator it = _items.find(item);
	if(it != _items.end())
		_items.erase(it);
}


/***********************************************************
get currency item
***********************************************************/
long OpenShopAction::GetCurrencyItem()
{
	return (long)_currencyitem.Id;
}

/***********************************************************
set currency item
***********************************************************/
void OpenShopAction::SetCurrencyItem(long it)
{
	_currencyitem = InventoryItemHandler::getInstance()->GetItemInfo(it);
}



/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void CutMapAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	long clientid = -1;

	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return;

	if(owner)
	{
		EventsSeq toplayer;
		toplayer.push_back(new CutMapEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), _Y));
		owner->SendEvents(clientid, toplayer);
	}
}


/***********************************************************
save action to lua file
***********************************************************/
void CutMapAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = CutMapAction()"<<std::endl;
	file<<"\t"<<name<<":SetY("<<_Y<<")"<<std::endl;
}




/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void OpenLetterWritterAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	long clientid = -1;

	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return;


	if(owner)
	{
		EventsSeq toplayer;
		toplayer.push_back(
			new RefreshGameGUIEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(),
										"LetterEditorBox", GuiParamsSeq(), true, false));
		owner->SendEvents(clientid, toplayer);
	}
}


/***********************************************************
save action to lua file
***********************************************************/
void OpenLetterWritterAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = OpenLetterWritterAction()"<<std::endl;
}


/***********************************************************
//! execute the action
//! parameter return the object type and number triggering the action
***********************************************************/
void OpenMailboxAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
								ActionArgumentBase* args)
{
	long clientid = -1;

	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3)
	{
		if(owner)
			clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
	}

	// check if client found - else return
	if(clientid < 0)
		return;


	//send to client
	if(owner)
		owner->OpenMailbox(clientid);
}


/***********************************************************
save action to lua file
***********************************************************/
void OpenMailboxAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = OpenMailboxAction()"<<std::endl;
}




/***********************************************************
execute the action
***********************************************************/
void PlaySoundAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
										ActionArgumentBase* args)
{
	long clientid = -2;
	if(!_toeveryone)
	{
		if(ObjectType == 2)
			clientid = (long)ObjectId;

		// on object moved by player
		if(ObjectType == 3)
		{
			if(owner)
				clientid = owner->GetGhostOwnerPlayer((long)ObjectId);
		}

		// check if client found - else return
		if(clientid < 0)
			return;
	}


	if(owner && _soundpath != "")
	{
		LbaNet::SoundInfo sinfo;
		sinfo.SoundPath = _soundpath;

		EventsSeq toplayer;
		toplayer.push_back(
			new PlaySoundEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), sinfo));
		owner->SendEvents(clientid, toplayer);
	}
}


/***********************************************************
save action to lua file
***********************************************************/
void PlaySoundAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = PlaySoundAction()"<<std::endl;
	file<<"\t"<<name<<":SetToEveryone("<<(_toeveryone?"true":"false")<<")"<<std::endl;
	if(_soundpath != "")
		file<<"\t"<<name<<":SetSoundPath(\""<<_soundpath<<"\")"<<std::endl;
}




/***********************************************************
execute the action
***********************************************************/
void SetFlagAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
										ActionArgumentBase* args)
{
	long clientid = -2;
	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3 && owner)
		clientid = owner->GetGhostOwnerPlayer((long)ObjectId);

	// check if client found - else return
	if(clientid < 0)
		return;


	if(owner && _flag != "")
		owner->SetDBFlag(clientid, _flag, _value);
}


/***********************************************************
save action to lua file
***********************************************************/
void SetFlagAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = SetFlagAction()"<<std::endl;
	file<<"\t"<<name<<":SetValue("<<_value<<")"<<std::endl;
	if(_flag != "")
		file<<"\t"<<name<<":SetFlagName(\""<<_flag<<"\")"<<std::endl;
}


/***********************************************************
execute the action
***********************************************************/
void ShoutTextAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
										ActionArgumentBase* args)
{
	if(owner && _textid >= 0)
	{
		LbaNet::ShoutTextInfo sinfo;
		sinfo.TextId = _textid;
		sinfo.TextSize = _textsize;
		sinfo.TextcolorR = _textcolorR;
		sinfo.TextcolorG = _textcolorG;
		sinfo.TextcolorB = _textcolorB;

		sinfo.ObjectType = ObjectType;
		sinfo.ObjectId = ObjectId;

		EventsSeq toplayer;
		toplayer.push_back(
			new DisplayShoutEvent(SynchronizedTimeHandler::GetCurrentTimeDouble(), sinfo));
		owner->SendEvents(-2, toplayer);
	}
}


/***********************************************************
save action to lua file
***********************************************************/
void ShoutTextAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = ShoutTextAction()"<<std::endl;
	file<<"\t"<<name<<":SetTextId("<<_textid<<")"<<std::endl;
	file<<"\t"<<name<<":SetTextSize("<<_textsize<<")"<<std::endl;
	file<<"\t"<<name<<":SetColorR("<<_textcolorR<<")"<<std::endl;
	file<<"\t"<<name<<":SetColorG("<<_textcolorG<<")"<<std::endl;
	file<<"\t"<<name<<":SetColorB("<<_textcolorB<<")"<<std::endl;	
}



/***********************************************************
execute the action
***********************************************************/
void PlayVideoAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
										ActionArgumentBase* args)
{
	long clientid = -1;
	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3 && owner)
		clientid = owner->GetGhostOwnerPlayer((long)ObjectId);

	// check if client found - else return
	if(clientid < 0)
		return;

	if(owner && _videopath != "")
		owner->PlayClientVideo(clientid, _videopath);
}


/***********************************************************
save action to lua file
***********************************************************/
void PlayVideoAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = PlayVideoAction()"<<std::endl;
	if(_videopath != "")
		file<<"\t"<<name<<":SetVideoPath(\""<<_videopath<<"\")"<<std::endl;
}




/***********************************************************
	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
***********************************************************/
void RandomAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
							ActionArgumentBase* args)
{
	int rnd = Randomizer::getInstance()->RandInt(_actions.size()-1);
	_actions[rnd]->Execute(owner, ObjectType, ObjectId, args);
}



/***********************************************************
save action to lua file
***********************************************************/
void RandomAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = RandomAction()"<<std::endl;
	for(size_t i=0; i< _actions.size(); ++i)
	{
		std::stringstream aname;
		aname<<name<<"_act"<<i;
		_actions[i]->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name<<":AddAction("<<aname.str()<<")"<<std::endl;
	}
}



/***********************************************************
add action
***********************************************************/
void RandomAction::AddAction(ActionBasePtr action)
{
	_actions.push_back(action);
}

/***********************************************************
remove action
***********************************************************/
void RandomAction::RemoveAction(ActionBasePtr action)
{
	std::vector<ActionBasePtr>::iterator it = std::find(_actions.begin(), _actions.end(), action);
	if(it != _actions.end())
		_actions.erase(it);
}


/***********************************************************
replace old action by new one
***********************************************************/
void RandomAction::ReplaceAction(ActionBasePtr olda, ActionBasePtr newa)
{
	std::vector<ActionBasePtr>::iterator it = std::find(_actions.begin(), _actions.end(), olda);
	if(it != _actions.end())
		*it = newa;
}




/***********************************************************
	//! execute the action
	//! parameter return the object type and number triggering the action
	// ObjectType ==>
	//! 1 -> npc object
	//! 2 -> player object
	//! 3 -> movable object
***********************************************************/
void DisplayHolomapAction::Execute(ScriptEnvironmentBase * owner, int ObjectType, Ice::Long ObjectId,
										ActionArgumentBase* args)
{
	long clientid = -1;
	if(ObjectType == 2)
		clientid = (long)ObjectId;

	// on object moved by player
	if(ObjectType == 3 && owner)
		clientid = owner->GetGhostOwnerPlayer((long)ObjectId);

	// check if client found - else return
	if(clientid < 0)
		return;

	if(owner)
		owner->DisplayHolomap(-1, clientid, _Mode, _HolomapId);
}


/***********************************************************
save action to lua file
***********************************************************/
void DisplayHolomapAction::SaveToLuaFile(std::ostream & file, const std::string & name)
{
	file<<"\t"<<name<<" = DisplayHolomapAction()"<<std::endl;
	file<<"\t"<<name<<":SetMode("<<_Mode<<")"<<std::endl;
	file<<"\t"<<name<<":SetHolomapId("<<_HolomapId<<")"<<std::endl;
}
