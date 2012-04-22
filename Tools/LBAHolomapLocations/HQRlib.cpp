/*
------------------------[ LBA Screen Viewer Source ]-------------------------
Copyright (C) 2004
-------------------------------[ HQRLib.cpp ]--------------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Fri Aug 21 2004
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


#include <io.h>
#include <fcntl.h>
#pragma hdrstop

#include "HQRlib.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------

int checkResource(char *fileName)
{
   FILE *fileHandle;

   fileHandle = fopen(fileName, "r+b");

   if (fileHandle)
	{
       fclose(fileHandle);
       return(1);
	}

   return (0);
}
//---------------------------------------------------------------------------

FILE* openResource(char* fileName)
{
   FILE *fileHandle;

   if (!fileName)
	    return (NULL);

   fileHandle = fopen(fileName, "r+b");

   return (fileHandle);
}
//---------------------------------------------------------------------------

FILE* openResourceAs(char* fileName)
{
   FILE *fileHandle;

   if (!fileName)
	    return (NULL);

   fileHandle = fopen(fileName, "w+b");


   return (fileHandle);
}
//---------------------------------------------------------------------------

int readResource(FILE* resourceFile,char* ptr, int length)
{
	if(!resourceFile)
		return(1);

	fread((char*)ptr,length,1,resourceFile);

	return(0);
}
//---------------------------------------------------------------------------

int ResourceSize(char* fileName)
{
   int handle,size;
   handle = open(fileName, O_RDONLY  );
   size = filelength(handle);
   close(handle);
	return size;
}
//---------------------------------------------------------------------------

void saveResource(FILE* resourceFile, unsigned char* ptr, int length)
{
   fseek(resourceFile, SEEK_SET, 0);
   fwrite(ptr,length,1,resourceFile);
}
//---------------------------------------------------------------------------

void closeResource(FILE* resourceFile)
{
	fclose(resourceFile);
}
//---------------------------------------------------------------------------
/*
int loadResource(char *fileName, short int arg_4, byte** ptr)
{
	FILE* resourceFile;
	int headerSize;
	int offToData;
	int dataSize;
	int compressedSize;
	short int mode;
	unsigned char *temp;

	resourceFile=openResource(fileName);

	if(!resourceFile)
		return (-1);

	readResource(resourceFile,(char*)&headerSize,4);

	if(arg_4>=headerSize/4)
	{
		closeResource(resourceFile);
		return (-1);
	}

	fseek(resourceFile,arg_4*4,SEEK_SET);
	readResource(resourceFile,(char*)&offToData,4);

	fseek(resourceFile,offToData,SEEK_SET);
	readResource(resourceFile,(char*)&dataSize,4);
	readResource(resourceFile,(char*)&compressedSize,4);
	readResource(resourceFile,(char*)&mode,2);

	*ptr=(unsigned char*)malloc(dataSize);

	if(!(*ptr))
		return (-1);

	if(mode<=0) // uncompressed
	{
		readResource(resourceFile,(char*)*ptr,dataSize);
	}
	else // compressed: both modes (1 & 2)
	{
		temp=(unsigned char*)malloc(compressedSize);
   	readResource(resourceFile,(char*)temp,compressedSize);
		decompResource(dataSize,*ptr,temp,(Byte)mode);
		free(temp);
   }

   closeResource(resourceFile);
   return dataSize;
}
//---------------------------------------------------------------------------

void decompResource(int decompressedSize, unsigned char* destination, unsigned char* source, Byte comp)
{
	byte loop;
	byte indic;
	unsigned char *jumpBack;
	int size;
	unsigned short int temp;
	int i;

	do{
		loop=8;
		indic=*(source++);
		do{
			if(!(indic&1))
			{
				temp=*(unsigned short int*)(source);
				source+=2;
				size=temp&0x0F;
				size+=comp+1;
				decompressedSize-=size;
				jumpBack=destination-(temp>>4)-1;
				for(i=0;i<size;i++)
				{
					*(destination++)=*(jumpBack++);
				}
				if(decompressedSize<=0)
					return;
				loop--;
			}
			else
			{
				*(destination++)=*(source++);
				loop--;
				decompressedSize--;
				if(decompressedSize<=0)
					return;
			}
			indic>>=1;
		}while(loop);
	}while(decompressedSize);
	return;
}
//---------------------------------------------------------------------------

void getLine(char* fileName, char* buffer, int sceneNumber)
{
   FILE* fileHandle;
   fileHandle = fopen(fileName,"r");
   free(buffer);
   for(int i=0; i < sceneNumber; i++)
   {
       fgets(buffer,256,fileHandle);
   }
   fgets(buffer,256,fileHandle);
   *strchr(buffer,0xA) = 0;
   fclose(fileHandle);
}
//----------------------------------------------------------------------------

TColor getColor(int tmp, FILE * resourceFile){   // read RGB color
   Byte b;
   Byte r,g,b2;
   TColor c;
   fseek(resourceFile, tmp, 0);
   fread(&b, 1, 1, resourceFile);
   r = b;
   fread(&b, 1, 1, resourceFile);
   g = b;
   fread(&b, 1, 1, resourceFile);
   b2 = b;

   c = b2 * 256 * 256;
   c += g * 256;
   c += r;

   return c;
}
//----------------------------------------------------------------------------

int getNumEntries(char* fileName){
   FILE* fileHandle;
   unsigned short entries;
   fileHandle = fopen(fileName,"rb");
   fread((char*)&entries,2,1,fileHandle);
   fclose(fileHandle);
   return ((entries/4)-1);
}    */
//----------------------------------------------------------------------------
