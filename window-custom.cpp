#ifdef __WAND__
target[name[window-custom.o] type[object]]
#endif

#include "window-custom.h"
#include <herbs/exceptionmissing.h>
#include <windows.h>

namespace
	{
	static const charsys_t* classname=STRSYS("Gui::WindowCustom::baseclassname");
	static const charsys_t* propname=STRSYS("Gui::WindowCustom::data");
	
	LRESULT CALLBACK eventCallback(HWND handle,UINT event_type
		,WPARAM param_0,LPARAM param_1)
		{
		Gui::WindowCustom* obj=(Gui::WindowCustom*)GetProp(handle,propname);
		if(obj==nullptr)
			{return DefWindowProc(handle,event_type,param_0,param_1);}
		switch(event_type)
			{
			case WM_DESTROY:
				delete obj;
				break;
			default:
				return obj->onEvent(event_type,param_0,param_1);
			}
		return DefWindowProc(handle,event_type,param_0,param_1);
		}	
	
	}
	
void Gui::WindowCustom::init()
	{
	WNDCLASSEX wndclass;
	ZeroMemory(&wndclass, sizeof(wndclass));
	wndclass.cbSize=sizeof(wndclass);
	wndclass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hInstance=GetModuleHandle(NULL);
	wndclass.lpfnWndProc=eventCallback;
	wndclass.lpszClassName=classname;

	if(!RegisterClassEx(&wndclass))
		{
		throw Herbs::ExceptionMissing(___FILE__,__LINE__);
		}
	}

Gui::WindowCustom::WindowCustom(Gui& gui_obj,uint32_t style_0,uint32_t style_1
	,Window* parent):Window(gui_obj)
	{
	create(classname,style_0,style_1,parent);
	SetProp((HWND)handle,propname,this);
	}

Gui::WindowCustom::~WindowCustom()
	{
	RemoveProp((HWND)handle,propname);
	}