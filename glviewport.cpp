#ifdef __WAND__
target
	[
	name[glviewport.o] type[object]
	dependency[gdi32;external]
	dependency[opengl32;external]
	platform[;Windows]

	]
#endif

#include "glviewport.h"
#include <windows.h>
#include <herbs/exceptionmissing/exceptionmissing.h>


Gui::GlViewport::GlViewport(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent):
	WindowCustom(gui_obj,style_0,style_1,parent)
	{
	dc_out=GetDC((HWND)handle);
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd,0,sizeof(pfd));
	pfd.nSize=sizeof(pfd);
	pfd.nVersion=1;
	pfd.dwFlags=PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType=PFD_TYPE_RGBA;
	pfd.cDepthBits=16;
	pfd.iLayerType=PFD_MAIN_PLANE;
	
	int iFormat=ChoosePixelFormat((HDC)dc_out,&pfd);
	if(iFormat==0)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
	
	if(!SetPixelFormat((HDC)dc_out,iFormat,&pfd))
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
	
	rc=wglCreateContext((HDC)dc_out);
	if(rc==NULL)
		{throw Herbs::ExceptionMissing(___FILE__,__LINE__);}
		
	}

size_t Gui::GlViewport::onEvent(uint32_t event_type,size_t param_0,size_t param_1)
	{
	switch(event_type)
		{
		case MessagePaint:
			{
			PAINTSTRUCT ps;
			BeginPaint((HWND)handle,&ps);
			onRender();
			EndPaint((HWND)handle,&ps);
			}
			return 0;
		
		case MessageSize:
			{
			auto size_this=sizeClientFromParam1(param_1);
			onResize(size_this.x,size_this.y);
			onRender();
			}
			break;
		}
	return WindowCustom::onEvent(event_type,param_0,param_1);
	}
	
Gui::GlViewport::~GlViewport()
	{
	wglDeleteContext((HGLRC)dc_out);
	ReleaseDC((HWND)handle,(HDC)dc_out);
	}
	
void Gui::GlViewport::buffersSwap()
	{
	SwapBuffers((HDC)dc_out);
	}

void Gui::GlViewport::contextGrab()
	{
	render_mutex.begin();
	wglMakeCurrent((HDC)dc_out,(HGLRC)rc);
	}

void Gui::GlViewport::contextRelease()
	{
	wglMakeCurrent(NULL,NULL);
	render_mutex.end();
	}
