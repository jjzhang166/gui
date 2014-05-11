#ifdef __WAND__
target[name[combobox.o] type[object] platform[;Windows]]
#endif

#include "combobox.h"

#include <herbs/stringsys/stringsys.h>
#include <windows.h>
#include <algorithm>

namespace
	{
	Vector::Vector2d<int> sizeGet(HWND handle)
		{
		SIZE s;
		size_t n=GetWindowTextLength(handle);
		Herbs::StringSys buffer(n);
		if(n!=0)
			{
			buffer.lengthValidSet(n);
			GetWindowText(handle,buffer.begin(),n+1);
			}
		else
			{buffer.append(CHARSYS('A'));}
		HDC dc=GetDC(handle);
		GetTextExtentPoint(dc,buffer.begin(),n,&s);
		ReleaseDC(handle,dc);
		return {s.cx,s.cy};
		}
	
	static const uint32_t SIZE_UPDATE=STM_MSGMAX;
	}

Gui::Combobox::Combobox(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent):
	WindowSystem(gui_obj,STR("COMBOBOX"),style_0
		,style_1|CBS_HASSTRINGS|CBS_DROPDOWNLIST|CBS_SIMPLE|WS_VSCROLL
		,parent)
	{
	}
	

Gui::Combobox& Gui::Combobox::itemAdd(const char_t* label)
	{
	SendMessage((HWND)handle,CB_ADDSTRING,0,(LPARAM)label);
	PostMessage((HWND)handle,SIZE_UPDATE,0,0);
	return *this;
	}
	
Gui::Combobox& Gui::Combobox::itemSelect(size_t index)
	{
	SendMessage((HWND)handle,CB_SETCURSEL,(WPARAM)index,0);
	return *this;
	}
	
size_t Gui::Combobox::itemSelectedGet() const
	{
	return SendMessage((HWND)handle,CB_GETCURSEL,0,0);
	}

size_t Gui::Combobox::onEvent(uint32_t event_type,size_t param_0,size_t param_1)
	{
	switch(event_type)
		{
		case MessageSetfont:
		case MessageSettext:
			PostMessage((HWND)handle,SIZE_UPDATE,0,0);
			break;
		case MessageSize:
			{
			auto size=sizeWindowGet();
			sizeAbsolute(std::max(size.x,size_min.x),std::max(size.y,8*size_min.y));
			}
			break;
		case SIZE_UPDATE:
			size_min=sizeGet((HWND)handle);
			SendMessage((HWND)handle,MessageSize,0,0);
			SendMessage(GetParent((HWND)handle),MessageSize,0,0);
			break;
		}
	return WindowSystem::onEvent(event_type,param_0,param_1);;
	}