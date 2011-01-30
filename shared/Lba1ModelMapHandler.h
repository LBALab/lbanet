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

#ifndef _LBA_NET_LBA1MODEL_MAP_HANDLER_H_
#define _LBA_NET_LBA1MODEL_MAP_HANDLER_H_

#include <string>
#include <map>
#include <vector>


static std::string Lba1ModelDataPath = "Data/Worlds/Lba1Original/Models/";

struct ModelSize
{
	float X;
	float Y;
	float Z;
};

struct ModeData
{
	int modelnumber;
	int bodynumber;
	std::map<std::string, std::vector<int> > animations;
	ModelSize Size;
	int WeaponType;
};
struct WeaponData
{
	std::map<std::string, ModeData> modes;
};
struct OutfitData
{
	std::map<std::string, WeaponData> weapons;
};
struct ModelData
{
	std::map<std::string, OutfitData> outfits;
};


/***********************************
*	class taking of mapping between string and number for lba 1 models
*************************************/
class Lba1ModelMapHandler
{
public:
	// constructor
	Lba1ModelMapHandler();

	// destructor
    ~Lba1ModelMapHandler();

	// singleton pattern
	static Lba1ModelMapHandler * getInstance();

	// get model number and body number
	// return 0 if model correct
	// return -1 if model incorrect
	// todo - implement mutli animation sequence
	int GetModelInfo(	const std::string & modelname,
						const std::string & outfit,
						const std::string & weapon,
						const std::string & mode,
						const std::string & animation,
						int & resmodel,
						int & resbody,
						std::vector<int> & resanimation);


	// get model extra info
	// return 0 if model correct
	// return -1 if model incorrect
	int GetModelExtraInfo(	const std::string & modelname,
								const std::string & outfit,
								const std::string & weapon,
								const std::string & mode,
								int & resWeaponType,
								ModelSize & resSize);

	// get full map info
	std::map<std::string, ModelData> & GetData()
	{ return _data; }

private:
	// singleton
	static Lba1ModelMapHandler *	_singletonInstance;

	std::map<std::string, ModelData>	_data;
};


#endif
