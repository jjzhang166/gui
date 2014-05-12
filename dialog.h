#ifdef __WAND__
target[name[dialog.h] type[include]]
dependency[dialog.o]
#endif

#ifndef GUI_DIALOG_H
#define GUI_DIALOG_H

#include <herbs/path/path.h>

namespace Gui
	{
	class Window;
	class Dialog
		{
		public:
			enum class MessageType:unsigned int
				{
				 INFORMATION
				,WARNING
				,ERROR
				};
			enum class MessageStatus:unsigned int
				{
				 OK
				,CANCEL
				,YES
				,NO
				};
			static MessageStatus messageDisplay(Window* parent,const char_t* message
				,const char_t* caption,MessageType type);
			
			static bool filenameGet(Window* parent,Herbs::Path& path_in,bool write);
		};
	}

#endif
