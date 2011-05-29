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


#if !defined(__LbaNetModel_TriangleMeshInfo_h)
#define __LbaNetModel_TriangleMeshInfo_h


#include <fstream>

/***********************************************************************
 * TriangleMeshInfo
 ***********************************************************************/
class TriangleMeshInfo
{
public:

	/***********************************************************
	constructor
	***********************************************************/
	TriangleMeshInfo::TriangleMeshInfo(const std::string & filename, bool deletematerial)
	: _deletematerial(deletematerial), _sizevertex(0), _sizeindices(0), _sizematerials(0)
	{
		_buffervertex = NULL;
		_bufferindices = NULL;
		_buffermaterials = NULL;

		// load data from binary file and set it into a triangle mesh
		std::ifstream file(filename.c_str(), std::ifstream::binary);
		if(!file.is_open())
			return;

		file.read((char*)&_sizevertex, sizeof(unsigned int));
		file.read((char*)&_sizeindices, sizeof(unsigned int));
		file.read((char*)&_sizematerials, sizeof(unsigned int));

		_buffervertex = new float[_sizevertex];
		_bufferindices = new unsigned int[_sizeindices];
		file.read((char*)_buffervertex, _sizevertex*sizeof(float));
		file.read((char*)_bufferindices, _sizeindices*sizeof(unsigned int));

		if(_sizematerials > 0)
		{
			_buffermaterials = new short[_sizematerials];
			file.read((char*)_buffermaterials, _sizematerials*sizeof(short));
		}
	}

	/***********************************************************
	destructor
	***********************************************************/
	TriangleMeshInfo::~TriangleMeshInfo()
	{
		if(_buffervertex)
			delete[] _buffervertex;

		if(_bufferindices)
			delete[] _bufferindices;

		if(_deletematerial && _buffermaterials)
			delete[] _buffermaterials;

	}

	unsigned int	_sizevertex;
	unsigned int	_sizeindices;
	unsigned int	_sizematerials;

	float *			_buffervertex;
	unsigned int *	_bufferindices;
	short *			_buffermaterials;

protected:
	bool			_deletematerial;
};

#endif