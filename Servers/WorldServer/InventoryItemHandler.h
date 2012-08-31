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
#include "ProjectileObjectDef.h"

/***********************************
*	InventoryItemDef
*************************************/
class InventoryItemDef
{
public:

	//! constructor
	InventoryItemDef(long id)
		: _actionDestroy(false)
	{
		_info.Id = id;
		_info.ReplaceItem = -1;
		_info.Effect2 = 0;

		_displayinfo.TypeRenderer = LbaNet::NoRender;
		_displayinfo.ModelId = 0;

		_displayinfo.RotX = 0;
		_displayinfo.RotY = 0;
		_displayinfo.RotZ = 0;

		_displayinfo.TransX = 0;
		_displayinfo.TransY = 0;
		_displayinfo.TransZ = 0;

		_displayinfo.ScaleX = 1;
		_displayinfo.ScaleY = 1;
		_displayinfo.ScaleZ = 1;	

		_displayinfo.ColorR = 0;
		_displayinfo.ColorG = 0;
		_displayinfo.ColorB = 0;
		_displayinfo.ColorA = 0;


		_displayinfo.UseBillboard = false;

		_displayinfo.UseTransparentMaterial = false;
		_displayinfo.MatAlpha = 1;
			
		_displayinfo.ColorMaterialType = 0;
		_displayinfo.MatAmbientColorR = 0.2f;
		_displayinfo.MatAmbientColorG = 0.2f;
		_displayinfo.MatAmbientColorB = 0.2f;
		_displayinfo.MatAmbientColorA = 1;			
		_displayinfo.MatDiffuseColorR = 0.8f;
		_displayinfo.MatDiffuseColorG = 0.8f;
		_displayinfo.MatDiffuseColorB = 0.8f;
		_displayinfo.MatDiffuseColorA = 1;
		_displayinfo.MatSpecularColorR = 0;
		_displayinfo.MatSpecularColorG = 0;
		_displayinfo.MatSpecularColorB = 0;
		_displayinfo.MatSpecularColorA = 1;	
		_displayinfo.MatEmissionColorR = 0;
		_displayinfo.MatEmissionColorG = 0;
		_displayinfo.MatEmissionColorB = 0;
		_displayinfo.MatEmissionColorA = 1;
		_displayinfo.MatShininess = 0;
	}

	//! constructor
	InventoryItemDef(const LbaNet::ItemInfo &info)
		: _info(info), _actionDestroy(false)
	{
		_displayinfo.TypeRenderer = LbaNet::NoRender;
		_displayinfo.ModelId = 0;

		_displayinfo.RotX = 0;
		_displayinfo.RotY = 0;
		_displayinfo.RotZ = 0;

		_displayinfo.TransX = 0;
		_displayinfo.TransY = 0;
		_displayinfo.TransZ = 0;

		_displayinfo.ScaleX = 1;
		_displayinfo.ScaleY = 1;
		_displayinfo.ScaleZ = 1;	

		_displayinfo.ColorR = 0;
		_displayinfo.ColorG = 0;
		_displayinfo.ColorB = 0;
		_displayinfo.ColorA = 0;
	}

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
    float GetEffect2() const{return _info.Effect2;}
    int GetFlag() const{return _info.Flag;}
    bool GetEphemere() const{return _info.Ephemere;}
    std::string GetStringFlag() const{return _info.StringFlag;}
    int GetColor1() const{return _info.Color1;}
    int GetColor2() const{return _info.Color2;}
	long GetReplacedItem() const{return (long)_info.ReplaceItem;}
	ActionBasePtr GetAction() const{return _action;}
	bool ActionDestroy(){return _actionDestroy;}

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
    void SetEffect2(float v){_info.Effect2 = v;}
    void SetFlag(int v){_info.Flag = v;}
    void SetEphemere(bool v){_info.Ephemere = v;}
    void SetStringFlag(const std::string & v){_info.StringFlag = v;}
    void SetColor1(int v){_info.Color1 = v;}
    void SetColor2(int v){_info.Color2 = v;}
	void SetReplacedItem(long v) {_info.ReplaceItem = v;}
	void SetAction(ActionBasePtr v) {_action = v;}
	void SetActionDestroy(bool v){_actionDestroy = v;}

	void AddContainedItem(long id, int min, int max, float proba, int group);

	LbaNet::ContainedItemList &GetContainedItemList()
	{return _info.List;}


	// save item to lua file
	void SaveToLuaFile(std::ostream & file) const;


	// add projectile
	void AddProjectile(ProjectileObjectDefPtr proj)
	{_projectiles.push_back(proj);}

	//! get projectiles
	std::vector<ProjectileObjectDefPtr> & GetProjectiles()
	{return _projectiles;}

	// remove projectile
	void RemoveProjectile(ProjectileObjectDefPtr proj);



	//! get display info
	void SetDisplayInfo(const LbaNet::ModelInfo & ainfo)
	{_displayinfo = ainfo;}

	//! set display info
	LbaNet::ModelInfo &GetDisplayInfo()
	{ return _displayinfo;}

	// set enum for render type as lua does not map enum
	//1 - RenderOsgModel
	//2 - RenderSprite
	//3 - RenderLba1M
	//4 - RenderLba2M
	void SetRenderType(int rtype);

	// accessor
	int GetRenderType() const;

	// public for LUA
	LbaNet::ModelInfo		_displayinfo;

private:
	LbaNet::ItemInfo		_info;

	bool					_hasdisplayinfo;

	ActionBasePtr			_action;
	bool					_actionDestroy;
	
	std::vector<ProjectileObjectDefPtr>	_projectiles;
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

	bool ActionDestroyItem(long itemid);

private:

	// singleton
	static InventoryItemHandler *		_singletonInstance;

	// item list
	std::map<long, InventoryItemDefPtr>			_items;
};


#endif
