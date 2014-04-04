#ifdef __WAND__
dependency[window-custom.o]
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
			virtual size_t onEvent(uint32_t event_type,size_t param_0,size_t param_1)
				{return doDefaultAction(event_type,param_0,param_1);}
				
			/**This method is called when a user issues a command.
			*/
			virtual void onCommand(uint32_t event_status,uint32_t command_id,Window& source)
				{}
			
			virtual ~WindowCustom();
			
		protected:
			WindowCustom(Gui& gui_obj,uint32_t style_0,uint32_t style_1,Window* parent);
		};
	}

#endif
