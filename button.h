#ifdef __WAND__
dependency[button.o]
target[name[button.h] type[include]]
#endif

#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "window-system.h"

namespace Gui
	{
	class Button:public WindowSystem
		{
		public:
			static void init();
			
			static Button* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent)
				{return new Button(gui_obj,style_0,style_1,parent);}
				
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1);
			
			void sizeMinimize();
		
		protected:
			Button(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);

		private:
			Vector::Vector2d<int> size_min;
		};
	};
	
#endif
