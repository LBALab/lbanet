//---------------------------------------------------------------------------


#pragma hdrstop
#include "HolomapLib.h"
#include "HQRLib.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


void saveHolomapLocations(char *fileName, THolomap Holomap)
{
  //  unsigned char* holomapPtr;
    FILE* holomapHandle;
  //  holomapPtr = (unsigned char*)malloc(1200);

    holomapHandle = fopen(fileName, "wb+");

    fseek(holomapHandle, SEEK_SET, 0);

    for(int i=0; i < Holomap.numOfLocations; i++)
    {
/*        *((unsigned short*)holomapPtr) = Holomap.Location[i].X; holomapPtr+=2;
        *((unsigned short*)holomapPtr) = Holomap.Location[i].Y; holomapPtr+=2;
        *((unsigned short*)holomapPtr) = Holomap.Location[i].Z; holomapPtr+=2;
        *((unsigned short*)holomapPtr) = Holomap.Location[i].textInfo; holomapPtr+=2;  */
        fwrite(&Holomap.Location[i].X,2,1,holomapHandle);
        fwrite(&Holomap.Location[i].Y,2,1,holomapHandle);
        fwrite(&Holomap.Location[i].Z,2,1,holomapHandle);
        fwrite(&Holomap.Location[i].textInfo,2,1,holomapHandle);
    }

    fclose(holomapHandle);

/*    saveResource(holomapHandle,holomapPtr,1200);
    closeResource(holomapHandle);
    free(holomapPtr);       */
}

THolomap loadHolomapLocations(char *fileName)
{
    int filesize;
    unsigned char* holomapPtr;
    THolomap Holomap;

    filesize = ResourceSize(fileName);
    FILE* holomapHandle = openResource(fileName);
    holomapPtr = (unsigned char*)malloc(filesize);
    readResource(holomapHandle,(char*)holomapPtr,filesize);
    closeResource(holomapHandle);

    Holomap.numOfLocations = filesize/8;
    //Holomap.Location = (TLocation*)malloc(sizeof(TLocation*)*Holomap.numOfLocations);

    for(int i=0; i < Holomap.numOfLocations; i++)
    {
        Holomap.Location[i].X = *((unsigned short *)holomapPtr); holomapPtr+=2;
        Holomap.Location[i].Y = *((unsigned short *)holomapPtr); holomapPtr+=2;
        Holomap.Location[i].Z = *((unsigned short *)holomapPtr); holomapPtr+=2;
        Holomap.Location[i].textInfo = *((unsigned short *)holomapPtr); holomapPtr+=2;
    }
    return Holomap;
}
