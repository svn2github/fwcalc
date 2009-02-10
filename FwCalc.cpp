//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("FwCalcMainForm.cpp", FwCalcMainDlg);
USEFORM("About.cpp", AboutDlg);
USEFORM("KeyboardShorcutForm.cpp", KeyboardShorcutDlg);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		SetApplicationMainFormOnTaskBar(Application, true);
		Application->CreateForm(__classid(TFwCalcMainDlg), &FwCalcMainDlg);
		Application->CreateForm(__classid(TAboutDlg), &AboutDlg);
		Application->CreateForm(__classid(TKeyboardShorcutDlg), &KeyboardShorcutDlg);
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
