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

#include "StreamReader.h"
#include <cstring>


/***********************************************************
	Constructor
***********************************************************/
StreamReader::StreamReader(const char* fileName)
{
	m_isOpen = open(fileName);
}

/***********************************************************
	Destructor
***********************************************************/
StreamReader::~StreamReader()
{
	if(m_isOpen)
		close();
}


/***********************************************************
	void StreamReader::get(void* destPtr, unsigned long size)
***********************************************************/
void StreamReader::get(void* destPtr, unsigned long size)
{
	if(!m_isOpen)
		return;

	if( (SR_BUFFER_SIZE - m_positionInBuffer) >= size)
	{
		memcpy(destPtr,&m_buffer[m_positionInBuffer],size);
		m_positionInBuffer += size;
	}
	else
	{
		// buffer isn't filled enough...
		char* tempPtr = (char*)destPtr;

		// feed what we can:
		unsigned long tmpsize = (SR_BUFFER_SIZE - m_positionInBuffer);
		memcpy( tempPtr, &m_buffer[m_positionInBuffer], tmpsize );
		tempPtr += tmpsize;
		size -= tmpsize;

		// feed the rest
		do
		{
			m_currentSector++;
			feedBuffer();

			if(size >= SR_BUFFER_SIZE)
			{
			memcpy(tempPtr, m_buffer, SR_BUFFER_SIZE);
			tempPtr += SR_BUFFER_SIZE;
			size -= SR_BUFFER_SIZE;
			}
			else
			{
			memcpy(tempPtr, m_buffer, size);
			m_positionInBuffer += size;
			size=0;
			}
		}
		while(size>0);
	}
}

/***********************************************************
	void StreamReader::seek(unsigned long seekPosition)
***********************************************************/
void StreamReader::seek(unsigned long seekPosition)
{
	if(!m_isOpen)
		return;

	unsigned long sectorToSeek = seekPosition / 2048;

	fseek(m_fileHandle, sectorToSeek * 2048, SEEK_SET );

	m_currentSector = sectorToSeek;

	feedBuffer();

	m_positionInBuffer = (seekPosition - (sectorToSeek*2048));
}

/***********************************************************
	bool StreamReader::open(const char* fileName, int fatal)
***********************************************************/
bool StreamReader::open(const char* fileName)
{
	m_fileHandle = fopen((const char*)fileName,"rb");

	if(m_fileHandle)
	{
		m_currentSector = 0;
		feedBuffer();
		return true;
	}
	else
	{
		return false;
	}
}

/***********************************************************
	void StreamReader::close()
***********************************************************/
void StreamReader::close()
{
	if(m_fileHandle != NULL)
		fclose( m_fileHandle );
}

/***********************************************************
	void StreamReader::feedBuffer()
***********************************************************/
void StreamReader::feedBuffer()
{
	if(m_fileHandle != NULL)
	{
		fread(m_buffer, SR_BUFFER_SIZE, 1, m_fileHandle);
		m_positionInBuffer = 0;
	}
}
