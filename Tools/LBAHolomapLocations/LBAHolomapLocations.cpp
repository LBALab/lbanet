//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("LBAHolomapLocations_main.cpp", Form1);
USEFORM("HoloHelp.cpp", frm_holoHelp);
USEFORM("about.cpp", frm_about);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
         Application->Initialize();
         Application->Title = "LBA Holomap Locations";
         Application->CreateForm(__classid(TForm1), &Form1);
         Application->CreateForm(__classid(Tfrm_holoHelp), &frm_holoHelp);
         Application->CreateForm(__classid(Tfrm_about), &frm_about);
         Application->Run();
    }
    catch (Exception &exception)
    {
         Application->ShowException(&exception);
    }
    catch (...)
    {
         try
         {
             throw Exception("");
         }
         catch (Exception &exception)
         {
             Application->ShowException(&exception);
         }
    }
    return 0;
}
//---------------------------------------------------------------------------
