#include <vcl.h>
#pragma hdrstop
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <math.h>

#include "CalculatorEngine.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString g_error = "";

int _matherrl (struct _exceptionl *a)
{
	g_error = AnsiString("ERROR: ") + a->name + " - ";

        switch(a->type)
        {
				case DOMAIN:    g_error = g_error + "Domain"; break;
				case SING:      g_error = g_error + "Singularity"; break;
				case OVERFLOW:  g_error = g_error + "Overflow"; break;
				case UNDERFLOW: g_error = g_error + "Underflow"; break;
				case TLOSS:     g_error = g_error + "TLoss"; break;
        }
//        FwCalcMainDlg->SetLastError(error);

        return 1;
}


// ---------------------------------------------------------------------------
// ---- class TRPNStackValue member implementation

__fastcall TRPNStackValue::TRPNStackValue()
{
	m_double = 0.0;
	m_ulong = 0;
}

void TRPNStackValue::Set(TRPNStackValue *v)
{
	m_double = v->GetD();
	m_ulong = v->GetI();
}

void TRPNStackValue::SetD(long double d)
{
	m_double = d;
	try
	{
		m_ulong = (unsigned long long)d;
	}
	catch(...)
	{
		m_ulong = 0xFFFFFFFFFFFFFFFF;
	}
}

void TRPNStackValue::SetI(unsigned long long ui)
{
	m_double = (double)ui;
	m_ulong = ui;
}

void TRPNStackValue::Set(AnsiString value, eBaseMode base)
{
	try
	{
		switch(base)
		{
			case eBaseHex:
			{
				// somehow handle > 32 bit values
				if(value.Length() > 8)
				{
				AnsiString vhigh = value.SubString(1, value.Length()-8);
				AnsiString vlow = value.SubString(value.Length()-8, value.Length());
					// Handle high 32 bits first
				unsigned long hv = 0;
				unsigned long lv = 0;
				unsigned long long x;
				unsigned long tmp;
					sscanf(vhigh.c_str(), "%X", &hv);
					sscanf(vlow.c_str(), "%X", &lv);
					x = (((unsigned long long)hv) << 32) | (unsigned long long)lv;
					SetI(x);
				}
				else
				{
				unsigned long x;
					sscanf(value.c_str(), "%X", &x);
					SetI(x);
				}
			}
			break;

			case eBaseDec:
			{
			long double d;
			AnsiString tmp = value.UpperCase().c_str();
			char *p = tmp.c_str();
				if(*p == 'E')
					tmp = AnsiString("1.0") + tmp;
				p = tmp.c_str();
				while(*p)
				{
					if(*p == ',')
						*p = '.';
					p++;
				}
				SetD(_atold(tmp.c_str()));
			}
			break;

			case eBaseOct:
			{
			int x;
				sscanf(value.c_str(), "%O", &x);
				SetI(x);
			}
			break;

			case eBaseBin:
			{
			unsigned long long mask = 1;
			unsigned long long x = 0;
			char *p = value.c_str();
			char *e = p + value.Length()-1;
				while(e >= p)
				{
					if(*e == '1')
						x |= mask;
					mask <<= 1;
					e--;
				}
				SetI(x);
			}
			break;
		}
	}
	catch(Exception &ex)
	{
		ShowMessage(ex.Message);
	}
	catch( ... )
	{
    	ShowMessage("Generic Exception");
	}
}


long double TRPNStackValue::GetD()
{
	return m_double;
}

unsigned long long TRPNStackValue::GetI()
{
	return m_ulong;
}

// ---------------------------------------------------------------------------
// ---- class TRPNStackValue member implementation

__fastcall TRPNStack::TRPNStack()
{

}

void TRPNStack::Push(AnsiString value, eBaseMode base)
{
TRPNStackValue *nv = new TRPNStackValue;
	nv->Set(value, base);
	Add(nv);
}

void TRPNStack::Push(TRPNStackValue *v)
{
TRPNStackValue *nv = new TRPNStackValue;
	nv->Set(v);
	Add(nv);
}

void TRPNStack::PushD(long double d)
{
std::auto_ptr<TRPNStackValue> tmp(new TRPNStackValue);
	tmp->SetD(d);
	Push(tmp.get());
}

void TRPNStack::PushI(unsigned long long ui)
{
std::auto_ptr<TRPNStackValue> tmp(new TRPNStackValue);
	tmp->SetI(ui);
	Push(tmp.get());
}


bool TRPNStack::Peek(int position, TRPNStackValue *v)
{
int index = Count - position - 1;	// inverse order

	// limit check
	if(index < 0)		return false;
	if(index >= Count)  return false;

TRPNStackValue *sv = (TRPNStackValue *)Items[index];
	v->Set(sv);

	return true;
}

bool TRPNStack::PeekD(int position, long double &d)
{
int index = Count - position - 1;	// inverse order

	// limit check
	if(index < 0)		return false;
	if(index >= Count)  return false;

TRPNStackValue *sv = (TRPNStackValue *)Items[index];
	d = sv->GetD();

	return true;
}

bool TRPNStack::PeekI(int position, unsigned long long &ui)
{
int index = Count - position - 1;	// inverse order

	// limit check
	if(index < 0)		return false;
	if(index >= Count)  return false;

TRPNStackValue *sv = (TRPNStackValue *)Items[index];
	ui = sv->GetI();

	return true;
}

bool TRPNStack::Pop(TRPNStackValue *d)
{
	if(Count == 0)
		return false;
int index = Count-1;
TRPNStackValue *sv = (TRPNStackValue * )Items[index];
	d->Set(sv);
	Delete(index);

	return true;
}

bool TRPNStack::PopD(long double &d)
{
	if(Count == 0)
		return false;
int index = Count-1;
TRPNStackValue *sv = (TRPNStackValue *)Items[index];
	d = sv->GetD();
	Delete(index);

	return true;
}

bool TRPNStack::PopI(unsigned long long &ui)
{
	if(Count == 0)
		return false;
int index = Count-1;
TRPNStackValue *sv = (TRPNStackValue *)Items[index];
	ui = sv->GetI();
	Delete(index);

	return true;
}



// ---------------------------------------------------------------------------
// ---- class TCalculatorEngine member implementation

__fastcall TCalculatorEngine::TCalculatorEngine()
{
int i;
	for(i=0;i<10;i++)
	{
		m_memory[i] = new TRPNStackValue;
		m_memory[i]->SetD(0.0);
	}

	m_stack = new TRPNStack;
	m_editor = "";

	m_base_mode = eBaseDec;
	m_trig_mode = eTrigDeg;

	// detect the current decimal character active on the system
	m_decimal_char = '.';

	m_request_sto = false;
	m_request_rcl = false;
	m_request_inverse = false;
	m_request_hyperbolic = false;

	m_last_key_was_e = false;



AnsiString tmp = AnsiString(1.1);
	if(tmp.Pos(","))
		m_decimal_char = ',';
}

__fastcall TCalculatorEngine::~TCalculatorEngine()
{
int i;
	for(i=0;i<10;i++)
    	delete m_memory[i];


	delete m_stack;
}

bool TCalculatorEngine::SetError(AnsiString err)
{
	m_last_error = err;
	if(OnError)
		OnError(this);

	return false;
}


AnsiString TCalculatorEngine::RPNStackValueToText(TRPNStackValue *v)
{
	switch(m_base_mode)
	{
		case eBaseHex:
		{
		unsigned long hv = (v->GetI() >> 32) & 0xFFFFFFFF;
		unsigned long lv = v->GetI() & 0xFFFFFFFF;
		AnsiString out;
			if(hv)
            	return AnsiString().sprintf("%X", hv) + AnsiString().sprintf("%08X", lv);
			return AnsiString().sprintf("%X", lv);
		}
		break;

		case eBaseDec:
		{
		AnsiString format = "%128";
			if(SignificantDigits)
				format = format + "." + SignificantDigits;
			format = format + "LG";

			return AnsiString().sprintf(format.c_str(), v->GetD()).Trim();
		}
		break;

		case eBaseOct:
		{
		char tmp[2000];
			ultoa(v->GetI(), tmp, 8);
			return AnsiString(tmp);
		}
		break;

		case eBaseBin:
		{
		char tmp[2000];
			ultoa(v->GetI(), tmp, 2);
			return AnsiString(tmp);
		}
		break;
	}
	return "";
}

bool TCalculatorEngine::Store(int slot)
{
	if(slot < 0 || slot >= 10)
		return false;

	if(m_editor != "")
		m_memory[slot]->Set(m_editor, m_base_mode);
	else
	{
		if(m_stack->Count)
		{
			m_stack->Peek(0, m_memory[slot]);        	
		}
		else
			return SetError("Stack Empty");
	}


	return true;
}

bool TCalculatorEngine::Recall(int slot)
{
	if(slot < 0 || slot >= 10)
		return false;

	RealizeStack();

	m_stack->Push(m_memory[slot]);

	if(OnStackChange)
		OnStackChange(this);

	return true;
}

AnsiString TCalculatorEngine::PeekMemory(int slot)
{
	if(slot < 0 || slot >= 10)
		return "";

	return  RPNStackValueToText(m_memory[slot]);
}

// --- property handlers
void __fastcall TCalculatorEngine::SetTrigMode(eTrigMode m)
{
	m_trig_mode = m;
	if(OnModeChange)
		OnModeChange(this);
}

void __fastcall TCalculatorEngine::SetBaseMode(eBaseMode m)
{
	if(m_base_mode != m)
	{
		RealizeStack();

		m_base_mode = m;
		if(OnModeChange)
			OnModeChange(this);
	}
}

void __fastcall TCalculatorEngine::SetRequestInverse(bool f)
{
	if(m_request_inverse != f)
	{
		m_request_inverse = f;
    	if(OnModeChange)
			OnModeChange(this);
	}
}
void __fastcall TCalculatorEngine::SetRequestHyperbolic(bool f)
{
	if(m_request_hyperbolic != f)
	{
		m_request_hyperbolic = f;
		if(OnModeChange)
			OnModeChange(this);
	}
}

void __fastcall TCalculatorEngine::SetSignificantDigits(int n)
{
	if(m_significant_digits != n)
	{
		m_significant_digits = n;

		if(OnStackChange)
			OnStackChange(this);
	}

}


AnsiString __fastcall TCalculatorEngine::GetRegisterValue(int position)
{
std::auto_ptr<TRPNStackValue> v(new TRPNStackValue);

	// if m_editor != "" then the editor is register 0 else register 0 is first on the stack
	if(m_editor != "")
	{
    	// handle zero register seperately
		if(position == 0)
			return m_editor;

		// else default handling
		if(!m_stack->Peek(position-1, v.get()))
        	return "";
		return RPNStackValueToText(v.get());
	}
	// else no value being edited
	if(!m_stack->Peek(position, v.get()))
    	return "";
	return RPNStackValueToText(v.get());
}

bool TCalculatorEngine::RealizeStack()
{
	if(m_editor != "")
	{
		m_stack->Push(m_editor, m_base_mode);
		m_editor = "";
		return true;
	}
	return false;
}

long double TCalculatorEngine::EnsureRAD(long double d)
{
	if(TrigMode == eTrigDeg)
		return d * M_PI / 180.0;
	if(TrigMode == eTrigGrad)
		return d * M_PI / 200.0;

	return d;
}

long double TCalculatorEngine::EnsureTrigMode(long double rad)
{
	switch(TrigMode)
	{
		case eTrigDeg:
		return rad * 180.0 / M_PI;

		case eTrigRad:
		return rad;

		case eTrigGrad:
		return rad * 200.0 / M_PI;
	}
	SetError("Unknown trig mode");
	return 0.0;
}

bool TCalculatorEngine::PopRegister(TRPNStackValue *v)
{
	RealizeStack();

	if(m_stack->Count == 0)
    	return false;		// Not enough values on the stack

	return m_stack->Pop(v);
}

void TCalculatorEngine::PushValueD(long double d)
{
	RealizeStack();
	m_stack->PushD(d);

	if(OnStackChange)
		OnStackChange(this);
}

void TCalculatorEngine::PushValueI(unsigned long long ui)
{
	RealizeStack();
	m_stack->PushI(ui);

	if(OnStackChange)
		OnStackChange(this);
}


void TCalculatorEngine::PushKeyToEditor(int key)
{
char tmp[2] = " ";
	tmp[0] = key;
	m_editor = m_editor + AnsiString(tmp).UpperCase();
	if(OnStackChange)
		OnStackChange(this);
}

void TCalculatorEngine::ProcessChar(char key)
{
	// Reset math error interface
	g_error = "";	// Clear error flags
	SetError("");
	if(m_editor == "ERR")
		m_editor = "";

	if(key < '0' || key > '9')
	{
		m_request_sto = false;
		m_request_rcl = false;
	}

	switch(key)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		if(m_request_sto)
		{
			Store(key - '0');
			m_request_sto = false;
		}
		else if(m_request_rcl)
		{
			Recall(key - '0');
			m_request_rcl = false;
		}
		else
		{
			if(m_base_mode == eBaseOct && key >= '8')	return;
			if(m_base_mode == eBaseOct && key >= '2')	return;
			PushKeyToEditor(key);
		}
		break;

		case 'A':
		case 'a':
		case 'B':
		case 'b':
		case 'C':
		case 'c':
		case 'D':
		case 'd':
		case 'F':
		case 'f':
		if(m_base_mode == eBaseHex)
			PushKeyToEditor(key);
		else if(key == 'c' && m_base_mode == eBaseDec)
		{
			if(m_request_inverse && m_request_hyperbolic) ProcessOperator(eOpArcCosh);
			if(!m_request_inverse && m_request_hyperbolic) ProcessOperator(eOpCosh);
			if(m_request_inverse && !m_request_hyperbolic) ProcessOperator(eOpArcCos);
			if(!m_request_inverse && !m_request_hyperbolic) ProcessOperator(eOpCos);
		}
		break;

		case 'E':
		case 'e':
		if(m_base_mode == eBaseHex || m_base_mode == eBaseDec)
			PushKeyToEditor(key);
		break;

		case '.':
		case ',':
		if(key == m_decimal_char)
		{
			if(m_editor.Pos(".") == 0 && m_editor.Pos(",") == 0)
				PushKeyToEditor(m_decimal_char);
		}
		break;

		case '+': ProcessOperator(eOpPlus); break;
		case '-':
		{
			if(m_last_key_was_e)
				ProcessOperator(eOpCHS);
			else
				ProcessOperator(eOpMinus);
			m_last_key_was_e = false;
		}
		break;
		case '*': ProcessOperator(eOpMul); break;
		case '/': ProcessOperator(eOpDiv); break;
		case '%': ProcessOperator(eOpPercent); break;
		case '&': ProcessOperator(eOpAND); break;
		case '|': ProcessOperator(eOpOR); break;
		case '~': ProcessOperator(eOpNOT); break;
		case '<': ProcessOperator(eOpLSH); break;
		case '>': ProcessOperator(eOpRSH); break;
		case 'm': ProcessOperator(eOpMOD); break;
		case 'x': ProcessOperator(eOpXOR); break;
		case '^': ProcessOperator(eOpyX); break;
		case 'q': ProcessOperator(eOpSqrt); break;


		case 'i': RequestInverse = !RequestInverse; break;
		case 'h': RequestHyperbolic = !RequestHyperbolic; break;

		case 's':
		if(m_request_inverse && m_request_hyperbolic) ProcessOperator(eOpArcSinh);
		if(!m_request_inverse && m_request_hyperbolic) ProcessOperator(eOpSinh);
		if(m_request_inverse && !m_request_hyperbolic) ProcessOperator(eOpArcSin);
		if(!m_request_inverse && !m_request_hyperbolic) ProcessOperator(eOpSin);
		break;

		case 't':
		if(m_request_inverse && m_request_hyperbolic) ProcessOperator(eOpArcTanh);
		if(!m_request_inverse && m_request_hyperbolic) ProcessOperator(eOpTanh);
		if(m_request_inverse && !m_request_hyperbolic) ProcessOperator(eOpArcTan);
		if(!m_request_inverse && !m_request_hyperbolic) ProcessOperator(eOpTan);
		break;

		case 'p': PushValueD(M_PI); break;

		case 'r': ProcessOperator(eOpSqrt); break;
		case 'o': ProcessOperator(wOp1divX); break;
		case '!': ProcessOperator(eOpFAC); break;
		case '\\': ProcessOperator(eOpSwapXY); break;

		case 'l': if(m_request_inverse) ProcessOperator(eOpeX); else ProcessOperator(eOpLN); break;
	}

	if(key == 'e' || key == 'E')
		m_last_key_was_e = true;
	else
		m_last_key_was_e = false;

	// if keypress was different from yperbolic or inverse request then reset request states
	if(!(key == 'i' || key == 'h'))
	{
		RequestInverse = false;
		RequestHyperbolic = false;
	}

	if(g_error != "")
		SetError(g_error);
}

bool TCalculatorEngine::EnterDecimalSeperator()
{
	ProcessChar(m_decimal_char);
}



void TCalculatorEngine::ProcessKey(TShiftState shift, int key)
{
	g_error = "";	// Clear error flags
	SetError("");
	if(m_editor == "ERR")
		m_editor = "";

	switch(key)
	{
		case VK_RETURN:	// Push value to stack
		if(m_editor != "")
			RealizeStack();
		else
		{
			// Dublicate stack value
		std::auto_ptr<TRPNStackValue> v(new TRPNStackValue);
			if(m_stack->Peek(0, v.get()))
				m_stack->Push(v.get());
		}
		break;

		case VK_END: ProcessOperator(eOpCHS); break;
		case VK_HOME: ProcessOperator(eOpSwapXY); break;
		case VK_ESCAPE:ProcessOperator(eOpCHS); break;

		case VK_DELETE:
		{
		std::auto_ptr<TRPNStackValue> v(new TRPNStackValue);
			if(m_editor != "")
				m_editor = "";
			else
				m_stack->Pop(v.get());
		}
		break;

		case VK_BACK:
		if(m_editor == "" && m_stack->Count)
		{
		std::auto_ptr<TRPNStackValue> v(new TRPNStackValue);
			m_stack->Pop(v.get());
			m_editor = RPNStackValueToText(v.get());
			if(m_editor == "+INF" || m_editor == "-INF")
            	m_editor = "";
		}
		if(m_editor != "")
			m_editor = m_editor.SubString(1, m_editor.Length()-1);
		break;

		case VK_UP:
		m_request_sto = true;
		break;

		case VK_DOWN:
		m_request_rcl = true;
		break;


	}
	if(OnStackChange)
		OnStackChange(this);

	if(g_error != "")
		SetError(g_error);
}

bool TCalculatorEngine::CheckRequiredVarCount(int count, AnsiString error_message)
{
int stack_size = m_stack->Count;
	if(m_editor != "")
		stack_size++;

	if(count > stack_size)
		return SetError(error_message);

	return true;
}

bool TCalculatorEngine::RequireBase(eBaseMode mode)
{
	if(m_base_mode != mode)
		return SetError("Operator not working with current base");

	return true;
}

bool TCalculatorEngine::ProcessOperator(eCalcOperator op)
{
int xx = sizeof(long double);

	try
	{
	std::auto_ptr<TRPNStackValue> v1(new TRPNStackValue);
	std::auto_ptr<TRPNStackValue> v2(new TRPNStackValue);
	std::auto_ptr<TRPNStackValue> result(new TRPNStackValue);

		g_error = "";	// Clear error flags
		SetError("");
		if(m_editor == "ERR")
			m_editor = "";

		switch(op)
		{
			case eOpPlus:
			if(!CheckRequiredVarCount(2, "+ requires two values")) return false;
			PopRegister(v1.get());
			PopRegister(v2.get());
			if(m_base_mode == eBaseDec) {result->SetD(v2->GetD() + v1->GetD());	m_stack->Push(result.get()); }
			else      					{result->SetI(v2->GetI() + v1->GetI());	m_stack->Push(result.get()); }
			break;

			case eOpMinus:
			if(!CheckRequiredVarCount(2, "- requires two values")) return false;
			PopRegister(v1.get());
			PopRegister(v2.get());
			if(m_base_mode == eBaseDec) {result->SetD(v2->GetD() - v1->GetD());	m_stack->Push(result.get()); }
			else      					{result->SetI(v2->GetI() - v1->GetI());	m_stack->Push(result.get()); }
			break;

			case eOpDiv:
			if(!CheckRequiredVarCount(2, "/ requires two values")) return false;
			PopRegister(v1.get());
			PopRegister(v2.get());
			if(m_base_mode == eBaseDec) {result->SetD(v2->GetD() / v1->GetD());	m_stack->Push(result.get()); }
			else      					{result->SetI(v2->GetI() / v1->GetI());	m_stack->Push(result.get()); }
			break;

			case eOpMul:
			if(!CheckRequiredVarCount(2, "* requires two values")) return false;
			PopRegister(v1.get());
			PopRegister(v2.get());
			if(m_base_mode == eBaseDec)
			{
			long double d1 = v1->GetD();
			long double d2 = v2->GetD();

				result->SetD(d1 * d2);
				m_stack->Push(result.get());
			}
			else      					{result->SetI(v2->GetI() * v1->GetI());	m_stack->Push(result.get()); }
			break;

			case eOpMeanStddev:
			if(!CheckRequiredVarCount(1, "minimum 1 value required")) return false;
			if(!RequireBase(eBaseDec))	return false;
			{
				RealizeStack();
			int i;
			long double mean = 0.0;
				for(i=0;i<m_stack->Count;i++)
				{
					m_stack->Peek(i,v1.get());
					mean += v1->GetD();
				}
				mean /= m_stack->Count;
			long double stddev = 0.0;
				if(m_stack->Count > 2)
				{
					for(i=0;i<m_stack->Count;i++)
					{
					  m_stack->Peek(i,v1.get());

						stddev += (v1->GetD() - mean) * (v1->GetD() - mean);
					}
					stddev /= m_stack->Count;
					stddev = sqrtl(stddev);
				}
				m_stack->Clear();
				m_stack->PushD(mean);
				m_stack->PushD(stddev);
			}
			break;

			case eOpCHS:
			if(!RequireBase(eBaseDec))	return false;
			if(m_editor != "")
			{
			int pe = m_editor.Pos("E");
				if(pe)
				{
				AnsiString prev = m_editor.SubString(1, pe);
				AnsiString postv = m_editor.SubString(pe+1, m_editor.Length());
					if(postv.SubString(1,1) == "-")
						m_editor = prev + postv.SubString(2, postv.Length());
					else
						m_editor = prev + "-" + postv;
				}
				else
				{
					if(m_editor.SubString(1,1) == "-")
						m_editor = m_editor.SubString(2, m_editor.Length()-1);
					else
						m_editor = AnsiString("-") + m_editor;
				}

			}
			else
			{
				if(PopRegister(v1.get()))
				{
					v1->SetD(-v1->GetD());
					PushRegister(v1.get());
				}
				else
				 m_editor = "-";
			}
			break;

			case eOPRND:
			PushValueD((long double)(random(RAND_MAX) / (long double)RAND_MAX));
			break;

			case eOpX2:
			if(!CheckRequiredVarCount(1, "x2 requires 1 values")) return false;
			PopRegister(v1.get());
			if(m_base_mode == eBaseDec) {result->SetD(v1->GetD() * v1->GetD());	m_stack->Push(result.get()); }
			else                        {result->SetI(v1->GetI() * v1->GetI());	m_stack->Push(result.get()); }
			break;

			case eOpLN:
			if(!CheckRequiredVarCount(1, "ln requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(logl(v1->GetD()));
			m_stack->Push(result.get());
			break;

			case eOpLOG:
			if(!CheckRequiredVarCount(1, "log10 requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(log10l(v1->GetD()));
			m_stack->Push(result.get());
			break;

			case wOp1divX:
			if(!CheckRequiredVarCount(1, "1/x requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(1.0 / v1->GetD());
			m_stack->Push(result.get());
			break;

			case eOpSqrt:
			if(!CheckRequiredVarCount(1, "sqrt requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(sqrtl(v1->GetD()));
			m_stack->Push(result.get());
			break;

			case eOpeX:
			if(!CheckRequiredVarCount(1, "e^x requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(expl(v1->GetD()));
			m_stack->Push(result.get());
			break;

			case eOp10X:
			if(!CheckRequiredVarCount(1, "10^x requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(powl(10.0, v1->GetD()));
			m_stack->Push(result.get());
			break;

			case eOpyX:
			if(!CheckRequiredVarCount(2, "y^x requires 2 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			PopRegister(v2.get());
			result->SetD(powl(v2->GetD(), v1->GetD()));
			m_stack->Push(result.get());
			break;

			case eOpSin:
			if(!CheckRequiredVarCount(1, "sin requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(sinl(EnsureRAD(v1->GetD())));
			m_stack->Push(result.get());
			break;

			case eOpCos:
			if(!CheckRequiredVarCount(1, "cos requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(cosl(EnsureRAD(v1->GetD())));
			m_stack->Push(result.get());
			break;

			case eOpTan:
			if(!CheckRequiredVarCount(1, "tan requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(tanl(EnsureRAD(v1->GetD())));
			m_stack->Push(result.get());
			break;

			case eOpSinh:
			if(!CheckRequiredVarCount(1, "sinh requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(sinhl(v1->GetD()));
			m_stack->Push(result.get());
			break;

			case eOpCosh:
			if(!CheckRequiredVarCount(1, "cosh requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(coshl(v1->GetD()));
			m_stack->Push(result.get());
			break;

			case eOpTanh:
			if(!CheckRequiredVarCount(1, "tanh requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(tanhl(v1->GetD()));
			m_stack->Push(result.get());
			break;

			case eOpArcSin:
			if(!CheckRequiredVarCount(1, "asin requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(EnsureTrigMode(asinl(v1->GetD())));
			m_stack->Push(result.get());
			break;

			case eOpArcCos:
			if(!CheckRequiredVarCount(1, "acos requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(EnsureTrigMode(acosl(v1->GetD())));
			m_stack->Push(result.get());
			break;

			case eOpArcTan:
			if(!CheckRequiredVarCount(1, "atan requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(EnsureTrigMode(atanl(v1->GetD())));
			m_stack->Push(result.get());
			break;

			case eOpArcSinh:
			if(!CheckRequiredVarCount(1, "asinh requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD( logl( v1->GetD() + sqrtl( v1->GetD() * v1->GetD() + 1.0 ) )  );
			m_stack->Push(result.get());
			break;

			case eOpArcCosh:
			if(!CheckRequiredVarCount(1, "acosh requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD( logl( v1->GetD() + sqrtl( v1->GetD() * v1->GetD() - 1.0 ) )  );
			m_stack->Push(result.get());
			break;

			case eOpArcTanh:
			if(!CheckRequiredVarCount(1, "atanh requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD( logl( (1.0 + v1->GetD()) / (1.0 - v1->GetD()) ) / 2.0 );
			m_stack->Push(result.get());
			break;

			case eOpToRAD:
			if(!CheckRequiredVarCount(1, "to rad requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(EnsureRAD(v1->GetD()));
			m_stack->Push(result.get());
			break;

			case eOpToDEG:
			if(!CheckRequiredVarCount(1, "to deg requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(EnsureRAD(v1->GetD()) * 180.0 / M_PI);
			m_stack->Push(result.get());
			break;

			case eOpToGrad:
			if(!CheckRequiredVarCount(1, "to grad requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(EnsureRAD(v1->GetD()) * 200.0 / M_PI);
			m_stack->Push(result.get());
			break;


			case eOpFAC:
			if(!CheckRequiredVarCount(1, "x! requires 1 values")) return false;
			{
			int n = 0;
				PopRegister(v1.get());
				if(m_base_mode == eBaseDec) n = (int)(v1->GetD());
				else						n = v1->GetI();

				if(n < 0 || n > 1754)
					return SetError("x! limit error 0 <= x <= 1754");
			long double x = 1;
			int i;
				for(i=1;i<=n;i++)
					x *= (long double)i;
				result->SetD(x);
				m_stack->Push(result.get());
			}
			break;

			case eOpPercent:
			if(!CheckRequiredVarCount(2, "% requires 2 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			PopRegister(v2.get());
			result->SetD(v2->GetD() * v1->GetD() / 100.0);
			m_stack->Push(result.get());
			break;

			case eOpFrac:
			if(!CheckRequiredVarCount(1, "FRAC requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD(v1->GetD() - (long long)v1->GetD());
			m_stack->Push(result.get());
			break;

			case eOpeInt:
			if(!CheckRequiredVarCount(1, "INT requires 1 values")) return false;
			if(!RequireBase(eBaseDec))	return false;
			PopRegister(v1.get());
			result->SetD((long long)(v1->GetD()));
			m_stack->Push(result.get());
			break;

			case eOpAbs:
			if(m_base_mode != eBaseDec)	return true;	// always unsigned
			if(!CheckRequiredVarCount(1, "FRAC requires 1 values")) return false;
			PopRegister(v1.get());
			if(v1->GetD() < 0.0)
				result->SetD(-v1->GetD());
			else
				result->SetD(v1->GetD());
			m_stack->Push(result.get());
			break;

			case eOpSwapXY:
			if(!CheckRequiredVarCount(2, "x<>y requires 2 values")) return false;
			PopRegister(v1.get());
			PopRegister(v2.get());
			m_stack->Push(v1.get());
			m_stack->Push(v2.get());
			break;

			case eOpLSH:
			if(!CheckRequiredVarCount(1, "LSH requires 1 values")) return false;
			{
				PopRegister(v1.get());
				result->SetI(v1->GetI() << 1);
				m_stack->Push(result.get());
			}
			break;

			case eOpRSH:
			if(!CheckRequiredVarCount(1, "RSH requires 1 values")) return false;
			{
				PopRegister(v1.get());
				result->SetI(v1->GetI() >> 1);
				m_stack->Push(result.get());
			}
			break;

			case eOpMOD:
			if(!CheckRequiredVarCount(2, "MOD requires 2 values")) return false;
			{
				PopRegister(v1.get());
				PopRegister(v2.get());
				result->SetI(v2->GetI() % v1->GetI());
				m_stack->Push(result.get());
			}
			break;

			case eOpBIT:
			if(!CheckRequiredVarCount(1, "BIT requires 1 values")) return false;
			{
				PopRegister(v1.get());
				result->SetI(1 << v1->GetI());
				m_stack->Push(result.get());
			}
			break;

			case eOpAND:
			if(!CheckRequiredVarCount(2, "AND requires 2 values")) return false;
			{
				PopRegister(v1.get());
				PopRegister(v2.get());
				result->SetI(v2->GetI() & v1->GetI());
				m_stack->Push(result.get());
			}
			break;

			case eOpOR:
			if(!CheckRequiredVarCount(2, "AND requires 2 values")) return false;
			{
				PopRegister(v1.get());
				PopRegister(v2.get());
				result->SetI(v2->GetI() | v1->GetI());
				m_stack->Push(result.get());
			}
			break;

			case eOpNOT:
			if(!CheckRequiredVarCount(1, "NOT requires 1 value")) return false;
			{
				PopRegister(v1.get());
				result->SetI(~v1->GetI());
				m_stack->Push(result.get());
			}
			break;

			case eOpXOR:
			if(!CheckRequiredVarCount(2, "XOR requires 2 values")) return false;
			{
				PopRegister(v1.get());
				PopRegister(v2.get());
				result->SetI(v2->GetI() ^ v1->GetI());
				m_stack->Push(result.get());
			}
			break;


			default:
			m_last_error = "Unknown Operator";
			if(OnError) OnError(this);
			return false;
		}
		if(OnStackChange)
			OnStackChange(this);

		if(g_error != "")
		{
			SetError(g_error);
			m_editor = "ERR";

			return false;
		}

		return true;
	}
	catch(Exception &ex)
	{
		m_editor = "ERR";
		return SetError(ex.Message);
	}
	catch( ... )
	{
    	m_editor = "ERR";
    	return SetError("Generic Exception");
	}
}
