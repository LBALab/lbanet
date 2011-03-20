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


#include "FileUtil.h"


#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
namespace fs = boost::filesystem;



/***********************************************************
check if file/directory exits
***********************************************************/
bool FileUtil::FileExist(const std::string &Filename, bool Directory)
{
	fs::path full_path( fs::system_complete( Filename ) );
	if ( !fs::exists( full_path ) )
		return false;

	if(Directory)
		return ( fs::is_directory( full_path ) );
	else
		return ( fs::is_regular_file( full_path ) );
		
}


/***********************************************************
list files in directory
***********************************************************/
bool FileUtil::ListFilesInDir(const std::string &Path, std::vector<std::string> &filelist,
									std::string filename)
{
	{
		fs::path full_path( fs::system_complete( Path ) );
		if ( !fs::exists( full_path ) )
			return false;

		if ( fs::is_directory( full_path ) )
		{
			fs::directory_iterator end_iter;
			for ( fs::directory_iterator dir_itr( full_path ); dir_itr != end_iter;	++dir_itr )
			{
				if ( fs::is_regular_file( dir_itr->status() ) )
				{
					if(filename == "" || (dir_itr->path().stem() == filename))
						filelist.push_back(dir_itr->path().filename());
				}
			}
		}
	}

	return true;
}



/***********************************************************
list dirs in directory
***********************************************************/
bool FileUtil::ListDirsInDir(const std::string &Path, std::vector<std::string> &filelist,
								std::string addfilename)
{
	fs::path full_path( fs::system_complete( Path ) );

	if ( !fs::exists( full_path ) )
		return false;


	if ( fs::is_directory( full_path ) )
	{
		fs::directory_iterator end_iter;
		for ( fs::directory_iterator dir_itr( full_path ); dir_itr != end_iter;	++dir_itr )
		{
			if ( fs::is_directory( dir_itr->status() ) )
			{
				filelist.push_back(dir_itr->path().string() + addfilename);
			}
		}
	}

	return true;
}


/***********************************************************
copy file
***********************************************************/
void FileUtil::MakeFileCopy(const std::string &Source, const std::string &Dest)
{
	boost::filesystem::copy_file(Source, Dest);
}



/***********************************************************
create directory
***********************************************************/
bool FileUtil::CreateNewDirectory(const std::string &Path)
{
	try	
	{
		boost::filesystem::create_directory( Path );
	}
	catch(...)
	{
		return false;
	}

	return true;
}