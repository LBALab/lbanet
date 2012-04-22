//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LBAHolomapLocations_main.h"
#include "HolomapLib.h"
#include "HoloHelp.h"
#include "about.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;

String vnum = "0.02";

THolomap Holomap;
AnsiString Path;

THandle * ComHandle;

AnsiString textInfo2[29] = {
"Citadel Island",
"Principal Island",
"White Leaf Desert",
"Proxima Island",
"Rebellion Island",
"Hamalayi Range",
"Tippett Island",
"Brundle Island",
"Fortress Island",
"Polar Island",
"Clear Water Lake (The Hamalayi mountains)",
"Water Tower (Principal island)",
"Twinsen's house (Citadel island)",
"Forger's Cell (Principal island)",
"Drug store (Citadel island)",
"Forger's house (Proxima island)",
"Dr FunFrock's headquarters (Principal island)",
"Teleportation Center (Brundle island)",
"Maritime Museum (Proxima island)",
"Cloning Center & Fortress (Fortress island)",
"Runic Stone (Proxima island)",
"Drug store (Citadel island)",
"Runic Stone",
"Mr. Mies Van der Rooh the architect's house. Bug street (Citadel island)",
"Well of Sendell (Polar island)",
"Library (Principal Island)",
"Port-Belooga (Principal Island)",
"Proxim-City (Proxima Island)",
"Mutant Factory (The Hamalayi mountains)"
};                            

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    Form1->Caption = Form1->Caption + vnum;
    Form1->Caption = Form1->Caption + " by alexfont";

    if(ParamCount()>0){
        Path = ParamStr(1);
        if(StrPos(LowerCase(Path).c_str(),".hl1")){
            Holomap = loadHolomapLocations(Path.c_str());
            pl_holomap->Visible = True;
        }
        else if(StrPos(LowerCase(Path).c_str(),".hl2")){
            ShowMessage("LBA2 Holomap Locations isn't supported in this version!");
        }
        else
            ShowMessage("This program doens't support this file!");
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenaHolomapLocationfilelhlldclun1Click(
      TObject *Sender)
{
    if(OpenDialog1->Execute()){
        Path = OpenDialog1->FileName;
        if(StrPos(LowerCase(Path).c_str(),".hl1")){
            Holomap = loadHolomapLocations(Path.c_str());
            pl_holomap->Visible = True;
        }
        else if(StrPos(LowerCase(Path).c_str(),".hl2")){
            ShowMessage("LBA2 Holomap Locations isn't supported in this version!");
        }
        else
            ShowMessage("This program doens't support this file!");
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListBox1Click(TObject *Sender)
{
    edt_x->Value = Holomap.Location[ListBox1->ItemIndex].X;
    edt_y->Value = Holomap.Location[ListBox1->ItemIndex].Y;
    edt_z->Value = Holomap.Location[ListBox1->ItemIndex].Z;
    edt_location->Value = Holomap.Location[ListBox1->ItemIndex].textInfo-200;
    mm_info->Clear();
    mm_info->Lines->Add(textInfo2[Holomap.Location[ListBox1->ItemIndex].textInfo-200]); 
}
//---------------------------------------------------------------------------
MESSAGE void TForm1::DropFile(TMessage &Message)
{
   char buffer[256];
   DragQueryFile((HDROP) Message.WParam,0,buffer,256); // 0 means one file dragged
   DragFinish((HDROP) Message.WParam);

   AnsiString *xis = new AnsiString(buffer);
   Path = *xis;
   delete xis;

        if(StrPos(LowerCase(Path).c_str(),".hl1")){
            Holomap = loadHolomapLocations(Path.c_str());
            pl_holomap->Visible = True;
        }
        else if(StrPos(LowerCase(Path).c_str(),".hl2")){
            ShowMessage("LBA2 Holomap Locations isn't supported in this version!");
        }
        else
            ShowMessage("This program doens't support this file!");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    DragAcceptFiles(Handle,true);   
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormDestroy(TObject *Sender)
{
    DragAcceptFiles(Handle,false);    
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveHolomapLocationfile1Click(TObject *Sender)
{
    if(Path!="")
        saveHolomapLocations(Path.c_str(),Holomap);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edt_locationChange(TObject *Sender)
{
    if(edt_location->Value!=(long)""){
        mm_info->Lines->Clear();
        mm_info->Lines->Add(textInfo2[edt_location->Value]);
        Holomap.Location[ListBox1->ItemIndex].textInfo = edt_location->Value+200;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edt_xChange(TObject *Sender)
{
    if(edt_x->Value!=(long)"")
        Holomap.Location[ListBox1->ItemIndex].X = edt_x->Value;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edt_yChange(TObject *Sender)
{
    if(edt_y->Value!=(long)"")
        Holomap.Location[ListBox1->ItemIndex].Y = edt_y->Value;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::edt_zChange(TObject *Sender)
{
    if(edt_z->Value!=(long)"")
        Holomap.Location[ListBox1->ItemIndex].Z = edt_z->Value;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SaveAs1Click(TObject *Sender)
{
    if(SaveDialog1->Execute()){
        Path = SaveDialog1->FileName;
        saveHolomapLocations(Path.c_str(),Holomap);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Close1Click(TObject *Sender)
{
    pl_holomap->Visible = False;
    Path = "";
    edt_x->Value=0;
    edt_y->Value=0;
    edt_z->Value=0;
    edt_location->Value = 0;
    ListBox1->ItemIndex = -1;
    mm_info->Lines->Clear();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::CoordinatesHelp1Click(TObject *Sender)
{
    frm_holoHelp->Show();    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::About1Click(TObject *Sender)
{
    frm_about->ShowModal();
}
//---------------------------------------------------------------------------

