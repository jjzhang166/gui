#ifdef __WAND__
target[name[window-custom.o] type[object] platform[;Windows] dependency[gdi32;external]]
#endif

#include "window-custom.h"
#include "gui.h"
#include <herbs/exceptionmissing/exceptionmissing.h>
#include <windows.h>

namespace
	{
	static const charsys_t* classname=STRSYS("Gui::WindowCustom::baseclassname");
	
	LRESULT CALLBACK eventCallback(HWND handle,UINT event_type
		,WPARAM param_0,LPARAM param_1)
		{
		Gui::WindowCustom* obj=(Gui::WindowCustom*)Gui::Window::objectGet(handle);
		if(obj==nullptr)
			{return DefWindowProc(handle,event_type,param_0,param_1);}
		
		try
			{
			switch(event_type)
				{
				case WM_COMMAND:
					{
					if(param_1!=0)
						{
						Gui::Window* source=Gui::Window::objectGet((HWND)param_1);
						if(source!=nullptr)
							{
							obj->onCommand(HIWORD(param_0),LOWORD(param_0),*source);
							return DefWindowProc(handle,event_type,param_0,param_1);
							}
						}
					return DefWindowProc(handle,event_type,param_0,param_1);
					}
					break;
					
				case WM_CTLCOLORSTATIC:
					return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
				
				case WM_DESTROY:
					delete obj;
					break;
					
				default:
					return obj->onEvent(event_type,param_0,param_1);
				}
			return DefWindowProc(handle,event_type,param_0,param_1);
			}
		catch(const Herbs::Exception& e)
			{
			e.print(obj->hostGet().sysout());
			return DefWindowProc(handle,event_type,param_0,param_1);
			}
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
	,Window* parent):Window(gui_obj,classname,style_0,style_1,parent)
	{
	
	}

Gui::WindowCustom::~WindowCustom()
	{
	}

size_t Gui::WindowCustom::onEvent(uint32_t event_type,size_t param_0,size_t param_1)
	{return DefWindowProc((HWND)handle,event_type,param_0,param_1);}