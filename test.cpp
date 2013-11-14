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
#include "blitter.h"

#include <cstdio>

namespace
	{
	void fill(Herbs::MatrixStorage<Gui::Blitter::PixelBGRA<float> >& img)
		{
		for(size_t k=0;k<img.nRowsGet();++k)
			{
			for(size_t l=0;l<img.nColsGet();++l)
				{
				img(k,l).blue=float(l)/img.nColsGet();
				img(k,l).green=0;
				img(k,l).red=0;
				}
			}
		}
	
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
				,img(256,256)
				{
				Gui::Toolbar* tools=Gui::Toolbar::create(gui_obj,0
					,Window::StyleChild|Window::StyleVisible,this);
				tools->buttonAdd(STR("Hello")).buttonAdd(STR("World"));
				firstSet(*tools);
				
				Gui::Blitter* blitter=Gui::Blitter::create(gui_obj
					,0
					,Window::StyleBorder|Window::StyleChild|Window::StyleVisible
					,this);
				secondSet(*blitter);
				blitter->pixelsSet(img);
				fill(img);
				}
			
			Herbs::MatrixStorage<Gui::Blitter::PixelBGRA<float> > img;
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


	
