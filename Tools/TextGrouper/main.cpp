/*
------------------------[ Lbanet Tool ]-------------------------
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
#include "MapInfoXmlReader.h"
#include "MapInfoXmlWriter.h"
#include <vector>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
namespace fs = boost::filesystem;

std::vector<std::string> GetFile(const std::string &directory)
{
	// get all xml file of the directory
	std::vector<std::string> files;
	{
		fs::path full_path( fs::system_complete( directory.c_str() ) );

		if ( !fs::exists( full_path ) )
			return files;

		if ( fs::is_directory( full_path ) )
		{
			fs::directory_iterator end_iter;
			for ( fs::directory_iterator dir_itr( full_path ); dir_itr != end_iter;	++dir_itr )
			{
				if (! fs::is_directory( dir_itr->status() ) )
				{
					files.push_back(dir_itr->path().string());
				}
			}
		}
	}

	return files;
}

void Group(const std::string & path, const std::string & outfile, const std::string & offsetfile)
{
	std::vector<std::string> files = GetFile(path);

	//todo - sort files

	std::map<long, std::string> globaltexts;
	std::map<std::string, long> offsets;

	for(size_t i=0; i<files.size(); ++i)
	{
		std::map<long, std::string> texts = MapInfoXmlReader::LoadTextFile(files[i]);

		long offset = 0;
		if(globaltexts.size() > 0)
		{
			offset = (globaltexts.rbegin()->first + 1);
			std::string name = files[i];
			name = name.substr(name.find_last_of("/")+1);
			offsets[name] = offset;
		}

		std::map<long, std::string>::iterator itmap = texts.begin();
		std::map<long, std::string>::iterator endmap = texts.end();
		for(; itmap != endmap; ++itmap)
		{
			globaltexts[itmap->first+offset] = itmap->second;
		}
	}

	MapInfoXmlWriter::SaveTexts(outfile, globaltexts);

	std::ofstream filem(offsetfile.c_str());
	std::map<std::string, long>::iterator ito = offsets.begin();
	std::map<std::string, long>::iterator endo = offsets.end();
	for(; ito != endo; ++ito)
		filem<<ito->first<<" "<<ito->second<<std::endl;
}


int main( int argc, char **argv )
{
	Group("Texts/de/Lba1", "Lba1/de/map.xml", "Lba1/textoffsets.txt");
	Group("Texts/en/Lba1", "Lba1/en/map.xml", "Lba1/textoffsets.txt");
	Group("Texts/fr/Lba1", "Lba1/fr/map.xml", "Lba1/textoffsets.txt");
	Group("Texts/it/Lba1", "Lba1/it/map.xml", "Lba1/textoffsets.txt");
	Group("Texts/sp/Lba1", "Lba1/sp/map.xml", "Lba1/textoffsets.txt");

	Group("Texts/de/Lba2", "Lba2/de/map.xml", "Lba2/textoffsets.txt");
	Group("Texts/en/Lba2", "Lba2/en/map.xml", "Lba2/textoffsets.txt");
	Group("Texts/fr/Lba2", "Lba2/fr/map.xml", "Lba2/textoffsets.txt");
	Group("Texts/it/Lba2", "Lba2/it/map.xml", "Lba2/textoffsets.txt");
	Group("Texts/sp/Lba2", "Lba2/sp/map.xml", "Lba2/textoffsets.txt");

	return 0;
}


