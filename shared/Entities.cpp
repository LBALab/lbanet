/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2005
-------------------------------[ HQRLib.cpp ]--------------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Mon Sep 19 2005
Email : alexandrefontoura@oninetspeed.pt

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
#include <fstream>
#include <iostream>
#ifdef _WIN32
	#include <io.h>
#else
	#include <stdio.h>
	#include <stdlib.h>
#endif

#include <fcntl.h>
#pragma hdrstop

#include "Entities.h"





entitiesTableStruct* parseEntities(std::string entitiesPath)
{
	int numOfEntities;
	int i;
	entitiesTableStruct* entitiesData;
	unsigned char* currentEntity;
	unsigned char* currentPtr;
	unsigned char* backupPtr;

	numOfEntities=getNumEntries(entitiesPath.c_str());

	entitiesData=(entitiesTableStruct*)malloc((sizeof(entitiesTableStruct)));

	entitiesData->numOfEntities=numOfEntities;
	entitiesData->entitiesTable=(entitiesTableEntry*)malloc(sizeof(entitiesTableEntry)*numOfEntities);

	for(i=0;i<numOfEntities;i++)
	{
		entitiesData->entitiesTable[i].numOfBody=0;
		entitiesData->entitiesTable[i].numOfAnims=0;

		loadResource(entitiesPath.c_str(), i, &currentEntity);

		currentPtr=currentEntity;

		while(*currentPtr!=255)
		{
			backupPtr=currentPtr+2;

			switch(*currentPtr)
			{
			case 1: // body
				{
					char body;
					short int realIndex;

					body=*(currentPtr+1);
					realIndex=*(short int*)(currentPtr+3);

					if(realIndex & 0x8000)
					{
						printf("Error while parsing entities: realIndex | 0x8000 !\n");
						exit(1);
					}

					entitiesData->entitiesTable[i].bodyList[entitiesData->entitiesTable[i].numOfBody].body=body;
					entitiesData->entitiesTable[i].bodyList[entitiesData->entitiesTable[i].numOfBody].index=realIndex;

					if((*(currentPtr+5)) && *(currentPtr+6)==14)
					{
						short int* ptr=(short int*)(currentPtr+7);

						entitiesData->entitiesTable[i].bodyList[entitiesData->entitiesTable[i].numOfBody].useColBox=1;
						
						entitiesData->entitiesTable[i].bodyList[entitiesData->entitiesTable[i].numOfBody].X1 = *(ptr++); //X1
						entitiesData->entitiesTable[i].bodyList[entitiesData->entitiesTable[i].numOfBody].Z1 = *(ptr++); //Z1
						entitiesData->entitiesTable[i].bodyList[entitiesData->entitiesTable[i].numOfBody].Y1 = *(ptr++); //Y1
						entitiesData->entitiesTable[i].bodyList[entitiesData->entitiesTable[i].numOfBody].X2 = *(ptr++); //X2
						entitiesData->entitiesTable[i].bodyList[entitiesData->entitiesTable[i].numOfBody].Z2 = *(ptr++); //Z2
						entitiesData->entitiesTable[i].bodyList[entitiesData->entitiesTable[i].numOfBody].Y2 = *(ptr++); //Y2					
					}
					else
					{
						entitiesData->entitiesTable[i].bodyList[entitiesData->entitiesTable[i].numOfBody].useColBox=0;
					}

					entitiesData->entitiesTable[i].numOfBody++;

					break;
				}
			case 3: // anim
				{
					int anim;
					int realIndex;

					anim=*(currentPtr+1);
					realIndex=*(short int*)(currentPtr+3);

					entitiesData->entitiesTable[i].animList[entitiesData->entitiesTable[i].numOfAnims].anim=anim;
					entitiesData->entitiesTable[i].animList[entitiesData->entitiesTable[i].numOfAnims].index=realIndex;

					entitiesData->entitiesTable[i].numOfAnims++;

					break;
				}
			default:
				{
					printf("Unsupported entry %d in parseEntities!\n",*currentPtr);
					exit(1);
					break;
				}
			}

			currentPtr=*(unsigned char*)backupPtr+backupPtr;		
		}
		free(currentEntity);
	}

	return(entitiesData);
}