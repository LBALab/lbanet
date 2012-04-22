//---------------------------------------------------------------------------

#ifndef LBAHolomapLocations_mainH
#define LBAHolomapLocations_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "CSPIN.h"
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <jpeg.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TPanel *pl_holomap;
    TMemo *mm_info;
    TListBox *ListBox1;
    TLabel *Label4;
    TLabel *Label3;
    TLabel *Label2;
    TLabel *Label1;
    TCSpinEdit *edt_x;
    TCSpinEdit *edt_y;
    TCSpinEdit *edt_z;
    TImage *Image1;
    TMainMenu *MainMenu1;
    TMenuItem *File1;
    TMenuItem *OpenaHolomapLocationfilelhlldclun1;
    TMenuItem *Exit1;
    TMenuItem *N1;
    TOpenDialog *OpenDialog1;
    TMenuItem *SaveHolomapLocationfile1;
    TLabel *Label5;
    TCSpinEdit *edt_location;
    TMenuItem *SaveAs1;
    TSaveDialog *SaveDialog1;
    TMenuItem *Close1;
    TMenuItem *About1;
    TMenuItem *CoordinatesHelp1;
    void __fastcall OpenaHolomapLocationfilelhlldclun1Click(
          TObject *Sender);
    void __fastcall ListBox1Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall SaveHolomapLocationfile1Click(TObject *Sender);
    void __fastcall edt_locationChange(TObject *Sender);
    void __fastcall edt_xChange(TObject *Sender);
    void __fastcall edt_yChange(TObject *Sender);
    void __fastcall edt_zChange(TObject *Sender);
    void __fastcall SaveAs1Click(TObject *Sender);
    void __fastcall Close1Click(TObject *Sender);
    void __fastcall CoordinatesHelp1Click(TObject *Sender);
    void __fastcall About1Click(TObject *Sender);
private:	// User declarations
    MESSAGE void DropFile(TMessage &Message);
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(WM_DROPFILES, TMessage, DropFile);
END_MESSAGE_MAP(TForm);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
