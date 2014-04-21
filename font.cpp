#ifdef __WAND__
target[type[object]name[font.o] platform[;Windows] dependency[gdi32;external]]
#endif

#include "font.h"
#include <windows.h>

Gui::Font::Font(void* h):handle(h)
	{}

Gui::Font::~Font()
	{
	if(handle!=nullptr)
		{DeleteObject(handle);}
	}

Gui::Font Gui::Font::fromThemeGet(Element e)
	{
	NONCLIENTMETRICS ncm;
	ncm.cbSize=sizeof(ncm);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS,0,&ncm,0);

	switch(e)
		{
		case Element::CAPTION:
			return Font(CreateFontIndirect(&ncm.lfCaptionFont));
		case Element::CAPTION_SMALL:
			return Font(CreateFontIndirect(&ncm.lfSmCaptionFont));
		case Element::MESSAGE:
			return Font(CreateFontIndirect(&ncm.lfMessageFont));
		case Element::ICON:
		case Element::WIDGET:
			return Font(CreateFontIndirect(&ncm.lfMenuFont));
		case Element::TOOLTIP:
			return Font(CreateFontIndirect(&ncm.lfStatusFont));
		}
	abort();
	}