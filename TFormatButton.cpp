#include <vcl.h>
#pragma hdrstop

#include "TFormatButton.h"
#include <Themes.hpp>
#include <memory>

//---------------------------------------------------------------------------

__fastcall TFormatButton::TFormatButton(TComponent *Owner)
	: TGraphicControl(Owner)
{
	ControlStyle = ControlStyle >> csDoubleClicks;
}

__fastcall TFormatButton::~TFormatButton()
{

}

void __fastcall TFormatButton::CMMouseEnter(TMessage &message)
{
	m_mouse_in_control = true;
	Invalidate();
}

void __fastcall TFormatButton::CMMouseLeave(TMessage &message)
{
	m_mouse_in_control = false;
    Invalidate();
}

void __fastcall TFormatButton::MouseUp(TMouseButton button, TShiftState Shift, int X, int Y)
{
	TGraphicControl::MouseUp(button, Shift, X, Y);
	m_button_pressed = false;
	Invalidate();
}
void __fastcall TFormatButton::MouseDown(TMouseButton button, TShiftState Shift, int X, int Y)
{
	TGraphicControl::MouseDown(button, Shift, X, Y);
	m_button_pressed = true;
	Invalidate();
}

void __fastcall TFormatButton::Paint(void)
{
TRect r(0, 0, Width, Height);
TThemedButton button;
TThemedElementDetails details;

	if(ThemeControl(this))
	{
	bool paint_on_glass = ThemeServices()->ThemesEnabled && !ComponentState.Contains(csDesigning);
		if(paint_on_glass)
		{
		TCustomForm *f = GetParentForm(this);
			paint_on_glass = (f != NULL && f->GlassFrame->FrameExtended() &&  f->GlassFrame->IntersectsControl(this));
		}

		if(paint_on_glass)
		{
			Canvas->Brush->Color = clBlack;
			Canvas->FillRect(ClientRect);
        }
		else
			PerformEraseBackground(this, Canvas->Handle);

		if(!Enabled)
			button = tbPushButtonPressed;
		else
		{
			if(m_mouse_in_control)
				button = tbPushButtonHot;
			else
		  		button = tbPushButtonNormal;
		}
		if(Enabled && m_button_pressed)
			button = ttbButtonPressed;
		if(!Enabled)
        	button = ttbButtonDisabled;

	TRect pr = ClientRect;
		details = ThemeServices()->GetElementDetails(button);
		ThemeServices()->DrawElement(Canvas->Handle, details, pr);
	  	pr = ThemeServices()->ContentRect(Canvas->Handle, details, pr);


	}
	else
	{
		Canvas->Brush->Color = clLime;
		Canvas->FillRect(r);
	}

	// Calculate the width of the formated text
	Canvas->Font->Assign(Font);
std::auto_ptr<TFont> saved_font(new TFont);
	saved_font->Assign(Canvas->Font);
AnsiString text = Caption;
int w = 0;                         
char *p = text.c_str();
	while(*p)
	{
		switch(*p)
		{
			case '\\':
			p++;
			if(*p == '\\')
			{
			char tmp[2] = " ";
				tmp[0] = *p;
				w += Canvas->TextWidth(tmp);
			}
			else if(*p == 's' || *p == 'S')	// sub/super script
				Canvas->Font->Size = 3*saved_font->Size / 4;
			else if(*p == 'n')	// normal script script
				Canvas->Font->Size = saved_font->Size;
			else if(*p == 'B')	// bold on
				Canvas->Font->Style = Canvas->Font->Style << fsBold;
			else if(*p == 'b')	// bold off
				Canvas->Font->Style = Canvas->Font->Style >> fsBold;
			else if(*p == 'I')	// Italic on
				Canvas->Font->Style = Canvas->Font->Style << fsItalic;
			else if(*p == 'i')	// italic off
				Canvas->Font->Style = Canvas->Font->Style >> fsItalic;
			else if(*p == 'f')
			{
			AnsiString font = saved_font->Name;
				if(p[1] == '{')
				{
					p+=2;
				char *e = strchr(p, '}');
					if(e)
					{
						*e = 0;
						font = p;
						p = e;
						*e = '}';
					}
				}
				Canvas->Font->Name = font;
			}
/*			else if(*p == 'c')
			{
				if(p[1] == '{')
				{
					p+=2;
				char *e = strchr(p, '}');
					if(e)
						p = e;
				}
			}*/
			break;

			default:
			{
			char tmp[2] = " ";
				tmp[0] = *p;
				w += Canvas->TextWidth(tmp);
			}
			break;
		}
		if(*p) p++;
	}

	SetBkMode(Canvas->Handle, TRANSPARENT);
	Canvas->Font->Assign(saved_font.get());

	// Render formated test
	text = Caption;

	// move to start position
int lh = Canvas->TextHeight("X");
int y_off = (Height - lh)/2;
TColor font_color = Font->Color;
	Canvas->MoveTo((Width - w)/2, y_off);

	p = text.c_str();
	while(*p)
	{
		switch(*p)
		{
			case '\\':
			p++;
			if(*p == '\\')
			{
			char tmp[2] = " ";
				tmp[0] = *p;
				Canvas->TextOut(Canvas->PenPos.x, Canvas->PenPos.y, tmp); 
				w += Canvas->TextWidth(tmp);
			}
			else if(*p == 's')  // sub script
			{
				Canvas->Font->Size = 3*saved_font->Size / 4;
				Canvas->MoveTo(Canvas->PenPos.x, y_off + lh/2);
			}
			else if(*p == 'S')	// super script
			{
				Canvas->Font->Size = 3*saved_font->Size / 4;
				Canvas->MoveTo(Canvas->PenPos.x, y_off);
			}
			else if(*p == 'n')	// normal script script
			{
				Canvas->Font->Size = saved_font->Size;
				Canvas->MoveTo(Canvas->PenPos.x, y_off);
            }
			else if(*p == 'B')	// bold on
				Canvas->Font->Style = Canvas->Font->Style << fsBold;
			else if(*p == 'b')	// bold off
				Canvas->Font->Style = Canvas->Font->Style >> fsBold;
			else if(*p == 'I')	// Italic on
				Canvas->Font->Style = Canvas->Font->Style << fsItalic;
			else if(*p == 'i')	// italic off
				Canvas->Font->Style = Canvas->Font->Style >> fsItalic;
			else if(*p == 'f')
			{
			AnsiString font = saved_font->Name;
				if(p[1] == '{')
				{
					p+=2;
				char *e = strchr(p, '}');
					if(e)
					{
						*e = 0;
						font = p;
						p = e;
						*e = '}';
					}
				}
				Canvas->Font->Name = font;
			}
/*			else if(*p == 'c')
			{
            TColor color = font_color;
				if(p[1] == '{')
				{
					p+=2;
				char *e = strchr(p, '}');
					if(e)
					{
						*e = 0;
						color = StringToColor(p);
						p = e;
						*e = '}';
					}
				}
				Canvas->Font->Color = Color;
			} */
			break;

			default:
			{
			char tmp[2] = " ";
				tmp[0] = *p;
				Canvas->TextOut(Canvas->PenPos.x, Canvas->PenPos.y, tmp); 
				w += Canvas->TextWidth(tmp);
			}
			break;
		}
		if(*p) p++;
	}


	// Cleanup
	Canvas->Font->Assign(saved_font.get());

}




#pragma package(smart_init)
