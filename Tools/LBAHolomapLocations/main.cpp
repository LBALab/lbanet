#include "HolomapLib.h"
#include <fstream>
#include <math.h>

#ifndef M_PI
#define M_PI    3.14159265358979323846f
#endif

int main( int argc, char **argv )
{
	THolomap hl = loadHolomapLocations("RESS09.hl1");

	std::ofstream file("outlua.csv");
	std::ofstream file2("out.csv");

	for(int i=0; i<119; ++i)
	{
		long locX = hl.Location[i].X;
		if(locX > 60000)
			locX -= 65534;
		locX = -locX;

		long locY = hl.Location[i].Y;
		if(locY > 60000)
			locY -= 65534;

		float resX = ((locX*90)/255.0f);
		float resY = ((locY*90)/255.0f);
		float resZ = 6+(hl.Location[i].Z/128.0f);

		float radX = resX*M_PI/180.0f;
		float radY = resY*M_PI/180.0f;

		float cY = resZ*sin(radY);
		float cZ = resZ*sin(radX)*cos(radY);
		float cX = resZ*cos(radY)*cos(radX);

	//y	float cX = resZ*cos(radX)*sin(radY);
	//z	float cY = resZ*sin(radX);
	//x	float cZ = resZ*cos(radX)*cos(radY);


		float resX2 = acos(cZ/resZ);

		float tmp = acos(cX/sqrt((cX*cX)+(cY*cY)));
		float resY2 = (cY >= 0)?tmp:((2*M_PI)-tmp);

		//float resX2 = asin(cY);
		//float resY2 = acos(cZ/cos(resX2));

		float degX = 180.0f*resX2/M_PI;
		float degY = 180.0f*resY2/M_PI;
		degX = 90 - degX;

		//int quartalX = (int)resX/90;

		//float Yfactor = (1+((fabs(resX))/90)) * (((quartalX % 2) == 0)? 1: -1);
		//float Xfactor = ((resY > 180) || (resY < -180))?1:-1;

		file<<std::endl<<std::endl;
		file<<"\tHolomapLoc_"<<i+1<<" = HolomapLocation("<<i+1<<")"<<std::endl;
		file<<"\tHolomapLoc_"<<i+1<<":SetTextId("<<hl.Location[i].textInfo-59<<")"<<std::endl;
		file<<"\tHolomapLoc_"<<i+1<<":SetName(\"\")"<<std::endl;
		file<<"\tHolomapLoc_"<<i+1<<":SetParentLocId(-1)"<<std::endl;
		file<<"\tHolomapLoc_"<<i+1<<":SetParentHoloId(1)"<<std::endl;
		file<<"\tHolomapLoc_"<<i+1<<":SetChildHoloId(-1)"<<std::endl;
		file<<"\tHolomapLoc_"<<i+1<<"_coord = HoloCoordinate()"<<std::endl;
		file<<"\t\tHolomapLoc_"<<i+1<<"_coord.polarcoords =true"<<std::endl;
		file<<"\t\tHolomapLoc_"<<i+1<<"_coord.posX ="<<degX<<std::endl;
		file<<"\t\tHolomapLoc_"<<i+1<<"_coord.posY ="<<degY<<std::endl;
		file<<"\t\tHolomapLoc_"<<i+1<<"_coord.posZ ="<<resZ<<std::endl;
		file<<"\t\tHolomapLoc_"<<i+1<<"_coord.dir_cen_X =0"<<std::endl;
		file<<"\t\tHolomapLoc_"<<i+1<<"_coord.dir_cen_Y =0"<<std::endl;
		file<<"\t\tHolomapLoc_"<<i+1<<"_coord.dir_cen_Z =0"<<std::endl;
		file<<"\tHolomapLoc_"<<i+1<<":SetCoordinate(HolomapLoc_"<<i+1<<"_coord)"<<std::endl;
		file<<"\tenvironment:AddHolomapLoc(HolomapLoc_"<<i+1<<")"<<std::endl;


		file2<<i+1<<","<<locX<<","<<locY<<","<<hl.Location[i].Z<<","<<hl.Location[i].textInfo-59<<std::endl;
	}

	file.flush();
	file.close();


	return 0;
}