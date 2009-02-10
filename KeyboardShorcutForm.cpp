//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "KeyboardShorcutForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TKeyboardShorcutDlg *KeyboardShorcutDlg;
//---------------------------------------------------------------------------
__fastcall TKeyboardShorcutDlg::TKeyboardShorcutDlg(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TKeyboardShorcutDlg::Button1Click(TObject *Sender)
{
	Hide();	
}
//---------------------------------------------------------------------------
