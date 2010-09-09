#include "globals.h"
#include "lba_map_gl.h"

#include <IL/il.h>
#include <IL/ilu.h>

int main(int argc, char** argv)
{
	ilInit();
	iluInit();
	int maxbricks = 0;

	for(int i=0; i<=133; ++i)
	{
		LBA_MAP_GL map(i, 0);
		map.ExportMapOSG();
		
		if(maxbricks < map.GetNumberBricks())
			maxbricks = map.GetNumberBricks();
	}

	for(int i=1; i<=148; ++i)
	{
		LBA_MAP_GL map(i, 1);
		map.ExportMapOSG();

		if(maxbricks < map.GetNumberBricks())
			maxbricks = map.GetNumberBricks();
	}

	std::cout<<std::endl<<"max number bricks: "<<maxbricks<<std::endl;
	return 0;
}
