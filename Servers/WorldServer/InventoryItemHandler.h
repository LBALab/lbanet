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

#ifndef _LBA_NET_INV_ITEM_HANDLER_H_
#define _LBA_NET_INV_ITEM_HANDLER_H_

#include <map>
#include <string>
#include <LbaTypes.h>
#include <boost/shared_ptr.hpp>

#include "Actions.h"

/***********************************
*	InventoryItemDef
*************************************/
class InventoryItemDef
{
public:

	//! constructor
	InventoryItemDef(long id)
	{
		_info.Id = id;
		_info.ReplaceItem = -1;
	}

	//! constructor
	InventoryItemDef(const LbaNet::ItemInfo &info)
		: _info(info)
	{}

	//! get info
	LbaNet::ItemInfo GetInfo()
	{return _info;}

	//! set info
	void SetInfo(const LbaNet::ItemInfo & info)
	{_info = info;}


	//! accessors
	long GetId() const{return (long)_info.Id;}
    std::string GetName() const{return _info.Name;}
    std::string GetIconName() const{return _info.IconName;}
    long GetNameTextId() const{return (long)_info.NameTextId;}
    long GetDescriptionId() const{return (long)_info.DescriptionId;}
    long GetLongDescriptionId() const{return (long)_info.LongDescriptionId;}
    int GetMax() const{return _info.Max;}
    int GetBuyPrice() const{return _info.BuyPrice;}
    int GetSellPrice() const{return _info.SellPrice;}
    std::string GetDescriptionTextExtra() const{return _info.DescriptionTextExtra;}
    int GetType() const{return _info.Type;}
    float GetEffect() const{return _info.Effect;}
    int GetFlag() const{return _info.Flag;}
    bool GetEphemere() const{return _info.Ephemere;}
    std::string GetStringFlag() const{return _info.StringFlag;}
    int GetColor1() const{return _info.Color1;}
    int GetColor2() const{return _info.Color2;}
	long GetReplacedItem() const{return (long)_info.ReplaceItem;}
	ActionBasePtr GetAction() const{return _action;}

	//! accessors
	void SetId(long v){_info.Id = v;}
    void SetName(const std::string & v){_info.Name = v;}
    void SetIconName(const std::string & v){_info.IconName = v;}
    void SetNameTextId(long v){_info.NameTextId = v;}
    void SetDescriptionId(long v){_info.DescriptionId = v;}
    void SetLongDescriptionId(long v){_info.LongDescriptionId = v;}
    void SetMax(int v){_info.Max = v;}
    void SetBuyPrice(int v){_info.BuyPrice = v;}
    void SetSellPrice(int v){_info.SellPrice = v;}
    void SetDescriptionTextExtra(const std::string & v){_info.DescriptionTextExtra = v;}
    void SetType(int v){_info.Type = v;}
    void SetEffect(float v){_info.Effect = v;}
    void SetFlag(int v){_info.Flag = v;}
    void SetEphemere(bool v){_info.Ephemere = v;}
    void SetStringFlag(const std::string & v){_info.StringFlag = v;}
    void SetColor1(int v){_info.Color1 = v;}
    void SetColor2(int v){_info.Color2 = v;}
	void SetReplacedItem(long v) {_info.ReplaceItem = v;}
	void SetAction(ActionBasePtr v) {_action = v;}


	void AddContainedItem(long id, int min, int max, float proba, int group);

	LbaNet::ContainedItemList &GetContainedItemList()
	{return _info.List;}


	// save item to lua file
	void SaveToLuaFile(std::ofstream & file) const;


private:
	LbaNet::ItemInfo _info;

	ActionBasePtr	_action;
};


typedef boost::shared_ptr<InventoryItemDef>	InventoryItemDefPtr;



/***********************************
*	class taking care of the log
*************************************/
class InventoryItemHandler
{
public:
	// constructor
	InventoryItemHandler();

	// destructor
	~InventoryItemHandler();

	// singleton pattern
	static InventoryItemHandler * getInstance();

	// get item
	InventoryItemDefPtr GetItem(long itemid);

	// get item info
	LbaNet::ItemInfo GetItemInfo(long itemid);

	// get item action
	ActionBasePtr GetItemAction(long itemid);

	//get item map
	const std::map<long, InventoryItemDefPtr> &GetItemMap()
	{ return _items;}

	// add/modify item
	// return item id in case of add
	long AddOrModItem(long index, const LbaNet::ItemInfo &info);

	//! set item in iventory
	void SetItem(InventoryItemDefPtr item);

	// remove item
	void RemoveItem(long index);

	// get item type
	std::string GetItemTypeString(long itemid);

	//! add item
	void AddItem(InventoryItemDefPtr item);

private:

	// singleton
	static InventoryItemHandler *		_singletonInstance;

	// item list
	std::map<long, InventoryItemDefPtr>			_items;
};


#endif
