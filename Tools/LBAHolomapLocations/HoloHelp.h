//---------------------------------------------------------------------------

#ifndef HoloHelpH
#define HoloHelpH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class Tfrm_holoHelp : public TForm
{
__published:	// IDE-managed Components
    TImage *Image1;
private:	// User declarations
public:		// User declarations
    __fastcall Tfrm_holoHelp(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_holoHelp *frm_holoHelp;
//---------------------------------------------------------------------------
#endif
