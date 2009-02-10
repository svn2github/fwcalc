#ifndef CalculatorEngineH
#define CalculatorEngineH

// -----------------------------------------------------------------------------
// ---- various defines and enumeration types

#define RPNSTACK_MAX    50

enum eTrigMode {eTrigRad, eTrigDeg, eTrigGrad};
enum eBaseMode {eBaseHex, eBaseDec, eBaseOct, eBaseBin};

enum eCalcOperator {eOpNone,
					eOpPlus, eOpMinus, eOpDiv, eOpMul,	// Two value operators
					eOpCHS,								// Change sign
					eOPRND,								// random number
					eOpMeanStddev,						// calc mean and stddev of stack
					eOpX2, eOpLN, eOpLOG, wOp1divX,
					eOpSqrt, eOpeX, eOp10X, eOpyX,
					eOpSin, eOpCos, eOpTan,
					eOpSinh, eOpCosh, eOpTanh,
					eOpToRAD,eOpToDEG, eOpToGrad, eOpFAC, eOpPercent,
					eOpFrac, eOpeInt, eOpAbs, eOpSwapXY,
					eOpArcSin, eOpArcCos, eOpArcTan,
					eOpArcSinh, eOpArcCosh, eOpArcTanh,
					// comp operators
					eOpLSH, eOpRSH, eOpMOD, eOpBIT,
					eOpAND, eOpOR, eOpNOT, eOpXOR
					};


// -----------------------------------------------------------------------------
// ---- TRPNStackValue definition
class TRPNStackValue : public TObject
{
private:
	long double m_double;			// double presition value (used for decimal calculations
	unsigned long long m_ulong;	// unsigned 64 bit integer used for bin/oct and hex calculations

public:
	__fastcall TRPNStackValue();

	void Set(TRPNStackValue *v);

	void SetD(long double d);
	void SetI(unsigned long long ui);
	void Set(AnsiString text, eBaseMode base);

	long double GetD();
	unsigned long long GetI();
};



// -----------------------------------------------------------------------------
// ---- TRPNStack definition
class TRPNStack : public TObjectList
{
private:

public:
		__fastcall TRPNStack();

		void Push(AnsiString value, eBaseMode base);
		void Push(TRPNStackValue *v);
		void PushD(long double d);
		void PushI(unsigned long long ui);

		bool Peek(int position, TRPNStackValue *v);
		bool PeekD(int position, long double &d);
		bool PeekI(int position, unsigned long long &ui);
		bool Pop(TRPNStackValue *v);
		bool PopD(long double &d);
		bool PopI(unsigned long long &ui);
};





class TCalculatorEngine : public TObject
{
protected:
	TRPNStack *m_stack;

	bool m_request_sto;
	bool m_request_rcl;
	bool m_request_inverse;
	bool m_request_hyperbolic;
	AnsiString m_editor;

	eTrigMode m_trig_mode;
	eBaseMode m_base_mode;

	int m_decimal_char;

	int m_significant_digits;

	AnsiString m_last_error;

	// memory
	TRPNStackValue *m_memory[10];

	// events
	TNotifyEvent f_on_stack_change;
	TNotifyEvent f_on_mode_change;
	TNotifyEvent f_on_error;

protected:
AnsiString RPNStackValueToText(TRPNStackValue *v);
void PushKeyToEditor(int key);

bool PopRegister(TRPNStackValue *v);
inline bool PushRegister(TRPNStackValue *v) {m_stack->Push(v);};
bool CheckRequiredVarCount(int count, AnsiString error_message);
bool RequireBase(eBaseMode mode);
bool RealizeStack();
long double EnsureRAD(long double d);
long double EnsureTrigMode(long double d);

bool SetError(AnsiString err);

public:
	__fastcall TCalculatorEngine();
	__fastcall ~TCalculatorEngine();

	// Memory handling
	bool Store(int slot);
	bool Recall(int slot);
	AnsiString PeekMemory(int slot);

	// Interface handlers
	void ProcessChar(char key);
	void ProcessKey(TShiftState shift, int key);
	bool ProcessOperator(eCalcOperator op);

	void PushValueD(long double d);
	void PushValueI(unsigned long long ui);

	// property handlers
	void __fastcall SetTrigMode(eTrigMode m);
	void __fastcall SetBaseMode(eBaseMode m);
	AnsiString __fastcall GetRegisterValue(int position);

	void __fastcall SetRequestInverse(bool f);
	void __fastcall SetRequestHyperbolic(bool f);

	void __fastcall SetSignificantDigits(int n);

	// properties
	__property eTrigMode TrigMode = {read=m_trig_mode, write=SetTrigMode};
	__property eBaseMode BaseMode = {read=m_base_mode, write=SetBaseMode};

	__property bool RequestInverse = {read=m_request_inverse, write=SetRequestInverse};
	__property bool RequestHyperbolic = {read=m_request_hyperbolic, write=SetRequestHyperbolic};

	__property int SignificantDigits = {read=m_significant_digits, write=SetSignificantDigits};

	__property AnsiString RegisterValue[int position] = {read=GetRegisterValue};

	__property AnsiString LastError = {read=m_last_error};

	// Events
	__property TNotifyEvent OnStackChange = {read=f_on_stack_change, write=f_on_stack_change};
	__property TNotifyEvent OnModeChange  = {read=f_on_mode_change, write=f_on_mode_change};
	__property TNotifyEvent OnError = {read=f_on_error, write=f_on_error};




};



#endif
