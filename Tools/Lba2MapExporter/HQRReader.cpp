#include "HQRReader.h"
#include <assert.h>

HQRReader::HQRReader(const std::string &fileName) : mBuffer(0)
{
	unsigned int uint32 = 0;

	mFileName = fileName;
	
	//Open specified file stream
	mFile.open(fileName.c_str(), ios::binary);
}

HQRReader::~HQRReader()
{	
	//Clean up the buffer
	if (mBuffer)
	{
		mBuffer = mBufferStart;
		delete[] mBuffer;
	}

	//Close the HQR file
	mFile.close();
}

int HQRReader::getSize()
{
	return mSize;
}

void HQRReader::LoadFile()
{
	//Clean up the buffer
	if (mBuffer)
	{
		mBuffer = mBufferStart;
		delete[] mBuffer;
	}

	//Copy the file into the buffer
	mFile.seekg(0, ios::end);
	ifstream::pos_type size = mFile.tellg();
    
	mBuffer = new char[size];
	mBufferStart = mBuffer;

    mFile.seekg(0, ios::beg);
    mFile.read(mBuffer, size);

	mSize = size;
}

void HQRReader::LoadEntry(int Entry)
{
	char cData[4];
	unsigned int Offset;
	unsigned int originalSize;
	unsigned int actualSize;
	short cType;	
	unsigned char uint8;
	std::vector<unsigned char> nData;	
	
	mFile.seekg((Entry - 1) * 4);
	mFile.read(cData, 4);		
	memcpy(&Offset, cData, 4);
	mFile.seekg(Offset);
	mFile.read(cData, 4);		
	memcpy(&originalSize, cData, 4);	
	mFile.read(cData, 4);		
	memcpy(&actualSize, cData, 4);
	mFile.read(cData, 2);		
	memcpy(&cType, cData, 2);
		
	//Clean up the buffer
	if (mBuffer)
	{
		mBuffer = mBufferStart;
		delete[] mBuffer;
	}

	//Create an internal buffer
	mBuffer = new char[originalSize];
	mSize = originalSize;	
	mBufferStart = mBuffer;
	
	//Copy the entry data into the temporary data vector
	for (unsigned int i = 0; i < actualSize; ++i)
	{
		mFile.read((char*)&uint8, 1);
		nData.push_back(uint8);
	}

	//If we have compression then decompress
	if (cType)
	{
		std::vector<unsigned char> tempBuffer;
		
		//Data is divided into blocks		
		int byteCount = 0;
		int bcount = 0;
		unsigned int aPos = 0;
		
		//Cycle through the blocks
		//loop until the tempBuffer is fill, duh o_o
		while ((aPos + 1) <= actualSize)		
		{		
			//Flag byte			
			unsigned char flagByte = nData[aPos];
		
			//Cycle through flag byte
			for (int i = 0; i < 8; ++i)
			{
				aPos++;
						
				//Check the bit
				if ((flagByte & (1 << i)) != 0)
				{
					tempBuffer.push_back(nData[aPos]);										
				}
				else
				{
					unsigned short e = nData[aPos]*256 + nData[aPos + 1];					
					int Length = ((e >> 8) & 0x000F) + cType + 1;					
					int Address = ((e << 4) & 0x0FF0) + ((e >> 12) & 0x00FF);

					//Loop through the length
					for (int g = 0; g < (int)Length; ++g)
					{
						tempBuffer.push_back((int)tempBuffer[tempBuffer.size() - Address - 1]);
					}

					aPos++;
				}
				
				if ((aPos + 1) >= actualSize) 
					break;				
			}

			aPos++;
		}
	
		//Make sure we fill the entrie buffer
		tempBuffer.resize(originalSize);

		//Copy the decompressed data to the internal buffer
		for (size_t iTB = 0; iTB < tempBuffer.size(); ++iTB)
		{
			mBuffer[iTB] = tempBuffer[iTB];
		}		
	}
	else
	{
		//Copy the uncompressed data to the internal buffer
		for (size_t iTB = 0; iTB < nData.size(); ++iTB)
		{
			mBuffer[iTB] = nData[iTB];
		}	
	}	
}

void HQRReader::Read(void *dest, size_t numBytes, bool Signed)
{	
	memcpy(dest, mBuffer, numBytes);		
	mBuffer += numBytes;
}

void HQRReader::Seek(int location)
{
	mBuffer = mBufferStart + location;
}

void HQRReader::SeekRelative(size_t location)
{
	mBuffer += location;
}

int HQRReader::getLocation()
{
	return mBuffer - mBufferStart;
}
