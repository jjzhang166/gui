#ifdef __WAND__
target[name[dialog.o] type[object] platform[;Windows]
dependency[comdlg32;external]
]
#endif

#include "dialog.h"
#include "window.h"
#include <herbs/stringsys/stringsys.h>
#include <windows.h>
#ifdef ERROR
#undef ERROR
#endif

unsigned int Gui::Dialog::messageDisplay(Window* parent
	,const Herbs::LogMessage& message
	,const char_t* caption)
	{
	HWND handle=(HWND)Window::handleGet(parent);
	
	int flags=0;
	
	switch(message.m_type)
		{
		case Herbs::LogMessage::Type::INFORMATION:
			flags=MB_ICONINFORMATION;
			break;
		case Herbs::LogMessage::Type::WARNING:
			flags=MB_ICONWARNING;
			break;
		case Herbs::LogMessage::Type::ERROR:
			flags=MB_ICONERROR;
			break;
		case Herbs::LogMessage::Type::NOT_SPECIFIED:
			flags=0;
			break;
		}
	
	//	Check if the caller asks a question
		{
		auto mptr=message.m_message;
		while(*mptr)
			{
			switch(*mptr)
				{
				case CHAR('?'):
				case CHAR('¿'):
				case CHAR('՞'):
				case CHAR(';'):
				case CHAR('؟'):
				case CHAR('？'):
				case CHAR('፧'):
				case CHAR('꘏'):
					flags|=MB_YESNOCANCEL;
				}
			++mptr;
			}
		}
		
	switch(MessageBox(handle,Herbs::bufferSysPtr(Herbs::stringsys(message.m_message))
		,Herbs::bufferSysPtr(Herbs::stringsys(caption)),flags))
		{
		case IDOK:
			return MESSAGESTATUS_OK;
		case IDCANCEL:
			return MESSAGESTATUS_CANCEL;
		case IDYES:
			return MESSAGESTATUS_YES;
		case IDNO:
			return MESSAGESTATUS_NO;
		default:
			return MESSAGESTATUS_CANCEL;
		}
	}

bool Gui::Dialog::prompt(Window* parent,const char_t* title
	,Herbs::Path& path_in,int mode)
	{
	bool ret;
	Herbs::StringSys path_str(0x7fff);
	if(path_in!=Herbs::Path(STR("")))
		{path_str.append(Herbs::StringSys(path_in));}
	
	OPENFILENAME ofn;
	memset(&ofn,0,sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner=(HWND)Window::handleGet(parent);
	ofn.lpstrFilter=STRSYS("Alla filer\0*.*\0\0");
	ofn.lpstrFile=path_str.begin();
	ofn.nMaxFile=0x7fff;
	ofn.lpstrTitle=Herbs::bufferSysPtr(Herbs::stringsys(title));
	ofn.Flags=OFN_ENABLESIZING|OFN_HIDEREADONLY|OFN_LONGNAMES|OFN_NOTESTFILECREATE
		|OFN_NODEREFERENCELINKS|OFN_PATHMUSTEXIST;
	
	if(mode==FILENAMEPROMPT_READ)
		{
		ofn.Flags|=OFN_FILEMUSTEXIST;
		ret=GetOpenFileName(&ofn);
		}
	else
		{
		ofn.Flags|=OFN_OVERWRITEPROMPT;
		ret=GetSaveFileName(&ofn);
		}
	path_str.lengthValidSet(Herbs::StringSys::count(ofn.lpstrFile));
	path_in=Herbs::Path(Herbs::stringloc(path_str));
	return ret;
	}
