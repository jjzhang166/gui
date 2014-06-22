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
	WindowCustom(gui_obj,style_0,style_1,parent),image_in(1,1),image_out(1,1)
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
			Herbs::MutexBlockLW::Guard guard(resize_block);
			image_out.resize(size_this.y,size_this.x);
			bitmapCopy();
			}
			break;
		}
	return WindowCustom::onEvent(event_type,param_0,param_1);
	}
	
void Gui::Blitter::pixelsSet(const Vector::MatrixStorage<PixelBGRA<float> >& bitmap)
	{
	Herbs::MutexBlockLW::Guard guard(resize_block);
	image_in.resize(bitmap.nRowsGet(),bitmap.nColsGet());
	for(size_t k=0;k<image_in.nRowsGet();++k)
		{
		for(size_t l=0;l<image_in.nColsGet();++l)
			{
			image_in(k,l).blue =255*std::min(std::max(bitmap(k,l).blue,0.0f),1.0f);
			image_in(k,l).green=255*std::min(std::max(bitmap(k,l).blue,0.0f),1.0f);
			image_in(k,l).red  =255*std::min(std::max(bitmap(k,l).blue,0.0f),1.0f);
			image_in(k,l).alpha=255;
			}
		}
	bitmapCopy();
	PostMessage(NULL,WM_USER,0,0); //Fix Wine redraw issue
	}

void Gui::Blitter::pixelsSet(const Vector::MatrixStorage<float>& graymap)
	{
	Herbs::MutexBlockLW::Guard guard(resize_block);
	image_in.resize(graymap.nRowsGet(),graymap.nColsGet());
	for(size_t k=0;k<image_in.nRowsGet();++k)
		{
		for(size_t l=0;l<image_in.nColsGet();++l)
			{
			float v=std::min( std::max(graymap(k,l),0.0f), 1.0f);
			
			image_in(k,l).blue =255*v;
			image_in(k,l).green=255*v;
			image_in(k,l).red  =255*v;
			image_in(k,l).alpha=255;
			}
		}
	bitmapCopy();
	PostMessage(NULL,WM_USER,0,0); //Fix Wine redraw issue
	}

void Gui::Blitter::bitmapCopy()
	{
	if(image_in.nColsGet()!=0 && image_in.nRowsGet()!=0)
		{
		float s_x=float(image_in.nColsGet())/image_out.nColsGet();
		float s_y=float(image_in.nRowsGet())/image_out.nRowsGet();
		for(size_t k=0;k<image_out.nRowsGet();++k)
			{
			for(size_t l=0;l<image_out.nColsGet();++l)
				{
				size_t s_k=size_t(s_y*k);
				size_t s_l=size_t(s_x*l);
				image_out(k,l)=image_in(s_k,s_l);
				}
			}
		draw((HDC)dc_out,image_out);
		}
	}
	
Gui::Blitter::~Blitter()
	{
	ReleaseDC((HWND)handle,(HDC)dc_out);
	}
