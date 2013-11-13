#ifdef __WAND__
target[name[blitter.o] type[object] dependencies[gdi32]]
#endif

#include "blitter.h"
#include <windows.h>

namespace
	{
	void draw(
		 HDC dc_out
		,const Herbs::MatrixStorage<Gui::Blitter::PixelBGRA<uint8_t> >& image_out
		)
		{
		BITMAPINFO info;
		memset(&info,0,sizeof(info));
		info.bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
		info.bmiHeader.biWidth=image_out.nColsGet();
		info.bmiHeader.biHeight=image_out.nRowsGet();
		info.bmiHeader.biPlanes=1;
		info.bmiHeader.biBitCount=32;
		info.bmiHeader.biCompression=BI_RGB;
		SetDIBitsToDevice(dc_out,0,0,image_out.nColsGet(),image_out.nRowsGet()
			,0,0,0,image_out.nRowsGet(),image_out.rowGet(0),&info,DIB_RGB_COLORS);
		}
	}

Gui::Blitter::Blitter(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent):
	WindowCustom(gui_obj,style_0,style_1,parent),image_in(nullptr),image_out(1,1)
	{
	dc_out=GetDC((HWND)handle);
	}

size_t Gui::Blitter::onEvent(uint32_t event_type,size_t param_0,size_t param_1)
	{
	switch(event_type)
		{
		case MessagePaint:
			{
			PAINTSTRUCT ps;
			BeginPaint((HWND)handle,&ps);
			draw(ps.hdc,image_out);
			EndPaint((HWND)handle,&ps);
			}
			return 0;
		
		case MessageSize:
			{
			auto size_this=sizeClientFromParam1(param_1);
			image_out.resize(size_this.y,size_this.x);
			bitmapCopy();
			}
			break;
		}
	return doDefaultAction(event_type,param_0,param_1);
	}
	
void Gui::Blitter::pixelsSet(const Herbs::MatrixStorage<PixelBGRA<float> >& bitmap)
	{
	image_in=&bitmap;
	bitmapCopy();
	draw((HDC)dc_out,image_out);
	}

void Gui::Blitter::bitmapCopy()
	{
	if(image_in!=nullptr)
		{
		float sx=float(image_in->nColsGet())/image_out.nColsGet();
		float sy=float(image_in->nRowsGet())/image_out.nRowsGet();
		for(size_t k=0;k<image_out.nRowsGet();++k)
			{
			for(size_t l=0;l<image_out.nColsGet();++l)
				{
				
				image_out(k,l).blue=255* (*image_in)(sy*k,sx*l).blue;
				image_out(k,l).green=255* (*image_in)(sy*k,sx*l).green;
				image_out(k,l).red=255* (*image_in)(sy*k,sx*l).red;
				image_out(k,l).alpha=255;
				}
			}
		}
	}
	
Gui::Blitter::~Blitter()
	{
	ReleaseDC((HWND)handle,(HDC)dc_out);
	}
