//---------------------------------------------------------------------------

#ifndef TFormatButtonH
#define TFormatButtonH

//---------------------------------------------------------------------------

class TFormatButton : public TGraphicControl
{
private:
	bool m_mouse_in_control;
	bool m_button_pressed;


	bool MouseInControl();

protected:
void __fastcall CMMouseEnter(TMessage &message);
void __fastcall CMMouseLeave(TMessage &message);

BEGIN_MESSAGE_MAP
  MESSAGE_HANDLER(CM_MOUSEENTER, TMessage, CMMouseEnter)
  MESSAGE_HANDLER(CM_MOUSELEAVE, TMessage,CMMouseLeave);
END_MESSAGE_MAP(TGraphicControl)

DYNAMIC void __fastcall MouseUp(TMouseButton button, TShiftState Shift, int X, int Y);
DYNAMIC void __fastcall MouseDown(TMouseButton button, TShiftState Shift, int X, int Y);


public:
	__fastcall TFormatButton(TComponent *Owner);
	__fastcall ~TFormatButton();

	virtual void __fastcall Paint(void);

__published:
	__property Caption;
	__property Font;

	__property OnClick;


};




#endif
