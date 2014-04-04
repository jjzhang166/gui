#ifdef __WAND__
dependency[toolbar.o]
target[name[toolbar.h] type[include]]
#endif

#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "window-system.h"

namespace Gui
	{
	class Toolbar:public WindowSystem
		{
		public:
			static void init();
			
			Toolbar& buttonAdd(const char_t* text);
			
			Toolbar& toggleAdd(const char_t* text);
			
			static Toolbar* create(Gui& gui_obj
				,uint32_t style_0,uint32_t style_1,Window* parent)
				{return new Toolbar(gui_obj,style_0,style_1,parent);}
		
		protected:
			Toolbar(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);

		private:
			unsigned int n_buttons;
		};
	};
	
#endif
