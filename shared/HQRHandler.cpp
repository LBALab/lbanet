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

#include "HQRHandler.h"
#include "StreamReader.h"
#include "type.h"


/***********************************************************
	Constructor
***********************************************************/
HQRHandler::HQRHandler(const std::string & fileName)
: m_fileName(fileName)
{}


/***********************************************************
	Load a given element of the HQR file into a buffer
***********************************************************/
unsigned char * HQRHandler::Load_HQR(int imageNumber, unsigned int &dataSize)
{
	StreamReader SR(m_fileName.c_str());
	if(!SR.isOpen())
		return NULL;

	unsigned int headerSize;
	unsigned int offToImage;
	unsigned int compressedSize;
	unsigned short int mode;
	unsigned char * ptr;


	SR.get( &headerSize, 4 );
	if(imageNumber >= (int)headerSize /4)
	{
		return 0;
	}

	SR.seek( imageNumber * 4 );
	SR.get( &offToImage, 4 );

	SR.seek( offToImage );
	SR.get( &dataSize , 4 );

	SR.get( &compressedSize , 4 );

	SR.get( &mode , 2 );

	ptr = new unsigned char[dataSize+1000];

	if( mode <= 0 )
	{

		SR.get( ptr, dataSize );
	}
	else if( mode == 1 )
	{
		unsigned char* compressedDataPtr;

		compressedDataPtr = new unsigned char[compressedSize + 500];
		SR.get( compressedDataPtr, compressedSize);

		HQR_Expand(dataSize, ptr, compressedDataPtr);

		delete compressedDataPtr;
	}

	return ptr;
}

/***********************************************************
	Expand compressed data to normal buffer
***********************************************************/
void HQRHandler::HQR_Expand(int decompressedSize, unsigned char *destination, unsigned char *source)
{
	char loop;
	char indic;
	unsigned char *jumpBack;
	int size;
	unsigned short int temp;
	int i;

	do
	{
		loop = 8;
		indic = *(source++);
		do
		{
			if (!(indic & 1))
			{
				temp = (*(source+1))*256+*(source);
				source += 2;
				size = temp & 0x0F;
				size += 2;
				decompressedSize -= size;
				jumpBack = destination - (temp >> 4) - 1;
				for (i = 0; i < size; i++)
				{
					*(destination++) = *(jumpBack++);
				}

				if (decompressedSize <= 0)
					return;

				loop--;
			}
			else
			{
				*(destination++) = *(source++);
				loop--;
				decompressedSize--;

				if (decompressedSize <= 0)
					return;
			}
			indic >>= 1;
		}
		while (loop);
	}
	while (decompressedSize);
}



