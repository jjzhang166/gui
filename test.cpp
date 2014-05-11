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
#include "fader_impl.h"
#include "font.h"
#include "textinput.h"
#include "label.h"
#include "combobox.h"

namespace
	{
	class LengthMap:public MathExt::ValueMap<double>
		{
		public:
			double forward(const double& x) const
				{return x;}
			
			double backward(const double& x) const
				{return x;}
			
			MathExt::Interval<double> domain() const
				{return {0,1};}
			
			MathExt::Interval<double> range() const
				{return {0,1};}
		};
	
	class Testwin:public Gui::WindowCustom
		{
		public:
			static Testwin* create(Gui::Gui& gui_obj)
				{
				return new Testwin(gui_obj);
				}
				
			void onCommand(uint32_t event_status,uint32_t control_id,Window& source)
				{
				}
				
			size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1)
				{
				switch(event_type)
					{
					case Window::MessageSize:
						{
						
						name_label->sizeRelative(1.0,0);
						auto size=name_label->sizeWindowGet();
						float row=0.5*size.y;
						name_label->moveAbsolute({-1.0,-1.0},{0.0,row});
						row+=size.y+0.25*size.y;
						name_input->sizeRelative(1.0,0);
						name_input->moveAbsolute({-1.0,-1.0},{0.0,row});
						size=name_input->sizeWindowGet();
						row+=size.y+0.5*size.y;
						
						mass_label->sizeRelative(1.0,0);
						size=mass_label->sizeWindowGet();
						mass_label->moveAbsolute({-1.0,-1.0},{0.0,row});
						row+=size.y+0.25*size.y;
						mass_input->sizeRelative(1.0,0);
						mass_input->moveAbsolute({-1.0,-1.0},{0.0,row});
						size=mass_input->sizeWindowGet();
						row+=size.y+0.5*size.y;
						
						length_label->sizeRelative(1.0,0);
						size=length_label->sizeWindowGet();
						length_label->moveAbsolute({-1.0,-1.0},{0.0,row});
						row+=size.y+0.25*size.y;
						length_input->sizeRelative(1.0,0);
						length_input->moveAbsolute({-1.0,-1.0},{0.0,row});
						size=length_input->sizeWindowGet();
						row+=size.y+0.5*size.y;
						
						gender_label->sizeRelative(1.0,0);
						size=length_label->sizeWindowGet();
						gender_label->moveAbsolute({-1.0,-1.0},{0.0,row});
						row+=size.y+0.25*size.y;
						gender_input->sizeRelative(1.0,0);
						gender_input->moveAbsolute({-1.0,-1.0},{0.0,row});
						size=gender_input->sizeWindowGet();
						row+=size.y+0.5*size.y;	
						}
						break;
					}
				return WindowCustom::onEvent(event_type,param_0,param_1);
				}
				
		private:
			Testwin(Gui::Gui& gui_obj):Gui::WindowCustom(gui_obj,0,0,nullptr)
				,label_font(Gui::Font::fromThemeGet(Gui::Font::Element::CAPTION_SMALL))
				,content_font(Gui::Font::fromThemeGet(Gui::Font::Element::WIDGET))
				{
			/*	tools=Gui::Toolbar::create(gui_obj,0
					,Window::StyleChild|Window::StyleVisible,this);
				tools->buttonAdd(STR("Hello")).buttonAdd(STR("World"));*/
				
					{
					name_label=Gui::Label::create(gui_obj
						,0,Window::StyleBorder|Window::StyleChild|Window::StyleVisible,this);
					name_label->titleSet(STR("Name"));
					name_label->fontChangeRequest(label_font);
				
					name_input=Gui::TextInput::create(gui_obj
						,0,Window::StyleBorder|Window::StyleChild|Window::StyleVisible,this);
					name_input->fontChangeRequest(content_font);
					}
					
					{
					mass_label=Gui::Label::create(gui_obj
						,0,Window::StyleBorder|Window::StyleChild|Window::StyleVisible,this);
					mass_label->titleSet(STR("Mass/kg"));
					mass_label->fontChangeRequest(label_font);
				
					mass_input=Gui::TextInput::create(gui_obj
						,0,Window::StyleBorder|Window::StyleChild|Window::StyleVisible,this);
					mass_input->fontChangeRequest(content_font);
					}
					
					{
					length_label=Gui::Label::create(gui_obj
						,0,Window::StyleBorder|Window::StyleChild|Window::StyleVisible,this);
					length_label->titleSet(STR("Length/m"));
					length_label->fontChangeRequest(label_font);
			
					length_input=Gui::FaderImpl<double>::create(gui_obj
						,0,Window::StyleBorder|Window::StyleChild|Window::StyleVisible,this
						,length_map);
					length_input->fontChangeRequest(content_font);
					}
					
					{
					gender_label=Gui::Label::create(gui_obj
						,0,Window::StyleBorder|Window::StyleChild|Window::StyleVisible,this);
					gender_label->titleSet(STR("Gender"));
					gender_label->fontChangeRequest(label_font);
					
					gender_input=Gui::Combobox::create(gui_obj
						,0,Window::StyleBorder|Window::StyleChild|Window::StyleVisible,this);
					gender_input->fontChangeRequest(content_font);
					
					gender_input->itemAdd(STR("Male"))
						.itemAdd(STR("Female"))
						.itemAdd(STR("Hermaphrodite"))
						.itemSelect(0);
					}
					
					
				}
			
			Gui::Label* name_label;
			Gui::TextInput* name_input;
			
			Gui::Label* mass_label;
			Gui::TextInput* mass_input;
			
			Gui::Label* length_label;
			Gui::FaderImpl<double>* length_input;
			LengthMap length_map;
			
			Gui::Label* gender_label;
			Gui::Combobox* gender_input;

			Gui::Font label_font;
			Gui::Font content_font;
			
		};
	}

void Gui::Test::init(Herbs::Directory&& dir)
	{
	WindowCustom::init();
	Toolbar::init();
	mainwin=Testwin::create(*this);
	mainwin->popup();
	mainwin->titleSet(STR("Gui test"));
	mainwin->sizeRelative(0.61,0.61);
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


	
