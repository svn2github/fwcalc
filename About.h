//---------------------------------------------------------------------------

#ifndef AboutH
#define AboutH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include <jpeg.hpp>//---------------------------------------------------------------------------
class TAboutDlg : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label3;
        TButton *Ok;
        TLabel *Version;
        TLabel *CompileTime;
	TImage *Image1;
	TLabel *HomepageURL;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall OkClick(TObject *Sender);
	void __fastcall HomepageURLClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TAboutDlg(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutDlg *AboutDlg;
//---------------------------------------------------------------------------
#endif
