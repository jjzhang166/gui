#ifdef __WAND__

target[
	name[
		Gui.o
	]
	type[
		object
	]
]
#endif


#include "Gui.h"
#include "window-custom.h"
#include <windows.h>

void Gui::Gui::init()
	{
	WindowCustom::init();
	}

int Gui::Gui::run()
	{
	MSG message;
	while(window_count)
		{
		if(GetMessage(&message, NULL, 0, 0) > 0)
			{
			TranslateMessage(&message);
			DispatchMessage(&message);
			}
		else
			{break;}
		}
	return message.wParam;
	}

Gui::Gui::~Gui()
	{
	}
	
void Gui::Gui::destroy()
	{
	delete this;
	}


	
