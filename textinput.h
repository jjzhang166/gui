#ifdef __WAND__
dependency[textinput.o]
target[name[textinput.h] type[include]]
#endif

#ifndef GUI_TEXTINPUT_H
#define GUI_TEXTINPUT_H

#include "window-system.h"

namespace Gui
	{
	class TextInput:public WindowSystem
		{
		public:
			static void init();
			
			static TextInput* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent)
				{return new TextInput(gui_obj,style_0,style_1,parent);}
				
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1);
		
		protected:
			TextInput(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);
		};
	};
	
#endif
