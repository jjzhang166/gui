#ifdef __WAND__
target[name[dialog.h] type[include]]
dependency[dialog.o]
#endif

#ifndef GUI_DIALOG_H
#define GUI_DIALOG_H

#include <herbs/path/path.h>
#include <herbs/logmessage/logmessage.h>

namespace Gui
	{
	class Window;
	class Dialog
		{
		public:
			static const unsigned int MESSAGESTATUS_OK=1;
			static const unsigned int MESSAGESTATUS_CANCEL=2;
			static const unsigned int MESSAGESTATUS_YES=6;
			static const unsigned int MESSAGESTATUS_NO=7;

			static unsigned int messageDisplay(Window* parent
				,const Herbs::LogMessage& message
				,const char_t* caption);
				
			static const int FILENAMEPROMPT_READ=0;
			static const int FILENAMEPROMPT_WRITE=1;
			
			static bool prompt(Window* parent,Herbs::Path& path_in,int mode);
		};
	}

#endif

