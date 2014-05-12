#ifdef __WAND__
target[name[datetime.o] type[object] platform[;Windows]
dependency[comctl32;external]]
#endif

#include "datetime.h"
#include <herbs/intformat/intformat.h>
#include <windows.h>
#include <commctrl.h>
#include <algorithm>

namespace
	{
	static const uint32_t SIZE_UPDATE=DTM_FIRST-1;
	}
	
void Gui::Datetime::init()
	{
	INITCOMMONCONTROLSEX a;
	a.dwSize=sizeof(a);
	a.dwICC=ICC_DATE_CLASSES;
	InitCommonControlsEx(&a);
	}

Gui::Datetime::Datetime(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent):
	WindowSystem(gui_obj,DATETIMEPICK_CLASS,style_0
		,style_1
		,parent)
	{
	SendMessage((HWND)handle,DTM_SETFORMAT,0,(LPARAM)STRSYS("yyyy'-'MM'-'dd' 'H':'mm"));
	PostMessage((HWND)handle,SIZE_UPDATE,0,0);
	}

size_t Gui::Datetime::onEvent(uint32_t event_type,size_t param_0,size_t param_1)
	{
	switch(event_type)
		{
		case MessageSetfont:
			SendMessage((HWND)handle,DTM_SETMCFONT,param_0,param_1);
			PostMessage((HWND)handle,SIZE_UPDATE,0,0);
			break;
		case MessageSize:
			{
			WindowSystem::onEvent(event_type,param_0,param_1);
			auto size=sizeWindowGet();
			sizeAbsolute(std::max(size.x,size_min.x),std::max(size.y,size_min.y));
			return 0;
			}
			break;
		case SIZE_UPDATE:
			size_min=sizeContent()+Vector::Vector2d<int>{0,4};
			SendMessage((HWND)handle,MessageSize,0,0);
			SendMessage(GetParent((HWND)handle),MessageSize,0,0);
			break;
		}
	return WindowSystem::onEvent(event_type,param_0,param_1);
	}

Herbs::String Gui::Datetime::titleGet() const
	{
	SYSTEMTIME st;
	SendMessage((HWND)handle,DTM_GETSYSTEMTIME,0,(LPARAM)&st);
	
	Herbs::String ret(32);
	
	ret.append(Herbs::IntFormat<unsigned int>(st.wYear) ).append('-');
	if(st.wMonth<10)
		{ret.append('0');}
	
	ret.append(Herbs::IntFormat<unsigned int>(st.wMonth)).append('-');
	if(st.wDay<10)
		{ret.append(Herbs::IntFormat<unsigned int>(st.wDay)).append(' ');}
	
	ret.append(Herbs::IntFormat<unsigned int>(st.wHour)).append(':');
	if(st.wMinute<10)
		{ret.append('0');}
		
	ret.append(Herbs::IntFormat<unsigned int>(st.wMinute));

	return std::move(ret);
	}

void Gui::Datetime::timeSet(Herbs::Timestamp time)
	{
	SYSTEMTIME st;
	memset(&st,0,sizeof(st));
	st.wYear=time.yearGet();
	st.wMonth=time.monthGet();
	st.wDay=time.dayGet();
	st.wHour=time.hourGet();
	st.wMinute=time.minGet();
	SendMessage((HWND)handle,DTM_SETSYSTEMTIME,0,(LPARAM)&st);
	}

Herbs::Timestamp Gui::Datetime::timeGet() const
	{
	Herbs::Timestamp time;
	SYSTEMTIME st;
	SendMessage((HWND)handle,DTM_GETSYSTEMTIME,0,(LPARAM)&st);
	
	time.yearSet(st.wYear);
	time.monthSet(st.wMonth);
	time.daySet(st.wDay);
	time.hourSet(st.wHour);
	time.minSet(st.wMinute);
	time.secSet(0);
	
	return time;
	}


