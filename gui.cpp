#ifdef __WAND__

target[
	name[
		gui.o
	]
	type[
		object
	]
	platform[;Windows]
]
#endif

#include "gui.h"
#include <windows.h>
#include <cstdio>

int Gui::Gui::run()
	{
	MSG message;

	while(window_count)
		{
		if(GetMessage(&message, NULL, 0, 0) > 0)
			{
			if(dialog_active!=NULL)
				{
				if(IsDialogMessage((HWND)dialog_active,&message))
					{continue;}
				}
			TranslateMessage(&message);
			DispatchMessage(&message);	
			}
		else
			{return message.wParam;}
		}
	return 0;
	}

Gui::Gui::~Gui()
	{
	}
	
void Gui::Gui::destroy()
	{
	delete this;
	}


	
