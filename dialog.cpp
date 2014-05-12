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

Gui::Dialog::MessageStatus Gui::Dialog::messageDisplay(Window* parent,const char_t* message
	,const char_t* caption,MessageType type)
	{
	HWND handle=(HWND)Window::handleGet(parent);
	
	unsigned int flags=0;
	
	//	Check if the caller asks a question
		{
		auto mptr=message;
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
	
	switch(type)
		{
		case MessageType::INFORMATION:
			flags|=MB_ICONINFORMATION;
			break;
		case MessageType::WARNING:
			flags|=MB_ICONWARNING;
			break;
		case MessageType::ERROR:
			flags|=MB_ICONERROR;
			break;
		}
		
	switch(MessageBox(handle,message,caption,flags))
		{
		case IDOK:
			return MessageStatus::OK;
		case IDCANCEL:
			return MessageStatus::CANCEL;
		case IDYES:
			return MessageStatus::YES;
		case IDNO:
			return MessageStatus::NO;
		default:
			return MessageStatus::CANCEL;
		}
	}

bool Gui::Dialog::filenameGet(Window* parent,Herbs::Path& path_in,bool write)
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
	ofn.Flags=OFN_ENABLESIZING|OFN_HIDEREADONLY|OFN_LONGNAMES|OFN_NOTESTFILECREATE
		|OFN_NODEREFERENCELINKS|OFN_PATHMUSTEXIST;
	
	if(!write)
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
