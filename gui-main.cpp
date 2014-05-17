#ifdef __WAND__

target[
	name[
		gui.exe
	]
	type[
		application
	]
	platform[
		;Windows
	]
]
#endif
#ifdef __WAND__

target[
	name[
		gui
	]
	type[
		application
	]
]
#endif


#include "test.h"

#include <herbs/maindefault/maindefault.h>
#include <utility>

Herbs::Application* Herbs::Application::instanceCreate(Herbs::LogWriter& log
	,Herbs::Directory&& dir)
	{
	return new Gui::Test(log,std::move(dir));
	}
