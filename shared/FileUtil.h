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


#ifndef __LBA_NET_FILE_UTIL_H__
#define __LBA_NET_FILE_UTIL_H__

#include <string>
#include <vector>

//*************************************************************************************************
//*                                      class FileUtil
//*************************************************************************************************

class FileUtil
{
public:
	// check if file/directory exits
	static  bool FileExist(const std::string &Filename, bool Directory);

	// list files in directory
	static  bool ListFilesInDir(const std::string &Path, std::vector<std::string> &filelist,
									std::string filename = "");

	// list dir in directory
	static  bool ListDirsInDir(const std::string &Path, std::vector<std::string> &filelist,
									std::string addfilename = "");

	// copy file
	static void MakeFileCopy(const std::string &Source, const std::string &Dest);

	// create directory
	static bool CreateNewDirectory(const std::string &Path);
};


#endif
