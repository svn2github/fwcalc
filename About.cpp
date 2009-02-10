//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "About.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutDlg *AboutDlg;

static AnsiString GetProgramVersionString()
{
DWORD t;
DWORD size = GetFileVersionInfoSize("FwCalc.exe", &t);
AnsiString ret = "unknown";

	if(size)
	{
    	void *buf = malloc(size);
      	        if(!buf)  return ret;
        
            	if(GetFileVersionInfo("FwCalc.exe", NULL, size, buf))
                {
            	LPVOID value;
            	UINT val_len;

            		if(VerQueryValue(buf, TEXT("\\StringFileInfo\\040904E4\\FileVersion"),&value, &val_len))
                        {
                        	ret = (LPSTR)value;
                        }
            	}
            	free(buf);
	}
        return ret;
}


//---------------------------------------------------------------------------
__fastcall TAboutDlg::TAboutDlg(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAboutDlg::FormCreate(TObject *Sender)
{
        Version->Caption = AnsiString("Version: ") + GetProgramVersionString();
        CompileTime->Caption = AnsiString("Compiled: ") + __DATE__ + "  " + __TIME__;        
}
//---------------------------------------------------------------------------
void __fastcall TAboutDlg::OkClick(TObject *Sender)
{
        Hide();        
}
//---------------------------------------------------------------------------

void __fastcall TAboutDlg::HomepageURLClick(TObject *Sender)
{
	ShellExecute(NULL, "open", "http://fwcalc.sourceforge.net/", "", "", SW_SHOWDEFAULT); 
}
//---------------------------------------------------------------------------

