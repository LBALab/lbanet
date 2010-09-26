/*
------------------------[ LBA Screen Viewer Source ]-------------------------
Copyright (C) 2004
--------------------------------[ HQRLib.h ]---------------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Fri Aug 21 2004
Email : alexandrefontoura@oninetspeed.pt

Info: some codes from yazor TwinEngine taken and modified by me

-------------------------------[ GNU License ]-------------------------------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

-----------------------------------------------------------------------------
*/

#ifndef EntitiesH
#define EntitiesH

#include "HQRlib.h"

struct bodyDataStruct
{
	char body;
	short int index;

	char useColBox;

	int X1;
	int X2;
	int Z1;
	int Z2;
	int Y1;
	int Y2;
};

struct animDataStruct
{
	int anim;
	int index;
};

struct entitiesTableEntry
{
	int numOfBody;
	int numOfAnims;
	bodyDataStruct bodyList[40];
	animDataStruct animList[40];
};

struct entitiesTableStruct
{
	int numOfEntities;
	entitiesTableEntry* entitiesTable;
};

entitiesTableStruct* parseEntities(std::string entitiesPath);
entitiesTableStruct* parseEntities2(void);

#endif