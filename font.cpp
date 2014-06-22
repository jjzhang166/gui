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

void Gui::Font::fromElement(Element e,float scale_factor)
	{
	NONCLIENTMETRICS ncm;
	ncm.cbSize=sizeof(ncm);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS,0,&ncm,0);

	switch(e)
		{
		case Element::CAPTION:
			ncm.lfCaptionFont.lfHeight*=scale_factor;
			handle=CreateFontIndirect(&ncm.lfCaptionFont);
			break;
		case Element::CAPTION_SMALL:
			ncm.lfSmCaptionFont.lfHeight*=scale_factor;
			handle=CreateFontIndirect(&ncm.lfSmCaptionFont);
			break;
		case Element::MESSAGE:
			ncm.lfMessageFont.lfHeight*=scale_factor;
			handle=CreateFontIndirect(&ncm.lfMessageFont);
			break;
		case Element::ICON:
		case Element::WIDGET:
			ncm.lfMenuFont.lfHeight*=scale_factor;
			handle=CreateFontIndirect(&ncm.lfMenuFont);
			break;
			
		case Element::TOOLTIP:
			ncm.lfStatusFont.lfHeight*=scale_factor;
			handle=CreateFontIndirect(&ncm.lfStatusFont);
			break;
		}
	}