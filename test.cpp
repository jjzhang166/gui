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
#include "window-custom.h"

namespace
	{
	class Testwin:public Gui::WindowCustom
		{
		public:
			static Testwin* create(Gui::Gui& gui_obj)
				{
				return new Testwin(gui_obj);
				}
			
			size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1)
				{
				return doDefaultAction(event_type,param_0,param_1);
				}
		private:
			Testwin(Gui::Gui& gui_obj):Gui::WindowCustom(gui_obj,0,0,nullptr){}
		};
	}

void Gui::Test::init(Herbs::Directory&& dir)
	{
	Gui::init();
	mainwin=Testwin::create(*this);
	mainwin->popup();
	mainwin->sizeRelative(0.33,0.33);
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


	
