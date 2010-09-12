#include "globals.h"
#include "lba_map_gl.h"
#include "lba_mapphys.h"

#include <IL/il.h>
#include <IL/ilu.h>

int main(int argc, char** argv)
{
	ilInit();
	iluInit();



	for(int i=0; i<=133; ++i)
	{
		// export graphic
		LBA_MAP_GL map(i, 0);
		map.ExportMapOSG();

		//export physic
		LBA_MAP_PHYS mapp(i, 0);
	}

	for(int i=1; i<=148; ++i)
	{
		// export graphic
		LBA_MAP_GL map(i, 1);
		map.ExportMapOSG();

		//export physic
		LBA_MAP_PHYS mapp(i, 1);
	}

	return 0;
}
