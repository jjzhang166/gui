#ifdef __WAND__
target[name[label.o] type[object] platform[;Windows]]
#endif

#include "label.h"

#include <windows.h>
#include <algorithm>

namespace
	{	
	static const uint32_t SIZE_UPDATE=STM_MSGMAX;
	}

Gui::Label::Label(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent):
	WindowSystem(gui_obj,STR("STATIC"),style_0,style_1,parent)
	{
	}

size_t Gui::Label::onEvent(uint32_t event_type,size_t param_0,size_t param_1)
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
			sizeAbsolute(std::max(size.x,size_min.x),std::max(size.y,size_min.y));
			}
			break;
		case SIZE_UPDATE:
			size_min=sizeContent();
			SendMessage((HWND)handle,MessageSize,0,0);
			SendMessage(GetParent((HWND)handle),MessageSize,0,0);
			break;
		}
	return WindowSystem::onEvent(event_type,param_0,param_1);;
	}