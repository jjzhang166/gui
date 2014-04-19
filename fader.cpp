#ifdef __WAND__
target[name[fader.o] type[object] dependency[comctl32;external] dependency[gdi32;external]platform[;Windows]]
#endif

#include "fader.h"

#define _WIN32_IE 0x5500
#include <windows.h>
#include <commctrl.h>
#include <herbs/stringsys/stringsys.h>
#include <herbs/floatformat/floatformat.h>

#include <cstdio>

void Gui::Fader::init()
	{
	INITCOMMONCONTROLSEX a;
	a.dwSize=sizeof(a);
	a.dwICC=ICC_WIN95_CLASSES;
	InitCommonControlsEx(&a);
	}

Gui::Fader::Fader(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent
	,Fadefunc& f):
	WindowSystem(gui_obj,TRACKBAR_CLASS,style_0,style_1|TBS_NOTICKS|TBS_BOTH,parent)
	,m_f(f)
	{
	SendMessage((HWND)handle,TBM_SETRANGEMIN, 0,0);
	SendMessage((HWND)handle,TBM_SETRANGEMAX,1,0x7fff);
	valueSet(0);
	}

double Gui::Fader::valueGet() const
	{
	int v=SendMessage((HWND)handle,TBM_GETPOS,0,0);
	return m_f.y(double(v)/0x7fff);
	}

void Gui::Fader::valueSet(double y)
	{
	double x=m_f.x(y);
	SendMessage((HWND)handle,TBM_SETPOS,1,(LPARAM)(x*0x7fff + 0.5));
	}
	
size_t Gui::Fader::onEvent(uint32_t event_type,size_t param_0,size_t param_1)
	{
	if(event_type==MessagePaint)
		{
		WindowSystem::onEvent(event_type,param_0,param_1);
		HDC hdc=GetDC((HWND)handle);
		RECT knob;
		SendMessage((HWND)handle,TBM_GETTHUMBRECT,0,(LPARAM)(&knob));
		double v=valueGet();
		
		Herbs::String str_out{Herbs::FloatFormat<7>(v)};
		auto size=sizeClientGet();
		RECT r={2,knob.bottom,size.x,size.y};
		FillRect(hdc,&r,GetSysColorBrush(COLOR_BTNFACE));
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 2, knob.bottom
			,Herbs::bufferSysPtr(Herbs::stringsys(str_out)), str_out.length()
			); 
		ReleaseDC((HWND)handle,hdc);
		}
	return WindowSystem::onEvent(event_type,param_0,param_1);
	}