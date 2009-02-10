//---------------------------------------------------------------------------

#ifndef KeyboardShorcutFormH
#define KeyboardShorcutFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TKeyboardShorcutDlg : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo1;
	TButton *Button1;
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TKeyboardShorcutDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKeyboardShorcutDlg *KeyboardShorcutDlg;
//---------------------------------------------------------------------------
#endif
