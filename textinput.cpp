#ifdef __WAND__
target[name[textinput.o] type[object] platform[;Windows]]
#endif

#include "textinput.h"

#include <windows.h>
#include <algorithm>


Gui::TextInput::TextInput(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent):
	WindowSystem(gui_obj,STR("EDIT"),style_0,style_1,parent)
	{
	}


size_t Gui::TextInput::onEvent(uint32_t event_type,size_t param_0,size_t param_1)
	{
	switch(event_type)
		{	
		case MessageSize:
			{	
			RECT r;
			SendMessage((HWND)handle,EM_GETRECT,0,(LPARAM)&r);
			auto size=sizeWindowGet();
			sizeAbsolute(size.x,std::max(size.y,2+abs(r.top)+abs(r.bottom)));
			}
			break;
		}
	return WindowSystem::onEvent(event_type,param_0,param_1);
	}