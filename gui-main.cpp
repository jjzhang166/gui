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

Herbs::Application* Herbs::Application::instanceCreate()
	{
	return new Gui::Test();
	}
