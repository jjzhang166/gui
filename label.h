#ifdef __WAND__
dependency[label.o]
target[name[label.h] type[include]]
#endif

#ifndef GUI_LABEL_H
#define GUI_LABEL_H

#include "window-system.h"

namespace Gui
	{
	class Label:public WindowSystem
		{
		public:
			static void init();
			
			static Label* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent)
				{return new Label(gui_obj,style_0,style_1,parent);}
				
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1);
		
		protected:
			Label(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);

		private:
			Vector::Vector2d<int> size_min;
		};
	};
	
#endif
