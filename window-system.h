#ifdef __WAND__
dependencies[window-system.o]
target[name[window-system.h] type[include]]
#endif

#ifndef WINDOWSYSTEM_H
#define WINDOWSYSTEM_H

#include "window.h"

namespace Gui
	{
	class WindowSystem:public Window
		{
		public:
			size_t doDefaultAction(uint32_t event_type,size_t param_0,size_t param_1);
			~WindowSystem();
			
			static WindowSystem* create(Gui& gui_obj,const charsys_t* classname,uint32_t style_0
				,uint32_t style_1,Window* parent)
				{return new WindowSystem(gui_obj,classname,style_0,style_1,parent);}
		
		protected:
			WindowSystem(Gui& gui_obj,const charsys_t* classname,uint32_t style_0
				,uint32_t style_1,Window* parent);

		private:
			typedef int (*Function)();
			Function winproc_old;
		};
	};
	
#endif
