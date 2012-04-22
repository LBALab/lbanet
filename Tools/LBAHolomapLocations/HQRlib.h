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

#ifndef HQRlibH
#define HQRlibH

#include <stdio.h>
#include <fstream>

//---------------------------------------------------------------------------
   /*
struct TPackEntry {
  long = Offset, CpSize, RlSize;
  short = Comp;
  int FType; // -3=hidden, -2=blank, -1=normal, >-1=repeated
  AnsiString Data;
};

DynamicArray<TPackEntry> TPackEntries;

struct OpOffsets{
  long D;
  int T;
};
      */

int checkResource(char *fileName);
FILE* openResource(char* fileName);
FILE* openResourceAs(char* fileName);
int readResource(FILE* resourceFile,char* ptr, int length);
void saveResource(FILE* resourceFile, unsigned char* ptr, int length);
void closeResource(FILE* resourceFile);
int ResourceSize(char* fileName);
/*int loadResource(char *fileName, short int arg_4, byte** ptr);
void decompResource(int decompressedSize, unsigned char* destination, unsigned char* source, Byte comp);
void getLine(char* fileName, char* buffer, int sceneNumber);
TColor getColor(int tmp, FILE * resourceFile);
int getNumEntries(char* fileName);  */

#endif
