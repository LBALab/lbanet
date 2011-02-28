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


#ifndef __LBA_NET_MAP_WORLD_INFO_H__
#define __LBA_NET_MAP_WORLD_INFO_H__

#include <string>
#include <map>
#include <vector>


// contain information about a spawning point
struct SpawningInfo
{
	long			Id;

	// name
	std::string		Name;

	// position
	float			PosX;
	float			PosY;
	float			PosZ;

	// rotation at arrival in degree
	int				Rotation;
};


// contain information about a exit area
struct ExitInfo
{
	// name
	std::string		Name;

	// top left corner
	float			TopRightX;
	float			TopRightY;
	float			TopRightZ;

	// bottom right corner
	float			BottomLeftX;
	float			BottomLeftY;
	float			BottomLeftZ;

	// arrival point of the exit
	std::string		NewMap;
	std::string		Spawning;
};


// contain information about a teleport place
struct TPInfo
{
	// name
	std::string		Name;

	// arrival point
	std::string		NewMap;
	std::string		Spawning;
};

// contains information about an LBA map
struct MapInfo
{
	// map name
	std::string		Name;

	// map type: e.g interior/exterior
	std::string		Type;

	// map description
	std::string		Description;

	// path to the music file to be played
	std::string		Music;

	// number of time the music should be played
	int				MusicLoop;

	// files to be loaded
	std::map<std::string, std::string>	Files;


	// spawning points
	std::map<std::string, SpawningInfo>	Spawnings;

	// exit points
	std::map<std::string, ExitInfo>	Exits;

};

// contains information about an LBA world
struct WorldInfo
{
	// world name
	std::string		Name;

	// map description
	std::string		Description;

	// map used at arrival in the world
	std::string		FirstMap;

	// spawn area used at arrival in the world
	std::string		FirstSpawning;

	// description of the maps constituing the world
	std::map<std::string, MapInfo>	Maps;

	// teleport places
	std::map<std::string, TPInfo>	Teleports;

};



#endif
