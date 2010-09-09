#include "globals.h"
#include "lba_map_gl.h"

#include <IL/il.h>
#include <IL/ilu.h>

int main(int argc, char** argv)
{
	ilInit();
	iluInit();

	//LBA_MAP_GL map(0, 0);
	//map.ExportMapOSG();

	for(int i=0; i<=133; ++i)
	{
		LBA_MAP_GL map(i, 0);
		map.ExportMapOSG();
	}

	for(int i=1; i<=148; ++i)
	{
		LBA_MAP_GL map(i, 1);
		map.ExportMapOSG();
	}

	return 0;
}
