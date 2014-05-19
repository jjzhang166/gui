#ifdef __WAND__
target[type[object]name[font.o] platform[;Windows] dependency[gdi32;external]]
#endif

#include "font.h"
#include <windows.h>

Gui::Font::~Font()
	{
	if(handle!=nullptr)
		{DeleteObject(handle);}
	}

Gui::Font::Font(Element e)
	{
	NONCLIENTMETRICS ncm;
	ncm.cbSize=sizeof(ncm);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS,0,&ncm,0);

	switch(e)
		{
		case Element::CAPTION:
			handle=CreateFontIndirect(&ncm.lfCaptionFont);
			break;
		case Element::CAPTION_SMALL:
			handle=CreateFontIndirect(&ncm.lfSmCaptionFont);
			break;
		case Element::MESSAGE:
			handle=CreateFontIndirect(&ncm.lfMessageFont);
			break;
		case Element::ICON:
		case Element::WIDGET:
			handle=CreateFontIndirect(&ncm.lfMenuFont);
			break;
			
		case Element::TOOLTIP:
			handle=CreateFontIndirect(&ncm.lfStatusFont);
			break;
		}
	}