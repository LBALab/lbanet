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

#include "InventoryItemHandler.h"
#include "XmlReader.h"
#include <fstream>

InventoryItemHandler* InventoryItemHandler::_singletonInstance = NULL;




/***********************************************************
AddContainedItem
***********************************************************/
void InventoryItemDef::AddContainedItem(long id, int min, int max, float proba, int group)
{
	LbaNet::ItemGroupElement elem;
    elem.Id = id;
    elem.Min = min;
    elem.Max = max;
    elem.Probability = proba;
    elem.Group = group;
	_info.List.push_back(elem);
}


/***********************************************************
save quest to lua file
***********************************************************/
void InventoryItemDef::SaveToLuaFile(std::ofstream & file) const
{
	std::stringstream name;
	name<<"Item_"<<GetId();
	file<<"\t"<<name.str()<<" = InventoryItemDef("<<GetId()<<")"<<std::endl;

	file<<"\t"<<name.str()<<":SetName(\""<<_info.Name<<"\")"<<std::endl;
	file<<"\t"<<name.str()<<":SetIconName(\""<<_info.IconName<<"\")"<<std::endl;
	file<<"\t"<<name.str()<<":SetNameTextId("<<_info.NameTextId<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetDescriptionId("<<_info.DescriptionId<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetLongDescriptionId("<<_info.LongDescriptionId<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetMax("<<_info.Max<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetBuyPrice("<<_info.BuyPrice<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetSellPrice("<<_info.SellPrice<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetDescriptionTextExtra(\""<<_info.DescriptionTextExtra<<"\")"<<std::endl;
	file<<"\t"<<name.str()<<":SetType("<<_info.Type<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetEffect("<<_info.Effect<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetEffect2("<<_info.Effect2<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetFlag("<<_info.Flag<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetEphemere("<<(_info.Ephemere?"true":"false")<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetStringFlag(\""<<_info.StringFlag<<"\")"<<std::endl;
	file<<"\t"<<name.str()<<":SetColor1("<<_info.Color1<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetColor2("<<_info.Color2<<")"<<std::endl;
	file<<"\t"<<name.str()<<":SetReplacedItem("<<_info.ReplaceItem<<")"<<std::endl;

	int rtype = GetRenderType();
	if(rtype > 0)
	{
		file<<"\t"<<name.str()<<":SetRenderType("<<rtype<<")"<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.ModelId = "<<_displayinfo.ModelId<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.ModelName = \""<<_displayinfo.ModelName<<"\""<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.Outfit = \""<<_displayinfo.Outfit<<"\""<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.Weapon = \""<<_displayinfo.Weapon<<"\""<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.Mode = \""<<_displayinfo.Mode<<"\""<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.UseLight = "<<(_displayinfo.UseLight?"true":"false")<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.CastShadow = "<<(_displayinfo.CastShadow?"true":"false")<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.ColorR = "<<_displayinfo.ColorR<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.ColorG = "<<_displayinfo.ColorG<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.ColorB = "<<_displayinfo.ColorB<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.ColorA = "<<_displayinfo.ColorA<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.TransX = "<<_displayinfo.TransX<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.TransY = "<<_displayinfo.TransY<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.TransZ = "<<_displayinfo.TransZ<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.ScaleX = "<<_displayinfo.ScaleX<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.ScaleY = "<<_displayinfo.ScaleY<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.ScaleZ = "<<_displayinfo.ScaleZ<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.RotX = "<<_displayinfo.RotX<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.RotY = "<<_displayinfo.RotY<<std::endl;
		file<<"\t"<<name.str()<<".DisplayDesc.RotZ = "<<_displayinfo.RotZ<<std::endl;
	}

	if(_action)
	{
		std::stringstream aname;
		aname<<name.str()<<"_act";
		_action->SaveToLuaFile(file, aname.str());

		file<<"\t"<<name.str()<<":SetAction("<<aname.str()<<")"<<std::endl;
	}

	for(size_t i=0; i< _info.List.size(); ++i)
	{
		file<<"\t"<<name.str()<<":AddContainedItem("
			<<_info.List[i].Id<<", "
			<<_info.List[i].Min<<", "
			<<_info.List[i].Max<<", "
			<<_info.List[i].Probability<<", "
			<<_info.List[i].Group<<")"<<std::endl;
	}

	file<<"\tenvironment:AddInventoryItem("<<name.str()<<")"<<std::endl<<std::endl;
}




/***********************************************************
	// set enum for render type as lua does not map enum
	//1 - RenderOsgModel
	//2 - RenderSprite
	//3 - RenderLba1M
	//4 - RenderLba2M
***********************************************************/
void InventoryItemDef::SetRenderType(int rtype)
{
	switch(rtype)
	{
		case 0:
			_displayinfo.TypeRenderer = LbaNet::NoRender;
		break;
		case 1:
			_displayinfo.TypeRenderer = LbaNet::RenderOsgModel;
		break;
		case 2:
			_displayinfo.TypeRenderer = LbaNet::RenderSprite;
		break;
		case 3:
			_displayinfo.TypeRenderer = LbaNet::RenderLba1M;
		break;
		case 4:
			_displayinfo.TypeRenderer = LbaNet::RenderLba2M;
		break;
		case 5:
			_displayinfo.TypeRenderer = LbaNet::RenderCross;
		break;
		case 6:
			_displayinfo.TypeRenderer = LbaNet::RenderBox;
		break;
		case 7:
			_displayinfo.TypeRenderer = LbaNet::RenderCapsule;
		break;
	}
}


/***********************************************************
accessor
***********************************************************/
int InventoryItemDef::GetRenderType() const
{
	switch(_displayinfo.TypeRenderer)
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
singleton pattern
***********************************************************/
InventoryItemHandler * InventoryItemHandler::getInstance()
{
    if(!_singletonInstance)
    {
        _singletonInstance = new InventoryItemHandler();
		return _singletonInstance;
    }
    else
    {
		return _singletonInstance;
    }
}


/***********************************************************
Constructor
***********************************************************/
InventoryItemHandler::InventoryItemHandler()
{

}

/***********************************************************
Destructor
***********************************************************/
InventoryItemHandler::~InventoryItemHandler()
{

}


/***********************************************************
get item
***********************************************************/
InventoryItemDefPtr InventoryItemHandler::GetItem(long itemid)
{
	if(_items.find(itemid) != _items.end())
		return _items[itemid];

	return InventoryItemDefPtr();
}


/***********************************************************
get item info
***********************************************************/
LbaNet::ItemInfo InventoryItemHandler::GetItemInfo(long itemid)
{
	if(_items.find(itemid) != _items.end())
		return _items[itemid]->GetInfo();

	// in case not found
	LbaNet::ItemInfo res;
	res.Id = -1;
	return res;
}

 
/***********************************************************
get item action
***********************************************************/
ActionBasePtr InventoryItemHandler::GetItemAction(long itemid)
{
	if(_items.find(itemid) != _items.end())
		return _items[itemid]->GetAction();

	// in case not found
	return ActionBasePtr();
}


/***********************************************************
add/modify item
return item id in case of add
***********************************************************/
long InventoryItemHandler::AddOrModItem(long index, const LbaNet::ItemInfo &info)
{
	if(index < 0)
	{
		// add to map
		long res = _items.rbegin()->first + 1;
		_items[res] = InventoryItemDefPtr(new InventoryItemDef(info));
		_items[res]->SetId(res);
		return res;
	}
	else
	{
		_items[index] = InventoryItemDefPtr(new InventoryItemDef(info));
		return index;
	}
}


/***********************************************************
set item in iventory
***********************************************************/
void InventoryItemHandler::SetItem(InventoryItemDefPtr item)
{
	_items[item->GetId()] = item;
}


/***********************************************************
remove item
***********************************************************/
void InventoryItemHandler::RemoveItem(long index)
{
	std::map<long, InventoryItemDefPtr>::iterator it = _items.find(index);
	if(it != _items.end())
		_items.erase(it);
}



/***********************************************************
get item info
***********************************************************/
std::string InventoryItemHandler::GetItemTypeString(long itemid)
{
	std::map<long, InventoryItemDefPtr>::iterator it = _items.find(itemid);
	if(it != _items.end())
	{
		switch(it->second->GetType())
		{
			case 1:
				return "Consumable";
			case 2:
				return "Key";
			case 3:
				return "Mount";
			case 4:
				return "Weapon";
			case 5:
				return "Quest";
			case 6:
				return "Other";
			case 7:
				return "Actionable";
			case 8:
				return "Letter";
			case 9:
				return "Outfit";
			case 10:
				return "Container";
		}
	}

	return "";
}


/***********************************************************
add item
***********************************************************/
void InventoryItemHandler::AddItem(InventoryItemDefPtr item)
{
	_items[item->GetId()] = item;
}
