/*
---------------------------------------------------------------
Little Big Adventure Online - HQR Reader
---------------------------------------------------------------
Notes:
		Thanks to Zink for his HQR file format documentation
---------------------------------------------------------------
*/

#ifndef HQRReader_H
#define HQRReader_H

#pragma once

#ifdef WIN32
#include "windows.h"
#endif

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class HQRReader
{
public:

	//Standard Constructor
	HQRReader(const std::string& fileName);
	//Standard Destructor
	~HQRReader();

	//Load an entry from an HQR file and use the internal buffer
	void LoadEntry(int Entry);
	//Trigger the specified HQR file to load as a binary file
	void LoadFile();

	//Set the read location of the buffer
	void Seek(int location);	
	//Set the read location of the buffer more than what it is now
	void SeekRelative(size_t location);	
	//Read at current location and increment the buffer
	void Read(void* dest, size_t numBytes, bool Signed = 0);
	//Get the current position in the buffer
	int getLocation();

	//Gets the size of the currently loaded entry
	int getSize();

private:

	//File stream object
	ifstream mFile; 
	//Name used to show the loaded HQR or binary file
	std::string mFileName;

	//Buffer Size
	int mSize;

	//Internal Buffer
	char* mBuffer;	
	char* mBufferStart;
};

#endif
