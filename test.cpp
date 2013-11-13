#ifdef __WAND__

target[
	name[
		test.o
	]
	type[
		object
	]
]
#endif


#include "test.h"
#include "viewsplit.h"
#include "toolbar.h"

#include <cstdio>

namespace
	{
	class Testwin:public Gui::ViewSplit
		{
		public:
			static Testwin* create(Gui::Gui& gui_obj)
				{
				return new Testwin(gui_obj);
				}
				
			void onCommand(uint32_t event_status,uint32_t control_id,Window& source)
				{
				}
				
		private:
			Testwin(Gui::Gui& gui_obj):Gui::ViewSplit(gui_obj,0,0,nullptr)
				{
				Gui::Toolbar* tools=Gui::Toolbar::create(gui_obj,0
					,Window::StyleChild|Window::StyleVisible,this);
				tools->buttonAdd(STR("Hello")).buttonAdd(STR("World"));
				firstSet(*tools);
				
				Gui::WindowSystem* textbox=Gui::WindowSystem::create(gui_obj
					,STRSYS("EDIT"),0
					,Window::StyleBorder|Window::StyleChild|Window::StyleVisible
					,this);
				secondSet(*textbox);
				}
		};
	}

void Gui::Test::init(Herbs::Directory&& dir)
	{
	Gui::init();
	Toolbar::init();
	mainwin=Testwin::create(*this);
	mainwin->popup();
	mainwin->sizeRelative(0.61,0.61);
	mainwin->titleSet(STR("Gui test"));
	mainwin->moveRelative(Vector::Vector2d<float>(0,0)
		,Vector::Vector2d<float>(0.5,0.5));
	mainwin->show(Window::DisplayNormal);
	}

Gui::Test::~Test()
	{
	}
	
void Gui::Test::destroy()
	{
	delete this;
	}


	
