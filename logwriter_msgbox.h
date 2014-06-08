#ifdef __WAND__
target[name[logwriter_msgbox.h] type[include]]
dependency[logwriter_msgbox.o]
#endif

#ifndef GUI_LOGWRITER_MSGBOX_H
#define GUI_LOGWRITER_MSGBOX_H

#include <herbs/logwriter/logwriter.h>

namespace Gui
	{
	class Window;
	
	class LogwriterMsgbox:public Herbs::LogWriter
		{
		public:	
			LogwriterMsgbox();
			void ownerSet(Window* win)
				{owner=win;}
			void write(const Herbs::LogMessage& message);
			
		private:
			Window* owner;
		};
	}

#endif
