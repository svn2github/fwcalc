//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>

#include <registry.hpp>

#include "FwCalcMainForm.h"
#include <math.h>
#include <Math.hpp>
#include <Clipbrd.hpp>
#include "About.h"

#include "KeyboardShorcutForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFwCalcMainDlg *FwCalcMainDlg;

//---------------------------------------------------------------------------
__fastcall TFwCalcMainDlg::TFwCalcMainDlg(TComponent* Owner)
        : TForm(Owner)
{
		m_plus_sign_color = clBlack;
		m_minus_sign_color = clRed;
        m_int_part_color = clBlue;
        m_dot_color = clRed;
        m_frac_part_color = clBlue;
        m_exp10_color = clBlack;
		m_powersign_plus_color = clBlack;
        m_powersign_minus_color = clRed;
        m_power_color = clGreen;

        m_font_size = -14;
		m_font_size_super = -12;

		m_engine = new TCalculatorEngine;

		m_engine->OnModeChange = OnModeChange;
		m_engine->OnStackChange = OnStackChange;
		m_engine->OnError = OnError;

		m_updating = false;

		OnModeChange(this);

		CreateOperatorButtons();
}

__fastcall TFwCalcMainDlg::~TFwCalcMainDlg()
{
	delete m_engine;
}

void __fastcall TFwCalcMainDlg::CMDialogKey(TWMKey &key)
{
	switch(key.CharCode)
	{
		case VK_PRIOR:
		case VK_UP:
		m_engine->ProcessKey(TShiftState(), VK_UP);
		break;

		case VK_NEXT:
		case VK_DOWN:
		m_engine->ProcessKey(TShiftState(), VK_DOWN);
		break;

		case VK_END:
		m_engine->ProcessKey(TShiftState(), VK_END);
		break;

		case VK_HOME:
		m_engine->ProcessKey(TShiftState(), VK_HOME);
		break;

	}
}

void __fastcall TFwCalcMainDlg::OnOperatorClick(TObject *Sender)
{
int i;
	for(i=0;i<16 && m_op_buttons[i] != Sender;i++);
	if(i < 16)
		m_engine->ProcessOperator(m_op_action[i]);
}

void __fastcall TFwCalcMainDlg::OnAltInputClick(TObject *Sender)
{
TFormatButton *b = dynamic_cast<TFormatButton *>(Sender);

	if(!b) return;

	if(b == m_alt1)
	{
		if(b->Caption == "A")
			m_engine->ProcessChar('A');
		else
			m_engine->PushValueD(M_PI);
	}
	else if(b == m_alt2)
	{
		if(b->Caption == "B")
			m_engine->ProcessChar('B');
		else
			m_engine->PushValueD(M_E);
	}
	else if(b == m_alt3)
	{
		if(b->Caption == "C")
			m_engine->ProcessChar('C');
		else
			m_engine->PushValueD(6.62606896E-34);
	}
	else if(b == m_alt4)
	{
		if(b->Caption == "D")
			m_engine->ProcessChar('D');
		else
			m_engine->PushValueD(6.67428E-11);
	}
	else if(b == m_alt5)
	{
		if(b->Caption == "E")
			m_engine->ProcessChar('E');
		else
			m_engine->PushValueD(299792458.0);
	}
	else if(b == m_alt6)
		m_engine->ProcessChar('F');
}

void __fastcall TFwCalcMainDlg::OnError(TObject *Sender)
{
	StatusBar->Panels->Items[4]->Text = m_engine->LastError;
}


void TFwCalcMainDlg::CreateOperatorButtons()
{
int x,y;
	for(y=0;y<4;y++)
	{
		for(x=0;x<4;x++)
		{
		int index = y*4 + x;
		TFormatButton *b = new TFormatButton(this);

			m_op_buttons[index] = b;
			b->Parent = ButtonPanel;
			b->Left = 5 + x*(Num7Button->Width + 1);
			b->Top = Num7Button->Top + y*(Num7Button->Height + 1);
			b->Width = Num7Button->Width;
			b->Height = Num7Button->Height;
			b->OnClick = OnOperatorClick;
			b->ShowHint = true;

		}
	}

	m_alt1 = new TFormatButton(this);
	m_alt1->Parent = ButtonPanel;
	m_alt1->Left = STOButton->Left - STOButton->Width - 1;
	m_alt1->Top = STOButton->Top;
	m_alt1->Width = STOButton->Width;
	m_alt1->Height = STOButton->Height;
	m_alt1->OnClick = OnAltInputClick;
	m_alt1->ShowHint = true;

	m_alt2 = new TFormatButton(this);
	m_alt2->Parent = ButtonPanel;
	m_alt2->Left = Num7Button->Left - Num7Button->Width - 1;
	m_alt2->Top = Num7Button->Top;
	m_alt2->Width = Num7Button->Width;
	m_alt2->Height = Num7Button->Height;
	m_alt2->OnClick = OnAltInputClick;
	m_alt2->ShowHint = true;

	m_alt3 = new TFormatButton(this);
	m_alt3->Parent = ButtonPanel;
	m_alt3->Left = Num4Button->Left - Num4Button->Width - 1;
	m_alt3->Top = Num4Button->Top;
	m_alt3->Width = Num4Button->Width;
	m_alt3->Height = Num4Button->Height;
	m_alt3->OnClick = OnAltInputClick;
	m_alt3->ShowHint = true;

	m_alt4 = new TFormatButton(this);
	m_alt4->Parent = ButtonPanel;
	m_alt4->Left = Num1Button->Left - Num1Button->Width - 1;
	m_alt4->Top = Num1Button->Top;
	m_alt4->Width = Num1Button->Width;
	m_alt4->Height = Num1Button->Height;
	m_alt4->OnClick = OnAltInputClick;
	m_alt4->ShowHint = true;

	m_alt5 = new TFormatButton(this);
	m_alt5->Parent = ButtonPanel;
	m_alt5->Left = Num0Button->Left - Num0Button->Width - 1;
	m_alt5->Top = Num0Button->Top;
	m_alt5->Width = Num0Button->Width;
	m_alt5->Height = Num0Button->Height;
	m_alt5->OnClick = OnAltInputClick;
	m_alt5->ShowHint = true;

	m_alt6 = new TFormatButton(this);
	m_alt6->Parent = ButtonPanel;
	m_alt6->Left = EnterButton->Left - Num0Button->Width - 1;
	m_alt6->Top = EnterButton->Top;
	m_alt6->Width = Num0Button->Width;
	m_alt6->Height = Num0Button->Height;
	m_alt6->OnClick = OnAltInputClick;
	m_alt6->ShowHint = true;
}

eCalcLayout TFwCalcMainDlg::LayoutFromShift(TShiftState Shift)
{
bool ctrl = Shift.Contains(ssCtrl);
bool shift = Shift.Contains(ssShift);

	if(ctrl && !shift)
		return eLayoutComp;
	if(!ctrl && shift)
		return eLayoutSciAlt;

	return eLayoutNormal;
}

void TFwCalcMainDlg::AssignAltButtons()
{
	if(m_alt1 == NULL)
    	return;

	if(m_engine->BaseMode == eBaseHex)
	{
		m_alt1->Caption = "A";
		m_alt2->Caption = "B";
		m_alt3->Caption = "C";
		m_alt4->Caption = "D";
		m_alt5->Caption = "E";
		m_alt6->Caption = "F";
		m_alt1->Visible = true;
		m_alt2->Visible = true;
		m_alt3->Visible = true;
		m_alt4->Visible = true;
		m_alt5->Visible = true;
		m_alt6->Visible = true;
		m_alt1->Hint = "Enter heaxidecimal value A";
		m_alt2->Hint = "Enter heaxidecimal value B";
		m_alt3->Hint = "Enter heaxidecimal value C";
		m_alt4->Hint = "Enter heaxidecimal value D";
		m_alt5->Hint = "Enter heaxidecimal value E";
		m_alt6->Hint = "Enter heaxidecimal value F";

		NumDotButton->Visible = false;
		NumEEXButton->Visible = false;
		CHSButton->Visible = false;

		Num0Button->Visible = true;
		Num1Button->Visible = true;
		Num2Button->Visible = true;
		Num3Button->Visible = true;
		Num4Button->Visible = true;
		Num5Button->Visible = true;
		Num6Button->Visible = true;
		Num7Button->Visible = true;
		Num8Button->Visible = true;
		Num9Button->Visible = true;
	}
	else if(m_engine->BaseMode == eBaseDec)
	{
		m_alt1->Caption = "\\f{Symbol}p\\f";
		m_alt2->Caption = "\\Be\\b";
		m_alt3->Caption = "\\B\\Ih\\b";
		m_alt4->Caption = "\\BG\\b";
		m_alt5->Caption = "\\B\\Ic\\b";
		m_alt6->Caption = "\\f{Symbol}\\Ie\\f\\s0\\n";
		m_alt1->Visible = true;
		m_alt2->Visible = true;
		m_alt3->Visible = true;
		m_alt4->Visible = true;
		m_alt5->Visible = true;
		m_alt6->Visible = false;
		m_alt1->Hint = "Enter value PI";
		m_alt2->Hint = "Enter value e (base of the natural logarithm)";
		m_alt3->Hint = "Enter value of Planck's constant";
		m_alt4->Hint = "Enter value of Newtons gravitational constant";
		m_alt5->Hint = "Enter value of the speed of light in vacuum";
		m_alt6->Hint = "Enter heaxidecimal value F";

		NumDotButton->Visible = true;
		NumEEXButton->Visible = true;
		CHSButton->Visible = true;

		Num0Button->Visible = true;
		Num1Button->Visible = true;
		Num2Button->Visible = true;
		Num3Button->Visible = true;
		Num4Button->Visible = true;
		Num5Button->Visible = true;
		Num6Button->Visible = true;
		Num7Button->Visible = true;
		Num8Button->Visible = true;
		Num9Button->Visible = true;
	}
	else if(m_engine->BaseMode == eBaseOct)
	{
		m_alt1->Visible = false;
		m_alt2->Visible = false;
		m_alt3->Visible = false;
		m_alt4->Visible = false;
		m_alt5->Visible = false;
		m_alt6->Visible = false;

		NumDotButton->Visible = false;
		NumEEXButton->Visible = false;
		CHSButton->Visible = false;

		Num0Button->Visible = true;
		Num1Button->Visible = true;
		Num2Button->Visible = true;
		Num3Button->Visible = true;
		Num4Button->Visible = true;
		Num5Button->Visible = true;
		Num6Button->Visible = true;
		Num7Button->Visible = true;
		Num8Button->Visible = false;
		Num9Button->Visible = false;
	}
	else // binary
	{
		m_alt1->Visible = false;
		m_alt2->Visible = false;
		m_alt3->Visible = false;
		m_alt4->Visible = false;
		m_alt5->Visible = false;
		m_alt6->Visible = false;

		NumDotButton->Visible = false;
		NumEEXButton->Visible = false;
		CHSButton->Visible = false;

		Num0Button->Visible = true;
		Num1Button->Visible = true;
		Num2Button->Visible = false;
		Num3Button->Visible = false;
		Num4Button->Visible = false;
		Num5Button->Visible = false;
		Num6Button->Visible = false;
		Num7Button->Visible = false;
		Num8Button->Visible = false;
		Num9Button->Visible = false;
	}
	m_alt1->Invalidate();
	m_alt2->Invalidate();
	m_alt3->Invalidate();
	m_alt4->Invalidate();
	m_alt5->Invalidate();
	m_alt6->Invalidate();
}

void TFwCalcMainDlg::AssignLayout(eCalcLayout layout)
{
	if(m_current_layout == layout)
    	return;

	m_current_layout = layout;

	AssignAltButtons();

	switch(layout)
	{
		case eLayoutNormal:
		{
		char *labels[16] = {"x\\S2", "ln", "Log", "1/x",
						  "\\f{Symbol}Ö\\fx", "e\\SX", "10\\SX", "y\\SX",
						  "sin", "cos", "tan", "x\\f{Symbol}«\\fy",
						  "hsin", "hcos", "htan", "RND"
						 };
		char *hints[16] = {"x squared [Enter *]", "natural logarithm [l]", "base 10 logarighm", "1 divided by x [o]",
						   "square-root [q]", "exponential function [i l]", "10 power x function", "y power x function [^]",
						   "sinus function [s]", "cosinus function [c]", "tangent function [t]", "Swap X with y operator [\\]",
						   "hyperbolic sinus function [h s]", "hyperbolic cosinus function [h c]", "hyperbolic tangent function [h t]", "Random number"
						  };
		eCalcOperator actions[16] = {eOpX2,eOpLN, eOpLOG, wOp1divX,
								  eOpSqrt, eOpeX, eOp10X, eOpyX,
								  eOpSin, eOpCos, eOpTan, eOpSwapXY,
								  eOpSinh, eOpCosh, eOpTanh, eOPRND};
		int i;
			for(i=0;i<16;i++)
			{
				m_op_buttons[i]->Caption = labels[i];
				m_op_buttons[i]->Hint = hints[i];
				m_op_action[i] = actions[i];
			}
		}
		break;

		case eLayoutSciAlt:
		{
		char *labels[] = {"\\f{Wingdings}è\\fRAD", "\\f{Wingdings}è\\fDEG", "\\f{Wingdings}è\\fGRAD", "%",
						  "Frac", "Int", "abs", "\\f{Symbol}\\Bs\\f",
						  "sin\\S-1", "cos\\S-1", "tan\\S-1", "x\\f{Symbol}«\\fy",
						  "hsin\\S-1", "hcos\\S-1", "htan\\S-1", "x!"};
		char *hints[16] = {"Convert to RAD", "Convert to DEG", "Convert to GRAD", "x percent of y operator",
						   "fractional part of number", "integer part of number", "norm of value", "calc mean and stddev of all values on stack y=mean x=stddev",
						   "inverse sinus function [i s]", "inverse cosinus function [i c]", "inverse tangent function [i t]", "Swap X with y operator [\\]",
						   "inverse hyperbolic sinus function [i h s]", "inverse hyperbolic cosinus function [i h c]", "inverse hyperbolic tangent function [i h t]", "factorial operator [!]"
						  };
		eCalcOperator actions[16] = {eOpToRAD,eOpToDEG, eOpToGrad, eOpPercent,
								  eOpFrac, eOpeInt, eOpAbs, eOpMeanStddev,
								  eOpArcSin, eOpArcCos, eOpArcTan, eOpSwapXY,
								  eOpArcSinh, eOpArcCosh, eOpArcTanh, eOpFAC};
		int i;
			for(i=0;i<16;i++)
			{
				m_op_buttons[i]->Caption = labels[i];
				m_op_buttons[i]->Hint = hints[i];
				m_op_action[i] = actions[i];
			}
		}
		break;

		case eLayoutComp:
		{
		char *labels[] = {"","","","",
						  "LSH", "RSH", "MOD", "BIT",
						  "AND", "OR", "NOT", "XOR",
						  "","","",""
						 };
		char *hints[16] = {"", "", "", "",
						   "left shift operator [<]", "right shift operator [>]", "y modulus x operator [m]", "set bit # operator",
						   "bitwise AND operator [&]", "birwise OR operator [|]", "bitwise NOT operator [~]", "bitwise XOR operator [x]",
						   "", "", "", ""
						  };
		eCalcOperator actions[16] = {eOpNone,eOpNone, eOpNone, eOpNone,
								  eOpLSH, eOpRSH, eOpMOD, eOpBIT,
								  eOpAND, eOpOR, eOpNOT, eOpXOR,
								  eOpNone, eOpNone, eOpNone, eOpNone};
		int i;
			for(i=0;i<16;i++)
			{
				m_op_buttons[i]->Caption = labels[i];
				m_op_buttons[i]->Hint = hints[i];
				m_op_action[i] = actions[i];
			}
		}
		break;
	}
int i;
	for(i=0;i<16;i++)
	{
	TFormatButton *b = m_op_buttons[i];
		if(b->Caption == "")
			b->Visible = false;
		else
			b->Visible = true;
		b->Invalidate();

	}
}


void __fastcall TFwCalcMainDlg::FormKeyPress(TObject *Sender, char &Key)
{
	if(!m_key_processed)
		m_engine->ProcessChar(Key);
}

//---------------------------------------------------------------------------
void __fastcall TFwCalcMainDlg::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	// Reset key processed flag
	m_key_processed = false;

	// Mark key as processed
	m_key_processed = true;

	// Process key
	switch(Key)
	{
		default:
		m_key_processed = false;	// Default handler set the processed flag to false
		break;

		case VK_BACK:
		case VK_DELETE:
		case VK_ESCAPE:
		m_engine->ProcessKey(Shift, Key);
		break;

		case VK_DECIMAL:
		m_engine->EnterDecimalSeperator();
		break;

		//case VK_ENTER:
		case VK_RETURN:
		m_engine->ProcessKey(Shift, Key);
		break;

		case VK_ADD:
		{
			if(Shift.Contains(ssShift))
			{
				if(m_engine->SignificantDigits < 19)
					m_engine->SignificantDigits++;
			}
			else
				m_engine->ProcessChar('+');
		}
		break;

		case VK_SUBTRACT:
		{
			if(Shift.Contains(ssShift))
			{
				if(m_engine->SignificantDigits > 0)
					m_engine->SignificantDigits--;
			}
			else
				m_engine->ProcessChar('-');
		}
		break;

		case 'h':
		case 'H':
		if(Shift.Contains(ssCtrl))
			m_engine->SetBaseMode(eBaseHex);
		else
			m_key_processed = false;
		break;

		case 'o':
		case 'O':
		if(Shift.Contains(ssCtrl))
			m_engine->SetBaseMode(eBaseOct);
		else
			m_key_processed = false;
		break;

		case 'd':
		case 'D':
		if(Shift.Contains(ssCtrl))
			m_engine->SetBaseMode(eBaseDec);
		else if(Shift.Contains(ssShift))
			m_engine->SetTrigMode(eTrigDeg);
		else
			m_key_processed = false;
		break;

		case 'G':
		if(Shift.Contains(ssShift))
			m_engine->SetTrigMode(eTrigGrad);
		else
			m_key_processed = false;
		break;

		case 'R':
		if(Shift.Contains(ssShift))
			m_engine->SetTrigMode(eTrigRad);
		else
			m_key_processed = false;
		break;

		case 'b':
		case 'B':
		if(Shift.Contains(ssCtrl))
			m_engine->SetBaseMode(eBaseBin);
		else
			m_key_processed = false;
		break;

		case VK_CONTROL:
		AssignLayout(LayoutFromShift(Shift));
		break;

		case VK_SHIFT:
		AssignLayout(LayoutFromShift(Shift));
		break;

		case VK_F1:
		if(Shift.Contains(ssCtrl) || Shift.Contains(ssShift)) m_engine->Recall(0); else m_engine->Store(0);
		break;

		case VK_F2:
		if(Shift.Contains(ssCtrl) || Shift.Contains(ssShift)) m_engine->Recall(1); else m_engine->Store(1);
		break;

		case VK_F3:
		if(Shift.Contains(ssCtrl) || Shift.Contains(ssShift)) m_engine->Recall(2); else m_engine->Store(2);
		break;

		case VK_F4:
		if(Shift.Contains(ssCtrl) || Shift.Contains(ssShift)) m_engine->Recall(3); else m_engine->Store(3);
		break;

		case VK_F5:
		if(Shift.Contains(ssCtrl) || Shift.Contains(ssShift)) m_engine->Recall(4); else m_engine->Store(4);
		break;

		case VK_F6:
		if(Shift.Contains(ssCtrl) || Shift.Contains(ssShift)) m_engine->Recall(5); else m_engine->Store(5);
		break;

		case VK_F7:
		if(Shift.Contains(ssCtrl) || Shift.Contains(ssShift)) m_engine->Recall(6); else m_engine->Store(6);
		break;

		case VK_F8:
		if(Shift.Contains(ssCtrl) || Shift.Contains(ssShift)) m_engine->Recall(7); else m_engine->Store(7);
		break;

		case VK_F9:
		if(Shift.Contains(ssCtrl) || Shift.Contains(ssShift)) m_engine->Recall(8); else m_engine->Store(8);
		break;

		case VK_F10:
		if(Shift.Contains(ssCtrl) || Shift.Contains(ssShift)) m_engine->Recall(9); else m_engine->Store(9);
		break;
	}
	PaintBox->Invalidate();
}

void __fastcall TFwCalcMainDlg::OnModeChange(TObject *Sender)
{
	m_updating = true;

		switch(m_engine->TrigMode)
		{
				case eTrigRad: StatusBar->Panels->Items[2]->Text = "RAD"; ToggleTrigButton->Caption = "Rad"; break;
				case eTrigDeg: StatusBar->Panels->Items[2]->Text = "DEG"; ToggleTrigButton->Caption = "Deg"; break;
				case eTrigGrad: StatusBar->Panels->Items[2]->Text = "GRAD"; ToggleTrigButton->Caption = "Grad"; break;
		}

		switch(m_engine->BaseMode)
		{
				case eBaseHex: StatusBar->Panels->Items[3]->Text = "HEX"; break;
				case eBaseDec: StatusBar->Panels->Items[3]->Text = "DEC"; break;
				case eBaseOct: StatusBar->Panels->Items[3]->Text = "OCT"; break;
				case eBaseBin: StatusBar->Panels->Items[3]->Text = "BIN"; break;
		}
		if(m_engine->RequestInverse)
			StatusBar->Panels->Items[0]->Text = "INV";
		else
			StatusBar->Panels->Items[0]->Text = "";

		if(m_engine->RequestHyperbolic)
			StatusBar->Panels->Items[1]->Text = "HYP";
		else
			StatusBar->Panels->Items[1]->Text = "";


//		StatusBar->Panels->Items[4]->Text = m_last_error;
	AssignAltButtons();
	m_updating = false;
	PaintBox->Invalidate();
}

void __fastcall TFwCalcMainDlg::OnStackChange(TObject *Sender)
{
	PaintBox->Invalidate();
}

//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::FormKeyUp(TObject *Sender, WORD &Key,
	  TShiftState Shift)
{
	switch(Key)
	{
		case VK_CONTROL:
		AssignLayout(LayoutFromShift(Shift));
		break;

		case VK_SHIFT:
		AssignLayout(LayoutFromShift(Shift));
		break;

	}
	m_key_processed = false;
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TFwCalcMainDlg::FormResize(TObject *Sender)
{
        PaintBox->Invalidate();
}
//---------------------------------------------------------------------------//---------------------------------------------------------------------------//---------------------------------------------------------------------------//---------------------------------------------------------------------------//---------------------------------------------------------------------------//---------------------------------------------------------------------------//---------------------------------------------------------------------------//---------------------------------------------------------------------------//---------------------------------------------------------------------------
void __fastcall TFwCalcMainDlg::HandleEnterNum(TObject *Sender)
{
TSpeedButton *b = dynamic_cast<TSpeedButton *>(Sender);
	if(b)
		m_engine->ProcessChar(*(b->Caption.c_str()));
}
//---------------------------------------------------------------------------//---------------------------------------------------------------------------//---------------------------------------------------------------------------//---------------------------------------------------------------------------//---------------------------------------------------------------------------//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------




void TFwCalcMainDlg::ParseValue(AnsiString txt, AnsiString &tlc, AnsiString &tuc)
{
AnsiString tmp = txt.c_str();

AnsiString num, power;

char *p = tmp.c_str();
char *e;

        e = strchr(p, 'E');
        if(e)
        {
				*e++ = 0;
                power = e;
				num = p;
                if(power == "")
                        power = "0";
        }
        else
        {
                num = p;
				power = "";
		}

		tlc = num;
		tuc = power;
}

void TFwCalcMainDlg::ParseDecNumber(AnsiString number, AnsiString &nn, AnsiString &dn, AnsiString &en)
{
	dn = "";
	en = "";
	nn = "";

AnsiString tmp = number.UpperCase().Trim().c_str();
char *p = tmp.c_str();
char *pd, *pe;
char *e = p;
	while(*e)
	{
		if(*e == ',')
			*e = '.';
		e++;
	}

	pd = strchr(p, '.');
	pe = strchr(p, 'E');

	if(pe)
	{
		en = (pe+1);
		*pe = 0;
		if(en == "")
        	en = "0";
	}
	if(pd)
	{
		dn = (pd+1);
		*pd = 0;
	}
    nn = p;
}

int TFwCalcMainDlg::CalcWidthOfDecNumber(TCanvas *cv, AnsiString number)
{
AnsiString nn, dn, en;

	ParseDecNumber(number, nn, dn, en);

int width = 0;

	if(en != "")
	{
		cv->Font->Size = m_font_size_super;
		width += cv->TextWidth(en);
		cv->Font->Size = m_font_size;
		width += cv->TextWidth(" 10");
	}
	cv->Font->Size = m_font_size;

	if(dn != "")
	{
	char sd[2] = " ";
		sd[0] = m_engine->DecimalChar;
		width += cv->TextWidth(sd);
		width += cv->TextWidth(dn);
	}
char sign = '+';
	if(nn.SubString(1,1) == '-')
	{
		sign = '-';
		nn = nn.SubString(2, nn.Length()-1);
	}
	width += cv->TextWidth(nn);
int gs = nn.Length() / 3;
	if(gs*3 == nn.Length())
    	gs--;
	width += gs * cv->TextWidth(" ") / 3;
	if(sign == '-')
    	width += cv->TextWidth("-");

	return width;
}

void TFwCalcMainDlg::PaintDecNumber(TCanvas *cv, int x, int y, AnsiString number)
{
AnsiString nn, dn, en;

	ParseDecNumber(number, nn, dn, en);

	char sign = '+';
	if(nn.SubString(1,1) == '-')
	{
		sign = '-';
		nn = nn.SubString(2, nn.Length()-1);
	}

	// Set default font size
	cv->Font->Size = m_font_size;

	// calc seperator width
int sw = cv->TextWidth(" ") / 3;

	// move to start position
	cv->MoveTo(x, y);

	// if negative write '-'
	if(sign == '-')
	{
		cv->Font->Color = m_minus_sign_color;
		cv->TextOut(cv->PenPos.x, cv->PenPos.y, "-");
	}
	// paint int part
	cv->Font->Color = m_int_part_color;
int gs = nn.Length() / 3;
	if(gs*3 == nn.Length())
    	gs--;
	// write first group
int fgl = nn.Length() - gs*3;
	cv->TextOut(cv->PenPos.x, cv->PenPos.y, nn.SubString(1, fgl));
	nn = nn.SubString(fgl+1, nn.Length()-fgl);
int i;
	for(i=0;i<gs;i++)
	{
		cv->MoveTo(cv->PenPos.x+sw, cv->PenPos.y);
	AnsiString gt = nn.SubString(1, 3);
    	nn = nn.SubString(4, nn.Length()-3);
		cv->TextOut(cv->PenPos.x, cv->PenPos.y, gt);
	}

	if(dn != "")
	{
	char sd[2] = " ";
		sd[0] = m_engine->DecimalChar;
		cv->Font->Color = m_dot_color;
		cv->TextOut(cv->PenPos.x, cv->PenPos.y, sd);
		cv->Font->Color = m_frac_part_color;
		cv->TextOut(cv->PenPos.x, cv->PenPos.y, dn);
	}
	if(en != "")
	{
	char fc = *(en.c_str());
		if(fc == '-' || fc == '+')
			en = en.SubString(2, en.Length()-1);

		cv->Font->Color = m_exp10_color;
		cv->TextOut(cv->PenPos.x, cv->PenPos.y, " 10");

		// switch to power font size
		cv->Font->Size = m_font_size_super;

		// draw power sign if required
	int y_off = cv->PenPos.y;
		if(fc == '-')
		{
			cv->Font->Color = m_powersign_minus_color;
			cv->TextOut(cv->PenPos.x, y_off-2, "-");
		}
		cv->Font->Color = m_power_color;
		cv->TextOut(cv->PenPos.x, y_off-2, en);
	}
}


void __fastcall TFwCalcMainDlg::PaintBoxPaint(TObject *Sender)
{
TRect r = TRect(0,0,PaintBox->Width, PaintBox->Height);
TCanvas *cv = PaintBox->Canvas;
	// Paint background
	cv->FillRect(r);
	cv->TextFlags = 0;
	cv->Font->Style = TFontStyles() << fsBold;
	cv->Font->Name = "Courier New";

	SetBkMode(cv->Handle, TRANSPARENT);

int lh = cv->TextHeight("X");
int y_off = r.Height() - lh;
int index = 0;

	while(y_off + lh >= 0)
	{
	// Determine number to write
	AnsiString txt = m_engine->RegisterValue[index].UpperCase();

		if(txt != "")
		{
			if(txt == "ERR")
			{
			AnsiString err_text = AnsiString("ERROR - ") + m_engine->LastError;
				cv->Font->Size = m_font_size;
				cv->Font->Color = clRed;
				cv->TextOut(r.Right - 10 - cv->TextWidth(err_text), y_off, err_text);
			}
			else
			{
				if(m_engine->BaseMode == eBaseDec)
				{
				int tw = CalcWidthOfDecNumber(cv, txt);
					PaintDecNumber(cv, r.Right - 10 - tw, y_off, txt);
				}
				else
				{
					cv->Font->Size = m_font_size;

					cv->TextOut(r.Right-cv->TextWidth(txt)-10, y_off, txt);
				}
			}
		}

		y_off -= lh;
		index++;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::Exit1Click(TObject *Sender)
{
		Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::setDigitsClick(TObject *Sender)
{
TMenuItem *mi = dynamic_cast<TMenuItem *>(Sender);

		if(mi)
		{
		wchar_t *p = mi->Caption.c_str();
				if(*p == '&')   p++;
		int digits = AnsiString(p).ToInt();
			   //	m_display_format = AnsiString("%.") + digits + "Lg";

		}
		PaintBox->Invalidate();
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::AutoDigits1Click(TObject *Sender)
{
//		m_display_format = "%Lg";
		PaintBox->Invalidate();
}
//---------------------------------------------------------------------------

void TFwCalcMainDlg::UpdateMemPopupMenu(TPopupMenu *m)
{
int i;
		for(i=0;i<10;i++)
		{
				m->Items->Items[i]->Caption = AnsiString(i) + ":   " + m_engine->PeekMemory(i);
		}

}

void __fastcall TFwCalcMainDlg::StoreMemButtonClick(TObject *Sender)
{
TPoint p;
		UpdateMemPopupMenu(STOPopupMenu);
		GetCursorPos(&p);
		STOPopupMenu->Popup(p.x, p.y);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::RecallMemButtonClick(TObject *Sender)
{
TPoint p;
		UpdateMemPopupMenu(RCLPopupMenu);
		GetCursorPos(&p);
		RCLPopupMenu->Popup(p.x, p.y);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::StoMemClick(TObject *Sender)
{
TMenuItem *mi = dynamic_cast<TMenuItem *>(Sender);

	if(mi == NULL)
		return;

	m_engine->Store(mi->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::RclMemClick(TObject *Sender)
{
TMenuItem *mi = dynamic_cast<TMenuItem *>(Sender);

	if(mi == NULL)
		return;

	m_engine->Recall(mi->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::About1Click(TObject *Sender)
{
		AboutDlg->Show();
}
//---------------------------------------------------------------------------


void __fastcall TFwCalcMainDlg::EnterButtonClick(TObject *Sender)
{
	m_engine->ProcessKey(TShiftState(), VK_RETURN);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::CLRButtonClick(TObject *Sender)
{
	m_engine->ProcessKey(TShiftState(), VK_DELETE);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::SetHexButtonClick(TObject *Sender)
{
	m_engine->BaseMode = eBaseHex;
	AssignLayout(eLayoutComp);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::SetDecButtonClick(TObject *Sender)
{
	m_engine->BaseMode = eBaseDec;
	AssignLayout(eLayoutNormal);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::SetOctButtonClick(TObject *Sender)
{
	m_engine->BaseMode = eBaseOct;
	AssignLayout(eLayoutComp);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::SetBinButtonClick(TObject *Sender)
{
	m_engine->BaseMode = eBaseBin;
	AssignLayout(eLayoutComp);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::ToggleTrigButtonClick(TObject *Sender)
{
TPoint p;
	GetCursorPos(&p);
	SelectDegMenu->Checked = m_engine->TrigMode == eTrigDeg;
	SelectRadMenu->Checked = m_engine->TrigMode == eTrigRad;
	SelectGradMenu->Checked = m_engine->TrigMode == eTrigGrad;

	TrigPopupMenu->Popup(p.x, p.y);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::NormalLayoutMenuClick(TObject *Sender)
{
	AssignLayout(eLayoutNormal);
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::SciAlt1LayoutMenuClick(TObject *Sender)
{
	AssignLayout(eLayoutSciAlt);
}
//---------------------------------------------------------------------------


void __fastcall TFwCalcMainDlg::ComputationalLayoutMenuClick(TObject *Sender)
{
	AssignLayout(eLayoutComp);	
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::FormShow(TObject *Sender)
{
	// Update layout
	AssignAltButtons();
	AssignLayout(eLayoutNormal);	
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::CHSButtonClick(TObject *Sender)
{
	m_engine->ProcessOperator(eOpCHS);	
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::BackButtonClick(TObject *Sender)
{
	m_engine->ProcessKey(TShiftState(), VK_BACK);	
}
//---------------------------------------------------------------------------


void __fastcall TFwCalcMainDlg::SelectDegMenuClick(TObject *Sender)
{
	m_engine->TrigMode = eTrigDeg;	
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::SelectRadMenuClick(TObject *Sender)
{
	m_engine->TrigMode = eTrigRad;	
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::SelectGradMenuClick(TObject *Sender)
{
	m_engine->TrigMode = eTrigGrad;	
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::Copy1Click(TObject *Sender)
{
		Clipboard()->AsText = m_engine->RegisterValue[0].UpperCase();
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::Paste1Click(TObject *Sender)
{
AnsiString value = Clipboard()->AsText;
char *p = value.c_str();
	while(*p)
	{
		m_engine->ProcessChar(*p);
		p++;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::SetDigitsMenuClick(TObject *Sender)
{
TMenuItem *mi = dynamic_cast<TMenuItem *>(Sender);
	if(mi)
	{
		if(mi->Caption == "Auto" || mi->Caption == "&Auto")
			m_engine->SignificantDigits = 0;
		else
		{
		char tmp[3] = "  ";
		char *p = AnsiString(mi->Caption).c_str();
		char *e = tmp;
			while(*p && e < tmp+2)
			{
				if(*p != '&')	*e++ = *p++;
				else            p++;
			}
			m_engine->SignificantDigits = AnsiString(tmp).Trim().ToInt();
		}
	}
}
//---------------------------------------------------------------------------



void __fastcall TFwCalcMainDlg::Keyboard1Click(TObject *Sender)
{
	KeyboardShorcutDlg->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFwCalcMainDlg::NumDotButtonClick(TObject *Sender)
{
TSpeedButton *b = dynamic_cast<TSpeedButton *>(Sender);
	if(b)
		m_engine->EnterDecimalSeperator();	
}


