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

void TransformTextLang(const std::vector<std::string> &files, 
					   const std::string outputfile, size_t start, size_t end)
{
	std::map<long, std::string> fulltxts;
	long idx=0;


	for(size_t i=start; i< end; ++i)
	{
		std::map<long, std::string> txts = MapInfoXmlReader::LoadTextFile(files[i]);
		std::map<long, std::string>::iterator itm = txts.begin();
		std::map<long, std::string>::iterator endm = txts.end();
		for(; itm != endm; ++itm, ++idx)
			fulltxts[idx] = itm->second;
	}

	MapInfoXmlWriter::SaveTexts(outputfile, fulltxts);
}


void TransformText(const std::string & directory, const std::string outputfile, bool lba1)
{
	int cc=0;
	int cc2 = 14;

	std::vector<std::string> files = GetFile(directory);
	TransformTextLang(files, outputfile+"/en.xml", cc, cc2);
	cc = cc2;
	cc2 += 14;
	TransformTextLang(files, outputfile+"/fr.xml", cc, cc2);
	cc = cc2;
	cc2 += 14;
	TransformTextLang(files, outputfile+"/de.xml", cc, cc2);
	cc = cc2;
	cc2 += 14;
	TransformTextLang(files, outputfile+"/sp.xml", cc, cc2);
	cc = cc2;
	cc2 += 14;
	TransformTextLang(files, outputfile+"/it.xml", cc, cc2);

}

int main( int argc, char **argv )
{
	TransformText("Data/LBA1", "Data/lba1res", true);
	TransformText("Data/LBA2", "Data/lba2res", false);

	return 0;
}


