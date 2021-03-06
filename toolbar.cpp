#ifdef __WAND__
target[name[toolbar.o] type[object] dependency[comctl32;external] platform[;Windows]]
#endif

#include "toolbar.h"

#define _WIN32_IE 0x5500
#include <windows.h>
#include <commctrl.h>
#include <herbs/stringsys/stringsys.h>

void Gui::Toolbar::init()
	{
	INITCOMMONCONTROLSEX a;
	a.dwSize=sizeof(a);
	a.dwICC=ICC_WIN95_CLASSES;
	InitCommonControlsEx(&a);
	}

Gui::Toolbar::Toolbar(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent):
	WindowSystem(gui_obj,TOOLBARCLASSNAME,style_0,style_1|TBSTYLE_LIST,parent)
	{}

Gui::Toolbar& Gui::Toolbar::buttonAdd(const char_t* text,uint32_t cmdid)
	{
	TBBUTTON button;
	Herbs::BufferSys text_out=Herbs::stringsys(text);
	button.iBitmap=I_IMAGENONE;
	button.idCommand=cmdid;
	button.fsState=TBSTATE_ENABLED;
	button.fsStyle=TBSTYLE_BUTTON|BTNS_AUTOSIZE;
	button.dwData=(DWORD_PTR)this;
	button.iString=(INT_PTR)( (charsys_t*)Herbs::bufferSysPtr(text_out) );
	SendMessage((HWND)handle,TB_BUTTONSTRUCTSIZE,sizeof(TBBUTTON),0);
	SendMessage((HWND)handle,TB_ADDBUTTONS,1,(LPARAM)&button);
	SendMessage((HWND)handle,TB_AUTOSIZE,0,0);
	return *this;
	}

void Gui::Toolbar::toggleStateSet(uint32_t cmdid,bool state)
	{
	SendMessage((HWND)handle,TB_CHECKBUTTON,cmdid,state);
	}
	
Gui::Toolbar& Gui::Toolbar::toggleAdd(const char_t* text,uint32_t cmdid)
	{
	TBBUTTON button;
	Herbs::BufferSys text_out=Herbs::stringsys(text);
	button.iBitmap=I_IMAGENONE;
	button.idCommand=cmdid;
	button.fsState=TBSTATE_ENABLED;
	button.fsStyle=TBSTYLE_BUTTON|BTNS_AUTOSIZE|BTNS_CHECK;
	button.dwData=(DWORD_PTR)this;
	button.iString=(INT_PTR)( (charsys_t*)Herbs::bufferSysPtr(text_out) );
	SendMessage((HWND)handle,TB_BUTTONSTRUCTSIZE,sizeof(TBBUTTON),0);
	SendMessage((HWND)handle,TB_ADDBUTTONS,1,(LPARAM)&button);
	SendMessage((HWND)handle,TB_AUTOSIZE,0,0);
	return *this;
	}
