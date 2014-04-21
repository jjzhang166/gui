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
#include "fader.h"
#include "font.h"

#include <cstdio>

namespace
	{
	class To_dB:public Gui::Fader::Fadefunc
		{
		public:
			To_dB():min_dB(-145),max_dB(6)
				{}
		
			double valueGet(uint32_t pos,uint32_t min,uint32_t max)
				{
				double x=double(pos - min)/double(max - min);
				return min_dB*(1.0-x) + x*max_dB;
				}
			
			uint32_t positionGet(double value,uint32_t min,uint32_t max)
				{
				double x=(value-min_dB)/(max_dB-min_dB);
				return uint32_t( x*max + (1-x)*min + 00.5);
				}
		
		private:
			double min_dB;
			double max_dB;
		};
		
	
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
				,font_label(Gui::Font::fromThemeGet(Gui::Font::Element::WIDGET))
				{
				Gui::Toolbar* tools=Gui::Toolbar::create(gui_obj,0
					,Window::StyleChild|Window::StyleVisible,this);
				tools->buttonAdd(STR("Hello")).buttonAdd(STR("World"));
				
				
				Gui::Fader* fader=Gui::Fader::create(gui_obj
					,0
					,Window::StyleBorder|Window::StyleChild|Window::StyleVisible
					,this,to_dB);
				
				fader->fontChangeRequest(font_label);
				fader->maxSet(0x7fff);
				fader->minSet(0);
				
				secondSet(*tools);
				firstSet(*fader);
				}
				
			To_dB to_dB;
			Gui::Font font_label;
		};
	}

void Gui::Test::init(Herbs::Directory&& dir)
	{
	WindowCustom::init();
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


	
