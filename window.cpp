#ifdef __WAND__
target[name[window.o] type[object]]
#endif

#include "window.h"
#include "gui.h"

#include <herbs/exceptionmissing.h>
#include <herbs/stringsys.h>
#include <windows.h>

namespace
	{
	static const charsys_t* propname=STRSYS("Gui::Window::data");
	}

void* Gui::Window::handleGet(Window* win)
	{
	if(win==nullptr)
		{return NULL;}
	return win->handle;
	}

Gui::Window* Gui::Window::objectGet(void* handle)
	{
	return (Window*)GetProp((HWND)handle,propname);
	}

Gui::Window::Window(Gui& gui_obj,const charsys_t* classname,uint32_t style_0
	,uint32_t style_1,Window* parent):m_gui(gui_obj)
	{
	HWND handle_parent=(HWND)handleGet(parent);

	handle=CreateWindowEx(style_0,classname,STRSYS(""),style_1,0,0,0,0,handle_parent
		,NULL,GetModuleHandle(NULL),NULL);

	if(handle==nullptr)
		{
		throw Herbs::ExceptionMissing(___FILE__,__LINE__);
		}
	m_gui.windowCountInc();
	SetProp((HWND)handle,propname,this);
	}

Gui::Window::~Window()
	{
	RemoveProp((HWND)handle,propname);
	m_gui.windowCountDec();
	}
	
size_t Gui::Window::doDefaultAction(uint32_t event_type,size_t param_0,size_t param_1)
	{
	return DefWindowProc((HWND)handle,event_type,param_0,param_1);
	}

void Gui::Window::moveAbsolute(Vector::Vector2d<float> anchor
	,Vector::Vector2d<float> position)
	{
	RECT winrect;
	GetWindowRect((HWND)handle,&winrect);
	Vector::Vector2d<float> wh(float(winrect.right-winrect.left),float(winrect.bottom-winrect.top));
	Vector::Vector2d<float> pos_new=position - 0.5f*(wh + Vector::productHadamard(wh,anchor));
	MoveWindow((HWND)handle,round(pos_new.x),round(pos_new.y),round(wh.x),round(wh.y),TRUE);
	}

void Gui::Window::moveRelative(Vector::Vector2d<float> anchor,Vector::Vector2d<float> position)
	{
	HWND handle_parent=GetParent((HWND)handle);

	if(handle_parent==NULL)
		{handle_parent=GetDesktopWindow();}

	RECT winrect;
	GetClientRect(handle_parent,&winrect);
	Vector::Vector2d<float> wh(float(winrect.right-winrect.left),float(winrect.bottom-winrect.top));
	wh=Vector::productHadamard(wh,position);
	moveAbsolute(anchor,wh);
	}

void Gui::Window::sizeAbsolute(int width,int height)
	{
	RECT winrect;
	GetWindowRect((HWND)handle,&winrect);
	MoveWindow((HWND)handle,winrect.left,winrect.top,width,height,TRUE);
	}

void Gui::Window::sizeRelative(float width,float height)
	{
	HWND handle_parent=GetParent((HWND)handle);
	if(handle_parent==NULL)
		{handle_parent=GetDesktopWindow();}

	RECT winrect;
	GetClientRect(handle_parent,&winrect);
	Vector::Vector2d<float> wh(float(winrect.right-winrect.left),float(winrect.bottom-winrect.top));
	wh=Vector::productHadamard(wh,Vector::Vector2d<float>(width,height));
	sizeAbsolute(wh.x,wh.y);
	}

Vector::Vector2d<int> Gui::Window::sizeClientGet() const
	{
	RECT winrect;
	GetClientRect((HWND)handle,&winrect);
	return Vector::Vector2d<int>(winrect.right-winrect.left,winrect.bottom-winrect.top);
	}

Vector::Vector2d<int> Gui::Window::sizeClientFromParam1(size_t param_1)
	{
	return Vector::Vector2d<int>(LOWORD(param_1),HIWORD(param_1));
	}
	
Vector::Vector2d<int> Gui::Window::sizeWindowGet() const
	{
	RECT winrect;
	GetWindowRect((HWND)handle,&winrect);
	return Vector::Vector2d<int>(winrect.right-winrect.left,winrect.bottom-winrect.top);
	}

void Gui::Window::show(int options)
	{
	ShowWindow((HWND)handle,options);
	}

void Gui::Window::styleSet(uint32_t style_0,uint32_t style_1)
	{
	SetWindowLongPtr((HWND)handle,GWL_STYLE,style_1);
	SetWindowPos((HWND)handle,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	SetWindowLongPtr((HWND)handle,GWL_EXSTYLE,style_0);
	SetWindowPos((HWND)handle,HWND_TOP,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	if(style_1&WS_CHILD)
		{
		HWND owner=GetWindow((HWND)handle,GW_OWNER);
		SetParent((HWND)handle,owner);
		}
	else
		{SetParent((HWND)handle,NULL);}
	}

void Gui::Window::popup()
	{
	styleSet(0,WS_OVERLAPPEDWINDOW);
	}

void Gui::Window::titleSet(const char_t* title)
	{
	SetWindowText((HWND)handle,Herbs::bufferSysPtr(Herbs::stringsys(title)));
	}
	
void Gui::Window::idSet(uint32_t id_new)
	{SetWindowLongPtr((HWND)handle,GWLP_ID,(LONG_PTR)id_new);}

uint32_t Gui::Window::idGet() const
	{return GetWindowLongPtr((HWND)handle,GWLP_ID);}

