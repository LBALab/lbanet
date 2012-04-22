//---------------------------------------------------------------------------

#ifndef HolomapLibH
#define HolomapLibH
//---------------------------------------------------------------------------

struct TLocation
{
    unsigned short X;
    unsigned short Y;
    unsigned short Z;
    unsigned short textInfo;
};

struct THolomap
{
	int numOfLocations;
	TLocation Location[150];
};

THolomap loadHolomapLocations(char *fileName);
void saveHolomapLocations(char *fileName, THolomap Holomap);

#endif
