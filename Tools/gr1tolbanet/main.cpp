#include <map>
#include <set>
#include <fstream>

#include "lba_map_gl.h"
#include "lba_mapphys.h"

#include <IL/il.h>
#include <IL/ilu.h>


static void Trim(std::string& str)
{
	std::string::size_type pos = str.find_last_not_of(' ');
	if(pos != std::string::npos)
	{
		str.erase(pos + 1);
		pos = str.find_first_not_of(' ');

		if(pos != std::string::npos)
			str.erase(0, pos);
	}
	else
		str.clear();

}

static void Tokenize(const std::string& str,
										std::vector<std::string>& tokens,
										const std::string& delimiters)
{
	// Skip delimiters at beginning.
	std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	std::string::size_type pos     = str.find_first_of(delimiters, lastPos);



	while (std::string::npos != pos || std::string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		std::string tmp = str.substr(lastPos, pos - lastPos);
		Trim(tmp);
		tokens.push_back(tmp);

		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);

		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}
}

int main(int argc, char** argv)
{
	ilInit();
	iluInit();

	std::cout<<"Please give the path of the gr file / batch file you want to convert:"<<std::endl;
	std::string file;
	std::cin>>file;
	int layout = 0;
	int lba2 = 1;

	std::string extension = file.substr(file.size() - 3);
	if(extension == "txt") // batch file
	{
		// parse the file
		std::ifstream txtfile(file.c_str());
		if (txtfile.fail())  
		{ 
			std::cout << "File not found" <<std::endl;
			return 0; 
		}

		std::string line;
		while(std::getline(txtfile, line)  && txtfile.good() )
		{
			std::vector<std::string> tokens;
			Tokenize(line, tokens, ",");

			file = tokens[0];
			layout = atoi(tokens[1].c_str());
			lba2 = 1;
			extension = file.substr(file.size() - 3);
			if(extension == "gr1")
				lba2 = 0;

			bool forcelayout = false;
			if(lba2 && layout >= 0)
				forcelayout = true;

			// export graphic
			LBA_MAP_GL map(lba2, file, layout, forcelayout);
			map.ExportMapOSG();

			//export physic
			LBA_MAP_PHYS mapp((lba2==1), file, layout, forcelayout);
		}
		txtfile.close();


		//terminate
		return 0;
	}


	if(extension == "gr1")
	{
		lba2 = false;
		std::cout<<"Please give the layout you used to create the gr1 file:"<<std::endl;
		std::cout<<"0: Prisons, factories, industrial buildings"<<std::endl;
		std::cout<<"1: Islands"<<std::endl;
		std::cout<<"5: Houses"<<std::endl;
		std::cout<<"7: Yellow brick buildings (e.g. Library)"<<std::endl;
		std::cout<<"8: Caves"<<std::endl;
		std::cout<<"9: Snow scenes"<<std::endl;
		std::cout<<"12: Military islands"<<std::endl;
		std::cout<<"17: Ruins"<<std::endl;
		std::cout<<"34: Sewers"<<std::endl;
		std::cout<<"36: Desert scenes"<<std::endl;
		std::cout<<"59: Ruined military islands (e.g. Rebellion)"<<std::endl;
		std::cout<<"93: Ruined scenes (e.g. Fortress)"<<std::endl;
		std::cout<<"106: Working areas (e.g. Polar Island)"<<std::endl;
		std::cout<<"116: Decorated scenes"<<std::endl<<std::endl;

		std::cin>>layout;

	}
	std::cout<<"Generating"<<std::endl;

	// export graphic
	LBA_MAP_GL map(lba2, file, layout);
	map.ExportMapOSG();

	//export physic
	LBA_MAP_PHYS mapp((lba2==1), file, layout);


	return 0;
}














