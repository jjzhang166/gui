#ifdef __WAND__
target[name[blitter.o] type[object] dependency[gdi32;external] platform[;Windows]]
#endif

#include "blitter.h"
#include <windows.h>

namespace
	{
	void draw(
		 HDC dc_out
		,const Vector::MatrixStorage<Gui::Blitter::PixelBGRA<uint8_t> >& image_out
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
	thread_lock=(CRITICAL_SECTION*)Herbs::malloc<CRITICAL_SECTION>(1);
	InitializeCriticalSection((CRITICAL_SECTION*)thread_lock);
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
			EnterCriticalSection((CRITICAL_SECTION*)thread_lock);
			image_out.resize(size_this.y,size_this.x);
			LeaveCriticalSection((CRITICAL_SECTION*)thread_lock);
			bitmapCopy();
			}
			break;
		}
	return WindowCustom::onEvent(event_type,param_0,param_1);
	}
	
void Gui::Blitter::pixelsSet(const Vector::MatrixStorage<PixelBGRA<float> >& bitmap)
	{
	image_in=&bitmap;
	bitmapCopy();
	draw((HDC)dc_out,image_out);
	}

void Gui::Blitter::bitmapCopy()
	{
	if(image_in!=nullptr)
		{
		EnterCriticalSection((CRITICAL_SECTION*)thread_lock);
		float sx=float(image_in->nColsGet())/image_out.nColsGet();
		float sy=float(image_in->nRowsGet())/image_out.nRowsGet();
		for(size_t k=0;k<image_out.nRowsGet();++k)
			{
			for(size_t l=0;l<image_out.nColsGet();++l)
				{
				size_t sk=(size_t)(sy*k);
				size_t sl=(size_t)(sx*l);
				image_out(k,l).blue=255* (*image_in)(sk,sl).blue;
				image_out(k,l).green=255* (*image_in)(sk,sl).green;
				image_out(k,l).red=255* (*image_in)(sk,sl).red;
				image_out(k,l).alpha=255;
				}
			}
		LeaveCriticalSection((CRITICAL_SECTION*)thread_lock);
		}
	}
	
Gui::Blitter::~Blitter()
	{
	Herbs::free((CRITICAL_SECTION*)thread_lock);
	ReleaseDC((HWND)handle,(HDC)dc_out);
	}
