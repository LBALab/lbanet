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
#include "XmlReader.h"

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


static std::string replaceall(const std::string & str, const std::string & toreplace, const std::string & with)
{
	std::string res = str;

	int len = toreplace.size(), pos;
	while((pos=res.find(toreplace)) != std::string::npos)
	{
		res=res.substr(0,pos)+with+res.substr(pos+len);
	}

	return res;
}

void TransformTextLang(const std::vector<std::string> &files, 
					   const std::string outputfile, size_t start, size_t end)
{
	std::map<long, std::string> fulltxts;
	long idx=0;

	std::ofstream startIdxF("startindex.txt");
	long startidx = 0;

	for(size_t i=start; i< end; ++i)
	{
		std::map<long, std::string> txts = MapInfoXmlReader::LoadTextFile(files[i]);
		std::map<long, std::string>::iterator itm = txts.begin();
		std::map<long, std::string>::iterator endm = txts.end();

		startIdxF << files[i] << " " << startidx << std::endl;
		startidx += txts.size();

		for(; itm != endm; ++itm, ++idx)
			fulltxts[idx] = itm->second;
	}
	startIdxF.close();

	XmlReader::SaveTextFile(outputfile, fulltxts);
	//MapInfoXmlWriter::SaveTexts(outputfile, fulltxts);
}


void TransformText(const std::string & directory, const std::string outputfile, bool lba1)
{
	int cc=0;
	int cc2 = 14;

	std::vector<std::string> files = GetFile(directory);
	TransformTextLang(files, outputfile+"/en/map.xml", cc, cc2);
	cc = cc2;
	cc2 += 14;
	TransformTextLang(files, outputfile+"/fr/map.xml", cc, cc2);
	cc = cc2;
	cc2 += 14;
	TransformTextLang(files, outputfile+"/de/map.xml", cc, cc2);
	cc = cc2;
	cc2 += 14;
	TransformTextLang(files, outputfile+"/sp/map.xml", cc, cc2);
	cc = cc2;
	cc2 += 14;
	TransformTextLang(files, outputfile+"/it/map.xml", cc, cc2);

}



void CompareFiles(const std::string & originalf, const std::string & newf,
				  const std::string outputfile)
{
	
	std::map<long, std::string> origtxt = XmlReader::LoadTextFile(originalf);
	std::map<long, std::string> newtxt = XmlReader::LoadTextFile(newf);

	//std::map<long, std::string> origtxt = MapInfoXmlReader::LoadTextFileN(originalf);
	//std::map<long, std::string> newtxt = MapInfoXmlReader::LoadTextFileN(newf);

	std::map<std::string, long> newtxtrev;
	{
		std::map<long, std::string>::iterator itmo = newtxt.begin();
		std::map<long, std::string>::iterator endmo = newtxt.end();
		for(; itmo != endmo; ++itmo)
			newtxtrev[itmo->second] = itmo->first;
	}

	std::ofstream ofile(outputfile.c_str());
	std::vector<long> notfoundv;

	{
		std::map<long, std::string>::iterator itmo = origtxt.begin();
		std::map<long, std::string>::iterator endmo = origtxt.end();
		for(; itmo != endmo; ++itmo)
		{
			std::map<std::string, long>::iterator foundit = newtxtrev.find(itmo->second);
			if(foundit != newtxtrev.end())
				ofile<<itmo->first<<" "<<foundit->second<<std::endl;
			else
				notfoundv.push_back(itmo->first);
		}
	}



	std::vector<long>::iterator itvec = notfoundv.begin();
	while(itvec != notfoundv.end())
	{
		bool found = false;

		{
			std::string tmp = origtxt[*itvec];
			tmp = tmp.substr(0, 30);


			std::map<long, std::string>::iterator itmo = newtxt.begin();
			std::map<long, std::string>::iterator endmo = newtxt.end();
			for(; itmo != endmo; ++itmo)
			{
				if(itmo->second.find(tmp) != std::string::npos)
				{
					ofile<<*itvec<<" "<<itmo->first<<std::endl;
					itvec = notfoundv.erase(itvec);
					found = true;
				}
			}
		}
		if(!found && origtxt[*itvec].size() > 30)
		{
			std::string tmp = origtxt[*itvec];
			tmp = tmp.substr(tmp.size()-30);


			std::map<long, std::string>::iterator itmo = newtxt.begin();
			std::map<long, std::string>::iterator endmo = newtxt.end();
			for(; itmo != endmo; ++itmo)
			{
				if(itmo->second.find(tmp) != std::string::npos)
				{
					ofile<<*itvec<<" "<<itmo->first<<std::endl;
					itvec = notfoundv.erase(itvec);
					found = true;
				}
			}
		}

		//if(!found )
		//{
		//	std::string tmp = origtxt[*itvec];
		//	tmp = replaceall(tmp, "@ @", "@");

		//	std::map<long, std::string>::iterator itmo = newtxt.begin();
		//	std::map<long, std::string>::iterator endmo = newtxt.end();
		//	for(; itmo != endmo; ++itmo)
		//	{
		//		if(itmo->second.find(tmp) != std::string::npos)
		//		{
		//			ofile<<*itvec<<" "<<itmo->first<<std::endl;
		//			itvec = notfoundv.erase(itvec);
		//			found = true;
		//		}
		//	}
		//}

		if(!found)
			++itvec;
	}
	long ccc = newtxt.rbegin()->first + 1;
	//ofile<<std::endl<<std::endl<<"not found: "<<std::endl;
	for(size_t i=0; i< notfoundv.size(); ++i, ++ccc)
	{
		ofile<<notfoundv[i]<<" "<<ccc<<std::endl;
		newtxt[ccc] = origtxt[notfoundv[i]];
	}

	XmlReader::SaveTextFile(newf, newtxt);
}

int main( int argc, char **argv )
{
	TransformText("Data/LBA1", "Data/lba1res", true);
	TransformText("Data/LBA2", "Data/lba2res", false);

	CompareFiles("Data/map.xml", "Data/lba1res/en/map.xml",
				  "Data/check.txt");

	return 0;
}


