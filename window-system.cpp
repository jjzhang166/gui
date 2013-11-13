#ifdef __WAND__
target[name[window-system.o] type[object]]
#endif

#include "window-system.h"
#include <herbs/exceptionmissing.h>
#include <windows.h>

namespace
	{	
	LRESULT CALLBACK eventCallback(HWND handle,UINT event_type
		,WPARAM param_0,LPARAM param_1)
		{
		Gui::WindowSystem* window=(Gui::WindowSystem*)Gui::Window::objectGet(handle);

		LRESULT ret=window->doDefaultAction(event_type,param_0,param_1);

		switch(event_type)
			{
			case WM_DESTROY:
				delete window;
				break;
			}
		return ret;
		}
	
	}
	
Gui::WindowSystem::WindowSystem(Gui& gui_obj,const charsys_t* classname
	,uint32_t style_0,uint32_t style_1,Window* parent):
	Window(gui_obj,classname,style_0,style_1,parent)
	{
	winproc_old=(Function)SetWindowLongPtr((HWND)handle,GWLP_WNDPROC,(LONG_PTR)eventCallback);
	}
	
size_t Gui::WindowSystem::doDefaultAction(uint32_t event_type,size_t param_0,size_t param_1)
	{
	return CallWindowProc((WNDPROC)winproc_old,(HWND)handle,event_type,param_0,param_1);
	}

Gui::WindowSystem::~WindowSystem()
	{
	SetWindowLongPtr((HWND)handle,GWLP_WNDPROC,(LONG_PTR)winproc_old); 
	}

