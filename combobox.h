#ifdef __WAND__
dependency[combobox.o]
target[name[combobox.h] type[include]]
#endif

#ifndef GUI_COMBOBOX_H
#define GUI_COMBOBOX_H

#include "window-system.h"

namespace Gui
	{
	class Combobox:public WindowSystem
		{
		public:
			static void init();
			
			static Combobox* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent)
				{return new Combobox(gui_obj,style_0,style_1,parent);}
				
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1);
			
			Combobox& itemAdd(const char_t* label);
			
			Combobox& itemSelect(size_t index);
			
			size_t itemSelectedGet() const;
		
		protected:
			Combobox(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);

		private:
			Vector::Vector2d<int> size_min;
		};
	};
	
#endif
