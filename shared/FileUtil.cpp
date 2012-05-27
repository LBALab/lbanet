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


#ifdef WIN32
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#else
#include <sys/stat.h>
#include <dirent.h>
#endif




/***********************************************************
check if file/directory exits
***********************************************************/
bool FileUtil::FileExist(const std::string &Filename, bool Directory)
{
#ifdef WIN32
	boost::filesystem::path full_path( boost::filesystem::system_complete( Filename ) );
	if ( !boost::filesystem::exists( full_path ) )
		return false;

	if(Directory)
		return ( boost::filesystem::is_directory( full_path ) );
	else
		return ( boost::filesystem::is_regular_file( full_path ) );
#else	
	struct stat st;
	return (stat(Filename.c_str(),&st) == 0);
#endif
}


/***********************************************************
list files in directory
***********************************************************/
bool FileUtil::ListFilesInDir(const std::string &Path, std::vector<std::string> &filelist,
									std::string filename)
{
#ifdef WIN32  
	{
		boost::filesystem::path full_path( boost::filesystem::system_complete( Path ) );
		if ( !boost::filesystem::exists( full_path ) )
			return false;

		if ( boost::filesystem::is_directory( full_path ) )
		{
			boost::filesystem::directory_iterator end_iter;
			for ( boost::filesystem::directory_iterator dir_itr( full_path ); dir_itr != end_iter;	++dir_itr )
			{
				if ( boost::filesystem::is_regular_file( dir_itr->status() ) )
				{
					if(filename == "" || (dir_itr->path().stem() == filename))
					{
						filelist.push_back(dir_itr->path().filename());
					}
				}
			}
		}
	}
	return true;	
#else
	// TODO
	return false;
#endif
}



/***********************************************************
list dirs in directory
***********************************************************/
bool FileUtil::ListDirsInDir(const std::string &Path, std::vector<std::string> &filelist,
								std::string addfilename)
{
#ifdef WIN32  
	boost::filesystem::path full_path( boost::filesystem::system_complete( Path ) );

	if ( !boost::filesystem::exists( full_path ) )
		return false;


	if ( boost::filesystem::is_directory( full_path ) )
	{
		boost::filesystem::directory_iterator end_iter;
		for ( boost::filesystem::directory_iterator dir_itr( full_path ); dir_itr != end_iter;	++dir_itr )
		{
			if ( boost::filesystem::is_directory( dir_itr->status() ) )
			{  
				if(dir_itr->filename() != ".svn")
					filelist.push_back(dir_itr->path().string() + addfilename);
			}
		}
	}
	return true;
#else
	DIR *dir;
	struct dirent *ent;
	dir = opendir(Path.c_str());
	if (dir != NULL) 
	{
		while ((ent = readdir (dir)) != NULL) 
		{
			if (ent->d_type == DT_DIR && ent->d_name != ".svn")
				filelist.push_back(Path + "/" + ent->d_name);
		}
		closedir (dir);
		return true;
	} 
	
	return false;
#endif	
}

/***********************************************************
list dirs in directory
***********************************************************/
bool FileUtil::ListDirsNoPathInDir(const std::string &Path, std::vector<std::string> &filelist)
{
 #ifdef WIN32 
	boost::filesystem::path full_path( boost::filesystem::system_complete( Path ) );

	if ( !boost::filesystem::exists( full_path ) )
		return false;


	if ( boost::filesystem::is_directory( full_path ) )
	{
		boost::filesystem::directory_iterator end_iter;
		for ( boost::filesystem::directory_iterator dir_itr( full_path ); dir_itr != end_iter;	++dir_itr )
		{
			if ( boost::filesystem::is_directory( dir_itr->status() ) )
			{	  
				if(dir_itr->filename() != ".svn")
				  filelist.push_back(dir_itr->filename());
					
			}
		}
	}
	return true;
#else
	DIR *dir;
	struct dirent *ent;
	dir = opendir(Path.c_str());
	if (dir != NULL) 
	{
		while ((ent = readdir (dir)) != NULL) 
		{
			if (ent->d_type == DT_DIR && ent->d_name != ".svn")
				filelist.push_back(ent->d_name);
		}
		closedir (dir);
		return true;
	} 
	
	return false;
#endif		
}




/***********************************************************
copy file
***********************************************************/
void FileUtil::MakeFileCopy(const std::string &Source, const std::string &Dest)
{
#ifdef WIN32  
	boost::filesystem::copy_file(Source, Dest);
#else
	//TODO
#endif	
}



/***********************************************************
create directory
***********************************************************/
bool FileUtil::CreateNewDirectory(const std::string &Path)
{
#ifdef WIN32  
	try
	{
		boost::filesystem::create_directory(Path);
	}
	catch(...)
	{
		return false;
	}
	return true;
#else
	return (mkdir(Path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0);
#endif
}