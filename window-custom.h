#ifdef __WAND__
dependencies[window-custom.o]
target[name[window-custom.h] type[include]]
#endif

#ifndef WINDOWCUSTOM_H
#define WINDOWCUSTOM_H

#include "window.h"

namespace Gui
	{
	class WindowCustom:public Window
		{
		public:
			/**Prepares use of WindowCustom
			*/
			static void init();
			
			/**This method is called when an GUI event occurs.
			*/
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1)=0;
			
			virtual ~WindowCustom();
			
		protected:
			WindowCustom(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);
			
		private:			
			static size_t eventCallback(void* handle,uint32_t event_type
				,size_t param_0,size_t param_1);			
		};
	}

#endif
