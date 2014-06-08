#ifdef __WAND__
target[name[logwriter_msgbox.o]type[object]]
#endif

#include "logwriter_msgbox.h"
#include "dialog.h"
#include "window.h"

Gui::LogwriterMsgbox::LogwriterMsgbox():owner(nullptr)
	{}

void Gui::LogwriterMsgbox::write(const Herbs::LogMessage& message)
	{
	Dialog::messageDisplay(owner,message,owner->titleGet().begin());
	}
