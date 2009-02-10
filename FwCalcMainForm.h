//---------------------------------------------------------------------------

#ifndef FwCalcMainFormH
#define FwCalcMainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>

#include "TFormatButton.h"

#include <stack>
#include <vector>
#include <deque>


#include "CalculatorEngine.h"

enum eCalcLayout {eLayoutUnknown, eLayoutNormal, eLayoutSciAlt, eLayoutComp};


//---------------------------------------------------------------------------



class TFwCalcMainDlg : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar;
	TPanel *ButtonPanel;
        TMainMenu *MainMenu1;
        TMenuItem *File1;
        TMenuItem *Exit1;
        TMenuItem *Edit1;
        TMenuItem *Copy1;
        TMenuItem *Paste1;
        TMenuItem *Config1;
        TPopupMenu *STOPopupMenu;
        TMenuItem *miMem0;
        TMenuItem *miMem1;
        TMenuItem *miMem2;
        TMenuItem *miMem3;
        TMenuItem *miMem4;
        TMenuItem *miMem5;
        TMenuItem *miMem6;
        TMenuItem *miMem7;
        TMenuItem *miMem8;
        TMenuItem *miMem9;
        TPopupMenu *RCLPopupMenu;
        TMenuItem *MenuItem1;
        TMenuItem *MenuItem2;
        TMenuItem *MenuItem3;
        TMenuItem *MenuItem4;
        TMenuItem *MenuItem5;
        TMenuItem *MenuItem6;
        TMenuItem *MenuItem7;
        TMenuItem *MenuItem8;
        TMenuItem *MenuItem9;
        TMenuItem *MenuItem10;
        TMenuItem *Help1;
        TMenuItem *About1;
	TMenuItem *Layout1;
	TMenuItem *NormalLayoutMenu;
	TMenuItem *SciAlt1LayoutMenu;
	TMenuItem *ComputationalLayoutMenu;
	TSpeedButton *Num7Button;
	TSpeedButton *Num8Button;
	TSpeedButton *Num9Button;
	TSpeedButton *Num4Button;
	TSpeedButton *Num5Button;
	TSpeedButton *Num6Button;
	TSpeedButton *Num1Button;
	TSpeedButton *Num2Button;
	TSpeedButton *Num3Button;
	TSpeedButton *Num0Button;
	TSpeedButton *NumDotButton;
	TSpeedButton *NumEEXButton;
	TSpeedButton *EnterButton;
	TSpeedButton *CHSButton;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SetHexButton;
	TSpeedButton *SetDecButton;
	TSpeedButton *SetOctButton;
	TSpeedButton *SetBinButton;
	TSpeedButton *ToggleTrigButton;
	TSpeedButton *STOButton;
	TSpeedButton *RCLButton;
	TSpeedButton *CLRButton;
	TSpeedButton *BackButton;
	TPanel *Panel1;
	TPaintBox *PaintBox;
	TPopupMenu *TrigPopupMenu;
	TMenuItem *SelectDegMenu;
	TMenuItem *SelectRadMenu;
	TMenuItem *SelectGradMenu;
	TMenuItem *Digits2;
	TMenuItem *N122;
	TMenuItem *N112;
	TMenuItem *N102;
	TMenuItem *N92;
	TMenuItem *N82;
	TMenuItem *N72;
	TMenuItem *N62;
	TMenuItem *N52;
	TMenuItem *N42;
	TMenuItem *N32;
	TMenuItem *N22;
	TMenuItem *N12;
	TMenuItem *N02;
	TMenuItem *Auto1;
	TMenuItem *N131;
	TMenuItem *N141;
	TMenuItem *N151;
	TMenuItem *N161;
	TMenuItem *N171;
	TMenuItem *N181;
	TMenuItem *N19201;
	TMenuItem *N1;
	TMenuItem *Keyboard1;
        void __fastcall FormKeyPress(TObject *Sender, char &Key);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall HandleEnterNum(TObject *Sender);
        void __fastcall PaintBoxPaint(TObject *Sender);
        void __fastcall Exit1Click(TObject *Sender);
		void __fastcall setDigitsClick(TObject *Sender);
        void __fastcall AutoDigits1Click(TObject *Sender);
        void __fastcall StoreMemButtonClick(TObject *Sender);
        void __fastcall RecallMemButtonClick(TObject *Sender);
        void __fastcall StoMemClick(TObject *Sender);
        void __fastcall RclMemClick(TObject *Sender);
		void __fastcall About1Click(TObject *Sender);
	void __fastcall FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall EnterButtonClick(TObject *Sender);
	void __fastcall CLRButtonClick(TObject *Sender);
	void __fastcall SetHexButtonClick(TObject *Sender);
	void __fastcall SetDecButtonClick(TObject *Sender);
	void __fastcall SetOctButtonClick(TObject *Sender);
	void __fastcall SetBinButtonClick(TObject *Sender);
	void __fastcall ToggleTrigButtonClick(TObject *Sender);
	void __fastcall NormalLayoutMenuClick(TObject *Sender);
	void __fastcall SciAlt1LayoutMenuClick(TObject *Sender);
	void __fastcall ComputationalLayoutMenuClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall CHSButtonClick(TObject *Sender);
	void __fastcall BackButtonClick(TObject *Sender);
	void __fastcall SelectDegMenuClick(TObject *Sender);
	void __fastcall SelectRadMenuClick(TObject *Sender);
	void __fastcall SelectGradMenuClick(TObject *Sender);
	void __fastcall Copy1Click(TObject *Sender);
	void __fastcall Paste1Click(TObject *Sender);
	void __fastcall SetDigitsMenuClick(TObject *Sender);
	void __fastcall Keyboard1Click(TObject *Sender);

private:	// windows event handlers
void __fastcall CMDialogKey(TWMKey &key);

BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(CM_DIALOGKEY , TWMKey, CMDialogKey)
END_MESSAGE_MAP(TForm)




private:	// User declarations
TCalculatorEngine *m_engine;

TFormatButton *m_op_buttons[16];
eCalcOperator m_op_action[16];
TFormatButton *m_alt1;
TFormatButton *m_alt2;
TFormatButton *m_alt3;
TFormatButton *m_alt4;
TFormatButton *m_alt5;
TFormatButton *m_alt6;

eCalcLayout m_current_layout;

TColor m_plus_sign_color;
TColor m_minus_sign_color;
TColor m_int_part_color;
TColor m_dot_color;
TColor m_frac_part_color;
TColor m_exp10_color;
TColor m_powersign_plus_color;
TColor m_powersign_minus_color;
TColor m_power_color;

int m_font_size;
int m_font_size_super;

bool m_updating;

private:
	void __fastcall OnModeChange(TObject *Sender);
	void __fastcall OnStackChange(TObject *Sender);

	void ParseValue(AnsiString txt, AnsiString &tlc, AnsiString &tuc);

	void UpdateMemPopupMenu(TPopupMenu *m);

	void CreateOperatorButtons();
	void AssignAltButtons();
	eCalcLayout LayoutFromShift(TShiftState Shift);
	void AssignLayout(eCalcLayout layout);

	void __fastcall OnOperatorClick(TObject *Sender);
	void __fastcall OnAltInputClick(TObject *Sender);

	void __fastcall OnError(TObject *Sender);


public:		// User declarations
        __fastcall TFwCalcMainDlg(TComponent* Owner);
        __fastcall ~TFwCalcMainDlg();
};
//---------------------------------------------------------------------------
extern PACKAGE TFwCalcMainDlg *FwCalcMainDlg;
//---------------------------------------------------------------------------
#endif
