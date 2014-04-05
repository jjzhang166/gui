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

int Gui::Gui::run()
	{
	MSG message;
/*	TODO: load all fonts from the NONCLIENTMETRICS object
	NONCLIENTMETRICS ncm;
	ncm.cbSize=sizeof(ncm);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS,0,&ncm,0);
*/
	while(window_count)
		{
		if(GetMessage(&message, NULL, 0, 0) > 0)
			{
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


	
